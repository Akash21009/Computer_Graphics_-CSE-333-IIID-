#include "utils.h"

extern bool controlPointsUpdated;
extern bool controlPointsFinished;
extern int selectedControlPoint;

float selectionThreshold = 3.0f; // Select any control point within 3 pixels of vicinity.
std::vector<float> rawControlPoints; // Screen-space positions of control-points 

void cleanup(GLFWwindow* window){
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

void clearLines(std::vector<float> &points){
    points.clear();
    controlPointsUpdated = true;
}

void addControlPoint(std::vector<float> &points, float x, float y, int w, int h){
    float rescaled_x = -1.0 + ((1.0*x - 0) / (w - 0)) * (1.0 - (-1.0));
    float rescaled_y = -1.0 + ((1.0*(h - y) - 0) / (h - 0)) * (1.0 - (-1.0));
    points.push_back(rescaled_x);
    points.push_back(rescaled_y);
    points.push_back(0.0); // Z-coordinate

		rawControlPoints.push_back(x);
		rawControlPoints.push_back(y);
}

// Search nearest control point to (x, y) and set its index to
// selectedControlPoint (return true), else -1 (return false)
bool searchNearestControlPoint(float x, float y)
{
  size_t npts = rawControlPoints.size()/2;
  if(npts > 0) {
	  float _x, _y, dist2 = 0.0f;
		float thresh2 = selectionThreshold*selectionThreshold;
	  for(size_t i=0; i<npts; i++) {
			_x = rawControlPoints[2*i];
			_y = rawControlPoints[2*i+1];
			dist2 = (x-_x)*(x-_x) + (y-_y)*(y-_y);
			if(dist2 <= thresh2) {
			  selectedControlPoint = i;
				return 1;
			}
		}
	}

	selectedControlPoint = -1;
	return 0;
}

void editControlPoint(std::vector<float> &points, float x, float y, int w, int h){
    if(selectedControlPoint < 0) return;
		if(selectedControlPoint >= points.size()/3) return;

    float rescaled_x = -1.0 + ((1.0*x - 0) / (w - 0)) * (1.0 - (-1.0));
    float rescaled_y = -1.0 + ((1.0*(h - y) - 0) / (h - 0)) * (1.0 - (-1.0));
    points[selectedControlPoint*3] = rescaled_x;
    points[selectedControlPoint*3+1] = rescaled_y;
    points[selectedControlPoint*3+2] = 0.0; // Z-coordinate

		rawControlPoints[selectedControlPoint*2] = x;
		rawControlPoints[selectedControlPoint*2+1] = y;
}

void showOptionsDialog(std::vector<float> &points, ImGuiIO &io){
        ImGui::Begin("Toolbox", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
				ImGui::Text("Mouse Left Click: add/select control points");
				ImGui::Text("Mouse Right Click: switch mode from \'Add\' to \'Select\'");
				ImGui::Text("Mouse Left Drag: move selected control point");
				ImGui::Separator();
				ImGui::Text("Current mode: %s", controlPointsFinished?"\'Select\'":"\'Add\'");
				if(ImGui::Button("Clear")){
            // Clear points
            clearLines(points);
						rawControlPoints.clear();
						controlPointsFinished = false;
						selectedControlPoint = -1; // Deselect
        }
        
        ImGui::End();
}

void setVAO(unsigned int &VAO){
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

GLuint createShader(const char* filename, GLenum type)
{
    const GLchar* source = getShaderCode(filename);
    if (source == NULL) {
        fprintf(stderr, "Error opening %s: ", filename); perror("");
        return 0;
    }
    GLuint res = glCreateShader(type);
    glShaderSource(res, 1, &source, NULL);
    free((void*)source);

    glCompileShader(res);
    GLint compile_ok = GL_FALSE;
    glGetShaderiv(res, GL_COMPILE_STATUS, &compile_ok);
    if (compile_ok == GL_FALSE) {
        // fprintf(stderr, "%s:", filename);
        std::cout << "Error in compilation of :" << filename << std::endl;
        glDeleteShader(res);
        return 0;
    }

    return res;
}

const char * setGLSLVersion(){
    #if __APPLE__
    // GL 3.2 + GLSL 150
        const char* glsl_version = "#version 150";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
    #else
        // GL 3.0 + GLSL 130
        const char* glsl_version = "#version 130";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
    #endif

    return glsl_version;
}

int openGLInit(){
    #if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
    bool err = gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
    bool err = glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
    bool err = gladLoadGL() == 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD2)
    bool err = gladLoadGL(glfwGetProcAddress) == 0; // glad2 recommend using the windowing library loader instead of the (optionally) bundled one.
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
    bool err = false;
    glbinding::Binding::initialize();
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
    bool err = false;
    glbinding::initialize([](const char* name) { return (glbinding::ProcAddress)glfwGetProcAddress(name); });
#else
    bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
#endif
    if (err)
    {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        exit(1);
    }

    //Enable multisampling
    glEnable(GL_MULTISAMPLE);

    // Enable Blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set point size
    glPointSize(10.0f);
		glEnable(GL_POINT_SMOOTH);

    // Enable smooth point rendering
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

		return 1;
}

unsigned int createProgram(const char *vshader_filename, const char* fshader_filename)
{
    //Create shader objects
    GLuint vs, fs;
    if ((vs = createShader(vshader_filename, GL_VERTEX_SHADER))   == 0) return 0;
    if ((fs = createShader(fshader_filename, GL_FRAGMENT_SHADER)) == 0) return 0;

    //Creare program object and link shader objects
    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    GLint link_ok;
    glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
    if (!link_ok) {
        // fprintf(stderr, "glLinkProgram error:");
        // printLog(program);
        std::cout << "Linking error " << std::endl  ;
        glDeleteShader(vs);
        glDeleteShader(fs);
        glDeleteProgram(program);
        return 0;
    }
    return program;
}


char * getShaderCode(const char* filename)
{
    FILE* input = fopen(filename, "rb");
    if(input == NULL) return NULL;

    if(fseek(input, 0, SEEK_END) == -1) return NULL;
    long size = ftell(input);
    if(size == -1) return NULL;
    if(fseek(input, 0, SEEK_SET) == -1) return NULL;

    /*if using c-compiler: dont cast malloc's return value*/
    char *content = (char*) malloc( (size_t) size +1  );
    if(content == NULL) return NULL;

    fread(content, 1, (size_t)size, input);
    if(ferror(input)) {
        free(content);
        return NULL;
    }

    fclose(input);
    content[size] = '\0';
    return content;
}

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

GLFWwindow* setupWindow(int width, int height)
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        exit(0);

    // Decide GL+GLSL versions
    const char * glsl_version = setGLSLVersion();
    

    // Create window with graphics context
    glfwWindowHint(GLFW_SAMPLES, 4);
    GLFWwindow* window = glfwCreateWindow(width, height, "Assignment 01: Piecewise interpolating Bezier curve", NULL, NULL);
    if (window == NULL)
        exit(0);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Initialize OpenGL loader
    int status = openGLInit();
    if(!status){
        std::cout << "Initialized OpenGL succesfully " << std::endl;
    }
    std::cout<< "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    return window;
}


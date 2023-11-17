//Assignment 03: Lighting and shading

/*References
  Trackball: http://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Arcball
*/

#include "utils.h"

#define  GLM_FORCE_RADIANS
#define  GLM_ENABLE_EXPERIMENTAL

#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

//Globals
int screen_width = 640, screen_height=640;
GLint vModel_uniform, vView_uniform, vProjection_uniform;
//GLint vColor_uniform;
GLint lpos_world_uniform;
GLint eye_normal_uniform;
GLint spotlight_direction_uniform;
int vertices=12;
int indices;
glm::mat4 modelT, viewT, projectionT;//The model, view and projection transformations

double oldX, oldY, currentX, currentY;
bool isDragging=false;

void createCubeObject(unsigned int &, unsigned int &);
void createSphereObject(unsigned int &, unsigned int &, int , int);

void setupModelTransformation(unsigned int &);
void setupViewTransformation(unsigned int &);
void setupProjectionTransformation(unsigned int &);
glm::vec3 getTrackBallVector(double x, double y);

int main(int, char**)
{
    // Setup window
    GLFWwindow *window = setupWindow(screen_width, screen_height);
    ImGuiIO& io = ImGui::GetIO(); // Create IO object

    ImVec4 clearColor = ImVec4(0.0f, 0.0f, 0.0f, 0.00f);

    unsigned int shaderProgram = createProgram("./shaders/vshader.vs", "./shaders/fshader.fs");

    //Get handle to color variable in shader
    // vColor_uniform = glGetUniformLocation(shaderProgram, "vColor");
    // if(vColor_uniform == -1){
    //     fprintf(stderr, "Could not bind location: vColor\n");
    //     exit(0);
    // }
    lpos_world_uniform = glGetUniformLocation(shaderProgram, "lpos_world");
    if(lpos_world_uniform == -1){
        fprintf(stderr, "Could not bind location: lpos_world\n");
        exit(0);
    }
    eye_normal_uniform = glGetUniformLocation(shaderProgram, "eye_normal");
    if(eye_normal_uniform == -1){
        fprintf(stderr, "Could not bind location: eye_normal\n");
        exit(0);
    }
    spotlight_direction_uniform=glGetUniformLocation(shaderProgram,"direction");
        if(spotlight_direction_uniform==-1){
            fprintf(stderr,"Could not bind location: direction.\n");
        }

    glUseProgram(shaderProgram);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    setupModelTransformation(shaderProgram);
    setupViewTransformation(shaderProgram);
    setupProjectionTransformation(shaderProgram);

    // createCubeObject(shaderProgram, VAO);
    createSphereObject(shaderProgram, VAO, 40, 40);

    oldX = oldY = currentX = currentY = 0.0;
    int prevLeftButtonState = GLFW_RELEASE;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Get current mouse position
        int leftButtonState = glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT);
        double x,y;
        glfwGetCursorPos(window,&x,&y);
        if(leftButtonState == GLFW_PRESS && prevLeftButtonState == GLFW_RELEASE){
            isDragging = true;
            currentX = oldX = x;
            currentY = oldY = y;
        }
        else if(leftButtonState == GLFW_PRESS && prevLeftButtonState == GLFW_PRESS){
            currentX = x;
            currentY = y;
        }
        else if(leftButtonState == GLFW_RELEASE && prevLeftButtonState == GLFW_PRESS){
            isDragging = false;
        }

        // Rotate based on mouse drag movement
        prevLeftButtonState = leftButtonState;
        if(isDragging && (currentX !=oldX || currentY != oldY))
        {
            glm::vec3 va = getTrackBallVector(oldX, oldY);
            glm::vec3 vb = getTrackBallVector(currentX, currentY);

            float angle = acos(std::min(1.0f, glm::dot(va,vb)));
            glm::vec3 axis_in_camera_coord = glm::cross(va, vb);
            glm::mat3 camera2object = glm::inverse(glm::mat3(viewT*modelT));
            glm::vec3 axis_in_object_coord = camera2object * axis_in_camera_coord;
            modelT = glm::rotate(modelT, angle, axis_in_object_coord);
            glUniformMatrix4fv(vModel_uniform, 1, GL_FALSE, glm::value_ptr(modelT));

            oldX = currentX;
            oldY = currentY;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glUseProgram(shaderProgram);

        {
            ImGui::Begin("Information");                          
            ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(VAO); 
        
        // glUniform3f(vColor_uniform, 0.5, 0.5, 0.5);
        glUniform3f(lpos_world_uniform, 0.0, -50.0, -40.0);
            glUniform3f(eye_normal_uniform, 0.0, -50.0, -40.0);

        glUniform3f(spotlight_direction_uniform,628.0,625.0,0.0);
        glDrawArrays(GL_TRIANGLES, 0, vertices*3);
        // Use the EBO to draw the sphere
        glDrawElements(GL_TRIANGLES, indices, GL_UNSIGNED_INT, 0);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);

    }

    // Cleanup
    cleanup(window);

    return 0;
}

void createCubeObject(unsigned int &program, unsigned int &cube_VAO)
{
    glUseProgram(program);

    //Bind shader variables
    int vVertex_attrib = glGetAttribLocation(program, "vVertex");
    if(vVertex_attrib == -1) {
        fprintf(stderr, "Could not bind location: vVertex\n");
        exit(0);
    }

    //Cube data
    GLfloat cube_vertices[] = {10, 10, -10, -10, 10, -10, -10, -10, -10, 10, -10, -10, //Front
                   10, 10, 10, -10, 10, 10, -10, -10, 10, 10, -10, 10}; //Back
    GLushort cube_indices[] = {
                0, 1, 2, 0, 2, 3, //Front
                4, 7, 5, 5, 7, 6, //Back
                1, 6, 2, 1, 5, 6, //Left
                0, 3, 4, 4, 7, 3, //Right
                0, 4, 1, 4, 5, 1, //Top
                2, 6, 3, 3, 6, 7 //Bottom
                };

    //Generate VAO object
    glGenVertexArrays(1, &cube_VAO);
    glBindVertexArray(cube_VAO);

    //Create VBOs for the VAO
    //Position information (data + format)
    int nVertices = (6*2)*3; //(6 faces) * (2 triangles each) * (3 vertices each)
    GLfloat *expanded_vertices = new GLfloat[nVertices*3];
    for(int i=0; i<nVertices; i++) {
        expanded_vertices[i*3] = cube_vertices[cube_indices[i]*3];
        expanded_vertices[i*3 + 1] = cube_vertices[cube_indices[i]*3+1];
        expanded_vertices[i*3 + 2] = cube_vertices[cube_indices[i]*3+2];
    }
    GLuint vertex_VBO;
    glGenBuffers(1, &vertex_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_VBO);
    glBufferData(GL_ARRAY_BUFFER, nVertices*3*sizeof(GLfloat), expanded_vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(vVertex_attrib);
    glVertexAttribPointer(vVertex_attrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    delete []expanded_vertices;

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); //Unbind the VAO to disable changes outside this function.
}
void createSphereObject(unsigned int &program, unsigned int &VAO, int longitudinalLines, int latitudinalLines) {
    glUseProgram(program);

    int vVertexAttrib = glGetAttribLocation(program, "vVertex");
    if (vVertexAttrib == -1) {
        fprintf(stderr, "Could not bind location: vVertex\n");
        exit(0);
    }

    int vNormalAttrib = glGetAttribLocation(program, "vNormal");
    if (vNormalAttrib == -1) {
        fprintf(stderr, "Could not bind location: vNormal\n");
        exit(0);
    }

    float radius = 15.0f; // Updated radius

    std::vector<GLfloat> sphereVertices;
    std::vector<GLuint> sphereIndices;
    std::vector<GLfloat> sphereNormals;

    float fR = 1.0f / static_cast<float>(longitudinalLines - 1);
    float fS = 1.0f / static_cast<float>(latitudinalLines - 1);

    for (int r = 0; r < longitudinalLines; ++r) {
        for (int s = 0; s < latitudinalLines; ++s) {
            float phi = glm::pi<float>() * r * fR;
            float theta = 2 * glm::pi<float>() * s * fS;

            float x = radius * sin(phi) * cos(theta);
            float y = radius * sin(phi) * sin(theta);
            float z = radius * cos(phi);

            sphereVertices.push_back(x);
            sphereVertices.push_back(y);
            sphereVertices.push_back(z);

            glm::vec3 d_theta = glm::vec3(-radius*glm::sin(phi)*glm::sin(theta), radius*glm::sin(phi)*glm::cos(theta),0.0f);
            glm::vec3 d_phi = glm::vec3(radius*glm::cos(phi)*glm::cos(theta), radius*glm::cos(phi)*glm::sin(theta),-radius*glm::sin(phi));

            glm::vec3 normal = glm::normalize(glm::cross(d_theta, d_phi));
            sphereNormals.push_back(normal.x);
            sphereNormals.push_back(normal.y);
            sphereNormals.push_back(normal.z);
        }
    }

    for (int r = 0; r < longitudinalLines - 1; ++r) {
        for (int s = 0; s < latitudinalLines - 1; ++s) {
            sphereIndices.push_back(r * latitudinalLines + s);
            sphereIndices.push_back(r * latitudinalLines + (s + 1));
            sphereIndices.push_back((r + 1) * latitudinalLines + s);

            sphereIndices.push_back((r + 1) * latitudinalLines + s);
            sphereIndices.push_back(r * latitudinalLines + (s + 1));
            sphereIndices.push_back((r + 1) * latitudinalLines + (s + 1));
        }
    }

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    int nVertices = static_cast<int>(sphereVertices.size() / 3);

    vertices=nVertices;
    indices = sphereIndices.size();

    GLuint vertexVBO;
    glGenBuffers(1, &vertexVBO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, sphereVertices.size() * sizeof(GLfloat), sphereVertices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(vVertexAttrib);
    glVertexAttribPointer(vVertexAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

    GLuint normalsVBO;
    glGenBuffers(1, &normalsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
    glBufferData(GL_ARRAY_BUFFER, sphereNormals.size() * sizeof(GLfloat), sphereNormals.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(vNormalAttrib);
    glVertexAttribPointer(vNormalAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphereIndices.size() * sizeof(GLuint), sphereIndices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}





void setupModelTransformation(unsigned int &program)
{
    //Modelling transformations (Model -> World coordinates)
    modelT = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));//Model coordinates are the world coordinates

    //Pass on the modelling matrix to the vertex shader
    glUseProgram(program);
    vModel_uniform = glGetUniformLocation(program, "vModel");
    if(vModel_uniform == -1){
        fprintf(stderr, "Could not bind location: vModel\n");
        exit(0);
    }
    glUniformMatrix4fv(vModel_uniform, 1, GL_FALSE, glm::value_ptr(modelT));
}


void setupViewTransformation(unsigned int &program)
{
    //Viewing transformations (World -> Camera coordinates
    //Camera at (0, 0, 100) looking down the negative Z-axis in a right handed coordinate system
    viewT = glm::lookAt(glm::vec3(40.0, -40.0, 40.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

    //Pass-on the viewing matrix to the vertex shader
    glUseProgram(program);
    vView_uniform = glGetUniformLocation(program, "vView");
    if(vView_uniform == -1){
        fprintf(stderr, "Could not bind location: vView\n");
        exit(0);
    }
    glUniformMatrix4fv(vView_uniform, 1, GL_FALSE, glm::value_ptr(viewT));
}

void setupProjectionTransformation(unsigned int &program)
{
    //Projection transformation
    projectionT = glm::perspective(45.0f, (GLfloat)screen_width/(GLfloat)screen_height, 0.1f, 1000.0f);

    //Pass on the projection matrix to the vertex shader
    glUseProgram(program);
    vProjection_uniform = glGetUniformLocation(program, "vProjection");
    if(vProjection_uniform == -1){
        fprintf(stderr, "Could not bind location: vProjection\n");
        exit(0);
    }
    glUniformMatrix4fv(vProjection_uniform, 1, GL_FALSE, glm::value_ptr(projectionT));
}

glm::vec3 getTrackBallVector(double x, double y)
{
	glm::vec3 p = glm::vec3(2.0*x/screen_width - 1.0, 2.0*y/screen_height - 1.0, 0.0); //Normalize to [-1, +1]
	p.y = -p.y; //Invert Y since screen coordinate and OpenGL coordinates have different Y directions.

	float mag2 = p.x*p.x + p.y*p.y;
	if(mag2 <= 1.0f)
		p.z = sqrtf(1.0f - mag2);
	else
		p = glm::normalize(p); //Nearest point, close to the sides of the trackball
	return p;
}


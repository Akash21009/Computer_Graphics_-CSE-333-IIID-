#include "utils/utils.hpp"
#include "drawable.hpp"
#include "camera/camera.hpp"
#include "mesh/mesh.hpp"

#define GLM_FORCE_RADIANS
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>


Mesh *createCubeMesh(float distance)
{
    GLfloat cubeVerts[] = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f
    };

    GLuint cubeIndices[] = {
        0, 1, 2,
        0, 2, 3,
        4, 5, 6,
        4, 6, 7,
        0, 4, 7,
        0, 7, 3,
        1, 5, 6,
        1, 6, 2,
        0, 1, 5,
        0, 5, 4,
        3, 2, 6,
        3, 6, 7
    };

    Mesh* cubeMesh = new Mesh(cubeVerts, cubeIndices, 8, 12);

    // Translate the cube to position it at a distance from the origin
    glm::mat4 cubeModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(distance, 0.0f, 0.0f));
    cubeMesh->setModelMatrix(cubeModelMatrix);

    return cubeMesh;
}


//SphereMesh
Mesh *testSphereMesh(int longitudnal_lines, int latitudnal_lines)
{
    GLfloat *verts = new GLfloat[(longitudnal_lines + 1 ) * (latitudnal_lines + 1) * 3];
	//number of vertices= (logitudnal line contributes and 1 for completing the loop)*(latitudanal line contributes and 1 for completing the loop)*(3 as each vertex have three coordinates)

    GLuint *indices = new GLuint[(longitudnal_lines-1) * (latitudnal_lines-1) * 6];
	//number of indices can be calculated by multiplying number of rings(longitudnal_lines-1) x number of sectors(latitudnal_lines-1) x 2(triangle on each face) x 3(each triangle have 3 vertices)
	float radius=0.5;


	//geting fraction of each ring and sector which contributed in complete sphere
    float fR = 1.0f / (float)(longitudnal_lines - 1);
    float fS = 1.0f / (float)(latitudnal_lines - 1);

    for (int r = 0; r < longitudnal_lines; ++r)
    {
        for (int s = 0; s < latitudnal_lines; ++s)
        {

			//parametric equations of sphere
           float const phi = glm::pi<float>()*r*fR;
            float const theta = 2 * glm::pi<float>()*s*fS;

            float const z = radius*cos(theta) * sin(phi);
            float const x = radius*sin(theta) * sin(phi);
            float const y = radius*cos(phi);

            verts[(r * latitudnal_lines + s) * 3] = x;
            verts[(r * latitudnal_lines + s) * 3 + 1] = y;
            verts[(r * latitudnal_lines + s) * 3 + 2] = z;
        }
    }

    int index = 0;
    for (int r = 0; r < longitudnal_lines - 1; ++r)
    {
        for (int s = 0; s < latitudnal_lines - 1; ++s)
        {
			//first triangle (tracing counter clock-wise)
            indices[index++] = r * latitudnal_lines + s;
            indices[index++] = r * latitudnal_lines + (s + 1);
            indices[index++] = (r + 1) * latitudnal_lines + s;

			//Second triangle (tracing counter clock-wise)
            indices[index++] = (r + 1) * latitudnal_lines + s;
            indices[index++] = r * latitudnal_lines + (s + 1);
            indices[index++] = (r + 1) * latitudnal_lines + (s + 1);
        }
    }

    return new Mesh(verts, indices, (longitudnal_lines + 1) * (latitudnal_lines + 1), (longitudnal_lines-1) * (latitudnal_lines-1) * 6);
}




int main(int, char **)
{
	// Setup window
	GLFWwindow *window = setupWindow(SCREEN_W, SCREEN_H, "Parametric Representations of Surfaces");
	ImGuiIO &io = ImGui::GetIO(); // Create IO

	double last_time = 0;
	double delta_time = 0;

	unsigned int shader_program = createProgram("shaders/vshader.vs", "shaders/fshader.fs");

	Camera *cam = new Camera(glm::vec3(-5.0f, 3.0f, 3.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
							 45.0f, 0.1f, 10000.0f, window);

	cam->setProjectionTransformation(shader_program);
	cam->setViewTransformation(shader_program);

	// Mesh *mesh = testCubeMesh();
	Mesh *cubeMesh = createCubeMesh(5.0f);
	Mesh *mesh = testSphereMesh(40, 40); 

	

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	while (!glfwWindowShouldClose(window))
	{
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		double curr_time = static_cast<double>(glfwGetTime());
		delta_time = curr_time - last_time;
		last_time = curr_time;

		if (!io.WantCaptureMouse)
		{
			cam->process_input(window, delta_time);
			cam->setViewTransformation(shader_program);
		}

		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(WHITE.x, WHITE.y, WHITE.z, WHITE.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		cubeMesh->draw(shader_program);

		mesh->draw(shader_program);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Cleanup
	cleanup(window);

	return 0;
}

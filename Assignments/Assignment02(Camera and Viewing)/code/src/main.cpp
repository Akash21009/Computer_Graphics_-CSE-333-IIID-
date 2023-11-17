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
GLint vColor_uniform;
glm::mat4 modelT, viewT, projectionT;//The model, view and projection transformations
glm::vec4 camPosition;
char textKeyStatus[256];


void createCubeObject(unsigned int &, unsigned int &);
void createAxesLine(unsigned int &, unsigned int &);

void setupModelTransformationCube(unsigned int &);
void setupModelTransformationAxis(unsigned int &program, float rot_angle, glm::vec3 rot_axis);
void setupViewTransformation(unsigned int &, float);
void setupProjectionTransformation(unsigned int &,unsigned char); //second parameter will use to generate either perspective or orthographic view.

int main(int, char**)
{
	// Setup window
	GLFWwindow *window = setupWindow(screen_width, screen_height);
	ImGuiIO& io = ImGui::GetIO(); // Create IO 
	ImVec4 clearColor = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
	camPosition = glm::vec4(20.0, 40.0, 80.0, 1.0);
	

	//Variables to control camera position and movement speed
	float cameraRadius = glm::length(glm::vec3(camPosition)); // Initial camera radius
	float cameraTheta = atan2(camPosition.x, camPosition.z);  // Initial azimuth angle (in radians)
	float cameraPhi = -acos(camPosition.y / cameraRadius); // Initial polar angle (in radians)
	float cameraSpeed = 0.01f;  // Speed of camera movement to orbit around the cube
	float zoomSpeed = 1.0f;      // speed of camera to zoom in and zoom out

	unsigned int shaderProgram = createProgram("./shaders/vshader.vs", "./shaders/fshader.fs");
	//Get handle to color variable in shader
	vColor_uniform = glGetUniformLocation(shaderProgram, "vColor");
	if(vColor_uniform == -1){
		fprintf(stderr, "Could not bind location: vColor\n");
		exit(0);
	}

	glUseProgram(shaderProgram);

	//setupModelTransformation(shaderProgram);
	// Modelling transformation is setup in the display loop
	setupViewTransformation(shaderProgram, cameraPhi);

	//ProjectionTransformation initialized as Perspective view
	setupProjectionTransformation(shaderProgram,'P');

	unsigned int cube_VAO, axis_VAO;
	createCubeObject(shaderProgram, cube_VAO);
	createAxesLine(shaderProgram, axis_VAO);

	

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		// Get key presses
        if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_LeftArrow))) {
		if(io.KeyCtrl){

				//Snapping to side elevated view
				if((0.0<=cameraTheta && cameraTheta<=0.785) || (5.49<cameraTheta && cameraTheta<=6.27)){
					cameraTheta=1.57;
				}
				else if((0.785<cameraTheta && cameraTheta<=2.35)){
					cameraTheta=3.14;
				}
				else if((2.35<cameraTheta && cameraTheta<=3.92)){
					cameraTheta=4.17;
					
				}
				else if((3.92<cameraTheta && cameraTheta<=5.49)){
					cameraTheta=0.0;
				}
				cameraPhi=-1.57;
          		strcpy(textKeyStatus, "Key status: Ctrl+Left");
		}
		else{
				cameraTheta += cameraSpeed;
          		strcpy(textKeyStatus, "Key status: Left");
		}
			
        }
        else if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_RightArrow))) {

			if(io.KeyCtrl){
				//Snapping to side elevated view
				if((0.0<=cameraTheta && cameraTheta<=0.785) || (5.49<cameraTheta && cameraTheta<=6.27)){
					cameraTheta=4.71;
				}
				else if((0.785<cameraTheta && cameraTheta<=2.35)){
					cameraTheta=0.0;
				}
				else if((2.35<cameraTheta && cameraTheta<=3.92)){
					cameraTheta=1.57;
					
				}
				else if((3.92<cameraTheta && cameraTheta<=5.49)){
					cameraTheta=3.14;
				}
				cameraPhi=-1.57;
          		strcpy(textKeyStatus, "Key status: Ctrl+Right");

			}
			else{
				cameraTheta-=cameraSpeed;
          strcpy(textKeyStatus, "Key status: Right");
			}
				
        }
        else if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_UpArrow))) {
		if(io.KeyCtrl){

			if((0.0<cameraTheta && cameraTheta<=0.785) || (5.49<cameraTheta && cameraTheta<=6.27)){
					cameraTheta=0.0;
				}
				else if(0.785<cameraTheta && cameraTheta<=2.35){
					cameraTheta=1.57;
				}
				else if(2.35<cameraTheta && cameraTheta<=3.92){
					cameraTheta=3.14;
				}
				else if(3.92<cameraTheta && cameraTheta<=5.49){
					cameraTheta=4.71;
				}

			cameraPhi=-0.01;
			
			strcpy(textKeyStatus, "Key status: Ctrl+Up");
		}
          else if(io.KeyShift){
		cameraRadius -= zoomSpeed;
            strcpy(textKeyStatus, "Key status: Shift + Up");}
          else {
		cameraPhi += cameraSpeed;

			if(cameraPhi>3.14){cameraPhi=-3.14;} //To orbit a full circle


            strcpy(textKeyStatus, "Key status: Up");}
        }
        else if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_DownArrow))) {
		if(io.KeyCtrl){

			if(io.KeyCtrl){
				//Snapping to front elevated view
				if((0.0<cameraTheta && cameraTheta<=0.785) || (5.49<cameraTheta && cameraTheta<=6.27)){
					cameraTheta=0.0;
				}
				else if(0.785<cameraTheta && cameraTheta<=2.35){
					cameraTheta=1.57;
				}
				else if(2.35<cameraTheta && cameraTheta<=3.92){
					cameraTheta=3.14;
				}
				else if(3.92<cameraTheta && cameraTheta<=5.49){
					cameraTheta=4.71;
				}
				cameraPhi=-1.57;
          		strcpy(textKeyStatus, "Key status: Ctrl+Down");

			}
			else{
				cameraPhi=-3.14;
			}

			

			strcpy(textKeyStatus, "Key status: Ctrl+Down");

		}
          else if(io.KeyShift){
		cameraRadius += zoomSpeed;
          strcpy(textKeyStatus, "Key status: Shift + Down");}
          else {
		cameraPhi -= cameraSpeed;

			if(cameraPhi<-3.14){cameraPhi=3.14;} //To orbit a full circle
			 
            strcpy(textKeyStatus, "Key status: Down");}
        }
		else if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_A))) {
			//switch to perspective view
			setupProjectionTransformation(shaderProgram,'P');
          strcpy(textKeyStatus, "Key status: A");
        }
		else if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_Z))) {
			//switch to othographic view
			setupProjectionTransformation(shaderProgram,'O');
          strcpy(textKeyStatus, "Key status: O");
        }
        else{ 
          strcpy(textKeyStatus, "Key status:");}

		if(cameraTheta<0.0){
				cameraTheta=6.27+cameraTheta;
		}
		if(cameraTheta>6.27){
			cameraTheta=0.0;
		}
		
		// Calculate new camera position in Cartesian coordinates as per updated cameraRadius,cameraPhi and cameraTheta using parametric equation of sphere
		camPosition.x = cameraRadius * sin(cameraPhi) * cos(cameraTheta);
		camPosition.y = cameraRadius * cos(cameraPhi);
		camPosition.z = cameraRadius * sin(cameraPhi) * sin(cameraTheta);

		setupViewTransformation(shaderProgram, cameraPhi);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		glUseProgram(shaderProgram);

		//ImGui UI menu
		ImGui::Begin("Main", NULL, ImGuiWindowFlags_AlwaysAutoResize);                          
		if(ImGui::CollapsingHeader("Information", ImGuiTreeNodeFlags_DefaultOpen))
		{
		  ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::Text("%s", textKeyStatus);
			ImGui::Text("Camera position: (%.2f, %.2f, %.2f)", camPosition.x, camPosition.y, camPosition.z);
		}
		ImGui::End();

		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		setupModelTransformationCube(shaderProgram);
		glBindVertexArray(cube_VAO); 
		glUniform4f(vColor_uniform, 0.5, 0.5, 0.5, 1.0);
		glDrawArrays(GL_TRIANGLES, 0, 6*2*3);
		glUniform4f(vColor_uniform, 0.0, 0.0, 0.0, 1.0);
		glDrawArrays(GL_LINE_STRIP, 0, 6*2*3);

    glDisable(GL_DEPTH_TEST); // Disable depth test for drawing axes. We want axes to be drawn on top of all

		glBindVertexArray(axis_VAO); 
		setupModelTransformationAxis(shaderProgram, 0.0, glm::vec3(0, 0, 1));
		glUniform4f(vColor_uniform, 1.0, 0.0, 0.0, 1.0); //Red -> X 
		glDrawArrays(GL_LINES, 0, 2);

		setupModelTransformationAxis(shaderProgram, glm::radians(90.0), glm::vec3(0, 0, 1));
		glUniform4f(vColor_uniform, 0.0, 1.0, 0.0, 1.0); //Green -> Y
		glDrawArrays(GL_LINES, 0, 2);

		setupModelTransformationAxis(shaderProgram, -glm::radians(90.0), glm::vec3(0, 1, 0));
		glUniform4f(vColor_uniform, 0.0, 0.0, 1.0, 1.0); //Blue -> Z
		glDrawArrays(GL_LINES, 0, 2);

    glEnable(GL_DEPTH_TEST); // Enable depth test again

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

void createAxesLine(unsigned int & program, unsigned int &axis_VAO)
{
  glUseProgram(program);

	//Bind shader variables
	int vVertex_attrib_position = glGetAttribLocation(program, "vVertex");
	if(vVertex_attrib_position == -1) {
		fprintf(stderr, "Could not bind location: vVertex\n");
		exit(0);
	}

	//Axes data
	GLfloat axis_vertices[] = {	0, 0, 0, 20, 0, 0}; //X-axis
  glGenVertexArrays(1, &axis_VAO);
	glBindVertexArray(axis_VAO);

	//Create VBO for the VAO
	int nVertices = 2; // 2 vertices
	GLuint vertex_VBO;
	glGenBuffers(1, &vertex_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_VBO);
	glBufferData(GL_ARRAY_BUFFER, nVertices*3*sizeof(GLfloat), axis_vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(vVertex_attrib_position);
	glVertexAttribPointer(vVertex_attrib_position, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0); //Unbind the VAO to disable changes outside this function.
}

void setupModelTransformationCube(unsigned int &program)
{
	//Modelling transformations (Model -> World coordinates)
	modelT = glm::scale(glm::mat4(1.0f), glm::vec3(1.0, 2.0, 1.0));
	modelT = glm::translate(modelT, glm::vec3(0.0f, 10.0f, 0.0f));

	//Pass on the modelling matrix to the vertex shader
	glUseProgram(program);
	vModel_uniform = glGetUniformLocation(program, "vModel");
	if(vModel_uniform == -1){
		fprintf(stderr, "Could not bind location: vModel\n");
		exit(0);
	}
	glUniformMatrix4fv(vModel_uniform, 1, GL_FALSE, glm::value_ptr(modelT));
}

void setupModelTransformationAxis(unsigned int &program, float rot_angle, glm::vec3 rot_axis)
{
	//Modelling transformations (Model -> World coordinates)
	modelT = glm::rotate(glm::mat4(1.0f), rot_angle, rot_axis);

	//Pass on the modelling matrix to the vertex shader
	glUseProgram(program);
	vModel_uniform = glGetUniformLocation(program, "vModel");
	if(vModel_uniform == -1){
		fprintf(stderr, "Could not bind location: vModel\n");
		exit(0);
	}
	glUniformMatrix4fv(vModel_uniform, 1, GL_FALSE, glm::value_ptr(modelT));
}


void setupViewTransformation(unsigned int &program, float cameraPhi)
{
	//Viewing transformations (World -> Camera coordinates
	if(cameraPhi>=0.0 || cameraPhi<-3.14){
		//negative z axis
	viewT = glm::lookAt(glm::vec3(camPosition), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0));
	}
	else{
		//positive z axis
	viewT = glm::lookAt(glm::vec3(camPosition), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	}

	//Pass-on the viewing matrix to the vertex shader
	glUseProgram(program);
	vView_uniform = glGetUniformLocation(program, "vView");
	if(vView_uniform == -1){
		fprintf(stderr, "Could not bind location: vView\n");
		exit(0);
	}
	glUniformMatrix4fv(vView_uniform, 1, GL_FALSE, glm::value_ptr(viewT));
}

void setupProjectionTransformation(unsigned int &program, unsigned char c='P')
{

	if(c=='P'){
		//Projection transformation(perspective view)
		projectionT = glm::perspective(45.0f, (GLfloat)screen_width/(GLfloat)screen_height, 0.1f, 1000.0f);}
	else if(c=='O'){
		//Projection transformation(orthographic view)
		projectionT = glm::ortho(-70.0f,70.0f,-70.0f,70.0f,0.1f,1000.0f);
	}

	//Pass on the projection matrix to the vertex shader
	glUseProgram(program);
	vProjection_uniform = glGetUniformLocation(program, "vProjection");
	if(vProjection_uniform == -1){
		fprintf(stderr, "Could not bind location: vProjection\n");
		exit(0);
	}
	glUniformMatrix4fv(vProjection_uniform, 1, GL_FALSE, glm::value_ptr(projectionT));
}


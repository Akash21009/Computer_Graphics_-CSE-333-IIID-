/*  @file main.cpp
 *  @brief This code runs the main function where the window is setup.
 *
 *  @author Vishwesh Vhavle
 *  @date September 1, 2023
 * 
 *  This code is provided solely for the purpose of the CSE 333/533 course    
 *  at IIIT Delhi. Unauthorized reproduction, distribution, or disclosure     
 *  of this code, in whole or in part, without the prior written consent of   
 *  the author is strictly prohibited.                                        
 *                                                                            
 *  This code is provided "as is", without warranty of any kind, express      
 *  or implied, including but not limited to the warranties of                
 *  merchantability, fitness for a particular purpose, and noninfringement.
 */

#include "utils.h"
#include <chrono>
#include <thread>

//Globals
int screen_width=720, screen_height=480;
GLint vModel_uniform, vView_uniform, vProjection_uniform, vColor_uniform;
glm::mat4 modelT, viewT, projectionT;// Model, View and Projection Transformation Matrices

double oldX, oldY, currentX, currentY;
bool isDragging=false;

const double desiredFrameRate = 20.0;
const double frameDelay = 1.0 / desiredFrameRate;

int main()
{
    // Setup Window
    GLFWwindow *window = setupWindow(screen_width, screen_height);
    ImGuiIO& io = ImGui::GetIO(); // Create IO Object

    ImVec4 clearColor = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);

    unsigned int shaderProgram = createProgram("./shaders/vshader.vs", "./shaders/fshader.fs");

    glUseProgram(shaderProgram);

    setupModelTransformation(shaderProgram);
    setupViewTransformation(shaderProgram);
    setupProjectionTransformation(shaderProgram);

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

        unsigned int VAO_0;
        glGenVertexArrays(1, &VAO_0);  
        createCubeObject(shaderProgram, VAO_0, 0);  

        unsigned int VAO_1;
        glGenVertexArrays(1, &VAO_1);  
        createCubeObject(shaderProgram, VAO_1, 1);  

        unsigned int VAO_2;
        glGenVertexArrays(1, &VAO_2);  
        createCubeObject(shaderProgram, VAO_2, 2);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);

        // Add a delay to control the frame rate
        std::this_thread::sleep_for(std::chrono::duration<double>(frameDelay));

    }

    // Cleanup
    cleanup(window);
    return 0;
}

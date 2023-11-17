/******************************************************************************
 *                                                                            *
 *  Copyright (c) 2023 Ojaswa Sharma. All rights reserved.                    *
 *                                                                            *
 *  Author: Ojaswa Sharma                                                     *
 *  E-mail: ojaswa@iiitd.ac.in                                                *
 *                                                                            *
 *  This code is provided solely for the purpose of the CSE 333/533 course    *
 *  at IIIT Delhi. Unauthorized reproduction, distribution, or disclosure     *
 *  of this code, in whole or in part, without the prior written consent of   *
 *  the author is strictly prohibited.                                        *
 *                                                                            *
 *  This code is provided "as is", without warranty of any kind, express      *
 *  or implied, including but not limited to the warranties of                *
 *  merchantability, fitness for a particular purpose, and noninfringement.   *
 *                                                                            *
 ******************************************************************************/ 

#include "utils.h"

#define DRAW_CUBIC_BEZIER 1 // Use to switch Linear and Cubic bezier curves
#define SAMPLES_PER_BEZIER 20 //Sample each Bezier curve as N=10 segments and draw as connected lines

// GLobal variables
std::vector<float> controlPoints;

std::vector<float> linearBezier;
std::vector<float> cubicBezier;
int width = 640, height = 640; 
bool controlPointsUpdated = false;
bool controlPointsFinished = false;
int selectedControlPoint = -1;



void calculatePiecewiseLinearBezier()
{
    // Since linearBezier is just a polyline, we can just copy the control points and plot.
    // However to show how a piecewise parametric curve needs to be plotted, we sample t and 
    // evaluate all linear bezier curves.
    // linearBezier.assign(controlPoints.begin(), controlPoints.end());

    linearBezier.clear();
    int sz  = controlPoints.size(); // Contains 3 points/vertex. Ignore Z
    float x[2], y[2];
    float delta_t = 1.0/(SAMPLES_PER_BEZIER - 1.0);
    float t;
    for(int i=0; i<(sz-3); i+=3) {
        x[0] = controlPoints[i];
        y[0] = controlPoints[i+1];
        x[1] = controlPoints[i+3];
        y[1] = controlPoints[i+4];
        linearBezier.push_back(x[0]);
        linearBezier.push_back(y[0]);
        linearBezier.push_back(0.0);
        t = 0.0;
        for (float j=1; j<(SAMPLES_PER_BEZIER-1); j++)
        {
        t += delta_t;
        linearBezier.push_back(x[0] + t*(x[1] - x[0]));
        linearBezier.push_back(y[0] + t*(y[1] - y[0]));
        linearBezier.push_back(0.0);
        }
        // No need to add the last point for this segment, since it will be added as first point in next.
    }
    
    linearBezier.push_back(x[1]);
    linearBezier.push_back(y[1]);
    linearBezier.push_back(0.0);
}

void calculatePiecewiseCubicBezier()
{
        /*
            Computes Piecewise Cubic Bezier for control points in controlPoints[]
            Parameters: ...
            Return: ...
            
        */
    cubicBezier.clear();
    int sz = controlPoints.size(); 
    float x[4], y[4];
    float lx,ly; //lastx and lasty (these will store 2nd intermediate point of last curve)
    lx=0.0;
    ly=0.0;
    float delta_t = 1.0 / (SAMPLES_PER_BEZIER - 1.0);
    float t;
    
    for (int i = 0; i < (sz - 3); i += 3)
    {

        //adding control points
        x[0] = controlPoints[i];
        y[0] = controlPoints[i + 1]; 
        x[3] = controlPoints[i + 3];
        y[3] = controlPoints[i + 4];

    //pushing first control point(anchor point)
    cubicBezier.push_back(x[0]);
    cubicBezier.push_back(y[0]);
    cubicBezier.push_back(0.0);


    //Adding intermadiate control points
        if(i<1){ //for fisrt control points it is random
        x[1] = (x[3]+x[0])/2.0;
        y[1] = ((y[3]+y[0]) / 2.0);
        
        }
        else{ //ensuring all C1 continiuty while joining curves i.e. sencond intermadiate point and last control point of first curve and first intermediate point of current curve are collinear
            
            float k=2; //change value accordingly
            x[1]=(k*x[0]-lx)/(k-1);
            y[1]=(k*y[0]-ly)/(k-1);
        }


        x[2] = (x[3]+x[0])/4.0;
        if(i%2==0){
        y[2] = ((y[3]+y[0]) / 2.0);
        }
        else{
            y[2] = -((y[3]+y[0]) / 2.0);
        }

        lx=x[2];
        ly=y[2];

        
        
        for (int j = 1; j < SAMPLES_PER_BEZIER; j++)
        {
            t = j * delta_t;
            float t2=t*t;
            float t3=t*t2;
            float tsub2 = (1-t)*(1-t);
            float tsub3 = tsub2*(1-t);

            //formula
            //Px(t) = (1 - t)^3 * P0x + 3 * (1 - t)^2 * t * P1x + 3 * (1 - t) * t^2 * P2x + t^3 * P3x
            //Py(t) = (1 - t)^3 * P0y + 3 * (1 - t)^2 * t * P1y + 3 * (1 - t) * t^2 * P2y + t^3 * P3y


            float px = x[0] * tsub3 + 3 * x[1] * t * tsub2 + 3 * x[2] * t2 * (1 - t) + x[3] * t3;
            float py = y[0] * tsub3 + 3 * y[1] * t * tsub2 + 3 * y[2] * t2 * (1 - t) + y[3] * t3;
            

            cubicBezier.push_back(px);
            cubicBezier.push_back(py);
            cubicBezier.push_back(0.0);
        }  
    }
    //pushing last control point(anchor point)
    cubicBezier.push_back(x[3]);
    cubicBezier.push_back(y[3]);
    cubicBezier.push_back(0.0);
}


int main(int, char* argv[])
{
    
    GLFWwindow* window = setupWindow(width, height);
    ImGuiIO& io = ImGui::GetIO(); // Create IO object

    ImVec4 clear_color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

    unsigned int shaderProgram = createProgram("./shaders/vshader.vs", "./shaders/fshader.fs");
	glUseProgram(shaderProgram);

    // Create VBOs, VAOs
    unsigned int VBO_controlPoints, VBO_linearBezier, VBO_cubicBezier;
    unsigned int VAO_controlPoints, VAO_linearBezier, VAO_cubicBezier;



    glGenBuffers(1, &VBO_controlPoints);
    glGenVertexArrays(1, &VAO_controlPoints);
    glGenBuffers(1, &VBO_linearBezier);
    glGenVertexArrays(1, &VAO_linearBezier);
    //TODO:
    glGenBuffers(1, &VBO_cubicBezier);
    glGenVertexArrays(1, &VAO_cubicBezier);

    int button_status = 0;

    

    //Display loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Rendering
        showOptionsDialog(controlPoints, io);
        ImGui::Render();

        // Add a new point on mouse click
        float x,y ;
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);


				if(!ImGui::IsAnyItemActive()) {
					if(ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
						x = io.MousePos.x;
						y = io.MousePos.y;
						if(!controlPointsFinished) { // Add points
							addControlPoint(controlPoints, x, y, width, height);
							controlPointsUpdated = true;
						} else { // Select point
							searchNearestControlPoint(x, y);
						} 
					}
					
					if(ImGui::IsMouseDragging(ImGuiMouseButton_Left) && controlPointsFinished) { // Edit points
						if(selectedControlPoint >=0) {
							x = io.MousePos.x;
							y = io.MousePos.y;
							editControlPoint(controlPoints, x, y, width, height);
                            
							controlPointsUpdated = true;
						}
					}
					
					if(ImGui::IsMouseClicked(ImGuiMouseButton_Right)) { // Stop adding points
						controlPointsFinished = true;
					}
				}

        if(controlPointsUpdated) {
            // Update VAO/VBO for control points (since we added a new point)
            glBindVertexArray(VAO_controlPoints);
            glBindBuffer(GL_ARRAY_BUFFER, VBO_controlPoints);
            glBufferData(GL_ARRAY_BUFFER, controlPoints.size()*sizeof(GLfloat), &controlPoints[0], GL_DYNAMIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0); //Enable first attribute buffer (vertices)



            // Update VAO/VBO for piecewise linear Bezier curve (since we added a new point)
            calculatePiecewiseLinearBezier();
            glBindVertexArray(VAO_linearBezier);
            glBindBuffer(GL_ARRAY_BUFFER, VBO_linearBezier);
            glBufferData(GL_ARRAY_BUFFER, linearBezier.size()*sizeof(GLfloat), &linearBezier[0], GL_DYNAMIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0); 

            // Update VAO/VBO for piecewise cubic Bezier curve
            //TODO:

            calculatePiecewiseCubicBezier();
            glBindVertexArray(VAO_cubicBezier);
            glBindBuffer(GL_ARRAY_BUFFER, VBO_cubicBezier);
            glBufferData(GL_ARRAY_BUFFER, cubicBezier.size() * sizeof(GLfloat), &cubicBezier[0], GL_DYNAMIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
            glEnableVertexAttribArray(0); 
        
            controlPointsUpdated = false; // Finish all VAO/VBO updates before setting this to false.
        }

        glUseProgram(shaderProgram);

        // Draw control points
        glBindVertexArray(VAO_controlPoints);
		glDrawArrays(GL_POINTS, 0, controlPoints.size()/3);
        
		

#if DRAW_CUBIC_BEZIER
        //TODO:

        glBindVertexArray(VAO_cubicBezier);
        glDrawArrays(GL_LINE_STRIP, 0, cubicBezier.size() / 3); // Draw lines
#else
        // Draw linear Bezier
        glBindVertexArray(VAO_linearBezier);
        glDrawArrays(GL_LINE_STRIP, 0, linearBezier.size()/3); //Draw lines
#endif

        glUseProgram(0);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);

    }

    // Delete VBO buffers
    glDeleteBuffers(1, &VBO_controlPoints);
    glDeleteBuffers(1, &VBO_linearBezier);
    //TODO:
    glDeleteBuffers(1, &VBO_cubicBezier);

    // Cleanup
    cleanup(window);
    return 0;
}

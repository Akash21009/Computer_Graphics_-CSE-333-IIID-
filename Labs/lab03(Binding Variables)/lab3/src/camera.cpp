/*  @file camera.cpp
 *  @brief This code provides viewing transformation matrices.
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

//Globals
extern int screen_width, screen_height;
extern GLint vModel_uniform, vView_uniform, vProjection_uniform, vColor_uniform;
extern glm::mat4 modelT, viewT, projectionT;// Model, View and Projection Transformation Matrices

extern double oldX, oldY, currentX, currentY;
extern bool isDragging;

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


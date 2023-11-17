/*  @file cube.cpp
 *  @brief This code renders 3 cubes.
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
#include <iostream>
#include <ctime>

extern GLint vColor_uniform;

void createCubeObject(unsigned int &program, unsigned int &cube_VAO, unsigned int cubeID)
{
    glUseProgram(program);

    // Bind Shader Variables
    int vVertex_attrib = glGetAttribLocation(program, "vVertex");
    if (vVertex_attrib == -1) {
        fprintf(stderr, "Could not bind location: vVertex\n");
        exit(0);
    }

    // Define vertices for different cubes (0 to 2)
    GLfloat cubeVertices[3][24] = {

                         // Cube Type 0
       {-3-18, -3, -3,   // Vertex 1
        3-18, -3, -3,    // Vertex 2
        3-18, 3, -3,     // Vertex 3
        -3-18, 3, -3,    // Vertex 4
        -3-18, -3, 3,    // Vertex 5
        3-18, -3, 3,     // Vertex 6
        3-18, 3, 3,      // Vertex 7
        -3-18, 3, 3},    // Vertex 8

                         // Cube Type 1
       {-3, -3, -3,     // Vertex 1
        3, -3, -3,      // Vertex 2
        3, 3, -3,       // Vertex 3
        -3, 3, -3,      // Vertex 4
        -3, -3, 3,      // Vertex 5
        3, -3, 3,       // Vertex 6
        3, 3, 3,        // Vertex 7
        -3, 3, 3},      // Vertex 8

                         // Cube Type 2
       {-3+18, -3, -3,   // Vertex 1
        3+18, -3, -3,    // Vertex 2
        3+18, 3, -3,     // Vertex 3
        -3+18, 3, -3,    // Vertex 4
        -3+18, -3, 3,    // Vertex 5
        3+18, -3, 3,     // Vertex 6
        3+18, 3, 3,      // Vertex 7
        -3+18, 3, 3},    // Vertex 8
    };

    GLushort cube_indices[] = {
        4, 0, 1, 1, 4, 5, // Front
        7, 3, 2, 2, 6, 7, // Back
        4, 0, 3, 3, 4, 7, // Left
        5, 1, 2, 2, 5, 6, // Right
        7, 4, 5, 5, 7, 6, // Top
        3, 0, 1, 1, 3, 2 // Bottom
    };

    // Position information (data + format)
    int nVertices = (6 * 2) * 3; // (6 faces) * (2 triangles each) * (3 vertices each)
    GLfloat *expanded_vertices = new GLfloat[nVertices * 3];
    for (int i = 0; i < nVertices; i++) {
        expanded_vertices[i * 3] = cubeVertices[cubeID][cube_indices[i] * 3];
        expanded_vertices[i * 3 + 1] = cubeVertices[cubeID][cube_indices[i] * 3 + 1];
        expanded_vertices[i * 3 + 2] = cubeVertices[cubeID][cube_indices[i] * 3 + 2];
    }

    // Generate VAO object
    glGenVertexArrays(1, &cube_VAO);
    glBindVertexArray(cube_VAO);

    // Create VBOs for the VAO
    GLuint vertex_VBO;
    glGenBuffers(1, &vertex_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_VBO);
    glBufferData(GL_ARRAY_BUFFER, nVertices * 3 * sizeof(GLfloat), expanded_vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(vVertex_attrib);
    glVertexAttribPointer(vVertex_attrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    delete[] expanded_vertices;

    // Calculate the time elapsed
    float timeElapsed = std::fmod(std::clock() / static_cast<float>(CLOCKS_PER_SEC), 0.03f);

    float red, green, blue;
    int numCubes = 3; // Total number of cubes
    int timeFactor = int(timeElapsed * 100) % 3; // Calculate a time-based factor

    switch (cubeID) {
        case 0:
            red = (timeFactor == 0) ? 1.0f : (timeFactor == 1) ? 0.5f : 0.0f;
            green = (timeFactor == 0) ? 0.5f : (timeFactor == 1) ? 0.5f : 1.0f;
            blue = (timeFactor == 0) ? 0.5f : (timeFactor == 1) ? 1.0f : 0.5f;
            break;
        case 1:
            red = (timeFactor == 0) ? 0.5f : (timeFactor == 1) ? 1.0f : 0.5f;
            green = (timeFactor == 0) ? 1.0f : (timeFactor == 1) ? 0.5f : 0.5f;
            blue = (timeFactor == 0) ? 0.5f : (timeFactor == 1) ? 0.5f : 1.0f;
            break;
        default:
            red = (timeFactor == 0) ? 0.5f : (timeFactor == 1) ? 0.0f : 1.0f;
            green = (timeFactor == 0) ? 0.5f : (timeFactor == 1) ? 1.0f : 0.5f;
            blue = (timeFactor == 0) ? 1.0f : (timeFactor == 1) ? 0.5f : 0.5f;
            break;
    }

    // --------------------------------EDIT--CODE--HERE--------------------------------------


    int vColor_uniform = glGetUniformLocation(program, "vColor");
    if (vColor_uniform == -1) {
        fprintf(stderr, "Could not bind location: vColor\n");
        exit(0);
    }

    // GLfloat cubeColor[3] = {red, blue, green};

    
    glUniform3f(vColor_uniform,red,blue,green);

    // GLuint color_VBO;
    // glGenBuffers(1, &color_VBO);
    // glBindBuffer(GL_ARRAY_BUFFER, color_VBO);
    // glBufferData(GL_ARRAY_BUFFER, nVertices * 3 * sizeof(GLfloat), cubeColor, GL_STATIC_DRAW);
    // glEnableVertexAttribArray(vColor_attrib);
    // glVertexAttribPointer(vColor_attrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, 6 * 2 * 3); // (6 faces) * (2 triangles per face) * (3 vertices per triangle)

    // ----------------------------------------------------------------------------------------

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); // Unbind the VAO to disable changes outside this function.
}

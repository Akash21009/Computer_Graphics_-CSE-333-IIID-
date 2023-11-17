// Assignment 03: Raytracing
#include "triangle.h"
#include "imgui_setup.h"
#include "camera.h"
#include "renderengine.h"
#include "world.h"
#include "material.h"
#include "object.h"
#include "sphere.h"
#include "lightsource.h"
#include "pointlightsource.h"
#include "color.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../depends/stb/stb_image.h"
#include "../depends/stb/stb_image_write.h"

#define RENDER_BATCH_COLUMNS 20 // Number of columns to render in a single go. Increase to gain some display/render speed!


Camera *camera;
RenderEngine *engine;

int screen_width = 800, screen_height = 600; // This is window size, used to display scaled raytraced image.
int image_width = 1920, image_height = 1080; // This is raytraced image size. Change it if needed.
GLuint texImage;




int main(int, char**)
{
    // Setup window
    GLFWwindow *window = setupWindow(screen_width, screen_height);

    ImVec4 clearColor = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);

    // Setup raytracer camera. This is used to spawn rays.
    Vector3D camera_position(0, 0, 10);
    Vector3D camera_target(0, 0, 0); //Looking down -Z axis
    Vector3D camera_up(0, 1, 0);
    float camera_fovy =  45;
    camera = new Camera(camera_position, camera_target, camera_up, camera_fovy, image_width, image_height);

    //Create a world
    World *world = new World;
    world->setAmbient(Color(1));
    world->setBackground(Color(0.1, 0.3, 0.6));
    
    Material *m = new Material(world);
    m->color = Color(0.1, 0.7, 0.0);
    m->ka = 0.1;
    m->kd = 0.9;
    m->ks = 1.0; //spot size
    m->kt = 0.5;
    m->kr = 0.7;
    m->eta = 0.3;
    m->n = 200; //lower n produce more spread of specular

    Material *m2 = new Material(world);
    m2->color = Color(1.0, 0.0, 0.0);
    m2->ka = 0.1;
    m2->kd = 0.9;
    m2->ks = 1.0; //spot size
    m2->kt = 0.5;
    m2->eta = 0.6;
    m2->kr = 0.5;
    m2->n = 200;

    Material *m3 = new Material(world);
    m3->color = Color(1.0, 0.0, 0.0);
    m3->ka = 0.1;
    m3->kd = 0.9;
    m3->ks = 1.0; //spot size
    m3->kr = 2;
    m3->kt = 0.7;
    m3->eta = 0.5;
    m3->n = 200;
    m3->absorption_coefficient=0.5;
    
    
    Object *sphere = new Sphere(Vector3D(4, -1, -5), 3, m);
    world->addObject(sphere);
    // Object *sphere2 = new Sphere(Vector3D(-4, 0, -3), 2, m);
    // world->addObject(sphere2);
    // Object *triangle2= new Triangle(Vector3D(-5, -2, -8), Vector3D(5, -2, -8),Vector3D(0, 4, -8), m3);
    // world->addObject(triangle2);
    Object *triangle= new Triangle(Vector3D(-10, -7, -10), Vector3D(13, -7, -10),Vector3D(0, 8, -10), m2);
    world->addObject(triangle);
    

    LightSource *light = new PointLightSource(world, Vector3D(0, 1, 0), Color(1, 1, 1));
    world->addLight(light);

    engine = new RenderEngine(world, camera);

    //Initialise texture
    glGenTextures(1, &texImage);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGB, GL_UNSIGNED_BYTE, camera->getBitmap());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        bool render_status;
        for(int i=0; i<RENDER_BATCH_COLUMNS; i++) 
            render_status = engine->renderLoop(); // RenderLoop() raytraces 1 column of pixels at a time.
        if(!render_status)
        {
            // Update texture
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texImage);
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, image_width, image_height, GL_RGB, GL_UNSIGNED_BYTE, camera->getBitmap());
        } 

        ImGui::Begin("Lumina", NULL, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("Size: %d x %d", image_width, image_height);
        if(ImGui::Button("Save")){
          char filename[] = "img.png";
          stbi_write_png(filename, image_width, image_height, 3, camera->getBitmap(),0);        
        }
        //Display render view - fit to width
        int win_w, win_h;
        glfwGetWindowSize(window, &win_w, &win_h);
        float image_aspect = (float)image_width/(float)image_height;
        float frac = 0.95; // ensure no horizontal scrolling
        ImGui::Image((void*)(intptr_t)texImage, ImVec2(frac*win_w, frac*win_w/image_aspect), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));

        ImGui::End();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    glDeleteTextures(1, &texImage);

    cleanup(window);

    return 0;
}


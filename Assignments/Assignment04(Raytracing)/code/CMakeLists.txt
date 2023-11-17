 cmake_minimum_required(VERSION 3.5)

project(Assignment04)
set(TARGET ${CMAKE_PROJECT_NAME})
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(GLEW REQUIRED)

set(SOURCES
		"src/main.cpp"
		"src/camera.cpp"
		"src/color.cpp"
		"src/imgui_setup.cpp"
		"src/material.cpp"
		"src/ray.cpp"
		"src/renderengine.cpp"
		"src/sphere.cpp"
		"src/utility.cpp"
		"src/vector3D.cpp"
		"src/world.cpp"
		"src/triangle.cpp"
		"depends/imgui/imgui_impl_glfw.cpp"
		"depends/imgui/imgui_impl_opengl3.cpp"
		"depends/imgui/imgui.cpp"
		"depends/imgui/imgui_demo.cpp"
		"depends/imgui/imgui_draw.cpp"
		"depends/imgui/imgui_widgets.cpp"
	 )

add_executable(${TARGET} ${SOURCES})

target_include_directories(${TARGET} PRIVATE
	${PROJECT_SOURCE_DIR}/src
	${PROJECT_SOURCE_DIR}/depends/imgui
	${PROJECT_SOURCE_DIR}/depends/stb
	${GLFW_INCLUDE_DIRS}
	${OPENGL_INCLUDE_DIR}
	${GLM_INCLUDE_DIRS/../include}
	)
target_link_libraries(${TARGET} ${OPENGL_LIBRARIES} glfw GLEW::GLEW)


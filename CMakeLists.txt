cmake_minimum_required(VERSION 3.30 FATAL_ERROR)

set(PROJECT_NAME SolarSystemOpenGL)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} 
	Sources/main.cpp 
	Sources/Window.cpp 
	Headers/Window.h
	Render/Sources/ShaderProgram.cpp
	Render/Headers/ShaderProgram.h
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)


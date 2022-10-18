cmake_minimum_required(VERSION 3.21)
project(cviceni1 VERSION 1.0.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++11")

find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME} Application.cpp Callback.cpp Camera.cpp main.cpp Model.cpp RenderedObject.cpp Scene.cpp Shader.cpp ShaderManager.cpp ShaderProgram.cpp Transformation.cpp Window.cpp)

target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
target_link_libraries(${PROJECT_NAME} "${PROJECT_SOURCE_DIR}/lib/glew/2.2.0_1/lib/libGLEW.dylib")
target_link_libraries(${PROJECT_NAME} "${PROJECT_SOURCE_DIR}/lib/glfw/lib-arm64/libglfw.3.dylib")

find_package(GLEW QUIET)
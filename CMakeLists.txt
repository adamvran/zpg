cmake_minimum_required(VERSION 3.21)
project(cviceni1 VERSION 1.0.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME}
        Application.cpp
        Callback.cpp
        Camera.cpp
        main.cpp
        RenderedObject.cpp
        Scene.cpp
        ShaderControll/Shader.cpp
        ShaderControll/ShaderManager.cpp
        Subject.cpp
        ShaderControll/ShaderProgram.cpp
        Transformations/Transformation.cpp
        Window.cpp
        Loader.cpp
        Loader.h
        Observer.cpp
        Observer.h
        MatrixType.h
        Lights/Light.cpp
        Lights/Light.h
        Colors.cpp
        Colors.h
        Skybox.cpp
        Models/Models.cpp
        Models/Models.h
        Models/BushesModel.cpp
        Models/GiftModel.cpp
        Models/SuziSmoothModel.cpp
        Models/SphereModel.cpp
        Models/TreeModel.cpp
        Models/PlainModel.cpp
        Models/SuziFlatModel.cpp
        Models/SuziFlatModel.h
        Models/SkycubeModel.cpp
        Models/SkycubeModel.h
        Models/Textures/AbstractTexture.cpp
        Models/Textures/PlaneTextureModel.cpp
        Models/Textures/SkyboxTextureModel.cpp
        Models/Textures/Texture.cpp
        Lights/LightType.h
        Lights/AbstractLight.cpp
        Transformations/AbstractTransform.cpp
        Lights/DirectionalLight.cpp
        Lights/PointLight.cpp
        Lights/SpotLight.cpp

        )

target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
target_link_libraries(${PROJECT_NAME} "-framework CoreFoundation")
target_link_libraries(${PROJECT_NAME} "${PROJECT_SOURCE_DIR}/lib/glew/2.2.0_1/lib/libGLEW.dylib")
target_link_libraries(${PROJECT_NAME} "${PROJECT_SOURCE_DIR}/lib/glfw/lib-arm64/libglfw.3.dylib")
link_libraries(${PROJECT_NAME} "${PROJECT_SOURCE_DIR}/soil/lib/SOIL.lib")

find_package(GLEW QUIET)
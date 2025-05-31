cmake_minimum_required(VERSION 3.28)
project(CMLEngine)

set(CMAKE_CXX_STANDARD 23)

include_directories(core)

add_executable(CMLEngine core/main.cpp
        core/rendering/buffer-objects/BufferObject.h
        core/rendering/buffer-objects/VAO.h
        core/rendering/ShaderProgram.cpp
        core/rendering/ShaderProgram.h
        core/rendering/buffer-objects/VAO.cpp
        core/rendering/Model.cpp
        core/rendering/Model.h
        core/rendering/Texture2D.cpp
        core/rendering/Texture2D.h
        core/world/instances/Instance.cpp
        core/world/instances/Instance.h
        core/rendering/Material.cpp
        core/rendering/Material.h
        core/world/Scene.cpp
        core/world/Scene.h
        core/world/instances/Camera.cpp
        core/world/instances/Camera.h
        core/world/instances/TexturedInstance.cpp
        core/world/instances/TexturedInstance.h
        core/asset-management/IAsset.cpp
        core/asset-management/IAsset.h
        core/asset-management/AssetManager.cpp
        core/asset-management/AssetManager.h
        core/asset-management/asset-loaders/IAssetLoaderBase.h
        core/asset-management/asset-loaders/IAssetLoader.cpp
        core/asset-management/asset-loaders/IAssetLoader.h
        core/asset-management/asset-loaders/TextureLoader.cpp
        core/asset-management/asset-loaders/TextureLoader.h
        core/asset-management/asset-loaders/ModelLoader.cpp
        core/asset-management/asset-loaders/ModelLoader.h
)

add_subdirectory(external/glfw)
target_link_libraries(CMLEngine PRIVATE glfw)
target_include_directories(CMLEngine PUBLIC "${CMAKE_SOURCE_DIR}/external/glfw/include")

add_subdirectory(external/glad)
target_link_libraries(CMLEngine PRIVATE glad)
target_include_directories(CMLEngine PUBLIC "${CMAKE_SOURCE_DIR}/external/glad/include")

include_directories(external/glm)

add_library(lodepng STATIC external/lodepng/lodepng.cpp)
target_include_directories(lodepng PUBLIC external/lodepng)
target_link_libraries(CMLEngine PRIVATE lodepng)

find_package(assimp CONFIG REQUIRED)
target_link_libraries(CMLEngine PRIVATE assimp::assimp)

set_target_properties(CMLEngine PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET CMLEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:CMLEngine>/res)
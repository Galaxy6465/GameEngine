# cmake_minimum_required(VERSION 3.16)
# project(MyEngine LANGUAGES C CXX)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # Global include paths so you never need "../"
# include_directories(
#     include
#     glad/include
#     imgui
#     imgui/backends
# )

# # Find your engine's source files automatically
# file(GLOB_RECURSE ENGINE_SOURCES src/*.cpp)

# # Third-party libraries (Glad C file + ImGui C++ files)
# set(THIRD_PARTY_SOURCES
#     glad/src/glad.c
#     imgui/imgui.cpp
#     imgui/imgui_draw.cpp
#     imgui/imgui_demo.cpp
#     imgui/imgui_tables.cpp
#     imgui/imgui_widgets.cpp
#     imgui/backends/imgui_impl_glfw.cpp
#     imgui/backends/imgui_impl_opengl3.cpp
# )

# # Define your final executable target
# add_executable(MyEngine ${ENGINE_SOURCES} ${THIRD_PARTY_SOURCES}
#     CMakeLists.txt
# )

# # Automatically copy resources to the build directory on every build
# add_custom_command(
#     TARGET MyEngine POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#         ${CMAKE_SOURCE_DIR}/resources
#         $<TARGET_FILE_DIR:MyEngine>/resources
#     COMMENT "Copying resources directory to output folder"
# )
# # Find and link OpenGL, GLFW, and system threads/dl libraries
# find_package(OpenGL REQUIRED)
# target_link_libraries(MyEngine PRIVATE OpenGL::GL glfw dl pthread)


cmake_minimum_required(VERSION 3.16)
project(MyEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find required external packages
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

# Include directories covering the root include and all modular sub-includes
include_directories(
    include
    src/core/include
    src/graphics/include
    src/io/include
    src/ui/include
    ThirdParty/glad/include
    ThirdParty/imgui
    ThirdParty/imgui/backends
)

# Automatically find all C++ source files recursively under src/
file(GLOB_RECURSE ENGINE_SOURCES src/*.cpp)

# Third-party source files with correct ThirdParty/ prefixes
set(THIRD_PARTY_SOURCES
    ThirdParty/glad/src/glad.c
    ThirdParty/imgui/imgui.cpp
    ThirdParty/imgui/imgui_draw.cpp
    ThirdParty/imgui/imgui_demo.cpp
    ThirdParty/imgui/imgui_tables.cpp
    ThirdParty/imgui/imgui_widgets.cpp
    ThirdParty/imgui/backends/imgui_impl_glfw.cpp
    ThirdParty/imgui/backends/imgui_impl_opengl3.cpp
)

# Define executable target
add_executable(MyEngine 
    ${ENGINE_SOURCES} 
    ${THIRD_PARTY_SOURCES}
    CMakeLists.txt
)

# Link OpenGL, GLFW, and system libraries
target_link_libraries(MyEngine PRIVATE OpenGL::GL glfw dl pthread)

# Automatically copy resources directory to the build folder
add_custom_command(
    TARGET MyEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        $<TARGET_FILE_DIR:MyEngine>/resources
    COMMENT "Copying resources directory to output folder"
)
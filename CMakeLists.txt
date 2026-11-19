cmake_minimum_required(VERSION 3.16)
project(MyEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENABLE_ASAN "Enable AddressSanitizer for memory debugging" OFF)

# Find required external packages
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

# Include directories covering the root include and all modular sub-includes
include_directories(
    include
    source/include
    ThirdParty/glad/include
    ThirdParty/imgui
    ThirdParty/imgui/backends
)

# Automatically find all C++ source files recursively under src/
file(GLOB_RECURSE ENGINE_SOURCES source/*.cpp)

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

# Enable AddressSanitizer when requested
if(ENABLE_ASAN AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(MyEngine PRIVATE
        -g
        -O1
        -fsanitize=address
        -fno-omit-frame-pointer
    )
    target_link_options(MyEngine PRIVATE
        -fsanitize=address
    )
endif()

# Automatically copy resources directory to the build folder
add_custom_command(
    TARGET MyEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        $<TARGET_FILE_DIR:MyEngine>/resources
    COMMENT "Copying resources directory to output folder"
)
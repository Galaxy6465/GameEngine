cmake_minimum_required(VERSION 3.16)
project(RayLibEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENABLE_ASAN "Enable AddressSanitizer for memory debugging" OFF)

# Find required external packages
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

# Set path to your local ImGui folder
set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/imgui")

# Include directories covering source/, glad/, and imgui/
include_directories(
    source
    glad/include
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

# Automatically find all C++ source files recursively under source/
file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

# Third-party / local library sources from glad/ and imgui/
set(THIRD_PARTY_SOURCES
    glad/src/glad.c
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# Define executable target
add_executable(MyEngine 
    ${ENGINE_SOURCES} 
    ${THIRD_PARTY_SOURCES}
)

# Link OpenGL, GLFW, and Linux system libraries
target_link_libraries(MyEngine PRIVATE 
    OpenGL::GL 
    glfw 
    dl 
    pthread 
    X11
)

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

# Automatically copy resources directory to the build folder (when present)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/resources")
    add_custom_command(
        TARGET MyEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/resources"
            "$<TARGET_FILE_DIR:MyEngine>/resources"
        COMMENT "Copying resources directory to output folder"
    )
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/res")
    add_custom_command(
        TARGET MyEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/res"
            "$<TARGET_FILE_DIR:MyEngine>/res"
        COMMENT "Copying engine shaders and resources"
    )
endif()

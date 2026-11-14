#!/bin/bash

# Exit immediately if any command fails
set -e

# Enable recursive globbing (** matches subdirectories)
shopt -s globstar

echo "[Building MyEngine...]"

# Automatically find all C++ source files under src/ and third-party folders
SRC_FILES=(
    src/**/*.cpp
    glad/src/glad.c
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
)

# Compile command utilizing the auto-discovered file array
g++ -std=c++17 \
    "${SRC_FILES[@]}" \
    -o MyEngine \
    -Iinclude \
    -Iglad/include \
    -Iimgui \
    -Iimgui/backends \
    -lglfw -lGL -ldl -lpthread

echo "[Build Successful! Launching MyEngine...]"

# Run the compiled binary
./MyEngine
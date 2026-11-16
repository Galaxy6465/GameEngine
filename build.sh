# #!/bin/bash

# # Exit immediately if any command fails
# set -e

# # Enable recursive globbing (** matches subdirectories)
# shopt -s globstar

# echo "[Building MyEngine...]"

# # Automatically find all C++ source files under src/ and third-party folders
# SRC_FILES=(
#     src/**/*.cpp
#     ThirdParty/glad/src/glad.c
#     ThirdParty/imgui/imgui.cpp
#     ThirdParty/imgui/imgui_demo.cpp
#     ThirdParty/imgui/imgui_draw.cpp
#     ThirdParty/imgui/imgui_tables.cpp
#     ThirdParty/imgui/imgui_widgets.cpp
#     ThirdParty/imgui/backends/imgui_impl_glfw.cpp
#     ThirdParty/imgui/backends/imgui_impl_opengl3.cpp
# )

# # Compile command utilizing the auto-discovered file array
# g++ -std=c++17 \
#     "${SRC_FILES[@]}" \
#     -o MyEngine \
#     -Iinclude \
#     -IThirdParty/glad/include \
#     -IThirdParty/imgui \
#     -IThirdParty/imgui/backends \
#     -lglfw -lGL -ldl -lpthread

# echo "[Build Successful! Launching MyEngine...]"

# # Run the compiled binary
# ./MyEngine

#!/bin/bash

# Exit immediately if any command fails
set -e

# Enable recursive globbing (** matches subdirectories)
shopt -s globstar

echo "[Building MyEngine...]"

# Automatically find all C++ source files under src/ and third-party folders
SRC_FILES=(
    src/**/*.cpp
    ThirdParty/glad/src/glad.c
    ThirdParty/imgui/imgui.cpp
    ThirdParty/imgui/imgui_demo.cpp
    ThirdParty/imgui/imgui_draw.cpp
    ThirdParty/imgui/imgui_tables.cpp
    ThirdParty/imgui/imgui_widgets.cpp
    ThirdParty/imgui/backends/imgui_impl_glfw.cpp
    ThirdParty/imgui/backends/imgui_impl_opengl3.cpp
)

# Compile command with all modular include paths included
g++ -std=c++17 \
    "${SRC_FILES[@]}" \
    -o MyEngine \
    -Iinclude \
    -Isrc/core/include \
    -Isrc/graphics/include \
    -Isrc/io/include \
    -Isrc/ui/include \
    -IThirdParty/glad/include \
    -IThirdParty/imgui \
    -IThirdParty/imgui/backends \
    -lglfw -lGL -ldl -lpthread

echo "[Build Successful! Launching MyEngine...]"

# Run the compiled binary
./MyEngine
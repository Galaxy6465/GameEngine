# Engine

A small C++17 desktop-engine experiment using GLFW to create a window, OpenGL 3.3
for rendering, GLAD for OpenGL function loading, and Dear ImGui for an optional
debug UI.

> The root CMake target currently renders with OpenGL and GLFW. The repository
> also contains a `raylib/` directory, but the root `CMakeLists.txt` does not
> build or link raylib.

## Requirements

The included CMake preset targets Linux with GCC/G++ at `/usr/bin/gcc` and
`/usr/bin/g++`. Install CMake, a C/C++ toolchain, GLFW, OpenGL development files,
and X11 development files. For Debian or Ubuntu:

```sh
sudo apt update
sudo apt install build-essential cmake libglfw3-dev libgl1-mesa-dev libx11-dev
```

GLAD and Dear ImGui are included in the repository. CMake still requires the
system GLFW and OpenGL packages.

## Configure, build, and run

Run these commands from the repository root:

```sh
cmake --preset RaylibEngine
cmake --build out/build/RaylibEngine --parallel
./out/build/RaylibEngine/MyEngine
```

The preset creates a Debug build in `out/build/RaylibEngine`. The executable
target is named `MyEngine`.

## Project layout

| Path | Purpose |
| --- | --- |
| `source/main_opengl.cpp` | Program entry point; sets application defaults and starts the application. |
| `source/Application/` | Application initialization, main loop, and shared application/window settings. |
| `source/Window/` | GLFW window ownership, event/update dispatch, frame clearing, layer rendering, and buffer presentation. |
| `source/Layers/Layer.h` | Base layer interface and lifecycle callbacks. |
| `source/Layers/LayerStack.*` | Owns layers and overlays and dispatches their lifecycle. |
| `source/Layers/RenderLayer.h` | Example OpenGL shader and animated 3D cube renderer. |
| `source/Layers/ImGuiOverlay.h` | Dear ImGui inspector overlay, including live triangle-color editing. |
| `source/utils/` | Header-only camera/matrix, shader, and texture helpers; see its README for usage. |
| `res/` | Runtime shader and asset files copied beside the built executable. |
| `source/Core/` | Logging macros and platform-related definitions. |
| `glad/` | Included GLAD OpenGL loader sources and headers. |
| `imgui/` | Included Dear ImGui sources and GLFW/OpenGL backends. |
| `raylib/` | Vendored raylib tree; it is not part of the current root CMake target. |

## Runtime workflow

1. `main_opengl.cpp` sets application settings and constructs `Application`.
2. `Application::Init()` initializes GLFW, requests an OpenGL 3.3 core context,
   creates the window, and loads OpenGL entry points through GLAD.
3. After GLAD is ready and the window context is current, the application pushes
   a `RenderLayer` and an `ImGuiOverlay` onto the window's layer stack.
   `PushLayer()` and `PushOverlay()` call each layer's `OnAttach()`.
4. Each frame, `Application::Run()` polls GLFW events, then calls the window's
   update and render methods.
5. The window updates each layer. For rendering, it makes its context current,
   sets the viewport, clears the frame, calls each layer's `OnRender()` in stack
   order, and finally calls `glfwSwapBuffers()`. The render layer is added
   before the overlay, so the ImGui inspector draws on top of the triangle.
6. When a layer is removed or the layer stack is destroyed, its `OnDetach()`
   callback releases layer-owned resources.

## Working with layers

Create a class derived from `Layer` and override the callbacks you need:

- `OnAttach()` — create resources that require the active graphics context.
- `OnUpdate()` — update per-frame state.
- `OnRender()` — issue drawing commands for the current frame.
- `OnDetach()` — release resources while the graphics context is still valid.

Add it to the window after OpenGL initialization:

```cpp
m_app_Windows->PushLayer(std::make_unique<MyLayer>());
```

Use `PushOverlay()` for a layer that should render after regular layers, such as
the ImGui UI. Keep the order in mind: each frame calls `OnRender()` in the same
order that layers and overlays are stored in the stack.

The current example shader and rotating 3D cube are in `source/Layers/RenderLayer.h`
and `res/cube.vs` / `res/cube.fs`. The inspector is in
`source/Layers/ImGuiOverlay.h`; it edits the cube color owned by the render layer.
The utilities in `source/utils/` are documented in
[`source/utils/README.md`](source/utils/README.md).

## Current lifecycle caveat

The current application loop needs shutdown handling before it can reliably
exit: `m_app_isRunning` in `Application` is not initialized, and the window-close
branch destroys the GLFW window but does not stop the loop. Also, `glfwTerminate()`
currently runs before the `Application`'s window member is destroyed, even though
layer cleanup uses the OpenGL context. Before relying on normal close behavior,
initialize the running flag, stop the loop when the window requests closing, and
destroy the window and its layers while GLFW and the window context are still
valid; call `glfwTerminate()` afterward.

The window dimensions are currently hard-coded as `800 x 600` in
`Application::Init()`. The width and height assigned in `main_opengl.cpp` are
not currently used to construct that window.

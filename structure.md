MyEngine/
├── include/
│   ├── core/         # Window, Input, Time, Camera
│   ├── graphics/     # Shader, Texture, Mesh, Model, Renderer
│   ├── scene/        # GameObject, Transform, Scene
│   └── utils/        # Logger, File loader, Constants
├── src/
│   ├── core/
│   ├── graphics/
│   ├── scene/
│   └── main.cpp      # Only initializes the Engine and starts it!
├── resources/
│   ├── shaders/      # .vs and .fs files
│   └── textures/     # .jpg, .png files
└── CMakeLists.txt    # Modern build configuration

MyEngine/
├── include/                  <-- Header files (.hpp / .h) - declarations only (classes, structs)
│   ├── core/                 <-- Engine infrastructure headers
│   │   ├── Engine.hpp        <-- Manages window lifecycle, game loop, and delta time
│   │   └── Input.hpp         <-- Handles keyboard and mouse states
│   └── graphics/             <-- Rendering system headers
│       ├── Shader.hpp        <-- Declares the Shader class (loading & setting uniforms)
│       ├── Texture.hpp       <-- Declares the Texture loader
│       └── Mesh.hpp          <-- Declares VAO/VBO vertex data structures
├── src/                      <-- Source files (.cpp) - actual implementation code
│   ├── core/
│   │   ├── Engine.cpp        <-- Implements window creation, glfw polling, and update loops
│   │   └── Input.cpp         <-- Implements key/mouse callbacks
│   ├── graphics/
│   │   ├── Shader.cpp        <-- Implements GLSL shader compilation and uniform setters
│   │   ├── Texture.cpp       <-- Implements stb_image loading into OpenGL texture buffers
│   │   └── Mesh.cpp          <-- Implements vertex buffer data uploads
│   └── main.cpp              <-- Entry point: creates the Engine instance and starts it
├── resources/                <-- Asset files (never hardcoded into source code)
│   ├── shaders/              <-- Raw GLSL files (.vs and .fs)
│   └── textures/             <-- Image files (.jpg, .png like container.jpg)
└── CMakeLists.txt            <-- Build automation configuration (or your g++ build command)

MyEngine/
├── glad/                     <-- Glad loader files (include/ and src/glad.c)
├── imgui/                    <-- Dear ImGui source files (*.cpp, *.h, and backends/)
├── include/                  <-- Your own engine headers
├── src/                      <-- Your own engine source files
└── main.cpp


``` mermaid
graph TD
    %% Phase 1: Window & Context
    subgraph Phase 1 ["Phase 1: Window & OpenGL Context"]
        A1["Initialize GLFW & Window Hints"] --> A2["Create Desktop Window & Context"]
        A2 --> A3["Initialize GLAD & Load OpenGL Pointers"]
        A3 --> A4["Clear-Color Render Loop Verification"]
    end

    %% Phase 2: Events & Input
    subgraph Phase 2 ["Phase 2: Event System & Input Polling"]
        B1["Define Abstract Base Events"] --> B2["Implement Event Dispatcher"]
        B2 --> B3["Wrap GLFW Input/Key/Mouse Polling"]
    end

    %% Phase 3: Application & Layers
    subgraph Phase 3 ["Phase 3: Application & Layer Architecture"]
        C1["Build Core Application Loop"] --> C2["Implement Layer & LayerStack"]
        C2 --> C3["Setup main.cpp Factory Pattern"]
    end

    %% Phase 4: Graphics Abstraction
    subgraph Phase 4 ["Phase 4: Graphics Pipeline Abstraction"]
        D1["Encapsulate Vertex Buffers (VBO/VAO)"] --> D2["Build Shader Compilation Utility"]
        D2 --> D3["Create Basic Draw Renderer Submission"]
    end

    %% Phase 5: UI & Dual-Purpose Framework
    subgraph Phase 5 ["Phase 5: User Interface & Dual-Purpose (ImGui & FBO)"]
        E1["Integrate Dear ImGui Layer"] --> E2["Implement Framebuffer Objects (FBO)"]
        E2 --> E3["Render Game Viewport Inside ImGui Panel"]
    end

    %% Phase 6: Sandbox Apps
    subgraph Phase 6 ["Phase 6: Sandbox & Tooling"]
        F1["Inherit Custom Client Apps"] --> F2["Build Dual-Purpose Games & Desktop Tools"]
    end

    %% Flow Connections
    A4 ==> B1
    B3 ==> C1
    C3 ==> D1
    D3 ==> E1
    E3 ==> F1
```
# OpenGL utilities

These are header-only OpenGL helpers in the `Utils` namespace. Include them
where needed and call their functions only after creating an OpenGL context and
loading GLAD. Create and release GPU resources while the context that owns them
is current. Resource file names in the examples are relative to the process's
working directory; run from the project root or the build output directory,
where CMake copies the `res/` folder.

## Shader

`u_shader.h` loads vertex and fragment shaders from text files, compiles and
links them, and provides uniform setters:

```cpp
#include "utils/u_shader.h"

Utils::Shader shader;
shader.LoadFromFiles("res/cube.vs", "res/cube.fs");
shader.Use();
shader.SetMat4("u_Model", model);
shader.SetMat4("u_View", camera.GetViewMatrix());
shader.SetMat4("u_Projection", camera.GetProjectionMatrix());
shader.SetVec4("u_Color", 0.8f, 0.3f, 0.2f, 1.0f);
```

Available setters are `SetBool`, `SetInt`, `SetFloat`, `SetVec3`, `SetVec4`,
and `SetMat4`. File, compilation, link, and missing-uniform errors throw
exceptions with details; handle them at an application boundary if your app
needs graceful recovery.

## Camera and matrices

`u_camera.h` provides `Utils::Vec3`, column-major `Utils::Mat4`, and `Utils::Camera`.
Matrices are laid out for OpenGL and can be uploaded directly with `Shader::SetMat4`.
Use radians for camera field of view and rotation angles; `Utils::DegreesToRadians`
converts degrees:

```cpp
Utils::Camera camera(
    {2.0f, 2.0f, 3.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f});
camera.SetPerspective(Utils::DegreesToRadians(45.0f), aspect, 0.1f, 100.0f);

const Utils::Mat4 model =
    Utils::Mat4::Translation({0.0f, 0.0f, 0.0f}) *
    Utils::Mat4::RotationY(angleRadians) *
    Utils::Mat4::Scale({1.0f, 1.0f, 1.0f});
```

Matrices multiply column vectors, so combine transforms in the order that
produces the desired model transform. The usual vertex-shader order is
`u_Projection * u_View * u_Model * vec4(position, 1.0)`.

## Textures

`u_texture.h` provides `Utils::Texture2D`. It can upload RGB or RGBA byte data
or load ASCII/binary PPM (`P3`/`P6`) images:

```cpp
#include "utils/u_texture.h"

Utils::Texture2D texture;
texture.LoadPPM("res/checker.ppm");
texture.Bind(0);
shader.Use();
shader.SetInt("u_Texture", 0);
```

For generated image data, call `Create(width, height, channels, pixels)` with
three (RGB) or four (RGBA) channels. `Bind()` selects a texture unit and
`Unbind()` clears the current 2D texture binding. PNG/JPEG decoding is not
included; convert images to PPM or add an image decoder if those formats are
needed. Texture creation and upload must happen with an active OpenGL context.

All three wrappers are non-copyable and release their OpenGL object in their
destructor. Ensure the correct context is still current when a wrapper is
destroyed, or call `Release()` earlier while that context is active.

cmake_minimum_required(VERSION 3.16)
project(MyEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENABLE_ASAN "Enable AddressSanitizer for memory debugging" OFF)

find_package(Threads REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

# Ensure cpp-httplib is available before linking:
# find_package(httplib CONFIG QUIET) # or FetchContent if vendored/fetched

set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/imgui")

file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp"
)

set(THIRD_PARTY_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/glad/src/glad.c"
    "${IMGUI_DIR}/imgui.cpp"
    "${IMGUI_DIR}/imgui_demo.cpp"
    "${IMGUI_DIR}/imgui_draw.cpp"
    "${IMGUI_DIR}/imgui_tables.cpp"
    "${IMGUI_DIR}/imgui_widgets.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_glfw.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp"
)

add_executable(MyEngine
    ${ENGINE_SOURCES}
    ${THIRD_PARTY_SOURCES}
)

target_include_directories(MyEngine PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/source"
)

target_include_directories(MyEngine SYSTEM PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/glad/include"
    "${IMGUI_DIR}"
    "${IMGUI_DIR}/backends"
)

target_link_libraries(MyEngine PRIVATE
    OpenGL::GL
    glfw
    Threads::Threads
)

if(TARGET cpp-httplib)
    target_link_libraries(MyEngine PRIVATE cpp-httplib)
endif()

if(UNIX AND NOT APPLE)
    target_link_libraries(MyEngine PRIVATE dl X11)
endif()

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


# foreach(asset_dir IN ITEMS resources res)
#     if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${asset_dir}")
#         add_custom_command(
#             TARGET MyEngine POST_BUILD
#             COMMAND ${CMAKE_COMMAND} -E copy_directory
#                 "${CMAKE_CURRENT_SOURCE_DIR}/${asset_dir}"
#                 "$<TARGET_FILE_DIR:MyEngine>/${asset_dir}"
#             COMMENT "Copying ${asset_dir} directory to output folder"
#         )
#     endif()
# endforeach()

# Track all files inside resources and res
file(GLOB_RECURSE ASSET_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/resources/*"
    "${CMAKE_CURRENT_SOURCE_DIR}/res/*"
)

# Runs EVERY time you build, even if no .cpp files changed
add_custom_target(CopyAssets ALL
    DEPENDS ${ASSET_FILES}
    COMMENT "Syncing shader and asset directories to output folder"
)

foreach(asset_dir IN ITEMS resources res)
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${asset_dir}")
        add_custom_command(
            TARGET CopyAssets POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${CMAKE_CURRENT_SOURCE_DIR}/${asset_dir}"
                "${CMAKE_BINARY_DIR}/${asset_dir}"
        )
    endif()
endforeach()

# Now there is no cycle!
add_dependencies(MyEngine CopyAssets)

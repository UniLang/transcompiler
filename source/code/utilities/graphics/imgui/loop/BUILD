package(default_visibility = ["//visibility:public"])

load("//bazel/rules/hcp:hcp.bzl", "hcp")
load("//bazel/rules/cpp:object.bzl", "cpp_object")
load("//bazel/rules/enum_cpp:enum_cpp.bzl", "enum_cpp")

hcp(
    name = "mechanics",
    deps = [
        "//code/utilities/filesystem/paths:lib",
        "//code/utilities/graphics/sdl:sdl_init_settings",
        "//code/utilities/graphics/sdl:sdl_window_creator",
        #"//code/utilities/graphics/sfml:game_loop",
        "//code/utilities/graphics/sdl:sdl_initializer",
        "//code/utilities/graphics/sdl:sdl_swap_interval_setter",
        "//code/utilities/graphics/opengl/loader:opengl_loader",
        "//code/utilities/graphics/imgui/initialize:opengl_initializer",
        "//code/utilities/graphics/imgui/initialize:imgui_initializer",
        "//code/utilities/graphics/imgui/loop:event_poller",
        #"@GL",
        "@imgui//:imgui_sdl_opengl3",
    ],
)

hcp(
    name = "event_poller",
    deps = [
        "//code/utilities/filesystem/paths:lib",
        "//code/utilities/graphics/sdl:sdl_init_settings",
        "//code/utilities/graphics/sdl:sdl_window_creator",
        "@GL",
        "@imgui//:imgui_sdl_opengl3",
    ],
)

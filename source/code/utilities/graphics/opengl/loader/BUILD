package(default_visibility = ["//visibility:public"])

load("//bazel/rules/hcp:hcp.bzl", "hcp")
load("//bazel/rules/cpp:object.bzl", "cpp_object")

cc_library(
    name = "opengl_loaders",
    srcs = ["opengl_loaders.hpp"],
    deps = [
        "@imgui//:imgui_sdl_opengl3",
    ],
)

hcp(
    name = "opengl_loader",
    deps = [
        "//code/utilities/graphics/opengl/loader:opengl_loaders",
    ],
)

package(default_visibility = ["//visibility:public"])

load("//bazel/rules/hcp:hcp.bzl", "hcp")
load("//bazel/rules/cpp:object.bzl", "cpp_object")
load("//bazel/rules/enum_cpp:enum_cpp.bzl", "enum_cpp")

hcp(
    name = "chart_get_settings",
    deps = [
        "//code/utilities/data_structures/color:rgb_part_range",
    ],
)

hcp(
    name = "chart_getter",
    deps = [
        "//code/utilities/chart/ascii:chart_get_settings",
        "//code/utilities/colors:lib",
        "//code/utilities/math",
        "//code/utilities/types/strings/creators:lib",
        "//code/utilities/types/strings/observers/padding:lib",
        "//code/utilities/types/vectors/observers:lib",
    ],
)

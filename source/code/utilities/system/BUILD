package(default_visibility = ["//visibility:public"])

load("//bazel/rules/hcp:hcp.bzl", "hcp")
load("//bazel/rules/cpp:object.bzl", "cpp_object")

hcp(
    name = "installed_programs_checker",
    deps = [
        "//code/utilities/system:check_installed_program_settings",
        "//code/utilities/system:lib",
    ],
)

hcp(
    name = "check_installed_program_settings",
    deps = [
    ],
)

cc_library(
    name = "lib",
    srcs = ["lib.cpp"],
    hdrs = ["lib.hpp"],
    deps = ["//code/utilities/program/call:lib"],
)

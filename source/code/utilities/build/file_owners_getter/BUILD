package(default_visibility = ["//visibility:public"])

load("//bazel/rules/hcp:hcp.bzl", "hcp")
load("//bazel/rules/cpp:object.bzl", "cpp_object")
load("//bazel/rules/cpp:main.bzl", "cpp_main")

hcp(
    name = "file_owners_getter",
    deps = [
        "//code/utilities/filesystem/paths:lib",
        "//code/utilities/output/printers:lib",
        "//code/utilities/program/call/process_spawn:process_spawner",
        "//code/utilities/types/strings/observers/other:lib",
        "//code/utilities/types/strings/observers/splitting:lib",
        "//code/utilities/types/strings/transformers/removing:lib",
        "//code/utilities/types/strings/transformers/trimming:lib",
    ],
)

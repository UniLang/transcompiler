package(default_visibility = ["//visibility:public"])

load("//bazel/rules/hcp:hcp.bzl", "hcp")
load("//bazel/rules/cpp:object.bzl", "cpp_object")

hcp(
    name = "file_duration_extractor",
    deps = [
        "//code/utilities/build/file_owners_getter",
        "//code/utilities/build/profile_parser/data:duration_file",
        "//code/utilities/build/profile_parser/data:owned_duration_file",
        "//code/utilities/filesystem/paths:lib",
        "//code/utilities/formats/json/converters:json_file_io",
        "//code/utilities/formats/json/converters:lib",
        "//code/utilities/types/strings/observers/other:lib",
        "//code/utilities/types/strings/observers/path:lib",
        "//code/utilities/types/strings/observers/splitting:lib",
    ],
)

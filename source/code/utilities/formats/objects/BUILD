package(default_visibility = ["//visibility:public"])

load("//bazel/rules/hcp:hcp.bzl", "hcp")
load("//bazel/rules/cpp:object.bzl", "cpp_object")

hcp(
    name = "cuda_arch_symbol_counter",
    deps = [
        "//code/utilities/types/vectors/creators:lib",
        "//code/utilities/types/vectors/observers:lib",
        "//code/utilities/filesystem/files/creating:lib",
        "//code/utilities/types/strings/transformers/appending:lib",
        "//code/utilities/types/strings/observers/splitting:lib",
        "//code/utilities/program/wrappers/cuobjdump:cuobjdump_finder",
        "//code/utilities/program/call:lib",
        "//code/utilities/types/strings/observers/converting:lib",
        "//code/utilities/types/strings/transformers/trimming:lib",
    ],
)

hcp(
    name = "cuda_arch_pruner",
    deps = [
        "//code/utilities/types/vectors/creators:lib",
        "//code/utilities/types/vectors/observers:lib",
        "//code/utilities/filesystem/files/creating:lib",
        "//code/utilities/types/strings/transformers/appending:lib",
        "//code/utilities/types/strings/observers/splitting:lib",
        "//code/utilities/program/wrappers/nvprune:nvprune_finder",
        "//code/utilities/program/call:lib",
        "//code/utilities/types/strings/observers/converting:lib",
        "//code/utilities/types/strings/transformers/trimming:lib",
        "//code/utilities/types/strings/transformers/search_replace:lib",
        "//code/utilities/program/call/process_spawn:process_spawner",
    ],
)
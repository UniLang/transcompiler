package(default_visibility = ["//visibility:public"])

load("//bazel/rules/hcp:hcp.bzl", "hcp")
load("//bazel/rules/cpp:object.bzl", "cpp_object")

hcp(
    name = "word_speaker",
    deps = [
        "//code/utilities/filesystem/files/temp:existing_temp_file",
        "//code/utilities/program/call:lib",
        "//code/utilities/random:lib",
        "//code/utilities/random/files:random_files",
    ],
)

hcp(
    name = "animal_crossing_speaker",
    deps = [
        "//code/utilities/assets:english_sounds",
        "//code/utilities/filesystem/files/temp:existing_temp_file",
        "//code/utilities/peripheral/sound/wav:pitch_adjuster",
        "//code/utilities/peripheral/sound/wav:tempo_adjuster",
        "//code/utilities/peripheral/sound/wav:wav_file_join_settings",
        "//code/utilities/peripheral/sound/wav:wav_file_joiner",
        "//code/utilities/program/call:lib",
        "//code/utilities/random:lib",
        "//code/utilities/types/vectors/operators:lib",
    ],
)

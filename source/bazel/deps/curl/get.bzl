# Do not edit this file directly.
# It was auto-generated by: code/programs/reflexivity/reflexive_refresh

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def curl():
    http_archive(
        name = "curl",
        build_file = "//bazel/deps/curl:build.BUILD",
        sha256 = "3f6c54fb691853e9b00ed484ea2f52566c7af172ecd48cd9eeec8041a9ac679b",
        strip_prefix = "curl-11974ac859c5d82def59e837e0db56fef7f6794e",
        urls = [
            "https://github.com/Unilang/curl/archive/11974ac859c5d82def59e837e0db56fef7f6794e.tar.gz",
        ],
        patches = [
            "//bazel/deps/curl/patches:p1.patch",
        ],
    )

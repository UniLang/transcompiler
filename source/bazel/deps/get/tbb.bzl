# Do not edit this file directly.
# It was auto-generated by: code/tools/reflexivity/build_gen

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def tbb():
    http_archive(
        name = "tbb",
        build_file = "//bazel/deps/build_files:tbb.BUILD",
        sha256 = "1a3fc4ff6932e524c8afc3461b350851977fc4bfeb498411020c15dd183e2c8a",
        strip_prefix = "tbb-314792356bf75f4a190277536aea543b9b6b310b",
        urls = [
            "https://github.com/Unilang/tbb/archive/314792356bf75f4a190277536aea543b9b6b310b.tar.gz",
        ],
    )
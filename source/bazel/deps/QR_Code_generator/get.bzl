# Do not edit this file directly.
# It was auto-generated by: code/programs/reflexivity/reflexive_refresh

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def qRCodeGenerator():
    http_archive(
        name = "QR_Code_generator",
        build_file = "//bazel/deps/QR_Code_generator:build.BUILD",
        sha256 = "1c281781d834e703ec40750ee0e0924567d8edc469d6f43083600e0195a74044",
        strip_prefix = "QR-Code-generator-8518684c0f33d004fa93971be2c6a8eca3167d1e",
        urls = [
            "https://github.com/Unilang/QR-Code-generator/archive/8518684c0f33d004fa93971be2c6a8eca3167d1e.tar.gz",
        ],
    )

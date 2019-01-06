load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive", "http_file")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

def toolchains():

    git_repository(
        name = 'co_vsco_bazel_toolchains',
        remote = 'https://github.com/vsco/bazel-toolchains',
        tag = 'v64.0.3282.167',
    )

    http_archive(
        name = "com_grail_bazel_toolchain",
        strip_prefix = "bazel-toolchain-master",
        urls = ["https://github.com/grailbio/bazel-toolchain/archive/master.tar.gz"],
    )


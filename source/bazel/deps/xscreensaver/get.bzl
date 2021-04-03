# Do not edit this file directly.
# It was auto-generated by: code/programs/reflexivity/reflexive_refresh

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def xscreensaver():
    http_archive(
        name = "xscreensaver",
        build_file = "//bazel/deps/xscreensaver:build.BUILD",
        sha256 = "014c757da20b2c369c51bcaa2860e39e1844f1e3a3d784fc29685f390b762f77",
        strip_prefix = "xscreensaver-9c9ac21de7b85b6c4c767f3005b510d78b0a3e97",
        urls = [
            "https://github.com/Unilang/xscreensaver/archive/9c9ac21de7b85b6c4c767f3005b510d78b0a3e97.tar.gz",
        ],
        patches = [
            "//bazel/deps/xscreensaver/patches:p1.patch",
            "//bazel/deps/xscreensaver/patches:p2.patch",
        ],
        patch_args = [
            "-p1",
        ],
        patch_cmds = [
            "sed -i '1s/^/void clear_gl_error(void);\\n /' hacks/glx/xlock-gl-utils.c",
        ],
    )

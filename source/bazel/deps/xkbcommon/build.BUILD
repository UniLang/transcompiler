package(default_visibility = ["//visibility:public"])

cc_library(
    name = "xkbcommon",
    srcs = glob(
        [
            "xkbcommon/**/*.h",
            "src/**/*.c",
        ],
        exclude = [
            #"src/keysym.c",
        ],
    ),
    hdrs = glob(
        [
            "xkbcommon/**/*.h",
            "src/**/*.h",
        ],
        exclude = [
            #"src/ks_tables.h",
        ],
    ),
    copts = [
        '-DXLOCALEDIR=\\\"/usr/share/X11/locale\\\"',
        '-DDEFAULT_XKB_RULES=\\\"evdev\\\"',
        '-DDFLT_XKB_CONFIG_ROOT=\\\"/usr/share/X11/xkb\\"',
        '-DDEFAULT_XKB_MODEL=\\\"pc105\\"',
        '-DDEFAULT_XKB_LAYOUT=\\\"us\\"',
        "-DKTABLESIZE=32",
    ],
    includes = [
        ".",
        "src",
        "src/x11",
        "xcb",
        "xcb/src",
        "xkbcommon",
        "xkbcommon/src",
        "xkbcommon/src/x11",
    ],
    deps = [
        "@xcb",
    ],
)

package(default_visibility = ["//visibility:public"])
load("//bazel/cookbook/hcp:hcp.bzl", "hcp")
load("//bazel/cookbook/hcp:hcp_pos.bzl", "hcp_pos")
load("//bazel/cookbook/cpp:object.bzl", "cpp_object")
load("//bazel/cookbook/hcp:hcp_and_hcp_pos.bzl", "hcp_and_hcp_pos")

hcp(name="slider_state", deps = [
    "//code/utilities/data_structures/graphics/objects/label:label_settings",
])

hcp_and_hcp_pos(name="slider", deps = [
    "//code/utilities/data_structures/graphics/objects/slider:slider_state",
])

hcp(name="slider_drawer", deps = [
    "//code/utilities/fonts/bdf/settings:character_segment",
    "//code/utilities/data_structures/graphics/objects/label:label_settings",
    "//code/utilities/data_structures/graphics/objects/slider:positioned_slider",
    "//code/utilities/data_structures/graphics/objects/label:label_drawer",
    "//code/utilities/data_structures/graphics/objects:frame_elements",
    "//code/utilities/types/vectors/operators:lib",
    "//code/utilities/peripheral/mouse/state:mouse_state",
    "//code/utilities/fonts/bdf/character_maps:character_maps",
])

hcp(name="default_sliders", deps = [
    "//code/utilities/data_structures/graphics/objects/slider:slider_state",
    "//code/utilities/data_structures/graphics/objects/label/style:default_label_styles",
])

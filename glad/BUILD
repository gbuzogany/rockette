load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
	name = "glad",
	hdrs = glob(["include/**/*.h"]),
	includes = ["include"],
	srcs = glob(["src/glad.c"]),
	visibility = ["//visibility:public"],
)

cc_library(
	name = "headers",
	hdrs = glob(["include/**/*.h"]),
	visibility = ["//visibility:public"],
)

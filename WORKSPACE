SDL2_LOCAL_PATH = "path_to_local_sdl2"
SDL2_LOCAL_BUILD_PATH = SDL2_LOCAL_PATH + "/BUILD.bazel"

workspace(name = "com_gbuzogany_dash")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")

load("//:bazel/repositories.bzl", "dash_repositories")
dash_repositories()

# grpc deps
load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")

grpc_deps()

load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")
grpc_extra_deps()

# end grpc deps

new_local_repository(
    name = "sdl2_local",
    path = SDL2_LOCAL_PATH,
    build_file = SDL2_LOCAL_BUILD_PATH
)

new_local_repository(
    name = "pi_deps",
    path = "/opt/vc/include",
    build_file_content = """
package(default_visibility = ["//visibility:public"])

cc_library(
    name = "headers",
    hdrs = glob(["**/*.h"])
)

"""
)

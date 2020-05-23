load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def dash_repositories():

    _maybe(
        http_archive,
        name = "net_zlib_zlib",
        sha256 = "6d4d6640ca3121620995ee255945161821218752b551a1a180f4215f7d124d45",
        build_file = "@com_gbuzogany_dash//bazel/third_party:zlib.BUILD",
        strip_prefix = "zlib-cacf7f1d4e3d44d871b605da3b647f07d718623f",
        urls = [
            "https://github.com/madler/zlib/archive/cacf7f1d4e3d44d871b605da3b647f07d718623f.tar.gz"
        ]
    )

    _maybe(
        http_archive,
        name = "glm",
        sha256 = "6b79c3d06d9745d1cce3f38c0c15666596f9aefff25ddb74df3af0a02f011ee1",
        build_file = "@com_gbuzogany_dash//bazel/third_party:glm.BUILD",
        strip_prefix = "glm",
        urls = [
            "https://github.com/g-truc/glm/releases/download/0.9.9.7/glm-0.9.9.7.zip"
        ]
    )

    _maybe(
        http_archive,
        name = "org_freetype_freetype2",
        build_file = "@com_gbuzogany_dash//bazel/third_party:freetype2.BUILD",
        sha256 = "33a28fabac471891d0523033e99c0005b95e5618dc8ffa7fa47f9dadcacb1c9b",
        strip_prefix = "freetype-2.8",
        urls = [
            "http://download.savannah.gnu.org/releases/freetype/freetype-2.8.tar.gz"
        ]
    )

    _maybe(
        http_archive,
        name = "org_libpng_libpng",
        build_file = "@com_gbuzogany_dash//bazel/third_party:libpng.BUILD",
        sha256 = "7f415186d38ca71c23058386d7cf5135c8beda821ee1beecdc2a7a26c0356615",
        strip_prefix = "libpng-1.2.57",
        urls = [
            "https://github.com/glennrp/libpng/archive/v1.2.57.tar.gz"
        ]
    )

    _maybe(
        http_archive,
        name = "com_github_grpc_grpc",
        sha256 = "4cbce7f708917b6e58b631c24c59fe720acc8fef5f959df9a58cdf9558d0a79b",
        strip_prefix = "grpc-1.28.1",
        urls = [
            "https://github.com/grpc/grpc/archive/v1.28.1.tar.gz"
        ]
    )

    _maybe(
        http_archive,
        name = "rules_python",
        sha256 = "e5470e92a18aa51830db99a4d9c492cc613761d5bdb7131c04bd92b9834380f6",
        strip_prefix = "rules_python-4b84ad270387a7c439ebdccfd530e2339601ef27",
        urls = [
            "https://github.com/bazelbuild/rules_python/archive/4b84ad270387a7c439ebdccfd530e2339601ef27.tar.gz"
        ]
    )

    _maybe(
        http_archive,
        name = "rules_python",
        sha256 = "e5470e92a18aa51830db99a4d9c492cc613761d5bdb7131c04bd92b9834380f6",
        strip_prefix = "rules_python-4b84ad270387a7c439ebdccfd530e2339601ef27",
        urls = [
            "https://github.com/bazelbuild/rules_python/archive/4b84ad270387a7c439ebdccfd530e2339601ef27.tar.gz"
        ]
    )


    _maybe(
        http_archive,
        name = "sdl2_remote",
        sha256 = "6af801082372daacdd48bef7b4b4eaadb2c942668d76bec0296d4eaf8113b35a",
        strip_prefix = "sdl2-bazel-v0.4",
        urls = [
            "https://github.com/gbuzogany/sdl2/archive/bazel-v0.4.tar.gz"
        ]
    )

    _maybe(
        http_archive,
        name = "angle_headers",
        sha256 = "204c8bc45e26940a2c2daa1fb63773efbe72d3c4b644fabc43fad2201d457419",
        urls = [
            "https://gbuzogany.com/angle/angle-include.zip"
        ],
        build_file_content = """
package(default_visibility = ["//visibility:public"])

cc_library(
    name = "headers",
    hdrs = glob(["include/**/*.h", "include/**/*.inc"]),
)
"""
    )

    _maybe(
        http_archive,
        name = "angle_mac",
        sha256 = "dd8b116c49772801fb98e4379bbdb755fe16eb1bb69f902a17b03456b2df4286",
        urls = [
            "https://gbuzogany.com/angle/angle-mac-bin.zip"
        ],
        build_file_content = """
package(default_visibility = ["//visibility:public"])

cc_library(
    name = "lib",
    srcs = [
        "libEGL.dylib",
        "libGLESv2.dylib"
    ]
)
"""
    )

    _maybe(
        http_archive,
        name = "angle_win",
        sha256 = "d00a5b31d262e5cec2a963839f926882311567753265cccab49a5bee91e489da",
        urls = [
            "https://gbuzogany.com/angle/angle-win-bin.zip"
        ],
        build_file_content = """
package(default_visibility = ["//visibility:public"])

cc_library(
    name = "lib",
    srcs = [
        "libEGL.dll",
        "libGLESv2.dll"
    ]
)
"""
    )

    _maybe(
        http_archive,
        name = "angle_linux",
        sha256 = "c53f3cb1b776150def2eb3f358c3e8b88f9b492a97a8fd325d86ed0291a9c12e",
        urls = [
            "https://gbuzogany.com/angle/angle-linux-bin.zip"
        ],
        build_file_content = """
package(default_visibility = ["//visibility:public"])

cc_library(
    name = "lib",
    srcs = [
        "libEGL.so",
        "libGLESv2.so"
    ]
)
"""
    )

def _maybe(repo_rule, name, **kwargs):
    if name not in native.existing_rules():
        repo_rule(name = name, **kwargs)
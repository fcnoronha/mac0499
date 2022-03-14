cc_library(
    name = "splay-tree",
    srcs = ["splayTree.cpp"],
    hdrs = ["splayTree.hpp"],
    copts = ["-O2"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "link-cut-tree",
    srcs = ["linkCutTree.cpp"],
    hdrs = ["linkCutTree.hpp"],
    deps = [":splay-tree"],
    visibility = ["//visibility:public"],
    copts = ["-O2"],
)

cc_library(
    name = "retroactive-union-find",
    srcs = ["retroactiveUnionFind.cpp"],
    hdrs = ["retroactiveUnionFind.hpp"],
    deps = [":link-cut-tree"],
    visibility = ["//visibility:public"],
    copts = ["-O2"],
)

cc_test(
    name = "retroactive-union-find-test",
    srcs = ["retroactiveUnionFindTest.cpp"],
    deps = [
        "@com_google_googletest//:gtest_main",
        ":retroactive-union-find",
    ],
)
###############################################################################
####################################### link-cut tree
###############################################################################

cc_library(
    name = "splay-tree",
    srcs = ["splayTree.cpp"],
    hdrs = ["splayTree.hpp"],
    copts = ["-O2", "-std=c++17", "-Wall", "-Wextra", "-pedantic"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "link-cut-tree",
    srcs = ["linkCutTree.cpp"],
    hdrs = ["linkCutTree.hpp"],
    deps = [":splay-tree"],
    visibility = ["//visibility:public"],
    copts = ["-O2", "-std=c++17", "-Wall", "-Wextra", "-pedantic"],
)
cc_test(
    name = "link-cut-tree-test",
    srcs = ["linkCutTreeTest.cpp"],
    deps = [
        "@com_google_googletest//:gtest_main",
        ":link-cut-tree",
    ],
)

###############################################################################
####################################### retroactive union-find
###############################################################################

cc_library(
    name = "retroactive-union-find",
    srcs = ["retroactiveUnionFind/retroactiveUnionFind.cpp"],
    hdrs = ["retroactiveUnionFind/retroactiveUnionFind.hpp"],
    deps = [":link-cut-tree"],
    visibility = ["//visibility:public"],
    copts = ["-O2", "-std=c++17", "-Wall", "-Wextra", "-pedantic"],
)

cc_test(
    name = "retroactive-union-find-test",
    srcs = ["retroactiveUnionFind/retroactiveUnionFindTest.cpp"],
    deps = [
        "@com_google_googletest//:gtest_main",
        ":retroactive-union-find"
    ],
)

###############################################################################
####################################### retroactive MSF
###############################################################################

cc_library(
    name = "incremental-msf",
    srcs = ["incrementalMSF/incrementalMSF.cpp"],
    hdrs = ["incrementalMSF/incrementalMSF.hpp"],
    deps = [":link-cut-tree"],
    visibility = ["//visibility:public"],
    copts = ["-O2", "-std=c++17", "-Wall", "-Wextra", "-pedantic"],
)

cc_test(
    name = "incremental-msf-test",
    srcs = ["incrementalMSF/incrementalMSFTest.cpp"],
    deps = [
        "@com_google_googletest//:gtest_main",
        ":incremental-msf",
    ],
)

cc_library(
    name = "retroactive-msf",
    srcs = ["retroactiveMSF/retroactiveMSF.cpp"],
    hdrs = ["retroactiveMSF/retroactiveMSF.hpp"],
    deps = [":incremental-msf"],
    visibility = ["//visibility:public"],
    copts = ["-O2", "-std=c++17", "-Wall", "-Wextra", "-pedantic"],
)
cc_test(
    name = "retroactive-msf-test",
    srcs = ["retroactiveMSF/retroactiveMSFTest.cpp"],
    deps = [
        "@com_google_googletest//:gtest_main",
        ":retroactive-msf",
    ],
)
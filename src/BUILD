cc_library(
    name="matrixBuild",
    srcs=["matrix.cpp"],
    hdrs=["matrix.h"],
    )
cc_library(
    name="catch",
    srcs=["catch.hpp"],
    deps=[],)

cc_binary(
    name="matrix",
    srcs=["matrix.cpp"],
    deps=[
        ":matrixBuild",
        ],
    )

cc_test(
    name="matrix_test",
    srcs=["matrix_test.cpp"],
    deps=[
        ":matrixBuild",
        ":catch",
        ],
    )

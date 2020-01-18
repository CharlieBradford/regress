cc_library(
    name="matrix",
    srcs=["matrix.cpp"],
    hdrs=["matrix.h"],
    )

cc_library(
    name="regression",
    srcs=["regression.cpp",
          "matrix.cpp"],
    hdrs=["regression.h",
          "matrix.h"],
    )

cc_binary(
    name="matrix_test",
    srcs=["matrix_test.cpp"],
    deps=[
        ":matrix",
        ":regression"
        ],
    )


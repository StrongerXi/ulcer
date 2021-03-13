cmake_minimum_required(VERSION 2.8)
project(ulcer)

set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -std=c89 -lm -g")

set(SOURCE_FILES
        src/util/alloc.c
        src/util/array.c
        src/util/cstring.c
        src/util/hash_table.c
        src/util/hashfn.c
        src/util/list.c
        src/builtins/common.c
        src/builtins/libfile.c
        src/builtins/libheap.c
        src/builtins/libmath.c
        src/builtins/libnative.c
        src/builtins/libruntime.c
        src/builtins/libstr.c
        src/frontend/lexer.c
        src/frontend/parser.c
        src/frontend/module.c
        src/frontend/source_code.c
        src/frontend/statement.c
        src/frontend/token.c
        src/frontend/expression.c
        src/environment.c
        src/error.c
        src/evaluator.c
        src/executor.c
        src/heap.c
        src/native.c
        src/main.c
)

add_executable(ulcer ${SOURCE_FILES})
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
        src/builtins/libfile.c
        src/builtins/libheap.c
        src/builtins/libmath.c
        src/builtins/libnative.c
        src/builtins/libruntime.c
        src/builtins/libstr.c
        src/environment.c
        src/error.c
        src/evaluator.c
        src/executor.c
        src/expression.c
        src/heap.c
        src/lexer.c
        src/parser.c
        src/module.c
        src/native.c
        src/source_code.c
        src/statement.c
        src/token.c
        src/main.c
)

add_executable(ulcer ${SOURCE_FILES})
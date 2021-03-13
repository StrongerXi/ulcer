
#include "../native.h"
#include "../error.h"
#include "common.h"
#include "../heap.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static void native_runtime_gc(environment_t env, unsigned int argc)
{
    heap_gc(env);

    environment_pop_value(env);

    environment_push_null(env);
}

void import_runtime_library(environment_t env)
{
    table_t tbl = create_table(env, "runtime");

    struct pair_nf pairs[] = {
        { "gc",         native_runtime_gc },
    };

    push_native_funcs(env, tbl, pairs, sizeof(pairs) / sizeof(struct pair_nf));
}
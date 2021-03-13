

#include "../runtime/native.h"
#include "../runtime/error.h"
#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static void native_heap_alloc(environment_t env, unsigned int argc)
{
    value_t  value;
    value_t* values;

    value = list_element(list_rbegin(env->stack), value_t, link);

    values = array_base(value->u.object_value->u.array, value_t*);

    if (argc < 1) {
        environment_pop_value(env);
        environment_push_null(env);
        return;
    }

    environment_push_pointer(env, (void*)malloc(native_check_int_value(values[0])));

    environment_xchg_stack(env);

    environment_pop_value(env);
}

static void native_heap_free(environment_t env, unsigned int argc)
{
    value_t  value;
    value_t* values;

    value = list_element(list_rbegin(env->stack), value_t, link);

    values = array_base(value->u.object_value->u.array, value_t*);

    if (argc < 1) {
        environment_pop_value(env);
        environment_push_null(env);
        return;
    }

    free(native_check_pointer_value(values[0]));

    environment_pop_value(env);

    environment_push_null(env);
}

void import_heap_library(environment_t env)
{
    table_t tbl = create_table(env, "heap");

    struct pair_nf pairs[] = {
        { "alloc",           native_heap_alloc  },
        { "free",            native_heap_free   },
    };

    push_native_funcs(env, tbl, pairs, sizeof(pairs) / sizeof(struct pair_nf));
}
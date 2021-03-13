

#include "../runtime/native.h"
#include "../runtime/error.h"
#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static void native_file_open(environment_t env, unsigned int argc)
{
    value_t  value;
    value_t* values;
    FILE* fp;

    value = list_element(list_rbegin(env->stack), value_t, link);

    values = array_base(value->u.object_value->u.array, value_t*);

    if (argc < 2) {
        environment_pop_value(env);
        environment_push_null(env);
        return;
    }

    fp = fopen(native_check_string_value(values[0]),
        native_check_string_value(values[1]));

    environment_push_pointer(env, (void*)fp);

    environment_xchg_stack(env);

    environment_pop_value(env);
}

static void native_file_close(environment_t env, unsigned int argc)
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

    environment_push_int(env, fclose((FILE*)native_check_pointer_value(values[0])));

    environment_xchg_stack(env);

    environment_pop_value(env);
}

static void native_file_read(environment_t env, unsigned int argc)
{
    value_t  value;
    value_t* values;

    value = list_element(list_rbegin(env->stack), value_t, link);

    values = array_base(value->u.object_value->u.array, value_t*);

    if (argc < 3) {
        environment_pop_value(env);
        environment_push_null(env);
        return;
    }

    environment_push_int(env, fread((void*)native_check_pointer_value(values[1]),
        1,
        native_check_int_value(values[2]),
        (FILE*)native_check_pointer_value(values[0])));

    environment_xchg_stack(env);

    environment_pop_value(env);
}

static void native_file_write(environment_t env, unsigned int argc)
{
    value_t  value;
    value_t* values;

    value = list_element(list_rbegin(env->stack), value_t, link);

    values = array_base(value->u.object_value->u.array, value_t*);

    if (argc < 3) {
        environment_pop_value(env);
        environment_push_null(env);
        return;
    }

    environment_push_int(env, fwrite((void*)native_check_pointer_value(values[1]),
            1,
            native_check_int_value(values[2]),
            (FILE*)native_check_pointer_value(values[0])));

    environment_xchg_stack(env);

    environment_pop_value(env);
}

void import_file_library(environment_t env)
{
    table_t tbl = create_table(env, "file");

    struct pair_nf pairs[] = {
        { "open",           native_file_open    },
        { "close",          native_file_close   },
        { "read",           native_file_read    },
        { "write",          native_file_write   },
    };

    push_native_funcs(env, tbl, pairs, sizeof(pairs) / sizeof(struct pair_nf));
}

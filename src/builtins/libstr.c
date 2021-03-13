#include "../native.h"
#include "../error.h"
#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

static
cstring_t do_replace(cstring_t str, cstring_t pattern, cstring_t to, int max)
{
    unsigned long pattern_len = cstring_length(pattern);
    unsigned long to_len = cstring_length(to);
    cstring_t str_end = str + cstring_length(str);
    cstring_t dst = cstring_newempty(cstring_length(str));
    char *find = str;
    char *last = str;
    bool repeat = max < 0 ? true : false;

    for (; repeat ? repeat : max--;) {
        find = strstr(find, pattern);
        if (find == NULL) {
            goto done;
        }

        dst = cstring_catlen(dst, last, (unsigned long)(find - last));
        dst = cstring_catlen(dst, to, to_len);

        find += pattern_len;
        last = find;
    }

done:
    dst = cstring_catlen(dst, last, (unsigned long)(str_end - last));
    return dst;
}

static void native_string_replace(environment_t env, unsigned int argc)
{
    value_t  value;
    value_t* values;
    cstring_t dst;
    int max;

    value = list_element(list_rbegin(env->stack), value_t, link);

    values = array_base(value->u.object_value->u.array, value_t*);

    if (argc < 3) {
        environment_pop_value(env);
        environment_push_null(env);
        return;
    }

    if (argc == 3) {
        max = -1;
    } else {
        max = native_check_int_value(values[3]);
    }

    dst = do_replace(
        (cstring_t)native_check_string_value(values[0]),
        (cstring_t)native_check_string_value(values[1]),
        (cstring_t)native_check_string_value(values[2]),
        max);

    environment_push_string(env, dst);
   
    cstring_free(dst);

    environment_xchg_stack(env);

    environment_pop_value(env);
}

static void native_string_length(environment_t env, unsigned int argc)
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

    environment_push_int(env, cstring_length((cstring_t)native_check_string_value(values[0])));

    environment_xchg_stack(env);

    environment_pop_value(env);
}

static void native_string_copy(environment_t env, unsigned int argc)
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

    environment_push_str(env, native_check_string_value(values[0]));

    environment_xchg_stack(env);

    environment_pop_value(env);
}

void import_string_library(environment_t env)
{
    table_t tbl = create_table(env, "string");

    struct pair_nf pairs[] = {
        { "length",         native_string_length },
        { "copy",           native_string_copy },
        { "replace",        native_string_replace },
    };

    push_native_funcs(env, tbl, pairs, sizeof(pairs) / sizeof(struct pair_nf));
}
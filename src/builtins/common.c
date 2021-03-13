#include "common.h"


table_t create_table(environment_t env, const char* name)
{

    value_t val;

    environment_push_str(env, name);

    environment_push_table(env);

    val = list_element(list_rbegin(env->stack), value_t, link);

    table_push_pair(environment_get_global_table(env), env);

    return val->u.object_value->u.table;
}

void push_native_funcs(environment_t env, table_t table, struct pair_nf pairs[], int n)
{
    int i;
    for (i = 0; i < n; i++) {
        environment_push_str(env, pairs[i].name);
        environment_push_native_function(env, pairs[i].func);
        table_push_pair(table, env);
    }
}

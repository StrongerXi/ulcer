#ifndef _BUILTINS_COMMON_H_
#define _BUILTINS_COMMON_H_

#include "../runtime/environment.h"
#include "../runtime/evaluator.h"

struct pair_nf {
  const char* name;
  native_function_pt func;
};

// Map `name` to a newly created table in the global table of `env`
// Return the table.
table_t create_table(environment_t env, const char* name);

// push `n` native functions from `pairs` into `table`
// `env` fascilitates value creation
void push_native_funcs(environment_t env, table_t table, struct pair_nf pairs[], int n);

#endif

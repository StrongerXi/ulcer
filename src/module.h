

#ifndef _ULCER_MODULE_H_
#define _ULCER_MODULE_H_

#include "config.h"
#include "util/stack.h"
#include "util/list.h"
#include "statement.h"

typedef struct module_s*         module_t;
typedef struct statements_s*     statements_t;

struct statements_s {
    list_t       stmts;
    stack_node_t link;
};

struct module_s {
    statements_t statements;
    list_t       functions;
    list_node_t  link;
};

module_t module_new(void);
void     module_free(module_t module);
void     module_add_function(module_t module, statement_t function_stmt);
void     module_add_statment(module_t module, statement_t stmt);

#endif
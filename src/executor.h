

#ifndef _ULCER_EXECUTOR_H_
#define _ULCER_EXECUTOR_H_

#include "config.h"
#include "environment.h"
#include "source_code.h"

typedef enum executor_result_e  executor_result_t;
typedef struct executor_s*      executor_t;

enum executor_result_e {
    EXECUTOR_RESULT_NORMAL,
    EXECUTOR_RESULT_RETURN,
    EXECUTOR_RESULT_BREAK,
    EXECUTOR_RESULT_CONTINUE,
};

/**
 * Parse `sc` and execute it with `env`.
 * EFFECT: 
 * - any effect from running the code
 * - update `env`
 */
void execute_code(environment_t env, source_code_t sc);
executor_result_t executor_statement(environment_t env, statement_t stmt);

#endif
#include "parser.h"
#include "native.h"
#include "lexer.h"
#include "util/list.h"
#include "environment.h"
#include "source_code.h"
#include "executor.h"
#include "heap.h"
#include "libsdl.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


source_code_t read_in_source_code_at(char* path) {
    source_code_t sc = source_code_new(path, SOURCE_CODE_TYPE_FILE);
    if (sc == NULL) {
      fprintf(stderr, "ulcer: cannot open %s: No such file or directory\n", path);
      exit(-1);
    }
    return sc;
}


int main(int argc, char** args)
{
    {
#ifdef WIN32
        _CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);  
#endif
    }

    {
        if (argc < 2) {
            printf("usage: ulcer souce_code.ul\n");
            printf("press any key to exit");
            getchar();
            exit(-1);
        }

        // parse source code and set up execution environment
        source_code_t sc = read_in_source_code_at(args[1]);
        lexer_t lex = lexer_new(sc);
        parser_t parse = parser_new(lex);
        module_t module = parser_generate_module(parse);
        environment_t env = environment_new();
        environment_add_module(env, module);
        setup_native_module(env);

        // run code and validate stack
        executor_t executor = executor_new(env);
        executor_run(executor);
        assert(list_is_empty(env->stack));

        // release resources
        executor_free(executor);
        environment_free(env);
        parser_free(parse);
        lexer_free(lex);
        source_code_free(sc);
    }

    return 0;
}
#include "frontend/source_code.h"
#include "frontend/lexer.h"
#include "frontend/parser.h"
#include "runtime/native.h"
#include "runtime/environment.h"
#include "runtime/executor.h"
#include "runtime/heap.h"
#include "util/list.h"
#include "builtins/libsdl.h"

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
        environment_t env = environment_new();
        setup_native_module(env);
        // program execution entry
        execute_code(env, sc);
        // release resources
        source_code_free(sc);
        environment_free(env);
    }

    return 0;
}
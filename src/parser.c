#include "parser.h"
#include <string.h>

uint32_t parse(int argc, char** restrict argv) {
    uint32_t result = 0;
    for(int i = 1; i < argc; i++) {
        if(!strcmp(COMMAND_HELP, argv[i]) ||
            !strcmp(COMMAND_HELP_ALT1, argv[i])) result |= HELP;

        if(!strcmp(COMMAND_MAKEFILE, argv[i]) || !strcmp(COMMAND_MAKEFILE_ALT1, argv[i])) {
            result |= MAKEFILE;
        }

        if(!strcmp(COMMAND_CPLUSPLUS, argv[i])) {
            result |= CPLUSPLUS;
        }
    }

    return result;
}
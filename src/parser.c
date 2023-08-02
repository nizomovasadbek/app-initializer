#include "parser.h"
#include <string.h>

uint32_t parse(int argc, char** restrict argv) {
    uint32_t result = 0;
    for(int i = 1; i < argc; i++) {
        if(!strcmp(COMMAND_HELP, argv[i]) ||
            !strcmp(COMMAND_HELP_ALT1, argv[i])) result |= HELP;
    }

    return result;
}
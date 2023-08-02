#ifndef _PARSER_H
#define _PARSER_H

#define HELP                0x01

#define COMMAND_HELP        "-h"
#define COMMAND_HELP_ALT1   "--help"

#include <stdint.h>

uint32_t parse(int, char** restrict);

#endif
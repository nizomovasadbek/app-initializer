#ifndef _PARSER_H
#define _PARSER_H

#define HELP                0x01
#define MAKEFILE            0x02
#define CPLUSPLUS           0x04
#define RESERVED1           0x08
#define RESERVED2           0x10
#define RESERVED3           0x20
#define RESERVED4           0x40
#define RESERVED5           0x80
#define RESERVED6           0x100
#define RESERVED7           0x200

#define COMMAND_HELP            "-h"
#define COMMAND_HELP_ALT1       "--help"
#define COMMAND_MAKEFILE        "--makefile"
#define COMMAND_MAKEFILE_ALT1   "-m"
#define COMMAND_CPLUSPLUS       "-cpp"

#include <stdint.h>

uint32_t parse(int, char** restrict);

#endif
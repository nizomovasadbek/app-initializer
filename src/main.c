#include <stdio.h>
#include "parser.h"
#include "generator.h"

int main(int argc, char* argv[]) {

    if(argc == 1) {
        printf("Argument should be at least one parameter\n<main> <app_name> [OPTIONS...]\n");
        printf("More info <main> -h, --help\n");
        return -1;
    }

    uint32_t result = parse(argc, argv);
    if(result & HELP) {
        printf("Simple C/C++ app generator.\n\t-h, --help -- prints this message and exits\n");
        return 1;
    }

    generate(result, argv[1]);

    return 0;
}
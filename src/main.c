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
        printf("Simple C/C++ app generator.\n\t-h, --help\t\tprints this message and exits\n");
        printf("\t-m, --makefile\t\tGenerate project with Makefile (Default cmake file)\n");
		printf("\nVersion 1.0.0\n");
		return 1;
    }

    for(unsigned char i = 1; i < argc; i++) {
        if(argv[i][0] != '-') {
            generate(result, argv[i]);
        }
    }

    return 0;
}

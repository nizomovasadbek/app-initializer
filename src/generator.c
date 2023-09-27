#include "generator.h"
#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

const char* cmake_content = "cmake_minimum_required(VERSION 3.12)\n"
 "project(main)\nset(CMAKE_CXX_FLAGS \"-Wall -Wextra\")\n"
 "set(CMAKE_CXX_FLAGS_DEBUG \"-g -fsanitize=address\")\n"
 "set(CMAKE_CXX_FLAGS_RELEASE \"-O3\")\n"
 "file(GLOB SRC \"src/*.c\")\n"
 "add_executable(main ${SRC})\n";

const char* make_content = "CC=gcc\nCC_FLAG=-g -fsanitize=address\nSRC=src\nBUILD=build\nMAIN=main"
 "\nall: check compile\ncompile:\n\t$(CC) $(CC_FLAG) $(SRC)/main.c -o $(BUILD)/$(MAIN)\n\n"
 "check:\n\tmkdir -p $(BUILD)\n\nclean:\n\trm -rf $(BUILD)\n";

const char* c_content = "#include <stdio.h>\n\nint main() {\n\tprintf(\"Hello World!\\n\");\n"
    "\n\treturn 0;\n}";

const char* cpp_content = "#include <iostream>\n\nint main(){\n\t"
    "std::cout << \"Hello, World\" << std::endl;\n\treturn 0;\n}";

bool generateCmake(const char* restrict, void (*)(const char* restrict));
bool generateMake(const char* restrict, void (*)(const char* restrict));
void generateCfile(const char *restrict);
void generateCppFile(const char *restrict);

bool generate(uint32_t result, const char* folder_name) {
    uint32_t folder_name_length = strlen(folder_name);
    int status = mkdir(folder_name, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    char sub[folder_name_length + 6];
    memset(sub, 0, folder_name_length + 6);
    strncat(sub, folder_name, folder_name_length);
    strncat(sub, "/src", 5);
    status = status || mkdir(sub, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    void (*function)(const char *restrict) = generateCfile;
    if(result & CPLUSPLUS) {
        function = generateCppFile;
    }

    if(result & MAKEFILE) {
        status = status || !generateMake(folder_name, function);
    } else
        status = status || !generateCmake(folder_name, function);

    return !status;
}

bool generateMake(const char* restrict folder_name, void (*generate_c)(const char *restrict c_file)) {
    unsigned flen = strlen(folder_name);
    char makefilename[flen + 10];
    memset(makefilename, 0, flen+10);
    strcat(makefilename, folder_name);
    strcat(makefilename, "/Makefile");

    FILE* make = fopen(makefilename, "w+");
    if(make == NULL) return false;

    fwrite(make_content, strlen(make_content), 1, make);
    generate_c(folder_name);

    fclose(make);
    return true;
}

bool generateCmake(const char* restrict foldername, void (*generate_c)(const char *restrict c_file)) {
    unsigned flen = strlen(foldername);
    char cmakefilename[flen + 16];
    memset(cmakefilename, 0, flen + 16);
    strcat(cmakefilename, foldername);
    strcat(cmakefilename, "/CMakeLists.txt");

    FILE* cmake = fopen(cmakefilename, "w+");

    if(cmake == NULL) return false;
    fwrite(cmake_content, strlen(cmake_content), 1, cmake);
    generate_c(foldername);

    fclose(cmake);
    return true;
}

void generateCfile(const char *restrict c_file) {
    unsigned len = strlen(c_file);
    char sub[len + 12];
    memset(sub, 0, 12);
    strcat(sub, c_file);
    strcat(sub, "/src/main.c");

    FILE* cfile = fopen(sub, "w+");
    if(!cfile) return;

    fwrite(c_content, strlen(c_content), 1, cfile);

    fclose(cfile);
}

void generateCppFile(const char *restrict cpp_file) {
    unsigned len = strlen(cpp_file);
    char sub[len + 14];
    memset(sub, 0, 14);
    strcat(sub, cpp_file);
    strcat(sub, "/src/main.cpp");

    FILE* cppfile = fopen(sub, "w+");
    if(!cppfile) return;

    fwrite(cpp_content, strlen(cpp_content), 1, cppfile);

    fclose(cppfile);
}
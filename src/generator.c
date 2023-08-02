#include "generator.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

const char* cmake_content = "cmake_minimum_required(VERSION 3.12)\n"
 "project(main)\nset(CMAKE_CXX_FLAGS \"-Wall -Wextra\")\n"
 "set(CMAKE_CXX_FLAGS_DEBUG \"-g -fsanitize=address\")\n"
 "set(CMAKE_CXX_FLAGS_RELEASE \"-O3\")\n"
 "file(GLOB SRC \"src/*.c\")\n"
 "add_executable(main ${SRC})\n";

bool generateCmake(const char* restrict);

bool generate(__attribute__((unused)) uint32_t result, const char* folder_name) {
    uint32_t folder_name_length = strlen(folder_name);
    int status = mkdir(folder_name, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    char sub[folder_name_length + 6];
    memset(sub, 0, folder_name_length + 6);
    strncat(sub, folder_name, folder_name_length);
    strncat(sub, "/src", 5);
    status = status || mkdir(sub, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    status = status || !generateCmake(folder_name);

    if(!status) {
        return true;
    }

    return false;
}

bool generateCmake(const char* restrict foldername) {
    char cmakefilename[strlen(foldername) + 16];
    memset(cmakefilename, 0, strlen(foldername) + 16);
    strcat(cmakefilename, foldername);
    strcat(cmakefilename, "/CMakeLists.txt");

    FILE* cmake = fopen(cmakefilename, "w+");
    
    if(cmake == NULL) return false;
    fwrite(cmake_content, strlen(cmake_content), 1, cmake);

    fclose(cmake);
    return true;
}
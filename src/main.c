#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "converter.h"

#define MAX_PATH_LENGTH 256

void print_usage(const char* prog_name) {
    printf("Usage: %s [-atob | -btoa] -png <png_path> -rawi <rawi_path>\n", prog_name);
    printf("  -atob  Convert rawi to PNG\n");
    printf("  -btoa  Convert PNG to rawi\n");
    printf("  -png   Path to the PNG file\n");
    printf("  -rawi  Path to the rawi file\n");
}

int main(int argc, char* argv[]) {
    fprintf(stderr, argv);
    int convert_rawi_to_png = 0;
    int convert_png_to_rawi = 0;
    char png_path[MAX_PATH_LENGTH] = {0};
    char rawi_path[MAX_PATH_LENGTH] = {0};

    for (int i = 1; i < argc; i++) {
        printf("Argument %d: %s\n", i, argv[i]);  // Debugging output
        if (strcmp(argv[i], "-atob") == 0) {
            convert_rawi_to_png = 1;
        } else if (strcmp(argv[i], "-btoa") == 0) {
            convert_png_to_rawi = 1;
        } else if (strcmp(argv[i], "-png") == 0) {
            if (i + 1 < argc) {
                strncpy(png_path, argv[++i], MAX_PATH_LENGTH - 1);
            } else {
                fprintf(stderr, "Error: Missing PNG path\n");
                return EXIT_FAILURE;
            }
        } else if (strcmp(argv[i], "-rawi") == 0) {
            if (i + 1 < argc) {
                strncpy(rawi_path, argv[++i], MAX_PATH_LENGTH - 1);
            } else {
                fprintf(stderr, "Error: Missing rawi path\n");
                return EXIT_FAILURE;
            }
        } else {
            print_usage(argv[0]);
            return EXIT_FAILURE;
        }
    }

    if (convert_rawi_to_png) {
        if (strlen(rawi_path) == 0 || strlen(png_path) == 0) {
            fprintf(stderr, "Error: Both rawi and PNG paths must be specified for -atob\n");
            return EXIT_FAILURE;
        }
        return convertRawiToPng(rawi_path, png_path) ? EXIT_SUCCESS : EXIT_FAILURE;
    }

    if (convert_png_to_rawi) {
        if (strlen(png_path) == 0 || strlen(rawi_path) == 0) {
            fprintf(stderr, "Error: Both PNG and rawi paths must be specified for -btoa\n");
            return EXIT_FAILURE;
        }
        return convertPngToRawi(png_path, rawi_path) ? EXIT_SUCCESS : EXIT_FAILURE;
    }

    print_usage(argv[0]);
    return EXIT_FAILURE;
}

#ifndef CONVERTER_H
#define CONVERTER_H
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "reader.h"

// Function to convert a rawi image to PNG
int convertRawiToPng(const char* rawiFilename, const char* pngFilename);

// Function to convert a PNG image to rawi
int convertPngToRawi(const char* pngFilename, const char* rawiFilename);

#endif // CONVERTER_H

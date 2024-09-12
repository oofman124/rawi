#ifndef READER_H
#define READER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int width;
    int height;
    unsigned char* pixelData;
} RawiImage;

// Function to load a `rawi` image from file
RawiImage* loadRawiImage(const char* filename);

// Function to save a `rawi` image to file
int saveRawiImage(const char* filename, RawiImage* image);

// Function to create a new RawiImage with pixel data
RawiImage* createRawiImage(int width, int height, unsigned char* pixelData);

// Function to free memory associated with RawiImage
void freeRawiImage(RawiImage* image);

// Function to print image info
void printImageInfo(RawiImage* image);

#endif // READER_H

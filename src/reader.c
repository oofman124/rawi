#include "reader.h"

// Function to load a `rawi` image from file
RawiImage* loadRawiImage(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    // Check the magic number "rawi"
    char magic[5];
    fread(magic, 1, 4, file);
    magic[4] = '\0';  // Null-terminate

    if (strcmp(magic, "rawi") != 0) {
        fprintf(stderr, "Invalid file format. Expected 'rawi' header.\n");
        fclose(file);
        return NULL;
    }

    // Read width and height
    int width, height;
    fread(&width, sizeof(int), 1, file);
    fread(&height, sizeof(int), 1, file);

    // Allocate memory for pixel data (RGB, 3 bytes per pixel)
    size_t dataSize = width * height * 3;
    unsigned char* pixelData = (unsigned char*)malloc(dataSize);
    if (!pixelData) {
        perror("Error allocating memory for pixel data");
        fclose(file);
        return NULL;
    }

    // Read pixel data
    fread(pixelData, 1, dataSize, file);
    fclose(file);

    // Create the image structure
    RawiImage* image = (RawiImage*)malloc(sizeof(RawiImage));
    if (!image) {
        perror("Error allocating memory for image structure");
        free(pixelData);
        return NULL;
    }
    image->width = width;
    image->height = height;
    image->pixelData = pixelData;

    return image;
}

// Function to save a `rawi` image to file
int saveRawiImage(const char* filename, RawiImage* image) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        perror("Error opening file for writing");
        return 0;
    }

    // Write the "rawi" header
    fwrite("rawi", 1, 4, file);

    // Write width and height
    fwrite(&image->width, sizeof(int), 1, file);
    fwrite(&image->height, sizeof(int), 1, file);

    // Write pixel data
    size_t dataSize = image->width * image->height * 3;
    fwrite(image->pixelData, 1, dataSize, file);
    fclose(file);

    return 1;
}

// Function to create a new RawiImage
RawiImage* createRawiImage(int width, int height, unsigned char* pixelData) {
    RawiImage* image = (RawiImage*)malloc(sizeof(RawiImage));
    if (!image) {
        perror("Error allocating memory for image structure");
        return NULL;
    }
    image->width = width;
    image->height = height;

    size_t dataSize = width * height * 3;
    image->pixelData = (unsigned char*)malloc(dataSize);
    if (!image->pixelData) {
        perror("Error allocating memory for pixel data");
        free(image);
        return NULL;
    }

    memcpy(image->pixelData, pixelData, dataSize);
    return image;
}

// Function to free memory associated with RawiImage
void freeRawiImage(RawiImage* image) {
    if (image) {
        free(image->pixelData);
        free(image);
    }
}

// Function to print image info
void printImageInfo(RawiImage* image) {
    if (!image) return;
    printf("Width: %d, Height: %d\n", image->width, image->height);
}

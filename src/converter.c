#include "converter.h"
#include "stb_image.h"
#include "stb_image_write.h"
#include <stdio.h>
#include <stdlib.h>

// Function to convert rawi to PNG
int convertRawiToPng(const char* rawiFilename, const char* pngFilename) {
    RawiImage* rawiImage = loadRawiImage(rawiFilename);
    if (!rawiImage) {
        fprintf(stderr, "Failed to load rawi image.\n");
        return 0;
    }

    // Use stb_image_write to save as PNG
    int success = stbi_write_png(pngFilename, rawiImage->width, rawiImage->height, 3, rawiImage->pixelData, rawiImage->width * 3);
    if (!success) {
        fprintf(stderr, "Failed to write PNG file: %s\n", pngFilename);
        freeRawiImage(rawiImage);
        return 0;
    }

    printf("Converted %s to %s\n", rawiFilename, pngFilename);
    freeRawiImage(rawiImage);
    return 1;
}

// Function to convert PNG to rawi
int convertPngToRawi(const char* pngFilename, const char* rawiFilename) {
    int width, height, channels;
    unsigned char* imageData = stbi_load(pngFilename, &width, &height, &channels, 3);  // Force 3 channels (RGB)
    if (!imageData) {
        fprintf(stderr, "Failed to load PNG file: %s\n", pngFilename);
        return 0;
    }

    RawiImage* rawiImage = createRawiImage(width, height, imageData);
    if (!rawiImage) {
        fprintf(stderr, "Failed to create rawi image.\n");
        stbi_image_free(imageData);
        return 0;
    }

    if (!saveRawiImage(rawiFilename, rawiImage)) {
        fprintf(stderr, "Failed to save rawi image: %s\n", rawiFilename);
        freeRawiImage(rawiImage);
        stbi_image_free(imageData);
        return 0;
    }

    printf("Converted %s to %s\n", pngFilename, rawiFilename);
    freeRawiImage(rawiImage);
    stbi_image_free(imageData);
    return 1;
}

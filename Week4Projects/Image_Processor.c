#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Ensure structure packing (no padding between struct members)
#pragma pack(push, 1)

// BMP File Header (14 bytes)
typedef struct {
    uint16_t type;        // File type: should be 0x4D42 for BMP
    uint32_t size;        // File size in bytes
    uint16_t reserved1;   // Reserved (must be 0)
    uint16_t reserved2;   // Reserved (must be 0)
    uint32_t offset;      // Offset to start of pixel data
} BMPHeader;

// DIB Header (BITMAPINFOHEADER - 40 bytes) 



typedef struct {
    uint32_t size;             // DIB header size
    int32_t  width;            // Image width
    int32_t  height;           // Image height
    uint16_t planes;           // Color planes (must be 1)
    uint16_t bitsPerPixel;     // Bits per pixel (24 for RGB)
    uint32_t compression;      // Compression type (0 = none)
    uint32_t imageSize;        // Image size (can be 0 for uncompressed)
    int32_t  xPixelsPerM;      // Horizontal resolution
    int32_t  yPixelsPerM;      // Vertical resolution
    uint32_t colorsUsed;       // Number of colors in palette (0 = default)
    uint32_t importantColors;  // Important colors (0 = all)
} DIBHeader;

// RGB pixel structure (3 bytes per pixel)
typedef struct {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
} RGBPixel;

#pragma pack(pop)

// Image processing functions
void grayscale(RGBPixel *pixels, int width, int height);
void invert(RGBPixel *pixels, int width, int height);
void mirror_horizontal(RGBPixel *pixels, int width, int height);
void mirror_vertical(RGBPixel *pixels, int width, int height);

int main() {
    char input_filename[] = "input.bmp";
    char output_filename[] = "output.bmp";

    // Open BMP file for reading
    FILE *input = fopen(input_filename, "rb");
    if (!input) {
        printf("Could not open %s\n", input_filename);
        return 1;
    }

    // Read headers
    BMPHeader bmp;
    DIBHeader dib;
    fread(&bmp, sizeof(BMPHeader), 1, input);
    fread(&dib, sizeof(DIBHeader), 1, input);

    // Validate file
    if (bmp.type != 0x4D42 || dib.bitsPerPixel != 24) {
        printf("Only 24-bit BMP files are supported.\n");
        fclose(input);
        return 1;
    }

    int width = dib.width;
    int height = dib.height;
    int padding = (4 - (width * sizeof(RGBPixel)) % 4) % 4;

    // Allocate memory for pixel data
    RGBPixel *pixels = malloc(width * height * sizeof(RGBPixel));
    if (!pixels) {
        printf("Memory allocation failed.\n");
        fclose(input);
        return 1;
    }

    // Read pixel data (BMP stores pixels from bottom to top)
    for (int i = height - 1; i >= 0; i--) {
        fread(&pixels[i * width], sizeof(RGBPixel), width, input);
        fseek(input, padding, SEEK_CUR);  // Skip padding
    }

    fclose(input);

    // Ask user for image effect
    printf("Choose image effect:\n");
    printf("1. Grayscale\n");
    printf("2. Invert Colors\n");
    printf("3. Mirror Horizontally\n");
    printf("4. Mirror Vertically\n");
    printf("Enter your choice (1-4): ");
    int choice;
    scanf("%d", &choice);

    // Apply selected effect
    switch (choice) {
        case 1: grayscale(pixels, width, height); break;
        case 2: invert(pixels, width, height); break;
        case 3: mirror_horizontal(pixels, width, height); break;
        case 4: mirror_vertical(pixels, width, height); break;
        default:
            printf("Invalid choice.\n");
            free(pixels);
            return 1;
    }

    // Write processed image to output file
    FILE *output = fopen(output_filename, "wb");
    if (!output) {
        printf("Could not create output file.\n");
        free(pixels);
        return 1;
    }

    // Write headers
    fwrite(&bmp, sizeof(BMPHeader), 1, output);
    fwrite(&dib, sizeof(DIBHeader), 1, output);

    // Write pixel data with padding
    for (int i = height - 1; i >= 0; i--) {
        fwrite(&pixels[i * width], sizeof(RGBPixel), width, output);
        for (int p = 0; p < padding; p++)
            fputc(0x00, output);  // Add padding byte
    }

    fclose(output);
    free(pixels);

    printf("Image processed and saved as %s\n", output_filename);
    return 0;
}

// 🟦 Grayscale conversion
void grayscale(RGBPixel *pixels, int width, int height) {
    for (int i = 0; i < width * height; i++) {
        uint8_t avg = (pixels[i].red + pixels[i].green + pixels[i].blue) / 3;
        pixels[i].red = pixels[i].green = pixels[i].blue = avg;
    }
}

// 🟥 Invert colors
void invert(RGBPixel *pixels, int width, int height) {
    for (int i = 0; i < width * height; i++) {
        pixels[i].red   = 255 - pixels[i].red;
        pixels[i].green = 255 - pixels[i].green;
        pixels[i].blue  = 255 - pixels[i].blue;
    }
}

// 🟩 Mirror horizontally (left-right)
void mirror_horizontal(RGBPixel *pixels, int width, int height) {
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width / 2; col++) {
            int left = row * width + col;
            int right = row * width + (width - col - 1);
            RGBPixel temp = pixels[left];
            pixels[left] = pixels[right];
            pixels[right] = temp;
        }
    }
}

// 🟨 Mirror vertically (top-bottom)
void mirror_vertical(RGBPixel *pixels, int width, int height) {
    for (int row = 0; row < height / 2; row++) {
        for (int col = 0; col < width; col++) {
            int top = row * width + col;
            int bottom = (height - row - 1) * width + col;
            RGBPixel temp = pixels[top];
            pixels[top] = pixels[bottom];
            pixels[bottom] = temp;
        }
    }
}

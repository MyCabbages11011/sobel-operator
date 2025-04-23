#include "bmp.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]);

void sobel_operator(int height, int width, RGBTRIPLE image[height][width]);

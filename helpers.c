#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float red = image[i][j].rgbtRed;
            float green = image[i][j].rgbtGreen;
            float blue = image[i][j].rgbtBlue;

            int rgb_avg = round((red + green + blue) / 3);

            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = rgb_avg;
        }
    }
    return;
}

void sobel_operator(int height, int width, RGBTRIPLE image[height][width])
{ 
    int kernel_x[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    int kernel_y[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};
    
    int max = 255;
    int min = 0;


    RGBTRIPLE (*copy)[width] = calloc(height, sizeof(*copy));
    if (copy == NULL){
        printf("not enought mem for sobel");
        return;
    } 

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++){

            copy[i][j] = image[i][j];
        }
    }

    for (int i = 1; i < height - 1; i++) {
        for (int j = 1; j < width - 1; j++){

            float g_x = 0.0; 
            float g_y = 0.0;

            for (int h_grid = -1; h_grid <= 1; h_grid++){
                for (int w_grid = -1; w_grid <= 1; w_grid++) {
                    int surround_i = i + h_grid;
                    int surround_j = j + w_grid;

                    if (surround_i >= 0 && surround_i < height && surround_j >= 0 && surround_j < width) {
                        
                        BYTE intensity = copy[surround_i][surround_j].rgbtRed;

                        g_x += intensity * kernel_x[h_grid + 1][w_grid + 1];
                        g_y += intensity * kernel_y[h_grid + 1][w_grid + 1];
                    }
                }
            }

            int gradient = round(sqrt((g_x * g_x) + (g_y * g_y)));
            //printf("Pixel [%d][%d] magnitude: %d\n", i, j, gradient);

            
            if (gradient > 255) gradient = 255;
            else if (gradient <= 0) gradient = 0;

            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = gradient;

        }
    }
    return;
}

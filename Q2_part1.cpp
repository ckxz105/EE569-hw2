// EE569 Homework Assignment #2
// Date: 2018.2.10
// Name: Jun Liu
// ID  : 4871562115
// email:liu494@usc.edu

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>  // use max and min algorithm
#include <cmath> // use for pow function
#include <sstream>
#include <string>
using namespace std;

// the function the check wheter the position of the image should contains values or not

int main(int argc, char *argv[])

{
    // Define file pointer and variables
    FILE * file1, *file;
    int BytesPerPixel = 1, Size1 = 512, Size2 = 512, byteRange = 256;
    
    // Allocate image data array
    unsigned char Imagedata_org[Size1][Size2][BytesPerPixel];
    unsigned char result_part1[Size1][Size2][BytesPerPixel];
    unsigned char result_part2[Size1][Size2][BytesPerPixel];
    unsigned char result_part3_1[Size1][Size2][BytesPerPixel];
    unsigned char result_part3_2[Size1][Size2][BytesPerPixel];
    unsigned char result_part3_3[Size1][Size2][BytesPerPixel];
    unsigned char result_part3_4[Size1][Size2][BytesPerPixel];
    double Threshold_M2[2][2];
    double Threshold_M4[4][4];
    double Threshold_M8[8][8];
    Threshold_M2[0][0] = 1;
    Threshold_M2[0][1] = 2;
    Threshold_M2[1][0] = 3;
    Threshold_M2[1][1] = 0;
    int startX, startY;
    // generate I4 matrix
    for (int i = 0;i < 4;i++)
    {
        if (i == 0)
        {
            startX = 2;
            startY = 2;
        }
        else if (i == 1)
        {
            startX = 0;
            startY = 0;
        }
        else if (i == 2)
        {
            startX = 0;
            startY = 2;
        }
        else
        {
            startX = 2;
            startY = 0;
        }
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                Threshold_M4[startX + j][startY + k] = 4 * Threshold_M2[j][k] + i;
            }
        }
    }
    // generate I8 matrix
    for (int i = 0;i < 4;i++)
    {
        if (i == 0)
        {
            startX = 4;
            startY = 4;
        }
        else if (i == 1)
        {
            startX = 0;
            startY = 0;
        }
        else if (i == 2)
        {
            startX = 0;
            startY = 4;
        }
        else
        {
            startX = 4;
            startY = 0;
        }
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                Threshold_M8[startX + j][startY + k] = 4 * Threshold_M4[j][k] + i;
            }
        }
    }
    // generate T2 matrix
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            Threshold_M2[i][j] = (Threshold_M2[i][j] + 0.5) / 2 / 2;
        }
    }
    // generate T4 matrix
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            Threshold_M4[i][j] = (Threshold_M4[i][j] + 0.5) / 4 / 4;
        }
    }
    // generate T8 matrix
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Threshold_M8[i][j] = (Threshold_M8[i][j] + 0.5) / 8 / 8;
            //cout << Threshold_M8[i][j] << "," ;
        }
        //cout << endl;
    }

    // Read image (filename specified by first argument) into image data matrix
    if (!(file1=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata_org, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file1);
    fclose(file1);

    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
    int threshld = 127;
    int temp, randNumber, XPosForT, YPosForT;
    double part3_temp;
    // the part to transform the original image to disk-shaped image
    for (int i = 0; i < Size1; i++) 
    {
        for (int j = 0; j < Size2; j++) 
        {
            for (int k = 0; k < BytesPerPixel; k++)
            {  
                // fixed thresholding
                temp = (int) Imagedata_org[i][j][k];
                if (temp < threshld)
                {
                    result_part1[i][j][k] = (char) 0;
                }
                else
                {
                    result_part1[i][j][k] = (char) 255;
                }

                // Random thresholding
                randNumber = rand() % 255;
                if (randNumber > temp)
                {
                    result_part2[i][j][k] = (char) 0;
                }
                else
                {
                    result_part2[i][j][k] = (char) 255;
                }

                // dithering matrix thresholding
                part3_temp = ((double) temp) / 255;
                // T2
                XPosForT = i % 2;
                YPosForT = j % 2;
                if (part3_temp > Threshold_M2[XPosForT][YPosForT])
                {
                    result_part3_1[i][j][k] = (char) 255;
                }
                else
                {
                    result_part3_1[i][j][k] = (char) 0;
                }

                // T4
                XPosForT = i % 4;
                YPosForT = j % 4;
                if (part3_temp > Threshold_M4[XPosForT][YPosForT])
                {
                    result_part3_2[i][j][k] = (char) 255;
                }
                else
                {
                    result_part3_2[i][j][k] = (char) 0;
                }

                // T8
                XPosForT = i % 8;
                YPosForT = j % 8;
                if (part3_temp > Threshold_M8[XPosForT][YPosForT])
                {
                    result_part3_3[i][j][k] = (char) 255;
                }
                else
                {
                    result_part3_3[i][j][k] = (char) 0;
                }
                // extra part
                if (part3_temp > Threshold_M8[XPosForT][YPosForT])
                {
                    result_part3_3[i][j][k] = (char) 255;
                }
                else
                {
                    result_part3_3[i][j][k] = (char) 0;
                }
            }
        }
    }



    // output the processed images
    char out1[] = "Q2_part1.raw", out2[] = "Q2_part2.raw", out3[] = "Q2_part3_Size = 2.raw", out4[] = "Q2_part3_Size = 4.raw", out5[] = "Q2_part3_Size = 8.raw",out6[] = "Q2_part3_4levels.raw";
    if (!(file = fopen(out1,"wb"))) 
    {
        cout << "Cannot open file1: " << out1 << endl;
        exit(1);
    }
    fwrite(result_part1, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);
    fclose(file);

    if (!(file = fopen(out2,"wb"))) 
    {
        cout << "Cannot open file1: " << out2 << endl;
        exit(1);
    }
    fwrite(result_part2, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);
    fclose(file);

    if (!(file = fopen(out3,"wb"))) 
    {
        cout << "Cannot open file1: " << out3 << endl;
        exit(1);
    }
    fwrite(result_part3_1, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);
    fclose(file);

    if (!(file = fopen(out4,"wb"))) 
    {
        cout << "Cannot open file1: " << out4 << endl;
        exit(1);
    }
    fwrite(result_part3_2, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);
    fclose(file);

    if (!(file = fopen(out5,"wb"))) 
    {
        cout << "Cannot open file1: " << out5 << endl;
        exit(1);
    }
    fwrite(result_part3_3, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);
    fclose(file);

    if (!(file = fopen(out6,"wb"))) 
    {
        cout << "Cannot open file1: " << out6 << endl;
        exit(1);
    }
    fwrite(result_part3_4, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);
    fclose(file);
    return 0;
}
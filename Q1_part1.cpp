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
const int Size1 = 512, Size2 = 512;
const int BytesPerPixel = 3;
// The function to calculate PSNR
// input1 and input2: the pointer of first pixel of image, example: image[0][0][0]
// input3: the pointer of the first position of PSNR array, exmpale: PSNR[0]
void PSNR_Calculate(unsigned char * image1,unsigned char * image2, double * PSNR_array)
{
    double PSNR = 0, MSE = 0, maxValue = 255;
    for (int k = 0; k < BytesPerPixel; k++)
    {
        PSNR = 0;
        MSE = 0;
        for (int i = 0; i < Size1; i++)
        {
            for (int j = 0; j < Size2; j++)
            {
                MSE += pow( ((int)(image1[(i * Size2 + j) * BytesPerPixel+ k])) - ((int)(image2[(i * Size2 + j) * BytesPerPixel+ k])), 2);
            }
        }
        MSE = MSE / Size1 / Size2;
        PSNR = 10 * log10(maxValue * maxValue / MSE);
        PSNR_array[k] = PSNR;
    }
}
// the function to transfer number to string
string num2str(double i)
{
    stringstream ss;
    ss<<i;
    return ss.str();
}
// the function the check wheter the position of the image should contains values or not
bool Check_Plottable(double midPosition, int i, int j, int size)
{
    float threshold = sqrt(pow((midPosition),2) + pow(0.5,2) ) / midPosition;
    float ratio = sqrt(pow(((double) i - midPosition),2) + pow(((double) j - midPosition),2) ) / midPosition;
    if (ratio > threshold)
    {
        return false;
    }
    else
    {
        return true;
    }
}
// calculate the ratio of the position (for getting the corresponding original pixel position of the result)
double Get_Ratio(double midPosition, int i, int j, int size)
{
    double xPos = (double) i - midPosition;
    double yPos = (double) j - midPosition;
    double ratio1 = yPos / xPos;
    double ratio2 = 0;
    double edgeXPos = 0, edgeYPos = 0;
    if (abs(ratio1) > 1)
    {
        if (yPos >= 0)
        {
            edgeYPos = midPosition;
            edgeXPos = midPosition / ratio1;
        }
        else 
        {
            edgeYPos = - midPosition;
            edgeXPos = - midPosition / ratio1;
        }
    }
    else
    {
        if (xPos >= 0)
        {
            edgeXPos = midPosition;
            edgeYPos = midPosition * ratio1;
        }
        else 
        {
            edgeXPos = - midPosition;
            edgeYPos = - midPosition * ratio1;
        }
    }
    ratio2 = sqrt(pow(edgeXPos,2) + pow(edgeYPos,2)) / midPosition;
    return ratio2;
}

int main(int argc, char *argv[])

{
    // Define file pointer and variables
    FILE * file1, *file;
    int BytesPerPixel = 3, Size1 = 512, Size2 = 512, byteRange = 256;
    
    // Allocate image data array
    unsigned char Imagedata_org[Size1][Size2][BytesPerPixel];
    unsigned char result_transformed[Size1][Size2][BytesPerPixel];
    unsigned char result_reversed[Size1][Size2][BytesPerPixel];
    // Read image (filename specified by first argument) into image data matrix
    if (!(file1=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata_org, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file1);
    fclose(file1);

    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
    bool check_plottable = false;
    double ratio = 0;
    double newXPos, newYPos, deltaX, deltaY, value_correspond;
    int newXpos_int, newYpos_int;
    double midPosition = (double (Size1) - 1) / 2;
    // the part to transform the original image to disk-shaped image
    for (int i = 0; i < Size1; i++) 
    {
        for (int j = 0; j < Size2; j++) 
        {
            check_plottable = Check_Plottable(midPosition, i, j, Size1);
            for (int k = 0; k < BytesPerPixel; k++)
            {
                // if the position of the pixel is out of the range of the image area, set as 0 for black
                if (!check_plottable)
                {
                    result_transformed[i][j][k] = (char) 0;
                }
                // otherwise we need to find the corresponding locaiton of the original image's pixel location
                else
                {
                    ratio = Get_Ratio(midPosition, i,j,Size1);
                    newXPos = ((double) i - midPosition) * ratio + midPosition;
                    newYPos = ((double) j - midPosition) * ratio + midPosition;
                    newXpos_int = floor(newXPos);
                    newYpos_int = floor(newYPos);
                    deltaX = newXPos - newXpos_int;
                    deltaY = newYPos - newYpos_int;
                    //cout << "ratio = " << ratio << " POS = " << i << "," << j << endl;
                    //cout << "pos: " << newXPos << "," << newYPos << endl;
                    value_correspond = (1 - deltaX) * (1 - deltaY) * (int (Imagedata_org[newXpos_int][newYpos_int][k])) + (deltaX) * (1 - deltaY) * (int (Imagedata_org[newXpos_int][newYpos_int + 1][k])) + (1 - deltaX) * (deltaY) * (int (Imagedata_org[newXpos_int + 1][newYpos_int][k])) + (deltaX) * (deltaY) * (int (Imagedata_org[newXpos_int + 1][newYpos_int + 1][k]));
                    result_transformed[i][j][k] = (char) (int (value_correspond));
                }
                
            }
        }
    }

    // the part to transform the disk-shaped image to normal image
    for (int i = 0; i < Size1; i++) 
    {
        for (int j = 0; j < Size2; j++) 
        {
            for (int k = 0; k < BytesPerPixel; k++)
            {
                ratio = Get_Ratio(midPosition, i,j,Size1);
                newXPos = ((double) i - midPosition) / ratio + midPosition;
                newYPos = ((double) j - midPosition) / ratio + midPosition;
                newXpos_int = floor(newXPos);
                newYpos_int = floor(newYPos);
                deltaX = newXPos - newXpos_int;
                deltaY = newYPos - newYpos_int;
                //cout << "ratio = " << ratio << " POS = " << i << "," << j << endl;
                //cout << "pos: " << newXPos << "," << newYPos << endl;
                value_correspond = (1 - deltaX) * (1 - deltaY) * (int (result_transformed[newXpos_int][newYpos_int][k])) + (deltaX) * (1 - deltaY) * (int (result_transformed[newXpos_int][newYpos_int + 1][k])) + (1 - deltaX) * (deltaY) * (int (result_transformed[newXpos_int + 1][newYpos_int][k])) + (deltaX) * (deltaY) * (int (result_transformed[newXpos_int + 1][newYpos_int + 1][k]));
                result_reversed[i][j][k] = (char) (int (value_correspond));
            }
        }
    }

    // calculate and display the PSNR results
    double PSNR_array[BytesPerPixel];
    PSNR_Calculate(&result_reversed[0][0][0],&Imagedata_org[0][0][0],PSNR_array);
    cout << "The PSNR between original and reversed results is: " << endl;
    cout << "R: " << PSNR_array[0] << endl;
    cout << "G: " << PSNR_array[1] << endl;
    cout << "B: " << PSNR_array[2] << endl;

    // output the processed images
    char out1[] = "Q1_output.raw", out2[] = "Q1_reversed.raw";
    if (!(file = fopen(out1,"wb"))) 
    {
        cout << "Cannot open file1: " << out1 << endl;
        exit(1);
    }
    fwrite(result_transformed, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);
    fclose(file);

    if (!(file = fopen(out2,"wb"))) 
    {
        cout << "Cannot open file1: " << out2 << endl;
        exit(1);
    }
    fwrite(result_reversed, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);
    fclose(file);
    return 0;
}
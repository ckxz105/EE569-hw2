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

const int BytesPerPixel = 1, Size1 = 512, Size2 = 512, byteRange = 256;

// Allocate image data array
unsigned char Imagedata_org[Size1][Size2][BytesPerPixel];
double Imagedata_part1[Size1][Size2][BytesPerPixel];
double Imagedata_part2[Size1][Size2][BytesPerPixel];
double Imagedata_part3[Size1][Size2][BytesPerPixel];

unsigned char result_part1[Size1][Size2][BytesPerPixel];
unsigned char result_part2[Size1][Size2][BytesPerPixel];
unsigned char result_part3[Size1][Size2][BytesPerPixel];

double H2[5][5] = {0,0,0,0,0,0,0,0,0,0,0,0,0,7.0/48,5.0/48,3.0/48,5.0/48,7.0/48,5.0/48,3.0/48,1.0/48,3.0/48,5.0/48,3.0/48,1.0/48};
double H3[5][5] = {0,0,0,0,0,0,0,0,0,0,0,0,0,8.0/42,4.0/42,2.0/42,4.0/42,8.0/42,4.0/42,2.0/42,1.0/42,2.0/42,4.0/42,2.0/42,1.0/42};

void addError(double error2, double error3, int i, int j, int posX, int posY)
{
    double newValue;
    for (int k = 0; k < BytesPerPixel; k++)
    {
        Imagedata_part2[posX+i][posY+j][k] = H2[2+i][2+j] * error2 + Imagedata_part2[posX+i][posY+j][k];
        Imagedata_part3[posX+i][posY+j][k] = H3[2+i][2+j] * error3 + Imagedata_part3[posX+i][posY+j][k];
    }
}

int main(int argc, char *argv[])

{
    // Define file pointer and variables
    FILE * file1, *file;



    // Read image (filename specified by first argument) into image data matrix
    if (!(file1=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata_org, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file1);
    fclose(file1);

    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
    double temp, temp2, temp3, newValue;
    double error, error2, error3, valDouble;
    bool isAtRightEdge, isAtBottom, isNearRightEdge, isNearBottom,isAtLeftEdge,isNearLeftEdge;



    for (int i = 0; i < Size1; i++) 
    {
        for (int j = 0; j < Size2; j++) 
        {
            for (int k = 0; k < BytesPerPixel; k++)
            {  
                valDouble = ((double)(int)Imagedata_org[i][j][k]) / 255;
                Imagedata_part1[i][j][k] = valDouble;
                Imagedata_part2[i][j][k] = valDouble;
                Imagedata_part3[i][j][k] = valDouble;
            }
        }
    }

    int remain;
    // the part to transform the original image to disk-shaped image
    for (int i = 0; i < Size1; i++) 
    {
        remain = i % 2;
        if (remain == 0)
        {
            for (int j = 0; j < Size2; j++) 
            {
                for (int k = 0; k < BytesPerPixel; k++)
                {  
                    // part 1
                    temp = Imagedata_part1[i][j][k];
                    if (temp > 0.5)
                    {
                        result_part1[i][j][k] = (char) 255;
                        error = temp - 1;
                    }
                    else
                    {
                        result_part1[i][j][k] = (char) 0;
                        error = temp;
                    }
                    if (j != (Size1 - 1))
                    {
                        Imagedata_part1[i][j+1][k] = error * 7 / 16 + Imagedata_part1[i][j+1][k];

                    }

                    if (i != (Size2 - 1))
                    {
                        Imagedata_part1[i+1][j][k] = error * 5 / 16 + Imagedata_part1[i+1][j][k];
                    }

                    if ((i != (Size2 - 1)) & (j != (Size1 - 1)))
                    {
                        Imagedata_part1[i+1][j+1][k] = error * 1 / 16 + Imagedata_part1[i+1][j+1][k];
                        
                    }


                    if ((i != (Size2 - 1)) & (j != 0))
                    {
                        Imagedata_part1[i+1][j-1][k] = error * 3 / 16 + Imagedata_part1[i+1][j-1][k];
                    }
                }
            }
        }
        else
        {
            for (int j = Size2 - 1; j >= 0 ; j--) 
            {
                for (int k = 0; k < BytesPerPixel; k++)
                {  
                    // part 1
                    temp = Imagedata_part1[i][j][k];
                    if (temp > 0.5)
                    {
                        result_part1[i][j][k] = (char) 255;
                        error = temp - 1;
                    }
                    else
                    {
                        result_part1[i][j][k] = (char) 0;
                        error = temp;
                    }
                    if (j != 0)
                    {
                        Imagedata_part1[i][j-1][k] = error * 7 / 16 + Imagedata_part1[i][j-1][k];

                    }

                    if (i != (Size1 - 1))
                    {
                        Imagedata_part1[i+1][j][k] = error * 5 / 16 + Imagedata_part1[i+1][j][k];
                    }

                    if ((i != (Size1 - 1)) & (j != 0))
                    {
                        Imagedata_part1[i+1][j-1][k] = error * 1 / 16 + Imagedata_part1[i+1][j-1][k];
                        
                    }


                    if ((i != (Size1 - 1)) & (j != (Size2 - 1)))
                    {
                        Imagedata_part1[i+1][j+1][k] = error * 3 / 16 + Imagedata_part1[i+1][j+1][k];
                    }
                }
            }
        }
    }

    for (int i = 0; i < Size1; i++) 
    {
        for (int j = 0; j < Size2; j++) 
        {
            for (int k = 0; k < BytesPerPixel; k++)
            {  
                // part 2 and 3
                // part 2's error
                temp2 = Imagedata_part2[i][j][k];
                if (temp2 > 0.5)
                {
                    result_part2[i][j][k] = (char) 255;
                    error2 = temp2 - 1;
                }
                else
                {
                    result_part2[i][j][k] = (char) 0;
                    error2 = temp2;
                }
                // part 3's error
                temp3 = Imagedata_part3[i][j][k];
                if (temp3 > 0.5)
                {
                    result_part3[i][j][k] = (char) 255;
                    error3 = temp3 - 1;
                }
                else
                {
                    result_part3[i][j][k] = (char) 0;
                    error3 = temp3;
                }
                isAtBottom = (i == (Size1 - 1));
                isNearBottom = (i == (Size1 - 2));
                isAtRightEdge = (j == (Size2 - 1));
                isNearRightEdge = (j == (Size2 - 2));
                isAtLeftEdge = (j == 0);
                isNearLeftEdge = (j == 1);

                if (isAtBottom)
                {
                    if (isAtRightEdge)
                    {
                        continue;
                    }
                    else if (isNearRightEdge)
                    {
                        addError(error2,error3,0,1,i,j);
                    }
                    else
                    {
                        addError(error2,error3,0,1,i,j);
                        addError(error2,error3,0,2,i,j);
                    }
                }
                else if (isNearBottom)
                {
                    if (isAtRightEdge)
                    {
                        addError(error2,error3,1,0,i,j);
                        addError(error2,error3,1,-1,i,j);
                        addError(error2,error3,1,-2,i,j);
                    }
                    else if (isNearRightEdge)
                    {
                        addError(error2,error3,1,0,i,j);
                        addError(error2,error3,1,-1,i,j);
                        addError(error2,error3,1,-2,i,j);
                        addError(error2,error3,1,1,i,j);
                        addError(error2,error3,0,1,i,j);
                    }
                    else if (isAtLeftEdge)
                    {
                        addError(error2,error3,1,0,i,j);
                        addError(error2,error3,1,1,i,j);
                        addError(error2,error3,1,2,i,j);
                        addError(error2,error3,0,1,i,j);
                        addError(error2,error3,0,2,i,j);
                    }
                    else if (isNearLeftEdge)
                    {
                        addError(error2,error3,1,-1,i,j);
                        addError(error2,error3,1,0,i,j);
                        addError(error2,error3,1,1,i,j);
                        addError(error2,error3,1,2,i,j);
                        addError(error2,error3,0,1,i,j);
                        addError(error2,error3,0,2,i,j);

                    }
                    else
                    {
                        addError(error2,error3,1,-2,i,j);
                        addError(error2,error3,1,-1,i,j);
                        addError(error2,error3,1,0,i,j);
                        addError(error2,error3,1,1,i,j);
                        addError(error2,error3,1,2,i,j);
                        addError(error2,error3,0,1,i,j);
                        addError(error2,error3,0,2,i,j);
                    }
                }
                else
                {
                    if (isAtRightEdge)
                    {
                        addError(error2,error3,1,-2,i,j);
                        addError(error2,error3,1,-1,i,j);
                        addError(error2,error3,1,0,i,j);
                        addError(error2,error3,2,-2,i,j);
                        addError(error2,error3,2,-1,i,j);
                        addError(error2,error3,2,0,i,j);
                    }
                    else if (isNearRightEdge)
                    {
                        addError(error2,error3,0,1,i,j);
                        addError(error2,error3,1,-2,i,j);
                        addError(error2,error3,1,-1,i,j);
                        addError(error2,error3,1,0,i,j);
                        addError(error2,error3,1,1,i,j);
                        addError(error2,error3,2,-2,i,j);
                        addError(error2,error3,2,-1,i,j);
                        addError(error2,error3,2,0,i,j);
                        addError(error2,error3,2,0,i,j);
                    }
                    else if (isAtLeftEdge)
                    {
                        addError(error2,error3,2,0,i,j);
                        addError(error2,error3,2,1,i,j);
                        addError(error2,error3,2,2,i,j);
                        addError(error2,error3,1,0,i,j);
                        addError(error2,error3,1,1,i,j);
                        addError(error2,error3,1,2,i,j);
                        addError(error2,error3,0,1,i,j);
                        addError(error2,error3,0,2,i,j);
                    }
                    else if (isNearLeftEdge)
                    {
                        addError(error2,error3,2,-1,i,j);
                        addError(error2,error3,2,0,i,j);
                        addError(error2,error3,2,1,i,j);
                        addError(error2,error3,2,2,i,j);
                        addError(error2,error3,1,-1,i,j);
                        addError(error2,error3,1,0,i,j);
                        addError(error2,error3,1,1,i,j);
                        addError(error2,error3,1,2,i,j);
                        addError(error2,error3,0,1,i,j);
                        addError(error2,error3,0,2,i,j);

                    }
                    else
                    {
                        addError(error2,error3,2,-2,i,j);
                        addError(error2,error3,2,-1,i,j);
                        addError(error2,error3,2,0,i,j);
                        addError(error2,error3,2,1,i,j);
                        addError(error2,error3,2,2,i,j);
                        addError(error2,error3,1,-2,i,j);
                        addError(error2,error3,1,-1,i,j);
                        addError(error2,error3,1,0,i,j);
                        addError(error2,error3,1,1,i,j);
                        addError(error2,error3,1,2,i,j);
                        addError(error2,error3,0,1,i,j);
                        addError(error2,error3,0,2,i,j);
                    }
                }

            }
        }
    }



    // output the processed images
    char out1[] = "Q2_2_part1.raw", out2[] = "Q2_2_part2.raw", out3[] = "Q2_2_part3.raw"
    ;
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
    fwrite(result_part3, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);
    fclose(file);

    return 0;
}
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

const int BytesPerPixel = 3, Size1 = 700, Size2 = 700, byteRange = 256;

// Allocate image data array
unsigned char Imagedata_org[Size1][Size2][BytesPerPixel];
double Imagedata_part1[Size1][Size2][BytesPerPixel];
double Imagedata_RGB[Size1][Size2][BytesPerPixel];
double Imagedata_CMY[Size1][Size2][BytesPerPixel];

unsigned char result_part1[Size1][Size2][BytesPerPixel];
unsigned char result_part2[Size1][Size2][BytesPerPixel];
unsigned char result_part3[Size1][Size2][BytesPerPixel];
unsigned char result_part4[Size1][Size2][BytesPerPixel];


void getVal(int i, int j, double *error, int *count)
{
    int p[12] ,idx = 0, minIndex = 0;
    double R = Imagedata_RGB[i][j][0];
    double G = Imagedata_RGB[i][j][1];
    double B = Imagedata_RGB[i][j][2];
    double C = Imagedata_CMY[i][j][0];
    double M = Imagedata_CMY[i][j][1];
    double Y = Imagedata_CMY[i][j][2];
    string choice;
    double d[4], minDist = 10.0;
    

    //cout << "RGB color is" << R << "," << G << "," << B << endl;

    
    // find which 4 vertices should be applied
    if ((R + G) > 1.0)
    {
        if ((G + B) > 1.0)
        {
            if ((R+G+B) > 2.0)
            {
                choice = "CMYW";
                count[0]++;
            }
            else
            {
                choice = "MYGC";
                count[1]++;
            }
        }
        else
        {
            choice = "RGMY";
            count[2]++;
        }
    }
    else if (!((G+B) > 1.0))
    {
        if (!((R+G+B)> 1.0))
        {
            choice = "KRGB";
            count[3]++;
        }
        else
        {
            choice = "RGBM";
            count[4]++;
        }
    }
    else
    {
        choice = "CMGB";
        count[5]++;
    }

    // set the 4 vertices
    if (!(choice.find("W") == string::npos))
    {
        p[idx] = 0;
        p[idx + 1] = 0;
        p[idx + 2] = 0;
        idx = idx + 3;
    }
    if (!(choice.find("C") == string::npos))
    {
        p[idx] = 1;
        p[idx + 1] = 0;
        p[idx + 2] = 0;
        idx = idx + 3;
    }
    if (!(choice.find("M") == string::npos))
    {
        p[idx] = 0;
        p[idx + 1] = 1;
        p[idx + 2] = 0;
        idx = idx + 3;
    }
    if (!(choice.find("Y") == string::npos))
    {
        p[idx] = 0;
        p[idx + 1] = 0;
        p[idx + 2] = 1;
        idx = idx + 3;
    }
    if (!(choice.find("R") == string::npos))
    {
        p[idx] = 0;
        p[idx + 1] = 1;
        p[idx + 2] = 1;
        idx = idx + 3;
    }
    if (!(choice.find("G") == string::npos))
    {
        p[idx] = 1;
        p[idx + 1] = 0;
        p[idx + 2] = 1;
        idx = idx + 3;
    }
    if (!(choice.find("B") == string::npos))
    {
        p[idx] = 1;
        p[idx + 1] = 1;
        p[idx + 2] = 0;
        idx = idx + 3;
    }


    if (!(choice.find("K") == string::npos))
    {
        p[idx] = 1;
        p[idx + 1] = 1;
        p[idx + 2] = 1;
        idx = idx + 3;
    }

   
    for (int i = 0; i < 4; i++)
    {
        d[i] = sqrt(pow((C - p[3*i]),2) + pow((M - p[3*i+1]),2) + pow((Y - p[3*i+2]),2));
        //cout << "dist" << i << " = " << d[i] << endl;
        if (minDist > d[i])
        {
            minDist = d[i];
            minIndex = i;
        }
    }
    //cout << "Final choice:" << minIndex << endl;
    //cout << "min index: " << minIndex << endl;
    //cout << p[minIndex*3] * 255 << "," << p[minIndex*3+1] * 255 <<"," << p[minIndex*3+2] * 255 << endl;
    result_part3[i][j][0] = (char) ((int)(p[minIndex*3] * 255));
    result_part3[i][j][1] = (char) ((int)(p[minIndex*3+1] * 255));
    result_part3[i][j][2] = (char) ((int)(p[minIndex*3+2] * 255));
    error[0] = C - p[minIndex*3];
    error[1] = M - p[minIndex*3+1];
    error[2] = Y - p[minIndex*3+2];
    //cout << "error: " << error[0] << "," << error[1] <<"," <<error[2] << endl;
    //addError(&diff[0],i,j);

}

int main(int argc, char *argv[])

{
    // Define file pointer and variables
    FILE * file1, *file;
int count[6];
for (int i = 0;i< 6;i++)
{
    count[i] = 0;
}

    // Read image (filename specified by first argument) into image data matrix
    if (!(file1=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata_org, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file1);
    fclose(file1);

    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
    double temp, temp2, temp3, newValue;
    double error, error2, error3, valDouble, error_arr[3];
    bool isAtRightEdge, isAtBottom, isNearRightEdge, isNearBottom,isAtLeftEdge,isNearLeftEdge;
    int R,G,B;


    for (int i = 0; i < Size1; i++) 
    {
        for (int j = 0; j < Size2; j++) 
        {
            for (int k = 0; k < BytesPerPixel; k++)
            {  
                valDouble = ((double) ((int)Imagedata_org[i][j][k])) / 255.0;
                Imagedata_part1[i][j][k] = valDouble;
                Imagedata_RGB[i][j][k] = valDouble;
                Imagedata_CMY[i][j][k] = 1 - valDouble;
            }
        }
    }

    string Y;
    // the part to transform the original image to disk-shaped image
    for (int i = 0; i < Size1; i++) 
    {
        for (int j = 0; j < Size2; j++) 
        {
            getVal(i, j, &error_arr[0],&count[0]);
            //cout << "error: " << error_arr[0] << "," << error_arr[1] <<"," <<error_arr[2] << endl;
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

                //cout << "error = " << error_arr[k] << endl;
                if (j != (Size1 - 1))
                {
                    Imagedata_part1[i][j+1][k] = error * 7 / 16 + Imagedata_part1[i][j+1][k];
                    //cout << "org: " << Imagedata_part3[i][j+1][k];
                    Imagedata_CMY[i][j+1][k] = error_arr[k] * 7 / 16 + Imagedata_CMY[i][j+1][k];
                    //cout << " after: " << Imagedata_part3[i][j+1][k] << endl;
                }

                if (i != (Size2 - 1))
                {
                    Imagedata_part1[i+1][j][k] = error * 5 / 16 + Imagedata_part1[i+1][j][k];
                    Imagedata_CMY[i+1][j][k] = error_arr[k] * 5 / 16 + Imagedata_CMY[i+1][j][k];
                }

                if ((i != (Size2 - 1)) & (j != (Size1 - 1)))
                {
                    Imagedata_part1[i+1][j+1][k] = error * 1 / 16 + Imagedata_part1[i+1][j+1][k];
                    Imagedata_CMY[i+1][j+1][k] = error_arr[k] * 1 / 16 + Imagedata_CMY[i+1][j+1][k];
                    
                }


                if ((i != (Size2 - 1)) & (j != 0))
                {
                    Imagedata_part1[i+1][j-1][k] = error * 3 / 16 + Imagedata_part1[i+1][j-1][k];
                    Imagedata_CMY[i+1][j-1][k] = error_arr[k]* 3 / 16 + Imagedata_CMY[i+1][j-1][k];
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
                result_part2[i][j][k] = (char) (255 - result_part1[i][j][k]);
                result_part4[i][j][k] = (char) (255 - result_part3[i][j][k]);
            }
        }
    }

    // output the processed images
    char out1[] = "Q2_3_part1.raw", out2[] = "Q2_3_part2.raw", out3[] = "Q2_3_part3.raw"
    , out4[] = "Q2_3_part4.raw";
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

    if (!(file = fopen(out4,"wb"))) 
    {
        cout << "Cannot open file1: " << out4 << endl;
        exit(1);
    }
    fwrite(result_part4, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);
    fclose(file);

    return 0;
}
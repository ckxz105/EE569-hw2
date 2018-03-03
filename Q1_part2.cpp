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
const int Size1 = 640, Size2 = 480;
const int BytesPerPixel = 3;
const int N = 8;
const int enlargedSize = 250;
unsigned char result_LM[Size1 + 2 * enlargedSize][Size2 * 3 + 2 * enlargedSize][BytesPerPixel];
double det(double matrix[N][N],int size)
{
    // if the size of the target is only 1, return the value directly
    if(size == 1)
    {
        return matrix[0][0];
    }
    double result = 0;
    double temp[N][N]={0.0};
    int i,j,k;
    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size - 1; j++)
        {
            for(k = 0; k < size - 1 ; k++)
            {
                temp[j][k] = matrix[j+1][(k>=i) ? k+1 : k];
                
            }
        }
        // use traverse to find the lower level's determine
        double t = det(temp,size - 1);
        if(i % 2 == 0)
        {
            result += matrix[0][i]*t;
        }
        else
        {
            result -=  matrix[0][i]*t;
        }
    }
    return result;
}


void getHMatrix(int x[4],int y[4], int X[4], int Y[4], double H_matrix[8])
{
    double D[8][8] = {x[0],y[0],1,0,0,0,-x[0]*X[0],-y[0]*X[0],x[1],y[1],1,0,0,0,-x[1]*X[1],-y[1]*X[1],x[2],y[2],1,0,0,0,-x[2]*X[2],-y[2]*X[2],x[3],y[3],1,0,0,0,-x[3]*X[3],-y[3]*X[3],0,0,0,x[0],y[0],1,-x[0]*Y[0],-y[0]*Y[0],0,0,0,x[1],y[1],1,-x[1]*Y[1],-y[1]*Y[1],0,0,0,x[2],y[2],1,-x[2]*Y[2],-y[2]*Y[2],0,0,0,x[3],y[3],1,-x[3]*Y[3],-y[3]*Y[3]};

    double D1[8][8],D2[8][8],D3[8][8],D4[8][8],D5[8][8],D6[8][8],D7[8][8],D8[8][8];

    int target;

    target = 0;
    for (int j = 0; j < 8; j++)
    {
        if (j == target)
        {
            D1[0][j] = X[0];
            D1[1][j] = X[1];
            D1[2][j] = X[2];
            D1[3][j] = X[3];
            D1[4][j] = Y[0];
            D1[5][j] = Y[1];
            D1[6][j] = Y[2];
            D1[7][j] = Y[3];

        }
        else
        {
            for (int i = 0; i < 8; i++)
            {
                D1[i][j] = D[i][j];
            }
        }
    }


    target = 1;
    for (int j = 0; j < 8; j++)
    {
        if (j == target)
        {
            D2[0][j] = X[0];
            D2[1][j] = X[1];
            D2[2][j] = X[2];
            D2[3][j] = X[3];
            D2[4][j] = Y[0];
            D2[5][j] = Y[1];
            D2[6][j] = Y[2];
            D2[7][j] = Y[3];

        }
        else
        {
            for (int i = 0; i < 8; i++)
            {
                D2[i][j] = D[i][j];
            }
        }
    }

    target = 2;
    for (int j = 0; j < 8; j++)
    {
        if (j == target)
        {
            D3[0][j] = X[0];
            D3[1][j] = X[1];
            D3[2][j] = X[2];
            D3[3][j] = X[3];
            D3[4][j] = Y[0];
            D3[5][j] = Y[1];
            D3[6][j] = Y[2];
            D3[7][j] = Y[3];

        }
        else
        {
            for (int i = 0; i < 8; i++)
            {
                D3[i][j] = D[i][j];
            }
        }
    }

    target = 3;
    for (int j = 0; j < 8; j++)
    {
        if (j == target)
        {
            D4[0][j] = X[0];
            D4[1][j] = X[1];
            D4[2][j] = X[2];
            D4[3][j] = X[3];
            D4[4][j] = Y[0];
            D4[5][j] = Y[1];
            D4[6][j] = Y[2];
            D4[7][j] = Y[3];

        }
        else
        {
            for (int i = 0; i < 8; i++)
            {
                D4[i][j] = D[i][j];
            }
        }
    }

    target = 4;
    for (int j = 0; j < 8; j++)
    {
        if (j == target)
        {
            D5[0][j] = X[0];
            D5[1][j] = X[1];
            D5[2][j] = X[2];
            D5[3][j] = X[3];
            D5[4][j] = Y[0];
            D5[5][j] = Y[1];
            D5[6][j] = Y[2];
            D5[7][j] = Y[3];

        }
        else
        {
            for (int i = 0; i < 8; i++)
            {
                D5[i][j] = D[i][j];
            }
        }
    }

    target = 5;
    for (int j = 0; j < 8; j++)
    {
        if (j == target)
        {
            D6[0][j] = X[0];
            D6[1][j] = X[1];
            D6[2][j] = X[2];
            D6[3][j] = X[3];
            D6[4][j] = Y[0];
            D6[5][j] = Y[1];
            D6[6][j] = Y[2];
            D6[7][j] = Y[3];

        }
        else
        {
            for (int i = 0; i < 8; i++)
            {
                D6[i][j] = D[i][j];
            }
        }
    }

    target = 6;
    for (int j = 0; j < 8; j++)
    {
        if (j == target)
        {
            D7[0][j] = X[0];
            D7[1][j] = X[1];
            D7[2][j] = X[2];
            D7[3][j] = X[3];
            D7[4][j] = Y[0];
            D7[5][j] = Y[1];
            D7[6][j] = Y[2];
            D7[7][j] = Y[3];

        }
        else
        {
            for (int i = 0; i < 8; i++)
            {
                D7[i][j] = D[i][j];
            }
        }
    }

    target = 7;
    for (int j = 0; j < 8; j++)
    {
        if (j == target)
        {
            D8[0][j] = X[0];
            D8[1][j] = X[1];
            D8[2][j] = X[2];
            D8[3][j] = X[3];
            D8[4][j] = Y[0];
            D8[5][j] = Y[1];
            D8[6][j] = Y[2];
            D8[7][j] = Y[3];

        }
        else
        {
            for (int i = 0; i < 8; i++)
            {
                D8[i][j] = D[i][j];
            }
        }
    }

    H_matrix[0] = det(D1,8) / det(D,8);
    H_matrix[1] = det(D2,8) / det(D,8);
    H_matrix[2] = det(D3,8) / det(D,8);
    H_matrix[3] = det(D4,8) / det(D,8);
    H_matrix[4] = det(D5,8) / det(D,8);
    H_matrix[5] = det(D6,8) / det(D,8);
    H_matrix[6] = det(D7,8) / det(D,8);
    H_matrix[7] = det(D8,8) / det(D,8);
}




int main(int argc, char *argv[])

{
    // Define file pointer and variables
    FILE * file1, *file;
    int BytesPerPixel = 3, byteRange = 256;
    
    // Allocate image data array
    unsigned char Imagedata_L[Size1][Size2][BytesPerPixel];
    unsigned char Imagedata_M[Size1][Size2][BytesPerPixel];
    unsigned char Imagedata_R[Size1][Size2][BytesPerPixel];

    unsigned char result_reversed[Size1][Size2][BytesPerPixel];
    // Read image (filename specified by first argument) into image data matrix
    if (!(file1=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata_L, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file1);
    fclose(file1);
    // Read image (filename specified by first argument) into image data matrix
    if (!(file1=fopen(argv[2],"rb"))) {
        cout << "Cannot open file: " << argv[2] <<endl;
        exit(1);
    }
    fread(Imagedata_M, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file1);
    fclose(file1);
        // Read image (filename specified by first argument) into image data matrix
    if (!(file1=fopen(argv[3],"rb"))) {
        cout << "Cannot open file: " << argv[3] <<endl;
        exit(1);
    }
    fread(Imagedata_R, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file1);
    fclose(file1);
    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

    int Y_LM[4] = {325,323,452,271};
    int X_LM[4] = {196,33,241,591};
    int y_LM[4] = {65+Size2,58+Size2,191+Size2,12+Size2};
    int x_LM[4] = {190,21,244,605};
    double H_LM[8];
    getHMatrix(x_LM,y_LM,X_LM,Y_LM,H_LM);


    int Y_MR[4] = {51+2*Size2,256+2*Size2,258+2*Size2,91+2*Size2};
    int X_MR[4] = {195,367,524,586};
    int y_MR[4] = {253+Size2,462+Size2,462+Size2,289+Size2};
    int x_MR[4] = {201,373,543,578};
    double H_MR[8];
    getHMatrix(x_MR,y_MR,X_MR,Y_MR,H_MR);

    int c1 = 0;
    double temp1,temp2,temp3,temp4,deltaX,deltaY,value_M;
    int positionP = 0, positionQ = 0, fpq = 0, fpq1 = 0, fp1q1 = 0, fp1q = 0, value_correspond;
    for (int i = -enlargedSize ; i < (Size1 + enlargedSize);i++)
    {
        for (int j = -enlargedSize; j < (3 * Size2) + enlargedSize; j++)
        {
            for (int k = 0; k < BytesPerPixel; k++)
            {
                // calculate the corresponding location to the left image
                temp1 = (((H_LM[0] * (double) i) + (H_LM[1] * (double) j) + H_LM[2]) / ((H_LM[6] * (double) i) + (H_LM[7] * (double) j) + 1));
                temp2 = (((H_LM[3] * (double) i) + (H_LM[4] * (double) j) + H_LM[5]) / ((H_LM[6] * (double) i) + (H_LM[7] * (double) j) + 1));
                temp3 = (((H_MR[0] * (double) i) + (H_MR[1] * (double) j) + H_MR[2]) / ((H_MR[6] * (double) i) + (H_MR[7] * (double) j) + 1));
                temp4 = (((H_MR[3] * (double) i) + (H_MR[4] * (double) j) + H_MR[5]) / ((H_MR[6] * (double) i) + (H_MR[7] * (double) j) + 1));
                
                // if we can find corresponding pixel in the original image, find the value
                if ((temp1 >= 0) & (temp2 >= 0 ) &(temp1 < Size1) & (temp2 < Size2))
                {
                    positionP = floor(temp1);
                    positionQ = floor(temp2);
                    fpq = (int) Imagedata_L[positionP][positionQ][k];
                    fpq1 = (int) Imagedata_L[positionP + 1][positionQ][k];
                    fp1q = (int) Imagedata_L[positionP][positionQ + 1][k];
                    fp1q1 = (int) Imagedata_L[positionP + 1][positionQ + 1][k];
                    deltaX = temp1 - positionP;
                    deltaY = temp2 - positionQ;
                    value_correspond = (int) fpq*(1 - deltaX)*(1 - deltaY) + fpq1*(deltaX)*(1 - deltaY) + fp1q*(1 - deltaX)*(deltaY) + fp1q1*(deltaX)*(deltaY);
                }
                
                else if ((temp3 >= 0) & (temp4 >= 2*Size2) &(temp3 < Size1) & (temp4 < 3*Size2))
                {
                    c1++;
                    positionP = floor(temp3);
                    positionQ = floor(temp4 - 2 * Size2);
                    fpq = (int) Imagedata_R[positionP][positionQ][k];
                    fpq1 = (int) Imagedata_R[positionP + 1][positionQ][k];
                    fp1q = (int) Imagedata_R[positionP][positionQ + 1][k];
                    fp1q1 = (int) Imagedata_R[positionP + 1][positionQ + 1][k];
                    deltaX = temp3 - positionP;
                    deltaY = temp4 - 2 * Size2 - positionQ;
                    value_correspond = (int) fpq*(1 - deltaX)*(1 - deltaY) + fpq1*(deltaX)*(1 - deltaY) + fp1q*(1 - deltaX)*(deltaY) + fp1q1*(deltaX)*(deltaY);
                }
                // otherwise set to 0
                else
                {
                    value_correspond = 0;
                }
                // if current location is at the middle picture, get an average
                
                if ((i >= 0) & (i < Size1) &(j >= (Size2)) &(j < 2 * Size2))
                {
                    
                    /*
                    // if duplicated part exist
                    if (value_correspond != 0)
                    {
                        value_M = (int) Imagedata_M[i][j-Size2][k];
                        result_LM[i+enlargedSize][j+enlargedSize][k] = (char) ((value_M + value_correspond) / 2);
                    }
                    // if no duplicated part, put on the value directly
                    else
                    */
                    {
                        result_LM[i+enlargedSize][j+enlargedSize][k] = Imagedata_M[i][j-Size2][k];
                    }
                    
                }
                
                // otherwise use the calcualted values / 0 directly
                else
                {

                    result_LM[i+enlargedSize][j+enlargedSize][k] = (char) (int (value_correspond));

                }
            }
        }
    }

    // output the processed images
    char out1[] = "Q1_combined.raw";
    if (!(file = fopen(out1,"wb"))) 
    {
        cout << "Cannot open file1: " << out1 << endl;
        exit(1);
    }
    fwrite(result_LM, sizeof(unsigned char), (Size1 + 2 * enlargedSize)*(3 * Size2 + 2 * enlargedSize)*BytesPerPixel, file);
    fclose(file);

    return 0;
}
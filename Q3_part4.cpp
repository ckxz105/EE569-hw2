// EE569 Homework Assignment #2
// Date: 2018.2.10
// Name: Jun Liu
// ID  : 4871562115
// email:liu494@usc.edu

#include<vector>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>  // use max and min algorithm
#include <cmath> // use for pow function
#include <sstream>
#include <string>
#include <fstream>  
#include <iomanip>
using namespace std;

const int BytesPerPixel = 1, Size1 = 372, Size2 = 372;

// Allocate image data array
unsigned char Imagedata_org[Size1][Size2][BytesPerPixel];
bool Imagedata_part1[Size1][Size2][BytesPerPixel];
bool Imagedata_part1_cut[Size1 / 4][Size2 / 4][BytesPerPixel];
bool Imagedata_step1[Size1 / 4][Size2 / 4][BytesPerPixel];
bool Imagedata_findSize[Size1][Size2][BytesPerPixel];
bool Imagedata_cut[Size1 / 4][Size2 / 4][BytesPerPixel];
unsigned char result_part1[Size1 / 4][Size2 / 4][BytesPerPixel];


bool compare(bool* m, int n, string type)
{
    // use for step2's unconditional mark patterns
    if ( (n == 0) & ((type == "S") | (type == "T")) )
    {
        bool possible[16][9] = {
                               // spur
                               0,0,1,
                               0,1,0,
                               0,0,0,

                               1,0,0,
                               0,1,0,
                               0,0,0,
                               // single 4-connection
                               0,0,0,
                               0,1,0,
                               0,1,0,

                               0,0,0,
                               0,1,1,
                               0,0,0,
                               // L - cluster
                               0,0,1,
                               0,1,1,
                               0,0,0,

                               0,1,1,
                               0,1,0,
                               0,0,0,

                               1,1,0,
                               0,1,0,
                               0,0,0,

                               1,0,0,
                               1,1,0,
                               0,0,0,

                               0,0,0,
                               1,1,0,
                               1,0,0,

                               0,0,0,
                               0,1,0,
                               1,1,0,

                               0,0,0,
                               0,1,0,
                               0,1,1,

                               0,0,0,
                               0,1,1,
                               0,0,1,
                               // 4 - connected offset
                               0,1,1,
                               1,1,0,
                               0,0,0,

                               1,1,0,
                               0,1,1,
                               0,0,0,

                               0,1,0,
                               0,1,1,
                               0,0,1,

                               0,0,1,
                               0,1,1,
                               0,1,0
                           };
        for (int i = 0; i < 16; i++)
        {
            if ((m[0] == possible[i][0])&& (m[1] == possible[i][1]) && (m[2] == possible[i][2]) && (m[3] == possible[i][3]) && (m[4] == possible[i][4]) && (m[5] == possible[i][5]) && (m[6] == possible[i][6]) && (m[7] == possible[i][7]) && (m[8] == possible[i][8]) )
            {
                return true;
            }
        }
        // spur corner cluster - part1
        if ((m[2] == true) && (m[4] == true) && (m[6] == true) && (m[0] == false) && (m[8] == false))
        {
            int count1 = 0, count2 = 0;
            if (m[1])
                count1++;
            if (m[5])
                count1++;
            if (m[3])
                count2++;
            if (m[7])
                count2++;

            if ((count1 == 0) && (count2 > 0))
            {
                return true;
            }

            else if ((count1 > 0) && (count2 == 0))
            {
                return true;
            }
            
        }
        // spur corner cluster - part2
        if ((m[0] == true) && (m[4] == true) && (m[8] == true) && (m[2] == false) && (m[6] == false))
        {
            int count1 = 0, count2 = 0;
            if (m[1])
                count1++;
            if (m[3])
                count1++;
            if (m[5])
                count2++;
            if (m[7])
                count2++;

            if ((count1 == 0) && (count2 > 0))
            {
                return true;
            }

            if ((count1 > 0) && (count2 == 0))
            {
                return true;
            }
        }
        // corner cluster
        if ((m[0] == true) & (m[1] == true) & (m[3] == true) & (m[4] == true))
        {
            return true;
        }
        // tee branch - part 1
        if ((m[1] == true) & (m[3] == true) & (m[4] == true) & (m[5] == true) & (m[2] == false) & (m[7] == false) & (m[8] == false)) 
        {
            return true;
        }

        // tee branch - part 2
        if ((m[1] == true) & (m[3] == true) & (m[4] == true) & (m[5] == true) & (m[0] == false) & (m[6] == false) & (m[7] == false)) 
        {
            return true;
        }

        // tee branch - part 3
        if ((m[7] == true) & (m[3] == true) & (m[4] == true) & (m[5] == true) & (m[0] == false) & (m[1] == false) & (m[6] == false)) 
        {
            return true;
        }

        // tee branch - part 4
        if ((m[7] == true) & (m[3] == true) & (m[4] == true) & (m[5] == true) & (m[1] == false) & (m[2] == false) & (m[8] == false)) 
        {
            return true;
        }

        // tee branch - part 5
        if ((m[1] == true) & (m[3] == true) & (m[4] == true) & (m[7] == true) & (m[5] == false) & (m[6] == false) & (m[8] == false)) 
        {
            return true;
        }

        // tee branch - part 6
        if ((m[1] == true) & (m[3] == true) & (m[4] == true) & (m[7] == true) & (m[0] == false) & (m[2] == false) & (m[5] == false)) 
        {
            return true;
        }

        // tee branch - part 7
        if ((m[1] == true) & (m[4] == true) & (m[5] == true) & (m[7] == true) & (m[0] == false) & (m[2] == false) & (m[3] == false)) 
        {
            return true;
        }

        // tee branch - part 8
        if ((m[1] == true) & (m[4] == true) & (m[5] == true) & (m[7] == true) & (m[3] == false) & (m[6] == false) & (m[8] == false)) 
        {
            return true;
        }
        // vee branch - 1
        if ((m[0] == true) & (m[2] == true) & (m[4] == true))
        {
            int count1 = 0;
            if (m[6])
                count1++;
            if (m[7])
                count1++;
            if (m[8])
                count1++;

            if (count1 > 0)
            {
                return true;
            }
        }
        // vee branch - 2
        if ((m[0] == true) & (m[4] == true) & (m[6] == true))
        {
            int count1 = 0;
            if (m[2])
                count1++;
            if (m[5])
                count1++;
            if (m[8])
                count1++;

            if (count1 > 0)
            {
                return true;
            }
        }
        // vee branch - 3
        if ((m[4] == true) & (m[6] == true) & (m[8] == true))
        {
            int count1 = 0;
            if (m[0])
                count1++;
            if (m[1])
                count1++;
            if (m[2])
                count1++;

            if (count1 > 0)
            {
                return true;
            }
        }
        // vee branch - 4
        if ((m[2] == true) & (m[4] == true) & (m[8] == true))
        {
            int count1 = 0;
            if (m[0])
                count1++;
            if (m[3])
                count1++;
            if (m[6])
                count1++;

            if (count1 > 0)
            {
                return true;
            }
        }
        // diagonal branch
        if ((m[1] == true) & (m[2] == false) & (m[3] == false) & (m[4] == true) & (m[5] == true) & (m[6] == true) & (m[7] == false))
        {
            return true;
        }
        if ((m[0] == false) & (m[1] == true) & (m[3] == true) & (m[4] == true) & (m[5] == false) & (m[7] == false) & (m[8] == true))
        {
            return true;
        }
        if ((m[1] == false) & (m[2] == true) & (m[3] == true) & (m[4] == true) & (m[5] == false) & (m[6] == false) & (m[7] == true))
        {
            return true;
        }
        if ((m[0] == true) & (m[1] == false) & (m[3] == false) & (m[4] == true) & (m[5] == true) & (m[7] == true) & (m[8] == false))
        {
            return true;
        }
        //

    }

        // use for step2's unconditional mark patterns
    if ( (n == 0) & (type == "K") )
    {
        bool possible[12][9] = {
                               // spur
                               0,0,0,
                               0,1,0,
                               0,0,1,

                               0,0,0,
                               0,1,0,
                               1,0,0,

                               0,0,1,
                               0,1,0,
                               0,0,0,

                               1,0,0,
                               0,1,0,
                               0,0,0,

                               // single 4-connection
                               0,0,0,
                               0,1,0,
                               0,1,0,

                               0,0,0,
                               0,1,1,
                               0,0,0,

                               0,0,0,
                               1,1,0,
                               0,0,0,

                               0,1,0,
                               0,1,0,
                               0,0,0,
                               // L corner
                               0,1,0,
                               0,1,1,
                               0,0,0,

                               0,1,0,
                               1,1,0,
                               0,0,0,

                               0,0,0,
                               0,1,1,
                               0,1,0,

                               0,0,0,
                               1,1,0,
                               0,1,0,

                           };
        for (int i = 0; i < 12; i++)
        {
            if ((m[0] == possible[i][0]) & (m[1] == possible[i][1]) & (m[2] == possible[i][2]) & (m[3] == possible[i][3]) & (m[4] == possible[i][4]) & (m[5] == possible[i][5]) & (m[6] == possible[i][6]) & (m[7] == possible[i][7]) & (m[8] == possible[i][8]) )
            {
                return true;
            }
        }
        // corner cluster
        if ((m[0] == true) & (m[1] == true) & (m[3] == true) & (m[4] == true))
        {
            return true;
        }
        // tee branch - part 1
        if ((m[1] == true) & (m[3] == true) & (m[4] == true) & (m[5] == true)) 
        {
            return true;
        }

        // tee branch - part 2
        if ((m[1] == true) & (m[3] == true) & (m[4] == true) & (m[7] == true)) 
        {
            return true;
        }

        // tee branch - part 3
        if ((m[7] == true) & (m[3] == true) & (m[4] == true) & (m[5] == true)) 
        {
            return true;
        }

        // tee branch - part 4
        if ((m[1] == true) & (m[4] == true) & (m[5] == true) & (m[7] == true)) 
        {
            return true;
        }

        // vee branch - 1
        if ((m[0] == true) & (m[2] == true) & (m[4] == true))
        {
            int count1 = 0;
            if (m[6])
                count1++;
            if (m[7])
                count1++;
            if (m[8])
                count1++;

            if (count1 > 0)
            {
                return true;
            }
        }
        // vee branch - 2
        if ((m[0] == true) & (m[4] == true) & (m[6] == true))
        {
            int count1 = 0;
            if (m[2])
                count1++;
            if (m[5])
                count1++;
            if (m[8])
                count1++;

            if (count1 > 0)
            {
                return true;
            }
        }
        // vee branch - 3
        if ((m[4] == true) & (m[6] == true) & (m[8] == true))
        {
            int count1 = 0;
            if (m[0])
                count1++;
            if (m[1])
                count1++;
            if (m[2])
                count1++;

            if (count1 > 0)
            {
                return true;
            }
        }
        // vee branch - 4
        if ((m[2] == true) & (m[4] == true) & (m[8] == true))
        {
            int count1 = 0;
            if (m[0])
                count1++;
            if (m[3])
                count1++;
            if (m[6])
                count1++;

            if (count1 > 0)
            {
                return true;
            }
        }
        // diagonal branch
        if ((m[1] == true) & (m[2] == false) & (m[3] == false) & (m[4] == true) & (m[5] == true) & (m[6] == true) & (m[7] == false))
        {
            return true;
        }
        if ((m[0] == false) & (m[1] == true) & (m[3] == true) & (m[4] == true) & (m[5] == false) & (m[7] == false) & (m[8] == true))
        {
            return true;
        }
        if ((m[1] == false) & (m[2] == true) & (m[3] == true) & (m[4] == true) & (m[5] == false) & (m[6] == false) & (m[7] == true))
        {
            return true;
        }
        if ((m[0] == true) & (m[1] == false) & (m[3] == false) & (m[4] == true) & (m[5] == true) & (m[7] == true) & (m[8] == false))
        {
            return true;
        }
        //

    }
    if ((n == 1) & (type == "S"))
    {
        bool possible[4][9] = {false,false,true,false,true,false,false,false,false,
                               true,false,false,false,true,false,false,false,false,
                               false,false,false,false,true,false,true,false,false,
                               false,false,false,false,true,false,false,false,true};

        for (int i = 0; i < 4; i++)
        {
            if ((m[0] == possible[i][0]) & (m[1] == possible[i][1]) & (m[2] == possible[i][2]) & (m[3] == possible[i][3]) & (m[4] == possible[i][4]) & (m[5] == possible[i][5]) & (m[6] == possible[i][6]) & (m[7] == possible[i][7]) & (m[8] == possible[i][8]) )
            {
                return true;
            }
        }
    }

    else if ((n == 2) & (type == "S"))
    {
        bool possible[4][9] = {false,false,false,false,true,true,false,false,false,
                               false,true,false,false,true,false,false,false,false,
                               false,false,false,true,true,false,false,false,false,
                               false,false,false,false,true,false,false,true,false};
        for (int i = 0; i < 4; i++)
        {
            if ((m[0] == possible[i][0]) & (m[1] == possible[i][1]) & (m[2] == possible[i][2]) & (m[3] == possible[i][3]) & (m[4] == possible[i][4]) & (m[5] == possible[i][5]) & (m[6] == possible[i][6]) & (m[7] == possible[i][7]) & (m[8] == possible[i][8]) )
            {
                return true;
            }
        }
    }

    else if ((n == 3) & (type == "S"))
    {
        bool possible[8][9] = {false,false,true,false,true,true,false,false,false,
                               false,true,true,false,true,false,false,false,false,
                               true,true,false,false,true,false,false,false,false,
                               true,false,false,true,true,false,false,false,false,
                               false,false,false,true,true,false,true,false,false,
                               false,false,false,false,true,false,true,true,false,
                               false,false,false,false,true,false,false,true,true,
                               false,false,false,false,true,true,false,false,true};
        for (int i = 0; i < 8; i++)
        {
            if ((m[0] == possible[i][0]) & (m[1] == possible[i][1]) & (m[2] == possible[i][2]) & (m[3] == possible[i][3]) & (m[4] == possible[i][4]) & (m[5] == possible[i][5]) & (m[6] == possible[i][6]) & (m[7] == possible[i][7]) & (m[8] == possible[i][8]) )
            {
                return true;
            }
        }
    }

    if ( (n == 4) && ((type == "T") || (type == "K")) )
    {
        bool possible[8][9] = {false,true,false,false,true,true,false,false,false,
                               false,true,false,true,true,false,false,false,false,
                               false,false,false,true,true,false,false,true,false,
                               false,false,false,false,true,true,false,true,false,

                               false,false,true,false,true,true,false,false,true,
                               true,true,true,false,true,false,false,false,false,
                               true,false,false,true,true,false,true,false,false,
                               false,false,false,false,true,false,true,true,true};
        for (int i = 0; i < 8; i++)
        {
            if ((m[0] == possible[i][0]) & (m[1] == possible[i][1]) & (m[2] == possible[i][2]) & (m[3] == possible[i][3]) & (m[4] == possible[i][4]) & (m[5] == possible[i][5]) & (m[6] == possible[i][6]) & (m[7] == possible[i][7]) & (m[8] == possible[i][8]) )
            {
                return true;
            }
        }
    }

    if ( (n == 4) && (type == "S") )
    {
        bool possible[4][9] = {false,false,true,false,true,true,false,false,true,
                               true,true,true,false,true,false,false,false,false,
                               true,false,false,true,true,false,true,false,false,
                               false,false,false,false,true,false,true,true,true};
        for (int i = 0; i < 4; i++)
        {
            if ((m[0] == possible[i][0]) & (m[1] == possible[i][1]) & (m[2] == possible[i][2]) & (m[3] == possible[i][3]) & (m[4] == possible[i][4]) & (m[5] == possible[i][5]) & (m[6] == possible[i][6]) & (m[7] == possible[i][7]) & (m[8] == possible[i][8]) )
            {
                return true;
            }
        }
    }

    if ( (n == 5) && ((type == "S") || (type == "T")) )
    {
        bool possible[8][9] = {true,true,false,false,true,true,false,false,false,
                               false,true,false,false,true,true,false,false,true,
                               false,true,true,true,true,false,false,false,false,
                               false,false,true,false,true,true,false,true,false,
                               false,true,true,false,true,true,false,false,false,
                               true,true,false,true,true,false,false,false,false,
                               false,false,false,true,true,false,true,true,false,
                               false,false,false,false,true,true,false,true,true

                           };
        for (int i = 0; i < 8; i++)
        {
            if ((m[0] == possible[i][0]) & (m[1] == possible[i][1]) & (m[2] == possible[i][2]) & (m[3] == possible[i][3]) & (m[4] == possible[i][4]) & (m[5] == possible[i][5]) & (m[6] == possible[i][6]) & (m[7] == possible[i][7]) & (m[8] == possible[i][8]) )
            {
                return true;
            }
        }
    }

    if ( (n == 6) && ((type == "S") || (type == "T")) )
    {
        bool possible[10][9] = {true,true,false,false,true,true,false,false,true,
                                false,true,true,true,true,false,true,false,false,

                                true,true,true,false,true,true,false,false,false,
                                false,true,true,false,true,true,false,false,true,
                                true,true,true,true,true,false,false,false,false,
                                true,true,false,true,true,false,true,false,false,
                                true,false,false,true,true,false,true,true,false,
                                false,false,false,true,true,false,true,true,true,
                                false,false,false,false,true,true,true,true,true,
                                false,false,true,false,true,true,false,true,true

                           };
        for (int i = 0; i < 10; i++)
        {
            if ((m[0] == possible[i][0]) && (m[1] == possible[i][1]) && (m[2] == possible[i][2]) && (m[3] == possible[i][3]) & (m[4] == possible[i][4]) && (m[5] == possible[i][5]) && (m[6] == possible[i][6]) && (m[7] == possible[i][7]) && (m[8] == possible[i][8]) )
            {
                return true;
            }
        }
    }

    if ( (n == 6) && (type == "K") )
    {
        bool possible[8][9] = { true,true,true,false,true,true,false,false,false,
                                false,true,true,false,true,true,false,false,true,
                                true,true,true,true,true,false,false,false,false,
                                true,true,false,true,true,false,true,false,false,
                                true,false,false,true,true,false,true,true,false,
                                false,false,false,true,true,false,true,true,true,
                                false,false,false,false,true,true,true,true,true,
                                false,false,true,false,true,true,false,true,true

                              };
        for (int i = 0; i < 8; i++)
        {
            if ((m[0] == possible[i][0]) && (m[1] == possible[i][1]) && (m[2] == possible[i][2]) && (m[3] == possible[i][3]) & (m[4] == possible[i][4]) && (m[5] == possible[i][5]) && (m[6] == possible[i][6]) && (m[7] == possible[i][7]) && (m[8] == possible[i][8]) )
            {
                return true;
            }
        }
    }

    if (n == 7)
    {
        bool possible[4][9] = { true,true,true,false,true,true,false,false,true,
                                true,true,true,true,true,false,true,false,false,
                                true,false,false,true,true,false,true,true,true,
                                false,false,true,false,true,true,true,true,true
                              };
        for (int i = 0; i < 4; i++)
        {
            if ((m[0] == possible[i][0]) & (m[1] == possible[i][1]) & (m[2] == possible[i][2]) & (m[3] == possible[i][3]) & (m[4] == possible[i][4]) & (m[5] == possible[i][5]) & (m[6] == possible[i][6]) & (m[7] == possible[i][7]) & (m[8] == possible[i][8]) )
            {
                return true;
            }
        }
    }


    if (n == 8)
    {
        bool possible[4][9] = { false,true,true,false,true,true,false,true,true,
                                true,true,true,true,true,true,false,false,false,
                                true,true,false,true,true,false,true,true,false,
                                false,false,false,true,true,true,true,true,true
                              };
        for (int i = 0; i < 4; i++)
        {
            if ((m[0] == possible[i][0]) && (m[1] == possible[i][1]) && (m[2] == possible[i][2]) && (m[3] == possible[i][3]) & (m[4] == possible[i][4]) && (m[5] == possible[i][5]) && (m[6] == possible[i][6]) && (m[7] == possible[i][7]) && (m[8] == possible[i][8]) )
            {
                return true;
            }
        }
    }

    if (n == 9)
    {
        bool possible[8][9] = { true,true,true,false,true,true,false,true,true,
                                false,true,true,false,true,true,true,true,true,
                                true,true,true,true,true,true,true,false,false,
                                true,true,true,true,true,true,false,false,true,
                                true,true,true,true,true,false,true,true,false,
                                true,true,false,true,true,false,true,true,true,
                                true,false,false,true,true,true,true,true,true,
                                false,false,true,true,true,true,true,true,true
                              };
        for (int i = 0; i < 8; i++)
        {
            if ((m[0] == possible[i][0]) && (m[1] == possible[i][1]) && (m[2] == possible[i][2]) && (m[3] == possible[i][3]) & (m[4] == possible[i][4]) && (m[5] == possible[i][5]) && (m[6] == possible[i][6]) && (m[7] == possible[i][7]) && (m[8] == possible[i][8]) )
            {
                return true;
            }
        }
    }


    if (n == 10)
    {
        bool possible[4][9] = { true,true,true,false,true,true,true,true,true,
                                true,true,true,true,true,true,true,false,true,
                                true,true,true,true,true,false,true,true,true,
                                true,false,true,true,true,true,true,true,true
                              };
        for (int i = 0; i < 4; i++)
        {
            if ((m[0] == possible[i][0]) && (m[1] == possible[i][1]) && (m[2] == possible[i][2]) && (m[3] == possible[i][3]) & (m[4] == possible[i][4]) && (m[5] == possible[i][5]) && (m[6] == possible[i][6]) && (m[7] == possible[i][7]) && (m[8] == possible[i][8]) )
            {
                return true;
            }
        }
    }

    if ( (n == 11) && (type == "K") )
    {
        bool possible[4][9] = { true,true,true,true,true,true,false,true,true,
                                true,true,true,true,true,true,true,true,false,
                                true,true,false,true,true,true,true,true,true,
                                false,true,true,true,true,true,true,true,true
                              };
        for (int i = 0; i < 4; i++)
        {
            if ((m[0] == possible[i][0]) && (m[1] == possible[i][1]) && (m[2] == possible[i][2]) && (m[3] == possible[i][3]) & (m[4] == possible[i][4]) && (m[5] == possible[i][5]) && (m[6] == possible[i][6]) && (m[7] == possible[i][7]) && (m[8] == possible[i][8]) )
            {
                return true;
            }
        }
    }

    return false;
}

bool check_shrinkable(int i, int j,string type)
{
    
    if (Imagedata_cut[i][j][0] == false)
    {
        Imagedata_step1[i][j][0] = false;
        return false;
    }
    bool m[3][3];
    // find the 3x3 matrix of current pixel's surrending, set 0 if the surrounding does not exist
    for (int a = -1; a < 2; a++)
    {
        for (int b = -1; b < 2; b++)
        {
            if ((i+a >= 0) & (i+a < Size1) & (j+b >=0) & (j+b < Size2))
            {
                m[a+1][b+1] = Imagedata_cut[i+a][j+b][0];
            }
            else
            {
                m[a+1][b+1] = false;
            }
            
        }
    }
    // step 1: use filter 1 to check is able to shrink or not
    for (int n = 1; n < 12; n++)
    {
        if (compare(&m[0][0],n,type))
        {
            //cout << "YES" << endl;
            Imagedata_step1[i][j][0] = true;
            return true;
        }
    }

    Imagedata_step1[i][j][0] = false;
    return false;

}

void STK_step2(string type)
{
    bool m[3][3];
    bool check = false;
    for (int i = 0; i < Size1 / 4; i++) 
    {
        for (int j = 0; j < Size2 / 4; j++) 
        {
            // if this value need to check with filter 2
            if (Imagedata_step1[i][j][0] == true)
            {
                // find the 3x3 matrix of current pixel's surrending, set 0 if the surrounding does not exist
                for (int a = -1; a < 2; a++)
                {
                    for (int b = -1; b < 2; b++)
                    {
                        if ((i+a >= 0) && (i+a < Size1) && (j+b >=0) && (j+b < Size2))
                        {
                            m[a+1][b+1] = Imagedata_step1[i+a][j+b][0];
                        }
                        else
                        {
                            m[a+1][b+1] = false;
                        }
                        
                    }
                }
                check = compare(&m[0][0],0,type);
                // if the pattern is not found, this point is able to be removed
                if (!check)
                {
                    Imagedata_cut[i][j][0] = false;
                }
            }
        }
    }
}
// define a linkedlist structure
struct Node {
  int xaxis;
  int yaxis;
  Node *next;

  Node(int xValue, int yValue);
  Node(int xValue, int yValue, Node *n);
};
// add new elements first time
Node::Node(int xValue, int yValue)
{
    xaxis = xValue;
    yaxis = yValue;
    next = NULL;
}
// add the new elements at the first position of the linkedlist
Node::Node(int xValue, int yValue, Node *n)
{
    xaxis = xValue;
    yaxis = yValue;
    next = n;
}
// get the amount of pixels stored in the bucket
int size(Node *list) {
    int amount = 0;
    Node *p = list;
    while (p != NULL)
    {
        amount++;
        // Go to next
        p = p->next;
    }
    return amount;
}
// add the new pixel position to the memory
void addAtHead(Node *&list,const int xValue, int yValue) 
{
    list = new Node(xValue, yValue, list);

}

typedef Node * ListType;
// define the structure to store the pixel information
class Table {
    public:
        Table(int space);
        void insert(int xValue, int yValue, int insertPos);
        void printAll();
        int count_shrinking();
        int findInWhichStar(int i, int j);
        void cutJigsaw(int number, int * saveArea);
    private:
        int spaceCount;
        ListType * histInfo; // the place to store the hashed buckets

};
// initialize function
Table::Table(int space){
    spaceCount = space;
    histInfo = new ListType[spaceCount];
    for (int i = 0; i < space; i++) 
    {
        histInfo[i] = NULL;
    }
}

// add the new pixel position to the memory
void Table::insert(int xValue, int yValue, int insertPos)
{
    addAtHead(histInfo[insertPos],xValue,yValue);
}
// check the histogram detail, just use for test purpose
void Table::printAll()  
{
    fstream f1;
    char out1[] = "Q3_size_of_each_star.txt";
    f1.open(out1,fstream::out);
    int i = 0, temp = 0, summ = 0;
    if (f1.is_open())
    {
        for (i = 0; i < spaceCount; i++)
        {
            temp = size(histInfo[i]);
            if (temp != 0)
            {
                cout << i <<": " << temp << endl;
                f1 << i << "," << temp<< endl;
            }
        }
    }
    f1.close();
}

// find the pixel belong to which star in the array
int Table::findInWhichStar(int i, int j)
{
    bool found = false;
    Node *p;
    int starLoc = 0;
    while (!found)
    {
        p = histInfo[starLoc];
        while (p->next != NULL)
        {
            if ((p->xaxis == i) && (p->yaxis == j))
            {
                return starLoc;
            }
            p = p->next;
        }
        starLoc++;
    }
    return -1;
}

// find the left upper corner's location and the right lower corner's location
// of given jigsaw
void Table::cutJigsaw(int number, int * saveArea)
{
    int minX = 32767, minY = 32767, maxX = 0, maxY = 0;
    Node * p;
    p = histInfo[number];
    while (p->next != NULL)
    {
        if (p->xaxis > maxX)
        {
            maxX = p->xaxis;
        }
        if (p->xaxis < minX)
        {
            minX = p->xaxis;
        }
        if (p->yaxis > maxY)
        {
            maxY = p->yaxis;
        }
        if (p->yaxis < minY)
        {
            minY = p->yaxis;
        }
        p = p->next;
    }
    saveArea[0] = minX;
    saveArea[1] = minY;
    saveArea[2] = maxX;
    saveArea[3] = maxY;
}

// if one point of a star found, search for the whole pixels of this star
// and store these pixel locations into result_star
// then, set this pixel value to be 0
void getOneStar(int i, int j, int starCount, Table * result_star)
{
    for (int a = -1; a < 2; a++)
    {
        for (int b = -1; b < 2; b++)
        {
            if ((i+a >= 0) && (i+a < Size1) && (j+b >=0) && (j+b < Size2))
            {
                if (Imagedata_findSize[i+a][j+b][0])
                {
                    Imagedata_findSize[i+a][j+b][0] = false;
                    result_star->insert(i,j,starCount);
                    // traverse the whole neighbor pixel
                    getOneStar(i+a,j+b, starCount, result_star);
                }
            }
        }
    }
    return;
}

void fitering(int * saveArea)
{
    bool flag;
    int squarX, squarY, squareSize = 46;
    bool temp1[Size1 / 4][Size2 / 4];
    bool temp2[Size1 / 4][Size2 / 4];
    for (int j = 0; j < 4; j++)
    {
        saveArea[j] = 0;
    }
    for (int i = 0; i < Size1 / 4; i++) 
    {
        // checek whether we have reached the square area
        if ((Imagedata_cut[i][1][0] == true) && (Imagedata_cut[i][40][0] == true))
        {

            squarX = i;
            squarY = 0;
            break;
        }
    }
    for (int i = 0; i < Size1 / 4; i++)
    {
        for (int j = 0; j < Size2 / 4; j++)
        {
            temp1[i][j] = Imagedata_cut[i][j][0];
            temp2[i][j] = 0;
        }
    }
    // remove the square area
    for (int i = 0; i < squareSize; i++)
    {
        for (int j = 0; j < squareSize; j++)
        {
            temp1[i+squarX][j] = 0;
            temp2[i][j] = !Imagedata_cut[i+squarX][j][0];
        }
    }
    /*
    // shrink process
    bool checkResult;
    int count = 1;
    while (count != 0)
    {
        count = 0;
        // repeat until this bound level is impossible to shrink
        for (int i = 0; i < Size1 / 4; i++) 
        {
            for (int j = 0; j < Size2 / 4; j++) 
            {
                checkResult = check_shrinkable(i,j,"S");
                if (checkResult == true)
                {
                    count++;
                }
            }
        }
        STK_step2("S");
    }
    */

    // first filtering
    // find the shrinking result's point to check the shape of the jigsaw
    // upper location
    for (int i = 0; i < squarX; i++)
    {
        for (int j = 0; j < 60; j++)
        {
            if (temp1[i][j])
            {
                saveArea[0] = 1;
            }
        }
    }
    // left location
    for (int i = 5 + squarX; i < 30 + squarX; i++)
    {
        for (int j = 0; j < 25; j++)
        {
            if (temp1[i][j])
            {
                saveArea[1] = 1;
            }
        }
    }
    // lower location
    for (int i = 35 + squarX; i < 55 + squarX; i++)
    {
        for (int j = 0; j < 60; j++)
        {
            if (temp1[i][j])
            {
                saveArea[2] = 1;
            }
        }
    }    
    // right location
    for (int i = 5 + squarX; i < 30 + squarX; i++)
    {
        for (int j = 25; j < 50; j++)
        {
            if (temp1[i][j])
            {
                saveArea[3] = 1;
            }
        }
    }

    // second filtering
    // upper location
    for (int i = 7; i < 13; i++)
    {
        for (int j = 20; j < 26; j++)
        {
            if (temp2[i][j])
            {
                saveArea[0] = -1;
            }
        }
    }
    // left location
    for (int i = 18; i < 26; i++)
    {
        for (int j = 7; j < 12; j++)
        {
            if (temp2[i][j])
            {
                saveArea[1] = -1;
            }
        }
    }
    // lower location
    for (int i = 35; i < 39; i++)
    {
        for (int j = 20; j < 26; j++)
        {
            if (temp2[i][j])
            {
                saveArea[2] = -1;
            }
        }
    }    
    // right location
    for (int i = 18; i < 26; i++)
    {
        for (int j = 39; j < 44; j++)
        {
            if (temp2[i][j])
            {
                saveArea[3] = -1;
            }
        }
    }

} 

int main(int argc, char *argv[])

{
    // Define file pointer and variables
    FILE * file1;
    // Read image (filename specified by first argument) into image data matrix
    if (!(file1=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata_org, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file1);
    fclose(file1);

    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
    int temp;
    // transform the image to binary representation form

   
    for (int i = 0; i < Size1; i++) 
    {
        for (int j = 0; j < Size2; j++) 
        {
            temp = (int) Imagedata_org[i][j][0];
            if (temp < 127)
            {
                Imagedata_part1[i][j][0] = true;
                Imagedata_findSize[i][j][0] = true;
            }
            else
            {
                Imagedata_part1[i][j][0] = false;
                Imagedata_findSize[i][j][0] = false;
            }
        }
    }

    // shrink process

    class Node;
    typedef Node * ListType;
    ListType * histInfo;    
    Table * result_star;
    // initialize the structure
    result_star = new Table(200);
    int starCount = 0;
    for (int i = 0; i < Size1; i++) 
    {
        for (int j = 0; j < Size2; j++) 
        {
            if (Imagedata_findSize[i][j][0])
            {
                // if one point of a star found, search for the whole pixels of this star
                getOneStar(i, j,starCount,result_star);
                starCount++;
            }
        }
    }
    cout << "Not using shrinking method:" << endl;
    cout << "Totally " << starCount << " stars counted" << endl;


    int cutLoc[4];
    int jigsawInfo[starCount][4];

    for (int i = 0; i < starCount; i++)
    {
      // reset the cutting area
      for (int j = 0; j < Size1 / 4;j++)
      {
        for (int k = 0; k < Size2 / 4;k++)
        {
          Imagedata_cut[j][k][0] = 0;
        }
      }
      // get the up left corner and right lower corner
      result_star->cutJigsaw(i, &cutLoc[0]);

      // cut one jigsaw into the temp table
      for (int j = cutLoc[0]; j < cutLoc[2];j++)
      {
        for (int k =cutLoc[1]; k < cutLoc[3];k++)
        {
          Imagedata_cut[j - cutLoc[0]][k - cutLoc[1]][0] = Imagedata_part1[j][k][0];
        }
      }
      // opearte filtering on the image
      fitering(&jigsawInfo[i][0]);
    }
    cout << "The representation of each jigsaw: " << endl;
    for (int i = 0; i < starCount; i++)
    {
        cout.flags(ios::left);
        cout << "Star No." << setw(2) <<(i+1) << ": " ;
        for (int j = 0; j < 4; j++)
        {
            cout.flags(ios::left);
            cout << setw(4)<<jigsawInfo[i][j] << " ";
        }
        cout << endl;
    }

    cout << "----------------------------------" << endl;
    cout << "If considering the shape of each jigsaw:" << endl;
    int uniqueStarCount = starCount;
    int duplicateArray[16];
    int duplicateAmount = 0;
    for (int i = 0; i < starCount;i++)
    {
        for (int j = i+1; j < starCount;j++)
        {
            bool checktDuplicated = false;
            for  (int k = 0; k < duplicateAmount; k++)
            {
                if (j == duplicateArray[k])
                {
                    checktDuplicated = true;
                }
            }

            if (!checktDuplicated)
            {
                int headTailCount[6];
                for (int k = 0; k < 6; k++)
                {
                    headTailCount[k] = 0;
                }
                for (int k = 0; k < 4; k++)
                {
                    // count the amount of head/tail/flat in jigsaw
                    if (jigsawInfo[i][k] == 1)
                    {
                        headTailCount[0]++;
                    }
                    else if (jigsawInfo[i][k] == -1)
                    {
                        headTailCount[1]++;
                    }
                    else
                    {
                        headTailCount[2]++;
                    }

                    if (jigsawInfo[j][k] == 1)
                    {
                        headTailCount[3]++;
                    }
                    else if (jigsawInfo[j][k] == -1)
                    {
                        headTailCount[4]++;
                    }
                    else
                    {
                        headTailCount[5]++;
                    }
                }
                if ((headTailCount[0] == headTailCount[3]) && (headTailCount[1] == headTailCount[4]) && (headTailCount[2] == headTailCount[5]))
                {
                    int needToCheck = 2;
                    
                    if (headTailCount[0] == 2)
                    {
                        needToCheck = 1;
                    }
                    else if (headTailCount[1] == 2)
                    {
                        needToCheck = -1;
                    }
                    else if (headTailCount[2] == 2)
                    {
                        needToCheck = 0;
                    }
                    // need to check the result
                    if (needToCheck != 2)
                    {
                        int pos1[2], pos2[2];
                        bool firstTime1 = true, firstTime2 = true;
                        for (int k = 0; k < 4; k++)
                        {
                            if (jigsawInfo[i][k] == needToCheck)
                            {
                                if (firstTime1)
                                {
                                    pos1[0] = k;
                                    firstTime1 = false;
                                }
                                else
                                {
                                    pos1[1] = k;
                                }
                            }
                            if (jigsawInfo[j][k] == needToCheck)
                            {
                                if (firstTime2)
                                {
                                    pos2[0] = k;
                                    firstTime2 = false;
                                }
                                else
                                {
                                    pos2[1] = k;
                                }
                            }
                        }
                        if (abs(2 - (pos1[1] - pos1[0])) ==  abs(2 - (pos2[1] - pos2[0]))  )
                        {
                            cout << "These 2 jigasws are same: " << (i+1) << "," << (j+1) << endl;
                            uniqueStarCount--;
                            duplicateArray[duplicateAmount] = j;
                            duplicateAmount++;
                        }

                    }
                    else
                    {
                        cout << "These 2 jigasws are same: " << (i+1) << "," << (j+1) << endl;
                        uniqueStarCount--;
                        duplicateArray[duplicateAmount] = j;
                        duplicateAmount++;
                    }
                }
            }
        }
    }

    cout << "The number of unique pieces is: " << uniqueStarCount << endl;
    // store the image
    for (int i = 0; i < Size1 / 4; i++) 
    {
        for (int j = 0; j < Size2 / 4; j++) 
        {
            if (Imagedata_cut[i][j][0])
            {
                result_part1[i][j][0] = (char) (255);
            }
            else
            {
                result_part1[i][j][0] = (char) (0);
            }
        }
    }
    // output the processed images
    char out1[] = "Q3_part1_1.raw";
    if (!(file1 = fopen(out1,"wb"))) 
    {
        cout << "Cannot open file1: " << out1 << endl;
        exit(1);
    }
    fwrite(result_part1, sizeof(unsigned char), Size1*Size2 / 16, file1);
    fclose(file1);

    return 0;
}
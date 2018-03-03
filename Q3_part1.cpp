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

using namespace std;

const int BytesPerPixel = 1, Size1 = 480, Size2 = 640;

// Allocate image data array
unsigned char Imagedata_org[Size1][Size2][BytesPerPixel];
bool Imagedata_part1[Size1][Size2][BytesPerPixel];
bool Imagedata_step1[Size1][Size2][BytesPerPixel];
bool Imagedata_findSize[Size1][Size2][BytesPerPixel];
unsigned char result_part1[Size1][Size2][BytesPerPixel];


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
    
    if (Imagedata_part1[i][j][0] == false)
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
                m[a+1][b+1] = Imagedata_part1[i+a][j+b][0];
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
    for (int i = 0; i < Size1; i++) 
    {
        for (int j = 0; j < Size2; j++) 
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
                    Imagedata_part1[i][j][0] = false;
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

int Table::count_shrinking()
{
    int starCount = 0;
    int starLoc = 0;
    int sumStar[spaceCount]; 
    for (int i = 0; i < Size1; i++) 
    {
        for (int j = 0; j < Size2; j++) 
        {
            // if the marking map has marked in this point
            if (Imagedata_step1[i][j][0])
            {
                cout << i << "," << j << " is found the star is at: " << endl;
                starLoc = findInWhichStar(i,j);
                cout << starLoc << endl;
                if (sumStar[starLoc] == 0)
                {
                    sumStar[starLoc] = 1;
                }
            }
        }
    }
    for (int i = 0; i < spaceCount; i++)
    {
        if (sumStar[starLoc] == 1)
        {
            starCount++;
        }
    }
    return starCount;
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
            if (temp > 127)
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

    //string para = argv[2];
    result_star->printAll();
    bool checkResult;
    int count = 1;
    //for (int time = 0; time < 100; time++)
    while (count != 0)
    {
        count = 0;
        // repeat until this bound level is impossible to shrink
        for (int i = 0; i < Size1; i++) 
        {
            for (int j = 0; j < Size2; j++) 
            {
                checkResult = check_shrinkable(i,j,"S");
                if (checkResult == true)
                {
                    count++;
                }
            }
        }
        cout << "The count of marked points in step1 is: " << count << endl;
        STK_step2("S");
    }

    count = 0;
    // store the image
    for (int i = 0; i < Size1; i++) 
    {
        for (int j = 0; j < Size2; j++) 
        {
            if (Imagedata_part1[i][j][0])
            {
                result_part1[i][j][0] = (char) (255);
                count++;
            }
            else
            {
                result_part1[i][j][0] = (char) (0);
            }
        }
    }
    cout << "Totally amunt of stars: " << count << endl;

    // output the processed images
    char out1[] = "Q3_part1_1.raw";
    if (!(file1 = fopen(out1,"wb"))) 
    {
        cout << "Cannot open file1: " << out1 << endl;
        exit(1);
    }
    fwrite(result_part1, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file1);
    fclose(file1);

    return 0;
}
#!/bin/bash
# EE569 Homework Assignment #2
# Date: 2018.2.25
# Name: Jun Liu
# ID  : 4871562115
# email:liu494@usc.edu
# Operating System: Mac OS X 10.12.6
# Compiler: g++ 4.2.1

#****************************************************************************************
# How to run the programs:
# Question 1
# Q1_part1: ./Q1_part1 puppy.raw
# or        ./Q1_part1 tiger.raw
# or        ./Q1_part1 panda.raw
# Q1_part2: ./Q1_part2 left.raw middle.raw right.raw
# Question 2
# Q2_part1: ./Q2_part1 colorchecker.raw
# Q2_part2: ./Q2_part2 colorchecker.raw
# Q2_part3: ./Q2_part3 flower.raw
# Question 3
# This part 1 is used for shrinking the stars.raw
# Q3_part1: ./Q3_part1 star.raw
# This part 2 is used for thinning the jigsaw_1.raw
# Q3_part2: ./Q3_part2 jigsaw_1.raw
# This part 3 is used for shrinking the jigsaw_2.raw
# Q3_part3: ./Q3_part3 jigsaw_2.raw
# This part 3 is used for counting the board.raw
# Q3_part3: ./Q3_part4 board.raw
#****************************************************************************************
all: Q1_part.o Q1_part2.o
	g++ -ggdb -Wall -Wno-sign-compare -o Q1_part1.o
	g++ -ggdb -Wall -Wno-sign-compare -o Q1_part2.o

Q1_part1: Q1_part1.o
	g++ -ggdb -Wall -Wno-sign-compare -o Q1_part1.o
    
Q1_part1.o: Q1_part1.cpp
	g++ -ggdb -Wall -Wno-sign-compare -c Q1_part1.cpp

Q1_part2: Q1_part2.o
	g++ -ggdb -Wall -Wno-sign-compare -o Q1_part2.o
    
Q1_part2.o: Q1_part2.cpp
	g++ -ggdb -Wall -Wno-sign-compare -c Q1_part2.cpp


Q2_part1: Q2_part1.o
	g++ -ggdb -Wall -Wno-sign-compare -o Q2_part1.o
    
Q2_part1.o: Q2_part1.cpp
	g++ -ggdb -Wall -Wno-sign-compare -c Q2_part1.cpp

Q2_part2: Q2_part2.o
	g++ -ggdb -Wall -Wno-sign-compare -o Q2_part2.o
    
Q2_part2.o: Q2_part2.cpp
	g++ -ggdb -Wall -Wno-sign-compare -c Q2_part2.cpp

Q2_part3: Q2_part3.o
    g++ -ggdb -Wall -Wno-sign-compare -o Q2_part3.o
    
Q2_part3.o: Q2_part3.cpp
    g++ -ggdb -Wall -Wno-sign-compare -c Q2_part3.cpp

Q3_part1: Q3_part1.o
    g++ -ggdb -Wall -Wno-sign-compare -o Q3_part1.o
    
Q3_part1.o: Q3_part1.cpp
    g++ -ggdb -Wall -Wno-sign-compare -c Q3_part1.cpp

Q3_part2: Q3_part2.o
    g++ -ggdb -Wall -Wno-sign-compare -o Q3_part2.o
    
Q3_part2.o: Q3_part2.cpp
    g++ -ggdb -Wall -Wno-sign-compare -c Q3_part2.cpp

Q3_part3: Q3_part3.o
    g++ -ggdb -Wall -Wno-sign-compare -o Q3_part3.o
    
Q3_part3.o: Q3_part3.cpp
    g++ -ggdb -Wall -Wno-sign-compare -c Q3_part3.cpp
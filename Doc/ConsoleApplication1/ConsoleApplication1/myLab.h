#ifndef myLab_h
#define myLab_h


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

//const
#define PI 3.14159265358979323846264338327950288

//
typedef struct {
	double real;
	double img;

}ComplexNum;

//
typedef struct {
	ComplexNum comValue1;
	ComplexNum comValue2;
}BTRValue;
//
typedef struct {
	ComplexNum comValue1;
	ComplexNum comValue2;
	ComplexNum comValue3;
} BTRValue3;

typedef struct {
	long* evenIndexArray;
	long evenSize;
	long* oddIndexArray;
	long oddSize;
}EVEN_ODD_ARRAY;

typedef struct {
	long* group1IndexArray;
	long group1Size;
	long* group2IndexArray;
	long group2Size;
	long* group3IndexArray;
	long group3Size;
}THREE_ARRAY;

//Function
ComplexNum getComplexNum(double real, double img);

//Function
ComplexNum Complex_Multi(ComplexNum com1, ComplexNum com2);
//Function
double* fakeImageTerm(long size);

//Function name: load_data
//Purpose: Read data from file and allocate memory space for them
void load_data_complex(char filename[], double** pRealNumber, double** pImageNumber, long* pInputSize);
//Function name: load_data
//Purpose: Read data from file and allocate memory space for them
void load_data_real(char filename[], double** pRealNumber, long* pInputSize);

//Function to free memory on heap.
void free_resource(double* pRealNumber, double* pImageNumber);

//Function:
ComplexNum twiddleN(long k, long N);
ComplexNum twiddleP(long k, long N);

//
ComplexNum Complex_Plus(ComplexNum com1, ComplexNum com2);

//
ComplexNum Complex_Minus(ComplexNum, ComplexNum);

//Function
BTRValue unitBF(ComplexNum, ComplexNum, long, long, int);
//Function
BTRValue unitBF3(ComplexNum, ComplexNum, ComplexNum, long, long, int);


//Function
//ComplexNum* radix2FFTCalc(ComplexNum* ComplexNum[], const long size, int mark);
ComplexNum* radix2FFTCalc(ComplexNum* ComplexNum, const long size, int mark);
//Function
ComplexNum* radix3FFTCalc(ComplexNum* ComplexNum[], const long size, int mark);
//Function
EVEN_ODD_ARRAY getEvenOddArray(long*, long);
//Function
THREE_ARRAY getThreeArray(long*, long);

//Function
void freeEvenOddArray(EVEN_ODD_ARRAY);
//Function
void freeThreeArray(THREE_ARRAY);

//Function
ComplexNum* makeComplexArray(double* realArray, double* imgArray, long size);

//Function
void outputArray(ComplexNum*, long);


//Function Reorder
ComplexNum* ReOrder(ComplexNum*, long);
//Function Reorder
ComplexNum* ReOrder2(ComplexNum*, long);

//Function to generate new order
EVEN_ODD_ARRAY generate_Index_array(long* original, long size, long times);
//Function to generate new order
THREE_ARRAY generate_Index_array2(long* original, long size, long times);

//Out put data into file.
void output_data(const char filename[], ComplexNum* outputData, long int size);


ComplexNum* loadComplexNumber(const char FilePath, long int* size);

double calcComplexAbs(ComplexNum);




#endif /* myLab_h */
#pragma once

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "myLab.h"
#include "CuTest.h"


int main(int argc, const char * argv[]) {
	// insert code here...
	//printf("Hello, World!\n");
	//declare two arrays to store the r and c number
	double* pRealNumber;
	double* pImageNumber;
	long lInputSize = 0;
	ComplexNum* inputComplexNumber;
	ComplexNum* temp;
	double* zeroSet;
	/****************Radix2FFT---Complex**************
	load_data_complex("testcase\\test1.txt", &pRealNumber, &pImageNumber, &lInputSize);
	inputComplexNumber = makeComplexArray(pRealNumber, pImageNumber, lInputSize);
	temp = radix2FFTCalc(inputComplexNumber, lInputSize, 0);
	outputArray(temp, lInputSize);
	output_data("testcase\\test1_real.txt", temp, lInputSize);
	****************Radix2FFT---Complex**************/

	/***********Radix2FFT-----Real*********
	load_data_real("testcase\\test2.txt", &pRealNumber, &lInputSize);
	zeroSet = fakeImageTerm(lInputSize);
	inputComplexNumber = makeComplexArray(pRealNumber, zeroSet, lInputSize);
	temp = radix2FFTCalc(inputComplexNumber, lInputSize, 0);
	outputArray(temp, lInputSize);
	output_data("testcase\\test2_real.txt", temp, lInputSize);
	****************Radix2FFT---Real**************/

	/***********Radix2IFFT-----Complex*********
	load_data_complex("testcase\\test3.txt", &pRealNumber, &pImageNumber, &lInputSize);
	inputComplexNumber = makeComplexArray(pRealNumber, pImageNumber, lInputSize);
	temp = radix2FFTCalc(inputComplexNumber, lInputSize, 1);
	outputArray(temp, lInputSize);
	output_data("testcase\\test3_real.txt", temp, lInputSize);
	****************Radix2IFFT---Complex**************/

	/***********Radix2IFFT-----Real*********
	load_data_real("testcase\\test4.txt", &pRealNumber, &lInputSize);
	zeroSet = fakeImageTerm(lInputSize);
	inputComplexNumber = makeComplexArray(pRealNumber, zeroSet, lInputSize);
	temp = radix2FFTCalc(inputComplexNumber, lInputSize, 1);
	outputArray(temp, lInputSize);
	output_data("testcase\\test4_real.txt", temp, lInputSize);
	****************Radix2IFFT---Real**************/


	/****************************************************************************************************/
	/****************Radix3FFT---Complex**************
	load_data_complex("//Users//renjianke//Desktop//input3.txt", &pRealNumber, &pImageNumber, &lInputSize);
	inputComplexNumber = makeComplexArray(pRealNumber, pImageNumber, lInputSize);
	temp = radix3FFTCalc(inputComplexNumber, lInputSize, 0);
	outputArray(temp, lInputSize);
	****************Radix3FFT---Complex**************/

	/***********Radix3FFT-----Real*********
	load_data_real("//Users//renjianke//Desktop//input3.txt", &pRealNumber, &lInputSize);
	zeroSet = fakeImageTerm(lInputSize);
	inputComplexNumber = makeComplexArray(pRealNumber, zeroSet, lInputSize);
	temp = radix2FFTCalc(inputComplexNumber, lInputSize, 0);
	outputArray(temp, lInputSize);
	****************Radix3FFT---Real**************/

	/***********Radix3IFFT-----Complex*********
	load_data_complex("//Users//renjianke//Desktop//input3.txt", &pRealNumber, &pImageNumber, &lInputSize);
	inputComplexNumber = makeComplexArray(pRealNumber, pImageNumber, lInputSize);
	temp = radix2FFTCalc(inputComplexNumber, lInputSize, 1);
	outputArray(temp, lInputSize);
	****************Radix3IFFT---Complex**************/

	/***********Radix3IFFT-----Real*********
	load_data_real("//Users//renjianke//Desktop//input3.txt", &pRealNumber, &lInputSize);
	zeroSet = fakeImageTerm(lInputSize);
	inputComplexNumber = makeComplexArray(pRealNumber, zeroSet, lInputSize);
	temp = radix2FFTCalc(inputComplexNumber, lInputSize, 1);
	outputArray(temp, lInputSize);
	****************Radix3IFFT---Real**************/

	//free_resource(pRealNumber, pImageNumber);
	if (temp != NULL) {
		free(temp);
		temp = NULL;
	}
	return 0;
}




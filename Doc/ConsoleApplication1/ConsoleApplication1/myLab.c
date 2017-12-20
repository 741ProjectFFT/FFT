#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "myLab.h"
#define _CRT_SECURE_NO_WARNINGS
#include "CuTest.h"
#include <math.h>

/* ***********************************************************/
//Function
ComplexNum getComplexNum(double real, double img) {
	ComplexNum cpln = { 0 };
	cpln.real = real;
	cpln.img = img;
	return cpln;
}
//Test function
void TestgetComplexNumber(CuTest *tc) {
	ComplexNum a = getComplexNum(1.1, 2.2);
	double actual_r = a.real;
	double actual_i = a.img;
	double expected_r = 1.1;
	double expected_i = 2.2;
	CuAssertDblEquals(tc, expected_r, actual_r, 1e-1);
	CuAssertDblEquals(tc, expected_i, actual_i, 1e-1);
}
//Test Suite
CuSuite* getCompleNumberSuite() {
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, TestgetComplexNumber);
	return suite;
}
/*****************************************************************/
//Function
double* fakeImageTerm(long size) {
	double* arrZero;
	arrZero = malloc(sizeof(double) * (size + 1));
	arrZero = memset(arrZero, 0x0, sizeof(double) * (size + 1));
	return arrZero;
}
//Test function
void TestfakeImageTerm(CuTest *tc) {
	double* actual = fakeImageTerm(10);
	double expected[10];
	for (int i = 0; i < 10;  i++) {
		expected[i] = 0;
	}
	for (int i = 0; i < 10; i++) {
		CuAssertDblEquals(tc, expected[i], actual[i], 1e-1);
	}
	
}
//Test Suite
CuSuite* fakeImageTermSuite() {
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, TestfakeImageTerm);
	return suite;
}
/*****************************************************************/
//Function
ComplexNum Complex_Multi(ComplexNum com1, ComplexNum com2) {
	ComplexNum retValue = { 0 };
	retValue.real = com1.real * com2.real - com1.img * com2.img;
	retValue.img = com1.img * com2.real + com1.real * com2.img;
	return retValue;
}
//Test function
void TestComplex_Multi(CuTest *tc) {
	ComplexNum com1;
	ComplexNum com2;
	com1.real = 5.3;
	com1.img = 5.3;
	com2.real = 2.0;
	com2.img = 2.0;
	ComplexNum actual = Complex_Multi(com1, com2);
	ComplexNum expected;
	expected.real = 0;
	expected.img = 21.2;
	CuAssertDblEquals(tc, actual.img, expected.img, 1e-2);
	CuAssertDblEquals(tc, actual.real, expected.real, 1e-2);
}
//Test Suite
CuSuite* Complex_MultiSuite() {
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, TestComplex_Multi);
	return suite;
}
/*****************************************************************/
//Function
void load_data_real(char filename[], double** ppRealNumber, long* pInputSize) {
	FILE *fp = NULL;
	char line[1024] = { 0 };
	size_t len = 0;
 	size_t read = -1;
	long nLine = 0;


	fopen_s(&fp, filename, "r");
	if (fp == NULL)
	{
		exit(EXIT_FAILURE);
	}
	// determine how many lines does the file have
	while (fgets(line, 1024, fp) != NULL) {
		//printf("Retrieved line of length %zu :\n", read);
		//printf("%s", line);
		nLine++;
	}
	//Allocate buffer for RealNumber and ImageNumber on heap
	*ppRealNumber = malloc(sizeof(double) * (nLine + 1));

	//Initialize buffer
	*ppRealNumber = memset(*ppRealNumber, 0x0, sizeof(double) * (nLine + 1));

	//Set position pointer into beginning location.
	fseek(fp, 0, SEEK_SET);

	long nCount = 0;
	//Format read
	while (fgets(line, 1024, fp) != NULL) {
		sscanf_s(line, "%lf\n", &((*ppRealNumber)[nCount]));
		//printf("%e\n", (*ppRealNumber)[nCount]);
		nCount++;
	}

	*pInputSize = nCount;

	fclose(fp);

	return;

}
void Testload_data_real(CuTest *tc) {
	double* pRealNumber;
	int expected_size = 32;
	double expected_realNumber[32] = { 321, 438, 128, 75, 94, 237, 85, 190, 235, 169, 42, 173, 376, 468, 3, 289, 149, 267, 458, 404, 291, 66, 415, 387, 64, 366, 372, 2, 205, 297, 329, 117 };
	long lInputSize = 0;
	load_data_real("input_Real.txt", &pRealNumber, &lInputSize);
	int actual_size = (int)lInputSize;
	for (int i = 0; i < lInputSize; i++) {
		CuAssertDblEquals(tc, pRealNumber[i], expected_realNumber[i], 1e-2);
	}
	CuAssertIntEquals(tc, actual_size, expected_size);
}
//Test Suite
CuSuite* load_data_realSuite() {
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, Testload_data_real);
	return suite;
}
/*****************************************************************/
//Function
void load_data_complex(char filename[], double** ppRealNumber, double** ppImageNumber, long* pInputSize) {
	///Users/renjianke/Desktop/input.txt
	FILE *fp = NULL;
	char line[1024] = { 0 };
	size_t len = 0;
	size_t read = -1;
	long nLine = 0;


	fopen_s (&fp, filename, "r");
	if (fp == NULL)
	{
		exit(EXIT_FAILURE);
	}
	// determine how many lines does the file have
	while (fgets(line, 1024, fp) != NULL) {

		//printf("%s", line);
		//printf("Retrieved line of length %zu :\n", read);
		//printf("%s", line);
		nLine++;
	}
	//Allocate buffer for RealNumber and ImageNumber on heap
	*ppRealNumber = malloc(sizeof(double) * (nLine + 1));
	*ppImageNumber = malloc(sizeof(double) * (nLine + 1));

	//Initialize buffer
	*ppRealNumber = memset(*ppRealNumber, 0x0, sizeof(double) * (nLine + 1));
	*ppImageNumber = memset(*ppImageNumber, 0x0, sizeof(double) * (nLine + 1));

	//Set position pointer into beginning location.
	fseek(fp, 0, SEEK_SET);

	long nCount = 0;
	//Format read
	while (fgets(line, 1024, fp) != NULL) {

		sscanf_s(line, "%lf & %lf\n", &((*ppRealNumber)[nCount]), &((*ppImageNumber)[nCount]));
		//printf("%e\n", (*ppRealNumber)[nCount]);
		nCount++;
	}

	*pInputSize = nCount;


	fclose(fp);

	return;
}
void Testload_data_complex(CuTest *tc) {
	double* pRealNumber;
	double* pImageNumber;
	int expected_size = 32;
	double expected_imgNumber[32] = { 262, 410, 339, 131, 206, 380, 99, 285, 18, 349, 228, 71, 463, 452, 56, 358, 275, 422, 485, 144, 219, 392, 112, 431, 163, 495, 240, 217, 476, 465, 369, 371 };
	double expected_realNumber[32] = { 321, 438, 128, 75, 94, 237, 85, 190, 235, 169, 42, 173, 376, 468, 3, 289, 149, 267, 458, 404, 291, 66, 415, 387, 64, 366, 372, 2, 205, 297, 329, 117 };
	long lInputSize = 0;
	load_data_complex("input_complex.txt", &pRealNumber, &pImageNumber, &lInputSize);
	int actual_size = (int)lInputSize;
	for (int i = 0; i < lInputSize; i++) {
		CuAssertDblEquals(tc, pRealNumber[i], expected_realNumber[i], 1e-2);
		CuAssertDblEquals(tc, pImageNumber[i], expected_imgNumber[i], 1e-2);
	}
	CuAssertIntEquals(tc, actual_size, expected_size);
}
//Test Suite
CuSuite* load_data_complexSuite() {
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, Testload_data_complex);
	return suite;
}
/*****************************************************************/

//Not applicable to unit test
//Function to free memory on heap.
void free_resource(double* pRealNumber, double* pImageNumber) {
	if (pRealNumber != NULL)
	{
		free(pRealNumber);
		pRealNumber = NULL;
	}

	if (pImageNumber != NULL) {
		free(pImageNumber);
		pImageNumber = NULL;
	}

}
/*****************************************************************/
//Function: negative
ComplexNum twiddleN(long k, long N)
{
	ComplexNum retValue = { 0 };
	retValue.real = cos((2 * PI * k) / N);
	retValue.img = -sin((2 * PI * k) / N);
	return retValue;
}
void TesttwiddleN(CuTest *tc) {
	ComplexNum expected;
	expected.real = 0;
	expected.img = -1;
	long k = 1;
	long N = 4;
	ComplexNum actual;
	actual = twiddleN(k, N);
	CuAssertDblEquals(tc, actual.real, expected.real, 1e-2);
	CuAssertDblEquals(tc, actual.img, expected.img, 1e-2);
}
//Test Suite
CuSuite* twiddleNSuite() {
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, TesttwiddleN);
	return suite;
}
/*****************************************************************/
//Function:
ComplexNum twiddleP(long k, long N)
{
	ComplexNum retValue = { 0 };
	retValue.real = cos((2 * PI * k) / N);
	retValue.img = sin((2 * PI * k) / N);
	return retValue;
}
void TesttwiddleP(CuTest *tc) {
	ComplexNum expected;
	expected.real = 0;
	expected.img = 1;
	long k = 1;
	long N = 4;
	ComplexNum actual;
	actual = twiddleP(k, N);
	CuAssertDblEquals(tc, actual.real, expected.real, 1e-2);
	CuAssertDblEquals(tc, actual.img, expected.img, 1e-2);
}
//Test Suite
CuSuite* twiddlePSuite() {
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, TesttwiddleP);
	return suite;
}
/*****************************************************************/
/*****************************************************************/
ComplexNum Complex_Plus(ComplexNum com1, ComplexNum com2) {
	ComplexNum retValue = { 0 };
	retValue.img = com1.img + com2.img;
	retValue.real = com1.real + com2.real;
	return retValue;
}
void TestComplex_Plus(CuTest *tc) {
	ComplexNum com1;
	ComplexNum com2;
	com1.real = 5.3;
	com1.img = 5.3;
	com2.real = 2.0;
	com2.img = 2.0;
	ComplexNum actual = Complex_Plus(com1, com2);
	ComplexNum expected;
	expected.real = 7.3;
	expected.img = 7.3;
	CuAssertDblEquals(tc, actual.img, expected.img, 1e-2);
	CuAssertDblEquals(tc, actual.real, expected.real, 1e-2);
}
//Test Suite
CuSuite* Complex_PlusSuite() {
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, TestComplex_Plus);
	return suite;
}
/*****************************************************************/
/*****************************************************************/
ComplexNum Complex_Minus(ComplexNum com1, ComplexNum com2) {
	ComplexNum comRet = { 0 };
	comRet.img = com1.img - com2.img;
	comRet.real = com1.real - com2.real;
	return comRet;
}
void TestComplex_Minus(CuTest *tc) {
	ComplexNum com1;
	ComplexNum com2;
	com1.real = 5.3;
	com1.img = 5.3;
	com2.real = 2.0;
	com2.img = 2.0;
	ComplexNum actual = Complex_Minus(com1, com2);
	ComplexNum expected;
	expected.real = 3.3;
	expected.img = 3.3;
	CuAssertDblEquals(tc, actual.img, expected.img, 1e-2);
	CuAssertDblEquals(tc, actual.real, expected.real, 1e-2);
}
//Test Suite
CuSuite* Complex_MinusSuite() {
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, TestComplex_Minus);
	return suite;
}
/*****************************************************************/
//Function
BTRValue unitBF(ComplexNum com1, ComplexNum com2, long k, long N, int mark) {
	BTRValue retBTRValue = { 0 };
	if (mark == 0) {
		retBTRValue.comValue1 = Complex_Plus(com1, Complex_Multi(twiddleN(k, N), com2));
		retBTRValue.comValue2 = Complex_Minus(com1, Complex_Multi(twiddleN(k, N), com2));
	}
	else if(mark == 1) {
		retBTRValue.comValue1 = Complex_Plus(com1, Complex_Multi(twiddleP(k, N), com2));
		retBTRValue.comValue2 = Complex_Minus(com1, Complex_Multi(twiddleP(k, N), com2));
	}
	return retBTRValue;
}
void TestunitBF(CuTest *tc) {
	ComplexNum com1;
	ComplexNum com2;
	com1.real = 3;
	com1.img = 3;
	com2.real = 2;
	com2.img = 2;
	long k = 1;
	long N = 4;
	BTRValue actual = unitBF(com1, com2, k, N, 1);
	CuAssertDblEquals(tc, actual.comValue1.real, 1, 1e-2);
	CuAssertDblEquals(tc, actual.comValue1.img, 5, 1e-2);
	CuAssertDblEquals(tc, actual.comValue2.real, 5, 1e-2);
	CuAssertDblEquals(tc, actual.comValue2.img, 1, 1e-2);

}
//Test Suite
CuSuite* unitBFSuite() {
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, TestunitBF);
	return suite;
}
/*****************************************************************/

//Function
BTRValue unitBF3(ComplexNum com1, ComplexNum com2, ComplexNum com3, long k, long N, int mark) {
	BTRValue retBTRValue = { 0 };
	if (mark == 0) {
		retBTRValue.comValue1 = Complex_Plus(com1, Complex_Multi(twiddleN(k, N), com2));
		retBTRValue.comValue2 = Complex_Minus(com1, Complex_Multi(twiddleN(k, N), com2));
	}
	else {
		retBTRValue.comValue1 = Complex_Plus(com1, Complex_Multi(twiddleP(k, N), com2));
		retBTRValue.comValue2 = Complex_Minus(com1, Complex_Multi(twiddleP(k, N), com2));
	}
	return retBTRValue;
}
/*****************************************************************/
//Function

//ComplexNum* radix2FFTCalc(ComplexNum* arrComN[], const long size, int mark) {
ComplexNum* radix2FFTCalc(ComplexNum* arrComN, const long size, int mark) {
	ComplexNum* retComplexArray = NULL;
	ComplexNum* reorderedComArray = ReOrder(arrComN, size);
	ComplexNum coefficient;
	double t = 0;
	//Init RetComplexArray
	retComplexArray = malloc((sizeof(ComplexNum) + 1) * size);
	retComplexArray = memset(retComplexArray, 0x0, (sizeof(ComplexNum) + 1) * size);

	//Is Calc Array
	bool* arrIsCalc;
	arrIsCalc = malloc(sizeof(bool) * (size + 1));
	arrIsCalc = memset(arrIsCalc, 0x0, sizeof(bool) * (size + 1));

	for (int i = 0; i < size; i++) {
		arrIsCalc[i] = false;
	}

	//Index array
	long* arrIndex;
	arrIndex = malloc(sizeof(long) * (size + 1));
	arrIndex = memset(arrIndex, 0x0, sizeof(long) * (size + 1));

	//The times of stages for calc.
	long lTimes = log2(size);

	// ******** loop 1 for stages **********//
	for (long i = 0; i < lTimes; i++) {
		arrIsCalc = memset(arrIsCalc, 0x0, sizeof(bool) * (size + 1));
		//
		long calcTime = 0;
		// ****** loop 2 for each input********//
		for (long j = 0; j < size; j++) {
			//Generate twiddle k.
			long* tempArray;
			tempArray = malloc(sizeof(long) * (size / 2 + 1));
			tempArray = memset(tempArray, 0x0, sizeof(long) * (size / 2 + 1));
			if (arrIsCalc[j] == false) {
				for (int i = 0; i < size / 2; i++) {
					//tempArray[i] = size / 2 - i - 1;
					tempArray[i] = i;
				}

				//get twiddle k
				for (long k = 0; k < lTimes - i - 1; k++) {
					EVEN_ODD_ARRAY even_odd_array = getEvenOddArray(tempArray, size / 2);
					memcpy(tempArray, even_odd_array.evenIndexArray, even_odd_array.evenSize * sizeof(long));
					freeEvenOddArray(even_odd_array);
				}

				long currentE = (int)pow(2, i);
				//twiddle used index
				long* twIndexArray;
				twIndexArray = malloc(sizeof(long) * (size / 2 + 1));
				twIndexArray = memset(twIndexArray, 0x0, sizeof(long) * (size / 2 + 1));


				long m = 0;
				for (long l = 0; l < size / 2; l++) {
					if (m > pow(2, i) - 1) {
						m = 0;
					}
					twIndexArray[l] = tempArray[m];
					//printf("%d ", twIndexArray[l]);
					m++;
				}

				//printf("\r\n");

				BTRValue unitBF_value = unitBF(reorderedComArray[j], reorderedComArray[j + currentE], twIndexArray[calcTime], size, mark);
				reorderedComArray[j] = unitBF_value.comValue1;
				reorderedComArray[j + currentE] = unitBF_value.comValue2;
				calcTime++;
				if (mark == 1) {
					t = 1.0 / size;
					coefficient = getComplexNum(t, 0);
					//printf("%f\n", t);
					retComplexArray[j] = Complex_Multi(unitBF_value.comValue1, coefficient);
					retComplexArray[j + currentE] = Complex_Multi(unitBF_value.comValue2, coefficient);
				}
				else if(mark == 0) {
					retComplexArray[j] = unitBF_value.comValue1;
					retComplexArray[j + currentE] = unitBF_value.comValue2;
				}

				arrIsCalc[j] = true;
				arrIsCalc[j + currentE] = true;

				if (tempArray != NULL) {
					free(tempArray);
					tempArray = NULL;
				}
				if (twIndexArray != NULL) {
					free(twIndexArray);
					twIndexArray = NULL;
				}
			}
		}
	}
	if (arrIsCalc != NULL) {
		free(arrIsCalc);
		arrIsCalc = NULL;
	}
	if (arrIndex != NULL) {
		free(arrIndex);
		arrIndex = NULL;
	}
	if (arrComN != NULL) {
		free(arrComN);
		arrComN = NULL;
	}
	return retComplexArray;
}
void Testunitradix2FFTCalc(CuTest *tc) {


	//ComplexNum* radix2FFTCalc(ComplexNum* arrComN, const long size, int mark)
	
	

	ComplexNum com1;
	ComplexNum com2;
	ComplexNum* inputArray  = malloc(sizeof(ComplexNum) * 2 + 1);
	inputArray = memset(inputArray, 0x0, sizeof(ComplexNum) * 2 + 1);




	com1.real = 5;
	com1.img = 5;
	com2.real = 1;
	com2.img = 1;
	inputArray[0] = com1;
	inputArray[1] = com2;
	long size = 2;
	long N = 2;
	ComplexNum* actual = radix2FFTCalc(inputArray, size, 1);
	CuAssertDblEquals(tc, actual[0].real, 3, 1e-2);
	CuAssertDblEquals(tc, actual[0].img, 3, 1e-2);
	CuAssertDblEquals(tc, actual[1].real, 2, 1e-2);
	CuAssertDblEquals(tc, actual[1].img, 2, 1e-2);

}
//Test Suite
CuSuite* radix2FFTCalcSuite() {
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, Testunitradix2FFTCalc);
	return suite;
}
/*****************************************************************/
//Function
ComplexNum* radix3FFTCalc(ComplexNum* arrComN[], const long size, int mark) {
	ComplexNum* retComplexArray = NULL;
	ComplexNum* reorderedComArray = ReOrder2(arrComN, size);
	ComplexNum coefficient;
	double t = 0;
	//Init RetComplexArray
	retComplexArray = malloc((sizeof(ComplexNum) + 1) * size);
	retComplexArray = memset(retComplexArray, 0x0, (sizeof(ComplexNum) + 1) * size);

	//Is Calc Array
	bool* arrIsCalc;
	arrIsCalc = malloc(sizeof(bool) * (size + 1));
	arrIsCalc = memset(arrIsCalc, 0x0, sizeof(bool) * (size + 1));

	for (long i = 0; i < size; i++) {
		arrIsCalc[i] = false;
	}

	//Index array
	long* arrIndex;
	arrIndex = malloc(sizeof(long) * (size + 1));
	arrIndex = memset(arrIndex, 0x0, sizeof(long) * (size + 1));

	//The times of stages for calc.
	long lTimes = log2(size) / log2(3);

	// ******** loop 1 for stages **********//
	for (long i = 0; i < lTimes; i++) {
		arrIsCalc = memset(arrIsCalc, 0x0, sizeof(bool) * (size + 1));
		//
		long calcTime = 0;
		// ****** loop 2 for each input********//
		for (long j = 0; j < size; j++) {
			//Generate twiddle k.
			long* tempArray;
			tempArray = malloc(sizeof(long) * (size / 3 + 1));
			tempArray = memset(tempArray, 0x0, sizeof(long) * (size / 3 + 1));
			if (arrIsCalc[j] == false) {
				for (long i = 0; i < size / 3; i++) {
					//tempArray[i] = size / 2 - i - 1;
					tempArray[i] = i;
				}

				//get twiddle k
				for (long k = 0; k < lTimes - i - 1; k++) {
					THREE_ARRAY three_array = getThreeArray(tempArray, size / 3);
					memcpy(tempArray, three_array.group1IndexArray, three_array.group1Size * sizeof(long));
					freeThreeArray(three_array);
				}

				long currentE = (int)pow(3, i);
				//twiddle used index
				long* twIndexArray;
				twIndexArray = malloc(sizeof(long) * (size / 3 + 1));
				twIndexArray = memset(twIndexArray, 0x0, sizeof(long) * (size / 3 + 1));


				long m = 0;
				for (long l = 0; l < size / 3; l++) {
					if (m > pow(3, i) - 1) {
						m = 0;
					}
					twIndexArray[l] = tempArray[m];
					//printf("%d ", twIndexArray[l]);
					m++;
				}

				//printf("\r\n");

				BTRValue unitBF_value = unitBF(reorderedComArray[j], reorderedComArray[j + currentE], twIndexArray[calcTime], size, mark);
				reorderedComArray[j] = unitBF_value.comValue1;
				reorderedComArray[j + currentE] = unitBF_value.comValue2;
				calcTime++;
				if (mark == 1) {
					t = 1 / size;
					coefficient = getComplexNum(t, 0);
					//printf("%f\n", t);
					retComplexArray[j] = Complex_Multi(unitBF_value.comValue1, coefficient);
					retComplexArray[j + currentE] = Complex_Multi(unitBF_value.comValue2, coefficient);
				}
				else {
					retComplexArray[j] = unitBF_value.comValue1;
					retComplexArray[j + currentE] = unitBF_value.comValue2;
				}

				arrIsCalc[j] = true;
				arrIsCalc[j + currentE] = true;

				if (tempArray != NULL) {
					free(tempArray);
					tempArray = NULL;
				}
				if (twIndexArray != NULL) {
					free(twIndexArray);
					twIndexArray = NULL;
				}
			}
		}
	}
	if (arrIsCalc != NULL) {
		free(arrIsCalc);
		arrIsCalc = NULL;
	}
	if (arrIndex != NULL) {
		free(arrIndex);
		arrIndex = NULL;
	}
	if (arrComN != 0) {
		free(arrComN);
		arrComN = NULL;
	}
	return retComplexArray;
}
/*****************************************************************/
//Function
EVEN_ODD_ARRAY getEvenOddArray(long* array, long size) {
	EVEN_ODD_ARRAY retArrayObject = { 0 };
	retArrayObject.evenIndexArray = malloc(sizeof(long) * (size + 1));
	retArrayObject.evenIndexArray = memset((void*)retArrayObject.evenIndexArray, 0x0, sizeof(long) * (size + 1));
	retArrayObject.oddIndexArray = malloc(sizeof(long) * (size + 1));
	retArrayObject.oddIndexArray = memset((void*)retArrayObject.oddIndexArray, 0x0, sizeof(long) * (size + 1));

	for (int i = 0; i < size; i++) {
		if (i % 2 == 0) {
			retArrayObject.evenIndexArray[retArrayObject.evenSize] = array[i];
			retArrayObject.evenSize++;
		}
		else
		{
			retArrayObject.oddIndexArray[retArrayObject.oddSize] = array[i];
			retArrayObject.oddSize++;
		}

	}
	return retArrayObject;
}
void TestgetEvenOddArray(CuTest *tc) {


	//EVEN_ODD_ARRAY getEvenOddArray(long* array, long size)


	EVEN_ODD_ARRAY answer_array = { 0 };
	long even_array[2] = { 1, 3 };
	answer_array.evenIndexArray = even_array;
	answer_array.evenSize = 2;
	long odd_array[2] = { 2, 4 };
	answer_array.oddIndexArray = odd_array;
	answer_array.oddSize = 2;

	long input_array[4] = { 1,2,3,4 };

	
	EVEN_ODD_ARRAY actual = getEvenOddArray(input_array, 4);
	//CuAssertIntEquals(tc, ex, ac)
	for (int i = 0; i < 2; i++)
	{
		CuAssertIntEquals(tc, answer_array.evenIndexArray[i], actual.evenIndexArray[i]);
		CuAssertIntEquals(tc, answer_array.oddIndexArray[i], actual.oddIndexArray[i]);
	}
	CuAssertIntEquals(tc, answer_array.evenSize, actual.evenSize);
	CuAssertIntEquals(tc, answer_array.oddSize, actual.oddSize);
	
}
//Test Suite
CuSuite* getEvenOddArraySuite() {
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, TestgetEvenOddArray);
	return suite;
}
/*****************************************************************/
/*****************************************************************/
//Function
THREE_ARRAY getThreeArray(long* array, long size) {
	THREE_ARRAY retArrayObject = { 0 };
	retArrayObject.group1IndexArray = malloc(sizeof(long) * (size + 1));
	retArrayObject.group1IndexArray = memset((void*)retArrayObject.group1IndexArray, 0x0, sizeof(long) * (size + 1));
	retArrayObject.group2IndexArray = malloc(sizeof(long) * (size + 1));
	retArrayObject.group2IndexArray = memset((void*)retArrayObject.group2IndexArray, 0x0, sizeof(long) * (size + 1));
	retArrayObject.group3IndexArray = malloc(sizeof(long) * (size + 1));
	retArrayObject.group3IndexArray = memset((void*)retArrayObject.group3IndexArray, 0x0, sizeof(long) * (size + 1));

	for (int i = 0; i < size; i++) {
		if (i % 3 == 0) {
			retArrayObject.group1IndexArray[retArrayObject.group1Size] = array[i];
			retArrayObject.group1Size++;
		}
		else if (i % 3 == 1)
		{
			retArrayObject.group2IndexArray[retArrayObject.group2Size] = array[i];
			retArrayObject.group2Size++;
		}
		else {
			retArrayObject.group3IndexArray[retArrayObject.group3Size] = array[i];
			retArrayObject.group3Size++;
		}

	}
	return retArrayObject;
}


void TestgetThreeArray(CuTest *tc) {


	//EVEN_ODD_ARRAY getEvenOddArray(long* array, long size)


	THREE_ARRAY answer_array = { 0 };
	long group1[2] = { 1, 4 };
	long group2[2] = { 2, 5 };
	long group3[2] = { 3, 6 };
	answer_array.group1IndexArray = group1;
	answer_array.group1Size = 2;
	answer_array.group2IndexArray = group2;
	answer_array.group2Size = 2;
	answer_array.group3IndexArray = group3;
	answer_array.group3Size = 2;

	long input_array[6] = { 1, 2, 3, 4, 5, 6};


	THREE_ARRAY actual = getThreeArray(input_array, 6);
	//CuAssertIntEquals(tc, ex, ac)
	for (int i = 0; i < 2; i++)
	{
		CuAssertIntEquals(tc, answer_array.group1IndexArray[i], actual.group1IndexArray[i]);
		CuAssertIntEquals(tc, answer_array.group2IndexArray[i], actual.group2IndexArray[i]);
		CuAssertIntEquals(tc, answer_array.group3IndexArray[i], actual.group3IndexArray[i]);
	}
	CuAssertIntEquals(tc, answer_array.group1Size, actual.group1Size);
	CuAssertIntEquals(tc, answer_array.group2Size, actual.group2Size);
	CuAssertIntEquals(tc, answer_array.group3Size, actual.group3Size);

}
//Test Suite
CuSuite* TestgetThreeArraySuite() {
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, TestgetThreeArray);
	return suite;
}
/*****************************************************************/
/*****************************************************************/
//Function
void freeEvenOddArray(EVEN_ODD_ARRAY object) {
	if (object.evenIndexArray != NULL) {
		free(object.evenIndexArray);
		object.evenIndexArray = NULL;
	}

	if (object.oddIndexArray != NULL) {
		free(object.oddIndexArray);
		object.oddIndexArray = NULL;
	}
}


/*****************************************************************/
//Function
void freeThreeArray(THREE_ARRAY object) {
	if (object.group1IndexArray != NULL) {
		free(object.group1IndexArray);
		object.group1IndexArray = NULL;
	}

	if (object.group2IndexArray != NULL) {
		free(object.group2IndexArray);
		object.group2IndexArray = NULL;
	}
	if (object.group3IndexArray != NULL) {
		free(object.group3IndexArray);
		object.group3IndexArray = NULL;
	}
}


/*****************************************************************/
//Function
ComplexNum* makeComplexArray(double* realArray, double* imgArray, long size) {
	ComplexNum* retValue;
	retValue = malloc(sizeof(ComplexNum) * (size + 1));
	retValue = memset(retValue, 0x0, sizeof(ComplexNum) * (size + 1));

	for (int i = 0; i < size; i++) {
		retValue[i].real = realArray[i];
		retValue[i].img = imgArray[i];
	}

	return retValue;
}

void TestmakeComplexArray(CuTest *tc) {


	//ComplexNum* makeComplexArray(double* realArray, double* imgArray, long size)
	double inputReal[2] = { 1.5, 2.2 };
	double inputImg[2] = { 3.5, 4.5 };
	
	ComplexNum answer_array[2] = { 0 };
	answer_array[0].real = 1.5;
	answer_array[0].img = 3.5;
	answer_array[1].real = 2.2;
	answer_array[1].img = 4.5;

	


	ComplexNum* actual = makeComplexArray(inputReal, inputImg, 2);
	//CuAssertIntEquals(tc, ex, ac)
	for (int i = 0; i < 2; i++)
	{
		CuAssertIntEquals(tc, answer_array[i].real, actual[i].real);
		CuAssertIntEquals(tc, answer_array[i].img, actual[i].img);
	}

}
//Test Suite
CuSuite* TestmakeComplexArraySuite() {
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, TestmakeComplexArray);
	return suite;
}
/*****************************************************************/


/*****************************************************************/
//Function
void outputArray(ComplexNum* array, long size) {
	for (long i = 0; i < size; i++) {
		printf("%ld: %lf %lfi \r\n", i, array[i].real, array[i].img);
	}
}
/*****************************************************************/


/*****************************************************************/
//Function Reorder
ComplexNum* ReOrder(ComplexNum* origin, long size) {
	ComplexNum* retBuffer;
	retBuffer = malloc(sizeof(ComplexNum) * (size + 1));
	memset(retBuffer, 0x0, sizeof(ComplexNum) * (size + 1));
	long* indexArr;

	indexArr = malloc(sizeof(indexArr) * (size + 1));
	memset(retBuffer, 0x0, sizeof(indexArr) * (size + 1));
	for (int i = 0; i < size; i++) {
		indexArr[i] = i;
	}
	long number_Step = (long)log2(size);
	EVEN_ODD_ARRAY evenOdd = generate_Index_array(indexArr, size, number_Step - 1);

	for (int i = 0; i < evenOdd.evenSize; i++) {
		long temp_ = evenOdd.evenIndexArray[i];
		retBuffer[i] = origin[temp_];
	}

	for (long i = evenOdd.evenSize; i < evenOdd.evenSize + evenOdd.oddSize; i++) {
		retBuffer[i] = origin[evenOdd.oddIndexArray[i - evenOdd.evenSize]];
	}

	if (indexArr != NULL) {
		free(indexArr);
		indexArr = NULL;
	}

	if (origin != NULL) {
		free(origin = NULL);
		origin = NULL;
	}

	freeEvenOddArray(evenOdd);
	return retBuffer;
}


void TestReOrder(CuTest *tc) {


	//ComplexNum* ReOrder(ComplexNum* origin, long size)
	ComplexNum input_array[4] = { 0 };
	for (int i = 0; i < 4; i++) {
		input_array[i].img = 2 * i;
		input_array[i].real = i;
	}

	ComplexNum answer_array[4] = { 0 };
	memcpy(&answer_array[0], &input_array[0], sizeof(ComplexNum));
	memcpy(&answer_array[1], &input_array[2], sizeof(ComplexNum));
	memcpy(&answer_array[2], &input_array[1], sizeof(ComplexNum));
	memcpy(&answer_array[3], &input_array[3], sizeof(ComplexNum));




	ComplexNum* actual = ReOrder(input_array, 4);
	//CuAssertIntEquals(tc, ex, ac)
	for (int i = 0; i < 4; i++)
	{
		CuAssertIntEquals(tc, answer_array[i].real, actual[i].real);
		CuAssertIntEquals(tc, answer_array[i].img, actual[i].img);
	}

}
//Test Suite
CuSuite* TestReOrderSuite() {
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, TestReOrder);
	return suite;
}
/*****************************************************************/
///*****************************************************************/
//Function Reorder
ComplexNum* ReOrder2(ComplexNum* origin, long size) {
	ComplexNum* retBuffer;
	retBuffer = malloc(sizeof(ComplexNum) * (size + 1));
	memset(retBuffer, 0x0, sizeof(ComplexNum) * (size + 1));
	long* indexArr;

	indexArr = malloc(sizeof(indexArr) * (size + 1));
	memset(retBuffer, 0x0, sizeof(indexArr) * (size + 1));
	for (int i = 0; i < size; i++) {
		indexArr[i] = i;
	}
	long number_Step = (long)(log2(size) / log2(3));
	THREE_ARRAY threeA = generate_Index_array2(indexArr, size, number_Step - 1);

	for (long i = 0; i < threeA.group1Size; i++) {
		long temp_ = threeA.group1IndexArray[i];
		retBuffer[i] = origin[temp_];
	}
	for (long i = threeA.group1Size; i < threeA.group1Size + threeA.group2Size; i++) {
		long temp_ = threeA.group2IndexArray[i - threeA.group1Size];
		retBuffer[i] = origin[temp_];
	}
	 
	for (long i = threeA.group1Size; i < threeA.group1Size + threeA.group2Size + threeA.group3Size; i++) {
		long temp_ = threeA.group3IndexArray[i - threeA.group1Size - threeA.group2Size];
		retBuffer[i] = origin[temp_];
	}

	if (indexArr != NULL) {
		free(indexArr);
		indexArr = NULL;
	}

	if (origin != NULL) {
		free(origin = NULL);
		origin = NULL;
	}

	freeThreeArray(threeA);
	return retBuffer;
}
//
//void TestReOrder2(CuTest *tc) {
//
//
//	//ComplexNum* ReOrder2(ComplexNum* origin, long size)
//	ComplexNum input_array[6] = { 0 };
//	for (int i = 0; i < 6; i++) {
//		input_array[i].img = 2 * i;
//		input_array[i].real = i;
//	}
//
//	//0 1 2 3 4 5
//
//	ComplexNum answer_array[6] = { 0 };
//	memcpy(&answer_array[0], &input_array[0], sizeof(ComplexNum));
//	memcpy(&answer_array[1], &input_array[3], sizeof(ComplexNum));
//	memcpy(&answer_array[2], &input_array[1], sizeof(ComplexNum));
//	memcpy(&answer_array[3], &input_array[4], sizeof(ComplexNum));
//	memcpy(&answer_array[4], &input_array[2], sizeof(ComplexNum));
//	memcpy(&answer_array[5], &input_array[5], sizeof(ComplexNum));
//
//
//
//
//	ComplexNum* actual = ReOrder2(input_array, 6);
//	//CuAssertIntEquals(tc, ex, ac)
//	for (int i = 0; i < 6; i++)
//	{
//		CuAssertIntEquals(tc, answer_array[i].real, actual[i].real);
//		CuAssertIntEquals(tc, answer_array[i].img, actual[i].img);
//	}
//
//}
////Test Suite
//CuSuite* TestReOrder2Suite() {
//	CuSuite* suite = CuSuiteNew();
//	SUITE_ADD_TEST(suite, TestReOrder2);
//	return suite;
//}

/*****************************************************************/
/*****************************************************************/
//Function to generate new order
EVEN_ODD_ARRAY generate_Index_array(long* original, long size, long times)
{
	//excution time
	if (times <= 1) {
		return getEvenOddArray(original, size);
	}
	else
	{

		EVEN_ODD_ARRAY spreateArr = getEvenOddArray(original, size);
		EVEN_ODD_ARRAY even = generate_Index_array(spreateArr.evenIndexArray, spreateArr.evenSize, times - 1);
		EVEN_ODD_ARRAY odd = generate_Index_array(spreateArr.oddIndexArray, spreateArr.oddSize, times - 1);

		EVEN_ODD_ARRAY retObject = { 0 };
		retObject.evenIndexArray = malloc(sizeof(long) * (even.evenSize + even.oddSize + 1));
		retObject.oddIndexArray = malloc(sizeof(long) * (odd.oddSize + odd.evenSize + 1));
		retObject.evenSize = even.evenSize + even.oddSize;
		retObject.oddSize = odd.evenSize + odd.oddSize;
		//initialization
		memset(retObject.evenIndexArray, 0x0, retObject.evenSize);
		memset(retObject.oddIndexArray, 0x0, retObject.oddSize);
		memcpy(retObject.evenIndexArray, even.evenIndexArray, sizeof(long) * even.evenSize);
		memcpy(retObject.evenIndexArray + even.evenSize, even.oddIndexArray, sizeof(long) * even.oddSize);
		memcpy(retObject.oddIndexArray, odd.evenIndexArray, sizeof(long) * odd.evenSize);
		memcpy(retObject.oddIndexArray + odd.evenSize, odd.oddIndexArray, sizeof(long) * odd.oddSize);
		freeEvenOddArray(odd);
		freeEvenOddArray(even);

		return retObject;

	}
}

void Testgenerate_Index_array(CuTest *tc) {


	//EVEN_ODD_ARRAY generate_Index_array(long* original, long size, long times)
	long input_array[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	EVEN_ODD_ARRAY answer_array = { 0 };
	//First time
	//0 1 2 3 4 5 6 7
	//0 2 4 6
	//1 3 5 7
	//Second time
	//0 2 4 6 1 3 5 7
	//0 4 1 5
	//2 6 3 7
	long evenArray[4] = { 0,4,1,5 };
	answer_array.evenIndexArray = evenArray;
	answer_array.evenSize = 4;
	long oddArray[4] = {2, 4, 3, 7};
	answer_array.oddIndexArray = oddArray;
	answer_array.oddSize = 4;






	EVEN_ODD_ARRAY actual = generate_Index_array(input_array, 8, 2);
	//CuAssertIntEquals(tc, ex, ac)
	for (int i = 0; i < answer_array.evenSize; i++)
	{
		CuAssertIntEquals(tc, answer_array.evenIndexArray[i], actual.evenIndexArray[i]);
		CuAssertIntEquals(tc, answer_array.oddIndexArray[i], actual.oddIndexArray[i]);
	}
	CuAssertIntEquals(tc, answer_array.evenSize, actual.evenSize);
	CuAssertIntEquals(tc, answer_array.oddSize, actual.oddSize);

}
//Test Suite
CuSuite* Testgenerate_Index_arraySuite() {
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, Testgenerate_Index_array);
	return suite;
}
/*****************************************************************/
//Function to generate new order
THREE_ARRAY generate_Index_array2(long* original, long size, long times)
{
	//excution time
	if (times <= 1) {
		return getThreeArray(original, size);
	}
	else
	{

		THREE_ARRAY spreateArr = getThreeArray(original, size);
		THREE_ARRAY group1 = generate_Index_array2(spreateArr.group1IndexArray, spreateArr.group1Size, times - 1);
		THREE_ARRAY group2 = generate_Index_array2(spreateArr.group2IndexArray, spreateArr.group2Size, times - 1);
		THREE_ARRAY group3 = generate_Index_array2(spreateArr.group3IndexArray, spreateArr.group3Size, times - 1);

		THREE_ARRAY retObject = { 0 };
		retObject.group1IndexArray = malloc(sizeof(long) * (group1.group1Size + group1.group2Size + group1.group3Size + 1));
		retObject.group2IndexArray = malloc(sizeof(long) * (group2.group1Size + group2.group2Size + group2.group3Size + 1));
		retObject.group3IndexArray = malloc(sizeof(long) * (group3.group1Size + group3.group2Size + group3.group3Size + 1));
		retObject.group1Size = group1.group1Size + group1.group2Size + group1.group3Size;
		retObject.group2Size = group2.group1Size + group2.group2Size + group2.group3Size;
		retObject.group3Size = group3.group1Size + group3.group2Size + group3.group3Size;
		//initialization
		memset(retObject.group1IndexArray, 0x0, retObject.group1Size);
		memset(retObject.group2IndexArray, 0x0, retObject.group2Size);
		memset(retObject.group3IndexArray, 0x0, retObject.group3Size);

		memcpy(retObject.group1IndexArray, group1.group1IndexArray, sizeof(long) * group1.group1Size);
		memcpy(retObject.group1IndexArray + group1.group1Size, group1.group2IndexArray, sizeof(long) * group1.group2Size);
		memcpy(retObject.group1IndexArray + group1.group1Size + group1.group2Size, group1.group3IndexArray, sizeof(long) * group1.group3Size);
		memcpy(retObject.group2IndexArray, group2.group1IndexArray, sizeof(long) * group2.group1Size);
		memcpy(retObject.group2IndexArray + group2.group1Size, group2.group2IndexArray, sizeof(long) * group2.group2Size);
		memcpy(retObject.group2IndexArray + group2.group1Size + group2.group2Size, group2.group3IndexArray, sizeof(long) * group2.group3Size);
		memcpy(retObject.group3IndexArray, group3.group1IndexArray, sizeof(long) * group3.group1Size);
		memcpy(retObject.group3IndexArray + group3.group1Size, group3.group2IndexArray, sizeof(long) * group3.group2Size);
		memcpy(retObject.group3IndexArray + group3.group1Size + group3.group2Size, group3.group3IndexArray, sizeof(long) * group3.group3Size);
		freeThreeArray(group1);
		freeThreeArray(group2);
		freeThreeArray(group3);

		return retObject;

	}
}


void output_data(const char filename[], ComplexNum* outputData, long int size) {
	FILE *fp = NULL;
	fopen_s(&fp, filename, "w+");
	if (fp == NULL)
	{
		printf("Can not create output file.");
	}

	for (int i = 0; i < size; i++) {
		fprintf_s(fp, "%f & %f\r\n", outputData[i].real, outputData[i].img);
	}
	fclose(fp);
}

ComplexNum* loadComplexNumber(const char* FilePath, long int* size)
{
	double* pRealNumber;
	double* pImageNumber;
	long lInputSize = 0;
	ComplexNum* inputComplexNumber;
	load_data_complex(FilePath, &pRealNumber, &pImageNumber, &lInputSize);
	inputComplexNumber = makeComplexArray(pRealNumber, pImageNumber, lInputSize);
	free_resource(pRealNumber, pImageNumber);
	*size = lInputSize;
	return inputComplexNumber;
}


double calcComplexAbs(ComplexNum complex_)
{
	return sqrt(complex_.real * complex_.real + complex_.img * complex_.img);
}


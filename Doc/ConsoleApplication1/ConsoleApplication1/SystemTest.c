#include "myLab.h"

//load_data_complex("input_complex.txt", &pRealNumber, &pImageNumber, &lInputSize);



int main() {

	long int file1_size = 0;
	long int file2_size = 0;
	ComplexNum* file1 = loadComplexNumber("testcase\\test3_out.txt", &file1_size);
	ComplexNum* file2 = loadComplexNumber("testcase\\test3_real.txt", &file2_size);

	double sumofError = 0;

	for (int i = 0; i < file1_size; i++) {
		//printf("%f %f %f \r\n", calcComplexAbs(file1[i]), calcComplexAbs(file2[i]), pow((calcComplexAbs(file1[i]) - calcComplexAbs(file2[i])), 2));
		//printf("Number:%f, %f, %f, %f\r\n", file1[i].real, file1[i].img, file2[i].real, file2[i].img);
		sumofError = sumofError + pow((calcComplexAbs(file1[i]) - calcComplexAbs(file2[i])), 2);
	} 

	printf("The MSE value is %f \r\n", sumofError / file1_size);

	if (file1 != NULL) {
		free(file1);
	}

	if (file2 != NULL) {
		free(file2);
	}
	

	return 0;
}
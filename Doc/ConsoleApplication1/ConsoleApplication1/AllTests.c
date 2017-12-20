    #include "CuTest.h"
    
    CuSuite* StrUtilGetSuite();
    
    void RunAllTests(void) {
        CuString *output = CuStringNew();
        CuSuite* suite = CuSuiteNew();
        
		
		printf("getCompleNumber function tested!\n");
		CuSuiteAddSuite(suite, getCompleNumberSuite());
		printf("fakeImageTerm function tested!\n");
		CuSuiteAddSuite(suite, fakeImageTermSuite());
		printf("Complex_Multi function tested!\n");
		CuSuiteAddSuite(suite, Complex_MultiSuite());
		printf("load_data_complex function tested!\n");
		CuSuiteAddSuite(suite, load_data_complexSuite());
		printf("load_data_real function tested!\n");
		CuSuiteAddSuite(suite, load_data_realSuite());
		printf("twiddleN function tested!\n");
		CuSuiteAddSuite(suite, twiddleNSuite());
		printf("twiddleP function tested!\n");
		CuSuiteAddSuite(suite, twiddlePSuite());
		printf("Complex_Plus function tested!\n");
		CuSuiteAddSuite(suite, Complex_PlusSuite());
		printf("Complex_Minus function tested!\n");
		CuSuiteAddSuite(suite, Complex_MinusSuite());
		printf("unitBF function tested!\n");
		CuSuiteAddSuite(suite, unitBFSuite());
		printf("radix2FFTCalc function tested!\n");
		CuSuiteAddSuite(suite, radix2FFTCalcSuite());
		
		printf("getEvenOddArray function tested!\n");
		CuSuiteAddSuite(suite, getEvenOddArraySuite());

		printf("getThreeArray function tested!\n");
		CuSuiteAddSuite(suite, TestgetThreeArraySuite());

		printf("makeComplexArray function tested!\n");
		CuSuiteAddSuite(suite, TestmakeComplexArraySuite());

		printf("ReOrder function tested!\n");
		CuSuiteAddSuite(suite, TestReOrderSuite());

        CuSuiteRun(suite);
        CuSuiteSummary(suite, output);
        CuSuiteDetails(suite, output);
        printf("%s\n", output->buffer);
    }
    
    int main(void) {
        RunAllTests();
    }
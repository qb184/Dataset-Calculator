/*Author: Quynh Bui*/
/*BY SUBMITTING THIS FILE TO CARMEN, I CERTIFY THAT I STRICTLY ADHERED TO THE TENURES OF THE OHIO STATE UNIVERSITY'S ACADEMIC INTEGRITY POLICY WITH RESPECT TO THIS ASSIGNMENT*/

#include <stdio.h>
#include <stdlib.h>
int getNumDatasets();
void allocatePtrDatasetArray(float ***datasetArrayPtr, int numDataset);
void getFloatValues(int numSets, int **sizeIntArrayPtr, float ***datasetArrayPtr);
void getOption(int numSets, int *sizeIntArrayPtr, float **datasetArrayPtr);
void printResult(int numSets, int option, int *sizeIntArrayPtr, float **datasetArrayPtr, int *choice);
float getMax(int *sizeIntArrayPtr, float **datasetArrayPtr, int *datasetNum);
float getMin(int *sizeIntArrayPtr, float **datasetArrayPtr, int *datasetNum);
float getSum(int *sizeIntArrayPtr, float **datasetArrayPtr, int *datasetNum);
float getAverage(int *sizeIntArrayPtr, float **datasetArrayPtr, int *datasetNum);
void printValues(int *sizeIntArrayPtr, float **datasetArrayPtr, int *datasetNum);
void exitProgram(int numSets, int *sizeIntArrayPtr, float **datasetArrayPtr);

int main(void)
{
	float **dataSetsArrayPtr = NULL; /*pointer to array of float pointers to data sets*/
	int *dataSetSizesArrayPtr = NULL; /*pointer to array of int sizes of data sets*/
	int numSets = 0; /*number of data sets*/
	numSets = getNumDatasets();
	getFloatValues(numSets,&dataSetSizesArrayPtr,&dataSetsArrayPtr);
	getOption(numSets,dataSetSizesArrayPtr,dataSetsArrayPtr);
}

/*function to get number of data sets*/
int getNumDatasets()
{
	int result;
	printf("\nEnter the number of data sets: ");
	scanf("%d",&result);
	return result;
}
/*function to allocate array of pointers to dataset*/
void allocatePtrDatasetArray(float ***datasetArrayPtr, int numDataset)
{
	*datasetArrayPtr = malloc(numDataset*sizeof(float *));
	if(datasetArrayPtr==NULL){
		printf("Cannot allocate memory");
		exit(0);
	}
}
/*function to allocate size int array*/
void allocatePtrSizeArray(int **sizeIntArrayPtr, int numSets)
{
	*sizeIntArrayPtr = malloc(numSets*sizeof(int));
	if(sizeIntArrayPtr==NULL) {
		printf("Couldn't allocate memory");
		exit(0);
	}
}
/*function to prompt user to input number of floating point values*/
void getFloatValues(int numSets, int **sizeIntArrayPtr, float ***datasetArrPtr)
{
	int i;

	allocatePtrDatasetArray(datasetArrPtr,numSets); /*allocate array of pointers to float values*/
	allocatePtrSizeArray(sizeIntArrayPtr,numSets);
	printf("Enter the number of floating point values in each data set:\n");
	
	for(i=0;i<numSets;i++){
		int sizeEachSet;
		int j;
		scanf("%d",&sizeEachSet); 

		*(*sizeIntArrayPtr+i) = sizeEachSet;

		*(*datasetArrPtr+i) = malloc(sizeEachSet*sizeof(float)); 

		if((*datasetArrPtr+i)==NULL){
			printf("Couldn't allocate memory");
			exit(0);
		}
		
		for(j=0;j<sizeEachSet;j++){
			scanf("%f", (*(*datasetArrPtr+i)+j));
		}
		
	}
}

/*function to get operation option*/
void getOption(int numDataSet, int *sizeIntPtr, float **datasetArrPtr)
{
	int option;
	do {
		int *datasetChoice = malloc(sizeof(int)); /**/
		do {
		printf("\nEnter the number of data set on which you want to do the calculation: ");
		scanf("%d", datasetChoice);
		} while (*datasetChoice>=numDataSet);

		printf("Please choose one of the following options for a calculation based on the data set you have choosen:\n");
		printf("1) Find the minimum value\n");
		printf("2) Find the maximum value\n");
		printf("3) Calculate the sum of all the values\n");
		printf("4) Calculate the average of all the values\n");
		printf("5) Print all the values in the data set\n");
		printf("6) Exit\n");
		printf("\nEnter 1-6: ");
		scanf("%d", &option);
		printResult(numDataSet,option, sizeIntPtr, datasetArrPtr, datasetChoice);
	} while (option!=6);
}
/*function get Option*/
void printResult(int numSet, int option, int *sizeArrayPtr, float **datasetArrayPtr, int *choice)
{
		switch (option) {
			case 1:
			{
				float max=getMax(sizeArrayPtr, datasetArrayPtr, choice);
				printf("The maximum value in data set %d is: %.3f\n",*choice, max);
				break;
			}

			case 2:
			{
				float min = getMin(sizeArrayPtr, datasetArrayPtr, choice);
				printf("The minimum value in data set %d is: %.3f\n",*choice, min);
				break;
			}
			case 3:
			{
				float sum = getSum(sizeArrayPtr, datasetArrayPtr, choice);
				printf("The sum of all values in data set %d is: %.3f\n",*choice, sum);
				break;
			}
			case 4:
			{
				float average = getAverage(sizeArrayPtr, datasetArrayPtr, choice);
				printf("The average of values in data set %d is: %.3f\n", *choice, average);
				break;
			}
			case 5:
			{
				printf("Print values of data set %d:\n",*choice);
				printValues(sizeArrayPtr, datasetArrayPtr, choice);
				break;
			}
			case 6:
			{
				printf("Exiting program...\n");
				exitProgram(numSet,sizeArrayPtr,datasetArrayPtr);

			}
			default:
				break;
		}
				
}
/*function to calculate maximum*/
float getMax(int *sizeArrayPtr, float **datasetArrayPtr, int *datasetChoice) 
{
	float maxValue = *(*(datasetArrayPtr+*datasetChoice));
	int size = *(sizeArrayPtr+*datasetChoice); 
	int i;
	for(i=1;i<size;i++) {
		float temp = *(*(datasetArrayPtr+*datasetChoice)+i);
		if(temp > maxValue) {
			maxValue = temp;
		}
	}
	return maxValue;
}
/*function to calculate minimum*/
float getMin(int *sizeArrayPtr, float **datasetArrayPtr, int *datasetChoice)
{
	float minValue = *(*(datasetArrayPtr + *datasetChoice));
	int size = *(sizeArrayPtr + *datasetChoice);
	int i;
	for(i=1;i<size;i++){
		float temp = *(*(datasetArrayPtr+ *datasetChoice)+i);
		if(temp < minValue) {
			minValue = temp;
		}
	}
	return minValue;
}
/*function to calculate sum*/
float getSum(int *sizeArrayPtr,float **datasetArrayPtr, int *datasetChoice)
{
	float sumValue;
	int size = *(sizeArrayPtr+ *datasetChoice);
	int i;
	for(i=0;i<size;i++){
		sumValue += *(*(datasetArrayPtr+ *datasetChoice)+i);
	}
	return sumValue;
}
/*function to calculate average*/
float getAverage(int *sizeArrayPtr,float **datasetArrayPtr, int *datasetChoice)
{
	float average;
	float sum = getSum(sizeArrayPtr, datasetArrayPtr, datasetChoice);
	int size = *(sizeArrayPtr+*datasetChoice);
	average =sum/size;
	return average;
}
/*function to print all values of the data set*/
void printValues(int *sizeArrayPtr, float **datasetArrayPtr, int *datasetChoice)
{
	int size = *(sizeArrayPtr + *datasetChoice);
	int i;
	for(i=0;i<size;i++){
		float value = *(*(datasetArrayPtr+ *datasetChoice)+i); /*or float?, can i set datasetArrayPtr?*/
		printf("%.3f\t", value);
	}
	printf("\n");
}
/*function exit*/
void exitProgram(int numSets, int *sizeArrayPtr, float **datasetArrayPtr)
{
	if(*datasetArrayPtr!=NULL){
		int i;
		for(i=0;i<numSets;i++){
			free(*(datasetArrayPtr+i));
		}
	}
	*datasetArrayPtr = NULL;

	if(datasetArrayPtr!=NULL){
		free(datasetArrayPtr);
	}
	datasetArrayPtr = NULL;
	
	if(sizeArrayPtr!=NULL){
		free(sizeArrayPtr);
	}
	sizeArrayPtr = NULL;

	exit(0);
}











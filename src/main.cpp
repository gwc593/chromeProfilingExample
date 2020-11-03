#include<iostream>
#include"Debugging/Profiling/Instrumentor.h"

void merge(int arr[], int l, int m, int r)
{
	//copy L & R
	const int nl = m - l+1; //size of Larr
	const int nr = r - m; //size of Rarr
	
	int lc = 0; //left arr iteration position
	int rc = 0; //right arr iteration position
	int ac = l; // full arr iteration position


	int* Larr = new int[nl]; // allocate memory to store Left array
	int* Rarr = new int[nr]; //allocate memory to store right array

	//copy left array
	for (int i = 0; i < nl; ++i) {
		Larr[i] = arr[l+i];
	}

	// copy right array
	for (int i = 0; i < nr; ++i) {
		Rarr[i] = arr[m+i+1];
	}

	//merge sorted arrays
	while (lc < nl && rc < nr) {
		if (Larr[lc] < Rarr[rc]) {
			arr[ac] = Larr[lc++];
		}
		else {
			arr[ac] = Rarr[rc++];
		}
		++ac;
	}

	//merge remainder of left array if any
	while (lc < nl) {
		arr[ac++] = Larr[lc++];
	}

	//merge remainder of right array if any
	while (rc < nr) {
		arr[ac++] = Rarr[rc++];
	}

	//free heap allocations
	delete[] Larr;
	delete[] Rarr;
}

void mergeSort(int arr[], int l, int r)
{
	//keep halfing the partition of the array being dealt with until single value
	if (l < r) {
		int m = (l + r) / 2;

		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}

void mergeSort(int arr[], size_t size)
{
	PROFILE_FUNCTION()
	mergeSort(arr, 0, size - 1);
}

void BubbleSort(int arr[], size_t size)
{
	PROFILE_FUNCTION()
	bool state = true;

	while (state) {
		state = false;
		int temp;

		for (int i = 0; i < size-1; ++i) {
			if (arr[i] > arr[i + 1]) {
				temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
				state = true;
			}
		}
	}
}

void setOutOfOrderArr(int arr[], size_t size)
{
	PROFILE_FUNCTION()
		for (int i = 0; i < size; ++i) {
			arr[i] = size - i;
		}
}

int main(int argc, char** argv){
	
	PROFILE_BEGIN_SESSION("SORTING", "sort.json");
	#define Size 20000
	int N[Size];

	setOutOfOrderArr(N, Size);
	BubbleSort(N, Size);


	setOutOfOrderArr(N, Size);
	mergeSort(N, Size);


	PROFILE_END_SESSION();


	return 0;
}
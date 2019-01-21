#include <iostream>
using namespace std;


void insertionSort(int A[], int n)
{
	for (int i = 1; i < n; i++)				// insertion loop
	{
		char cur = A[i];					// current element to insert
		int j = i - 1;						// start at previous element

		while ((j >= 0) && (A[j] > cur))	// while A[j] is out of order
		{
			A[j + 1] = A[j];				// move A[j] right
			j--;							// decrement j
		}

		A[j + 1] = cur;						// this is the proper place for cur
	}
}

void main()
{
	//char A[] = {'B','C','D','A','E','H','G','F'};
	int A[8] = { 3, 7, 5, 2, 8, 4, 6, 1 };

	insertionSort(A, 8);

	cout << "Sorted array : ";
	for (int i = 0; i < 8; i++) cout << A[i] << ' ';

	::getchar();
}
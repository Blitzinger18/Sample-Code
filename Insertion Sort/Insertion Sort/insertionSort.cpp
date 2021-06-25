#include <iostream>
#include <cstdlib>
#include <time.h>
#include <chrono> 

using namespace std;
using namespace std::chrono;


int main() {
	//user inputs number of elements
	int size;
	cout << "Please enter the number of elements: ";
	cin >> size;
	cout << endl;
	cin.ignore();

	//initialize array
	double* array = new double[size];

	//calculate indicies
	int size1 = sizeof(array) / sizeof(array[0]);

	//seed for random number generator
	srand(time(0));

	//print and fill array
	cout << "This array is unsorted" << endl << endl;
	for (int i = 0; i < size; i++) {
		array[i] = rand() % 100 * .01;
		cout << array[i] << " ";
	}
	cout << endl << endl;

	//___________________________Insertion Sort Begins__________________________________

	//start time clock
	auto start = high_resolution_clock::now();

	int i, j;
	double key;
	for (i = 1; i < size; i++)
	{
		key = array[i];
		j = i - 1;

		//move elements that are greater than key ahead one index
		while (j >= 0 && array[j] > key)
		{
			array[j + 1] = array[j];
			j = j - 1;
		}
		array[j + 1] = key;
	}
	//stop time clock
	auto stop = high_resolution_clock::now();

	cout << "This is the sorted array." << endl << endl;

	//print sorted array
	for (int i = 0; i < size; i++) {
		cout << array[i] << " ";
	}
	cout << endl;

	//calculate runtime
	auto duration = duration_cast<microseconds>(stop - start);

	cout << "Time taken to run function: "
		<< duration.count() << " microseconds" << endl;
	
	cin.ignore();

	//remove pointer array from memory
	delete[] array;


	return 0;
}
#include <iostream>
#include <cstdlib>
#include <vector>
#include <time.h>
#include <chrono> 

using namespace std;
using namespace std::chrono;

//prototypes
void merge(vector<double> & element);
void mergeSort(vector<double>&left, vector<double>& right, vector<double>& elements);

//sorts elements in the vectors
void merge(vector<double> & element) {
	if (element.size() <= 1) return;

	//loads temp vectors for sorting
	int mid = element.size() / 2;
	vector<double> left;
	vector<double> right;

	for (size_t j = 0; j < mid; j++)
		left.push_back(element[j]);
	for (size_t j = 0; j < (element.size()) - mid; j++)
		right.push_back(element[mid + j]);

	//recursive function calls
	merge(left);
	merge(right);
	mergeSort(left, right, element);
}
//sorts elements
void mergeSort(vector<double>&left, vector<double>& right, vector<double>& elements)
{
	int nL = left.size();
	int nR = right.size();
	int i = 0, j = 0, k = 0;

	//checks values at indicies and compares them for sorting
	while (j < nL && k < nR)
	{
		if (left[j] < right[k]) {
			elements[i] = left[j];
			j++;
		}
		else {
			elements[i] = right[k];
			k++;
		}
		i++;
	}
	while (j < nL) {
		elements[i] = left[j];
		j++; i++;
	}
	while (k < nR) {
		elements[i] = right[k];
		k++; i++;
	}
}


int main() {

	//user inputs number of elements
	int size;
	cout << "Please enter the number of elements: ";
	cin >> size;
	cout << endl;
	cin.ignore();

	vector<double> numbers;

	//seed random number generator
	srand(time(0));

	//print and fill initial vector
	cout << "This array is unsorted" << endl << endl;
	for (int i = 0; i < size; i++) {
		numbers.push_back(rand() % 100 * .01);
		cout << numbers.at(i) << " ";
	} 
	cout << endl << endl;

	//start time clock
	auto start = high_resolution_clock::now();

	//call function
	merge(numbers);

	//stop time clock
	auto stop = high_resolution_clock::now();

	//print sorted vector
	cout << "This is the sorted array." << endl << endl;

	for (int i = 0; i < size; i++) {
		cout << numbers.at(i) << " ";
	}
	cout << endl << endl;
	
	//calculate runtime
	auto duration = duration_cast<microseconds>(stop - start);

	cout << "Time taken to run function: "
		<< duration.count() << " microseconds" << endl;

	cout << "Press ENTER to exit." << endl;

	cin.ignore();
 
	return 0;
}
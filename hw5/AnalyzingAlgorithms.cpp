/*
Matthew Chan					    PIC 10B Intermediate Programming
ID: 604178275          		  		Winter 2015
Email: matthew.a.chan@gmail.com		Assignment #5
Section: 2B
Honesty Pledge:

I, Matthew Chan, pledge that this is my own independent
work,which conforms to the guidelines of academic honesty as
described in the course syllabus.

List of known bugs: None.
*/
#include "Algorithms.h"
#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<ctime>
using namespace std;

const int NUM_SORT_FUNCTIONS = 6;
const int ARRAY_COL_WIDTH = 6;
const int N_COL_WIDTH = 10;
const int BN_COL_WIDTH = 10;

void set_seed(){
	// stores the current time of the computer as an int
	int seed = static_cast<int>(time(NULL));
	// sets the random number seed to that int
	srand(seed);
}

int random(int min, int max) {
	int num_values_to_pick_from = max - min + 1;
	// constructs a random integer ranging from min to max
	return (rand() % num_values_to_pick_from) + min;
}

void print_array(const int A[], const int N, ostream& os = cout){
	os << right;
	for(int i = 0; i < N; i++){
	   if(i % 10 == 0) os << endl;
		os << setw(ARRAY_COL_WIDTH) << A[i];
	}
}

void performSort(void (*sort)(int[], const int, int&), int data[], const int N, string filename, ostream& os){
	// Create output filestream
	ofstream out(filename, fstream::app);
	// Print the elements of the inital unsorted array to the output file
	print_array(data, N, out);
	// Create a counter to track the number of statements used in the algorithm (measure complexity)
	int counter = 0;
	// Sort the array using the specified method
	sort(data, N, counter);
	// Print the elements of the sorted array to the output file
	print_array(data, N, out);
	out << "\nNum statements: " << counter << endl;
	// Print out the number of statements used by the sorting algorithm to the output file
	os << setw(BN_COL_WIDTH) << counter;
	
	// Close the output filestream
	out.close();
}

void makeRecord(int N, ostream& os){
	// Print out the number of elements to be sorted
	os << setw(N_COL_WIDTH) << N;
	// Create a pointer to an array with N random elements
	int* data = new int[N];
	for (int i = 0; i < N; i++) {
		data[i] = random(1, 10000);
	}
	// Create a clone of the data array
	int* clone = new int[N];
	for (int i = 0; i < N; i++) {
		clone[i] = data[i];
	}
	// Perform each of the 6 sorting algorithms, this will print out the statements required for each algorithm to the output file
	performSort(bubble_sort, clone, N, "bubblesort.txt", os);
	for (int i = 0; i < N; i++) {
		clone[i] = data[i];
	}
	performSort(selection_sort, clone, N, "selectionsort.txt", os);
	for (int i = 0; i < N; i++) {
		clone[i] = data[i];
	}
	performSort(insertion_sort, clone, N, "insertionsort.txt", os);
	for (int i = 0; i < N; i++) {
		clone[i] = data[i];
	}
	performSort(merge_sort, clone, N, "mergesort.txt", os);
	for (int i = 0; i < N; i++) {
		clone[i] = data[i];
	}
	performSort(shell_sort, clone, N, "shellsort.txt", os);
	for (int i = 0; i < N; i++) {
		clone[i] = data[i];
	}
	performSort(radix_sort, clone, N, "radixsort.txt", os);
	for (int i = 0; i < N; i++) {
		clone[i] = data[i];
	}
	os << endl;
}

void sortAndCount(string count_file){
	ofstream out(count_file);
	out << "*********Number of Statements for Various Sorting Algorithms*********" << endl << endl;
	out << setw(N_COL_WIDTH) << "N" << setw(N_COL_WIDTH) << "Bubble" << setw(N_COL_WIDTH) << "Selection" << setw(N_COL_WIDTH) << "Insertion" << setw(N_COL_WIDTH) << "Merge" << setw(N_COL_WIDTH) << "Shell" << setw(N_COL_WIDTH) << "Radix" << endl;
	// Fills out the rows for the the statements required to sort an array with N elements
	makeRecord(1, out);
	makeRecord(2, out);
	makeRecord(4, out);
	makeRecord(8, out);
	makeRecord(16, out);
	makeRecord(32, out);
	makeRecord(64, out);
	makeRecord(128, out);
	makeRecord(256, out);
	makeRecord(512, out);
	makeRecord(1024, out);
	// Close the output filestream
	out.close();
}

void analyzeCounts(string count_file, string analysis_file){
	// Create an input filestream
	ifstream in(count_file);
	// Create an output filestream
	ofstream out(analysis_file);
	out << "*********Algorithm Analysis*********" << endl << endl;
	out << setw(N_COL_WIDTH) << "T(2N)/T(N)" << setw(N_COL_WIDTH) << "Bubble" << setw(N_COL_WIDTH) << "Selection" << setw(N_COL_WIDTH) << "Insertion" << setw(N_COL_WIDTH) << "Merge" << setw(N_COL_WIDTH) << "Shell" << setw(N_COL_WIDTH) << "Radix" << endl;
	// Create a string to hold all of the unwanted buffer data
	string sBuffer;
	getline(in, sBuffer);	// Catch the header
	getline(in, sBuffer);	// Catch the empty line
	getline(in, sBuffer);	// Catch the column headers
	// Create a char to hold unwanted buffer data
	char cBuffer;
	in.get(cBuffer);	// Catch the endline character
	// Create an int to hold unwanted buffer data
	int iBuffer;
	in >> iBuffer;	// Catch the first column data
	// Create a matrix that will hold the values from the table
	double row[11][6];
	// Read in values to the table
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 6; j++) {
			in >> row[i][j];
		}
		// Clear the unneccessary parts in the input buffer
		getline(in, sBuffer);	// Catches the endline
		in >> iBuffer;	// Catches the first column data
	}
	// Output the T(2N)/T(N) values to the table
	for (int i = 0; i < 10; i++) {
		out << setw(N_COL_WIDTH) << " ";
		for (int j = 0; j < 6; j++) {
			out << setw(N_COL_WIDTH) << fixed << setprecision(6) << (double)(row[i + 1][j] / row[i][j]);
		}
		out << endl;
	}
	// Close the input filestream
	in.close();
	// Close the output filestream
	out.close();
}

int main(){
	set_seed();
	string count_file = "StatementCount.txt";
	string analysis_file = "AlgorithmAnalysis.txt";
	sortAndCount(count_file);
	analyzeCounts(count_file, analysis_file);
	system("PAUSE");
	return 0;
}
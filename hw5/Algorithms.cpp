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
#include<iostream>
#include<vector>
#include "Algorithms.h"
using namespace std;

void shell_sort(int a[], const int size, int& statements) {
	// The Shell Sort h-sequence to use is 9841, 3280, 1093, 364, 121, 40, 13, 3, 1
	int h_sequence[9] = { 9841, 3280, 1093, 364, 121, 40, 13, 3, 1 };
	for each (int gap in h_sequence) {
		for (int i = gap; i < size; i++) {
			// Swap the two evaluated numbers if they are out of order
			for (int j = i - gap; j >= 0 && a[j] > a[j + gap]; j -= gap) {
				swap(a[j], a[j + gap]);
				statements += 5;	// Swap statement, increment for loop, for condition test
			}
			statements += 4;	// Init for loop, increment for loop, 2 for condition test
		}
		statements += 3;	// Init for loop, iterating through the for each loop, for condition test
	}
	statements += 2;	// Initialize h_sequence array, init for each loop
}

void bubble_sort(int a[], const int size, int& statements) {
    bool quit = false;
	// each iteration passes through the array creates a 'bubble'
	for(int i = 1; (i < size && quit==false); i++) {
   	    quit = true;
		// pass through the array, swapping adjacent elements if out of order 
		// this moves the bubble along
		for(int j = 0; j < size-i; j++){
			if(a[j] > a[j+1]){
			  swap(a[j], a[j+1]);
			  // continue with bubble sort if you had to make a swap
			  quit = false;
			  statements += 5;	// swap counts as 3 statements, 1 bool assignment
			}
			statements += 3;	// for loop increment, for loop condition test, if statement
		}
		statements += 5;	// bool assignment, for loop init, for loop counter increment, 2 for loop condition test
	}
	statements += 3; // bool initialization, for loop initialization, for loop condition test
}

void selection_sort(int a[], const int size, int& statements){
    int smallest;
	for(int i = 0; i < size-1; i++) {
	    smallest = i;
		// find the index of the smallest unsorted item (ith smallest overall)
		for(int j = i+1; j < size; j++){
			if(a[j] < a[smallest]){
			  smallest = j;
			  statements ++;	// assignment
			}
			statements += 3;	// increment loop, if statement, for loop condition test
		}
		// swap the ith element with the ith smallest element
		swap(a[i], a[smallest]);
		statements += 8;	// int assignment, increment for loop, for loop init, swap function call, 2 for loop condition test
	}
	statements += 3; // int initialization, for loop init, for loop condition test

}

void insertion_sort(int a[], const int size, int& statements){
    int inserted_item;
	int j;
    // insert each element into its proper place in the sorted region of the array
	for(int i = 1; i < size; i++){
		// chose the item to insert
		inserted_item = a[i];
		for(j = i-1; j >= 0 && a[j] > inserted_item; j--){
		   // shift to the right by 1 place each element in sorted region  
		   // that is bigger then the inserted item
			a[j+1] = a[j];			
			statements += 3;	// assignment, increment for loop, for loop condition test
		}
		// insert the item into its correct position in the sorted region
		a[j+1] = inserted_item;
		statements += 6;	// increment for loop, assign 2 int values, init for loop, 2 for loop condition test
	}
	statements += 4;	// two int initializations, for loop init, for loop condition test

}

void merge(int a[], int first, int middle, int last, int& statements){
  int* temp = new int[last - first + 1];
  int i;      // index for first sorted array
  int j;      // index for second sorted array
  int k = 0;  // index for temp array
  // Copy first sorted array into temp array
  for(i = first; i <= middle; i++){
     temp[k++] = a[i];
	 statements += 3;	// assignment, increment for loop, for loop condition test
  }
   // Copy second sorted array backwards into temp array
  for(j = last; j > middle; j--){
     temp[k++] = a[j];
	 statements += 3;	// assignment, increment for loop, for loop condition test
  }
  i = 0;
  j = last - first;
  // merge the two arrays back into original array
  for(k = first; k <= last; k++){
    a[k] = (temp[i] <= temp[j] ? temp[i++] : temp[j--]);
	statements += 3;	// assignment, increment for loop, for loop condition test
  }
  delete[] temp;
  statements += 13;	// 4 int init, 2 int assign, 3 for loop init, 3 for loop condition tests, 1 deallocation call
}

void merge_sort(int a[], const int size, int first, int last, int& statements){
	if(first < last){
     	int middle = (first + last)/2;
		merge_sort(a, size, first, middle, statements);
		merge_sort(a, size, middle + 1, last, statements);
	    merge(a, first, middle, last, statements);
		statements += 4;	// 1 int init, 3 recursive calls
	}
	statements++;	// if comparison statement
}

void merge_sort(int a[], const int size, int& statements){
	merge_sort(a, size, 0, size-1, statements);
	statements++;	// recursive call
}

void sort_into_vectors_by_radix(int a[], const int size, int radix, vector<int> bin[], int& statements){
   // sort by given radix
   for(int j = 0; j < size; j++) {
	   int n = pow(10, radix);
	   int index = (a[j] % n) / (n/10.0);
	   bin[index].push_back(a[j]);
	   statements += 5;	// 2 int init, 1 vector function call, for loop condition test, for loop increment
   }
   statements += 2;	// for loop init, for loop condition test
}

void empty_vectors_back_into_array(int a[], const int size, vector<int> bin[], int& statements){
   int j = size-1;
     // empty vectors in order into array
   for(int i = 9; i >= 0; i--) {	   
	   while(!bin[i].empty()){
	     a[j--] = bin[i].back();
		 bin[i].pop_back();		 
		 statements += 3;	// 2 vector function calls, while loop condition test
	   }
	   statements += 4;	// for loop increment, for loop condition test, while loop condition test, while loop init
   }
   statements += 3;	// int initialization, for loop init, for loop condition test
}

void radix_sort(int a[], const int size, int& statements){
   vector<int> bin[10];
   for(int i = 0; i < 10; i++){
     bin[i] = vector<int>();
	 statements += 3;	// vector assignment, for loop increment, for loop condition test
   }
   // sort by ones
   sort_into_vectors_by_radix(a, size, 1, bin, statements);
   // empty vectors in order into array
   empty_vectors_back_into_array(a, size, bin, statements);
   // sort by tens
   sort_into_vectors_by_radix(a, size, 2, bin, statements);
   // empty vectors in order into array
   empty_vectors_back_into_array(a, size, bin, statements);
   // sort by hundreds
   sort_into_vectors_by_radix(a, size, 3, bin, statements);
   // empty vectors in order into array
   empty_vectors_back_into_array(a, size, bin, statements);
   // sort by thousands
   sort_into_vectors_by_radix(a, size, 4, bin, statements);
   // empty vectors in order into array
   empty_vectors_back_into_array(a, size, bin, statements);
   // sort by ten thousands
   sort_into_vectors_by_radix(a, size, 5, bin, statements);
   // empty vectors in order into array
   empty_vectors_back_into_array(a, size, bin, statements);
   statements += 13;	// 10 recursive calls, 1 vector init, 1 for loop init, for loop condition test
}
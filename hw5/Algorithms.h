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
#ifndef ALGORITHMS_H
#define ALGORITHMS_H

void bubble_sort(int a[], const int size, int& statements);
void selection_sort(int a[], const int size, int& statements);
void insertion_sort(int a[], const int size, int& statements);
void merge_sort(int a[], const int size, int& statements);
void radix_sort(int a[], const int size, int& statements);
void shell_sort(int a[], const int size, int& statements);
#endif

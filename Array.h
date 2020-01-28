/**
 * @file    Array.h
 * @brief   The various sorting algorithms discussed in class will be 
 *			applied to an Array object; sorting methods for
 *			this class will be introduced one at a time.
 *
 * @author  Binh Thanh Nguyen
 * @date    Fri, Sep 20, 2019
 */

#ifndef ARRAY_H
#define ARRAY_H 

#include <iostream>
	using std::ostream;
	using std::cout;
	using std::cin;
	using std::endl;
#include <ctime>
#include <string>
	using std::string;
#include <cmath>
	using std::pow;
#include <utility>
	using std::pair;

class Array
{
public:
	Array (int size, int order);	// constructor
	Array (const Array& original);	// copy-constructor
	~Array();						// destructor
	void write (const string& sortName, 
			    const string& orderName,
			    ostream& outfile = cout) const;
	int getSize () const;
	// Sorting methods
	pair<double,int> selectionSort();
	pair<double,int> bubbleSort();
	pair<double,int> insertionSort();
	pair<double,int> modifiedInsertionSort();
	pair<double,int> mergeSort();
	pair<double,int> quickSort();
	pair<double,int> randomizedQuickSort();
	pair<double,int> heapSort();
	
private:
	// private methods
	void swap (int& a, int& b);
	pair<int,int> binarySearch(int value, int first, int last);
	int moveDownHeap (int i, int n);
	int quickSort (int first, int last);
	int randomizedQuickSort(int first, int last);
	int mergeSort (int first, int last);
	int merge (int first, int last);

private:
	int* data;
	int size;
};

// With regard to the algorithm names, define an enumerated type (SORTS) and the algorithm names array (SORT NAMES).
enum SORTS {SELECTION, BUBBLE, INSERTION, MODINSERTION, MERGE, QUICK, RANQUICK, HEAP};
const string SORT_NAMES[8] = {"Selection    ", "Bubble       ", "Insertion    ", "Mod.Insertion",
							  "Merge        ", "Quick        ", "Ran Quick    ", "Heap         "};

// The names of the various data orderings are handled in a fashion analagous to that of the sorting orders.
enum ORDERS {RANDOM, IN_ORDER, REVERSE_ORDER};
const string ORDER_NAMES[3] = {"Random ", "InOrder", "Reverse"};

#endif
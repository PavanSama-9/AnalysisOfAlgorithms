/**
 * @file    Array.cpp
 * @brief   This file contains the implementation of the constructor, destructor,
 *			copy-constructor, write and private swap methods.
 *
 * @author  Pavan Kumar Reddy Sama
 * @date    Fri, Sep 20, 2019
 */

#include "Array.h"

/**
 * @brief       The constructor for the array is informed of the desired size and ordering of the data. 
 *				This will allow the sorting algorithms to be compared across both dimensions.
 *
 * @param        newSize     	the desired size of array
 * @param        order     		the enem desired order of the data
**/
Array::Array (int newSize, int order)
{
	size = newSize;
	data = new int [size];
	for (int i = 0; i < size; i++)
	{
		switch (order)
		{
			case RANDOM:
				data[i] = rand()%1000;
				break;
			case IN_ORDER:
				data[i] = i;
				break;
			case REVERSE_ORDER:
				data[i] = size - (i + 1);
				break;
		}	// end switch
	}	// end for loop
}	// end method

/**
 * @brief       Copy constructor of the array object, when an object is passed (to a function) by value as an argument
 *
 * @param[out]      original     array to be copied, pass by reference
**/
Array::Array (const Array& original)
{
	size = original.size;
	data = new int [size];

	for (int i = 0; i < size; i++)	// deep copy
		data[i] = original.data[i];
}	// end method

/**
 * @brief       Destructor will free the memory allocated by array data
**/
Array::~Array()
{
	delete [] data;
}	// end method

/**
 * @brief       write() will display the information of the data array
 *
 * @param        sortName     	 the name of associated sort method
 * @param        orderName       the name of associated order
 * @param[out]   outfile    	 stream out
**/
void Array::write (const string& sortName, 
				   const string& orderName, 
				   ostream& outfile) const
{
	outfile << "\nThe sort name: " << sortName << endl;
	outfile << "The order name: " << orderName << endl;
	outfile << "The array info:\n";
	for (int i = 0; i < size; i++)
	{
		outfile << '\t' << data[i];
		// display every 10 elements per line.
		if (i % 10 == 9)
			outfile << endl;
	}	// end writing elements od data
	outfile << endl;
}	// end method

/**
 * @brief       getSize () will return the size of the array object
 *
 * @return  	the size of the array object
**/
int Array::getSize () const 
{
	return size;
}	// end method

/**
 * @brief       swap() method will swap two numbers.
 *
 * @param[out]       a     the first value
 * @param[out]       b     the second value
**/
void Array::swap (int& a, int& b)
{
	int temp = a;	// save first number
	a = b;			
	b = temp;
}	// end method

/**
 * @brief       The selection sort looks for the smallest value; when the end of the list is
*				reached, the smallest value is exchanged with the first element of the list.
*				After n-1 passes, n-1 elements will have been moved into their correct
*				positions, leaving the last and largest element in position by process 
*				of elimination
**/
pair<double,int> Array::selectionSort()
{
	pair<double,int> record;
	int comparision_count = 0;
	clock_t start = clock();	// save the starting time
	// for each position in the array
	for (int i = 0; i < size; i++)
	{
		// assume the smallest is the beginning position
		int smallest = data[i];
		int smallest_indx = i;
		// find smallest value in subsequent positions
		for (int j = i+1; j < size; j++)
		{	
			comparision_count++;
			if (smallest > data[j])
			{	
				// update the smallest value and index
				smallest = data[j];
				smallest_indx = j;
			}	// end if 
		}	// end for loop of finding smallest
		// swap smallest with current position in Array
		if (smallest_indx != i)
			swap (data[smallest_indx], data[i]);
	}	// end for loop of each position in the array
	clock_t finish = clock();	// save the ending time
	double time = (finish - start) * 1.0 / CLOCKS_PER_SEC;	// the time of sort execution.
	record.first = time;
	record.second = comparision_count;
	return record;
}	// end method

/**
 * @brief       The bubble sort moves the largest value to the end of the list 
 *				on the first pass; it finds and moves this large value by comparing 
 *				consecutive pairs of elements, swapping them when out of place.
 *				Each subsequent pass sees one more value put in the correct position.
 *				Should no consecutive pair of elements require a swap, the list is in order 
 *				and the bubble sort can stop early.
**/
pair<double,int> Array::bubbleSort()
{
	pair<double,int> record;
	int comparision_count = 0;
	clock_t start = clock();	// save the starting time

	int sink = 0;
	bool swapOccurred;
	do
	{
		// assume there is no swap occurred
		swapOccurred = false;
		// each pair of elements in an ever-shrinking list
		for (int pairIndx = 0; pairIndx < size - 1 - sink; pairIndx++)
		{
			comparision_count++;
			if (data[pairIndx] > data[pairIndx+1])
			{
				swap(data[pairIndx],data[pairIndx+1]);
				swapOccurred = true;
			}	// end if - swap occurs
		}	// end for loop
		sink++;
	}	// end do-while
	while (swapOccurred);	// a swap occured this pass

	clock_t finish = clock();	// save the ending time
	double time = (finish - start) * 1.0 / CLOCKS_PER_SEC;	// the time of sort execution.
	record.first = time;
	record.second = comparision_count;
	return record;
}	// end method

/**
 * @brief       insertionSort() puts sub-arrays of ever-increasing size in order 
 *				as it considers additional elements one at a time. 
 *              This process continues until each element of the list has been 
 *				dropped into its correct position relative to the others
**/
pair<double,int> Array::insertionSort()
{
	pair<double,int> record;
	int comparision_count = 0;
	clock_t start = clock();	// save the starting time

	for (int i = 1; i < size; i++)	// for each element after the first
	{
		// save this element
		int save_item = data[i];
		// scanning the previous elements
		int j = i-1;
		// while previous elements are bigger than saved element
		comparision_count++;
		while (j >= 0 && data[j] > save_item)
		{
			// move previous element forward one position
			data[j+1] = data[j];
			j--;
			comparision_count++;
		}
		// insert saved element in open hole
		data[j+1] = save_item;
	}	// end for loop

	clock_t finish = clock();	// save the ending time
	double time = (finish - start) * 1.0 / CLOCKS_PER_SEC;	// the time of sort execution.
	record.first = time;
	record.second = comparision_count;
	return record;
}	// end method

/**
 * @brief       modified_insertionSort() puts sub-arrays of ever-increasing size in order 
 *				as it considers additional elements one at a time. 
 *              This process continues until each element of the list has been 
 *				dropped into its correct position relative to the others
**/
pair<double,int> Array::modifiedInsertionSort()
{
	pair<double,int> record;
	int comparision_count = 0;
	clock_t start = clock();	// save the starting time

	for (int i = 1; i < size; ++i)	// for each element after the first
	{
		// save this element
		int save_item = data[i];
		// scanning the previous elements
		int j = i-1;
		// find location where selected sould be inseretd
    	pair<int,int> sub_record = binarySearch(save_item, 0, j);
    	int loc = sub_record.first;		// location where selected sould be inseretd
    	comparision_count += sub_record.second;	// the comparion count from binary search
    	// Move all elements after location to create space
    	while (j >= loc)
    	{
    		// move previous element forward one position
    		data[j + 1] = data[j];
    		j--;
    	}
    	// insert saved element in open hole
    	data[j+1] = save_item;
	}	// end for loop

	clock_t finish = clock();	// save the ending time
	double time = (finish - start) * 1.0 / CLOCKS_PER_SEC;	// the time of sort execution.
	record.first = time;
	record.second = comparision_count;
	return record;

}	// end method

/**
 * @brief       binarySearch() will find the right location for the consider element
 *				It supports the modified insertion sort above
**/
pair<int,int> Array::binarySearch(int value, int first, int last)
{
	pair<int,int> record;
	int comparision_count = 0;

	record.first = first;
	if (first <= last)
	{
		int mid = (first + last) / 2;
		comparision_count++;
		if (value < data[mid])
			record = binarySearch (value, first, mid - 1);
		else if (value > data[mid])
			record = binarySearch (value, mid + 1, last);
		else // value = data [mid]
			record.first = mid;
		comparision_count +=  record.second;
	}
	record.second = comparision_count;
	return record;
}	// end method

/**
 * @brief       The merge sort() public method will evoke a recursive private method
 *				which sort the whole array.
**/
pair<double,int> Array::mergeSort()
{
	pair<double,int> record;
	int comparision_count = 0;
	clock_t start = clock();	// save the starting time

	comparision_count = mergeSort (0, size-1);

	clock_t finish = clock();	// save the ending time
	double time = (finish - start) * 1.0 / CLOCKS_PER_SEC;	// the time of sort execution.
	record.first = time;
	record.second = comparision_count;
	return record;
}

/**
 * @brief      This merge sort function is a recursive private method with integer parameters first and last.
 *			   It will support the public method which sort the whole array.
 *
 * @param        first     		the first index of array
 * @param        last     		the last index of array
**/
int Array::mergeSort(int first, int last)
{
	int comparision_count = 0;
	if (last - first > 0)// more than one in subarray
	{
		int mid = (first + last) / 2;
		comparision_count = mergeSort (first, mid);
		comparision_count += mergeSort (mid+1, last);
		comparision_count += merge (first, last);
	}	// end if
	return comparision_count;
}	// end method

/**
 * @brief       The merge method always has two sorted lists and merge them into 
 *				one merge array in order. It is the private method which supports
 *				mergesort() function.
 *
 * @detail 		The array starts from the first and ends at the last index. It is
 *				considered as two sub arrays from first to middle and middle + 1 to last.
 *
 * @param        first     		the first index of array
 * @param        last     		the last index of array
**/
int Array::merge (int first, int last)
{
	int comparision_count = 0;

	int* merged = new int [last-first+1];
	int mid = (first + last) / 2;
	// sorted list #1 starts at first
	int indx_1 = first;
	// sorted list #2 starts at mid + 1
	int indx_2 = mid + 1;
	// set starting index of merge array
	int indx = 0;
	comparision_count++;
	while (indx_1 <= mid && indx_2 <= last) // both lists #1 & #2 are not exhausted
	{
		comparision_count++;
		if (data[indx_1] < data[indx_2])// data in list #1 < data in list #2
		{
			merged[indx] = data[indx_1]; // <- data in list #1
			indx_1++;	// increment index of first sub-array
		}
		else // data in list #1 >= data in list #2
		{
			merged[indx] = data[indx_2]; // <- data in list #2
			indx_2++;	// increment index of second sub-array
		}	// end else
		indx++;	// increment index of merge array
	}	// end while
	comparision_count++;
	while (indx_1 <= mid) // list #1 is not exhausted
	{
		comparision_count++;
		merged[indx] = data[indx_1]; // <- data in list #1 (since #2 is empty)
		indx++;			// increment index of merge array
		indx_1++;		// increment index of first sub-array
	}	// end while
	comparision_count++;
	while (indx_2 <= last) // list #2 is not exhausted
	{
		comparision_count++;
		merged[indx] = data[indx_2]; // <- data in list #2 (since #1 is empty)
		indx++;			// increment index of merge array
		indx_2++;		// increment index of second sub-array
	}	// end while
	for (int i = first; i <= last; i++)
	{
		// overwrite original positions with "merged"
		data[i] = merged[i-first];
	}
	delete [] merged;
	return comparision_count;
}	// end method

/**
 * @brief       quickSort public method will sort the whole array  
 *				based on a series of recursions which devided array into 2 parts
 *				associted to the lower and upper than the chosen pivot.
**/
pair<double,int> Array::quickSort()
{
	pair<double,int> record;
	int comparision_count = 0;
	clock_t start = clock();	// save the starting time

	if (size >= 2)	// there is no need to sort if the array contains only one element
	{
		comparision_count = quickSort (0, size-1); // kicks of a series of recursions.
	}	// end if

	clock_t finish = clock();	// save the ending time
	double time = (finish - start) * 1.0 / CLOCKS_PER_SEC;	// the time of sort execution.
	record.first = time;
	record.second = comparision_count;
	return record;
}	// end method

/**
 * @brief       The recursive portion of method quickSort should be defined as 
 *				a private method of class Array. 
 *				It accepts two integer parameters, first and last, and support the public
 *				quick sort method.
 *
 * @param        first     		the first index of array
 * @param        last     		the last index of array
**/
int Array::quickSort(int first, int last)
{
	int comparision_count = 0;

	if (first < last)
	{
		int pivot_index = last;
		int pivot_value = data[pivot_index];			// pivot value for easy reference
		
		pivot_index = first;							// start looking for "correct" location
		
		for (int i = first; i < last; ++i)				// by scanning the entire array
		{
			comparision_count++;
			if (data[i] < pivot_value)					// if value smaller than pivot is found
			{
				swap(data[i], data[pivot_index]);		// swap it into first partition
				pivot_index++;							// and move the dividing point
			}
		}
		
		swap(data[pivot_index], data[last]);			// swap pivot into its correct location
		int mid = pivot_index;
		
		comparision_count += quickSort(first, mid-1);
		comparision_count += quickSort(mid+1, last);
	}

	return comparision_count;

}	// end method

/**
 * @brief       quickSort public method will sort the whole array  
 *				based on a series of recursions which devided array into 2 parts
 *				associted to the lower and upper than the chosen pivot.
**/
pair<double,int> Array::randomizedQuickSort()
{
	pair<double,int> record;
	int comparision_count = 0;
	clock_t start = clock();	// save the starting time

	if (size >= 2)	// there is no need to sort if the array contains only one element
	{
		comparision_count = randomizedQuickSort (0, size-1); // kicks of a series of recursions.
	}	// end if

	clock_t finish = clock();	// save the ending time
	double time = (finish - start) * 1.0 / CLOCKS_PER_SEC;	// the time of sort execution.
	record.first = time;
	record.second = comparision_count;
	return record;
}	// end method

/**
 * @brief       The recursive portion of method quickSort should be defined as 
 *				a private method of class Array. 
 *				It accepts two integer parameters, first and last, and support the public
 *				quick sort method.
 *
 * @param        first     		the first index of array
 * @param        last     		the last index of array
**/
int Array::randomizedQuickSort(int first, int last)
{
	int comparision_count = 0;
	if (first < last)
	{
		int pivot_index = first + (rand() % (last-first+1));
														// random
		int pivot_value = data[pivot_index];			// pivot value for easy reference

		swap (data[pivot_index], data[last]);			// move pivot to end (out of the way)
		
		pivot_index = first;							// start looking for "correct" location
		
		for (int i = first; i < last; ++i)				// by scanning the entire array
		{
			comparision_count++;
			if (data[i] < pivot_value)					// if value smaller than pivot is found
			{
				swap(data[i], data[pivot_index]);		// swap it into first partition
				pivot_index++;							// and move the dividing point
			}
		}
		
		swap(data[pivot_index], data[last]);			// swap pivot into its correct location
		int mid = pivot_index;
		
		comparision_count += randomizedQuickSort(first, mid-1);			// quicksort everything left of division
		comparision_count += randomizedQuickSort(mid+1, last);				// quicksort everything right of division
	}
	
	return comparision_count;
}	// end method

/**
 * @brief       The heap sort uses the heap data structure 
 *				introduced in implementing the priority queue.
 *				Base on the max heap property, heap sorted is implemented.
**/
pair<double,int> Array::heapSort()
{
	pair<double,int> record;
	int comparision_count = 0;
	clock_t start = clock();	// save the starting time

	for (int i = size/2 - 1; i >= 0; i--) // max heapify
	{
		comparision_count = moveDownHeap (i, size-1);
	}
	
	for (int n = size-1; n >= 1; n--)
	{
		swap (data[0], data[n]);
		comparision_count += moveDownHeap (0, n-1);
	}	// end for

	clock_t finish = clock();	// save the ending time
	double time = (finish - start) * 1.0 / CLOCKS_PER_SEC;	// the time of sort execution.
	record.first = time;
	record.second = comparision_count;
	return record;

}	// end method

/**
 * @brief      moveDownHeap() should be defined as a private method of class Array.
 *			   It will consider the first (current) node and compare with its children to make
 *			   sure the max heap property be reserved.
 *
 * @param        first     			the first (current) node index 
 * @param        last     			the last current node index
**/
int Array::moveDownHeap (int first, int last)
{
	int comparision_count = 0;
	bool done = false;
	while (! done)
	{
		if (2*first + 1 > last)// no left child
			done = true;
		else // left child is present
		{
			// assume left child is larger
			int largest = 2*first + 1;
			if (2*first + 2 <= last)// right child is present
			{
				comparision_count++;
				if (data[2*first + 2] > data[2*first + 1]) // right child is larger than left
				{
					// mark right child as the larger
					largest = 2*first + 2;
				}	// end if
			}
			comparision_count++; 
			if (data[first] < data[largest]) // parent smaller than the larger child
			{
				swap (data[first], data[largest]);
				first = largest;
			}	// end if
			else // parent larger than the larger child
				done = true;
		}	// end else left child is present
	}	// end while loop
	return comparision_count;
}	// end method
/**
 *******************************************************************************
 * @file    main.cpp
 * @brief   
 *	The sorting algorithms are invoked in a very regular fashion. The initial array size is 100;  
 *	it is then alternated to produce the series 1000, 10,000 30,000.... For each size, three arrays are each
 *	called with data in three different orders. For each sorting algorithm, the array object is passed by value 
 *	to a sort-selection function.
 *
 * @remarks
 *      Course:        Computer Science 4713, Fall 2019
 *      Due Date:      Oct 14, 2019
 *      Instructor:    Prof. Huang
 *
 * @author  Pavan Kumar Reddy Sama
 * @date    Fri, Sep 20, 2019
 *******************************************************************************
**/

#include "Array.h"
#include <iomanip>
	using std::setw;
	using std::setprecision;
	using std::setiosflags;
	using std::ios;

// sort-selection function prototype
pair<double,int> sort (Array numbers, int sortType);
void testing (Array numbers, int sortType, int orderType);
void main_menu();
void sort_menu();

int main()
{
	srand (17);	// random seed
	
	main_menu();
	
	int choice;
	cout << "Enter the choice: ";
	cin >> choice;
	while (choice < 1 || choice > 4)
	{
		cout << "Invalid input\n";
		cout << "Enter the choice again: ";
		cin >> choice;
	}

	if (choice == 1)
	{
		double epsilon = 0.0005;
		int size = 100;			// starting size
		int sizeLimit = 30000;	// size limit
		int multiplier = 10;
		double maxTime = 0;
		double timeLimit = 60;
		do
		{
			// Title of table
			cout << setw(9) << size << setw(50) << "Random" << setw(20) << "Inorder" << setw(20) << "Reverse\n";
			for (int i = 0; i < 100; ++i)
				cout << '-';
			cout << endl;

			Array* a[3];	// allocate dynamic arrays
			a[0] = new Array (size, RANDOM);
			a[1] = new Array (size, IN_ORDER);
			a[2] = new Array (size, REVERSE_ORDER);
			// enum SORTS {SELECTION, BUBBLE, INSERTION, MODINSERTION, MERGE, QUICK, RANQUICK, HEAP};
			for (int sortIndx = SELECTION; sortIndx <= HEAP; sortIndx++)
			{
				cout << SORT_NAMES[sortIndx] << setw(25) << "Time:              ";
				// enum ORDERS {RANDOM, IN_ORDER, REVERSE_ORDER}
				for (int orderIndx = RANDOM; orderIndx <= REVERSE_ORDER; orderIndx++)
				{
					// pair<double,int> record = sort(*a[orderIndx], sortIndx);
					double time = sort(*a[orderIndx], sortIndx).first;
					if (maxTime < time)
						maxTime = time;
					if (time > epsilon)
						cout << setw(20) << setprecision(3) << setiosflags (ios::showpoint|ios::fixed)
							 << time;
					else	// avoid distracting display of decimals for very small times
						cout << setw(20) << "0";
				}	// end for orderIndx
				cout << endl;
				cout << "             " << setw(25) << "Comparision Count: ";
				for (int orderIndx = RANDOM; orderIndx <= REVERSE_ORDER; orderIndx++)
				{
					int comparision_count = sort(*a[orderIndx], sortIndx).second;
					cout << setw(20) << comparision_count;
				}	// end for orderIndx
				cout << endl;
				for (int i = 0; i < 19; ++i)
					cout << ' ';
				for (int i = 0; i < 81; ++i)
					cout << '-';
				cout << endl;
			}	// end for sortIndx
			cout << endl;
			// free dynamic arrays 
			for (int i = 0; i < 3; i++)
			{
				delete a[i];
			}	// end for loop of setting dynamic arrays free
			size *= multiplier;
			multiplier = (size==10000) ? 3 : 10;	// alternate multiplier
		}	// end do while
		while (maxTime < timeLimit && size <=sizeLimit);
	} // end choice == 1, time statistics
	else if (choice == 2)
	{
		;
	}
	else if (choice == 3)
	{
		int size = 100;
		Array* a[3];	// allocate dynamic arrays
		a[0] = new Array (size, RANDOM);
		a[1] = new Array (size, IN_ORDER);
		a[2] = new Array (size, REVERSE_ORDER);
		sort_menu();
		cout << "Enter the choice: ";
		cin >> choice;
		while (choice < 1 || choice > 9)
		{
			cout << "Invalid input\n";
			cout << "Enter the choice again: ";
			cin >> choice;

		}
		if (choice != 9)
		{
			// need to be fixed
			int sortIndx = choice -1;
			for (int orderIndx = RANDOM; orderIndx <= REVERSE_ORDER; orderIndx++)
			{	
				testing (*a[orderIndx], sortIndx, orderIndx);
			}
		}
	}
	
	cout << "Good bye!\n";
	return 0;
}	// end function

/**
 * @brief       sort() will take the array object (pass by value) and sort it
 *				with the selected sorting algorithm.
 *
 * @param        numbers     Array object which will be sorted
 * @param        sortType    the enum which evokes the type of sort method
 * @param   	 orderType   the enum which evokes the type of order of the array to be sorted.
 *
 * @return  the execution time of selected sorting method .
**/

pair<double,int> sort (Array numbers, int sortType)
{
	pair<double,int> record;
	switch (sortType)
	{
		case SELECTION:
			record = numbers.selectionSort();
			break;
		case BUBBLE:
			record = numbers.bubbleSort();
			break;
		case INSERTION:
			record = numbers.insertionSort();
			break;
		case MODINSERTION:
			record = numbers.modifiedInsertionSort();
			break;
		case MERGE:
			record = numbers.mergeSort();
			break;
		case QUICK:
			record = numbers.quickSort();
			break;
		case RANQUICK:
			record = numbers.randomizedQuickSort();
			break;
		case HEAP:
			record = numbers.heapSort();
			break;
	} // end switch
	return record;
}	// end function sort

void testing (Array numbers, int sortType, int orderType)
{
	cout << "\nBefore sorting: \n";
	numbers.write (SORT_NAMES[sortType], ORDER_NAMES[orderType]);

	switch (sortType)
	{
		case SELECTION:
			numbers.selectionSort();
			break;
		case BUBBLE:
			numbers.bubbleSort();
			break;
		case INSERTION:
			numbers.insertionSort();
			break;
		case MODINSERTION:
			numbers.modifiedInsertionSort();
			break;
		case MERGE:
			numbers.mergeSort();
			break;
		case QUICK:
			numbers.quickSort();
			break;
		case RANQUICK:
			numbers.randomizedQuickSort();
			break;
		case HEAP:
			numbers.heapSort();
			break;
	} // end switch
	
	cout << "\nAfter sorting: \n";
	numbers.write (SORT_NAMES[sortType], ORDER_NAMES[orderType]);
}

void main_menu()
{
	cout << "******************************************" << endl; 
	cout << "****          Project 1: Menu         ****" << endl;
	cout << "*  1. Time execution statistics          *" << endl;
	cout << "*  2. Comparision execution statistics   *" << endl;
	cout << "*  3. Testing sort                       *" << endl;
	cout << "*  4. Exit                               *" << endl;
	cout << "******************************************" << endl; 
}

void sort_menu()
{
	cout << "******************************************" << endl; 
	cout << "****          Sorting menu            ****" << endl;
	cout << "*  1. Selection Sort                     *" << endl;
	cout << "*  2. Bubble Sort                        *" << endl;
	cout << "*  3. Insertion Sort                     *" << endl;
	cout << "*  4. Modified Insertion Sort            *" << endl;
	cout << "*  5. Merge Sort                         *" << endl;
	cout << "*  6. Quick Sort                         *" << endl;
	cout << "*  7. Randomized Quick Sort              *" << endl;
	cout << "*  8. Heap Sort                          *" << endl;
	cout << "*  9. Exit                               *" << endl;
	cout << "******************************************" << endl; 
}
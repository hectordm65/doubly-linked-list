//Test client for CSC 2431 Homework 1.
//DO NOT MODIFY

#include <iostream>
using namespace std;

#include "sortedList.h"

//Client function to print a list of listItemType
//Parameters: the list to print (posList)
//Returns: nothing
void print(doublyLinkedList list)
{
	for (int i = 1; i <= list.getLength(); i++)
	{
		listItemType x = *new listItemType;
		list.retrieveElement(i, x);
		cout << x << endl;
	}
}

//prototypes void print(doublyLinkedList list);
int main()
{
	doublyLinkedList first;

	//create a list with 6 elements for testing
	first.insertElement(20);
	first.insertElement(10);
	first.insertElement(30);
	first.insertElement(40);
	first.insertElement(25);
	first.insertElement(5);

	int pos;

	first.locateElement(30, pos);

	first.deleteElement(pos);

	cout << "first, printed with client print:  " << endl;

	print(first);

	//create a copy of 5-element list

	doublyLinkedList second(first);
	//test all 3 cases for delete
	second.deleteElement(1);
	second.deleteElement(4);
	second.deleteElement(2);
	cout << "\nsecond, printed with client print:  " << endl;
	print(second);

	//test copy constructor 
	doublyLinkedList third(first);

	//test == and !=
	cout << boolalpha;
	cout << "\ntesting == " << endl;
	cout << (first == first) << endl; //this should be true
	cout << (first == second) << endl; //this should be false
	cout << (first == third) << endl; //this should be true
	cout << "\ntesting != " << endl;
	cout << (first != first) << endl; //this should be false
	cout << (first != second) << endl; //this should be true
	cout << (first != third) << endl; //this should be false

	//test print functions
	cout << "\nTesting printFront on first: " << endl;
	first.printFront();
	cout << "\nTesting printBack on first: " << endl;
	first.printBack();
	
	//test reverse
	first.reverse();
	
	cout << "\nTesting printFront on first after reverse: " << endl;
	first.printFront(); //this should be in the reverse order of the original (printing front of reverse)
	cout << "\nTesting printBack on first after reverse: " << endl;
	first.printBack(); //this should be the same as the original (printing reverse of reverse)
	return 0;
}

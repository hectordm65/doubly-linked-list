// Implementation file for sortedList, a pointer-based by-position list of type
// specified in header.

#include "sortedList.h"     // header file
#include <cstddef>		// for NULL
#include <cassert>     // for assert()
#include <iostream>

//using namespace std;

doublyLinkedList::doublyLinkedList()	// Default Constructor
: size(0), head(NULL), tail(NULL)
{
	head = NULL;
	tail = NULL;
}


doublyLinkedList::~doublyLinkedList()	// Destructor
{
	bool success;

	while (!isEmpty())
	{
	success = deleteElement(1);  // Repeatedly delete item 1
	}
}


bool doublyLinkedList::isEmpty() const
{
	return (size == 0);
}


int doublyLinkedList::getLength() const
{
	return size;
}


// Copy Constructor
doublyLinkedList::doublyLinkedList(const doublyLinkedList& original)
: size(original.size)
{
	if (original.head == NULL)
	{
		head = NULL;  // original list is empty
		tail = NULL; // ensures that the whole list will be empty
	}
	else
	{
		// copy first node
		head = new listNode;
		tail = new listNode;
		
		assert(head != NULL);  // check allocation
		assert(tail != NULL);  // check allocation

		head->item = original.head->item;

		head->previous = NULL; //is this needed?

		tail->previous = original.tail->previous;
		tail->item = original.tail->item;
		tail->next = NULL;

		// copy rest of list
		listNode *newPtr = head;  // new list pointer

		// newPtr points to last node in new list 
		// origPtr points to nodes in original list
		for (listNode *origPtr = original.head->next; origPtr != NULL; origPtr = origPtr->next)
		{
			newPtr->next = new listNode;
			newPtr->previous = new listNode;
			assert(newPtr->next != NULL && newPtr->previous != NULL);

			if (newPtr->previous != NULL)
			{
				newPtr->previous = newPtr;
			}

			newPtr = newPtr->next;
			
			newPtr->item = origPtr->item;


		}

		newPtr->previous = newPtr;
		newPtr->next = NULL;
	}

}


// Locates a specified node in a linked list
// Parameters: the number of the desired node (starting at 1, an int)
// Returns: Returns a pointer to the desired node, or NULL if position out of range.
doublyLinkedList::listNode *doublyLinkedList::ptrTo(int position) const
{
	if ((position < 1) || (position > getLength()))
		return NULL;

	else  // count from the beginning of the list
	{
		listNode *cur = head;

		for (int skip = 1; skip < position; ++skip)
			cur = cur->next;

		return cur;
	}
}


bool doublyLinkedList::retrieveElement(int position, listItemType& dataItem) const
{
	bool success = ((position >= 1) && (position <= getLength()));

	if (success)
	{
		// get pointer to node, then data in node
		listNode *cur = ptrTo(position);
		if (cur->item != NULL)
		{
			dataItem = cur->item;
		}
		
	}

	return success;
}



// Iterative SortedList Insert
void doublyLinkedList::insertElement(listItemType newItem)
{
	listNode *prev = NULL;
	listNode *cur = head;

	while ((cur != NULL) && (newItem > cur->item))
	{
		prev = cur;
		cur = cur->next;
	}

	listNode *newPtr = new listNode;
	newPtr->item = newItem;
	newPtr->next = cur;
	newPtr->previous = prev;


	if (prev == NULL)
	{
		head = newPtr;
		if (head->next != NULL)
		{
			cur->previous = head;
		}
	}
	else if (cur != NULL && prev != NULL)
	{
		prev->next = newPtr;
		cur->previous = newPtr;
	}
	else if (cur == NULL)
	{
		tail = newPtr;
		prev->next = tail;
	}

	size++;
}


void doublyLinkedList::locateElement(listItemType key, int& position)
{
	listNode *cur = head;
	
	position = 1;

	while (cur != NULL && cur->item != key)
	{
		cur = cur->next;
		position++;
	}

	if (cur == NULL)
		position = -1;
}


bool doublyLinkedList::deleteElement(int position)
{

	listNode *cur = new listNode;

	bool success = ((position >= 1) && (position <= getLength()));

	if (success)
	{
		--size;

		if (position == 1)
		{
			// delete the first node from the list
			cur = head;  // save pointer to node
			head = head->next;
			//head->previous = NULL;
		}
		else
		{
			listNode *prev = ptrTo(position - 1);

			// delete the node after the node 
			//    to which Prev points

			cur = prev->next;  // save pointer to node
			prev->next = cur->next;
			if (cur->next == tail)
			{
				tail->previous = prev;
			}
			else
			{
				cur->previous = prev;
			}
		}

		// return node to system
		cur->next = NULL;
		cur->previous = NULL;
		delete cur;
		cur = NULL;
	}

	return success;
}

bool doublyLinkedList::operator== (const doublyLinkedList& right)
{
	//shortcut in case comparing same two sortedLists
	if (&right == this)
		return true;

	//check sizes are the same
	if (getLength() != right.getLength())
		return false;

	//temporary variables for comparison
	listItemType mine;
	listItemType theirs;

	//compare each element
	for (int i = 1; i <= getLength(); i++)
	{
		//use public methods to get each element
		retrieveElement(i, mine);
		right.retrieveElement(i, theirs);

		//return false after any mismatch
		if (mine != theirs)
			return false;
	}

	//if code gets here, all elements must be the same
	return true;
}

bool doublyLinkedList::operator!= (const doublyLinkedList& right)
{
	return !(*this == right);

}



void doublyLinkedList::printFront()
{
	for (int i = 1; i <= this->getLength(); i++)
	{
		listItemType x;
		this->retrieveElement(i, x);
		
		std::cout << x << std::endl;
	}
}

void doublyLinkedList::printBack()
{
	int listLength = this->getLength();



	for (int i = listLength; i > 0; i--)
	{
		listItemType x;
		this->retrieveElement(i, x);

		std::cout << x << std::endl;
	}
}

void doublyLinkedList::reverse()
{
	int listLength = this->getLength();

	listNode *cur = new listNode;

	assert(cur != NULL);

	for (listNode *origPtr = tail->previous; origPtr != NULL; origPtr = origPtr->previous)
	{
		cur->next = new listNode;
		cur->previous = new listNode;

		assert(cur->next != NULL && cur->previous != NULL);

		cur->previous = cur;
		cur = cur->next;

		cur->item = origPtr->item;
	}
}
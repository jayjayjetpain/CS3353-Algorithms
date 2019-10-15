#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

using namespace std;

/*  LinkedList is a user-defined doubely linked-list that uses a templated-node structure
 *  so that any data type can be used as the data for the node. Contains inserting and removing
 *  from anywhere in the list as well as special functions to add/remove specifically at the end
 *  of the list. This class utilizes a user-defined iterator (Iterator) which has limited
 *  functionality such as assignment, incrementation, dereferencing, != comparison and node access.
 *  Using the Iterator, any node can be accessed in a more time-effcient manner than iterating
 *  throuhg using solely node pointers
 */

template<typename A>
struct LLNode
{
	LLNode* next;
	LLNode* prev;
	A data;
};

template<typename A>
class LinkedList
{
private:
	LLNode<A>* head;
	LLNode<A>* tail;
	int length;

public:
	LinkedList();
	LinkedList(const LinkedList<A>&);
	~LinkedList();
	LinkedList<A>& operator=(const LinkedList<A>&);
	LLNode<A>& operator[](int);
	void insert(int, A);
	void push_back(A);
	void remove(int);
	void pop_back();
	LLNode<A>* first();
	LLNode<A>* last();
	bool isEmpty();
	int getLength();

	//iterator sub-class for a LinkedList
	class Iterator : public iterator<forward_iterator_tag, A>
	{
		friend class LinkedList<A>;
	private:
		LLNode<A>* nodePtr;
		Iterator(LLNode<A>* newPtr) : nodePtr(newPtr) {}

	public:
		Iterator() : nodePtr(nullptr) {}

		//sets this iterator equal to another, already-created one
		Iterator& operator=(const Iterator& source)
		{
			nodePtr = source.nodePtr;
			return *this;
		}

		//using the indirection operator, "dereferance" the iterator by returning its data
		A& operator*() const
		{
			//handles invalid dereferances
			if (nodePtr == nullptr)
			{
				throw runtime_error("Invalid dereference (*)");
			}
			return nodePtr->data;
		}

		//using the arrow operator, allow access to the iterator's node's data
		A& operator->() const
		{
			//handles invalid dereferances
			if (nodePtr == nullptr)
			{
				throw runtime_error("Invalid dereference (->)");
			}
			return nodePtr->data;
		}

		//moves the pointer to the next node in the list (pre-increment)
		Iterator& operator++()
		{
			//ensures no segmentation faults due to incrementing
			if (nodePtr == nullptr)
			{
				throw runtime_error("Out-of-bounds increment (pre)");
			}
			nodePtr = nodePtr->next;
			return *this;
		}

		//moves the pointer to the next node in the list (post-increment)
		Iterator& operator++(int)
		{
			//ensures no segmentation faults due to incrementing
			if (nodePtr == nullptr)
			{
				throw runtime_error("Out-of-bounds increment (post)");
			}
			Iterator temp(*this);
			nodePtr = nodePtr->next;
			return temp;
		}

		//moves the pointer to the next node in the list multiple nodes at a time
		Iterator& operator+=(int addNum)
		{
			for (int i = 0; i < addNum; i++)
			{
				this->operator ++();
			}
			return *this;
		}

		//compares this iterator to another and sees if they aren't the same
		bool operator!=(const Iterator& temp) const
		{
			return nodePtr != temp.nodePtr;
		}

		//allows access the node's data from other places
		LLNode<A>* getNode()
		{
			return nodePtr;
		}

	};

	Iterator begin() const;
	Iterator end() const;
	int search(A);
};


template<typename A>
LinkedList<A>::LinkedList()
{
	head = nullptr;
	tail = nullptr;
	length = 0;
}

template<typename A>
LinkedList<A>::LinkedList(const LinkedList<A>& source)
{
	head = tail = nullptr;
	length = 0;
	for (typename LinkedList<A>::Iterator i = source.begin(); i != nullptr; i++)
	{
		push_back(*i);
	}
}

template<typename A>
LinkedList<A>::~LinkedList()
{
	if (head == nullptr) { return; }
	while (head->next != nullptr)
	{
		LLNode<A>* temp = head;
		head = head->next;
		delete temp;
	}
	delete head;
}

//sets this LinkedList equal to one passed in
template<typename A>
LinkedList<A>& LinkedList<A>::operator=(const LinkedList<A>& source)
{
	if (this != &source) //as long as the passed-in Ll isn't itself
	{
		//deletes the contents if any in this Ll
		while (head != nullptr && head->next != nullptr)
		{
			LLNode<A>* temp = head;
			head = head->next;
			delete temp;
		}
		delete head;

		//then using iterator traversal, copies the contents from the passed-in one
		for (typename LinkedList<A>::Iterator i(source.begin()); i != nullptr; i++)
		{
			push_back(i.nodePtr->data);
		}

		//sets data members equal to that of the passed-in one THAT MESSED UP MY PROGRAM SBFGEIU
		//head = source.begin().nodePtr;
		//tail = source.end().nodePtr;
		//length = source.length;
	}
	return *this;
}

//access the node at position "index" by moving through it (not recommended)
template<typename A>
LLNode<A>& LinkedList<A>::operator[](int index)
{
	//ensures proper access
	if (index >= length || index < 0)
	{
		throw runtime_error("Index out of bounds");
	}
	//iterates to the proper node
	LLNode<A>* temp = first();
	for (int i = 0; i < index; i++)
	{
		temp = temp->next;
	}
	return *temp;
}

//inserts a node with data "addData" to the position passed in and handles data members
template<typename A>
void LinkedList<A>::insert(int loc, A addData)
{
	LLNode<A>* temp = new LLNode<A>();  //new node for insertion
	temp->data = addData;

	if (isEmpty())   //if the list is already empty
	{
		temp->next = head;  //the new node is both the head and the tail
		temp->prev = head;
		head = temp;
		tail = temp;
		length++;
	}
	else if (loc <= 0) //addition at 0
	{
		if (loc < 0) //handles negative insertion by placing it at the beginning
		{
			cout << "Tried to enter below 0. Entering at beginning." << endl;
		}
		temp->next = head;
		temp->prev = head->prev;
		head->prev = temp;
		head = temp;
		length++;
	}
	else if (loc >= length)  //addition to the end
	{
		if (loc > length) //handles insertion of indecies past the length by putting them at the end
		{
			cout << "Tried to enter past length. Entering at end." << endl;
		}
		temp->prev = tail;
		temp->next = tail->next;
		tail->next = temp;
		tail = temp;
		length++;
	}
	else    //else places it at the proper location
	{
		LLNode<A>* trace = first();
		for (int i = 0; i < loc - 1; i++)
		{
			trace = trace->next;
		}
		trace->next->prev = temp;
		temp->next = trace->next;
		temp->prev = trace;
		trace->next = temp;
		length++;
	}
}

//adds a new node to the end of the list
template<typename A>
void LinkedList<A>::push_back(A addData)
{
	LLNode<A>* temp = new LLNode<A>();
	temp->data = addData;

	if (head == nullptr) //if the list is empty
	{
		temp->next = head;  //the new node is the head and tail
		temp->prev = head;
		head = temp;
		tail = temp;
		length++;
	}
	else //else puts the node at the tail position nad reassigns tail
	{
		temp->prev = tail;
		temp->next = tail->next;
		tail->next = temp;
		tail = temp;
		length++;
	}
}

//removes a node from the specified location
template<typename A>
void LinkedList<A>::remove(int loc)
{
	if (isEmpty())   //if the list is empty, there is nothing to remove
	{
		throw runtime_error("Remove: List already empty");
	}
	if (loc < 0 || loc >= length)    //can't remove any item out of bounds
	{
		throw runtime_error("Remove: Tried to remove element out of bounds");
	}

	//traces to the node to be removed
	LLNode<A>* trace = first();
	for (int i = 0; i < loc; i++)
	{
		trace = trace->next;
	}
	if (loc == 0)    //if wanting to remove the front
	{
		if (length == 1) //if the front is the only element then the list will be empty
		{
			head = tail = nullptr;
			delete trace;
			length--;
			return;
		}
		//else just make the second node the front and delete the first
		trace->next->prev = nullptr;
		head = trace->next;
		delete trace;
		length--;
	}
	else if (loc == length - 1)    //if wanting to the remove the back
	{
		trace->prev->next = nullptr;    //make the second to last element the back
		tail = trace->prev;
		delete trace;   //and delete the back
		length--;
	}
	else    //else if its an element in the middle
	{
		trace->prev->next = trace->next;    //remove it from the pointers of its next and prev nodes
		trace->next->prev = trace->prev;
		delete trace;   //and delete it
		length--;
	}
}

//removes the back node of the list
template<typename A>
void LinkedList<A>::pop_back()
{
	if (isEmpty())   //can't remove the back if there are no nodes
	{
		throw runtime_error("Can't pop back of empty list");
	}

	LLNode<A>* trace = last();
	if (length == 1) //if the back is the front as well (only one element)
	{
		head = tail = nullptr;  //then maek the list empty
		delete trace;
		length--;
		return;
	}
	else    //else just make the second to last node the back and delete the back
	{
		trace->prev->next = nullptr;
		tail = trace->prev;
		delete trace;
		length--;
	}
}

//returns a node pointer to the first node in the list
template<typename A>
LLNode<A>* LinkedList<A>::first()
{
	return head;
}

//returns a node pointer to the last node in the list
template<typename A>
LLNode<A>* LinkedList<A>::last()
{
	return tail;
}

//checks whether the list has nay nodes in it
template<typename A>
bool LinkedList<A>::isEmpty()
{
	if (head == nullptr && tail == nullptr)
	{
		return true;
	}
	return false;
}

//returns the length of the list (i.e. the node number)
template<typename A>
int LinkedList<A>::getLength()
{
	return length;
}

//using the defined iterator class, get an iterator pointing to the beginning of the list
template<typename A>
typename LinkedList<A>::Iterator LinkedList<A>::begin() const
{
	return Iterator(head);
}

//using the defined iterator class, get an iterator pointing to the end of the list
template<typename A>
typename LinkedList<A>::Iterator LinkedList<A>::end() const
{
	return Iterator(tail);
}

//using the defined iterator class, search the list for a key and return its index
template<typename A>
int LinkedList<A>::search(A key)
{
	int trace = 0;
	//using iterator traversal, go through the list and check for the key
	for (typename LinkedList<A>::Iterator i(begin()); i != nullptr; i++)
	{
		if (i.nodePtr->data == key)
		{
			return trace;
		}
		trace++;
	}
	return -1;
}

#endif // LINKEDLIST_H
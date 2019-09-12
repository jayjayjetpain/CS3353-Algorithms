#pragma once
#ifndef SORTALGOS_H
#define SORTALGOS_H

#include <iostream>
#include <string>
#include <vector>

/* SortAlgos holds the implementation of the three main sorts of the lab - Bubble Sort, Insertion Sort, and Merge Sort - as well as their
 * "inner" functions that need to be called to execute them. This class is not a sub-class of Sort or any other class; instead, its header
 * file is included in Sort.cpp so that Sort's function pointer can use the memory locations of the (static) sort functions in this file's
 * definition to dynamically assign/run the methods without directly interacting with that class (concrete implementation decoupled from 
 * the interface of Algorithms -> Sort as per the Strategy design pattern)
 */

template<typename T>
class SortAlgos  {
public:
    static void BubbleSort(std::vector<T>&);
    static void MergeSort(std::vector<T>&);
    static void InsertionSort(std::vector<T>&);
    
private:
    static void swap(T*, T*);
    static void mergeSort(std::vector<T>&, int, int);
    static void merge(std::vector<T>&, int, int, int);

};

//templated bubble sort, static for better memory management and access via the function pointer in Sort class
template<typename T>
void SortAlgos<T>::BubbleSort(std::vector<T>& list)
{
	bool swapped = true;	//boolean to check if the list is iterated with/without swapping values
	int n = list.size();	//local variable of the list's size

	//until there is no swapping in an iteration
	while(swapped == true)
	{
		swapped = false;	//sets to false since no swap has happened at the beginning
		//loops through the list, swapping values when needed
		for (int i = 0; i < (n - 1); i++)
		{
			//only swap values if the current value is larger than the one that proceeds it
			if (list.at(i) > list.at(i+1))
			{
				//calls member static function swap which takes the memory addressed of the two elements to swap, and swaps their places
				swap(&list.at(i), &list.at(i+1));
				swapped = true;		//if we make it here then something has been swapped
			}
		}
		//after every iteration through the list, the last element in the list will be the largest value, so we can lower our loop
		//constraints each time to go for faster sorting
		n = n - 1;
	}
}

//templated public version of the merge sort algorithm used as the static method called by the function pointer
template<typename T>
void SortAlgos<T>::MergeSort(std::vector<T>& list)
{
	//calls the private version of merge sort which takes a front and end index of the vector as well as the vector itself
    mergeSort(list,0,list.size()-1);
}

//the "true" recursive function of merge sort called by the public function and itself to mimic the division provcess of Merge Sort
template<typename T>
void SortAlgos<T>::mergeSort(std::vector<T>& list, int left, int right)
{
	//if the left index is less than the right index, i.e. the sub-vector size > 1, then we can still divide further
    if(left < right)
    {
        int mid = (left + right)/2;	//finds the middle of the current sub-vector

		//divies the left side from the left to the middle value and the right side from one past the middle to the right
        mergeSort(list, left, mid);
        mergeSort(list, mid + 1, right);

		//after dividing into both sub-vector, call this merge function to merge and sort the values back together
        merge(list, left, mid, right);
    }
}

//templated Insertion Sort implementation, static for better memory management and to be called by Sort's function pointer
template<typename T>
void SortAlgos<T>::InsertionSort(std::vector<T>& list)
{
    int i,j;
    T comp;
	//loops from the 2nd element to the end
    for(i = 1; i < list.size(); i++)
    {
        comp = list.at(i);	//sets the key value to be compared against
        j = i - 1;	//sets index j for the copying of values in the while loop

		//until j is either below 0 or the value at j is a smaller value than the key value...
        while(j >= 0 && list.at(j) > comp)
        {
            list.at(j+1) = list.at(j);	//move the values larger than the key to the left of it
            j--;
        }
		list.at(j + 1) = comp;	//and put the key in its proper, sorted place
    }
}

//sub-function for Bubble Sort, static since the main method is; swaps two values using their memory addresses
template<typename T>
void SortAlgos<T>::swap(T* one, T* two)
{
    T temp = *one;
    *one = *two;
    *two = temp;
}

//merging function called in each recursion of merge sort to re-unite the sub-vectors and sort them along the way; based loosely on model developed in class
template<typename T>
void SortAlgos<T>::merge(std::vector<T>& list, int left, int mid, int right)
{
    std::vector<T> t1;	//temp vector for comparisons

	//makes local varibles for left and right (not parameters; in parameter, left = start, right = end)
    int i = left;
	int j = mid + 1;
	
	//until left and right go past their left and right sub-vectors
    while(i <= mid && j <= right)
    {
		//compare the values at left/right to know which to push to the temp vector
        if(list.at(i) <= list.at(j))
        {
            t1.push_back(list.at(i));	//if i (left) is less, then push it to the temp vector and increment it
            i++;
        }
        else
        {
            t1.push_back(list.at(j));	//if j (right) is less, then push it to the temp vector and increment it
            j++;
        }
    }

	//copy the remaining values to the temp array
    while(i <= mid)
    {
        t1.push_back(list.at(i));	//if the loop was terminated by j going past left (end) then copy the rest of the first sub-vector
        i++;
    }
    while(j <= right)
    {
        t1.push_back(list.at(j));	//if the loop was terminated by i going past mid (middle) then copy the rest of the first sub-vector
        j++;
    }

	//then recopy the values that are now in the proper order in the temp vector back to the actual vector to finish sorting the sub-vectors
	for (i = left; i <= right; i += 1)
	{
		list.at(i) = t1.at(i - left);
	}
}

#endif // SortAlgos_H
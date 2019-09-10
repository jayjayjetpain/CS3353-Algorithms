#pragma once
#ifndef SORTALGOS_H
#define SORTALGOS_H

#include <iostream>
#include <string>
#include <vector>

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

template<typename T>
void SortAlgos<T>::BubbleSort(std::vector<T>& list)
{
    int swapNum = 1;
    int j = 0;
    int k = 1;

    while(swapNum != 0)
    {
        swapNum = 0;
        for(int i = 0; i < list.size()-1; i++)
        {
            if(list.at(i) > list.at(i+1))
            {
                swap(&list.at(i), &list.at(i+1));
                swapNum++;
            }
//            j++;
//           k++;
        }
    }
}

template<typename T>
void SortAlgos<T>::MergeSort(std::vector<T>& list)
{
    mergeSort(list,0,list.size()-1);
}

template<typename T>
void SortAlgos<T>::mergeSort(std::vector<T>& list, int left, int right)
{
    if(left < right)
    {
        int mid = (left + right)/2;

        mergeSort(list, left, mid);
        mergeSort(list, mid + 1, right);

        merge(list, left, mid, right);
    }
}

template<typename T>
void SortAlgos<T>::InsertionSort(std::vector<T>& list)
{
    int i,j;
    T start;
    for(i = 1; i < list.size(); i++)
    {
        start = list.at(i);
        j = i - 1;

        while(j >= 0 && list.at(j) > start)
        {
            list.at(j+1) = list.at(j);
            j--;
        }
        list.at(j+1) = start;
    }
}

template<typename T>
void SortAlgos<T>::swap(T* one, T* two)
{
    T temp = *one;
    *one = *two;
    *two = temp;
}

template<typename T>
void SortAlgos<T>::merge(std::vector<T>& list, int left, int mid, int right)
{
    std::vector<T> t1;

    int i = left;
	int j = mid + 1;
    int k = 0;
    while(i <= mid && j <= right)
    {
        if(list.at(i) <= list.at(j))
        {
            t1.push_back(list.at(i));
            i++;
        }
        else
        {
            t1.push_back(list.at(j));
            j++;
        }
        k++;
    }

    while(i <= mid)
    {
        t1.push_back(list.at(i));
        i++;
        k++;
    }
    while(j <= right)
    {
        t1.push_back(list.at(j));
        j++;
        k++;
    }

	for (i = left; i <= right; i += 1)
	{
		list.at(i) = t1.at(i - left);
	}

}

#endif // SortAlgos_H
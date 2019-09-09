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
    void swap(T*, T*);
    void MergeSort(std::vector<T>&, int, int);
    void merge(std::vector<T>&, int, int, int);

};

template<typename T>
static void SortAlgos<T>::BubbleSort(std::vector<T>& list)
{
    int swapNum = 1;
    int j = 0;
    int k = 1;

    while(swapNum != 0)
    {
        swapNum = 0;
        for(int i = 0; i < list.size()-1; i++)
        {
            if(list.at(k) > list.at(j))
            {
                swap(list.at(j), list.at(k));
                swapNum++;
            }
            j++;
            k++;
        }
    }
}

template<typename T>
static void SortAlgos<T>::MergeSort(std::vector<T>& list)
{
    MergeSort(list,0,list.size()-1);
}

template<typename T>
void SortAlgos<T>::MergeSort(std::vector<T>& list, int left, int right)
{
    if(left < right)
    {
        int mid = (left + right - 1)/2;

        MergeSort(list, left, mid);
        MergeSort(list, mid + 1, right);

        merge(list, left, mid, right);
    }
}

template<typename T>
static void SortAlgos<T>::InsertionSort(std::vector<T>& list)
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
        list.at(j) = start;
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
    int center = (mid - left + 1);
    int end = (right - mid);

    std::vector<T> t1,t2;

    for(int z = 0; z < center; z++)
    {
        t1.at(z) = list.at(left + z);
    }
    for(int y = 0; y < ; y++)
    {
        t2.at(y) = list.at(mid + 1 + y);
    }

    int i,j = 0;
    int k = 1;
    while(left <= center && right <= end)
    {
        if(t1.at(i) < t2.at(j))
        {
            list.at(k) = t1.at(i);
            i++;
        }
        else
        {
            list.at(k) = t2.at(j);
            j++;
        }
        k++;
    }

    while(i <= center)
    {
        list.at(k) = t1.at(i);
        i++;
        k++;
    }
    while(j <= end)
    {
        list.at(k) = t2.at(j);
        j++;
        k++;
    }

}

#endif // SortAlgos_H
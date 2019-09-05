#pragma once
#ifndef SORTALGOS_H
#define SORTALGOS_H

#include "Sort.h"
#include <iostream>
#include <string>
#include <vector>

class SortAlgos : Sort  {
public:
    static void BubbleSort(std::vector<int>&);
    static void MergeSort(std::vector<int>&);
    static void InsertionSort(std::vector<int>&);

private:


};

#endif // SortAlgos_H
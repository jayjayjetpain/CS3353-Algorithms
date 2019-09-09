#pragma once
#ifndef SORT_H
#define SORT_H

#include "Algorithms.h"
#include <iostream>
#include <string>
#include <vector>

class Sort : Algorithms  {
public:
    Sort();
    virtual void Load(std::string&);
    virtual void Execute();
    virtual void Display();
    virtual void Stats();
    virtual void Select(int);
    virtual void Save(std::string&);
    virtual void Configure();

private:
    void(*algo)(std::vector<int>&) = nullptr;
    //static std::vector<void(*)(std::vector<int>&)> algorithms;
    std::vector<int> numList;

    std::chrono::duration<double> time_span;
    std::string currAlgo;
    int totElements;

    std::ofstream out;
};

#endif // Sort_H
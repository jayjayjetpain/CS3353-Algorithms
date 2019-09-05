#pragma once
#ifndef SORT_H
#define SORT_H

#include "Algorithms.h"
#include <iostream>
#include <string>
#include <vector>

class Sort : Algorithms  {
public:
    virtual void Load(std::string&);
    virtual void Execute();
    virtual void Display();
    virtual void Stats();
    virtual void Select();
    virtual void Save();
    virtual void Configure();

private:
    static std::vector<void(*)(std::vector<int>&)> algorithms;

};

#endif // Sort_H
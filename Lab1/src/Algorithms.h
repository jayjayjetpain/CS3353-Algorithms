#pragma once
#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <iostream>
#include <string>

class Algorithms   {
public:
    virtual void Load(std::string) = 0;
    virtual void Execute() = 0;
    virtual void Display() = 0;
    virtual void Stats() = 0;
    virtual void Select(int) = 0;
    virtual void Save(std::string) = 0;
    virtual void Configure() = 0;

private:
    enum SortingAlgo {
        BUBBLE = 0,
        MERGE,
        INSERTION,
        LAST
    };

};

#endif // ALGORITHMS_H
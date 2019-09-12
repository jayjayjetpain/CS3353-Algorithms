#pragma once
#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <iostream>
#include <string>

/* Abstract Base class - utilized as the "Strategy class" that will be inherited and fully implemented and then accessed
 * by the main method through the use of polymorphism with a base class pointer with the address of a derived class. Holds
 * functionality to load data sets from files, execute algorithms, display results of the algorithms, display stats of the
 * algorithms' procedures, select a type of algorithm (e.g. a sort/search) dynamically, save the results and stats of the
 * algorithms to an output file, and then configure if needed.
 */

class Algorithms   {
public:
    virtual void Load(std::string) = 0;
    virtual void Execute() = 0;
    virtual void Display() = 0;
    virtual void Stats() = 0;
    virtual void Select(int) = 0;
    virtual void Save(std::string) = 0;
    virtual void Configure() = 0;

};

#endif // ALGORITHMS_H
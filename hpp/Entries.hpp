#ifndef ENTRIES_HPP
#define ENTRIES_HPP

#include "Entry.hpp"

class Entries
{
public:
    Entries();
    Entries(const Entries& other);
    Entries& operator=(const Entries& other);
    ~Entries();

    Entry& operator[](size_t i);
    const Entry& operator[](size_t i)const;

    void push_back(Entry& entry);
    void erase();

    size_t getSize()const {return size;}

private:
    Entry* entries;
    size_t size;
};

#endif

//TODO make update and search y something function
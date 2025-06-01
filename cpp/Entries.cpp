#include "Entries.hpp"

Entries::Entries() : entries(nullptr), size(0) {entries = new Entry[size];}

Entries::Entries(const Entries &other): Entries()
{
    Entry* temp = nullptr;
    try
    {
        temp =  new Entry[other.size];
        for (size_t i = 0; i < other.size; i++)
        {
            temp[i] = other.entries[i];
        }
    }
    catch(const std::exception& e)
    {
        delete[] temp;
        std::cerr << e.what() << '\n';
    }

    entries = temp;
    size = other.size;
}

Entries &Entries::operator=(const Entries &other)
{
    if(this!= &other)
    {
        Entry* temp = nullptr;
        try
        {
            temp = new Entry[other.size];
            for (size_t i = 0; i < other.size; i++)
            {
                temp[i] = other.entries[i];
            }
        }
        catch(const std::exception& e)
        {
            delete[] temp;
            std::cerr << e.what() << '\n';
        }
        delete[] entries;
        entries = temp;
        size = other.size;        
    }
    return *this;
}

Entries::~Entries()
{
    erase();
}

Entry &Entries::operator[](size_t i)
{
    if(i>= size) throw std::out_of_range("Out of range in entries!");
    return entries[i];
}

const Entry& Entries::operator[](size_t i) const
{
    if(i>= size) throw std::out_of_range("Out of range in entries!");
    return entries[i];
}

void Entries::push_back(Entry &entry)
{
    Entry* temp = nullptr;
    try
    {
        temp = new Entry[size+1];
        for (size_t i = 0; i < size; i++)
        {
            temp[i] = entries[i];
        }
        temp[size] = entry;
    }
    catch(const std::exception& e)
    {
        delete[] temp;
        std::cerr << e.what() << '\n';
    }
    delete[] entries;
    entries=temp;
    ++size;
}

void Entries::erase()
{
    delete[] entries;
    entries = nullptr;
    size=0;
}

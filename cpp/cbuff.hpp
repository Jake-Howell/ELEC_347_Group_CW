#ifndef C_BUFF
#define C_BUFF
#include "mbed.h"
#include "uop_msb.h"
#include <cstddef>

using namespace uop_msb;

class Circular_Buff{

    //public attributes and member functions can be seen and used by anywhere in the software
    public:
        //constructor
        Circular_Buff (size_t size);  //initalise member attribute to 'size'
        //destructor
        ~Circular_Buff();
        void put(float sample);
        float get();
        void reset();
        bool empty() const;
        bool full() const;
        size_t capacity() const;
        size_t curr_size() const;


    //protected attributes and member functions that only this class and children of this class can see and use
    protected:

    //private attributes and member functions that only this class can see and use
    private:
        Mutex mutex_;
        const size_t size_of_buff;      //specify size of buffer
        int head = 0;                   //store the location of the first element in buffer
        int tail = 0;                   //store location of last element in buffer
        bool isFull = false;

        float* buffer;                  //store location of buffer when created by constructor
};

#endif
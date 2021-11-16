#ifndef C_BUFF
#define C_BUFF
#include "mbed.h"
#include "uop_msb.h"
#include <cstddef>

using namespace uop_msb;

#include "cbuff.hpp"

class Circular_Buff{

    //public attributes and member functions can be seen and used by anywhere in the software
    public:
        //constructor
        Circular_Buff (size_t size) : size_of_buff(size){  //initalise member attribute to 'size
            buffer = new float [size];                     //allocate memory for buffer
        }
        //destructor
        ~Circular_Buff(){
            delete buffer;  //delete array from heap to avoid memory leaks
        }
        void put(float sample){
            mutex.lock();
            buffer[head] = sample;
            if (full){
                tail = (tail + 1) % size_of_buff;
            }

            head = (head + 1) % size_of_buff;   //increment head by 1, and wrap around if greater than buffer size
            full = (head == tail);    //if the head is in the same position as the tail, the buffer is full
            mutex.unlock();
        }
        float get(){        //get last sample and remove it from buffer
            mutex.lock();
            if(empty()){
                return float();
            }
            float sample = buffer[tail];
            full = false;
            tail = (tail + 1) % size_of_buff;
            mutex.unlock();
            return sample;
        }
        void reset(){
            mutex.lock();   //lock mutex so no other threads can access whilst variables are being modified
            head = tail;
            full = false;
            mutex.unlock(); //unlock mutex 
        }
        bool empty() const{
            return (!full && (head == tail)); //if the head is equal to the tail, the buffer is empty
        }
        bool isFull() const{
            return full;  //check full flag
        }
        size_t capacity() const{
            return size_of_buff;    //return size of buffer
        }
        size_t curr_size() const{
            size_t current_size = size_of_buff;
            if(!full){
                if(head >= tail){
                    current_size = head - tail;
                }
                else{
                    current_size = size_of_buff + head - tail;
                }
            }
            return current_size;
        }


    //protected attributes and member functions that only this class and children of this class can see and use
    protected:

    //private attributes and member functions that only this class can see and use
    private:
        Mutex mutex;                    //create mutex object to make buffer thread safe
        const size_t size_of_buff;      //specify size of buffer
        int head = 0;                   //store the location of the first element in buffer
        int tail = 0;                   //store location of last element in buffer
        bool full = false;

        float* buffer;                  //store location of buffer when created by constructor
};

#endif
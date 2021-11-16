#include "mbed.h"
#include "uop_msb.h"
using namespace uop_msb;

#include "cbuff.cpp"

Circular_Buff samples(101);
DigitalOut led(LED3);
// main() runs in its own thread in the OS
int main()
{
    float count = 0.0f;
    float count2  = 3.14195f;
    float lastNum;
    int current_size;
    int buffer_Cap;
    while (true) {
        printf("\n\nWRITING\n\n");
        for (int i = 0; i < 10; i++){
            count = count + 1.0f;
            samples.put(count);
            samples.put(count2);
            led = (samples.isFull()); //display warning light when buffer is full
            current_size = samples.curr_size();
            buffer_Cap = samples.capacity();
            printf("Current buffer size: \t%d/%d\n\n", current_size, buffer_Cap);
        }
        printf("\n\nREADING\n\n");
        for (int i = 0; i < 10; i++){
            lastNum = samples.get();
            current_size = samples.curr_size();
            buffer_Cap = samples.capacity();
            //printf("Last Sample    : \t%5.3f\n", lastNum);
            printf("Current buffer size: \t%d/%d\n\n", current_size, buffer_Cap);
        }
        

        
        
    }
}


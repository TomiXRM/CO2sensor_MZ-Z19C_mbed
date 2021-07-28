#include <mbed.h>

Serial pc(USBTX,USBRX,230400);
InterruptIn pin(A0);
Timer timer;
uint32_t timeLow,timeHigh,ppm;

void timerRise(){
        timeLow = timer.read_ms();
        timer.reset();
}

void timerFall(){
        timeHigh = timer.read_ms();
        timer.reset();
        ppm = 5000 * (timeHigh - 2) / (timeHigh + timeLow - 4);
}
int main() {
        pc.printf("Hello World!!");
        pin.mode(PullNone);
        timer.start();
        pin.rise(&timerRise);
        pin.fall(&timerFall);
        while(1) {
                pc.printf("count : %d\r\n",ppm);
                wait_ms(10);
        }
}
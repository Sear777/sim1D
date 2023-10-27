#include "sleepMilliseconds.h"
void sleepMilliseconds(int milliseconds) {
    struct timespec sleepTime;
    sleepTime.tv_sec = milliseconds / 1000;
    sleepTime.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&sleepTime, nullptr);
}
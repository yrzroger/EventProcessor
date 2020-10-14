/*
 * Copyright (c) 2020 RogerYu.
 */

//#define LOG_NDEBUG 0
#define LOG_TAG "EventProcessorTest"

#include "EventProcessor.h"

using namespace android;

bool mQuit = false;

void sighandler(int num)
{
    ALOGW("Got signal:%d SIGINT:%d SIGHUP:%d SIGUSR1:%d SIGUSR2:%d\n", num, SIGINT, SIGHUP, SIGUSR1, SIGUSR2);
    if(num == SIGINT) {
        printf("\nSIGINT: Stop!\n");
        mQuit = true;
    }

}

int main(int argc, char ** argv)
{
    ALOGD("%s, pid=%d, tid=%d", __func__, getpid(), gettid());

    signal(SIGINT, sighandler);

    sp<EventProcessor> eventProcessor = new EventProcessor;
    eventProcessor->initialize();
    eventProcessor->prepare();
    eventProcessor->start();
    eventProcessor->stop();
    
    sleep(1);
    
    
    eventProcessor->func_1("EventProcessor Test");
    eventProcessor->func_2(1000);
    eventProcessor->func_3();
    
    do {
        usleep(10000);
    } while(!mQuit);
    
    
    return 0;
}
/*
 * Copyright (c) 2020 RogerYu.
 */

#ifndef _REVENT_PROCESSOR_H_
#define _REVENT_PROCESSOR_H_

#include <media/stagefright/foundation/AHandler.h>
#include <media/stagefright/foundation/ALooper.h>
#include <media/stagefright/foundation/AMessage.h>
#include <media/stagefright/foundation/ADebug.h>

namespace android {

struct EventProcessor : public AHandler
{
public:
    EventProcessor();

    status_t initialize();

    status_t prepare();
    status_t start();
    status_t stop();

    status_t func_1(const char *path);
    status_t func_2(int32_t n);
    status_t func_3();

    enum {
        kWhatPrepare,
        kWhatStart,
        kWhatStop,

        kWhatFUNC_1,
        kWhatFUNC_2,
        kWhatFUNC_3,
    };

protected:
    virtual ~EventProcessor();
    virtual void onMessageReceived(const sp<AMessage> &msg); // Inherited from AHandler

private:
    sp<ALooper> mLooper;
    
    void onPrepare();
    void onStart();
    void onStop();
    
    status_t onFunc_1();
    status_t onFunc_2();
    status_t onFunc_3();

    DISALLOW_EVIL_CONSTRUCTORS(EventProcessor); 
};

} // namespace android

#endif // _REVENT_PROCESSOR_H_

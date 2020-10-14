/*
 * Copyright (c) 2020 RogerYu.
 */

//#define LOG_NDEBUG 0
#define LOG_TAG "EventProcessor"

#include "EventProcessor.h"

namespace android {

EventProcessor::EventProcessor() {
    ALOGV("%s", __func__);
}

EventProcessor::~EventProcessor() {
    ALOGV("%s", __func__);
}

// static
status_t PostAndAwaitResponse(
        const sp<AMessage> &msg, sp<AMessage> *response) {
    status_t err = msg->postAndAwaitResponse(response);

    if (err != OK) {
        return err;
    }

    if (!(*response)->findInt32("err", &err)) {
        err = OK;
    }

    return err;
}

void EventProcessor::onMessageReceived(const sp<AMessage> &msg) {
    ALOGD("onMessageReceived: %s", msg->debugString().c_str());
    switch (msg->what()) {
        case kWhatPrepare:
        {
            onPrepare();
            break;
        }
        case kWhatStart:
        {
            onStart();
            break;
        }
        case kWhatStop:
        {
            onStop();
            break;
        }
        case kWhatFUNC_1:
        {
            AString mPath;
            CHECK(msg->findString("path", &mPath));
            ALOGD("patch=%s", mPath.c_str());
            status_t err = onFunc_1();
            
            sp<AReplyToken> replyID;
            CHECK(msg->senderAwaitsResponse(&replyID));

            sp<AMessage> response = new AMessage;
            response->setInt32("err", err);
            response->postReply(replyID);
            
            
            break;
        }
        case kWhatFUNC_2:
        {
            status_t err = onFunc_2();
            
            sp<AReplyToken> replyID;
            CHECK(msg->senderAwaitsResponse(&replyID));

            sp<AMessage> response = new AMessage;
            response->setInt32("err", err);
            response->postReply(replyID);
            break;
        }
        case kWhatFUNC_3:
        {
            status_t err = onFunc_3();
            
            sp<AReplyToken> replyID;
            CHECK(msg->senderAwaitsResponse(&replyID));

            sp<AMessage> response = new AMessage;
            response->setInt32("err", err);
            response->postReply(replyID);
            break;
        }
        default:
            break;
    }
}

status_t EventProcessor::initialize() {
    ALOGD("%s start, pid=%d, tid=%d", __func__, getpid(), gettid());

    mLooper = new ALooper;
    mLooper->setName("EventProcessor");
    mLooper->registerHandler(this);
    mLooper->start();
    
    ALOGD("%s end, pid=%d, tid=%d", __func__, getpid(), gettid());
    
    return OK;
}

status_t EventProcessor::prepare() {
    ALOGD("%s start, pid=%d, tid=%d", __func__, getpid(), gettid());
    
    sp<AMessage> msg = new AMessage(kWhatPrepare, this);
    msg->post();
    
    ALOGD("%s end, pid=%d, tid=%d", __func__, getpid(), gettid());
    
    return OK;
}

status_t EventProcessor::start() {
    ALOGD("%s start, pid=%d, tid=%d", __func__, getpid(), gettid());
    
    sp<AMessage> msg = new AMessage(kWhatStart, this);
    msg->post();
    
    ALOGD("%s end, pid=%d, tid=%d", __func__, getpid(), gettid());
    
    return OK;
}

status_t EventProcessor::stop() {
    ALOGD("%s start, pid=%d, tid=%d", __func__, getpid(), gettid());
    
    sp<AMessage> msg = new AMessage(kWhatStop, this);
    msg->post();

    ALOGD("%s end, pid=%d, tid=%d", __func__, getpid(), gettid());

    return OK;
}

void EventProcessor::onPrepare() {
    ALOGD("%s, pid=%d, tid=%d", __func__, getpid(), gettid());
}

void EventProcessor::onStart() {
    ALOGD("%s, pid=%d, tid=%d", __func__, getpid(), gettid());
}

void EventProcessor::onStop() {
    ALOGD("%s, pid=%d, tid=%d", __func__, getpid(), gettid());
}

// 需要等待结果返回
status_t EventProcessor::func_1(const char *path) {
    ALOGD("%s start, pid=%d, tid=%d", __func__, getpid(), gettid());
    
    sp<AMessage> msg = new AMessage(kWhatFUNC_1, this);
    msg->setString("path", path);
    sp<AMessage> response;
    status_t err = PostAndAwaitResponse(msg, &response);
    
    ALOGD("%s end, pid=%d, tid=%d", __func__, getpid(), gettid());
    
    return err;
}

// 需要等待结果返回
status_t EventProcessor::func_2(int32_t n) {
    ALOGD("%s start, pid=%d, tid=%d", __func__, getpid(), gettid());
    
    sp<AMessage> msg = new AMessage(kWhatFUNC_3, this);
    msg->setInt32("num", n);
    sp<AMessage> response;
    status_t err = PostAndAwaitResponse(msg, &response);
    
    ALOGD("%s end, pid=%d, tid=%d", __func__, getpid(), gettid());
    
    return err;
}

// 需要等待结果返回
status_t EventProcessor::func_3() {
    ALOGD("%s start, pid=%d, tid=%d", __func__, getpid(), gettid());
    
    sp<AMessage> msg = new AMessage(kWhatFUNC_3, this);
    sp<AMessage> response;
    status_t err = PostAndAwaitResponse(msg, &response);
    
    ALOGD("%s end, pid=%d, tid=%d", __func__, getpid(), gettid());
    
    return err;
}

status_t EventProcessor::onFunc_1() {
    ALOGD("%s, pid=%d, tid=%d", __func__, getpid(), gettid());
    return OK;
}

status_t EventProcessor::onFunc_2() {
    ALOGD("%s, pid=%d, tid=%d", __func__, getpid(), gettid());
    return OK;
}

status_t EventProcessor::onFunc_3() {
    ALOGD("%s, pid=%d, tid=%d", __func__, getpid(), gettid());
    return OK;
}



}  // namespace android

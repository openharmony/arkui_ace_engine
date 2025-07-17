/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

#undef KOALA_INTEROP_MODULE
#define KOALA_INTEROP_MODULE InteropNativeModule
#include "common-interop.h"
#include "interop-types.h"
#include "callback-resource.h"
#include <deque>
#include <unordered_map>
#include <atomic>
#include "interop-utils.h"

static bool needReleaseFront = false;
static std::deque<CallbackEventKind> callbackEventsQueue;
static std::deque<CallbackBuffer> callbackCallSubqueue;
static std::deque<InteropInt32> callbackResourceSubqueue;

static std::atomic<KVMDeferred*> currentDeferred(nullptr);

static KVMDeferred* takeCurrent(KNativePointer waitContext) {
    KVMDeferred* current;
    do {
        current = currentDeferred.load();
    } while (!currentDeferred.compare_exchange_strong(current, nullptr));
    return current;
}

void notifyWaiter() {
    auto current = takeCurrent(nullptr);
    if (current)
        current->resolve(current, nullptr, 0);
}

KVMObjectHandle impl_CallbackAwait(KVMContext vmContext, KNativePointer waitContext) {
    KVMObjectHandle result = nullptr;
    auto* current = takeCurrent(waitContext);
    if (current) {
        current->reject(current, "Wrong");
    }
    auto next = CreateDeferred(vmContext, &result);
    KVMDeferred* null = nullptr;
    while (!currentDeferred.compare_exchange_strong(null, next)) {}
    return result;
}
KOALA_INTEROP_CTX_1(CallbackAwait, KVMObjectHandle, KNativePointer)

void impl_UnblockCallbackWait(KNativePointer waitContext) {
    auto current = takeCurrent(waitContext);
    if (current) current->resolve(current, nullptr, 0);
}
KOALA_INTEROP_V1(UnblockCallbackWait, KNativePointer)

void enqueueCallback(const CallbackBuffer* event) {
    callbackEventsQueue.push_back(Event_CallCallback);
    callbackCallSubqueue.push_back(*event);
    notifyWaiter();
}

void holdManagedCallbackResource(InteropInt32 resourceId) {
    callbackEventsQueue.push_back(Event_HoldManagedResource);
    callbackResourceSubqueue.push_back(resourceId);
    notifyWaiter();
}

void releaseManagedCallbackResource(InteropInt32 resourceId) {
    callbackEventsQueue.push_back(Event_ReleaseManagedResource);
    callbackResourceSubqueue.push_back(resourceId);
    notifyWaiter();
}

KInt impl_CheckCallbackEvent(KSerializerBuffer buffer, KInt size) {
    KByte* result = (KByte*)buffer;
    if (needReleaseFront)
    {
        switch (callbackEventsQueue.front())
        {
            case Event_CallCallback:
                callbackCallSubqueue.front().resourceHolder.release();
                callbackCallSubqueue.pop_front();
                break;
            case Event_HoldManagedResource:
            case Event_ReleaseManagedResource:
                callbackResourceSubqueue.pop_front();
                break;
            default:
                INTEROP_FATAL("Unknown event kind");
        }
        callbackEventsQueue.pop_front();
        needReleaseFront = false;
    }
    if (callbackEventsQueue.empty()) {
        return 0;
    }
    const CallbackEventKind frontEventKind = callbackEventsQueue.front();
    interop_memcpy(result, size, &frontEventKind, sizeof(int32_t));

    switch (frontEventKind)
    {
        case Event_CallCallback: {
            interop_memcpy(result + 4, size, callbackCallSubqueue.front().buffer, sizeof(CallbackBuffer::buffer));
            break;
        }
        case Event_HoldManagedResource:
        case Event_ReleaseManagedResource: {
            const InteropInt32 resourceId = callbackResourceSubqueue.front();
            interop_memcpy(result + 4, size, &resourceId, sizeof(InteropInt32));
            break;
        }
        default:
            INTEROP_FATAL("Unknown event kind");
    }
    needReleaseFront = true;
    return 1;
}
KOALA_INTEROP_DIRECT_2(CheckCallbackEvent, KInt, KSerializerBuffer, KInt)

void impl_ReleaseCallbackResource(InteropInt32 resourceId) {
    releaseManagedCallbackResource(resourceId);
}
KOALA_INTEROP_V1(ReleaseCallbackResource, KInt)

void impl_HoldCallbackResource(InteropInt32 resourceId) {
    holdManagedCallbackResource(resourceId);
}
KOALA_INTEROP_V1(HoldCallbackResource, KInt)

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

#ifndef _INTEROP_CALLBACK_RESOURCE_H
#define _INTEROP_CALLBACK_RESOURCE_H

#include <vector>
#include "interop-types.h"

#ifdef KOALA_WINDOWS
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __attribute__ ((visibility ("default")))
#endif

class CallbackResourceHolder {
private:
    std::vector<InteropCallbackResource> heldResources;
public:
    void holdCallbackResource(const InteropCallbackResource* resource) {
        resource->hold(resource->resourceId);
        this->heldResources.push_back(*resource);
    }
    void release() {
        for (auto resource : this->heldResources) {
            resource.release(resource.resourceId);
        }
        this->heldResources.clear();
    }
};

struct CallbackBuffer {
    InteropInt32 kind;
    uint8_t buffer[4096];
    CallbackResourceHolder resourceHolder;
};

enum CallbackEventKind {
    Event_CallCallback = 0,
    Event_HoldManagedResource = 1,
    Event_ReleaseManagedResource = 2,
};

extern "C" DLL_EXPORT void enqueueCallback(const CallbackBuffer* event);
extern "C" DLL_EXPORT void holdManagedCallbackResource(InteropInt32 resourceId);
extern "C" DLL_EXPORT void releaseManagedCallbackResource(InteropInt32 resourceId);

#endif

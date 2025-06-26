/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#define KOALA_INTEROP_MODULE ArkUINativeModule

#include <deque>
#include <stdexcept>
#include "events.h"
#include "common-interop.h"
#include "interop-types.h"

static std::deque<EventBuffer> eventQueue;

void sendEvent(const EventBuffer* event) {
    eventQueue.push_back(*event);
}

KInt impl_CheckArkoalaGeneratedEvents(KByte* result, KInt size) {
    if (((size_t)size) < sizeof(EventBuffer::buffer))
        INTEROP_FATAL("Expected buffer size be not less than sizeof(EventBuffer) bytes");

    if (!eventQueue.size())
        return 0;

    memcpy(result, eventQueue.front().buffer, sizeof(EventBuffer::buffer));
    eventQueue.pop_front();
    return 1;
}
KOALA_INTEROP_2(CheckArkoalaGeneratedEvents, KInt, KByte*, KInt)

KInt impl_InjectEvent(KByte* data, KInt size) {
    if ((size_t)size >= sizeof(EventBuffer::buffer))
        return 0;

    EventBuffer event;
    memcpy(event.buffer, data, size);

    sendEvent(&event);
    return 1;
}
KOALA_INTEROP_2(InjectEvent, KInt, KByte*, KInt)

void impl_EmulateTextInputEvent(KInt nodeId, const KStringPtr& text) {
    /*
    Ark_String str {
        .chars = text.c_str(),
        .length = static_cast<Ark_Int32>(text.length())
    };
    Opt_PreviewText preview;
    preview.tag = ARK_TAG_UNDEFINED;
    GetFullImpl()->getEventsAPI()->getTextInputEventsReceiver()->onChange(nodeId, str, preview);
    */
}
// KOALA_INTEROP_V2(EmulateTextInputEvent, KInt, KStringPtr) // TODO Where to place it?

#define KOALA_INTEROP_MODULE ArkUINativeModule

#include <deque>
#include <stdexcept>
#include "events.h"
#include "common-interop.h"
#include "interop-types.h"
#include "securec.h"

static std::deque<EventBuffer> eventQueue;

void sendEvent(const EventBuffer* event) {
    eventQueue.push_back(*event);
}

KInt impl_CheckArkoalaGeneratedEvents(KByte* result, KInt size) {
    if (((size_t)size) < sizeof(EventBuffer::buffer))
        INTEROP_FATAL("Expected buffer size be not less than sizeof(EventBuffer) bytes");

    if (!eventQueue.size())
        return 0;

    if (memcpy_s(result, sizeof(EventBuffer::buffer), eventQueue.front().buffer,
        sizeof(EventBuffer::buffer)) != 0) {
        return 0;
    }
    eventQueue.pop_front();
    return 1;
}
KOALA_INTEROP_2(CheckArkoalaGeneratedEvents, KInt, KByte*, KInt)

KInt impl_InjectEvent(KByte* data, KInt size) {
    if ((size_t)size >= sizeof(EventBuffer::buffer) || data == NULL)
        return 0;

    EventBuffer event;
    if (memcpy_s(event.buffer, sizeof(EventBuffer::buffer), data, size) != 0) {
        return 0;
    }

    sendEvent(&event);
    return 1;
}
KOALA_INTEROP_2(InjectEvent, KInt, KByte*, KInt)

void impl_EmulateTextInputEvent(KInt nodeId, const KStringPtr& text) {
}

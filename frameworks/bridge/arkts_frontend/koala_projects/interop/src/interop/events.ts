import { int32 } from '@koalaui/common'
import { DeserializerBase } from './DeserializerBase'
import { InteropNativeModule } from './InteropNativeModule'
import { ResourceHolder } from './ResourceManager'
import { wrapSystemCallback } from './InteropOps'
import { KSerializerBuffer } from './InteropTypes'

const API_KIND_MAX = 100
const apiEventHandlers: (EventHandler | undefined)[] = new Array(API_KIND_MAX).fill(undefined)
export type EventHandler = (deserializer: DeserializerBase) => void
export function registerApiEventHandler(apiKind: int32, handler: EventHandler): void {
    if (apiKind < 0 || apiKind > API_KIND_MAX) {
        throw new Error(`Maximum api kind is ${API_KIND_MAX}, received ${apiKind}`)
    }
    if (apiEventHandlers[apiKind] !== undefined) {
        throw new Error(`Callback caller for api kind ${apiKind} already was set`)
    }
    apiEventHandlers[apiKind] = handler
}
export function handleApiEvent(apiKind: int32, deserializer: DeserializerBase): void {
    if (apiKind < 0 || apiKind > API_KIND_MAX) {
        throw new Error(`Maximum api kind is ${API_KIND_MAX}, received ${apiKind}`)
    }
    if (apiEventHandlers[apiKind] === undefined) {
        throw new Error(`Callback caller for api kind ${apiKind} was not set`)
    }
    apiEventHandlers[apiKind]!(deserializer)
}
export function wrapSystemApiHandlerCallback(): void {
    wrapSystemCallback(1, (buffer: KSerializerBuffer, len:int32) => {
        const deserializer = new DeserializerBase(buffer, len)
        const apiKind = deserializer.readInt32()
        handleApiEvent(apiKind, deserializer)
        return 0
    })
}
export function checkEvents(): void {
    while (checkSingleEvent()) {}
}


enum CallbackEventKind {
    Event_CallCallback = 0,
    Event_HoldManagedResource = 1,
    Event_ReleaseManagedResource = 2,
}

const bufferSize = 8 * 1024
const buffer = new Uint8Array(bufferSize)
const deserializer = new DeserializerBase(buffer.buffer, bufferSize)
function checkSingleEvent(): boolean {
    deserializer.resetCurrentPosition()
    let result = InteropNativeModule._CheckCallbackEvent(buffer, bufferSize)
    if (result === 0) {
        return false
    }
    const eventKind = deserializer.readInt32() as CallbackEventKind
    switch (eventKind) {
        case CallbackEventKind.Event_CallCallback: {
            const apiKind = deserializer.readInt32()
            handleApiEvent(apiKind, deserializer)
            return true;
        }
        case CallbackEventKind.Event_HoldManagedResource: {
            const resourceId = deserializer.readInt32()
            ResourceHolder.instance().hold(resourceId)
            return true;
        }
        case CallbackEventKind.Event_ReleaseManagedResource: {
            const resourceId = deserializer.readInt32()
            ResourceHolder.instance().release(resourceId)
            return true;
        }
        default: {
            throw new Error(`Unknown callback event kind ${eventKind}`)
        }
    }
}
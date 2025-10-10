package Interop

import std.collection.*

const API_KIND_MAX: Int32 = 100
var apiEventHandlers: ArrayList<Option<EventHandler>> = ArrayList<Option<EventHandler>>(Int64(API_KIND_MAX)) {i => Option.None}
public type EventHandler = (deserializer: DeserializerBase) -> Unit
public func registerApiEventHandler(apiKind: Int32, handler: EventHandler) {
    if (apiKind < 0 || apiKind > API_KIND_MAX) {
        throw Exception("Maximum api kind is ${API_KIND_MAX}, received ${apiKind}")
    }
    if (let Some(apiEventHandler) <- apiEventHandlers[Int64(apiKind)]) {
        throw Exception("Callback caller for api kind ${apiKind} was set already")
    } else {
        apiEventHandlers[Int64(apiKind)] = handler
    }
}
public func handleApiEvent(apiKind: Int32, deserializer: DeserializerBase) {
    if (apiKind < 0 || apiKind > API_KIND_MAX) {
        throw Exception("Maximum api kind is ${API_KIND_MAX}, received ${apiKind}")
    }
    if (let Some(apiEventHandler) <- apiEventHandlers[Int64(apiKind)]) {
        apiEventHandler(deserializer)
    } else {
        throw Exception("Callback caller for api kind ${apiKind} was not set")
    }
}
public func wrapSystemApiHandlerCallback() {
    wrapSystemCallback(1, {buffer: KSerializerBuffer, len: Int32 =>
        let deserializer = DeserializerBase(buffer, len)
        let apiKind = deserializer.readInt32()
        handleApiEvent(apiKind, deserializer)
        return 0
    })
}
public func checkEvents(): Unit {
    while (checkSingleEvent()) {}
}


class CallbackEventKind {
    public static var Event_CallCallback: CallbackEventKind = CallbackEventKind(0)
    public static var Event_HoldManagedResource: CallbackEventKind = CallbackEventKind(1)
    public static var Event_ReleaseManagedResource: CallbackEventKind = CallbackEventKind(2)
    public var value: Int32
    CallbackEventKind(arg0: Int32) {
        value = arg0
    }
}


let bufferSize: Int32 = 1024
let buffer = Array<UInt8>(Int64(bufferSize), repeat: 0)
let deserializer = DeserializerBase(buffer, bufferSize)

public func checkSingleEvent(): Bool {
    deserializer.resetCurrentPosition()
    let result = InteropNativeModule._CheckCallbackEvent(deserializer.asBuffer(), bufferSize)
    if (result == 0) {
        return false
    }
    let eventKind = deserializer.readInt32()
    if (eventKind == CallbackEventKind.Event_CallCallback.value) {
        let apiKind = deserializer.readInt32()
        handleApiEvent(apiKind, deserializer)
        return true;
    }
    else if (eventKind == CallbackEventKind.Event_HoldManagedResource.value) {
        let resourceId = deserializer.readInt32()
        ResourceHolder.instance().hold(resourceId)
        return true
    }
    else if (eventKind == CallbackEventKind.Event_ReleaseManagedResource.value) {
        let resourceId = deserializer.readInt32()
        ResourceHolder.instance().release(resourceId)
        return true
    }
    else { throw Exception("Unknown callback event kind ${eventKind}") }
}

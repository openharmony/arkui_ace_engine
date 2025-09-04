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

@file:OptIn(ExperimentalForeignApi::class)

package koalaui.interop

import kotlinx.cinterop.*

val API_KIND_MAX: Int = 100
val apiEventHandlers: Array<EventHandler?> = arrayOfNulls(API_KIND_MAX)
typealias EventHandler = (DeserializerBase) -> Unit
public fun registerApiEventHandler(apiKind: Int, handler: EventHandler): Unit {
    if (apiKind < 0 || apiKind > API_KIND_MAX) {
        throw Error("Maximum api kind is ${API_KIND_MAX}, received ${apiKind}")
    }
    if (apiEventHandlers[apiKind] != null) {
        throw Error("Callback caller for api kind ${apiKind} already was set")
    }
    apiEventHandlers[apiKind] = handler
}
public fun handleApiEvent(apiKind: Int, deserializer: DeserializerBase): Unit {
    if (apiKind < 0 || apiKind > API_KIND_MAX) {
        throw Error("Maximum api kind is ${API_KIND_MAX}, received ${apiKind}")
    }
    if (apiEventHandlers[apiKind] == null) {
        throw Error("Callback caller for api kind ${apiKind} was not set")
    }
    apiEventHandlers[apiKind]!!.invoke(deserializer)
}
public fun wrapSystemApiHandlerCallback(): Unit {
    CallbackRegistry.wrapSystem(1, { buffer: KSerializerBuffer, len: Int ->
        val deserializer = DeserializerBase(buffer, len)
        val apiKind = deserializer.readInt32()
        handleApiEvent(apiKind, deserializer)
        return@wrapSystem 0
    })
}
public fun checkEvents(): Unit {
    while (checkSingleEvent()) {}
}

enum class CallbackEventKind(var value: Int) {
    Event_CallCallback(0),
    Event_HoldManagedResource(1),
    Event_ReleaseManagedResource(2)
}

private fun createDeserializer(bufferSize: Int): DeserializerBase {
    val buffer = InteropNativeModule._Malloc(bufferSize.toLong())
    return DeserializerBase(buffer, bufferSize)
}

val bufferSize: Int = 8 * 1024
val deserializer = createDeserializer(bufferSize)

private fun checkSingleEvent(): Boolean {
    val result = InteropNativeModule._CheckCallbackEvent(deserializer.asBuffer(), bufferSize)
    if (result == 0) {
        return false
    }
    deserializer.resetCurrentPosition()
    val eventKind = deserializer.readInt32()
    if (eventKind == CallbackEventKind.Event_CallCallback.value) {
        val apiKind = deserializer.readInt32()
        handleApiEvent(apiKind, deserializer)
        return true
    }
    else if (eventKind == CallbackEventKind.Event_HoldManagedResource.value) {
        val resourceId = deserializer.readInt32()
        ResourceHolder.hold(resourceId)
        return true
    }
    else if (eventKind == CallbackEventKind.Event_ReleaseManagedResource.value) {
        val resourceId = deserializer.readInt32()
        ResourceHolder.release(resourceId)
        return true
    }
    else {
        throw Exception("Unknown callback event kind ${eventKind}")
    }
}

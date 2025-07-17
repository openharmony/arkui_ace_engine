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

import { KBuffer, DeserializerBase } from "@koalaui/interop"
import { deserializeAndCallCallback } from "./generated/peers/CallbackDeserializeCall"
import { ResourceHolder, InteropNativeModule } from "@koalaui/interop"

enum CallbackEventKind {
    Event_CallCallback = 0,
    Event_HoldManagedResource = 1,
    Event_ReleaseManagedResource = 2,
}

const bufferSize = 4096
const buffer = new KBuffer(bufferSize)
const deserializer = new DeserializerBase(buffer.buffer, bufferSize)
export function checkArkoalaCallbacks() {
    while (true) {
        deserializer.resetCurrentPosition()
        let result = InteropNativeModule._CheckCallbackEvent(buffer.buffer, bufferSize)
        if (result == 0) break

        const eventKind = CallbackEventKind.fromValue(deserializer.readInt32())
        switch (eventKind.valueOf()) {
            case CallbackEventKind.Event_CallCallback.valueOf(): {
                deserializeAndCallCallback(deserializer)
                break;
            } 
            case CallbackEventKind.Event_HoldManagedResource.valueOf(): {
                const resourceId = deserializer.readInt32()
                ResourceHolder.instance().hold(resourceId)
                break;
            } 
            case CallbackEventKind.Event_ReleaseManagedResource.valueOf(): {
                const resourceId = deserializer.readInt32()
                ResourceHolder.instance().release(resourceId)
                break;
            }
            default: throw new Error(`Unknown callback event kind ${eventKind}`)
        }
    }
}

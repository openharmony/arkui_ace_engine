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

import { Deserializer } from "./Deserializer";
import { deserializeAndCallCallback } from "./CallbackDeserializeCall"
import { InteropNativeModule, ResourceHolder } from "@koalaui/interop"

enum CallbackEventKind {
    Event_CallCallback = 0,
    Event_HoldManagedResource = 1,
    Event_ReleaseManagedResource = 2,
}

const bufferSize = 4096
const buffer = new Uint8Array(bufferSize)
const deserializer = new Deserializer(buffer.buffer, bufferSize)
export function checkArkoalaCallbacks() {
    while (true) {
        let result = InteropNativeModule._CheckCallbackEvent(buffer, bufferSize)
        if (result == 0) break

        deserializer.resetCurrentPosition()
        const eventKind = deserializer.readInt32() as CallbackEventKind
        switch (eventKind) {
            case CallbackEventKind.Event_CallCallback: {
                deserializeAndCallCallback(deserializer)
                break;
            } 
            case CallbackEventKind.Event_HoldManagedResource: {
                const resourceId = deserializer.readInt32()
                ResourceHolder.instance().hold(resourceId)
                break;
            } 
            case CallbackEventKind.Event_ReleaseManagedResource: {
                const resourceId = deserializer.readInt32()
                ResourceHolder.instance().release(resourceId)
                break;
            }
            default: throw new Error(`Unknown callback event kind ${eventKind}`)
        }
    }
}

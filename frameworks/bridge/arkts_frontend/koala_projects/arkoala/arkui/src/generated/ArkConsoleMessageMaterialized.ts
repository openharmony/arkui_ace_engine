/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { MessageLevel } from "./ArkWebInterfaces"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class ConsoleMessageInternal {
    public static fromPtr(ptr: KPointer): ConsoleMessage {
        const obj: ConsoleMessage = new ConsoleMessage(undefined, undefined, undefined, undefined)
        obj.peer = new Finalizable(ptr, ConsoleMessage.getFinalizer())
        return obj
    }
}
export class ConsoleMessage implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_consolemessage(message: string, sourceId: string, lineNumber: number, messageLevel: MessageLevel): KPointer {
        const retval = ArkUIGeneratedNativeModule._ConsoleMessage_ctor(message, sourceId, lineNumber, messageLevel)
        return retval
    }
     constructor(message?: string, sourceId?: string, lineNumber?: number, messageLevel?: MessageLevel) {
        if (((message) !== (undefined)) || ((sourceId) !== (undefined)) || ((lineNumber) !== (undefined)) || ((messageLevel) !== (undefined)))
        {
            const ctorPtr: KPointer = ConsoleMessage.ctor_consolemessage((message)!, (sourceId)!, (lineNumber)!, (messageLevel)!)
            this.peer = new Finalizable(ctorPtr, ConsoleMessage.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ConsoleMessage_getFinalizer()
    }
    public getMessage(): string {
        return this.getMessage_serialize()
    }
    public getSourceId(): string {
        return this.getSourceId_serialize()
    }
    public getLineNumber(): number {
        return this.getLineNumber_serialize()
    }
    public getMessageLevel(): MessageLevel {
        return this.getMessageLevel_serialize()
    }
    private getMessage_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._ConsoleMessage_getMessage(this.peer!.ptr)
        return retval
    }
    private getSourceId_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._ConsoleMessage_getSourceId(this.peer!.ptr)
        return retval
    }
    private getLineNumber_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._ConsoleMessage_getLineNumber(this.peer!.ptr)
        return retval
    }
    private getMessageLevel_serialize(): MessageLevel {
        const retval = ArkUIGeneratedNativeModule._ConsoleMessage_getMessageLevel(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
}

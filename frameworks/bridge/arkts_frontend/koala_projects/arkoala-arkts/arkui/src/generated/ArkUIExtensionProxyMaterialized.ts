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

import { Callback_UIExtensionProxy_Void } from "./SyntheticDeclarations"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export interface UIExtensionProxy {
    send(data: Map<string, Object>): void
    sendSync(data: Map<string, Object>): Map<string, Object>
    onAsyncReceiverRegister(callback_: ((parameter: UIExtensionProxy) => void)): void
    onSyncReceiverRegister(callback_: ((parameter: UIExtensionProxy) => void)): void
    offAsyncReceiverRegister(callback_?: ((parameter: UIExtensionProxy) => void)): void
    offSyncReceiverRegister(callback_?: ((parameter: UIExtensionProxy) => void)): void
}
export class UIExtensionProxyInternal implements MaterializedBase,UIExtensionProxy {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_uiextensionproxy(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._UIExtensionProxy_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = UIExtensionProxyInternal.ctor_uiextensionproxy()
        this.peer = new Finalizable(ctorPtr, UIExtensionProxyInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._UIExtensionProxy_getFinalizer()
    }
    public send(data: Map<string, Object>): void {
        const data_casted = data as (Map<string, Object>)
        this.send_serialize(data_casted)
        return
    }
    public sendSync(data: Map<string, Object>): Map<string, Object> {
        const data_casted = data as (Map<string, Object>)
        return this.sendSync_serialize(data_casted)
    }
    public onAsyncReceiverRegister(callback_: ((parameter: UIExtensionProxy) => void)): void {
        const callback__casted = callback_ as (((parameter: UIExtensionProxy) => void))
        this.onAsyncReceiverRegister_serialize(callback__casted)
        return
    }
    public onSyncReceiverRegister(callback_: ((parameter: UIExtensionProxy) => void)): void {
        const callback__casted = callback_ as (((parameter: UIExtensionProxy) => void))
        this.onSyncReceiverRegister_serialize(callback__casted)
        return
    }
    public offAsyncReceiverRegister(callback_?: ((parameter: UIExtensionProxy) => void)): void {
        const callback__casted = callback_ as (((parameter: UIExtensionProxy) => void) | undefined)
        this.offAsyncReceiverRegister_serialize(callback__casted)
        return
    }
    public offSyncReceiverRegister(callback_?: ((parameter: UIExtensionProxy) => void)): void {
        const callback__casted = callback_ as (((parameter: UIExtensionProxy) => void) | undefined)
        this.offSyncReceiverRegister_serialize(callback__casted)
        return
    }
    on(type: string, callback_: ((parameter: UIExtensionProxy) => void)): void {
        throw new Error("TBD")
    }
    off(type: string, callback_: ((parameter: UIExtensionProxy) => void)): void {
        throw new Error("TBD")
    }
    private send_serialize(data: Map<string, Object>): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(data.size as int32 as int32)
        for (const pair of data) {
            const data_key = pair[0]
            const data_value = pair[1]
            thisSerializer.writeString(data_key)
            thisSerializer.writeCustomObject("Object", data_value)
        }
        ArkUIGeneratedNativeModule._UIExtensionProxy_send(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private sendSync_serialize(data: Map<string, Object>): Map<string, Object> {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(data.size as int32 as int32)
        for (const pair of data) {
            const data_key = pair[0]
            const data_value = pair[1]
            thisSerializer.writeString(data_key)
            thisSerializer.writeCustomObject("Object", data_value)
        }
        const retval  = ArkUIGeneratedNativeModule._UIExtensionProxy_sendSync(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const buffer_size : int32 = retvalDeserializer.readInt32()
        let buffer : Map<string, Object> = new Map<string, Object>()
        // TODO: TS map resize
        for (let buffer_i = 0; buffer_i < buffer_size; buffer_i++) {
            const buffer_key : string = (retvalDeserializer.readString() as string)
            const buffer_value : Object = (retvalDeserializer.readCustomObject("Object") as Object)
            buffer.set(buffer_key, buffer_value)
        }
        const returnResult : Map<string, Object> = buffer
        return returnResult
    }
    private onAsyncReceiverRegister_serialize(callback_: ((parameter: UIExtensionProxy) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._UIExtensionProxy_onAsyncReceiverRegister(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private onSyncReceiverRegister_serialize(callback_: ((parameter: UIExtensionProxy) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._UIExtensionProxy_onSyncReceiverRegister(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private offAsyncReceiverRegister_serialize(callback_?: ((parameter: UIExtensionProxy) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type as int32)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._UIExtensionProxy_offAsyncReceiverRegister(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private offSyncReceiverRegister_serialize(callback_?: ((parameter: UIExtensionProxy) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type as int32)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._UIExtensionProxy_offSyncReceiverRegister(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static fromPtr(ptr: KPointer): UIExtensionProxyInternal {
        const obj : UIExtensionProxyInternal = new UIExtensionProxyInternal()
        obj.peer = new Finalizable(ptr, UIExtensionProxyInternal.getFinalizer())
        return obj
    }
}

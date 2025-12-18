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

import { default as router } from '@ohos.router'
import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { CallbackTransformer } from './../CallbackTransformer'
export class router_RouterOptions_serializer {
    public static write(buffer: SerializerBase, value: router.RouterOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForUrl  = value.url
        valueSerializer.writeString(valueHolderForUrl)
        const valueHolderForParams  = value.params
        if (valueHolderForParams !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForParamsTmpValue  = valueHolderForParams!
            valueSerializer.holdAndWriteObject(valueHolderForParamsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForRecoverable  = value.recoverable
        if (valueHolderForRecoverable !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRecoverableTmpValue  = valueHolderForRecoverable!
            valueSerializer.writeBoolean(valueHolderForRecoverableTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): router.RouterOptions {
        let valueDeserializer : DeserializerBase = buffer
        const urlTmpResult : string = (valueDeserializer.readString() as string)
        const paramsTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let paramsTmpBuf : Object | undefined = undefined
        if ((paramsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            paramsTmpBuf = (valueDeserializer.readObject() as object)
        }
        const paramsTmpResult : Object | undefined = paramsTmpBuf
        const recoverableTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let recoverableTmpBuf : boolean | undefined = undefined
        if ((recoverableTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            recoverableTmpBuf = valueDeserializer.readBoolean()
        }
        const recoverableTmpResult : boolean | undefined = recoverableTmpBuf
        let value : router.RouterOptions = ({url: urlTmpResult, params: paramsTmpResult, recoverable: recoverableTmpResult} as router.RouterOptions)
        return value
    }
}
export class router_RouterState_serializer {
    public static write(buffer: SerializerBase, value: router.RouterState): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForIndex  = value.index
        valueSerializer.writeInt32(valueHolderForIndex)
        const valueHolderForName  = value.name
        valueSerializer.writeString(valueHolderForName)
        const valueHolderForPath  = value.path
        valueSerializer.writeString(valueHolderForPath)
        const valueHolderForParams  = value.params
        valueSerializer.holdAndWriteObject(valueHolderForParams)
    }
    public static read(buffer: DeserializerBase): router.RouterState {
        let valueDeserializer : DeserializerBase = buffer
        const indexTmpResult : int32 = valueDeserializer.readInt32()
        const nameTmpResult : string = (valueDeserializer.readString() as string)
        const pathTmpResult : string = (valueDeserializer.readString() as string)
        const paramsTmpResult : Object = (valueDeserializer.readObject() as object)
        let value : router.RouterState = ({index: indexTmpResult, name: nameTmpResult, path: pathTmpResult, params: paramsTmpResult} as router.RouterState)
        return value
    }
}

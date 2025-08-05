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

import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { KInt, KPointer, KBoolean, NativeBuffer, KStringPtr, SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { TypeChecker } from "#components"
import { CallbackTransformer } from "./../CallbackTransformer"
export type ErrorCallback = (error: BusinessError) => void;
export interface BusinessError {
    name: string;
    message: string;
    stack?: string;
    code: number;
}
export class BusinessError_serializer {
    public static write(buffer: SerializerBase, value: BusinessError): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForName  = value.name
        valueSerializer.writeString(valueHolderForName)
        const valueHolderForMessage  = value.message
        valueSerializer.writeString(valueHolderForMessage)
        const valueHolderForStack  = value.stack
        if (valueHolderForStack !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStackTmpValue  = valueHolderForStack!
            valueSerializer.writeString(valueHolderForStackTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForCode  = value.code
        valueSerializer.writeNumber(valueHolderForCode)
    }
    public static read(buffer: DeserializerBase): BusinessError {
        let valueDeserializer : DeserializerBase = buffer
        const nameTmpResult : string = (valueDeserializer.readString() as string)
        const messageTmpResult : string = (valueDeserializer.readString() as string)
        const stackTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let stackTmpBuf : string | undefined
        if ((stackTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            stackTmpBuf = (valueDeserializer.readString() as string)
        }
        const stackTmpResult : string | undefined = stackTmpBuf
        const codeTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : BusinessError = ({name: nameTmpResult, message: messageTmpResult, stack: stackTmpResult, code: codeTmpResult} as BusinessError)
        return value
    }
}

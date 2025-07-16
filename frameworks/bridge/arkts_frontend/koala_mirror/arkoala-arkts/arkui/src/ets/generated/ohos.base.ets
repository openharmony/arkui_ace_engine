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
import { KInt, KPointer, KBoolean, NativeBuffer, KStringPtr, wrapCallback, SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { CallbackKind } from "./peers/CallbackKind"
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
        const value_name  = value.name
        valueSerializer.writeString(value_name)
        const value_message  = value.message
        valueSerializer.writeString(value_message)
        const value_stack  = value.stack
        let value_stack_type : int32 = RuntimeType.UNDEFINED
        value_stack_type = runtimeType(value_stack)
        valueSerializer.writeInt8((value_stack_type).toChar())
        if ((value_stack_type) != (RuntimeType.UNDEFINED)) {
            const value_stack_value  = value_stack!
            valueSerializer.writeString(value_stack_value)
        }
        const value_code  = value.code
        valueSerializer.writeNumber(value_code)
    }
    public static read(buffer: DeserializerBase): BusinessError {
        let valueDeserializer : DeserializerBase = buffer
        const name_result : string = (valueDeserializer.readString() as string)
        const message_result : string = (valueDeserializer.readString() as string)
        const stack_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let stack_buf : string | undefined
        if ((stack_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            stack_buf = (valueDeserializer.readString() as string)
        }
        const stack_result : string | undefined = stack_buf
        const code_result : number = (valueDeserializer.readNumber() as number)
        let value : BusinessError = ({name: name_result, message: message_result, stack: stack_result, code: code_result} as BusinessError)
        return value
    }
}

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
export interface Resource {
    bundleName: string;
    moduleName: string;
    id: number;
    params?: Array<string>;
    type?: number;
}
export class Resource_serializer {
    public static write(buffer: SerializerBase, value: Resource): void {
        let valueSerializer : SerializerBase = buffer
        const value_bundleName  = value.bundleName
        valueSerializer.writeString(value_bundleName)
        const value_moduleName  = value.moduleName
        valueSerializer.writeString(value_moduleName)
        const value_id  = value.id
        valueSerializer.writeNumber(value_id)
        const value_params  = value.params
        let value_params_type : int32 = RuntimeType.UNDEFINED
        value_params_type = runtimeType(value_params)
        valueSerializer.writeInt8((value_params_type).toChar())
        if ((value_params_type) != (RuntimeType.UNDEFINED)) {
            const value_params_value  = value_params!
            valueSerializer.writeInt32((value_params_value.length).toInt())
            for (let value_params_value_counter_i = 0; value_params_value_counter_i < value_params_value.length; value_params_value_counter_i++) {
                const value_params_value_element : string = value_params_value[value_params_value_counter_i]
                valueSerializer.writeString(value_params_value_element)
            }
        }
        const value_type  = value.type
        let value_type_type : int32 = RuntimeType.UNDEFINED
        value_type_type = runtimeType(value_type)
        valueSerializer.writeInt8((value_type_type).toChar())
        if ((value_type_type) != (RuntimeType.UNDEFINED)) {
            const value_type_value  = value_type!
            valueSerializer.writeNumber(value_type_value)
        }
    }
    public static read(buffer: DeserializerBase): Resource {
        let valueDeserializer : DeserializerBase = buffer
        const bundleName_result : string = (valueDeserializer.readString() as string)
        const moduleName_result : string = (valueDeserializer.readString() as string)
        const id_result : number = (valueDeserializer.readNumber() as number)
        const params_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let params_buf : Array<string> | undefined
        if ((params_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const params_buf__length : int32 = valueDeserializer.readInt32()
            let params_buf_ : Array<string> = new Array<string>(params_buf__length)
            for (let params_buf__i = 0; params_buf__i < params_buf__length; params_buf__i++) {
                params_buf_[params_buf__i] = (valueDeserializer.readString() as string)
            }
            params_buf = params_buf_
        }
        const params_result : Array<string> | undefined = params_buf
        const type_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let type_buf : number | undefined
        if ((type_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            type_buf = (valueDeserializer.readNumber() as number)
        }
        const type_result : number | undefined = type_buf
        let value : Resource = ({bundleName: bundleName_result, moduleName: moduleName_result, id: id_result, params: params_result, type: type_result} as Resource)
        return value
    }
}

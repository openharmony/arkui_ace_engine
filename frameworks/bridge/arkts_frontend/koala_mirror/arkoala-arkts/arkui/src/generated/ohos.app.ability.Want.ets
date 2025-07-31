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
export interface Want {
    bundleName?: string;
    abilityName?: string;
    deviceId?: string;
    uri?: string;
    type?: string;
    flags?: number;
    action?: string;
    parameters?: Map<string, Object>;
    entities?: Array<string>;
    moduleName?: string;
}
export class Want_serializer {
    public static write(buffer: SerializerBase, value: Want): void {
        let valueSerializer : SerializerBase = buffer
        const value_bundleName  = value.bundleName
        let value_bundleName_type : int32 = RuntimeType.UNDEFINED
        value_bundleName_type = runtimeType(value_bundleName)
        valueSerializer.writeInt8((value_bundleName_type).toChar())
        if ((value_bundleName_type) != (RuntimeType.UNDEFINED)) {
            const value_bundleName_value  = value_bundleName!
            valueSerializer.writeString(value_bundleName_value)
        }
        const value_abilityName  = value.abilityName
        let value_abilityName_type : int32 = RuntimeType.UNDEFINED
        value_abilityName_type = runtimeType(value_abilityName)
        valueSerializer.writeInt8((value_abilityName_type).toChar())
        if ((value_abilityName_type) != (RuntimeType.UNDEFINED)) {
            const value_abilityName_value  = value_abilityName!
            valueSerializer.writeString(value_abilityName_value)
        }
        const value_deviceId  = value.deviceId
        let value_deviceId_type : int32 = RuntimeType.UNDEFINED
        value_deviceId_type = runtimeType(value_deviceId)
        valueSerializer.writeInt8((value_deviceId_type).toChar())
        if ((value_deviceId_type) != (RuntimeType.UNDEFINED)) {
            const value_deviceId_value  = value_deviceId!
            valueSerializer.writeString(value_deviceId_value)
        }
        const value_uri  = value.uri
        let value_uri_type : int32 = RuntimeType.UNDEFINED
        value_uri_type = runtimeType(value_uri)
        valueSerializer.writeInt8((value_uri_type).toChar())
        if ((value_uri_type) != (RuntimeType.UNDEFINED)) {
            const value_uri_value  = value_uri!
            valueSerializer.writeString(value_uri_value)
        }
        const value_type  = value.type
        let value_type_type : int32 = RuntimeType.UNDEFINED
        value_type_type = runtimeType(value_type)
        valueSerializer.writeInt8((value_type_type).toChar())
        if ((value_type_type) != (RuntimeType.UNDEFINED)) {
            const value_type_value  = value_type!
            valueSerializer.writeString(value_type_value)
        }
        const value_flags  = value.flags
        let value_flags_type : int32 = RuntimeType.UNDEFINED
        value_flags_type = runtimeType(value_flags)
        valueSerializer.writeInt8((value_flags_type).toChar())
        if ((value_flags_type) != (RuntimeType.UNDEFINED)) {
            const value_flags_value  = value_flags!
            valueSerializer.writeNumber(value_flags_value)
        }
        const value_action  = value.action
        let value_action_type : int32 = RuntimeType.UNDEFINED
        value_action_type = runtimeType(value_action)
        valueSerializer.writeInt8((value_action_type).toChar())
        if ((value_action_type) != (RuntimeType.UNDEFINED)) {
            const value_action_value  = value_action!
            valueSerializer.writeString(value_action_value)
        }
        const value_parameters  = value.parameters
        let value_parameters_type : int32 = RuntimeType.UNDEFINED
        value_parameters_type = runtimeType(value_parameters)
        valueSerializer.writeInt8((value_parameters_type).toChar())
        if ((value_parameters_type) != (RuntimeType.UNDEFINED)) {
            const value_parameters_value  = value_parameters!
            valueSerializer.writeInt32((value_parameters_value.size).toInt())
            for (const pair of value_parameters_value) {
                const value_parameters_value_key = pair[0]
                const value_parameters_value_value = pair[1]
                valueSerializer.writeString(value_parameters_value_key)
                valueSerializer.holdAndWriteObject(value_parameters_value_value)
            }
        }
        const value_entities  = value.entities
        let value_entities_type : int32 = RuntimeType.UNDEFINED
        value_entities_type = runtimeType(value_entities)
        valueSerializer.writeInt8((value_entities_type).toChar())
        if ((value_entities_type) != (RuntimeType.UNDEFINED)) {
            const value_entities_value  = value_entities!
            valueSerializer.writeInt32((value_entities_value.length).toInt())
            for (let value_entities_value_counter_i = 0; value_entities_value_counter_i < value_entities_value.length; value_entities_value_counter_i++) {
                const value_entities_value_element : string = value_entities_value[value_entities_value_counter_i]
                valueSerializer.writeString(value_entities_value_element)
            }
        }
        const value_moduleName  = value.moduleName
        let value_moduleName_type : int32 = RuntimeType.UNDEFINED
        value_moduleName_type = runtimeType(value_moduleName)
        valueSerializer.writeInt8((value_moduleName_type).toChar())
        if ((value_moduleName_type) != (RuntimeType.UNDEFINED)) {
            const value_moduleName_value  = value_moduleName!
            valueSerializer.writeString(value_moduleName_value)
        }
    }
    public static read(buffer: DeserializerBase): Want {
        let valueDeserializer : DeserializerBase = buffer
        const bundleName_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bundleName_buf : string | undefined
        if ((bundleName_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            bundleName_buf = (valueDeserializer.readString() as string)
        }
        const bundleName_result : string | undefined = bundleName_buf
        const abilityName_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let abilityName_buf : string | undefined
        if ((abilityName_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            abilityName_buf = (valueDeserializer.readString() as string)
        }
        const abilityName_result : string | undefined = abilityName_buf
        const deviceId_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let deviceId_buf : string | undefined
        if ((deviceId_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            deviceId_buf = (valueDeserializer.readString() as string)
        }
        const deviceId_result : string | undefined = deviceId_buf
        const uri_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let uri_buf : string | undefined
        if ((uri_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            uri_buf = (valueDeserializer.readString() as string)
        }
        const uri_result : string | undefined = uri_buf
        const type_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let type_buf : string | undefined
        if ((type_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            type_buf = (valueDeserializer.readString() as string)
        }
        const type_result : string | undefined = type_buf
        const flags_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let flags_buf : number | undefined
        if ((flags_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            flags_buf = (valueDeserializer.readNumber() as number)
        }
        const flags_result : number | undefined = flags_buf
        const action_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let action_buf : string | undefined
        if ((action_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            action_buf = (valueDeserializer.readString() as string)
        }
        const action_result : string | undefined = action_buf
        const parameters_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let parameters_buf : Map<string, Object> | undefined
        if ((parameters_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const parameters_buf__size : int32 = valueDeserializer.readInt32()
            let parameters_buf_ : Map<string, Object> = new Map<string, Object>()
            // TODO: TS map resize
            for (let parameters_buf__i = 0; parameters_buf__i < parameters_buf__size; parameters_buf__i++) {
                const parameters_buf__key : string = (valueDeserializer.readString() as string)
                const parameters_buf__value : Object = (valueDeserializer.readObject() as object)
                parameters_buf_.set(parameters_buf__key, parameters_buf__value)
            }
            parameters_buf = parameters_buf_
        }
        const parameters_result : Map<string, Object> | undefined = parameters_buf
        const entities_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let entities_buf : Array<string> | undefined
        if ((entities_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const entities_buf__length : int32 = valueDeserializer.readInt32()
            let entities_buf_ : Array<string> = new Array<string>(entities_buf__length)
            for (let entities_buf__i = 0; entities_buf__i < entities_buf__length; entities_buf__i++) {
                entities_buf_[entities_buf__i] = (valueDeserializer.readString() as string)
            }
            entities_buf = entities_buf_
        }
        const entities_result : Array<string> | undefined = entities_buf
        const moduleName_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let moduleName_buf : string | undefined
        if ((moduleName_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            moduleName_buf = (valueDeserializer.readString() as string)
        }
        const moduleName_result : string | undefined = moduleName_buf
        let value : Want = ({bundleName: bundleName_result, abilityName: abilityName_result, deviceId: deviceId_result, uri: uri_result, type: type_result, flags: flags_result, action: action_result, parameters: parameters_result, entities: entities_result, moduleName: moduleName_result} as Want)
        return value
    }
}

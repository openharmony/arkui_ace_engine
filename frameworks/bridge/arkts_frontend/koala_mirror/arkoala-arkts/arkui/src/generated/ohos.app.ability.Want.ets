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
        const valueHolderForBundleName  = value.bundleName
        if (valueHolderForBundleName !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBundleNameTmpValue  = valueHolderForBundleName!
            valueSerializer.writeString(valueHolderForBundleNameTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAbilityName  = value.abilityName
        if (valueHolderForAbilityName !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAbilityNameTmpValue  = valueHolderForAbilityName!
            valueSerializer.writeString(valueHolderForAbilityNameTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDeviceId  = value.deviceId
        if (valueHolderForDeviceId !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDeviceIdTmpValue  = valueHolderForDeviceId!
            valueSerializer.writeString(valueHolderForDeviceIdTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForUri  = value.uri
        if (valueHolderForUri !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForUriTmpValue  = valueHolderForUri!
            valueSerializer.writeString(valueHolderForUriTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForType  = value.type
        if (valueHolderForType !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTypeTmpValue  = valueHolderForType!
            valueSerializer.writeString(valueHolderForTypeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFlags  = value.flags
        if (valueHolderForFlags !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFlagsTmpValue  = valueHolderForFlags!
            valueSerializer.writeNumber(valueHolderForFlagsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAction  = value.action
        if (valueHolderForAction !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForActionTmpValue  = valueHolderForAction!
            valueSerializer.writeString(valueHolderForActionTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForParameters  = value.parameters
        if (valueHolderForParameters !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForParametersTmpValue  = valueHolderForParameters!
            valueSerializer.writeInt32((valueHolderForParametersTmpValue.size).toInt())
            for (const pair of valueHolderForParametersTmpValue) {
                const valueHolderForParametersTmpValueKeyVar = pair[0]
                const valueHolderForParametersTmpValueValueVar = pair[1]
                valueSerializer.writeString(valueHolderForParametersTmpValueKeyVar)
                valueSerializer.holdAndWriteObject(valueHolderForParametersTmpValueValueVar)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEntities  = value.entities
        if (valueHolderForEntities !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEntitiesTmpValue  = valueHolderForEntities!
            valueSerializer.writeInt32((valueHolderForEntitiesTmpValue.length).toInt())
            for (let valueHolderForEntitiesTmpValueCounterI = 0; valueHolderForEntitiesTmpValueCounterI < valueHolderForEntitiesTmpValue.length; valueHolderForEntitiesTmpValueCounterI++) {
                const valueHolderForEntitiesTmpValueTmpElement : string = valueHolderForEntitiesTmpValue[valueHolderForEntitiesTmpValueCounterI]
                valueSerializer.writeString(valueHolderForEntitiesTmpValueTmpElement)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForModuleName  = value.moduleName
        if (valueHolderForModuleName !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForModuleNameTmpValue  = valueHolderForModuleName!
            valueSerializer.writeString(valueHolderForModuleNameTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): Want {
        let valueDeserializer : DeserializerBase = buffer
        const bundleNameTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bundleNameTmpBuf : string | undefined
        if ((bundleNameTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            bundleNameTmpBuf = (valueDeserializer.readString() as string)
        }
        const bundleNameTmpResult : string | undefined = bundleNameTmpBuf
        const abilityNameTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let abilityNameTmpBuf : string | undefined
        if ((abilityNameTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            abilityNameTmpBuf = (valueDeserializer.readString() as string)
        }
        const abilityNameTmpResult : string | undefined = abilityNameTmpBuf
        const deviceIdTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let deviceIdTmpBuf : string | undefined
        if ((deviceIdTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            deviceIdTmpBuf = (valueDeserializer.readString() as string)
        }
        const deviceIdTmpResult : string | undefined = deviceIdTmpBuf
        const uriTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let uriTmpBuf : string | undefined
        if ((uriTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            uriTmpBuf = (valueDeserializer.readString() as string)
        }
        const uriTmpResult : string | undefined = uriTmpBuf
        const typeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let typeTmpBuf : string | undefined
        if ((typeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            typeTmpBuf = (valueDeserializer.readString() as string)
        }
        const typeTmpResult : string | undefined = typeTmpBuf
        const flagsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let flagsTmpBuf : number | undefined
        if ((flagsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            flagsTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const flagsTmpResult : number | undefined = flagsTmpBuf
        const actionTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let actionTmpBuf : string | undefined
        if ((actionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            actionTmpBuf = (valueDeserializer.readString() as string)
        }
        const actionTmpResult : string | undefined = actionTmpBuf
        const parametersTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let parametersTmpBuf : Map<string, Object> | undefined
        if ((parametersTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const parametersTmpBuf_SizeVar : int32 = valueDeserializer.readInt32()
            let parametersTmpBuf_ : Map<string, Object> = new Map<string, Object>()
            // TODO: TS map resize
            for (let parametersTmpBuf_IVar = 0; parametersTmpBuf_IVar < parametersTmpBuf_SizeVar; parametersTmpBuf_IVar++) {
                const parametersTmpBuf_KeyVar : string = (valueDeserializer.readString() as string)
                const parametersTmpBuf_ValueVar : Object = (valueDeserializer.readObject() as object)
                parametersTmpBuf_.set(parametersTmpBuf_KeyVar, parametersTmpBuf_ValueVar)
            }
            parametersTmpBuf = parametersTmpBuf_
        }
        const parametersTmpResult : Map<string, Object> | undefined = parametersTmpBuf
        const entitiesTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let entitiesTmpBuf : Array<string> | undefined
        if ((entitiesTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const entitiesTmpBuf_Length : int32 = valueDeserializer.readInt32()
            let entitiesTmpBuf_ : Array<string> = new Array<string>(entitiesTmpBuf_Length)
            for (let entitiesTmpBuf_BufCounterI = 0; entitiesTmpBuf_BufCounterI < entitiesTmpBuf_Length; entitiesTmpBuf_BufCounterI++) {
                entitiesTmpBuf_[entitiesTmpBuf_BufCounterI] = (valueDeserializer.readString() as string)
            }
            entitiesTmpBuf = entitiesTmpBuf_
        }
        const entitiesTmpResult : Array<string> | undefined = entitiesTmpBuf
        const moduleNameTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let moduleNameTmpBuf : string | undefined
        if ((moduleNameTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            moduleNameTmpBuf = (valueDeserializer.readString() as string)
        }
        const moduleNameTmpResult : string | undefined = moduleNameTmpBuf
        let value : Want = ({bundleName: bundleNameTmpResult, abilityName: abilityNameTmpResult, deviceId: deviceIdTmpResult, uri: uriTmpResult, type: typeTmpResult, flags: flagsTmpResult, action: actionTmpResult, parameters: parametersTmpResult, entities: entitiesTmpResult, moduleName: moduleNameTmpResult} as Want)
        return value
    }
}

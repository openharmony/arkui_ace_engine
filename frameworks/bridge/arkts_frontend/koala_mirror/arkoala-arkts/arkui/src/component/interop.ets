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
import { ExtendableComponent, ExtendableComponentInternal } from "./extendableComponent"
import { GlobalScope } from "./../generated/GlobalScope"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { TypeChecker } from "#components"
import { CallbackTransformer } from "./../CallbackTransformer"
export interface CompatibleComponentInfo {
    name: string;
    component: object;
}
export type CompatibleInitCallback = () => CompatibleComponentInfo;
export type CompatibleUpdateCallback = (component: object) => void;
export function compatibleComponent(init: CompatibleInitCallback, update: CompatibleUpdateCallback, component?: ExtendableComponent | undefined): void {
    GlobalScope.compatibleComponent(init, update, component)
}
export function bindCompatibleProvideCallback(component: ExtendableComponent, createCompatibleState: object, setCallback: object, compatibleComponent?: object | undefined): void {
    GlobalScope.bindCompatibleProvideCallback(component, createCompatibleState, setCallback, compatibleComponent)
}
export function getCompatibleState<T>(state: object, createCompatibleState: object): object {
    return GlobalScope.getCompatibleState(state, createCompatibleState)
}
export function compatibleWrappedBuilder(builder: object, args: object): void {
    GlobalScope.compatibleWrappedBuilder(builder, args)
}
export class CompatibleComponentInfo_serializer {
    public static write(buffer: SerializerBase, value: CompatibleComponentInfo): void {
        let valueSerializer : SerializerBase = buffer
        const value_name  = value.name
        valueSerializer.writeString(value_name)
        const value_component  = value.component
        valueSerializer.writeCustomObject("object", value_component)
    }
    public static read(buffer: DeserializerBase): CompatibleComponentInfo {
        let valueDeserializer : DeserializerBase = buffer
        const name_result : string = (valueDeserializer.readString() as string)
        const component_result : object = (valueDeserializer.readCustomObject("object") as object)
        let value : CompatibleComponentInfo = ({name: name_result, component: component_result} as CompatibleComponentInfo)
        return value
    }
}

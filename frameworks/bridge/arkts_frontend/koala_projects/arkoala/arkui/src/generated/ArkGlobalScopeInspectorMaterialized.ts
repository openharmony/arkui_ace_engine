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

import { Finalizable, isResource, isInstanceOf, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, KPointer, MaterializedBase } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class GlobalScope_inspector {
    public static getInspectorNodes(): Object {
        return GlobalScope_inspector.getInspectorNodes_serialize()
    }
    public static getInspectorNodeById(id: number): Object {
        const id_casted = id as (number)
        return GlobalScope_inspector.getInspectorNodeById_serialize(id_casted)
    }
    public static setAppBgColor(value: string): void {
        const value_casted = value as (string)
        GlobalScope_inspector.setAppBgColor_serialize(value_casted)
        return
    }
    private static getInspectorNodes_serialize(): Object {
        const retval = ArkUIGeneratedNativeModule._GlobalScope_inspector_getInspectorNodes()
        throw new Error("Object deserialization is not implemented.")
    }
    private static getInspectorNodeById_serialize(id: number): Object {
        const retval = ArkUIGeneratedNativeModule._GlobalScope_inspector_getInspectorNodeById(id)
        throw new Error("Object deserialization is not implemented.")
    }
    private static setAppBgColor_serialize(value: string): void {
        ArkUIGeneratedNativeModule._GlobalScope_inspector_setAppBgColor(value)
    }
}

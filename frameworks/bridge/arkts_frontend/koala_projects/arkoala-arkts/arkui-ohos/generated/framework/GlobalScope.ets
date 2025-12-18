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

import { SerializerBase, DeserializerBase, NativeBuffer, Finalizable, RuntimeType, MaterializedBase, KPointer, toPeerPtr } from '@koalaui/interop'
import { global_resource_Resource_serializer } from './resource'
import { AnimateParam_serializer, AnimateParam, CommonMethod, PointerStyle as arkui_component_common_PointerStyle } from './../component/common'
import { ComponentInfo_serializer, ComponentInfo } from './../component/idlize'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { CallbackTransformer } from './../CallbackTransformer'
import { CallbackKind } from './peers/CallbackKind'
import { ArkUIGeneratedNativeModule } from '#components'
import { RecordData, Callback as ohos_base_Callback } from '@ohos.base'
import { Resource as global_resource_Resource } from 'global.resource'
import { CustomStyles } from '#handwritten'
import { default as pointer } from '@ohos.multimodalInput.pointer'
export class GlobalScope {
    public static postCardAction(component: Object, action: Object): void {
        const component_casted = component as (Object)
        const action_casted = action as (Object)
        GlobalScope.postCardAction_serialize(component_casted, action_casted)
        return
    }
    static postCardAction_serialize(component: Object, action: Object): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(component)
        thisSerializer.holdAndWriteObject(action)
        ArkUIGeneratedNativeModule._GlobalScope_postCardAction(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static $r(value: string, params: Array<RecordData>): global_resource_Resource {
        const value_casted = value as (string)
        const params_casted = params as (Array<RecordData>)
        return GlobalScope.$r_serialize(value_casted, params_casted)
    }
    static $r_serialize(value: string, params: Array<RecordData>): global_resource_Resource {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((params.length).toInt())
        for (let paramsCounterI = 0; paramsCounterI < params.length; paramsCounterI++) {
            const paramsTmpElement : RecordData = params[paramsCounterI]
            if (paramsTmpElement !== undefined && paramsTmpElement !== null) {
                thisSerializer.writeInt8(RuntimeType.OBJECT)
                const paramsTmpElementTmpValue  = paramsTmpElement!
                thisSerializer.holdAndWriteObject(paramsTmpElementTmpValue)
            } else {
                thisSerializer.writeInt8(RuntimeType.UNDEFINED)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_$r(value, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : global_resource_Resource = global_resource_Resource_serializer.read(retvalDeserializer)
        return returnResult
    }
    public static $rawfile(value: string): global_resource_Resource {
        const value_casted = value as (string)
        return GlobalScope.$rawfile_serialize(value_casted)
    }
    static $rawfile_serialize(value: string): global_resource_Resource {
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_$rawfile(value)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : global_resource_Resource = global_resource_Resource_serializer.read(retvalDeserializer)
        return returnResult
    }
    public static animateTo(value: AnimateParam, event: (() => void)): void {
        const value_casted = value as (AnimateParam)
        const event_casted = event as ((() => void))
        GlobalScope.animateTo_serialize(value_casted, event_casted)
        return
    }
    static animateTo_serialize(value: AnimateParam, event: (() => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        AnimateParam_serializer.write(thisSerializer, value)
        thisSerializer.holdAndWriteCallback(event)
        ArkUIGeneratedNativeModule._GlobalScope_animateTo(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static animateToImmediately(value: AnimateParam, event: (() => void)): void {
        const value_casted = value as (AnimateParam)
        const event_casted = event as ((() => void))
        GlobalScope.animateToImmediately_serialize(value_casted, event_casted)
        return
    }
    static animateToImmediately_serialize(value: AnimateParam, event: (() => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        AnimateParam_serializer.write(thisSerializer, value)
        thisSerializer.holdAndWriteCallback(event)
        ArkUIGeneratedNativeModule._GlobalScope_animateToImmediately(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static setAppBgColor(value: string): void {
        const value_casted = value as (string)
        GlobalScope.setAppBgColor_serialize(value_casted)
        return
    }
    static setAppBgColor_serialize(value: string): void {
        ArkUIGeneratedNativeModule._GlobalScope_setAppBgColor(value)
    }
    public static getRectangleById(id: string): ComponentInfo {
        const id_casted = id as (string)
        return GlobalScope.getRectangleById_serialize(id_casted)
    }
    static getRectangleById_serialize(id: string): ComponentInfo {
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_getRectangleById(id)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : ComponentInfo = ComponentInfo_serializer.read(retvalDeserializer)
        return returnResult
    }
    public static Profiler_registerVsyncCallback(callback_: ohos_base_Callback<string>): void {
        const callback__casted = callback_ as (ohos_base_Callback<string>)
        GlobalScope.Profiler_registerVsyncCallback_serialize(callback__casted)
        return
    }
    static Profiler_registerVsyncCallback_serialize(callback_: ohos_base_Callback<string>): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._GlobalScope_Profiler_registerVsyncCallback(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static Profiler_unregisterVsyncCallback(): void {
        GlobalScope.Profiler_unregisterVsyncCallback_serialize()
        return
    }
    static Profiler_unregisterVsyncCallback_serialize(): void {
        ArkUIGeneratedNativeModule._GlobalScope_Profiler_unregisterVsyncCallback()
    }
    public static cursorControl_setCursor(value: arkui_component_common_PointerStyle): void {
        const value_casted = value as (arkui_component_common_PointerStyle)
        GlobalScope.cursorControl_setCursor_serialize(value_casted)
        return
    }
    static cursorControl_setCursor_serialize(value: arkui_component_common_PointerStyle): void {
        ArkUIGeneratedNativeModule._GlobalScope_cursorControl_setCursor(value.valueOf())
    }
    public static cursorControl_restoreDefault(): void {
        GlobalScope.cursorControl_restoreDefault_serialize()
        return
    }
    static cursorControl_restoreDefault_serialize(): void {
        ArkUIGeneratedNativeModule._GlobalScope_cursorControl_restoreDefault()
    }
    public static focusControl_requestFocus(value: string): boolean {
        const value_casted = value as (string)
        return GlobalScope.focusControl_requestFocus_serialize(value_casted)
    }
    static focusControl_requestFocus_serialize(value: string): boolean {
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_focusControl_requestFocus(value)
        return retval
    }
}

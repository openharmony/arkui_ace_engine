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

import { SerializerBase, DeserializerBase, NativeBuffer, Finalizable, runtimeType, RuntimeType, MaterializedBase, KPointer, toPeerPtr } from "@koalaui/interop"
import { Resource_serializer } from "./resource"
import { AnimateParam_serializer, AnimateParam, FinishCallbackType, ExpectedFrameRateRange } from "./../component/common"
import { ComponentInfo_serializer, ComponentInfo, Offset_componentutils, TranslateResult, ScaleResult, RotateResult, Matrix4Result } from "./../component/idlize"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { Resource } from "global.resource"
import { default as curves } from "@ohos.curves"
import { extractors } from "#handwritten"
import { PlayMode } from "./../component/enums"
import { Size } from "arkui.Graphics"
import { default as pointer } from "@ohos.multimodalInput.pointer"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
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
    public static $r(value: string, params: Array<Object | null | undefined>): Resource {
        const value_casted = value as (string)
        const params_casted = params as (Array<Object | null | undefined>)
        return GlobalScope.$r_serialize(value_casted, params_casted)
    }
    static $r_serialize(value: string, params: Array<Object | null | undefined>): Resource {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((params.length).toInt())
        for (let paramsCounterI = 0; paramsCounterI < params.length; paramsCounterI++) {
            const paramsTmpElement : Object | null | undefined = params[paramsCounterI]
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
        const returnResult : Resource = Resource_serializer.read(retvalDeserializer)
        return returnResult
    }
    public static $rawfile(value: string): Resource {
        const value_casted = value as (string)
        return GlobalScope.$rawfile_serialize(value_casted)
    }
    static $rawfile_serialize(value: string): Resource {
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_$rawfile(value)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : Resource = Resource_serializer.read(retvalDeserializer)
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
    public static vp2px(value: number): number {
        const value_casted = value as (number)
        return GlobalScope.vp2px_serialize(value_casted)
    }
    static vp2px_serialize(value: number): number {
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_vp2px(value)
        return retval
    }
    public static px2vp(value: number): number {
        const value_casted = value as (number)
        return GlobalScope.px2vp_serialize(value_casted)
    }
    static px2vp_serialize(value: number): number {
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_px2vp(value)
        return retval
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
    public static Profiler_registerVsyncCallback(callback_: ((value0: string) => void)): void {
        const callback__casted = callback_ as (((value0: string) => void))
        GlobalScope.Profiler_registerVsyncCallback_serialize(callback__casted)
        return
    }
    static Profiler_registerVsyncCallback_serialize(callback_: ((value0: string) => void)): void {
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
    public static cursorControl_setCursor(value: pointer.PointerStyle): void {
        const value_casted = value as (pointer.PointerStyle)
        GlobalScope.cursorControl_setCursor_serialize(value_casted)
        return
    }
    static cursorControl_setCursor_serialize(value: pointer.PointerStyle): void {
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

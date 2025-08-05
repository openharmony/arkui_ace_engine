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

import { Edges_serializer, BorderRadiuses_serializer, Edges, Dimension, BorderRadiuses, Length } from "./../component/units"
import { SerializerBase, DeserializerBase, NativeBuffer, Finalizable, runtimeType, RuntimeType, MaterializedBase, KPointer, toPeerPtr } from "@koalaui/interop"
import { Resource_serializer, Resource } from "./resource"
import { AnimateParam_serializer, AnimateParam, FinishCallbackType, ExpectedFrameRateRange } from "./../component/common"
import { ComponentInfo_serializer, ComponentInfo, Offset_componentutils, TranslateResult, ScaleResult, RotateResult, Matrix4Result } from "./../component/idlize"
import { uiEffect_BrightnessBlenderParam_serializer, uiEffect_BrightnessBlender_serializer, uiEffect } from "./ohos.graphics.uiEffect"
import { text_FontDescriptor_serializer, text } from "./ohos.graphics.text"
import { font_UIFontConfig_serializer, font } from "./ohos.font"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { BorderStyle, PlayMode } from "./../component/enums"
import { curves } from "./ohos.curves"
import { Size } from "./arkui.Graphics"
import { pointer } from "./ohos.multimodalInput.pointer"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
export class GlobalScope {
    public static edgeColors(all: number): Edges {
        const all_casted = all as (number)
        return GlobalScope.edgeColors_serialize(all_casted)
    }
    static edgeColors_serialize(all: number): Edges {
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_edgeColors(all)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : Edges = Edges_serializer.read(retvalDeserializer)
        return returnResult
    }
    public static edgeWidths(all: number): Edges {
        const all_casted = all as (number)
        return GlobalScope.edgeWidths_serialize(all_casted)
    }
    static edgeWidths_serialize(all: number): Edges {
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_edgeWidths(all)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : Edges = Edges_serializer.read(retvalDeserializer)
        return returnResult
    }
    public static borderStyles(all: BorderStyle): Edges {
        const all_casted = all as (BorderStyle)
        return GlobalScope.borderStyles_serialize(all_casted)
    }
    static borderStyles_serialize(all: BorderStyle): Edges {
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_borderStyles(TypeChecker.BorderStyle_ToNumeric(all))
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : Edges = Edges_serializer.read(retvalDeserializer)
        return returnResult
    }
    public static borderRadiuses(all: number): BorderRadiuses {
        const all_casted = all as (number)
        return GlobalScope.borderRadiuses_serialize(all_casted)
    }
    static borderRadiuses_serialize(all: number): BorderRadiuses {
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_borderRadiuses(all)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : BorderRadiuses = BorderRadiuses_serializer.read(retvalDeserializer)
        return returnResult
    }
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
    public static $r(value: string, params: Array<Object | undefined>): Resource {
        const value_casted = value as (string)
        const params_casted = params as (Array<Object | undefined>)
        return GlobalScope.$r_serialize(value_casted, params_casted)
    }
    static $r_serialize(value: string, params: Array<Object | undefined>): Resource {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((params.length).toInt())
        for (let paramsCounterI = 0; paramsCounterI < params.length; paramsCounterI++) {
            const paramsTmpElement : Object | undefined = params[paramsCounterI]
            if (paramsTmpElement !== undefined) {
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
    public static Profiler_registerVsyncCallback(callback_: ((info: string) => void)): void {
        const callback__casted = callback_ as (((info: string) => void))
        GlobalScope.Profiler_registerVsyncCallback_serialize(callback__casted)
        return
    }
    static Profiler_registerVsyncCallback_serialize(callback_: ((info: string) => void)): void {
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
        ArkUIGeneratedNativeModule._GlobalScope_cursorControl_setCursor(TypeChecker.pointer_PointerStyle_ToNumeric(value))
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
    public static uiEffect_createEffect(): uiEffect.VisualEffect {
        return GlobalScope.uiEffect_createEffect_serialize()
    }
    static uiEffect_createEffect_serialize(): uiEffect.VisualEffect {
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_uiEffect_createEffect()
        const obj : uiEffect.VisualEffect = uiEffect.VisualEffectInternal.fromPtr(retval)
        return obj
    }
    public static uiEffect_createBrightnessBlender(param: uiEffect.BrightnessBlenderParam): uiEffect.BrightnessBlender {
        const param_casted = param as (uiEffect.BrightnessBlenderParam)
        return GlobalScope.uiEffect_createBrightnessBlender_serialize(param_casted)
    }
    static uiEffect_createBrightnessBlender_serialize(param: uiEffect.BrightnessBlenderParam): uiEffect.BrightnessBlender {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        uiEffect_BrightnessBlenderParam_serializer.write(thisSerializer, param)
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_uiEffect_createBrightnessBlender(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : uiEffect.BrightnessBlender = uiEffect_BrightnessBlender_serializer.read(retvalDeserializer)
        return returnResult
    }
    public static text_getSystemFontFullNamesByType(fontType: text.SystemFontType): Promise<Array<string>> {
        const fontType_casted = fontType as (text.SystemFontType)
        return GlobalScope.text_getSystemFontFullNamesByType_serialize(fontType_casted)
    }
    static text_getSystemFontFullNamesByType_serialize(fontType: text.SystemFontType): Promise<Array<string>> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        const retval  = thisSerializer.holdAndWriteCallbackForPromise<Array<string>>()[0]
        ArkUIGeneratedNativeModule._GlobalScope_text_getSystemFontFullNamesByType(TypeChecker.text_SystemFontType_ToNumeric(fontType), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    public static text_getFontDescriptorByFullName(fullName: string, fontType: text.SystemFontType): Promise<text.FontDescriptor> {
        const fullName_casted = fullName as (string)
        const fontType_casted = fontType as (text.SystemFontType)
        return GlobalScope.text_getFontDescriptorByFullName_serialize(fullName_casted, fontType_casted)
    }
    static text_getFontDescriptorByFullName_serialize(fullName: string, fontType: text.SystemFontType): Promise<text.FontDescriptor> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        const retval  = thisSerializer.holdAndWriteCallbackForPromise<text.FontDescriptor>()[0]
        ArkUIGeneratedNativeModule._GlobalScope_text_getFontDescriptorByFullName(fullName, TypeChecker.text_SystemFontType_ToNumeric(fontType), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    public static text_matchFontDescriptors(desc: text.FontDescriptor): Promise<Array<text.FontDescriptor>> {
        const desc_casted = desc as (text.FontDescriptor)
        return GlobalScope.text_matchFontDescriptors_serialize(desc_casted)
    }
    static text_matchFontDescriptors_serialize(desc: text.FontDescriptor): Promise<Array<text.FontDescriptor>> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        text_FontDescriptor_serializer.write(thisSerializer, desc)
        const retval  = thisSerializer.holdAndWriteCallbackForPromise<Array<text.FontDescriptor>>()[0]
        ArkUIGeneratedNativeModule._GlobalScope_text_matchFontDescriptors(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    public static font_getUIFontConfig(): font.UIFontConfig {
        return GlobalScope.font_getUIFontConfig_serialize()
    }
    static font_getUIFontConfig_serialize(): font.UIFontConfig {
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_font_getUIFontConfig()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : font.UIFontConfig = font_UIFontConfig_serializer.read(retvalDeserializer)
        return returnResult
    }
    public static curves_initCurve(curve: curves.Curve | undefined): curves.ICurve {
        const curve_casted = curve as (curves.Curve | undefined)
        return GlobalScope.curves_initCurve_serialize(curve_casted)
    }
    static curves_initCurve_serialize(curve: curves.Curve | undefined): curves.ICurve {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (curve !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const curveTmpValue  = (curve as curves.Curve)
            thisSerializer.writeInt32(TypeChecker.curves_Curve_ToNumeric(curveTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_curves_initCurve(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : curves.ICurve = curves.ICurveInternal.fromPtr(retval)
        return obj
    }
    public static curves_stepsCurve(count: number, end: boolean): curves.ICurve {
        const count_casted = count as (number)
        const end_casted = end as (boolean)
        return GlobalScope.curves_stepsCurve_serialize(count_casted, end_casted)
    }
    static curves_stepsCurve_serialize(count: number, end: boolean): curves.ICurve {
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_curves_stepsCurve(count, end ? 1 : 0)
        const obj : curves.ICurve = curves.ICurveInternal.fromPtr(retval)
        return obj
    }
    public static curves_customCurve(interpolate: ((fraction: number) => number)): curves.ICurve {
        const interpolate_casted = interpolate as (((fraction: number) => number))
        return GlobalScope.curves_customCurve_serialize(interpolate_casted)
    }
    static curves_customCurve_serialize(interpolate: ((fraction: number) => number)): curves.ICurve {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(interpolate)
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_curves_customCurve(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : curves.ICurve = curves.ICurveInternal.fromPtr(retval)
        return obj
    }
    public static curves_cubicBezierCurve(x1: number, y1: number, x2: number, y2: number): curves.ICurve {
        const x1_casted = x1 as (number)
        const y1_casted = y1 as (number)
        const x2_casted = x2 as (number)
        const y2_casted = y2 as (number)
        return GlobalScope.curves_cubicBezierCurve_serialize(x1_casted, y1_casted, x2_casted, y2_casted)
    }
    static curves_cubicBezierCurve_serialize(x1: number, y1: number, x2: number, y2: number): curves.ICurve {
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_curves_cubicBezierCurve(x1, y1, x2, y2)
        const obj : curves.ICurve = curves.ICurveInternal.fromPtr(retval)
        return obj
    }
    public static curves_springCurve(velocity: number, mass: number, stiffness: number, damping: number): curves.ICurve {
        const velocity_casted = velocity as (number)
        const mass_casted = mass as (number)
        const stiffness_casted = stiffness as (number)
        const damping_casted = damping as (number)
        return GlobalScope.curves_springCurve_serialize(velocity_casted, mass_casted, stiffness_casted, damping_casted)
    }
    static curves_springCurve_serialize(velocity: number, mass: number, stiffness: number, damping: number): curves.ICurve {
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_curves_springCurve(velocity, mass, stiffness, damping)
        const obj : curves.ICurve = curves.ICurveInternal.fromPtr(retval)
        return obj
    }
    public static curves_springMotion(response: number | undefined, dampingFraction: number | undefined, overlapDuration: number | undefined): curves.ICurve {
        const response_casted = response as (number | undefined)
        const dampingFraction_casted = dampingFraction as (number | undefined)
        const overlapDuration_casted = overlapDuration as (number | undefined)
        return GlobalScope.curves_springMotion_serialize(response_casted, dampingFraction_casted, overlapDuration_casted)
    }
    static curves_springMotion_serialize(response: number | undefined, dampingFraction: number | undefined, overlapDuration: number | undefined): curves.ICurve {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (response !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const responseTmpValue  = response!
            thisSerializer.writeNumber(responseTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (dampingFraction !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const dampingFractionTmpValue  = dampingFraction!
            thisSerializer.writeNumber(dampingFractionTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (overlapDuration !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const overlapDurationTmpValue  = overlapDuration!
            thisSerializer.writeNumber(overlapDurationTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_curves_springMotion(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : curves.ICurve = curves.ICurveInternal.fromPtr(retval)
        return obj
    }
    public static curves_responsiveSpringMotion(response: number | undefined, dampingFraction: number | undefined, overlapDuration: number | undefined): curves.ICurve {
        const response_casted = response as (number | undefined)
        const dampingFraction_casted = dampingFraction as (number | undefined)
        const overlapDuration_casted = overlapDuration as (number | undefined)
        return GlobalScope.curves_responsiveSpringMotion_serialize(response_casted, dampingFraction_casted, overlapDuration_casted)
    }
    static curves_responsiveSpringMotion_serialize(response: number | undefined, dampingFraction: number | undefined, overlapDuration: number | undefined): curves.ICurve {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (response !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const responseTmpValue  = response!
            thisSerializer.writeNumber(responseTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (dampingFraction !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const dampingFractionTmpValue  = dampingFraction!
            thisSerializer.writeNumber(dampingFractionTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (overlapDuration !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const overlapDurationTmpValue  = overlapDuration!
            thisSerializer.writeNumber(overlapDurationTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_curves_responsiveSpringMotion(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : curves.ICurve = curves.ICurveInternal.fromPtr(retval)
        return obj
    }
    public static curves_interpolatingSpring(velocity: number, mass: number, stiffness: number, damping: number): curves.ICurve {
        const velocity_casted = velocity as (number)
        const mass_casted = mass as (number)
        const stiffness_casted = stiffness as (number)
        const damping_casted = damping as (number)
        return GlobalScope.curves_interpolatingSpring_serialize(velocity_casted, mass_casted, stiffness_casted, damping_casted)
    }
    static curves_interpolatingSpring_serialize(velocity: number, mass: number, stiffness: number, damping: number): curves.ICurve {
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_curves_interpolatingSpring(velocity, mass, stiffness, damping)
        const obj : curves.ICurve = curves.ICurveInternal.fromPtr(retval)
        return obj
    }
}

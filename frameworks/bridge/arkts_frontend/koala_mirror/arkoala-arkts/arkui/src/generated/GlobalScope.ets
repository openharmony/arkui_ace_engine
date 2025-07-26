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
import { SerializerBase, DeserializerBase, NativeBuffer, Finalizable, runtimeType, RuntimeType, MaterializedBase, registerCallback, wrapCallback, KPointer, toPeerPtr } from "@koalaui/interop"
import { Resource_serializer, Resource } from "./resource"
import { AnimateParam_serializer, AnimateParam, FinishCallbackType, ExpectedFrameRateRange, CustomStyles } from "./../component/common"
import { ExtendableComponent_serializer, ExtendableComponent, LifeCycle, ExtendableComponentInternal } from "./../component/extendableComponent"
import { ComponentInfo_serializer, ComponentInfo, Offset_componentutils, TranslateResult, ScaleResult, RotateResult, Matrix4Result } from "./../component/idlize"
import { uiEffect_BrightnessBlenderParam_serializer, uiEffect_BrightnessBlender_serializer, uiEffect } from "./ohos.graphics.uiEffect"
import { text_FontDescriptor_serializer, text } from "./ohos.graphics.text"
import { font_UIFontConfig_serializer, font } from "./ohos.font"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { BorderStyle, PlayMode } from "./../component/enums"
import { curves } from "./ohos.curves"
import { CompatibleInitCallback, CompatibleComponentInfo, CompatibleUpdateCallback } from "./../component/interop"
import { UIContext } from "./ohos.arkui.UIContext"
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
        for (let params_counter_i = 0; params_counter_i < params.length; params_counter_i++) {
            const params_element : Object | undefined = params[params_counter_i]
            let params_element_type : int32 = RuntimeType.UNDEFINED
            params_element_type = runtimeType(params_element)
            thisSerializer.writeInt8((params_element_type).toChar())
            if ((params_element_type) != (RuntimeType.UNDEFINED)) {
                const params_element_value  = params_element!
                thisSerializer.holdAndWriteObject(params_element_value)
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
    public static applyStyles<T>(self: T, customStyles: CustomStyles): T {
        const self_casted = self as (T)
        const customStyles_casted = customStyles as (CustomStyles)
        return GlobalScope.applyStyles_serialize(self_casted, customStyles_casted)
    }
    static applyStyles_serialize<T>(self: T, customStyles: CustomStyles): T {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeCustomObject("T", (self as Object))
        thisSerializer.holdAndWriteCallback(customStyles)
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_applyStyles(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        throw new Error("Object deserialization is not implemented.")
    }
    public static setAppBgColor(value: string): void {
        const value_casted = value as (string)
        GlobalScope.setAppBgColor_serialize(value_casted)
        return
    }
    static setAppBgColor_serialize(value: string): void {
        ArkUIGeneratedNativeModule._GlobalScope_setAppBgColor(value)
    }
    public static compatibleComponent(init: CompatibleInitCallback, update: CompatibleUpdateCallback, component: ExtendableComponent | undefined): void {
        const init_casted = init as (CompatibleInitCallback)
        const update_casted = update as (CompatibleUpdateCallback)
        const component_casted = component as (ExtendableComponent | undefined)
        GlobalScope.compatibleComponent_serialize(init_casted, update_casted, component_casted)
        return
    }
    static compatibleComponent_serialize(init: CompatibleInitCallback, update: CompatibleUpdateCallback, component: ExtendableComponent | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(init)
        thisSerializer.holdAndWriteCallback(update)
        let component_type : int32 = RuntimeType.UNDEFINED
        component_type = runtimeType(component)
        thisSerializer.writeInt8((component_type).toChar())
        if ((component_type) != (RuntimeType.UNDEFINED)) {
            const component_value  = component!
            ExtendableComponent_serializer.write(thisSerializer, component_value)
        }
        ArkUIGeneratedNativeModule._GlobalScope_compatibleComponent(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static bindCompatibleProvideCallback(component: ExtendableComponent, createCompatibleState: object, setCallback: object, compatibleComponent: object | undefined): void {
        const component_casted = component as (ExtendableComponent)
        const createCompatibleState_casted = createCompatibleState as (object)
        const setCallback_casted = setCallback as (object)
        const compatibleComponent_casted = compatibleComponent as (object | undefined)
        GlobalScope.bindCompatibleProvideCallback_serialize(component_casted, createCompatibleState_casted, setCallback_casted, compatibleComponent_casted)
        return
    }
    static bindCompatibleProvideCallback_serialize(component: ExtendableComponent, createCompatibleState: object, setCallback: object, compatibleComponent: object | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeCustomObject("object", createCompatibleState)
        thisSerializer.writeCustomObject("object", setCallback)
        let compatibleComponent_type : int32 = RuntimeType.UNDEFINED
        compatibleComponent_type = runtimeType(compatibleComponent)
        thisSerializer.writeInt8((compatibleComponent_type).toChar())
        if ((compatibleComponent_type) != (RuntimeType.UNDEFINED)) {
            const compatibleComponent_value  = compatibleComponent!
            thisSerializer.writeCustomObject("object", compatibleComponent_value)
        }
        ArkUIGeneratedNativeModule._GlobalScope_bindCompatibleProvideCallback(toPeerPtr(component), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static getCompatibleState<T>(state: object, createCompatibleState: object): object {
        const state_casted = state as (object)
        const createCompatibleState_casted = createCompatibleState as (object)
        return GlobalScope.getCompatibleState_serialize(state_casted, createCompatibleState_casted)
    }
    static getCompatibleState_serialize<T>(state: object, createCompatibleState: object): object {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeCustomObject("object", state)
        thisSerializer.writeCustomObject("object", createCompatibleState)
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_getCompatibleState(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        throw new Error("Object deserialization is not implemented.")
    }
    public static compatibleWrappedBuilder(builder: object, args: object): void {
        const builder_casted = builder as (object)
        const args_casted = args as (object)
        GlobalScope.compatibleWrappedBuilder_serialize(builder_casted, args_casted)
        return
    }
    static compatibleWrappedBuilder_serialize(builder: object, args: object): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeCustomObject("object", builder)
        thisSerializer.writeCustomObject("object", args)
        ArkUIGeneratedNativeModule._GlobalScope_compatibleWrappedBuilder(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
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
}

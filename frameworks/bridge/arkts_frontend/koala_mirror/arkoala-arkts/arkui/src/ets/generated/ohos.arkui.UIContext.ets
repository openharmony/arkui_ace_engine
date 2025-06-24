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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { TextMenuOptions_serializer, TextMenuOptions } from "./textCommon"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { AnimateParam_serializer, SheetOptions_serializer, AnimateParam, SheetOptions } from "./common"
import { TextPickerDialogOptions_serializer, TextPickerDialogOptions } from "./textPicker"
import { FrameNode_serializer, FrameNode, FrameNodeInternal } from "./arkui.FrameNode"
import { common_Context_serializer, common } from "./ohos.app.ability.common"
import { drawing } from "./ohos.graphics.drawing"
import { WidthBreakpoint, HeightBreakpoint } from "./enums"
import { ComponentContent, ComponentContentInternal } from "./arkui.ComponentContent"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
export class TextMenuControllerInternal {
    public static fromPtr(ptr: KPointer): TextMenuController {
        return new TextMenuController(ptr)
    }
}
export class TextMenuController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, TextMenuController.getFinalizer())
    }
    static ctor(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TextMenuController_ctor()
        return retval
    }
    constructor() {
        this(TextMenuController.ctor())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextMenuController_getFinalizer()
    }
    public setMenuOptions(options: TextMenuOptions): void {
        const options_casted = options as (TextMenuOptions)
        this.setMenuOptions_serialize(options_casted)
        return
    }
    private setMenuOptions_serialize(options: TextMenuOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        TextMenuOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._TextMenuController_setMenuOptions(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class UIContextInternal {
    public static fromPtr(ptr: KPointer): UIContext {
        return new UIContext(ptr)
    }
}
export class UIContext implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, UIContext.getFinalizer())
    }
    static ctor(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._UIContext_ctor()
        return retval
    }
    constructor() {
        this(UIContext.ctor())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._UIContext_getFinalizer()
    }
    public getFont(): drawing.Font {
        return this.getFont_serialize()
    }
    public getFilteredInspectorTree(filters?: Array<string>): string {
        const filters_casted = filters as (Array<string> | undefined)
        return this.getFilteredInspectorTree_serialize(filters_casted)
    }
    public getFilteredInspectorTreeById(id: string, depth: number, filters?: Array<string>): string {
        const id_casted = id as (string)
        const depth_casted = depth as (number)
        const filters_casted = filters as (Array<string> | undefined)
        return this.getFilteredInspectorTreeById_serialize(id_casted, depth_casted, filters_casted)
    }
    public animateTo(value: AnimateParam, event: (() => void)): void {
        const value_casted = value as (AnimateParam)
        const event_casted = event as ((() => void))
        this.animateTo_serialize(value_casted, event_casted)
        return
    }
    public showTextPickerDialog(options: TextPickerDialogOptions): void {
        const options_casted = options as (TextPickerDialogOptions)
        this.showTextPickerDialog_serialize(options_casted)
        return
    }
    public runScopedTask(callback_: (() => void)): void {
        const callback__casted = callback_ as ((() => void))
        this.runScopedTask_serialize(callback__casted)
        return
    }
    public animateToImmediately(param: AnimateParam, event: (() => void)): void {
        const param_casted = param as (AnimateParam)
        const event_casted = event as ((() => void))
        this.animateToImmediately_serialize(param_casted, event_casted)
        return
    }
    public getFrameNodeById(id: string): FrameNode | undefined {
        const id_casted = id as (string)
        return this.getFrameNodeById_serialize(id_casted)
    }
    public getAttachedFrameNodeById(id: string): FrameNode | undefined {
        const id_casted = id as (string)
        return this.getAttachedFrameNodeById_serialize(id_casted)
    }
    public getFrameNodeByUniqueId(id: number): FrameNode | undefined {
        const id_casted = id as (number)
        return this.getFrameNodeByUniqueId_serialize(id_casted)
    }
    public vp2px(value: number): number {
        const value_casted = value as (number)
        return this.vp2px_serialize(value_casted)
    }
    public px2vp(value: number): number {
        const value_casted = value as (number)
        return this.px2vp_serialize(value_casted)
    }
    public fp2px(value: number): number {
        const value_casted = value as (number)
        return this.fp2px_serialize(value_casted)
    }
    public px2fp(value: number): number {
        const value_casted = value as (number)
        return this.px2fp_serialize(value_casted)
    }
    public lpx2px(value: number): number {
        const value_casted = value as (number)
        return this.lpx2px_serialize(value_casted)
    }
    public px2lpx(value: number): number {
        const value_casted = value as (number)
        return this.px2lpx_serialize(value_casted)
    }
    public getHostContext(): common.Context | undefined {
        return this.getHostContext_serialize()
    }
    public setDynamicDimming(id: string, value: number): void {
        const id_casted = id as (string)
        const value_casted = value as (number)
        this.setDynamicDimming_serialize(id_casted, value_casted)
        return
    }
    public getWindowName(): string | undefined {
        return this.getWindowName_serialize()
    }
    public getWindowWidthBreakpoint(): WidthBreakpoint {
        return this.getWindowWidthBreakpoint_serialize()
    }
    public getWindowHeightBreakpoint(): HeightBreakpoint {
        return this.getWindowHeightBreakpoint_serialize()
    }
    public openBindSheet<T>(bindSheetContent: ComponentContent, sheetOptions?: SheetOptions, targetId?: number): Promise<void> {
        const bindSheetContent_casted = bindSheetContent as (ComponentContent)
        const sheetOptions_casted = sheetOptions as (SheetOptions | undefined)
        const targetId_casted = targetId as (number | undefined)
        return this.openBindSheet_serialize(bindSheetContent_casted, sheetOptions_casted, targetId_casted)
    }
    public updateBindSheet<T>(bindSheetContent: ComponentContent, sheetOptions: SheetOptions, partialUpdate?: boolean): Promise<void> {
        const bindSheetContent_casted = bindSheetContent as (ComponentContent)
        const sheetOptions_casted = sheetOptions as (SheetOptions)
        const partialUpdate_casted = partialUpdate as (boolean | undefined)
        return this.updateBindSheet_serialize(bindSheetContent_casted, sheetOptions_casted, partialUpdate_casted)
    }
    public closeBindSheet<T>(bindSheetContent: ComponentContent): Promise<void> {
        const bindSheetContent_casted = bindSheetContent as (ComponentContent)
        return this.closeBindSheet_serialize(bindSheetContent_casted)
    }
    public clearResourceCache(): void {
        this.clearResourceCache_serialize()
        return
    }
    public isFollowingSystemFontScale(): boolean {
        return this.isFollowingSystemFontScale_serialize()
    }
    public getMaxFontScale(): number {
        return this.getMaxFontScale_serialize()
    }
    private getFont_serialize(): drawing.Font {
        const retval  = ArkUIGeneratedNativeModule._UIContext_getFont(this.peer!.ptr)
        const obj : drawing.Font = drawing.FontInternal.fromPtr(retval)
        return obj
    }
    private getFilteredInspectorTree_serialize(filters?: Array<string>): string {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let filters_type : int32 = RuntimeType.UNDEFINED
        filters_type = runtimeType(filters)
        thisSerializer.writeInt8(filters_type)
        if ((RuntimeType.UNDEFINED) != (filters_type)) {
            const filters_value  = filters!
            thisSerializer.writeInt32(filters_value.length as int32)
            for (let i = 0; i < filters_value.length; i++) {
                const filters_value_element : string = filters_value[i]
                thisSerializer.writeString(filters_value_element)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._UIContext_getFilteredInspectorTree(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private getFilteredInspectorTreeById_serialize(id: string, depth: number, filters?: Array<string>): string {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let filters_type : int32 = RuntimeType.UNDEFINED
        filters_type = runtimeType(filters)
        thisSerializer.writeInt8(filters_type)
        if ((RuntimeType.UNDEFINED) != (filters_type)) {
            const filters_value  = filters!
            thisSerializer.writeInt32(filters_value.length as int32)
            for (let i = 0; i < filters_value.length; i++) {
                const filters_value_element : string = filters_value[i]
                thisSerializer.writeString(filters_value_element)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._UIContext_getFilteredInspectorTreeById(this.peer!.ptr, id, depth, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private animateTo_serialize(value: AnimateParam, event: (() => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        AnimateParam_serializer.write(thisSerializer, value)
        thisSerializer.holdAndWriteCallback(event)
        ArkUIGeneratedNativeModule._UIContext_animateTo(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private showTextPickerDialog_serialize(options: TextPickerDialogOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        TextPickerDialogOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._UIContext_showTextPickerDialog(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private runScopedTask_serialize(callback_: (() => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._UIContext_runScopedTask(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private animateToImmediately_serialize(param: AnimateParam, event: (() => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        AnimateParam_serializer.write(thisSerializer, param)
        thisSerializer.holdAndWriteCallback(event)
        ArkUIGeneratedNativeModule._UIContext_animateToImmediately(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getFrameNodeById_serialize(id: string): FrameNode | undefined {
        const retval  = ArkUIGeneratedNativeModule._UIContext_getFrameNodeById(this.peer!.ptr, id)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = (retvalDeserializer.readInt8() as int32)
        let buffer : FrameNode | undefined
        if ((RuntimeType.UNDEFINED) != (buffer_runtimeType))
        {
            buffer = (FrameNode_serializer.read(retvalDeserializer) as FrameNode)
        }
        const returnResult : FrameNode | undefined = buffer
        return returnResult
    }
    private getAttachedFrameNodeById_serialize(id: string): FrameNode | undefined {
        const retval  = ArkUIGeneratedNativeModule._UIContext_getAttachedFrameNodeById(this.peer!.ptr, id)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = (retvalDeserializer.readInt8() as int32)
        let buffer : FrameNode | undefined
        if ((RuntimeType.UNDEFINED) != (buffer_runtimeType))
        {
            buffer = (FrameNode_serializer.read(retvalDeserializer) as FrameNode)
        }
        const returnResult : FrameNode | undefined = buffer
        return returnResult
    }
    private getFrameNodeByUniqueId_serialize(id: number): FrameNode | undefined {
        const retval  = ArkUIGeneratedNativeModule._UIContext_getFrameNodeByUniqueId(this.peer!.ptr, id)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = (retvalDeserializer.readInt8() as int32)
        let buffer : FrameNode | undefined
        if ((RuntimeType.UNDEFINED) != (buffer_runtimeType))
        {
            buffer = (FrameNode_serializer.read(retvalDeserializer) as FrameNode)
        }
        const returnResult : FrameNode | undefined = buffer
        return returnResult
    }
    private vp2px_serialize(value: number): number {
        const retval  = ArkUIGeneratedNativeModule._UIContext_vp2px(this.peer!.ptr, value)
        return retval
    }
    private px2vp_serialize(value: number): number {
        const retval  = ArkUIGeneratedNativeModule._UIContext_px2vp(this.peer!.ptr, value)
        return retval
    }
    private fp2px_serialize(value: number): number {
        const retval  = ArkUIGeneratedNativeModule._UIContext_fp2px(this.peer!.ptr, value)
        return retval
    }
    private px2fp_serialize(value: number): number {
        const retval  = ArkUIGeneratedNativeModule._UIContext_px2fp(this.peer!.ptr, value)
        return retval
    }
    private lpx2px_serialize(value: number): number {
        const retval  = ArkUIGeneratedNativeModule._UIContext_lpx2px(this.peer!.ptr, value)
        return retval
    }
    private px2lpx_serialize(value: number): number {
        const retval  = ArkUIGeneratedNativeModule._UIContext_px2lpx(this.peer!.ptr, value)
        return retval
    }
    private getHostContext_serialize(): common.Context | undefined {
        const retval  = ArkUIGeneratedNativeModule._UIContext_getHostContext(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = (retvalDeserializer.readInt8() as int32)
        let buffer : common.Context | undefined
        if ((RuntimeType.UNDEFINED) != (buffer_runtimeType))
        {
            buffer = (common_Context_serializer.read(retvalDeserializer) as common.Context)
        }
        const returnResult : common.Context | undefined = buffer
        return returnResult
    }
    private setDynamicDimming_serialize(id: string, value: number): void {
        ArkUIGeneratedNativeModule._UIContext_setDynamicDimming(this.peer!.ptr, id, value)
    }
    private getWindowName_serialize(): string | undefined {
        const retval  = ArkUIGeneratedNativeModule._UIContext_getWindowName(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = (retvalDeserializer.readInt8() as int32)
        let buffer : string | undefined
        if ((RuntimeType.UNDEFINED) != (buffer_runtimeType))
        {
            buffer = (retvalDeserializer.readString() as string)
        }
        const returnResult : string | undefined = buffer
        return returnResult
    }
    private getWindowWidthBreakpoint_serialize(): WidthBreakpoint {
        const retval  = ArkUIGeneratedNativeModule._UIContext_getWindowWidthBreakpoint(this.peer!.ptr)
        return TypeChecker.WidthBreakpoint_FromNumeric(retval)
    }
    private getWindowHeightBreakpoint_serialize(): HeightBreakpoint {
        const retval  = ArkUIGeneratedNativeModule._UIContext_getWindowHeightBreakpoint(this.peer!.ptr)
        return TypeChecker.HeightBreakpoint_FromNumeric(retval)
    }
    private openBindSheet_serialize<T>(bindSheetContent: ComponentContent, sheetOptions?: SheetOptions, targetId?: number): Promise<void> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let sheetOptions_type : int32 = RuntimeType.UNDEFINED
        sheetOptions_type = runtimeType(sheetOptions)
        thisSerializer.writeInt8(sheetOptions_type)
        if ((RuntimeType.UNDEFINED) != (sheetOptions_type)) {
            const sheetOptions_value  = sheetOptions!
            SheetOptions_serializer.write(thisSerializer, sheetOptions_value)
        }
        let targetId_type : int32 = RuntimeType.UNDEFINED
        targetId_type = runtimeType(targetId)
        thisSerializer.writeInt8(targetId_type)
        if ((RuntimeType.UNDEFINED) != (targetId_type)) {
            const targetId_value  = targetId!
            thisSerializer.writeNumber(targetId_value)
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._UIContext_openBindSheet(this.peer!.ptr, toPeerPtr(bindSheetContent), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private updateBindSheet_serialize<T>(bindSheetContent: ComponentContent, sheetOptions: SheetOptions, partialUpdate?: boolean): Promise<void> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        SheetOptions_serializer.write(thisSerializer, sheetOptions)
        let partialUpdate_type : int32 = RuntimeType.UNDEFINED
        partialUpdate_type = runtimeType(partialUpdate)
        thisSerializer.writeInt8(partialUpdate_type)
        if ((RuntimeType.UNDEFINED) != (partialUpdate_type)) {
            const partialUpdate_value  = partialUpdate!
            thisSerializer.writeBoolean(partialUpdate_value)
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._UIContext_updateBindSheet(this.peer!.ptr, toPeerPtr(bindSheetContent), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private closeBindSheet_serialize<T>(bindSheetContent: ComponentContent): Promise<void> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._UIContext_closeBindSheet(this.peer!.ptr, toPeerPtr(bindSheetContent), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private clearResourceCache_serialize(): void {
        ArkUIGeneratedNativeModule._UIContext_clearResourceCache(this.peer!.ptr)
    }
    private isFollowingSystemFontScale_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._UIContext_isFollowingSystemFontScale(this.peer!.ptr)
        return retval
    }
    private getMaxFontScale_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._UIContext_getMaxFontScale(this.peer!.ptr)
        return retval
    }
}
export class TextMenuController_serializer {
    public static write(buffer: SerializerBase, value: TextMenuController): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): TextMenuController {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return TextMenuControllerInternal.fromPtr(ptr)
    }
}
export class UIContext_serializer {
    public static write(buffer: SerializerBase, value: UIContext): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): UIContext {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return UIContextInternal.fromPtr(ptr)
    }
}

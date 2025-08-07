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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { PopupCommonOptions_serializer, MenuOptions_serializer, PopupCommonOptions, MenuOptions, AnimateParam_serializer, SheetOptions_serializer, AnimateParam, SheetOptions } from "./../component/common"
import { ComponentContent, ComponentContentInternal } from "./arkui.ComponentContent"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackTransformer } from "./../CallbackTransformer"
import { TextMenuOptions_serializer, TextMenuOptions } from "./../component/textCommon"
import { TextPickerDialogOptions_serializer, TextPickerDialogOptions } from "./../component/textPicker"
import { FrameNode_serializer, FrameNode, FrameNodeInternal } from "./arkui.FrameNode"
import { common_Context_serializer, common } from "./ohos.app.ability.common"
import { drawing } from "./ohos.graphics.drawing"
import { WidthBreakpoint, HeightBreakpoint } from "./../component/enums"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
export class PromptActionInternal {
    public static fromPtr(ptr: KPointer): PromptAction {
        return new PromptAction(ptr)
    }
}
export class PromptAction implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, PromptAction.getFinalizer())
    }
    constructor() {
        this(PromptAction.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._PromptAction_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._PromptAction_getFinalizer()
    }
    public openPopup<T>(content: ComponentContent, target: TargetInfo, options?: PopupCommonOptions): Promise<void> {
        const content_casted = content as (ComponentContent)
        const target_casted = target as (TargetInfo)
        const options_casted = options as (PopupCommonOptions | undefined)
        return this.openPopup_serialize(content_casted, target_casted, options_casted)
    }
    public upatePopup<T>(content: ComponentContent, options: PopupCommonOptions, partialUpdate?: boolean): Promise<void> {
        const content_casted = content as (ComponentContent)
        const options_casted = options as (PopupCommonOptions)
        const partialUpdate_casted = partialUpdate as (boolean | undefined)
        return this.upatePopup_serialize(content_casted, options_casted, partialUpdate_casted)
    }
    public closePopup<T>(content: ComponentContent): Promise<void> {
        const content_casted = content as (ComponentContent)
        return this.closePopup_serialize(content_casted)
    }
    public openMenu<T>(content: ComponentContent, target: TargetInfo, options?: MenuOptions): Promise<void> {
        const content_casted = content as (ComponentContent)
        const target_casted = target as (TargetInfo)
        const options_casted = options as (MenuOptions | undefined)
        return this.openMenu_serialize(content_casted, target_casted, options_casted)
    }
    public updateMenu<T>(content: ComponentContent, options: MenuOptions, partialUpdate?: boolean): Promise<void> {
        const content_casted = content as (ComponentContent)
        const options_casted = options as (MenuOptions)
        const partialUpdate_casted = partialUpdate as (boolean | undefined)
        return this.updateMenu_serialize(content_casted, options_casted, partialUpdate_casted)
    }
    public closeMenu<T>(content: ComponentContent): Promise<void> {
        const content_casted = content as (ComponentContent)
        return this.closeMenu_serialize(content_casted)
    }
    private openPopup_serialize<T>(content: ComponentContent, target: TargetInfo, options?: PopupCommonOptions): Promise<void> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        TargetInfo_serializer.write(thisSerializer, target)
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            PopupCommonOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._PromptAction_openPopup(this.peer!.ptr, toPeerPtr(content), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private upatePopup_serialize<T>(content: ComponentContent, options: PopupCommonOptions, partialUpdate?: boolean): Promise<void> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        PopupCommonOptions_serializer.write(thisSerializer, options)
        if (partialUpdate !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const partialUpdateTmpValue  = partialUpdate!
            thisSerializer.writeBoolean(partialUpdateTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._PromptAction_upatePopup(this.peer!.ptr, toPeerPtr(content), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private closePopup_serialize<T>(content: ComponentContent): Promise<void> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._PromptAction_closePopup(this.peer!.ptr, toPeerPtr(content), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private openMenu_serialize<T>(content: ComponentContent, target: TargetInfo, options?: MenuOptions): Promise<void> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        TargetInfo_serializer.write(thisSerializer, target)
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            MenuOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._PromptAction_openMenu(this.peer!.ptr, toPeerPtr(content), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private updateMenu_serialize<T>(content: ComponentContent, options: MenuOptions, partialUpdate?: boolean): Promise<void> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        MenuOptions_serializer.write(thisSerializer, options)
        if (partialUpdate !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const partialUpdateTmpValue  = partialUpdate!
            thisSerializer.writeBoolean(partialUpdateTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._PromptAction_updateMenu(this.peer!.ptr, toPeerPtr(content), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private closeMenu_serialize<T>(content: ComponentContent): Promise<void> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._PromptAction_closeMenu(this.peer!.ptr, toPeerPtr(content), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
}
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
    constructor() {
        this(TextMenuController.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TextMenuController_construct()
        return retval
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
    constructor() {
        this(UIContext.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._UIContext_construct()
        return retval
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
        if (filters !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const filtersTmpValue  = filters!
            thisSerializer.writeInt32((filtersTmpValue.length).toInt())
            for (let filtersTmpValueCounterI = 0; filtersTmpValueCounterI < filtersTmpValue.length; filtersTmpValueCounterI++) {
                const filtersTmpValueTmpElement : string = filtersTmpValue[filtersTmpValueCounterI]
                thisSerializer.writeString(filtersTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._UIContext_getFilteredInspectorTree(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private getFilteredInspectorTreeById_serialize(id: string, depth: number, filters?: Array<string>): string {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (filters !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const filtersTmpValue  = filters!
            thisSerializer.writeInt32((filtersTmpValue.length).toInt())
            for (let filtersTmpValueCounterI = 0; filtersTmpValueCounterI < filtersTmpValue.length; filtersTmpValueCounterI++) {
                const filtersTmpValueTmpElement : string = filtersTmpValue[filtersTmpValueCounterI]
                thisSerializer.writeString(filtersTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
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
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : FrameNode | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = (FrameNode_serializer.read(retvalDeserializer) as FrameNode)
        }
        const returnResult : FrameNode | undefined = buffer
        return returnResult
    }
    private getAttachedFrameNodeById_serialize(id: string): FrameNode | undefined {
        const retval  = ArkUIGeneratedNativeModule._UIContext_getAttachedFrameNodeById(this.peer!.ptr, id)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : FrameNode | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = (FrameNode_serializer.read(retvalDeserializer) as FrameNode)
        }
        const returnResult : FrameNode | undefined = buffer
        return returnResult
    }
    private getFrameNodeByUniqueId_serialize(id: number): FrameNode | undefined {
        const retval  = ArkUIGeneratedNativeModule._UIContext_getFrameNodeByUniqueId(this.peer!.ptr, id)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : FrameNode | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
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
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : common.Context | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
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
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : string | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
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
        if (sheetOptions !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const sheetOptionsTmpValue  = sheetOptions!
            SheetOptions_serializer.write(thisSerializer, sheetOptionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (targetId !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const targetIdTmpValue  = targetId!
            thisSerializer.writeNumber(targetIdTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._UIContext_openBindSheet(this.peer!.ptr, toPeerPtr(bindSheetContent), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private updateBindSheet_serialize<T>(bindSheetContent: ComponentContent, sheetOptions: SheetOptions, partialUpdate?: boolean): Promise<void> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        SheetOptions_serializer.write(thisSerializer, sheetOptions)
        if (partialUpdate !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const partialUpdateTmpValue  = partialUpdate!
            thisSerializer.writeBoolean(partialUpdateTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
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
export interface TargetInfo {
    id: string | number;
    componentId?: number;
}
export class PromptAction_serializer {
    public static write(buffer: SerializerBase, value: PromptAction): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): PromptAction {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return PromptActionInternal.fromPtr(ptr)
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
export class TargetInfo_serializer {
    public static write(buffer: SerializerBase, value: TargetInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForId  = value.id
        if (valueHolderForId instanceof string) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForIdForIdx0  = valueHolderForId as string
            valueSerializer.writeString(valueHolderForIdForIdx0)
        } else if (valueHolderForId instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForIdForIdx1  = valueHolderForId as number
            valueSerializer.writeNumber(valueHolderForIdForIdx1)
        }
        const valueHolderForComponentId  = value.componentId
        if (valueHolderForComponentId !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForComponentIdTmpValue  = valueHolderForComponentId!
            valueSerializer.writeNumber(valueHolderForComponentIdTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): TargetInfo {
        let valueDeserializer : DeserializerBase = buffer
        const idTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let idTmpBuf : string | number | undefined
        if (idTmpBufUnionSelector == (0).toChar()) {
            idTmpBuf = (valueDeserializer.readString() as string)
        } else if (idTmpBufUnionSelector == (1).toChar()) {
            idTmpBuf = (valueDeserializer.readNumber() as number)
        } else {
            throw new Error("One of the branches for idTmpBuf has to be chosen through deserialisation.")
        }
        const idTmpResult : string | number = (idTmpBuf as string | number)
        const componentIdTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let componentIdTmpBuf : number | undefined
        if ((componentIdTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            componentIdTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const componentIdTmpResult : number | undefined = componentIdTmpBuf
        let value : TargetInfo = ({id: idTmpResult, componentId: componentIdTmpResult} as TargetInfo)
        return value
    }
}

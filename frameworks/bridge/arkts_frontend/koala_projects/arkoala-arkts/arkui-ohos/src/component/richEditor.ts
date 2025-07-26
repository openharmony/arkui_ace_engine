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

import { TextEditControllerEx, TextEditControllerExInternal, LayoutManager, LayoutManagerInternal, PreviewText, TextRange, TextDataDetectorConfig, OnDidChangeCallback, EditMenuOptions, KeyboardAppearance, DecorationStyleResult, MenuType, StyledStringController, StyledStringControllerInternal, StyledStringChangedListener } from "./textCommon"
import { SelectionOptions, RectResult, ArkCommonMethodPeer, CommonMethod, CustomBuilder, ShadowOptions, Callback_ClickEvent_Void, ClickEvent, HapticFeedbackMode, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { CopyOptions, BarState, ResponseType, Color, FontStyle, FontWeight, TextAlign, WordBreak, LineBreakStrategy, ImageSpanAlignment, ImageFit } from "./enums"
import { ResourceColor, ResourceStr, Length, Dimension, Padding, BorderRadiuses, Font } from "./units"
import { Callback_Boolean_Void, Tuple_Dimension_Dimension } from "./navigation"
import { EnterKeyType, SubmitEvent } from "./textInput"
import { Resource } from "global/resource"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Tuple_Number_Number } from "./arkui-synthetics"
import { DecorationStyleInterface, StyledString, StyledStringInternal, MutableStyledString, MutableStyledStringInternal } from "./styledString"
import { TextBackgroundStyle } from "./span"
import { PixelMap, PixelMapInternal } from "./arkui-pixelmap"
import { SymbolEffectStrategy, SymbolRenderingStrategy } from "./symbolglyph"
import { Callback_GestureEvent_Void, GestureEvent } from "./gesture"
import { OnHoverCallback } from "./sdk-stubs"
import { ColorMetrics } from "../Graphics"

import { CustomNodeBuilder } from "./customBuilder"
export class RichEditorBaseControllerInternal {
    public static fromPtr(ptr: KPointer): RichEditorBaseController {
        const obj : RichEditorBaseController = new RichEditorBaseController()
        obj.peer = new Finalizable(ptr, RichEditorBaseController.getFinalizer())
        return obj
    }
}
export class RichEditorBaseController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_richeditorbasecontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._RichEditorBaseController_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = RichEditorBaseController.ctor_richeditorbasecontroller()
        this.peer = new Finalizable(ctorPtr, RichEditorBaseController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._RichEditorBaseController_getFinalizer()
    }
    public getCaretOffset(): number {
        return this.getCaretOffset_serialize()
    }
    public setCaretOffset(offset: number): boolean {
        const offset_casted = offset as (number)
        return this.setCaretOffset_serialize(offset_casted)
    }
    public closeSelectionMenu(): void {
        this.closeSelectionMenu_serialize()
        return
    }
    public getTypingStyle(): RichEditorTextStyle {
        return this.getTypingStyle_serialize()
    }
    public setTypingStyle(value: RichEditorTextStyle): void {
        const value_casted = value as (RichEditorTextStyle)
        this.setTypingStyle_serialize(value_casted)
        return
    }
    public setSelection(selectionStart: number, selectionEnd: number, options?: SelectionOptions): void {
        const selectionStart_casted = selectionStart as (number)
        const selectionEnd_casted = selectionEnd as (number)
        const options_casted = options as (SelectionOptions | undefined)
        this.setSelection_serialize(selectionStart_casted, selectionEnd_casted, options_casted)
        return
    }
    public isEditing(): boolean {
        return this.isEditing_serialize()
    }
    public stopEditing(): void {
        this.stopEditing_serialize()
        return
    }
    public getLayoutManager(): LayoutManager {
        return this.getLayoutManager_serialize()
    }
    public getPreviewText(): PreviewText {
        return this.getPreviewText_serialize()
    }
    public getCaretRect(): RectResult | undefined {
        return this.getCaretRect_serialize()
    }
    private getCaretOffset_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._RichEditorBaseController_getCaretOffset(this.peer!.ptr)
        return retval
    }
    private setCaretOffset_serialize(offset: number): boolean {
        const retval  = ArkUIGeneratedNativeModule._RichEditorBaseController_setCaretOffset(this.peer!.ptr, offset)
        return retval
    }
    private closeSelectionMenu_serialize(): void {
        ArkUIGeneratedNativeModule._RichEditorBaseController_closeSelectionMenu(this.peer!.ptr)
    }
    private getTypingStyle_serialize(): RichEditorTextStyle {
        const retval  = ArkUIGeneratedNativeModule._RichEditorBaseController_getTypingStyle(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : RichEditorTextStyle = retvalDeserializer.readRichEditorTextStyle()
        return returnResult
    }
    private setTypingStyle_serialize(value: RichEditorTextStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeRichEditorTextStyle(value)
        ArkUIGeneratedNativeModule._RichEditorBaseController_setTypingStyle(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setSelection_serialize(selectionStart: number, selectionEnd: number, options?: SelectionOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeSelectionOptions(options_value)
        }
        ArkUIGeneratedNativeModule._RichEditorBaseController_setSelection(this.peer!.ptr, selectionStart, selectionEnd, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private isEditing_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._RichEditorBaseController_isEditing(this.peer!.ptr)
        return retval
    }
    private stopEditing_serialize(): void {
        ArkUIGeneratedNativeModule._RichEditorBaseController_stopEditing(this.peer!.ptr)
    }
    private getLayoutManager_serialize(): LayoutManager {
        const retval  = ArkUIGeneratedNativeModule._RichEditorBaseController_getLayoutManager(this.peer!.ptr)
        const obj : LayoutManager = LayoutManagerInternal.fromPtr(retval)
        return obj
    }
    private getPreviewText_serialize(): PreviewText {
        const retval  = ArkUIGeneratedNativeModule._RichEditorBaseController_getPreviewText(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : PreviewText = retvalDeserializer.readPreviewText()
        return returnResult
    }
    private getCaretRect_serialize(): RectResult | undefined {
        const retval  = ArkUIGeneratedNativeModule._RichEditorBaseController_getCaretRect(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
}
export class ArkRichEditorPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkRichEditorPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._RichEditor_construct(peerId, flags)
        const _peer  = new ArkRichEditorPeer(_peerPtr, peerId, "RichEditor", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setRichEditorOptions0Attribute(value: RichEditorOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeRichEditorOptions(value)
        ArkUIGeneratedNativeModule._RichEditorInterface_setRichEditorOptions0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRichEditorOptions1Attribute(options: RichEditorStyledStringOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeRichEditorStyledStringOptions(options)
        ArkUIGeneratedNativeModule._RichEditorInterface_setRichEditorOptions1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onReadyAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_onReady(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSelectAttribute(value: ((parameter: RichEditorSelection) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_onSelect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSelectionChangeAttribute(value: ((parameter: RichEditorRange) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_onSelectionChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    aboutToIMEInputAttribute(value: ((parameter: RichEditorInsertValue) => boolean) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_aboutToIMEInput(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onIMEInputCompleteAttribute(value: ((parameter: RichEditorTextSpanResult) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_onIMEInputComplete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDidIMEInputAttribute(value: ((parameter: TextRange) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_onDidIMEInput(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    aboutToDeleteAttribute(value: ((parameter: RichEditorDeleteValue) => boolean) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_aboutToDelete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDeleteCompleteAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_onDeleteComplete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    copyOptionsAttribute(value: CopyOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as CopyOptions)
            thisSerializer.writeInt32(TypeChecker.CopyOptions_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_copyOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onPasteAttribute(value: PasteEventCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_onPaste(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableDataDetectorAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_enableDataDetector(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enablePreviewTextAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_enablePreviewText(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    dataDetectorConfigAttribute(value: TextDataDetectorConfig | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeTextDataDetectorConfig(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_dataDetectorConfig(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    caretColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as Resource
                thisSerializer.writeResource(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_caretColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedBackgroundColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as Resource
                thisSerializer.writeResource(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_selectedBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onEditingChangeAttribute(value: ((isVisible: boolean) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_onEditingChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enterKeyTypeAttribute(value: EnterKeyType | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as EnterKeyType)
            thisSerializer.writeInt32(TypeChecker.EnterKeyType_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_enterKeyType(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSubmitAttribute(value: SubmitCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_onSubmit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillChangeAttribute(value: ((parameter: RichEditorChangeValue) => boolean) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_onWillChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDidChangeAttribute(value: OnDidChangeCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_onDidChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onCutAttribute(value: ((parameter: CutEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_onCut(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onCopyAttribute(value: ((parameter: CopyEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_onCopy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    editMenuOptionsAttribute(value: EditMenuOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeEditMenuOptions(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_editMenuOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableKeyboardOnFocusAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_enableKeyboardOnFocus(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableHapticFeedbackAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_enableHapticFeedback(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    barStateAttribute(value: BarState | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as BarState)
            thisSerializer.writeInt32(TypeChecker.BarState_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_barState(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    maxLengthAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_maxLength(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    maxLinesAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_maxLines(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    keyboardAppearanceAttribute(value: KeyboardAppearance | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as KeyboardAppearance)
            thisSerializer.writeInt32(TypeChecker.KeyboardAppearance_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_keyboardAppearance(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    stopBackPressAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_stopBackPress(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    bindSelectionMenuAttribute(spanType: RichEditorSpanType | undefined, content: CustomBuilder | undefined, responseType: ResponseType | RichEditorResponseType | undefined, options?: SelectionMenuOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let spanType_type : int32 = RuntimeType.UNDEFINED
        spanType_type = runtimeType(spanType)
        thisSerializer.writeInt8(spanType_type as int32)
        if ((RuntimeType.UNDEFINED) != (spanType_type)) {
            const spanType_value  = (spanType as RichEditorSpanType)
            thisSerializer.writeInt32(TypeChecker.RichEditorSpanType_ToNumeric(spanType_value))
        }
        let content_type : int32 = RuntimeType.UNDEFINED
        content_type = runtimeType(content)
        thisSerializer.writeInt8(content_type as int32)
        if ((RuntimeType.UNDEFINED) != (content_type)) {
            const content_value  = content!
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(content_value))
        }
        let responseType_type : int32 = RuntimeType.UNDEFINED
        responseType_type = runtimeType(responseType)
        thisSerializer.writeInt8(responseType_type as int32)
        if ((RuntimeType.UNDEFINED) != (responseType_type)) {
            const responseType_value  = responseType!
            let responseType_value_type : int32 = RuntimeType.UNDEFINED
            responseType_value_type = runtimeType(responseType_value)
            if (TypeChecker.isResponseType(responseType_value)) {
                thisSerializer.writeInt8(0 as int32)
                const responseType_value_0  = responseType_value as ResponseType
                thisSerializer.writeInt32(TypeChecker.ResponseType_ToNumeric(responseType_value_0))
            }
            else if (TypeChecker.isRichEditorResponseType(responseType_value)) {
                thisSerializer.writeInt8(1 as int32)
                const responseType_value_1  = responseType_value as RichEditorResponseType
                thisSerializer.writeInt32(TypeChecker.RichEditorResponseType_ToNumeric(responseType_value_1))
            }
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeSelectionMenuOptions(options_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_bindSelectionMenu(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    customKeyboardAttribute(value: CustomBuilder | undefined, options?: KeyboardOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_value))
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeKeyboardOptions(options_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_customKeyboard(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    placeholderAttribute(value: ResourceStr | undefined, style?: PlaceholderStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Resource
                thisSerializer.writeResource(value_value_1)
            }
        }
        let style_type : int32 = RuntimeType.UNDEFINED
        style_type = runtimeType(style)
        thisSerializer.writeInt8(style_type as int32)
        if ((RuntimeType.UNDEFINED) != (style_type)) {
            const style_value  = style!
            thisSerializer.writePlaceholderStyle(style_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_placeholder(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum RichEditorDeleteDirection {
    BACKWARD = 0,
    FORWARD = 1
}
export enum RichEditorSpanType {
    TEXT = 0,
    IMAGE = 1,
    MIXED = 2,
    BUILDER = 3,
    DEFAULT = 4
}
export enum RichEditorResponseType {
    RIGHT_CLICK = 0,
    LONG_PRESS = 1,
    SELECT = 2,
    DEFAULT = 3
}
export interface RichEditorSpanPosition {
    spanIndex: number;
    spanRange: [ number, number ];
}
export interface RichEditorTextStyle {
    fontColor?: ResourceColor;
    fontSize?: Length | number;
    fontStyle?: FontStyle;
    fontWeight?: number | FontWeight | string;
    fontFamily?: ResourceStr;
    decoration?: DecorationStyleInterface;
    textShadow?: ShadowOptions | Array<ShadowOptions>;
    letterSpacing?: number | string;
    lineHeight?: number | string | Resource;
    halfLeading?: boolean;
    fontFeature?: string;
    textBackgroundStyle?: TextBackgroundStyle;
}
export interface LeadingMarginPlaceholder {
    pixelMap: PixelMap;
    size: [ Dimension, Dimension ];
}
export interface RichEditorParagraphStyle {
    textAlign?: TextAlign;
    leadingMargin?: Dimension | LeadingMarginPlaceholder;
    wordBreak?: WordBreak;
    lineBreakStrategy?: LineBreakStrategy;
    paragraphSpacing?: number;
}
export interface PasteEvent {
    preventDefault?: (() => void);
}
export interface RichEditorTextSpan {
    spanPosition: RichEditorSpanPosition;
    value: string;
    textStyle?: RichEditorTextStyle;
}
export interface RichEditorLayoutStyle {
    margin?: Dimension | Padding;
    borderRadius?: Dimension | BorderRadiuses;
}
export interface RichEditorImageSpanStyle {
    size?: [ Dimension, Dimension ];
    verticalAlign?: ImageSpanAlignment;
    objectFit?: ImageFit;
    layoutStyle?: RichEditorLayoutStyle;
}
export interface RichEditorSymbolSpanStyle {
    fontSize?: number | string | Resource;
    fontColor?: Array<ResourceColor>;
    fontWeight?: number | FontWeight | string;
    effectStrategy?: SymbolEffectStrategy;
    renderingStrategy?: SymbolRenderingStrategy;
}
export interface RichEditorTextStyleResult {
    fontColor: ResourceColor;
    fontSize: number;
    fontStyle: FontStyle;
    fontWeight: number;
    fontFamily: string;
    decoration: DecorationStyleResult;
    textShadow?: Array<ShadowOptions>;
    letterSpacing?: number;
    lineHeight?: number;
    halfLeading?: boolean;
    fontFeature?: string;
    textBackgroundStyle?: TextBackgroundStyle;
}
export interface RichEditorParagraphResult {
    style: RichEditorParagraphStyle;
    range: [ number, number ];
}
export interface RichEditorSymbolSpanStyleResult {
    fontSize: number | string | Resource;
    fontColor: Array<ResourceColor>;
    fontWeight: number | FontWeight | string;
    effectStrategy: SymbolEffectStrategy;
    renderingStrategy: SymbolRenderingStrategy;
}
export interface RichEditorTextSpanResult {
    spanPosition: RichEditorSpanPosition;
    value: string;
    textStyle: RichEditorTextStyleResult;
    offsetInSpan: [ number, number ];
    symbolSpanStyle?: RichEditorSymbolSpanStyle;
    valueResource?: Resource;
    paragraphStyle?: RichEditorParagraphStyle;
    previewText?: string;
    urlStyle?: RichEditorUrlStyle;
}
export interface RichEditorImageSpanStyleResult {
    size: [ number, number ];
    verticalAlign: ImageSpanAlignment;
    objectFit: ImageFit;
    layoutStyle?: RichEditorLayoutStyle;
}
export interface RichEditorImageSpanResult {
    spanPosition: RichEditorSpanPosition;
    valuePixelMap?: PixelMap;
    valueResourceStr?: ResourceStr;
    imageStyle: RichEditorImageSpanStyleResult;
    offsetInSpan: [ number, number ];
}
export interface RichEditorImageSpan {
    spanPosition: RichEditorSpanPosition;
    value: PixelMap | ResourceStr;
    imageStyle?: RichEditorImageSpanStyle;
}
export interface RichEditorRange {
    start?: number;
    end?: number;
}
export interface RichEditorGesture {
    onClick?: ((event: ClickEvent) => void);
    onLongPress?: ((event: GestureEvent) => void);
    onDoubleClick?: ((event: GestureEvent) => void);
}
export interface RichEditorTextSpanOptions {
    offset?: number;
    style?: RichEditorTextStyle;
    paragraphStyle?: RichEditorParagraphStyle;
    gesture?: RichEditorGesture;
    urlStyle?: RichEditorUrlStyle;
}
export interface KeyboardOptions {
    supportAvoidance?: boolean;
}
export interface RichEditorImageSpanOptions {
    offset?: number;
    imageStyle?: RichEditorImageSpanStyle;
    gesture?: RichEditorGesture;
    onHover?: OnHoverCallback;
}
export interface RichEditorBuilderSpanOptions {
    offset?: number;
    dragBackgroundColor?: ColorMetrics;
    isDragShadowNeeded?: boolean;
}
export interface PlaceholderStyle {
    font?: Font;
    fontColor?: ResourceColor;
}
export interface RichEditorSpanStyleOptions extends RichEditorRange {
}
export interface RichEditorParagraphStyleOptions extends RichEditorRange {
    style: RichEditorParagraphStyle;
}
export interface RichEditorUpdateTextSpanStyleOptions extends RichEditorSpanStyleOptions {
    textStyle: RichEditorTextStyle;
    urlStyle?: RichEditorUrlStyle;
}
export interface RichEditorUpdateImageSpanStyleOptions extends RichEditorSpanStyleOptions {
    imageStyle: RichEditorImageSpanStyle;
}
export interface RichEditorUpdateSymbolSpanStyleOptions extends RichEditorSpanStyleOptions {
    symbolStyle: RichEditorSymbolSpanStyle;
}
export interface RichEditorSymbolSpanOptions {
    offset?: number;
    style?: RichEditorSymbolSpanStyle;
}
export interface RichEditorSelection {
    selection: [ number, number ];
    spans: Array<RichEditorTextSpanResult | RichEditorImageSpanResult>;
}
export interface RichEditorInsertValue {
    insertOffset: number;
    insertValue: string;
    previewText?: string;
}
export interface RichEditorDeleteValue {
    offset: number;
    direction: RichEditorDeleteDirection;
    length: number;
    richEditorDeleteSpans: Array<RichEditorTextSpanResult | RichEditorImageSpanResult>;
}
export interface RichEditorChangeValue {
    rangeBefore: TextRange;
    replacedSpans: Array<RichEditorTextSpanResult>;
    replacedImageSpans: Array<RichEditorImageSpanResult>;
    replacedSymbolSpans: Array<RichEditorTextSpanResult>;
}
export interface RichEditorOptions {
    controller: RichEditorController;
}
export interface RichEditorStyledStringOptions {
    controller: RichEditorStyledStringController;
}
export interface SelectionMenuOptions {
    onAppear?: MenuOnAppearCallback;
    onDisappear?: (() => void);
    menuType?: MenuType;
    onMenuShow?: MenuCallback;
    onMenuHide?: MenuCallback;
    previewMenuOptions?: PreviewMenuOptions;
}
export interface PreviewMenuOptions {
    hapticFeedbackMode?: HapticFeedbackMode;
}
export type RichEditorSpan = RichEditorImageSpanResult | RichEditorTextSpanResult;
export type Callback_RichEditorSelection_Void = (parameter: RichEditorSelection) => void;
export type Callback_RichEditorRange_Void = (parameter: RichEditorRange) => void;
export type Callback_RichEditorInsertValue_Boolean = (parameter: RichEditorInsertValue) => boolean;
export type Callback_RichEditorTextSpanResult_Void = (parameter: RichEditorTextSpanResult) => void;
export type Callback_TextRange_Void = (parameter: TextRange) => void;
export type Callback_RichEditorDeleteValue_Boolean = (parameter: RichEditorDeleteValue) => boolean;
export type Callback_RichEditorChangeValue_Boolean = (parameter: RichEditorChangeValue) => boolean;
export type Callback_CutEvent_Void = (parameter: CutEvent) => void;
export type Callback_CopyEvent_Void = (parameter: CopyEvent) => void;
export interface RichEditorAttribute extends CommonMethod {
    onReady(value: (() => void) | undefined): this
    onSelect(value: ((parameter: RichEditorSelection) => void) | undefined): this
    onSelectionChange(value: ((parameter: RichEditorRange) => void) | undefined): this
    aboutToIMEInput(value: ((parameter: RichEditorInsertValue) => boolean) | undefined): this
    onIMEInputComplete(value: ((parameter: RichEditorTextSpanResult) => void) | undefined): this
    onDidIMEInput(value: ((parameter: TextRange) => void) | undefined): this
    aboutToDelete(value: ((parameter: RichEditorDeleteValue) => boolean) | undefined): this
    onDeleteComplete(value: (() => void) | undefined): this
    copyOptions(value: CopyOptions | undefined): this
    onPaste(value: PasteEventCallback | undefined): this
    enableDataDetector(value: boolean | undefined): this
    enablePreviewText(value: boolean | undefined): this
    dataDetectorConfig(value: TextDataDetectorConfig | undefined): this
    caretColor(value: ResourceColor | undefined): this
    selectedBackgroundColor(value: ResourceColor | undefined): this
    onEditingChange(value: ((isVisible: boolean) => void) | undefined): this
    enterKeyType(value: EnterKeyType | undefined): this
    onSubmit(value: SubmitCallback | undefined): this
    onWillChange(value: ((parameter: RichEditorChangeValue) => boolean) | undefined): this
    onDidChange(value: OnDidChangeCallback | undefined): this
    onCut(value: ((parameter: CutEvent) => void) | undefined): this
    onCopy(value: ((parameter: CopyEvent) => void) | undefined): this
    editMenuOptions(value: EditMenuOptions | undefined): this
    enableKeyboardOnFocus(value: boolean | undefined): this
    enableHapticFeedback(value: boolean | undefined): this
    barState(value: BarState | undefined): this
    maxLength(value: number | undefined): this
    maxLines(value: number | undefined): this
    keyboardAppearance(value: KeyboardAppearance | undefined): this
    stopBackPress(value: boolean | undefined): this
    bindSelectionMenu(spanType: RichEditorSpanType | undefined, content: CustomBuilder | undefined, responseType: ResponseType | RichEditorResponseType | undefined, options?: SelectionMenuOptions): this
    customKeyboard(value: CustomBuilder | undefined, options?: KeyboardOptions): this
    placeholder(value: ResourceStr | undefined, style?: PlaceholderStyle): this
}
export class ArkRichEditorStyle extends ArkCommonMethodStyle implements RichEditorAttribute {
    onReady_value?: (() => void) | undefined
    onSelect_value?: ((parameter: RichEditorSelection) => void) | undefined
    onSelectionChange_value?: ((parameter: RichEditorRange) => void) | undefined
    aboutToIMEInput_value?: ((parameter: RichEditorInsertValue) => boolean) | undefined
    onIMEInputComplete_value?: ((parameter: RichEditorTextSpanResult) => void) | undefined
    onDidIMEInput_value?: ((parameter: TextRange) => void) | undefined
    aboutToDelete_value?: ((parameter: RichEditorDeleteValue) => boolean) | undefined
    onDeleteComplete_value?: (() => void) | undefined
    copyOptions_value?: CopyOptions | undefined
    onPaste_value?: PasteEventCallback | undefined
    enableDataDetector_value?: boolean | undefined
    enablePreviewText_value?: boolean | undefined
    dataDetectorConfig_value?: TextDataDetectorConfig | undefined
    caretColor_value?: ResourceColor | undefined
    selectedBackgroundColor_value?: ResourceColor | undefined
    onEditingChange_value?: ((isVisible: boolean) => void) | undefined
    enterKeyType_value?: EnterKeyType | undefined
    onSubmit_value?: SubmitCallback | undefined
    onWillChange_value?: ((parameter: RichEditorChangeValue) => boolean) | undefined
    onDidChange_value?: OnDidChangeCallback | undefined
    onCut_value?: ((parameter: CutEvent) => void) | undefined
    onCopy_value?: ((parameter: CopyEvent) => void) | undefined
    editMenuOptions_value?: EditMenuOptions | undefined
    enableKeyboardOnFocus_value?: boolean | undefined
    enableHapticFeedback_value?: boolean | undefined
    barState_value?: BarState | undefined
    maxLength_value?: number | undefined
    maxLines_value?: number | undefined
    keyboardAppearance_value?: KeyboardAppearance | undefined
    stopBackPress_value?: boolean | undefined
    public onReady(value: (() => void) | undefined): this {
        return this
    }
    public onSelect(value: ((parameter: RichEditorSelection) => void) | undefined): this {
        return this
    }
    public onSelectionChange(value: ((parameter: RichEditorRange) => void) | undefined): this {
        return this
    }
    public aboutToIMEInput(value: ((parameter: RichEditorInsertValue) => boolean) | undefined): this {
        return this
    }
    public onIMEInputComplete(value: ((parameter: RichEditorTextSpanResult) => void) | undefined): this {
        return this
    }
    public onDidIMEInput(value: ((parameter: TextRange) => void) | undefined): this {
        return this
    }
    public aboutToDelete(value: ((parameter: RichEditorDeleteValue) => boolean) | undefined): this {
        return this
    }
    public onDeleteComplete(value: (() => void) | undefined): this {
        return this
    }
    public copyOptions(value: CopyOptions | undefined): this {
        return this
    }
    public onPaste(value: PasteEventCallback | undefined): this {
        return this
    }
    public enableDataDetector(value: boolean | undefined): this {
        return this
    }
    public enablePreviewText(value: boolean | undefined): this {
        return this
    }
    public dataDetectorConfig(value: TextDataDetectorConfig | undefined): this {
        return this
    }
    public caretColor(value: ResourceColor | undefined): this {
        return this
    }
    public selectedBackgroundColor(value: ResourceColor | undefined): this {
        return this
    }
    public onEditingChange(value: ((isVisible: boolean) => void) | undefined): this {
        return this
    }
    public enterKeyType(value: EnterKeyType | undefined): this {
        return this
    }
    public onSubmit(value: SubmitCallback | undefined): this {
        return this
    }
    public onWillChange(value: ((parameter: RichEditorChangeValue) => boolean) | undefined): this {
        return this
    }
    public onDidChange(value: OnDidChangeCallback | undefined): this {
        return this
    }
    public onCut(value: ((parameter: CutEvent) => void) | undefined): this {
        return this
    }
    public onCopy(value: ((parameter: CopyEvent) => void) | undefined): this {
        return this
    }
    public editMenuOptions(value: EditMenuOptions | undefined): this {
        return this
    }
    public enableKeyboardOnFocus(value: boolean | undefined): this {
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        return this
    }
    public barState(value: BarState | undefined): this {
        return this
    }
    public maxLength(value: number | undefined): this {
        return this
    }
    public maxLines(value: number | undefined): this {
        return this
    }
    public keyboardAppearance(value: KeyboardAppearance | undefined): this {
        return this
    }
    public stopBackPress(value: boolean | undefined): this {
        return this
    }
    public bindSelectionMenu(spanType: RichEditorSpanType | undefined, content: CustomBuilder | undefined, responseType: ResponseType | RichEditorResponseType | undefined, options?: SelectionMenuOptions): this {
        return this
    }
    public customKeyboard(value: CustomBuilder | undefined, options?: KeyboardOptions): this {
        return this
    }
    public placeholder(value: ResourceStr | undefined, style?: PlaceholderStyle): this {
        return this
        }
}
export interface CutEvent {
    preventDefault?: (() => void);
}
export interface CopyEvent {
    preventDefault?: (() => void);
}
export interface RichEditorUrlStyle {
    url?: ResourceStr;
}
export type SubmitCallback = (enterKey: EnterKeyType, event: SubmitEvent) => void;
export type MenuOnAppearCallback = (start: number, end: number) => void;
export type MenuCallback = (start: number, end: number) => void;
export type PasteEventCallback = (event?: PasteEvent) => void;
export class ArkRichEditorComponent extends ArkCommonMethodComponent implements RichEditorAttribute {
    getPeer(): ArkRichEditorPeer {
        return (this.peer as ArkRichEditorPeer)
    }
    public setRichEditorOptions(value: RichEditorOptions | RichEditorStyledStringOptions): this {
        if (this.checkPriority("setRichEditorOptions")) {
            const value_type = runtimeType(value)
            if (TypeChecker.isRichEditorOptions(value, true)) {
                const value_casted = value as (RichEditorOptions)
                this.getPeer()?.setRichEditorOptions0Attribute(value_casted)
                return this
            }
            if (TypeChecker.isRichEditorStyledStringOptions(value, true)) {
                const options_casted = value as (RichEditorStyledStringOptions)
                this.getPeer()?.setRichEditorOptions1Attribute(options_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public onReady(value: (() => void) | undefined): this {
        if (this.checkPriority("onReady")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onReadyAttribute(value_casted)
            return this
        }
        return this
    }
    public onSelect(value: ((parameter: RichEditorSelection) => void) | undefined): this {
        if (this.checkPriority("onSelect")) {
            const value_casted = value as (((parameter: RichEditorSelection) => void) | undefined)
            this.getPeer()?.onSelectAttribute(value_casted)
            return this
        }
        return this
    }
    public onSelectionChange(value: ((parameter: RichEditorRange) => void) | undefined): this {
        if (this.checkPriority("onSelectionChange")) {
            const value_casted = value as (((parameter: RichEditorRange) => void) | undefined)
            this.getPeer()?.onSelectionChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public aboutToIMEInput(value: ((parameter: RichEditorInsertValue) => boolean) | undefined): this {
        if (this.checkPriority("aboutToIMEInput")) {
            const value_casted = value as (((parameter: RichEditorInsertValue) => boolean) | undefined)
            this.getPeer()?.aboutToIMEInputAttribute(value_casted)
            return this
        }
        return this
    }
    public onIMEInputComplete(value: ((parameter: RichEditorTextSpanResult) => void) | undefined): this {
        if (this.checkPriority("onIMEInputComplete")) {
            const value_casted = value as (((parameter: RichEditorTextSpanResult) => void) | undefined)
            this.getPeer()?.onIMEInputCompleteAttribute(value_casted)
            return this
        }
        return this
    }
    public onDidIMEInput(value: ((parameter: TextRange) => void) | undefined): this {
        if (this.checkPriority("onDidIMEInput")) {
            const value_casted = value as (((parameter: TextRange) => void) | undefined)
            this.getPeer()?.onDidIMEInputAttribute(value_casted)
            return this
        }
        return this
    }
    public aboutToDelete(value: ((parameter: RichEditorDeleteValue) => boolean) | undefined): this {
        if (this.checkPriority("aboutToDelete")) {
            const value_casted = value as (((parameter: RichEditorDeleteValue) => boolean) | undefined)
            this.getPeer()?.aboutToDeleteAttribute(value_casted)
            return this
        }
        return this
    }
    public onDeleteComplete(value: (() => void) | undefined): this {
        if (this.checkPriority("onDeleteComplete")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onDeleteCompleteAttribute(value_casted)
            return this
        }
        return this
    }
    public copyOptions(value: CopyOptions | undefined): this {
        if (this.checkPriority("copyOptions")) {
            const value_casted = value as (CopyOptions | undefined)
            this.getPeer()?.copyOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public onPaste(value: PasteEventCallback | undefined): this {
        if (this.checkPriority("onPaste")) {
            const value_casted = value as (PasteEventCallback | undefined)
            this.getPeer()?.onPasteAttribute(value_casted)
            return this
        }
        return this
    }
    public enableDataDetector(value: boolean | undefined): this {
        if (this.checkPriority("enableDataDetector")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enableDataDetectorAttribute(value_casted)
            return this
        }
        return this
    }
    public enablePreviewText(value: boolean | undefined): this {
        if (this.checkPriority("enablePreviewText")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enablePreviewTextAttribute(value_casted)
            return this
        }
        return this
    }
    public dataDetectorConfig(value: TextDataDetectorConfig | undefined): this {
        if (this.checkPriority("dataDetectorConfig")) {
            const value_casted = value as (TextDataDetectorConfig | undefined)
            this.getPeer()?.dataDetectorConfigAttribute(value_casted)
            return this
        }
        return this
    }
    public caretColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("caretColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.caretColorAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedBackgroundColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("selectedBackgroundColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.selectedBackgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    public onEditingChange(value: ((isVisible: boolean) => void) | undefined): this {
        if (this.checkPriority("onEditingChange")) {
            const value_casted = value as (((isVisible: boolean) => void) | undefined)
            this.getPeer()?.onEditingChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public enterKeyType(value: EnterKeyType | undefined): this {
        if (this.checkPriority("enterKeyType")) {
            const value_casted = value as (EnterKeyType | undefined)
            this.getPeer()?.enterKeyTypeAttribute(value_casted)
            return this
        }
        return this
    }
    public onSubmit(value: SubmitCallback | undefined): this {
        if (this.checkPriority("onSubmit")) {
            const value_casted = value as (SubmitCallback | undefined)
            this.getPeer()?.onSubmitAttribute(value_casted)
            return this
        }
        return this
    }
    public onWillChange(value: ((parameter: RichEditorChangeValue) => boolean) | undefined): this {
        if (this.checkPriority("onWillChange")) {
            const value_casted = value as (((parameter: RichEditorChangeValue) => boolean) | undefined)
            this.getPeer()?.onWillChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onDidChange(value: OnDidChangeCallback | undefined): this {
        if (this.checkPriority("onDidChange")) {
            const value_casted = value as (OnDidChangeCallback | undefined)
            this.getPeer()?.onDidChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onCut(value: ((parameter: CutEvent) => void) | undefined): this {
        if (this.checkPriority("onCut")) {
            const value_casted = value as (((parameter: CutEvent) => void) | undefined)
            this.getPeer()?.onCutAttribute(value_casted)
            return this
        }
        return this
    }
    public onCopy(value: ((parameter: CopyEvent) => void) | undefined): this {
        if (this.checkPriority("onCopy")) {
            const value_casted = value as (((parameter: CopyEvent) => void) | undefined)
            this.getPeer()?.onCopyAttribute(value_casted)
            return this
        }
        return this
    }
    public editMenuOptions(value: EditMenuOptions | undefined): this {
        if (this.checkPriority("editMenuOptions")) {
            const value_casted = value as (EditMenuOptions | undefined)
            this.getPeer()?.editMenuOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public enableKeyboardOnFocus(value: boolean | undefined): this {
        if (this.checkPriority("enableKeyboardOnFocus")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enableKeyboardOnFocusAttribute(value_casted)
            return this
        }
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        if (this.checkPriority("enableHapticFeedback")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enableHapticFeedbackAttribute(value_casted)
            return this
        }
        return this
    }
    public barState(value: BarState | undefined): this {
        if (this.checkPriority("barState")) {
            const value_casted = value as (BarState | undefined)
            this.getPeer()?.barStateAttribute(value_casted)
            return this
        }
        return this
    }
    public maxLength(value: number | undefined): this {
        if (this.checkPriority("maxLength")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.maxLengthAttribute(value_casted)
            return this
        }
        return this
    }
    public maxLines(value: number | undefined): this {
        if (this.checkPriority("maxLines")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.maxLinesAttribute(value_casted)
            return this
        }
        return this
    }
    public keyboardAppearance(value: KeyboardAppearance | undefined): this {
        if (this.checkPriority("keyboardAppearance")) {
            const value_casted = value as (KeyboardAppearance | undefined)
            this.getPeer()?.keyboardAppearanceAttribute(value_casted)
            return this
        }
        return this
    }
    public stopBackPress(value: boolean | undefined): this {
        if (this.checkPriority("stopBackPress")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.stopBackPressAttribute(value_casted)
            return this
        }
        return this
    }
    public bindSelectionMenu(spanType: RichEditorSpanType | undefined, content: CustomBuilder | undefined, responseType: ResponseType | RichEditorResponseType | undefined, options?: SelectionMenuOptions): this {
        if (this.checkPriority("bindSelectionMenu")) {
            const spanType_casted = spanType as (RichEditorSpanType | undefined)
            const content_casted = content as (CustomBuilder | undefined)
            const responseType_casted = responseType as (ResponseType | RichEditorResponseType | undefined)
            const options_casted = options as (SelectionMenuOptions)
            this.getPeer()?.bindSelectionMenuAttribute(spanType_casted, content_casted, responseType_casted, options_casted)
            return this
        }
        return this
    }
    public customKeyboard(value: CustomBuilder | undefined, options?: KeyboardOptions): this {
        if (this.checkPriority("customKeyboard")) {
            const value_casted = value as (CustomBuilder | undefined)
            const options_casted = options as (KeyboardOptions)
            this.getPeer()?.customKeyboardAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    public placeholder(value: ResourceStr | undefined, style?: PlaceholderStyle): this {
        if (this.checkPriority("placeholder")) {
            const value_casted = value as (ResourceStr | undefined)
            const style_casted = style as (PlaceholderStyle)
            this.getPeer()?.placeholderAttribute(value_casted, style_casted)
            return this
        }
        return this
    }
    
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function RichEditor(
    /** @memo */
    style: ((attributes: RichEditorAttribute) => void) | undefined,
    value: RichEditorOptions | RichEditorStyledStringOptions,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkRichEditorComponent()
    })
    NodeAttach<ArkRichEditorPeer>((): ArkRichEditorPeer => ArkRichEditorPeer.create(receiver), (_: ArkRichEditorPeer) => {
        receiver.setRichEditorOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
export class RichEditorControllerInternal {
    public static fromPtr(ptr: KPointer): RichEditorController {
        const obj : RichEditorController = new RichEditorController()
        obj.peer = new Finalizable(ptr, RichEditorController.getFinalizer())
        return obj
    }
}
export class RichEditorController extends RichEditorBaseController implements MaterializedBase {
    static ctor_richeditorcontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._RichEditorController_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = RichEditorController.ctor_richeditorcontroller()
        this.peer = new Finalizable(ctorPtr, RichEditorController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._RichEditorController_getFinalizer()
    }
    public addTextSpan(value: string, options?: RichEditorTextSpanOptions): number {
        const value_casted = value as (string)
        const options_casted = options as (RichEditorTextSpanOptions | undefined)
        return this.addTextSpan_serialize(value_casted, options_casted)
    }
    public addImageSpan(value: PixelMap | ResourceStr, options?: RichEditorImageSpanOptions): number {
        const value_casted = value as (PixelMap | ResourceStr)
        const options_casted = options as (RichEditorImageSpanOptions | undefined)
        return this.addImageSpan_serialize(value_casted, options_casted)
    }
    public addBuilderSpan(value: CustomBuilder, options?: RichEditorBuilderSpanOptions): number {
        const value_casted = value as (CustomBuilder)
        const options_casted = options as (RichEditorBuilderSpanOptions | undefined)
        return this.addBuilderSpan_serialize(value_casted, options_casted)
    }
    public addSymbolSpan(value: Resource, options?: RichEditorSymbolSpanOptions): number {
        const value_casted = value as (Resource)
        const options_casted = options as (RichEditorSymbolSpanOptions | undefined)
        return this.addSymbolSpan_serialize(value_casted, options_casted)
    }
    public updateSpanStyle(value: RichEditorUpdateTextSpanStyleOptions | RichEditorUpdateImageSpanStyleOptions | RichEditorUpdateSymbolSpanStyleOptions): void {
        const value_casted = value as (RichEditorUpdateTextSpanStyleOptions | RichEditorUpdateImageSpanStyleOptions | RichEditorUpdateSymbolSpanStyleOptions)
        this.updateSpanStyle_serialize(value_casted)
        return
    }
    public updateParagraphStyle(value: RichEditorParagraphStyleOptions): void {
        const value_casted = value as (RichEditorParagraphStyleOptions)
        this.updateParagraphStyle_serialize(value_casted)
        return
    }
    public deleteSpans(value?: RichEditorRange): void {
        const value_casted = value as (RichEditorRange | undefined)
        this.deleteSpans_serialize(value_casted)
        return
    }
    public getSpans(value?: RichEditorRange): Array<RichEditorImageSpanResult | RichEditorTextSpanResult> {
        const value_casted = value as (RichEditorRange | undefined)
        return this.getSpans_serialize(value_casted)
    }
    public getParagraphs(value?: RichEditorRange): Array<RichEditorParagraphResult> {
        const value_casted = value as (RichEditorRange | undefined)
        return this.getParagraphs_serialize(value_casted)
    }
    public getSelection(): RichEditorSelection {
        return this.getSelection_serialize()
    }
    public fromStyledString(value: StyledString): Array<RichEditorSpan> {
        const value_casted = value as (StyledString)
        return this.fromStyledString_serialize(value_casted)
    }
    public toStyledString(value: RichEditorRange): StyledString {
        const value_casted = value as (RichEditorRange)
        return this.toStyledString_serialize(value_casted)
    }
    private addTextSpan_serialize(value: string, options?: RichEditorTextSpanOptions): number {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeRichEditorTextSpanOptions(options_value)
        }
        const retval  = ArkUIGeneratedNativeModule._RichEditorController_addTextSpan(this.peer!.ptr, value, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private addImageSpan_serialize(value: PixelMap | ResourceStr, options?: RichEditorImageSpanOptions): number {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isPixelMap(value, false, false)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as PixelMap
            thisSerializer.writePixelMap(value_0)
        }
        else if ((RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as ResourceStr
            let value_1_type : int32 = RuntimeType.UNDEFINED
            value_1_type = runtimeType(value_1)
            if (RuntimeType.STRING == value_1_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_1_0  = value_1 as string
                thisSerializer.writeString(value_1_0)
            }
            else if (RuntimeType.OBJECT == value_1_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_1_1  = value_1 as Resource
                thisSerializer.writeResource(value_1_1)
            }
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeRichEditorImageSpanOptions(options_value)
        }
        const retval  = ArkUIGeneratedNativeModule._RichEditorController_addImageSpan(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private addBuilderSpan_serialize(value: CustomBuilder, options?: RichEditorBuilderSpanOptions): number {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value))
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeRichEditorBuilderSpanOptions(options_value)
        }
        const retval  = ArkUIGeneratedNativeModule._RichEditorController_addBuilderSpan(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private addSymbolSpan_serialize(value: Resource, options?: RichEditorSymbolSpanOptions): number {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeResource(value)
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeRichEditorSymbolSpanOptions(options_value)
        }
        const retval  = ArkUIGeneratedNativeModule._RichEditorController_addSymbolSpan(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private updateSpanStyle_serialize(value: RichEditorUpdateTextSpanStyleOptions | RichEditorUpdateImageSpanStyleOptions | RichEditorUpdateSymbolSpanStyleOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isRichEditorUpdateTextSpanStyleOptions(value, false, false)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as RichEditorUpdateTextSpanStyleOptions
            thisSerializer.writeRichEditorUpdateTextSpanStyleOptions(value_0)
        }
        else if (TypeChecker.isRichEditorUpdateImageSpanStyleOptions(value, false)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as RichEditorUpdateImageSpanStyleOptions
            thisSerializer.writeRichEditorUpdateImageSpanStyleOptions(value_1)
        }
        else if (TypeChecker.isRichEditorUpdateSymbolSpanStyleOptions(value, false)) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as RichEditorUpdateSymbolSpanStyleOptions
            thisSerializer.writeRichEditorUpdateSymbolSpanStyleOptions(value_2)
        }
        ArkUIGeneratedNativeModule._RichEditorController_updateSpanStyle(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private updateParagraphStyle_serialize(value: RichEditorParagraphStyleOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeRichEditorParagraphStyleOptions(value)
        ArkUIGeneratedNativeModule._RichEditorController_updateParagraphStyle(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private deleteSpans_serialize(value?: RichEditorRange): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeRichEditorRange(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorController_deleteSpans(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getSpans_serialize(value?: RichEditorRange): Array<RichEditorImageSpanResult | RichEditorTextSpanResult> {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeRichEditorRange(value_value)
        }
        const retval  = ArkUIGeneratedNativeModule._RichEditorController_getSpans(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<RichEditorImageSpanResult | RichEditorTextSpanResult> = new Array<RichEditorImageSpanResult | RichEditorTextSpanResult>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            const buffer_buf_selector : int32 = retvalDeserializer.readInt8()
            let buffer_buf : RichEditorImageSpanResult | RichEditorTextSpanResult | undefined
            if (buffer_buf_selector == 0) {
                buffer_buf = retvalDeserializer.readRichEditorImageSpanResult()
            }
            else if (buffer_buf_selector == 1) {
                buffer_buf = retvalDeserializer.readRichEditorTextSpanResult()
            }
            else {
                throw new Error("One of the branches for buffer_buf has to be chosen through deserialisation.")
            }
            buffer[buffer_i] = (buffer_buf as RichEditorImageSpanResult | RichEditorTextSpanResult)
        }
        const returnResult : Array<RichEditorImageSpanResult | RichEditorTextSpanResult> = buffer
        return returnResult
    }
    private getParagraphs_serialize(value?: RichEditorRange): Array<RichEditorParagraphResult> {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeRichEditorRange(value_value)
        }
        const retval  = ArkUIGeneratedNativeModule._RichEditorController_getParagraphs(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<RichEditorParagraphResult> = new Array<RichEditorParagraphResult>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = retvalDeserializer.readRichEditorParagraphResult()
        }
        const returnResult : Array<RichEditorParagraphResult> = buffer
        return returnResult
    }
    private getSelection_serialize(): RichEditorSelection {
        const retval  = ArkUIGeneratedNativeModule._RichEditorController_getSelection(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : RichEditorSelection = retvalDeserializer.readRichEditorSelection()
        return returnResult
    }
    private fromStyledString_serialize(value: StyledString): Array<RichEditorSpan> {
        const retval  = ArkUIGeneratedNativeModule._RichEditorController_fromStyledString(this.peer!.ptr, toPeerPtr(value))
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<RichEditorSpan> = new Array<RichEditorSpan>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            const buffer_buf_selector : int32 = retvalDeserializer.readInt8()
            let buffer_buf : RichEditorImageSpanResult | RichEditorTextSpanResult | undefined
            if (buffer_buf_selector == 0) {
                buffer_buf = retvalDeserializer.readRichEditorImageSpanResult()
            }
            else if (buffer_buf_selector == 1) {
                buffer_buf = retvalDeserializer.readRichEditorTextSpanResult()
            }
            else {
                throw new Error("One of the branches for buffer_buf has to be chosen through deserialisation.")
            }
            buffer[buffer_i] = (buffer_buf as RichEditorImageSpanResult | RichEditorTextSpanResult)
        }
        const returnResult : Array<RichEditorSpan> = buffer
        return returnResult
    }
    private toStyledString_serialize(value: RichEditorRange): StyledString {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeRichEditorRange(value)
        const retval  = ArkUIGeneratedNativeModule._RichEditorController_toStyledString(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : StyledString = StyledStringInternal.fromPtr(retval)
        return obj
    }
}
export class RichEditorStyledStringControllerInternal {
    public static fromPtr(ptr: KPointer): RichEditorStyledStringController {
        const obj : RichEditorStyledStringController = new RichEditorStyledStringController()
        obj.peer = new Finalizable(ptr, RichEditorStyledStringController.getFinalizer())
        return obj
    }
}
export class RichEditorStyledStringController extends RichEditorBaseController implements MaterializedBase {
    static ctor_richeditorstyledstringcontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._RichEditorStyledStringController_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = RichEditorStyledStringController.ctor_richeditorstyledstringcontroller()
        this.peer = new Finalizable(ctorPtr, RichEditorStyledStringController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._RichEditorStyledStringController_getFinalizer()
    }
    public setStyledString(styledString: StyledString): void {
        const styledString_casted = styledString as (StyledString)
        this.setStyledString_serialize(styledString_casted)
        return
    }
    public getStyledString(): MutableStyledString {
        return this.getStyledString_serialize()
    }
    public getSelection(): RichEditorRange {
        return this.getSelection_serialize()
    }
    public onContentChanged(listener: StyledStringChangedListener): void {
        const listener_casted = listener as (StyledStringChangedListener)
        this.onContentChanged_serialize(listener_casted)
        return
    }
    private setStyledString_serialize(styledString: StyledString): void {
        ArkUIGeneratedNativeModule._RichEditorStyledStringController_setStyledString(this.peer!.ptr, toPeerPtr(styledString))
    }
    private getStyledString_serialize(): MutableStyledString {
        const retval  = ArkUIGeneratedNativeModule._RichEditorStyledStringController_getStyledString(this.peer!.ptr)
        const obj : MutableStyledString = MutableStyledStringInternal.fromPtr(retval)
        return obj
    }
    private getSelection_serialize(): RichEditorRange {
        const retval  = ArkUIGeneratedNativeModule._RichEditorStyledStringController_getSelection(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : RichEditorRange = retvalDeserializer.readRichEditorRange()
        return returnResult
    }
    private onContentChanged_serialize(listener: StyledStringChangedListener): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeStyledStringChangedListener(listener)
        ArkUIGeneratedNativeModule._RichEditorStyledStringController_onContentChanged(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}

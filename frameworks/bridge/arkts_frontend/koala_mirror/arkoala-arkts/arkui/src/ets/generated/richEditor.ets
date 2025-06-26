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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { SelectionOptions_serializer, RectResult_serializer, SelectionOptions, RectResult, ArkCommonMethodPeer, CommonMethod, ShadowOptions, ClickEvent, HoverEvent, HapticFeedbackMode, ArkCommonMethodComponent, ArkCommonMethodStyle, ClickEvent_serializer, ShadowOptions_serializer, HoverEvent_serializer } from "./common"
import { PreviewText_serializer, TextEditControllerEx, TextEditControllerExInternal, LayoutManager, LayoutManagerInternal, PreviewText, TextDataDetectorConfig_serializer, EditMenuOptions_serializer, TextRange, TextDataDetectorConfig, OnDidChangeCallback, EditMenuOptions, KeyboardAppearance, MenuType, DecorationStyleResult, TextRange_serializer, DecorationStyleResult_serializer, StyledStringChangedListener_serializer, StyledStringController, StyledStringControllerInternal, StyledStringChangedListener } from "./textCommon"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { Resource_serializer, Resource } from "./resource"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { VoidCallback, ResourceColor, ResourceStr, Font, Length, Dimension, Padding, BorderRadiuses, Font_serializer, Padding_serializer, BorderRadiuses_serializer } from "./units"
import { CopyOptions, Color, BarState, ResponseType, FontStyle, FontWeight, TextAlign, WordBreak, LineBreakStrategy, ImageSpanAlignment, ImageFit } from "./enums"
import { EnterKeyType, SubmitEvent } from "./textInput"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CustomBuilder } from "./builder"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { DecorationStyleInterface, DecorationStyleInterface_serializer, StyledString, StyledStringInternal, MutableStyledString, MutableStyledStringInternal } from "./styledString"
import { TextBackgroundStyle, TextBackgroundStyle_serializer } from "./span"
import { image, image_PixelMap_serializer } from "./ohos.multimedia.image"
import { SymbolEffectStrategy, SymbolRenderingStrategy } from "./symbolglyph"
import { GestureEvent, GestureEvent_serializer } from "./gesture"
import { ColorMetrics, ColorMetrics_serializer } from "./ark.Graphics"
import { NodeAttach, remember } from "@koalaui/runtime"
import { CustomNodeBuilder } from "./custom_builder"
export class RichEditorBaseControllerInternal {
    public static fromPtr(ptr: KPointer): RichEditorBaseController {
        return new RichEditorBaseController(ptr)
    }
}
export class RichEditorBaseController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, RichEditorBaseController.getFinalizer())
    }
    static ctor(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._RichEditorBaseController_ctor()
        return retval
    }
    constructor() {
        this(RichEditorBaseController.ctor())
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
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : RichEditorTextStyle = RichEditorTextStyle_serializer.read(retvalDeserializer)
        return returnResult
    }
    private setTypingStyle_serialize(value: RichEditorTextStyle): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        RichEditorTextStyle_serializer.write(thisSerializer, value)
        ArkUIGeneratedNativeModule._RichEditorBaseController_setTypingStyle(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setSelection_serialize(selectionStart: number, selectionEnd: number, options?: SelectionOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            SelectionOptions_serializer.write(thisSerializer, options_value)
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
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : PreviewText = PreviewText_serializer.read(retvalDeserializer)
        return returnResult
    }
    private getCaretRect_serialize(): RectResult | undefined {
        const retval  = ArkUIGeneratedNativeModule._RichEditorBaseController_getCaretRect(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = (retvalDeserializer.readInt8() as int32)
        let buffer : RectResult | undefined
        if ((RuntimeType.UNDEFINED) != (buffer_runtimeType))
        {
            buffer = RectResult_serializer.read(retvalDeserializer)
        }
        const returnResult : RectResult | undefined = buffer
        return returnResult
    }
}
export class ArkRichEditorPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkRichEditorPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._RichEditor_construct(peerId, flags)
        const _peer  = new ArkRichEditorPeer(_peerPtr, peerId, "RichEditor", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setRichEditorOptions0Attribute(value: RichEditorOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        RichEditorOptions_serializer.write(thisSerializer, value)
        ArkUIGeneratedNativeModule._RichEditorInterface_setRichEditorOptions0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRichEditorOptions1Attribute(options: RichEditorStyledStringOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        RichEditorStyledStringOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._RichEditorInterface_setRichEditorOptions1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onReadyAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_onReady(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSelectAttribute(value: ((value0: RichEditorSelection) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_onSelect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSelectionChangeAttribute(value: ((value0: RichEditorRange) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_onSelectionChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    aboutToIMEInputAttribute(value: ((value0: RichEditorInsertValue) => boolean) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_aboutToIMEInput(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onIMEInputCompleteAttribute(value: ((value0: RichEditorTextSpanResult) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_onIMEInputComplete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDidIMEInputAttribute(value: ((value0: TextRange) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_onDidIMEInput(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    aboutToDeleteAttribute(value: ((value0: RichEditorDeleteValue) => boolean) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_aboutToDelete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDeleteCompleteAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_onDeleteComplete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    copyOptionsAttribute(value: CopyOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as CopyOptions)
            thisSerializer.writeInt32(TypeChecker.CopyOptions_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_copyOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onPasteAttribute(value: PasteEventCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_onPaste(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableDataDetectorAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_enableDataDetector(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enablePreviewTextAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_enablePreviewText(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    dataDetectorConfigAttribute(value: TextDataDetectorConfig | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            TextDataDetectorConfig_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_dataDetectorConfig(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    caretColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3)
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_caretColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedBackgroundColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3)
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_selectedBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onEditingChangeAttribute(value: ((value0: boolean) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_onEditingChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enterKeyTypeAttribute(value: EnterKeyType | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as EnterKeyType)
            thisSerializer.writeInt32(TypeChecker.EnterKeyType_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_enterKeyType(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSubmitAttribute(value: SubmitCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_onSubmit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillChangeAttribute(value: ((value0: RichEditorChangeValue) => boolean) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_onWillChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDidChangeAttribute(value: OnDidChangeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_onDidChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onCutAttribute(value: ((value0: CutEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_onCut(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onCopyAttribute(value: ((value0: CopyEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_onCopy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    editMenuOptionsAttribute(value: EditMenuOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            EditMenuOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_editMenuOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableKeyboardOnFocusAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_enableKeyboardOnFocus(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableHapticFeedbackAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_enableHapticFeedback(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    barStateAttribute(value: BarState | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as BarState)
            thisSerializer.writeInt32(TypeChecker.BarState_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_barState(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    maxLengthAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_maxLength(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    maxLinesAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_maxLines(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    keyboardAppearanceAttribute(value: KeyboardAppearance | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as KeyboardAppearance)
            thisSerializer.writeInt32(TypeChecker.KeyboardAppearance_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_keyboardAppearance(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    stopBackPressAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_stopBackPress(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    bindSelectionMenuAttribute(spanType: RichEditorSpanType | undefined, content: CustomBuilder | undefined, responseType: ResponseType | RichEditorResponseType | undefined, options?: SelectionMenuOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let spanType_type : int32 = RuntimeType.UNDEFINED
        spanType_type = runtimeType(spanType)
        thisSerializer.writeInt8(spanType_type)
        if ((RuntimeType.UNDEFINED) != (spanType_type)) {
            const spanType_value  = (spanType as RichEditorSpanType)
            thisSerializer.writeInt32(TypeChecker.RichEditorSpanType_ToNumeric(spanType_value))
        }
        let content_type : int32 = RuntimeType.UNDEFINED
        content_type = runtimeType(content)
        thisSerializer.writeInt8(content_type)
        if ((RuntimeType.UNDEFINED) != (content_type)) {
            const content_value  = content!
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(content_value))
        }
        let responseType_type : int32 = RuntimeType.UNDEFINED
        responseType_type = runtimeType(responseType)
        thisSerializer.writeInt8(responseType_type)
        if ((RuntimeType.UNDEFINED) != (responseType_type)) {
            const responseType_value  = responseType!
            let responseType_value_type : int32 = RuntimeType.UNDEFINED
            responseType_value_type = runtimeType(responseType_value)
            if (TypeChecker.isResponseType(responseType_value)) {
                thisSerializer.writeInt8(0)
                const responseType_value_0  = responseType_value as ResponseType
                thisSerializer.writeInt32(TypeChecker.ResponseType_ToNumeric(responseType_value_0))
            }
            else if (TypeChecker.isRichEditorResponseType(responseType_value)) {
                thisSerializer.writeInt8(1)
                const responseType_value_1  = responseType_value as RichEditorResponseType
                thisSerializer.writeInt32(TypeChecker.RichEditorResponseType_ToNumeric(responseType_value_1))
            }
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            SelectionMenuOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_bindSelectionMenu(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    customKeyboardAttribute(value: CustomBuilder | undefined, options?: KeyboardOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_value))
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            KeyboardOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_customKeyboard(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    placeholderAttribute(value: ResourceStr | undefined, style?: PlaceholderStyle): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_1)
            }
        }
        let style_type : int32 = RuntimeType.UNDEFINED
        style_type = runtimeType(style)
        thisSerializer.writeInt8(style_type)
        if ((RuntimeType.UNDEFINED) != (style_type)) {
            const style_value  = style!
            PlaceholderStyle_serializer.write(thisSerializer, style_value)
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
    pixelMap: image.PixelMap;
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
    preventDefault?: VoidCallback;
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
    valuePixelMap?: image.PixelMap;
    valueResourceStr?: ResourceStr;
    imageStyle: RichEditorImageSpanStyleResult;
    offsetInSpan: [ number, number ];
}
export interface RichEditorImageSpan {
    spanPosition: RichEditorSpanPosition;
    value: image.PixelMap | ResourceStr;
    imageStyle?: RichEditorImageSpanStyle;
}
export interface RichEditorRange {
    start?: number;
    end?: number;
}
export interface RichEditorGesture {
    onClick?: ((value0: ClickEvent) => void);
    onLongPress?: ((value0: GestureEvent) => void);
    onDoubleClick?: ((value0: GestureEvent) => void);
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
    onDisappear?: VoidCallback;
    menuType?: MenuType;
    onMenuShow?: MenuCallback;
    onMenuHide?: MenuCallback;
    previewMenuOptions?: PreviewMenuOptions;
}
export interface PreviewMenuOptions {
    hapticFeedbackMode?: HapticFeedbackMode;
}
export type RichEditorSpan = RichEditorImageSpanResult | RichEditorTextSpanResult;
export interface RichEditorAttribute extends CommonMethod {
    onReady(value: VoidCallback | undefined): this
    onSelect(value: ((value0: RichEditorSelection) => void) | undefined): this
    onSelectionChange(value: ((value0: RichEditorRange) => void) | undefined): this
    aboutToIMEInput(value: ((value0: RichEditorInsertValue) => boolean) | undefined): this
    onIMEInputComplete(value: ((value0: RichEditorTextSpanResult) => void) | undefined): this
    onDidIMEInput(value: ((value0: TextRange) => void) | undefined): this
    aboutToDelete(value: ((value0: RichEditorDeleteValue) => boolean) | undefined): this
    onDeleteComplete(value: VoidCallback | undefined): this
    copyOptions(value: CopyOptions | undefined): this
    onPaste(value: PasteEventCallback | undefined): this
    enableDataDetector(value: boolean | undefined): this
    enablePreviewText(value: boolean | undefined): this
    dataDetectorConfig(value: TextDataDetectorConfig | undefined): this
    caretColor(value: ResourceColor | undefined): this
    selectedBackgroundColor(value: ResourceColor | undefined): this
    onEditingChange(value: ((value0: boolean) => void) | undefined): this
    enterKeyType(value: EnterKeyType | undefined): this
    onSubmit(value: SubmitCallback | undefined): this
    onWillChange(value: ((value0: RichEditorChangeValue) => boolean) | undefined): this
    onDidChange(value: OnDidChangeCallback | undefined): this
    onCut(value: ((value0: CutEvent) => void) | undefined): this
    onCopy(value: ((value0: CopyEvent) => void) | undefined): this
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
    attributeModifier(value: AttributeModifier<RichEditorAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkRichEditorStyle extends ArkCommonMethodStyle implements RichEditorAttribute {
    onReady_value?: VoidCallback | undefined
    onSelect_value?: ((value0: RichEditorSelection) => void) | undefined
    onSelectionChange_value?: ((value0: RichEditorRange) => void) | undefined
    aboutToIMEInput_value?: ((value0: RichEditorInsertValue) => boolean) | undefined
    onIMEInputComplete_value?: ((value0: RichEditorTextSpanResult) => void) | undefined
    onDidIMEInput_value?: ((value0: TextRange) => void) | undefined
    aboutToDelete_value?: ((value0: RichEditorDeleteValue) => boolean) | undefined
    onDeleteComplete_value?: VoidCallback | undefined
    copyOptions_value?: CopyOptions | undefined
    onPaste_value?: PasteEventCallback | undefined
    enableDataDetector_value?: boolean | undefined
    enablePreviewText_value?: boolean | undefined
    dataDetectorConfig_value?: TextDataDetectorConfig | undefined
    caretColor_value?: ResourceColor | undefined
    selectedBackgroundColor_value?: ResourceColor | undefined
    onEditingChange_value?: ((value0: boolean) => void) | undefined
    enterKeyType_value?: EnterKeyType | undefined
    onSubmit_value?: SubmitCallback | undefined
    onWillChange_value?: ((value0: RichEditorChangeValue) => boolean) | undefined
    onDidChange_value?: OnDidChangeCallback | undefined
    onCut_value?: ((value0: CutEvent) => void) | undefined
    onCopy_value?: ((value0: CopyEvent) => void) | undefined
    editMenuOptions_value?: EditMenuOptions | undefined
    enableKeyboardOnFocus_value?: boolean | undefined
    enableHapticFeedback_value?: boolean | undefined
    barState_value?: BarState | undefined
    maxLength_value?: number | undefined
    maxLines_value?: number | undefined
    keyboardAppearance_value?: KeyboardAppearance | undefined
    stopBackPress_value?: boolean | undefined
    attributeModifier_value?: AttributeModifier<RichEditorAttribute> | AttributeModifier<CommonMethod> | undefined
    public onReady(value: VoidCallback | undefined): this {
        return this
    }
    public onSelect(value: ((value0: RichEditorSelection) => void) | undefined): this {
        return this
    }
    public onSelectionChange(value: ((value0: RichEditorRange) => void) | undefined): this {
        return this
    }
    public aboutToIMEInput(value: ((value0: RichEditorInsertValue) => boolean) | undefined): this {
        return this
    }
    public onIMEInputComplete(value: ((value0: RichEditorTextSpanResult) => void) | undefined): this {
        return this
    }
    public onDidIMEInput(value: ((value0: TextRange) => void) | undefined): this {
        return this
    }
    public aboutToDelete(value: ((value0: RichEditorDeleteValue) => boolean) | undefined): this {
        return this
    }
    public onDeleteComplete(value: VoidCallback | undefined): this {
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
    public onEditingChange(value: ((value0: boolean) => void) | undefined): this {
        return this
    }
    public enterKeyType(value: EnterKeyType | undefined): this {
        return this
    }
    public onSubmit(value: SubmitCallback | undefined): this {
        return this
    }
    public onWillChange(value: ((value0: RichEditorChangeValue) => boolean) | undefined): this {
        return this
    }
    public onDidChange(value: OnDidChangeCallback | undefined): this {
        return this
    }
    public onCut(value: ((value0: CutEvent) => void) | undefined): this {
        return this
    }
    public onCopy(value: ((value0: CopyEvent) => void) | undefined): this {
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
    public attributeModifier(value: AttributeModifier<RichEditorAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: RichEditorAttribute): void {
        super.apply(target)
        if (this.onReady_value !== undefined)
            target.onReady(this.onReady_value!)
        if (this.onSelect_value !== undefined)
            target.onSelect(this.onSelect_value!)
        if (this.onSelectionChange_value !== undefined)
            target.onSelectionChange(this.onSelectionChange_value!)
        if (this.aboutToIMEInput_value !== undefined)
            target.aboutToIMEInput(this.aboutToIMEInput_value!)
        if (this.onIMEInputComplete_value !== undefined)
            target.onIMEInputComplete(this.onIMEInputComplete_value!)
        if (this.onDidIMEInput_value !== undefined)
            target.onDidIMEInput(this.onDidIMEInput_value!)
        if (this.aboutToDelete_value !== undefined)
            target.aboutToDelete(this.aboutToDelete_value!)
        if (this.onDeleteComplete_value !== undefined)
            target.onDeleteComplete(this.onDeleteComplete_value!)
        if (this.copyOptions_value !== undefined)
            target.copyOptions(this.copyOptions_value!)
        if (this.onPaste_value !== undefined)
            target.onPaste(this.onPaste_value!)
        if (this.enableDataDetector_value !== undefined)
            target.enableDataDetector(this.enableDataDetector_value!)
        if (this.enablePreviewText_value !== undefined)
            target.enablePreviewText(this.enablePreviewText_value!)
        if (this.dataDetectorConfig_value !== undefined)
            target.dataDetectorConfig(this.dataDetectorConfig_value!)
        if (this.caretColor_value !== undefined)
            target.caretColor(this.caretColor_value!)
        if (this.selectedBackgroundColor_value !== undefined)
            target.selectedBackgroundColor(this.selectedBackgroundColor_value!)
        if (this.onEditingChange_value !== undefined)
            target.onEditingChange(this.onEditingChange_value!)
        if (this.enterKeyType_value !== undefined)
            target.enterKeyType(this.enterKeyType_value!)
        if (this.onSubmit_value !== undefined)
            target.onSubmit(this.onSubmit_value!)
        if (this.onWillChange_value !== undefined)
            target.onWillChange(this.onWillChange_value!)
        if (this.onDidChange_value !== undefined)
            target.onDidChange(this.onDidChange_value!)
        if (this.onCut_value !== undefined)
            target.onCut(this.onCut_value!)
        if (this.onCopy_value !== undefined)
            target.onCopy(this.onCopy_value!)
        if (this.editMenuOptions_value !== undefined)
            target.editMenuOptions(this.editMenuOptions_value!)
        if (this.enableKeyboardOnFocus_value !== undefined)
            target.enableKeyboardOnFocus(this.enableKeyboardOnFocus_value!)
        if (this.enableHapticFeedback_value !== undefined)
            target.enableHapticFeedback(this.enableHapticFeedback_value!)
        if (this.barState_value !== undefined)
            target.barState(this.barState_value!)
        if (this.maxLength_value !== undefined)
            target.maxLength(this.maxLength_value!)
        if (this.maxLines_value !== undefined)
            target.maxLines(this.maxLines_value!)
        if (this.keyboardAppearance_value !== undefined)
            target.keyboardAppearance(this.keyboardAppearance_value!)
        if (this.stopBackPress_value !== undefined)
            target.stopBackPress(this.stopBackPress_value!)
    }
}
export interface CutEvent {
    preventDefault?: VoidCallback;
}
export interface CopyEvent {
    preventDefault?: VoidCallback;
}
export interface RichEditorUrlStyle {
    url?: ResourceStr;
}
export type SubmitCallback = (enterKey: EnterKeyType, event: SubmitEvent) => void;
export type MenuOnAppearCallback = (start: number, end: number) => void;
export type MenuCallback = (start: number, end: number) => void;
export type PasteEventCallback = (event?: PasteEvent) => void;
export type OnHoverCallback = (status: boolean, event: HoverEvent) => void;

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
    public onReady(value: VoidCallback | undefined): this {
        if (this.checkPriority("onReady")) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.onReadyAttribute(value_casted)
            return this
        }
        return this
    }
    public onSelect(value: ((value0: RichEditorSelection) => void) | undefined): this {
        if (this.checkPriority("onSelect")) {
            const value_casted = value as (((value0: RichEditorSelection) => void) | undefined)
            this.getPeer()?.onSelectAttribute(value_casted)
            return this
        }
        return this
    }
    public onSelectionChange(value: ((value0: RichEditorRange) => void) | undefined): this {
        if (this.checkPriority("onSelectionChange")) {
            const value_casted = value as (((value0: RichEditorRange) => void) | undefined)
            this.getPeer()?.onSelectionChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public aboutToIMEInput(value: ((value0: RichEditorInsertValue) => boolean) | undefined): this {
        if (this.checkPriority("aboutToIMEInput")) {
            const value_casted = value as (((value0: RichEditorInsertValue) => boolean) | undefined)
            this.getPeer()?.aboutToIMEInputAttribute(value_casted)
            return this
        }
        return this
    }
    public onIMEInputComplete(value: ((value0: RichEditorTextSpanResult) => void) | undefined): this {
        if (this.checkPriority("onIMEInputComplete")) {
            const value_casted = value as (((value0: RichEditorTextSpanResult) => void) | undefined)
            this.getPeer()?.onIMEInputCompleteAttribute(value_casted)
            return this
        }
        return this
    }
    public onDidIMEInput(value: ((value0: TextRange) => void) | undefined): this {
        if (this.checkPriority("onDidIMEInput")) {
            const value_casted = value as (((value0: TextRange) => void) | undefined)
            this.getPeer()?.onDidIMEInputAttribute(value_casted)
            return this
        }
        return this
    }
    public aboutToDelete(value: ((value0: RichEditorDeleteValue) => boolean) | undefined): this {
        if (this.checkPriority("aboutToDelete")) {
            const value_casted = value as (((value0: RichEditorDeleteValue) => boolean) | undefined)
            this.getPeer()?.aboutToDeleteAttribute(value_casted)
            return this
        }
        return this
    }
    public onDeleteComplete(value: VoidCallback | undefined): this {
        if (this.checkPriority("onDeleteComplete")) {
            const value_casted = value as (VoidCallback | undefined)
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
    public onEditingChange(value: ((value0: boolean) => void) | undefined): this {
        if (this.checkPriority("onEditingChange")) {
            const value_casted = value as (((value0: boolean) => void) | undefined)
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
    public onWillChange(value: ((value0: RichEditorChangeValue) => boolean) | undefined): this {
        if (this.checkPriority("onWillChange")) {
            const value_casted = value as (((value0: RichEditorChangeValue) => boolean) | undefined)
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
    public onCut(value: ((value0: CutEvent) => void) | undefined): this {
        if (this.checkPriority("onCut")) {
            const value_casted = value as (((value0: CutEvent) => void) | undefined)
            this.getPeer()?.onCutAttribute(value_casted)
            return this
        }
        return this
    }
    public onCopy(value: ((value0: CopyEvent) => void) | undefined): this {
        if (this.checkPriority("onCopy")) {
            const value_casted = value as (((value0: CopyEvent) => void) | undefined)
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
            const options_casted = options as (SelectionMenuOptions | undefined)
            this.getPeer()?.bindSelectionMenuAttribute(spanType_casted, content_casted, responseType_casted, options_casted)
            return this
        }
        return this
    }
    public customKeyboard(value: CustomBuilder | undefined, options?: KeyboardOptions): this {
        if (this.checkPriority("customKeyboard")) {
            const value_casted = value as (CustomBuilder | undefined)
            const options_casted = options as (KeyboardOptions | undefined)
            this.getPeer()?.customKeyboardAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    public placeholder(value: ResourceStr | undefined, style?: PlaceholderStyle): this {
        if (this.checkPriority("placeholder")) {
            const value_casted = value as (ResourceStr | undefined)
            const style_casted = style as (PlaceholderStyle | undefined)
            this.getPeer()?.placeholderAttribute(value_casted, style_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RichEditorAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withRichEditorStyle(receiver: RichEditorAttribute, modifier: AttributeModifier<RichEditorAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkRichEditorStyle()
        if (modifier!.isUpdater)
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
@memo
@BuilderLambda("RichEditorImpl")
export function RichEditor(
    value: RichEditorOptions | RichEditorStyledStringOptions,
    @memo
    content_?: () => void,
): RichEditorAttribute {
    throw new Error("Not implemented")
}

@memo
export function RichEditorImpl(
    @memo
    style: ((attributes: RichEditorAttribute) => void) | undefined,
    value: RichEditorOptions | RichEditorStyledStringOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkRichEditorComponent>((): ArkRichEditorComponent => {
        return new ArkRichEditorComponent()
    })
    NodeAttach<ArkRichEditorPeer>((): ArkRichEditorPeer => ArkRichEditorPeer.create(receiver), (_: ArkRichEditorPeer): void => {
        receiver.setRichEditorOptions(value)
        style?.(receiver)
        withRichEditorStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class RichEditorBaseController_serializer {
    public static write(buffer: SerializerBase, value: RichEditorBaseController): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): RichEditorBaseController {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return RichEditorBaseControllerInternal.fromPtr(ptr)
    }
}
export class RichEditorController_serializer {
    public static write(buffer: SerializerBase, value: RichEditorController): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): RichEditorController {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return RichEditorControllerInternal.fromPtr(ptr)
    }
}
export class RichEditorOptions_serializer {
    public static write(buffer: SerializerBase, value: RichEditorOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_controller  = value.controller
        RichEditorController_serializer.write(valueSerializer, value_controller)
    }
    public static read(buffer: DeserializerBase): RichEditorOptions {
        let valueDeserializer : DeserializerBase = buffer
        const controller_result : RichEditorController = (RichEditorController_serializer.read(valueDeserializer) as RichEditorController)
        let value : RichEditorOptions = ({controller: controller_result} as RichEditorOptions)
        return value
    }
}
export class RichEditorStyledStringController_serializer {
    public static write(buffer: SerializerBase, value: RichEditorStyledStringController): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): RichEditorStyledStringController {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return RichEditorStyledStringControllerInternal.fromPtr(ptr)
    }
}
export class RichEditorStyledStringOptions_serializer {
    public static write(buffer: SerializerBase, value: RichEditorStyledStringOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_controller  = value.controller
        RichEditorStyledStringController_serializer.write(valueSerializer, value_controller)
    }
    public static read(buffer: DeserializerBase): RichEditorStyledStringOptions {
        let valueDeserializer : DeserializerBase = buffer
        const controller_result : RichEditorStyledStringController = (RichEditorStyledStringController_serializer.read(valueDeserializer) as RichEditorStyledStringController)
        let value : RichEditorStyledStringOptions = ({controller: controller_result} as RichEditorStyledStringOptions)
        return value
    }
}
export class KeyboardOptions_serializer {
    public static write(buffer: SerializerBase, value: KeyboardOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_supportAvoidance  = value.supportAvoidance
        let value_supportAvoidance_type : int32 = RuntimeType.UNDEFINED
        value_supportAvoidance_type = runtimeType(value_supportAvoidance)
        valueSerializer.writeInt8(value_supportAvoidance_type)
        if ((RuntimeType.UNDEFINED) != (value_supportAvoidance_type)) {
            const value_supportAvoidance_value  = value_supportAvoidance!
            valueSerializer.writeBoolean(value_supportAvoidance_value)
        }
    }
    public static read(buffer: DeserializerBase): KeyboardOptions {
        let valueDeserializer : DeserializerBase = buffer
        const supportAvoidance_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let supportAvoidance_buf : boolean | undefined
        if ((RuntimeType.UNDEFINED) != (supportAvoidance_buf_runtimeType))
        {
            supportAvoidance_buf = valueDeserializer.readBoolean()
        }
        const supportAvoidance_result : boolean | undefined = supportAvoidance_buf
        let value : KeyboardOptions = ({supportAvoidance: supportAvoidance_result} as KeyboardOptions)
        return value
    }
}
export class PreviewMenuOptions_serializer {
    public static write(buffer: SerializerBase, value: PreviewMenuOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_hapticFeedbackMode  = value.hapticFeedbackMode
        let value_hapticFeedbackMode_type : int32 = RuntimeType.UNDEFINED
        value_hapticFeedbackMode_type = runtimeType(value_hapticFeedbackMode)
        valueSerializer.writeInt8(value_hapticFeedbackMode_type)
        if ((RuntimeType.UNDEFINED) != (value_hapticFeedbackMode_type)) {
            const value_hapticFeedbackMode_value  = (value_hapticFeedbackMode as HapticFeedbackMode)
            valueSerializer.writeInt32(TypeChecker.HapticFeedbackMode_ToNumeric(value_hapticFeedbackMode_value))
        }
    }
    public static read(buffer: DeserializerBase): PreviewMenuOptions {
        let valueDeserializer : DeserializerBase = buffer
        const hapticFeedbackMode_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let hapticFeedbackMode_buf : HapticFeedbackMode | undefined
        if ((RuntimeType.UNDEFINED) != (hapticFeedbackMode_buf_runtimeType))
        {
            hapticFeedbackMode_buf = TypeChecker.HapticFeedbackMode_FromNumeric(valueDeserializer.readInt32())
        }
        const hapticFeedbackMode_result : HapticFeedbackMode | undefined = hapticFeedbackMode_buf
        let value : PreviewMenuOptions = ({hapticFeedbackMode: hapticFeedbackMode_result} as PreviewMenuOptions)
        return value
    }
}
export class RichEditorBuilderSpanOptions_serializer {
    public static write(buffer: SerializerBase, value: RichEditorBuilderSpanOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_offset  = value.offset
        let value_offset_type : int32 = RuntimeType.UNDEFINED
        value_offset_type = runtimeType(value_offset)
        valueSerializer.writeInt8(value_offset_type)
        if ((RuntimeType.UNDEFINED) != (value_offset_type)) {
            const value_offset_value  = value_offset!
            valueSerializer.writeNumber(value_offset_value)
        }
        const value_dragBackgroundColor  = value.dragBackgroundColor
        let value_dragBackgroundColor_type : int32 = RuntimeType.UNDEFINED
        value_dragBackgroundColor_type = runtimeType(value_dragBackgroundColor)
        valueSerializer.writeInt8(value_dragBackgroundColor_type)
        if ((RuntimeType.UNDEFINED) != (value_dragBackgroundColor_type)) {
            const value_dragBackgroundColor_value  = value_dragBackgroundColor!
            ColorMetrics_serializer.write(valueSerializer, value_dragBackgroundColor_value)
        }
        const value_isDragShadowNeeded  = value.isDragShadowNeeded
        let value_isDragShadowNeeded_type : int32 = RuntimeType.UNDEFINED
        value_isDragShadowNeeded_type = runtimeType(value_isDragShadowNeeded)
        valueSerializer.writeInt8(value_isDragShadowNeeded_type)
        if ((RuntimeType.UNDEFINED) != (value_isDragShadowNeeded_type)) {
            const value_isDragShadowNeeded_value  = value_isDragShadowNeeded!
            valueSerializer.writeBoolean(value_isDragShadowNeeded_value)
        }
    }
    public static read(buffer: DeserializerBase): RichEditorBuilderSpanOptions {
        let valueDeserializer : DeserializerBase = buffer
        const offset_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let offset_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (offset_buf_runtimeType))
        {
            offset_buf = (valueDeserializer.readNumber() as number)
        }
        const offset_result : number | undefined = offset_buf
        const dragBackgroundColor_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let dragBackgroundColor_buf : ColorMetrics | undefined
        if ((RuntimeType.UNDEFINED) != (dragBackgroundColor_buf_runtimeType))
        {
            dragBackgroundColor_buf = (ColorMetrics_serializer.read(valueDeserializer) as ColorMetrics)
        }
        const dragBackgroundColor_result : ColorMetrics | undefined = dragBackgroundColor_buf
        const isDragShadowNeeded_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let isDragShadowNeeded_buf : boolean | undefined
        if ((RuntimeType.UNDEFINED) != (isDragShadowNeeded_buf_runtimeType))
        {
            isDragShadowNeeded_buf = valueDeserializer.readBoolean()
        }
        const isDragShadowNeeded_result : boolean | undefined = isDragShadowNeeded_buf
        let value : RichEditorBuilderSpanOptions = ({offset: offset_result, dragBackgroundColor: dragBackgroundColor_result, isDragShadowNeeded: isDragShadowNeeded_result} as RichEditorBuilderSpanOptions)
        return value
    }
}
export class RichEditorDeleteValue_serializer {
    public static write(buffer: SerializerBase, value: RichEditorDeleteValue): void {
        let valueSerializer : SerializerBase = buffer
        const value_offset  = value.offset
        valueSerializer.writeNumber(value_offset)
        const value_direction  = value.direction
        valueSerializer.writeInt32(TypeChecker.RichEditorDeleteDirection_ToNumeric(value_direction))
        const value_length  = value.length
        valueSerializer.writeNumber(value_length)
        const value_richEditorDeleteSpans  = value.richEditorDeleteSpans
        valueSerializer.writeInt32(value_richEditorDeleteSpans.length as int32)
        for (let i = 0; i < value_richEditorDeleteSpans.length; i++) {
            const value_richEditorDeleteSpans_element : RichEditorTextSpanResult | RichEditorImageSpanResult = value_richEditorDeleteSpans[i]
            let value_richEditorDeleteSpans_element_type : int32 = RuntimeType.UNDEFINED
            value_richEditorDeleteSpans_element_type = runtimeType(value_richEditorDeleteSpans_element)
            if (TypeChecker.isRichEditorTextSpanResult(value_richEditorDeleteSpans_element, true, false, false, true, false, false, false, false, false)) {
                valueSerializer.writeInt8(0)
                const value_richEditorDeleteSpans_element_0  = value_richEditorDeleteSpans_element as RichEditorTextSpanResult
                RichEditorTextSpanResult_serializer.write(valueSerializer, value_richEditorDeleteSpans_element_0)
            }
            else if (TypeChecker.isRichEditorImageSpanResult(value_richEditorDeleteSpans_element, true, false, false, false, true)) {
                valueSerializer.writeInt8(1)
                const value_richEditorDeleteSpans_element_1  = value_richEditorDeleteSpans_element as RichEditorImageSpanResult
                RichEditorImageSpanResult_serializer.write(valueSerializer, value_richEditorDeleteSpans_element_1)
            }
        }
    }
    public static read(buffer: DeserializerBase): RichEditorDeleteValue {
        let valueDeserializer : DeserializerBase = buffer
        const offset_result : number = (valueDeserializer.readNumber() as number)
        const direction_result : RichEditorDeleteDirection = TypeChecker.RichEditorDeleteDirection_FromNumeric(valueDeserializer.readInt32())
        const length_result : number = (valueDeserializer.readNumber() as number)
        const richEditorDeleteSpans_buf_length : int32 = valueDeserializer.readInt32()
        let richEditorDeleteSpans_buf : Array<RichEditorTextSpanResult | RichEditorImageSpanResult> = new Array<RichEditorTextSpanResult | RichEditorImageSpanResult>(richEditorDeleteSpans_buf_length)
        for (let richEditorDeleteSpans_buf_i = 0; richEditorDeleteSpans_buf_i < richEditorDeleteSpans_buf_length; richEditorDeleteSpans_buf_i++) {
            const richEditorDeleteSpans_buf_buf_selector : int32 = valueDeserializer.readInt8()
            let richEditorDeleteSpans_buf_buf : RichEditorTextSpanResult | RichEditorImageSpanResult | undefined
            if (richEditorDeleteSpans_buf_buf_selector == 0) {
                richEditorDeleteSpans_buf_buf = RichEditorTextSpanResult_serializer.read(valueDeserializer)
            }
            else if (richEditorDeleteSpans_buf_buf_selector == 1) {
                richEditorDeleteSpans_buf_buf = RichEditorImageSpanResult_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for richEditorDeleteSpans_buf_buf has to be chosen through deserialisation.")
            }
            richEditorDeleteSpans_buf[richEditorDeleteSpans_buf_i] = (richEditorDeleteSpans_buf_buf as RichEditorTextSpanResult | RichEditorImageSpanResult)
        }
        const richEditorDeleteSpans_result : Array<RichEditorTextSpanResult | RichEditorImageSpanResult> = richEditorDeleteSpans_buf
        let value : RichEditorDeleteValue = ({offset: offset_result, direction: direction_result, length: length_result, richEditorDeleteSpans: richEditorDeleteSpans_result} as RichEditorDeleteValue)
        return value
    }
}
export class RichEditorGesture_serializer {
    public static write(buffer: SerializerBase, value: RichEditorGesture): void {
        let valueSerializer : SerializerBase = buffer
        const value_onClick  = value.onClick
        let value_onClick_type : int32 = RuntimeType.UNDEFINED
        value_onClick_type = runtimeType(value_onClick)
        valueSerializer.writeInt8(value_onClick_type)
        if ((RuntimeType.UNDEFINED) != (value_onClick_type)) {
            const value_onClick_value  = value_onClick!
            valueSerializer.holdAndWriteCallback(value_onClick_value)
        }
        const value_onLongPress  = value.onLongPress
        let value_onLongPress_type : int32 = RuntimeType.UNDEFINED
        value_onLongPress_type = runtimeType(value_onLongPress)
        valueSerializer.writeInt8(value_onLongPress_type)
        if ((RuntimeType.UNDEFINED) != (value_onLongPress_type)) {
            const value_onLongPress_value  = value_onLongPress!
            valueSerializer.holdAndWriteCallback(value_onLongPress_value)
        }
        const value_onDoubleClick  = value.onDoubleClick
        let value_onDoubleClick_type : int32 = RuntimeType.UNDEFINED
        value_onDoubleClick_type = runtimeType(value_onDoubleClick)
        valueSerializer.writeInt8(value_onDoubleClick_type)
        if ((RuntimeType.UNDEFINED) != (value_onDoubleClick_type)) {
            const value_onDoubleClick_value  = value_onDoubleClick!
            valueSerializer.holdAndWriteCallback(value_onDoubleClick_value)
        }
    }
    public static read(buffer: DeserializerBase): RichEditorGesture {
        let valueDeserializer : DeserializerBase = buffer
        const onClick_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let onClick_buf : ((value0: ClickEvent) => void) | undefined
        if ((RuntimeType.UNDEFINED) != (onClick_buf_runtimeType))
        {
            const onClick_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onClick_buf__call : KPointer = valueDeserializer.readPointer()
            const onClick_buf__callSync : KPointer = valueDeserializer.readPointer()
            onClick_buf = (value0: ClickEvent):void => { 
    const onClick_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onClick_buf__argsSerializer.writeInt32(onClick_buf__resource.resourceId);
    onClick_buf__argsSerializer.writePointer(onClick_buf__call);
    onClick_buf__argsSerializer.writePointer(onClick_buf__callSync);
    ClickEvent_serializer.write(onClick_buf__argsSerializer, value0);
    InteropNativeModule._CallCallback(1097178637, onClick_buf__argsSerializer.asBuffer(), onClick_buf__argsSerializer.length());
    onClick_buf__argsSerializer.release();
    return; }
        }
        const onClick_result : ((value0: ClickEvent) => void) | undefined = onClick_buf
        const onLongPress_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let onLongPress_buf : ((value0: GestureEvent) => void) | undefined
        if ((RuntimeType.UNDEFINED) != (onLongPress_buf_runtimeType))
        {
            const onLongPress_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onLongPress_buf__call : KPointer = valueDeserializer.readPointer()
            const onLongPress_buf__callSync : KPointer = valueDeserializer.readPointer()
            onLongPress_buf = (value0: GestureEvent):void => { 
    const onLongPress_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onLongPress_buf__argsSerializer.writeInt32(onLongPress_buf__resource.resourceId);
    onLongPress_buf__argsSerializer.writePointer(onLongPress_buf__call);
    onLongPress_buf__argsSerializer.writePointer(onLongPress_buf__callSync);
    GestureEvent_serializer.write(onLongPress_buf__argsSerializer, value0);
    InteropNativeModule._CallCallback(-1143194492, onLongPress_buf__argsSerializer.asBuffer(), onLongPress_buf__argsSerializer.length());
    onLongPress_buf__argsSerializer.release();
    return; }
        }
        const onLongPress_result : ((value0: GestureEvent) => void) | undefined = onLongPress_buf
        const onDoubleClick_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let onDoubleClick_buf : ((value0: GestureEvent) => void) | undefined
        if ((RuntimeType.UNDEFINED) != (onDoubleClick_buf_runtimeType))
        {
            const onDoubleClick_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDoubleClick_buf__call : KPointer = valueDeserializer.readPointer()
            const onDoubleClick_buf__callSync : KPointer = valueDeserializer.readPointer()
            onDoubleClick_buf = (value0: GestureEvent):void => { 
    const onDoubleClick_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onDoubleClick_buf__argsSerializer.writeInt32(onDoubleClick_buf__resource.resourceId);
    onDoubleClick_buf__argsSerializer.writePointer(onDoubleClick_buf__call);
    onDoubleClick_buf__argsSerializer.writePointer(onDoubleClick_buf__callSync);
    GestureEvent_serializer.write(onDoubleClick_buf__argsSerializer, value0);
    InteropNativeModule._CallCallback(-1143194492, onDoubleClick_buf__argsSerializer.asBuffer(), onDoubleClick_buf__argsSerializer.length());
    onDoubleClick_buf__argsSerializer.release();
    return; }
        }
        const onDoubleClick_result : ((value0: GestureEvent) => void) | undefined = onDoubleClick_buf
        let value : RichEditorGesture = ({onClick: onClick_result, onLongPress: onLongPress_result, onDoubleClick: onDoubleClick_result} as RichEditorGesture)
        return value
    }
}
export class RichEditorInsertValue_serializer {
    public static write(buffer: SerializerBase, value: RichEditorInsertValue): void {
        let valueSerializer : SerializerBase = buffer
        const value_insertOffset  = value.insertOffset
        valueSerializer.writeNumber(value_insertOffset)
        const value_insertValue  = value.insertValue
        valueSerializer.writeString(value_insertValue)
        const value_previewText  = value.previewText
        let value_previewText_type : int32 = RuntimeType.UNDEFINED
        value_previewText_type = runtimeType(value_previewText)
        valueSerializer.writeInt8(value_previewText_type)
        if ((RuntimeType.UNDEFINED) != (value_previewText_type)) {
            const value_previewText_value  = value_previewText!
            valueSerializer.writeString(value_previewText_value)
        }
    }
    public static read(buffer: DeserializerBase): RichEditorInsertValue {
        let valueDeserializer : DeserializerBase = buffer
        const insertOffset_result : number = (valueDeserializer.readNumber() as number)
        const insertValue_result : string = (valueDeserializer.readString() as string)
        const previewText_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let previewText_buf : string | undefined
        if ((RuntimeType.UNDEFINED) != (previewText_buf_runtimeType))
        {
            previewText_buf = (valueDeserializer.readString() as string)
        }
        const previewText_result : string | undefined = previewText_buf
        let value : RichEditorInsertValue = ({insertOffset: insertOffset_result, insertValue: insertValue_result, previewText: previewText_result} as RichEditorInsertValue)
        return value
    }
}
export class RichEditorRange_serializer {
    public static write(buffer: SerializerBase, value: RichEditorRange): void {
        let valueSerializer : SerializerBase = buffer
        const value_start  = value.start
        let value_start_type : int32 = RuntimeType.UNDEFINED
        value_start_type = runtimeType(value_start)
        valueSerializer.writeInt8(value_start_type)
        if ((RuntimeType.UNDEFINED) != (value_start_type)) {
            const value_start_value  = value_start!
            valueSerializer.writeNumber(value_start_value)
        }
        const value_end  = value.end
        let value_end_type : int32 = RuntimeType.UNDEFINED
        value_end_type = runtimeType(value_end)
        valueSerializer.writeInt8(value_end_type)
        if ((RuntimeType.UNDEFINED) != (value_end_type)) {
            const value_end_value  = value_end!
            valueSerializer.writeNumber(value_end_value)
        }
    }
    public static read(buffer: DeserializerBase): RichEditorRange {
        let valueDeserializer : DeserializerBase = buffer
        const start_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let start_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (start_buf_runtimeType))
        {
            start_buf = (valueDeserializer.readNumber() as number)
        }
        const start_result : number | undefined = start_buf
        const end_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let end_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (end_buf_runtimeType))
        {
            end_buf = (valueDeserializer.readNumber() as number)
        }
        const end_result : number | undefined = end_buf
        let value : RichEditorRange = ({start: start_result, end: end_result} as RichEditorRange)
        return value
    }
}
export class RichEditorSelection_serializer {
    public static write(buffer: SerializerBase, value: RichEditorSelection): void {
        let valueSerializer : SerializerBase = buffer
        const value_selection  = value.selection
        const value_selection_0  = value_selection[0]
        valueSerializer.writeNumber(value_selection_0)
        const value_selection_1  = value_selection[1]
        valueSerializer.writeNumber(value_selection_1)
        const value_spans  = value.spans
        valueSerializer.writeInt32(value_spans.length as int32)
        for (let i = 0; i < value_spans.length; i++) {
            const value_spans_element : RichEditorTextSpanResult | RichEditorImageSpanResult = value_spans[i]
            let value_spans_element_type : int32 = RuntimeType.UNDEFINED
            value_spans_element_type = runtimeType(value_spans_element)
            if (TypeChecker.isRichEditorTextSpanResult(value_spans_element, true, false, false, true, false, false, false, false, false)) {
                valueSerializer.writeInt8(0)
                const value_spans_element_0  = value_spans_element as RichEditorTextSpanResult
                RichEditorTextSpanResult_serializer.write(valueSerializer, value_spans_element_0)
            }
            else if (TypeChecker.isRichEditorImageSpanResult(value_spans_element, true, false, false, false, true)) {
                valueSerializer.writeInt8(1)
                const value_spans_element_1  = value_spans_element as RichEditorImageSpanResult
                RichEditorImageSpanResult_serializer.write(valueSerializer, value_spans_element_1)
            }
        }
    }
    public static read(buffer: DeserializerBase): RichEditorSelection {
        let valueDeserializer : DeserializerBase = buffer
        const selection_buf_value0 : number = (valueDeserializer.readNumber() as number)
        const selection_buf_value1 : number = (valueDeserializer.readNumber() as number)
        const selection_result : [ number, number ] = ([selection_buf_value0, selection_buf_value1] as [ number, number ])
        const spans_buf_length : int32 = valueDeserializer.readInt32()
        let spans_buf : Array<RichEditorTextSpanResult | RichEditorImageSpanResult> = new Array<RichEditorTextSpanResult | RichEditorImageSpanResult>(spans_buf_length)
        for (let spans_buf_i = 0; spans_buf_i < spans_buf_length; spans_buf_i++) {
            const spans_buf_buf_selector : int32 = valueDeserializer.readInt8()
            let spans_buf_buf : RichEditorTextSpanResult | RichEditorImageSpanResult | undefined
            if (spans_buf_buf_selector == 0) {
                spans_buf_buf = RichEditorTextSpanResult_serializer.read(valueDeserializer)
            }
            else if (spans_buf_buf_selector == 1) {
                spans_buf_buf = RichEditorImageSpanResult_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for spans_buf_buf has to be chosen through deserialisation.")
            }
            spans_buf[spans_buf_i] = (spans_buf_buf as RichEditorTextSpanResult | RichEditorImageSpanResult)
        }
        const spans_result : Array<RichEditorTextSpanResult | RichEditorImageSpanResult> = spans_buf
        let value : RichEditorSelection = ({selection: selection_result, spans: spans_result} as RichEditorSelection)
        return value
    }
}
export class RichEditorSpanPosition_serializer {
    public static write(buffer: SerializerBase, value: RichEditorSpanPosition): void {
        let valueSerializer : SerializerBase = buffer
        const value_spanIndex  = value.spanIndex
        valueSerializer.writeNumber(value_spanIndex)
        const value_spanRange  = value.spanRange
        const value_spanRange_0  = value_spanRange[0]
        valueSerializer.writeNumber(value_spanRange_0)
        const value_spanRange_1  = value_spanRange[1]
        valueSerializer.writeNumber(value_spanRange_1)
    }
    public static read(buffer: DeserializerBase): RichEditorSpanPosition {
        let valueDeserializer : DeserializerBase = buffer
        const spanIndex_result : number = (valueDeserializer.readNumber() as number)
        const spanRange_buf_value0 : number = (valueDeserializer.readNumber() as number)
        const spanRange_buf_value1 : number = (valueDeserializer.readNumber() as number)
        const spanRange_result : [ number, number ] = ([spanRange_buf_value0, spanRange_buf_value1] as [ number, number ])
        let value : RichEditorSpanPosition = ({spanIndex: spanIndex_result, spanRange: spanRange_result} as RichEditorSpanPosition)
        return value
    }
}
export class CopyEvent_serializer {
    public static write(buffer: SerializerBase, value: CopyEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_preventDefault  = value.preventDefault
        let value_preventDefault_type : int32 = RuntimeType.UNDEFINED
        value_preventDefault_type = runtimeType(value_preventDefault)
        valueSerializer.writeInt8(value_preventDefault_type)
        if ((RuntimeType.UNDEFINED) != (value_preventDefault_type)) {
            const value_preventDefault_value  = value_preventDefault!
            valueSerializer.holdAndWriteCallback(value_preventDefault_value)
        }
    }
    public static read(buffer: DeserializerBase): CopyEvent {
        let valueDeserializer : DeserializerBase = buffer
        const preventDefault_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let preventDefault_buf : VoidCallback | undefined
        if ((RuntimeType.UNDEFINED) != (preventDefault_buf_runtimeType))
        {
            const preventDefault_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const preventDefault_buf__call : KPointer = valueDeserializer.readPointer()
            const preventDefault_buf__callSync : KPointer = valueDeserializer.readPointer()
            preventDefault_buf = ():void => { 
    const preventDefault_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    preventDefault_buf__argsSerializer.writeInt32(preventDefault_buf__resource.resourceId);
    preventDefault_buf__argsSerializer.writePointer(preventDefault_buf__call);
    preventDefault_buf__argsSerializer.writePointer(preventDefault_buf__callSync);
    InteropNativeModule._CallCallback(-2038961969, preventDefault_buf__argsSerializer.asBuffer(), preventDefault_buf__argsSerializer.length());
    preventDefault_buf__argsSerializer.release();
    return; }
        }
        const preventDefault_result : VoidCallback | undefined = preventDefault_buf
        let value : CopyEvent = ({preventDefault: preventDefault_result} as CopyEvent)
        return value
    }
}
export class CutEvent_serializer {
    public static write(buffer: SerializerBase, value: CutEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_preventDefault  = value.preventDefault
        let value_preventDefault_type : int32 = RuntimeType.UNDEFINED
        value_preventDefault_type = runtimeType(value_preventDefault)
        valueSerializer.writeInt8(value_preventDefault_type)
        if ((RuntimeType.UNDEFINED) != (value_preventDefault_type)) {
            const value_preventDefault_value  = value_preventDefault!
            valueSerializer.holdAndWriteCallback(value_preventDefault_value)
        }
    }
    public static read(buffer: DeserializerBase): CutEvent {
        let valueDeserializer : DeserializerBase = buffer
        const preventDefault_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let preventDefault_buf : VoidCallback | undefined
        if ((RuntimeType.UNDEFINED) != (preventDefault_buf_runtimeType))
        {
            const preventDefault_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const preventDefault_buf__call : KPointer = valueDeserializer.readPointer()
            const preventDefault_buf__callSync : KPointer = valueDeserializer.readPointer()
            preventDefault_buf = ():void => { 
    const preventDefault_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    preventDefault_buf__argsSerializer.writeInt32(preventDefault_buf__resource.resourceId);
    preventDefault_buf__argsSerializer.writePointer(preventDefault_buf__call);
    preventDefault_buf__argsSerializer.writePointer(preventDefault_buf__callSync);
    InteropNativeModule._CallCallback(-2038961969, preventDefault_buf__argsSerializer.asBuffer(), preventDefault_buf__argsSerializer.length());
    preventDefault_buf__argsSerializer.release();
    return; }
        }
        const preventDefault_result : VoidCallback | undefined = preventDefault_buf
        let value : CutEvent = ({preventDefault: preventDefault_result} as CutEvent)
        return value
    }
}
export class PasteEvent_serializer {
    public static write(buffer: SerializerBase, value: PasteEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_preventDefault  = value.preventDefault
        let value_preventDefault_type : int32 = RuntimeType.UNDEFINED
        value_preventDefault_type = runtimeType(value_preventDefault)
        valueSerializer.writeInt8(value_preventDefault_type)
        if ((RuntimeType.UNDEFINED) != (value_preventDefault_type)) {
            const value_preventDefault_value  = value_preventDefault!
            valueSerializer.holdAndWriteCallback(value_preventDefault_value)
        }
    }
    public static read(buffer: DeserializerBase): PasteEvent {
        let valueDeserializer : DeserializerBase = buffer
        const preventDefault_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let preventDefault_buf : VoidCallback | undefined
        if ((RuntimeType.UNDEFINED) != (preventDefault_buf_runtimeType))
        {
            const preventDefault_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const preventDefault_buf__call : KPointer = valueDeserializer.readPointer()
            const preventDefault_buf__callSync : KPointer = valueDeserializer.readPointer()
            preventDefault_buf = ():void => { 
    const preventDefault_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    preventDefault_buf__argsSerializer.writeInt32(preventDefault_buf__resource.resourceId);
    preventDefault_buf__argsSerializer.writePointer(preventDefault_buf__call);
    preventDefault_buf__argsSerializer.writePointer(preventDefault_buf__callSync);
    InteropNativeModule._CallCallback(-2038961969, preventDefault_buf__argsSerializer.asBuffer(), preventDefault_buf__argsSerializer.length());
    preventDefault_buf__argsSerializer.release();
    return; }
        }
        const preventDefault_result : VoidCallback | undefined = preventDefault_buf
        let value : PasteEvent = ({preventDefault: preventDefault_result} as PasteEvent)
        return value
    }
}
export class RichEditorChangeValue_serializer {
    public static write(buffer: SerializerBase, value: RichEditorChangeValue): void {
        let valueSerializer : SerializerBase = buffer
        const value_rangeBefore  = value.rangeBefore
        TextRange_serializer.write(valueSerializer, value_rangeBefore)
        const value_replacedSpans  = value.replacedSpans
        valueSerializer.writeInt32(value_replacedSpans.length as int32)
        for (let i = 0; i < value_replacedSpans.length; i++) {
            const value_replacedSpans_element : RichEditorTextSpanResult = value_replacedSpans[i]
            RichEditorTextSpanResult_serializer.write(valueSerializer, value_replacedSpans_element)
        }
        const value_replacedImageSpans  = value.replacedImageSpans
        valueSerializer.writeInt32(value_replacedImageSpans.length as int32)
        for (let i = 0; i < value_replacedImageSpans.length; i++) {
            const value_replacedImageSpans_element : RichEditorImageSpanResult = value_replacedImageSpans[i]
            RichEditorImageSpanResult_serializer.write(valueSerializer, value_replacedImageSpans_element)
        }
        const value_replacedSymbolSpans  = value.replacedSymbolSpans
        valueSerializer.writeInt32(value_replacedSymbolSpans.length as int32)
        for (let i = 0; i < value_replacedSymbolSpans.length; i++) {
            const value_replacedSymbolSpans_element : RichEditorTextSpanResult = value_replacedSymbolSpans[i]
            RichEditorTextSpanResult_serializer.write(valueSerializer, value_replacedSymbolSpans_element)
        }
    }
    public static read(buffer: DeserializerBase): RichEditorChangeValue {
        let valueDeserializer : DeserializerBase = buffer
        const rangeBefore_result : TextRange = TextRange_serializer.read(valueDeserializer)
        const replacedSpans_buf_length : int32 = valueDeserializer.readInt32()
        let replacedSpans_buf : Array<RichEditorTextSpanResult> = new Array<RichEditorTextSpanResult>(replacedSpans_buf_length)
        for (let replacedSpans_buf_i = 0; replacedSpans_buf_i < replacedSpans_buf_length; replacedSpans_buf_i++) {
            replacedSpans_buf[replacedSpans_buf_i] = RichEditorTextSpanResult_serializer.read(valueDeserializer)
        }
        const replacedSpans_result : Array<RichEditorTextSpanResult> = replacedSpans_buf
        const replacedImageSpans_buf_length : int32 = valueDeserializer.readInt32()
        let replacedImageSpans_buf : Array<RichEditorImageSpanResult> = new Array<RichEditorImageSpanResult>(replacedImageSpans_buf_length)
        for (let replacedImageSpans_buf_i = 0; replacedImageSpans_buf_i < replacedImageSpans_buf_length; replacedImageSpans_buf_i++) {
            replacedImageSpans_buf[replacedImageSpans_buf_i] = RichEditorImageSpanResult_serializer.read(valueDeserializer)
        }
        const replacedImageSpans_result : Array<RichEditorImageSpanResult> = replacedImageSpans_buf
        const replacedSymbolSpans_buf_length : int32 = valueDeserializer.readInt32()
        let replacedSymbolSpans_buf : Array<RichEditorTextSpanResult> = new Array<RichEditorTextSpanResult>(replacedSymbolSpans_buf_length)
        for (let replacedSymbolSpans_buf_i = 0; replacedSymbolSpans_buf_i < replacedSymbolSpans_buf_length; replacedSymbolSpans_buf_i++) {
            replacedSymbolSpans_buf[replacedSymbolSpans_buf_i] = RichEditorTextSpanResult_serializer.read(valueDeserializer)
        }
        const replacedSymbolSpans_result : Array<RichEditorTextSpanResult> = replacedSymbolSpans_buf
        let value : RichEditorChangeValue = ({rangeBefore: rangeBefore_result, replacedSpans: replacedSpans_result, replacedImageSpans: replacedImageSpans_result, replacedSymbolSpans: replacedSymbolSpans_result} as RichEditorChangeValue)
        return value
    }
}
export class RichEditorSymbolSpanStyle_serializer {
    public static write(buffer: SerializerBase, value: RichEditorSymbolSpanStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_fontSize  = value.fontSize
        let value_fontSize_type : int32 = RuntimeType.UNDEFINED
        value_fontSize_type = runtimeType(value_fontSize)
        valueSerializer.writeInt8(value_fontSize_type)
        if ((RuntimeType.UNDEFINED) != (value_fontSize_type)) {
            const value_fontSize_value  = value_fontSize!
            let value_fontSize_value_type : int32 = RuntimeType.UNDEFINED
            value_fontSize_value_type = runtimeType(value_fontSize_value)
            if (RuntimeType.NUMBER == value_fontSize_value_type) {
                valueSerializer.writeInt8(0)
                const value_fontSize_value_0  = value_fontSize_value as number
                valueSerializer.writeNumber(value_fontSize_value_0)
            }
            else if (RuntimeType.STRING == value_fontSize_value_type) {
                valueSerializer.writeInt8(1)
                const value_fontSize_value_1  = value_fontSize_value as string
                valueSerializer.writeString(value_fontSize_value_1)
            }
            else if (RuntimeType.OBJECT == value_fontSize_value_type) {
                valueSerializer.writeInt8(2)
                const value_fontSize_value_2  = value_fontSize_value as Resource
                Resource_serializer.write(valueSerializer, value_fontSize_value_2)
            }
        }
        const value_fontColor  = value.fontColor
        let value_fontColor_type : int32 = RuntimeType.UNDEFINED
        value_fontColor_type = runtimeType(value_fontColor)
        valueSerializer.writeInt8(value_fontColor_type)
        if ((RuntimeType.UNDEFINED) != (value_fontColor_type)) {
            const value_fontColor_value  = value_fontColor!
            valueSerializer.writeInt32(value_fontColor_value.length as int32)
            for (let i = 0; i < value_fontColor_value.length; i++) {
                const value_fontColor_value_element : ResourceColor = value_fontColor_value[i]
                let value_fontColor_value_element_type : int32 = RuntimeType.UNDEFINED
                value_fontColor_value_element_type = runtimeType(value_fontColor_value_element)
                if (TypeChecker.isColor(value_fontColor_value_element)) {
                    valueSerializer.writeInt8(0)
                    const value_fontColor_value_element_0  = value_fontColor_value_element as Color
                    valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_fontColor_value_element_0))
                }
                else if (RuntimeType.NUMBER == value_fontColor_value_element_type) {
                    valueSerializer.writeInt8(1)
                    const value_fontColor_value_element_1  = value_fontColor_value_element as number
                    valueSerializer.writeNumber(value_fontColor_value_element_1)
                }
                else if (RuntimeType.STRING == value_fontColor_value_element_type) {
                    valueSerializer.writeInt8(2)
                    const value_fontColor_value_element_2  = value_fontColor_value_element as string
                    valueSerializer.writeString(value_fontColor_value_element_2)
                }
                else if (RuntimeType.OBJECT == value_fontColor_value_element_type) {
                    valueSerializer.writeInt8(3)
                    const value_fontColor_value_element_3  = value_fontColor_value_element as Resource
                    Resource_serializer.write(valueSerializer, value_fontColor_value_element_3)
                }
            }
        }
        const value_fontWeight  = value.fontWeight
        let value_fontWeight_type : int32 = RuntimeType.UNDEFINED
        value_fontWeight_type = runtimeType(value_fontWeight)
        valueSerializer.writeInt8(value_fontWeight_type)
        if ((RuntimeType.UNDEFINED) != (value_fontWeight_type)) {
            const value_fontWeight_value  = value_fontWeight!
            let value_fontWeight_value_type : int32 = RuntimeType.UNDEFINED
            value_fontWeight_value_type = runtimeType(value_fontWeight_value)
            if (RuntimeType.NUMBER == value_fontWeight_value_type) {
                valueSerializer.writeInt8(0)
                const value_fontWeight_value_0  = value_fontWeight_value as number
                valueSerializer.writeNumber(value_fontWeight_value_0)
            }
            else if (TypeChecker.isFontWeight(value_fontWeight_value)) {
                valueSerializer.writeInt8(1)
                const value_fontWeight_value_1  = value_fontWeight_value as FontWeight
                valueSerializer.writeInt32(TypeChecker.FontWeight_ToNumeric(value_fontWeight_value_1))
            }
            else if (RuntimeType.STRING == value_fontWeight_value_type) {
                valueSerializer.writeInt8(2)
                const value_fontWeight_value_2  = value_fontWeight_value as string
                valueSerializer.writeString(value_fontWeight_value_2)
            }
        }
        const value_effectStrategy  = value.effectStrategy
        let value_effectStrategy_type : int32 = RuntimeType.UNDEFINED
        value_effectStrategy_type = runtimeType(value_effectStrategy)
        valueSerializer.writeInt8(value_effectStrategy_type)
        if ((RuntimeType.UNDEFINED) != (value_effectStrategy_type)) {
            const value_effectStrategy_value  = (value_effectStrategy as SymbolEffectStrategy)
            valueSerializer.writeInt32(TypeChecker.SymbolEffectStrategy_ToNumeric(value_effectStrategy_value))
        }
        const value_renderingStrategy  = value.renderingStrategy
        let value_renderingStrategy_type : int32 = RuntimeType.UNDEFINED
        value_renderingStrategy_type = runtimeType(value_renderingStrategy)
        valueSerializer.writeInt8(value_renderingStrategy_type)
        if ((RuntimeType.UNDEFINED) != (value_renderingStrategy_type)) {
            const value_renderingStrategy_value  = (value_renderingStrategy as SymbolRenderingStrategy)
            valueSerializer.writeInt32(TypeChecker.SymbolRenderingStrategy_ToNumeric(value_renderingStrategy_value))
        }
    }
    public static read(buffer: DeserializerBase): RichEditorSymbolSpanStyle {
        let valueDeserializer : DeserializerBase = buffer
        const fontSize_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let fontSize_buf : number | string | Resource | undefined
        if ((RuntimeType.UNDEFINED) != (fontSize_buf_runtimeType))
        {
            const fontSize_buf__selector : int32 = valueDeserializer.readInt8()
            let fontSize_buf_ : number | string | Resource | undefined
            if (fontSize_buf__selector == 0) {
                fontSize_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (fontSize_buf__selector == 1) {
                fontSize_buf_ = (valueDeserializer.readString() as string)
            }
            else if (fontSize_buf__selector == 2) {
                fontSize_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for fontSize_buf_ has to be chosen through deserialisation.")
            }
            fontSize_buf = (fontSize_buf_ as number | string | Resource)
        }
        const fontSize_result : number | string | Resource | undefined = fontSize_buf
        const fontColor_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let fontColor_buf : Array<ResourceColor> | undefined
        if ((RuntimeType.UNDEFINED) != (fontColor_buf_runtimeType))
        {
            const fontColor_buf__length : int32 = valueDeserializer.readInt32()
            let fontColor_buf_ : Array<ResourceColor> = new Array<ResourceColor>(fontColor_buf__length)
            for (let fontColor_buf__i = 0; fontColor_buf__i < fontColor_buf__length; fontColor_buf__i++) {
                const fontColor_buf__buf_selector : int32 = valueDeserializer.readInt8()
                let fontColor_buf__buf : Color | number | string | Resource | undefined
                if (fontColor_buf__buf_selector == 0) {
                    fontColor_buf__buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
                }
                else if (fontColor_buf__buf_selector == 1) {
                    fontColor_buf__buf = (valueDeserializer.readNumber() as number)
                }
                else if (fontColor_buf__buf_selector == 2) {
                    fontColor_buf__buf = (valueDeserializer.readString() as string)
                }
                else if (fontColor_buf__buf_selector == 3) {
                    fontColor_buf__buf = Resource_serializer.read(valueDeserializer)
                }
                else {
                    throw new Error("One of the branches for fontColor_buf__buf has to be chosen through deserialisation.")
                }
                fontColor_buf_[fontColor_buf__i] = (fontColor_buf__buf as Color | number | string | Resource)
            }
            fontColor_buf = fontColor_buf_
        }
        const fontColor_result : Array<ResourceColor> | undefined = fontColor_buf
        const fontWeight_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let fontWeight_buf : number | FontWeight | string | undefined
        if ((RuntimeType.UNDEFINED) != (fontWeight_buf_runtimeType))
        {
            const fontWeight_buf__selector : int32 = valueDeserializer.readInt8()
            let fontWeight_buf_ : number | FontWeight | string | undefined
            if (fontWeight_buf__selector == 0) {
                fontWeight_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (fontWeight_buf__selector == 1) {
                fontWeight_buf_ = TypeChecker.FontWeight_FromNumeric(valueDeserializer.readInt32())
            }
            else if (fontWeight_buf__selector == 2) {
                fontWeight_buf_ = (valueDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for fontWeight_buf_ has to be chosen through deserialisation.")
            }
            fontWeight_buf = (fontWeight_buf_ as number | FontWeight | string)
        }
        const fontWeight_result : number | FontWeight | string | undefined = fontWeight_buf
        const effectStrategy_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let effectStrategy_buf : SymbolEffectStrategy | undefined
        if ((RuntimeType.UNDEFINED) != (effectStrategy_buf_runtimeType))
        {
            effectStrategy_buf = TypeChecker.SymbolEffectStrategy_FromNumeric(valueDeserializer.readInt32())
        }
        const effectStrategy_result : SymbolEffectStrategy | undefined = effectStrategy_buf
        const renderingStrategy_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let renderingStrategy_buf : SymbolRenderingStrategy | undefined
        if ((RuntimeType.UNDEFINED) != (renderingStrategy_buf_runtimeType))
        {
            renderingStrategy_buf = TypeChecker.SymbolRenderingStrategy_FromNumeric(valueDeserializer.readInt32())
        }
        const renderingStrategy_result : SymbolRenderingStrategy | undefined = renderingStrategy_buf
        let value : RichEditorSymbolSpanStyle = ({fontSize: fontSize_result, fontColor: fontColor_result, fontWeight: fontWeight_result, effectStrategy: effectStrategy_result, renderingStrategy: renderingStrategy_result} as RichEditorSymbolSpanStyle)
        return value
    }
}
export class RichEditorUpdateSymbolSpanStyleOptions_serializer {
    public static write(buffer: SerializerBase, value: RichEditorUpdateSymbolSpanStyleOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_start  = value.start
        let value_start_type : int32 = RuntimeType.UNDEFINED
        value_start_type = runtimeType(value_start)
        valueSerializer.writeInt8(value_start_type)
        if ((RuntimeType.UNDEFINED) != (value_start_type)) {
            const value_start_value  = value_start!
            valueSerializer.writeNumber(value_start_value)
        }
        const value_end  = value.end
        let value_end_type : int32 = RuntimeType.UNDEFINED
        value_end_type = runtimeType(value_end)
        valueSerializer.writeInt8(value_end_type)
        if ((RuntimeType.UNDEFINED) != (value_end_type)) {
            const value_end_value  = value_end!
            valueSerializer.writeNumber(value_end_value)
        }
        const value_symbolStyle  = value.symbolStyle
        RichEditorSymbolSpanStyle_serializer.write(valueSerializer, value_symbolStyle)
    }
    public static read(buffer: DeserializerBase): RichEditorUpdateSymbolSpanStyleOptions {
        let valueDeserializer : DeserializerBase = buffer
        const start_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let start_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (start_buf_runtimeType))
        {
            start_buf = (valueDeserializer.readNumber() as number)
        }
        const start_result : number | undefined = start_buf
        const end_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let end_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (end_buf_runtimeType))
        {
            end_buf = (valueDeserializer.readNumber() as number)
        }
        const end_result : number | undefined = end_buf
        const symbolStyle_result : RichEditorSymbolSpanStyle = RichEditorSymbolSpanStyle_serializer.read(valueDeserializer)
        let value : RichEditorUpdateSymbolSpanStyleOptions = ({start: start_result, end: end_result, symbolStyle: symbolStyle_result} as RichEditorUpdateSymbolSpanStyleOptions)
        return value
    }
}
export class RichEditorUrlStyle_serializer {
    public static write(buffer: SerializerBase, value: RichEditorUrlStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_url  = value.url
        let value_url_type : int32 = RuntimeType.UNDEFINED
        value_url_type = runtimeType(value_url)
        valueSerializer.writeInt8(value_url_type)
        if ((RuntimeType.UNDEFINED) != (value_url_type)) {
            const value_url_value  = value_url!
            let value_url_value_type : int32 = RuntimeType.UNDEFINED
            value_url_value_type = runtimeType(value_url_value)
            if (RuntimeType.STRING == value_url_value_type) {
                valueSerializer.writeInt8(0)
                const value_url_value_0  = value_url_value as string
                valueSerializer.writeString(value_url_value_0)
            }
            else if (RuntimeType.OBJECT == value_url_value_type) {
                valueSerializer.writeInt8(1)
                const value_url_value_1  = value_url_value as Resource
                Resource_serializer.write(valueSerializer, value_url_value_1)
            }
        }
    }
    public static read(buffer: DeserializerBase): RichEditorUrlStyle {
        let valueDeserializer : DeserializerBase = buffer
        const url_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let url_buf : ResourceStr | undefined
        if ((RuntimeType.UNDEFINED) != (url_buf_runtimeType))
        {
            const url_buf__selector : int32 = valueDeserializer.readInt8()
            let url_buf_ : string | Resource | undefined
            if (url_buf__selector == 0) {
                url_buf_ = (valueDeserializer.readString() as string)
            }
            else if (url_buf__selector == 1) {
                url_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for url_buf_ has to be chosen through deserialisation.")
            }
            url_buf = (url_buf_ as string | Resource)
        }
        const url_result : ResourceStr | undefined = url_buf
        let value : RichEditorUrlStyle = ({url: url_result} as RichEditorUrlStyle)
        return value
    }
}
export class SelectionMenuOptions_serializer {
    public static write(buffer: SerializerBase, value: SelectionMenuOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_onAppear  = value.onAppear
        let value_onAppear_type : int32 = RuntimeType.UNDEFINED
        value_onAppear_type = runtimeType(value_onAppear)
        valueSerializer.writeInt8(value_onAppear_type)
        if ((RuntimeType.UNDEFINED) != (value_onAppear_type)) {
            const value_onAppear_value  = value_onAppear!
            valueSerializer.holdAndWriteCallback(value_onAppear_value)
        }
        const value_onDisappear  = value.onDisappear
        let value_onDisappear_type : int32 = RuntimeType.UNDEFINED
        value_onDisappear_type = runtimeType(value_onDisappear)
        valueSerializer.writeInt8(value_onDisappear_type)
        if ((RuntimeType.UNDEFINED) != (value_onDisappear_type)) {
            const value_onDisappear_value  = value_onDisappear!
            valueSerializer.holdAndWriteCallback(value_onDisappear_value)
        }
        const value_menuType  = value.menuType
        let value_menuType_type : int32 = RuntimeType.UNDEFINED
        value_menuType_type = runtimeType(value_menuType)
        valueSerializer.writeInt8(value_menuType_type)
        if ((RuntimeType.UNDEFINED) != (value_menuType_type)) {
            const value_menuType_value  = (value_menuType as MenuType)
            valueSerializer.writeInt32(TypeChecker.MenuType_ToNumeric(value_menuType_value))
        }
        const value_onMenuShow  = value.onMenuShow
        let value_onMenuShow_type : int32 = RuntimeType.UNDEFINED
        value_onMenuShow_type = runtimeType(value_onMenuShow)
        valueSerializer.writeInt8(value_onMenuShow_type)
        if ((RuntimeType.UNDEFINED) != (value_onMenuShow_type)) {
            const value_onMenuShow_value  = value_onMenuShow!
            valueSerializer.holdAndWriteCallback(value_onMenuShow_value)
        }
        const value_onMenuHide  = value.onMenuHide
        let value_onMenuHide_type : int32 = RuntimeType.UNDEFINED
        value_onMenuHide_type = runtimeType(value_onMenuHide)
        valueSerializer.writeInt8(value_onMenuHide_type)
        if ((RuntimeType.UNDEFINED) != (value_onMenuHide_type)) {
            const value_onMenuHide_value  = value_onMenuHide!
            valueSerializer.holdAndWriteCallback(value_onMenuHide_value)
        }
        const value_previewMenuOptions  = value.previewMenuOptions
        let value_previewMenuOptions_type : int32 = RuntimeType.UNDEFINED
        value_previewMenuOptions_type = runtimeType(value_previewMenuOptions)
        valueSerializer.writeInt8(value_previewMenuOptions_type)
        if ((RuntimeType.UNDEFINED) != (value_previewMenuOptions_type)) {
            const value_previewMenuOptions_value  = value_previewMenuOptions!
            PreviewMenuOptions_serializer.write(valueSerializer, value_previewMenuOptions_value)
        }
    }
    public static read(buffer: DeserializerBase): SelectionMenuOptions {
        let valueDeserializer : DeserializerBase = buffer
        const onAppear_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let onAppear_buf : MenuOnAppearCallback | undefined
        if ((RuntimeType.UNDEFINED) != (onAppear_buf_runtimeType))
        {
            const onAppear_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onAppear_buf__call : KPointer = valueDeserializer.readPointer()
            const onAppear_buf__callSync : KPointer = valueDeserializer.readPointer()
            onAppear_buf = (start: number, end: number):void => { 
    const onAppear_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onAppear_buf__argsSerializer.writeInt32(onAppear_buf__resource.resourceId);
    onAppear_buf__argsSerializer.writePointer(onAppear_buf__call);
    onAppear_buf__argsSerializer.writePointer(onAppear_buf__callSync);
    onAppear_buf__argsSerializer.writeNumber(start);
    onAppear_buf__argsSerializer.writeNumber(end);
    InteropNativeModule._CallCallback(-614475458, onAppear_buf__argsSerializer.asBuffer(), onAppear_buf__argsSerializer.length());
    onAppear_buf__argsSerializer.release();
    return; }
        }
        const onAppear_result : MenuOnAppearCallback | undefined = onAppear_buf
        const onDisappear_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let onDisappear_buf : VoidCallback | undefined
        if ((RuntimeType.UNDEFINED) != (onDisappear_buf_runtimeType))
        {
            const onDisappear_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDisappear_buf__call : KPointer = valueDeserializer.readPointer()
            const onDisappear_buf__callSync : KPointer = valueDeserializer.readPointer()
            onDisappear_buf = ():void => { 
    const onDisappear_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onDisappear_buf__argsSerializer.writeInt32(onDisappear_buf__resource.resourceId);
    onDisappear_buf__argsSerializer.writePointer(onDisappear_buf__call);
    onDisappear_buf__argsSerializer.writePointer(onDisappear_buf__callSync);
    InteropNativeModule._CallCallback(-2038961969, onDisappear_buf__argsSerializer.asBuffer(), onDisappear_buf__argsSerializer.length());
    onDisappear_buf__argsSerializer.release();
    return; }
        }
        const onDisappear_result : VoidCallback | undefined = onDisappear_buf
        const menuType_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let menuType_buf : MenuType | undefined
        if ((RuntimeType.UNDEFINED) != (menuType_buf_runtimeType))
        {
            menuType_buf = TypeChecker.MenuType_FromNumeric(valueDeserializer.readInt32())
        }
        const menuType_result : MenuType | undefined = menuType_buf
        const onMenuShow_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let onMenuShow_buf : MenuCallback | undefined
        if ((RuntimeType.UNDEFINED) != (onMenuShow_buf_runtimeType))
        {
            const onMenuShow_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onMenuShow_buf__call : KPointer = valueDeserializer.readPointer()
            const onMenuShow_buf__callSync : KPointer = valueDeserializer.readPointer()
            onMenuShow_buf = (start: number, end: number):void => { 
    const onMenuShow_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onMenuShow_buf__argsSerializer.writeInt32(onMenuShow_buf__resource.resourceId);
    onMenuShow_buf__argsSerializer.writePointer(onMenuShow_buf__call);
    onMenuShow_buf__argsSerializer.writePointer(onMenuShow_buf__callSync);
    onMenuShow_buf__argsSerializer.writeNumber(start);
    onMenuShow_buf__argsSerializer.writeNumber(end);
    InteropNativeModule._CallCallback(810927048, onMenuShow_buf__argsSerializer.asBuffer(), onMenuShow_buf__argsSerializer.length());
    onMenuShow_buf__argsSerializer.release();
    return; }
        }
        const onMenuShow_result : MenuCallback | undefined = onMenuShow_buf
        const onMenuHide_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let onMenuHide_buf : MenuCallback | undefined
        if ((RuntimeType.UNDEFINED) != (onMenuHide_buf_runtimeType))
        {
            const onMenuHide_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onMenuHide_buf__call : KPointer = valueDeserializer.readPointer()
            const onMenuHide_buf__callSync : KPointer = valueDeserializer.readPointer()
            onMenuHide_buf = (start: number, end: number):void => { 
    const onMenuHide_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onMenuHide_buf__argsSerializer.writeInt32(onMenuHide_buf__resource.resourceId);
    onMenuHide_buf__argsSerializer.writePointer(onMenuHide_buf__call);
    onMenuHide_buf__argsSerializer.writePointer(onMenuHide_buf__callSync);
    onMenuHide_buf__argsSerializer.writeNumber(start);
    onMenuHide_buf__argsSerializer.writeNumber(end);
    InteropNativeModule._CallCallback(810927048, onMenuHide_buf__argsSerializer.asBuffer(), onMenuHide_buf__argsSerializer.length());
    onMenuHide_buf__argsSerializer.release();
    return; }
        }
        const onMenuHide_result : MenuCallback | undefined = onMenuHide_buf
        const previewMenuOptions_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let previewMenuOptions_buf : PreviewMenuOptions | undefined
        if ((RuntimeType.UNDEFINED) != (previewMenuOptions_buf_runtimeType))
        {
            previewMenuOptions_buf = PreviewMenuOptions_serializer.read(valueDeserializer)
        }
        const previewMenuOptions_result : PreviewMenuOptions | undefined = previewMenuOptions_buf
        let value : SelectionMenuOptions = ({onAppear: onAppear_result, onDisappear: onDisappear_result, menuType: menuType_result, onMenuShow: onMenuShow_result, onMenuHide: onMenuHide_result, previewMenuOptions: previewMenuOptions_result} as SelectionMenuOptions)
        return value
    }
}
export class LeadingMarginPlaceholder_serializer {
    public static write(buffer: SerializerBase, value: LeadingMarginPlaceholder): void {
        let valueSerializer : SerializerBase = buffer
        const value_pixelMap  = value.pixelMap
        image_PixelMap_serializer.write(valueSerializer, value_pixelMap)
        const value_size  = value.size
        const value_size_0  = value_size[0]
        let value_size_0_type : int32 = RuntimeType.UNDEFINED
        value_size_0_type = runtimeType(value_size_0)
        if (RuntimeType.STRING == value_size_0_type) {
            valueSerializer.writeInt8(0)
            const value_size_0_0  = value_size_0 as string
            valueSerializer.writeString(value_size_0_0)
        }
        else if (RuntimeType.NUMBER == value_size_0_type) {
            valueSerializer.writeInt8(1)
            const value_size_0_1  = value_size_0 as number
            valueSerializer.writeNumber(value_size_0_1)
        }
        else if (RuntimeType.OBJECT == value_size_0_type) {
            valueSerializer.writeInt8(2)
            const value_size_0_2  = value_size_0 as Resource
            Resource_serializer.write(valueSerializer, value_size_0_2)
        }
        const value_size_1  = value_size[1]
        let value_size_1_type : int32 = RuntimeType.UNDEFINED
        value_size_1_type = runtimeType(value_size_1)
        if (RuntimeType.STRING == value_size_1_type) {
            valueSerializer.writeInt8(0)
            const value_size_1_0  = value_size_1 as string
            valueSerializer.writeString(value_size_1_0)
        }
        else if (RuntimeType.NUMBER == value_size_1_type) {
            valueSerializer.writeInt8(1)
            const value_size_1_1  = value_size_1 as number
            valueSerializer.writeNumber(value_size_1_1)
        }
        else if (RuntimeType.OBJECT == value_size_1_type) {
            valueSerializer.writeInt8(2)
            const value_size_1_2  = value_size_1 as Resource
            Resource_serializer.write(valueSerializer, value_size_1_2)
        }
    }
    public static read(buffer: DeserializerBase): LeadingMarginPlaceholder {
        let valueDeserializer : DeserializerBase = buffer
        const pixelMap_result : image.PixelMap = (image_PixelMap_serializer.read(valueDeserializer) as image.PixelMap)
        const size_buf_value0_buf_selector : int32 = valueDeserializer.readInt8()
        let size_buf_value0_buf : string | number | Resource | undefined
        if (size_buf_value0_buf_selector == 0) {
            size_buf_value0_buf = (valueDeserializer.readString() as string)
        }
        else if (size_buf_value0_buf_selector == 1) {
            size_buf_value0_buf = (valueDeserializer.readNumber() as number)
        }
        else if (size_buf_value0_buf_selector == 2) {
            size_buf_value0_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for size_buf_value0_buf has to be chosen through deserialisation.")
        }
        const size_buf_value0 : Dimension = (size_buf_value0_buf as string | number | Resource)
        const size_buf_value1_buf_selector : int32 = valueDeserializer.readInt8()
        let size_buf_value1_buf : string | number | Resource | undefined
        if (size_buf_value1_buf_selector == 0) {
            size_buf_value1_buf = (valueDeserializer.readString() as string)
        }
        else if (size_buf_value1_buf_selector == 1) {
            size_buf_value1_buf = (valueDeserializer.readNumber() as number)
        }
        else if (size_buf_value1_buf_selector == 2) {
            size_buf_value1_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for size_buf_value1_buf has to be chosen through deserialisation.")
        }
        const size_buf_value1 : Dimension = (size_buf_value1_buf as string | number | Resource)
        const size_result : [ Dimension, Dimension ] = ([size_buf_value0, size_buf_value1] as [ Dimension, Dimension ])
        let value : LeadingMarginPlaceholder = ({pixelMap: pixelMap_result, size: size_result} as LeadingMarginPlaceholder)
        return value
    }
}
export class RichEditorSymbolSpanOptions_serializer {
    public static write(buffer: SerializerBase, value: RichEditorSymbolSpanOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_offset  = value.offset
        let value_offset_type : int32 = RuntimeType.UNDEFINED
        value_offset_type = runtimeType(value_offset)
        valueSerializer.writeInt8(value_offset_type)
        if ((RuntimeType.UNDEFINED) != (value_offset_type)) {
            const value_offset_value  = value_offset!
            valueSerializer.writeNumber(value_offset_value)
        }
        const value_style  = value.style
        let value_style_type : int32 = RuntimeType.UNDEFINED
        value_style_type = runtimeType(value_style)
        valueSerializer.writeInt8(value_style_type)
        if ((RuntimeType.UNDEFINED) != (value_style_type)) {
            const value_style_value  = value_style!
            RichEditorSymbolSpanStyle_serializer.write(valueSerializer, value_style_value)
        }
    }
    public static read(buffer: DeserializerBase): RichEditorSymbolSpanOptions {
        let valueDeserializer : DeserializerBase = buffer
        const offset_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let offset_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (offset_buf_runtimeType))
        {
            offset_buf = (valueDeserializer.readNumber() as number)
        }
        const offset_result : number | undefined = offset_buf
        const style_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let style_buf : RichEditorSymbolSpanStyle | undefined
        if ((RuntimeType.UNDEFINED) != (style_buf_runtimeType))
        {
            style_buf = RichEditorSymbolSpanStyle_serializer.read(valueDeserializer)
        }
        const style_result : RichEditorSymbolSpanStyle | undefined = style_buf
        let value : RichEditorSymbolSpanOptions = ({offset: offset_result, style: style_result} as RichEditorSymbolSpanOptions)
        return value
    }
}
export class PlaceholderStyle_serializer {
    public static write(buffer: SerializerBase, value: PlaceholderStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_font  = value.font
        let value_font_type : int32 = RuntimeType.UNDEFINED
        value_font_type = runtimeType(value_font)
        valueSerializer.writeInt8(value_font_type)
        if ((RuntimeType.UNDEFINED) != (value_font_type)) {
            const value_font_value  = value_font!
            Font_serializer.write(valueSerializer, value_font_value)
        }
        const value_fontColor  = value.fontColor
        let value_fontColor_type : int32 = RuntimeType.UNDEFINED
        value_fontColor_type = runtimeType(value_fontColor)
        valueSerializer.writeInt8(value_fontColor_type)
        if ((RuntimeType.UNDEFINED) != (value_fontColor_type)) {
            const value_fontColor_value  = value_fontColor!
            let value_fontColor_value_type : int32 = RuntimeType.UNDEFINED
            value_fontColor_value_type = runtimeType(value_fontColor_value)
            if (TypeChecker.isColor(value_fontColor_value)) {
                valueSerializer.writeInt8(0)
                const value_fontColor_value_0  = value_fontColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_fontColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_fontColor_value_type) {
                valueSerializer.writeInt8(1)
                const value_fontColor_value_1  = value_fontColor_value as number
                valueSerializer.writeNumber(value_fontColor_value_1)
            }
            else if (RuntimeType.STRING == value_fontColor_value_type) {
                valueSerializer.writeInt8(2)
                const value_fontColor_value_2  = value_fontColor_value as string
                valueSerializer.writeString(value_fontColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_fontColor_value_type) {
                valueSerializer.writeInt8(3)
                const value_fontColor_value_3  = value_fontColor_value as Resource
                Resource_serializer.write(valueSerializer, value_fontColor_value_3)
            }
        }
    }
    public static read(buffer: DeserializerBase): PlaceholderStyle {
        let valueDeserializer : DeserializerBase = buffer
        const font_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let font_buf : Font | undefined
        if ((RuntimeType.UNDEFINED) != (font_buf_runtimeType))
        {
            font_buf = Font_serializer.read(valueDeserializer)
        }
        const font_result : Font | undefined = font_buf
        const fontColor_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let fontColor_buf : ResourceColor | undefined
        if ((RuntimeType.UNDEFINED) != (fontColor_buf_runtimeType))
        {
            const fontColor_buf__selector : int32 = valueDeserializer.readInt8()
            let fontColor_buf_ : Color | number | string | Resource | undefined
            if (fontColor_buf__selector == 0) {
                fontColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (fontColor_buf__selector == 1) {
                fontColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (fontColor_buf__selector == 2) {
                fontColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (fontColor_buf__selector == 3) {
                fontColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for fontColor_buf_ has to be chosen through deserialisation.")
            }
            fontColor_buf = (fontColor_buf_ as Color | number | string | Resource)
        }
        const fontColor_result : ResourceColor | undefined = fontColor_buf
        let value : PlaceholderStyle = ({font: font_result, fontColor: fontColor_result} as PlaceholderStyle)
        return value
    }
}
export class RichEditorLayoutStyle_serializer {
    public static write(buffer: SerializerBase, value: RichEditorLayoutStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_margin  = value.margin
        let value_margin_type : int32 = RuntimeType.UNDEFINED
        value_margin_type = runtimeType(value_margin)
        valueSerializer.writeInt8(value_margin_type)
        if ((RuntimeType.UNDEFINED) != (value_margin_type)) {
            const value_margin_value  = value_margin!
            let value_margin_value_type : int32 = RuntimeType.UNDEFINED
            value_margin_value_type = runtimeType(value_margin_value)
            if ((RuntimeType.STRING == value_margin_value_type) || (RuntimeType.NUMBER == value_margin_value_type) || (RuntimeType.OBJECT == value_margin_value_type)) {
                valueSerializer.writeInt8(0)
                const value_margin_value_0  = value_margin_value as Dimension
                let value_margin_value_0_type : int32 = RuntimeType.UNDEFINED
                value_margin_value_0_type = runtimeType(value_margin_value_0)
                if (RuntimeType.STRING == value_margin_value_0_type) {
                    valueSerializer.writeInt8(0)
                    const value_margin_value_0_0  = value_margin_value_0 as string
                    valueSerializer.writeString(value_margin_value_0_0)
                }
                else if (RuntimeType.NUMBER == value_margin_value_0_type) {
                    valueSerializer.writeInt8(1)
                    const value_margin_value_0_1  = value_margin_value_0 as number
                    valueSerializer.writeNumber(value_margin_value_0_1)
                }
                else if (RuntimeType.OBJECT == value_margin_value_0_type) {
                    valueSerializer.writeInt8(2)
                    const value_margin_value_0_2  = value_margin_value_0 as Resource
                    Resource_serializer.write(valueSerializer, value_margin_value_0_2)
                }
            }
            else if (TypeChecker.isPadding(value_margin_value, false, false, false, false)) {
                valueSerializer.writeInt8(1)
                const value_margin_value_1  = value_margin_value as Padding
                Padding_serializer.write(valueSerializer, value_margin_value_1)
            }
        }
        const value_borderRadius  = value.borderRadius
        let value_borderRadius_type : int32 = RuntimeType.UNDEFINED
        value_borderRadius_type = runtimeType(value_borderRadius)
        valueSerializer.writeInt8(value_borderRadius_type)
        if ((RuntimeType.UNDEFINED) != (value_borderRadius_type)) {
            const value_borderRadius_value  = value_borderRadius!
            let value_borderRadius_value_type : int32 = RuntimeType.UNDEFINED
            value_borderRadius_value_type = runtimeType(value_borderRadius_value)
            if ((RuntimeType.STRING == value_borderRadius_value_type) || (RuntimeType.NUMBER == value_borderRadius_value_type) || (RuntimeType.OBJECT == value_borderRadius_value_type)) {
                valueSerializer.writeInt8(0)
                const value_borderRadius_value_0  = value_borderRadius_value as Dimension
                let value_borderRadius_value_0_type : int32 = RuntimeType.UNDEFINED
                value_borderRadius_value_0_type = runtimeType(value_borderRadius_value_0)
                if (RuntimeType.STRING == value_borderRadius_value_0_type) {
                    valueSerializer.writeInt8(0)
                    const value_borderRadius_value_0_0  = value_borderRadius_value_0 as string
                    valueSerializer.writeString(value_borderRadius_value_0_0)
                }
                else if (RuntimeType.NUMBER == value_borderRadius_value_0_type) {
                    valueSerializer.writeInt8(1)
                    const value_borderRadius_value_0_1  = value_borderRadius_value_0 as number
                    valueSerializer.writeNumber(value_borderRadius_value_0_1)
                }
                else if (RuntimeType.OBJECT == value_borderRadius_value_0_type) {
                    valueSerializer.writeInt8(2)
                    const value_borderRadius_value_0_2  = value_borderRadius_value_0 as Resource
                    Resource_serializer.write(valueSerializer, value_borderRadius_value_0_2)
                }
            }
            else if (TypeChecker.isBorderRadiuses(value_borderRadius_value, false, false, false, false)) {
                valueSerializer.writeInt8(1)
                const value_borderRadius_value_1  = value_borderRadius_value as BorderRadiuses
                BorderRadiuses_serializer.write(valueSerializer, value_borderRadius_value_1)
            }
        }
    }
    public static read(buffer: DeserializerBase): RichEditorLayoutStyle {
        let valueDeserializer : DeserializerBase = buffer
        const margin_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let margin_buf : Dimension | Padding | undefined
        if ((RuntimeType.UNDEFINED) != (margin_buf_runtimeType))
        {
            const margin_buf__selector : int32 = valueDeserializer.readInt8()
            let margin_buf_ : Dimension | Padding | undefined
            if (margin_buf__selector == 0) {
                const margin_buf__u_selector : int32 = valueDeserializer.readInt8()
                let margin_buf__u : string | number | Resource | undefined
                if (margin_buf__u_selector == 0) {
                    margin_buf__u = (valueDeserializer.readString() as string)
                }
                else if (margin_buf__u_selector == 1) {
                    margin_buf__u = (valueDeserializer.readNumber() as number)
                }
                else if (margin_buf__u_selector == 2) {
                    margin_buf__u = Resource_serializer.read(valueDeserializer)
                }
                else {
                    throw new Error("One of the branches for margin_buf__u has to be chosen through deserialisation.")
                }
                margin_buf_ = (margin_buf__u as string | number | Resource)
            }
            else if (margin_buf__selector == 1) {
                margin_buf_ = Padding_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for margin_buf_ has to be chosen through deserialisation.")
            }
            margin_buf = (margin_buf_ as Dimension | Padding)
        }
        const margin_result : Dimension | Padding | undefined = margin_buf
        const borderRadius_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let borderRadius_buf : Dimension | BorderRadiuses | undefined
        if ((RuntimeType.UNDEFINED) != (borderRadius_buf_runtimeType))
        {
            const borderRadius_buf__selector : int32 = valueDeserializer.readInt8()
            let borderRadius_buf_ : Dimension | BorderRadiuses | undefined
            if (borderRadius_buf__selector == 0) {
                const borderRadius_buf__u_selector : int32 = valueDeserializer.readInt8()
                let borderRadius_buf__u : string | number | Resource | undefined
                if (borderRadius_buf__u_selector == 0) {
                    borderRadius_buf__u = (valueDeserializer.readString() as string)
                }
                else if (borderRadius_buf__u_selector == 1) {
                    borderRadius_buf__u = (valueDeserializer.readNumber() as number)
                }
                else if (borderRadius_buf__u_selector == 2) {
                    borderRadius_buf__u = Resource_serializer.read(valueDeserializer)
                }
                else {
                    throw new Error("One of the branches for borderRadius_buf__u has to be chosen through deserialisation.")
                }
                borderRadius_buf_ = (borderRadius_buf__u as string | number | Resource)
            }
            else if (borderRadius_buf__selector == 1) {
                borderRadius_buf_ = BorderRadiuses_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for borderRadius_buf_ has to be chosen through deserialisation.")
            }
            borderRadius_buf = (borderRadius_buf_ as Dimension | BorderRadiuses)
        }
        const borderRadius_result : Dimension | BorderRadiuses | undefined = borderRadius_buf
        let value : RichEditorLayoutStyle = ({margin: margin_result, borderRadius: borderRadius_result} as RichEditorLayoutStyle)
        return value
    }
}
export class RichEditorParagraphStyle_serializer {
    public static write(buffer: SerializerBase, value: RichEditorParagraphStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_textAlign  = value.textAlign
        let value_textAlign_type : int32 = RuntimeType.UNDEFINED
        value_textAlign_type = runtimeType(value_textAlign)
        valueSerializer.writeInt8(value_textAlign_type)
        if ((RuntimeType.UNDEFINED) != (value_textAlign_type)) {
            const value_textAlign_value  = (value_textAlign as TextAlign)
            valueSerializer.writeInt32(TypeChecker.TextAlign_ToNumeric(value_textAlign_value))
        }
        const value_leadingMargin  = value.leadingMargin
        let value_leadingMargin_type : int32 = RuntimeType.UNDEFINED
        value_leadingMargin_type = runtimeType(value_leadingMargin)
        valueSerializer.writeInt8(value_leadingMargin_type)
        if ((RuntimeType.UNDEFINED) != (value_leadingMargin_type)) {
            const value_leadingMargin_value  = value_leadingMargin!
            let value_leadingMargin_value_type : int32 = RuntimeType.UNDEFINED
            value_leadingMargin_value_type = runtimeType(value_leadingMargin_value)
            if ((RuntimeType.STRING == value_leadingMargin_value_type) || (RuntimeType.NUMBER == value_leadingMargin_value_type) || (RuntimeType.OBJECT == value_leadingMargin_value_type)) {
                valueSerializer.writeInt8(0)
                const value_leadingMargin_value_0  = value_leadingMargin_value as Dimension
                let value_leadingMargin_value_0_type : int32 = RuntimeType.UNDEFINED
                value_leadingMargin_value_0_type = runtimeType(value_leadingMargin_value_0)
                if (RuntimeType.STRING == value_leadingMargin_value_0_type) {
                    valueSerializer.writeInt8(0)
                    const value_leadingMargin_value_0_0  = value_leadingMargin_value_0 as string
                    valueSerializer.writeString(value_leadingMargin_value_0_0)
                }
                else if (RuntimeType.NUMBER == value_leadingMargin_value_0_type) {
                    valueSerializer.writeInt8(1)
                    const value_leadingMargin_value_0_1  = value_leadingMargin_value_0 as number
                    valueSerializer.writeNumber(value_leadingMargin_value_0_1)
                }
                else if (RuntimeType.OBJECT == value_leadingMargin_value_0_type) {
                    valueSerializer.writeInt8(2)
                    const value_leadingMargin_value_0_2  = value_leadingMargin_value_0 as Resource
                    Resource_serializer.write(valueSerializer, value_leadingMargin_value_0_2)
                }
            }
            else if (TypeChecker.isLeadingMarginPlaceholder(value_leadingMargin_value, false, false)) {
                valueSerializer.writeInt8(1)
                const value_leadingMargin_value_1  = value_leadingMargin_value as LeadingMarginPlaceholder
                LeadingMarginPlaceholder_serializer.write(valueSerializer, value_leadingMargin_value_1)
            }
        }
        const value_wordBreak  = value.wordBreak
        let value_wordBreak_type : int32 = RuntimeType.UNDEFINED
        value_wordBreak_type = runtimeType(value_wordBreak)
        valueSerializer.writeInt8(value_wordBreak_type)
        if ((RuntimeType.UNDEFINED) != (value_wordBreak_type)) {
            const value_wordBreak_value  = (value_wordBreak as WordBreak)
            valueSerializer.writeInt32(TypeChecker.WordBreak_ToNumeric(value_wordBreak_value))
        }
        const value_lineBreakStrategy  = value.lineBreakStrategy
        let value_lineBreakStrategy_type : int32 = RuntimeType.UNDEFINED
        value_lineBreakStrategy_type = runtimeType(value_lineBreakStrategy)
        valueSerializer.writeInt8(value_lineBreakStrategy_type)
        if ((RuntimeType.UNDEFINED) != (value_lineBreakStrategy_type)) {
            const value_lineBreakStrategy_value  = (value_lineBreakStrategy as LineBreakStrategy)
            valueSerializer.writeInt32(TypeChecker.LineBreakStrategy_ToNumeric(value_lineBreakStrategy_value))
        }
        const value_paragraphSpacing  = value.paragraphSpacing
        let value_paragraphSpacing_type : int32 = RuntimeType.UNDEFINED
        value_paragraphSpacing_type = runtimeType(value_paragraphSpacing)
        valueSerializer.writeInt8(value_paragraphSpacing_type)
        if ((RuntimeType.UNDEFINED) != (value_paragraphSpacing_type)) {
            const value_paragraphSpacing_value  = value_paragraphSpacing!
            valueSerializer.writeNumber(value_paragraphSpacing_value)
        }
    }
    public static read(buffer: DeserializerBase): RichEditorParagraphStyle {
        let valueDeserializer : DeserializerBase = buffer
        const textAlign_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let textAlign_buf : TextAlign | undefined
        if ((RuntimeType.UNDEFINED) != (textAlign_buf_runtimeType))
        {
            textAlign_buf = TypeChecker.TextAlign_FromNumeric(valueDeserializer.readInt32())
        }
        const textAlign_result : TextAlign | undefined = textAlign_buf
        const leadingMargin_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let leadingMargin_buf : Dimension | LeadingMarginPlaceholder | undefined
        if ((RuntimeType.UNDEFINED) != (leadingMargin_buf_runtimeType))
        {
            const leadingMargin_buf__selector : int32 = valueDeserializer.readInt8()
            let leadingMargin_buf_ : Dimension | LeadingMarginPlaceholder | undefined
            if (leadingMargin_buf__selector == 0) {
                const leadingMargin_buf__u_selector : int32 = valueDeserializer.readInt8()
                let leadingMargin_buf__u : string | number | Resource | undefined
                if (leadingMargin_buf__u_selector == 0) {
                    leadingMargin_buf__u = (valueDeserializer.readString() as string)
                }
                else if (leadingMargin_buf__u_selector == 1) {
                    leadingMargin_buf__u = (valueDeserializer.readNumber() as number)
                }
                else if (leadingMargin_buf__u_selector == 2) {
                    leadingMargin_buf__u = Resource_serializer.read(valueDeserializer)
                }
                else {
                    throw new Error("One of the branches for leadingMargin_buf__u has to be chosen through deserialisation.")
                }
                leadingMargin_buf_ = (leadingMargin_buf__u as string | number | Resource)
            }
            else if (leadingMargin_buf__selector == 1) {
                leadingMargin_buf_ = LeadingMarginPlaceholder_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for leadingMargin_buf_ has to be chosen through deserialisation.")
            }
            leadingMargin_buf = (leadingMargin_buf_ as Dimension | LeadingMarginPlaceholder)
        }
        const leadingMargin_result : Dimension | LeadingMarginPlaceholder | undefined = leadingMargin_buf
        const wordBreak_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let wordBreak_buf : WordBreak | undefined
        if ((RuntimeType.UNDEFINED) != (wordBreak_buf_runtimeType))
        {
            wordBreak_buf = TypeChecker.WordBreak_FromNumeric(valueDeserializer.readInt32())
        }
        const wordBreak_result : WordBreak | undefined = wordBreak_buf
        const lineBreakStrategy_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let lineBreakStrategy_buf : LineBreakStrategy | undefined
        if ((RuntimeType.UNDEFINED) != (lineBreakStrategy_buf_runtimeType))
        {
            lineBreakStrategy_buf = TypeChecker.LineBreakStrategy_FromNumeric(valueDeserializer.readInt32())
        }
        const lineBreakStrategy_result : LineBreakStrategy | undefined = lineBreakStrategy_buf
        const paragraphSpacing_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let paragraphSpacing_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (paragraphSpacing_buf_runtimeType))
        {
            paragraphSpacing_buf = (valueDeserializer.readNumber() as number)
        }
        const paragraphSpacing_result : number | undefined = paragraphSpacing_buf
        let value : RichEditorParagraphStyle = ({textAlign: textAlign_result, leadingMargin: leadingMargin_result, wordBreak: wordBreak_result, lineBreakStrategy: lineBreakStrategy_result, paragraphSpacing: paragraphSpacing_result} as RichEditorParagraphStyle)
        return value
    }
}
export class RichEditorParagraphStyleOptions_serializer {
    public static write(buffer: SerializerBase, value: RichEditorParagraphStyleOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_start  = value.start
        let value_start_type : int32 = RuntimeType.UNDEFINED
        value_start_type = runtimeType(value_start)
        valueSerializer.writeInt8(value_start_type)
        if ((RuntimeType.UNDEFINED) != (value_start_type)) {
            const value_start_value  = value_start!
            valueSerializer.writeNumber(value_start_value)
        }
        const value_end  = value.end
        let value_end_type : int32 = RuntimeType.UNDEFINED
        value_end_type = runtimeType(value_end)
        valueSerializer.writeInt8(value_end_type)
        if ((RuntimeType.UNDEFINED) != (value_end_type)) {
            const value_end_value  = value_end!
            valueSerializer.writeNumber(value_end_value)
        }
        const value_style  = value.style
        RichEditorParagraphStyle_serializer.write(valueSerializer, value_style)
    }
    public static read(buffer: DeserializerBase): RichEditorParagraphStyleOptions {
        let valueDeserializer : DeserializerBase = buffer
        const start_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let start_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (start_buf_runtimeType))
        {
            start_buf = (valueDeserializer.readNumber() as number)
        }
        const start_result : number | undefined = start_buf
        const end_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let end_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (end_buf_runtimeType))
        {
            end_buf = (valueDeserializer.readNumber() as number)
        }
        const end_result : number | undefined = end_buf
        const style_result : RichEditorParagraphStyle = RichEditorParagraphStyle_serializer.read(valueDeserializer)
        let value : RichEditorParagraphStyleOptions = ({start: start_result, end: end_result, style: style_result} as RichEditorParagraphStyleOptions)
        return value
    }
}
export class RichEditorImageSpanStyle_serializer {
    public static write(buffer: SerializerBase, value: RichEditorImageSpanStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_size  = value.size
        let value_size_type : int32 = RuntimeType.UNDEFINED
        value_size_type = runtimeType(value_size)
        valueSerializer.writeInt8(value_size_type)
        if ((RuntimeType.UNDEFINED) != (value_size_type)) {
            const value_size_value  = value_size!
            const value_size_value_0  = value_size_value[0]
            let value_size_value_0_type : int32 = RuntimeType.UNDEFINED
            value_size_value_0_type = runtimeType(value_size_value_0)
            if (RuntimeType.STRING == value_size_value_0_type) {
                valueSerializer.writeInt8(0)
                const value_size_value_0_0  = value_size_value_0 as string
                valueSerializer.writeString(value_size_value_0_0)
            }
            else if (RuntimeType.NUMBER == value_size_value_0_type) {
                valueSerializer.writeInt8(1)
                const value_size_value_0_1  = value_size_value_0 as number
                valueSerializer.writeNumber(value_size_value_0_1)
            }
            else if (RuntimeType.OBJECT == value_size_value_0_type) {
                valueSerializer.writeInt8(2)
                const value_size_value_0_2  = value_size_value_0 as Resource
                Resource_serializer.write(valueSerializer, value_size_value_0_2)
            }
            const value_size_value_1  = value_size_value[1]
            let value_size_value_1_type : int32 = RuntimeType.UNDEFINED
            value_size_value_1_type = runtimeType(value_size_value_1)
            if (RuntimeType.STRING == value_size_value_1_type) {
                valueSerializer.writeInt8(0)
                const value_size_value_1_0  = value_size_value_1 as string
                valueSerializer.writeString(value_size_value_1_0)
            }
            else if (RuntimeType.NUMBER == value_size_value_1_type) {
                valueSerializer.writeInt8(1)
                const value_size_value_1_1  = value_size_value_1 as number
                valueSerializer.writeNumber(value_size_value_1_1)
            }
            else if (RuntimeType.OBJECT == value_size_value_1_type) {
                valueSerializer.writeInt8(2)
                const value_size_value_1_2  = value_size_value_1 as Resource
                Resource_serializer.write(valueSerializer, value_size_value_1_2)
            }
        }
        const value_verticalAlign  = value.verticalAlign
        let value_verticalAlign_type : int32 = RuntimeType.UNDEFINED
        value_verticalAlign_type = runtimeType(value_verticalAlign)
        valueSerializer.writeInt8(value_verticalAlign_type)
        if ((RuntimeType.UNDEFINED) != (value_verticalAlign_type)) {
            const value_verticalAlign_value  = (value_verticalAlign as ImageSpanAlignment)
            valueSerializer.writeInt32(TypeChecker.ImageSpanAlignment_ToNumeric(value_verticalAlign_value))
        }
        const value_objectFit  = value.objectFit
        let value_objectFit_type : int32 = RuntimeType.UNDEFINED
        value_objectFit_type = runtimeType(value_objectFit)
        valueSerializer.writeInt8(value_objectFit_type)
        if ((RuntimeType.UNDEFINED) != (value_objectFit_type)) {
            const value_objectFit_value  = (value_objectFit as ImageFit)
            valueSerializer.writeInt32(TypeChecker.ImageFit_ToNumeric(value_objectFit_value))
        }
        const value_layoutStyle  = value.layoutStyle
        let value_layoutStyle_type : int32 = RuntimeType.UNDEFINED
        value_layoutStyle_type = runtimeType(value_layoutStyle)
        valueSerializer.writeInt8(value_layoutStyle_type)
        if ((RuntimeType.UNDEFINED) != (value_layoutStyle_type)) {
            const value_layoutStyle_value  = value_layoutStyle!
            RichEditorLayoutStyle_serializer.write(valueSerializer, value_layoutStyle_value)
        }
    }
    public static read(buffer: DeserializerBase): RichEditorImageSpanStyle {
        let valueDeserializer : DeserializerBase = buffer
        const size_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let size_buf : [ Dimension, Dimension ] | undefined
        if ((RuntimeType.UNDEFINED) != (size_buf_runtimeType))
        {
            const size_buf__value0_buf_selector : int32 = valueDeserializer.readInt8()
            let size_buf__value0_buf : string | number | Resource | undefined
            if (size_buf__value0_buf_selector == 0) {
                size_buf__value0_buf = (valueDeserializer.readString() as string)
            }
            else if (size_buf__value0_buf_selector == 1) {
                size_buf__value0_buf = (valueDeserializer.readNumber() as number)
            }
            else if (size_buf__value0_buf_selector == 2) {
                size_buf__value0_buf = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for size_buf__value0_buf has to be chosen through deserialisation.")
            }
            const size_buf__value0 : Dimension = (size_buf__value0_buf as string | number | Resource)
            const size_buf__value1_buf_selector : int32 = valueDeserializer.readInt8()
            let size_buf__value1_buf : string | number | Resource | undefined
            if (size_buf__value1_buf_selector == 0) {
                size_buf__value1_buf = (valueDeserializer.readString() as string)
            }
            else if (size_buf__value1_buf_selector == 1) {
                size_buf__value1_buf = (valueDeserializer.readNumber() as number)
            }
            else if (size_buf__value1_buf_selector == 2) {
                size_buf__value1_buf = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for size_buf__value1_buf has to be chosen through deserialisation.")
            }
            const size_buf__value1 : Dimension = (size_buf__value1_buf as string | number | Resource)
            size_buf = ([size_buf__value0, size_buf__value1] as [ Dimension, Dimension ])
        }
        const size_result : [ Dimension, Dimension ] | undefined = size_buf
        const verticalAlign_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let verticalAlign_buf : ImageSpanAlignment | undefined
        if ((RuntimeType.UNDEFINED) != (verticalAlign_buf_runtimeType))
        {
            verticalAlign_buf = TypeChecker.ImageSpanAlignment_FromNumeric(valueDeserializer.readInt32())
        }
        const verticalAlign_result : ImageSpanAlignment | undefined = verticalAlign_buf
        const objectFit_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let objectFit_buf : ImageFit | undefined
        if ((RuntimeType.UNDEFINED) != (objectFit_buf_runtimeType))
        {
            objectFit_buf = TypeChecker.ImageFit_FromNumeric(valueDeserializer.readInt32())
        }
        const objectFit_result : ImageFit | undefined = objectFit_buf
        const layoutStyle_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let layoutStyle_buf : RichEditorLayoutStyle | undefined
        if ((RuntimeType.UNDEFINED) != (layoutStyle_buf_runtimeType))
        {
            layoutStyle_buf = RichEditorLayoutStyle_serializer.read(valueDeserializer)
        }
        const layoutStyle_result : RichEditorLayoutStyle | undefined = layoutStyle_buf
        let value : RichEditorImageSpanStyle = ({size: size_result, verticalAlign: verticalAlign_result, objectFit: objectFit_result, layoutStyle: layoutStyle_result} as RichEditorImageSpanStyle)
        return value
    }
}
export class RichEditorImageSpanStyleResult_serializer {
    public static write(buffer: SerializerBase, value: RichEditorImageSpanStyleResult): void {
        let valueSerializer : SerializerBase = buffer
        const value_size  = value.size
        const value_size_0  = value_size[0]
        valueSerializer.writeNumber(value_size_0)
        const value_size_1  = value_size[1]
        valueSerializer.writeNumber(value_size_1)
        const value_verticalAlign  = value.verticalAlign
        valueSerializer.writeInt32(TypeChecker.ImageSpanAlignment_ToNumeric(value_verticalAlign))
        const value_objectFit  = value.objectFit
        valueSerializer.writeInt32(TypeChecker.ImageFit_ToNumeric(value_objectFit))
        const value_layoutStyle  = value.layoutStyle
        let value_layoutStyle_type : int32 = RuntimeType.UNDEFINED
        value_layoutStyle_type = runtimeType(value_layoutStyle)
        valueSerializer.writeInt8(value_layoutStyle_type)
        if ((RuntimeType.UNDEFINED) != (value_layoutStyle_type)) {
            const value_layoutStyle_value  = value_layoutStyle!
            RichEditorLayoutStyle_serializer.write(valueSerializer, value_layoutStyle_value)
        }
    }
    public static read(buffer: DeserializerBase): RichEditorImageSpanStyleResult {
        let valueDeserializer : DeserializerBase = buffer
        const size_buf_value0 : number = (valueDeserializer.readNumber() as number)
        const size_buf_value1 : number = (valueDeserializer.readNumber() as number)
        const size_result : [ number, number ] = ([size_buf_value0, size_buf_value1] as [ number, number ])
        const verticalAlign_result : ImageSpanAlignment = TypeChecker.ImageSpanAlignment_FromNumeric(valueDeserializer.readInt32())
        const objectFit_result : ImageFit = TypeChecker.ImageFit_FromNumeric(valueDeserializer.readInt32())
        const layoutStyle_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let layoutStyle_buf : RichEditorLayoutStyle | undefined
        if ((RuntimeType.UNDEFINED) != (layoutStyle_buf_runtimeType))
        {
            layoutStyle_buf = RichEditorLayoutStyle_serializer.read(valueDeserializer)
        }
        const layoutStyle_result : RichEditorLayoutStyle | undefined = layoutStyle_buf
        let value : RichEditorImageSpanStyleResult = ({size: size_result, verticalAlign: verticalAlign_result, objectFit: objectFit_result, layoutStyle: layoutStyle_result} as RichEditorImageSpanStyleResult)
        return value
    }
}
export class RichEditorParagraphResult_serializer {
    public static write(buffer: SerializerBase, value: RichEditorParagraphResult): void {
        let valueSerializer : SerializerBase = buffer
        const value_style  = value.style
        RichEditorParagraphStyle_serializer.write(valueSerializer, value_style)
        const value_range  = value.range
        const value_range_0  = value_range[0]
        valueSerializer.writeNumber(value_range_0)
        const value_range_1  = value_range[1]
        valueSerializer.writeNumber(value_range_1)
    }
    public static read(buffer: DeserializerBase): RichEditorParagraphResult {
        let valueDeserializer : DeserializerBase = buffer
        const style_result : RichEditorParagraphStyle = RichEditorParagraphStyle_serializer.read(valueDeserializer)
        const range_buf_value0 : number = (valueDeserializer.readNumber() as number)
        const range_buf_value1 : number = (valueDeserializer.readNumber() as number)
        const range_result : [ number, number ] = ([range_buf_value0, range_buf_value1] as [ number, number ])
        let value : RichEditorParagraphResult = ({style: style_result, range: range_result} as RichEditorParagraphResult)
        return value
    }
}
export class RichEditorTextStyle_serializer {
    public static write(buffer: SerializerBase, value: RichEditorTextStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_fontColor  = value.fontColor
        let value_fontColor_type : int32 = RuntimeType.UNDEFINED
        value_fontColor_type = runtimeType(value_fontColor)
        valueSerializer.writeInt8(value_fontColor_type)
        if ((RuntimeType.UNDEFINED) != (value_fontColor_type)) {
            const value_fontColor_value  = value_fontColor!
            let value_fontColor_value_type : int32 = RuntimeType.UNDEFINED
            value_fontColor_value_type = runtimeType(value_fontColor_value)
            if (TypeChecker.isColor(value_fontColor_value)) {
                valueSerializer.writeInt8(0)
                const value_fontColor_value_0  = value_fontColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_fontColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_fontColor_value_type) {
                valueSerializer.writeInt8(1)
                const value_fontColor_value_1  = value_fontColor_value as number
                valueSerializer.writeNumber(value_fontColor_value_1)
            }
            else if (RuntimeType.STRING == value_fontColor_value_type) {
                valueSerializer.writeInt8(2)
                const value_fontColor_value_2  = value_fontColor_value as string
                valueSerializer.writeString(value_fontColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_fontColor_value_type) {
                valueSerializer.writeInt8(3)
                const value_fontColor_value_3  = value_fontColor_value as Resource
                Resource_serializer.write(valueSerializer, value_fontColor_value_3)
            }
        }
        const value_fontSize  = value.fontSize
        let value_fontSize_type : int32 = RuntimeType.UNDEFINED
        value_fontSize_type = runtimeType(value_fontSize)
        valueSerializer.writeInt8(value_fontSize_type)
        if ((RuntimeType.UNDEFINED) != (value_fontSize_type)) {
            const value_fontSize_value  = value_fontSize!
            let value_fontSize_value_type : int32 = RuntimeType.UNDEFINED
            value_fontSize_value_type = runtimeType(value_fontSize_value)
            if (RuntimeType.STRING == value_fontSize_value_type) {
                valueSerializer.writeInt8(0)
                const value_fontSize_value_0  = value_fontSize_value as string
                valueSerializer.writeString(value_fontSize_value_0)
            }
            else if (RuntimeType.NUMBER == value_fontSize_value_type) {
                valueSerializer.writeInt8(1)
                const value_fontSize_value_1  = value_fontSize_value as number
                valueSerializer.writeNumber(value_fontSize_value_1)
            }
            else if (RuntimeType.OBJECT == value_fontSize_value_type) {
                valueSerializer.writeInt8(2)
                const value_fontSize_value_2  = value_fontSize_value as Resource
                Resource_serializer.write(valueSerializer, value_fontSize_value_2)
            }
        }
        const value_fontStyle  = value.fontStyle
        let value_fontStyle_type : int32 = RuntimeType.UNDEFINED
        value_fontStyle_type = runtimeType(value_fontStyle)
        valueSerializer.writeInt8(value_fontStyle_type)
        if ((RuntimeType.UNDEFINED) != (value_fontStyle_type)) {
            const value_fontStyle_value  = (value_fontStyle as FontStyle)
            valueSerializer.writeInt32(TypeChecker.FontStyle_ToNumeric(value_fontStyle_value))
        }
        const value_fontWeight  = value.fontWeight
        let value_fontWeight_type : int32 = RuntimeType.UNDEFINED
        value_fontWeight_type = runtimeType(value_fontWeight)
        valueSerializer.writeInt8(value_fontWeight_type)
        if ((RuntimeType.UNDEFINED) != (value_fontWeight_type)) {
            const value_fontWeight_value  = value_fontWeight!
            let value_fontWeight_value_type : int32 = RuntimeType.UNDEFINED
            value_fontWeight_value_type = runtimeType(value_fontWeight_value)
            if (RuntimeType.NUMBER == value_fontWeight_value_type) {
                valueSerializer.writeInt8(0)
                const value_fontWeight_value_0  = value_fontWeight_value as number
                valueSerializer.writeNumber(value_fontWeight_value_0)
            }
            else if (TypeChecker.isFontWeight(value_fontWeight_value)) {
                valueSerializer.writeInt8(1)
                const value_fontWeight_value_1  = value_fontWeight_value as FontWeight
                valueSerializer.writeInt32(TypeChecker.FontWeight_ToNumeric(value_fontWeight_value_1))
            }
            else if (RuntimeType.STRING == value_fontWeight_value_type) {
                valueSerializer.writeInt8(2)
                const value_fontWeight_value_2  = value_fontWeight_value as string
                valueSerializer.writeString(value_fontWeight_value_2)
            }
        }
        const value_fontFamily  = value.fontFamily
        let value_fontFamily_type : int32 = RuntimeType.UNDEFINED
        value_fontFamily_type = runtimeType(value_fontFamily)
        valueSerializer.writeInt8(value_fontFamily_type)
        if ((RuntimeType.UNDEFINED) != (value_fontFamily_type)) {
            const value_fontFamily_value  = value_fontFamily!
            let value_fontFamily_value_type : int32 = RuntimeType.UNDEFINED
            value_fontFamily_value_type = runtimeType(value_fontFamily_value)
            if (RuntimeType.STRING == value_fontFamily_value_type) {
                valueSerializer.writeInt8(0)
                const value_fontFamily_value_0  = value_fontFamily_value as string
                valueSerializer.writeString(value_fontFamily_value_0)
            }
            else if (RuntimeType.OBJECT == value_fontFamily_value_type) {
                valueSerializer.writeInt8(1)
                const value_fontFamily_value_1  = value_fontFamily_value as Resource
                Resource_serializer.write(valueSerializer, value_fontFamily_value_1)
            }
        }
        const value_decoration  = value.decoration
        let value_decoration_type : int32 = RuntimeType.UNDEFINED
        value_decoration_type = runtimeType(value_decoration)
        valueSerializer.writeInt8(value_decoration_type)
        if ((RuntimeType.UNDEFINED) != (value_decoration_type)) {
            const value_decoration_value  = value_decoration!
            DecorationStyleInterface_serializer.write(valueSerializer, value_decoration_value)
        }
        const value_textShadow  = value.textShadow
        let value_textShadow_type : int32 = RuntimeType.UNDEFINED
        value_textShadow_type = runtimeType(value_textShadow)
        valueSerializer.writeInt8(value_textShadow_type)
        if ((RuntimeType.UNDEFINED) != (value_textShadow_type)) {
            const value_textShadow_value  = value_textShadow!
            let value_textShadow_value_type : int32 = RuntimeType.UNDEFINED
            value_textShadow_value_type = runtimeType(value_textShadow_value)
            if (TypeChecker.isShadowOptions(value_textShadow_value, false, false, false, false, false, false)) {
                valueSerializer.writeInt8(0)
                const value_textShadow_value_0  = value_textShadow_value as ShadowOptions
                ShadowOptions_serializer.write(valueSerializer, value_textShadow_value_0)
            }
            else if (((RuntimeType.OBJECT) == (value_textShadow_value_type)) && (TypeChecker.isArray_ShadowOptions(value_textShadow_value))) {
                valueSerializer.writeInt8(1)
                const value_textShadow_value_1  = value_textShadow_value as Array<ShadowOptions>
                valueSerializer.writeInt32(value_textShadow_value_1.length as int32)
                for (let i = 0; i < value_textShadow_value_1.length; i++) {
                    const value_textShadow_value_1_element : ShadowOptions = value_textShadow_value_1[i]
                    ShadowOptions_serializer.write(valueSerializer, value_textShadow_value_1_element)
                }
            }
        }
        const value_letterSpacing  = value.letterSpacing
        let value_letterSpacing_type : int32 = RuntimeType.UNDEFINED
        value_letterSpacing_type = runtimeType(value_letterSpacing)
        valueSerializer.writeInt8(value_letterSpacing_type)
        if ((RuntimeType.UNDEFINED) != (value_letterSpacing_type)) {
            const value_letterSpacing_value  = value_letterSpacing!
            let value_letterSpacing_value_type : int32 = RuntimeType.UNDEFINED
            value_letterSpacing_value_type = runtimeType(value_letterSpacing_value)
            if (RuntimeType.NUMBER == value_letterSpacing_value_type) {
                valueSerializer.writeInt8(0)
                const value_letterSpacing_value_0  = value_letterSpacing_value as number
                valueSerializer.writeNumber(value_letterSpacing_value_0)
            }
            else if (RuntimeType.STRING == value_letterSpacing_value_type) {
                valueSerializer.writeInt8(1)
                const value_letterSpacing_value_1  = value_letterSpacing_value as string
                valueSerializer.writeString(value_letterSpacing_value_1)
            }
        }
        const value_lineHeight  = value.lineHeight
        let value_lineHeight_type : int32 = RuntimeType.UNDEFINED
        value_lineHeight_type = runtimeType(value_lineHeight)
        valueSerializer.writeInt8(value_lineHeight_type)
        if ((RuntimeType.UNDEFINED) != (value_lineHeight_type)) {
            const value_lineHeight_value  = value_lineHeight!
            let value_lineHeight_value_type : int32 = RuntimeType.UNDEFINED
            value_lineHeight_value_type = runtimeType(value_lineHeight_value)
            if (RuntimeType.NUMBER == value_lineHeight_value_type) {
                valueSerializer.writeInt8(0)
                const value_lineHeight_value_0  = value_lineHeight_value as number
                valueSerializer.writeNumber(value_lineHeight_value_0)
            }
            else if (RuntimeType.STRING == value_lineHeight_value_type) {
                valueSerializer.writeInt8(1)
                const value_lineHeight_value_1  = value_lineHeight_value as string
                valueSerializer.writeString(value_lineHeight_value_1)
            }
            else if (RuntimeType.OBJECT == value_lineHeight_value_type) {
                valueSerializer.writeInt8(2)
                const value_lineHeight_value_2  = value_lineHeight_value as Resource
                Resource_serializer.write(valueSerializer, value_lineHeight_value_2)
            }
        }
        const value_halfLeading  = value.halfLeading
        let value_halfLeading_type : int32 = RuntimeType.UNDEFINED
        value_halfLeading_type = runtimeType(value_halfLeading)
        valueSerializer.writeInt8(value_halfLeading_type)
        if ((RuntimeType.UNDEFINED) != (value_halfLeading_type)) {
            const value_halfLeading_value  = value_halfLeading!
            valueSerializer.writeBoolean(value_halfLeading_value)
        }
        const value_fontFeature  = value.fontFeature
        let value_fontFeature_type : int32 = RuntimeType.UNDEFINED
        value_fontFeature_type = runtimeType(value_fontFeature)
        valueSerializer.writeInt8(value_fontFeature_type)
        if ((RuntimeType.UNDEFINED) != (value_fontFeature_type)) {
            const value_fontFeature_value  = value_fontFeature!
            valueSerializer.writeString(value_fontFeature_value)
        }
        const value_textBackgroundStyle  = value.textBackgroundStyle
        let value_textBackgroundStyle_type : int32 = RuntimeType.UNDEFINED
        value_textBackgroundStyle_type = runtimeType(value_textBackgroundStyle)
        valueSerializer.writeInt8(value_textBackgroundStyle_type)
        if ((RuntimeType.UNDEFINED) != (value_textBackgroundStyle_type)) {
            const value_textBackgroundStyle_value  = value_textBackgroundStyle!
            TextBackgroundStyle_serializer.write(valueSerializer, value_textBackgroundStyle_value)
        }
    }
    public static read(buffer: DeserializerBase): RichEditorTextStyle {
        let valueDeserializer : DeserializerBase = buffer
        const fontColor_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let fontColor_buf : ResourceColor | undefined
        if ((RuntimeType.UNDEFINED) != (fontColor_buf_runtimeType))
        {
            const fontColor_buf__selector : int32 = valueDeserializer.readInt8()
            let fontColor_buf_ : Color | number | string | Resource | undefined
            if (fontColor_buf__selector == 0) {
                fontColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (fontColor_buf__selector == 1) {
                fontColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (fontColor_buf__selector == 2) {
                fontColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (fontColor_buf__selector == 3) {
                fontColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for fontColor_buf_ has to be chosen through deserialisation.")
            }
            fontColor_buf = (fontColor_buf_ as Color | number | string | Resource)
        }
        const fontColor_result : ResourceColor | undefined = fontColor_buf
        const fontSize_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let fontSize_buf : string | number | Resource | undefined
        if ((RuntimeType.UNDEFINED) != (fontSize_buf_runtimeType))
        {
            const fontSize_buf__selector : int32 = valueDeserializer.readInt8()
            let fontSize_buf_ : string | number | Resource | undefined
            if (fontSize_buf__selector == 0) {
                fontSize_buf_ = (valueDeserializer.readString() as string)
            }
            else if (fontSize_buf__selector == 1) {
                fontSize_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (fontSize_buf__selector == 2) {
                fontSize_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for fontSize_buf_ has to be chosen through deserialisation.")
            }
            fontSize_buf = (fontSize_buf_ as string | number | Resource)
        }
        const fontSize_result : Length | number | undefined = fontSize_buf
        const fontStyle_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let fontStyle_buf : FontStyle | undefined
        if ((RuntimeType.UNDEFINED) != (fontStyle_buf_runtimeType))
        {
            fontStyle_buf = TypeChecker.FontStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const fontStyle_result : FontStyle | undefined = fontStyle_buf
        const fontWeight_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let fontWeight_buf : number | FontWeight | string | undefined
        if ((RuntimeType.UNDEFINED) != (fontWeight_buf_runtimeType))
        {
            const fontWeight_buf__selector : int32 = valueDeserializer.readInt8()
            let fontWeight_buf_ : number | FontWeight | string | undefined
            if (fontWeight_buf__selector == 0) {
                fontWeight_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (fontWeight_buf__selector == 1) {
                fontWeight_buf_ = TypeChecker.FontWeight_FromNumeric(valueDeserializer.readInt32())
            }
            else if (fontWeight_buf__selector == 2) {
                fontWeight_buf_ = (valueDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for fontWeight_buf_ has to be chosen through deserialisation.")
            }
            fontWeight_buf = (fontWeight_buf_ as number | FontWeight | string)
        }
        const fontWeight_result : number | FontWeight | string | undefined = fontWeight_buf
        const fontFamily_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let fontFamily_buf : ResourceStr | undefined
        if ((RuntimeType.UNDEFINED) != (fontFamily_buf_runtimeType))
        {
            const fontFamily_buf__selector : int32 = valueDeserializer.readInt8()
            let fontFamily_buf_ : string | Resource | undefined
            if (fontFamily_buf__selector == 0) {
                fontFamily_buf_ = (valueDeserializer.readString() as string)
            }
            else if (fontFamily_buf__selector == 1) {
                fontFamily_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for fontFamily_buf_ has to be chosen through deserialisation.")
            }
            fontFamily_buf = (fontFamily_buf_ as string | Resource)
        }
        const fontFamily_result : ResourceStr | undefined = fontFamily_buf
        const decoration_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let decoration_buf : DecorationStyleInterface | undefined
        if ((RuntimeType.UNDEFINED) != (decoration_buf_runtimeType))
        {
            decoration_buf = DecorationStyleInterface_serializer.read(valueDeserializer)
        }
        const decoration_result : DecorationStyleInterface | undefined = decoration_buf
        const textShadow_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let textShadow_buf : ShadowOptions | Array<ShadowOptions> | undefined
        if ((RuntimeType.UNDEFINED) != (textShadow_buf_runtimeType))
        {
            const textShadow_buf__selector : int32 = valueDeserializer.readInt8()
            let textShadow_buf_ : ShadowOptions | Array<ShadowOptions> | undefined
            if (textShadow_buf__selector == 0) {
                textShadow_buf_ = ShadowOptions_serializer.read(valueDeserializer)
            }
            else if (textShadow_buf__selector == 1) {
                const textShadow_buf__u_length : int32 = valueDeserializer.readInt32()
                let textShadow_buf__u : Array<ShadowOptions> = new Array<ShadowOptions>(textShadow_buf__u_length)
                for (let textShadow_buf__u_i = 0; textShadow_buf__u_i < textShadow_buf__u_length; textShadow_buf__u_i++) {
                    textShadow_buf__u[textShadow_buf__u_i] = ShadowOptions_serializer.read(valueDeserializer)
                }
                textShadow_buf_ = textShadow_buf__u
            }
            else {
                throw new Error("One of the branches for textShadow_buf_ has to be chosen through deserialisation.")
            }
            textShadow_buf = (textShadow_buf_ as ShadowOptions | Array<ShadowOptions>)
        }
        const textShadow_result : ShadowOptions | Array<ShadowOptions> | undefined = textShadow_buf
        const letterSpacing_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let letterSpacing_buf : number | string | undefined
        if ((RuntimeType.UNDEFINED) != (letterSpacing_buf_runtimeType))
        {
            const letterSpacing_buf__selector : int32 = valueDeserializer.readInt8()
            let letterSpacing_buf_ : number | string | undefined
            if (letterSpacing_buf__selector == 0) {
                letterSpacing_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (letterSpacing_buf__selector == 1) {
                letterSpacing_buf_ = (valueDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for letterSpacing_buf_ has to be chosen through deserialisation.")
            }
            letterSpacing_buf = (letterSpacing_buf_ as number | string)
        }
        const letterSpacing_result : number | string | undefined = letterSpacing_buf
        const lineHeight_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let lineHeight_buf : number | string | Resource | undefined
        if ((RuntimeType.UNDEFINED) != (lineHeight_buf_runtimeType))
        {
            const lineHeight_buf__selector : int32 = valueDeserializer.readInt8()
            let lineHeight_buf_ : number | string | Resource | undefined
            if (lineHeight_buf__selector == 0) {
                lineHeight_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (lineHeight_buf__selector == 1) {
                lineHeight_buf_ = (valueDeserializer.readString() as string)
            }
            else if (lineHeight_buf__selector == 2) {
                lineHeight_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for lineHeight_buf_ has to be chosen through deserialisation.")
            }
            lineHeight_buf = (lineHeight_buf_ as number | string | Resource)
        }
        const lineHeight_result : number | string | Resource | undefined = lineHeight_buf
        const halfLeading_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let halfLeading_buf : boolean | undefined
        if ((RuntimeType.UNDEFINED) != (halfLeading_buf_runtimeType))
        {
            halfLeading_buf = valueDeserializer.readBoolean()
        }
        const halfLeading_result : boolean | undefined = halfLeading_buf
        const fontFeature_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let fontFeature_buf : string | undefined
        if ((RuntimeType.UNDEFINED) != (fontFeature_buf_runtimeType))
        {
            fontFeature_buf = (valueDeserializer.readString() as string)
        }
        const fontFeature_result : string | undefined = fontFeature_buf
        const textBackgroundStyle_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let textBackgroundStyle_buf : TextBackgroundStyle | undefined
        if ((RuntimeType.UNDEFINED) != (textBackgroundStyle_buf_runtimeType))
        {
            textBackgroundStyle_buf = TextBackgroundStyle_serializer.read(valueDeserializer)
        }
        const textBackgroundStyle_result : TextBackgroundStyle | undefined = textBackgroundStyle_buf
        let value : RichEditorTextStyle = ({fontColor: fontColor_result, fontSize: fontSize_result, fontStyle: fontStyle_result, fontWeight: fontWeight_result, fontFamily: fontFamily_result, decoration: decoration_result, textShadow: textShadow_result, letterSpacing: letterSpacing_result, lineHeight: lineHeight_result, halfLeading: halfLeading_result, fontFeature: fontFeature_result, textBackgroundStyle: textBackgroundStyle_result} as RichEditorTextStyle)
        return value
    }
}
export class RichEditorTextStyleResult_serializer {
    public static write(buffer: SerializerBase, value: RichEditorTextStyleResult): void {
        let valueSerializer : SerializerBase = buffer
        const value_fontColor  = value.fontColor
        let value_fontColor_type : int32 = RuntimeType.UNDEFINED
        value_fontColor_type = runtimeType(value_fontColor)
        if (TypeChecker.isColor(value_fontColor)) {
            valueSerializer.writeInt8(0)
            const value_fontColor_0  = value_fontColor as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_fontColor_0))
        }
        else if (RuntimeType.NUMBER == value_fontColor_type) {
            valueSerializer.writeInt8(1)
            const value_fontColor_1  = value_fontColor as number
            valueSerializer.writeNumber(value_fontColor_1)
        }
        else if (RuntimeType.STRING == value_fontColor_type) {
            valueSerializer.writeInt8(2)
            const value_fontColor_2  = value_fontColor as string
            valueSerializer.writeString(value_fontColor_2)
        }
        else if (RuntimeType.OBJECT == value_fontColor_type) {
            valueSerializer.writeInt8(3)
            const value_fontColor_3  = value_fontColor as Resource
            Resource_serializer.write(valueSerializer, value_fontColor_3)
        }
        const value_fontSize  = value.fontSize
        valueSerializer.writeNumber(value_fontSize)
        const value_fontStyle  = value.fontStyle
        valueSerializer.writeInt32(TypeChecker.FontStyle_ToNumeric(value_fontStyle))
        const value_fontWeight  = value.fontWeight
        valueSerializer.writeNumber(value_fontWeight)
        const value_fontFamily  = value.fontFamily
        valueSerializer.writeString(value_fontFamily)
        const value_decoration  = value.decoration
        DecorationStyleResult_serializer.write(valueSerializer, value_decoration)
        const value_textShadow  = value.textShadow
        let value_textShadow_type : int32 = RuntimeType.UNDEFINED
        value_textShadow_type = runtimeType(value_textShadow)
        valueSerializer.writeInt8(value_textShadow_type)
        if ((RuntimeType.UNDEFINED) != (value_textShadow_type)) {
            const value_textShadow_value  = value_textShadow!
            valueSerializer.writeInt32(value_textShadow_value.length as int32)
            for (let i = 0; i < value_textShadow_value.length; i++) {
                const value_textShadow_value_element : ShadowOptions = value_textShadow_value[i]
                ShadowOptions_serializer.write(valueSerializer, value_textShadow_value_element)
            }
        }
        const value_letterSpacing  = value.letterSpacing
        let value_letterSpacing_type : int32 = RuntimeType.UNDEFINED
        value_letterSpacing_type = runtimeType(value_letterSpacing)
        valueSerializer.writeInt8(value_letterSpacing_type)
        if ((RuntimeType.UNDEFINED) != (value_letterSpacing_type)) {
            const value_letterSpacing_value  = value_letterSpacing!
            valueSerializer.writeNumber(value_letterSpacing_value)
        }
        const value_lineHeight  = value.lineHeight
        let value_lineHeight_type : int32 = RuntimeType.UNDEFINED
        value_lineHeight_type = runtimeType(value_lineHeight)
        valueSerializer.writeInt8(value_lineHeight_type)
        if ((RuntimeType.UNDEFINED) != (value_lineHeight_type)) {
            const value_lineHeight_value  = value_lineHeight!
            valueSerializer.writeNumber(value_lineHeight_value)
        }
        const value_halfLeading  = value.halfLeading
        let value_halfLeading_type : int32 = RuntimeType.UNDEFINED
        value_halfLeading_type = runtimeType(value_halfLeading)
        valueSerializer.writeInt8(value_halfLeading_type)
        if ((RuntimeType.UNDEFINED) != (value_halfLeading_type)) {
            const value_halfLeading_value  = value_halfLeading!
            valueSerializer.writeBoolean(value_halfLeading_value)
        }
        const value_fontFeature  = value.fontFeature
        let value_fontFeature_type : int32 = RuntimeType.UNDEFINED
        value_fontFeature_type = runtimeType(value_fontFeature)
        valueSerializer.writeInt8(value_fontFeature_type)
        if ((RuntimeType.UNDEFINED) != (value_fontFeature_type)) {
            const value_fontFeature_value  = value_fontFeature!
            valueSerializer.writeString(value_fontFeature_value)
        }
        const value_textBackgroundStyle  = value.textBackgroundStyle
        let value_textBackgroundStyle_type : int32 = RuntimeType.UNDEFINED
        value_textBackgroundStyle_type = runtimeType(value_textBackgroundStyle)
        valueSerializer.writeInt8(value_textBackgroundStyle_type)
        if ((RuntimeType.UNDEFINED) != (value_textBackgroundStyle_type)) {
            const value_textBackgroundStyle_value  = value_textBackgroundStyle!
            TextBackgroundStyle_serializer.write(valueSerializer, value_textBackgroundStyle_value)
        }
    }
    public static read(buffer: DeserializerBase): RichEditorTextStyleResult {
        let valueDeserializer : DeserializerBase = buffer
        const fontColor_buf_selector : int32 = valueDeserializer.readInt8()
        let fontColor_buf : Color | number | string | Resource | undefined
        if (fontColor_buf_selector == 0) {
            fontColor_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (fontColor_buf_selector == 1) {
            fontColor_buf = (valueDeserializer.readNumber() as number)
        }
        else if (fontColor_buf_selector == 2) {
            fontColor_buf = (valueDeserializer.readString() as string)
        }
        else if (fontColor_buf_selector == 3) {
            fontColor_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for fontColor_buf has to be chosen through deserialisation.")
        }
        const fontColor_result : ResourceColor = (fontColor_buf as Color | number | string | Resource)
        const fontSize_result : number = (valueDeserializer.readNumber() as number)
        const fontStyle_result : FontStyle = TypeChecker.FontStyle_FromNumeric(valueDeserializer.readInt32())
        const fontWeight_result : number = (valueDeserializer.readNumber() as number)
        const fontFamily_result : string = (valueDeserializer.readString() as string)
        const decoration_result : DecorationStyleResult = DecorationStyleResult_serializer.read(valueDeserializer)
        const textShadow_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let textShadow_buf : Array<ShadowOptions> | undefined
        if ((RuntimeType.UNDEFINED) != (textShadow_buf_runtimeType))
        {
            const textShadow_buf__length : int32 = valueDeserializer.readInt32()
            let textShadow_buf_ : Array<ShadowOptions> = new Array<ShadowOptions>(textShadow_buf__length)
            for (let textShadow_buf__i = 0; textShadow_buf__i < textShadow_buf__length; textShadow_buf__i++) {
                textShadow_buf_[textShadow_buf__i] = ShadowOptions_serializer.read(valueDeserializer)
            }
            textShadow_buf = textShadow_buf_
        }
        const textShadow_result : Array<ShadowOptions> | undefined = textShadow_buf
        const letterSpacing_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let letterSpacing_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (letterSpacing_buf_runtimeType))
        {
            letterSpacing_buf = (valueDeserializer.readNumber() as number)
        }
        const letterSpacing_result : number | undefined = letterSpacing_buf
        const lineHeight_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let lineHeight_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (lineHeight_buf_runtimeType))
        {
            lineHeight_buf = (valueDeserializer.readNumber() as number)
        }
        const lineHeight_result : number | undefined = lineHeight_buf
        const halfLeading_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let halfLeading_buf : boolean | undefined
        if ((RuntimeType.UNDEFINED) != (halfLeading_buf_runtimeType))
        {
            halfLeading_buf = valueDeserializer.readBoolean()
        }
        const halfLeading_result : boolean | undefined = halfLeading_buf
        const fontFeature_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let fontFeature_buf : string | undefined
        if ((RuntimeType.UNDEFINED) != (fontFeature_buf_runtimeType))
        {
            fontFeature_buf = (valueDeserializer.readString() as string)
        }
        const fontFeature_result : string | undefined = fontFeature_buf
        const textBackgroundStyle_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let textBackgroundStyle_buf : TextBackgroundStyle | undefined
        if ((RuntimeType.UNDEFINED) != (textBackgroundStyle_buf_runtimeType))
        {
            textBackgroundStyle_buf = TextBackgroundStyle_serializer.read(valueDeserializer)
        }
        const textBackgroundStyle_result : TextBackgroundStyle | undefined = textBackgroundStyle_buf
        let value : RichEditorTextStyleResult = ({fontColor: fontColor_result, fontSize: fontSize_result, fontStyle: fontStyle_result, fontWeight: fontWeight_result, fontFamily: fontFamily_result, decoration: decoration_result, textShadow: textShadow_result, letterSpacing: letterSpacing_result, lineHeight: lineHeight_result, halfLeading: halfLeading_result, fontFeature: fontFeature_result, textBackgroundStyle: textBackgroundStyle_result} as RichEditorTextStyleResult)
        return value
    }
}
export class RichEditorUpdateImageSpanStyleOptions_serializer {
    public static write(buffer: SerializerBase, value: RichEditorUpdateImageSpanStyleOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_start  = value.start
        let value_start_type : int32 = RuntimeType.UNDEFINED
        value_start_type = runtimeType(value_start)
        valueSerializer.writeInt8(value_start_type)
        if ((RuntimeType.UNDEFINED) != (value_start_type)) {
            const value_start_value  = value_start!
            valueSerializer.writeNumber(value_start_value)
        }
        const value_end  = value.end
        let value_end_type : int32 = RuntimeType.UNDEFINED
        value_end_type = runtimeType(value_end)
        valueSerializer.writeInt8(value_end_type)
        if ((RuntimeType.UNDEFINED) != (value_end_type)) {
            const value_end_value  = value_end!
            valueSerializer.writeNumber(value_end_value)
        }
        const value_imageStyle  = value.imageStyle
        RichEditorImageSpanStyle_serializer.write(valueSerializer, value_imageStyle)
    }
    public static read(buffer: DeserializerBase): RichEditorUpdateImageSpanStyleOptions {
        let valueDeserializer : DeserializerBase = buffer
        const start_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let start_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (start_buf_runtimeType))
        {
            start_buf = (valueDeserializer.readNumber() as number)
        }
        const start_result : number | undefined = start_buf
        const end_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let end_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (end_buf_runtimeType))
        {
            end_buf = (valueDeserializer.readNumber() as number)
        }
        const end_result : number | undefined = end_buf
        const imageStyle_result : RichEditorImageSpanStyle = RichEditorImageSpanStyle_serializer.read(valueDeserializer)
        let value : RichEditorUpdateImageSpanStyleOptions = ({start: start_result, end: end_result, imageStyle: imageStyle_result} as RichEditorUpdateImageSpanStyleOptions)
        return value
    }
}
export class RichEditorUpdateTextSpanStyleOptions_serializer {
    public static write(buffer: SerializerBase, value: RichEditorUpdateTextSpanStyleOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_start  = value.start
        let value_start_type : int32 = RuntimeType.UNDEFINED
        value_start_type = runtimeType(value_start)
        valueSerializer.writeInt8(value_start_type)
        if ((RuntimeType.UNDEFINED) != (value_start_type)) {
            const value_start_value  = value_start!
            valueSerializer.writeNumber(value_start_value)
        }
        const value_end  = value.end
        let value_end_type : int32 = RuntimeType.UNDEFINED
        value_end_type = runtimeType(value_end)
        valueSerializer.writeInt8(value_end_type)
        if ((RuntimeType.UNDEFINED) != (value_end_type)) {
            const value_end_value  = value_end!
            valueSerializer.writeNumber(value_end_value)
        }
        const value_textStyle  = value.textStyle
        RichEditorTextStyle_serializer.write(valueSerializer, value_textStyle)
        const value_urlStyle  = value.urlStyle
        let value_urlStyle_type : int32 = RuntimeType.UNDEFINED
        value_urlStyle_type = runtimeType(value_urlStyle)
        valueSerializer.writeInt8(value_urlStyle_type)
        if ((RuntimeType.UNDEFINED) != (value_urlStyle_type)) {
            const value_urlStyle_value  = value_urlStyle!
            RichEditorUrlStyle_serializer.write(valueSerializer, value_urlStyle_value)
        }
    }
    public static read(buffer: DeserializerBase): RichEditorUpdateTextSpanStyleOptions {
        let valueDeserializer : DeserializerBase = buffer
        const start_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let start_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (start_buf_runtimeType))
        {
            start_buf = (valueDeserializer.readNumber() as number)
        }
        const start_result : number | undefined = start_buf
        const end_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let end_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (end_buf_runtimeType))
        {
            end_buf = (valueDeserializer.readNumber() as number)
        }
        const end_result : number | undefined = end_buf
        const textStyle_result : RichEditorTextStyle = RichEditorTextStyle_serializer.read(valueDeserializer)
        const urlStyle_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let urlStyle_buf : RichEditorUrlStyle | undefined
        if ((RuntimeType.UNDEFINED) != (urlStyle_buf_runtimeType))
        {
            urlStyle_buf = RichEditorUrlStyle_serializer.read(valueDeserializer)
        }
        const urlStyle_result : RichEditorUrlStyle | undefined = urlStyle_buf
        let value : RichEditorUpdateTextSpanStyleOptions = ({start: start_result, end: end_result, textStyle: textStyle_result, urlStyle: urlStyle_result} as RichEditorUpdateTextSpanStyleOptions)
        return value
    }
}
export class RichEditorImageSpanOptions_serializer {
    public static write(buffer: SerializerBase, value: RichEditorImageSpanOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_offset  = value.offset
        let value_offset_type : int32 = RuntimeType.UNDEFINED
        value_offset_type = runtimeType(value_offset)
        valueSerializer.writeInt8(value_offset_type)
        if ((RuntimeType.UNDEFINED) != (value_offset_type)) {
            const value_offset_value  = value_offset!
            valueSerializer.writeNumber(value_offset_value)
        }
        const value_imageStyle  = value.imageStyle
        let value_imageStyle_type : int32 = RuntimeType.UNDEFINED
        value_imageStyle_type = runtimeType(value_imageStyle)
        valueSerializer.writeInt8(value_imageStyle_type)
        if ((RuntimeType.UNDEFINED) != (value_imageStyle_type)) {
            const value_imageStyle_value  = value_imageStyle!
            RichEditorImageSpanStyle_serializer.write(valueSerializer, value_imageStyle_value)
        }
        const value_gesture  = value.gesture
        let value_gesture_type : int32 = RuntimeType.UNDEFINED
        value_gesture_type = runtimeType(value_gesture)
        valueSerializer.writeInt8(value_gesture_type)
        if ((RuntimeType.UNDEFINED) != (value_gesture_type)) {
            const value_gesture_value  = value_gesture!
            RichEditorGesture_serializer.write(valueSerializer, value_gesture_value)
        }
        const value_onHover  = value.onHover
        let value_onHover_type : int32 = RuntimeType.UNDEFINED
        value_onHover_type = runtimeType(value_onHover)
        valueSerializer.writeInt8(value_onHover_type)
        if ((RuntimeType.UNDEFINED) != (value_onHover_type)) {
            const value_onHover_value  = value_onHover!
            valueSerializer.holdAndWriteCallback(value_onHover_value)
        }
    }
    public static read(buffer: DeserializerBase): RichEditorImageSpanOptions {
        let valueDeserializer : DeserializerBase = buffer
        const offset_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let offset_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (offset_buf_runtimeType))
        {
            offset_buf = (valueDeserializer.readNumber() as number)
        }
        const offset_result : number | undefined = offset_buf
        const imageStyle_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let imageStyle_buf : RichEditorImageSpanStyle | undefined
        if ((RuntimeType.UNDEFINED) != (imageStyle_buf_runtimeType))
        {
            imageStyle_buf = RichEditorImageSpanStyle_serializer.read(valueDeserializer)
        }
        const imageStyle_result : RichEditorImageSpanStyle | undefined = imageStyle_buf
        const gesture_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let gesture_buf : RichEditorGesture | undefined
        if ((RuntimeType.UNDEFINED) != (gesture_buf_runtimeType))
        {
            gesture_buf = RichEditorGesture_serializer.read(valueDeserializer)
        }
        const gesture_result : RichEditorGesture | undefined = gesture_buf
        const onHover_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let onHover_buf : OnHoverCallback | undefined
        if ((RuntimeType.UNDEFINED) != (onHover_buf_runtimeType))
        {
            const onHover_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onHover_buf__call : KPointer = valueDeserializer.readPointer()
            const onHover_buf__callSync : KPointer = valueDeserializer.readPointer()
            onHover_buf = (status: boolean, event: HoverEvent):void => { 
    const onHover_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onHover_buf__argsSerializer.writeInt32(onHover_buf__resource.resourceId);
    onHover_buf__argsSerializer.writePointer(onHover_buf__call);
    onHover_buf__argsSerializer.writePointer(onHover_buf__callSync);
    onHover_buf__argsSerializer.writeBoolean(status);
    HoverEvent_serializer.write(onHover_buf__argsSerializer, event);
    InteropNativeModule._CallCallback(-2025767812, onHover_buf__argsSerializer.asBuffer(), onHover_buf__argsSerializer.length());
    onHover_buf__argsSerializer.release();
    return; }
        }
        const onHover_result : OnHoverCallback | undefined = onHover_buf
        let value : RichEditorImageSpanOptions = ({offset: offset_result, imageStyle: imageStyle_result, gesture: gesture_result, onHover: onHover_result} as RichEditorImageSpanOptions)
        return value
    }
}
export class RichEditorImageSpanResult_serializer {
    public static write(buffer: SerializerBase, value: RichEditorImageSpanResult): void {
        let valueSerializer : SerializerBase = buffer
        const value_spanPosition  = value.spanPosition
        RichEditorSpanPosition_serializer.write(valueSerializer, value_spanPosition)
        const value_valuePixelMap  = value.valuePixelMap
        let value_valuePixelMap_type : int32 = RuntimeType.UNDEFINED
        value_valuePixelMap_type = runtimeType(value_valuePixelMap)
        valueSerializer.writeInt8(value_valuePixelMap_type)
        if ((RuntimeType.UNDEFINED) != (value_valuePixelMap_type)) {
            const value_valuePixelMap_value  = value_valuePixelMap!
            image_PixelMap_serializer.write(valueSerializer, value_valuePixelMap_value)
        }
        const value_valueResourceStr  = value.valueResourceStr
        let value_valueResourceStr_type : int32 = RuntimeType.UNDEFINED
        value_valueResourceStr_type = runtimeType(value_valueResourceStr)
        valueSerializer.writeInt8(value_valueResourceStr_type)
        if ((RuntimeType.UNDEFINED) != (value_valueResourceStr_type)) {
            const value_valueResourceStr_value  = value_valueResourceStr!
            let value_valueResourceStr_value_type : int32 = RuntimeType.UNDEFINED
            value_valueResourceStr_value_type = runtimeType(value_valueResourceStr_value)
            if (RuntimeType.STRING == value_valueResourceStr_value_type) {
                valueSerializer.writeInt8(0)
                const value_valueResourceStr_value_0  = value_valueResourceStr_value as string
                valueSerializer.writeString(value_valueResourceStr_value_0)
            }
            else if (RuntimeType.OBJECT == value_valueResourceStr_value_type) {
                valueSerializer.writeInt8(1)
                const value_valueResourceStr_value_1  = value_valueResourceStr_value as Resource
                Resource_serializer.write(valueSerializer, value_valueResourceStr_value_1)
            }
        }
        const value_imageStyle  = value.imageStyle
        RichEditorImageSpanStyleResult_serializer.write(valueSerializer, value_imageStyle)
        const value_offsetInSpan  = value.offsetInSpan
        const value_offsetInSpan_0  = value_offsetInSpan[0]
        valueSerializer.writeNumber(value_offsetInSpan_0)
        const value_offsetInSpan_1  = value_offsetInSpan[1]
        valueSerializer.writeNumber(value_offsetInSpan_1)
    }
    public static read(buffer: DeserializerBase): RichEditorImageSpanResult {
        let valueDeserializer : DeserializerBase = buffer
        const spanPosition_result : RichEditorSpanPosition = RichEditorSpanPosition_serializer.read(valueDeserializer)
        const valuePixelMap_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let valuePixelMap_buf : image.PixelMap | undefined
        if ((RuntimeType.UNDEFINED) != (valuePixelMap_buf_runtimeType))
        {
            valuePixelMap_buf = (image_PixelMap_serializer.read(valueDeserializer) as image.PixelMap)
        }
        const valuePixelMap_result : image.PixelMap | undefined = valuePixelMap_buf
        const valueResourceStr_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let valueResourceStr_buf : ResourceStr | undefined
        if ((RuntimeType.UNDEFINED) != (valueResourceStr_buf_runtimeType))
        {
            const valueResourceStr_buf__selector : int32 = valueDeserializer.readInt8()
            let valueResourceStr_buf_ : string | Resource | undefined
            if (valueResourceStr_buf__selector == 0) {
                valueResourceStr_buf_ = (valueDeserializer.readString() as string)
            }
            else if (valueResourceStr_buf__selector == 1) {
                valueResourceStr_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for valueResourceStr_buf_ has to be chosen through deserialisation.")
            }
            valueResourceStr_buf = (valueResourceStr_buf_ as string | Resource)
        }
        const valueResourceStr_result : ResourceStr | undefined = valueResourceStr_buf
        const imageStyle_result : RichEditorImageSpanStyleResult = RichEditorImageSpanStyleResult_serializer.read(valueDeserializer)
        const offsetInSpan_buf_value0 : number = (valueDeserializer.readNumber() as number)
        const offsetInSpan_buf_value1 : number = (valueDeserializer.readNumber() as number)
        const offsetInSpan_result : [ number, number ] = ([offsetInSpan_buf_value0, offsetInSpan_buf_value1] as [ number, number ])
        let value : RichEditorImageSpanResult = ({spanPosition: spanPosition_result, valuePixelMap: valuePixelMap_result, valueResourceStr: valueResourceStr_result, imageStyle: imageStyle_result, offsetInSpan: offsetInSpan_result} as RichEditorImageSpanResult)
        return value
    }
}
export class RichEditorTextSpanOptions_serializer {
    public static write(buffer: SerializerBase, value: RichEditorTextSpanOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_offset  = value.offset
        let value_offset_type : int32 = RuntimeType.UNDEFINED
        value_offset_type = runtimeType(value_offset)
        valueSerializer.writeInt8(value_offset_type)
        if ((RuntimeType.UNDEFINED) != (value_offset_type)) {
            const value_offset_value  = value_offset!
            valueSerializer.writeNumber(value_offset_value)
        }
        const value_style  = value.style
        let value_style_type : int32 = RuntimeType.UNDEFINED
        value_style_type = runtimeType(value_style)
        valueSerializer.writeInt8(value_style_type)
        if ((RuntimeType.UNDEFINED) != (value_style_type)) {
            const value_style_value  = value_style!
            RichEditorTextStyle_serializer.write(valueSerializer, value_style_value)
        }
        const value_paragraphStyle  = value.paragraphStyle
        let value_paragraphStyle_type : int32 = RuntimeType.UNDEFINED
        value_paragraphStyle_type = runtimeType(value_paragraphStyle)
        valueSerializer.writeInt8(value_paragraphStyle_type)
        if ((RuntimeType.UNDEFINED) != (value_paragraphStyle_type)) {
            const value_paragraphStyle_value  = value_paragraphStyle!
            RichEditorParagraphStyle_serializer.write(valueSerializer, value_paragraphStyle_value)
        }
        const value_gesture  = value.gesture
        let value_gesture_type : int32 = RuntimeType.UNDEFINED
        value_gesture_type = runtimeType(value_gesture)
        valueSerializer.writeInt8(value_gesture_type)
        if ((RuntimeType.UNDEFINED) != (value_gesture_type)) {
            const value_gesture_value  = value_gesture!
            RichEditorGesture_serializer.write(valueSerializer, value_gesture_value)
        }
        const value_urlStyle  = value.urlStyle
        let value_urlStyle_type : int32 = RuntimeType.UNDEFINED
        value_urlStyle_type = runtimeType(value_urlStyle)
        valueSerializer.writeInt8(value_urlStyle_type)
        if ((RuntimeType.UNDEFINED) != (value_urlStyle_type)) {
            const value_urlStyle_value  = value_urlStyle!
            RichEditorUrlStyle_serializer.write(valueSerializer, value_urlStyle_value)
        }
    }
    public static read(buffer: DeserializerBase): RichEditorTextSpanOptions {
        let valueDeserializer : DeserializerBase = buffer
        const offset_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let offset_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (offset_buf_runtimeType))
        {
            offset_buf = (valueDeserializer.readNumber() as number)
        }
        const offset_result : number | undefined = offset_buf
        const style_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let style_buf : RichEditorTextStyle | undefined
        if ((RuntimeType.UNDEFINED) != (style_buf_runtimeType))
        {
            style_buf = RichEditorTextStyle_serializer.read(valueDeserializer)
        }
        const style_result : RichEditorTextStyle | undefined = style_buf
        const paragraphStyle_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let paragraphStyle_buf : RichEditorParagraphStyle | undefined
        if ((RuntimeType.UNDEFINED) != (paragraphStyle_buf_runtimeType))
        {
            paragraphStyle_buf = RichEditorParagraphStyle_serializer.read(valueDeserializer)
        }
        const paragraphStyle_result : RichEditorParagraphStyle | undefined = paragraphStyle_buf
        const gesture_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let gesture_buf : RichEditorGesture | undefined
        if ((RuntimeType.UNDEFINED) != (gesture_buf_runtimeType))
        {
            gesture_buf = RichEditorGesture_serializer.read(valueDeserializer)
        }
        const gesture_result : RichEditorGesture | undefined = gesture_buf
        const urlStyle_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let urlStyle_buf : RichEditorUrlStyle | undefined
        if ((RuntimeType.UNDEFINED) != (urlStyle_buf_runtimeType))
        {
            urlStyle_buf = RichEditorUrlStyle_serializer.read(valueDeserializer)
        }
        const urlStyle_result : RichEditorUrlStyle | undefined = urlStyle_buf
        let value : RichEditorTextSpanOptions = ({offset: offset_result, style: style_result, paragraphStyle: paragraphStyle_result, gesture: gesture_result, urlStyle: urlStyle_result} as RichEditorTextSpanOptions)
        return value
    }
}
export class RichEditorTextSpanResult_serializer {
    public static write(buffer: SerializerBase, value: RichEditorTextSpanResult): void {
        let valueSerializer : SerializerBase = buffer
        const value_spanPosition  = value.spanPosition
        RichEditorSpanPosition_serializer.write(valueSerializer, value_spanPosition)
        const value_value  = value.value
        valueSerializer.writeString(value_value)
        const value_textStyle  = value.textStyle
        RichEditorTextStyleResult_serializer.write(valueSerializer, value_textStyle)
        const value_offsetInSpan  = value.offsetInSpan
        const value_offsetInSpan_0  = value_offsetInSpan[0]
        valueSerializer.writeNumber(value_offsetInSpan_0)
        const value_offsetInSpan_1  = value_offsetInSpan[1]
        valueSerializer.writeNumber(value_offsetInSpan_1)
        const value_symbolSpanStyle  = value.symbolSpanStyle
        let value_symbolSpanStyle_type : int32 = RuntimeType.UNDEFINED
        value_symbolSpanStyle_type = runtimeType(value_symbolSpanStyle)
        valueSerializer.writeInt8(value_symbolSpanStyle_type)
        if ((RuntimeType.UNDEFINED) != (value_symbolSpanStyle_type)) {
            const value_symbolSpanStyle_value  = value_symbolSpanStyle!
            RichEditorSymbolSpanStyle_serializer.write(valueSerializer, value_symbolSpanStyle_value)
        }
        const value_valueResource  = value.valueResource
        let value_valueResource_type : int32 = RuntimeType.UNDEFINED
        value_valueResource_type = runtimeType(value_valueResource)
        valueSerializer.writeInt8(value_valueResource_type)
        if ((RuntimeType.UNDEFINED) != (value_valueResource_type)) {
            const value_valueResource_value  = value_valueResource!
            Resource_serializer.write(valueSerializer, value_valueResource_value)
        }
        const value_paragraphStyle  = value.paragraphStyle
        let value_paragraphStyle_type : int32 = RuntimeType.UNDEFINED
        value_paragraphStyle_type = runtimeType(value_paragraphStyle)
        valueSerializer.writeInt8(value_paragraphStyle_type)
        if ((RuntimeType.UNDEFINED) != (value_paragraphStyle_type)) {
            const value_paragraphStyle_value  = value_paragraphStyle!
            RichEditorParagraphStyle_serializer.write(valueSerializer, value_paragraphStyle_value)
        }
        const value_previewText  = value.previewText
        let value_previewText_type : int32 = RuntimeType.UNDEFINED
        value_previewText_type = runtimeType(value_previewText)
        valueSerializer.writeInt8(value_previewText_type)
        if ((RuntimeType.UNDEFINED) != (value_previewText_type)) {
            const value_previewText_value  = value_previewText!
            valueSerializer.writeString(value_previewText_value)
        }
        const value_urlStyle  = value.urlStyle
        let value_urlStyle_type : int32 = RuntimeType.UNDEFINED
        value_urlStyle_type = runtimeType(value_urlStyle)
        valueSerializer.writeInt8(value_urlStyle_type)
        if ((RuntimeType.UNDEFINED) != (value_urlStyle_type)) {
            const value_urlStyle_value  = value_urlStyle!
            RichEditorUrlStyle_serializer.write(valueSerializer, value_urlStyle_value)
        }
    }
    public static read(buffer: DeserializerBase): RichEditorTextSpanResult {
        let valueDeserializer : DeserializerBase = buffer
        const spanPosition_result : RichEditorSpanPosition = RichEditorSpanPosition_serializer.read(valueDeserializer)
        const value_result : string = (valueDeserializer.readString() as string)
        const textStyle_result : RichEditorTextStyleResult = RichEditorTextStyleResult_serializer.read(valueDeserializer)
        const offsetInSpan_buf_value0 : number = (valueDeserializer.readNumber() as number)
        const offsetInSpan_buf_value1 : number = (valueDeserializer.readNumber() as number)
        const offsetInSpan_result : [ number, number ] = ([offsetInSpan_buf_value0, offsetInSpan_buf_value1] as [ number, number ])
        const symbolSpanStyle_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let symbolSpanStyle_buf : RichEditorSymbolSpanStyle | undefined
        if ((RuntimeType.UNDEFINED) != (symbolSpanStyle_buf_runtimeType))
        {
            symbolSpanStyle_buf = RichEditorSymbolSpanStyle_serializer.read(valueDeserializer)
        }
        const symbolSpanStyle_result : RichEditorSymbolSpanStyle | undefined = symbolSpanStyle_buf
        const valueResource_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let valueResource_buf : Resource | undefined
        if ((RuntimeType.UNDEFINED) != (valueResource_buf_runtimeType))
        {
            valueResource_buf = Resource_serializer.read(valueDeserializer)
        }
        const valueResource_result : Resource | undefined = valueResource_buf
        const paragraphStyle_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let paragraphStyle_buf : RichEditorParagraphStyle | undefined
        if ((RuntimeType.UNDEFINED) != (paragraphStyle_buf_runtimeType))
        {
            paragraphStyle_buf = RichEditorParagraphStyle_serializer.read(valueDeserializer)
        }
        const paragraphStyle_result : RichEditorParagraphStyle | undefined = paragraphStyle_buf
        const previewText_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let previewText_buf : string | undefined
        if ((RuntimeType.UNDEFINED) != (previewText_buf_runtimeType))
        {
            previewText_buf = (valueDeserializer.readString() as string)
        }
        const previewText_result : string | undefined = previewText_buf
        const urlStyle_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let urlStyle_buf : RichEditorUrlStyle | undefined
        if ((RuntimeType.UNDEFINED) != (urlStyle_buf_runtimeType))
        {
            urlStyle_buf = RichEditorUrlStyle_serializer.read(valueDeserializer)
        }
        const urlStyle_result : RichEditorUrlStyle | undefined = urlStyle_buf
        let value : RichEditorTextSpanResult = ({spanPosition: spanPosition_result, value: value_result, textStyle: textStyle_result, offsetInSpan: offsetInSpan_result, symbolSpanStyle: symbolSpanStyle_result, valueResource: valueResource_result, paragraphStyle: paragraphStyle_result, previewText: previewText_result, urlStyle: urlStyle_result} as RichEditorTextSpanResult)
        return value
    }
}
export class RichEditorControllerInternal {
    public static fromPtr(ptr: KPointer): RichEditorController {
        return new RichEditorController(ptr)
    }
}
export class RichEditorController extends RichEditorBaseController implements MaterializedBase {
    constructor(peerPtr: KPointer) {
        super(peerPtr)
    }
    static ctor(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._RichEditorController_ctor()
        return retval
    }
    constructor() {
        this(RichEditorController.ctor())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._RichEditorController_getFinalizer()
    }
    public addTextSpan(value: string, options?: RichEditorTextSpanOptions): number {
        const value_casted = value as (string)
        const options_casted = options as (RichEditorTextSpanOptions | undefined)
        return this.addTextSpan_serialize(value_casted, options_casted)
    }
    public addImageSpan(value: image.PixelMap | ResourceStr, options?: RichEditorImageSpanOptions): number {
        const value_casted = value as (image.PixelMap | ResourceStr)
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
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            RichEditorTextSpanOptions_serializer.write(thisSerializer, options_value)
        }
        const retval  = ArkUIGeneratedNativeModule._RichEditorController_addTextSpan(this.peer!.ptr, value, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private addImageSpan_serialize(value: image.PixelMap | ResourceStr, options?: RichEditorImageSpanOptions): number {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isimage_PixelMap(value, false, false)) {
            thisSerializer.writeInt8(0)
            const value_0  = value as image.PixelMap
            image_PixelMap_serializer.write(thisSerializer, value_0)
        }
        else if ((RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type)) {
            thisSerializer.writeInt8(1)
            const value_1  = value as ResourceStr
            let value_1_type : int32 = RuntimeType.UNDEFINED
            value_1_type = runtimeType(value_1)
            if (RuntimeType.STRING == value_1_type) {
                thisSerializer.writeInt8(0)
                const value_1_0  = value_1 as string
                thisSerializer.writeString(value_1_0)
            }
            else if (RuntimeType.OBJECT == value_1_type) {
                thisSerializer.writeInt8(1)
                const value_1_1  = value_1 as Resource
                Resource_serializer.write(thisSerializer, value_1_1)
            }
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            RichEditorImageSpanOptions_serializer.write(thisSerializer, options_value)
        }
        const retval  = ArkUIGeneratedNativeModule._RichEditorController_addImageSpan(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private addBuilderSpan_serialize(value: CustomBuilder, options?: RichEditorBuilderSpanOptions): number {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value))
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            RichEditorBuilderSpanOptions_serializer.write(thisSerializer, options_value)
        }
        const retval  = ArkUIGeneratedNativeModule._RichEditorController_addBuilderSpan(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private addSymbolSpan_serialize(value: Resource, options?: RichEditorSymbolSpanOptions): number {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Resource_serializer.write(thisSerializer, value)
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            RichEditorSymbolSpanOptions_serializer.write(thisSerializer, options_value)
        }
        const retval  = ArkUIGeneratedNativeModule._RichEditorController_addSymbolSpan(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private updateSpanStyle_serialize(value: RichEditorUpdateTextSpanStyleOptions | RichEditorUpdateImageSpanStyleOptions | RichEditorUpdateSymbolSpanStyleOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isRichEditorUpdateTextSpanStyleOptions(value, false, false)) {
            thisSerializer.writeInt8(0)
            const value_0  = value as RichEditorUpdateTextSpanStyleOptions
            RichEditorUpdateTextSpanStyleOptions_serializer.write(thisSerializer, value_0)
        }
        else if (TypeChecker.isRichEditorUpdateImageSpanStyleOptions(value, false)) {
            thisSerializer.writeInt8(1)
            const value_1  = value as RichEditorUpdateImageSpanStyleOptions
            RichEditorUpdateImageSpanStyleOptions_serializer.write(thisSerializer, value_1)
        }
        else if (TypeChecker.isRichEditorUpdateSymbolSpanStyleOptions(value, false)) {
            thisSerializer.writeInt8(2)
            const value_2  = value as RichEditorUpdateSymbolSpanStyleOptions
            RichEditorUpdateSymbolSpanStyleOptions_serializer.write(thisSerializer, value_2)
        }
        ArkUIGeneratedNativeModule._RichEditorController_updateSpanStyle(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private updateParagraphStyle_serialize(value: RichEditorParagraphStyleOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        RichEditorParagraphStyleOptions_serializer.write(thisSerializer, value)
        ArkUIGeneratedNativeModule._RichEditorController_updateParagraphStyle(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private deleteSpans_serialize(value?: RichEditorRange): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            RichEditorRange_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._RichEditorController_deleteSpans(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getSpans_serialize(value?: RichEditorRange): Array<RichEditorImageSpanResult | RichEditorTextSpanResult> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            RichEditorRange_serializer.write(thisSerializer, value_value)
        }
        const retval  = ArkUIGeneratedNativeModule._RichEditorController_getSpans(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<RichEditorImageSpanResult | RichEditorTextSpanResult> = new Array<RichEditorImageSpanResult | RichEditorTextSpanResult>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            const buffer_buf_selector : int32 = retvalDeserializer.readInt8()
            let buffer_buf : RichEditorImageSpanResult | RichEditorTextSpanResult | undefined
            if (buffer_buf_selector == 0) {
                buffer_buf = RichEditorImageSpanResult_serializer.read(retvalDeserializer)
            }
            else if (buffer_buf_selector == 1) {
                buffer_buf = RichEditorTextSpanResult_serializer.read(retvalDeserializer)
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
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            RichEditorRange_serializer.write(thisSerializer, value_value)
        }
        const retval  = ArkUIGeneratedNativeModule._RichEditorController_getParagraphs(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<RichEditorParagraphResult> = new Array<RichEditorParagraphResult>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = RichEditorParagraphResult_serializer.read(retvalDeserializer)
        }
        const returnResult : Array<RichEditorParagraphResult> = buffer
        return returnResult
    }
    private getSelection_serialize(): RichEditorSelection {
        const retval  = ArkUIGeneratedNativeModule._RichEditorController_getSelection(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : RichEditorSelection = RichEditorSelection_serializer.read(retvalDeserializer)
        return returnResult
    }
    private fromStyledString_serialize(value: StyledString): Array<RichEditorSpan> {
        const retval  = ArkUIGeneratedNativeModule._RichEditorController_fromStyledString(this.peer!.ptr, toPeerPtr(value))
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<RichEditorSpan> = new Array<RichEditorSpan>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            const buffer_buf_selector : int32 = retvalDeserializer.readInt8()
            let buffer_buf : RichEditorImageSpanResult | RichEditorTextSpanResult | undefined
            if (buffer_buf_selector == 0) {
                buffer_buf = RichEditorImageSpanResult_serializer.read(retvalDeserializer)
            }
            else if (buffer_buf_selector == 1) {
                buffer_buf = RichEditorTextSpanResult_serializer.read(retvalDeserializer)
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
        const thisSerializer : SerializerBase = SerializerBase.hold()
        RichEditorRange_serializer.write(thisSerializer, value)
        const retval  = ArkUIGeneratedNativeModule._RichEditorController_toStyledString(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : StyledString = StyledStringInternal.fromPtr(retval)
        return obj
    }
}
export class RichEditorStyledStringControllerInternal {
    public static fromPtr(ptr: KPointer): RichEditorStyledStringController {
        return new RichEditorStyledStringController(ptr)
    }
}
export class RichEditorStyledStringController extends RichEditorBaseController implements MaterializedBase {
    constructor(peerPtr: KPointer) {
        super(peerPtr)
    }
    static ctor(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._RichEditorStyledStringController_ctor()
        return retval
    }
    constructor() {
        this(RichEditorStyledStringController.ctor())
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
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : RichEditorRange = RichEditorRange_serializer.read(retvalDeserializer)
        return returnResult
    }
    private onContentChanged_serialize(listener: StyledStringChangedListener): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        StyledStringChangedListener_serializer.write(thisSerializer, listener)
        ArkUIGeneratedNativeModule._RichEditorStyledStringController_onContentChanged(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}

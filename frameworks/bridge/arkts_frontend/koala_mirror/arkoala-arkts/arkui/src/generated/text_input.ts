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

import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./../CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, CustomBuilder, TextDecorationOptions, InputCounterOptions, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod, TextContentControllerBase, TextContentControllerBaseInternal, SelectionOptions } from "./common"
import { ContentType } from "./text_area"
import { ResourceColor, Dimension, Font, Length, ResourceStr } from "./units"
import { TextOverflow, FontWeight, CopyOptions, TextAlign, TextContentStyle, BarState, WordBreak, LineBreakStrategy, TextHeightAdaptivePolicy, Color } from "./enums"
import { Callback_Boolean_Void } from "./navigation"
import { EditableTextOnChangeCallback, PreviewText, CaretStyle, InsertValue, DeleteValue, EditMenuOptions } from "./text_common"
import { FontStyle } from "./arkui-graphics-text"
import { Callback_String_Void } from "./grid_row"
import { PasteEvent, KeyboardOptions } from "./rich_editor"
import { CancelButtonOptions, CancelButtonSymbolOptions, Callback_InsertValue_Boolean, Callback_InsertValue_Void, Callback_DeleteValue_Boolean, Callback_DeleteValue_Void } from "./search"
import { Resource } from "./resource"
import { Callback_ResourceStr_Void } from "./select"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
export interface SubmitEvent {
    text: string
    keepEditableState(): void
}
export class SubmitEventInternal implements MaterializedBase,SubmitEvent {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get text(): string {
        return this.getText()
    }
    set text(text: string) {
        this.setText(text)
    }
    static ctor_submitevent(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SubmitEvent_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = SubmitEventInternal.ctor_submitevent()
        this.peer = new Finalizable(ctorPtr, SubmitEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SubmitEvent_getFinalizer()
    }
    public keepEditableState(): void {
        this.keepEditableState_serialize()
        return
    }
    private getText(): string {
        return this.getText_serialize()
    }
    private setText(text: string): void {
        const text_casted = text as (string)
        this.setText_serialize(text_casted)
        return
    }
    private keepEditableState_serialize(): void {
        ArkUIGeneratedNativeModule._SubmitEvent_keepEditableState(this.peer!.ptr)
    }
    private getText_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._SubmitEvent_getText(this.peer!.ptr)
        return retval
    }
    private setText_serialize(text: string): void {
        ArkUIGeneratedNativeModule._SubmitEvent_setText(this.peer!.ptr, text)
    }
    public static fromPtr(ptr: KPointer): SubmitEventInternal {
        const obj : SubmitEventInternal = new SubmitEventInternal()
        obj.peer = new Finalizable(ptr, SubmitEventInternal.getFinalizer())
        return obj
    }
}
export class ArkTextInputPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkTextInputPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._TextInput_construct(peerId, flags)
        const _peer  = new ArkTextInputPeer(_peerPtr, peerId, "TextInput", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setTextInputOptionsAttribute(value?: TextInputOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeTextInputOptions(value_value)
        }
        ArkUIGeneratedNativeModule._TextInputInterface_setTextInputOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    typeAttribute(value: InputType): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_type(this.peer.ptr, TypeChecker.InputType_ToNumeric(value))
    }
    contentTypeAttribute(value: ContentType): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_contentType(this.peer.ptr, TypeChecker.ContentType_ToNumeric(value))
    }
    placeholderColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3 as int32)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._TextInputAttribute_placeholderColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    textOverflowAttribute(value: TextOverflow): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_textOverflow(this.peer.ptr, TypeChecker.TextOverflow_ToNumeric(value))
    }
    textIndentAttribute(value: Dimension): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._TextInputAttribute_textIndent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    placeholderFontAttribute(value: Font | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeFont(value_value)
        }
        ArkUIGeneratedNativeModule._TextInputAttribute_placeholderFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enterKeyTypeAttribute(value: EnterKeyType): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_enterKeyType(this.peer.ptr, TypeChecker.EnterKeyType_ToNumeric(value))
    }
    caretColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3 as int32)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._TextInputAttribute_caretColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onEditChangedAttribute(value: ((isVisible: boolean) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_onEditChanged(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onEditChangeAttribute(value: ((isVisible: boolean) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_onEditChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSubmitAttribute(value: OnSubmitCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_onSubmit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onChangeAttribute(value: EditableTextOnChangeCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_onChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onTextSelectionChangeAttribute(value: OnTextSelectionChangeCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_onTextSelectionChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onContentScrollAttribute(value: OnContentScrollCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_onContentScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    maxLengthAttribute(value: number): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_maxLength(this.peer.ptr, value)
    }
    fontColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3 as int32)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._TextInputAttribute_fontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontSizeAttribute(value: Length): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._TextInputAttribute_fontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontStyleAttribute(value: FontStyle): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_fontStyle(this.peer.ptr, TypeChecker.FontStyle_ToNumeric(value))
    }
    fontWeightAttribute(value: number | FontWeight | string): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (TypeChecker.isFontWeight(value)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as FontWeight
            thisSerializer.writeInt32(TypeChecker.FontWeight_ToNumeric(value_1))
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        ArkUIGeneratedNativeModule._TextInputAttribute_fontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontFamilyAttribute(value: ResourceStr): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as Resource
            thisSerializer.writeResource(value_1)
        }
        ArkUIGeneratedNativeModule._TextInputAttribute_fontFamily(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onCopyAttribute(value: ((breakpoints: string) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_onCopy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onCutAttribute(value: ((breakpoints: string) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_onCut(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onPasteAttribute(value: OnPasteCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_onPaste(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    copyOptionAttribute(value: CopyOptions): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_copyOption(this.peer.ptr, TypeChecker.CopyOptions_ToNumeric(value))
    }
    showPasswordIconAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_showPasswordIcon(this.peer.ptr, value ? 1 : 0)
    }
    textAlignAttribute(value: TextAlign): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_textAlign(this.peer.ptr, TypeChecker.TextAlign_ToNumeric(value))
    }
    styleAttribute(value: TextInputStyle | TextContentStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isTextInputStyle(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as TextInputStyle
            thisSerializer.writeInt32(TypeChecker.TextInputStyle_ToNumeric(value_0))
        }
        else if (TypeChecker.isTextContentStyle(value)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as TextContentStyle
            thisSerializer.writeInt32(TypeChecker.TextContentStyle_ToNumeric(value_1))
        }
        ArkUIGeneratedNativeModule._TextInputAttribute_style(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    caretStyleAttribute(value: CaretStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeCaretStyle(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_caretStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedBackgroundColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3 as int32)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._TextInputAttribute_selectedBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    caretPositionAttribute(value: number): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_caretPosition(this.peer.ptr, value)
    }
    enableKeyboardOnFocusAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_enableKeyboardOnFocus(this.peer.ptr, value ? 1 : 0)
    }
    passwordIconAttribute(value: PasswordIcon): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writePasswordIcon(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_passwordIcon(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    showErrorAttribute(value: ResourceStr | undefined): void {
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
        ArkUIGeneratedNativeModule._TextInputAttribute_showError(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    showUnitAttribute(value: CustomBuilder): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value))
        ArkUIGeneratedNativeModule._TextInputAttribute_showUnit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    showUnderlineAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_showUnderline(this.peer.ptr, value ? 1 : 0)
    }
    underlineColorAttribute(value: ResourceColor | UnderlineColor | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if ((TypeChecker.isColor(value_value)) || (RuntimeType.NUMBER == value_value_type) || (RuntimeType.STRING == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as ResourceColor
                let value_value_0_type : int32 = RuntimeType.UNDEFINED
                value_value_0_type = runtimeType(value_value_0)
                if (TypeChecker.isColor(value_value_0)) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_value_0_0  = value_value_0 as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0_0))
                }
                else if (RuntimeType.NUMBER == value_value_0_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_value_0_1  = value_value_0 as number
                    thisSerializer.writeNumber(value_value_0_1)
                }
                else if (RuntimeType.STRING == value_value_0_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_value_0_2  = value_value_0 as string
                    thisSerializer.writeString(value_value_0_2)
                }
                else if (RuntimeType.OBJECT == value_value_0_type) {
                    thisSerializer.writeInt8(3 as int32)
                    const value_value_0_3  = value_value_0 as Resource
                    thisSerializer.writeResource(value_value_0_3)
                }
            }
            else if (TypeChecker.isUnderlineColor(value_value, false, false, false, false)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as UnderlineColor
                thisSerializer.writeUnderlineColor(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._TextInputAttribute_underlineColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectionMenuHiddenAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_selectionMenuHidden(this.peer.ptr, value ? 1 : 0)
    }
    barStateAttribute(value: BarState): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_barState(this.peer.ptr, TypeChecker.BarState_ToNumeric(value))
    }
    maxLinesAttribute(value: number): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_maxLines(this.peer.ptr, value)
    }
    wordBreakAttribute(value: WordBreak): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_wordBreak(this.peer.ptr, TypeChecker.WordBreak_ToNumeric(value))
    }
    lineBreakStrategyAttribute(value: LineBreakStrategy): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_lineBreakStrategy(this.peer.ptr, TypeChecker.LineBreakStrategy_ToNumeric(value))
    }
    cancelButton0Attribute(value: CancelButtonOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeCancelButtonOptions(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_cancelButton0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    cancelButton1Attribute(value: CancelButtonSymbolOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeCancelButtonSymbolOptions(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_cancelButton1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectAllAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_selectAll(this.peer.ptr, value ? 1 : 0)
    }
    minFontSizeAttribute(value: number | string | Resource): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._TextInputAttribute_minFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    maxFontSizeAttribute(value: number | string | Resource): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._TextInputAttribute_maxFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    heightAdaptivePolicyAttribute(value: TextHeightAdaptivePolicy): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_heightAdaptivePolicy(this.peer.ptr, TypeChecker.TextHeightAdaptivePolicy_ToNumeric(value))
    }
    enableAutoFillAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_enableAutoFill(this.peer.ptr, value ? 1 : 0)
    }
    decorationAttribute(value: TextDecorationOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeTextDecorationOptions(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_decoration(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    letterSpacingAttribute(value: number | string | Resource): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._TextInputAttribute_letterSpacing(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    lineHeightAttribute(value: number | string | Resource): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._TextInputAttribute_lineHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    passwordRulesAttribute(value: string): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_passwordRules(this.peer.ptr, value)
    }
    fontFeatureAttribute(value: string): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_fontFeature(this.peer.ptr, value)
    }
    showPasswordAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_showPassword(this.peer.ptr, value ? 1 : 0)
    }
    onSecurityStateChangeAttribute(value: ((isVisible: boolean) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_onSecurityStateChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillInsertAttribute(value: ((parameter: InsertValue) => boolean)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_onWillInsert(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDidInsertAttribute(value: ((parameter: InsertValue) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_onDidInsert(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillDeleteAttribute(value: ((parameter: DeleteValue) => boolean)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_onWillDelete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDidDeleteAttribute(value: ((parameter: DeleteValue) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_onDidDelete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    editMenuOptionsAttribute(value: EditMenuOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeEditMenuOptions(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_editMenuOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enablePreviewTextAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_enablePreviewText(this.peer.ptr, value ? 1 : 0)
    }
    enableHapticFeedbackAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_enableHapticFeedback(this.peer.ptr, value ? 1 : 0)
    }
    inputFilterAttribute(value: ResourceStr, error?: ((breakpoints: string) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as Resource
            thisSerializer.writeResource(value_1)
        }
        let error_type : int32 = RuntimeType.UNDEFINED
        error_type = runtimeType(error)
        thisSerializer.writeInt8(error_type as int32)
        if ((RuntimeType.UNDEFINED) != (error_type)) {
            const error_value  = error!
            thisSerializer.holdAndWriteCallback(error_value)
        }
        ArkUIGeneratedNativeModule._TextInputAttribute_inputFilter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    customKeyboardAttribute(value: CustomBuilder, options?: KeyboardOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value))
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeKeyboardOptions(options_value)
        }
        ArkUIGeneratedNativeModule._TextInputAttribute_customKeyboard(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    showCounterAttribute(value: boolean, options?: InputCounterOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeInputCounterOptions(options_value)
        }
        ArkUIGeneratedNativeModule._TextInputAttribute_showCounter(this.peer.ptr, value ? 1 : 0, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_textAttribute(callback: ((value: ResourceStr) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._TextInputAttribute__onChangeEvent_text(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum InputType {
    NORMAL = 0,
    Normal = 0,
    NUMBER = 1,
    Number = 1,
    PHONE_NUMBER = 2,
    PhoneNumber = 2,
    EMAIL = 3,
    Email = 3,
    PASSWORD = 4,
    Password = 4,
    NUMBER_PASSWORD = 8,
    SCREEN_LOCK_PASSWORD = 9,
    USER_NAME = 10,
    NEW_PASSWORD = 11,
    NUMBER_DECIMAL = 12,
    URL = 13
}
export enum EnterKeyType {
    GO = 2,
    Go = 2,
    SEARCH = 3,
    Search = 3,
    SEND = 4,
    Send = 4,
    NEXT = 5,
    Next = 5,
    DONE = 6,
    Done = 6,
    PREVIOUS = 7,
    NEW_LINE = 8
}
export interface UnderlineColor {
    typing?: ResourceColor | undefined;
    normal?: ResourceColor | undefined;
    error?: ResourceColor | undefined;
    disable?: ResourceColor | undefined;
}
export interface TextInputOptions {
    placeholder?: ResourceStr;
    text?: ResourceStr;
    controller?: TextInputController;
}
export enum TextInputStyle {
    DEFAULT = 0,
    Default = 0,
    INLINE = 1,
    Inline = 1
}

export interface PasswordIcon {
    onIconSrc?: string | Resource;
    offIconSrc?: string | Resource;
}
export type OnSubmitCallback = (enterKey: EnterKeyType, event: SubmitEvent) => void;
export type OnTextSelectionChangeCallback = (selectionStart: number, selectionEnd: number) => void;
export type OnContentScrollCallback = (totalOffsetX: number, totalOffsetY: number) => void;
export type OnPasteCallback = (content: string, event: PasteEvent) => void;
export interface TextInputAttribute extends CommonMethod {
    type(value: InputType): this
    contentType(value: ContentType): this
    placeholderColor(value: ResourceColor): this
    textOverflow(value: TextOverflow): this
    textIndent(value: Dimension): this
    placeholderFont(value: Font | undefined): this
    enterKeyType(value: EnterKeyType): this
    caretColor(value: ResourceColor): this
    onEditChanged(value: ((isVisible: boolean) => void)): this
    onEditChange(value: ((isVisible: boolean) => void)): this
    onSubmit(value: OnSubmitCallback): this
    onChange(value: EditableTextOnChangeCallback): this
    onTextSelectionChange(value: OnTextSelectionChangeCallback): this
    onContentScroll(value: OnContentScrollCallback): this
    maxLength(value: number): this
    fontColor(value: ResourceColor): this
    fontSize(value: Length): this
    fontStyle(value: FontStyle): this
    fontWeight(value: number | FontWeight | string): this
    fontFamily(value: ResourceStr): this
    onCopy(value: ((breakpoints: string) => void)): this
    onCut(value: ((breakpoints: string) => void)): this
    onPaste(value: OnPasteCallback): this
    copyOption(value: CopyOptions): this
    showPasswordIcon(value: boolean): this
    textAlign(value: TextAlign): this
    style(value: TextInputStyle | TextContentStyle): this
    caretStyle(value: CaretStyle): this
    selectedBackgroundColor(value: ResourceColor): this
    caretPosition(value: number): this
    enableKeyboardOnFocus(value: boolean): this
    passwordIcon(value: PasswordIcon): this
    showError(value: ResourceStr | undefined): this
    showUnit(value: CustomBuilder): this
    showUnderline(value: boolean): this
    underlineColor(value: ResourceColor | UnderlineColor | undefined): this
    selectionMenuHidden(value: boolean): this
    barState(value: BarState): this
    maxLines(value: number): this
    wordBreak(value: WordBreak): this
    lineBreakStrategy(value: LineBreakStrategy): this
    cancelButton(value: CancelButtonOptions | CancelButtonSymbolOptions): this
    selectAll(value: boolean): this
    minFontSize(value: number | string | Resource): this
    maxFontSize(value: number | string | Resource): this
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy): this
    enableAutoFill(value: boolean): this
    decoration(value: TextDecorationOptions): this
    letterSpacing(value: number | string | Resource): this
    lineHeight(value: number | string | Resource): this
    passwordRules(value: string): this
    fontFeature(value: string): this
    showPassword(value: boolean): this
    onSecurityStateChange(value: ((isVisible: boolean) => void)): this
    onWillInsert(value: ((parameter: InsertValue) => boolean)): this
    onDidInsert(value: ((parameter: InsertValue) => void)): this
    onWillDelete(value: ((parameter: DeleteValue) => boolean)): this
    onDidDelete(value: ((parameter: DeleteValue) => void)): this
    editMenuOptions(value: EditMenuOptions): this
    enablePreviewText(value: boolean): this
    enableHapticFeedback(value: boolean): this
    inputFilter(value: ResourceStr, error?: ((breakpoints: string) => void)): this
    customKeyboard(value: CustomBuilder, options?: KeyboardOptions): this
    showCounter(value: boolean, options?: InputCounterOptions): this
    _onChangeEvent_text(callback: ((value: ResourceStr) => void)): void
    attributeModifier(value: AttributeModifier<TextInputAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UITextInputAttribute extends UICommonMethod {
    /** @memo */
    type(value: InputType): this
    /** @memo */
    contentType(value: ContentType): this
    /** @memo */
    placeholderColor(value: ResourceColor): this
    /** @memo */
    textOverflow(value: TextOverflow): this
    /** @memo */
    textIndent(value: Dimension): this
    /** @memo */
    placeholderFont(value: Font | undefined): this
    /** @memo */
    enterKeyType(value: EnterKeyType): this
    /** @memo */
    caretColor(value: ResourceColor): this
    /** @memo */
    onEditChanged(value: ((isVisible: boolean) => void)): this
    /** @memo */
    onEditChange(value: ((isVisible: boolean) => void)): this
    /** @memo */
    onSubmit(value: OnSubmitCallback): this
    /** @memo */
    onChange(value: EditableTextOnChangeCallback): this
    /** @memo */
    onTextSelectionChange(value: OnTextSelectionChangeCallback): this
    /** @memo */
    onContentScroll(value: OnContentScrollCallback): this
    /** @memo */
    maxLength(value: number): this
    /** @memo */
    fontColor(value: ResourceColor): this
    /** @memo */
    fontSize(value: Length): this
    /** @memo */
    fontStyle(value: FontStyle): this
    /** @memo */
    fontWeight(value: number | FontWeight | string): this
    /** @memo */
    fontFamily(value: ResourceStr): this
    /** @memo */
    onCopy(value: ((breakpoints: string) => void)): this
    /** @memo */
    onCut(value: ((breakpoints: string) => void)): this
    /** @memo */
    onPaste(value: OnPasteCallback): this
    /** @memo */
    copyOption(value: CopyOptions): this
    /** @memo */
    showPasswordIcon(value: boolean): this
    /** @memo */
    textAlign(value: TextAlign): this
    /** @memo */
    style(value: TextInputStyle | TextContentStyle): this
    /** @memo */
    caretStyle(value: CaretStyle): this
    /** @memo */
    selectedBackgroundColor(value: ResourceColor): this
    /** @memo */
    caretPosition(value: number): this
    /** @memo */
    enableKeyboardOnFocus(value: boolean): this
    /** @memo */
    passwordIcon(value: PasswordIcon): this
    /** @memo */
    showError(value: ResourceStr | undefined): this
    /** @memo */
    showUnit(value: CustomBuilder): this
    /** @memo */
    showUnderline(value: boolean): this
    /** @memo */
    underlineColor(value: ResourceColor | UnderlineColor | undefined): this
    /** @memo */
    selectionMenuHidden(value: boolean): this
    /** @memo */
    barState(value: BarState): this
    /** @memo */
    maxLines(value: number): this
    /** @memo */
    wordBreak(value: WordBreak): this
    /** @memo */
    lineBreakStrategy(value: LineBreakStrategy): this
    /** @memo */
    cancelButton(value: CancelButtonOptions | CancelButtonSymbolOptions): this
    /** @memo */
    selectAll(value: boolean): this
    /** @memo */
    minFontSize(value: number | string | Resource): this
    /** @memo */
    maxFontSize(value: number | string | Resource): this
    /** @memo */
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy): this
    /** @memo */
    enableAutoFill(value: boolean): this
    /** @memo */
    decoration(value: TextDecorationOptions): this
    /** @memo */
    letterSpacing(value: number | string | Resource): this
    /** @memo */
    lineHeight(value: number | string | Resource): this
    /** @memo */
    passwordRules(value: string): this
    /** @memo */
    fontFeature(value: string): this
    /** @memo */
    showPassword(value: boolean): this
    /** @memo */
    onSecurityStateChange(value: ((isVisible: boolean) => void)): this
    /** @memo */
    onWillInsert(value: ((parameter: InsertValue) => boolean)): this
    /** @memo */
    onDidInsert(value: ((parameter: InsertValue) => void)): this
    /** @memo */
    onWillDelete(value: ((parameter: DeleteValue) => boolean)): this
    /** @memo */
    onDidDelete(value: ((parameter: DeleteValue) => void)): this
    /** @memo */
    editMenuOptions(value: EditMenuOptions): this
    /** @memo */
    enablePreviewText(value: boolean): this
    /** @memo */
    enableHapticFeedback(value: boolean): this
    /** @memo */
    inputFilter(value: ResourceStr, error?: ((breakpoints: string) => void)): this
    /** @memo */
    customKeyboard(value: CustomBuilder, options?: KeyboardOptions): this
    /** @memo */
    showCounter(value: boolean, options?: InputCounterOptions): this
    /** @memo */
    _onChangeEvent_text(callback: ((value: ResourceStr) => void)): void
    /** @memo */
    attributeModifier(value: AttributeModifier<TextInputAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkTextInputStyle extends ArkCommonMethodStyle implements TextInputAttribute {
    type_value?: InputType
    contentType_value?: ContentType
    placeholderColor_value?: ResourceColor
    textOverflow_value?: TextOverflow
    textIndent_value?: Dimension
    placeholderFont_value?: Font
    enterKeyType_value?: EnterKeyType
    caretColor_value?: ResourceColor
    onEditChanged_value?: ((isVisible: boolean) => void)
    onEditChange_value?: ((isVisible: boolean) => void)
    onSubmit_value?: OnSubmitCallback
    onChange_value?: EditableTextOnChangeCallback
    onTextSelectionChange_value?: OnTextSelectionChangeCallback
    onContentScroll_value?: OnContentScrollCallback
    maxLength_value?: number
    fontColor_value?: ResourceColor
    fontSize_value?: Length
    fontStyle_value?: FontStyle
    fontWeight_value?: number | FontWeight | string
    fontFamily_value?: ResourceStr
    onCopy_value?: ((breakpoints: string) => void)
    onCut_value?: ((breakpoints: string) => void)
    onPaste_value?: OnPasteCallback
    copyOption_value?: CopyOptions
    showPasswordIcon_value?: boolean
    textAlign_value?: TextAlign
    style_value?: TextInputStyle | TextContentStyle
    caretStyle_value?: CaretStyle
    selectedBackgroundColor_value?: ResourceColor
    caretPosition_value?: number
    enableKeyboardOnFocus_value?: boolean
    passwordIcon_value?: PasswordIcon
    showError_value?: ResourceStr | undefined
    showUnit_value?: CustomBuilder
    showUnderline_value?: boolean
    underlineColor_value?: ResourceColor | UnderlineColor | undefined
    selectionMenuHidden_value?: boolean
    barState_value?: BarState
    maxLines_value?: number
    wordBreak_value?: WordBreak
    lineBreakStrategy_value?: LineBreakStrategy
    cancelButton_value?: CancelButtonOptions
    selectAll_value?: boolean
    minFontSize_value?: number | string | Resource
    maxFontSize_value?: number | string | Resource
    heightAdaptivePolicy_value?: TextHeightAdaptivePolicy
    enableAutoFill_value?: boolean
    decoration_value?: TextDecorationOptions
    letterSpacing_value?: number | string | Resource
    lineHeight_value?: number | string | Resource
    passwordRules_value?: string
    fontFeature_value?: string
    showPassword_value?: boolean
    onSecurityStateChange_value?: ((isVisible: boolean) => void)
    onWillInsert_value?: ((parameter: InsertValue) => boolean)
    onDidInsert_value?: ((parameter: InsertValue) => void)
    onWillDelete_value?: ((parameter: DeleteValue) => boolean)
    onDidDelete_value?: ((parameter: DeleteValue) => void)
    editMenuOptions_value?: EditMenuOptions
    enablePreviewText_value?: boolean
    enableHapticFeedback_value?: boolean
    public type(value: InputType): this {
        return this
    }
    public contentType(value: ContentType): this {
        return this
    }
    public placeholderColor(value: ResourceColor): this {
        return this
    }
    public textOverflow(value: TextOverflow): this {
        return this
    }
    public textIndent(value: Dimension): this {
        return this
    }
    public placeholderFont(value: Font | undefined): this {
        return this
    }
    public enterKeyType(value: EnterKeyType): this {
        return this
    }
    public caretColor(value: ResourceColor): this {
        return this
    }
    public onEditChanged(value: ((isVisible: boolean) => void)): this {
        return this
    }
    public onEditChange(value: ((isVisible: boolean) => void)): this {
        return this
    }
    public onSubmit(value: OnSubmitCallback): this {
        return this
    }
    public onChange(value: EditableTextOnChangeCallback): this {
        return this
    }
    public onTextSelectionChange(value: OnTextSelectionChangeCallback): this {
        return this
    }
    public onContentScroll(value: OnContentScrollCallback): this {
        return this
    }
    public maxLength(value: number): this {
        return this
    }
    public fontColor(value: ResourceColor): this {
        return this
    }
    public fontSize(value: Length): this {
        return this
    }
    public fontStyle(value: FontStyle): this {
        return this
    }
    public fontWeight(value: number | FontWeight | string): this {
        return this
    }
    public fontFamily(value: ResourceStr): this {
        return this
    }
    public onCopy(value: ((breakpoints: string) => void)): this {
        return this
    }
    public onCut(value: ((breakpoints: string) => void)): this {
        return this
    }
    public onPaste(value: OnPasteCallback): this {
        return this
    }
    public copyOption(value: CopyOptions): this {
        return this
    }
    public showPasswordIcon(value: boolean): this {
        return this
    }
    public textAlign(value: TextAlign): this {
        return this
    }
    public style(value: TextInputStyle | TextContentStyle): this {
        return this
    }
    public caretStyle(value: CaretStyle): this {
        return this
    }
    public selectedBackgroundColor(value: ResourceColor): this {
        return this
    }
    public caretPosition(value: number): this {
        return this
    }
    public enableKeyboardOnFocus(value: boolean): this {
        return this
    }
    public passwordIcon(value: PasswordIcon): this {
        return this
    }
    public showError(value: ResourceStr | undefined): this {
        return this
    }
    public showUnit(value: CustomBuilder): this {
        return this
    }
    public showUnderline(value: boolean): this {
        return this
    }
    public underlineColor(value: ResourceColor | UnderlineColor | undefined): this {
        return this
    }
    public selectionMenuHidden(value: boolean): this {
        return this
    }
    public barState(value: BarState): this {
        return this
    }
    public maxLines(value: number): this {
        return this
    }
    public wordBreak(value: WordBreak): this {
        return this
    }
    public lineBreakStrategy(value: LineBreakStrategy): this {
        return this
    }
    public cancelButton(value: CancelButtonOptions | CancelButtonSymbolOptions): this {
        return this
    }
    public selectAll(value: boolean): this {
        return this
    }
    public minFontSize(value: number | string | Resource): this {
        return this
    }
    public maxFontSize(value: number | string | Resource): this {
        return this
    }
    public heightAdaptivePolicy(value: TextHeightAdaptivePolicy): this {
        return this
    }
    public enableAutoFill(value: boolean): this {
        return this
    }
    public decoration(value: TextDecorationOptions): this {
        return this
    }
    public letterSpacing(value: number | string | Resource): this {
        return this
    }
    public lineHeight(value: number | string | Resource): this {
        return this
    }
    public passwordRules(value: string): this {
        return this
    }
    public fontFeature(value: string): this {
        return this
    }
    public showPassword(value: boolean): this {
        return this
    }
    public onSecurityStateChange(value: ((isVisible: boolean) => void)): this {
        return this
    }
    public onWillInsert(value: ((parameter: InsertValue) => boolean)): this {
        return this
    }
    public onDidInsert(value: ((parameter: InsertValue) => void)): this {
        return this
    }
    public onWillDelete(value: ((parameter: DeleteValue) => boolean)): this {
        return this
    }
    public onDidDelete(value: ((parameter: DeleteValue) => void)): this {
        return this
    }
    public editMenuOptions(value: EditMenuOptions): this {
        return this
    }
    public enablePreviewText(value: boolean): this {
        return this
    }
    public enableHapticFeedback(value: boolean): this {
        return this
    }
    public inputFilter(value: ResourceStr, error?: ((breakpoints: string) => void)): this {
        return this
    }
    public customKeyboard(value: CustomBuilder, options?: KeyboardOptions): this {
        return this
    }
    public showCounter(value: boolean, options?: InputCounterOptions): this {
        return this
    }
    public _onChangeEvent_text(callback: ((value: ResourceStr) => void)): void {
        throw new Error("Unimplmented")
    }
    public attributeModifier(value: AttributeModifier<TextInputAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
/** @memo:stable */
export class ArkTextInputComponent extends ArkCommonMethodComponent implements UITextInputAttribute {
    getPeer(): ArkTextInputPeer {
        return (this.peer as ArkTextInputPeer)
    }
    /** @memo */
    public setTextInputOptions(value?: TextInputOptions): this {
        if (this.checkPriority("setTextInputOptions")) {
            const value_casted = value as (TextInputOptions | undefined)
            this.getPeer()?.setTextInputOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public type(value: InputType): this {
        if (this.checkPriority("type")) {
            const value_casted = value as (InputType)
            this.getPeer()?.typeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public contentType(value: ContentType): this {
        if (this.checkPriority("contentType")) {
            const value_casted = value as (ContentType)
            this.getPeer()?.contentTypeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public placeholderColor(value: ResourceColor): this {
        if (this.checkPriority("placeholderColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.placeholderColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public textOverflow(value: TextOverflow): this {
        if (this.checkPriority("textOverflow")) {
            const value_casted = value as (TextOverflow)
            this.getPeer()?.textOverflowAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public textIndent(value: Dimension): this {
        if (this.checkPriority("textIndent")) {
            const value_casted = value as (Dimension)
            this.getPeer()?.textIndentAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public placeholderFont(value: Font | undefined): this {
        if (this.checkPriority("placeholderFont")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.placeholderFontAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enterKeyType(value: EnterKeyType): this {
        if (this.checkPriority("enterKeyType")) {
            const value_casted = value as (EnterKeyType)
            this.getPeer()?.enterKeyTypeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public caretColor(value: ResourceColor): this {
        if (this.checkPriority("caretColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.caretColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onEditChanged(value: ((isVisible: boolean) => void)): this {
        if (this.checkPriority("onEditChanged")) {
            const value_casted = value as (((isVisible: boolean) => void))
            this.getPeer()?.onEditChangedAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onEditChange(value: ((isVisible: boolean) => void)): this {
        if (this.checkPriority("onEditChange")) {
            const value_casted = value as (((isVisible: boolean) => void))
            this.getPeer()?.onEditChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onSubmit(value: OnSubmitCallback): this {
        if (this.checkPriority("onSubmit")) {
            const value_casted = value as (OnSubmitCallback)
            this.getPeer()?.onSubmitAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onChange(value: EditableTextOnChangeCallback): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (EditableTextOnChangeCallback)
            this.getPeer()?.onChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onTextSelectionChange(value: OnTextSelectionChangeCallback): this {
        if (this.checkPriority("onTextSelectionChange")) {
            const value_casted = value as (OnTextSelectionChangeCallback)
            this.getPeer()?.onTextSelectionChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onContentScroll(value: OnContentScrollCallback): this {
        if (this.checkPriority("onContentScroll")) {
            const value_casted = value as (OnContentScrollCallback)
            this.getPeer()?.onContentScrollAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public maxLength(value: number): this {
        if (this.checkPriority("maxLength")) {
            const value_casted = value as (number)
            this.getPeer()?.maxLengthAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontColor(value: ResourceColor): this {
        if (this.checkPriority("fontColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.fontColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontSize(value: Length): this {
        if (this.checkPriority("fontSize")) {
            const value_casted = value as (Length)
            this.getPeer()?.fontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontStyle(value: FontStyle): this {
        if (this.checkPriority("fontStyle")) {
            const value_casted = value as (FontStyle)
            this.getPeer()?.fontStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontWeight(value: number | FontWeight | string): this {
        if (this.checkPriority("fontWeight")) {
            const value_casted = value as (number | FontWeight | string)
            this.getPeer()?.fontWeightAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontFamily(value: ResourceStr): this {
        if (this.checkPriority("fontFamily")) {
            const value_casted = value as (ResourceStr)
            this.getPeer()?.fontFamilyAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onCopy(value: ((breakpoints: string) => void)): this {
        if (this.checkPriority("onCopy")) {
            const value_casted = value as (((breakpoints: string) => void))
            this.getPeer()?.onCopyAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onCut(value: ((breakpoints: string) => void)): this {
        if (this.checkPriority("onCut")) {
            const value_casted = value as (((breakpoints: string) => void))
            this.getPeer()?.onCutAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onPaste(value: OnPasteCallback): this {
        if (this.checkPriority("onPaste")) {
            const value_casted = value as (OnPasteCallback)
            this.getPeer()?.onPasteAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public copyOption(value: CopyOptions): this {
        if (this.checkPriority("copyOption")) {
            const value_casted = value as (CopyOptions)
            this.getPeer()?.copyOptionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public showPasswordIcon(value: boolean): this {
        if (this.checkPriority("showPasswordIcon")) {
            const value_casted = value as (boolean)
            this.getPeer()?.showPasswordIconAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public textAlign(value: TextAlign): this {
        if (this.checkPriority("textAlign")) {
            const value_casted = value as (TextAlign)
            this.getPeer()?.textAlignAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public style(value: TextInputStyle | TextContentStyle): this {
        if (this.checkPriority("style")) {
            const value_casted = value as (TextInputStyle | TextContentStyle)
            this.getPeer()?.styleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public caretStyle(value: CaretStyle): this {
        if (this.checkPriority("caretStyle")) {
            const value_casted = value as (CaretStyle)
            this.getPeer()?.caretStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public selectedBackgroundColor(value: ResourceColor): this {
        if (this.checkPriority("selectedBackgroundColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.selectedBackgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public caretPosition(value: number): this {
        if (this.checkPriority("caretPosition")) {
            const value_casted = value as (number)
            this.getPeer()?.caretPositionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enableKeyboardOnFocus(value: boolean): this {
        if (this.checkPriority("enableKeyboardOnFocus")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableKeyboardOnFocusAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public passwordIcon(value: PasswordIcon): this {
        if (this.checkPriority("passwordIcon")) {
            const value_casted = value as (PasswordIcon)
            this.getPeer()?.passwordIconAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public showError(value: ResourceStr | undefined): this {
        if (this.checkPriority("showError")) {
            const value_casted = value as (ResourceStr | undefined)
            this.getPeer()?.showErrorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public showUnit(value: CustomBuilder): this {
        if (this.checkPriority("showUnit")) {
            const value_casted = value as (CustomBuilder)
            this.getPeer()?.showUnitAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public showUnderline(value: boolean): this {
        if (this.checkPriority("showUnderline")) {
            const value_casted = value as (boolean)
            this.getPeer()?.showUnderlineAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public underlineColor(value: ResourceColor | UnderlineColor | undefined): this {
        if (this.checkPriority("underlineColor")) {
            const value_casted = value as (ResourceColor | UnderlineColor | undefined)
            this.getPeer()?.underlineColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public selectionMenuHidden(value: boolean): this {
        if (this.checkPriority("selectionMenuHidden")) {
            const value_casted = value as (boolean)
            this.getPeer()?.selectionMenuHiddenAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public barState(value: BarState): this {
        if (this.checkPriority("barState")) {
            const value_casted = value as (BarState)
            this.getPeer()?.barStateAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public maxLines(value: number): this {
        if (this.checkPriority("maxLines")) {
            const value_casted = value as (number)
            this.getPeer()?.maxLinesAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public wordBreak(value: WordBreak): this {
        if (this.checkPriority("wordBreak")) {
            const value_casted = value as (WordBreak)
            this.getPeer()?.wordBreakAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public lineBreakStrategy(value: LineBreakStrategy): this {
        if (this.checkPriority("lineBreakStrategy")) {
            const value_casted = value as (LineBreakStrategy)
            this.getPeer()?.lineBreakStrategyAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public cancelButton(value: CancelButtonOptions | CancelButtonSymbolOptions): this {
        if (this.checkPriority("cancelButton")) {
            const value_type = runtimeType(value)
            if (TypeChecker.isCancelButtonOptions(value, true, true)) {
                const value_casted = value as (CancelButtonOptions)
                this.getPeer()?.cancelButton0Attribute(value_casted)
                return this
            }
            if (TypeChecker.isCancelButtonSymbolOptions(value, true, true)) {
                const value_casted = value as (CancelButtonSymbolOptions)
                this.getPeer()?.cancelButton1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public selectAll(value: boolean): this {
        if (this.checkPriority("selectAll")) {
            const value_casted = value as (boolean)
            this.getPeer()?.selectAllAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public minFontSize(value: number | string | Resource): this {
        if (this.checkPriority("minFontSize")) {
            const value_casted = value as (number | string | Resource)
            this.getPeer()?.minFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public maxFontSize(value: number | string | Resource): this {
        if (this.checkPriority("maxFontSize")) {
            const value_casted = value as (number | string | Resource)
            this.getPeer()?.maxFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public heightAdaptivePolicy(value: TextHeightAdaptivePolicy): this {
        if (this.checkPriority("heightAdaptivePolicy")) {
            const value_casted = value as (TextHeightAdaptivePolicy)
            this.getPeer()?.heightAdaptivePolicyAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enableAutoFill(value: boolean): this {
        if (this.checkPriority("enableAutoFill")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableAutoFillAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public decoration(value: TextDecorationOptions): this {
        if (this.checkPriority("decoration")) {
            const value_casted = value as (TextDecorationOptions)
            this.getPeer()?.decorationAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public letterSpacing(value: number | string | Resource): this {
        if (this.checkPriority("letterSpacing")) {
            const value_casted = value as (number | string | Resource)
            this.getPeer()?.letterSpacingAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public lineHeight(value: number | string | Resource): this {
        if (this.checkPriority("lineHeight")) {
            const value_casted = value as (number | string | Resource)
            this.getPeer()?.lineHeightAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public passwordRules(value: string): this {
        if (this.checkPriority("passwordRules")) {
            const value_casted = value as (string)
            this.getPeer()?.passwordRulesAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontFeature(value: string): this {
        if (this.checkPriority("fontFeature")) {
            const value_casted = value as (string)
            this.getPeer()?.fontFeatureAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public showPassword(value: boolean): this {
        if (this.checkPriority("showPassword")) {
            const value_casted = value as (boolean)
            this.getPeer()?.showPasswordAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onSecurityStateChange(value: ((isVisible: boolean) => void)): this {
        if (this.checkPriority("onSecurityStateChange")) {
            const value_casted = value as (((isVisible: boolean) => void))
            this.getPeer()?.onSecurityStateChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onWillInsert(value: ((parameter: InsertValue) => boolean)): this {
        if (this.checkPriority("onWillInsert")) {
            const value_casted = value as (((parameter: InsertValue) => boolean))
            this.getPeer()?.onWillInsertAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onDidInsert(value: ((parameter: InsertValue) => void)): this {
        if (this.checkPriority("onDidInsert")) {
            const value_casted = value as (((parameter: InsertValue) => void))
            this.getPeer()?.onDidInsertAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onWillDelete(value: ((parameter: DeleteValue) => boolean)): this {
        if (this.checkPriority("onWillDelete")) {
            const value_casted = value as (((parameter: DeleteValue) => boolean))
            this.getPeer()?.onWillDeleteAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onDidDelete(value: ((parameter: DeleteValue) => void)): this {
        if (this.checkPriority("onDidDelete")) {
            const value_casted = value as (((parameter: DeleteValue) => void))
            this.getPeer()?.onDidDeleteAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public editMenuOptions(value: EditMenuOptions): this {
        if (this.checkPriority("editMenuOptions")) {
            const value_casted = value as (EditMenuOptions)
            this.getPeer()?.editMenuOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enablePreviewText(value: boolean): this {
        if (this.checkPriority("enablePreviewText")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enablePreviewTextAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enableHapticFeedback(value: boolean): this {
        if (this.checkPriority("enableHapticFeedback")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableHapticFeedbackAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public inputFilter(value: ResourceStr, error?: ((breakpoints: string) => void)): this {
        if (this.checkPriority("inputFilter")) {
            const value_casted = value as (ResourceStr)
            const error_casted = error as (((breakpoints: string) => void) | undefined)
            this.getPeer()?.inputFilterAttribute(value_casted, error_casted)
            return this
        }
        return this
    }
    /** @memo */
    public customKeyboard(value: CustomBuilder, options?: KeyboardOptions): this {
        if (this.checkPriority("customKeyboard")) {
            const value_casted = value as (CustomBuilder)
            const options_casted = options as (KeyboardOptions | undefined)
            this.getPeer()?.customKeyboardAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public showCounter(value: boolean, options?: InputCounterOptions): this {
        if (this.checkPriority("showCounter")) {
            const value_casted = value as (boolean)
            const options_casted = options as (InputCounterOptions | undefined)
            this.getPeer()?.showCounterAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public _onChangeEvent_text(callback: ((value: ResourceStr) => void)): void {
        if (this.checkPriority("_onChangeEvent_text")) {
            const callback_casted = callback as (((value: ResourceStr) => void))
            this.getPeer()?._onChangeEvent_textAttribute(callback_casted)
            return
        }
        return
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<TextInputAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ArkTextInput(
    /** @memo */
    style: ((attributes: UITextInputAttribute) => void) | undefined,
    /** @memo */
    content_: (() => void) | undefined,
    value?: TextInputOptions,
): void {
    const receiver = remember(() => {
        return new ArkTextInputComponent()
    })
    NodeAttach<ArkTextInputPeer>((): ArkTextInputPeer => ArkTextInputPeer.create(receiver), (_: ArkTextInputPeer) => {
        receiver.setTextInputOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
export class TextInputControllerInternal {
    public static fromPtr(ptr: KPointer): TextInputController {
        const obj : TextInputController = new TextInputController()
        obj.peer = new Finalizable(ptr, TextInputController.getFinalizer())
        return obj
    }
}
export class TextInputController extends TextContentControllerBase implements MaterializedBase {
    static ctor_textinputcontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TextInputController_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = TextInputController.ctor_textinputcontroller()
        this.peer = new Finalizable(ctorPtr, TextInputController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextInputController_getFinalizer()
    }
    public caretPosition(value: number): void {
        const value_casted = value as (number)
        this.caretPosition_serialize(value_casted)
        return
    }
    public setTextSelection(selectionStart: number, selectionEnd: number, options?: SelectionOptions): void {
        const selectionStart_casted = selectionStart as (number)
        const selectionEnd_casted = selectionEnd as (number)
        const options_casted = options as (SelectionOptions | undefined)
        this.setTextSelection_serialize(selectionStart_casted, selectionEnd_casted, options_casted)
        return
    }
    public stopEditing(): void {
        this.stopEditing_serialize()
        return
    }
    private caretPosition_serialize(value: number): void {
        ArkUIGeneratedNativeModule._TextInputController_caretPosition(this.peer!.ptr, value)
    }
    private setTextSelection_serialize(selectionStart: number, selectionEnd: number, options?: SelectionOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeSelectionOptions(options_value)
        }
        ArkUIGeneratedNativeModule._TextInputController_setTextSelection(this.peer!.ptr, selectionStart, selectionEnd, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private stopEditing_serialize(): void {
        ArkUIGeneratedNativeModule._TextInputController_stopEditing(this.peer!.ptr)
    }
}

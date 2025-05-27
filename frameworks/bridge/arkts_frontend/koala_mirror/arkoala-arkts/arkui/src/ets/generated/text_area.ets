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

import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer, Finalizable, SerializerBase, registerCallback } from "@koalaui/interop"
import { Serializer } from "./peers/Serializer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, TextDecorationOptions, InputCounterOptions, CustomBuilder, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod, TextContentControllerBase, TextContentControllerBaseInternal, SelectionOptions } from "./common"
import { ResourceColor, Font, Length, ResourceStr, Dimension } from "./units"
import { EnterKeyType, SubmitEvent } from "./text_input"
import { TextAlign, FontWeight, TextOverflow, CopyOptions, TextContentStyle, BarState, TextHeightAdaptivePolicy, WordBreak, LineBreakStrategy, Color } from "./enums"
import { FontStyle } from "./arkui-graphics-text"
import { CaretStyle, EditableTextOnChangeCallback, PreviewText, InsertValue, DeleteValue, EditMenuOptions } from "./text_common"
import { Callback_Number_Number_Void } from "./grid"
import { Callback_Boolean_Void } from "./navigation"
import { Callback_String_Void } from "./grid_row"
import { PasteEvent, KeyboardOptions } from "./rich_editor"
import { Resource } from "./resource"
import { LengthMetrics } from "./arkui-graphics"
import { Callback_InsertValue_Boolean, Callback_InsertValue_Void, Callback_DeleteValue_Boolean, Callback_DeleteValue_Void } from "./search"
import { Callback_ResourceStr_Void } from "./select"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Deserializer } from "./peers/Deserializer"
export class ArkTextAreaPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkTextAreaPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._TextArea_construct(peerId, flags)
        const _peer  = new ArkTextAreaPeer(_peerPtr, peerId, "TextArea", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setTextAreaOptionsAttribute(value?: TextAreaOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeTextAreaOptions(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaInterface_setTextAreaOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    placeholderColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_placeholderColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    placeholderFontAttribute(value: Font): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeFont(value)
        ArkUIGeneratedNativeModule._TextAreaAttribute_placeholderFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enterKeyTypeAttribute(value: EnterKeyType): void {
        ArkUIGeneratedNativeModule._TextAreaAttribute_enterKeyType(this.peer.ptr, TypeChecker.EnterKeyType_ToNumeric(value))
    }
    textAlignAttribute(value: TextAlign): void {
        ArkUIGeneratedNativeModule._TextAreaAttribute_textAlign(this.peer.ptr, TypeChecker.TextAlign_ToNumeric(value))
    }
    caretColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_caretColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_fontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontSizeAttribute(value: Length): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_fontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontStyleAttribute(value: FontStyle): void {
        ArkUIGeneratedNativeModule._TextAreaAttribute_fontStyle(this.peer.ptr, TypeChecker.FontStyle_ToNumeric(value))
    }
    fontWeightAttribute(value: number | FontWeight | string): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (TypeChecker.isFontWeight(value)) {
            thisSerializer.writeInt8(1)
            const value_1  = value as FontWeight
            thisSerializer.writeInt32(TypeChecker.FontWeight_ToNumeric(value_1))
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_fontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontFamilyAttribute(value: ResourceStr): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as Resource
            thisSerializer.writeResource(value_1)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_fontFamily(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    textOverflowAttribute(value: TextOverflow): void {
        ArkUIGeneratedNativeModule._TextAreaAttribute_textOverflow(this.peer.ptr, TypeChecker.TextOverflow_ToNumeric(value))
    }
    textIndentAttribute(value: Dimension): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_textIndent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    caretStyleAttribute(value: CaretStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeCaretStyle(value)
        ArkUIGeneratedNativeModule._TextAreaAttribute_caretStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedBackgroundColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_selectedBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSubmit0Attribute(value: ((enterKey: EnterKeyType) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextAreaAttribute_onSubmit0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSubmit1Attribute(value: TextAreaSubmitCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextAreaAttribute_onSubmit1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onChangeAttribute(value: EditableTextOnChangeCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextAreaAttribute_onChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onTextSelectionChangeAttribute(value: ((first: number,last: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextAreaAttribute_onTextSelectionChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onContentScrollAttribute(value: ((first: number,last: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextAreaAttribute_onContentScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onEditChangeAttribute(value: ((isVisible: boolean) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextAreaAttribute_onEditChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onCopyAttribute(value: ((breakpoints: string) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextAreaAttribute_onCopy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onCutAttribute(value: ((breakpoints: string) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextAreaAttribute_onCut(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onPasteAttribute(value: ((value: string,event: PasteEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextAreaAttribute_onPaste(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    copyOptionAttribute(value: CopyOptions): void {
        ArkUIGeneratedNativeModule._TextAreaAttribute_copyOption(this.peer.ptr, TypeChecker.CopyOptions_ToNumeric(value))
    }
    enableKeyboardOnFocusAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TextAreaAttribute_enableKeyboardOnFocus(this.peer.ptr, value ? 1 : 0)
    }
    maxLengthAttribute(value: number): void {
        ArkUIGeneratedNativeModule._TextAreaAttribute_maxLength(this.peer.ptr, value)
    }
    styleAttribute(value: TextContentStyle): void {
        ArkUIGeneratedNativeModule._TextAreaAttribute_style(this.peer.ptr, TypeChecker.TextContentStyle_ToNumeric(value))
    }
    barStateAttribute(value: BarState): void {
        ArkUIGeneratedNativeModule._TextAreaAttribute_barState(this.peer.ptr, TypeChecker.BarState_ToNumeric(value))
    }
    selectionMenuHiddenAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TextAreaAttribute_selectionMenuHidden(this.peer.ptr, value ? 1 : 0)
    }
    minFontSizeAttribute(value: number | string | Resource): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_minFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    maxFontSizeAttribute(value: number | string | Resource): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_maxFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    heightAdaptivePolicyAttribute(value: TextHeightAdaptivePolicy): void {
        ArkUIGeneratedNativeModule._TextAreaAttribute_heightAdaptivePolicy(this.peer.ptr, TypeChecker.TextHeightAdaptivePolicy_ToNumeric(value))
    }
    maxLinesAttribute(value: number): void {
        ArkUIGeneratedNativeModule._TextAreaAttribute_maxLines(this.peer.ptr, value)
    }
    wordBreakAttribute(value: WordBreak): void {
        ArkUIGeneratedNativeModule._TextAreaAttribute_wordBreak(this.peer.ptr, TypeChecker.WordBreak_ToNumeric(value))
    }
    lineBreakStrategyAttribute(value: LineBreakStrategy): void {
        ArkUIGeneratedNativeModule._TextAreaAttribute_lineBreakStrategy(this.peer.ptr, TypeChecker.LineBreakStrategy_ToNumeric(value))
    }
    decorationAttribute(value: TextDecorationOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeTextDecorationOptions(value)
        ArkUIGeneratedNativeModule._TextAreaAttribute_decoration(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    letterSpacingAttribute(value: number | string | Resource): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_letterSpacing(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    lineSpacingAttribute(value: LengthMetrics): void {
        ArkUIGeneratedNativeModule._TextAreaAttribute_lineSpacing(this.peer.ptr, toPeerPtr(value))
    }
    lineHeightAttribute(value: number | string | Resource): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_lineHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    typeAttribute(value: TextAreaType): void {
        ArkUIGeneratedNativeModule._TextAreaAttribute_type(this.peer.ptr, TypeChecker.TextAreaType_ToNumeric(value))
    }
    enableAutoFillAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TextAreaAttribute_enableAutoFill(this.peer.ptr, value ? 1 : 0)
    }
    contentTypeAttribute(value: ContentType): void {
        ArkUIGeneratedNativeModule._TextAreaAttribute_contentType(this.peer.ptr, TypeChecker.ContentType_ToNumeric(value))
    }
    fontFeatureAttribute(value: string): void {
        ArkUIGeneratedNativeModule._TextAreaAttribute_fontFeature(this.peer.ptr, value)
    }
    onWillInsertAttribute(value: ((parameter: InsertValue) => boolean)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextAreaAttribute_onWillInsert(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDidInsertAttribute(value: ((parameter: InsertValue) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextAreaAttribute_onDidInsert(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillDeleteAttribute(value: ((parameter: DeleteValue) => boolean)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextAreaAttribute_onWillDelete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDidDeleteAttribute(value: ((parameter: DeleteValue) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextAreaAttribute_onDidDelete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    editMenuOptionsAttribute(value: EditMenuOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeEditMenuOptions(value)
        ArkUIGeneratedNativeModule._TextAreaAttribute_editMenuOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enablePreviewTextAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TextAreaAttribute_enablePreviewText(this.peer.ptr, value ? 1 : 0)
    }
    enableHapticFeedbackAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TextAreaAttribute_enableHapticFeedback(this.peer.ptr, value ? 1 : 0)
    }
    inputFilterAttribute(value: ResourceStr, error?: ((breakpoints: string) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as Resource
            thisSerializer.writeResource(value_1)
        }
        let error_type : int32 = RuntimeType.UNDEFINED
        error_type = runtimeType(error)
        thisSerializer.writeInt8(error_type)
        if ((RuntimeType.UNDEFINED) != (error_type)) {
            const error_value  = error!
            thisSerializer.holdAndWriteCallback(error_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_inputFilter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    showCounterAttribute(value: boolean, options?: InputCounterOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeInputCounterOptions(options_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_showCounter(this.peer.ptr, value ? 1 : 0, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    customKeyboardAttribute(value: CustomBuilder, options?: KeyboardOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value))
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeKeyboardOptions(options_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_customKeyboard(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_textAttribute(callback: ((value: ResourceStr) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._TextAreaAttribute__onChangeEvent_text(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface TextAreaOptions {
    placeholder?: ResourceStr;
    text?: ResourceStr;
    controller?: TextAreaController;
}

export enum TextAreaType {
    NORMAL = 0,
    NUMBER = 2,
    PHONE_NUMBER = 3,
    EMAIL = 5,
    NUMBER_DECIMAL = 12,
    URL = 13
}
export enum ContentType {
    USER_NAME = 0,
    PASSWORD = 1,
    NEW_PASSWORD = 2,
    FULL_STREET_ADDRESS = 3,
    HOUSE_NUMBER = 4,
    DISTRICT_ADDRESS = 5,
    CITY_ADDRESS = 6,
    PROVINCE_ADDRESS = 7,
    COUNTRY_ADDRESS = 8,
    PERSON_FULL_NAME = 9,
    PERSON_LAST_NAME = 10,
    PERSON_FIRST_NAME = 11,
    PHONE_NUMBER = 12,
    PHONE_COUNTRY_CODE = 13,
    FULL_PHONE_NUMBER = 14,
    EMAIL_ADDRESS = 15,
    BANK_CARD_NUMBER = 16,
    ID_CARD_NUMBER = 17,
    NICKNAME = 23,
    DETAIL_INFO_WITHOUT_STREET = 24,
    FORMAT_ADDRESS = 25
}
export type TextAreaSubmitCallback = (enterKeyType: EnterKeyType, event?: SubmitEvent) => void;
export type Callback_EnterKeyType_Void = (enterKey: EnterKeyType) => void;
export type Callback_String_PasteEvent_Void = (value: string, event: PasteEvent) => void;
export interface TextAreaAttribute extends CommonMethod {
    placeholderColor(value: ResourceColor): this
    placeholderFont(value: Font): this
    enterKeyType(value: EnterKeyType): this
    textAlign(value: TextAlign): this
    caretColor(value: ResourceColor): this
    fontColor(value: ResourceColor): this
    fontSize(value: Length): this
    fontStyle(value: FontStyle): this
    fontWeight(value: number | FontWeight | string): this
    fontFamily(value: ResourceStr): this
    textOverflow(value: TextOverflow): this
    textIndent(value: Dimension): this
    caretStyle(value: CaretStyle): this
    selectedBackgroundColor(value: ResourceColor): this
    onSubmit(value: ((enterKey: EnterKeyType) => void) | TextAreaSubmitCallback): this
    onChange(value: EditableTextOnChangeCallback): this
    onTextSelectionChange(value: ((first: number,last: number) => void)): this
    onContentScroll(value: ((first: number,last: number) => void)): this
    onEditChange(value: ((isVisible: boolean) => void)): this
    onCopy(value: ((breakpoints: string) => void)): this
    onCut(value: ((breakpoints: string) => void)): this
    onPaste(value: ((value: string,event: PasteEvent) => void)): this
    copyOption(value: CopyOptions): this
    enableKeyboardOnFocus(value: boolean): this
    maxLength(value: number): this
    style(value: TextContentStyle): this
    barState(value: BarState): this
    selectionMenuHidden(value: boolean): this
    minFontSize(value: number | string | Resource): this
    maxFontSize(value: number | string | Resource): this
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy): this
    maxLines(value: number): this
    wordBreak(value: WordBreak): this
    lineBreakStrategy(value: LineBreakStrategy): this
    decoration(value: TextDecorationOptions): this
    letterSpacing(value: number | string | Resource): this
    lineSpacing(value: LengthMetrics): this
    lineHeight(value: number | string | Resource): this
    type(value: TextAreaType): this
    enableAutoFill(value: boolean): this
    contentType(value: ContentType): this
    fontFeature(value: string): this
    onWillInsert(value: ((parameter: InsertValue) => boolean)): this
    onDidInsert(value: ((parameter: InsertValue) => void)): this
    onWillDelete(value: ((parameter: DeleteValue) => boolean)): this
    onDidDelete(value: ((parameter: DeleteValue) => void)): this
    editMenuOptions(value: EditMenuOptions): this
    enablePreviewText(value: boolean): this
    enableHapticFeedback(value: boolean): this
    inputFilter(value: ResourceStr, error?: ((breakpoints: string) => void)): this
    showCounter(value: boolean, options?: InputCounterOptions): this
    customKeyboard(value: CustomBuilder, options?: KeyboardOptions): this
    _onChangeEvent_text(callback: ((value: ResourceStr) => void)): void
    attributeModifier(value: AttributeModifier<TextAreaAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UITextAreaAttribute extends UICommonMethod {
    @memo
    placeholderColor(value: ResourceColor): this
    @memo
    placeholderFont(value: Font): this
    @memo
    enterKeyType(value: EnterKeyType): this
    @memo
    textAlign(value: TextAlign): this
    @memo
    caretColor(value: ResourceColor): this
    @memo
    fontColor(value: ResourceColor): this
    @memo
    fontSize(value: Length): this
    @memo
    fontStyle(value: FontStyle): this
    @memo
    fontWeight(value: number | FontWeight | string): this
    @memo
    fontFamily(value: ResourceStr): this
    @memo
    textOverflow(value: TextOverflow): this
    @memo
    textIndent(value: Dimension): this
    @memo
    caretStyle(value: CaretStyle): this
    @memo
    selectedBackgroundColor(value: ResourceColor): this
    @memo
    onSubmit(value: ((enterKey: EnterKeyType) => void) | TextAreaSubmitCallback): this
    @memo
    onChange(value: EditableTextOnChangeCallback): this
    @memo
    onTextSelectionChange(value: ((first: number,last: number) => void)): this
    @memo
    onContentScroll(value: ((first: number,last: number) => void)): this
    @memo
    onEditChange(value: ((isVisible: boolean) => void)): this
    @memo
    onCopy(value: ((breakpoints: string) => void)): this
    @memo
    onCut(value: ((breakpoints: string) => void)): this
    @memo
    onPaste(value: ((value: string,event: PasteEvent) => void)): this
    @memo
    copyOption(value: CopyOptions): this
    @memo
    enableKeyboardOnFocus(value: boolean): this
    @memo
    maxLength(value: number): this
    @memo
    style(value: TextContentStyle): this
    @memo
    barState(value: BarState): this
    @memo
    selectionMenuHidden(value: boolean): this
    @memo
    minFontSize(value: number | string | Resource): this
    @memo
    maxFontSize(value: number | string | Resource): this
    @memo
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy): this
    @memo
    maxLines(value: number): this
    @memo
    wordBreak(value: WordBreak): this
    @memo
    lineBreakStrategy(value: LineBreakStrategy): this
    @memo
    decoration(value: TextDecorationOptions): this
    @memo
    letterSpacing(value: number | string | Resource): this
    @memo
    lineSpacing(value: LengthMetrics): this
    @memo
    lineHeight(value: number | string | Resource): this
    @memo
    type(value: TextAreaType): this
    @memo
    enableAutoFill(value: boolean): this
    @memo
    contentType(value: ContentType): this
    @memo
    fontFeature(value: string): this
    @memo
    onWillInsert(value: ((parameter: InsertValue) => boolean)): this
    @memo
    onDidInsert(value: ((parameter: InsertValue) => void)): this
    @memo
    onWillDelete(value: ((parameter: DeleteValue) => boolean)): this
    @memo
    onDidDelete(value: ((parameter: DeleteValue) => void)): this
    @memo
    editMenuOptions(value: EditMenuOptions): this
    @memo
    enablePreviewText(value: boolean): this
    @memo
    enableHapticFeedback(value: boolean): this
    @memo
    inputFilter(value: ResourceStr, error?: ((breakpoints: string) => void)): this
    @memo
    showCounter(value: boolean, options?: InputCounterOptions): this
    @memo
    customKeyboard(value: CustomBuilder, options?: KeyboardOptions): this
    @memo
    _onChangeEvent_text(callback: ((value: ResourceStr) => void)): void
    @memo
    attributeModifier(value: AttributeModifier<TextAreaAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkTextAreaStyle extends ArkCommonMethodStyle implements TextAreaAttribute {
    placeholderColor_value?: ResourceColor
    placeholderFont_value?: Font
    enterKeyType_value?: EnterKeyType
    textAlign_value?: TextAlign
    caretColor_value?: ResourceColor
    fontColor_value?: ResourceColor
    fontSize_value?: Length
    fontStyle_value?: FontStyle
    fontWeight_value?: number | FontWeight | string
    fontFamily_value?: ResourceStr
    textOverflow_value?: TextOverflow
    textIndent_value?: Dimension
    caretStyle_value?: CaretStyle
    selectedBackgroundColor_value?: ResourceColor
    onSubmit_value?: ((enterKey: EnterKeyType) => void)
    onChange_value?: EditableTextOnChangeCallback
    onTextSelectionChange_value?: ((first: number,last: number) => void)
    onContentScroll_value?: ((first: number,last: number) => void)
    onEditChange_value?: ((isVisible: boolean) => void)
    onCopy_value?: ((breakpoints: string) => void)
    onCut_value?: ((breakpoints: string) => void)
    onPaste_value?: ((value: string,event: PasteEvent) => void)
    copyOption_value?: CopyOptions
    enableKeyboardOnFocus_value?: boolean
    maxLength_value?: number
    style_value?: TextContentStyle
    barState_value?: BarState
    selectionMenuHidden_value?: boolean
    minFontSize_value?: number | string | Resource
    maxFontSize_value?: number | string | Resource
    heightAdaptivePolicy_value?: TextHeightAdaptivePolicy
    maxLines_value?: number
    wordBreak_value?: WordBreak
    lineBreakStrategy_value?: LineBreakStrategy
    decoration_value?: TextDecorationOptions
    letterSpacing_value?: number | string | Resource
    lineSpacing_value?: LengthMetrics
    lineHeight_value?: number | string | Resource
    type_value?: TextAreaType
    enableAutoFill_value?: boolean
    contentType_value?: ContentType
    fontFeature_value?: string
    onWillInsert_value?: ((parameter: InsertValue) => boolean)
    onDidInsert_value?: ((parameter: InsertValue) => void)
    onWillDelete_value?: ((parameter: DeleteValue) => boolean)
    onDidDelete_value?: ((parameter: DeleteValue) => void)
    editMenuOptions_value?: EditMenuOptions
    enablePreviewText_value?: boolean
    enableHapticFeedback_value?: boolean
    public placeholderColor(value: ResourceColor): this {
        return this
    }
    public placeholderFont(value: Font): this {
        return this
    }
    public enterKeyType(value: EnterKeyType): this {
        return this
    }
    public textAlign(value: TextAlign): this {
        return this
    }
    public caretColor(value: ResourceColor): this {
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
    public textOverflow(value: TextOverflow): this {
        return this
    }
    public textIndent(value: Dimension): this {
        return this
    }
    public caretStyle(value: CaretStyle): this {
        return this
    }
    public selectedBackgroundColor(value: ResourceColor): this {
        return this
    }
    public onSubmit(value: ((enterKey: EnterKeyType) => void) | TextAreaSubmitCallback): this {
        return this
    }
    public onChange(value: EditableTextOnChangeCallback): this {
        return this
    }
    public onTextSelectionChange(value: ((first: number,last: number) => void)): this {
        return this
    }
    public onContentScroll(value: ((first: number,last: number) => void)): this {
        return this
    }
    public onEditChange(value: ((isVisible: boolean) => void)): this {
        return this
    }
    public onCopy(value: ((breakpoints: string) => void)): this {
        return this
    }
    public onCut(value: ((breakpoints: string) => void)): this {
        return this
    }
    public onPaste(value: ((value: string,event: PasteEvent) => void)): this {
        return this
    }
    public copyOption(value: CopyOptions): this {
        return this
    }
    public enableKeyboardOnFocus(value: boolean): this {
        return this
    }
    public maxLength(value: number): this {
        return this
    }
    public style(value: TextContentStyle): this {
        return this
    }
    public barState(value: BarState): this {
        return this
    }
    public selectionMenuHidden(value: boolean): this {
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
    public maxLines(value: number): this {
        return this
    }
    public wordBreak(value: WordBreak): this {
        return this
    }
    public lineBreakStrategy(value: LineBreakStrategy): this {
        return this
    }
    public decoration(value: TextDecorationOptions): this {
        return this
    }
    public letterSpacing(value: number | string | Resource): this {
        return this
    }
    public lineSpacing(value: LengthMetrics): this {
        return this
    }
    public lineHeight(value: number | string | Resource): this {
        return this
    }
    public type(value: TextAreaType): this {
        return this
    }
    public enableAutoFill(value: boolean): this {
        return this
    }
    public contentType(value: ContentType): this {
        return this
    }
    public fontFeature(value: string): this {
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
    public showCounter(value: boolean, options?: InputCounterOptions): this {
        return this
    }
    public customKeyboard(value: CustomBuilder, options?: KeyboardOptions): this {
        return this
    }
    public _onChangeEvent_text(callback: ((value: ResourceStr) => void)): void {
        throw new Error("Unimplmented")
    }
    public attributeModifier(value: AttributeModifier<TextAreaAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
@memo_stable
export class ArkTextAreaComponent extends ArkCommonMethodComponent implements UITextAreaAttribute {
    getPeer(): ArkTextAreaPeer {
        return (this.peer as ArkTextAreaPeer)
    }
    @memo
    public setTextAreaOptions(value?: TextAreaOptions): this {
        if (this.checkPriority("setTextAreaOptions")) {
            const value_casted = value as (TextAreaOptions | undefined)
            this.getPeer()?.setTextAreaOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public placeholderColor(value: ResourceColor): this {
        if (this.checkPriority("placeholderColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.placeholderColorAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public placeholderFont(value: Font): this {
        if (this.checkPriority("placeholderFont")) {
            const value_casted = value as (Font)
            this.getPeer()?.placeholderFontAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public enterKeyType(value: EnterKeyType): this {
        if (this.checkPriority("enterKeyType")) {
            const value_casted = value as (EnterKeyType)
            this.getPeer()?.enterKeyTypeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public textAlign(value: TextAlign): this {
        if (this.checkPriority("textAlign")) {
            const value_casted = value as (TextAlign)
            this.getPeer()?.textAlignAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public caretColor(value: ResourceColor): this {
        if (this.checkPriority("caretColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.caretColorAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public fontColor(value: ResourceColor): this {
        if (this.checkPriority("fontColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.fontColorAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public fontSize(value: Length): this {
        if (this.checkPriority("fontSize")) {
            const value_casted = value as (Length)
            this.getPeer()?.fontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public fontStyle(value: FontStyle): this {
        if (this.checkPriority("fontStyle")) {
            const value_casted = value as (FontStyle)
            this.getPeer()?.fontStyleAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public fontWeight(value: number | FontWeight | string): this {
        if (this.checkPriority("fontWeight")) {
            const value_casted = value as (number | FontWeight | string)
            this.getPeer()?.fontWeightAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public fontFamily(value: ResourceStr): this {
        if (this.checkPriority("fontFamily")) {
            const value_casted = value as (ResourceStr)
            this.getPeer()?.fontFamilyAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public textOverflow(value: TextOverflow): this {
        if (this.checkPriority("textOverflow")) {
            const value_casted = value as (TextOverflow)
            this.getPeer()?.textOverflowAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public textIndent(value: Dimension): this {
        if (this.checkPriority("textIndent")) {
            const value_casted = value as (Dimension)
            this.getPeer()?.textIndentAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public caretStyle(value: CaretStyle): this {
        if (this.checkPriority("caretStyle")) {
            const value_casted = value as (CaretStyle)
            this.getPeer()?.caretStyleAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public selectedBackgroundColor(value: ResourceColor): this {
        if (this.checkPriority("selectedBackgroundColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.selectedBackgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onSubmit(value: ((enterKey: EnterKeyType) => void) | TextAreaSubmitCallback): this {
        if (this.checkPriority("onSubmit")) {
            const value_type = runtimeType(value)
            if (RuntimeType.FUNCTION == value_type) {
                const value_casted = value as (((enterKey: EnterKeyType) => void))
                this.getPeer()?.onSubmit0Attribute(value_casted)
                return this
            }
            if (RuntimeType.FUNCTION == value_type) {
                const value_casted = value as (TextAreaSubmitCallback)
                this.getPeer()?.onSubmit1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    @memo
    public onChange(value: EditableTextOnChangeCallback): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (EditableTextOnChangeCallback)
            this.getPeer()?.onChangeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onTextSelectionChange(value: ((first: number,last: number) => void)): this {
        if (this.checkPriority("onTextSelectionChange")) {
            const value_casted = value as (((first: number,last: number) => void))
            this.getPeer()?.onTextSelectionChangeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onContentScroll(value: ((first: number,last: number) => void)): this {
        if (this.checkPriority("onContentScroll")) {
            const value_casted = value as (((first: number,last: number) => void))
            this.getPeer()?.onContentScrollAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onEditChange(value: ((isVisible: boolean) => void)): this {
        if (this.checkPriority("onEditChange")) {
            const value_casted = value as (((isVisible: boolean) => void))
            this.getPeer()?.onEditChangeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onCopy(value: ((breakpoints: string) => void)): this {
        if (this.checkPriority("onCopy")) {
            const value_casted = value as (((breakpoints: string) => void))
            this.getPeer()?.onCopyAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onCut(value: ((breakpoints: string) => void)): this {
        if (this.checkPriority("onCut")) {
            const value_casted = value as (((breakpoints: string) => void))
            this.getPeer()?.onCutAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onPaste(value: ((value: string,event: PasteEvent) => void)): this {
        if (this.checkPriority("onPaste")) {
            const value_casted = value as (((value: string,event: PasteEvent) => void))
            this.getPeer()?.onPasteAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public copyOption(value: CopyOptions): this {
        if (this.checkPriority("copyOption")) {
            const value_casted = value as (CopyOptions)
            this.getPeer()?.copyOptionAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public enableKeyboardOnFocus(value: boolean): this {
        if (this.checkPriority("enableKeyboardOnFocus")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableKeyboardOnFocusAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public maxLength(value: number): this {
        if (this.checkPriority("maxLength")) {
            const value_casted = value as (number)
            this.getPeer()?.maxLengthAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public style(value: TextContentStyle): this {
        if (this.checkPriority("style")) {
            const value_casted = value as (TextContentStyle)
            this.getPeer()?.styleAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public barState(value: BarState): this {
        if (this.checkPriority("barState")) {
            const value_casted = value as (BarState)
            this.getPeer()?.barStateAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public selectionMenuHidden(value: boolean): this {
        if (this.checkPriority("selectionMenuHidden")) {
            const value_casted = value as (boolean)
            this.getPeer()?.selectionMenuHiddenAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public minFontSize(value: number | string | Resource): this {
        if (this.checkPriority("minFontSize")) {
            const value_casted = value as (number | string | Resource)
            this.getPeer()?.minFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public maxFontSize(value: number | string | Resource): this {
        if (this.checkPriority("maxFontSize")) {
            const value_casted = value as (number | string | Resource)
            this.getPeer()?.maxFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public heightAdaptivePolicy(value: TextHeightAdaptivePolicy): this {
        if (this.checkPriority("heightAdaptivePolicy")) {
            const value_casted = value as (TextHeightAdaptivePolicy)
            this.getPeer()?.heightAdaptivePolicyAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public maxLines(value: number): this {
        if (this.checkPriority("maxLines")) {
            const value_casted = value as (number)
            this.getPeer()?.maxLinesAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public wordBreak(value: WordBreak): this {
        if (this.checkPriority("wordBreak")) {
            const value_casted = value as (WordBreak)
            this.getPeer()?.wordBreakAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public lineBreakStrategy(value: LineBreakStrategy): this {
        if (this.checkPriority("lineBreakStrategy")) {
            const value_casted = value as (LineBreakStrategy)
            this.getPeer()?.lineBreakStrategyAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public decoration(value: TextDecorationOptions): this {
        if (this.checkPriority("decoration")) {
            const value_casted = value as (TextDecorationOptions)
            this.getPeer()?.decorationAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public letterSpacing(value: number | string | Resource): this {
        if (this.checkPriority("letterSpacing")) {
            const value_casted = value as (number | string | Resource)
            this.getPeer()?.letterSpacingAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public lineSpacing(value: LengthMetrics): this {
        if (this.checkPriority("lineSpacing")) {
            const value_casted = value as (LengthMetrics)
            this.getPeer()?.lineSpacingAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public lineHeight(value: number | string | Resource): this {
        if (this.checkPriority("lineHeight")) {
            const value_casted = value as (number | string | Resource)
            this.getPeer()?.lineHeightAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public type(value: TextAreaType): this {
        if (this.checkPriority("type")) {
            const value_casted = value as (TextAreaType)
            this.getPeer()?.typeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public enableAutoFill(value: boolean): this {
        if (this.checkPriority("enableAutoFill")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableAutoFillAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public contentType(value: ContentType): this {
        if (this.checkPriority("contentType")) {
            const value_casted = value as (ContentType)
            this.getPeer()?.contentTypeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public fontFeature(value: string): this {
        if (this.checkPriority("fontFeature")) {
            const value_casted = value as (string)
            this.getPeer()?.fontFeatureAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onWillInsert(value: ((parameter: InsertValue) => boolean)): this {
        if (this.checkPriority("onWillInsert")) {
            const value_casted = value as (((parameter: InsertValue) => boolean))
            this.getPeer()?.onWillInsertAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onDidInsert(value: ((parameter: InsertValue) => void)): this {
        if (this.checkPriority("onDidInsert")) {
            const value_casted = value as (((parameter: InsertValue) => void))
            this.getPeer()?.onDidInsertAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onWillDelete(value: ((parameter: DeleteValue) => boolean)): this {
        if (this.checkPriority("onWillDelete")) {
            const value_casted = value as (((parameter: DeleteValue) => boolean))
            this.getPeer()?.onWillDeleteAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onDidDelete(value: ((parameter: DeleteValue) => void)): this {
        if (this.checkPriority("onDidDelete")) {
            const value_casted = value as (((parameter: DeleteValue) => void))
            this.getPeer()?.onDidDeleteAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public editMenuOptions(value: EditMenuOptions): this {
        if (this.checkPriority("editMenuOptions")) {
            const value_casted = value as (EditMenuOptions)
            this.getPeer()?.editMenuOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public enablePreviewText(value: boolean): this {
        if (this.checkPriority("enablePreviewText")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enablePreviewTextAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public enableHapticFeedback(value: boolean): this {
        if (this.checkPriority("enableHapticFeedback")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableHapticFeedbackAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public inputFilter(value: ResourceStr, error?: ((breakpoints: string) => void)): this {
        if (this.checkPriority("inputFilter")) {
            const value_casted = value as (ResourceStr)
            const error_casted = error as (((breakpoints: string) => void) | undefined)
            this.getPeer()?.inputFilterAttribute(value_casted, error_casted)
            return this
        }
        return this
    }
    @memo
    public showCounter(value: boolean, options?: InputCounterOptions): this {
        if (this.checkPriority("showCounter")) {
            const value_casted = value as (boolean)
            const options_casted = options as (InputCounterOptions | undefined)
            this.getPeer()?.showCounterAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    @memo
    public customKeyboard(value: CustomBuilder, options?: KeyboardOptions): this {
        if (this.checkPriority("customKeyboard")) {
            const value_casted = value as (CustomBuilder)
            const options_casted = options as (KeyboardOptions | undefined)
            this.getPeer()?.customKeyboardAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    @memo
    public _onChangeEvent_text(callback: ((value: ResourceStr) => void)): void {
        if (this.checkPriority("_onChangeEvent_text")) {
            const callback_casted = callback as (((value: ResourceStr) => void))
            this.getPeer()?._onChangeEvent_textAttribute(callback_casted)
            return
        }
        return
    }
    @memo
    public attributeModifier(value: AttributeModifier<TextAreaAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
@memo
@BuilderLambda("TextArea")
export function TextArea(
    value?: TextAreaOptions,
    @memo
    content_?: () => void,
): TextAreaAttribute {
    throw new Error("Not implemented")
}

@memo
export function TextArea(
    @memo
    style: ((attributes: UITextAreaAttribute) => void) | undefined,
    value?: TextAreaOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkTextAreaComponent>((): ArkTextAreaComponent => {
        return new ArkTextAreaComponent()
    })
    NodeAttach<ArkTextAreaPeer>((): ArkTextAreaPeer => ArkTextAreaPeer.create(receiver), (_: ArkTextAreaPeer): void => {
        receiver.setTextAreaOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
export class TextAreaControllerInternal {
    public static fromPtr(ptr: KPointer): TextAreaController {
        const obj : TextAreaController = new TextAreaController()
        obj.peer = new Finalizable(ptr, TextAreaController.getFinalizer())
        return obj
    }
}
export class TextAreaController extends TextContentControllerBase implements MaterializedBase {
    static ctor_textareacontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TextAreaController_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = TextAreaController.ctor_textareacontroller()
        this.peer = new Finalizable(ctorPtr, TextAreaController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextAreaController_getFinalizer()
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
        ArkUIGeneratedNativeModule._TextAreaController_caretPosition(this.peer!.ptr, value)
    }
    private setTextSelection_serialize(selectionStart: number, selectionEnd: number, options?: SelectionOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeSelectionOptions(options_value)
        }
        ArkUIGeneratedNativeModule._TextAreaController_setTextSelection(this.peer!.ptr, selectionStart, selectionEnd, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private stopEditing_serialize(): void {
        ArkUIGeneratedNativeModule._TextAreaController_stopEditing(this.peer!.ptr)
    }
}

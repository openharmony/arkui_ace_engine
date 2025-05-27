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
import { ArkCommonMethodPeer, CommonMethod, TextDecorationOptions, CustomBuilder, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod, TextContentControllerBase, TextContentControllerBaseInternal, SelectionOptions } from "./common"
import { ResourceColor, Dimension, Font, ResourceStr, Length } from "./units"
import { SymbolGlyphModifier } from "./arkui-external"
import { Callback_Boolean_Void } from "./navigation"
import { CaretStyle, EditableTextOnChangeCallback, PreviewText, InsertValue, DeleteValue, EditMenuOptions } from "./text_common"
import { EnterKeyType, SubmitEvent, OnTextSelectionChangeCallback, OnContentScrollCallback, OnPasteCallback } from "./text_input"
import { Callback_String_Void } from "./grid_row"
import { PasteEvent, KeyboardOptions } from "./rich_editor"
import { CopyOptions, TextAlign, Color } from "./enums"
import { Resource } from "./resource"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Deserializer } from "./peers/Deserializer"
export class ArkSearchPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkSearchPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Search_construct(peerId, flags)
        const _peer  = new ArkSearchPeer(_peerPtr, peerId, "Search", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setSearchOptionsAttribute(options?: SearchOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeSearchOptions(options_value)
        }
        ArkUIGeneratedNativeModule._SearchInterface_setSearchOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_fontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    searchIconAttribute(value: IconOptions | SymbolGlyphModifier): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isIconOptions(value, false, false, false)) {
            thisSerializer.writeInt8(0)
            const value_0  = value as IconOptions
            thisSerializer.writeIconOptions(value_0)
        }
        else if (TypeChecker.isSymbolGlyphModifier(value)) {
            thisSerializer.writeInt8(1)
            const value_1  = value as SymbolGlyphModifier
            thisSerializer.writeSymbolGlyphModifier(value_1)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_searchIcon(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    cancelButtonAttribute(value: CancelButtonOptions | CancelButtonSymbolOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isCancelButtonOptions(value, true, true)) {
            thisSerializer.writeInt8(0)
            const value_0  = value as CancelButtonOptions
            thisSerializer.writeCancelButtonOptions(value_0)
        }
        else if (TypeChecker.isCancelButtonSymbolOptions(value, true, true)) {
            thisSerializer.writeInt8(1)
            const value_1  = value as CancelButtonSymbolOptions
            thisSerializer.writeCancelButtonSymbolOptions(value_1)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_cancelButton(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
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
        ArkUIGeneratedNativeModule._SearchAttribute_textIndent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onEditChangeAttribute(value: ((isVisible: boolean) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._SearchAttribute_onEditChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_selectedBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    caretStyleAttribute(value: CaretStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeCaretStyle(value)
        ArkUIGeneratedNativeModule._SearchAttribute_caretStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_placeholderColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    placeholderFontAttribute(value: Font | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeFont(value_value)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_placeholderFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    textFontAttribute(value: Font | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeFont(value_value)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_textFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enterKeyTypeAttribute(value: EnterKeyType): void {
        ArkUIGeneratedNativeModule._SearchAttribute_enterKeyType(this.peer.ptr, TypeChecker.EnterKeyType_ToNumeric(value))
    }
    onSubmit0Attribute(value: ((breakpoints: string) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._SearchAttribute_onSubmit0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSubmit1Attribute(value: SearchSubmitCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._SearchAttribute_onSubmit1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onChangeAttribute(value: EditableTextOnChangeCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._SearchAttribute_onChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onTextSelectionChangeAttribute(value: OnTextSelectionChangeCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._SearchAttribute_onTextSelectionChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onContentScrollAttribute(value: OnContentScrollCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._SearchAttribute_onContentScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onCopyAttribute(value: ((breakpoints: string) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._SearchAttribute_onCopy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onCutAttribute(value: ((breakpoints: string) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._SearchAttribute_onCut(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onPasteAttribute(value: OnPasteCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._SearchAttribute_onPaste(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    copyOptionAttribute(value: CopyOptions): void {
        ArkUIGeneratedNativeModule._SearchAttribute_copyOption(this.peer.ptr, TypeChecker.CopyOptions_ToNumeric(value))
    }
    maxLengthAttribute(value: number): void {
        ArkUIGeneratedNativeModule._SearchAttribute_maxLength(this.peer.ptr, value)
    }
    textAlignAttribute(value: TextAlign): void {
        ArkUIGeneratedNativeModule._SearchAttribute_textAlign(this.peer.ptr, TypeChecker.TextAlign_ToNumeric(value))
    }
    enableKeyboardOnFocusAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._SearchAttribute_enableKeyboardOnFocus(this.peer.ptr, value ? 1 : 0)
    }
    selectionMenuHiddenAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._SearchAttribute_selectionMenuHidden(this.peer.ptr, value ? 1 : 0)
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
        ArkUIGeneratedNativeModule._SearchAttribute_minFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_maxFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    decorationAttribute(value: TextDecorationOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeTextDecorationOptions(value)
        ArkUIGeneratedNativeModule._SearchAttribute_decoration(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_letterSpacing(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
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
        ArkUIGeneratedNativeModule._SearchAttribute_lineHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    typeAttribute(value: SearchType): void {
        ArkUIGeneratedNativeModule._SearchAttribute_type(this.peer.ptr, TypeChecker.SearchType_ToNumeric(value))
    }
    fontFeatureAttribute(value: string): void {
        ArkUIGeneratedNativeModule._SearchAttribute_fontFeature(this.peer.ptr, value)
    }
    onWillInsertAttribute(value: ((parameter: InsertValue) => boolean)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._SearchAttribute_onWillInsert(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDidInsertAttribute(value: ((parameter: InsertValue) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._SearchAttribute_onDidInsert(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillDeleteAttribute(value: ((parameter: DeleteValue) => boolean)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._SearchAttribute_onWillDelete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDidDeleteAttribute(value: ((parameter: DeleteValue) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._SearchAttribute_onDidDelete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    editMenuOptionsAttribute(value: EditMenuOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeEditMenuOptions(value)
        ArkUIGeneratedNativeModule._SearchAttribute_editMenuOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enablePreviewTextAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._SearchAttribute_enablePreviewText(this.peer.ptr, value ? 1 : 0)
    }
    enableHapticFeedbackAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._SearchAttribute_enableHapticFeedback(this.peer.ptr, value ? 1 : 0)
    }
    searchButtonAttribute(value: string, option?: SearchButtonOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let option_type : int32 = RuntimeType.UNDEFINED
        option_type = runtimeType(option)
        thisSerializer.writeInt8(option_type)
        if ((RuntimeType.UNDEFINED) != (option_type)) {
            const option_value  = option!
            thisSerializer.writeSearchButtonOptions(option_value)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_searchButton(this.peer.ptr, value, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
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
        ArkUIGeneratedNativeModule._SearchAttribute_inputFilter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_customKeyboard(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_valueAttribute(callback: ((breakpoints: string) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._SearchAttribute__onChangeEvent_value(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum CancelButtonStyle {
    CONSTANT = 0,
    INVISIBLE = 1,
    INPUT = 2
}
export enum SearchType {
    NORMAL = 0,
    NUMBER = 2,
    PHONE_NUMBER = 3,
    EMAIL = 5,
    NUMBER_DECIMAL = 12,
    URL = 13
}
export interface SearchOptions {
    value?: string;
    placeholder?: ResourceStr;
    icon?: string;
    controller?: SearchController;
}

export interface IconOptions {
    size?: Length;
    color?: ResourceColor;
    src?: ResourceStr;
}
export interface SearchButtonOptions {
    fontSize?: Length;
    fontColor?: ResourceColor;
    autoDisable?: boolean;
}
export interface CancelButtonOptions {
    style?: CancelButtonStyle;
    icon?: IconOptions;
}
export interface CancelButtonSymbolOptions {
    style?: CancelButtonStyle;
    icon?: SymbolGlyphModifier;
}
export type SearchSubmitCallback = (searchContent: string, event?: SubmitEvent) => void;
export type Callback_InsertValue_Boolean = (parameter: InsertValue) => boolean;
export type Callback_InsertValue_Void = (parameter: InsertValue) => void;
export type Callback_DeleteValue_Boolean = (parameter: DeleteValue) => boolean;
export type Callback_DeleteValue_Void = (parameter: DeleteValue) => void;
export interface SearchAttribute extends CommonMethod {
    fontColor(value: ResourceColor): this
    searchIcon(value: IconOptions | SymbolGlyphModifier): this
    cancelButton(value: CancelButtonOptions | CancelButtonSymbolOptions): this
    textIndent(value: Dimension): this
    onEditChange(value: ((isVisible: boolean) => void)): this
    selectedBackgroundColor(value: ResourceColor): this
    caretStyle(value: CaretStyle): this
    placeholderColor(value: ResourceColor): this
    placeholderFont(value: Font | undefined): this
    textFont(value: Font | undefined): this
    enterKeyType(value: EnterKeyType): this
    onSubmit(value: ((breakpoints: string) => void) | SearchSubmitCallback): this
    onChange(value: EditableTextOnChangeCallback): this
    onTextSelectionChange(value: OnTextSelectionChangeCallback): this
    onContentScroll(value: OnContentScrollCallback): this
    onCopy(value: ((breakpoints: string) => void)): this
    onCut(value: ((breakpoints: string) => void)): this
    onPaste(value: OnPasteCallback): this
    copyOption(value: CopyOptions): this
    maxLength(value: number): this
    textAlign(value: TextAlign): this
    enableKeyboardOnFocus(value: boolean): this
    selectionMenuHidden(value: boolean): this
    minFontSize(value: number | string | Resource): this
    maxFontSize(value: number | string | Resource): this
    decoration(value: TextDecorationOptions): this
    letterSpacing(value: number | string | Resource): this
    lineHeight(value: number | string | Resource): this
    type(value: SearchType): this
    fontFeature(value: string): this
    onWillInsert(value: ((parameter: InsertValue) => boolean)): this
    onDidInsert(value: ((parameter: InsertValue) => void)): this
    onWillDelete(value: ((parameter: DeleteValue) => boolean)): this
    onDidDelete(value: ((parameter: DeleteValue) => void)): this
    editMenuOptions(value: EditMenuOptions): this
    enablePreviewText(value: boolean): this
    enableHapticFeedback(value: boolean): this
    searchButton(value: string, option?: SearchButtonOptions): this
    inputFilter(value: ResourceStr, error?: ((breakpoints: string) => void)): this
    customKeyboard(value: CustomBuilder, options?: KeyboardOptions): this
    _onChangeEvent_value(callback: ((breakpoints: string) => void)): void
    attributeModifier(value: AttributeModifier<SearchAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UISearchAttribute extends UICommonMethod {
    @memo
    fontColor(value: ResourceColor): this
    @memo
    searchIcon(value: IconOptions | SymbolGlyphModifier): this
    @memo
    cancelButton(value: CancelButtonOptions | CancelButtonSymbolOptions): this
    @memo
    textIndent(value: Dimension): this
    @memo
    onEditChange(value: ((isVisible: boolean) => void)): this
    @memo
    selectedBackgroundColor(value: ResourceColor): this
    @memo
    caretStyle(value: CaretStyle): this
    @memo
    placeholderColor(value: ResourceColor): this
    @memo
    placeholderFont(value: Font | undefined): this
    @memo
    textFont(value: Font | undefined): this
    @memo
    enterKeyType(value: EnterKeyType): this
    @memo
    onSubmit(value: ((breakpoints: string) => void) | SearchSubmitCallback): this
    @memo
    onChange(value: EditableTextOnChangeCallback): this
    @memo
    onTextSelectionChange(value: OnTextSelectionChangeCallback): this
    @memo
    onContentScroll(value: OnContentScrollCallback): this
    @memo
    onCopy(value: ((breakpoints: string) => void)): this
    @memo
    onCut(value: ((breakpoints: string) => void)): this
    @memo
    onPaste(value: OnPasteCallback): this
    @memo
    copyOption(value: CopyOptions): this
    @memo
    maxLength(value: number): this
    @memo
    textAlign(value: TextAlign): this
    @memo
    enableKeyboardOnFocus(value: boolean): this
    @memo
    selectionMenuHidden(value: boolean): this
    @memo
    minFontSize(value: number | string | Resource): this
    @memo
    maxFontSize(value: number | string | Resource): this
    @memo
    decoration(value: TextDecorationOptions): this
    @memo
    letterSpacing(value: number | string | Resource): this
    @memo
    lineHeight(value: number | string | Resource): this
    @memo
    type(value: SearchType): this
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
    searchButton(value: string, option?: SearchButtonOptions): this
    @memo
    inputFilter(value: ResourceStr, error?: ((breakpoints: string) => void)): this
    @memo
    customKeyboard(value: CustomBuilder, options?: KeyboardOptions): this
    @memo
    _onChangeEvent_value(callback: ((breakpoints: string) => void)): void
    @memo
    attributeModifier(value: AttributeModifier<SearchAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkSearchStyle extends ArkCommonMethodStyle implements SearchAttribute {
    fontColor_value?: ResourceColor
    searchIcon_value?: IconOptions | SymbolGlyphModifier
    cancelButton_value?: CancelButtonOptions | CancelButtonSymbolOptions
    textIndent_value?: Dimension
    onEditChange_value?: ((isVisible: boolean) => void)
    selectedBackgroundColor_value?: ResourceColor
    caretStyle_value?: CaretStyle
    placeholderColor_value?: ResourceColor
    placeholderFont_value?: Font
    textFont_value?: Font
    enterKeyType_value?: EnterKeyType
    onSubmit_value?: ((breakpoints: string) => void)
    onChange_value?: EditableTextOnChangeCallback
    onTextSelectionChange_value?: OnTextSelectionChangeCallback
    onContentScroll_value?: OnContentScrollCallback
    onCopy_value?: ((breakpoints: string) => void)
    onCut_value?: ((breakpoints: string) => void)
    onPaste_value?: OnPasteCallback
    copyOption_value?: CopyOptions
    maxLength_value?: number
    textAlign_value?: TextAlign
    enableKeyboardOnFocus_value?: boolean
    selectionMenuHidden_value?: boolean
    minFontSize_value?: number | string | Resource
    maxFontSize_value?: number | string | Resource
    decoration_value?: TextDecorationOptions
    letterSpacing_value?: number | string | Resource
    lineHeight_value?: number | string | Resource
    type_value?: SearchType
    fontFeature_value?: string
    onWillInsert_value?: ((parameter: InsertValue) => boolean)
    onDidInsert_value?: ((parameter: InsertValue) => void)
    onWillDelete_value?: ((parameter: DeleteValue) => boolean)
    onDidDelete_value?: ((parameter: DeleteValue) => void)
    editMenuOptions_value?: EditMenuOptions
    enablePreviewText_value?: boolean
    enableHapticFeedback_value?: boolean
    public fontColor(value: ResourceColor): this {
        return this
    }
    public searchIcon(value: IconOptions | SymbolGlyphModifier): this {
        return this
    }
    public cancelButton(value: CancelButtonOptions | CancelButtonSymbolOptions): this {
        return this
    }
    public textIndent(value: Dimension): this {
        return this
    }
    public onEditChange(value: ((isVisible: boolean) => void)): this {
        return this
    }
    public selectedBackgroundColor(value: ResourceColor): this {
        return this
    }
    public caretStyle(value: CaretStyle): this {
        return this
    }
    public placeholderColor(value: ResourceColor): this {
        return this
    }
    public placeholderFont(value: Font | undefined): this {
        return this
    }
    public textFont(value: Font | undefined): this {
        return this
    }
    public enterKeyType(value: EnterKeyType): this {
        return this
    }
    public onSubmit(value: ((breakpoints: string) => void) | SearchSubmitCallback): this {
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
    public maxLength(value: number): this {
        return this
    }
    public textAlign(value: TextAlign): this {
        return this
    }
    public enableKeyboardOnFocus(value: boolean): this {
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
    public decoration(value: TextDecorationOptions): this {
        return this
    }
    public letterSpacing(value: number | string | Resource): this {
        return this
    }
    public lineHeight(value: number | string | Resource): this {
        return this
    }
    public type(value: SearchType): this {
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
    public searchButton(value: string, option?: SearchButtonOptions): this {
        return this
    }
    public inputFilter(value: ResourceStr, error?: ((breakpoints: string) => void)): this {
        return this
    }
    public customKeyboard(value: CustomBuilder, options?: KeyboardOptions): this {
        return this
    }
    public _onChangeEvent_value(callback: ((breakpoints: string) => void)): void {
        throw new Error("Unimplmented")
    }
    public attributeModifier(value: AttributeModifier<SearchAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
@memo_stable
export class ArkSearchComponent extends ArkCommonMethodComponent implements UISearchAttribute {
    getPeer(): ArkSearchPeer {
        return (this.peer as ArkSearchPeer)
    }
    @memo
    public setSearchOptions(options?: SearchOptions): this {
        if (this.checkPriority("setSearchOptions")) {
            const options_casted = options as (SearchOptions | undefined)
            this.getPeer()?.setSearchOptionsAttribute(options_casted)
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
    public searchIcon(value: IconOptions | SymbolGlyphModifier): this {
        if (this.checkPriority("searchIcon")) {
            const value_casted = value as (IconOptions | SymbolGlyphModifier)
            this.getPeer()?.searchIconAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public cancelButton(value: CancelButtonOptions | CancelButtonSymbolOptions): this {
        if (this.checkPriority("cancelButton")) {
            const value_casted = value as (CancelButtonOptions | CancelButtonSymbolOptions)
            this.getPeer()?.cancelButtonAttribute(value_casted)
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
    public onEditChange(value: ((isVisible: boolean) => void)): this {
        if (this.checkPriority("onEditChange")) {
            const value_casted = value as (((isVisible: boolean) => void))
            this.getPeer()?.onEditChangeAttribute(value_casted)
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
    public caretStyle(value: CaretStyle): this {
        if (this.checkPriority("caretStyle")) {
            const value_casted = value as (CaretStyle)
            this.getPeer()?.caretStyleAttribute(value_casted)
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
    public placeholderFont(value: Font | undefined): this {
        if (this.checkPriority("placeholderFont")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.placeholderFontAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public textFont(value: Font | undefined): this {
        if (this.checkPriority("textFont")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.textFontAttribute(value_casted)
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
    public onSubmit(value: ((breakpoints: string) => void) | SearchSubmitCallback): this {
        if (this.checkPriority("onSubmit")) {
            const value_type = runtimeType(value)
            if (RuntimeType.FUNCTION == value_type) {
                const value_casted = value as (((breakpoints: string) => void))
                this.getPeer()?.onSubmit0Attribute(value_casted)
                return this
            }
            if (RuntimeType.FUNCTION == value_type) {
                const value_casted = value as (SearchSubmitCallback)
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
    public onTextSelectionChange(value: OnTextSelectionChangeCallback): this {
        if (this.checkPriority("onTextSelectionChange")) {
            const value_casted = value as (OnTextSelectionChangeCallback)
            this.getPeer()?.onTextSelectionChangeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onContentScroll(value: OnContentScrollCallback): this {
        if (this.checkPriority("onContentScroll")) {
            const value_casted = value as (OnContentScrollCallback)
            this.getPeer()?.onContentScrollAttribute(value_casted)
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
    public onPaste(value: OnPasteCallback): this {
        if (this.checkPriority("onPaste")) {
            const value_casted = value as (OnPasteCallback)
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
    public maxLength(value: number): this {
        if (this.checkPriority("maxLength")) {
            const value_casted = value as (number)
            this.getPeer()?.maxLengthAttribute(value_casted)
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
    public enableKeyboardOnFocus(value: boolean): this {
        if (this.checkPriority("enableKeyboardOnFocus")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableKeyboardOnFocusAttribute(value_casted)
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
    public lineHeight(value: number | string | Resource): this {
        if (this.checkPriority("lineHeight")) {
            const value_casted = value as (number | string | Resource)
            this.getPeer()?.lineHeightAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public type(value: SearchType): this {
        if (this.checkPriority("type")) {
            const value_casted = value as (SearchType)
            this.getPeer()?.typeAttribute(value_casted)
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
    public searchButton(value: string, option?: SearchButtonOptions): this {
        if (this.checkPriority("searchButton")) {
            const value_casted = value as (string)
            const option_casted = option as (SearchButtonOptions | undefined)
            this.getPeer()?.searchButtonAttribute(value_casted, option_casted)
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
    public _onChangeEvent_value(callback: ((breakpoints: string) => void)): void {
        if (this.checkPriority("_onChangeEvent_value")) {
            const callback_casted = callback as (((breakpoints: string) => void))
            this.getPeer()?._onChangeEvent_valueAttribute(callback_casted)
            return
        }
        return
    }
    @memo
    public attributeModifier(value: AttributeModifier<SearchAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
@memo
@BuilderLambda("Search")
export function Search(
    options?: SearchOptions,
    @memo
    content_?: () => void,
): SearchAttribute {
    throw new Error("Not implemented")
}

@memo
export function Search(
    @memo
    style: ((attributes: UISearchAttribute) => void) | undefined,
    options?: SearchOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkSearchComponent>((): ArkSearchComponent => {
        return new ArkSearchComponent()
    })
    NodeAttach<ArkSearchPeer>((): ArkSearchPeer => ArkSearchPeer.create(receiver), (_: ArkSearchPeer): void => {
        receiver.setSearchOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
export class SearchControllerInternal {
    public static fromPtr(ptr: KPointer): SearchController {
        const obj : SearchController = new SearchController()
        obj.peer = new Finalizable(ptr, SearchController.getFinalizer())
        return obj
    }
}
export class SearchController extends TextContentControllerBase implements MaterializedBase {
    static ctor_searchcontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SearchController_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = SearchController.ctor_searchcontroller()
        this.peer = new Finalizable(ctorPtr, SearchController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SearchController_getFinalizer()
    }
    public caretPosition(value: number): void {
        const value_casted = value as (number)
        this.caretPosition_serialize(value_casted)
        return
    }
    public stopEditing(): void {
        this.stopEditing_serialize()
        return
    }
    public setTextSelection(selectionStart: number, selectionEnd: number, options?: SelectionOptions): void {
        const selectionStart_casted = selectionStart as (number)
        const selectionEnd_casted = selectionEnd as (number)
        const options_casted = options as (SelectionOptions | undefined)
        this.setTextSelection_serialize(selectionStart_casted, selectionEnd_casted, options_casted)
        return
    }
    private caretPosition_serialize(value: number): void {
        ArkUIGeneratedNativeModule._SearchController_caretPosition(this.peer!.ptr, value)
    }
    private stopEditing_serialize(): void {
        ArkUIGeneratedNativeModule._SearchController_stopEditing(this.peer!.ptr)
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
        ArkUIGeneratedNativeModule._SearchController_setTextSelection(this.peer!.ptr, selectionStart, selectionEnd, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}

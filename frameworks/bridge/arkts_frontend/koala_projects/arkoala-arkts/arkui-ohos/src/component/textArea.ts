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
import { ArkCommonMethodPeer, CommonMethod, TextDecorationOptions, InputCounterOptions, CustomBuilder, ArkCommonMethodComponent, ArkCommonMethodStyle, TextContentControllerBase, TextContentControllerBaseInternal, SelectionOptions } from "./common"
import { ResourceColor, Font, Length, ResourceStr, Dimension, PX, VP, FP, LPX, Percentage } from "./units"
import { EnterKeyType, SubmitEvent, ContentType } from "./textInput"
import { TextAlign, FontStyle, FontWeight, TextOverflow, CopyOptions, TextContentStyle, BarState, TextHeightAdaptivePolicy, WordBreak, LineBreakStrategy, EllipsisMode, Color } from "./enums"
import { CaretStyle, EditableTextOnChangeCallback, PreviewText, TextChangeOptions, InsertValue, DeleteValue, EditMenuOptions, AutoCapitalizationMode, EditableTextChangeValue, KeyboardAppearance } from "./textCommon"
import { Callback_Number_Number_Void } from "./grid"
import { Callback_Boolean_Void } from "./navigation"
import { Callback_String_Void } from "./gridRow"
import { PasteEvent, KeyboardOptions } from "./richEditor"
import { Resource } from "global/resource"
import { LengthMetrics } from "../Graphics"
import { Callback_InsertValue_Boolean, Callback_InsertValue_Void, Callback_DeleteValue_Boolean, Callback_DeleteValue_Void, Callback_EditableTextChangeValue_Boolean } from "./search"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"

import { Deserializer } from "./peers/Deserializer"
export class ArkTextAreaPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkTextAreaPeer {
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
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeTextAreaOptions(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaInterface_setTextAreaOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    placeholderColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._TextAreaAttribute_placeholderColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextAreaAttribute_placeholderFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextAreaAttribute_enterKeyType(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    textAlignAttribute(value: TextAlign | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as TextAlign)
            thisSerializer.writeInt32(TypeChecker.TextAlign_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_textAlign(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextAreaAttribute_caretColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._TextAreaAttribute_fontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontSizeAttribute(value: Length | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_fontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontStyleAttribute(value: FontStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as FontStyle)
            thisSerializer.writeInt32(TypeChecker.FontStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_fontStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontWeightAttribute(value: number | FontWeight | string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isFontWeight(value_value)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as FontWeight
                thisSerializer.writeInt32(TypeChecker.FontWeight_ToNumeric(value_value_1))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_fontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontFamilyAttribute(value: ResourceStr | undefined): void {
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
        ArkUIGeneratedNativeModule._TextAreaAttribute_fontFamily(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    textOverflowAttribute(value: TextOverflow | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as TextOverflow)
            thisSerializer.writeInt32(TypeChecker.TextOverflow_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_textOverflow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    textIndentAttribute(value: Dimension | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_textIndent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    caretStyleAttribute(value: CaretStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeCaretStyle(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_caretStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextAreaAttribute_selectedBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSubmit0Attribute(value: ((enterKey: EnterKeyType) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_onSubmit0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSubmit1Attribute(value: TextAreaSubmitCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_onSubmit1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onChangeAttribute(value: EditableTextOnChangeCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_onChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onTextSelectionChangeAttribute(value: ((first: number,last: number) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_onTextSelectionChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onContentScrollAttribute(value: ((first: number,last: number) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_onContentScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onEditChangeAttribute(value: ((isVisible: boolean) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_onEditChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onCopyAttribute(value: ((breakpoints: string) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_onCopy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onCutAttribute(value: ((breakpoints: string) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_onCut(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onPasteAttribute(value: ((value: string,event: PasteEvent) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_onPaste(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    copyOptionAttribute(value: CopyOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as CopyOptions)
            thisSerializer.writeInt32(TypeChecker.CopyOptions_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_copyOption(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextAreaAttribute_enableKeyboardOnFocus(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextAreaAttribute_maxLength(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    styleAttribute(value: TextContentStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as TextContentStyle)
            thisSerializer.writeInt32(TypeChecker.TextContentStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_style(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextAreaAttribute_barState(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectionMenuHiddenAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_selectionMenuHidden(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    minFontSizeAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as Resource
                thisSerializer.writeResource(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_minFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    maxFontSizeAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as Resource
                thisSerializer.writeResource(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_maxFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    minFontScaleAttribute(value: number | Resource | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Resource
                thisSerializer.writeResource(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_minFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    maxFontScaleAttribute(value: number | Resource | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Resource
                thisSerializer.writeResource(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_maxFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    heightAdaptivePolicyAttribute(value: TextHeightAdaptivePolicy | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as TextHeightAdaptivePolicy)
            thisSerializer.writeInt32(TypeChecker.TextHeightAdaptivePolicy_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_heightAdaptivePolicy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextAreaAttribute_maxLines(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    wordBreakAttribute(value: WordBreak | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as WordBreak)
            thisSerializer.writeInt32(TypeChecker.WordBreak_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_wordBreak(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    lineBreakStrategyAttribute(value: LineBreakStrategy | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as LineBreakStrategy)
            thisSerializer.writeInt32(TypeChecker.LineBreakStrategy_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_lineBreakStrategy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    decorationAttribute(value: TextDecorationOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeTextDecorationOptions(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_decoration(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    letterSpacingAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as Resource
                thisSerializer.writeResource(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_letterSpacing(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    lineSpacingAttribute(value: LengthMetrics | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLengthMetrics(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_lineSpacing(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    lineHeightAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as Resource
                thisSerializer.writeResource(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_lineHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    typeAttribute(value: TextAreaType | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as TextAreaType)
            thisSerializer.writeInt32(TypeChecker.TextAreaType_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_type(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableAutoFillAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_enableAutoFill(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    contentTypeAttribute(value: ContentType | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as ContentType)
            thisSerializer.writeInt32(TypeChecker.ContentType_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_contentType(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontFeatureAttribute(value: string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_fontFeature(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillInsertAttribute(value: ((parameter: InsertValue) => boolean) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_onWillInsert(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDidInsertAttribute(value: ((parameter: InsertValue) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_onDidInsert(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillDeleteAttribute(value: ((parameter: DeleteValue) => boolean) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_onWillDelete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDidDeleteAttribute(value: ((parameter: DeleteValue) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_onDidDelete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextAreaAttribute_editMenuOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextAreaAttribute_enablePreviewText(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextAreaAttribute_enableHapticFeedback(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    autoCapitalizationModeAttribute(value: AutoCapitalizationMode | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as AutoCapitalizationMode)
            thisSerializer.writeInt32(TypeChecker.AutoCapitalizationMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_autoCapitalizationMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    halfLeadingAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_halfLeading(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    ellipsisModeAttribute(value: EllipsisMode | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as EllipsisMode)
            thisSerializer.writeInt32(TypeChecker.EllipsisMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_ellipsisMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextAreaAttribute_stopBackPress(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillChangeAttribute(value: ((parameter: EditableTextChangeValue) => boolean) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_onWillChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextAreaAttribute_keyboardAppearance(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    inputFilterAttribute(value: ResourceStr | undefined, error?: ((breakpoints: string) => void)): void {
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
        let error_type : int32 = RuntimeType.UNDEFINED
        error_type = runtimeType(error)
        thisSerializer.writeInt8(error_type as int32)
        if ((RuntimeType.UNDEFINED) != (error_type)) {
            const error_value  = error!
            thisSerializer.holdAndWriteCallback(error_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_inputFilter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    showCounterAttribute(value: boolean | undefined, options?: InputCounterOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeInputCounterOptions(options_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_showCounter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextAreaAttribute_customKeyboard(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_textAttribute(callback: ((text: ResourceStr) => void)): void {
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
export type TextAreaInterface = (value?: TextAreaOptions) => TextAreaAttribute;
export enum TextAreaType {
    NORMAL = 0,
    NUMBER = 2,
    PHONE_NUMBER = 3,
    EMAIL = 5,
    NUMBER_DECIMAL = 12,
    URL = 13
}
export type TextAreaSubmitCallback = (enterKeyType: EnterKeyType, event?: SubmitEvent) => void;
export type Callback_EnterKeyType_Void = (enterKey: EnterKeyType) => void;
export type Callback_String_PasteEvent_Void = (value: string, event: PasteEvent) => void;
export type Callback_ResourceStr_Void = (text: ResourceStr) => void;
export interface TextAreaAttribute extends CommonMethod {
    placeholderColor(value: ResourceColor | undefined): this
    placeholderFont(value: Font | undefined): this
    enterKeyType(value: EnterKeyType | undefined): this
    textAlign(value: TextAlign | undefined): this
    caretColor(value: ResourceColor | undefined): this
    fontColor(value: ResourceColor | undefined): this
    fontSize(value: Length | undefined): this
    fontStyle(value: FontStyle | undefined): this
    fontWeight(value: number | FontWeight | string | undefined): this
    fontFamily(value: ResourceStr | undefined): this
    textOverflow(value: TextOverflow | undefined): this
    textIndent(value: Dimension | undefined): this
    caretStyle(value: CaretStyle | undefined): this
    selectedBackgroundColor(value: ResourceColor | undefined): this
    onSubmit(value: ((enterKey: EnterKeyType) => void) | undefined | TextAreaSubmitCallback | undefined): this
    onChange(value: EditableTextOnChangeCallback | undefined): this
    onTextSelectionChange(value: ((first: number,last: number) => void) | undefined): this
    onContentScroll(value: ((first: number,last: number) => void) | undefined): this
    onEditChange(value: ((isVisible: boolean) => void) | undefined): this
    onCopy(value: ((breakpoints: string) => void) | undefined): this
    onCut(value: ((breakpoints: string) => void) | undefined): this
    onPaste(value: ((value: string,event: PasteEvent) => void) | undefined): this
    copyOption(value: CopyOptions | undefined): this
    enableKeyboardOnFocus(value: boolean | undefined): this
    maxLength(value: number | undefined): this
    style(value: TextContentStyle | undefined): this
    barState(value: BarState | undefined): this
    selectionMenuHidden(value: boolean | undefined): this
    minFontSize(value: number | string | Resource | undefined): this
    maxFontSize(value: number | string | Resource | undefined): this
    minFontScale(value: number | Resource | undefined): this
    maxFontScale(value: number | Resource | undefined): this
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy | undefined): this
    maxLines(value: number | undefined): this
    wordBreak(value: WordBreak | undefined): this
    lineBreakStrategy(value: LineBreakStrategy | undefined): this
    decoration(value: TextDecorationOptions | undefined): this
    letterSpacing(value: number | string | Resource | undefined): this
    lineSpacing(value: LengthMetrics | undefined): this
    lineHeight(value: number | string | Resource | undefined): this
    type(value: TextAreaType | undefined): this
    enableAutoFill(value: boolean | undefined): this
    contentType(value: ContentType | undefined): this
    fontFeature(value: string | undefined): this
    onWillInsert(value: ((parameter: InsertValue) => boolean) | undefined): this
    onDidInsert(value: ((parameter: InsertValue) => void) | undefined): this
    onWillDelete(value: ((parameter: DeleteValue) => boolean) | undefined): this
    onDidDelete(value: ((parameter: DeleteValue) => void) | undefined): this
    editMenuOptions(value: EditMenuOptions | undefined): this
    enablePreviewText(value: boolean | undefined): this
    enableHapticFeedback(value: boolean | undefined): this
    autoCapitalizationMode(value: AutoCapitalizationMode | undefined): this
    halfLeading(value: boolean | undefined): this
    ellipsisMode(value: EllipsisMode | undefined): this
    stopBackPress(value: boolean | undefined): this
    onWillChange(value: ((parameter: EditableTextChangeValue) => boolean) | undefined): this
    keyboardAppearance(value: KeyboardAppearance | undefined): this
    inputFilter(value: ResourceStr | undefined, error?: ((breakpoints: string) => void)): this
    showCounter(value: boolean | undefined, options?: InputCounterOptions): this
    customKeyboard(value: CustomBuilder | undefined, options?: KeyboardOptions): this
    _onChangeEvent_text(callback: ((text: ResourceStr) => void)): void
}
export class ArkTextAreaStyle extends ArkCommonMethodStyle implements TextAreaAttribute {
    placeholderColor_value?: ResourceColor | undefined
    placeholderFont_value?: Font | undefined
    enterKeyType_value?: EnterKeyType | undefined
    textAlign_value?: TextAlign | undefined
    caretColor_value?: ResourceColor | undefined
    fontColor_value?: ResourceColor | undefined
    fontSize_value?: Length | undefined
    fontStyle_value?: FontStyle | undefined
    fontWeight_value?: number | FontWeight | string | undefined
    fontFamily_value?: ResourceStr | undefined
    textOverflow_value?: TextOverflow | undefined
    textIndent_value?: Dimension | undefined
    caretStyle_value?: CaretStyle | undefined
    selectedBackgroundColor_value?: ResourceColor | undefined
    onSubmit_value?: ((enterKey: EnterKeyType) => void) | undefined
    onChange_value?: EditableTextOnChangeCallback | undefined
    onTextSelectionChange_value?: ((first: number,last: number) => void) | undefined
    onContentScroll_value?: ((first: number,last: number) => void) | undefined
    onEditChange_value?: ((isVisible: boolean) => void) | undefined
    onCopy_value?: ((breakpoints: string) => void) | undefined
    onCut_value?: ((breakpoints: string) => void) | undefined
    onPaste_value?: ((value: string,event: PasteEvent) => void) | undefined
    copyOption_value?: CopyOptions | undefined
    enableKeyboardOnFocus_value?: boolean | undefined
    maxLength_value?: number | undefined
    style_value?: TextContentStyle | undefined
    barState_value?: BarState | undefined
    selectionMenuHidden_value?: boolean | undefined
    minFontSize_value?: number | string | Resource | undefined
    maxFontSize_value?: number | string | Resource | undefined
    minFontScale_value?: number | Resource | undefined
    maxFontScale_value?: number | Resource | undefined
    heightAdaptivePolicy_value?: TextHeightAdaptivePolicy | undefined
    maxLines_value?: number | undefined
    wordBreak_value?: WordBreak | undefined
    lineBreakStrategy_value?: LineBreakStrategy | undefined
    decoration_value?: TextDecorationOptions | undefined
    letterSpacing_value?: number | string | Resource | undefined
    lineSpacing_value?: LengthMetrics | undefined
    lineHeight_value?: number | string | Resource | undefined
    type_value?: TextAreaType | undefined
    enableAutoFill_value?: boolean | undefined
    contentType_value?: ContentType | undefined
    fontFeature_value?: string | undefined
    onWillInsert_value?: ((parameter: InsertValue) => boolean) | undefined
    onDidInsert_value?: ((parameter: InsertValue) => void) | undefined
    onWillDelete_value?: ((parameter: DeleteValue) => boolean) | undefined
    onDidDelete_value?: ((parameter: DeleteValue) => void) | undefined
    editMenuOptions_value?: EditMenuOptions | undefined
    enablePreviewText_value?: boolean | undefined
    enableHapticFeedback_value?: boolean | undefined
    autoCapitalizationMode_value?: AutoCapitalizationMode | undefined
    halfLeading_value?: boolean | undefined
    ellipsisMode_value?: EllipsisMode | undefined
    stopBackPress_value?: boolean | undefined
    onWillChange_value?: ((parameter: EditableTextChangeValue) => boolean) | undefined
    keyboardAppearance_value?: KeyboardAppearance | undefined
    public placeholderColor(value: ResourceColor | undefined): this {
        return this
    }
    public placeholderFont(value: Font | undefined): this {
        return this
    }
    public enterKeyType(value: EnterKeyType | undefined): this {
        return this
    }
    public textAlign(value: TextAlign | undefined): this {
        return this
    }
    public caretColor(value: ResourceColor | undefined): this {
        return this
    }
    public fontColor(value: ResourceColor | undefined): this {
        return this
    }
    public fontSize(value: Length | undefined): this {
        return this
    }
    public fontStyle(value: FontStyle | undefined): this {
        return this
    }
    public fontWeight(value: number | FontWeight | string | undefined): this {
        return this
    }
    public fontFamily(value: ResourceStr | undefined): this {
        return this
    }
    public textOverflow(value: TextOverflow | undefined): this {
        return this
    }
    public textIndent(value: Dimension | undefined): this {
        return this
    }
    public caretStyle(value: CaretStyle | undefined): this {
        return this
    }
    public selectedBackgroundColor(value: ResourceColor | undefined): this {
        return this
    }
    public onSubmit(value: ((enterKey: EnterKeyType) => void) | undefined | TextAreaSubmitCallback | undefined): this {
        return this
    }
    public onChange(value: EditableTextOnChangeCallback | undefined): this {
        return this
    }
    public onTextSelectionChange(value: ((first: number,last: number) => void) | undefined): this {
        return this
    }
    public onContentScroll(value: ((first: number,last: number) => void) | undefined): this {
        return this
    }
    public onEditChange(value: ((isVisible: boolean) => void) | undefined): this {
        return this
    }
    public onCopy(value: ((breakpoints: string) => void) | undefined): this {
        return this
    }
    public onCut(value: ((breakpoints: string) => void) | undefined): this {
        return this
    }
    public onPaste(value: ((value: string,event: PasteEvent) => void) | undefined): this {
        return this
    }
    public copyOption(value: CopyOptions | undefined): this {
        return this
    }
    public enableKeyboardOnFocus(value: boolean | undefined): this {
        return this
    }
    public maxLength(value: number | undefined): this {
        return this
    }
    public style(value: TextContentStyle | undefined): this {
        return this
    }
    public barState(value: BarState | undefined): this {
        return this
    }
    public selectionMenuHidden(value: boolean | undefined): this {
        return this
    }
    public minFontSize(value: number | string | Resource | undefined): this {
        return this
    }
    public maxFontSize(value: number | string | Resource | undefined): this {
        return this
    }
    public minFontScale(value: number | Resource | undefined): this {
        return this
    }
    public maxFontScale(value: number | Resource | undefined): this {
        return this
    }
    public heightAdaptivePolicy(value: TextHeightAdaptivePolicy | undefined): this {
        return this
    }
    public maxLines(value: number | undefined): this {
        return this
    }
    public wordBreak(value: WordBreak | undefined): this {
        return this
    }
    public lineBreakStrategy(value: LineBreakStrategy | undefined): this {
        return this
    }
    public decoration(value: TextDecorationOptions | undefined): this {
        return this
    }
    public letterSpacing(value: number | string | Resource | undefined): this {
        return this
    }
    public lineSpacing(value: LengthMetrics | undefined): this {
        return this
    }
    public lineHeight(value: number | string | Resource | undefined): this {
        return this
    }
    public type(value: TextAreaType | undefined): this {
        return this
    }
    public enableAutoFill(value: boolean | undefined): this {
        return this
    }
    public contentType(value: ContentType | undefined): this {
        return this
    }
    public fontFeature(value: string | undefined): this {
        return this
    }
    public onWillInsert(value: ((parameter: InsertValue) => boolean) | undefined): this {
        return this
    }
    public onDidInsert(value: ((parameter: InsertValue) => void) | undefined): this {
        return this
    }
    public onWillDelete(value: ((parameter: DeleteValue) => boolean) | undefined): this {
        return this
    }
    public onDidDelete(value: ((parameter: DeleteValue) => void) | undefined): this {
        return this
    }
    public editMenuOptions(value: EditMenuOptions | undefined): this {
        return this
    }
    public enablePreviewText(value: boolean | undefined): this {
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        return this
    }
    public autoCapitalizationMode(value: AutoCapitalizationMode | undefined): this {
        return this
    }
    public halfLeading(value: boolean | undefined): this {
        return this
    }
    public ellipsisMode(value: EllipsisMode | undefined): this {
        return this
    }
    public stopBackPress(value: boolean | undefined): this {
        return this
    }
    public onWillChange(value: ((parameter: EditableTextChangeValue) => boolean) | undefined): this {
        return this
    }
    public keyboardAppearance(value: KeyboardAppearance | undefined): this {
        return this
    }
    public inputFilter(value: ResourceStr | undefined, error?: ((breakpoints: string) => void)): this {
        return this
    }
    public showCounter(value: boolean | undefined, options?: InputCounterOptions): this {
        return this
    }
    public customKeyboard(value: CustomBuilder | undefined, options?: KeyboardOptions): this {
        return this
    }
    public _onChangeEvent_text(callback: ((text: ResourceStr) => void)): void {
        throw new Error("Unimplmented")
        }
}
export class ArkTextAreaComponent extends ArkCommonMethodComponent implements TextAreaAttribute {
    getPeer(): ArkTextAreaPeer {
        return (this.peer as ArkTextAreaPeer)
    }
    public setTextAreaOptions(value?: TextAreaOptions): this {
        if (this.checkPriority("setTextAreaOptions")) {
            const value_casted = value as (TextAreaOptions | undefined)
            this.getPeer()?.setTextAreaOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public placeholderColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("placeholderColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.placeholderColorAttribute(value_casted)
            return this
        }
        return this
    }
    public placeholderFont(value: Font | undefined): this {
        if (this.checkPriority("placeholderFont")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.placeholderFontAttribute(value_casted)
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
    public textAlign(value: TextAlign | undefined): this {
        if (this.checkPriority("textAlign")) {
            const value_casted = value as (TextAlign | undefined)
            this.getPeer()?.textAlignAttribute(value_casted)
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
    public fontColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("fontColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.fontColorAttribute(value_casted)
            return this
        }
        return this
    }
    public fontSize(value: Length | undefined): this {
        if (this.checkPriority("fontSize")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.fontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public fontStyle(value: FontStyle | undefined): this {
        if (this.checkPriority("fontStyle")) {
            const value_casted = value as (FontStyle | undefined)
            this.getPeer()?.fontStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public fontWeight(value: number | FontWeight | string | undefined): this {
        if (this.checkPriority("fontWeight")) {
            const value_casted = value as (number | FontWeight | string | undefined)
            this.getPeer()?.fontWeightAttribute(value_casted)
            return this
        }
        return this
    }
    public fontFamily(value: ResourceStr | undefined): this {
        if (this.checkPriority("fontFamily")) {
            const value_casted = value as (ResourceStr | undefined)
            this.getPeer()?.fontFamilyAttribute(value_casted)
            return this
        }
        return this
    }
    public textOverflow(value: TextOverflow | undefined): this {
        if (this.checkPriority("textOverflow")) {
            const value_casted = value as (TextOverflow | undefined)
            this.getPeer()?.textOverflowAttribute(value_casted)
            return this
        }
        return this
    }
    public textIndent(value: Dimension | undefined): this {
        if (this.checkPriority("textIndent")) {
            const value_casted = value as (Dimension | undefined)
            this.getPeer()?.textIndentAttribute(value_casted)
            return this
        }
        return this
    }
    public caretStyle(value: CaretStyle | undefined): this {
        if (this.checkPriority("caretStyle")) {
            const value_casted = value as (CaretStyle | undefined)
            this.getPeer()?.caretStyleAttribute(value_casted)
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
    public onSubmit(value: ((enterKey: EnterKeyType) => void) | undefined | TextAreaSubmitCallback | undefined): this {
        if (this.checkPriority("onSubmit")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.FUNCTION == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (((enterKey: EnterKeyType) => void) | undefined)
                this.getPeer()?.onSubmit0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.FUNCTION == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (TextAreaSubmitCallback | undefined)
                this.getPeer()?.onSubmit1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public onChange(value: EditableTextOnChangeCallback | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (EditableTextOnChangeCallback | undefined)
            this.getPeer()?.onChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onTextSelectionChange(value: ((first: number,last: number) => void) | undefined): this {
        if (this.checkPriority("onTextSelectionChange")) {
            const value_casted = value as (((first: number,last: number) => void) | undefined)
            this.getPeer()?.onTextSelectionChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onContentScroll(value: ((first: number,last: number) => void) | undefined): this {
        if (this.checkPriority("onContentScroll")) {
            const value_casted = value as (((first: number,last: number) => void) | undefined)
            this.getPeer()?.onContentScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public onEditChange(value: ((isVisible: boolean) => void) | undefined): this {
        if (this.checkPriority("onEditChange")) {
            const value_casted = value as (((isVisible: boolean) => void) | undefined)
            this.getPeer()?.onEditChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onCopy(value: ((breakpoints: string) => void) | undefined): this {
        if (this.checkPriority("onCopy")) {
            const value_casted = value as (((breakpoints: string) => void) | undefined)
            this.getPeer()?.onCopyAttribute(value_casted)
            return this
        }
        return this
    }
    public onCut(value: ((breakpoints: string) => void) | undefined): this {
        if (this.checkPriority("onCut")) {
            const value_casted = value as (((breakpoints: string) => void) | undefined)
            this.getPeer()?.onCutAttribute(value_casted)
            return this
        }
        return this
    }
    public onPaste(value: ((value: string,event: PasteEvent) => void) | undefined): this {
        if (this.checkPriority("onPaste")) {
            const value_casted = value as (((value: string,event: PasteEvent) => void) | undefined)
            this.getPeer()?.onPasteAttribute(value_casted)
            return this
        }
        return this
    }
    public copyOption(value: CopyOptions | undefined): this {
        if (this.checkPriority("copyOption")) {
            const value_casted = value as (CopyOptions | undefined)
            this.getPeer()?.copyOptionAttribute(value_casted)
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
    public maxLength(value: number | undefined): this {
        if (this.checkPriority("maxLength")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.maxLengthAttribute(value_casted)
            return this
        }
        return this
    }
    public style(value: TextContentStyle | undefined): this {
        if (this.checkPriority("style")) {
            const value_casted = value as (TextContentStyle | undefined)
            this.getPeer()?.styleAttribute(value_casted)
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
    public selectionMenuHidden(value: boolean | undefined): this {
        if (this.checkPriority("selectionMenuHidden")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.selectionMenuHiddenAttribute(value_casted)
            return this
        }
        return this
    }
    public minFontSize(value: number | string | Resource | undefined): this {
        if (this.checkPriority("minFontSize")) {
            const value_casted = value as (number | string | Resource | undefined)
            this.getPeer()?.minFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public maxFontSize(value: number | string | Resource | undefined): this {
        if (this.checkPriority("maxFontSize")) {
            const value_casted = value as (number | string | Resource | undefined)
            this.getPeer()?.maxFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public minFontScale(value: number | Resource | undefined): this {
        if (this.checkPriority("minFontScale")) {
            const value_casted = value as (number | Resource | undefined)
            this.getPeer()?.minFontScaleAttribute(value_casted)
            return this
        }
        return this
    }
    public maxFontScale(value: number | Resource | undefined): this {
        if (this.checkPriority("maxFontScale")) {
            const value_casted = value as (number | Resource | undefined)
            this.getPeer()?.maxFontScaleAttribute(value_casted)
            return this
        }
        return this
    }
    public heightAdaptivePolicy(value: TextHeightAdaptivePolicy | undefined): this {
        if (this.checkPriority("heightAdaptivePolicy")) {
            const value_casted = value as (TextHeightAdaptivePolicy | undefined)
            this.getPeer()?.heightAdaptivePolicyAttribute(value_casted)
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
    public wordBreak(value: WordBreak | undefined): this {
        if (this.checkPriority("wordBreak")) {
            const value_casted = value as (WordBreak | undefined)
            this.getPeer()?.wordBreakAttribute(value_casted)
            return this
        }
        return this
    }
    public lineBreakStrategy(value: LineBreakStrategy | undefined): this {
        if (this.checkPriority("lineBreakStrategy")) {
            const value_casted = value as (LineBreakStrategy | undefined)
            this.getPeer()?.lineBreakStrategyAttribute(value_casted)
            return this
        }
        return this
    }
    public decoration(value: TextDecorationOptions | undefined): this {
        if (this.checkPriority("decoration")) {
            const value_casted = value as (TextDecorationOptions | undefined)
            this.getPeer()?.decorationAttribute(value_casted)
            return this
        }
        return this
    }
    public letterSpacing(value: number | string | Resource | undefined): this {
        if (this.checkPriority("letterSpacing")) {
            const value_casted = value as (number | string | Resource | undefined)
            this.getPeer()?.letterSpacingAttribute(value_casted)
            return this
        }
        return this
    }
    public lineSpacing(value: LengthMetrics | undefined): this {
        if (this.checkPriority("lineSpacing")) {
            const value_casted = value as (LengthMetrics | undefined)
            this.getPeer()?.lineSpacingAttribute(value_casted)
            return this
        }
        return this
    }
    public lineHeight(value: number | string | Resource | undefined): this {
        if (this.checkPriority("lineHeight")) {
            const value_casted = value as (number | string | Resource | undefined)
            this.getPeer()?.lineHeightAttribute(value_casted)
            return this
        }
        return this
    }
    public type(value: TextAreaType | undefined): this {
        if (this.checkPriority("type")) {
            const value_casted = value as (TextAreaType | undefined)
            this.getPeer()?.typeAttribute(value_casted)
            return this
        }
        return this
    }
    public enableAutoFill(value: boolean | undefined): this {
        if (this.checkPriority("enableAutoFill")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enableAutoFillAttribute(value_casted)
            return this
        }
        return this
    }
    public contentType(value: ContentType | undefined): this {
        if (this.checkPriority("contentType")) {
            const value_casted = value as (ContentType | undefined)
            this.getPeer()?.contentTypeAttribute(value_casted)
            return this
        }
        return this
    }
    public fontFeature(value: string | undefined): this {
        if (this.checkPriority("fontFeature")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.fontFeatureAttribute(value_casted)
            return this
        }
        return this
    }
    public onWillInsert(value: ((parameter: InsertValue) => boolean) | undefined): this {
        if (this.checkPriority("onWillInsert")) {
            const value_casted = value as (((parameter: InsertValue) => boolean) | undefined)
            this.getPeer()?.onWillInsertAttribute(value_casted)
            return this
        }
        return this
    }
    public onDidInsert(value: ((parameter: InsertValue) => void) | undefined): this {
        if (this.checkPriority("onDidInsert")) {
            const value_casted = value as (((parameter: InsertValue) => void) | undefined)
            this.getPeer()?.onDidInsertAttribute(value_casted)
            return this
        }
        return this
    }
    public onWillDelete(value: ((parameter: DeleteValue) => boolean) | undefined): this {
        if (this.checkPriority("onWillDelete")) {
            const value_casted = value as (((parameter: DeleteValue) => boolean) | undefined)
            this.getPeer()?.onWillDeleteAttribute(value_casted)
            return this
        }
        return this
    }
    public onDidDelete(value: ((parameter: DeleteValue) => void) | undefined): this {
        if (this.checkPriority("onDidDelete")) {
            const value_casted = value as (((parameter: DeleteValue) => void) | undefined)
            this.getPeer()?.onDidDeleteAttribute(value_casted)
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
    public enablePreviewText(value: boolean | undefined): this {
        if (this.checkPriority("enablePreviewText")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enablePreviewTextAttribute(value_casted)
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
    public autoCapitalizationMode(value: AutoCapitalizationMode | undefined): this {
        if (this.checkPriority("autoCapitalizationMode")) {
            const value_casted = value as (AutoCapitalizationMode | undefined)
            this.getPeer()?.autoCapitalizationModeAttribute(value_casted)
            return this
        }
        return this
    }
    public halfLeading(value: boolean | undefined): this {
        if (this.checkPriority("halfLeading")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.halfLeadingAttribute(value_casted)
            return this
        }
        return this
    }
    public ellipsisMode(value: EllipsisMode | undefined): this {
        if (this.checkPriority("ellipsisMode")) {
            const value_casted = value as (EllipsisMode | undefined)
            this.getPeer()?.ellipsisModeAttribute(value_casted)
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
    public onWillChange(value: ((parameter: EditableTextChangeValue) => boolean) | undefined): this {
        if (this.checkPriority("onWillChange")) {
            const value_casted = value as (((parameter: EditableTextChangeValue) => boolean) | undefined)
            this.getPeer()?.onWillChangeAttribute(value_casted)
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
    public inputFilter(value: ResourceStr | undefined, error?: ((breakpoints: string) => void)): this {
        if (this.checkPriority("inputFilter")) {
            const value_casted = value as (ResourceStr | undefined)
            const error_casted = error as (((breakpoints: string) => void) | undefined)
            this.getPeer()?.inputFilterAttribute(value_casted, error_casted)
            return this
        }
        return this
    }
    public showCounter(value: boolean | undefined, options?: InputCounterOptions): this {
        if (this.checkPriority("showCounter")) {
            const value_casted = value as (boolean | undefined)
            const options_casted = options as (InputCounterOptions | undefined)
            this.getPeer()?.showCounterAttribute(value_casted, options_casted)
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
    public _onChangeEvent_text(callback: ((text: ResourceStr) => void)): void {
        if (this.checkPriority("_onChangeEvent_text")) {
            const callback_casted = callback as (((text: ResourceStr) => void))
            this.getPeer()?._onChangeEvent_textAttribute(callback_casted)
            return
        }
        return
    }
    
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function TextArea(
    /** @memo */
    style: ((attributes: TextAreaAttribute) => void) | undefined,
    value?: TextAreaOptions,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkTextAreaComponent()
    })
    NodeAttach<ArkTextAreaPeer>((): ArkTextAreaPeer => ArkTextAreaPeer.create(receiver), (_: ArkTextAreaPeer) => {
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
        thisSerializer.writeInt8(options_type as int32)
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

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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr, Finalizable, registerCallback } from "@koalaui/interop"
import { Resource_serializer, Resource } from "./../generated/resource"
import { Font_serializer, ResourceColor, Font, Length, ResourceStr, Dimension } from "./units"
import { CaretStyle_serializer, EditMenuOptions_serializer, CaretStyle, EditableTextOnChangeCallback, PreviewText, TextChangeOptions, InsertValue, DeleteValue, EditMenuOptions, AutoCapitalizationMode, EditableTextChangeValue, KeyboardAppearance } from "./textCommon"
import { TextDecorationOptions_serializer, InputCounterOptions_serializer, ArkCommonMethodPeer, CommonMethod, TextDecorationOptions, InputCounterOptions, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet, SelectionOptions_serializer, TextContentControllerBase, TextContentControllerBaseInternal, SelectionOptions } from "./common"
import { LengthMetrics_serializer, LengthMetrics } from "./../generated/arkui.Graphics"
import { KeyboardOptions_serializer, PasteEvent, KeyboardOptions } from "./richEditor"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { Color, TextAlign, FontStyle, FontWeight, TextOverflow, CopyOptions, TextContentStyle, BarState, TextHeightAdaptivePolicy, WordBreak, LineBreakStrategy, EllipsisMode } from "./enums"
import { EnterKeyType, SubmitEvent, ContentType } from "./textInput"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CustomBuilder } from "./builder"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
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
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            TextAreaOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaInterface_setTextAreaOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPlaceholderColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((3).toChar())
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setPlaceholderColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPlaceholderFontAttribute(value: Font | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            Font_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setPlaceholderFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnterKeyTypeAttribute(value: EnterKeyType | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as EnterKeyType)
            thisSerializer.writeInt32(TypeChecker.EnterKeyType_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setEnterKeyType(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextAlignAttribute(value: TextAlign | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as TextAlign)
            thisSerializer.writeInt32(TypeChecker.TextAlign_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setTextAlign(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCaretColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((3).toChar())
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setCaretColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((3).toChar())
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontSizeAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontStyleAttribute(value: FontStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as FontStyle)
            thisSerializer.writeInt32(TypeChecker.FontStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setFontStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontWeightAttribute(value: number | FontWeight | ResourceStr | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (TypeChecker.isFontWeight(value_value)) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as FontWeight
                thisSerializer.writeInt32(TypeChecker.FontWeight_ToNumeric(value_value_1))
            }
            else if ((RuntimeType.STRING == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as ResourceStr
                let value_value_2_type : int32 = RuntimeType.UNDEFINED
                value_value_2_type = runtimeType(value_value_2)
                if (RuntimeType.STRING == value_value_2_type) {
                    thisSerializer.writeInt8((0).toChar())
                    const value_value_2_0  = value_value_2 as string
                    thisSerializer.writeString(value_value_2_0)
                }
                else if (RuntimeType.OBJECT == value_value_2_type) {
                    thisSerializer.writeInt8((1).toChar())
                    const value_value_2_1  = value_value_2 as Resource
                    Resource_serializer.write(thisSerializer, value_value_2_1)
                }
            }
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setFontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontFamilyAttribute(value: ResourceStr | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setFontFamily(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextOverflowAttribute(value: TextOverflow | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as TextOverflow)
            thisSerializer.writeInt32(TypeChecker.TextOverflow_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setTextOverflow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextIndentAttribute(value: Dimension | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setTextIndent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCaretStyleAttribute(value: CaretStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            CaretStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setCaretStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedBackgroundColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((3).toChar())
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setSelectedBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSubmitAttribute(value: ((enterKey: EnterKeyType) => void) | TextAreaSubmitCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.FUNCTION == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as ((enterKey: EnterKeyType) => void)
                thisSerializer.holdAndWriteCallback(value_value_0)
            }
            else if (RuntimeType.FUNCTION == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as TextAreaSubmitCallback
                thisSerializer.holdAndWriteCallback(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setOnSubmit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: EditableTextOnChangeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setOnChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnTextSelectionChangeAttribute(value: ((selectionStart: number,selectionEnd: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setOnTextSelectionChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnContentScrollAttribute(value: ((selectionStart: number,selectionEnd: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setOnContentScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnEditChangeAttribute(value: ((isEditing: boolean) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setOnEditChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnCopyAttribute(value: ((value: string) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setOnCopy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnCutAttribute(value: ((value: string) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setOnCut(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnPasteAttribute(value: ((value: string,event: PasteEvent) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setOnPaste(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCopyOptionAttribute(value: CopyOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as CopyOptions)
            thisSerializer.writeInt32(TypeChecker.CopyOptions_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setCopyOption(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableKeyboardOnFocusAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setEnableKeyboardOnFocus(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxLengthAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setMaxLength(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStyleAttribute(value: TextContentStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as TextContentStyle)
            thisSerializer.writeInt32(TypeChecker.TextContentStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBarStateAttribute(value: BarState | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as BarState)
            thisSerializer.writeInt32(TypeChecker.BarState_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setBarState(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectionMenuHiddenAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setSelectionMenuHidden(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinFontSizeAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setMinFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxFontSizeAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setMaxFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinFontScaleAttribute(value: number | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setMinFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxFontScaleAttribute(value: number | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setMaxFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setHeightAdaptivePolicyAttribute(value: TextHeightAdaptivePolicy | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as TextHeightAdaptivePolicy)
            thisSerializer.writeInt32(TypeChecker.TextHeightAdaptivePolicy_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setHeightAdaptivePolicy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxLinesAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setMaxLines(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setWordBreakAttribute(value: WordBreak | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as WordBreak)
            thisSerializer.writeInt32(TypeChecker.WordBreak_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setWordBreak(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLineBreakStrategyAttribute(value: LineBreakStrategy | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as LineBreakStrategy)
            thisSerializer.writeInt32(TypeChecker.LineBreakStrategy_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setLineBreakStrategy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDecorationAttribute(value: TextDecorationOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            TextDecorationOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setDecoration(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLetterSpacingAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setLetterSpacing(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLineSpacingAttribute(value: LengthMetrics | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            LengthMetrics_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setLineSpacing(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLineHeightAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setLineHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTypeAttribute(value: TextAreaType | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as TextAreaType)
            thisSerializer.writeInt32(TypeChecker.TextAreaType_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setType(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableAutoFillAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setEnableAutoFill(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setContentTypeAttribute(value: ContentType | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as ContentType)
            thisSerializer.writeInt32(TypeChecker.ContentType_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setContentType(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontFeatureAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setFontFeature(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnWillInsertAttribute(value: ((value0: InsertValue) => boolean) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setOnWillInsert(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnDidInsertAttribute(value: ((value0: InsertValue) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setOnDidInsert(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnWillDeleteAttribute(value: ((value0: DeleteValue) => boolean) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setOnWillDelete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnDidDeleteAttribute(value: ((value0: DeleteValue) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setOnDidDelete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEditMenuOptionsAttribute(value: EditMenuOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            EditMenuOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setEditMenuOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnablePreviewTextAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setEnablePreviewText(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableHapticFeedbackAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setEnableHapticFeedback(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAutoCapitalizationModeAttribute(value: AutoCapitalizationMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as AutoCapitalizationMode)
            thisSerializer.writeInt32(TypeChecker.AutoCapitalizationMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setAutoCapitalizationMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setHalfLeadingAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setHalfLeading(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEllipsisModeAttribute(value: EllipsisMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as EllipsisMode)
            thisSerializer.writeInt32(TypeChecker.EllipsisMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setEllipsisMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStopBackPressAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setStopBackPress(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnWillChangeAttribute(value: ((value0: EditableTextChangeValue) => boolean) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setOnWillChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setKeyboardAppearanceAttribute(value: KeyboardAppearance | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as KeyboardAppearance)
            thisSerializer.writeInt32(TypeChecker.KeyboardAppearance_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setKeyboardAppearance(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setInputFilterAttribute(value: ResourceStr | undefined, error?: ((value: string) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_1)
            }
        }
        let error_type : int32 = RuntimeType.UNDEFINED
        error_type = runtimeType(error)
        thisSerializer.writeInt8((error_type).toChar())
        if ((error_type) != (RuntimeType.UNDEFINED)) {
            const error_value  = error!
            thisSerializer.holdAndWriteCallback(error_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setInputFilter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setShowCounterAttribute(value: boolean | undefined, options?: InputCounterOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            InputCounterOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setShowCounter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCustomKeyboardAttribute(value: CustomBuilder | undefined, options?: KeyboardOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_value))
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            KeyboardOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._TextAreaAttribute_setCustomKeyboard(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    set_onChangeEvent_textAttribute(callback_: ((text: ResourceStr | Resource | string) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._TextAreaAttribute_set_onChangeEvent_text(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface TextAreaOptions {
    placeholder?: ResourceStr;
    text?: ResourceStr | Resource | string;
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
export type TextAreaSubmitCallback = (enterKeyType: EnterKeyType, event?: SubmitEvent) => void;
export interface TextAreaAttribute extends CommonMethod {
    placeholderColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method placeholderColor")
    }
    placeholderFont(value: Font | undefined): this {
        throw new Error("Unimplemented method placeholderFont")
    }
    enterKeyType(value: EnterKeyType | undefined): this {
        throw new Error("Unimplemented method enterKeyType")
    }
    textAlign(value: TextAlign | undefined): this {
        throw new Error("Unimplemented method textAlign")
    }
    caretColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method caretColor")
    }
    fontColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method fontColor")
    }
    fontSize(value: Length | undefined): this {
        throw new Error("Unimplemented method fontSize")
    }
    fontStyle(value: FontStyle | undefined): this {
        throw new Error("Unimplemented method fontStyle")
    }
    fontWeight(value: number | FontWeight | ResourceStr | undefined): this {
        throw new Error("Unimplemented method fontWeight")
    }
    fontFamily(value: ResourceStr | undefined): this {
        throw new Error("Unimplemented method fontFamily")
    }
    textOverflow(value: TextOverflow | undefined): this {
        throw new Error("Unimplemented method textOverflow")
    }
    textIndent(value: Dimension | undefined): this {
        throw new Error("Unimplemented method textIndent")
    }
    caretStyle(value: CaretStyle | undefined): this {
        throw new Error("Unimplemented method caretStyle")
    }
    selectedBackgroundColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method selectedBackgroundColor")
    }
    onSubmit(value: ((enterKey: EnterKeyType) => void) | TextAreaSubmitCallback | undefined): this {
        throw new Error("Unimplemented method onSubmit")
    }
    onChange(value: EditableTextOnChangeCallback | undefined): this {
        throw new Error("Unimplemented method onChange")
    }
    onTextSelectionChange(value: ((selectionStart: number,selectionEnd: number) => void) | undefined): this {
        throw new Error("Unimplemented method onTextSelectionChange")
    }
    onContentScroll(value: ((selectionStart: number,selectionEnd: number) => void) | undefined): this {
        throw new Error("Unimplemented method onContentScroll")
    }
    onEditChange(value: ((isEditing: boolean) => void) | undefined): this {
        throw new Error("Unimplemented method onEditChange")
    }
    onCopy(value: ((value: string) => void) | undefined): this {
        throw new Error("Unimplemented method onCopy")
    }
    onCut(value: ((value: string) => void) | undefined): this {
        throw new Error("Unimplemented method onCut")
    }
    onPaste(value: ((value: string,event: PasteEvent) => void) | undefined): this {
        throw new Error("Unimplemented method onPaste")
    }
    copyOption(value: CopyOptions | undefined): this {
        throw new Error("Unimplemented method copyOption")
    }
    enableKeyboardOnFocus(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableKeyboardOnFocus")
    }
    maxLength(value: number | undefined): this {
        throw new Error("Unimplemented method maxLength")
    }
    style(value: TextContentStyle | undefined): this {
        throw new Error("Unimplemented method style")
    }
    barState(value: BarState | undefined): this {
        throw new Error("Unimplemented method barState")
    }
    selectionMenuHidden(value: boolean | undefined): this {
        throw new Error("Unimplemented method selectionMenuHidden")
    }
    minFontSize(value: number | string | Resource | undefined): this {
        throw new Error("Unimplemented method minFontSize")
    }
    maxFontSize(value: number | string | Resource | undefined): this {
        throw new Error("Unimplemented method maxFontSize")
    }
    minFontScale(value: number | Resource | undefined): this {
        throw new Error("Unimplemented method minFontScale")
    }
    maxFontScale(value: number | Resource | undefined): this {
        throw new Error("Unimplemented method maxFontScale")
    }
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy | undefined): this {
        throw new Error("Unimplemented method heightAdaptivePolicy")
    }
    maxLines(value: number | undefined): this {
        throw new Error("Unimplemented method maxLines")
    }
    wordBreak(value: WordBreak | undefined): this {
        throw new Error("Unimplemented method wordBreak")
    }
    lineBreakStrategy(value: LineBreakStrategy | undefined): this {
        throw new Error("Unimplemented method lineBreakStrategy")
    }
    decoration(value: TextDecorationOptions | undefined): this {
        throw new Error("Unimplemented method decoration")
    }
    letterSpacing(value: number | string | Resource | undefined): this {
        throw new Error("Unimplemented method letterSpacing")
    }
    lineSpacing(value: LengthMetrics | undefined): this {
        throw new Error("Unimplemented method lineSpacing")
    }
    lineHeight(value: number | string | Resource | undefined): this {
        throw new Error("Unimplemented method lineHeight")
    }
    type(value: TextAreaType | undefined): this {
        throw new Error("Unimplemented method type")
    }
    enableAutoFill(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableAutoFill")
    }
    contentType(value: ContentType | undefined): this {
        throw new Error("Unimplemented method contentType")
    }
    fontFeature(value: string | undefined): this {
        throw new Error("Unimplemented method fontFeature")
    }
    onWillInsert(value: ((value0: InsertValue) => boolean) | undefined): this {
        throw new Error("Unimplemented method onWillInsert")
    }
    onDidInsert(value: ((value0: InsertValue) => void) | undefined): this {
        throw new Error("Unimplemented method onDidInsert")
    }
    onWillDelete(value: ((value0: DeleteValue) => boolean) | undefined): this {
        throw new Error("Unimplemented method onWillDelete")
    }
    onDidDelete(value: ((value0: DeleteValue) => void) | undefined): this {
        throw new Error("Unimplemented method onDidDelete")
    }
    editMenuOptions(value: EditMenuOptions | undefined): this {
        throw new Error("Unimplemented method editMenuOptions")
    }
    enablePreviewText(value: boolean | undefined): this {
        throw new Error("Unimplemented method enablePreviewText")
    }
    enableHapticFeedback(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableHapticFeedback")
    }
    autoCapitalizationMode(value: AutoCapitalizationMode | undefined): this {
        throw new Error("Unimplemented method autoCapitalizationMode")
    }
    halfLeading(value: boolean | undefined): this {
        throw new Error("Unimplemented method halfLeading")
    }
    ellipsisMode(value: EllipsisMode | undefined): this {
        throw new Error("Unimplemented method ellipsisMode")
    }
    stopBackPress(value: boolean | undefined): this {
        throw new Error("Unimplemented method stopBackPress")
    }
    onWillChange(value: ((value0: EditableTextChangeValue) => boolean) | undefined): this {
        throw new Error("Unimplemented method onWillChange")
    }
    keyboardAppearance(value: KeyboardAppearance | undefined): this {
        throw new Error("Unimplemented method keyboardAppearance")
    }
    inputFilter(value: ResourceStr | undefined, error?: ((value: string) => void)): this {
        throw new Error("Unimplemented method inputFilter")
    }
    showCounter(value: boolean | undefined, options?: InputCounterOptions): this {
        throw new Error("Unimplemented method showCounter")
    }
    customKeyboard(value: CustomBuilder | undefined, options?: KeyboardOptions): this {
        throw new Error("Unimplemented method customKeyboard")
    }
    _onChangeEvent_text(callback_: ((text: ResourceStr | Resource | string) => void)): void {
        throw new Error("Unimplemented method _onChangeEvent_text")
    }
    attributeModifier(value: AttributeModifier<TextAreaAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
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
    fontWeight_value?: number | FontWeight | ResourceStr | undefined
    fontFamily_value?: ResourceStr | undefined
    textOverflow_value?: TextOverflow | undefined
    textIndent_value?: Dimension | undefined
    caretStyle_value?: CaretStyle | undefined
    selectedBackgroundColor_value?: ResourceColor | undefined
    onSubmit_value?: ((enterKey: EnterKeyType) => void) | TextAreaSubmitCallback | undefined
    onChange_value?: EditableTextOnChangeCallback | undefined
    onTextSelectionChange_value?: ((selectionStart: number,selectionEnd: number) => void) | undefined
    onContentScroll_value?: ((selectionStart: number,selectionEnd: number) => void) | undefined
    onEditChange_value?: ((isEditing: boolean) => void) | undefined
    onCopy_value?: ((value: string) => void) | undefined
    onCut_value?: ((value: string) => void) | undefined
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
    onWillInsert_value?: ((value0: InsertValue) => boolean) | undefined
    onDidInsert_value?: ((value0: InsertValue) => void) | undefined
    onWillDelete_value?: ((value0: DeleteValue) => boolean) | undefined
    onDidDelete_value?: ((value0: DeleteValue) => void) | undefined
    editMenuOptions_value?: EditMenuOptions | undefined
    enablePreviewText_value?: boolean | undefined
    enableHapticFeedback_value?: boolean | undefined
    autoCapitalizationMode_value?: AutoCapitalizationMode | undefined
    halfLeading_value?: boolean | undefined
    ellipsisMode_value?: EllipsisMode | undefined
    stopBackPress_value?: boolean | undefined
    onWillChange_value?: ((value0: EditableTextChangeValue) => boolean) | undefined
    keyboardAppearance_value?: KeyboardAppearance | undefined
    attributeModifier_value?: AttributeModifier<TextAreaAttribute> | AttributeModifier<CommonMethod> | undefined
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
    public fontWeight(value: number | FontWeight | ResourceStr | undefined): this {
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
    public onSubmit(value: ((enterKey: EnterKeyType) => void) | TextAreaSubmitCallback | undefined): this {
        return this
    }
    public onChange(value: EditableTextOnChangeCallback | undefined): this {
        return this
    }
    public onTextSelectionChange(value: ((selectionStart: number,selectionEnd: number) => void) | undefined): this {
        return this
    }
    public onContentScroll(value: ((selectionStart: number,selectionEnd: number) => void) | undefined): this {
        return this
    }
    public onEditChange(value: ((isEditing: boolean) => void) | undefined): this {
        return this
    }
    public onCopy(value: ((value: string) => void) | undefined): this {
        return this
    }
    public onCut(value: ((value: string) => void) | undefined): this {
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
    public onWillInsert(value: ((value0: InsertValue) => boolean) | undefined): this {
        return this
    }
    public onDidInsert(value: ((value0: InsertValue) => void) | undefined): this {
        return this
    }
    public onWillDelete(value: ((value0: DeleteValue) => boolean) | undefined): this {
        return this
    }
    public onDidDelete(value: ((value0: DeleteValue) => void) | undefined): this {
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
    public onWillChange(value: ((value0: EditableTextChangeValue) => boolean) | undefined): this {
        return this
    }
    public keyboardAppearance(value: KeyboardAppearance | undefined): this {
        return this
    }
    public inputFilter(value: ResourceStr | undefined, error?: ((value: string) => void)): this {
        return this
    }
    public showCounter(value: boolean | undefined, options?: InputCounterOptions): this {
        return this
    }
    public customKeyboard(value: CustomBuilder | undefined, options?: KeyboardOptions): this {
        return this
    }
    public _onChangeEvent_text(callback_: ((text: ResourceStr | Resource | string) => void)): void {
        throw new Error("Unimplemented")
    }
    public attributeModifier(value: AttributeModifier<TextAreaAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: TextAreaAttribute): void {
        super.apply(target)
        if (this.placeholderColor_value !== undefined)
            target.placeholderColor(this.placeholderColor_value!)
        if (this.placeholderFont_value !== undefined)
            target.placeholderFont(this.placeholderFont_value!)
        if (this.enterKeyType_value !== undefined)
            target.enterKeyType(this.enterKeyType_value!)
        if (this.textAlign_value !== undefined)
            target.textAlign(this.textAlign_value!)
        if (this.caretColor_value !== undefined)
            target.caretColor(this.caretColor_value!)
        if (this.fontColor_value !== undefined)
            target.fontColor(this.fontColor_value!)
        if (this.fontSize_value !== undefined)
            target.fontSize(this.fontSize_value!)
        if (this.fontStyle_value !== undefined)
            target.fontStyle(this.fontStyle_value!)
        if (this.fontWeight_value !== undefined)
            target.fontWeight(this.fontWeight_value!)
        if (this.fontFamily_value !== undefined)
            target.fontFamily(this.fontFamily_value!)
        if (this.textOverflow_value !== undefined)
            target.textOverflow(this.textOverflow_value!)
        if (this.textIndent_value !== undefined)
            target.textIndent(this.textIndent_value!)
        if (this.caretStyle_value !== undefined)
            target.caretStyle(this.caretStyle_value!)
        if (this.selectedBackgroundColor_value !== undefined)
            target.selectedBackgroundColor(this.selectedBackgroundColor_value!)
        if (this.onSubmit_value !== undefined)
            target.onSubmit(this.onSubmit_value!)
        if (this.onChange_value !== undefined)
            target.onChange(this.onChange_value!)
        if (this.onTextSelectionChange_value !== undefined)
            target.onTextSelectionChange(this.onTextSelectionChange_value!)
        if (this.onContentScroll_value !== undefined)
            target.onContentScroll(this.onContentScroll_value!)
        if (this.onEditChange_value !== undefined)
            target.onEditChange(this.onEditChange_value!)
        if (this.onCopy_value !== undefined)
            target.onCopy(this.onCopy_value!)
        if (this.onCut_value !== undefined)
            target.onCut(this.onCut_value!)
        if (this.onPaste_value !== undefined)
            target.onPaste(this.onPaste_value!)
        if (this.copyOption_value !== undefined)
            target.copyOption(this.copyOption_value!)
        if (this.enableKeyboardOnFocus_value !== undefined)
            target.enableKeyboardOnFocus(this.enableKeyboardOnFocus_value!)
        if (this.maxLength_value !== undefined)
            target.maxLength(this.maxLength_value!)
        if (this.style_value !== undefined)
            target.style(this.style_value!)
        if (this.barState_value !== undefined)
            target.barState(this.barState_value!)
        if (this.selectionMenuHidden_value !== undefined)
            target.selectionMenuHidden(this.selectionMenuHidden_value!)
        if (this.minFontSize_value !== undefined)
            target.minFontSize(this.minFontSize_value!)
        if (this.maxFontSize_value !== undefined)
            target.maxFontSize(this.maxFontSize_value!)
        if (this.minFontScale_value !== undefined)
            target.minFontScale(this.minFontScale_value!)
        if (this.maxFontScale_value !== undefined)
            target.maxFontScale(this.maxFontScale_value!)
        if (this.heightAdaptivePolicy_value !== undefined)
            target.heightAdaptivePolicy(this.heightAdaptivePolicy_value!)
        if (this.maxLines_value !== undefined)
            target.maxLines(this.maxLines_value!)
        if (this.wordBreak_value !== undefined)
            target.wordBreak(this.wordBreak_value!)
        if (this.lineBreakStrategy_value !== undefined)
            target.lineBreakStrategy(this.lineBreakStrategy_value!)
        if (this.decoration_value !== undefined)
            target.decoration(this.decoration_value!)
        if (this.letterSpacing_value !== undefined)
            target.letterSpacing(this.letterSpacing_value!)
        if (this.lineSpacing_value !== undefined)
            target.lineSpacing(this.lineSpacing_value!)
        if (this.lineHeight_value !== undefined)
            target.lineHeight(this.lineHeight_value!)
        if (this.type_value !== undefined)
            target.type(this.type_value!)
        if (this.enableAutoFill_value !== undefined)
            target.enableAutoFill(this.enableAutoFill_value!)
        if (this.contentType_value !== undefined)
            target.contentType(this.contentType_value!)
        if (this.fontFeature_value !== undefined)
            target.fontFeature(this.fontFeature_value!)
        if (this.onWillInsert_value !== undefined)
            target.onWillInsert(this.onWillInsert_value!)
        if (this.onDidInsert_value !== undefined)
            target.onDidInsert(this.onDidInsert_value!)
        if (this.onWillDelete_value !== undefined)
            target.onWillDelete(this.onWillDelete_value!)
        if (this.onDidDelete_value !== undefined)
            target.onDidDelete(this.onDidDelete_value!)
        if (this.editMenuOptions_value !== undefined)
            target.editMenuOptions(this.editMenuOptions_value!)
        if (this.enablePreviewText_value !== undefined)
            target.enablePreviewText(this.enablePreviewText_value!)
        if (this.enableHapticFeedback_value !== undefined)
            target.enableHapticFeedback(this.enableHapticFeedback_value!)
        if (this.autoCapitalizationMode_value !== undefined)
            target.autoCapitalizationMode(this.autoCapitalizationMode_value!)
        if (this.halfLeading_value !== undefined)
            target.halfLeading(this.halfLeading_value!)
        if (this.ellipsisMode_value !== undefined)
            target.ellipsisMode(this.ellipsisMode_value!)
        if (this.stopBackPress_value !== undefined)
            target.stopBackPress(this.stopBackPress_value!)
        if (this.onWillChange_value !== undefined)
            target.onWillChange(this.onWillChange_value!)
        if (this.keyboardAppearance_value !== undefined)
            target.keyboardAppearance(this.keyboardAppearance_value!)
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
            this.getPeer()?.setPlaceholderColorAttribute(value_casted)
            return this
        }
        return this
    }
    public placeholderFont(value: Font | undefined): this {
        if (this.checkPriority("placeholderFont")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.setPlaceholderFontAttribute(value_casted)
            return this
        }
        return this
    }
    public enterKeyType(value: EnterKeyType | undefined): this {
        if (this.checkPriority("enterKeyType")) {
            const value_casted = value as (EnterKeyType | undefined)
            this.getPeer()?.setEnterKeyTypeAttribute(value_casted)
            return this
        }
        return this
    }
    public textAlign(value: TextAlign | undefined): this {
        if (this.checkPriority("textAlign")) {
            const value_casted = value as (TextAlign | undefined)
            this.getPeer()?.setTextAlignAttribute(value_casted)
            return this
        }
        return this
    }
    public caretColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("caretColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setCaretColorAttribute(value_casted)
            return this
        }
        return this
    }
    public fontColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("fontColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setFontColorAttribute(value_casted)
            return this
        }
        return this
    }
    public fontSize(value: Length | undefined): this {
        if (this.checkPriority("fontSize")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public fontStyle(value: FontStyle | undefined): this {
        if (this.checkPriority("fontStyle")) {
            const value_casted = value as (FontStyle | undefined)
            this.getPeer()?.setFontStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public fontWeight(value: number | FontWeight | ResourceStr | undefined): this {
        if (this.checkPriority("fontWeight")) {
            const value_casted = value as (number | FontWeight | ResourceStr | undefined)
            this.getPeer()?.setFontWeightAttribute(value_casted)
            return this
        }
        return this
    }
    public fontFamily(value: ResourceStr | undefined): this {
        if (this.checkPriority("fontFamily")) {
            const value_casted = value as (ResourceStr | undefined)
            this.getPeer()?.setFontFamilyAttribute(value_casted)
            return this
        }
        return this
    }
    public textOverflow(value: TextOverflow | undefined): this {
        if (this.checkPriority("textOverflow")) {
            const value_casted = value as (TextOverflow | undefined)
            this.getPeer()?.setTextOverflowAttribute(value_casted)
            return this
        }
        return this
    }
    public textIndent(value: Dimension | undefined): this {
        if (this.checkPriority("textIndent")) {
            const value_casted = value as (Dimension | undefined)
            this.getPeer()?.setTextIndentAttribute(value_casted)
            return this
        }
        return this
    }
    public caretStyle(value: CaretStyle | undefined): this {
        if (this.checkPriority("caretStyle")) {
            const value_casted = value as (CaretStyle | undefined)
            this.getPeer()?.setCaretStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedBackgroundColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("selectedBackgroundColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setSelectedBackgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    public onSubmit(value: ((enterKey: EnterKeyType) => void) | TextAreaSubmitCallback | undefined): this {
        if (this.checkPriority("onSubmit")) {
            const value_casted = value as (((enterKey: EnterKeyType) => void) | TextAreaSubmitCallback | undefined)
            this.getPeer()?.setOnSubmitAttribute(value_casted)
            return this
        }
        return this
    }
    public onChange(value: EditableTextOnChangeCallback | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (EditableTextOnChangeCallback | undefined)
            this.getPeer()?.setOnChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onTextSelectionChange(value: ((selectionStart: number,selectionEnd: number) => void) | undefined): this {
        if (this.checkPriority("onTextSelectionChange")) {
            const value_casted = value as (((selectionStart: number,selectionEnd: number) => void) | undefined)
            this.getPeer()?.setOnTextSelectionChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onContentScroll(value: ((selectionStart: number,selectionEnd: number) => void) | undefined): this {
        if (this.checkPriority("onContentScroll")) {
            const value_casted = value as (((selectionStart: number,selectionEnd: number) => void) | undefined)
            this.getPeer()?.setOnContentScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public onEditChange(value: ((isEditing: boolean) => void) | undefined): this {
        if (this.checkPriority("onEditChange")) {
            const value_casted = value as (((isEditing: boolean) => void) | undefined)
            this.getPeer()?.setOnEditChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onCopy(value: ((value: string) => void) | undefined): this {
        if (this.checkPriority("onCopy")) {
            const value_casted = value as (((value: string) => void) | undefined)
            this.getPeer()?.setOnCopyAttribute(value_casted)
            return this
        }
        return this
    }
    public onCut(value: ((value: string) => void) | undefined): this {
        if (this.checkPriority("onCut")) {
            const value_casted = value as (((value: string) => void) | undefined)
            this.getPeer()?.setOnCutAttribute(value_casted)
            return this
        }
        return this
    }
    public onPaste(value: ((value: string,event: PasteEvent) => void) | undefined): this {
        if (this.checkPriority("onPaste")) {
            const value_casted = value as (((value: string,event: PasteEvent) => void) | undefined)
            this.getPeer()?.setOnPasteAttribute(value_casted)
            return this
        }
        return this
    }
    public copyOption(value: CopyOptions | undefined): this {
        if (this.checkPriority("copyOption")) {
            const value_casted = value as (CopyOptions | undefined)
            this.getPeer()?.setCopyOptionAttribute(value_casted)
            return this
        }
        return this
    }
    public enableKeyboardOnFocus(value: boolean | undefined): this {
        if (this.checkPriority("enableKeyboardOnFocus")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableKeyboardOnFocusAttribute(value_casted)
            return this
        }
        return this
    }
    public maxLength(value: number | undefined): this {
        if (this.checkPriority("maxLength")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setMaxLengthAttribute(value_casted)
            return this
        }
        return this
    }
    public style(value: TextContentStyle | undefined): this {
        if (this.checkPriority("style")) {
            const value_casted = value as (TextContentStyle | undefined)
            this.getPeer()?.setStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public barState(value: BarState | undefined): this {
        if (this.checkPriority("barState")) {
            const value_casted = value as (BarState | undefined)
            this.getPeer()?.setBarStateAttribute(value_casted)
            return this
        }
        return this
    }
    public selectionMenuHidden(value: boolean | undefined): this {
        if (this.checkPriority("selectionMenuHidden")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setSelectionMenuHiddenAttribute(value_casted)
            return this
        }
        return this
    }
    public minFontSize(value: number | string | Resource | undefined): this {
        if (this.checkPriority("minFontSize")) {
            const value_casted = value as (number | string | Resource | undefined)
            this.getPeer()?.setMinFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public maxFontSize(value: number | string | Resource | undefined): this {
        if (this.checkPriority("maxFontSize")) {
            const value_casted = value as (number | string | Resource | undefined)
            this.getPeer()?.setMaxFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public minFontScale(value: number | Resource | undefined): this {
        if (this.checkPriority("minFontScale")) {
            const value_casted = value as (number | Resource | undefined)
            this.getPeer()?.setMinFontScaleAttribute(value_casted)
            return this
        }
        return this
    }
    public maxFontScale(value: number | Resource | undefined): this {
        if (this.checkPriority("maxFontScale")) {
            const value_casted = value as (number | Resource | undefined)
            this.getPeer()?.setMaxFontScaleAttribute(value_casted)
            return this
        }
        return this
    }
    public heightAdaptivePolicy(value: TextHeightAdaptivePolicy | undefined): this {
        if (this.checkPriority("heightAdaptivePolicy")) {
            const value_casted = value as (TextHeightAdaptivePolicy | undefined)
            this.getPeer()?.setHeightAdaptivePolicyAttribute(value_casted)
            return this
        }
        return this
    }
    public maxLines(value: number | undefined): this {
        if (this.checkPriority("maxLines")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setMaxLinesAttribute(value_casted)
            return this
        }
        return this
    }
    public wordBreak(value: WordBreak | undefined): this {
        if (this.checkPriority("wordBreak")) {
            const value_casted = value as (WordBreak | undefined)
            this.getPeer()?.setWordBreakAttribute(value_casted)
            return this
        }
        return this
    }
    public lineBreakStrategy(value: LineBreakStrategy | undefined): this {
        if (this.checkPriority("lineBreakStrategy")) {
            const value_casted = value as (LineBreakStrategy | undefined)
            this.getPeer()?.setLineBreakStrategyAttribute(value_casted)
            return this
        }
        return this
    }
    public decoration(value: TextDecorationOptions | undefined): this {
        if (this.checkPriority("decoration")) {
            const value_casted = value as (TextDecorationOptions | undefined)
            this.getPeer()?.setDecorationAttribute(value_casted)
            return this
        }
        return this
    }
    public letterSpacing(value: number | string | Resource | undefined): this {
        if (this.checkPriority("letterSpacing")) {
            const value_casted = value as (number | string | Resource | undefined)
            this.getPeer()?.setLetterSpacingAttribute(value_casted)
            return this
        }
        return this
    }
    public lineSpacing(value: LengthMetrics | undefined): this {
        if (this.checkPriority("lineSpacing")) {
            const value_casted = value as (LengthMetrics | undefined)
            this.getPeer()?.setLineSpacingAttribute(value_casted)
            return this
        }
        return this
    }
    public lineHeight(value: number | string | Resource | undefined): this {
        if (this.checkPriority("lineHeight")) {
            const value_casted = value as (number | string | Resource | undefined)
            this.getPeer()?.setLineHeightAttribute(value_casted)
            return this
        }
        return this
    }
    public type(value: TextAreaType | undefined): this {
        if (this.checkPriority("type")) {
            const value_casted = value as (TextAreaType | undefined)
            this.getPeer()?.setTypeAttribute(value_casted)
            return this
        }
        return this
    }
    public enableAutoFill(value: boolean | undefined): this {
        if (this.checkPriority("enableAutoFill")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableAutoFillAttribute(value_casted)
            return this
        }
        return this
    }
    public contentType(value: ContentType | undefined): this {
        if (this.checkPriority("contentType")) {
            const value_casted = value as (ContentType | undefined)
            this.getPeer()?.setContentTypeAttribute(value_casted)
            return this
        }
        return this
    }
    public fontFeature(value: string | undefined): this {
        if (this.checkPriority("fontFeature")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.setFontFeatureAttribute(value_casted)
            return this
        }
        return this
    }
    public onWillInsert(value: ((value0: InsertValue) => boolean) | undefined): this {
        if (this.checkPriority("onWillInsert")) {
            const value_casted = value as (((value0: InsertValue) => boolean) | undefined)
            this.getPeer()?.setOnWillInsertAttribute(value_casted)
            return this
        }
        return this
    }
    public onDidInsert(value: ((value0: InsertValue) => void) | undefined): this {
        if (this.checkPriority("onDidInsert")) {
            const value_casted = value as (((value0: InsertValue) => void) | undefined)
            this.getPeer()?.setOnDidInsertAttribute(value_casted)
            return this
        }
        return this
    }
    public onWillDelete(value: ((value0: DeleteValue) => boolean) | undefined): this {
        if (this.checkPriority("onWillDelete")) {
            const value_casted = value as (((value0: DeleteValue) => boolean) | undefined)
            this.getPeer()?.setOnWillDeleteAttribute(value_casted)
            return this
        }
        return this
    }
    public onDidDelete(value: ((value0: DeleteValue) => void) | undefined): this {
        if (this.checkPriority("onDidDelete")) {
            const value_casted = value as (((value0: DeleteValue) => void) | undefined)
            this.getPeer()?.setOnDidDeleteAttribute(value_casted)
            return this
        }
        return this
    }
    public editMenuOptions(value: EditMenuOptions | undefined): this {
        if (this.checkPriority("editMenuOptions")) {
            const value_casted = value as (EditMenuOptions | undefined)
            this.getPeer()?.setEditMenuOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public enablePreviewText(value: boolean | undefined): this {
        if (this.checkPriority("enablePreviewText")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnablePreviewTextAttribute(value_casted)
            return this
        }
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        if (this.checkPriority("enableHapticFeedback")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableHapticFeedbackAttribute(value_casted)
            return this
        }
        return this
    }
    public autoCapitalizationMode(value: AutoCapitalizationMode | undefined): this {
        if (this.checkPriority("autoCapitalizationMode")) {
            const value_casted = value as (AutoCapitalizationMode | undefined)
            this.getPeer()?.setAutoCapitalizationModeAttribute(value_casted)
            return this
        }
        return this
    }
    public halfLeading(value: boolean | undefined): this {
        if (this.checkPriority("halfLeading")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setHalfLeadingAttribute(value_casted)
            return this
        }
        return this
    }
    public ellipsisMode(value: EllipsisMode | undefined): this {
        if (this.checkPriority("ellipsisMode")) {
            const value_casted = value as (EllipsisMode | undefined)
            this.getPeer()?.setEllipsisModeAttribute(value_casted)
            return this
        }
        return this
    }
    public stopBackPress(value: boolean | undefined): this {
        if (this.checkPriority("stopBackPress")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setStopBackPressAttribute(value_casted)
            return this
        }
        return this
    }
    public onWillChange(value: ((value0: EditableTextChangeValue) => boolean) | undefined): this {
        if (this.checkPriority("onWillChange")) {
            const value_casted = value as (((value0: EditableTextChangeValue) => boolean) | undefined)
            this.getPeer()?.setOnWillChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public keyboardAppearance(value: KeyboardAppearance | undefined): this {
        if (this.checkPriority("keyboardAppearance")) {
            const value_casted = value as (KeyboardAppearance | undefined)
            this.getPeer()?.setKeyboardAppearanceAttribute(value_casted)
            return this
        }
        return this
    }
    public inputFilter(value: ResourceStr | undefined, error?: ((value: string) => void)): this {
        if (this.checkPriority("inputFilter")) {
            const value_casted = value as (ResourceStr | undefined)
            const error_casted = error as (((value: string) => void) | undefined)
            this.getPeer()?.setInputFilterAttribute(value_casted, error_casted)
            return this
        }
        return this
    }
    public showCounter(value: boolean | undefined, options?: InputCounterOptions): this {
        if (this.checkPriority("showCounter")) {
            const value_casted = value as (boolean | undefined)
            const options_casted = options as (InputCounterOptions | undefined)
            this.getPeer()?.setShowCounterAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    public customKeyboard(value: CustomBuilder | undefined, options?: KeyboardOptions): this {
        if (this.checkPriority("customKeyboard")) {
            const value_casted = value as (CustomBuilder | undefined)
            const options_casted = options as (KeyboardOptions | undefined)
            this.getPeer()?.setCustomKeyboardAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    public _onChangeEvent_text(callback_: ((text: ResourceStr | Resource | string) => void)): void {
        if (this.checkPriority("_onChangeEvent_text")) {
            const callback__casted = callback_ as (((text: ResourceStr | Resource | string) => void))
            this.getPeer()?.set_onChangeEvent_textAttribute(callback__casted)
            return
        }
        return
    }
    public attributeModifier(value: AttributeModifier<TextAreaAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withTextAreaStyle(receiver: TextAreaAttribute, modifier: AttributeModifier<TextAreaAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkTextAreaStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("TextArea")
// export function TextArea(
//     value?: TextAreaOptions,
//     @memo
//     content_?: () => void,
// ): TextAreaAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function TextArea(
    @memo
    style: ((attributes: TextAreaAttribute) => void) | undefined,
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
        withTextAreaStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkTextAreaSet extends ArkCommonMethodSet implements TextAreaAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _placeholderColor_flag?: boolean
    _placeholderColor0_value?: ResourceColor | undefined
    _placeholderFont_flag?: boolean
    _placeholderFont0_value?: Font | undefined
    _enterKeyType_flag?: boolean
    _enterKeyType0_value?: EnterKeyType | undefined
    _textAlign_flag?: boolean
    _textAlign0_value?: TextAlign | undefined
    _caretColor_flag?: boolean
    _caretColor0_value?: ResourceColor | undefined
    _fontColor_flag?: boolean
    _fontColor0_value?: ResourceColor | undefined
    _fontSize_flag?: boolean
    _fontSize0_value?: Length | undefined
    _fontStyle_flag?: boolean
    _fontStyle0_value?: FontStyle | undefined
    _fontWeight_flag?: boolean
    _fontWeight0_value?: number | FontWeight | ResourceStr | undefined
    _fontFamily_flag?: boolean
    _fontFamily0_value?: ResourceStr | undefined
    _textOverflow_flag?: boolean
    _textOverflow0_value?: TextOverflow | undefined
    _textIndent_flag?: boolean
    _textIndent0_value?: Dimension | undefined
    _caretStyle_flag?: boolean
    _caretStyle0_value?: CaretStyle | undefined
    _selectedBackgroundColor_flag?: boolean
    _selectedBackgroundColor0_value?: ResourceColor | undefined
    _onSubmit_flag?: boolean
    _onSubmit0_value?: ((enterKey: EnterKeyType) => void) | TextAreaSubmitCallback | undefined
    _onChange_flag?: boolean
    _onChange0_value?: EditableTextOnChangeCallback | undefined
    _onTextSelectionChange_flag?: boolean
    _onTextSelectionChange0_value?: ((selectionStart: number,selectionEnd: number) => void) | undefined
    _onContentScroll_flag?: boolean
    _onContentScroll0_value?: ((selectionStart: number,selectionEnd: number) => void) | undefined
    _onEditChange_flag?: boolean
    _onEditChange0_value?: ((isEditing: boolean) => void) | undefined
    _onCopy_flag?: boolean
    _onCopy0_value?: ((value: string) => void) | undefined
    _onCut_flag?: boolean
    _onCut0_value?: ((value: string) => void) | undefined
    _onPaste_flag?: boolean
    _onPaste0_value?: ((value: string,event: PasteEvent) => void) | undefined
    _copyOption_flag?: boolean
    _copyOption0_value?: CopyOptions | undefined
    _enableKeyboardOnFocus_flag?: boolean
    _enableKeyboardOnFocus0_value?: boolean | undefined
    _maxLength_flag?: boolean
    _maxLength0_value?: number | undefined
    _style_flag?: boolean
    _style0_value?: TextContentStyle | undefined
    _barState_flag?: boolean
    _barState0_value?: BarState | undefined
    _selectionMenuHidden_flag?: boolean
    _selectionMenuHidden0_value?: boolean | undefined
    _minFontSize_flag?: boolean
    _minFontSize0_value?: number | string | Resource | undefined
    _maxFontSize_flag?: boolean
    _maxFontSize0_value?: number | string | Resource | undefined
    _minFontScale_flag?: boolean
    _minFontScale0_value?: number | Resource | undefined
    _maxFontScale_flag?: boolean
    _maxFontScale0_value?: number | Resource | undefined
    _heightAdaptivePolicy_flag?: boolean
    _heightAdaptivePolicy0_value?: TextHeightAdaptivePolicy | undefined
    _maxLines_flag?: boolean
    _maxLines0_value?: number | undefined
    _wordBreak_flag?: boolean
    _wordBreak0_value?: WordBreak | undefined
    _lineBreakStrategy_flag?: boolean
    _lineBreakStrategy0_value?: LineBreakStrategy | undefined
    _decoration_flag?: boolean
    _decoration0_value?: TextDecorationOptions | undefined
    _letterSpacing_flag?: boolean
    _letterSpacing0_value?: number | string | Resource | undefined
    _lineSpacing_flag?: boolean
    _lineSpacing0_value?: LengthMetrics | undefined
    _lineHeight_flag?: boolean
    _lineHeight0_value?: number | string | Resource | undefined
    _type_flag?: boolean
    _type0_value?: TextAreaType | undefined
    _enableAutoFill_flag?: boolean
    _enableAutoFill0_value?: boolean | undefined
    _contentType_flag?: boolean
    _contentType0_value?: ContentType | undefined
    _fontFeature_flag?: boolean
    _fontFeature0_value?: string | undefined
    _onWillInsert_flag?: boolean
    _onWillInsert0_value?: ((value0: InsertValue) => boolean) | undefined
    _onDidInsert_flag?: boolean
    _onDidInsert0_value?: ((value0: InsertValue) => void) | undefined
    _onWillDelete_flag?: boolean
    _onWillDelete0_value?: ((value0: DeleteValue) => boolean) | undefined
    _onDidDelete_flag?: boolean
    _onDidDelete0_value?: ((value0: DeleteValue) => void) | undefined
    _editMenuOptions_flag?: boolean
    _editMenuOptions0_value?: EditMenuOptions | undefined
    _enablePreviewText_flag?: boolean
    _enablePreviewText0_value?: boolean | undefined
    _enableHapticFeedback_flag?: boolean
    _enableHapticFeedback0_value?: boolean | undefined
    _autoCapitalizationMode_flag?: boolean
    _autoCapitalizationMode0_value?: AutoCapitalizationMode | undefined
    _halfLeading_flag?: boolean
    _halfLeading0_value?: boolean | undefined
    _ellipsisMode_flag?: boolean
    _ellipsisMode0_value?: EllipsisMode | undefined
    _stopBackPress_flag?: boolean
    _stopBackPress0_value?: boolean | undefined
    _onWillChange_flag?: boolean
    _onWillChange0_value?: ((value0: EditableTextChangeValue) => boolean) | undefined
    _keyboardAppearance_flag?: boolean
    _keyboardAppearance0_value?: KeyboardAppearance | undefined
    _inputFilter_flag?: boolean
    _inputFilter0_value?: ResourceStr | undefined
    _inputFilter1_value?: ((value: string) => void) | undefined
    _showCounter_flag?: boolean
    _showCounter0_value?: boolean | undefined
    _showCounter1_value?: InputCounterOptions | undefined
    _customKeyboard_flag?: boolean
    _customKeyboard0_value?: CustomBuilder | undefined
    _customKeyboard1_value?: KeyboardOptions | undefined
    __onChangeEvent_text_flag?: boolean
    __onChangeEvent_text0_value?: ((text: ResourceStr | Resource | string) => void)
    applyModifierPatch(component: TextAreaAttribute): void {
        if (this._placeholderColor_flag)
            component.placeholderColor((this._placeholderColor0_value as ResourceColor | undefined))
        if (this._placeholderFont_flag)
            component.placeholderFont((this._placeholderFont0_value as Font | undefined))
        if (this._enterKeyType_flag)
            component.enterKeyType((this._enterKeyType0_value as EnterKeyType | undefined))
        if (this._textAlign_flag)
            component.textAlign((this._textAlign0_value as TextAlign | undefined))
        if (this._caretColor_flag)
            component.caretColor((this._caretColor0_value as ResourceColor | undefined))
        if (this._fontColor_flag)
            component.fontColor((this._fontColor0_value as ResourceColor | undefined))
        if (this._fontSize_flag)
            component.fontSize((this._fontSize0_value as Length | undefined))
        if (this._fontStyle_flag)
            component.fontStyle((this._fontStyle0_value as FontStyle | undefined))
        if (this._fontWeight_flag)
            component.fontWeight((this._fontWeight0_value as number | FontWeight | ResourceStr | undefined))
        if (this._fontFamily_flag)
            component.fontFamily((this._fontFamily0_value as ResourceStr | undefined))
        if (this._textOverflow_flag)
            component.textOverflow((this._textOverflow0_value as TextOverflow | undefined))
        if (this._textIndent_flag)
            component.textIndent((this._textIndent0_value as Dimension | undefined))
        if (this._caretStyle_flag)
            component.caretStyle((this._caretStyle0_value as CaretStyle | undefined))
        if (this._selectedBackgroundColor_flag)
            component.selectedBackgroundColor((this._selectedBackgroundColor0_value as ResourceColor | undefined))
        if (this._onSubmit_flag)
            component.onSubmit((this._onSubmit0_value as ((enterKey: EnterKeyType) => void) | TextAreaSubmitCallback | undefined))
        if (this._onChange_flag)
            component.onChange((this._onChange0_value as EditableTextOnChangeCallback | undefined))
        if (this._onTextSelectionChange_flag)
            component.onTextSelectionChange((this._onTextSelectionChange0_value as ((selectionStart: number,selectionEnd: number) => void) | undefined))
        if (this._onContentScroll_flag)
            component.onContentScroll((this._onContentScroll0_value as ((selectionStart: number,selectionEnd: number) => void) | undefined))
        if (this._onEditChange_flag)
            component.onEditChange((this._onEditChange0_value as ((isEditing: boolean) => void) | undefined))
        if (this._onCopy_flag)
            component.onCopy((this._onCopy0_value as ((value: string) => void) | undefined))
        if (this._onCut_flag)
            component.onCut((this._onCut0_value as ((value: string) => void) | undefined))
        if (this._onPaste_flag)
            component.onPaste((this._onPaste0_value as ((value: string,event: PasteEvent) => void) | undefined))
        if (this._copyOption_flag)
            component.copyOption((this._copyOption0_value as CopyOptions | undefined))
        if (this._enableKeyboardOnFocus_flag)
            component.enableKeyboardOnFocus((this._enableKeyboardOnFocus0_value as boolean | undefined))
        if (this._maxLength_flag)
            component.maxLength((this._maxLength0_value as number | undefined))
        if (this._style_flag)
            component.style((this._style0_value as TextContentStyle | undefined))
        if (this._barState_flag)
            component.barState((this._barState0_value as BarState | undefined))
        if (this._selectionMenuHidden_flag)
            component.selectionMenuHidden((this._selectionMenuHidden0_value as boolean | undefined))
        if (this._minFontSize_flag)
            component.minFontSize((this._minFontSize0_value as number | string | Resource | undefined))
        if (this._maxFontSize_flag)
            component.maxFontSize((this._maxFontSize0_value as number | string | Resource | undefined))
        if (this._minFontScale_flag)
            component.minFontScale((this._minFontScale0_value as number | Resource | undefined))
        if (this._maxFontScale_flag)
            component.maxFontScale((this._maxFontScale0_value as number | Resource | undefined))
        if (this._heightAdaptivePolicy_flag)
            component.heightAdaptivePolicy((this._heightAdaptivePolicy0_value as TextHeightAdaptivePolicy | undefined))
        if (this._maxLines_flag)
            component.maxLines((this._maxLines0_value as number | undefined))
        if (this._wordBreak_flag)
            component.wordBreak((this._wordBreak0_value as WordBreak | undefined))
        if (this._lineBreakStrategy_flag)
            component.lineBreakStrategy((this._lineBreakStrategy0_value as LineBreakStrategy | undefined))
        if (this._decoration_flag)
            component.decoration((this._decoration0_value as TextDecorationOptions | undefined))
        if (this._letterSpacing_flag)
            component.letterSpacing((this._letterSpacing0_value as number | string | Resource | undefined))
        if (this._lineSpacing_flag)
            component.lineSpacing((this._lineSpacing0_value as LengthMetrics | undefined))
        if (this._lineHeight_flag)
            component.lineHeight((this._lineHeight0_value as number | string | Resource | undefined))
        if (this._type_flag)
            component.type((this._type0_value as TextAreaType | undefined))
        if (this._enableAutoFill_flag)
            component.enableAutoFill((this._enableAutoFill0_value as boolean | undefined))
        if (this._contentType_flag)
            component.contentType((this._contentType0_value as ContentType | undefined))
        if (this._fontFeature_flag)
            component.fontFeature((this._fontFeature0_value as string | undefined))
        if (this._onWillInsert_flag)
            component.onWillInsert((this._onWillInsert0_value as ((value0: InsertValue) => boolean) | undefined))
        if (this._onDidInsert_flag)
            component.onDidInsert((this._onDidInsert0_value as ((value0: InsertValue) => void) | undefined))
        if (this._onWillDelete_flag)
            component.onWillDelete((this._onWillDelete0_value as ((value0: DeleteValue) => boolean) | undefined))
        if (this._onDidDelete_flag)
            component.onDidDelete((this._onDidDelete0_value as ((value0: DeleteValue) => void) | undefined))
        if (this._editMenuOptions_flag)
            component.editMenuOptions((this._editMenuOptions0_value as EditMenuOptions | undefined))
        if (this._enablePreviewText_flag)
            component.enablePreviewText((this._enablePreviewText0_value as boolean | undefined))
        if (this._enableHapticFeedback_flag)
            component.enableHapticFeedback((this._enableHapticFeedback0_value as boolean | undefined))
        if (this._autoCapitalizationMode_flag)
            component.autoCapitalizationMode((this._autoCapitalizationMode0_value as AutoCapitalizationMode | undefined))
        if (this._halfLeading_flag)
            component.halfLeading((this._halfLeading0_value as boolean | undefined))
        if (this._ellipsisMode_flag)
            component.ellipsisMode((this._ellipsisMode0_value as EllipsisMode | undefined))
        if (this._stopBackPress_flag)
            component.stopBackPress((this._stopBackPress0_value as boolean | undefined))
        if (this._onWillChange_flag)
            component.onWillChange((this._onWillChange0_value as ((value0: EditableTextChangeValue) => boolean) | undefined))
        if (this._keyboardAppearance_flag)
            component.keyboardAppearance((this._keyboardAppearance0_value as KeyboardAppearance | undefined))
        if (this._inputFilter_flag)
            component.inputFilter((this._inputFilter0_value as ResourceStr | undefined), (this._inputFilter1_value as ((value: string) => void) | undefined))
        if (this._showCounter_flag)
            component.showCounter((this._showCounter0_value as boolean | undefined), (this._showCounter1_value as InputCounterOptions | undefined))
        if (this._customKeyboard_flag)
            component.customKeyboard((this._customKeyboard0_value as CustomBuilder | undefined), (this._customKeyboard1_value as KeyboardOptions | undefined))
    }
    public placeholderColor(value: ResourceColor | undefined): this {
        this._placeholderColor_flag = true
        this._placeholderColor0_value = value
        return this
    }
    public placeholderFont(value: Font | undefined): this {
        this._placeholderFont_flag = true
        this._placeholderFont0_value = value
        return this
    }
    public enterKeyType(value: EnterKeyType | undefined): this {
        this._enterKeyType_flag = true
        this._enterKeyType0_value = value
        return this
    }
    public textAlign(value: TextAlign | undefined): this {
        this._textAlign_flag = true
        this._textAlign0_value = value
        return this
    }
    public caretColor(value: ResourceColor | undefined): this {
        this._caretColor_flag = true
        this._caretColor0_value = value
        return this
    }
    public fontColor(value: ResourceColor | undefined): this {
        this._fontColor_flag = true
        this._fontColor0_value = value
        return this
    }
    public fontSize(value: Length | undefined): this {
        this._fontSize_flag = true
        this._fontSize0_value = value
        return this
    }
    public fontStyle(value: FontStyle | undefined): this {
        this._fontStyle_flag = true
        this._fontStyle0_value = value
        return this
    }
    public fontWeight(value: number | FontWeight | ResourceStr | undefined): this {
        this._fontWeight_flag = true
        this._fontWeight0_value = value
        return this
    }
    public fontFamily(value: ResourceStr | undefined): this {
        this._fontFamily_flag = true
        this._fontFamily0_value = value
        return this
    }
    public textOverflow(value: TextOverflow | undefined): this {
        this._textOverflow_flag = true
        this._textOverflow0_value = value
        return this
    }
    public textIndent(value: Dimension | undefined): this {
        this._textIndent_flag = true
        this._textIndent0_value = value
        return this
    }
    public caretStyle(value: CaretStyle | undefined): this {
        this._caretStyle_flag = true
        this._caretStyle0_value = value
        return this
    }
    public selectedBackgroundColor(value: ResourceColor | undefined): this {
        this._selectedBackgroundColor_flag = true
        this._selectedBackgroundColor0_value = value
        return this
    }
    public onSubmit(value: ((enterKey: EnterKeyType) => void) | TextAreaSubmitCallback | undefined): this {
        this._onSubmit_flag = true
        this._onSubmit0_value = value
        return this
    }
    public onChange(value: EditableTextOnChangeCallback | undefined): this {
        this._onChange_flag = true
        this._onChange0_value = value
        return this
    }
    public onTextSelectionChange(value: ((selectionStart: number,selectionEnd: number) => void) | undefined): this {
        this._onTextSelectionChange_flag = true
        this._onTextSelectionChange0_value = value
        return this
    }
    public onContentScroll(value: ((selectionStart: number,selectionEnd: number) => void) | undefined): this {
        this._onContentScroll_flag = true
        this._onContentScroll0_value = value
        return this
    }
    public onEditChange(value: ((isEditing: boolean) => void) | undefined): this {
        this._onEditChange_flag = true
        this._onEditChange0_value = value
        return this
    }
    public onCopy(value: ((value: string) => void) | undefined): this {
        this._onCopy_flag = true
        this._onCopy0_value = value
        return this
    }
    public onCut(value: ((value: string) => void) | undefined): this {
        this._onCut_flag = true
        this._onCut0_value = value
        return this
    }
    public onPaste(value: ((value: string,event: PasteEvent) => void) | undefined): this {
        this._onPaste_flag = true
        this._onPaste0_value = value
        return this
    }
    public copyOption(value: CopyOptions | undefined): this {
        this._copyOption_flag = true
        this._copyOption0_value = value
        return this
    }
    public enableKeyboardOnFocus(value: boolean | undefined): this {
        this._enableKeyboardOnFocus_flag = true
        this._enableKeyboardOnFocus0_value = value
        return this
    }
    public maxLength(value: number | undefined): this {
        this._maxLength_flag = true
        this._maxLength0_value = value
        return this
    }
    public style(value: TextContentStyle | undefined): this {
        this._style_flag = true
        this._style0_value = value
        return this
    }
    public barState(value: BarState | undefined): this {
        this._barState_flag = true
        this._barState0_value = value
        return this
    }
    public selectionMenuHidden(value: boolean | undefined): this {
        this._selectionMenuHidden_flag = true
        this._selectionMenuHidden0_value = value
        return this
    }
    public minFontSize(value: number | string | Resource | undefined): this {
        this._minFontSize_flag = true
        this._minFontSize0_value = value
        return this
    }
    public maxFontSize(value: number | string | Resource | undefined): this {
        this._maxFontSize_flag = true
        this._maxFontSize0_value = value
        return this
    }
    public minFontScale(value: number | Resource | undefined): this {
        this._minFontScale_flag = true
        this._minFontScale0_value = value
        return this
    }
    public maxFontScale(value: number | Resource | undefined): this {
        this._maxFontScale_flag = true
        this._maxFontScale0_value = value
        return this
    }
    public heightAdaptivePolicy(value: TextHeightAdaptivePolicy | undefined): this {
        this._heightAdaptivePolicy_flag = true
        this._heightAdaptivePolicy0_value = value
        return this
    }
    public maxLines(value: number | undefined): this {
        this._maxLines_flag = true
        this._maxLines0_value = value
        return this
    }
    public wordBreak(value: WordBreak | undefined): this {
        this._wordBreak_flag = true
        this._wordBreak0_value = value
        return this
    }
    public lineBreakStrategy(value: LineBreakStrategy | undefined): this {
        this._lineBreakStrategy_flag = true
        this._lineBreakStrategy0_value = value
        return this
    }
    public decoration(value: TextDecorationOptions | undefined): this {
        this._decoration_flag = true
        this._decoration0_value = value
        return this
    }
    public letterSpacing(value: number | string | Resource | undefined): this {
        this._letterSpacing_flag = true
        this._letterSpacing0_value = value
        return this
    }
    public lineSpacing(value: LengthMetrics | undefined): this {
        this._lineSpacing_flag = true
        this._lineSpacing0_value = value
        return this
    }
    public lineHeight(value: number | string | Resource | undefined): this {
        this._lineHeight_flag = true
        this._lineHeight0_value = value
        return this
    }
    public type(value: TextAreaType | undefined): this {
        this._type_flag = true
        this._type0_value = value
        return this
    }
    public enableAutoFill(value: boolean | undefined): this {
        this._enableAutoFill_flag = true
        this._enableAutoFill0_value = value
        return this
    }
    public contentType(value: ContentType | undefined): this {
        this._contentType_flag = true
        this._contentType0_value = value
        return this
    }
    public fontFeature(value: string | undefined): this {
        this._fontFeature_flag = true
        this._fontFeature0_value = value
        return this
    }
    public onWillInsert(value: ((value0: InsertValue) => boolean) | undefined): this {
        this._onWillInsert_flag = true
        this._onWillInsert0_value = value
        return this
    }
    public onDidInsert(value: ((value0: InsertValue) => void) | undefined): this {
        this._onDidInsert_flag = true
        this._onDidInsert0_value = value
        return this
    }
    public onWillDelete(value: ((value0: DeleteValue) => boolean) | undefined): this {
        this._onWillDelete_flag = true
        this._onWillDelete0_value = value
        return this
    }
    public onDidDelete(value: ((value0: DeleteValue) => void) | undefined): this {
        this._onDidDelete_flag = true
        this._onDidDelete0_value = value
        return this
    }
    public editMenuOptions(value: EditMenuOptions | undefined): this {
        this._editMenuOptions_flag = true
        this._editMenuOptions0_value = value
        return this
    }
    public enablePreviewText(value: boolean | undefined): this {
        this._enablePreviewText_flag = true
        this._enablePreviewText0_value = value
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        this._enableHapticFeedback_flag = true
        this._enableHapticFeedback0_value = value
        return this
    }
    public autoCapitalizationMode(value: AutoCapitalizationMode | undefined): this {
        this._autoCapitalizationMode_flag = true
        this._autoCapitalizationMode0_value = value
        return this
    }
    public halfLeading(value: boolean | undefined): this {
        this._halfLeading_flag = true
        this._halfLeading0_value = value
        return this
    }
    public ellipsisMode(value: EllipsisMode | undefined): this {
        this._ellipsisMode_flag = true
        this._ellipsisMode0_value = value
        return this
    }
    public stopBackPress(value: boolean | undefined): this {
        this._stopBackPress_flag = true
        this._stopBackPress0_value = value
        return this
    }
    public onWillChange(value: ((value0: EditableTextChangeValue) => boolean) | undefined): this {
        this._onWillChange_flag = true
        this._onWillChange0_value = value
        return this
    }
    public keyboardAppearance(value: KeyboardAppearance | undefined): this {
        this._keyboardAppearance_flag = true
        this._keyboardAppearance0_value = value
        return this
    }
    public inputFilter(value: ResourceStr | undefined, error?: ((value: string) => void)): this {
        this._inputFilter_flag = true
        this._inputFilter0_value = value
        this._inputFilter1_value = error
        return this
    }
    public showCounter(value: boolean | undefined, options?: InputCounterOptions): this {
        this._showCounter_flag = true
        this._showCounter0_value = value
        this._showCounter1_value = options
        return this
    }
    public customKeyboard(value: CustomBuilder | undefined, options?: KeyboardOptions): this {
        this._customKeyboard_flag = true
        this._customKeyboard0_value = value
        this._customKeyboard1_value = options
        return this
    }
    public _onChangeEvent_text(callback_: ((text: ResourceStr | Resource | string) => void)): void {
    }
    public attributeModifier(value: AttributeModifier<TextAreaAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class TextAreaController_serializer {
    public static write(buffer: SerializerBase, value: TextAreaController): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): TextAreaController {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return TextAreaControllerInternal.fromPtr(ptr)
    }
}
export class TextAreaOptions_serializer {
    public static write(buffer: SerializerBase, value: TextAreaOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_placeholder  = value.placeholder
        let value_placeholder_type : int32 = RuntimeType.UNDEFINED
        value_placeholder_type = runtimeType(value_placeholder)
        valueSerializer.writeInt8((value_placeholder_type).toChar())
        if ((value_placeholder_type) != (RuntimeType.UNDEFINED)) {
            const value_placeholder_value  = value_placeholder!
            let value_placeholder_value_type : int32 = RuntimeType.UNDEFINED
            value_placeholder_value_type = runtimeType(value_placeholder_value)
            if (RuntimeType.STRING == value_placeholder_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_placeholder_value_0  = value_placeholder_value as string
                valueSerializer.writeString(value_placeholder_value_0)
            }
            else if (RuntimeType.OBJECT == value_placeholder_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_placeholder_value_1  = value_placeholder_value as Resource
                Resource_serializer.write(valueSerializer, value_placeholder_value_1)
            }
        }
        const value_text  = value.text
        let value_text_type : int32 = RuntimeType.UNDEFINED
        value_text_type = runtimeType(value_text)
        valueSerializer.writeInt8((value_text_type).toChar())
        if ((value_text_type) != (RuntimeType.UNDEFINED)) {
            const value_text_value  = value_text!
            let value_text_value_type : int32 = RuntimeType.UNDEFINED
            value_text_value_type = runtimeType(value_text_value)
            if (RuntimeType.STRING == value_text_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_text_value_0  = value_text_value as string
                valueSerializer.writeString(value_text_value_0)
            }
            else if (RuntimeType.OBJECT == value_text_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_text_value_1  = value_text_value as Resource
                Resource_serializer.write(valueSerializer, value_text_value_1)
            }
        }
        const value_controller  = value.controller
        let value_controller_type : int32 = RuntimeType.UNDEFINED
        value_controller_type = runtimeType(value_controller)
        valueSerializer.writeInt8((value_controller_type).toChar())
        if ((value_controller_type) != (RuntimeType.UNDEFINED)) {
            const value_controller_value  = value_controller!
            TextAreaController_serializer.write(valueSerializer, value_controller_value)
        }
    }
    public static read(buffer: DeserializerBase): TextAreaOptions {
        let valueDeserializer : DeserializerBase = buffer
        const placeholder_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let placeholder_buf : ResourceStr | undefined
        if ((placeholder_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const placeholder_buf__selector : int32 = valueDeserializer.readInt8()
            let placeholder_buf_ : string | Resource | undefined
            if (placeholder_buf__selector == (0).toChar()) {
                placeholder_buf_ = (valueDeserializer.readString() as string)
            }
            else if (placeholder_buf__selector == (1).toChar()) {
                placeholder_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for placeholder_buf_ has to be chosen through deserialisation.")
            }
            placeholder_buf = (placeholder_buf_ as string | Resource)
        }
        const placeholder_result : ResourceStr | undefined = placeholder_buf
        const text_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let text_buf : string | Resource | undefined
        if ((text_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const text_buf__selector : int32 = valueDeserializer.readInt8()
            let text_buf_ : string | Resource | undefined
            if (text_buf__selector == (0).toChar()) {
                text_buf_ = (valueDeserializer.readString() as string)
            }
            else if (text_buf__selector == (1).toChar()) {
                text_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for text_buf_ has to be chosen through deserialisation.")
            }
            text_buf = (text_buf_ as string | Resource)
        }
        const text_result : ResourceStr | Resource | string | undefined = text_buf
        const controller_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let controller_buf : TextAreaController | undefined
        if ((controller_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            controller_buf = (TextAreaController_serializer.read(valueDeserializer) as TextAreaController)
        }
        const controller_result : TextAreaController | undefined = controller_buf
        let value : TextAreaOptions = ({placeholder: placeholder_result, text: text_result, controller: controller_result} as TextAreaOptions)
        return value
    }
}
export class TextAreaControllerInternal {
    public static fromPtr(ptr: KPointer): TextAreaController {
        return new TextAreaController(ptr)
    }
}
export class TextAreaController extends TextContentControllerBase implements MaterializedBase {
    constructor(peerPtr: KPointer) {
        super(peerPtr)
    }
    constructor() {
        this(TextAreaController.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TextAreaController_construct()
        return retval
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
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            SelectionOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._TextAreaController_setTextSelection(this.peer!.ptr, selectionStart, selectionEnd, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private stopEditing_serialize(): void {
        ArkUIGeneratedNativeModule._TextAreaController_stopEditing(this.peer!.ptr)
    }
}

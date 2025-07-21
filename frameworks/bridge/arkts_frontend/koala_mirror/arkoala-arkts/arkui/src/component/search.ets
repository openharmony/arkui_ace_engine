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
import { SymbolGlyphModifier_serializer, SymbolGlyphModifier } from "./../generated/arkui.SymbolGlyphModifier"
import { CaretStyle_serializer, EditMenuOptions_serializer, CaretStyle, EditableTextOnChangeCallback, PreviewText, TextChangeOptions, InsertValue, DeleteValue, EditMenuOptions, AutoCapitalizationMode, EditableTextChangeValue, KeyboardAppearance } from "./textCommon"
import { Font_serializer, ResourceColor, Dimension, Font, ResourceStr, Length } from "./units"
import { TextDecorationOptions_serializer, ArkCommonMethodPeer, CommonMethod, TextDecorationOptions, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet, SelectionOptions_serializer, TextContentControllerBase, TextContentControllerBaseInternal, SelectionOptions } from "./common"
import { KeyboardOptions_serializer, PasteEvent, KeyboardOptions } from "./richEditor"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { Color, CopyOptions, TextAlign } from "./enums"
import { EnterKeyType, SubmitEvent, OnTextSelectionChangeCallback, OnContentScrollCallback, OnPasteCallback } from "./textInput"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CustomBuilder } from "./builder"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
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
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            SearchOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._SearchInterface_setSearchOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_setFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSearchIconAttribute(value: IconOptions | SymbolGlyphModifier | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isIconOptions(value_value, false, false, false)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as IconOptions
                IconOptions_serializer.write(thisSerializer, value_value_0)
            }
            else if (TypeChecker.isSymbolGlyphModifier(value_value)) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as SymbolGlyphModifier
                SymbolGlyphModifier_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setSearchIcon(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCancelButtonAttribute(value: CancelButtonOptions | CancelButtonSymbolOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isCancelButtonOptions(value_value, true, true)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as CancelButtonOptions
                CancelButtonOptions_serializer.write(thisSerializer, value_value_0)
            }
            else if (TypeChecker.isCancelButtonSymbolOptions(value_value, true, true)) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as CancelButtonSymbolOptions
                CancelButtonSymbolOptions_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setCancelButton(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_setTextIndent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnEditChangeAttribute(value: ((value0: boolean) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setOnEditChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_setSelectedBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_setCaretStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_setPlaceholderColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_setPlaceholderFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextFontAttribute(value: Font | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            Font_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setTextFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_setEnterKeyType(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSubmitAttribute(value: ((value0: string) => void) | SearchSubmitCallback | undefined): void {
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
                const value_value_0  = value_value as ((value0: string) => void)
                thisSerializer.holdAndWriteCallback(value_value_0)
            }
            else if (RuntimeType.FUNCTION == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as SearchSubmitCallback
                thisSerializer.holdAndWriteCallback(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setOnSubmit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_setOnChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnTextSelectionChangeAttribute(value: OnTextSelectionChangeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setOnTextSelectionChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnContentScrollAttribute(value: OnContentScrollCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setOnContentScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnCopyAttribute(value: ((value0: string) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setOnCopy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnCutAttribute(value: ((value0: string) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setOnCut(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnPasteAttribute(value: OnPasteCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setOnPaste(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_setCopyOption(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_setMaxLength(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_setTextAlign(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_setEnableKeyboardOnFocus(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_setSelectionMenuHidden(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_setMinFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_setMaxFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_setMinFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_setMaxFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_setDecoration(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_setLetterSpacing(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_setLineHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTypeAttribute(value: SearchType | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as SearchType)
            thisSerializer.writeInt32(TypeChecker.SearchType_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setType(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_setFontFeature(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_setOnWillInsert(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_setOnDidInsert(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_setOnWillDelete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_setOnDidDelete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_setEditMenuOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_setEnablePreviewText(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_setEnableHapticFeedback(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_setAutoCapitalizationMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_setHalfLeading(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_setStopBackPress(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_setOnWillChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_setKeyboardAppearance(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSearchButtonAttribute(value: ResourceStr | undefined, option?: SearchButtonOptions): void {
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
        let option_type : int32 = RuntimeType.UNDEFINED
        option_type = runtimeType(option)
        thisSerializer.writeInt8((option_type).toChar())
        if ((option_type) != (RuntimeType.UNDEFINED)) {
            const option_value  = option!
            SearchButtonOptions_serializer.write(thisSerializer, option_value)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setSearchButton(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setInputFilterAttribute(value: ResourceStr | undefined, error?: ((value0: string) => void)): void {
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
        ArkUIGeneratedNativeModule._SearchAttribute_setInputFilter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_setCustomKeyboard(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    set_onChangeEvent_valueAttribute(callback_: ((value0: string) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._SearchAttribute_set_onChangeEvent_value(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
export interface SearchAttribute extends CommonMethod {
    fontColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method fontColor")
    }
    searchIcon(value: IconOptions | SymbolGlyphModifier | undefined): this {
        throw new Error("Unimplemented method searchIcon")
    }
    cancelButton(value: CancelButtonOptions | CancelButtonSymbolOptions | undefined): this {
        throw new Error("Unimplemented method cancelButton")
    }
    textIndent(value: Dimension | undefined): this {
        throw new Error("Unimplemented method textIndent")
    }
    onEditChange(value: ((value0: boolean) => void) | undefined): this {
        throw new Error("Unimplemented method onEditChange")
    }
    selectedBackgroundColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method selectedBackgroundColor")
    }
    caretStyle(value: CaretStyle | undefined): this {
        throw new Error("Unimplemented method caretStyle")
    }
    placeholderColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method placeholderColor")
    }
    placeholderFont(value: Font | undefined): this {
        throw new Error("Unimplemented method placeholderFont")
    }
    textFont(value: Font | undefined): this {
        throw new Error("Unimplemented method textFont")
    }
    enterKeyType(value: EnterKeyType | undefined): this {
        throw new Error("Unimplemented method enterKeyType")
    }
    onSubmit(value: ((value0: string) => void) | SearchSubmitCallback | undefined): this {
        throw new Error("Unimplemented method onSubmit")
    }
    onChange(value: EditableTextOnChangeCallback | undefined): this {
        throw new Error("Unimplemented method onChange")
    }
    onTextSelectionChange(value: OnTextSelectionChangeCallback | undefined): this {
        throw new Error("Unimplemented method onTextSelectionChange")
    }
    onContentScroll(value: OnContentScrollCallback | undefined): this {
        throw new Error("Unimplemented method onContentScroll")
    }
    onCopy(value: ((value0: string) => void) | undefined): this {
        throw new Error("Unimplemented method onCopy")
    }
    onCut(value: ((value0: string) => void) | undefined): this {
        throw new Error("Unimplemented method onCut")
    }
    onPaste(value: OnPasteCallback | undefined): this {
        throw new Error("Unimplemented method onPaste")
    }
    copyOption(value: CopyOptions | undefined): this {
        throw new Error("Unimplemented method copyOption")
    }
    maxLength(value: number | undefined): this {
        throw new Error("Unimplemented method maxLength")
    }
    textAlign(value: TextAlign | undefined): this {
        throw new Error("Unimplemented method textAlign")
    }
    enableKeyboardOnFocus(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableKeyboardOnFocus")
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
    decoration(value: TextDecorationOptions | undefined): this {
        throw new Error("Unimplemented method decoration")
    }
    letterSpacing(value: number | string | Resource | undefined): this {
        throw new Error("Unimplemented method letterSpacing")
    }
    lineHeight(value: number | string | Resource | undefined): this {
        throw new Error("Unimplemented method lineHeight")
    }
    type(value: SearchType | undefined): this {
        throw new Error("Unimplemented method type")
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
    stopBackPress(value: boolean | undefined): this {
        throw new Error("Unimplemented method stopBackPress")
    }
    onWillChange(value: ((value0: EditableTextChangeValue) => boolean) | undefined): this {
        throw new Error("Unimplemented method onWillChange")
    }
    keyboardAppearance(value: KeyboardAppearance | undefined): this {
        throw new Error("Unimplemented method keyboardAppearance")
    }
    searchButton(value: ResourceStr | undefined, option?: SearchButtonOptions): this {
        throw new Error("Unimplemented method searchButton")
    }
    inputFilter(value: ResourceStr | undefined, error?: ((value0: string) => void)): this {
        throw new Error("Unimplemented method inputFilter")
    }
    customKeyboard(value: CustomBuilder | undefined, options?: KeyboardOptions): this {
        throw new Error("Unimplemented method customKeyboard")
    }
    _onChangeEvent_value(callback_: ((value0: string) => void)): void {
        throw new Error("Unimplemented method _onChangeEvent_value")
    }
    attributeModifier(value: AttributeModifier<SearchAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkSearchStyle extends ArkCommonMethodStyle implements SearchAttribute {
    fontColor_value?: ResourceColor | undefined
    searchIcon_value?: IconOptions | SymbolGlyphModifier | undefined
    cancelButton_value?: CancelButtonOptions | CancelButtonSymbolOptions | undefined
    textIndent_value?: Dimension | undefined
    onEditChange_value?: ((value0: boolean) => void) | undefined
    selectedBackgroundColor_value?: ResourceColor | undefined
    caretStyle_value?: CaretStyle | undefined
    placeholderColor_value?: ResourceColor | undefined
    placeholderFont_value?: Font | undefined
    textFont_value?: Font | undefined
    enterKeyType_value?: EnterKeyType | undefined
    onSubmit_value?: ((value0: string) => void) | SearchSubmitCallback | undefined
    onChange_value?: EditableTextOnChangeCallback | undefined
    onTextSelectionChange_value?: OnTextSelectionChangeCallback | undefined
    onContentScroll_value?: OnContentScrollCallback | undefined
    onCopy_value?: ((value0: string) => void) | undefined
    onCut_value?: ((value0: string) => void) | undefined
    onPaste_value?: OnPasteCallback | undefined
    copyOption_value?: CopyOptions | undefined
    maxLength_value?: number | undefined
    textAlign_value?: TextAlign | undefined
    enableKeyboardOnFocus_value?: boolean | undefined
    selectionMenuHidden_value?: boolean | undefined
    minFontSize_value?: number | string | Resource | undefined
    maxFontSize_value?: number | string | Resource | undefined
    minFontScale_value?: number | Resource | undefined
    maxFontScale_value?: number | Resource | undefined
    decoration_value?: TextDecorationOptions | undefined
    letterSpacing_value?: number | string | Resource | undefined
    lineHeight_value?: number | string | Resource | undefined
    type_value?: SearchType | undefined
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
    stopBackPress_value?: boolean | undefined
    onWillChange_value?: ((value0: EditableTextChangeValue) => boolean) | undefined
    keyboardAppearance_value?: KeyboardAppearance | undefined
    attributeModifier_value?: AttributeModifier<SearchAttribute> | AttributeModifier<CommonMethod> | undefined
    public fontColor(value: ResourceColor | undefined): this {
        return this
    }
    public searchIcon(value: IconOptions | SymbolGlyphModifier | undefined): this {
        return this
    }
    public cancelButton(value: CancelButtonOptions | CancelButtonSymbolOptions | undefined): this {
        return this
    }
    public textIndent(value: Dimension | undefined): this {
        return this
    }
    public onEditChange(value: ((value0: boolean) => void) | undefined): this {
        return this
    }
    public selectedBackgroundColor(value: ResourceColor | undefined): this {
        return this
    }
    public caretStyle(value: CaretStyle | undefined): this {
        return this
    }
    public placeholderColor(value: ResourceColor | undefined): this {
        return this
    }
    public placeholderFont(value: Font | undefined): this {
        return this
    }
    public textFont(value: Font | undefined): this {
        return this
    }
    public enterKeyType(value: EnterKeyType | undefined): this {
        return this
    }
    public onSubmit(value: ((value0: string) => void) | SearchSubmitCallback | undefined): this {
        return this
    }
    public onChange(value: EditableTextOnChangeCallback | undefined): this {
        return this
    }
    public onTextSelectionChange(value: OnTextSelectionChangeCallback | undefined): this {
        return this
    }
    public onContentScroll(value: OnContentScrollCallback | undefined): this {
        return this
    }
    public onCopy(value: ((value0: string) => void) | undefined): this {
        return this
    }
    public onCut(value: ((value0: string) => void) | undefined): this {
        return this
    }
    public onPaste(value: OnPasteCallback | undefined): this {
        return this
    }
    public copyOption(value: CopyOptions | undefined): this {
        return this
    }
    public maxLength(value: number | undefined): this {
        return this
    }
    public textAlign(value: TextAlign | undefined): this {
        return this
    }
    public enableKeyboardOnFocus(value: boolean | undefined): this {
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
    public decoration(value: TextDecorationOptions | undefined): this {
        return this
    }
    public letterSpacing(value: number | string | Resource | undefined): this {
        return this
    }
    public lineHeight(value: number | string | Resource | undefined): this {
        return this
    }
    public type(value: SearchType | undefined): this {
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
    public stopBackPress(value: boolean | undefined): this {
        return this
    }
    public onWillChange(value: ((value0: EditableTextChangeValue) => boolean) | undefined): this {
        return this
    }
    public keyboardAppearance(value: KeyboardAppearance | undefined): this {
        return this
    }
    public searchButton(value: ResourceStr | undefined, option?: SearchButtonOptions): this {
        return this
    }
    public inputFilter(value: ResourceStr | undefined, error?: ((value0: string) => void)): this {
        return this
    }
    public customKeyboard(value: CustomBuilder | undefined, options?: KeyboardOptions): this {
        return this
    }
    public _onChangeEvent_value(callback_: ((value0: string) => void)): void {
        throw new Error("Unimplemented")
    }
    public attributeModifier(value: AttributeModifier<SearchAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: SearchAttribute): void {
        super.apply(target)
        if (this.fontColor_value !== undefined)
            target.fontColor(this.fontColor_value!)
        if (this.searchIcon_value !== undefined)
            target.searchIcon(this.searchIcon_value!)
        if (this.cancelButton_value !== undefined)
            target.cancelButton(this.cancelButton_value!)
        if (this.textIndent_value !== undefined)
            target.textIndent(this.textIndent_value!)
        if (this.onEditChange_value !== undefined)
            target.onEditChange(this.onEditChange_value!)
        if (this.selectedBackgroundColor_value !== undefined)
            target.selectedBackgroundColor(this.selectedBackgroundColor_value!)
        if (this.caretStyle_value !== undefined)
            target.caretStyle(this.caretStyle_value!)
        if (this.placeholderColor_value !== undefined)
            target.placeholderColor(this.placeholderColor_value!)
        if (this.placeholderFont_value !== undefined)
            target.placeholderFont(this.placeholderFont_value!)
        if (this.textFont_value !== undefined)
            target.textFont(this.textFont_value!)
        if (this.enterKeyType_value !== undefined)
            target.enterKeyType(this.enterKeyType_value!)
        if (this.onSubmit_value !== undefined)
            target.onSubmit(this.onSubmit_value!)
        if (this.onChange_value !== undefined)
            target.onChange(this.onChange_value!)
        if (this.onTextSelectionChange_value !== undefined)
            target.onTextSelectionChange(this.onTextSelectionChange_value!)
        if (this.onContentScroll_value !== undefined)
            target.onContentScroll(this.onContentScroll_value!)
        if (this.onCopy_value !== undefined)
            target.onCopy(this.onCopy_value!)
        if (this.onCut_value !== undefined)
            target.onCut(this.onCut_value!)
        if (this.onPaste_value !== undefined)
            target.onPaste(this.onPaste_value!)
        if (this.copyOption_value !== undefined)
            target.copyOption(this.copyOption_value!)
        if (this.maxLength_value !== undefined)
            target.maxLength(this.maxLength_value!)
        if (this.textAlign_value !== undefined)
            target.textAlign(this.textAlign_value!)
        if (this.enableKeyboardOnFocus_value !== undefined)
            target.enableKeyboardOnFocus(this.enableKeyboardOnFocus_value!)
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
        if (this.decoration_value !== undefined)
            target.decoration(this.decoration_value!)
        if (this.letterSpacing_value !== undefined)
            target.letterSpacing(this.letterSpacing_value!)
        if (this.lineHeight_value !== undefined)
            target.lineHeight(this.lineHeight_value!)
        if (this.type_value !== undefined)
            target.type(this.type_value!)
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
        if (this.stopBackPress_value !== undefined)
            target.stopBackPress(this.stopBackPress_value!)
        if (this.onWillChange_value !== undefined)
            target.onWillChange(this.onWillChange_value!)
        if (this.keyboardAppearance_value !== undefined)
            target.keyboardAppearance(this.keyboardAppearance_value!)
    }
}

export class ArkSearchComponent extends ArkCommonMethodComponent implements SearchAttribute {
    getPeer(): ArkSearchPeer {
        return (this.peer as ArkSearchPeer)
    }
    public setSearchOptions(options?: SearchOptions): this {
        if (this.checkPriority("setSearchOptions")) {
            const options_casted = options as (SearchOptions | undefined)
            this.getPeer()?.setSearchOptionsAttribute(options_casted)
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
    public searchIcon(value: IconOptions | SymbolGlyphModifier | undefined): this {
        if (this.checkPriority("searchIcon")) {
            const value_casted = value as (IconOptions | SymbolGlyphModifier | undefined)
            this.getPeer()?.setSearchIconAttribute(value_casted)
            return this
        }
        return this
    }
    public cancelButton(value: CancelButtonOptions | CancelButtonSymbolOptions | undefined): this {
        if (this.checkPriority("cancelButton")) {
            const value_casted = value as (CancelButtonOptions | CancelButtonSymbolOptions | undefined)
            this.getPeer()?.setCancelButtonAttribute(value_casted)
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
    public onEditChange(value: ((value0: boolean) => void) | undefined): this {
        if (this.checkPriority("onEditChange")) {
            const value_casted = value as (((value0: boolean) => void) | undefined)
            this.getPeer()?.setOnEditChangeAttribute(value_casted)
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
    public caretStyle(value: CaretStyle | undefined): this {
        if (this.checkPriority("caretStyle")) {
            const value_casted = value as (CaretStyle | undefined)
            this.getPeer()?.setCaretStyleAttribute(value_casted)
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
    public textFont(value: Font | undefined): this {
        if (this.checkPriority("textFont")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.setTextFontAttribute(value_casted)
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
    public onSubmit(value: ((value0: string) => void) | SearchSubmitCallback | undefined): this {
        if (this.checkPriority("onSubmit")) {
            const value_casted = value as (((value0: string) => void) | SearchSubmitCallback | undefined)
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
    public onTextSelectionChange(value: OnTextSelectionChangeCallback | undefined): this {
        if (this.checkPriority("onTextSelectionChange")) {
            const value_casted = value as (OnTextSelectionChangeCallback | undefined)
            this.getPeer()?.setOnTextSelectionChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onContentScroll(value: OnContentScrollCallback | undefined): this {
        if (this.checkPriority("onContentScroll")) {
            const value_casted = value as (OnContentScrollCallback | undefined)
            this.getPeer()?.setOnContentScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public onCopy(value: ((value0: string) => void) | undefined): this {
        if (this.checkPriority("onCopy")) {
            const value_casted = value as (((value0: string) => void) | undefined)
            this.getPeer()?.setOnCopyAttribute(value_casted)
            return this
        }
        return this
    }
    public onCut(value: ((value0: string) => void) | undefined): this {
        if (this.checkPriority("onCut")) {
            const value_casted = value as (((value0: string) => void) | undefined)
            this.getPeer()?.setOnCutAttribute(value_casted)
            return this
        }
        return this
    }
    public onPaste(value: OnPasteCallback | undefined): this {
        if (this.checkPriority("onPaste")) {
            const value_casted = value as (OnPasteCallback | undefined)
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
    public maxLength(value: number | undefined): this {
        if (this.checkPriority("maxLength")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setMaxLengthAttribute(value_casted)
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
    public enableKeyboardOnFocus(value: boolean | undefined): this {
        if (this.checkPriority("enableKeyboardOnFocus")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableKeyboardOnFocusAttribute(value_casted)
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
    public lineHeight(value: number | string | Resource | undefined): this {
        if (this.checkPriority("lineHeight")) {
            const value_casted = value as (number | string | Resource | undefined)
            this.getPeer()?.setLineHeightAttribute(value_casted)
            return this
        }
        return this
    }
    public type(value: SearchType | undefined): this {
        if (this.checkPriority("type")) {
            const value_casted = value as (SearchType | undefined)
            this.getPeer()?.setTypeAttribute(value_casted)
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
    public searchButton(value: ResourceStr | undefined, option?: SearchButtonOptions): this {
        if (this.checkPriority("searchButton")) {
            const value_casted = value as (ResourceStr | undefined)
            const option_casted = option as (SearchButtonOptions | undefined)
            this.getPeer()?.setSearchButtonAttribute(value_casted, option_casted)
            return this
        }
        return this
    }
    public inputFilter(value: ResourceStr | undefined, error?: ((value0: string) => void)): this {
        if (this.checkPriority("inputFilter")) {
            const value_casted = value as (ResourceStr | undefined)
            const error_casted = error as (((value0: string) => void) | undefined)
            this.getPeer()?.setInputFilterAttribute(value_casted, error_casted)
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
    public _onChangeEvent_value(callback_: ((value0: string) => void)): void {
        if (this.checkPriority("_onChangeEvent_value")) {
            const callback__casted = callback_ as (((value0: string) => void))
            this.getPeer()?.set_onChangeEvent_valueAttribute(callback__casted)
            return
        }
        return
    }
    public attributeModifier(value: AttributeModifier<SearchAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withSearchStyle(receiver: SearchAttribute, modifier: AttributeModifier<SearchAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkSearchStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Search")
// export function Search(
//     options?: SearchOptions,
//     @memo
//     content_?: () => void,
// ): SearchAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Search(
    @memo
    style: ((attributes: SearchAttribute) => void) | undefined,
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
        withSearchStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkSearchSet extends ArkCommonMethodSet implements SearchAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _fontColor_flag?: boolean
    _fontColor0_value?: ResourceColor | undefined
    _searchIcon_flag?: boolean
    _searchIcon0_value?: IconOptions | SymbolGlyphModifier | undefined
    _cancelButton_flag?: boolean
    _cancelButton0_value?: CancelButtonOptions | CancelButtonSymbolOptions | undefined
    _textIndent_flag?: boolean
    _textIndent0_value?: Dimension | undefined
    _onEditChange_flag?: boolean
    _onEditChange0_value?: ((value0: boolean) => void) | undefined
    _selectedBackgroundColor_flag?: boolean
    _selectedBackgroundColor0_value?: ResourceColor | undefined
    _caretStyle_flag?: boolean
    _caretStyle0_value?: CaretStyle | undefined
    _placeholderColor_flag?: boolean
    _placeholderColor0_value?: ResourceColor | undefined
    _placeholderFont_flag?: boolean
    _placeholderFont0_value?: Font | undefined
    _textFont_flag?: boolean
    _textFont0_value?: Font | undefined
    _enterKeyType_flag?: boolean
    _enterKeyType0_value?: EnterKeyType | undefined
    _onSubmit_flag?: boolean
    _onSubmit0_value?: ((value0: string) => void) | SearchSubmitCallback | undefined
    _onChange_flag?: boolean
    _onChange0_value?: EditableTextOnChangeCallback | undefined
    _onTextSelectionChange_flag?: boolean
    _onTextSelectionChange0_value?: OnTextSelectionChangeCallback | undefined
    _onContentScroll_flag?: boolean
    _onContentScroll0_value?: OnContentScrollCallback | undefined
    _onCopy_flag?: boolean
    _onCopy0_value?: ((value0: string) => void) | undefined
    _onCut_flag?: boolean
    _onCut0_value?: ((value0: string) => void) | undefined
    _onPaste_flag?: boolean
    _onPaste0_value?: OnPasteCallback | undefined
    _copyOption_flag?: boolean
    _copyOption0_value?: CopyOptions | undefined
    _maxLength_flag?: boolean
    _maxLength0_value?: number | undefined
    _textAlign_flag?: boolean
    _textAlign0_value?: TextAlign | undefined
    _enableKeyboardOnFocus_flag?: boolean
    _enableKeyboardOnFocus0_value?: boolean | undefined
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
    _decoration_flag?: boolean
    _decoration0_value?: TextDecorationOptions | undefined
    _letterSpacing_flag?: boolean
    _letterSpacing0_value?: number | string | Resource | undefined
    _lineHeight_flag?: boolean
    _lineHeight0_value?: number | string | Resource | undefined
    _type_flag?: boolean
    _type0_value?: SearchType | undefined
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
    _stopBackPress_flag?: boolean
    _stopBackPress0_value?: boolean | undefined
    _onWillChange_flag?: boolean
    _onWillChange0_value?: ((value0: EditableTextChangeValue) => boolean) | undefined
    _keyboardAppearance_flag?: boolean
    _keyboardAppearance0_value?: KeyboardAppearance | undefined
    _searchButton_flag?: boolean
    _searchButton0_value?: ResourceStr | undefined
    _searchButton1_value?: SearchButtonOptions | undefined
    _inputFilter_flag?: boolean
    _inputFilter0_value?: ResourceStr | undefined
    _inputFilter1_value?: ((value0: string) => void) | undefined
    _customKeyboard_flag?: boolean
    _customKeyboard0_value?: CustomBuilder | undefined
    _customKeyboard1_value?: KeyboardOptions | undefined
    __onChangeEvent_value_flag?: boolean
    __onChangeEvent_value0_value?: ((value0: string) => void)
    applyModifierPatch(component: SearchAttribute): void {
        if (this._fontColor_flag)
            component.fontColor((this._fontColor0_value as ResourceColor | undefined))
        if (this._searchIcon_flag)
            component.searchIcon((this._searchIcon0_value as IconOptions | SymbolGlyphModifier | undefined))
        if (this._cancelButton_flag)
            component.cancelButton((this._cancelButton0_value as CancelButtonOptions | CancelButtonSymbolOptions | undefined))
        if (this._textIndent_flag)
            component.textIndent((this._textIndent0_value as Dimension | undefined))
        if (this._onEditChange_flag)
            component.onEditChange((this._onEditChange0_value as ((value0: boolean) => void) | undefined))
        if (this._selectedBackgroundColor_flag)
            component.selectedBackgroundColor((this._selectedBackgroundColor0_value as ResourceColor | undefined))
        if (this._caretStyle_flag)
            component.caretStyle((this._caretStyle0_value as CaretStyle | undefined))
        if (this._placeholderColor_flag)
            component.placeholderColor((this._placeholderColor0_value as ResourceColor | undefined))
        if (this._placeholderFont_flag)
            component.placeholderFont((this._placeholderFont0_value as Font | undefined))
        if (this._textFont_flag)
            component.textFont((this._textFont0_value as Font | undefined))
        if (this._enterKeyType_flag)
            component.enterKeyType((this._enterKeyType0_value as EnterKeyType | undefined))
        if (this._onSubmit_flag)
            component.onSubmit((this._onSubmit0_value as ((value0: string) => void) | SearchSubmitCallback | undefined))
        if (this._onChange_flag)
            component.onChange((this._onChange0_value as EditableTextOnChangeCallback | undefined))
        if (this._onTextSelectionChange_flag)
            component.onTextSelectionChange((this._onTextSelectionChange0_value as OnTextSelectionChangeCallback | undefined))
        if (this._onContentScroll_flag)
            component.onContentScroll((this._onContentScroll0_value as OnContentScrollCallback | undefined))
        if (this._onCopy_flag)
            component.onCopy((this._onCopy0_value as ((value0: string) => void) | undefined))
        if (this._onCut_flag)
            component.onCut((this._onCut0_value as ((value0: string) => void) | undefined))
        if (this._onPaste_flag)
            component.onPaste((this._onPaste0_value as OnPasteCallback | undefined))
        if (this._copyOption_flag)
            component.copyOption((this._copyOption0_value as CopyOptions | undefined))
        if (this._maxLength_flag)
            component.maxLength((this._maxLength0_value as number | undefined))
        if (this._textAlign_flag)
            component.textAlign((this._textAlign0_value as TextAlign | undefined))
        if (this._enableKeyboardOnFocus_flag)
            component.enableKeyboardOnFocus((this._enableKeyboardOnFocus0_value as boolean | undefined))
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
        if (this._decoration_flag)
            component.decoration((this._decoration0_value as TextDecorationOptions | undefined))
        if (this._letterSpacing_flag)
            component.letterSpacing((this._letterSpacing0_value as number | string | Resource | undefined))
        if (this._lineHeight_flag)
            component.lineHeight((this._lineHeight0_value as number | string | Resource | undefined))
        if (this._type_flag)
            component.type((this._type0_value as SearchType | undefined))
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
        if (this._stopBackPress_flag)
            component.stopBackPress((this._stopBackPress0_value as boolean | undefined))
        if (this._onWillChange_flag)
            component.onWillChange((this._onWillChange0_value as ((value0: EditableTextChangeValue) => boolean) | undefined))
        if (this._keyboardAppearance_flag)
            component.keyboardAppearance((this._keyboardAppearance0_value as KeyboardAppearance | undefined))
        if (this._searchButton_flag)
            component.searchButton((this._searchButton0_value as ResourceStr | undefined), (this._searchButton1_value as SearchButtonOptions | undefined))
        if (this._inputFilter_flag)
            component.inputFilter((this._inputFilter0_value as ResourceStr | undefined), (this._inputFilter1_value as ((value0: string) => void) | undefined))
        if (this._customKeyboard_flag)
            component.customKeyboard((this._customKeyboard0_value as CustomBuilder | undefined), (this._customKeyboard1_value as KeyboardOptions | undefined))
    }
    public fontColor(value: ResourceColor | undefined): this {
        this._fontColor_flag = true
        this._fontColor0_value = value
        return this
    }
    public searchIcon(value: IconOptions | SymbolGlyphModifier | undefined): this {
        this._searchIcon_flag = true
        this._searchIcon0_value = value
        return this
    }
    public cancelButton(value: CancelButtonOptions | CancelButtonSymbolOptions | undefined): this {
        this._cancelButton_flag = true
        this._cancelButton0_value = value
        return this
    }
    public textIndent(value: Dimension | undefined): this {
        this._textIndent_flag = true
        this._textIndent0_value = value
        return this
    }
    public onEditChange(value: ((value0: boolean) => void) | undefined): this {
        this._onEditChange_flag = true
        this._onEditChange0_value = value
        return this
    }
    public selectedBackgroundColor(value: ResourceColor | undefined): this {
        this._selectedBackgroundColor_flag = true
        this._selectedBackgroundColor0_value = value
        return this
    }
    public caretStyle(value: CaretStyle | undefined): this {
        this._caretStyle_flag = true
        this._caretStyle0_value = value
        return this
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
    public textFont(value: Font | undefined): this {
        this._textFont_flag = true
        this._textFont0_value = value
        return this
    }
    public enterKeyType(value: EnterKeyType | undefined): this {
        this._enterKeyType_flag = true
        this._enterKeyType0_value = value
        return this
    }
    public onSubmit(value: ((value0: string) => void) | SearchSubmitCallback | undefined): this {
        this._onSubmit_flag = true
        this._onSubmit0_value = value
        return this
    }
    public onChange(value: EditableTextOnChangeCallback | undefined): this {
        this._onChange_flag = true
        this._onChange0_value = value
        return this
    }
    public onTextSelectionChange(value: OnTextSelectionChangeCallback | undefined): this {
        this._onTextSelectionChange_flag = true
        this._onTextSelectionChange0_value = value
        return this
    }
    public onContentScroll(value: OnContentScrollCallback | undefined): this {
        this._onContentScroll_flag = true
        this._onContentScroll0_value = value
        return this
    }
    public onCopy(value: ((value0: string) => void) | undefined): this {
        this._onCopy_flag = true
        this._onCopy0_value = value
        return this
    }
    public onCut(value: ((value0: string) => void) | undefined): this {
        this._onCut_flag = true
        this._onCut0_value = value
        return this
    }
    public onPaste(value: OnPasteCallback | undefined): this {
        this._onPaste_flag = true
        this._onPaste0_value = value
        return this
    }
    public copyOption(value: CopyOptions | undefined): this {
        this._copyOption_flag = true
        this._copyOption0_value = value
        return this
    }
    public maxLength(value: number | undefined): this {
        this._maxLength_flag = true
        this._maxLength0_value = value
        return this
    }
    public textAlign(value: TextAlign | undefined): this {
        this._textAlign_flag = true
        this._textAlign0_value = value
        return this
    }
    public enableKeyboardOnFocus(value: boolean | undefined): this {
        this._enableKeyboardOnFocus_flag = true
        this._enableKeyboardOnFocus0_value = value
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
    public lineHeight(value: number | string | Resource | undefined): this {
        this._lineHeight_flag = true
        this._lineHeight0_value = value
        return this
    }
    public type(value: SearchType | undefined): this {
        this._type_flag = true
        this._type0_value = value
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
    public searchButton(value: ResourceStr | undefined, option?: SearchButtonOptions): this {
        this._searchButton_flag = true
        this._searchButton0_value = value
        this._searchButton1_value = option
        return this
    }
    public inputFilter(value: ResourceStr | undefined, error?: ((value0: string) => void)): this {
        this._inputFilter_flag = true
        this._inputFilter0_value = value
        this._inputFilter1_value = error
        return this
    }
    public customKeyboard(value: CustomBuilder | undefined, options?: KeyboardOptions): this {
        this._customKeyboard_flag = true
        this._customKeyboard0_value = value
        this._customKeyboard1_value = options
        return this
    }
    public _onChangeEvent_value(callback_: ((value0: string) => void)): void {
    }
    public attributeModifier(value: AttributeModifier<SearchAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class SearchController_serializer {
    public static write(buffer: SerializerBase, value: SearchController): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): SearchController {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return SearchControllerInternal.fromPtr(ptr)
    }
}
export class CancelButtonSymbolOptions_serializer {
    public static write(buffer: SerializerBase, value: CancelButtonSymbolOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_style  = value.style
        let value_style_type : int32 = RuntimeType.UNDEFINED
        value_style_type = runtimeType(value_style)
        valueSerializer.writeInt8((value_style_type).toChar())
        if ((value_style_type) != (RuntimeType.UNDEFINED)) {
            const value_style_value  = (value_style as CancelButtonStyle)
            valueSerializer.writeInt32(TypeChecker.CancelButtonStyle_ToNumeric(value_style_value))
        }
        const value_icon  = value.icon
        let value_icon_type : int32 = RuntimeType.UNDEFINED
        value_icon_type = runtimeType(value_icon)
        valueSerializer.writeInt8((value_icon_type).toChar())
        if ((value_icon_type) != (RuntimeType.UNDEFINED)) {
            const value_icon_value  = value_icon!
            SymbolGlyphModifier_serializer.write(valueSerializer, value_icon_value)
        }
    }
    public static read(buffer: DeserializerBase): CancelButtonSymbolOptions {
        let valueDeserializer : DeserializerBase = buffer
        const style_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let style_buf : CancelButtonStyle | undefined
        if ((style_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            style_buf = TypeChecker.CancelButtonStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const style_result : CancelButtonStyle | undefined = style_buf
        const icon_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let icon_buf : SymbolGlyphModifier | undefined
        if ((icon_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            icon_buf = SymbolGlyphModifier_serializer.read(valueDeserializer)
        }
        const icon_result : SymbolGlyphModifier | undefined = icon_buf
        let value : CancelButtonSymbolOptions = ({style: style_result, icon: icon_result} as CancelButtonSymbolOptions)
        return value
    }
}
export class SearchOptions_serializer {
    public static write(buffer: SerializerBase, value: SearchOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_value  = value.value
        let value_value_type : int32 = RuntimeType.UNDEFINED
        value_value_type = runtimeType(value_value)
        valueSerializer.writeInt8((value_value_type).toChar())
        if ((value_value_type) != (RuntimeType.UNDEFINED)) {
            const value_value_value  = value_value!
            valueSerializer.writeString(value_value_value)
        }
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
        const value_icon  = value.icon
        let value_icon_type : int32 = RuntimeType.UNDEFINED
        value_icon_type = runtimeType(value_icon)
        valueSerializer.writeInt8((value_icon_type).toChar())
        if ((value_icon_type) != (RuntimeType.UNDEFINED)) {
            const value_icon_value  = value_icon!
            valueSerializer.writeString(value_icon_value)
        }
        const value_controller  = value.controller
        let value_controller_type : int32 = RuntimeType.UNDEFINED
        value_controller_type = runtimeType(value_controller)
        valueSerializer.writeInt8((value_controller_type).toChar())
        if ((value_controller_type) != (RuntimeType.UNDEFINED)) {
            const value_controller_value  = value_controller!
            SearchController_serializer.write(valueSerializer, value_controller_value)
        }
    }
    public static read(buffer: DeserializerBase): SearchOptions {
        let valueDeserializer : DeserializerBase = buffer
        const value_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let value_buf : string | undefined
        if ((value_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            value_buf = (valueDeserializer.readString() as string)
        }
        const value_result : string | undefined = value_buf
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
        const icon_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let icon_buf : string | undefined
        if ((icon_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            icon_buf = (valueDeserializer.readString() as string)
        }
        const icon_result : string | undefined = icon_buf
        const controller_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let controller_buf : SearchController | undefined
        if ((controller_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            controller_buf = (SearchController_serializer.read(valueDeserializer) as SearchController)
        }
        const controller_result : SearchController | undefined = controller_buf
        let value : SearchOptions = ({value: value_result, placeholder: placeholder_result, icon: icon_result, controller: controller_result} as SearchOptions)
        return value
    }
}
export class IconOptions_serializer {
    public static write(buffer: SerializerBase, value: IconOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_size  = value.size
        let value_size_type : int32 = RuntimeType.UNDEFINED
        value_size_type = runtimeType(value_size)
        valueSerializer.writeInt8((value_size_type).toChar())
        if ((value_size_type) != (RuntimeType.UNDEFINED)) {
            const value_size_value  = value_size!
            let value_size_value_type : int32 = RuntimeType.UNDEFINED
            value_size_value_type = runtimeType(value_size_value)
            if (RuntimeType.STRING == value_size_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_size_value_0  = value_size_value as string
                valueSerializer.writeString(value_size_value_0)
            }
            else if (RuntimeType.NUMBER == value_size_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_size_value_1  = value_size_value as number
                valueSerializer.writeNumber(value_size_value_1)
            }
            else if (RuntimeType.OBJECT == value_size_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_size_value_2  = value_size_value as Resource
                Resource_serializer.write(valueSerializer, value_size_value_2)
            }
        }
        const value_color  = value.color
        let value_color_type : int32 = RuntimeType.UNDEFINED
        value_color_type = runtimeType(value_color)
        valueSerializer.writeInt8((value_color_type).toChar())
        if ((value_color_type) != (RuntimeType.UNDEFINED)) {
            const value_color_value  = value_color!
            let value_color_value_type : int32 = RuntimeType.UNDEFINED
            value_color_value_type = runtimeType(value_color_value)
            if (TypeChecker.isColor(value_color_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_color_value_0  = value_color_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_color_value_0))
            }
            else if (RuntimeType.NUMBER == value_color_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_color_value_1  = value_color_value as number
                valueSerializer.writeNumber(value_color_value_1)
            }
            else if (RuntimeType.STRING == value_color_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_color_value_2  = value_color_value as string
                valueSerializer.writeString(value_color_value_2)
            }
            else if (RuntimeType.OBJECT == value_color_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_color_value_3  = value_color_value as Resource
                Resource_serializer.write(valueSerializer, value_color_value_3)
            }
        }
        const value_src  = value.src
        let value_src_type : int32 = RuntimeType.UNDEFINED
        value_src_type = runtimeType(value_src)
        valueSerializer.writeInt8((value_src_type).toChar())
        if ((value_src_type) != (RuntimeType.UNDEFINED)) {
            const value_src_value  = value_src!
            let value_src_value_type : int32 = RuntimeType.UNDEFINED
            value_src_value_type = runtimeType(value_src_value)
            if (RuntimeType.STRING == value_src_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_src_value_0  = value_src_value as string
                valueSerializer.writeString(value_src_value_0)
            }
            else if (RuntimeType.OBJECT == value_src_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_src_value_1  = value_src_value as Resource
                Resource_serializer.write(valueSerializer, value_src_value_1)
            }
        }
    }
    public static read(buffer: DeserializerBase): IconOptions {
        let valueDeserializer : DeserializerBase = buffer
        const size_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let size_buf : Length | undefined
        if ((size_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const size_buf__selector : int32 = valueDeserializer.readInt8()
            let size_buf_ : string | number | Resource | undefined
            if (size_buf__selector == (0).toChar()) {
                size_buf_ = (valueDeserializer.readString() as string)
            }
            else if (size_buf__selector == (1).toChar()) {
                size_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (size_buf__selector == (2).toChar()) {
                size_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for size_buf_ has to be chosen through deserialisation.")
            }
            size_buf = (size_buf_ as string | number | Resource)
        }
        const size_result : Length | undefined = size_buf
        const color_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let color_buf : ResourceColor | undefined
        if ((color_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const color_buf__selector : int32 = valueDeserializer.readInt8()
            let color_buf_ : Color | number | string | Resource | undefined
            if (color_buf__selector == (0).toChar()) {
                color_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (color_buf__selector == (1).toChar()) {
                color_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (color_buf__selector == (2).toChar()) {
                color_buf_ = (valueDeserializer.readString() as string)
            }
            else if (color_buf__selector == (3).toChar()) {
                color_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for color_buf_ has to be chosen through deserialisation.")
            }
            color_buf = (color_buf_ as Color | number | string | Resource)
        }
        const color_result : ResourceColor | undefined = color_buf
        const src_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let src_buf : ResourceStr | undefined
        if ((src_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const src_buf__selector : int32 = valueDeserializer.readInt8()
            let src_buf_ : string | Resource | undefined
            if (src_buf__selector == (0).toChar()) {
                src_buf_ = (valueDeserializer.readString() as string)
            }
            else if (src_buf__selector == (1).toChar()) {
                src_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for src_buf_ has to be chosen through deserialisation.")
            }
            src_buf = (src_buf_ as string | Resource)
        }
        const src_result : ResourceStr | undefined = src_buf
        let value : IconOptions = ({size: size_result, color: color_result, src: src_result} as IconOptions)
        return value
    }
}
export class SearchButtonOptions_serializer {
    public static write(buffer: SerializerBase, value: SearchButtonOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_fontSize  = value.fontSize
        let value_fontSize_type : int32 = RuntimeType.UNDEFINED
        value_fontSize_type = runtimeType(value_fontSize)
        valueSerializer.writeInt8((value_fontSize_type).toChar())
        if ((value_fontSize_type) != (RuntimeType.UNDEFINED)) {
            const value_fontSize_value  = value_fontSize!
            let value_fontSize_value_type : int32 = RuntimeType.UNDEFINED
            value_fontSize_value_type = runtimeType(value_fontSize_value)
            if (RuntimeType.STRING == value_fontSize_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_fontSize_value_0  = value_fontSize_value as string
                valueSerializer.writeString(value_fontSize_value_0)
            }
            else if (RuntimeType.NUMBER == value_fontSize_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_fontSize_value_1  = value_fontSize_value as number
                valueSerializer.writeNumber(value_fontSize_value_1)
            }
            else if (RuntimeType.OBJECT == value_fontSize_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_fontSize_value_2  = value_fontSize_value as Resource
                Resource_serializer.write(valueSerializer, value_fontSize_value_2)
            }
        }
        const value_fontColor  = value.fontColor
        let value_fontColor_type : int32 = RuntimeType.UNDEFINED
        value_fontColor_type = runtimeType(value_fontColor)
        valueSerializer.writeInt8((value_fontColor_type).toChar())
        if ((value_fontColor_type) != (RuntimeType.UNDEFINED)) {
            const value_fontColor_value  = value_fontColor!
            let value_fontColor_value_type : int32 = RuntimeType.UNDEFINED
            value_fontColor_value_type = runtimeType(value_fontColor_value)
            if (TypeChecker.isColor(value_fontColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_fontColor_value_0  = value_fontColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_fontColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_fontColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_fontColor_value_1  = value_fontColor_value as number
                valueSerializer.writeNumber(value_fontColor_value_1)
            }
            else if (RuntimeType.STRING == value_fontColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_fontColor_value_2  = value_fontColor_value as string
                valueSerializer.writeString(value_fontColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_fontColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_fontColor_value_3  = value_fontColor_value as Resource
                Resource_serializer.write(valueSerializer, value_fontColor_value_3)
            }
        }
        const value_autoDisable  = value.autoDisable
        let value_autoDisable_type : int32 = RuntimeType.UNDEFINED
        value_autoDisable_type = runtimeType(value_autoDisable)
        valueSerializer.writeInt8((value_autoDisable_type).toChar())
        if ((value_autoDisable_type) != (RuntimeType.UNDEFINED)) {
            const value_autoDisable_value  = value_autoDisable!
            valueSerializer.writeBoolean(value_autoDisable_value)
        }
    }
    public static read(buffer: DeserializerBase): SearchButtonOptions {
        let valueDeserializer : DeserializerBase = buffer
        const fontSize_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontSize_buf : Length | undefined
        if ((fontSize_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const fontSize_buf__selector : int32 = valueDeserializer.readInt8()
            let fontSize_buf_ : string | number | Resource | undefined
            if (fontSize_buf__selector == (0).toChar()) {
                fontSize_buf_ = (valueDeserializer.readString() as string)
            }
            else if (fontSize_buf__selector == (1).toChar()) {
                fontSize_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (fontSize_buf__selector == (2).toChar()) {
                fontSize_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for fontSize_buf_ has to be chosen through deserialisation.")
            }
            fontSize_buf = (fontSize_buf_ as string | number | Resource)
        }
        const fontSize_result : Length | undefined = fontSize_buf
        const fontColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontColor_buf : ResourceColor | undefined
        if ((fontColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const fontColor_buf__selector : int32 = valueDeserializer.readInt8()
            let fontColor_buf_ : Color | number | string | Resource | undefined
            if (fontColor_buf__selector == (0).toChar()) {
                fontColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (fontColor_buf__selector == (1).toChar()) {
                fontColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (fontColor_buf__selector == (2).toChar()) {
                fontColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (fontColor_buf__selector == (3).toChar()) {
                fontColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for fontColor_buf_ has to be chosen through deserialisation.")
            }
            fontColor_buf = (fontColor_buf_ as Color | number | string | Resource)
        }
        const fontColor_result : ResourceColor | undefined = fontColor_buf
        const autoDisable_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let autoDisable_buf : boolean | undefined
        if ((autoDisable_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            autoDisable_buf = valueDeserializer.readBoolean()
        }
        const autoDisable_result : boolean | undefined = autoDisable_buf
        let value : SearchButtonOptions = ({fontSize: fontSize_result, fontColor: fontColor_result, autoDisable: autoDisable_result} as SearchButtonOptions)
        return value
    }
}
export class CancelButtonOptions_serializer {
    public static write(buffer: SerializerBase, value: CancelButtonOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_style  = value.style
        let value_style_type : int32 = RuntimeType.UNDEFINED
        value_style_type = runtimeType(value_style)
        valueSerializer.writeInt8((value_style_type).toChar())
        if ((value_style_type) != (RuntimeType.UNDEFINED)) {
            const value_style_value  = (value_style as CancelButtonStyle)
            valueSerializer.writeInt32(TypeChecker.CancelButtonStyle_ToNumeric(value_style_value))
        }
        const value_icon  = value.icon
        let value_icon_type : int32 = RuntimeType.UNDEFINED
        value_icon_type = runtimeType(value_icon)
        valueSerializer.writeInt8((value_icon_type).toChar())
        if ((value_icon_type) != (RuntimeType.UNDEFINED)) {
            const value_icon_value  = value_icon!
            IconOptions_serializer.write(valueSerializer, value_icon_value)
        }
    }
    public static read(buffer: DeserializerBase): CancelButtonOptions {
        let valueDeserializer : DeserializerBase = buffer
        const style_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let style_buf : CancelButtonStyle | undefined
        if ((style_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            style_buf = TypeChecker.CancelButtonStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const style_result : CancelButtonStyle | undefined = style_buf
        const icon_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let icon_buf : IconOptions | undefined
        if ((icon_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            icon_buf = IconOptions_serializer.read(valueDeserializer)
        }
        const icon_result : IconOptions | undefined = icon_buf
        let value : CancelButtonOptions = ({style: style_result, icon: icon_result} as CancelButtonOptions)
        return value
    }
}
export class SearchControllerInternal {
    public static fromPtr(ptr: KPointer): SearchController {
        return new SearchController(ptr)
    }
}
export class SearchController extends TextContentControllerBase implements MaterializedBase {
    constructor(peerPtr: KPointer) {
        super(peerPtr)
    }
    constructor() {
        this(SearchController.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SearchController_construct()
        return retval
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
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            SelectionOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._SearchController_setTextSelection(this.peer!.ptr, selectionStart, selectionEnd, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}

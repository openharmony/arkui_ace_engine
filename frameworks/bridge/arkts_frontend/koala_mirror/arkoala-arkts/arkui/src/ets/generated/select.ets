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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { Resource_serializer, Resource } from "./resource"
import { Font_serializer, DividerStyleOptions_serializer, Offset_serializer, ResourceStr, Font, ResourceColor, Length, Dimension, DividerStyleOptions, Offset, EdgeOutlineWidths, EdgeColors, EdgeOutlineWidths_serializer, EdgeColors_serializer } from "./units"
import { DividerOptions_serializer, DividerOptions } from "./textPicker"
import { TextModifier_serializer, TextModifier } from "./arkui.TextModifier"
import { SymbolGlyphModifier_serializer, SymbolGlyphModifier } from "./arkui.SymbolGlyphModifier"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, BlurStyle, CommonConfiguration, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { Color, OptionWidthMode } from "./enums"
import { ControlSize } from "./button"
import { ContentModifier, AttributeModifier, hookSelectContentModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkSelectPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkSelectPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Select_construct(peerId, flags)
        const _peer  = new ArkSelectPeer(_peerPtr, peerId, "Select", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setSelectOptionsAttribute(options: Array<SelectOption>): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32(options.length as int32)
        for (let i = 0; i < options.length; i++) {
            const options_element : SelectOption = options[i]
            SelectOption_serializer.write(thisSerializer, options_element)
        }
        ArkUIGeneratedNativeModule._SelectInterface_setSelectOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedAttribute(value: number | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SelectAttribute_selected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    valueAttribute(value: ResourceStr | string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if ((RuntimeType.STRING == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as ResourceStr
                let value_value_0_type : int32 = RuntimeType.UNDEFINED
                value_value_0_type = runtimeType(value_value_0)
                if (RuntimeType.STRING == value_value_0_type) {
                    thisSerializer.writeInt8(0)
                    const value_value_0_0  = value_value_0 as string
                    thisSerializer.writeString(value_value_0_0)
                }
                else if (RuntimeType.OBJECT == value_value_0_type) {
                    thisSerializer.writeInt8(1)
                    const value_value_0_1  = value_value_0 as Resource
                    Resource_serializer.write(thisSerializer, value_value_0_1)
                }
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (TypeChecker.isResource(value_value, false, false, false, false, false)) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SelectAttribute_value(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontAttribute(value: Font | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            Font_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_font(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_fontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedOptionBgColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_selectedOptionBgColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedOptionFontAttribute(value: Font | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            Font_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_selectedOptionFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedOptionFontColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_selectedOptionFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    optionBgColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_optionBgColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    optionFontAttribute(value: Font | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            Font_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_optionFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    optionFontColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_optionFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSelectAttribute(value: OnSelectCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_onSelect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    spaceAttribute(value: Length | undefined): void {
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
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SelectAttribute_space(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    arrowPositionAttribute(value: ArrowPosition | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as ArrowPosition)
            thisSerializer.writeInt32(TypeChecker.ArrowPosition_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SelectAttribute_arrowPosition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    optionWidthAttribute(value: Dimension | OptionWidthMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if ((RuntimeType.STRING == value_value_type) || (RuntimeType.NUMBER == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as Dimension
                let value_value_0_type : int32 = RuntimeType.UNDEFINED
                value_value_0_type = runtimeType(value_value_0)
                if (RuntimeType.STRING == value_value_0_type) {
                    thisSerializer.writeInt8(0)
                    const value_value_0_0  = value_value_0 as string
                    thisSerializer.writeString(value_value_0_0)
                }
                else if (RuntimeType.NUMBER == value_value_0_type) {
                    thisSerializer.writeInt8(1)
                    const value_value_0_1  = value_value_0 as number
                    thisSerializer.writeNumber(value_value_0_1)
                }
                else if (RuntimeType.OBJECT == value_value_0_type) {
                    thisSerializer.writeInt8(2)
                    const value_value_0_2  = value_value_0 as Resource
                    Resource_serializer.write(thisSerializer, value_value_0_2)
                }
            }
            else if (TypeChecker.isOptionWidthMode(value_value)) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as OptionWidthMode
                thisSerializer.writeInt32(TypeChecker.OptionWidthMode_ToNumeric(value_value_1))
            }
        }
        ArkUIGeneratedNativeModule._SelectAttribute_optionWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    optionHeightAttribute(value: Dimension | undefined): void {
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
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SelectAttribute_optionHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    menuBackgroundColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_menuBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    menuBackgroundBlurStyleAttribute(value: BlurStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as BlurStyle)
            thisSerializer.writeInt32(TypeChecker.BlurStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SelectAttribute_menuBackgroundBlurStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    controlSizeAttribute(value: ControlSize | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as ControlSize)
            thisSerializer.writeInt32(TypeChecker.ControlSize_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SelectAttribute_controlSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    menuItemContentModifierAttribute(value: ContentModifier<MenuItemConfiguration> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteObject(value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_menuItemContentModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    dividerAttribute(value: DividerOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            DividerOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_divider(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    textModifierAttribute(value: TextModifier | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            TextModifier_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_textModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    arrowModifierAttribute(value: SymbolGlyphModifier | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            SymbolGlyphModifier_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_arrowModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    optionTextModifierAttribute(value: TextModifier | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            TextModifier_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_optionTextModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedOptionTextModifierAttribute(value: TextModifier | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            TextModifier_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_selectedOptionTextModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    dividerStyleAttribute(value: DividerStyleOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            DividerStyleOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_dividerStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    avoidanceAttribute(value: AvoidanceMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as AvoidanceMode)
            thisSerializer.writeInt32(TypeChecker.AvoidanceMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SelectAttribute_avoidance(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    menuOutlineAttribute(value: MenuOutlineOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            MenuOutlineOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_menuOutline(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    menuAlignAttribute(alignType: MenuAlignType | undefined, offset?: Offset): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let alignType_type : int32 = RuntimeType.UNDEFINED
        alignType_type = runtimeType(alignType)
        thisSerializer.writeInt8(alignType_type)
        if ((RuntimeType.UNDEFINED) != (alignType_type)) {
            const alignType_value  = (alignType as MenuAlignType)
            thisSerializer.writeInt32(TypeChecker.MenuAlignType_ToNumeric(alignType_value))
        }
        let offset_type : int32 = RuntimeType.UNDEFINED
        offset_type = runtimeType(offset)
        thisSerializer.writeInt8(offset_type)
        if ((RuntimeType.UNDEFINED) != (offset_type)) {
            const offset_value  = offset!
            Offset_serializer.write(thisSerializer, offset_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_menuAlign(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface SelectOption {
    value: ResourceStr;
    icon?: ResourceStr;
    symbolIcon?: SymbolGlyphModifier;
}
export enum ArrowPosition {
    END = 0,
    START = 1
}
export enum MenuAlignType {
    START = 0,
    CENTER = 1,
    END = 2
}
export enum AvoidanceMode {
    COVER_TARGET = 0,
    AVOID_AROUND_TARGET = 1
}
export type OnSelectCallback = (index: number, selectStr: string) => void;
export interface MenuOutlineOptions {
    width?: Dimension | EdgeOutlineWidths;
    color?: ResourceColor | EdgeColors;
}
export interface SelectAttribute extends CommonMethod {
    selected(value: number | Resource | undefined): this
    value(value: ResourceStr | string | Resource | undefined): this
    font(value: Font | undefined): this
    fontColor(value: ResourceColor | undefined): this
    selectedOptionBgColor(value: ResourceColor | undefined): this
    selectedOptionFont(value: Font | undefined): this
    selectedOptionFontColor(value: ResourceColor | undefined): this
    optionBgColor(value: ResourceColor | undefined): this
    optionFont(value: Font | undefined): this
    optionFontColor(value: ResourceColor | undefined): this
    onSelect(value: OnSelectCallback | undefined): this
    space(value: Length | undefined): this
    arrowPosition(value: ArrowPosition | undefined): this
    optionWidth(value: Dimension | OptionWidthMode | undefined): this
    optionHeight(value: Dimension | undefined): this
    menuBackgroundColor(value: ResourceColor | undefined): this
    menuBackgroundBlurStyle(value: BlurStyle | undefined): this
    controlSize(value: ControlSize | undefined): this
    menuItemContentModifier(value: ContentModifier<MenuItemConfiguration> | undefined): this
    divider(value: DividerOptions | undefined): this
    textModifier(value: TextModifier | undefined): this
    arrowModifier(value: SymbolGlyphModifier | undefined): this
    optionTextModifier(value: TextModifier | undefined): this
    selectedOptionTextModifier(value: TextModifier | undefined): this
    dividerStyle(value: DividerStyleOptions | undefined): this
    avoidance(value: AvoidanceMode | undefined): this
    menuOutline(value: MenuOutlineOptions | undefined): this
    menuAlign(alignType: MenuAlignType | undefined, offset?: Offset): this
    attributeModifier(value: AttributeModifier<SelectAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkSelectStyle extends ArkCommonMethodStyle implements SelectAttribute {
    selected_value?: number | Resource | undefined
    value_value?: ResourceStr | string | Resource | undefined
    font_value?: Font | undefined
    fontColor_value?: ResourceColor | undefined
    selectedOptionBgColor_value?: ResourceColor | undefined
    selectedOptionFont_value?: Font | undefined
    selectedOptionFontColor_value?: ResourceColor | undefined
    optionBgColor_value?: ResourceColor | undefined
    optionFont_value?: Font | undefined
    optionFontColor_value?: ResourceColor | undefined
    onSelect_value?: OnSelectCallback | undefined
    space_value?: Length | undefined
    arrowPosition_value?: ArrowPosition | undefined
    optionWidth_value?: Dimension | OptionWidthMode | undefined
    optionHeight_value?: Dimension | undefined
    menuBackgroundColor_value?: ResourceColor | undefined
    menuBackgroundBlurStyle_value?: BlurStyle | undefined
    controlSize_value?: ControlSize | undefined
    menuItemContentModifier_value?: ContentModifier<MenuItemConfiguration> | undefined
    divider_value?: DividerOptions | undefined
    textModifier_value?: TextModifier | undefined
    arrowModifier_value?: SymbolGlyphModifier | undefined
    optionTextModifier_value?: TextModifier | undefined
    selectedOptionTextModifier_value?: TextModifier | undefined
    dividerStyle_value?: DividerStyleOptions | undefined
    avoidance_value?: AvoidanceMode | undefined
    menuOutline_value?: MenuOutlineOptions | undefined
    attributeModifier_value?: AttributeModifier<SelectAttribute> | AttributeModifier<CommonMethod> | undefined
    public selected(value: number | Resource | undefined): this {
        return this
    }
    public value(value: ResourceStr | string | Resource | undefined): this {
        return this
    }
    public font(value: Font | undefined): this {
        return this
    }
    public fontColor(value: ResourceColor | undefined): this {
        return this
    }
    public selectedOptionBgColor(value: ResourceColor | undefined): this {
        return this
    }
    public selectedOptionFont(value: Font | undefined): this {
        return this
    }
    public selectedOptionFontColor(value: ResourceColor | undefined): this {
        return this
    }
    public optionBgColor(value: ResourceColor | undefined): this {
        return this
    }
    public optionFont(value: Font | undefined): this {
        return this
    }
    public optionFontColor(value: ResourceColor | undefined): this {
        return this
    }
    public onSelect(value: OnSelectCallback | undefined): this {
        return this
    }
    public space(value: Length | undefined): this {
        return this
    }
    public arrowPosition(value: ArrowPosition | undefined): this {
        return this
    }
    public optionWidth(value: Dimension | OptionWidthMode | undefined): this {
        return this
    }
    public optionHeight(value: Dimension | undefined): this {
        return this
    }
    public menuBackgroundColor(value: ResourceColor | undefined): this {
        return this
    }
    public menuBackgroundBlurStyle(value: BlurStyle | undefined): this {
        return this
    }
    public controlSize(value: ControlSize | undefined): this {
        return this
    }
    public menuItemContentModifier(value: ContentModifier<MenuItemConfiguration> | undefined): this {
        return this
    }
    public divider(value: DividerOptions | undefined): this {
        return this
    }
    public textModifier(value: TextModifier | undefined): this {
        return this
    }
    public arrowModifier(value: SymbolGlyphModifier | undefined): this {
        return this
    }
    public optionTextModifier(value: TextModifier | undefined): this {
        return this
    }
    public selectedOptionTextModifier(value: TextModifier | undefined): this {
        return this
    }
    public dividerStyle(value: DividerStyleOptions | undefined): this {
        return this
    }
    public avoidance(value: AvoidanceMode | undefined): this {
        return this
    }
    public menuOutline(value: MenuOutlineOptions | undefined): this {
        return this
    }
    public menuAlign(alignType: MenuAlignType | undefined, offset?: Offset): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<SelectAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: SelectAttribute): void {
        super.apply(target)
        if (this.selected_value !== undefined)
            target.selected(this.selected_value!)
        if (this.value_value !== undefined)
            target.value(this.value_value!)
        if (this.font_value !== undefined)
            target.font(this.font_value!)
        if (this.fontColor_value !== undefined)
            target.fontColor(this.fontColor_value!)
        if (this.selectedOptionBgColor_value !== undefined)
            target.selectedOptionBgColor(this.selectedOptionBgColor_value!)
        if (this.selectedOptionFont_value !== undefined)
            target.selectedOptionFont(this.selectedOptionFont_value!)
        if (this.selectedOptionFontColor_value !== undefined)
            target.selectedOptionFontColor(this.selectedOptionFontColor_value!)
        if (this.optionBgColor_value !== undefined)
            target.optionBgColor(this.optionBgColor_value!)
        if (this.optionFont_value !== undefined)
            target.optionFont(this.optionFont_value!)
        if (this.optionFontColor_value !== undefined)
            target.optionFontColor(this.optionFontColor_value!)
        if (this.onSelect_value !== undefined)
            target.onSelect(this.onSelect_value!)
        if (this.space_value !== undefined)
            target.space(this.space_value!)
        if (this.arrowPosition_value !== undefined)
            target.arrowPosition(this.arrowPosition_value!)
        if (this.optionWidth_value !== undefined)
            target.optionWidth(this.optionWidth_value!)
        if (this.optionHeight_value !== undefined)
            target.optionHeight(this.optionHeight_value!)
        if (this.menuBackgroundColor_value !== undefined)
            target.menuBackgroundColor(this.menuBackgroundColor_value!)
        if (this.menuBackgroundBlurStyle_value !== undefined)
            target.menuBackgroundBlurStyle(this.menuBackgroundBlurStyle_value!)
        if (this.controlSize_value !== undefined)
            target.controlSize(this.controlSize_value!)
        if (this.menuItemContentModifier_value !== undefined)
            target.menuItemContentModifier(this.menuItemContentModifier_value!)
        if (this.divider_value !== undefined)
            target.divider(this.divider_value!)
        if (this.textModifier_value !== undefined)
            target.textModifier(this.textModifier_value!)
        if (this.arrowModifier_value !== undefined)
            target.arrowModifier(this.arrowModifier_value!)
        if (this.optionTextModifier_value !== undefined)
            target.optionTextModifier(this.optionTextModifier_value!)
        if (this.selectedOptionTextModifier_value !== undefined)
            target.selectedOptionTextModifier(this.selectedOptionTextModifier_value!)
        if (this.dividerStyle_value !== undefined)
            target.dividerStyle(this.dividerStyle_value!)
        if (this.avoidance_value !== undefined)
            target.avoidance(this.avoidance_value!)
        if (this.menuOutline_value !== undefined)
            target.menuOutline(this.menuOutline_value!)
    }
}
export interface MenuItemConfiguration extends CommonConfiguration<MenuItemConfiguration> {
    value: ResourceStr;
    icon?: ResourceStr;
    symbolIcon?: SymbolGlyphModifier;
    selected: boolean;
    index: number;
}

export class ArkSelectComponent extends ArkCommonMethodComponent implements SelectAttribute {
    getPeer(): ArkSelectPeer {
        return (this.peer as ArkSelectPeer)
    }
    public setSelectOptions(options: Array<SelectOption>): this {
        if (this.checkPriority("setSelectOptions")) {
            const options_casted = options as (Array<SelectOption>)
            this.getPeer()?.setSelectOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public selected(value: number | Resource | undefined): this {
        if (this.checkPriority("selected")) {
            const value_casted = value as (number | Resource | undefined)
            this.getPeer()?.selectedAttribute(value_casted)
            return this
        }
        return this
    }
    public value(value: ResourceStr | string | Resource | undefined): this {
        if (this.checkPriority("value")) {
            const value_casted = value as (ResourceStr | string | Resource | undefined)
            this.getPeer()?.valueAttribute(value_casted)
            return this
        }
        return this
    }
    public font(value: Font | undefined): this {
        if (this.checkPriority("font")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.fontAttribute(value_casted)
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
    public selectedOptionBgColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("selectedOptionBgColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.selectedOptionBgColorAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedOptionFont(value: Font | undefined): this {
        if (this.checkPriority("selectedOptionFont")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.selectedOptionFontAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedOptionFontColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("selectedOptionFontColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.selectedOptionFontColorAttribute(value_casted)
            return this
        }
        return this
    }
    public optionBgColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("optionBgColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.optionBgColorAttribute(value_casted)
            return this
        }
        return this
    }
    public optionFont(value: Font | undefined): this {
        if (this.checkPriority("optionFont")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.optionFontAttribute(value_casted)
            return this
        }
        return this
    }
    public optionFontColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("optionFontColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.optionFontColorAttribute(value_casted)
            return this
        }
        return this
    }
    public onSelect(value: OnSelectCallback | undefined): this {
        if (this.checkPriority("onSelect")) {
            const value_casted = value as (OnSelectCallback | undefined)
            this.getPeer()?.onSelectAttribute(value_casted)
            return this
        }
        return this
    }
    public space(value: Length | undefined): this {
        if (this.checkPriority("space")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.spaceAttribute(value_casted)
            return this
        }
        return this
    }
    public arrowPosition(value: ArrowPosition | undefined): this {
        if (this.checkPriority("arrowPosition")) {
            const value_casted = value as (ArrowPosition | undefined)
            this.getPeer()?.arrowPositionAttribute(value_casted)
            return this
        }
        return this
    }
    public optionWidth(value: Dimension | OptionWidthMode | undefined): this {
        if (this.checkPriority("optionWidth")) {
            const value_casted = value as (Dimension | OptionWidthMode | undefined)
            this.getPeer()?.optionWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public optionHeight(value: Dimension | undefined): this {
        if (this.checkPriority("optionHeight")) {
            const value_casted = value as (Dimension | undefined)
            this.getPeer()?.optionHeightAttribute(value_casted)
            return this
        }
        return this
    }
    public menuBackgroundColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("menuBackgroundColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.menuBackgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    public menuBackgroundBlurStyle(value: BlurStyle | undefined): this {
        if (this.checkPriority("menuBackgroundBlurStyle")) {
            const value_casted = value as (BlurStyle | undefined)
            this.getPeer()?.menuBackgroundBlurStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public controlSize(value: ControlSize | undefined): this {
        if (this.checkPriority("controlSize")) {
            const value_casted = value as (ControlSize | undefined)
            this.getPeer()?.controlSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public menuItemContentModifier(value: ContentModifier<MenuItemConfiguration> | undefined): this {
        if (this.checkPriority("menuItemContentModifier")) {
            hookSelectContentModifier(this, value)
        }
        return this
    }
    public divider(value: DividerOptions | undefined): this {
        if (this.checkPriority("divider")) {
            const value_casted = value as (DividerOptions | undefined)
            this.getPeer()?.dividerAttribute(value_casted)
            return this
        }
        return this
    }
    public textModifier(value: TextModifier | undefined): this {
        if (this.checkPriority("textModifier")) {
            const value_casted = value as (TextModifier | undefined)
            this.getPeer()?.textModifierAttribute(value_casted)
            return this
        }
        return this
    }
    public arrowModifier(value: SymbolGlyphModifier | undefined): this {
        if (this.checkPriority("arrowModifier")) {
            const value_casted = value as (SymbolGlyphModifier | undefined)
            this.getPeer()?.arrowModifierAttribute(value_casted)
            return this
        }
        return this
    }
    public optionTextModifier(value: TextModifier | undefined): this {
        if (this.checkPriority("optionTextModifier")) {
            const value_casted = value as (TextModifier | undefined)
            this.getPeer()?.optionTextModifierAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedOptionTextModifier(value: TextModifier | undefined): this {
        if (this.checkPriority("selectedOptionTextModifier")) {
            const value_casted = value as (TextModifier | undefined)
            this.getPeer()?.selectedOptionTextModifierAttribute(value_casted)
            return this
        }
        return this
    }
    public dividerStyle(value: DividerStyleOptions | undefined): this {
        if (this.checkPriority("dividerStyle")) {
            const value_casted = value as (DividerStyleOptions | undefined)
            this.getPeer()?.dividerStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public avoidance(value: AvoidanceMode | undefined): this {
        if (this.checkPriority("avoidance")) {
            const value_casted = value as (AvoidanceMode | undefined)
            this.getPeer()?.avoidanceAttribute(value_casted)
            return this
        }
        return this
    }
    public menuOutline(value: MenuOutlineOptions | undefined): this {
        if (this.checkPriority("menuOutline")) {
            const value_casted = value as (MenuOutlineOptions | undefined)
            this.getPeer()?.menuOutlineAttribute(value_casted)
            return this
        }
        return this
    }
    public menuAlign(alignType: MenuAlignType | undefined, offset?: Offset): this {
        if (this.checkPriority("menuAlign")) {
            const alignType_casted = alignType as (MenuAlignType | undefined)
            const offset_casted = offset as (Offset | undefined)
            this.getPeer()?.menuAlignAttribute(alignType_casted, offset_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<SelectAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withSelectStyle(receiver: SelectAttribute, modifier: AttributeModifier<SelectAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkSelectStyle()
        if (modifier!.isUpdater)
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
@memo
@BuilderLambda("SelectImpl")
export function Select(
    options: Array<SelectOption>,
    @memo
    content_?: () => void,
): SelectAttribute {
    throw new Error("Not implemented")
}

@memo
export function SelectImpl(
    @memo
    style: ((attributes: SelectAttribute) => void) | undefined,
    options: Array<SelectOption>,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkSelectComponent>((): ArkSelectComponent => {
        return new ArkSelectComponent()
    })
    NodeAttach<ArkSelectPeer>((): ArkSelectPeer => ArkSelectPeer.create(receiver), (_: ArkSelectPeer): void => {
        receiver.setSelectOptions(options)
        style?.(receiver)
        withSelectStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class MenuItemConfiguration_serializer {
    public static write(buffer: SerializerBase, value: MenuItemConfiguration): void {
        let valueSerializer : SerializerBase = buffer
        const value_enabled  = value.enabled
        valueSerializer.writeBoolean(value_enabled)
        const value_contentModifier  = value.contentModifier
        valueSerializer.holdAndWriteObject(value_contentModifier)
        const value_value  = value.value
        let value_value_type : int32 = RuntimeType.UNDEFINED
        value_value_type = runtimeType(value_value)
        if (RuntimeType.STRING == value_value_type) {
            valueSerializer.writeInt8(0)
            const value_value_0  = value_value as string
            valueSerializer.writeString(value_value_0)
        }
        else if (RuntimeType.OBJECT == value_value_type) {
            valueSerializer.writeInt8(1)
            const value_value_1  = value_value as Resource
            Resource_serializer.write(valueSerializer, value_value_1)
        }
        const value_icon  = value.icon
        let value_icon_type : int32 = RuntimeType.UNDEFINED
        value_icon_type = runtimeType(value_icon)
        valueSerializer.writeInt8(value_icon_type)
        if ((RuntimeType.UNDEFINED) != (value_icon_type)) {
            const value_icon_value  = value_icon!
            let value_icon_value_type : int32 = RuntimeType.UNDEFINED
            value_icon_value_type = runtimeType(value_icon_value)
            if (RuntimeType.STRING == value_icon_value_type) {
                valueSerializer.writeInt8(0)
                const value_icon_value_0  = value_icon_value as string
                valueSerializer.writeString(value_icon_value_0)
            }
            else if (RuntimeType.OBJECT == value_icon_value_type) {
                valueSerializer.writeInt8(1)
                const value_icon_value_1  = value_icon_value as Resource
                Resource_serializer.write(valueSerializer, value_icon_value_1)
            }
        }
        const value_symbolIcon  = value.symbolIcon
        let value_symbolIcon_type : int32 = RuntimeType.UNDEFINED
        value_symbolIcon_type = runtimeType(value_symbolIcon)
        valueSerializer.writeInt8(value_symbolIcon_type)
        if ((RuntimeType.UNDEFINED) != (value_symbolIcon_type)) {
            const value_symbolIcon_value  = value_symbolIcon!
            SymbolGlyphModifier_serializer.write(valueSerializer, value_symbolIcon_value)
        }
        const value_selected  = value.selected
        valueSerializer.writeBoolean(value_selected)
        const value_index  = value.index
        valueSerializer.writeNumber(value_index)
    }
    public static read(buffer: DeserializerBase): MenuItemConfiguration {
        let valueDeserializer : DeserializerBase = buffer
        const enabled_result : boolean = valueDeserializer.readBoolean()
        const contentModifier_result : ContentModifier<MenuItemConfiguration> = (valueDeserializer.readObject() as ContentModifier<MenuItemConfiguration>)
        const value_buf_selector : int32 = valueDeserializer.readInt8()
        let value_buf : string | Resource | undefined
        if (value_buf_selector == 0) {
            value_buf = (valueDeserializer.readString() as string)
        }
        else if (value_buf_selector == 1) {
            value_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for value_buf has to be chosen through deserialisation.")
        }
        const value_result : ResourceStr = (value_buf as string | Resource)
        const icon_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let icon_buf : ResourceStr | undefined
        if ((RuntimeType.UNDEFINED) != (icon_buf_runtimeType))
        {
            const icon_buf__selector : int32 = valueDeserializer.readInt8()
            let icon_buf_ : string | Resource | undefined
            if (icon_buf__selector == 0) {
                icon_buf_ = (valueDeserializer.readString() as string)
            }
            else if (icon_buf__selector == 1) {
                icon_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for icon_buf_ has to be chosen through deserialisation.")
            }
            icon_buf = (icon_buf_ as string | Resource)
        }
        const icon_result : ResourceStr | undefined = icon_buf
        const symbolIcon_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let symbolIcon_buf : SymbolGlyphModifier | undefined
        if ((RuntimeType.UNDEFINED) != (symbolIcon_buf_runtimeType))
        {
            symbolIcon_buf = SymbolGlyphModifier_serializer.read(valueDeserializer)
        }
        const symbolIcon_result : SymbolGlyphModifier | undefined = symbolIcon_buf
        const selected_result : boolean = valueDeserializer.readBoolean()
        const index_result : number = (valueDeserializer.readNumber() as number)
        throw new Error("Interface with functions is not supported")
    }
}
export class SelectOption_serializer {
    public static write(buffer: SerializerBase, value: SelectOption): void {
        let valueSerializer : SerializerBase = buffer
        const value_value  = value.value
        let value_value_type : int32 = RuntimeType.UNDEFINED
        value_value_type = runtimeType(value_value)
        if (RuntimeType.STRING == value_value_type) {
            valueSerializer.writeInt8(0)
            const value_value_0  = value_value as string
            valueSerializer.writeString(value_value_0)
        }
        else if (RuntimeType.OBJECT == value_value_type) {
            valueSerializer.writeInt8(1)
            const value_value_1  = value_value as Resource
            Resource_serializer.write(valueSerializer, value_value_1)
        }
        const value_icon  = value.icon
        let value_icon_type : int32 = RuntimeType.UNDEFINED
        value_icon_type = runtimeType(value_icon)
        valueSerializer.writeInt8(value_icon_type)
        if ((RuntimeType.UNDEFINED) != (value_icon_type)) {
            const value_icon_value  = value_icon!
            let value_icon_value_type : int32 = RuntimeType.UNDEFINED
            value_icon_value_type = runtimeType(value_icon_value)
            if (RuntimeType.STRING == value_icon_value_type) {
                valueSerializer.writeInt8(0)
                const value_icon_value_0  = value_icon_value as string
                valueSerializer.writeString(value_icon_value_0)
            }
            else if (RuntimeType.OBJECT == value_icon_value_type) {
                valueSerializer.writeInt8(1)
                const value_icon_value_1  = value_icon_value as Resource
                Resource_serializer.write(valueSerializer, value_icon_value_1)
            }
        }
        const value_symbolIcon  = value.symbolIcon
        let value_symbolIcon_type : int32 = RuntimeType.UNDEFINED
        value_symbolIcon_type = runtimeType(value_symbolIcon)
        valueSerializer.writeInt8(value_symbolIcon_type)
        if ((RuntimeType.UNDEFINED) != (value_symbolIcon_type)) {
            const value_symbolIcon_value  = value_symbolIcon!
            SymbolGlyphModifier_serializer.write(valueSerializer, value_symbolIcon_value)
        }
    }
    public static read(buffer: DeserializerBase): SelectOption {
        let valueDeserializer : DeserializerBase = buffer
        const value_buf_selector : int32 = valueDeserializer.readInt8()
        let value_buf : string | Resource | undefined
        if (value_buf_selector == 0) {
            value_buf = (valueDeserializer.readString() as string)
        }
        else if (value_buf_selector == 1) {
            value_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for value_buf has to be chosen through deserialisation.")
        }
        const value_result : ResourceStr = (value_buf as string | Resource)
        const icon_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let icon_buf : ResourceStr | undefined
        if ((RuntimeType.UNDEFINED) != (icon_buf_runtimeType))
        {
            const icon_buf__selector : int32 = valueDeserializer.readInt8()
            let icon_buf_ : string | Resource | undefined
            if (icon_buf__selector == 0) {
                icon_buf_ = (valueDeserializer.readString() as string)
            }
            else if (icon_buf__selector == 1) {
                icon_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for icon_buf_ has to be chosen through deserialisation.")
            }
            icon_buf = (icon_buf_ as string | Resource)
        }
        const icon_result : ResourceStr | undefined = icon_buf
        const symbolIcon_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let symbolIcon_buf : SymbolGlyphModifier | undefined
        if ((RuntimeType.UNDEFINED) != (symbolIcon_buf_runtimeType))
        {
            symbolIcon_buf = SymbolGlyphModifier_serializer.read(valueDeserializer)
        }
        const symbolIcon_result : SymbolGlyphModifier | undefined = symbolIcon_buf
        let value : SelectOption = ({value: value_result, icon: icon_result, symbolIcon: symbolIcon_result} as SelectOption)
        return value
    }
}
export class MenuOutlineOptions_serializer {
    public static write(buffer: SerializerBase, value: MenuOutlineOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_width  = value.width
        let value_width_type : int32 = RuntimeType.UNDEFINED
        value_width_type = runtimeType(value_width)
        valueSerializer.writeInt8(value_width_type)
        if ((RuntimeType.UNDEFINED) != (value_width_type)) {
            const value_width_value  = value_width!
            let value_width_value_type : int32 = RuntimeType.UNDEFINED
            value_width_value_type = runtimeType(value_width_value)
            if ((RuntimeType.STRING == value_width_value_type) || (RuntimeType.NUMBER == value_width_value_type) || (RuntimeType.OBJECT == value_width_value_type)) {
                valueSerializer.writeInt8(0)
                const value_width_value_0  = value_width_value as Dimension
                let value_width_value_0_type : int32 = RuntimeType.UNDEFINED
                value_width_value_0_type = runtimeType(value_width_value_0)
                if (RuntimeType.STRING == value_width_value_0_type) {
                    valueSerializer.writeInt8(0)
                    const value_width_value_0_0  = value_width_value_0 as string
                    valueSerializer.writeString(value_width_value_0_0)
                }
                else if (RuntimeType.NUMBER == value_width_value_0_type) {
                    valueSerializer.writeInt8(1)
                    const value_width_value_0_1  = value_width_value_0 as number
                    valueSerializer.writeNumber(value_width_value_0_1)
                }
                else if (RuntimeType.OBJECT == value_width_value_0_type) {
                    valueSerializer.writeInt8(2)
                    const value_width_value_0_2  = value_width_value_0 as Resource
                    Resource_serializer.write(valueSerializer, value_width_value_0_2)
                }
            }
            else if (TypeChecker.isEdgeOutlineWidths(value_width_value, false, false, false, false)) {
                valueSerializer.writeInt8(1)
                const value_width_value_1  = value_width_value as EdgeOutlineWidths
                EdgeOutlineWidths_serializer.write(valueSerializer, value_width_value_1)
            }
        }
        const value_color  = value.color
        let value_color_type : int32 = RuntimeType.UNDEFINED
        value_color_type = runtimeType(value_color)
        valueSerializer.writeInt8(value_color_type)
        if ((RuntimeType.UNDEFINED) != (value_color_type)) {
            const value_color_value  = value_color!
            let value_color_value_type : int32 = RuntimeType.UNDEFINED
            value_color_value_type = runtimeType(value_color_value)
            if ((TypeChecker.isColor(value_color_value)) || (RuntimeType.NUMBER == value_color_value_type) || (RuntimeType.STRING == value_color_value_type) || (RuntimeType.OBJECT == value_color_value_type)) {
                valueSerializer.writeInt8(0)
                const value_color_value_0  = value_color_value as ResourceColor
                let value_color_value_0_type : int32 = RuntimeType.UNDEFINED
                value_color_value_0_type = runtimeType(value_color_value_0)
                if (TypeChecker.isColor(value_color_value_0)) {
                    valueSerializer.writeInt8(0)
                    const value_color_value_0_0  = value_color_value_0 as Color
                    valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_color_value_0_0))
                }
                else if (RuntimeType.NUMBER == value_color_value_0_type) {
                    valueSerializer.writeInt8(1)
                    const value_color_value_0_1  = value_color_value_0 as number
                    valueSerializer.writeNumber(value_color_value_0_1)
                }
                else if (RuntimeType.STRING == value_color_value_0_type) {
                    valueSerializer.writeInt8(2)
                    const value_color_value_0_2  = value_color_value_0 as string
                    valueSerializer.writeString(value_color_value_0_2)
                }
                else if (RuntimeType.OBJECT == value_color_value_0_type) {
                    valueSerializer.writeInt8(3)
                    const value_color_value_0_3  = value_color_value_0 as Resource
                    Resource_serializer.write(valueSerializer, value_color_value_0_3)
                }
            }
            else if (TypeChecker.isEdgeColors(value_color_value, false, false, false, false)) {
                valueSerializer.writeInt8(1)
                const value_color_value_1  = value_color_value as EdgeColors
                EdgeColors_serializer.write(valueSerializer, value_color_value_1)
            }
        }
    }
    public static read(buffer: DeserializerBase): MenuOutlineOptions {
        let valueDeserializer : DeserializerBase = buffer
        const width_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let width_buf : Dimension | EdgeOutlineWidths | undefined
        if ((RuntimeType.UNDEFINED) != (width_buf_runtimeType))
        {
            const width_buf__selector : int32 = valueDeserializer.readInt8()
            let width_buf_ : Dimension | EdgeOutlineWidths | undefined
            if (width_buf__selector == 0) {
                const width_buf__u_selector : int32 = valueDeserializer.readInt8()
                let width_buf__u : string | number | Resource | undefined
                if (width_buf__u_selector == 0) {
                    width_buf__u = (valueDeserializer.readString() as string)
                }
                else if (width_buf__u_selector == 1) {
                    width_buf__u = (valueDeserializer.readNumber() as number)
                }
                else if (width_buf__u_selector == 2) {
                    width_buf__u = Resource_serializer.read(valueDeserializer)
                }
                else {
                    throw new Error("One of the branches for width_buf__u has to be chosen through deserialisation.")
                }
                width_buf_ = (width_buf__u as string | number | Resource)
            }
            else if (width_buf__selector == 1) {
                width_buf_ = EdgeOutlineWidths_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for width_buf_ has to be chosen through deserialisation.")
            }
            width_buf = (width_buf_ as Dimension | EdgeOutlineWidths)
        }
        const width_result : Dimension | EdgeOutlineWidths | undefined = width_buf
        const color_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let color_buf : ResourceColor | EdgeColors | undefined
        if ((RuntimeType.UNDEFINED) != (color_buf_runtimeType))
        {
            const color_buf__selector : int32 = valueDeserializer.readInt8()
            let color_buf_ : ResourceColor | EdgeColors | undefined
            if (color_buf__selector == 0) {
                const color_buf__u_selector : int32 = valueDeserializer.readInt8()
                let color_buf__u : Color | number | string | Resource | undefined
                if (color_buf__u_selector == 0) {
                    color_buf__u = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
                }
                else if (color_buf__u_selector == 1) {
                    color_buf__u = (valueDeserializer.readNumber() as number)
                }
                else if (color_buf__u_selector == 2) {
                    color_buf__u = (valueDeserializer.readString() as string)
                }
                else if (color_buf__u_selector == 3) {
                    color_buf__u = Resource_serializer.read(valueDeserializer)
                }
                else {
                    throw new Error("One of the branches for color_buf__u has to be chosen through deserialisation.")
                }
                color_buf_ = (color_buf__u as Color | number | string | Resource)
            }
            else if (color_buf__selector == 1) {
                color_buf_ = EdgeColors_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for color_buf_ has to be chosen through deserialisation.")
            }
            color_buf = (color_buf_ as ResourceColor | EdgeColors)
        }
        const color_result : ResourceColor | EdgeColors | undefined = color_buf
        let value : MenuOutlineOptions = ({width: width_result, color: color_result} as MenuOutlineOptions)
        return value
    }
}

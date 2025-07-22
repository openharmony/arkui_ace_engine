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
import { Resource_serializer, Resource } from "./../generated/resource"
import { Font_serializer, DividerStyleOptions_serializer, Offset_serializer, ResourceStr, Font, ResourceColor, Length, Dimension, DividerStyleOptions, Offset, EdgeOutlineWidths, EdgeColors, EdgeOutlineWidths_serializer, EdgeColors_serializer } from "./units"
import { DividerOptions_serializer, DividerOptions } from "./textPicker"
import { TextModifier_serializer, TextModifier } from "./../generated/arkui.TextModifier"
import { SymbolGlyphModifier_serializer, SymbolGlyphModifier } from "./../generated/arkui.SymbolGlyphModifier"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, BlurStyle, CommonConfiguration, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { Color, OptionWidthMode } from "./enums"
import { ControlSize } from "./button"
import { ContentModifier, AttributeModifier, hookSelectContentModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
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
        thisSerializer.writeInt32((options.length).toInt())
        for (let options_counter_i = 0; options_counter_i < options.length; options_counter_i++) {
            const options_element : SelectOption = options[options_counter_i]
            SelectOption_serializer.write(thisSerializer, options_element)
        }
        ArkUIGeneratedNativeModule._SelectInterface_setSelectOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedAttribute(value: number | Resource | undefined): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_setSelected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setValueAttribute(value: ResourceStr | string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if ((RuntimeType.STRING == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as ResourceStr
                let value_value_0_type : int32 = RuntimeType.UNDEFINED
                value_value_0_type = runtimeType(value_value_0)
                if (RuntimeType.STRING == value_value_0_type) {
                    thisSerializer.writeInt8((0).toChar())
                    const value_value_0_0  = value_value_0 as string
                    thisSerializer.writeString(value_value_0_0)
                }
                else if (RuntimeType.OBJECT == value_value_0_type) {
                    thisSerializer.writeInt8((1).toChar())
                    const value_value_0_1  = value_value_0 as Resource
                    Resource_serializer.write(thisSerializer, value_value_0_1)
                }
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (TypeChecker.isResource(value_value, false, false, false, false, false)) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setValue(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontAttribute(value: Font | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            Font_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SelectAttribute_setFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedOptionBgColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_setSelectedOptionBgColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedOptionFontAttribute(value: Font | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            Font_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setSelectedOptionFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedOptionFontColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_setSelectedOptionFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOptionBgColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_setOptionBgColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOptionFontAttribute(value: Font | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            Font_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setOptionFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOptionFontColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_setOptionFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSelectAttribute(value: OnSelectCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setOnSelect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSpaceAttribute(value: Length | undefined): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_setSpace(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setArrowPositionAttribute(value: ArrowPosition | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as ArrowPosition)
            thisSerializer.writeInt32(TypeChecker.ArrowPosition_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setArrowPosition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOptionWidthAttribute(value: Dimension | OptionWidthMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if ((RuntimeType.STRING == value_value_type) || (RuntimeType.NUMBER == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Dimension
                let value_value_0_type : int32 = RuntimeType.UNDEFINED
                value_value_0_type = runtimeType(value_value_0)
                if (RuntimeType.STRING == value_value_0_type) {
                    thisSerializer.writeInt8((0).toChar())
                    const value_value_0_0  = value_value_0 as string
                    thisSerializer.writeString(value_value_0_0)
                }
                else if (RuntimeType.NUMBER == value_value_0_type) {
                    thisSerializer.writeInt8((1).toChar())
                    const value_value_0_1  = value_value_0 as number
                    thisSerializer.writeNumber(value_value_0_1)
                }
                else if (RuntimeType.OBJECT == value_value_0_type) {
                    thisSerializer.writeInt8((2).toChar())
                    const value_value_0_2  = value_value_0 as Resource
                    Resource_serializer.write(thisSerializer, value_value_0_2)
                }
            }
            else if (TypeChecker.isOptionWidthMode(value_value)) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as OptionWidthMode
                thisSerializer.writeInt32(TypeChecker.OptionWidthMode_ToNumeric(value_value_1))
            }
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setOptionWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOptionHeightAttribute(value: Dimension | undefined): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_setOptionHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMenuBackgroundColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_setMenuBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMenuBackgroundBlurStyleAttribute(value: BlurStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as BlurStyle)
            thisSerializer.writeInt32(TypeChecker.BlurStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setMenuBackgroundBlurStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setControlSizeAttribute(value: ControlSize | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as ControlSize)
            thisSerializer.writeInt32(TypeChecker.ControlSize_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setControlSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMenuItemContentModifierAttribute(value: ContentModifier<MenuItemConfiguration> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteObject(value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setMenuItemContentModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDividerAttribute(value: DividerOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            DividerOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setDivider(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextModifierAttribute(value: TextModifier | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            TextModifier_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setTextModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setArrowModifierAttribute(value: SymbolGlyphModifier | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            SymbolGlyphModifier_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setArrowModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOptionTextModifierAttribute(value: TextModifier | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            TextModifier_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setOptionTextModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedOptionTextModifierAttribute(value: TextModifier | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            TextModifier_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setSelectedOptionTextModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDividerStyleAttribute(value: DividerStyleOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            DividerStyleOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setDividerStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAvoidanceAttribute(value: AvoidanceMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as AvoidanceMode)
            thisSerializer.writeInt32(TypeChecker.AvoidanceMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setAvoidance(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMenuOutlineAttribute(value: MenuOutlineOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            MenuOutlineOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setMenuOutline(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMenuAlignAttribute(alignType: MenuAlignType | undefined, offset?: Offset): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let alignType_type : int32 = RuntimeType.UNDEFINED
        alignType_type = runtimeType(alignType)
        thisSerializer.writeInt8((alignType_type).toChar())
        if ((alignType_type) != (RuntimeType.UNDEFINED)) {
            const alignType_value  = (alignType as MenuAlignType)
            thisSerializer.writeInt32(TypeChecker.MenuAlignType_ToNumeric(alignType_value))
        }
        let offset_type : int32 = RuntimeType.UNDEFINED
        offset_type = runtimeType(offset)
        thisSerializer.writeInt8((offset_type).toChar())
        if ((offset_type) != (RuntimeType.UNDEFINED)) {
            const offset_value  = offset!
            Offset_serializer.write(thisSerializer, offset_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setMenuAlign(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    set_onChangeEvent_selectedAttribute(callback_: ((selected: number | Resource | undefined) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._SelectAttribute_set_onChangeEvent_selected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    set_onChangeEvent_valueAttribute(callback_: ((value: ResourceStr | string | Resource | undefined) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._SelectAttribute_set_onChangeEvent_value(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    selected(value: number | Resource | undefined): this {
        throw new Error("Unimplemented method selected")
    }
    value(value: ResourceStr | string | Resource | undefined): this {
        throw new Error("Unimplemented method value")
    }
    font(value: Font | undefined): this {
        throw new Error("Unimplemented method font")
    }
    fontColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method fontColor")
    }
    selectedOptionBgColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method selectedOptionBgColor")
    }
    selectedOptionFont(value: Font | undefined): this {
        throw new Error("Unimplemented method selectedOptionFont")
    }
    selectedOptionFontColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method selectedOptionFontColor")
    }
    optionBgColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method optionBgColor")
    }
    optionFont(value: Font | undefined): this {
        throw new Error("Unimplemented method optionFont")
    }
    optionFontColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method optionFontColor")
    }
    onSelect(value: OnSelectCallback | undefined): this {
        throw new Error("Unimplemented method onSelect")
    }
    space(value: Length | undefined): this {
        throw new Error("Unimplemented method space")
    }
    arrowPosition(value: ArrowPosition | undefined): this {
        throw new Error("Unimplemented method arrowPosition")
    }
    optionWidth(value: Dimension | OptionWidthMode | undefined): this {
        throw new Error("Unimplemented method optionWidth")
    }
    optionHeight(value: Dimension | undefined): this {
        throw new Error("Unimplemented method optionHeight")
    }
    menuBackgroundColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method menuBackgroundColor")
    }
    menuBackgroundBlurStyle(value: BlurStyle | undefined): this {
        throw new Error("Unimplemented method menuBackgroundBlurStyle")
    }
    controlSize(value: ControlSize | undefined): this {
        throw new Error("Unimplemented method controlSize")
    }
    menuItemContentModifier(value: ContentModifier<MenuItemConfiguration> | undefined): this {
        throw new Error("Unimplemented method menuItemContentModifier")
    }
    divider(value: DividerOptions | undefined): this {
        throw new Error("Unimplemented method divider")
    }
    textModifier(value: TextModifier | undefined): this {
        throw new Error("Unimplemented method textModifier")
    }
    arrowModifier(value: SymbolGlyphModifier | undefined): this {
        throw new Error("Unimplemented method arrowModifier")
    }
    optionTextModifier(value: TextModifier | undefined): this {
        throw new Error("Unimplemented method optionTextModifier")
    }
    selectedOptionTextModifier(value: TextModifier | undefined): this {
        throw new Error("Unimplemented method selectedOptionTextModifier")
    }
    dividerStyle(value: DividerStyleOptions | undefined): this {
        throw new Error("Unimplemented method dividerStyle")
    }
    avoidance(value: AvoidanceMode | undefined): this {
        throw new Error("Unimplemented method avoidance")
    }
    menuOutline(value: MenuOutlineOptions | undefined): this {
        throw new Error("Unimplemented method menuOutline")
    }
    menuAlign(alignType: MenuAlignType | undefined, offset?: Offset): this {
        throw new Error("Unimplemented method menuAlign")
    }
    _onChangeEvent_selected(callback_: ((selected: number | Resource | undefined) => void)): void {
        throw new Error("Unimplemented method _onChangeEvent_selected")
    }
    _onChangeEvent_value(callback_: ((value: ResourceStr | string | Resource | undefined) => void)): void {
        throw new Error("Unimplemented method _onChangeEvent_value")
    }
    attributeModifier(value: AttributeModifier<SelectAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
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
    public _onChangeEvent_selected(callback_: ((selected: number | Resource | undefined) => void)): void {
        throw new Error("Unimplemented")
    }
    public _onChangeEvent_value(callback_: ((value: ResourceStr | string | Resource | undefined) => void)): void {
        throw new Error("Unimplemented")
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
            this.getPeer()?.setSelectedAttribute(value_casted)
            return this
        }
        return this
    }
    public value(value: ResourceStr | string | Resource | undefined): this {
        if (this.checkPriority("value")) {
            const value_casted = value as (ResourceStr | string | Resource | undefined)
            this.getPeer()?.setValueAttribute(value_casted)
            return this
        }
        return this
    }
    public font(value: Font | undefined): this {
        if (this.checkPriority("font")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.setFontAttribute(value_casted)
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
    public selectedOptionBgColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("selectedOptionBgColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setSelectedOptionBgColorAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedOptionFont(value: Font | undefined): this {
        if (this.checkPriority("selectedOptionFont")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.setSelectedOptionFontAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedOptionFontColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("selectedOptionFontColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setSelectedOptionFontColorAttribute(value_casted)
            return this
        }
        return this
    }
    public optionBgColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("optionBgColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setOptionBgColorAttribute(value_casted)
            return this
        }
        return this
    }
    public optionFont(value: Font | undefined): this {
        if (this.checkPriority("optionFont")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.setOptionFontAttribute(value_casted)
            return this
        }
        return this
    }
    public optionFontColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("optionFontColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setOptionFontColorAttribute(value_casted)
            return this
        }
        return this
    }
    public onSelect(value: OnSelectCallback | undefined): this {
        if (this.checkPriority("onSelect")) {
            const value_casted = value as (OnSelectCallback | undefined)
            this.getPeer()?.setOnSelectAttribute(value_casted)
            return this
        }
        return this
    }
    public space(value: Length | undefined): this {
        if (this.checkPriority("space")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setSpaceAttribute(value_casted)
            return this
        }
        return this
    }
    public arrowPosition(value: ArrowPosition | undefined): this {
        if (this.checkPriority("arrowPosition")) {
            const value_casted = value as (ArrowPosition | undefined)
            this.getPeer()?.setArrowPositionAttribute(value_casted)
            return this
        }
        return this
    }
    public optionWidth(value: Dimension | OptionWidthMode | undefined): this {
        if (this.checkPriority("optionWidth")) {
            const value_casted = value as (Dimension | OptionWidthMode | undefined)
            this.getPeer()?.setOptionWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public optionHeight(value: Dimension | undefined): this {
        if (this.checkPriority("optionHeight")) {
            const value_casted = value as (Dimension | undefined)
            this.getPeer()?.setOptionHeightAttribute(value_casted)
            return this
        }
        return this
    }
    public menuBackgroundColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("menuBackgroundColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setMenuBackgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    public menuBackgroundBlurStyle(value: BlurStyle | undefined): this {
        if (this.checkPriority("menuBackgroundBlurStyle")) {
            const value_casted = value as (BlurStyle | undefined)
            this.getPeer()?.setMenuBackgroundBlurStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public controlSize(value: ControlSize | undefined): this {
        if (this.checkPriority("controlSize")) {
            const value_casted = value as (ControlSize | undefined)
            this.getPeer()?.setControlSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public menuItemContentModifier(value: ContentModifier<MenuItemConfiguration> | undefined): this {
        if (this.checkPriority("menuItemContentModifier")) {
            const value_casted = value as (ContentModifier<MenuItemConfiguration> | undefined)
            this.getPeer()?.setMenuItemContentModifierAttribute(value_casted)
            return this
        }
        return this
    }
    public divider(value: DividerOptions | undefined): this {
        if (this.checkPriority("divider")) {
            const value_casted = value as (DividerOptions | undefined)
            this.getPeer()?.setDividerAttribute(value_casted)
            return this
        }
        return this
    }
    public textModifier(value: TextModifier | undefined): this {
        if (this.checkPriority("textModifier")) {
            const value_casted = value as (TextModifier | undefined)
            this.getPeer()?.setTextModifierAttribute(value_casted)
            return this
        }
        return this
    }
    public arrowModifier(value: SymbolGlyphModifier | undefined): this {
        if (this.checkPriority("arrowModifier")) {
            const value_casted = value as (SymbolGlyphModifier | undefined)
            this.getPeer()?.setArrowModifierAttribute(value_casted)
            return this
        }
        return this
    }
    public optionTextModifier(value: TextModifier | undefined): this {
        if (this.checkPriority("optionTextModifier")) {
            const value_casted = value as (TextModifier | undefined)
            this.getPeer()?.setOptionTextModifierAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedOptionTextModifier(value: TextModifier | undefined): this {
        if (this.checkPriority("selectedOptionTextModifier")) {
            const value_casted = value as (TextModifier | undefined)
            this.getPeer()?.setSelectedOptionTextModifierAttribute(value_casted)
            return this
        }
        return this
    }
    public dividerStyle(value: DividerStyleOptions | undefined): this {
        if (this.checkPriority("dividerStyle")) {
            const value_casted = value as (DividerStyleOptions | undefined)
            this.getPeer()?.setDividerStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public avoidance(value: AvoidanceMode | undefined): this {
        if (this.checkPriority("avoidance")) {
            const value_casted = value as (AvoidanceMode | undefined)
            this.getPeer()?.setAvoidanceAttribute(value_casted)
            return this
        }
        return this
    }
    public menuOutline(value: MenuOutlineOptions | undefined): this {
        if (this.checkPriority("menuOutline")) {
            const value_casted = value as (MenuOutlineOptions | undefined)
            this.getPeer()?.setMenuOutlineAttribute(value_casted)
            return this
        }
        return this
    }
    public menuAlign(alignType: MenuAlignType | undefined, offset?: Offset): this {
        if (this.checkPriority("menuAlign")) {
            const alignType_casted = alignType as (MenuAlignType | undefined)
            const offset_casted = offset as (Offset | undefined)
            this.getPeer()?.setMenuAlignAttribute(alignType_casted, offset_casted)
            return this
        }
        return this
    }
    public _onChangeEvent_selected(callback_: ((selected: number | Resource | undefined) => void)): void {
        if (this.checkPriority("_onChangeEvent_selected")) {
            const callback__casted = callback_ as (((selected: number | Resource | undefined) => void))
            this.getPeer()?.set_onChangeEvent_selectedAttribute(callback__casted)
            return
        }
        return
    }
    public _onChangeEvent_value(callback_: ((value: ResourceStr | string | Resource | undefined) => void)): void {
        if (this.checkPriority("_onChangeEvent_value")) {
            const callback__casted = callback_ as (((value: ResourceStr | string | Resource | undefined) => void))
            this.getPeer()?.set_onChangeEvent_valueAttribute(callback__casted)
            return
        }
        return
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
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Select")
// export function Select(
//     options: Array<SelectOption>,
//     @memo
//     content_?: () => void,
// ): SelectAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Select(
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

export class ArkSelectSet extends ArkCommonMethodSet implements SelectAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _selected_flag?: boolean
    _selected0_value?: number | Resource | undefined
    _value_flag?: boolean
    _value0_value?: ResourceStr | string | Resource | undefined
    _font_flag?: boolean
    _font0_value?: Font | undefined
    _fontColor_flag?: boolean
    _fontColor0_value?: ResourceColor | undefined
    _selectedOptionBgColor_flag?: boolean
    _selectedOptionBgColor0_value?: ResourceColor | undefined
    _selectedOptionFont_flag?: boolean
    _selectedOptionFont0_value?: Font | undefined
    _selectedOptionFontColor_flag?: boolean
    _selectedOptionFontColor0_value?: ResourceColor | undefined
    _optionBgColor_flag?: boolean
    _optionBgColor0_value?: ResourceColor | undefined
    _optionFont_flag?: boolean
    _optionFont0_value?: Font | undefined
    _optionFontColor_flag?: boolean
    _optionFontColor0_value?: ResourceColor | undefined
    _onSelect_flag?: boolean
    _onSelect0_value?: OnSelectCallback | undefined
    _space_flag?: boolean
    _space0_value?: Length | undefined
    _arrowPosition_flag?: boolean
    _arrowPosition0_value?: ArrowPosition | undefined
    _optionWidth_flag?: boolean
    _optionWidth0_value?: Dimension | OptionWidthMode | undefined
    _optionHeight_flag?: boolean
    _optionHeight0_value?: Dimension | undefined
    _menuBackgroundColor_flag?: boolean
    _menuBackgroundColor0_value?: ResourceColor | undefined
    _menuBackgroundBlurStyle_flag?: boolean
    _menuBackgroundBlurStyle0_value?: BlurStyle | undefined
    _controlSize_flag?: boolean
    _controlSize0_value?: ControlSize | undefined
    _menuItemContentModifier_flag?: boolean
    _menuItemContentModifier0_value?: ContentModifier<MenuItemConfiguration> | undefined
    _divider_flag?: boolean
    _divider0_value?: DividerOptions | undefined
    _textModifier_flag?: boolean
    _textModifier0_value?: TextModifier | undefined
    _arrowModifier_flag?: boolean
    _arrowModifier0_value?: SymbolGlyphModifier | undefined
    _optionTextModifier_flag?: boolean
    _optionTextModifier0_value?: TextModifier | undefined
    _selectedOptionTextModifier_flag?: boolean
    _selectedOptionTextModifier0_value?: TextModifier | undefined
    _dividerStyle_flag?: boolean
    _dividerStyle0_value?: DividerStyleOptions | undefined
    _avoidance_flag?: boolean
    _avoidance0_value?: AvoidanceMode | undefined
    _menuOutline_flag?: boolean
    _menuOutline0_value?: MenuOutlineOptions | undefined
    _menuAlign_flag?: boolean
    _menuAlign0_value?: MenuAlignType | undefined
    _menuAlign1_value?: Offset | undefined
    __onChangeEvent_selected_flag?: boolean
    __onChangeEvent_selected0_value?: ((selected: number | Resource | undefined) => void)
    __onChangeEvent_value_flag?: boolean
    __onChangeEvent_value0_value?: ((value: ResourceStr | string | Resource | undefined) => void)
    applyModifierPatch(component: SelectAttribute): void {
        if (this._selected_flag)
            component.selected((this._selected0_value as number | Resource | undefined))
        if (this._value_flag)
            component.value((this._value0_value as ResourceStr | string | Resource | undefined))
        if (this._font_flag)
            component.font((this._font0_value as Font | undefined))
        if (this._fontColor_flag)
            component.fontColor((this._fontColor0_value as ResourceColor | undefined))
        if (this._selectedOptionBgColor_flag)
            component.selectedOptionBgColor((this._selectedOptionBgColor0_value as ResourceColor | undefined))
        if (this._selectedOptionFont_flag)
            component.selectedOptionFont((this._selectedOptionFont0_value as Font | undefined))
        if (this._selectedOptionFontColor_flag)
            component.selectedOptionFontColor((this._selectedOptionFontColor0_value as ResourceColor | undefined))
        if (this._optionBgColor_flag)
            component.optionBgColor((this._optionBgColor0_value as ResourceColor | undefined))
        if (this._optionFont_flag)
            component.optionFont((this._optionFont0_value as Font | undefined))
        if (this._optionFontColor_flag)
            component.optionFontColor((this._optionFontColor0_value as ResourceColor | undefined))
        if (this._onSelect_flag)
            component.onSelect((this._onSelect0_value as OnSelectCallback | undefined))
        if (this._space_flag)
            component.space((this._space0_value as Length | undefined))
        if (this._arrowPosition_flag)
            component.arrowPosition((this._arrowPosition0_value as ArrowPosition | undefined))
        if (this._optionWidth_flag)
            component.optionWidth((this._optionWidth0_value as Dimension | OptionWidthMode | undefined))
        if (this._optionHeight_flag)
            component.optionHeight((this._optionHeight0_value as Dimension | undefined))
        if (this._menuBackgroundColor_flag)
            component.menuBackgroundColor((this._menuBackgroundColor0_value as ResourceColor | undefined))
        if (this._menuBackgroundBlurStyle_flag)
            component.menuBackgroundBlurStyle((this._menuBackgroundBlurStyle0_value as BlurStyle | undefined))
        if (this._controlSize_flag)
            component.controlSize((this._controlSize0_value as ControlSize | undefined))
        if (this._menuItemContentModifier_flag)
            component.menuItemContentModifier((this._menuItemContentModifier0_value as ContentModifier<MenuItemConfiguration> | undefined))
        if (this._divider_flag)
            component.divider((this._divider0_value as DividerOptions | undefined))
        if (this._textModifier_flag)
            component.textModifier((this._textModifier0_value as TextModifier | undefined))
        if (this._arrowModifier_flag)
            component.arrowModifier((this._arrowModifier0_value as SymbolGlyphModifier | undefined))
        if (this._optionTextModifier_flag)
            component.optionTextModifier((this._optionTextModifier0_value as TextModifier | undefined))
        if (this._selectedOptionTextModifier_flag)
            component.selectedOptionTextModifier((this._selectedOptionTextModifier0_value as TextModifier | undefined))
        if (this._dividerStyle_flag)
            component.dividerStyle((this._dividerStyle0_value as DividerStyleOptions | undefined))
        if (this._avoidance_flag)
            component.avoidance((this._avoidance0_value as AvoidanceMode | undefined))
        if (this._menuOutline_flag)
            component.menuOutline((this._menuOutline0_value as MenuOutlineOptions | undefined))
        if (this._menuAlign_flag)
            component.menuAlign((this._menuAlign0_value as MenuAlignType | undefined), (this._menuAlign1_value as Offset | undefined))
    }
    public selected(value: number | Resource | undefined): this {
        this._selected_flag = true
        this._selected0_value = value
        return this
    }
    public value(value: ResourceStr | string | Resource | undefined): this {
        this._value_flag = true
        this._value0_value = value
        return this
    }
    public font(value: Font | undefined): this {
        this._font_flag = true
        this._font0_value = value
        return this
    }
    public fontColor(value: ResourceColor | undefined): this {
        this._fontColor_flag = true
        this._fontColor0_value = value
        return this
    }
    public selectedOptionBgColor(value: ResourceColor | undefined): this {
        this._selectedOptionBgColor_flag = true
        this._selectedOptionBgColor0_value = value
        return this
    }
    public selectedOptionFont(value: Font | undefined): this {
        this._selectedOptionFont_flag = true
        this._selectedOptionFont0_value = value
        return this
    }
    public selectedOptionFontColor(value: ResourceColor | undefined): this {
        this._selectedOptionFontColor_flag = true
        this._selectedOptionFontColor0_value = value
        return this
    }
    public optionBgColor(value: ResourceColor | undefined): this {
        this._optionBgColor_flag = true
        this._optionBgColor0_value = value
        return this
    }
    public optionFont(value: Font | undefined): this {
        this._optionFont_flag = true
        this._optionFont0_value = value
        return this
    }
    public optionFontColor(value: ResourceColor | undefined): this {
        this._optionFontColor_flag = true
        this._optionFontColor0_value = value
        return this
    }
    public onSelect(value: OnSelectCallback | undefined): this {
        this._onSelect_flag = true
        this._onSelect0_value = value
        return this
    }
    public space(value: Length | undefined): this {
        this._space_flag = true
        this._space0_value = value
        return this
    }
    public arrowPosition(value: ArrowPosition | undefined): this {
        this._arrowPosition_flag = true
        this._arrowPosition0_value = value
        return this
    }
    public optionWidth(value: Dimension | OptionWidthMode | undefined): this {
        this._optionWidth_flag = true
        this._optionWidth0_value = value
        return this
    }
    public optionHeight(value: Dimension | undefined): this {
        this._optionHeight_flag = true
        this._optionHeight0_value = value
        return this
    }
    public menuBackgroundColor(value: ResourceColor | undefined): this {
        this._menuBackgroundColor_flag = true
        this._menuBackgroundColor0_value = value
        return this
    }
    public menuBackgroundBlurStyle(value: BlurStyle | undefined): this {
        this._menuBackgroundBlurStyle_flag = true
        this._menuBackgroundBlurStyle0_value = value
        return this
    }
    public controlSize(value: ControlSize | undefined): this {
        this._controlSize_flag = true
        this._controlSize0_value = value
        return this
    }
    public menuItemContentModifier(value: ContentModifier<MenuItemConfiguration> | undefined): this {
        this._menuItemContentModifier_flag = true
        this._menuItemContentModifier0_value = value
        return this
    }
    public divider(value: DividerOptions | undefined): this {
        this._divider_flag = true
        this._divider0_value = value
        return this
    }
    public textModifier(value: TextModifier | undefined): this {
        this._textModifier_flag = true
        this._textModifier0_value = value
        return this
    }
    public arrowModifier(value: SymbolGlyphModifier | undefined): this {
        this._arrowModifier_flag = true
        this._arrowModifier0_value = value
        return this
    }
    public optionTextModifier(value: TextModifier | undefined): this {
        this._optionTextModifier_flag = true
        this._optionTextModifier0_value = value
        return this
    }
    public selectedOptionTextModifier(value: TextModifier | undefined): this {
        this._selectedOptionTextModifier_flag = true
        this._selectedOptionTextModifier0_value = value
        return this
    }
    public dividerStyle(value: DividerStyleOptions | undefined): this {
        this._dividerStyle_flag = true
        this._dividerStyle0_value = value
        return this
    }
    public avoidance(value: AvoidanceMode | undefined): this {
        this._avoidance_flag = true
        this._avoidance0_value = value
        return this
    }
    public menuOutline(value: MenuOutlineOptions | undefined): this {
        this._menuOutline_flag = true
        this._menuOutline0_value = value
        return this
    }
    public menuAlign(alignType: MenuAlignType | undefined, offset?: Offset): this {
        this._menuAlign_flag = true
        this._menuAlign0_value = alignType
        this._menuAlign1_value = offset
        return this
    }
    public _onChangeEvent_selected(callback_: ((selected: number | Resource | undefined) => void)): void {
    }
    public _onChangeEvent_value(callback_: ((value: ResourceStr | string | Resource | undefined) => void)): void {
    }
    public attributeModifier(value: AttributeModifier<SelectAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
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
            valueSerializer.writeInt8((0).toChar())
            const value_value_0  = value_value as string
            valueSerializer.writeString(value_value_0)
        }
        else if (RuntimeType.OBJECT == value_value_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_value_1  = value_value as Resource
            Resource_serializer.write(valueSerializer, value_value_1)
        }
        const value_icon  = value.icon
        let value_icon_type : int32 = RuntimeType.UNDEFINED
        value_icon_type = runtimeType(value_icon)
        valueSerializer.writeInt8((value_icon_type).toChar())
        if ((value_icon_type) != (RuntimeType.UNDEFINED)) {
            const value_icon_value  = value_icon!
            let value_icon_value_type : int32 = RuntimeType.UNDEFINED
            value_icon_value_type = runtimeType(value_icon_value)
            if (RuntimeType.STRING == value_icon_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_icon_value_0  = value_icon_value as string
                valueSerializer.writeString(value_icon_value_0)
            }
            else if (RuntimeType.OBJECT == value_icon_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_icon_value_1  = value_icon_value as Resource
                Resource_serializer.write(valueSerializer, value_icon_value_1)
            }
        }
        const value_symbolIcon  = value.symbolIcon
        let value_symbolIcon_type : int32 = RuntimeType.UNDEFINED
        value_symbolIcon_type = runtimeType(value_symbolIcon)
        valueSerializer.writeInt8((value_symbolIcon_type).toChar())
        if ((value_symbolIcon_type) != (RuntimeType.UNDEFINED)) {
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
        if (value_buf_selector == (0).toChar()) {
            value_buf = (valueDeserializer.readString() as string)
        }
        else if (value_buf_selector == (1).toChar()) {
            value_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for value_buf has to be chosen through deserialisation.")
        }
        const value_result : ResourceStr = (value_buf as string | Resource)
        const icon_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let icon_buf : ResourceStr | undefined
        if ((icon_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const icon_buf__selector : int32 = valueDeserializer.readInt8()
            let icon_buf_ : string | Resource | undefined
            if (icon_buf__selector == (0).toChar()) {
                icon_buf_ = (valueDeserializer.readString() as string)
            }
            else if (icon_buf__selector == (1).toChar()) {
                icon_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for icon_buf_ has to be chosen through deserialisation.")
            }
            icon_buf = (icon_buf_ as string | Resource)
        }
        const icon_result : ResourceStr | undefined = icon_buf
        const symbolIcon_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let symbolIcon_buf : SymbolGlyphModifier | undefined
        if ((symbolIcon_buf_runtimeType) != (RuntimeType.UNDEFINED))
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
            valueSerializer.writeInt8((0).toChar())
            const value_value_0  = value_value as string
            valueSerializer.writeString(value_value_0)
        }
        else if (RuntimeType.OBJECT == value_value_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_value_1  = value_value as Resource
            Resource_serializer.write(valueSerializer, value_value_1)
        }
        const value_icon  = value.icon
        let value_icon_type : int32 = RuntimeType.UNDEFINED
        value_icon_type = runtimeType(value_icon)
        valueSerializer.writeInt8((value_icon_type).toChar())
        if ((value_icon_type) != (RuntimeType.UNDEFINED)) {
            const value_icon_value  = value_icon!
            let value_icon_value_type : int32 = RuntimeType.UNDEFINED
            value_icon_value_type = runtimeType(value_icon_value)
            if (RuntimeType.STRING == value_icon_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_icon_value_0  = value_icon_value as string
                valueSerializer.writeString(value_icon_value_0)
            }
            else if (RuntimeType.OBJECT == value_icon_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_icon_value_1  = value_icon_value as Resource
                Resource_serializer.write(valueSerializer, value_icon_value_1)
            }
        }
        const value_symbolIcon  = value.symbolIcon
        let value_symbolIcon_type : int32 = RuntimeType.UNDEFINED
        value_symbolIcon_type = runtimeType(value_symbolIcon)
        valueSerializer.writeInt8((value_symbolIcon_type).toChar())
        if ((value_symbolIcon_type) != (RuntimeType.UNDEFINED)) {
            const value_symbolIcon_value  = value_symbolIcon!
            SymbolGlyphModifier_serializer.write(valueSerializer, value_symbolIcon_value)
        }
    }
    public static read(buffer: DeserializerBase): SelectOption {
        let valueDeserializer : DeserializerBase = buffer
        const value_buf_selector : int32 = valueDeserializer.readInt8()
        let value_buf : string | Resource | undefined
        if (value_buf_selector == (0).toChar()) {
            value_buf = (valueDeserializer.readString() as string)
        }
        else if (value_buf_selector == (1).toChar()) {
            value_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for value_buf has to be chosen through deserialisation.")
        }
        const value_result : ResourceStr = (value_buf as string | Resource)
        const icon_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let icon_buf : ResourceStr | undefined
        if ((icon_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const icon_buf__selector : int32 = valueDeserializer.readInt8()
            let icon_buf_ : string | Resource | undefined
            if (icon_buf__selector == (0).toChar()) {
                icon_buf_ = (valueDeserializer.readString() as string)
            }
            else if (icon_buf__selector == (1).toChar()) {
                icon_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for icon_buf_ has to be chosen through deserialisation.")
            }
            icon_buf = (icon_buf_ as string | Resource)
        }
        const icon_result : ResourceStr | undefined = icon_buf
        const symbolIcon_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let symbolIcon_buf : SymbolGlyphModifier | undefined
        if ((symbolIcon_buf_runtimeType) != (RuntimeType.UNDEFINED))
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
        valueSerializer.writeInt8((value_width_type).toChar())
        if ((value_width_type) != (RuntimeType.UNDEFINED)) {
            const value_width_value  = value_width!
            let value_width_value_type : int32 = RuntimeType.UNDEFINED
            value_width_value_type = runtimeType(value_width_value)
            if ((RuntimeType.STRING == value_width_value_type) || (RuntimeType.NUMBER == value_width_value_type) || (RuntimeType.OBJECT == value_width_value_type)) {
                valueSerializer.writeInt8((0).toChar())
                const value_width_value_0  = value_width_value as Dimension
                let value_width_value_0_type : int32 = RuntimeType.UNDEFINED
                value_width_value_0_type = runtimeType(value_width_value_0)
                if (RuntimeType.STRING == value_width_value_0_type) {
                    valueSerializer.writeInt8((0).toChar())
                    const value_width_value_0_0  = value_width_value_0 as string
                    valueSerializer.writeString(value_width_value_0_0)
                }
                else if (RuntimeType.NUMBER == value_width_value_0_type) {
                    valueSerializer.writeInt8((1).toChar())
                    const value_width_value_0_1  = value_width_value_0 as number
                    valueSerializer.writeNumber(value_width_value_0_1)
                }
                else if (RuntimeType.OBJECT == value_width_value_0_type) {
                    valueSerializer.writeInt8((2).toChar())
                    const value_width_value_0_2  = value_width_value_0 as Resource
                    Resource_serializer.write(valueSerializer, value_width_value_0_2)
                }
            }
            else if (TypeChecker.isEdgeOutlineWidths(value_width_value, false, false, false, false)) {
                valueSerializer.writeInt8((1).toChar())
                const value_width_value_1  = value_width_value as EdgeOutlineWidths
                EdgeOutlineWidths_serializer.write(valueSerializer, value_width_value_1)
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
            if ((TypeChecker.isColor(value_color_value)) || (RuntimeType.NUMBER == value_color_value_type) || (RuntimeType.STRING == value_color_value_type) || (RuntimeType.OBJECT == value_color_value_type)) {
                valueSerializer.writeInt8((0).toChar())
                const value_color_value_0  = value_color_value as ResourceColor
                let value_color_value_0_type : int32 = RuntimeType.UNDEFINED
                value_color_value_0_type = runtimeType(value_color_value_0)
                if (TypeChecker.isColor(value_color_value_0)) {
                    valueSerializer.writeInt8((0).toChar())
                    const value_color_value_0_0  = value_color_value_0 as Color
                    valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_color_value_0_0))
                }
                else if (RuntimeType.NUMBER == value_color_value_0_type) {
                    valueSerializer.writeInt8((1).toChar())
                    const value_color_value_0_1  = value_color_value_0 as number
                    valueSerializer.writeNumber(value_color_value_0_1)
                }
                else if (RuntimeType.STRING == value_color_value_0_type) {
                    valueSerializer.writeInt8((2).toChar())
                    const value_color_value_0_2  = value_color_value_0 as string
                    valueSerializer.writeString(value_color_value_0_2)
                }
                else if (RuntimeType.OBJECT == value_color_value_0_type) {
                    valueSerializer.writeInt8((3).toChar())
                    const value_color_value_0_3  = value_color_value_0 as Resource
                    Resource_serializer.write(valueSerializer, value_color_value_0_3)
                }
            }
            else if (TypeChecker.isEdgeColors(value_color_value, false, false, false, false)) {
                valueSerializer.writeInt8((1).toChar())
                const value_color_value_1  = value_color_value as EdgeColors
                EdgeColors_serializer.write(valueSerializer, value_color_value_1)
            }
        }
    }
    public static read(buffer: DeserializerBase): MenuOutlineOptions {
        let valueDeserializer : DeserializerBase = buffer
        const width_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let width_buf : Dimension | EdgeOutlineWidths | undefined
        if ((width_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const width_buf__selector : int32 = valueDeserializer.readInt8()
            let width_buf_ : Dimension | EdgeOutlineWidths | undefined
            if (width_buf__selector == (0).toChar()) {
                const width_buf__u_selector : int32 = valueDeserializer.readInt8()
                let width_buf__u : string | number | Resource | undefined
                if (width_buf__u_selector == (0).toChar()) {
                    width_buf__u = (valueDeserializer.readString() as string)
                }
                else if (width_buf__u_selector == (1).toChar()) {
                    width_buf__u = (valueDeserializer.readNumber() as number)
                }
                else if (width_buf__u_selector == (2).toChar()) {
                    width_buf__u = Resource_serializer.read(valueDeserializer)
                }
                else {
                    throw new Error("One of the branches for width_buf__u has to be chosen through deserialisation.")
                }
                width_buf_ = (width_buf__u as string | number | Resource)
            }
            else if (width_buf__selector == (1).toChar()) {
                width_buf_ = EdgeOutlineWidths_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for width_buf_ has to be chosen through deserialisation.")
            }
            width_buf = (width_buf_ as Dimension | EdgeOutlineWidths)
        }
        const width_result : Dimension | EdgeOutlineWidths | undefined = width_buf
        const color_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let color_buf : ResourceColor | EdgeColors | undefined
        if ((color_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const color_buf__selector : int32 = valueDeserializer.readInt8()
            let color_buf_ : ResourceColor | EdgeColors | undefined
            if (color_buf__selector == (0).toChar()) {
                const color_buf__u_selector : int32 = valueDeserializer.readInt8()
                let color_buf__u : Color | number | string | Resource | undefined
                if (color_buf__u_selector == (0).toChar()) {
                    color_buf__u = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
                }
                else if (color_buf__u_selector == (1).toChar()) {
                    color_buf__u = (valueDeserializer.readNumber() as number)
                }
                else if (color_buf__u_selector == (2).toChar()) {
                    color_buf__u = (valueDeserializer.readString() as string)
                }
                else if (color_buf__u_selector == (3).toChar()) {
                    color_buf__u = Resource_serializer.read(valueDeserializer)
                }
                else {
                    throw new Error("One of the branches for color_buf__u has to be chosen through deserialisation.")
                }
                color_buf_ = (color_buf__u as Color | number | string | Resource)
            }
            else if (color_buf__selector == (1).toChar()) {
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

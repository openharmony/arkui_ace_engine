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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { Resource_serializer } from "./../framework/resource"
import { Bindable_Number_serializer, Bindable_Global_Resource_Resource_serializer, Bindable_String_serializer, ArkCommonMethodPeer, CommonMethod, Bindable, BlurStyle, CommonConfiguration, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { Font_serializer, DividerStyleOptions_serializer, Offset_serializer, ResourceStr, Font, ResourceColor, Length, Dimension, DividerStyleOptions, Offset, EdgeOutlineWidths, EdgeColors, EdgeOutlineWidths_serializer, EdgeColors_serializer } from "./units"
import { DividerOptions } from "./textPicker"
import { TextModifier_serializer } from "./../TextModifier"
import { SymbolGlyphModifier_serializer } from "./../SymbolGlyphModifier"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { Resource } from "global.resource"
import { Color, OptionWidthMode } from "./enums"
import { ControlSize } from "./button"
import { ContentModifier, extractors, AttributeModifier, hookSelectContentModifier, hookSelectSetDividerMethod, hookSelectAttributeModifier, AttributeUpdater } from "#handwritten"
import { TextModifier } from "arkui.TextModifier"
import { SymbolGlyphModifier } from "arkui.SymbolGlyphModifier"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { SelectModifier } from "./../SelectModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkSelectPeer extends ArkCommonMethodPeer {
    attributeSet?: SelectModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkSelectPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Select_construct(peerId, flags)
        const _peer  = new ArkSelectPeer(_peerPtr, peerId, 'Select', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setSelectOptionsAttribute(options: Array<SelectOption>): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((options.length).toInt())
        for (let optionsCounterI = 0; optionsCounterI < options.length; optionsCounterI++) {
            const optionsTmpElement : SelectOption = options[optionsCounterI]
            SelectOption_serializer.write(thisSerializer, optionsTmpElement)
        }
        ArkUIGeneratedNativeModule._SelectInterface_setSelectOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedAttribute(value: number | Resource | Bindable<number> | Bindable<Resource> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Bindable<number>) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as Bindable<number>
                Bindable_Number_serializer.write(thisSerializer, valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Bindable<Resource>) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as Bindable<Resource>
                Bindable_Global_Resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setSelected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setValueAttribute(value: ResourceStr | Bindable<string> | Bindable<Resource> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof ResourceStr) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as ResourceStr
                if (valueTmpValueForIdx0 instanceof string) {
                    thisSerializer.writeInt8((0).toByte())
                    const valueTmpValueForIdx0ForIdx0  = valueTmpValueForIdx0 as string
                    thisSerializer.writeString(valueTmpValueForIdx0ForIdx0)
                } else if (valueTmpValueForIdx0 instanceof Resource) {
                    thisSerializer.writeInt8((1).toByte())
                    const valueTmpValueForIdx0ForIdx1  = valueTmpValueForIdx0 as Resource
                    Resource_serializer.write(thisSerializer, valueTmpValueForIdx0ForIdx1)
                }
            } else if (valueTmpValue instanceof Bindable<string>) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as Bindable<string>
                Bindable_String_serializer.write(thisSerializer, valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Bindable<Resource>) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as Bindable<Resource>
                Bindable_Global_Resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setValue(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontAttribute(value: Font | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            Font_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedOptionBgColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setSelectedOptionBgColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedOptionFontAttribute(value: Font | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            Font_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setSelectedOptionFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedOptionFontColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setSelectedOptionFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOptionBgColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setOptionBgColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOptionFontAttribute(value: Font | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            Font_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setOptionFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOptionFontColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setOptionFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSelectAttribute(value: OnSelectCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setOnSelect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSpaceAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setSpace(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setArrowPositionAttribute(value: ArrowPosition | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as ArrowPosition)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setArrowPosition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOptionWidthAttribute(value: Dimension | OptionWidthMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Dimension) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Dimension
                if (valueTmpValueForIdx0 instanceof string) {
                    thisSerializer.writeInt8((0).toByte())
                    const valueTmpValueForIdx0ForIdx0  = valueTmpValueForIdx0 as string
                    thisSerializer.writeString(valueTmpValueForIdx0ForIdx0)
                } else if (valueTmpValueForIdx0 instanceof number) {
                    thisSerializer.writeInt8((1).toByte())
                    const valueTmpValueForIdx0ForIdx1  = valueTmpValueForIdx0 as number
                    thisSerializer.writeNumber(valueTmpValueForIdx0ForIdx1)
                } else if (valueTmpValueForIdx0 instanceof Resource) {
                    thisSerializer.writeInt8((2).toByte())
                    const valueTmpValueForIdx0ForIdx2  = valueTmpValueForIdx0 as Resource
                    Resource_serializer.write(thisSerializer, valueTmpValueForIdx0ForIdx2)
                }
            } else if (valueTmpValue instanceof OptionWidthMode) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as OptionWidthMode
                thisSerializer.writeInt32(valueTmpValueForIdx1.getOrdinal())
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setOptionWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOptionHeightAttribute(value: Dimension | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setOptionHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMenuBackgroundColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setMenuBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMenuBackgroundBlurStyleAttribute(value: BlurStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as BlurStyle)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setMenuBackgroundBlurStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setControlSizeAttribute(value: ControlSize | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as ControlSize)
            thisSerializer.writeInt32(valueTmpValue.getOrdinal())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setControlSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextModifierAttribute(value: TextModifier | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            TextModifier_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setTextModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setArrowModifierAttribute(value: SymbolGlyphModifier | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            SymbolGlyphModifier_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setArrowModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOptionTextModifierAttribute(value: TextModifier | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            TextModifier_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setOptionTextModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedOptionTextModifierAttribute(value: TextModifier | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            TextModifier_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setSelectedOptionTextModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDividerStyleAttribute(value: DividerStyleOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            DividerStyleOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setDividerStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAvoidanceAttribute(value: AvoidanceMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as AvoidanceMode)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setAvoidance(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMenuOutlineAttribute(value: MenuOutlineOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            MenuOutlineOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setMenuOutline(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBackgroundColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMenuAlignAttribute(alignType: MenuAlignType | undefined, offset?: Offset): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (alignType !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const alignTypeTmpValue  = (alignType as MenuAlignType)
            thisSerializer.writeInt32(alignTypeTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (offset !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const offsetTmpValue  = offset!
            Offset_serializer.write(thisSerializer, offsetTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setMenuAlign(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    setSelectOptions(options: Array<SelectOption>): this {
        throw new Error("Unimplemented method setSelectOptions")
    }
    selected(value: number | Resource | Bindable<number> | Bindable<Resource> | undefined): this {
        throw new Error("Unimplemented method selected")
    }
    value(value: ResourceStr | Bindable<string> | Bindable<Resource> | undefined): this {
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
    divider(value: DividerOptions | null | undefined): this {
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
    backgroundColor(value: ResourceColor | undefined): this
    menuAlign(alignType: MenuAlignType | undefined, offset?: Offset): this {
        throw new Error("Unimplemented method menuAlign")
    }
    attributeModifier(value: AttributeModifier<SelectAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkSelectStyle extends ArkCommonMethodStyle implements SelectAttribute {
    selected_value?: number | Resource | Bindable<number> | Bindable<Resource> | undefined
    value_value?: ResourceStr | Bindable<string> | Bindable<Resource> | undefined
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
    divider_value?: DividerOptions | null | undefined
    textModifier_value?: TextModifier | undefined
    arrowModifier_value?: SymbolGlyphModifier | undefined
    optionTextModifier_value?: TextModifier | undefined
    selectedOptionTextModifier_value?: TextModifier | undefined
    dividerStyle_value?: DividerStyleOptions | undefined
    avoidance_value?: AvoidanceMode | undefined
    menuOutline_value?: MenuOutlineOptions | undefined
    attributeModifier_value?: AttributeModifier<SelectAttribute> | AttributeModifier<CommonMethod> | undefined
    backgroundColor_value?: ResourceColor | undefined
    setSelectOptions(options: Array<SelectOption>): this {
        return this
    }
    selected(value: number | Resource | Bindable<number> | Bindable<Resource> | undefined): this {
        return this
    }
    value(value: ResourceStr | Bindable<string> | Bindable<Resource> | undefined): this {
        return this
    }
    font(value: Font | undefined): this {
        return this
    }
    fontColor(value: ResourceColor | undefined): this {
        return this
    }
    selectedOptionBgColor(value: ResourceColor | undefined): this {
        return this
    }
    selectedOptionFont(value: Font | undefined): this {
        return this
    }
    selectedOptionFontColor(value: ResourceColor | undefined): this {
        return this
    }
    optionBgColor(value: ResourceColor | undefined): this {
        return this
    }
    optionFont(value: Font | undefined): this {
        return this
    }
    optionFontColor(value: ResourceColor | undefined): this {
        return this
    }
    onSelect(value: OnSelectCallback | undefined): this {
        return this
    }
    space(value: Length | undefined): this {
        return this
    }
    arrowPosition(value: ArrowPosition | undefined): this {
        return this
    }
    optionWidth(value: Dimension | OptionWidthMode | undefined): this {
        return this
    }
    optionHeight(value: Dimension | undefined): this {
        return this
    }
    menuBackgroundColor(value: ResourceColor | undefined): this {
        return this
    }
    menuBackgroundBlurStyle(value: BlurStyle | undefined): this {
        return this
    }
    controlSize(value: ControlSize | undefined): this {
        return this
    }
    menuItemContentModifier(value: ContentModifier<MenuItemConfiguration> | undefined): this {
        return this
    }
    divider(value: DividerOptions | null | undefined): this {
        return this
    }
    textModifier(value: TextModifier | undefined): this {
        return this
    }
    arrowModifier(value: SymbolGlyphModifier | undefined): this {
        return this
    }
    optionTextModifier(value: TextModifier | undefined): this {
        return this
    }
    selectedOptionTextModifier(value: TextModifier | undefined): this {
        return this
    }
    dividerStyle(value: DividerStyleOptions | undefined): this {
        return this
    }
    avoidance(value: AvoidanceMode | undefined): this {
        return this
    }
    menuOutline(value: MenuOutlineOptions | undefined): this {
        return this
    }
    backgroundColor(value: ResourceColor | undefined): this {
        return this
    }
    menuAlign(alignType: MenuAlignType | undefined, offset?: Offset): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<SelectAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
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
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
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
    public selected(value: number | Resource | Bindable<number> | Bindable<Resource> | undefined): this {
        if (this.checkPriority("selected")) {
            const value_casted = value as (number | Resource | Bindable<number> | Bindable<Resource> | undefined)
            this.getPeer()?.setSelectedAttribute(value_casted)
            return this
        }
        return this
    }
    public value(value: ResourceStr | Bindable<string> | Bindable<Resource> | undefined): this {
        if (this.checkPriority("value")) {
            const value_casted = value as (ResourceStr | Bindable<string> | Bindable<Resource> | undefined)
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
            hookSelectContentModifier(this, value)
        }
        return this
    }
    public divider(value: DividerOptions | null | undefined): this {
        if (this.checkPriority("divider")) {
            hookSelectSetDividerMethod(this, value)
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
    public backgroundColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("backgroundColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setBackgroundColorAttribute(value_casted)
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
    public attributeModifier(value: AttributeModifier<SelectAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        hookSelectAttributeModifier(this, value);
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

@memo
export function SelectImpl(
    @memo
    style: ((attributes: SelectAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkSelectComponent>((): ArkSelectComponent => {
        return new ArkSelectComponent()
    })
    NodeAttach<ArkSelectPeer>((): ArkSelectPeer => ArkSelectPeer.create(receiver), (peer: ArkSelectPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

export class MenuItemConfiguration_serializer {
    public static write(buffer: SerializerBase, value: MenuItemConfiguration): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForEnabled  = value.enabled
        valueSerializer.writeBoolean(valueHolderForEnabled)
        const valueHolderForContentModifier  = value.contentModifier
        valueSerializer.holdAndWriteObject(valueHolderForContentModifier)
        const valueHolderForValue  = value.value
        if (valueHolderForValue instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForValueForIdx0  = valueHolderForValue as string
            valueSerializer.writeString(valueHolderForValueForIdx0)
        } else if (valueHolderForValue instanceof Resource) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForValueForIdx1  = valueHolderForValue as Resource
            Resource_serializer.write(valueSerializer, valueHolderForValueForIdx1)
        }
        const valueHolderForIcon  = value.icon
        if (valueHolderForIcon !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIconTmpValue  = valueHolderForIcon!
            if (valueHolderForIconTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForIconTmpValueForIdx0  = valueHolderForIconTmpValue as string
                valueSerializer.writeString(valueHolderForIconTmpValueForIdx0)
            } else if (valueHolderForIconTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForIconTmpValueForIdx1  = valueHolderForIconTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForIconTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSymbolIcon  = value.symbolIcon
        if (valueHolderForSymbolIcon !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSymbolIconTmpValue  = valueHolderForSymbolIcon!
            SymbolGlyphModifier_serializer.write(valueSerializer, valueHolderForSymbolIconTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSelected  = value.selected
        valueSerializer.writeBoolean(valueHolderForSelected)
        const valueHolderForIndex  = value.index
        valueSerializer.writeNumber(valueHolderForIndex)
    }
    public static read(buffer: DeserializerBase): MenuItemConfiguration {
        let valueDeserializer : DeserializerBase = buffer
        const enabledTmpResult : boolean = valueDeserializer.readBoolean()
        const contentModifierTmpResult : ContentModifier<MenuItemConfiguration> = (valueDeserializer.readObject() as ContentModifier<MenuItemConfiguration>)
        const valueTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let valueTmpBuf : string | Resource | undefined
        if (valueTmpBufUnionSelector == (0).toChar()) {
            valueTmpBuf = (valueDeserializer.readString() as string)
        } else if (valueTmpBufUnionSelector == (1).toChar()) {
            valueTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for valueTmpBuf has to be chosen through deserialisation.")
        }
        const valueTmpResult : ResourceStr = (valueTmpBuf as string | Resource)
        const iconTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let iconTmpBuf : ResourceStr | undefined = undefined
        if ((iconTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const iconTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let iconTmpBuf_ : string | Resource | undefined
            if (iconTmpBuf_UnionSelector == (0).toChar()) {
                iconTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (iconTmpBuf_UnionSelector == (1).toChar()) {
                iconTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for iconTmpBuf_ has to be chosen through deserialisation.")
            }
            iconTmpBuf = (iconTmpBuf_ as string | Resource)
        }
        const iconTmpResult : ResourceStr | undefined = iconTmpBuf
        const symbolIconTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let symbolIconTmpBuf : SymbolGlyphModifier | undefined = undefined
        if ((symbolIconTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            symbolIconTmpBuf = (SymbolGlyphModifier_serializer.read(valueDeserializer) as SymbolGlyphModifier)
        }
        const symbolIconTmpResult : SymbolGlyphModifier | undefined = symbolIconTmpBuf
        const selectedTmpResult : boolean = valueDeserializer.readBoolean()
        const indexTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : MenuItemConfiguration = ({enabled: enabledTmpResult, contentModifier: contentModifierTmpResult, value: valueTmpResult, icon: iconTmpResult, symbolIcon: symbolIconTmpResult, selected: selectedTmpResult, index: indexTmpResult} as MenuItemConfiguration)
        return value
    }
}
export class SelectOption_serializer {
    public static write(buffer: SerializerBase, value: SelectOption): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForValue  = value.value
        if (valueHolderForValue instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForValueForIdx0  = valueHolderForValue as string
            valueSerializer.writeString(valueHolderForValueForIdx0)
        } else if (valueHolderForValue instanceof Resource) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForValueForIdx1  = valueHolderForValue as Resource
            Resource_serializer.write(valueSerializer, valueHolderForValueForIdx1)
        }
        const valueHolderForIcon  = value.icon
        if (valueHolderForIcon !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIconTmpValue  = valueHolderForIcon!
            if (valueHolderForIconTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForIconTmpValueForIdx0  = valueHolderForIconTmpValue as string
                valueSerializer.writeString(valueHolderForIconTmpValueForIdx0)
            } else if (valueHolderForIconTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForIconTmpValueForIdx1  = valueHolderForIconTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForIconTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSymbolIcon  = value.symbolIcon
        if (valueHolderForSymbolIcon !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSymbolIconTmpValue  = valueHolderForSymbolIcon!
            SymbolGlyphModifier_serializer.write(valueSerializer, valueHolderForSymbolIconTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): SelectOption {
        let valueDeserializer : DeserializerBase = buffer
        const valueTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let valueTmpBuf : string | Resource | undefined
        if (valueTmpBufUnionSelector == (0).toChar()) {
            valueTmpBuf = (valueDeserializer.readString() as string)
        } else if (valueTmpBufUnionSelector == (1).toChar()) {
            valueTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for valueTmpBuf has to be chosen through deserialisation.")
        }
        const valueTmpResult : ResourceStr = (valueTmpBuf as string | Resource)
        const iconTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let iconTmpBuf : ResourceStr | undefined = undefined
        if ((iconTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const iconTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let iconTmpBuf_ : string | Resource | undefined
            if (iconTmpBuf_UnionSelector == (0).toChar()) {
                iconTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (iconTmpBuf_UnionSelector == (1).toChar()) {
                iconTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for iconTmpBuf_ has to be chosen through deserialisation.")
            }
            iconTmpBuf = (iconTmpBuf_ as string | Resource)
        }
        const iconTmpResult : ResourceStr | undefined = iconTmpBuf
        const symbolIconTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let symbolIconTmpBuf : SymbolGlyphModifier | undefined = undefined
        if ((symbolIconTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            symbolIconTmpBuf = (SymbolGlyphModifier_serializer.read(valueDeserializer) as SymbolGlyphModifier)
        }
        const symbolIconTmpResult : SymbolGlyphModifier | undefined = symbolIconTmpBuf
        let value : SelectOption = ({value: valueTmpResult, icon: iconTmpResult, symbolIcon: symbolIconTmpResult} as SelectOption)
        return value
    }
}
export class MenuOutlineOptions_serializer {
    public static write(buffer: SerializerBase, value: MenuOutlineOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForWidth  = value.width
        if (valueHolderForWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWidthTmpValue  = valueHolderForWidth!
            if (valueHolderForWidthTmpValue instanceof Dimension) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForWidthTmpValueForIdx0  = valueHolderForWidthTmpValue as Dimension
                if (valueHolderForWidthTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForWidthTmpValueForIdx0ForIdx0  = valueHolderForWidthTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForWidthTmpValueForIdx0ForIdx0)
                } else if (valueHolderForWidthTmpValueForIdx0 instanceof number) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForWidthTmpValueForIdx0ForIdx1  = valueHolderForWidthTmpValueForIdx0 as number
                    valueSerializer.writeNumber(valueHolderForWidthTmpValueForIdx0ForIdx1)
                } else if (valueHolderForWidthTmpValueForIdx0 instanceof Resource) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForWidthTmpValueForIdx0ForIdx2  = valueHolderForWidthTmpValueForIdx0 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForWidthTmpValueForIdx0ForIdx2)
                }
            } else if (valueHolderForWidthTmpValue instanceof EdgeOutlineWidths) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForWidthTmpValueForIdx1  = valueHolderForWidthTmpValue as EdgeOutlineWidths
                EdgeOutlineWidths_serializer.write(valueSerializer, valueHolderForWidthTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForColor  = value.color
        if (valueHolderForColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColorTmpValue  = valueHolderForColor!
            if (valueHolderForColorTmpValue instanceof ResourceColor) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForColorTmpValueForIdx0  = valueHolderForColorTmpValue as ResourceColor
                if (valueHolderForColorTmpValueForIdx0 instanceof Color) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForColorTmpValueForIdx0ForIdx0  = valueHolderForColorTmpValueForIdx0 as Color
                    valueSerializer.writeInt32(valueHolderForColorTmpValueForIdx0ForIdx0.getOrdinal())
                } else if (valueHolderForColorTmpValueForIdx0 instanceof number) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForColorTmpValueForIdx0ForIdx1  = valueHolderForColorTmpValueForIdx0 as number
                    valueSerializer.writeNumber(valueHolderForColorTmpValueForIdx0ForIdx1)
                } else if (valueHolderForColorTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForColorTmpValueForIdx0ForIdx2  = valueHolderForColorTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForColorTmpValueForIdx0ForIdx2)
                } else if (valueHolderForColorTmpValueForIdx0 instanceof Resource) {
                    valueSerializer.writeInt8((3).toByte())
                    const valueHolderForColorTmpValueForIdx0ForIdx3  = valueHolderForColorTmpValueForIdx0 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForColorTmpValueForIdx0ForIdx3)
                }
            } else if (valueHolderForColorTmpValue instanceof EdgeColors) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForColorTmpValueForIdx1  = valueHolderForColorTmpValue as EdgeColors
                EdgeColors_serializer.write(valueSerializer, valueHolderForColorTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): MenuOutlineOptions {
        let valueDeserializer : DeserializerBase = buffer
        const widthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let widthTmpBuf : Dimension | EdgeOutlineWidths | undefined = undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const widthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let widthTmpBuf_ : Dimension | EdgeOutlineWidths | undefined
            if (widthTmpBuf_UnionSelector == (0).toChar()) {
                const widthTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let widthTmpBuf_BufU : string | number | Resource | undefined
                if (widthTmpBuf_BufUUnionSelector == (0).toChar()) {
                    widthTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (widthTmpBuf_BufUUnionSelector == (1).toChar()) {
                    widthTmpBuf_BufU = (valueDeserializer.readNumber() as number)
                } else if (widthTmpBuf_BufUUnionSelector == (2).toChar()) {
                    widthTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for widthTmpBuf_BufU has to be chosen through deserialisation.")
                }
                widthTmpBuf_ = (widthTmpBuf_BufU as string | number | Resource)
            } else if (widthTmpBuf_UnionSelector == (1).toChar()) {
                widthTmpBuf_ = EdgeOutlineWidths_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for widthTmpBuf_ has to be chosen through deserialisation.")
            }
            widthTmpBuf = (widthTmpBuf_ as Dimension | EdgeOutlineWidths)
        }
        const widthTmpResult : Dimension | EdgeOutlineWidths | undefined = widthTmpBuf
        const colorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let colorTmpBuf : ResourceColor | EdgeColors | undefined = undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const colorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let colorTmpBuf_ : ResourceColor | EdgeColors | undefined
            if (colorTmpBuf_UnionSelector == (0).toChar()) {
                const colorTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let colorTmpBuf_BufU : Color | number | string | Resource | undefined
                if (colorTmpBuf_BufUUnionSelector == (0).toChar()) {
                    colorTmpBuf_BufU = Color.values()[valueDeserializer.readInt32()]
                } else if (colorTmpBuf_BufUUnionSelector == (1).toChar()) {
                    colorTmpBuf_BufU = (valueDeserializer.readNumber() as number)
                } else if (colorTmpBuf_BufUUnionSelector == (2).toChar()) {
                    colorTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (colorTmpBuf_BufUUnionSelector == (3).toChar()) {
                    colorTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for colorTmpBuf_BufU has to be chosen through deserialisation.")
                }
                colorTmpBuf_ = (colorTmpBuf_BufU as Color | number | string | Resource)
            } else if (colorTmpBuf_UnionSelector == (1).toChar()) {
                colorTmpBuf_ = EdgeColors_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for colorTmpBuf_ has to be chosen through deserialisation.")
            }
            colorTmpBuf = (colorTmpBuf_ as ResourceColor | EdgeColors)
        }
        const colorTmpResult : ResourceColor | EdgeColors | undefined = colorTmpBuf
        let value : MenuOutlineOptions = ({width: widthTmpResult, color: colorTmpResult} as MenuOutlineOptions)
        return value
    }
}

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
import { Resource_serializer, Resource } from "./../generated/resource"
import { Bindable_Number_serializer, Bindable_Global_Resource_Resource_serializer, Bindable_String_serializer, ArkCommonMethodPeer, CommonMethod, Bindable, BlurStyle, CommonConfiguration, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier } from "./common"
import { Font_serializer, DividerStyleOptions_serializer, Offset_serializer, ResourceStr, Font, ResourceColor, Length, Dimension, DividerStyleOptions, Offset, EdgeOutlineWidths, EdgeColors, EdgeOutlineWidths_serializer, EdgeColors_serializer } from "./units"
import { DividerOptions_serializer, DividerOptions } from "./textPicker"
import { TextModifier_serializer, TextModifier } from "./../generated/arkui.TextModifier"
import { SymbolGlyphModifier_serializer, SymbolGlyphModifier } from "./../generated/arkui.SymbolGlyphModifier"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { Color, OptionWidthMode } from "./enums"
import { ControlSize } from "./button"
import { ContentModifier, AttributeModifier, hookSelectContentModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
export class ArkSelectPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
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
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Bindable<number>) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as Bindable<number>
                Bindable_Number_serializer.write(thisSerializer, valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Bindable<Resource>) {
                thisSerializer.writeInt8((3).toChar())
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
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as ResourceStr
                if (valueTmpValueForIdx0 instanceof string) {
                    thisSerializer.writeInt8((0).toChar())
                    const valueTmpValueForIdx0ForIdx0  = valueTmpValueForIdx0 as string
                    thisSerializer.writeString(valueTmpValueForIdx0ForIdx0)
                } else if (valueTmpValueForIdx0 instanceof Resource) {
                    thisSerializer.writeInt8((1).toChar())
                    const valueTmpValueForIdx0ForIdx1  = valueTmpValueForIdx0 as Resource
                    Resource_serializer.write(thisSerializer, valueTmpValueForIdx0ForIdx1)
                }
            } else if (valueTmpValue instanceof Bindable<string>) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as Bindable<string>
                Bindable_String_serializer.write(thisSerializer, valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Bindable<Resource>) {
                thisSerializer.writeInt8((2).toChar())
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
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueTmpValueForIdx0))
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toChar())
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
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueTmpValueForIdx0))
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toChar())
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
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueTmpValueForIdx0))
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toChar())
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
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueTmpValueForIdx0))
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toChar())
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
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueTmpValueForIdx0))
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toChar())
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
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
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
            thisSerializer.writeInt32(TypeChecker.ArrowPosition_ToNumeric(valueTmpValue))
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
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as Dimension
                if (valueTmpValueForIdx0 instanceof string) {
                    thisSerializer.writeInt8((0).toChar())
                    const valueTmpValueForIdx0ForIdx0  = valueTmpValueForIdx0 as string
                    thisSerializer.writeString(valueTmpValueForIdx0ForIdx0)
                } else if (valueTmpValueForIdx0 instanceof number) {
                    thisSerializer.writeInt8((1).toChar())
                    const valueTmpValueForIdx0ForIdx1  = valueTmpValueForIdx0 as number
                    thisSerializer.writeNumber(valueTmpValueForIdx0ForIdx1)
                } else if (valueTmpValueForIdx0 instanceof Resource) {
                    thisSerializer.writeInt8((2).toChar())
                    const valueTmpValueForIdx0ForIdx2  = valueTmpValueForIdx0 as Resource
                    Resource_serializer.write(thisSerializer, valueTmpValueForIdx0ForIdx2)
                }
            } else if (valueTmpValue instanceof OptionWidthMode) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as OptionWidthMode
                thisSerializer.writeInt32(TypeChecker.OptionWidthMode_ToNumeric(valueTmpValueForIdx1))
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
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
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
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueTmpValueForIdx0))
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toChar())
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
            thisSerializer.writeInt32(TypeChecker.BlurStyle_ToNumeric(valueTmpValue))
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
            thisSerializer.writeInt32(TypeChecker.ControlSize_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setControlSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDividerAttribute(value: DividerOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            DividerOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setDivider(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
            thisSerializer.writeInt32(TypeChecker.AvoidanceMode_ToNumeric(valueTmpValue))
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
    setMenuAlignAttribute(alignType: MenuAlignType | undefined, offset?: Offset): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (alignType !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const alignTypeTmpValue  = (alignType as MenuAlignType)
            thisSerializer.writeInt32(TypeChecker.MenuAlignType_ToNumeric(alignTypeTmpValue))
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
    divider_value?: DividerOptions | undefined
    textModifier_value?: TextModifier | undefined
    arrowModifier_value?: SymbolGlyphModifier | undefined
    optionTextModifier_value?: TextModifier | undefined
    selectedOptionTextModifier_value?: TextModifier | undefined
    dividerStyle_value?: DividerStyleOptions | undefined
    avoidance_value?: AvoidanceMode | undefined
    menuOutline_value?: MenuOutlineOptions | undefined
    attributeModifier_value?: AttributeModifier<SelectAttribute> | AttributeModifier<CommonMethod> | undefined
    public selected(value: number | Resource | Bindable<number> | Bindable<Resource> | undefined): this {
        return this
    }
    public value(value: ResourceStr | Bindable<string> | Bindable<Resource> | undefined): this {
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
    public attributeModifier(value: AttributeModifier<SelectAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

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
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class SelectModifier extends CommonMethodModifier implements SelectAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _selected_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selected_0_0value?: number | Resource | Bindable<number> | Bindable<Resource> | undefined
    _value_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _value_0_0value?: ResourceStr | Bindable<string> | Bindable<Resource> | undefined
    _font_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _font_0_0value?: Font | undefined
    _fontColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontColor_0_0value?: ResourceColor | undefined
    _selectedOptionBgColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedOptionBgColor_0_0value?: ResourceColor | undefined
    _selectedOptionFont_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedOptionFont_0_0value?: Font | undefined
    _selectedOptionFontColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedOptionFontColor_0_0value?: ResourceColor | undefined
    _optionBgColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _optionBgColor_0_0value?: ResourceColor | undefined
    _optionFont_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _optionFont_0_0value?: Font | undefined
    _optionFontColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _optionFontColor_0_0value?: ResourceColor | undefined
    _onSelect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onSelect_0_0value?: OnSelectCallback | undefined
    _space_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _space_0_0value?: Length | undefined
    _arrowPosition_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _arrowPosition_0_0value?: ArrowPosition | undefined
    _optionWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _optionWidth_0_0value?: Dimension | OptionWidthMode | undefined
    _optionHeight_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _optionHeight_0_0value?: Dimension | undefined
    _menuBackgroundColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _menuBackgroundColor_0_0value?: ResourceColor | undefined
    _menuBackgroundBlurStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _menuBackgroundBlurStyle_0_0value?: BlurStyle | undefined
    _controlSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _controlSize_0_0value?: ControlSize | undefined
    _divider_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _divider_0_0value?: DividerOptions | undefined
    _textModifier_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textModifier_0_0value?: TextModifier | undefined
    _arrowModifier_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _arrowModifier_0_0value?: SymbolGlyphModifier | undefined
    _optionTextModifier_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _optionTextModifier_0_0value?: TextModifier | undefined
    _selectedOptionTextModifier_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedOptionTextModifier_0_0value?: TextModifier | undefined
    _dividerStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _dividerStyle_0_0value?: DividerStyleOptions | undefined
    _avoidance_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _avoidance_0_0value?: AvoidanceMode | undefined
    _menuOutline_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _menuOutline_0_0value?: MenuOutlineOptions | undefined
    _menuAlign_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _menuAlign_0_0value?: MenuAlignType | undefined
    _menuAlign_0_1value?: Offset | undefined
    applyModifierPatch(peer: ArkSelectPeer): void {
        super.applyModifierPatch(peer)
        if (this._selected_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selected_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSelectedAttribute((this._selected_0_0value as number | Resource | Bindable<number> | Bindable<Resource> | undefined));
                    this._selected_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selected_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selected_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSelectedAttribute((undefined as number | Resource | Bindable<number> | Bindable<Resource> | undefined));
                }
            }
        }
        if (this._value_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._value_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setValueAttribute((this._value_0_0value as ResourceStr | Bindable<string> | Bindable<Resource> | undefined));
                    this._value_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._value_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._value_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setValueAttribute((undefined as ResourceStr | Bindable<string> | Bindable<Resource> | undefined));
                }
            }
        }
        if (this._font_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._font_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontAttribute((this._font_0_0value as Font | undefined));
                    this._font_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._font_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._font_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontAttribute((undefined as Font | undefined));
                }
            }
        }
        if (this._fontColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontColorAttribute((this._fontColor_0_0value as ResourceColor | undefined));
                    this._fontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._selectedOptionBgColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectedOptionBgColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSelectedOptionBgColorAttribute((this._selectedOptionBgColor_0_0value as ResourceColor | undefined));
                    this._selectedOptionBgColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectedOptionBgColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectedOptionBgColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSelectedOptionBgColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._selectedOptionFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectedOptionFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSelectedOptionFontAttribute((this._selectedOptionFont_0_0value as Font | undefined));
                    this._selectedOptionFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectedOptionFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectedOptionFont_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSelectedOptionFontAttribute((undefined as Font | undefined));
                }
            }
        }
        if (this._selectedOptionFontColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectedOptionFontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSelectedOptionFontColorAttribute((this._selectedOptionFontColor_0_0value as ResourceColor | undefined));
                    this._selectedOptionFontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectedOptionFontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectedOptionFontColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSelectedOptionFontColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._optionBgColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._optionBgColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOptionBgColorAttribute((this._optionBgColor_0_0value as ResourceColor | undefined));
                    this._optionBgColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._optionBgColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._optionBgColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOptionBgColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._optionFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._optionFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOptionFontAttribute((this._optionFont_0_0value as Font | undefined));
                    this._optionFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._optionFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._optionFont_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOptionFontAttribute((undefined as Font | undefined));
                }
            }
        }
        if (this._optionFontColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._optionFontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOptionFontColorAttribute((this._optionFontColor_0_0value as ResourceColor | undefined));
                    this._optionFontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._optionFontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._optionFontColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOptionFontColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._onSelect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onSelect_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnSelectAttribute((this._onSelect_0_0value as OnSelectCallback | undefined));
                    this._onSelect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onSelect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onSelect_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnSelectAttribute((undefined as OnSelectCallback | undefined));
                }
            }
        }
        if (this._space_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._space_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSpaceAttribute((this._space_0_0value as Length | undefined));
                    this._space_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._space_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._space_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSpaceAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._arrowPosition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._arrowPosition_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setArrowPositionAttribute((this._arrowPosition_0_0value as ArrowPosition | undefined));
                    this._arrowPosition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._arrowPosition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._arrowPosition_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setArrowPositionAttribute((undefined as ArrowPosition | undefined));
                }
            }
        }
        if (this._optionWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._optionWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOptionWidthAttribute((this._optionWidth_0_0value as Dimension | OptionWidthMode | undefined));
                    this._optionWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._optionWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._optionWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOptionWidthAttribute((undefined as Dimension | OptionWidthMode | undefined));
                }
            }
        }
        if (this._optionHeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._optionHeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOptionHeightAttribute((this._optionHeight_0_0value as Dimension | undefined));
                    this._optionHeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._optionHeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._optionHeight_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOptionHeightAttribute((undefined as Dimension | undefined));
                }
            }
        }
        if (this._menuBackgroundColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._menuBackgroundColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMenuBackgroundColorAttribute((this._menuBackgroundColor_0_0value as ResourceColor | undefined));
                    this._menuBackgroundColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._menuBackgroundColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._menuBackgroundColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMenuBackgroundColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._menuBackgroundBlurStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._menuBackgroundBlurStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMenuBackgroundBlurStyleAttribute((this._menuBackgroundBlurStyle_0_0value as BlurStyle | undefined));
                    this._menuBackgroundBlurStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._menuBackgroundBlurStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._menuBackgroundBlurStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMenuBackgroundBlurStyleAttribute((undefined as BlurStyle | undefined));
                }
            }
        }
        if (this._controlSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._controlSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setControlSizeAttribute((this._controlSize_0_0value as ControlSize | undefined));
                    this._controlSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._controlSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._controlSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setControlSizeAttribute((undefined as ControlSize | undefined));
                }
            }
        }
        if (this._divider_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._divider_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDividerAttribute((this._divider_0_0value as DividerOptions | undefined));
                    this._divider_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._divider_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._divider_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDividerAttribute((undefined as DividerOptions | undefined));
                }
            }
        }
        if (this._textModifier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._textModifier_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTextModifierAttribute((this._textModifier_0_0value as TextModifier | undefined));
                    this._textModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._textModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._textModifier_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTextModifierAttribute((undefined as TextModifier | undefined));
                }
            }
        }
        if (this._arrowModifier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._arrowModifier_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setArrowModifierAttribute((this._arrowModifier_0_0value as SymbolGlyphModifier | undefined));
                    this._arrowModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._arrowModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._arrowModifier_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setArrowModifierAttribute((undefined as SymbolGlyphModifier | undefined));
                }
            }
        }
        if (this._optionTextModifier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._optionTextModifier_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOptionTextModifierAttribute((this._optionTextModifier_0_0value as TextModifier | undefined));
                    this._optionTextModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._optionTextModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._optionTextModifier_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOptionTextModifierAttribute((undefined as TextModifier | undefined));
                }
            }
        }
        if (this._selectedOptionTextModifier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectedOptionTextModifier_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSelectedOptionTextModifierAttribute((this._selectedOptionTextModifier_0_0value as TextModifier | undefined));
                    this._selectedOptionTextModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectedOptionTextModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectedOptionTextModifier_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSelectedOptionTextModifierAttribute((undefined as TextModifier | undefined));
                }
            }
        }
        if (this._dividerStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._dividerStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDividerStyleAttribute((this._dividerStyle_0_0value as DividerStyleOptions | undefined));
                    this._dividerStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._dividerStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._dividerStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDividerStyleAttribute((undefined as DividerStyleOptions | undefined));
                }
            }
        }
        if (this._avoidance_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._avoidance_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAvoidanceAttribute((this._avoidance_0_0value as AvoidanceMode | undefined));
                    this._avoidance_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._avoidance_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._avoidance_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAvoidanceAttribute((undefined as AvoidanceMode | undefined));
                }
            }
        }
        if (this._menuOutline_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._menuOutline_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMenuOutlineAttribute((this._menuOutline_0_0value as MenuOutlineOptions | undefined));
                    this._menuOutline_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._menuOutline_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._menuOutline_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMenuOutlineAttribute((undefined as MenuOutlineOptions | undefined));
                }
            }
        }
        if (this._menuAlign_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._menuAlign_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMenuAlignAttribute((this._menuAlign_0_0value as MenuAlignType | undefined), (this._menuAlign_0_1value as Offset | undefined));
                    this._menuAlign_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._menuAlign_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._menuAlign_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMenuAlignAttribute((undefined as MenuAlignType | undefined), (undefined as Offset | undefined | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: SelectModifier): void {
        super.mergeModifier(modifier)
        if (modifier._selected_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selected_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selected(modifier._selected_0_0value);
                    break;
                }
                default: {
                    this.selected((undefined as number | Resource | Bindable<number> | Bindable<Resource> | undefined));
                }
            }
        }
        if (modifier._value_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._value_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.value(modifier._value_0_0value);
                    break;
                }
                default: {
                    this.value((undefined as ResourceStr | Bindable<string> | Bindable<Resource> | undefined));
                }
            }
        }
        if (modifier._font_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._font_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.font(modifier._font_0_0value);
                    break;
                }
                default: {
                    this.font((undefined as Font | undefined));
                }
            }
        }
        if (modifier._fontColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontColor(modifier._fontColor_0_0value);
                    break;
                }
                default: {
                    this.fontColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._selectedOptionBgColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selectedOptionBgColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selectedOptionBgColor(modifier._selectedOptionBgColor_0_0value);
                    break;
                }
                default: {
                    this.selectedOptionBgColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._selectedOptionFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selectedOptionFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selectedOptionFont(modifier._selectedOptionFont_0_0value);
                    break;
                }
                default: {
                    this.selectedOptionFont((undefined as Font | undefined));
                }
            }
        }
        if (modifier._selectedOptionFontColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selectedOptionFontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selectedOptionFontColor(modifier._selectedOptionFontColor_0_0value);
                    break;
                }
                default: {
                    this.selectedOptionFontColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._optionBgColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._optionBgColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.optionBgColor(modifier._optionBgColor_0_0value);
                    break;
                }
                default: {
                    this.optionBgColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._optionFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._optionFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.optionFont(modifier._optionFont_0_0value);
                    break;
                }
                default: {
                    this.optionFont((undefined as Font | undefined));
                }
            }
        }
        if (modifier._optionFontColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._optionFontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.optionFontColor(modifier._optionFontColor_0_0value);
                    break;
                }
                default: {
                    this.optionFontColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._onSelect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onSelect_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onSelect(modifier._onSelect_0_0value);
                    break;
                }
                default: {
                    this.onSelect((undefined as OnSelectCallback | undefined));
                }
            }
        }
        if (modifier._space_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._space_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.space(modifier._space_0_0value);
                    break;
                }
                default: {
                    this.space((undefined as Length | undefined));
                }
            }
        }
        if (modifier._arrowPosition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._arrowPosition_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.arrowPosition(modifier._arrowPosition_0_0value);
                    break;
                }
                default: {
                    this.arrowPosition((undefined as ArrowPosition | undefined));
                }
            }
        }
        if (modifier._optionWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._optionWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.optionWidth(modifier._optionWidth_0_0value);
                    break;
                }
                default: {
                    this.optionWidth((undefined as Dimension | OptionWidthMode | undefined));
                }
            }
        }
        if (modifier._optionHeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._optionHeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.optionHeight(modifier._optionHeight_0_0value);
                    break;
                }
                default: {
                    this.optionHeight((undefined as Dimension | undefined));
                }
            }
        }
        if (modifier._menuBackgroundColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._menuBackgroundColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.menuBackgroundColor(modifier._menuBackgroundColor_0_0value);
                    break;
                }
                default: {
                    this.menuBackgroundColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._menuBackgroundBlurStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._menuBackgroundBlurStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.menuBackgroundBlurStyle(modifier._menuBackgroundBlurStyle_0_0value);
                    break;
                }
                default: {
                    this.menuBackgroundBlurStyle((undefined as BlurStyle | undefined));
                }
            }
        }
        if (modifier._controlSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._controlSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.controlSize(modifier._controlSize_0_0value);
                    break;
                }
                default: {
                    this.controlSize((undefined as ControlSize | undefined));
                }
            }
        }
        if (modifier._divider_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._divider_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.divider(modifier._divider_0_0value);
                    break;
                }
                default: {
                    this.divider((undefined as DividerOptions | undefined));
                }
            }
        }
        if (modifier._textModifier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._textModifier_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.textModifier(modifier._textModifier_0_0value);
                    break;
                }
                default: {
                    this.textModifier((undefined as TextModifier | undefined));
                }
            }
        }
        if (modifier._arrowModifier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._arrowModifier_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.arrowModifier(modifier._arrowModifier_0_0value);
                    break;
                }
                default: {
                    this.arrowModifier((undefined as SymbolGlyphModifier | undefined));
                }
            }
        }
        if (modifier._optionTextModifier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._optionTextModifier_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.optionTextModifier(modifier._optionTextModifier_0_0value);
                    break;
                }
                default: {
                    this.optionTextModifier((undefined as TextModifier | undefined));
                }
            }
        }
        if (modifier._selectedOptionTextModifier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selectedOptionTextModifier_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selectedOptionTextModifier(modifier._selectedOptionTextModifier_0_0value);
                    break;
                }
                default: {
                    this.selectedOptionTextModifier((undefined as TextModifier | undefined));
                }
            }
        }
        if (modifier._dividerStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._dividerStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.dividerStyle(modifier._dividerStyle_0_0value);
                    break;
                }
                default: {
                    this.dividerStyle((undefined as DividerStyleOptions | undefined));
                }
            }
        }
        if (modifier._avoidance_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._avoidance_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.avoidance(modifier._avoidance_0_0value);
                    break;
                }
                default: {
                    this.avoidance((undefined as AvoidanceMode | undefined));
                }
            }
        }
        if (modifier._menuOutline_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._menuOutline_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.menuOutline(modifier._menuOutline_0_0value);
                    break;
                }
                default: {
                    this.menuOutline((undefined as MenuOutlineOptions | undefined));
                }
            }
        }
        if (modifier._menuAlign_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._menuAlign_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.menuAlign(modifier._menuAlign_0_0value, modifier._menuAlign_0_1value);
                    break;
                }
                default: {
                    this.menuAlign((undefined as MenuAlignType | undefined), (undefined as Offset | undefined | undefined));
                }
            }
        }
    }
    selected(value: number | Resource | Bindable<number> | Bindable<Resource> | undefined): this {
        if (((this._selected_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._selected_0_flag = AttributeUpdaterFlag.UPDATE
            this._selected_0_0value = value
        } else
        {
            this._selected_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    value(value: ResourceStr | Bindable<string> | Bindable<Resource> | undefined): this {
        if (((this._value_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._value_0_flag = AttributeUpdaterFlag.UPDATE
            this._value_0_0value = value
        } else
        {
            this._value_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    font(value: Font | undefined): this {
        if (((this._font_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._font_0_flag = AttributeUpdaterFlag.UPDATE
            this._font_0_0value = value
        } else
        {
            this._font_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontColor(value: ResourceColor | undefined): this {
        if (((this._fontColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fontColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontColor_0_0value = value
        } else
        {
            this._fontColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selectedOptionBgColor(value: ResourceColor | undefined): this {
        if (((this._selectedOptionBgColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._selectedOptionBgColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectedOptionBgColor_0_0value = value
        } else
        {
            this._selectedOptionBgColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selectedOptionFont(value: Font | undefined): this {
        if (((this._selectedOptionFont_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._selectedOptionFont_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectedOptionFont_0_0value = value
        } else
        {
            this._selectedOptionFont_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selectedOptionFontColor(value: ResourceColor | undefined): this {
        if (((this._selectedOptionFontColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._selectedOptionFontColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectedOptionFontColor_0_0value = value
        } else
        {
            this._selectedOptionFontColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    optionBgColor(value: ResourceColor | undefined): this {
        if (((this._optionBgColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._optionBgColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._optionBgColor_0_0value = value
        } else
        {
            this._optionBgColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    optionFont(value: Font | undefined): this {
        if (((this._optionFont_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._optionFont_0_flag = AttributeUpdaterFlag.UPDATE
            this._optionFont_0_0value = value
        } else
        {
            this._optionFont_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    optionFontColor(value: ResourceColor | undefined): this {
        if (((this._optionFontColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._optionFontColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._optionFontColor_0_0value = value
        } else
        {
            this._optionFontColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onSelect(value: OnSelectCallback | undefined): this {
        if (((this._onSelect_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onSelect_0_flag = AttributeUpdaterFlag.UPDATE
            this._onSelect_0_0value = value
        } else
        {
            this._onSelect_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    space(value: Length | undefined): this {
        if (((this._space_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._space_0_flag = AttributeUpdaterFlag.UPDATE
            this._space_0_0value = value
        } else
        {
            this._space_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    arrowPosition(value: ArrowPosition | undefined): this {
        if (((this._arrowPosition_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._arrowPosition_0_flag = AttributeUpdaterFlag.UPDATE
            this._arrowPosition_0_0value = value
        } else
        {
            this._arrowPosition_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    optionWidth(value: Dimension | OptionWidthMode | undefined): this {
        if (((this._optionWidth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._optionWidth_0_flag = AttributeUpdaterFlag.UPDATE
            this._optionWidth_0_0value = value
        } else
        {
            this._optionWidth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    optionHeight(value: Dimension | undefined): this {
        if (((this._optionHeight_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._optionHeight_0_flag = AttributeUpdaterFlag.UPDATE
            this._optionHeight_0_0value = value
        } else
        {
            this._optionHeight_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    menuBackgroundColor(value: ResourceColor | undefined): this {
        if (((this._menuBackgroundColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._menuBackgroundColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._menuBackgroundColor_0_0value = value
        } else
        {
            this._menuBackgroundColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    menuBackgroundBlurStyle(value: BlurStyle | undefined): this {
        if (((this._menuBackgroundBlurStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._menuBackgroundBlurStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._menuBackgroundBlurStyle_0_0value = value
        } else
        {
            this._menuBackgroundBlurStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    controlSize(value: ControlSize | undefined): this {
        if (((this._controlSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._controlSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._controlSize_0_0value = value
        } else
        {
            this._controlSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    divider(value: DividerOptions | undefined): this {
        if (((this._divider_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._divider_0_flag = AttributeUpdaterFlag.UPDATE
            this._divider_0_0value = value
        } else
        {
            this._divider_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    textModifier(value: TextModifier | undefined): this {
        if (((this._textModifier_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._textModifier_0_flag = AttributeUpdaterFlag.UPDATE
            this._textModifier_0_0value = value
        } else
        {
            this._textModifier_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    arrowModifier(value: SymbolGlyphModifier | undefined): this {
        if (((this._arrowModifier_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._arrowModifier_0_flag = AttributeUpdaterFlag.UPDATE
            this._arrowModifier_0_0value = value
        } else
        {
            this._arrowModifier_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    optionTextModifier(value: TextModifier | undefined): this {
        if (((this._optionTextModifier_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._optionTextModifier_0_flag = AttributeUpdaterFlag.UPDATE
            this._optionTextModifier_0_0value = value
        } else
        {
            this._optionTextModifier_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selectedOptionTextModifier(value: TextModifier | undefined): this {
        if (((this._selectedOptionTextModifier_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._selectedOptionTextModifier_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectedOptionTextModifier_0_0value = value
        } else
        {
            this._selectedOptionTextModifier_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    dividerStyle(value: DividerStyleOptions | undefined): this {
        if (((this._dividerStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._dividerStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._dividerStyle_0_0value = value
        } else
        {
            this._dividerStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    avoidance(value: AvoidanceMode | undefined): this {
        if (((this._avoidance_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._avoidance_0_flag = AttributeUpdaterFlag.UPDATE
            this._avoidance_0_0value = value
        } else
        {
            this._avoidance_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    menuOutline(value: MenuOutlineOptions | undefined): this {
        if (((this._menuOutline_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._menuOutline_0_flag = AttributeUpdaterFlag.UPDATE
            this._menuOutline_0_0value = value
        } else
        {
            this._menuOutline_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    menuAlign(alignType: MenuAlignType | undefined, offset?: Offset): this {
        if (((this._menuAlign_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._menuAlign_0_flag = AttributeUpdaterFlag.UPDATE
            this._menuAlign_0_0value = alignType
            this._menuAlign_0_1value = offset
        } else
        {
            this._menuAlign_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<SelectAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
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
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForValueForIdx0  = valueHolderForValue as string
            valueSerializer.writeString(valueHolderForValueForIdx0)
        } else if (valueHolderForValue instanceof Resource) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForValueForIdx1  = valueHolderForValue as Resource
            Resource_serializer.write(valueSerializer, valueHolderForValueForIdx1)
        }
        const valueHolderForIcon  = value.icon
        if (valueHolderForIcon !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIconTmpValue  = valueHolderForIcon!
            if (valueHolderForIconTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForIconTmpValueForIdx0  = valueHolderForIconTmpValue as string
                valueSerializer.writeString(valueHolderForIconTmpValueForIdx0)
            } else if (valueHolderForIconTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toChar())
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
        let iconTmpBuf : ResourceStr | undefined
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
        let symbolIconTmpBuf : SymbolGlyphModifier | undefined
        if ((symbolIconTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            symbolIconTmpBuf = SymbolGlyphModifier_serializer.read(valueDeserializer)
        }
        const symbolIconTmpResult : SymbolGlyphModifier | undefined = symbolIconTmpBuf
        const selectedTmpResult : boolean = valueDeserializer.readBoolean()
        const indexTmpResult : number = (valueDeserializer.readNumber() as number)
        throw new Error("Interface with functions is not supported")
    }
}
export class SelectOption_serializer {
    public static write(buffer: SerializerBase, value: SelectOption): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForValue  = value.value
        if (valueHolderForValue instanceof string) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForValueForIdx0  = valueHolderForValue as string
            valueSerializer.writeString(valueHolderForValueForIdx0)
        } else if (valueHolderForValue instanceof Resource) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForValueForIdx1  = valueHolderForValue as Resource
            Resource_serializer.write(valueSerializer, valueHolderForValueForIdx1)
        }
        const valueHolderForIcon  = value.icon
        if (valueHolderForIcon !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIconTmpValue  = valueHolderForIcon!
            if (valueHolderForIconTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForIconTmpValueForIdx0  = valueHolderForIconTmpValue as string
                valueSerializer.writeString(valueHolderForIconTmpValueForIdx0)
            } else if (valueHolderForIconTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toChar())
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
        let iconTmpBuf : ResourceStr | undefined
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
        let symbolIconTmpBuf : SymbolGlyphModifier | undefined
        if ((symbolIconTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            symbolIconTmpBuf = SymbolGlyphModifier_serializer.read(valueDeserializer)
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
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForWidthTmpValueForIdx0  = valueHolderForWidthTmpValue as Dimension
                if (valueHolderForWidthTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toChar())
                    const valueHolderForWidthTmpValueForIdx0ForIdx0  = valueHolderForWidthTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForWidthTmpValueForIdx0ForIdx0)
                } else if (valueHolderForWidthTmpValueForIdx0 instanceof number) {
                    valueSerializer.writeInt8((1).toChar())
                    const valueHolderForWidthTmpValueForIdx0ForIdx1  = valueHolderForWidthTmpValueForIdx0 as number
                    valueSerializer.writeNumber(valueHolderForWidthTmpValueForIdx0ForIdx1)
                } else if (valueHolderForWidthTmpValueForIdx0 instanceof Resource) {
                    valueSerializer.writeInt8((2).toChar())
                    const valueHolderForWidthTmpValueForIdx0ForIdx2  = valueHolderForWidthTmpValueForIdx0 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForWidthTmpValueForIdx0ForIdx2)
                }
            } else if (valueHolderForWidthTmpValue instanceof EdgeOutlineWidths) {
                valueSerializer.writeInt8((1).toChar())
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
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForColorTmpValueForIdx0  = valueHolderForColorTmpValue as ResourceColor
                if (valueHolderForColorTmpValueForIdx0 instanceof Color) {
                    valueSerializer.writeInt8((0).toChar())
                    const valueHolderForColorTmpValueForIdx0ForIdx0  = valueHolderForColorTmpValueForIdx0 as Color
                    valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForColorTmpValueForIdx0ForIdx0))
                } else if (valueHolderForColorTmpValueForIdx0 instanceof number) {
                    valueSerializer.writeInt8((1).toChar())
                    const valueHolderForColorTmpValueForIdx0ForIdx1  = valueHolderForColorTmpValueForIdx0 as number
                    valueSerializer.writeNumber(valueHolderForColorTmpValueForIdx0ForIdx1)
                } else if (valueHolderForColorTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((2).toChar())
                    const valueHolderForColorTmpValueForIdx0ForIdx2  = valueHolderForColorTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForColorTmpValueForIdx0ForIdx2)
                } else if (valueHolderForColorTmpValueForIdx0 instanceof Resource) {
                    valueSerializer.writeInt8((3).toChar())
                    const valueHolderForColorTmpValueForIdx0ForIdx3  = valueHolderForColorTmpValueForIdx0 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForColorTmpValueForIdx0ForIdx3)
                }
            } else if (valueHolderForColorTmpValue instanceof EdgeColors) {
                valueSerializer.writeInt8((1).toChar())
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
        let widthTmpBuf : Dimension | EdgeOutlineWidths | undefined
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
        let colorTmpBuf : ResourceColor | EdgeColors | undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const colorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let colorTmpBuf_ : ResourceColor | EdgeColors | undefined
            if (colorTmpBuf_UnionSelector == (0).toChar()) {
                const colorTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let colorTmpBuf_BufU : Color | number | string | Resource | undefined
                if (colorTmpBuf_BufUUnionSelector == (0).toChar()) {
                    colorTmpBuf_BufU = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
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

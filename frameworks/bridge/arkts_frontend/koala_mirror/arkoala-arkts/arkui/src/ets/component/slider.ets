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
import { LinearGradient_serializer, LinearGradient } from "./dataPanel"
import { SizeOptions_serializer, ResourceColor, Length, Dimension, SizeOptions, ResourceStr } from "./units"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, CommonConfiguration, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { Color, CrownSensitivity, Axis } from "./enums"
import { ContentModifier, AttributeModifier, hookSliderContentModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkSliderPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkSliderPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Slider_construct(peerId, flags)
        const _peer  = new ArkSliderPeer(_peerPtr, peerId, "Slider", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setSliderOptionsAttribute(options?: SliderOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            SliderOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._SliderInterface_setSliderOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBlockColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SliderAttribute_setBlockColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTrackColorAttribute(value: ResourceColor | LinearGradient | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if ((TypeChecker.isColor(value_value)) || (RuntimeType.NUMBER == value_value_type) || (RuntimeType.STRING == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as ResourceColor
                let value_value_0_type : int32 = RuntimeType.UNDEFINED
                value_value_0_type = runtimeType(value_value_0)
                if (TypeChecker.isColor(value_value_0)) {
                    thisSerializer.writeInt8((0).toChar())
                    const value_value_0_0  = value_value_0 as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0_0))
                }
                else if (RuntimeType.NUMBER == value_value_0_type) {
                    thisSerializer.writeInt8((1).toChar())
                    const value_value_0_1  = value_value_0 as number
                    thisSerializer.writeNumber(value_value_0_1)
                }
                else if (RuntimeType.STRING == value_value_0_type) {
                    thisSerializer.writeInt8((2).toChar())
                    const value_value_0_2  = value_value_0 as string
                    thisSerializer.writeString(value_value_0_2)
                }
                else if (RuntimeType.OBJECT == value_value_0_type) {
                    thisSerializer.writeInt8((3).toChar())
                    const value_value_0_3  = value_value_0 as Resource
                    Resource_serializer.write(thisSerializer, value_value_0_3)
                }
            }
            else if (TypeChecker.isLinearGradient(value_value)) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as LinearGradient
                LinearGradient_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SliderAttribute_setTrackColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedColorAttribute(value: ResourceColor | LinearGradient | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if ((TypeChecker.isColor(value_value)) || (RuntimeType.NUMBER == value_value_type) || (RuntimeType.STRING == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as ResourceColor
                let value_value_0_type : int32 = RuntimeType.UNDEFINED
                value_value_0_type = runtimeType(value_value_0)
                if (TypeChecker.isColor(value_value_0)) {
                    thisSerializer.writeInt8((0).toChar())
                    const value_value_0_0  = value_value_0 as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0_0))
                }
                else if (RuntimeType.NUMBER == value_value_0_type) {
                    thisSerializer.writeInt8((1).toChar())
                    const value_value_0_1  = value_value_0 as number
                    thisSerializer.writeNumber(value_value_0_1)
                }
                else if (RuntimeType.STRING == value_value_0_type) {
                    thisSerializer.writeInt8((2).toChar())
                    const value_value_0_2  = value_value_0 as string
                    thisSerializer.writeString(value_value_0_2)
                }
                else if (RuntimeType.OBJECT == value_value_0_type) {
                    thisSerializer.writeInt8((3).toChar())
                    const value_value_0_3  = value_value_0 as Resource
                    Resource_serializer.write(thisSerializer, value_value_0_3)
                }
            }
            else if (TypeChecker.isLinearGradient(value_value)) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as LinearGradient
                LinearGradient_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SliderAttribute_setSelectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setShowStepsAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_setShowSteps(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTrackThicknessAttribute(value: Length | undefined): void {
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
        ArkUIGeneratedNativeModule._SliderAttribute_setTrackThickness(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: ((value: number,mode: SliderChangeMode) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_setOnChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBlockBorderColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SliderAttribute_setBlockBorderColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBlockBorderWidthAttribute(value: Length | undefined): void {
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
        ArkUIGeneratedNativeModule._SliderAttribute_setBlockBorderWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStepColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SliderAttribute_setStepColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTrackBorderRadiusAttribute(value: Length | undefined): void {
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
        ArkUIGeneratedNativeModule._SliderAttribute_setTrackBorderRadius(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedBorderRadiusAttribute(value: Dimension | undefined): void {
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
        ArkUIGeneratedNativeModule._SliderAttribute_setSelectedBorderRadius(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBlockSizeAttribute(value: SizeOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            SizeOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_setBlockSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBlockStyleAttribute(value: SliderBlockStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            SliderBlockStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_setBlockStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStepSizeAttribute(value: Length | undefined): void {
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
        ArkUIGeneratedNativeModule._SliderAttribute_setStepSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSliderInteractionModeAttribute(value: SliderInteraction | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as SliderInteraction)
            thisSerializer.writeInt32(TypeChecker.SliderInteraction_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SliderAttribute_setSliderInteractionMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinResponsiveDistanceAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_setMinResponsiveDistance(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setContentModifierAttribute(value: ContentModifier<SliderConfiguration> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteObject(value_value)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_setContentModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSlideRangeAttribute(value: SlideRange | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            SlideRange_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_setSlideRange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDigitalCrownSensitivityAttribute(value: CrownSensitivity | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as CrownSensitivity)
            thisSerializer.writeInt32(TypeChecker.CrownSensitivity_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SliderAttribute_setDigitalCrownSensitivity(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SliderAttribute_setEnableHapticFeedback(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setShowTipsAttribute(value: boolean | undefined, content?: ResourceStr): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        let content_type : int32 = RuntimeType.UNDEFINED
        content_type = runtimeType(content)
        thisSerializer.writeInt8((content_type).toChar())
        if ((content_type) != (RuntimeType.UNDEFINED)) {
            const content_value  = content!
            let content_value_type : int32 = RuntimeType.UNDEFINED
            content_value_type = runtimeType(content_value)
            if (RuntimeType.STRING == content_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const content_value_0  = content_value as string
                thisSerializer.writeString(content_value_0)
            }
            else if (RuntimeType.OBJECT == content_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const content_value_1  = content_value as Resource
                Resource_serializer.write(thisSerializer, content_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SliderAttribute_setShowTips(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    set_onChangeEvent_valueAttribute(callback_: ((value: number | undefined) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._SliderAttribute_set_onChangeEvent_value(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum SliderStyle {
    OUT_SET = 0,
    OutSet = 0,
    IN_SET = 1,
    InSet = 1,
    NONE = 2
}
export enum SliderChangeMode {
    BEGIN = 0,
    Begin = 0,
    MOVING = 1,
    Moving = 1,
    END = 2,
    End = 2,
    CLICK = 3,
    Click = 3
}
export enum SliderInteraction {
    SLIDE_AND_CLICK = 0,
    SLIDE_ONLY = 1,
    SLIDE_AND_CLICK_UP = 2
}
export interface SlideRange {
    from?: number;
    to?: number;
}
export interface SliderOptions {
    value?: number | undefined;
    min?: number;
    max?: number;
    step?: number;
    style?: SliderStyle;
    direction?: Axis;
    reverse?: boolean;
}
export enum SliderBlockType {
    DEFAULT = 0,
    IMAGE = 1,
    SHAPE = 2
}
export interface SliderBlockStyle {
    type: SliderBlockType;
    image?: ResourceStr;
}
export type SliderTriggerChangeCallback = (value: number, mode: SliderChangeMode) => void;
export interface SliderConfiguration extends CommonConfiguration<SliderConfiguration> {
    value: number;
    min: number;
    max: number;
    step: number;
    triggerChange: SliderTriggerChangeCallback;
}
export interface SliderAttribute extends CommonMethod {
    blockColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method blockColor")
    }
    trackColor(value: ResourceColor | LinearGradient | undefined): this {
        throw new Error("Unimplemented method trackColor")
    }
    selectedColor(value: ResourceColor | LinearGradient | undefined): this {
        throw new Error("Unimplemented method selectedColor")
    }
    showSteps(value: boolean | undefined): this {
        throw new Error("Unimplemented method showSteps")
    }
    trackThickness(value: Length | undefined): this {
        throw new Error("Unimplemented method trackThickness")
    }
    onChange(value: ((value: number,mode: SliderChangeMode) => void) | undefined): this {
        throw new Error("Unimplemented method onChange")
    }
    blockBorderColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method blockBorderColor")
    }
    blockBorderWidth(value: Length | undefined): this {
        throw new Error("Unimplemented method blockBorderWidth")
    }
    stepColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method stepColor")
    }
    trackBorderRadius(value: Length | undefined): this {
        throw new Error("Unimplemented method trackBorderRadius")
    }
    selectedBorderRadius(value: Dimension | undefined): this {
        throw new Error("Unimplemented method selectedBorderRadius")
    }
    blockSize(value: SizeOptions | undefined): this {
        throw new Error("Unimplemented method blockSize")
    }
    blockStyle(value: SliderBlockStyle | undefined): this {
        throw new Error("Unimplemented method blockStyle")
    }
    stepSize(value: Length | undefined): this {
        throw new Error("Unimplemented method stepSize")
    }
    sliderInteractionMode(value: SliderInteraction | undefined): this {
        throw new Error("Unimplemented method sliderInteractionMode")
    }
    minResponsiveDistance(value: number | undefined): this {
        throw new Error("Unimplemented method minResponsiveDistance")
    }
    contentModifier(value: ContentModifier<SliderConfiguration> | undefined): this {
        throw new Error("Unimplemented method contentModifier")
    }
    slideRange(value: SlideRange | undefined): this {
        throw new Error("Unimplemented method slideRange")
    }
    digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        throw new Error("Unimplemented method digitalCrownSensitivity")
    }
    enableHapticFeedback(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableHapticFeedback")
    }
    showTips(value: boolean | undefined, content?: ResourceStr): this {
        throw new Error("Unimplemented method showTips")
    }
    _onChangeEvent_value(callback_: ((value: number | undefined) => void)): void {
        throw new Error("Unimplemented method _onChangeEvent_value")
    }
    attributeModifier(value: AttributeModifier<SliderAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkSliderStyle extends ArkCommonMethodStyle implements SliderAttribute {
    blockColor_value?: ResourceColor | undefined
    trackColor_value?: ResourceColor | LinearGradient | undefined
    selectedColor_value?: ResourceColor | LinearGradient | undefined
    showSteps_value?: boolean | undefined
    trackThickness_value?: Length | undefined
    onChange_value?: ((value: number,mode: SliderChangeMode) => void) | undefined
    blockBorderColor_value?: ResourceColor | undefined
    blockBorderWidth_value?: Length | undefined
    stepColor_value?: ResourceColor | undefined
    trackBorderRadius_value?: Length | undefined
    selectedBorderRadius_value?: Dimension | undefined
    blockSize_value?: SizeOptions | undefined
    blockStyle_value?: SliderBlockStyle | undefined
    stepSize_value?: Length | undefined
    sliderInteractionMode_value?: SliderInteraction | undefined
    minResponsiveDistance_value?: number | undefined
    contentModifier_value?: ContentModifier<SliderConfiguration> | undefined
    slideRange_value?: SlideRange | undefined
    digitalCrownSensitivity_value?: CrownSensitivity | undefined
    enableHapticFeedback_value?: boolean | undefined
    attributeModifier_value?: AttributeModifier<SliderAttribute> | AttributeModifier<CommonMethod> | undefined
    public blockColor(value: ResourceColor | undefined): this {
        return this
    }
    public trackColor(value: ResourceColor | LinearGradient | undefined): this {
        return this
    }
    public selectedColor(value: ResourceColor | LinearGradient | undefined): this {
        return this
    }
    public showSteps(value: boolean | undefined): this {
        return this
    }
    public trackThickness(value: Length | undefined): this {
        return this
    }
    public onChange(value: ((value: number,mode: SliderChangeMode) => void) | undefined): this {
        return this
    }
    public blockBorderColor(value: ResourceColor | undefined): this {
        return this
    }
    public blockBorderWidth(value: Length | undefined): this {
        return this
    }
    public stepColor(value: ResourceColor | undefined): this {
        return this
    }
    public trackBorderRadius(value: Length | undefined): this {
        return this
    }
    public selectedBorderRadius(value: Dimension | undefined): this {
        return this
    }
    public blockSize(value: SizeOptions | undefined): this {
        return this
    }
    public blockStyle(value: SliderBlockStyle | undefined): this {
        return this
    }
    public stepSize(value: Length | undefined): this {
        return this
    }
    public sliderInteractionMode(value: SliderInteraction | undefined): this {
        return this
    }
    public minResponsiveDistance(value: number | undefined): this {
        return this
    }
    public contentModifier(value: ContentModifier<SliderConfiguration> | undefined): this {
        return this
    }
    public slideRange(value: SlideRange | undefined): this {
        return this
    }
    public digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        return this
    }
    public showTips(value: boolean | undefined, content?: ResourceStr): this {
        return this
    }
    public _onChangeEvent_value(callback_: ((value: number | undefined) => void)): void {
        throw new Error("Unimplemented")
    }
    public attributeModifier(value: AttributeModifier<SliderAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: SliderAttribute): void {
        super.apply(target)
        if (this.blockColor_value !== undefined)
            target.blockColor(this.blockColor_value!)
        if (this.trackColor_value !== undefined)
            target.trackColor(this.trackColor_value!)
        if (this.selectedColor_value !== undefined)
            target.selectedColor(this.selectedColor_value!)
        if (this.showSteps_value !== undefined)
            target.showSteps(this.showSteps_value!)
        if (this.trackThickness_value !== undefined)
            target.trackThickness(this.trackThickness_value!)
        if (this.onChange_value !== undefined)
            target.onChange(this.onChange_value!)
        if (this.blockBorderColor_value !== undefined)
            target.blockBorderColor(this.blockBorderColor_value!)
        if (this.blockBorderWidth_value !== undefined)
            target.blockBorderWidth(this.blockBorderWidth_value!)
        if (this.stepColor_value !== undefined)
            target.stepColor(this.stepColor_value!)
        if (this.trackBorderRadius_value !== undefined)
            target.trackBorderRadius(this.trackBorderRadius_value!)
        if (this.selectedBorderRadius_value !== undefined)
            target.selectedBorderRadius(this.selectedBorderRadius_value!)
        if (this.blockSize_value !== undefined)
            target.blockSize(this.blockSize_value!)
        if (this.blockStyle_value !== undefined)
            target.blockStyle(this.blockStyle_value!)
        if (this.stepSize_value !== undefined)
            target.stepSize(this.stepSize_value!)
        if (this.sliderInteractionMode_value !== undefined)
            target.sliderInteractionMode(this.sliderInteractionMode_value!)
        if (this.minResponsiveDistance_value !== undefined)
            target.minResponsiveDistance(this.minResponsiveDistance_value!)
        if (this.contentModifier_value !== undefined)
            target.contentModifier(this.contentModifier_value!)
        if (this.slideRange_value !== undefined)
            target.slideRange(this.slideRange_value!)
        if (this.digitalCrownSensitivity_value !== undefined)
            target.digitalCrownSensitivity(this.digitalCrownSensitivity_value!)
        if (this.enableHapticFeedback_value !== undefined)
            target.enableHapticFeedback(this.enableHapticFeedback_value!)
    }
}

export class ArkSliderComponent extends ArkCommonMethodComponent implements SliderAttribute {
    getPeer(): ArkSliderPeer {
        return (this.peer as ArkSliderPeer)
    }
    public setSliderOptions(options?: SliderOptions): this {
        if (this.checkPriority("setSliderOptions")) {
            const options_casted = options as (SliderOptions | undefined)
            this.getPeer()?.setSliderOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public blockColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("blockColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setBlockColorAttribute(value_casted)
            return this
        }
        return this
    }
    public trackColor(value: ResourceColor | LinearGradient | undefined): this {
        if (this.checkPriority("trackColor")) {
            const value_casted = value as (ResourceColor | LinearGradient | undefined)
            this.getPeer()?.setTrackColorAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedColor(value: ResourceColor | LinearGradient | undefined): this {
        if (this.checkPriority("selectedColor")) {
            const value_casted = value as (ResourceColor | LinearGradient | undefined)
            this.getPeer()?.setSelectedColorAttribute(value_casted)
            return this
        }
        return this
    }
    public showSteps(value: boolean | undefined): this {
        if (this.checkPriority("showSteps")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setShowStepsAttribute(value_casted)
            return this
        }
        return this
    }
    public trackThickness(value: Length | undefined): this {
        if (this.checkPriority("trackThickness")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setTrackThicknessAttribute(value_casted)
            return this
        }
        return this
    }
    public onChange(value: ((value: number,mode: SliderChangeMode) => void) | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((value: number,mode: SliderChangeMode) => void) | undefined)
            this.getPeer()?.setOnChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public blockBorderColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("blockBorderColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setBlockBorderColorAttribute(value_casted)
            return this
        }
        return this
    }
    public blockBorderWidth(value: Length | undefined): this {
        if (this.checkPriority("blockBorderWidth")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setBlockBorderWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public stepColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("stepColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setStepColorAttribute(value_casted)
            return this
        }
        return this
    }
    public trackBorderRadius(value: Length | undefined): this {
        if (this.checkPriority("trackBorderRadius")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setTrackBorderRadiusAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedBorderRadius(value: Dimension | undefined): this {
        if (this.checkPriority("selectedBorderRadius")) {
            const value_casted = value as (Dimension | undefined)
            this.getPeer()?.setSelectedBorderRadiusAttribute(value_casted)
            return this
        }
        return this
    }
    public blockSize(value: SizeOptions | undefined): this {
        if (this.checkPriority("blockSize")) {
            const value_casted = value as (SizeOptions | undefined)
            this.getPeer()?.setBlockSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public blockStyle(value: SliderBlockStyle | undefined): this {
        if (this.checkPriority("blockStyle")) {
            const value_casted = value as (SliderBlockStyle | undefined)
            this.getPeer()?.setBlockStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public stepSize(value: Length | undefined): this {
        if (this.checkPriority("stepSize")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setStepSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public sliderInteractionMode(value: SliderInteraction | undefined): this {
        if (this.checkPriority("sliderInteractionMode")) {
            const value_casted = value as (SliderInteraction | undefined)
            this.getPeer()?.setSliderInteractionModeAttribute(value_casted)
            return this
        }
        return this
    }
    public minResponsiveDistance(value: number | undefined): this {
        if (this.checkPriority("minResponsiveDistance")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setMinResponsiveDistanceAttribute(value_casted)
            return this
        }
        return this
    }
    public contentModifier(value: ContentModifier<SliderConfiguration> | undefined): this {
        if (this.checkPriority("contentModifier")) {
            const value_casted = value as (ContentModifier<SliderConfiguration> | undefined)
            this.getPeer()?.setContentModifierAttribute(value_casted)
            return this
        }
        return this
    }
    public slideRange(value: SlideRange | undefined): this {
        if (this.checkPriority("slideRange")) {
            const value_casted = value as (SlideRange | undefined)
            this.getPeer()?.setSlideRangeAttribute(value_casted)
            return this
        }
        return this
    }
    public digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        if (this.checkPriority("digitalCrownSensitivity")) {
            const value_casted = value as (CrownSensitivity | undefined)
            this.getPeer()?.setDigitalCrownSensitivityAttribute(value_casted)
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
    public showTips(value: boolean | undefined, content?: ResourceStr): this {
        if (this.checkPriority("showTips")) {
            const value_casted = value as (boolean | undefined)
            const content_casted = content as (ResourceStr | undefined)
            this.getPeer()?.setShowTipsAttribute(value_casted, content_casted)
            return this
        }
        return this
    }
    public _onChangeEvent_value(callback_: ((value: number | undefined) => void)): void {
        if (this.checkPriority("_onChangeEvent_value")) {
            const callback__casted = callback_ as (((value: number | undefined) => void))
            this.getPeer()?.set_onChangeEvent_valueAttribute(callback__casted)
            return
        }
        return
    }
    public attributeModifier(value: AttributeModifier<SliderAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withSliderStyle(receiver: SliderAttribute, modifier: AttributeModifier<SliderAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkSliderStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Slider")
// export function Slider(
//     options?: SliderOptions,
//     @memo
//     content_?: () => void,
// ): SliderAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Slider(
    @memo
    style: ((attributes: SliderAttribute) => void) | undefined,
    options?: SliderOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkSliderComponent>((): ArkSliderComponent => {
        return new ArkSliderComponent()
    })
    NodeAttach<ArkSliderPeer>((): ArkSliderPeer => ArkSliderPeer.create(receiver), (_: ArkSliderPeer): void => {
        receiver.setSliderOptions(options)
        style?.(receiver)
        withSliderStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkSliderSet extends ArkCommonMethodSet implements SliderAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _blockColor_flag?: boolean
    _blockColor0_value?: ResourceColor | undefined
    _trackColor_flag?: boolean
    _trackColor0_value?: ResourceColor | LinearGradient | undefined
    _selectedColor_flag?: boolean
    _selectedColor0_value?: ResourceColor | LinearGradient | undefined
    _showSteps_flag?: boolean
    _showSteps0_value?: boolean | undefined
    _trackThickness_flag?: boolean
    _trackThickness0_value?: Length | undefined
    _onChange_flag?: boolean
    _onChange0_value?: ((value: number,mode: SliderChangeMode) => void) | undefined
    _blockBorderColor_flag?: boolean
    _blockBorderColor0_value?: ResourceColor | undefined
    _blockBorderWidth_flag?: boolean
    _blockBorderWidth0_value?: Length | undefined
    _stepColor_flag?: boolean
    _stepColor0_value?: ResourceColor | undefined
    _trackBorderRadius_flag?: boolean
    _trackBorderRadius0_value?: Length | undefined
    _selectedBorderRadius_flag?: boolean
    _selectedBorderRadius0_value?: Dimension | undefined
    _blockSize_flag?: boolean
    _blockSize0_value?: SizeOptions | undefined
    _blockStyle_flag?: boolean
    _blockStyle0_value?: SliderBlockStyle | undefined
    _stepSize_flag?: boolean
    _stepSize0_value?: Length | undefined
    _sliderInteractionMode_flag?: boolean
    _sliderInteractionMode0_value?: SliderInteraction | undefined
    _minResponsiveDistance_flag?: boolean
    _minResponsiveDistance0_value?: number | undefined
    _contentModifier_flag?: boolean
    _contentModifier0_value?: ContentModifier<SliderConfiguration> | undefined
    _slideRange_flag?: boolean
    _slideRange0_value?: SlideRange | undefined
    _digitalCrownSensitivity_flag?: boolean
    _digitalCrownSensitivity0_value?: CrownSensitivity | undefined
    _enableHapticFeedback_flag?: boolean
    _enableHapticFeedback0_value?: boolean | undefined
    _showTips_flag?: boolean
    _showTips0_value?: boolean | undefined
    _showTips1_value?: ResourceStr | undefined
    __onChangeEvent_value_flag?: boolean
    __onChangeEvent_value0_value?: ((value: number | undefined) => void)
    applyModifierPatch(component: SliderAttribute): void {
        if (this._blockColor_flag)
            component.blockColor((this._blockColor0_value as ResourceColor | undefined))
        if (this._trackColor_flag)
            component.trackColor((this._trackColor0_value as ResourceColor | LinearGradient | undefined))
        if (this._selectedColor_flag)
            component.selectedColor((this._selectedColor0_value as ResourceColor | LinearGradient | undefined))
        if (this._showSteps_flag)
            component.showSteps((this._showSteps0_value as boolean | undefined))
        if (this._trackThickness_flag)
            component.trackThickness((this._trackThickness0_value as Length | undefined))
        if (this._onChange_flag)
            component.onChange((this._onChange0_value as ((value: number,mode: SliderChangeMode) => void) | undefined))
        if (this._blockBorderColor_flag)
            component.blockBorderColor((this._blockBorderColor0_value as ResourceColor | undefined))
        if (this._blockBorderWidth_flag)
            component.blockBorderWidth((this._blockBorderWidth0_value as Length | undefined))
        if (this._stepColor_flag)
            component.stepColor((this._stepColor0_value as ResourceColor | undefined))
        if (this._trackBorderRadius_flag)
            component.trackBorderRadius((this._trackBorderRadius0_value as Length | undefined))
        if (this._selectedBorderRadius_flag)
            component.selectedBorderRadius((this._selectedBorderRadius0_value as Dimension | undefined))
        if (this._blockSize_flag)
            component.blockSize((this._blockSize0_value as SizeOptions | undefined))
        if (this._blockStyle_flag)
            component.blockStyle((this._blockStyle0_value as SliderBlockStyle | undefined))
        if (this._stepSize_flag)
            component.stepSize((this._stepSize0_value as Length | undefined))
        if (this._sliderInteractionMode_flag)
            component.sliderInteractionMode((this._sliderInteractionMode0_value as SliderInteraction | undefined))
        if (this._minResponsiveDistance_flag)
            component.minResponsiveDistance((this._minResponsiveDistance0_value as number | undefined))
        if (this._contentModifier_flag)
            component.contentModifier((this._contentModifier0_value as ContentModifier<SliderConfiguration> | undefined))
        if (this._slideRange_flag)
            component.slideRange((this._slideRange0_value as SlideRange | undefined))
        if (this._digitalCrownSensitivity_flag)
            component.digitalCrownSensitivity((this._digitalCrownSensitivity0_value as CrownSensitivity | undefined))
        if (this._enableHapticFeedback_flag)
            component.enableHapticFeedback((this._enableHapticFeedback0_value as boolean | undefined))
        if (this._showTips_flag)
            component.showTips((this._showTips0_value as boolean | undefined), (this._showTips1_value as ResourceStr | undefined))
    }
    public blockColor(value: ResourceColor | undefined): this {
        this._blockColor_flag = true
        this._blockColor0_value = value
        return this
    }
    public trackColor(value: ResourceColor | LinearGradient | undefined): this {
        this._trackColor_flag = true
        this._trackColor0_value = value
        return this
    }
    public selectedColor(value: ResourceColor | LinearGradient | undefined): this {
        this._selectedColor_flag = true
        this._selectedColor0_value = value
        return this
    }
    public showSteps(value: boolean | undefined): this {
        this._showSteps_flag = true
        this._showSteps0_value = value
        return this
    }
    public trackThickness(value: Length | undefined): this {
        this._trackThickness_flag = true
        this._trackThickness0_value = value
        return this
    }
    public onChange(value: ((value: number,mode: SliderChangeMode) => void) | undefined): this {
        this._onChange_flag = true
        this._onChange0_value = value
        return this
    }
    public blockBorderColor(value: ResourceColor | undefined): this {
        this._blockBorderColor_flag = true
        this._blockBorderColor0_value = value
        return this
    }
    public blockBorderWidth(value: Length | undefined): this {
        this._blockBorderWidth_flag = true
        this._blockBorderWidth0_value = value
        return this
    }
    public stepColor(value: ResourceColor | undefined): this {
        this._stepColor_flag = true
        this._stepColor0_value = value
        return this
    }
    public trackBorderRadius(value: Length | undefined): this {
        this._trackBorderRadius_flag = true
        this._trackBorderRadius0_value = value
        return this
    }
    public selectedBorderRadius(value: Dimension | undefined): this {
        this._selectedBorderRadius_flag = true
        this._selectedBorderRadius0_value = value
        return this
    }
    public blockSize(value: SizeOptions | undefined): this {
        this._blockSize_flag = true
        this._blockSize0_value = value
        return this
    }
    public blockStyle(value: SliderBlockStyle | undefined): this {
        this._blockStyle_flag = true
        this._blockStyle0_value = value
        return this
    }
    public stepSize(value: Length | undefined): this {
        this._stepSize_flag = true
        this._stepSize0_value = value
        return this
    }
    public sliderInteractionMode(value: SliderInteraction | undefined): this {
        this._sliderInteractionMode_flag = true
        this._sliderInteractionMode0_value = value
        return this
    }
    public minResponsiveDistance(value: number | undefined): this {
        this._minResponsiveDistance_flag = true
        this._minResponsiveDistance0_value = value
        return this
    }
    public contentModifier(value: ContentModifier<SliderConfiguration> | undefined): this {
        this._contentModifier_flag = true
        this._contentModifier0_value = value
        return this
    }
    public slideRange(value: SlideRange | undefined): this {
        this._slideRange_flag = true
        this._slideRange0_value = value
        return this
    }
    public digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        this._digitalCrownSensitivity_flag = true
        this._digitalCrownSensitivity0_value = value
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        this._enableHapticFeedback_flag = true
        this._enableHapticFeedback0_value = value
        return this
    }
    public showTips(value: boolean | undefined, content?: ResourceStr): this {
        this._showTips_flag = true
        this._showTips0_value = value
        this._showTips1_value = content
        return this
    }
    public _onChangeEvent_value(callback_: ((value: number | undefined) => void)): void {
    }
    public attributeModifier(value: AttributeModifier<SliderAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class SlideRange_serializer {
    public static write(buffer: SerializerBase, value: SlideRange): void {
        let valueSerializer : SerializerBase = buffer
        const value_from  = value.from
        let value_from_type : int32 = RuntimeType.UNDEFINED
        value_from_type = runtimeType(value_from)
        valueSerializer.writeInt8((value_from_type).toChar())
        if ((value_from_type) != (RuntimeType.UNDEFINED)) {
            const value_from_value  = value_from!
            valueSerializer.writeNumber(value_from_value)
        }
        const value_to  = value.to
        let value_to_type : int32 = RuntimeType.UNDEFINED
        value_to_type = runtimeType(value_to)
        valueSerializer.writeInt8((value_to_type).toChar())
        if ((value_to_type) != (RuntimeType.UNDEFINED)) {
            const value_to_value  = value_to!
            valueSerializer.writeNumber(value_to_value)
        }
    }
    public static read(buffer: DeserializerBase): SlideRange {
        let valueDeserializer : DeserializerBase = buffer
        const from_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let from_buf : number | undefined
        if ((from_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            from_buf = (valueDeserializer.readNumber() as number)
        }
        const from_result : number | undefined = from_buf
        const to_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let to_buf : number | undefined
        if ((to_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            to_buf = (valueDeserializer.readNumber() as number)
        }
        const to_result : number | undefined = to_buf
        let value : SlideRange = ({from: from_result, to: to_result} as SlideRange)
        return value
    }
}
export class SliderConfiguration_serializer {
    public static write(buffer: SerializerBase, value: SliderConfiguration): void {
        let valueSerializer : SerializerBase = buffer
        const value_enabled  = value.enabled
        valueSerializer.writeBoolean(value_enabled)
        const value_contentModifier  = value.contentModifier
        valueSerializer.holdAndWriteObject(value_contentModifier)
        const value_value  = value.value
        valueSerializer.writeNumber(value_value)
        const value_min  = value.min
        valueSerializer.writeNumber(value_min)
        const value_max  = value.max
        valueSerializer.writeNumber(value_max)
        const value_step  = value.step
        valueSerializer.writeNumber(value_step)
        const value_triggerChange  = value.triggerChange
        valueSerializer.holdAndWriteCallback(value_triggerChange)
    }
    public static read(buffer: DeserializerBase): SliderConfiguration {
        let valueDeserializer : DeserializerBase = buffer
        const enabled_result : boolean = valueDeserializer.readBoolean()
        const contentModifier_result : ContentModifier<SliderConfiguration> = (valueDeserializer.readObject() as ContentModifier<SliderConfiguration>)
        const value_result : number = (valueDeserializer.readNumber() as number)
        const min_result : number = (valueDeserializer.readNumber() as number)
        const max_result : number = (valueDeserializer.readNumber() as number)
        const step_result : number = (valueDeserializer.readNumber() as number)
        const triggerChange_buf_resource : CallbackResource = valueDeserializer.readCallbackResource()
        const triggerChange_buf_call : KPointer = valueDeserializer.readPointer()
        const triggerChange_buf_callSync : KPointer = valueDeserializer.readPointer()
        const triggerChange_result : SliderTriggerChangeCallback = (value: number, mode: SliderChangeMode):void => { 
    const triggerChange_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    triggerChange_buf_argsSerializer.writeInt32(triggerChange_buf_resource.resourceId);
    triggerChange_buf_argsSerializer.writePointer(triggerChange_buf_call);
    triggerChange_buf_argsSerializer.writePointer(triggerChange_buf_callSync);
    triggerChange_buf_argsSerializer.writeNumber(value);
    triggerChange_buf_argsSerializer.writeInt32(TypeChecker.SliderChangeMode_ToNumeric(mode));
    InteropNativeModule._CallCallback(711649376, triggerChange_buf_argsSerializer.asBuffer(), triggerChange_buf_argsSerializer.length());
    triggerChange_buf_argsSerializer.release();
    return; }
        let value : SliderConfiguration = ({enabled: enabled_result, contentModifier: contentModifier_result, value: value_result, min: min_result, max: max_result, step: step_result, triggerChange: triggerChange_result} as SliderConfiguration)
        return value
    }
}
export class SliderOptions_serializer {
    public static write(buffer: SerializerBase, value: SliderOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_value  = value.value
        let value_value_type : int32 = RuntimeType.UNDEFINED
        value_value_type = runtimeType(value_value)
        valueSerializer.writeInt8((value_value_type).toChar())
        if ((value_value_type) != (RuntimeType.UNDEFINED)) {
            const value_value_value  = value_value!
            valueSerializer.writeNumber(value_value_value)
        }
        const value_min  = value.min
        let value_min_type : int32 = RuntimeType.UNDEFINED
        value_min_type = runtimeType(value_min)
        valueSerializer.writeInt8((value_min_type).toChar())
        if ((value_min_type) != (RuntimeType.UNDEFINED)) {
            const value_min_value  = value_min!
            valueSerializer.writeNumber(value_min_value)
        }
        const value_max  = value.max
        let value_max_type : int32 = RuntimeType.UNDEFINED
        value_max_type = runtimeType(value_max)
        valueSerializer.writeInt8((value_max_type).toChar())
        if ((value_max_type) != (RuntimeType.UNDEFINED)) {
            const value_max_value  = value_max!
            valueSerializer.writeNumber(value_max_value)
        }
        const value_step  = value.step
        let value_step_type : int32 = RuntimeType.UNDEFINED
        value_step_type = runtimeType(value_step)
        valueSerializer.writeInt8((value_step_type).toChar())
        if ((value_step_type) != (RuntimeType.UNDEFINED)) {
            const value_step_value  = value_step!
            valueSerializer.writeNumber(value_step_value)
        }
        const value_style  = value.style
        let value_style_type : int32 = RuntimeType.UNDEFINED
        value_style_type = runtimeType(value_style)
        valueSerializer.writeInt8((value_style_type).toChar())
        if ((value_style_type) != (RuntimeType.UNDEFINED)) {
            const value_style_value  = (value_style as SliderStyle)
            valueSerializer.writeInt32(TypeChecker.SliderStyle_ToNumeric(value_style_value))
        }
        const value_direction  = value.direction
        let value_direction_type : int32 = RuntimeType.UNDEFINED
        value_direction_type = runtimeType(value_direction)
        valueSerializer.writeInt8((value_direction_type).toChar())
        if ((value_direction_type) != (RuntimeType.UNDEFINED)) {
            const value_direction_value  = (value_direction as Axis)
            valueSerializer.writeInt32(TypeChecker.Axis_ToNumeric(value_direction_value))
        }
        const value_reverse  = value.reverse
        let value_reverse_type : int32 = RuntimeType.UNDEFINED
        value_reverse_type = runtimeType(value_reverse)
        valueSerializer.writeInt8((value_reverse_type).toChar())
        if ((value_reverse_type) != (RuntimeType.UNDEFINED)) {
            const value_reverse_value  = value_reverse!
            valueSerializer.writeBoolean(value_reverse_value)
        }
    }
    public static read(buffer: DeserializerBase): SliderOptions {
        let valueDeserializer : DeserializerBase = buffer
        const value_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let value_buf : number | undefined
        if ((value_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            value_buf = (valueDeserializer.readNumber() as number)
        }
        const value_result : number | undefined = value_buf
        const min_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let min_buf : number | undefined
        if ((min_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            min_buf = (valueDeserializer.readNumber() as number)
        }
        const min_result : number | undefined = min_buf
        const max_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let max_buf : number | undefined
        if ((max_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            max_buf = (valueDeserializer.readNumber() as number)
        }
        const max_result : number | undefined = max_buf
        const step_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let step_buf : number | undefined
        if ((step_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            step_buf = (valueDeserializer.readNumber() as number)
        }
        const step_result : number | undefined = step_buf
        const style_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let style_buf : SliderStyle | undefined
        if ((style_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            style_buf = TypeChecker.SliderStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const style_result : SliderStyle | undefined = style_buf
        const direction_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let direction_buf : Axis | undefined
        if ((direction_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            direction_buf = TypeChecker.Axis_FromNumeric(valueDeserializer.readInt32())
        }
        const direction_result : Axis | undefined = direction_buf
        const reverse_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let reverse_buf : boolean | undefined
        if ((reverse_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            reverse_buf = valueDeserializer.readBoolean()
        }
        const reverse_result : boolean | undefined = reverse_buf
        let value : SliderOptions = ({value: value_result, min: min_result, max: max_result, step: step_result, style: style_result, direction: direction_result, reverse: reverse_result} as SliderOptions)
        return value
    }
}
export class SliderBlockStyle_serializer {
    public static write(buffer: SerializerBase, value: SliderBlockStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_type  = value.type
        valueSerializer.writeInt32(TypeChecker.SliderBlockType_ToNumeric(value_type))
        const value_image  = value.image
        let value_image_type : int32 = RuntimeType.UNDEFINED
        value_image_type = runtimeType(value_image)
        valueSerializer.writeInt8((value_image_type).toChar())
        if ((value_image_type) != (RuntimeType.UNDEFINED)) {
            const value_image_value  = value_image!
            let value_image_value_type : int32 = RuntimeType.UNDEFINED
            value_image_value_type = runtimeType(value_image_value)
            if (RuntimeType.STRING == value_image_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_image_value_0  = value_image_value as string
                valueSerializer.writeString(value_image_value_0)
            }
            else if (RuntimeType.OBJECT == value_image_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_image_value_1  = value_image_value as Resource
                Resource_serializer.write(valueSerializer, value_image_value_1)
            }
        }
    }
    public static read(buffer: DeserializerBase): SliderBlockStyle {
        let valueDeserializer : DeserializerBase = buffer
        const type_result : SliderBlockType = TypeChecker.SliderBlockType_FromNumeric(valueDeserializer.readInt32())
        const image_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let image_buf : ResourceStr | undefined
        if ((image_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const image_buf__selector : int32 = valueDeserializer.readInt8()
            let image_buf_ : string | Resource | undefined
            if (image_buf__selector == (0).toChar()) {
                image_buf_ = (valueDeserializer.readString() as string)
            }
            else if (image_buf__selector == (1).toChar()) {
                image_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for image_buf_ has to be chosen through deserialisation.")
            }
            image_buf = (image_buf_ as string | Resource)
        }
        const image_result : ResourceStr | undefined = image_buf
        let value : SliderBlockStyle = ({type: type_result, image: image_result} as SliderBlockStyle)
        return value
    }
}

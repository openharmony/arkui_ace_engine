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
import { LinearGradient_serializer, LinearGradient } from "./dataPanel"
import { SizeOptions_serializer, ResourceColor, Length, Dimension, SizeOptions, ResourceStr } from "./units"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, CommonConfiguration, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { Color, CrownSensitivity, Axis } from "./enums"
import { ContentModifier, AttributeModifier, hookSliderContentModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
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
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            SliderOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._SliderInterface_setSliderOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    blockColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SliderAttribute_blockColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    trackColorAttribute(value: ResourceColor | LinearGradient | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if ((TypeChecker.isColor(value_value)) || (RuntimeType.NUMBER == value_value_type) || (RuntimeType.STRING == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as ResourceColor
                let value_value_0_type : int32 = RuntimeType.UNDEFINED
                value_value_0_type = runtimeType(value_value_0)
                if (TypeChecker.isColor(value_value_0)) {
                    thisSerializer.writeInt8(0)
                    const value_value_0_0  = value_value_0 as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0_0))
                }
                else if (RuntimeType.NUMBER == value_value_0_type) {
                    thisSerializer.writeInt8(1)
                    const value_value_0_1  = value_value_0 as number
                    thisSerializer.writeNumber(value_value_0_1)
                }
                else if (RuntimeType.STRING == value_value_0_type) {
                    thisSerializer.writeInt8(2)
                    const value_value_0_2  = value_value_0 as string
                    thisSerializer.writeString(value_value_0_2)
                }
                else if (RuntimeType.OBJECT == value_value_0_type) {
                    thisSerializer.writeInt8(3)
                    const value_value_0_3  = value_value_0 as Resource
                    Resource_serializer.write(thisSerializer, value_value_0_3)
                }
            }
            else if (TypeChecker.isLinearGradient(value_value)) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as LinearGradient
                LinearGradient_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SliderAttribute_trackColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedColorAttribute(value: ResourceColor | LinearGradient | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if ((TypeChecker.isColor(value_value)) || (RuntimeType.NUMBER == value_value_type) || (RuntimeType.STRING == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as ResourceColor
                let value_value_0_type : int32 = RuntimeType.UNDEFINED
                value_value_0_type = runtimeType(value_value_0)
                if (TypeChecker.isColor(value_value_0)) {
                    thisSerializer.writeInt8(0)
                    const value_value_0_0  = value_value_0 as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0_0))
                }
                else if (RuntimeType.NUMBER == value_value_0_type) {
                    thisSerializer.writeInt8(1)
                    const value_value_0_1  = value_value_0 as number
                    thisSerializer.writeNumber(value_value_0_1)
                }
                else if (RuntimeType.STRING == value_value_0_type) {
                    thisSerializer.writeInt8(2)
                    const value_value_0_2  = value_value_0 as string
                    thisSerializer.writeString(value_value_0_2)
                }
                else if (RuntimeType.OBJECT == value_value_0_type) {
                    thisSerializer.writeInt8(3)
                    const value_value_0_3  = value_value_0 as Resource
                    Resource_serializer.write(thisSerializer, value_value_0_3)
                }
            }
            else if (TypeChecker.isLinearGradient(value_value)) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as LinearGradient
                LinearGradient_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SliderAttribute_selectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    showStepsAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_showSteps(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    trackThicknessAttribute(value: Length | undefined): void {
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
        ArkUIGeneratedNativeModule._SliderAttribute_trackThickness(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onChangeAttribute(value: ((value: number,mode: SliderChangeMode) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_onChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    blockBorderColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SliderAttribute_blockBorderColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    blockBorderWidthAttribute(value: Length | undefined): void {
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
        ArkUIGeneratedNativeModule._SliderAttribute_blockBorderWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    stepColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SliderAttribute_stepColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    trackBorderRadiusAttribute(value: Length | undefined): void {
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
        ArkUIGeneratedNativeModule._SliderAttribute_trackBorderRadius(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedBorderRadiusAttribute(value: Dimension | undefined): void {
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
        ArkUIGeneratedNativeModule._SliderAttribute_selectedBorderRadius(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    blockSizeAttribute(value: SizeOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            SizeOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_blockSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    blockStyleAttribute(value: SliderBlockStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            SliderBlockStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_blockStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    stepSizeAttribute(value: Length | undefined): void {
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
        ArkUIGeneratedNativeModule._SliderAttribute_stepSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    sliderInteractionModeAttribute(value: SliderInteraction | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as SliderInteraction)
            thisSerializer.writeInt32(TypeChecker.SliderInteraction_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SliderAttribute_sliderInteractionMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    minResponsiveDistanceAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_minResponsiveDistance(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    contentModifierAttribute(value: ContentModifier<SliderConfiguration> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteObject(value_value)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_contentModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    slideRangeAttribute(value: SlideRange | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            SlideRange_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_slideRange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    digitalCrownSensitivityAttribute(value: CrownSensitivity | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as CrownSensitivity)
            thisSerializer.writeInt32(TypeChecker.CrownSensitivity_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SliderAttribute_digitalCrownSensitivity(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableHapticFeedbackAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_enableHapticFeedback(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    showTipsAttribute(value: boolean | undefined, content?: ResourceStr): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        let content_type : int32 = RuntimeType.UNDEFINED
        content_type = runtimeType(content)
        thisSerializer.writeInt8(content_type)
        if ((RuntimeType.UNDEFINED) != (content_type)) {
            const content_value  = content!
            let content_value_type : int32 = RuntimeType.UNDEFINED
            content_value_type = runtimeType(content_value)
            if (RuntimeType.STRING == content_value_type) {
                thisSerializer.writeInt8(0)
                const content_value_0  = content_value as string
                thisSerializer.writeString(content_value_0)
            }
            else if (RuntimeType.OBJECT == content_value_type) {
                thisSerializer.writeInt8(1)
                const content_value_1  = content_value as Resource
                Resource_serializer.write(thisSerializer, content_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SliderAttribute_showTips(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    blockColor(value: ResourceColor | undefined): this
    trackColor(value: ResourceColor | LinearGradient | undefined): this
    selectedColor(value: ResourceColor | LinearGradient | undefined): this
    showSteps(value: boolean | undefined): this
    trackThickness(value: Length | undefined): this
    onChange(value: ((value: number,mode: SliderChangeMode) => void) | undefined): this
    blockBorderColor(value: ResourceColor | undefined): this
    blockBorderWidth(value: Length | undefined): this
    stepColor(value: ResourceColor | undefined): this
    trackBorderRadius(value: Length | undefined): this
    selectedBorderRadius(value: Dimension | undefined): this
    blockSize(value: SizeOptions | undefined): this
    blockStyle(value: SliderBlockStyle | undefined): this
    stepSize(value: Length | undefined): this
    sliderInteractionMode(value: SliderInteraction | undefined): this
    minResponsiveDistance(value: number | undefined): this
    contentModifier(value: ContentModifier<SliderConfiguration> | undefined): this
    slideRange(value: SlideRange | undefined): this
    digitalCrownSensitivity(value: CrownSensitivity | undefined): this
    enableHapticFeedback(value: boolean | undefined): this
    showTips(value: boolean | undefined, content?: ResourceStr): this
    attributeModifier(value: AttributeModifier<SliderAttribute> | AttributeModifier<CommonMethod> | undefined): this
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
            this.getPeer()?.blockColorAttribute(value_casted)
            return this
        }
        return this
    }
    public trackColor(value: ResourceColor | LinearGradient | undefined): this {
        if (this.checkPriority("trackColor")) {
            const value_casted = value as (ResourceColor | LinearGradient | undefined)
            this.getPeer()?.trackColorAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedColor(value: ResourceColor | LinearGradient | undefined): this {
        if (this.checkPriority("selectedColor")) {
            const value_casted = value as (ResourceColor | LinearGradient | undefined)
            this.getPeer()?.selectedColorAttribute(value_casted)
            return this
        }
        return this
    }
    public showSteps(value: boolean | undefined): this {
        if (this.checkPriority("showSteps")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.showStepsAttribute(value_casted)
            return this
        }
        return this
    }
    public trackThickness(value: Length | undefined): this {
        if (this.checkPriority("trackThickness")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.trackThicknessAttribute(value_casted)
            return this
        }
        return this
    }
    public onChange(value: ((value: number,mode: SliderChangeMode) => void) | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((value: number,mode: SliderChangeMode) => void) | undefined)
            this.getPeer()?.onChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public blockBorderColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("blockBorderColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.blockBorderColorAttribute(value_casted)
            return this
        }
        return this
    }
    public blockBorderWidth(value: Length | undefined): this {
        if (this.checkPriority("blockBorderWidth")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.blockBorderWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public stepColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("stepColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.stepColorAttribute(value_casted)
            return this
        }
        return this
    }
    public trackBorderRadius(value: Length | undefined): this {
        if (this.checkPriority("trackBorderRadius")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.trackBorderRadiusAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedBorderRadius(value: Dimension | undefined): this {
        if (this.checkPriority("selectedBorderRadius")) {
            const value_casted = value as (Dimension | undefined)
            this.getPeer()?.selectedBorderRadiusAttribute(value_casted)
            return this
        }
        return this
    }
    public blockSize(value: SizeOptions | undefined): this {
        if (this.checkPriority("blockSize")) {
            const value_casted = value as (SizeOptions | undefined)
            this.getPeer()?.blockSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public blockStyle(value: SliderBlockStyle | undefined): this {
        if (this.checkPriority("blockStyle")) {
            const value_casted = value as (SliderBlockStyle | undefined)
            this.getPeer()?.blockStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public stepSize(value: Length | undefined): this {
        if (this.checkPriority("stepSize")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.stepSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public sliderInteractionMode(value: SliderInteraction | undefined): this {
        if (this.checkPriority("sliderInteractionMode")) {
            const value_casted = value as (SliderInteraction | undefined)
            this.getPeer()?.sliderInteractionModeAttribute(value_casted)
            return this
        }
        return this
    }
    public minResponsiveDistance(value: number | undefined): this {
        if (this.checkPriority("minResponsiveDistance")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.minResponsiveDistanceAttribute(value_casted)
            return this
        }
        return this
    }
    public contentModifier(value: ContentModifier<SliderConfiguration> | undefined): this {
        if (this.checkPriority("contentModifier")) {
            hookSliderContentModifier(this, value)
        }
        return this
    }
    public slideRange(value: SlideRange | undefined): this {
        if (this.checkPriority("slideRange")) {
            const value_casted = value as (SlideRange | undefined)
            this.getPeer()?.slideRangeAttribute(value_casted)
            return this
        }
        return this
    }
    public digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        if (this.checkPriority("digitalCrownSensitivity")) {
            const value_casted = value as (CrownSensitivity | undefined)
            this.getPeer()?.digitalCrownSensitivityAttribute(value_casted)
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
    public showTips(value: boolean | undefined, content?: ResourceStr): this {
        if (this.checkPriority("showTips")) {
            const value_casted = value as (boolean | undefined)
            const content_casted = content as (ResourceStr | undefined)
            this.getPeer()?.showTipsAttribute(value_casted, content_casted)
            return this
        }
        return this
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
        if (modifier!.isUpdater)
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
@memo
@BuilderLambda("SliderImpl")
export function Slider(
    options?: SliderOptions | undefined,
    @memo
    content_?: () => void,
): SliderAttribute {
    throw new Error("Not implemented")
}

@memo
export function SliderImpl(
    @memo
    style: ((attributes: SliderAttribute) => void) | undefined,
    options?: SliderOptions | undefined,
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

export class SlideRange_serializer {
    public static write(buffer: SerializerBase, value: SlideRange): void {
        let valueSerializer : SerializerBase = buffer
        const value_from  = value.from
        let value_from_type : int32 = RuntimeType.UNDEFINED
        value_from_type = runtimeType(value_from)
        valueSerializer.writeInt8(value_from_type)
        if ((RuntimeType.UNDEFINED) != (value_from_type)) {
            const value_from_value  = value_from!
            valueSerializer.writeNumber(value_from_value)
        }
        const value_to  = value.to
        let value_to_type : int32 = RuntimeType.UNDEFINED
        value_to_type = runtimeType(value_to)
        valueSerializer.writeInt8(value_to_type)
        if ((RuntimeType.UNDEFINED) != (value_to_type)) {
            const value_to_value  = value_to!
            valueSerializer.writeNumber(value_to_value)
        }
    }
    public static read(buffer: DeserializerBase): SlideRange {
        let valueDeserializer : DeserializerBase = buffer
        const from_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let from_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (from_buf_runtimeType))
        {
            from_buf = (valueDeserializer.readNumber() as number)
        }
        const from_result : number | undefined = from_buf
        const to_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let to_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (to_buf_runtimeType))
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
        valueSerializer.writeInt8(value_value_type)
        if ((RuntimeType.UNDEFINED) != (value_value_type)) {
            const value_value_value  = value_value!
            valueSerializer.writeNumber(value_value_value)
        }
        const value_min  = value.min
        let value_min_type : int32 = RuntimeType.UNDEFINED
        value_min_type = runtimeType(value_min)
        valueSerializer.writeInt8(value_min_type)
        if ((RuntimeType.UNDEFINED) != (value_min_type)) {
            const value_min_value  = value_min!
            valueSerializer.writeNumber(value_min_value)
        }
        const value_max  = value.max
        let value_max_type : int32 = RuntimeType.UNDEFINED
        value_max_type = runtimeType(value_max)
        valueSerializer.writeInt8(value_max_type)
        if ((RuntimeType.UNDEFINED) != (value_max_type)) {
            const value_max_value  = value_max!
            valueSerializer.writeNumber(value_max_value)
        }
        const value_step  = value.step
        let value_step_type : int32 = RuntimeType.UNDEFINED
        value_step_type = runtimeType(value_step)
        valueSerializer.writeInt8(value_step_type)
        if ((RuntimeType.UNDEFINED) != (value_step_type)) {
            const value_step_value  = value_step!
            valueSerializer.writeNumber(value_step_value)
        }
        const value_style  = value.style
        let value_style_type : int32 = RuntimeType.UNDEFINED
        value_style_type = runtimeType(value_style)
        valueSerializer.writeInt8(value_style_type)
        if ((RuntimeType.UNDEFINED) != (value_style_type)) {
            const value_style_value  = (value_style as SliderStyle)
            valueSerializer.writeInt32(TypeChecker.SliderStyle_ToNumeric(value_style_value))
        }
        const value_direction  = value.direction
        let value_direction_type : int32 = RuntimeType.UNDEFINED
        value_direction_type = runtimeType(value_direction)
        valueSerializer.writeInt8(value_direction_type)
        if ((RuntimeType.UNDEFINED) != (value_direction_type)) {
            const value_direction_value  = (value_direction as Axis)
            valueSerializer.writeInt32(TypeChecker.Axis_ToNumeric(value_direction_value))
        }
        const value_reverse  = value.reverse
        let value_reverse_type : int32 = RuntimeType.UNDEFINED
        value_reverse_type = runtimeType(value_reverse)
        valueSerializer.writeInt8(value_reverse_type)
        if ((RuntimeType.UNDEFINED) != (value_reverse_type)) {
            const value_reverse_value  = value_reverse!
            valueSerializer.writeBoolean(value_reverse_value)
        }
    }
    public static read(buffer: DeserializerBase): SliderOptions {
        let valueDeserializer : DeserializerBase = buffer
        const value_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let value_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (value_buf_runtimeType))
        {
            value_buf = (valueDeserializer.readNumber() as number)
        }
        const value_result : number | undefined = value_buf
        const min_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let min_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (min_buf_runtimeType))
        {
            min_buf = (valueDeserializer.readNumber() as number)
        }
        const min_result : number | undefined = min_buf
        const max_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let max_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (max_buf_runtimeType))
        {
            max_buf = (valueDeserializer.readNumber() as number)
        }
        const max_result : number | undefined = max_buf
        const step_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let step_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (step_buf_runtimeType))
        {
            step_buf = (valueDeserializer.readNumber() as number)
        }
        const step_result : number | undefined = step_buf
        const style_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let style_buf : SliderStyle | undefined
        if ((RuntimeType.UNDEFINED) != (style_buf_runtimeType))
        {
            style_buf = TypeChecker.SliderStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const style_result : SliderStyle | undefined = style_buf
        const direction_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let direction_buf : Axis | undefined
        if ((RuntimeType.UNDEFINED) != (direction_buf_runtimeType))
        {
            direction_buf = TypeChecker.Axis_FromNumeric(valueDeserializer.readInt32())
        }
        const direction_result : Axis | undefined = direction_buf
        const reverse_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let reverse_buf : boolean | undefined
        if ((RuntimeType.UNDEFINED) != (reverse_buf_runtimeType))
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
        valueSerializer.writeInt8(value_image_type)
        if ((RuntimeType.UNDEFINED) != (value_image_type)) {
            const value_image_value  = value_image!
            let value_image_value_type : int32 = RuntimeType.UNDEFINED
            value_image_value_type = runtimeType(value_image_value)
            if (RuntimeType.STRING == value_image_value_type) {
                valueSerializer.writeInt8(0)
                const value_image_value_0  = value_image_value as string
                valueSerializer.writeString(value_image_value_0)
            }
            else if (RuntimeType.OBJECT == value_image_value_type) {
                valueSerializer.writeInt8(1)
                const value_image_value_1  = value_image_value as Resource
                Resource_serializer.write(valueSerializer, value_image_value_1)
            }
        }
    }
    public static read(buffer: DeserializerBase): SliderBlockStyle {
        let valueDeserializer : DeserializerBase = buffer
        const type_result : SliderBlockType = TypeChecker.SliderBlockType_FromNumeric(valueDeserializer.readInt32())
        const image_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let image_buf : ResourceStr | undefined
        if ((RuntimeType.UNDEFINED) != (image_buf_runtimeType))
        {
            const image_buf__selector : int32 = valueDeserializer.readInt8()
            let image_buf_ : string | Resource | undefined
            if (image_buf__selector == 0) {
                image_buf_ = (valueDeserializer.readString() as string)
            }
            else if (image_buf__selector == 1) {
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

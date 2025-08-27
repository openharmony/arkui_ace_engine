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

import { int32, int64, float32 } from "@koalaui/common"
import { nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer } from "@koalaui/interop"
import { Serializer } from "./peers/Serializer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { ResourceColor, Length, Dimension, SizeOptions, ResourceStr, PX, VP, FP, LPX, Percentage } from "./units"
import { LinearGradient } from "./dataPanel"
import { ContentModifier, CommonConfiguration } from "./arkui-wrapper-builder"
import { CrownSensitivity, Color, Axis } from "./enums"
import { Callback_Number_Void } from "./alphabetIndexer"
import { Resource } from "global.resource"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"

export class ArkSliderPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkSliderPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Slider_construct(peerId, flags)
        const _peer  = new ArkSliderPeer(_peerPtr, peerId, "Slider", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setSliderOptionsAttribute(options?: SliderOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeSliderOptions(options_value)
        }
        ArkUIGeneratedNativeModule._SliderInterface_setSliderOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    blockColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SliderAttribute_blockColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    trackColorAttribute(value: ResourceColor | LinearGradient | undefined): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value = value!
            let value_value_type: int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isLinearGradient(value_value)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1 = value_value as LinearGradient
                thisSerializer.writeLinearGradient(value_value_1)
            }
            else if ((TypeChecker.isColor(value_value)) || (RuntimeType.NUMBER == value_value_type) || (RuntimeType.STRING == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0 = value_value as ResourceColor
                let value_value_0_type: int32 = RuntimeType.UNDEFINED
                value_value_0_type = runtimeType(value_value_0)
                if (TypeChecker.isColor(value_value_0)) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_value_0_0 = value_value_0 as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0_0))
                }
                else if (RuntimeType.NUMBER == value_value_0_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_value_0_1 = value_value_0 as number
                    thisSerializer.writeNumber(value_value_0_1)
                }
                else if (RuntimeType.STRING == value_value_0_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_value_0_2 = value_value_0 as string
                    thisSerializer.writeString(value_value_0_2)
                }
                else if (RuntimeType.OBJECT == value_value_0_type) {
                    thisSerializer.writeInt8(3 as int32)
                    const value_value_0_3 = value_value_0 as Resource
                    thisSerializer.writeResource(value_value_0_3)
                }
            }
        }
        ArkUIGeneratedNativeModule._SliderAttribute_trackColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedColor0Attribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SliderAttribute_selectedColor0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedColor1Attribute(value: ResourceColor | LinearGradient | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isLinearGradient(value_value)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as LinearGradient
                thisSerializer.writeLinearGradient(value_value_1)
            }
            else if ((TypeChecker.isColor(value_value)) || (RuntimeType.NUMBER == value_value_type) || (RuntimeType.STRING == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as ResourceColor
                let value_value_0_type : int32 = RuntimeType.UNDEFINED
                value_value_0_type = runtimeType(value_value_0)
                if (TypeChecker.isColor(value_value_0)) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_value_0_0  = value_value_0 as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0_0))
                }
                else if (RuntimeType.NUMBER == value_value_0_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_value_0_1  = value_value_0 as number
                    thisSerializer.writeNumber(value_value_0_1)
                }
                else if (RuntimeType.STRING == value_value_0_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_value_0_2  = value_value_0 as string
                    thisSerializer.writeString(value_value_0_2)
                }
                else if (RuntimeType.OBJECT == value_value_0_type) {
                    thisSerializer.writeInt8(3 as int32)
                    const value_value_0_3  = value_value_0 as Resource
                    thisSerializer.writeResource(value_value_0_3)
                }
            }
        }
        ArkUIGeneratedNativeModule._SliderAttribute_selectedColor1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    minLabelAttribute(value: string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_minLabel(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    maxLabelAttribute(value: string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_maxLabel(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    showStepsAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_showSteps(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    trackThicknessAttribute(value: Length | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_trackThickness(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onChangeAttribute(value: ((value: number,mode: SliderChangeMode) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_onChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    blockBorderColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SliderAttribute_blockBorderColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    blockBorderWidthAttribute(value: Length | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_blockBorderWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    stepColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SliderAttribute_stepColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    trackBorderRadiusAttribute(value: Length | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_trackBorderRadius(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedBorderRadiusAttribute(value: Dimension | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_selectedBorderRadius(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    blockSizeAttribute(value: SizeOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeSizeOptions(value_value)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_blockSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    blockStyleAttribute(value: SliderBlockStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeSliderBlockStyle(value_value)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_blockStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    stepSizeAttribute(value: Length | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_stepSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    sliderInteractionModeAttribute(value: SliderInteraction | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as SliderInteraction)
            thisSerializer.writeInt32(TypeChecker.SliderInteraction_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SliderAttribute_sliderInteractionMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    minResponsiveDistanceAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_minResponsiveDistance(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    contentModifierAttribute(value: ContentModifier | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteObject(value_value)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_contentModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    slideRangeAttribute(value: SlideRange | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeSlideRange(value_value)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_slideRange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    digitalCrownSensitivityAttribute(value: CrownSensitivity | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as CrownSensitivity)
            thisSerializer.writeInt32(TypeChecker.CrownSensitivity_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SliderAttribute_digitalCrownSensitivity(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SliderAttribute_enableHapticFeedback(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    showTipsAttribute(value: boolean | undefined, content?:  ResourceStr | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        let content_type : int32 = RuntimeType.UNDEFINED
        content_type = runtimeType(content)
        thisSerializer.writeInt8(content_type as int32)
        if ((RuntimeType.UNDEFINED) != (content_type)) {
            const content_value  = content!
            let content_value_type : int32 = RuntimeType.UNDEFINED
            content_value_type = runtimeType(content_value)
            if (RuntimeType.STRING == content_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const content_value_0  = content_value as string
                thisSerializer.writeString(content_value_0)
            }
            else if (RuntimeType.OBJECT == content_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const content_value_1  = content_value as Resource
                thisSerializer.writeResource(content_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SliderAttribute_showTips(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_valueAttribute(callback: ((index: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._SliderAttribute__onChangeEvent_value(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    value?: number;
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
    shape?: string;
}
export type SliderTriggerChangeCallback = (value: number, mode: SliderChangeMode) => void;
export interface SliderConfiguration extends CommonConfiguration {
    value: number;
    min: number;
    max: number;
    step: number;
    triggerChange: SliderTriggerChangeCallback;
}
export type SliderInterface = (options?: SliderOptions) => SliderAttribute;
export type Callback_Number_SliderChangeMode_Void = (value: number, mode: SliderChangeMode) => void;
export interface SliderAttribute extends CommonMethod {
    blockColor(value: ResourceColor | undefined): this
    trackColor(value: ResourceColor | LinearGradient | undefined): this
    selectedColor(value: ResourceColor | LinearGradient | undefined): this
    minLabel(value: string | undefined): this
    maxLabel(value: string | undefined): this
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
    contentModifier(value: ContentModifier | undefined): this
    slideRange(value: SlideRange | undefined): this
    digitalCrownSensitivity(value: CrownSensitivity | undefined): this
    enableHapticFeedback(value: boolean | undefined): this
    showTips(value: boolean | undefined, content?: ResourceStr | undefined): this
    _onChangeEvent_value(callback: ((index: number) => void)): void
}
export class ArkSliderStyle extends ArkCommonMethodStyle implements SliderAttribute {
    blockColor_value?: ResourceColor | undefined
    trackColor_value?: ResourceColor | LinearGradient | undefined
    selectedColor_value?: ResourceColor | undefined
    minLabel_value?: string | undefined
    maxLabel_value?: string | undefined
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
    contentModifier_value?: ContentModifier | undefined
    slideRange_value?: SlideRange | undefined
    digitalCrownSensitivity_value?: CrownSensitivity | undefined
    enableHapticFeedback_value?: boolean | undefined
    public blockColor(value: ResourceColor | undefined): this {
        return this
    }
    public trackColor(value: ResourceColor | LinearGradient | undefined): this {
        return this
    }
    public selectedColor(value: ResourceColor | LinearGradient | undefined): this {
        return this
    }
    public minLabel(value: string | undefined): this {
        return this
    }
    public maxLabel(value: string | undefined): this {
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
    public contentModifier(value: ContentModifier | undefined): this {
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
    public showTips(value: boolean | undefined, content?: ResourceStr | undefined): this {
        return this
    }
    public _onChangeEvent_value(callback: ((index: number) => void)): void {
        throw new Error("Unimplmented")
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
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ResourceColor | undefined)
                this.getPeer()?.selectedColor1Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ResourceColor | LinearGradient | undefined)
                this.getPeer()?.selectedColor1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public minLabel(value: string | undefined): this {
        if (this.checkPriority("minLabel")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.minLabelAttribute(value_casted)
            return this
        }
        return this
    }
    public maxLabel(value: string | undefined): this {
        if (this.checkPriority("maxLabel")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.maxLabelAttribute(value_casted)
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
    public contentModifier(value: ContentModifier | undefined): this {
        if (this.checkPriority("contentModifier")) {
            const value_casted = value as (ContentModifier | undefined)
            this.getPeer()?.contentModifierAttribute(value_casted)
            return this
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
    public showTips(value: boolean | undefined, content?: ResourceStr | undefined): this {
        if (this.checkPriority("showTips")) {
            const value_casted = value as (boolean | undefined)
            const content_casted = content as (ResourceStr | undefined)
            this.getPeer()?.showTipsAttribute(value_casted, content_casted)
            return this
        }
        return this
    }
    public _onChangeEvent_value(callback: ((index: number) => void)): void {
        if (this.checkPriority("_onChangeEvent_value")) {
            const callback_casted = callback as (((index: number) => void))
            this.getPeer()?._onChangeEvent_valueAttribute(callback_casted)
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
export function Slider(
    /** @memo */
    style: ((attributes: SliderAttribute) => void) | undefined,
    options?: SliderOptions,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkSliderComponent()
    })
    NodeAttach<ArkSliderPeer>((): ArkSliderPeer => ArkSliderPeer.create(receiver), (_: ArkSliderPeer) => {
        receiver.setSliderOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

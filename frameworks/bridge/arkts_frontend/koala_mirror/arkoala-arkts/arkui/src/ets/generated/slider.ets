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
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod } from "./common"
import { ResourceColor, Length, Dimension, SizeOptions, ResourceStr } from "./units"
import { LinearGradient } from "./data_panel"
import { ContentModifier, CommonConfiguration } from "./arkui-wrapper-builder"
import { Callback_Number_Void } from "./alphabet_indexer"
import { Color, Axis } from "./enums"
import { Resource } from "./resource"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { UICommonBase, AttributeModifier } from "./../handwritten"
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
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeSliderOptions(options_value)
        }
        ArkUIGeneratedNativeModule._SliderInterface_setSliderOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    blockColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_blockColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    trackColorAttribute(value: ResourceColor | LinearGradient): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if ((TypeChecker.isColor(value)) || (RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type)) {
            thisSerializer.writeInt8(0)
            const value_0  = value as ResourceColor
            let value_0_type : int32 = RuntimeType.UNDEFINED
            value_0_type = runtimeType(value_0)
            if (TypeChecker.isColor(value_0)) {
                thisSerializer.writeInt8(0)
                const value_0_0  = value_0 as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0_0))
            }
            else if (RuntimeType.NUMBER == value_0_type) {
                thisSerializer.writeInt8(1)
                const value_0_1  = value_0 as number
                thisSerializer.writeNumber(value_0_1)
            }
            else if (RuntimeType.STRING == value_0_type) {
                thisSerializer.writeInt8(2)
                const value_0_2  = value_0 as string
                thisSerializer.writeString(value_0_2)
            }
            else if (RuntimeType.OBJECT == value_0_type) {
                thisSerializer.writeInt8(3)
                const value_0_3  = value_0 as Resource
                thisSerializer.writeResource(value_0_3)
            }
        }
        else if (TypeChecker.isLinearGradient(value)) {
            thisSerializer.writeInt8(1)
            const value_1  = value as LinearGradient
            thisSerializer.writeLinearGradient(value_1)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_trackColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_selectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    minLabelAttribute(value: string): void {
        ArkUIGeneratedNativeModule._SliderAttribute_minLabel(this.peer.ptr, value)
    }
    maxLabelAttribute(value: string): void {
        ArkUIGeneratedNativeModule._SliderAttribute_maxLabel(this.peer.ptr, value)
    }
    showStepsAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._SliderAttribute_showSteps(this.peer.ptr, value ? 1 : 0)
    }
    trackThicknessAttribute(value: Length): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_trackThickness(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onChangeAttribute(value: ((value: number,mode: SliderChangeMode) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._SliderAttribute_onChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    blockBorderColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_blockBorderColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    blockBorderWidthAttribute(value: Length): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_blockBorderWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    stepColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_stepColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    trackBorderRadiusAttribute(value: Length): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_trackBorderRadius(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedBorderRadiusAttribute(value: Dimension): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_selectedBorderRadius(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    blockSizeAttribute(value: SizeOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeSizeOptions(value)
        ArkUIGeneratedNativeModule._SliderAttribute_blockSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    blockStyleAttribute(value: SliderBlockStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeSliderBlockStyle(value)
        ArkUIGeneratedNativeModule._SliderAttribute_blockStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    stepSizeAttribute(value: Length): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_stepSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    sliderInteractionModeAttribute(value: SliderInteraction): void {
        ArkUIGeneratedNativeModule._SliderAttribute_sliderInteractionMode(this.peer.ptr, TypeChecker.SliderInteraction_ToNumeric(value))
    }
    minResponsiveDistanceAttribute(value: number): void {
        ArkUIGeneratedNativeModule._SliderAttribute_minResponsiveDistance(this.peer.ptr, value)
    }
    contentModifierAttribute(value: ContentModifier): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteObject(value)
        ArkUIGeneratedNativeModule._SliderAttribute_contentModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    slideRangeAttribute(value: SlideRange): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeSlideRange(value)
        ArkUIGeneratedNativeModule._SliderAttribute_slideRange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    showTipsAttribute(value: boolean, content?: ResourceStr): void {
        const thisSerializer : Serializer = Serializer.hold()
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
                thisSerializer.writeResource(content_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SliderAttribute_showTips(this.peer.ptr, value ? 1 : 0, thisSerializer.asBuffer(), thisSerializer.length())
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

export type Callback_Number_SliderChangeMode_Void = (value: number, mode: SliderChangeMode) => void;
export interface SliderAttribute extends CommonMethod {
    blockColor(value: ResourceColor): this
    trackColor(value: ResourceColor | LinearGradient): this
    selectedColor(value: ResourceColor): this
    minLabel(value: string): this
    maxLabel(value: string): this
    showSteps(value: boolean): this
    trackThickness(value: Length): this
    onChange(value: ((value: number,mode: SliderChangeMode) => void)): this
    blockBorderColor(value: ResourceColor): this
    blockBorderWidth(value: Length): this
    stepColor(value: ResourceColor): this
    trackBorderRadius(value: Length): this
    selectedBorderRadius(value: Dimension): this
    blockSize(value: SizeOptions): this
    blockStyle(value: SliderBlockStyle): this
    stepSize(value: Length): this
    sliderInteractionMode(value: SliderInteraction): this
    minResponsiveDistance(value: number): this
    contentModifier(value: ContentModifier): this
    slideRange(value: SlideRange): this
    showTips(value: boolean, content?: ResourceStr): this
    _onChangeEvent_value(callback: ((index: number) => void)): void
    attributeModifier(value: AttributeModifier<SliderAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UISliderAttribute extends UICommonMethod {
    @memo
    blockColor(value: ResourceColor): this
    @memo
    trackColor(value: ResourceColor | LinearGradient): this
    @memo
    selectedColor(value: ResourceColor): this
    @memo
    minLabel(value: string): this
    @memo
    maxLabel(value: string): this
    @memo
    showSteps(value: boolean): this
    @memo
    trackThickness(value: Length): this
    @memo
    onChange(value: ((value: number,mode: SliderChangeMode) => void)): this
    @memo
    blockBorderColor(value: ResourceColor): this
    @memo
    blockBorderWidth(value: Length): this
    @memo
    stepColor(value: ResourceColor): this
    @memo
    trackBorderRadius(value: Length): this
    @memo
    selectedBorderRadius(value: Dimension): this
    @memo
    blockSize(value: SizeOptions): this
    @memo
    blockStyle(value: SliderBlockStyle): this
    @memo
    stepSize(value: Length): this
    @memo
    sliderInteractionMode(value: SliderInteraction): this
    @memo
    minResponsiveDistance(value: number): this
    @memo
    contentModifier(value: ContentModifier): this
    @memo
    slideRange(value: SlideRange): this
    @memo
    showTips(value: boolean, content?: ResourceStr): this
    @memo
    _onChangeEvent_value(callback: ((index: number) => void)): void
    @memo
    attributeModifier(value: AttributeModifier<SliderAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkSliderStyle extends ArkCommonMethodStyle implements SliderAttribute {
    blockColor_value?: ResourceColor
    trackColor_value?: ResourceColor | LinearGradient
    selectedColor_value?: ResourceColor
    minLabel_value?: string
    maxLabel_value?: string
    showSteps_value?: boolean
    trackThickness_value?: Length
    onChange_value?: ((value: number,mode: SliderChangeMode) => void)
    blockBorderColor_value?: ResourceColor
    blockBorderWidth_value?: Length
    stepColor_value?: ResourceColor
    trackBorderRadius_value?: Length
    selectedBorderRadius_value?: Dimension
    blockSize_value?: SizeOptions
    blockStyle_value?: SliderBlockStyle
    stepSize_value?: Length
    sliderInteractionMode_value?: SliderInteraction
    minResponsiveDistance_value?: number
    contentModifier_value?: ContentModifier
    slideRange_value?: SlideRange
    public blockColor(value: ResourceColor): this {
        return this
    }
    public trackColor(value: ResourceColor | LinearGradient): this {
        return this
    }
    public selectedColor(value: ResourceColor): this {
        return this
    }
    public minLabel(value: string): this {
        return this
    }
    public maxLabel(value: string): this {
        return this
    }
    public showSteps(value: boolean): this {
        return this
    }
    public trackThickness(value: Length): this {
        return this
    }
    public onChange(value: ((value: number,mode: SliderChangeMode) => void)): this {
        return this
    }
    public blockBorderColor(value: ResourceColor): this {
        return this
    }
    public blockBorderWidth(value: Length): this {
        return this
    }
    public stepColor(value: ResourceColor): this {
        return this
    }
    public trackBorderRadius(value: Length): this {
        return this
    }
    public selectedBorderRadius(value: Dimension): this {
        return this
    }
    public blockSize(value: SizeOptions): this {
        return this
    }
    public blockStyle(value: SliderBlockStyle): this {
        return this
    }
    public stepSize(value: Length): this {
        return this
    }
    public sliderInteractionMode(value: SliderInteraction): this {
        return this
    }
    public minResponsiveDistance(value: number): this {
        return this
    }
    public contentModifier(value: ContentModifier): this {
        return this
    }
    public slideRange(value: SlideRange): this {
        return this
    }
    public showTips(value: boolean, content?: ResourceStr): this {
        return this
    }
    public _onChangeEvent_value(callback: ((index: number) => void)): void {
        throw new Error("Unimplmented")
    }
    public attributeModifier(value: AttributeModifier<SliderAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
@memo_stable
export class ArkSliderComponent extends ArkCommonMethodComponent implements UISliderAttribute {
    getPeer(): ArkSliderPeer {
        return (this.peer as ArkSliderPeer)
    }
    @memo
    public setSliderOptions(options?: SliderOptions): this {
        if (this.checkPriority("setSliderOptions")) {
            const options_casted = options as (SliderOptions | undefined)
            this.getPeer()?.setSliderOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    @memo
    public blockColor(value: ResourceColor): this {
        if (this.checkPriority("blockColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.blockColorAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public trackColor(value: ResourceColor | LinearGradient): this {
        if (this.checkPriority("trackColor")) {
            const value_casted = value as (ResourceColor | LinearGradient)
            this.getPeer()?.trackColorAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public selectedColor(value: ResourceColor): this {
        if (this.checkPriority("selectedColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.selectedColorAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public minLabel(value: string): this {
        if (this.checkPriority("minLabel")) {
            const value_casted = value as (string)
            this.getPeer()?.minLabelAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public maxLabel(value: string): this {
        if (this.checkPriority("maxLabel")) {
            const value_casted = value as (string)
            this.getPeer()?.maxLabelAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public showSteps(value: boolean): this {
        if (this.checkPriority("showSteps")) {
            const value_casted = value as (boolean)
            this.getPeer()?.showStepsAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public trackThickness(value: Length): this {
        if (this.checkPriority("trackThickness")) {
            const value_casted = value as (Length)
            this.getPeer()?.trackThicknessAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onChange(value: ((value: number,mode: SliderChangeMode) => void)): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((value: number,mode: SliderChangeMode) => void))
            this.getPeer()?.onChangeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public blockBorderColor(value: ResourceColor): this {
        if (this.checkPriority("blockBorderColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.blockBorderColorAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public blockBorderWidth(value: Length): this {
        if (this.checkPriority("blockBorderWidth")) {
            const value_casted = value as (Length)
            this.getPeer()?.blockBorderWidthAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public stepColor(value: ResourceColor): this {
        if (this.checkPriority("stepColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.stepColorAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public trackBorderRadius(value: Length): this {
        if (this.checkPriority("trackBorderRadius")) {
            const value_casted = value as (Length)
            this.getPeer()?.trackBorderRadiusAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public selectedBorderRadius(value: Dimension): this {
        if (this.checkPriority("selectedBorderRadius")) {
            const value_casted = value as (Dimension)
            this.getPeer()?.selectedBorderRadiusAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public blockSize(value: SizeOptions): this {
        if (this.checkPriority("blockSize")) {
            const value_casted = value as (SizeOptions)
            this.getPeer()?.blockSizeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public blockStyle(value: SliderBlockStyle): this {
        if (this.checkPriority("blockStyle")) {
            const value_casted = value as (SliderBlockStyle)
            this.getPeer()?.blockStyleAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public stepSize(value: Length): this {
        if (this.checkPriority("stepSize")) {
            const value_casted = value as (Length)
            this.getPeer()?.stepSizeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public sliderInteractionMode(value: SliderInteraction): this {
        if (this.checkPriority("sliderInteractionMode")) {
            const value_casted = value as (SliderInteraction)
            this.getPeer()?.sliderInteractionModeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public minResponsiveDistance(value: number): this {
        if (this.checkPriority("minResponsiveDistance")) {
            const value_casted = value as (number)
            this.getPeer()?.minResponsiveDistanceAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public contentModifier(value: ContentModifier): this {
        if (this.checkPriority("contentModifier")) {
            const value_casted = value as (ContentModifier)
            this.getPeer()?.contentModifierAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public slideRange(value: SlideRange): this {
        if (this.checkPriority("slideRange")) {
            const value_casted = value as (SlideRange)
            this.getPeer()?.slideRangeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public showTips(value: boolean, content?: ResourceStr): this {
        if (this.checkPriority("showTips")) {
            const value_casted = value as (boolean)
            const content_casted = content as (ResourceStr | undefined)
            this.getPeer()?.showTipsAttribute(value_casted, content_casted)
            return this
        }
        return this
    }
    @memo
    public _onChangeEvent_value(callback: ((index: number) => void)): void {
        if (this.checkPriority("_onChangeEvent_value")) {
            const callback_casted = callback as (((index: number) => void))
            this.getPeer()?._onChangeEvent_valueAttribute(callback_casted)
            return
        }
        return
    }
    @memo
    public attributeModifier(value: AttributeModifier<SliderAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
@memo
@BuilderLambda("Slider")
export function Slider(
    options?: SliderOptions,
    @memo
    content_?: () => void,
): SliderAttribute {
    throw new Error("Not implemented")
}

@memo
export function Slider(
    @memo
    style: ((attributes: UISliderAttribute) => void) | undefined,
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
        content_?.()
        receiver.applyAttributesFinish()
    })
}

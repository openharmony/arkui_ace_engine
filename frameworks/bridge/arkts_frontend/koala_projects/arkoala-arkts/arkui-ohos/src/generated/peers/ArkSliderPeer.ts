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

import { int32, float32 } from "@koalaui/common"
import { nullptr, KPointer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { runtimeType, RuntimeType } from "@koalaui/interop"
import { Serializer } from "./Serializer"
import { ComponentBase } from "../../ComponentBase"
import { PeerNode } from "../../PeerNode"
import { ArkUIGeneratedNativeModule } from "#components"
import { ArkCommonMethodPeer, ArkCommonMethodAttributes } from "./ArkCommonPeer"
import { CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, ContentModifier } from "./../../component/common"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage } from "./../../component/units"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey } from "./../../component/enums"
import { LengthMetrics } from "../../Graphics"
import { ResizableOptions } from "./../../component/image"
import { Resource } from "global/resource";
import { Callback_Void } from "./../../component/abilityComponent"
import { FocusBoxStyle, FocusPriority } from "./../../component/focus"
import { CircleShape } from "./../ArkCircleShapeMaterialized"
import { EllipseShape } from "./../ArkEllipseShapeMaterialized"
import { PathShape } from "./../ArkPathShapeMaterialized"
import { RectShape } from "./../ArkRectShapeMaterialized"
import { AttributeModifier } from "./../../component/common" 
import { GestureInfo, BaseGestureEvent, GestureJudgeResult, GestureType, GestureMask, TapGestureInterface, LongPressGestureInterface, PanGestureInterface, PinchGestureInterface, SwipeGestureInterface, RotationGestureInterface, GestureGroupInterface } from "./../../component/gesture"
import { PixelMap } from "./../ArkPixelMapMaterialized"
import { LinearGradient } from "./../../component/dataPanel"
import { Callback_Number_SliderChangeMode_Void, SliderChangeMode, SliderBlockStyle, SliderInteraction, SliderConfiguration, SlideRange, SliderAttribute, SliderOptions } from "./../../component/slider"
import { Callback_Number_Void } from "./../../component/alphabetIndexer"
import { CallbackKind } from "./CallbackKind"
import { CallbackTransformer } from "./CallbackTransformer"
import { TypeChecker } from "#components"
import { MaterializedBase, toPeerPtr, wrapCallback } from "@koalaui/interop"
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
        thisSerializer.writeInt8(options_type as int32)
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
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Color
            thisSerializer.writeInt32(value_0.valueOf())
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3 as int32)
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
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as ResourceColor
            let value_0_type : int32 = RuntimeType.UNDEFINED
            value_0_type = runtimeType(value_0)
            if (TypeChecker.isColor(value_0)) {
                thisSerializer.writeInt8(0 as int32)
                const value_0_0  = value_0 as Color
                thisSerializer.writeInt32(value_0_0.valueOf())
            }
            else if (RuntimeType.NUMBER == value_0_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_0_1  = value_0 as number
                thisSerializer.writeNumber(value_0_1)
            }
            else if (RuntimeType.STRING == value_0_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_0_2  = value_0 as string
                thisSerializer.writeString(value_0_2)
            }
            else if (RuntimeType.OBJECT == value_0_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_0_3  = value_0 as Resource
                thisSerializer.writeResource(value_0_3)
            }
        }
        else if (TypeChecker.isLinearGradient(value)) {
            thisSerializer.writeInt8(1 as int32)
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
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Color
            thisSerializer.writeInt32(value_0.valueOf())
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3 as int32)
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
        ArkUIGeneratedNativeModule._SliderAttribute_trackThickness(this.peer.ptr, value)
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
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Color
            thisSerializer.writeInt32(value_0.valueOf())
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3 as int32)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_blockBorderColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    blockBorderWidthAttribute(value: Length): void {
        ArkUIGeneratedNativeModule._SliderAttribute_blockBorderWidth(this.peer.ptr, value)
    }
    stepColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Color
            thisSerializer.writeInt32(value_0.valueOf())
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3 as int32)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._SliderAttribute_stepColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    trackBorderRadiusAttribute(value: Length): void {
        ArkUIGeneratedNativeModule._SliderAttribute_trackBorderRadius(this.peer.ptr, value)
    }
    selectedBorderRadiusAttribute(value: Dimension): void {
        ArkUIGeneratedNativeModule._SliderAttribute_selectedBorderRadius(this.peer.ptr, value)
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
        ArkUIGeneratedNativeModule._SliderAttribute_stepSize(this.peer.ptr, value)
    }
    sliderInteractionModeAttribute(value: SliderInteraction): void {
        ArkUIGeneratedNativeModule._SliderAttribute_sliderInteractionMode(this.peer.ptr, value.valueOf())
    }
    minResponsiveDistanceAttribute(value: number): void {
        ArkUIGeneratedNativeModule._SliderAttribute_minResponsiveDistance(this.peer.ptr, value)
    }
    contentModifierAttribute(value: ContentModifier<object>): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeCustomObject("ContentModifier", value)
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
export interface ArkSliderAttributes extends ArkCommonMethodAttributes {
    blockColor?: ResourceColor
    trackColor?: ResourceColor | LinearGradient
    selectedColor?: ResourceColor
    minLabel?: string
    maxLabel?: string
    showSteps?: boolean
    trackThickness?: Length
    onChange?: ((value: number,mode: SliderChangeMode) => void)
    blockBorderColor?: ResourceColor
    blockBorderWidth?: Length
    stepColor?: ResourceColor
    trackBorderRadius?: Length
    selectedBorderRadius?: Dimension
    blockSize?: SizeOptions
    blockStyle?: SliderBlockStyle
    stepSize?: Length
    sliderInteractionMode?: SliderInteraction
    minResponsiveDistance?: number
    contentModifier?: ContentModifier<object>
    slideRange?: SlideRange
}

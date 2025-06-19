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
import { KStringPtr, KBoolean, RuntimeType, runtimeType } from "@koalaui/interop"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ComponentBase } from "./../ComponentBase"
import { TypeChecker } from "#components"
import { ArkCommonMethodComponent } from "./ArkCommon"
import { ArkSliderPeer } from "./peers/ArkSliderPeer"
import { CommonMethod, Rectangle, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, CustomBuilder, DragItemInfo, UniformDataType, PreDragStatus, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, ContentModifier } from "./ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions } from "./ArkUnitsInterfaces"
import { DrawModifier } from "./ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey } from "./ArkEnumsInterfaces"
import { Callback_Array_TouchTestInfo_TouchResult, Callback_ClickEvent_Void, Callback_Boolean_HoverEvent_Void, Callback_MouseEvent_Void, Callback_TouchEvent_Void, Callback_KeyEvent_Void, Callback_KeyEvent_Boolean, Callback_Void, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, Callback_DragEvent_String_Void, Callback_PreDragStatus_Void, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, Callback_TouchEvent_HitTestMode, Literal_Alignment_align, Callback_Number_SliderChangeMode_Void, Callback_Number_Void } from "./SyntheticDeclarations"
import { LengthMetrics } from "./ArkLengthMetricsMaterialized"
import { ResizableOptions } from "./ArkImageInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { ClickEvent } from "./ArkClickEventMaterialized"
import { HoverEvent } from "./ArkHoverEventMaterialized"
import { MouseEvent } from "./ArkMouseEventMaterialized"
import { TouchEvent } from "./ArkTouchEventMaterialized"
import { KeyEvent } from "./ArkKeyEventMaterialized"
import { FocusBoxStyle, FocusPriority } from "./ArkFocusInterfaces"
import { TransitionEffect } from "./ArkTransitionEffectMaterialized"
import { DragEvent } from "./ArkDragEventMaterialized"
import { CircleShape } from "./ArkCircleShapeMaterialized"
import { EllipseShape } from "./ArkEllipseShapeMaterialized"
import { PathShape } from "./ArkPathShapeMaterialized"
import { RectShape } from "./ArkRectShapeMaterialized"
import { ProgressMask } from "./ArkProgressMaskMaterialized"
import { AttributeModifier } from "./../handwritten"
import { GestureModifier } from "./ArkGestureModifierMaterialized"
import { GestureInfo, GestureJudgeResult, GestureType, GestureMask } from "./ArkGestureInterfaces"
import { BaseGestureEvent } from "./ArkBaseGestureEventMaterialized"
import { PixelMap } from "./ArkPixelMapMaterialized"
import { LinearGradient } from "./ArkLinearGradientMaterialized"
import { SliderChangeMode, SliderBlockStyle, SliderInteraction, SliderConfiguration, SlideRange, SliderAttribute, SliderOptions } from "./ArkSliderInterfaces"
/** @memo:stable */
export class ArkSliderComponent extends ArkCommonMethodComponent {
    getPeer(): ArkSliderPeer {
        return (this.peer as ArkSliderPeer)
    }
    /** @memo */
    public setSliderOptions(options?: SliderOptions): this {
        if (this.checkPriority("setSliderOptions")) {
            const options_casted = options as (SliderOptions | undefined)
            this.getPeer()?.setSliderOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public blockColor(value: ResourceColor): this {
        if (this.checkPriority("blockColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.blockColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public trackColor(value: ResourceColor | LinearGradient): this {
        if (this.checkPriority("trackColor")) {
            const value_casted = value as (ResourceColor | LinearGradient)
            this.getPeer()?.trackColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public selectedColor(value: ResourceColor): this {
        if (this.checkPriority("selectedColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.selectedColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public minLabel(value: string): this {
        if (this.checkPriority("minLabel")) {
            const value_casted = value as (string)
            this.getPeer()?.minLabelAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public maxLabel(value: string): this {
        if (this.checkPriority("maxLabel")) {
            const value_casted = value as (string)
            this.getPeer()?.maxLabelAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public showSteps(value: boolean): this {
        if (this.checkPriority("showSteps")) {
            const value_casted = value as (boolean)
            this.getPeer()?.showStepsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public trackThickness(value: Length): this {
        if (this.checkPriority("trackThickness")) {
            const value_casted = value as (Length)
            this.getPeer()?.trackThicknessAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onChange(value: ((value: number,mode: SliderChangeMode) => void)): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((value: number,mode: SliderChangeMode) => void))
            this.getPeer()?.onChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public blockBorderColor(value: ResourceColor): this {
        if (this.checkPriority("blockBorderColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.blockBorderColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public blockBorderWidth(value: Length): this {
        if (this.checkPriority("blockBorderWidth")) {
            const value_casted = value as (Length)
            this.getPeer()?.blockBorderWidthAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public stepColor(value: ResourceColor): this {
        if (this.checkPriority("stepColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.stepColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public trackBorderRadius(value: Length): this {
        if (this.checkPriority("trackBorderRadius")) {
            const value_casted = value as (Length)
            this.getPeer()?.trackBorderRadiusAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public selectedBorderRadius(value: Dimension): this {
        if (this.checkPriority("selectedBorderRadius")) {
            const value_casted = value as (Dimension)
            this.getPeer()?.selectedBorderRadiusAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public blockSize(value: SizeOptions): this {
        if (this.checkPriority("blockSize")) {
            const value_casted = value as (SizeOptions)
            this.getPeer()?.blockSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public blockStyle(value: SliderBlockStyle): this {
        if (this.checkPriority("blockStyle")) {
            const value_casted = value as (SliderBlockStyle)
            this.getPeer()?.blockStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public stepSize(value: Length): this {
        if (this.checkPriority("stepSize")) {
            const value_casted = value as (Length)
            this.getPeer()?.stepSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public sliderInteractionMode(value: SliderInteraction): this {
        if (this.checkPriority("sliderInteractionMode")) {
            const value_casted = value as (SliderInteraction)
            this.getPeer()?.sliderInteractionModeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public minResponsiveDistance(value: number): this {
        if (this.checkPriority("minResponsiveDistance")) {
            const value_casted = value as (number)
            this.getPeer()?.minResponsiveDistanceAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public contentModifier(value: ContentModifier<object>): this {
        if (this.checkPriority("contentModifier")) {
            const value_casted = value as (ContentModifier<object>)
            this.getPeer()?.contentModifierAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public slideRange(value: SlideRange): this {
        if (this.checkPriority("slideRange")) {
            const value_casted = value as (SlideRange)
            this.getPeer()?.slideRangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public showTips(value: boolean, content?: ResourceStr): this {
        if (this.checkPriority("showTips")) {
            const value_casted = value as (boolean)
            const content_casted = content as (ResourceStr | undefined)
            this.getPeer()?.showTipsAttribute(value_casted, content_casted)
            return this
        }
        return this
    }
    /** @memo */
    public _onChangeEvent_value(callback: ((index: number) => void)): void {
        if (this.checkPriority("_onChangeEvent_value")) {
            const callback_casted = callback as (((index: number) => void))
            this.getPeer()?._onChangeEvent_valueAttribute(callback_casted)
            return
        }
        return
    }
    public applyAttributesFinish(): void {
        // we calls this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

/** @memo */
export function ArkSlider(
  /** @memo */
  style: ((attributes: ArkSliderComponent) => void) | undefined,
  /** @memo */
  content_: (() => void) | undefined,
  options?: SliderOptions | undefined
) {
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

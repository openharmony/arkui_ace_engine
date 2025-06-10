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
import { ArkDatePickerPeer } from "./peers/ArkDatePickerPeer"
import { CommonMethod, Rectangle, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, CustomBuilder, DragItemInfo, UniformDataType, PreDragStatus, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, PickerTextStyle } from "./ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions } from "./ArkUnitsInterfaces"
import { DrawModifier } from "./ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey } from "./ArkEnumsInterfaces"
import { Callback_Array_TouchTestInfo_TouchResult, Callback_ClickEvent_Void, Callback_Boolean_HoverEvent_Void, Callback_MouseEvent_Void, Callback_TouchEvent_Void, Callback_KeyEvent_Void, Callback_KeyEvent_Boolean, Callback_Void, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, Callback_DragEvent_String_Void, Callback_PreDragStatus_Void, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, Callback_TouchEvent_HitTestMode, Literal_Alignment_align, Callback_DatePickerResult_Void, Callback_Date_Void } from "./SyntheticDeclarations"
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
import { DatePickerResult, DatePickerOptions, DatePickerAttribute } from "./ArkDatePickerInterfaces"
/** @memo:stable */
export class ArkDatePickerComponent extends ArkCommonMethodComponent {
    getPeer(): ArkDatePickerPeer {
        return (this.peer as ArkDatePickerPeer)
    }
    /** @memo */
    public setDatePickerOptions(options?: DatePickerOptions): this {
        if (this.checkPriority("setDatePickerOptions")) {
            const options_casted = options as (DatePickerOptions | undefined)
            this.getPeer()?.setDatePickerOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public lunar(value: boolean): this {
        if (this.checkPriority("lunar")) {
            const value_casted = value as (boolean)
            this.getPeer()?.lunarAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public disappearTextStyle(value: PickerTextStyle): this {
        if (this.checkPriority("disappearTextStyle")) {
            const value_casted = value as (PickerTextStyle)
            this.getPeer()?.disappearTextStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public textStyle(value: PickerTextStyle): this {
        if (this.checkPriority("textStyle")) {
            const value_casted = value as (PickerTextStyle)
            this.getPeer()?.textStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public selectedTextStyle(value: PickerTextStyle): this {
        if (this.checkPriority("selectedTextStyle")) {
            const value_casted = value as (PickerTextStyle)
            this.getPeer()?.selectedTextStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onChange(value: ((value: DatePickerResult) => void)): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((value: DatePickerResult) => void))
            this.getPeer()?.onChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onDateChange(value: ((parameter: Date) => void)): this {
        if (this.checkPriority("onDateChange")) {
            const value_casted = value as (((parameter: Date) => void))
            this.getPeer()?.onDateChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public _onChangeEvent_selected(callback: ((parameter: Date) => void)): void {
        if (this.checkPriority("_onChangeEvent_selected")) {
            const callback_casted = callback as (((parameter: Date) => void))
            this.getPeer()?._onChangeEvent_selectedAttribute(callback_casted)
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
export function ArkDatePicker(
  /** @memo */
  style: ((attributes: ArkDatePickerComponent) => void) | undefined,
  /** @memo */
  content_: (() => void) | undefined,
  options?: DatePickerOptions | undefined
) {
    const receiver = remember(() => {
        return new ArkDatePickerComponent()
    })
    NodeAttach<ArkDatePickerPeer>((): ArkDatePickerPeer => ArkDatePickerPeer.create(receiver), (_: ArkDatePickerPeer) => {
        receiver.setDatePickerOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

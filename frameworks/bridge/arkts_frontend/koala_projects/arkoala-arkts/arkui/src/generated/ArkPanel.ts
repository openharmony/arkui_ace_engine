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
import { ArkPanelPeer } from "./peers/ArkPanelPeer"
import { CommonMethod, Rectangle, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, CustomBuilder, DragItemInfo, UniformDataType, PreDragStatus, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback } from "./ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions } from "./ArkUnitsInterfaces"
import { DrawModifier } from "./ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey } from "./ArkEnumsInterfaces"
import { Callback_Array_TouchTestInfo_TouchResult, Callback_ClickEvent_Void, Callback_Boolean_HoverEvent_Void, Callback_MouseEvent_Void, Callback_TouchEvent_Void, Callback_KeyEvent_Void, Callback_KeyEvent_Boolean, Callback_Void, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, Callback_DragEvent_String_Void, Callback_PreDragStatus_Void, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, Callback_TouchEvent_HitTestMode, Literal_Alignment_align, Callback_Number_Number_PanelMode_Void, Callback_Number_Void, Callback_PanelMode_Void } from "./SyntheticDeclarations"
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
import { PanelMode, PanelType, PanelHeight, PanelAttribute } from "./ArkPanelInterfaces"
/** @memo:stable */
export class ArkPanelComponent extends ArkCommonMethodComponent {
    getPeer(): ArkPanelPeer {
        return (this.peer as ArkPanelPeer)
    }
    /** @memo */
    public setPanelOptions(show: boolean): this {
        if (this.checkPriority("setPanelOptions")) {
            const show_casted = show as (boolean)
            this.getPeer()?.setPanelOptionsAttribute(show_casted)
            return this
        }
        return this
    }
    /** @memo */
    public mode(value: PanelMode): this {
        if (this.checkPriority("mode")) {
            const value_casted = value as (PanelMode)
            this.getPeer()?.modeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public type(value: PanelType): this {
        if (this.checkPriority("type")) {
            const value_casted = value as (PanelType)
            this.getPeer()?.typeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public dragBar(value: boolean): this {
        if (this.checkPriority("dragBar")) {
            const value_casted = value as (boolean)
            this.getPeer()?.dragBarAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public customHeight(value: Dimension | PanelHeight): this {
        if (this.checkPriority("customHeight")) {
            const value_casted = value as (Dimension | PanelHeight)
            this.getPeer()?.customHeightAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fullHeight(value: number | string): this {
        if (this.checkPriority("fullHeight")) {
            const value_casted = value as (number | string)
            this.getPeer()?.fullHeightAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public halfHeight(value: number | string): this {
        if (this.checkPriority("halfHeight")) {
            const value_casted = value as (number | string)
            this.getPeer()?.halfHeightAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public miniHeight(value: number | string): this {
        if (this.checkPriority("miniHeight")) {
            const value_casted = value as (number | string)
            this.getPeer()?.miniHeightAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public show(value: boolean): this {
        if (this.checkPriority("show")) {
            const value_casted = value as (boolean)
            this.getPeer()?.showAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public backgroundMask(value: ResourceColor): this {
        if (this.checkPriority("backgroundMask")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.backgroundMaskAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public showCloseIcon(value: boolean): this {
        if (this.checkPriority("showCloseIcon")) {
            const value_casted = value as (boolean)
            this.getPeer()?.showCloseIconAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onChange(value: ((width: number,height: number,mode: PanelMode) => void)): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((width: number,height: number,mode: PanelMode) => void))
            this.getPeer()?.onChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onHeightChange(value: ((index: number) => void)): this {
        if (this.checkPriority("onHeightChange")) {
            const value_casted = value as (((index: number) => void))
            this.getPeer()?.onHeightChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public _onChangeEvent_mode(callback: ((mode: PanelMode) => void)): void {
        if (this.checkPriority("_onChangeEvent_mode")) {
            const callback_casted = callback as (((mode: PanelMode) => void))
            this.getPeer()?._onChangeEvent_modeAttribute(callback_casted)
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
export function ArkPanel(
  /** @memo */
  style: ((attributes: ArkPanelComponent) => void) | undefined,
  /** @memo */
  content_: (() => void) | undefined,
  show: boolean
) {
    const receiver = remember(() => {
        return new ArkPanelComponent()
    })
    NodeAttach<ArkPanelPeer>((): ArkPanelPeer => ArkPanelPeer.create(receiver), (_: ArkPanelPeer) => {
        receiver.setPanelOptions(show)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

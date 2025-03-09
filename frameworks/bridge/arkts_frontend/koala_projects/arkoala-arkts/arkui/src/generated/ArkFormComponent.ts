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
import { ArkFormComponentPeer } from "./peers/ArkFormComponentPeer"
import { CommonMethod, Rectangle, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, CustomBuilder, DragItemInfo, UniformDataType, PreDragStatus, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback } from "./ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions } from "./ArkUnitsInterfaces"
import { DrawModifier } from "./ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey } from "./ArkEnumsInterfaces"
import { Callback_Array_TouchTestInfo_TouchResult, Callback_ClickEvent_Void, Callback_Boolean_HoverEvent_Void, Callback_MouseEvent_Void, Callback_TouchEvent_Void, Callback_KeyEvent_Void, Callback_KeyEvent_Boolean, Callback_Void, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, Callback_DragEvent_String_Void, Callback_PreDragStatus_Void, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, Callback_TouchEvent_HitTestMode, Literal_Alignment_align, Callback_FormCallbackInfo_Void, Callback_Literal_Number_errcode_String_msg_Void, Literal_Number_errcode_String_msg, Callback_Any_Void } from "./SyntheticDeclarations"
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
import { FormDimension, FormCallbackInfo, FormInfo, FormComponentAttribute } from "./ArkFormComponentInterfaces"
/** @memo:stable */
export class ArkFormComponentComponent extends ArkCommonMethodComponent {
    getPeer(): ArkFormComponentPeer {
        return (this.peer as ArkFormComponentPeer)
    }
    /** @memo */
    public setFormComponentOptions(value: FormInfo): this {
        if (this.checkPriority("setFormComponentOptions")) {
            const value_casted = value as (FormInfo)
            this.getPeer()?.setFormComponentOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public size(value: SizeOptions): this {
        if (this.checkPriority("size")) {
            const value_casted = value as (SizeOptions)
            this.getPeer()?.sizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public moduleName(value: string): this {
        if (this.checkPriority("moduleName")) {
            const value_casted = value as (string)
            this.getPeer()?.moduleNameAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public dimension(value: FormDimension): this {
        if (this.checkPriority("dimension")) {
            const value_casted = value as (FormDimension)
            this.getPeer()?.dimensionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public allowUpdate(value: boolean): this {
        if (this.checkPriority("allowUpdate")) {
            const value_casted = value as (boolean)
            this.getPeer()?.allowUpdateAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public visibility(value: Visibility): this {
        if (this.checkPriority("visibility")) {
            const value_casted = value as (Visibility)
            this.getPeer()?.visibilityAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onAcquired(value: ((parameter: FormCallbackInfo) => void)): this {
        if (this.checkPriority("onAcquired")) {
            const value_casted = value as (((parameter: FormCallbackInfo) => void))
            this.getPeer()?.onAcquiredAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onError(value: ((info: Literal_Number_errcode_String_msg) => void)): this {
        if (this.checkPriority("onError")) {
            const value_casted = value as (((info: Literal_Number_errcode_String_msg) => void))
            this.getPeer()?.onErrorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onRouter(value: ((info: object) => void)): this {
        if (this.checkPriority("onRouter")) {
            const value_casted = value as (((info: object) => void))
            this.getPeer()?.onRouterAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onUninstall(value: ((parameter: FormCallbackInfo) => void)): this {
        if (this.checkPriority("onUninstall")) {
            const value_casted = value as (((parameter: FormCallbackInfo) => void))
            this.getPeer()?.onUninstallAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onLoad(value: (() => void)): this {
        if (this.checkPriority("onLoad")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onLoadAttribute(value_casted)
            return this
        }
        return this
    }
    public applyAttributesFinish(): void {
        // we calls this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

/** @memo */
export function ArkFormComponent(
  /** @memo */
  style: ((attributes: ArkFormComponentComponent) => void) | undefined,
  /** @memo */
  content_: (() => void) | undefined,
  value: FormInfo
) {
    const receiver = remember(() => {
        return new ArkFormComponentComponent()
    })
    NodeAttach<ArkFormComponentPeer>((): ArkFormComponentPeer => ArkFormComponentPeer.create(receiver), (_: ArkFormComponentPeer) => {
        receiver.setFormComponentOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

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
import { ArkUIExtensionComponentPeer } from "./peers/ArkUiExtensionComponentPeer"
import { CommonMethod, Rectangle, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, CustomBuilder, DragItemInfo, UniformDataType, PreDragStatus, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback } from "./ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions } from "./ArkUnitsInterfaces"
import { DrawModifier } from "./ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey } from "./ArkEnumsInterfaces"
import { Callback_Array_TouchTestInfo_TouchResult, Callback_ClickEvent_Void, Callback_Boolean_HoverEvent_Void, Callback_MouseEvent_Void, Callback_TouchEvent_Void, Callback_KeyEvent_Void, Callback_KeyEvent_Boolean, Callback_Void, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, Callback_DragEvent_String_Void, Callback_PreDragStatus_Void, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, Callback_TouchEvent_HitTestMode, Literal_Alignment_align, Callback_UIExtensionProxy_Void, Callback_Literal_Number_code_Want_want_Void, Literal_Number_code_Want_want, Callback_Number_Void, Callback_TerminationInfo_Void } from "./SyntheticDeclarations"
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
import { UIExtensionProxy } from "./ArkUIExtensionProxyMaterialized"
import { ReceiveCallback, UIExtensionOptions, UIExtensionComponentAttribute } from "./ArkUiExtensionComponentInterfaces"
import { Want, ErrorCallback } from "./ArkArkuiExternalInterfaces"
import { TerminationInfo } from "./ArkEmbeddedComponentInterfaces"
/** @memo:stable */
export class ArkUIExtensionComponentComponent extends ArkCommonMethodComponent {
    getPeer(): ArkUIExtensionComponentPeer {
        return (this.peer as ArkUIExtensionComponentPeer)
    }
    /** @memo */
    public setUIExtensionComponentOptions(want: Want, options?: UIExtensionOptions): this {
        if (this.checkPriority("setUIExtensionComponentOptions")) {
            const want_casted = want as (Want)
            const options_casted = options as (UIExtensionOptions | undefined)
            this.getPeer()?.setUIExtensionComponentOptionsAttribute(want_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onRemoteReady(value: ((parameter: UIExtensionProxy) => void)): this {
        if (this.checkPriority("onRemoteReady")) {
            const value_casted = value as (((parameter: UIExtensionProxy) => void))
            this.getPeer()?.onRemoteReadyAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onReceive(value: ReceiveCallback): this {
        if (this.checkPriority("onReceive")) {
            const value_casted = value as (ReceiveCallback)
            this.getPeer()?.onReceiveAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onResult(value: ((parameter: Literal_Number_code_Want_want) => void)): this {
        if (this.checkPriority("onResult")) {
            const value_casted = value as (((parameter: Literal_Number_code_Want_want) => void))
            this.getPeer()?.onResultAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onRelease(value: ((index: number) => void)): this {
        if (this.checkPriority("onRelease")) {
            const value_casted = value as (((index: number) => void))
            this.getPeer()?.onReleaseAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onError(value: ErrorCallback): this {
        if (this.checkPriority("onError")) {
            const value_casted = value as (ErrorCallback)
            this.getPeer()?.onErrorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onTerminated(value: ((parameter: TerminationInfo) => void)): this {
        if (this.checkPriority("onTerminated")) {
            const value_casted = value as (((parameter: TerminationInfo) => void))
            this.getPeer()?.onTerminatedAttribute(value_casted)
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
export function ArkUIExtensionComponent(
  /** @memo */
  style: ((attributes: ArkUIExtensionComponentComponent) => void) | undefined,
  /** @memo */
  content_: (() => void) | undefined,
  want: Want, options?: UIExtensionOptions | undefined
) {
    const receiver = remember(() => {
        return new ArkUIExtensionComponentComponent()
    })
    NodeAttach<ArkUIExtensionComponentPeer>((): ArkUIExtensionComponentPeer => ArkUIExtensionComponentPeer.create(receiver), (_: ArkUIExtensionComponentPeer) => {
        receiver.setUIExtensionComponentOptions(want,options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

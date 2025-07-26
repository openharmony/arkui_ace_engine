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
import { ArkVideoPeer } from "./peers/ArkVideoPeer"
import { CommonMethod, Rectangle, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, CustomBuilder, DragItemInfo, UniformDataType, PreDragStatus, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback } from "./ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, VoidCallback } from "./ArkUnitsInterfaces"
import { DrawModifier } from "./ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, ImageFit } from "./ArkEnumsInterfaces"
import { Callback_Array_TouchTestInfo_TouchResult, Callback_ClickEvent_Void, Callback_Boolean_HoverEvent_Void, Callback_MouseEvent_Void, Callback_TouchEvent_Void, Callback_KeyEvent_Void, Callback_KeyEvent_Boolean, Callback_Void, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, Callback_DragEvent_String_Void, Callback_PreDragStatus_Void, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, Callback_TouchEvent_HitTestMode, Literal_Alignment_align, Callback_FullscreenInfo_Void, Callback_PreparedInfo_Void, Callback_PlaybackInfo_Void } from "./SyntheticDeclarations"
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
import { FullscreenInfo, PreparedInfo, PlaybackInfo, VideoOptions, VideoAttribute } from "./ArkVideoInterfaces"
import { ImageAnalyzerConfig } from "./ArkImageCommonInterfaces"
/** @memo:stable */
export class ArkVideoComponent extends ArkCommonMethodComponent {
    getPeer(): ArkVideoPeer {
        return (this.peer as ArkVideoPeer)
    }
    /** @memo */
    public setVideoOptions(value: VideoOptions): this {
        if (this.checkPriority("setVideoOptions")) {
            const value_casted = value as (VideoOptions)
            this.getPeer()?.setVideoOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public muted(value: boolean): this {
        if (this.checkPriority("muted")) {
            const value_casted = value as (boolean)
            this.getPeer()?.mutedAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public autoPlay(value: boolean): this {
        if (this.checkPriority("autoPlay")) {
            const value_casted = value as (boolean)
            this.getPeer()?.autoPlayAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public controls(value: boolean): this {
        if (this.checkPriority("controls")) {
            const value_casted = value as (boolean)
            this.getPeer()?.controlsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public loop(value: boolean): this {
        if (this.checkPriority("loop")) {
            const value_casted = value as (boolean)
            this.getPeer()?.loopAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public objectFit(value: ImageFit): this {
        if (this.checkPriority("objectFit")) {
            const value_casted = value as (ImageFit)
            this.getPeer()?.objectFitAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onStart(value: VoidCallback): this {
        if (this.checkPriority("onStart")) {
            const value_casted = value as (VoidCallback)
            this.getPeer()?.onStartAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onPause(value: VoidCallback): this {
        if (this.checkPriority("onPause")) {
            const value_casted = value as (VoidCallback)
            this.getPeer()?.onPauseAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onFinish(value: VoidCallback): this {
        if (this.checkPriority("onFinish")) {
            const value_casted = value as (VoidCallback)
            this.getPeer()?.onFinishAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onFullscreenChange(value: ((parameter: FullscreenInfo) => void)): this {
        if (this.checkPriority("onFullscreenChange")) {
            const value_casted = value as (((parameter: FullscreenInfo) => void))
            this.getPeer()?.onFullscreenChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onPrepared(value: ((parameter: PreparedInfo) => void)): this {
        if (this.checkPriority("onPrepared")) {
            const value_casted = value as (((parameter: PreparedInfo) => void))
            this.getPeer()?.onPreparedAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onSeeking(value: ((parameter: PlaybackInfo) => void)): this {
        if (this.checkPriority("onSeeking")) {
            const value_casted = value as (((parameter: PlaybackInfo) => void))
            this.getPeer()?.onSeekingAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onSeeked(value: ((parameter: PlaybackInfo) => void)): this {
        if (this.checkPriority("onSeeked")) {
            const value_casted = value as (((parameter: PlaybackInfo) => void))
            this.getPeer()?.onSeekedAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onUpdate(value: ((parameter: PlaybackInfo) => void)): this {
        if (this.checkPriority("onUpdate")) {
            const value_casted = value as (((parameter: PlaybackInfo) => void))
            this.getPeer()?.onUpdateAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onError(value: (() => void)): this {
        if (this.checkPriority("onError")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onErrorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onStop(value: (() => void)): this {
        if (this.checkPriority("onStop")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onStopAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enableAnalyzer(value: boolean): this {
        if (this.checkPriority("enableAnalyzer")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableAnalyzerAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public analyzerConfig(value: ImageAnalyzerConfig): this {
        if (this.checkPriority("analyzerConfig")) {
            const value_casted = value as (ImageAnalyzerConfig)
            this.getPeer()?.analyzerConfigAttribute(value_casted)
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
export function ArkVideo(
  /** @memo */
  style: ((attributes: ArkVideoComponent) => void) | undefined,
  /** @memo */
  content_: (() => void) | undefined,
  value: VideoOptions
) {
    const receiver = remember(() => {
        return new ArkVideoComponent()
    })
    NodeAttach<ArkVideoPeer>((): ArkVideoPeer => ArkVideoPeer.create(receiver), (_: ArkVideoPeer) => {
        receiver.setVideoOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

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

import { int32, float32, unsafeCast } from "@koalaui/common"
import { KStringPtr, KBoolean, RuntimeType, runtimeType, isInstanceOf } from "@koalaui/interop"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ComponentBase } from "./../ComponentBase"
import { isResource, isPadding } from "./../utils"
import { ArkCommonMethodComponent } from "./ArkCommon"
import { ArkVideoPeer } from "./peers/ArkVideoPeer"
import { CommonMethod, Rectangle, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, UniformDataType, CustomBuilder, DragItemInfo, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, DrawContext, TouchTestInfo, TouchResult, AdaptiveColor, BlurStyleActivePolicy, RepeatMode, LinearGradient_common, FinishCallbackType, ExpectedFrameRateRange, TransitionEffects, TransitionEdge, MotionBlurAnchor, LocalizedHorizontalAlignParam, LocalizedVerticalAlignParam, PreDragStatus, ShadowType, UIGestureEvent, BlurStyleOptions, ThemeColorMode, FractionStop, DragPreviewMode, ImageModifier, OverlayOffset, TransitionHierarchyStrategy, PopupMessageOptions, SymbolGlyphModifier, MenuPreviewMode, ContextMenuAnimationOptions, BindOptions, SheetSize, SheetType, SheetTitleOptions, SheetMode, ScrollSizeMode, UIContext, SheetKeyboardAvoidMode, SourceTool, RectResult, TouchTestStrategy, EventTarget, SourceType, TouchObject, HistoricalPoint, IntentionCode, DragBehavior, Summary, DragResult, DismissPopupAction, DismissContentCoverAction, SheetDismiss, DismissSheetAction, SpringBackAction, DismissReason } from "./ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage, Area, Bias, Font, VoidCallback } from "./ArkUnitsInterfaces"
import { DrawModifier } from "./ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, PixelRoundCalcPolicy, Curve, PlayMode, TransitionType, HorizontalAlign, VerticalAlign, ClickEffectLevel, SharedTransitionEffectType, Placement, ArrowPointPosition, MouseButton, MouseAction, TouchType, KeyType, KeySource, FontWeight, FontStyle, ImageFit } from "./ArkEnumsInterfaces"
import { LengthMetrics } from "./ArkLengthMetricsMaterialized"
import { ResizableOptions, DrawingLattice } from "./ArkImageInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { FocusBoxStyle, FocusPriority } from "./ArkFocusInterfaces"
import { TransitionEffect } from "./ArkTransitionEffectMaterialized"
import { CircleShape } from "./ArkCircleShapeMaterialized"
import { EllipseShape } from "./ArkEllipseShapeMaterialized"
import { PathShape } from "./ArkPathShapeMaterialized"
import { RectShape } from "./ArkRectShapeMaterialized"
import { ProgressMask } from "./ArkProgressMaskMaterialized"
import { AttributeModifier } from "./../handwritten"
import { GestureModifier } from "./ArkGestureModifierMaterialized"
import { PixelMap } from "./ArkPixelMapMaterialized"
import { GestureType, GestureMask, GestureInfo, GestureJudgeResult, GestureInterface, TapGestureParameters, PanDirection, SwipeDirection, GestureMode, GestureHandler, GesturePriority, FingerInfo } from "./ArkGestureInterfaces"
import { TapGestureInterface } from "./ArkTapGestureInterfaceMaterialized"
import { LongPressGestureInterface } from "./ArkLongPressGestureInterfaceMaterialized"
import { PanGestureInterface } from "./ArkPanGestureInterfaceMaterialized"
import { PinchGestureInterface } from "./ArkPinchGestureInterfaceMaterialized"
import { SwipeGestureInterface } from "./ArkSwipeGestureInterfaceMaterialized"
import { RotationGestureInterface } from "./ArkRotationGestureInterfaceMaterialized"
import { GestureGroupInterface } from "./ArkGestureGroupInterfaceMaterialized"
import { LengthUnit, ShapeSize, PathShapeOptions, RectShapeOptions, RoundRectShapeOptions } from "./ArkArkuiExternalInterfaces"
import { ClickEvent } from "./ArkClickEventMaterialized"
import { HoverEvent } from "./ArkHoverEventMaterialized"
import { MouseEvent } from "./ArkMouseEventMaterialized"
import { TouchEvent } from "./ArkTouchEventMaterialized"
import { KeyEvent } from "./ArkKeyEventMaterialized"
import { ColorMetrics } from "./ArkColorMetricsMaterialized"
import { ICurve } from "./ArkICurveMaterialized"
import { DragEvent } from "./ArkDragEventMaterialized"
import { BaseGestureEvent } from "./ArkBaseGestureEventMaterialized"
import { PanGestureOptions } from "./ArkPanGestureOptionsMaterialized"
import { BaseEvent } from "./ArkBaseEventMaterialized"
import { UnifiedData } from "./ArkUnifiedDataMaterialized"
import { GestureControl } from "./ArkGestureControlNamespace"
import { GestureEvent } from "./ArkGestureEventMaterialized"
import { ImageAnalyzerConfig, ImageAnalyzerType, ImageAIOptions } from "./ArkImageCommonInterfaces"
import { FullscreenInfo, PreparedInfo, PlaybackInfo, VideoOptions, VideoAttribute, PlaybackSpeed, SeekMode } from "./ArkVideoInterfaces"
import { VideoController } from "./ArkVideoControllerMaterialized"
import { ImageAnalyzerController } from "./ArkImageAnalyzerControllerMaterialized"
/** @memo:stable */
export class ArkVideoComponent extends ArkCommonMethodComponent {
    protected getPeer(): ArkVideoPeer {
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

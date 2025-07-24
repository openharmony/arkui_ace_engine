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
import { ArkImageAnimatorPeer } from "./peers/ArkImageAnimatorPeer"
import { CommonMethod, Rectangle, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, UniformDataType, CustomBuilder, DragItemInfo, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, DrawContext, TouchTestInfo, TouchResult, AdaptiveColor, BlurStyleActivePolicy, RepeatMode, LinearGradient_common, FinishCallbackType, ExpectedFrameRateRange, TransitionEffects, TransitionEdge, MotionBlurAnchor, LocalizedHorizontalAlignParam, LocalizedVerticalAlignParam, PreDragStatus, ShadowType, UIGestureEvent, BlurStyleOptions, ThemeColorMode, FractionStop, DragPreviewMode, ImageModifier, OverlayOffset, TransitionHierarchyStrategy, PopupMessageOptions, SymbolGlyphModifier, MenuPreviewMode, ContextMenuAnimationOptions, BindOptions, SheetSize, SheetType, SheetTitleOptions, SheetMode, ScrollSizeMode, UIContext, SheetKeyboardAvoidMode, SourceTool, RectResult, TouchTestStrategy, EventTarget, SourceType, TouchObject, HistoricalPoint, IntentionCode, DragBehavior, Summary, DragResult, DismissPopupAction, DismissContentCoverAction, SheetDismiss, DismissSheetAction, SpringBackAction, DismissReason } from "./ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage, Area, Bias, Font } from "./ArkUnitsInterfaces"
import { DrawModifier } from "./ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, PixelRoundCalcPolicy, Curve, PlayMode, TransitionType, HorizontalAlign, VerticalAlign, ClickEffectLevel, SharedTransitionEffectType, Placement, ArrowPointPosition, MouseButton, MouseAction, TouchType, KeyType, KeySource, FontWeight, FontStyle, AnimationStatus, FillMode } from "./ArkEnumsInterfaces"
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
import { ImageFrameInfo, ImageAnimatorAttribute } from "./ArkImageAnimatorInterfaces"
/** @memo:stable */
export class ArkImageAnimatorComponent extends ArkCommonMethodComponent {
    protected getPeer(): ArkImageAnimatorPeer {
        return (this.peer as ArkImageAnimatorPeer)
    }
    /** @memo */
    public setImageAnimatorOptions(): this {
        if (this.checkPriority("setImageAnimatorOptions")) {
            this.getPeer()?.setImageAnimatorOptionsAttribute()
            return this
        }
        return this
    }
    /** @memo */
    public images(value: Array<ImageFrameInfo>): this {
        if (this.checkPriority("images")) {
            const value_casted = value as (Array<ImageFrameInfo>)
            this.getPeer()?.imagesAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public state(value: AnimationStatus): this {
        if (this.checkPriority("state")) {
            const value_casted = value as (AnimationStatus)
            this.getPeer()?.stateAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public duration(value: number): this {
        if (this.checkPriority("duration")) {
            const value_casted = value as (number)
            this.getPeer()?.durationAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public reverse(value: boolean): this {
        if (this.checkPriority("reverse")) {
            const value_casted = value as (boolean)
            this.getPeer()?.reverseAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fixedSize(value: boolean): this {
        if (this.checkPriority("fixedSize")) {
            const value_casted = value as (boolean)
            this.getPeer()?.fixedSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public preDecode(value: number): this {
        if (this.checkPriority("preDecode")) {
            const value_casted = value as (number)
            this.getPeer()?.preDecodeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fillMode(value: FillMode): this {
        if (this.checkPriority("fillMode")) {
            const value_casted = value as (FillMode)
            this.getPeer()?.fillModeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public iterations(value: number): this {
        if (this.checkPriority("iterations")) {
            const value_casted = value as (number)
            this.getPeer()?.iterationsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onStart(value: (() => void)): this {
        if (this.checkPriority("onStart")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onStartAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onPause(value: (() => void)): this {
        if (this.checkPriority("onPause")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onPauseAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onRepeat(value: (() => void)): this {
        if (this.checkPriority("onRepeat")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onRepeatAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onCancel(value: (() => void)): this {
        if (this.checkPriority("onCancel")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onCancelAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onFinish(value: (() => void)): this {
        if (this.checkPriority("onFinish")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onFinishAttribute(value_casted)
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
export function ArkImageAnimator(
  /** @memo */
  style: ((attributes: ArkImageAnimatorComponent) => void) | undefined,
  /** @memo */
  content_: (() => void) | undefined,
  
) {
    const receiver = remember(() => {
        return new ArkImageAnimatorComponent()
    })
    NodeAttach<ArkImageAnimatorPeer>((): ArkImageAnimatorPeer => ArkImageAnimatorPeer.create(receiver), (_: ArkImageAnimatorPeer) => {
        receiver.setImageAnimatorOptions()
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

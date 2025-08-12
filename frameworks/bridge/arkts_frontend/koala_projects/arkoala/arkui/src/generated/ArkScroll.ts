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
import { ArkScrollableCommonMethodComponent } from "./ArkCommon"
import { ArkScrollPeer } from "./peers/ArkScrollPeer"
import { ScrollableCommonMethod, CommonMethod, Rectangle, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, UniformDataType, CustomBuilder, DragItemInfo, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, DrawContext, TouchTestInfo, TouchResult, AdaptiveColor, BlurStyleActivePolicy, RepeatMode, LinearGradient_common, FinishCallbackType, ExpectedFrameRateRange, TransitionEffects, TransitionEdge, MotionBlurAnchor, LocalizedHorizontalAlignParam, LocalizedVerticalAlignParam, PreDragStatus, ShadowType, UIGestureEvent, BlurStyleOptions, ThemeColorMode, FractionStop, DragPreviewMode, ImageModifier, OverlayOffset, TransitionHierarchyStrategy, PopupMessageOptions, SymbolGlyphModifier, MenuPreviewMode, ContextMenuAnimationOptions, BindOptions, SheetSize, SheetType, SheetTitleOptions, SheetMode, ScrollSizeMode, UIContext, SheetKeyboardAvoidMode, SourceTool, RectResult, TouchTestStrategy, EventTarget, SourceType, TouchObject, HistoricalPoint, IntentionCode, DragBehavior, Summary, DragResult, DismissPopupAction, DismissContentCoverAction, SheetDismiss, DismissSheetAction, SpringBackAction, DismissReason, NestedScrollOptions, ContentClipMode, EdgeEffectOptions, FadingEdgeOptions } from "./ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage, Area, Bias, Font, VoidCallback } from "./ArkUnitsInterfaces"
import { DrawModifier } from "./ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, PixelRoundCalcPolicy, Curve, PlayMode, TransitionType, HorizontalAlign, VerticalAlign, ClickEffectLevel, SharedTransitionEffectType, Placement, ArrowPointPosition, MouseButton, MouseAction, TouchType, KeyType, KeySource, FontWeight, FontStyle, BarState, EdgeEffect, NestedScrollMode, Edge } from "./ArkEnumsInterfaces"
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
import { ScrollOnWillScrollCallback, ScrollOnScrollCallback, ScrollDirection, OnScrollEdgeCallback, OnScrollFrameBeginCallback, ScrollSnapOptions, OffsetOptions, ScrollAttribute, ScrollOptions, ScrollEdgeOptions, ScrollPageOptions, OffsetResult, ScrollAlign, ScrollToIndexOptions, ScrollAnimationOptions } from "./ArkScrollInterfaces"
import { ScrollSnapAlign } from "./ArkListInterfaces"
import { Scroller } from "./ArkScrollerMaterialized"
/** @memo:stable */
export class ArkScrollComponent extends ArkScrollableCommonMethodComponent {
    protected getPeer(): ArkScrollPeer {
        return (this.peer as ArkScrollPeer)
    }
    /** @memo */
    public setScrollOptions(scroller?: Scroller): this {
        if (this.checkPriority("setScrollOptions")) {
            const scroller_casted = scroller as (Scroller | undefined)
            this.getPeer()?.setScrollOptionsAttribute(scroller_casted)
            return this
        }
        return this
    }
    /** @memo */
    public scrollable(value: ScrollDirection): this {
        if (this.checkPriority("scrollable")) {
            const value_casted = value as (ScrollDirection)
            this.getPeer()?.scrollableAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onScroll(value: ((first: number, last: number) => void)): this {
        if (this.checkPriority("onScroll")) {
            const value_casted = value as (((first: number, last: number) => void))
            this.getPeer()?.onScrollAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onWillScroll(value?: ScrollOnWillScrollCallback): this {
        if (this.checkPriority("onWillScroll")) {
            const value_casted = value as (ScrollOnWillScrollCallback | undefined)
            this.getPeer()?.onWillScrollAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onDidScroll(value: ScrollOnScrollCallback): this {
        if (this.checkPriority("onDidScroll")) {
            const value_casted = value as (ScrollOnScrollCallback)
            this.getPeer()?.onDidScrollAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onScrollEdge(value: OnScrollEdgeCallback): this {
        if (this.checkPriority("onScrollEdge")) {
            const value_casted = value as (OnScrollEdgeCallback)
            this.getPeer()?.onScrollEdgeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onScrollStart(value: VoidCallback): this {
        if (this.checkPriority("onScrollStart")) {
            const value_casted = value as (VoidCallback)
            this.getPeer()?.onScrollStartAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onScrollEnd(value: (() => void)): this {
        if (this.checkPriority("onScrollEnd")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onScrollEndAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onScrollStop(value: VoidCallback): this {
        if (this.checkPriority("onScrollStop")) {
            const value_casted = value as (VoidCallback)
            this.getPeer()?.onScrollStopAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public scrollBar(value: BarState): this {
        if (this.checkPriority("scrollBar")) {
            const value_casted = value as (BarState)
            this.getPeer()?.scrollBarAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public scrollBarColor(value: Color | number | string): this {
        if (this.checkPriority("scrollBarColor")) {
            const value_casted = value as (Color | number | string)
            this.getPeer()?.scrollBarColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public scrollBarWidth(value: number | string): this {
        if (this.checkPriority("scrollBarWidth")) {
            const value_casted = value as (number | string)
            this.getPeer()?.scrollBarWidthAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onScrollFrameBegin(value: OnScrollFrameBeginCallback): this {
        if (this.checkPriority("onScrollFrameBegin")) {
            const value_casted = value as (OnScrollFrameBeginCallback)
            this.getPeer()?.onScrollFrameBeginAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public nestedScroll(value: NestedScrollOptions): this {
        if (this.checkPriority("nestedScroll")) {
            const value_casted = value as (NestedScrollOptions)
            this.getPeer()?.nestedScrollAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enableScrollInteraction(value: boolean): this {
        if (this.checkPriority("enableScrollInteraction")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableScrollInteractionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public friction(value: number | Resource): this {
        if (this.checkPriority("friction")) {
            const value_casted = value as (number | Resource)
            this.getPeer()?.frictionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public scrollSnap(value: ScrollSnapOptions): this {
        if (this.checkPriority("scrollSnap")) {
            const value_casted = value as (ScrollSnapOptions)
            this.getPeer()?.scrollSnapAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enablePaging(value: boolean): this {
        if (this.checkPriority("enablePaging")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enablePagingAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public initialOffset(value: OffsetOptions): this {
        if (this.checkPriority("initialOffset")) {
            const value_casted = value as (OffsetOptions)
            this.getPeer()?.initialOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public edgeEffect(edgeEffect: EdgeEffect, options?: EdgeEffectOptions): this {
        if (this.checkPriority("edgeEffect")) {
            const edgeEffect_casted = edgeEffect as (EdgeEffect)
            const options_casted = options as (EdgeEffectOptions | undefined)
            this.getPeer()?.edgeEffectAttribute(edgeEffect_casted, options_casted)
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
export function ArkScroll(
  /** @memo */
  style: ((attributes: ArkScrollComponent) => void) | undefined,
  /** @memo */
  content_: (() => void) | undefined,
  scroller?: Scroller | undefined
) {
    const receiver = remember(() => {
        return new ArkScrollComponent()
    })
    NodeAttach<ArkScrollPeer>((): ArkScrollPeer => ArkScrollPeer.create(receiver), (_: ArkScrollPeer) => {
        receiver.setScrollOptions(scroller)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

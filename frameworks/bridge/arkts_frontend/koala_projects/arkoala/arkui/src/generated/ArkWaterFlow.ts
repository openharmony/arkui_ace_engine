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
import { ArkWaterFlowPeer } from "./peers/ArkWaterFlowPeer"
import { ScrollableCommonMethod, CommonMethod, Rectangle, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, UniformDataType, CustomBuilder, DragItemInfo, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, DrawContext, TouchTestInfo, TouchResult, AdaptiveColor, BlurStyleActivePolicy, RepeatMode, LinearGradient_common, FinishCallbackType, ExpectedFrameRateRange, TransitionEffects, TransitionEdge, MotionBlurAnchor, LocalizedHorizontalAlignParam, LocalizedVerticalAlignParam, PreDragStatus, ShadowType, UIGestureEvent, BlurStyleOptions, ThemeColorMode, FractionStop, DragPreviewMode, ImageModifier, OverlayOffset, TransitionHierarchyStrategy, PopupMessageOptions, SymbolGlyphModifier, MenuPreviewMode, ContextMenuAnimationOptions, BindOptions, SheetSize, SheetType, SheetTitleOptions, SheetMode, ScrollSizeMode, UIContext, SheetKeyboardAvoidMode, SourceTool, RectResult, TouchTestStrategy, EventTarget, SourceType, TouchObject, HistoricalPoint, IntentionCode, DragBehavior, Summary, DragResult, DismissPopupAction, DismissContentCoverAction, SheetDismiss, DismissSheetAction, SpringBackAction, DismissReason, NestedScrollOptions, ContentClipMode, EdgeEffectOptions, FadingEdgeOptions } from "./ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage, Area, Bias, Font } from "./ArkUnitsInterfaces"
import { DrawModifier } from "./ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, PixelRoundCalcPolicy, Curve, PlayMode, TransitionType, HorizontalAlign, VerticalAlign, ClickEffectLevel, SharedTransitionEffectType, Placement, ArrowPointPosition, MouseButton, MouseAction, TouchType, KeyType, KeySource, FontWeight, FontStyle, BarState, EdgeEffect, NestedScrollMode, FlexDirection, Edge } from "./ArkEnumsInterfaces"
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
import { ScrollOnWillScrollCallback, ScrollOnScrollCallback, ScrollOptions, ScrollEdgeOptions, ScrollPageOptions, OffsetResult, ScrollAlign, ScrollToIndexOptions, ScrollAnimationOptions } from "./ArkScrollInterfaces"
import { WaterFlowAttribute, WaterFlowOptions, WaterFlowLayoutMode, SectionOptions, GetItemMainSizeByIndex } from "./ArkWaterFlowInterfaces"
import { ScrollState } from "./ArkListInterfaces"
import { Scroller } from "./ArkScrollerMaterialized"
import { WaterFlowSections } from "./ArkWaterFlowSectionsMaterialized"
/** @memo:stable */
export class ArkWaterFlowComponent extends ArkScrollableCommonMethodComponent {
    protected getPeer(): ArkWaterFlowPeer {
        return (this.peer as ArkWaterFlowPeer)
    }
    /** @memo */
    public setWaterFlowOptions(options?: WaterFlowOptions): this {
        if (this.checkPriority("setWaterFlowOptions")) {
            const options_casted = options as (WaterFlowOptions | undefined)
            this.getPeer()?.setWaterFlowOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public columnsTemplate(value: string): this {
        if (this.checkPriority("columnsTemplate")) {
            const value_casted = value as (string)
            this.getPeer()?.columnsTemplateAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public itemConstraintSize(value: ConstraintSizeOptions): this {
        if (this.checkPriority("itemConstraintSize")) {
            const value_casted = value as (ConstraintSizeOptions)
            this.getPeer()?.itemConstraintSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public rowsTemplate(value: string): this {
        if (this.checkPriority("rowsTemplate")) {
            const value_casted = value as (string)
            this.getPeer()?.rowsTemplateAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public columnsGap(value: Length): this {
        if (this.checkPriority("columnsGap")) {
            const value_casted = value as (Length)
            this.getPeer()?.columnsGapAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public rowsGap(value: Length): this {
        if (this.checkPriority("rowsGap")) {
            const value_casted = value as (Length)
            this.getPeer()?.rowsGapAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public layoutDirection(value: FlexDirection): this {
        if (this.checkPriority("layoutDirection")) {
            const value_casted = value as (FlexDirection)
            this.getPeer()?.layoutDirectionAttribute(value_casted)
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
    public cachedCount(count: number, show?: boolean): this {
        if (this.checkPriority("cachedCount")) {
            const count_type = runtimeType(count)
            const show_type = runtimeType(show)
            if (RuntimeType.UNDEFINED == show_type) {
                const value_casted = count as (number)
                this.getPeer()?.cachedCount0Attribute(value_casted)
                return this
            }
            if (RuntimeType.BOOLEAN == show_type) {
                const count_casted = count as (number)
                const show_casted = show as (boolean)
                this.getPeer()?.cachedCount1Attribute(count_casted, show_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public onReachStart(value: (() => void)): this {
        if (this.checkPriority("onReachStart")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onReachStartAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onReachEnd(value: (() => void)): this {
        if (this.checkPriority("onReachEnd")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onReachEndAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onScrollFrameBegin(value: ((offset: number, state: ScrollState) => { offsetRemain: number })): this {
        if (this.checkPriority("onScrollFrameBegin")) {
            const value_casted = value as (((offset: number, state: ScrollState) => { offsetRemain: number }))
            this.getPeer()?.onScrollFrameBeginAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onScrollIndex(value: ((first: number, last: number) => void)): this {
        if (this.checkPriority("onScrollIndex")) {
            const value_casted = value as (((first: number, last: number) => void))
            this.getPeer()?.onScrollIndexAttribute(value_casted)
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
export function ArkWaterFlow(
  /** @memo */
  style: ((attributes: ArkWaterFlowComponent) => void) | undefined,
  /** @memo */
  content_: (() => void) | undefined,
  options?: WaterFlowOptions | undefined
) {
    const receiver = remember(() => {
        return new ArkWaterFlowComponent()
    })
    NodeAttach<ArkWaterFlowPeer>((): ArkWaterFlowPeer => ArkWaterFlowPeer.create(receiver), (_: ArkWaterFlowPeer) => {
        receiver.setWaterFlowOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

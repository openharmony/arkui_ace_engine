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
import { ArkTabsPeer } from "./peers/ArkTabsPeer"
import { CommonMethod, Rectangle, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, UniformDataType, CustomBuilder, DragItemInfo, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, DrawContext, TouchTestInfo, TouchResult, AdaptiveColor, BlurStyleActivePolicy, RepeatMode, LinearGradient_common, FinishCallbackType, ExpectedFrameRateRange, TransitionEffects, TransitionEdge, MotionBlurAnchor, LocalizedHorizontalAlignParam, LocalizedVerticalAlignParam, PreDragStatus, ShadowType, UIGestureEvent, BlurStyleOptions, ThemeColorMode, FractionStop, DragPreviewMode, ImageModifier, OverlayOffset, TransitionHierarchyStrategy, PopupMessageOptions, SymbolGlyphModifier, MenuPreviewMode, ContextMenuAnimationOptions, BindOptions, SheetSize, SheetType, SheetTitleOptions, SheetMode, ScrollSizeMode, UIContext, SheetKeyboardAvoidMode, SourceTool, RectResult, TouchTestStrategy, EventTarget, SourceType, TouchObject, HistoricalPoint, IntentionCode, DragBehavior, Summary, DragResult, DismissPopupAction, DismissContentCoverAction, SheetDismiss, DismissSheetAction, SpringBackAction, DismissReason } from "./ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage, Area, Bias, Font } from "./ArkUnitsInterfaces"
import { DrawModifier } from "./ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, PixelRoundCalcPolicy, Curve, PlayMode, TransitionType, HorizontalAlign, VerticalAlign, ClickEffectLevel, SharedTransitionEffectType, Placement, ArrowPointPosition, MouseButton, MouseAction, TouchType, KeyType, KeySource, FontWeight, FontStyle, EdgeEffect } from "./ArkEnumsInterfaces"
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
import { BarPosition, BarMode, AnimationMode, OnTabsAnimationStartCallback, OnTabsAnimationEndCallback, OnTabsGestureSwipeCallback, DividerStyle, BarGridColumnOptions, TabsCustomContentTransitionCallback, OnTabsContentWillChangeCallback, ScrollableBarModeOptions, TabsAttribute, LayoutStyle, TabsOptions } from "./ArkTabsInterfaces"
import { TabsController } from "./ArkTabsControllerMaterialized"
/** @memo:stable */
export class ArkTabsComponent extends ArkCommonMethodComponent {
    protected getPeer(): ArkTabsPeer {
        return (this.peer as ArkTabsPeer)
    }
    /** @memo */
    public setTabsOptions(options?: TabsOptions): this {
        if (this.checkPriority("setTabsOptions")) {
            const options_casted = options as (TabsOptions | undefined)
            this.getPeer()?.setTabsOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public vertical(value: boolean): this {
        if (this.checkPriority("vertical")) {
            const value_casted = value as (boolean)
            this.getPeer()?.verticalAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public barPosition(value: BarPosition): this {
        if (this.checkPriority("barPosition")) {
            const value_casted = value as (BarPosition)
            this.getPeer()?.barPositionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public scrollable(value: boolean): this {
        if (this.checkPriority("scrollable")) {
            const value_casted = value as (boolean)
            this.getPeer()?.scrollableAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public barMode(value: BarMode, options?: ScrollableBarModeOptions): this {
        if (this.checkPriority("barMode")) {
            const value_type = runtimeType(value)
            const options_type = runtimeType(options)
            if ((((RuntimeType.NUMBER) == (value_type)) && ((unsafeCast<int32>(value)) >= (0)) && ((unsafeCast<int32>(value)) <= (1))) && (RuntimeType.UNDEFINED == options_type)) {
                const value_casted = value as (BarMode)
                this.getPeer()?.barMode0Attribute(value_casted)
                return this
            }
            if ((((RuntimeType.NUMBER) == (value_type)) && ((unsafeCast<int32>(value)) >= (0)) && ((unsafeCast<int32>(value)) <= (1))) && ((RuntimeType.OBJECT == options_type) || (RuntimeType.UNDEFINED == options_type))) {
                const value_casted = value as (BarMode)
                const options_casted = options as (ScrollableBarModeOptions | undefined)
                this.getPeer()?.barMode1Attribute(value_casted, options_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public barWidth(value: Length): this {
        if (this.checkPriority("barWidth")) {
            const value_casted = value as (Length)
            this.getPeer()?.barWidthAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public barHeight(value: Length): this {
        if (this.checkPriority("barHeight")) {
            const value_casted = value as (Length)
            this.getPeer()?.barHeightAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public animationDuration(value: number): this {
        if (this.checkPriority("animationDuration")) {
            const value_casted = value as (number)
            this.getPeer()?.animationDurationAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public animationMode(value?: AnimationMode): this {
        if (this.checkPriority("animationMode")) {
            const value_casted = value as (AnimationMode | undefined)
            this.getPeer()?.animationModeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public edgeEffect(value?: EdgeEffect): this {
        if (this.checkPriority("edgeEffect")) {
            const value_casted = value as (EdgeEffect | undefined)
            this.getPeer()?.edgeEffectAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onChange(value: ((index: number) => void)): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((index: number) => void))
            this.getPeer()?.onChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onTabBarClick(value: ((index: number) => void)): this {
        if (this.checkPriority("onTabBarClick")) {
            const value_casted = value as (((index: number) => void))
            this.getPeer()?.onTabBarClickAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onAnimationStart(value: OnTabsAnimationStartCallback): this {
        if (this.checkPriority("onAnimationStart")) {
            const value_casted = value as (OnTabsAnimationStartCallback)
            this.getPeer()?.onAnimationStartAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onAnimationEnd(value: OnTabsAnimationEndCallback): this {
        if (this.checkPriority("onAnimationEnd")) {
            const value_casted = value as (OnTabsAnimationEndCallback)
            this.getPeer()?.onAnimationEndAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onGestureSwipe(value: OnTabsGestureSwipeCallback): this {
        if (this.checkPriority("onGestureSwipe")) {
            const value_casted = value as (OnTabsGestureSwipeCallback)
            this.getPeer()?.onGestureSwipeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fadingEdge(value: boolean): this {
        if (this.checkPriority("fadingEdge")) {
            const value_casted = value as (boolean)
            this.getPeer()?.fadingEdgeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public divider(value?: DividerStyle): this {
        if (this.checkPriority("divider")) {
            const value_casted = value as (DividerStyle | undefined)
            this.getPeer()?.dividerAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public barOverlap(value: boolean): this {
        if (this.checkPriority("barOverlap")) {
            const value_casted = value as (boolean)
            this.getPeer()?.barOverlapAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public barBackgroundColor(value: ResourceColor): this {
        if (this.checkPriority("barBackgroundColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.barBackgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public barGridAlign(value: BarGridColumnOptions): this {
        if (this.checkPriority("barGridAlign")) {
            const value_casted = value as (BarGridColumnOptions)
            this.getPeer()?.barGridAlignAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public customContentTransition(value: TabsCustomContentTransitionCallback): this {
        if (this.checkPriority("customContentTransition")) {
            const value_casted = value as (TabsCustomContentTransitionCallback)
            this.getPeer()?.customContentTransitionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public barBackgroundBlurStyle(style: BlurStyle, options?: BackgroundBlurStyleOptions): this {
        if (this.checkPriority("barBackgroundBlurStyle")) {
            const style_type = runtimeType(style)
            const options_type = runtimeType(options)
            if ((((RuntimeType.NUMBER) == (style_type)) && ((unsafeCast<int32>(style)) >= (0)) && ((unsafeCast<int32>(style)) <= (12))) && (RuntimeType.UNDEFINED == options_type)) {
                const value_casted = style as (BlurStyle)
                this.getPeer()?.barBackgroundBlurStyle0Attribute(value_casted)
                return this
            }
            if ((((RuntimeType.NUMBER) == (style_type)) && ((unsafeCast<int32>(style)) >= (0)) && ((unsafeCast<int32>(style)) <= (12))) && (RuntimeType.OBJECT == options_type)) {
                const style_casted = style as (BlurStyle)
                const options_casted = options as (BackgroundBlurStyleOptions)
                this.getPeer()?.barBackgroundBlurStyle1Attribute(style_casted, options_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public barBackgroundEffect(value: BackgroundEffectOptions): this {
        if (this.checkPriority("barBackgroundEffect")) {
            const value_casted = value as (BackgroundEffectOptions)
            this.getPeer()?.barBackgroundEffectAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onContentWillChange(value: OnTabsContentWillChangeCallback): this {
        if (this.checkPriority("onContentWillChange")) {
            const value_casted = value as (OnTabsContentWillChangeCallback)
            this.getPeer()?.onContentWillChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public barModeScrollable(options: ScrollableBarModeOptions): this {
        if (this.checkPriority("barModeScrollable")) {
            const options_casted = options as (ScrollableBarModeOptions)
            this.getPeer()?.barModeScrollableAttribute(options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public _onChangeEvent_index(callback: ((index: number) => void)): void {
        if (this.checkPriority("_onChangeEvent_index")) {
            const callback_casted = callback as (((index: number) => void))
            this.getPeer()?._onChangeEvent_indexAttribute(callback_casted)
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
export function ArkTabs(
  /** @memo */
  style: ((attributes: ArkTabsComponent) => void) | undefined,
  /** @memo */
  content_: (() => void) | undefined,
  options?: TabsOptions | undefined
) {
    const receiver = remember(() => {
        return new ArkTabsComponent()
    })
    NodeAttach<ArkTabsPeer>((): ArkTabsPeer => ArkTabsPeer.create(receiver), (_: ArkTabsPeer) => {
        receiver.setTabsOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

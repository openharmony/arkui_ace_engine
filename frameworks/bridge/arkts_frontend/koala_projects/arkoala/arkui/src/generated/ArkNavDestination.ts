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
import { ArkNavDestinationPeer } from "./peers/ArkNavDestinationPeer"
import { CommonMethod, Rectangle, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, UniformDataType, CustomBuilder, DragItemInfo, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, DrawContext, TouchTestInfo, TouchResult, AdaptiveColor, BlurStyleActivePolicy, RepeatMode, LinearGradient_common, FinishCallbackType, ExpectedFrameRateRange, TransitionEffects, TransitionEdge, MotionBlurAnchor, LocalizedHorizontalAlignParam, LocalizedVerticalAlignParam, PreDragStatus, ShadowType, UIGestureEvent, BlurStyleOptions, ThemeColorMode, FractionStop, DragPreviewMode, ImageModifier, OverlayOffset, TransitionHierarchyStrategy, PopupMessageOptions, SymbolGlyphModifier, MenuPreviewMode, ContextMenuAnimationOptions, BindOptions, SheetSize, SheetType, SheetTitleOptions, SheetMode, ScrollSizeMode, UIContext, SheetKeyboardAvoidMode, SourceTool, RectResult, TouchTestStrategy, EventTarget, SourceType, TouchObject, HistoricalPoint, IntentionCode, DragBehavior, Summary, DragResult, DismissPopupAction, DismissContentCoverAction, SheetDismiss, DismissSheetAction, SpringBackAction, DismissReason, LayoutSafeAreaType, LayoutSafeAreaEdge } from "./ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage, Area, Bias, Font } from "./ArkUnitsInterfaces"
import { DrawModifier } from "./ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, PixelRoundCalcPolicy, Curve, PlayMode, TransitionType, HorizontalAlign, VerticalAlign, ClickEffectLevel, SharedTransitionEffectType, Placement, ArrowPointPosition, MouseButton, MouseAction, TouchType, KeyType, KeySource, FontWeight, FontStyle, TitleHeight } from "./ArkEnumsInterfaces"
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
import { LengthUnit, ShapeSize, PathShapeOptions, RectShapeOptions, RoundRectShapeOptions, TextModifier } from "./ArkArkuiExternalInterfaces"
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
import { NavDestinationMode, NavigationSystemTransitionType, NavDestinationCommonTitle, NavDestinationCustomTitle, NavDestinationAttribute, RouteMapConfig } from "./ArkNavDestinationInterfaces"
import { NavigationMenuItem, SystemBarStyle, NavigationTitleOptions, ToolbarItem, NavigationToolbarOptions, BarStyle, ToolbarItemStatus, NavigationOptions, NavigationInterception, PopInfo, LaunchMode, InterceptionShowCallback, InterceptionModeCallback } from "./ArkNavigationInterfaces"
import { NavDestinationContext } from "./ArkNavDestinationContextMaterialized"
import { NavPathInfo } from "./ArkNavPathInfoMaterialized"
import { NavPathStack } from "./ArkNavPathStackMaterialized"
/** @memo:stable */
export class ArkNavDestinationComponent extends ArkCommonMethodComponent {
    protected getPeer(): ArkNavDestinationPeer {
        return (this.peer as ArkNavDestinationPeer)
    }
    /** @memo */
    public setNavDestinationOptions(): this {
        if (this.checkPriority("setNavDestinationOptions")) {
            this.getPeer()?.setNavDestinationOptionsAttribute()
            return this
        }
        return this
    }
    /** @memo */
    public hideTitleBar(hide: boolean, animated?: boolean): this {
        if (this.checkPriority("hideTitleBar")) {
            const hide_type = runtimeType(hide)
            const animated_type = runtimeType(animated)
            if (RuntimeType.UNDEFINED == animated_type) {
                const value_casted = hide as (boolean)
                this.getPeer()?.hideTitleBar0Attribute(value_casted)
                return this
            }
            if (RuntimeType.BOOLEAN == animated_type) {
                const hide_casted = hide as (boolean)
                const animated_casted = animated as (boolean)
                this.getPeer()?.hideTitleBar1Attribute(hide_casted, animated_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public onShown(value: (() => void)): this {
        if (this.checkPriority("onShown")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onShownAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onHidden(value: (() => void)): this {
        if (this.checkPriority("onHidden")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onHiddenAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onBackPressed(value: (() => boolean)): this {
        if (this.checkPriority("onBackPressed")) {
            const value_casted = value as ((() => boolean))
            this.getPeer()?.onBackPressedAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public mode(value: NavDestinationMode): this {
        if (this.checkPriority("mode")) {
            const value_casted = value as (NavDestinationMode)
            this.getPeer()?.modeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public backButtonIcon(value: ResourceStr | PixelMap | SymbolGlyphModifier): this {
        if (this.checkPriority("backButtonIcon")) {
            const value_casted = value as (ResourceStr | PixelMap | SymbolGlyphModifier)
            this.getPeer()?.backButtonIconAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public menus(value: Array<NavigationMenuItem> | CustomBuilder): this {
        if (this.checkPriority("menus")) {
            const value_casted = value as (Array<NavigationMenuItem> | CustomBuilder)
            this.getPeer()?.menusAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onReady(value: ((parameter: NavDestinationContext) => void)): this {
        if (this.checkPriority("onReady")) {
            const value_casted = value as (((parameter: NavDestinationContext) => void))
            this.getPeer()?.onReadyAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onWillAppear(value: (() => void)): this {
        if (this.checkPriority("onWillAppear")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onWillAppearAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onWillDisappear(value: (() => void)): this {
        if (this.checkPriority("onWillDisappear")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onWillDisappearAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onWillShow(value: (() => void)): this {
        if (this.checkPriority("onWillShow")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onWillShowAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onWillHide(value: (() => void)): this {
        if (this.checkPriority("onWillHide")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onWillHideAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public systemBarStyle(value?: SystemBarStyle): this {
        if (this.checkPriority("systemBarStyle")) {
            const value_casted = value as (SystemBarStyle | undefined)
            this.getPeer()?.systemBarStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public recoverable(value?: boolean): this {
        if (this.checkPriority("recoverable")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.recoverableAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public systemTransition(value: NavigationSystemTransitionType): this {
        if (this.checkPriority("systemTransition")) {
            const value_casted = value as (NavigationSystemTransitionType)
            this.getPeer()?.systemTransitionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public title(value: string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource, options?: NavigationTitleOptions): this {
        if (this.checkPriority("title")) {
            const value_casted = value as (string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource)
            const options_casted = options as (NavigationTitleOptions | undefined)
            this.getPeer()?.titleAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public toolbarConfiguration(toolbarParam: Array<ToolbarItem> | CustomBuilder, options?: NavigationToolbarOptions): this {
        if (this.checkPriority("toolbarConfiguration")) {
            const toolbarParam_casted = toolbarParam as (Array<ToolbarItem> | CustomBuilder)
            const options_casted = options as (NavigationToolbarOptions | undefined)
            this.getPeer()?.toolbarConfigurationAttribute(toolbarParam_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public hideToolBar(hide: boolean, animated?: boolean): this {
        if (this.checkPriority("hideToolBar")) {
            const hide_casted = hide as (boolean)
            const animated_casted = animated as (boolean | undefined)
            this.getPeer()?.hideToolBarAttribute(hide_casted, animated_casted)
            return this
        }
        return this
    }
    /** @memo */
    public ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): this {
        if (this.checkPriority("ignoreLayoutSafeArea")) {
            const types_casted = types as (Array<LayoutSafeAreaType> | undefined)
            const edges_casted = edges as (Array<LayoutSafeAreaEdge> | undefined)
            this.getPeer()?.ignoreLayoutSafeAreaAttribute(types_casted, edges_casted)
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
export function ArkNavDestination(
  /** @memo */
  style: ((attributes: ArkNavDestinationComponent) => void) | undefined,
  /** @memo */
  content_: (() => void) | undefined,
  
) {
    const receiver = remember(() => {
        return new ArkNavDestinationComponent()
    })
    NodeAttach<ArkNavDestinationPeer>((): ArkNavDestinationPeer => ArkNavDestinationPeer.create(receiver), (_: ArkNavDestinationPeer) => {
        receiver.setNavDestinationOptions()
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

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
import { ArkSideBarContainerPeer } from "./peers/ArkSidebarPeer"
import { CommonMethod, Rectangle, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, UniformDataType, CustomBuilder, DragItemInfo, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, DrawContext, TouchTestInfo, TouchResult, AdaptiveColor, BlurStyleActivePolicy, RepeatMode, LinearGradient_common, FinishCallbackType, ExpectedFrameRateRange, TransitionEffects, TransitionEdge, MotionBlurAnchor, LocalizedHorizontalAlignParam, LocalizedVerticalAlignParam, PreDragStatus, ShadowType, UIGestureEvent, BlurStyleOptions, ThemeColorMode, FractionStop, DragPreviewMode, ImageModifier, OverlayOffset, TransitionHierarchyStrategy, PopupMessageOptions, SymbolGlyphModifier, MenuPreviewMode, ContextMenuAnimationOptions, BindOptions, SheetSize, SheetType, SheetTitleOptions, SheetMode, ScrollSizeMode, UIContext, SheetKeyboardAvoidMode, SourceTool, RectResult, TouchTestStrategy, EventTarget, SourceType, TouchObject, HistoricalPoint, IntentionCode, DragBehavior, Summary, DragResult, DismissPopupAction, DismissContentCoverAction, SheetDismiss, DismissSheetAction, SpringBackAction, DismissReason } from "./ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage, Area, Bias, Font } from "./ArkUnitsInterfaces"
import { DrawModifier } from "./ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, PixelRoundCalcPolicy, Curve, PlayMode, TransitionType, HorizontalAlign, VerticalAlign, ClickEffectLevel, SharedTransitionEffectType, Placement, ArrowPointPosition, MouseButton, MouseAction, TouchType, KeyType, KeySource, FontWeight, FontStyle } from "./ArkEnumsInterfaces"
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
import { ButtonStyle, SideBarPosition, ButtonIconOptions, SideBarContainerType, SideBarContainerAttribute } from "./ArkSidebarInterfaces"
import { DividerStyle } from "./ArkTabsInterfaces"
/** @memo:stable */
export class ArkSideBarContainerComponent extends ArkCommonMethodComponent {
    protected getPeer(): ArkSideBarContainerPeer {
        return (this.peer as ArkSideBarContainerPeer)
    }
    /** @memo */
    public setSideBarContainerOptions(type?: SideBarContainerType): this {
        if (this.checkPriority("setSideBarContainerOptions")) {
            const type_casted = type as (SideBarContainerType | undefined)
            this.getPeer()?.setSideBarContainerOptionsAttribute(type_casted)
            return this
        }
        return this
    }
    /** @memo */
    public showSideBar(value: boolean): this {
        if (this.checkPriority("showSideBar")) {
            const value_casted = value as (boolean)
            this.getPeer()?.showSideBarAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public controlButton(value: ButtonStyle): this {
        if (this.checkPriority("controlButton")) {
            const value_casted = value as (ButtonStyle)
            this.getPeer()?.controlButtonAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public showControlButton(value: boolean): this {
        if (this.checkPriority("showControlButton")) {
            const value_casted = value as (boolean)
            this.getPeer()?.showControlButtonAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onChange(value: ((parameter: boolean) => void)): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((parameter: boolean) => void))
            this.getPeer()?.onChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public sideBarWidth(value: number | Length): this {
        if (this.checkPriority("sideBarWidth")) {
            const value_type = runtimeType(value)
            if (RuntimeType.NUMBER == value_type) {
                const value_casted = value as (number)
                this.getPeer()?.sideBarWidth0Attribute(value_casted)
                return this
            }
            if (((RuntimeType.NUMBER) == (value_type)) || ((RuntimeType.STRING) == (value_type)) || (((RuntimeType.OBJECT) == (value_type)) && (isResource(value)))) {
                const value_casted = value as (Length)
                this.getPeer()?.sideBarWidth1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public minSideBarWidth(value: number | Length): this {
        if (this.checkPriority("minSideBarWidth")) {
            const value_type = runtimeType(value)
            if (RuntimeType.NUMBER == value_type) {
                const value_casted = value as (number)
                this.getPeer()?.minSideBarWidth0Attribute(value_casted)
                return this
            }
            if (((RuntimeType.NUMBER) == (value_type)) || ((RuntimeType.STRING) == (value_type)) || (((RuntimeType.OBJECT) == (value_type)) && (isResource(value)))) {
                const value_casted = value as (Length)
                this.getPeer()?.minSideBarWidth1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public maxSideBarWidth(value: number | Length): this {
        if (this.checkPriority("maxSideBarWidth")) {
            const value_type = runtimeType(value)
            if (RuntimeType.NUMBER == value_type) {
                const value_casted = value as (number)
                this.getPeer()?.maxSideBarWidth0Attribute(value_casted)
                return this
            }
            if (((RuntimeType.NUMBER) == (value_type)) || ((RuntimeType.STRING) == (value_type)) || (((RuntimeType.OBJECT) == (value_type)) && (isResource(value)))) {
                const value_casted = value as (Length)
                this.getPeer()?.maxSideBarWidth1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public autoHide(value: boolean): this {
        if (this.checkPriority("autoHide")) {
            const value_casted = value as (boolean)
            this.getPeer()?.autoHideAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public sideBarPosition(value: SideBarPosition): this {
        if (this.checkPriority("sideBarPosition")) {
            const value_casted = value as (SideBarPosition)
            this.getPeer()?.sideBarPositionAttribute(value_casted)
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
    public minContentWidth(value: Dimension): this {
        if (this.checkPriority("minContentWidth")) {
            const value_casted = value as (Dimension)
            this.getPeer()?.minContentWidthAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public _onChangeEvent_showSideBar(callback: ((parameter: boolean) => void)): void {
        if (this.checkPriority("_onChangeEvent_showSideBar")) {
            const callback_casted = callback as (((parameter: boolean) => void))
            this.getPeer()?._onChangeEvent_showSideBarAttribute(callback_casted)
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
export function ArkSideBarContainer(
  /** @memo */
  style: ((attributes: ArkSideBarContainerComponent) => void) | undefined,
  /** @memo */
  content_: (() => void) | undefined,
  type?: SideBarContainerType | undefined
) {
    const receiver = remember(() => {
        return new ArkSideBarContainerComponent()
    })
    NodeAttach<ArkSideBarContainerPeer>((): ArkSideBarContainerPeer => ArkSideBarContainerPeer.create(receiver), (_: ArkSideBarContainerPeer) => {
        receiver.setSideBarContainerOptions(type)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

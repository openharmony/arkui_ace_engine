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
import { ArkSelectPeer } from "./peers/ArkSelectPeer"
import { CommonMethod, Rectangle, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, UniformDataType, CustomBuilder, DragItemInfo, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, DrawContext, TouchTestInfo, TouchResult, AdaptiveColor, BlurStyleActivePolicy, RepeatMode, LinearGradient_common, FinishCallbackType, ExpectedFrameRateRange, TransitionEffects, TransitionEdge, MotionBlurAnchor, LocalizedHorizontalAlignParam, LocalizedVerticalAlignParam, PreDragStatus, ShadowType, UIGestureEvent, BlurStyleOptions, ThemeColorMode, FractionStop, DragPreviewMode, ImageModifier, OverlayOffset, TransitionHierarchyStrategy, PopupMessageOptions, SymbolGlyphModifier, MenuPreviewMode, ContextMenuAnimationOptions, BindOptions, SheetSize, SheetType, SheetTitleOptions, SheetMode, ScrollSizeMode, UIContext, SheetKeyboardAvoidMode, SourceTool, RectResult, TouchTestStrategy, EventTarget, SourceType, TouchObject, HistoricalPoint, IntentionCode, DragBehavior, Summary, DragResult, DismissPopupAction, DismissContentCoverAction, SheetDismiss, DismissSheetAction, SpringBackAction, DismissReason, ContentModifier, CommonConfiguration } from "./ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage, Area, Bias, Font, Offset } from "./ArkUnitsInterfaces"
import { DrawModifier } from "./ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, PixelRoundCalcPolicy, Curve, PlayMode, TransitionType, HorizontalAlign, VerticalAlign, ClickEffectLevel, SharedTransitionEffectType, Placement, ArrowPointPosition, MouseButton, MouseAction, TouchType, KeyType, KeySource, FontWeight, FontStyle, OptionWidthMode } from "./ArkEnumsInterfaces"
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
import { ArrowPosition, MenuItemConfiguration, MenuAlignType, SelectAttribute, SelectOption } from "./ArkSelectInterfaces"
import { ControlSize } from "./ArkButtonInterfaces"
import { DividerOptions } from "./ArkTextPickerInterfaces"
/** @memo:stable */
export class ArkSelectComponent extends ArkCommonMethodComponent {
    protected getPeer(): ArkSelectPeer {
        return (this.peer as ArkSelectPeer)
    }
    /** @memo */
    public setSelectOptions(options: Array<SelectOption>): this {
        if (this.checkPriority("setSelectOptions")) {
            const options_casted = options as (Array<SelectOption>)
            this.getPeer()?.setSelectOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public selected(value: number | Resource): this {
        if (this.checkPriority("selected")) {
            const value_casted = value as (number | Resource)
            this.getPeer()?.selectedAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public value(value: ResourceStr): this {
        if (this.checkPriority("value")) {
            const value_casted = value as (ResourceStr)
            this.getPeer()?.valueAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public font(value: Font): this {
        if (this.checkPriority("font")) {
            const value_casted = value as (Font)
            this.getPeer()?.fontAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontColor(value: ResourceColor): this {
        if (this.checkPriority("fontColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.fontColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public selectedOptionBgColor(value: ResourceColor): this {
        if (this.checkPriority("selectedOptionBgColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.selectedOptionBgColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public selectedOptionFont(value: Font): this {
        if (this.checkPriority("selectedOptionFont")) {
            const value_casted = value as (Font)
            this.getPeer()?.selectedOptionFontAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public selectedOptionFontColor(value: ResourceColor): this {
        if (this.checkPriority("selectedOptionFontColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.selectedOptionFontColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public optionBgColor(value: ResourceColor): this {
        if (this.checkPriority("optionBgColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.optionBgColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public optionFont(value: Font): this {
        if (this.checkPriority("optionFont")) {
            const value_casted = value as (Font)
            this.getPeer()?.optionFontAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public optionFontColor(value: ResourceColor): this {
        if (this.checkPriority("optionFontColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.optionFontColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onSelect(value: ((index: number, value: string) => void)): this {
        if (this.checkPriority("onSelect")) {
            const value_casted = value as (((index: number, value: string) => void))
            this.getPeer()?.onSelectAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public space(value: Length): this {
        if (this.checkPriority("space")) {
            const value_casted = value as (Length)
            this.getPeer()?.spaceAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public arrowPosition(value: ArrowPosition): this {
        if (this.checkPriority("arrowPosition")) {
            const value_casted = value as (ArrowPosition)
            this.getPeer()?.arrowPositionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public optionWidth(value: Dimension | OptionWidthMode): this {
        if (this.checkPriority("optionWidth")) {
            const value_casted = value as (Dimension | OptionWidthMode)
            this.getPeer()?.optionWidthAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public optionHeight(value: Dimension): this {
        if (this.checkPriority("optionHeight")) {
            const value_casted = value as (Dimension)
            this.getPeer()?.optionHeightAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public menuBackgroundColor(value: ResourceColor): this {
        if (this.checkPriority("menuBackgroundColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.menuBackgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public menuBackgroundBlurStyle(value: BlurStyle): this {
        if (this.checkPriority("menuBackgroundBlurStyle")) {
            const value_casted = value as (BlurStyle)
            this.getPeer()?.menuBackgroundBlurStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public controlSize(value: ControlSize): this {
        if (this.checkPriority("controlSize")) {
            const value_casted = value as (ControlSize)
            this.getPeer()?.controlSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public menuItemContentModifier(value: ContentModifier<any>): this {
        if (this.checkPriority("menuItemContentModifier")) {
            const value_casted = value as (ContentModifier<any>)
            this.getPeer()?.menuItemContentModifierAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public divider(value?: DividerOptions): this {
        if (this.checkPriority("divider")) {
            const value_casted = value as (DividerOptions | undefined)
            this.getPeer()?.dividerAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public menuAlign(alignType: MenuAlignType, offset?: Offset): this {
        if (this.checkPriority("menuAlign")) {
            const alignType_casted = alignType as (MenuAlignType)
            const offset_casted = offset as (Offset | undefined)
            this.getPeer()?.menuAlignAttribute(alignType_casted, offset_casted)
            return this
        }
        return this
    }
    /** @memo */
    public _onChangeEvent_selected(callback: ((selected: number | Resource) => void)): void {
        if (this.checkPriority("_onChangeEvent_selected")) {
            const callback_casted = callback as (((selected: number | Resource) => void))
            this.getPeer()?._onChangeEvent_selectedAttribute(callback_casted)
            return
        }
        return
    }
    /** @memo */
    public _onChangeEvent_value(callback: ((value: ResourceStr) => void)): void {
        if (this.checkPriority("_onChangeEvent_value")) {
            const callback_casted = callback as (((value: ResourceStr) => void))
            this.getPeer()?._onChangeEvent_valueAttribute(callback_casted)
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
export function ArkSelect(
  /** @memo */
  style: ((attributes: ArkSelectComponent) => void) | undefined,
  /** @memo */
  content_: (() => void) | undefined,
  options: Array<SelectOption>
) {
    const receiver = remember(() => {
        return new ArkSelectComponent()
    })
    NodeAttach<ArkSelectPeer>((): ArkSelectPeer => ArkSelectPeer.create(receiver), (_: ArkSelectPeer) => {
        receiver.setSelectOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

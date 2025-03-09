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
import { ArkButtonPeer } from "./peers/ArkButtonPeer"
import { CommonMethod, Rectangle, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, UniformDataType, CustomBuilder, DragItemInfo, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, ContentModifier, DrawContext, TouchTestInfo, TouchResult, AdaptiveColor, BlurStyleActivePolicy, RepeatMode, LinearGradient_common, FinishCallbackType, ExpectedFrameRateRange, TransitionEffects, TransitionEdge, MotionBlurAnchor, LocalizedHorizontalAlignParam, LocalizedVerticalAlignParam, PreDragStatus, ShadowType, UIGestureEvent, BlurStyleOptions, ThemeColorMode, FractionStop, DragPreviewMode, ImageModifier, OverlayOffset, TransitionHierarchyStrategy, PopupMessageOptions, SymbolGlyphModifier, MenuPreviewMode, ContextMenuAnimationOptions, BindOptions, SheetSize, SheetType, SheetTitleOptions, SheetMode, ScrollSizeMode, UIContext, SheetKeyboardAvoidMode, CommonConfiguration, SourceTool, RectResult, TouchTestStrategy, EventTarget, SourceType, TouchObject, HistoricalPoint, IntentionCode, DragBehavior, Summary, DragResult, DismissPopupAction, DismissContentCoverAction, SheetDismiss, DismissSheetAction, SpringBackAction, DismissReason } from "./ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage, Area, Bias, Font } from "./ArkUnitsInterfaces"
import { DrawModifier } from "./ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, FontWeight, FontStyle, PixelRoundCalcPolicy, Curve, PlayMode, TransitionType, HorizontalAlign, VerticalAlign, ClickEffectLevel, SharedTransitionEffectType, Placement, ArrowPointPosition, TextOverflow, TextHeightAdaptivePolicy, MouseButton, MouseAction, TouchType, KeyType, KeySource } from "./ArkEnumsInterfaces"
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
import { ButtonType, ButtonStyleMode, ControlSize, ButtonRole, ButtonConfiguration, LabelStyle, ButtonTriggerClickCallback, ButtonAttribute, ButtonOptions } from "./ArkButtonInterfaces"
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
/** @memo:stable */
export class ArkButtonComponent extends ArkCommonMethodComponent {
    protected getPeer(): ArkButtonPeer {
        return (this.peer as ArkButtonPeer)
    }
    /** @memo */
    public setButtonOptions(label?: ButtonOptions | ResourceStr, options?: ButtonOptions): this {
        if (this.checkPriority("setButtonOptions")) {
            const label_type = runtimeType(label)
            const options_type = runtimeType(options)
            if ((RuntimeType.UNDEFINED == label_type) && (RuntimeType.UNDEFINED == options_type)) {
                this.getPeer()?.setButtonOptions0Attribute()
                return this
            }
            if ((((RuntimeType.OBJECT) == (label_type)) && (((label!.hasOwnProperty("type")) || (label!.hasOwnProperty("stateEffect")) || (label!.hasOwnProperty("buttonStyle")) || (label!.hasOwnProperty("controlSize")) || (label!.hasOwnProperty("role"))))) && (RuntimeType.UNDEFINED == options_type)) {
                const options_casted = label as (ButtonOptions)
                this.getPeer()?.setButtonOptions1Attribute(options_casted)
                return this
            }
            if (((RuntimeType.STRING == label_type) || (RuntimeType.OBJECT == label_type)) && ((RuntimeType.OBJECT == options_type) || (RuntimeType.UNDEFINED == options_type))) {
                const label_casted = label as (ResourceStr)
                const options_casted = options as (ButtonOptions | undefined)
                this.getPeer()?.setButtonOptions2Attribute(label_casted, options_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public type(value: ButtonType): this {
        if (this.checkPriority("type")) {
            const value_casted = value as (ButtonType)
            this.getPeer()?.typeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public stateEffect(value: boolean): this {
        if (this.checkPriority("stateEffect")) {
            const value_casted = value as (boolean)
            this.getPeer()?.stateEffectAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public buttonStyle(value: ButtonStyleMode): this {
        if (this.checkPriority("buttonStyle")) {
            const value_casted = value as (ButtonStyleMode)
            this.getPeer()?.buttonStyleAttribute(value_casted)
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
    public role(value: ButtonRole): this {
        if (this.checkPriority("role")) {
            const value_casted = value as (ButtonRole)
            this.getPeer()?.roleAttribute(value_casted)
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
    public fontSize(value: Length): this {
        if (this.checkPriority("fontSize")) {
            const value_casted = value as (Length)
            this.getPeer()?.fontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontWeight(value: number | FontWeight | string): this {
        if (this.checkPriority("fontWeight")) {
            const value_casted = value as (number | FontWeight | string)
            this.getPeer()?.fontWeightAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontStyle(value: FontStyle): this {
        if (this.checkPriority("fontStyle")) {
            const value_casted = value as (FontStyle)
            this.getPeer()?.fontStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontFamily(value: string | Resource): this {
        if (this.checkPriority("fontFamily")) {
            const value_casted = value as (string | Resource)
            this.getPeer()?.fontFamilyAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public contentModifier(value: ContentModifier<any>): this {
        if (this.checkPriority("contentModifier")) {
            const value_casted = value as (ContentModifier<any>)
            this.getPeer()?.contentModifierAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public labelStyle(value: LabelStyle): this {
        if (this.checkPriority("labelStyle")) {
            const value_casted = value as (LabelStyle)
            this.getPeer()?.labelStyleAttribute(value_casted)
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
export function ArkButton(
  /** @memo */
  style: ((attributes: ArkButtonComponent) => void) | undefined,
  /** @memo */
  content_: (() => void) | undefined,
  label?: ButtonOptions | ResourceStr | undefined, options?: ButtonOptions | undefined
) {
    const receiver = remember(() => {
        return new ArkButtonComponent()
    })
    NodeAttach<ArkButtonPeer>((): ArkButtonPeer => ArkButtonPeer.create(receiver), (_: ArkButtonPeer) => {
        receiver.setButtonOptions(label,options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

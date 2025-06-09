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
import { ArkBaseSpanPeer, ArkSpanPeer } from "./peers/ArkSpanPeer"
import { CommonMethod, Rectangle, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, CustomBuilder, DragItemInfo, UniformDataType, PreDragStatus, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback } from "./ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, Font } from "./ArkUnitsInterfaces"
import { DrawModifier } from "./ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, FontStyle, FontWeight, TextCase } from "./ArkEnumsInterfaces"
import { Callback_Array_TouchTestInfo_TouchResult, Callback_ClickEvent_Void, Callback_Boolean_HoverEvent_Void, Callback_MouseEvent_Void, Callback_TouchEvent_Void, Callback_KeyEvent_Void, Callback_KeyEvent_Boolean, Callback_Void, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, Callback_DragEvent_String_Void, Callback_PreDragStatus_Void, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, Callback_TouchEvent_HitTestMode, Literal_Alignment_align } from "./SyntheticDeclarations"
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
import { TextBackgroundStyle, BaseSpan, SpanAttribute } from "./ArkSpanInterfaces"
import { DecorationStyleInterface } from "./ArkStyledStringInterfaces"
/** @memo:stable */
export class ArkBaseSpanComponent extends ArkCommonMethodComponent {
    getPeer(): ArkBaseSpanPeer {
        return (this.peer as ArkBaseSpanPeer)
    }
    /** @memo */
    public textBackgroundStyle(value: TextBackgroundStyle): this {
        if (this.checkPriority("textBackgroundStyle")) {
            const value_casted = value as (TextBackgroundStyle)
            this.getPeer()?.textBackgroundStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public baselineOffset(value: LengthMetrics): this {
        if (this.checkPriority("baselineOffset")) {
            const value_casted = value as (LengthMetrics)
            this.getPeer()?.baselineOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    public applyAttributesFinish(): void {
        // we calls this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo:stable */
export class ArkSpanComponent extends ArkBaseSpanComponent {
    getPeer(): ArkSpanPeer {
        return (this.peer as ArkSpanPeer)
    }
    /** @memo */
    public setSpanOptions(value: string | Resource): this {
        if (this.checkPriority("setSpanOptions")) {
            const value_casted = value as (string | Resource)
            this.getPeer()?.setSpanOptionsAttribute(value_casted)
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
    public fontSize(value: number | string | Resource): this {
        if (this.checkPriority("fontSize")) {
            const value_casted = value as (number | string | Resource)
            this.getPeer()?.fontSizeAttribute(value_casted)
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
    public fontWeight(value: number | FontWeight | string): this {
        if (this.checkPriority("fontWeight")) {
            const value_casted = value as (number | FontWeight | string)
            this.getPeer()?.fontWeightAttribute(value_casted)
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
    public decoration(value: DecorationStyleInterface): this {
        if (this.checkPriority("decoration")) {
            const value_casted = value as (DecorationStyleInterface)
            this.getPeer()?.decorationAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public letterSpacing(value: number | string): this {
        if (this.checkPriority("letterSpacing")) {
            const value_casted = value as (number | string)
            this.getPeer()?.letterSpacingAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public textCase(value: TextCase): this {
        if (this.checkPriority("textCase")) {
            const value_casted = value as (TextCase)
            this.getPeer()?.textCaseAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public lineHeight(value: Length): this {
        if (this.checkPriority("lineHeight")) {
            const value_casted = value as (Length)
            this.getPeer()?.lineHeightAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public textShadow(value: ShadowOptions | Array<ShadowOptions>): this {
        if (this.checkPriority("textShadow")) {
            const value_casted = value as (ShadowOptions | Array<ShadowOptions>)
            this.getPeer()?.textShadowAttribute(value_casted)
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
export function ArkSpan(
  /** @memo */
  style: ((attributes: ArkSpanComponent) => void) | undefined,
  /** @memo */
  content_: (() => void) | undefined,
  value: string | Resource
) {
    const receiver = remember(() => {
        return new ArkSpanComponent()
    })
    NodeAttach<ArkSpanPeer>((): ArkSpanPeer => ArkSpanPeer.create(receiver), (_: ArkSpanPeer) => {
        receiver.setSpanOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

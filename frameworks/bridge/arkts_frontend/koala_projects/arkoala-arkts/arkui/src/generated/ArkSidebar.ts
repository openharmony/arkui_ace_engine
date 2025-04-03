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
import { ArkSideBarContainerPeer } from "./peers/ArkSidebarPeer"
import { CommonMethod, Rectangle, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, CustomBuilder, DragItemInfo, UniformDataType, PreDragStatus, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback } from "./ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions } from "./ArkUnitsInterfaces"
import { DrawModifier } from "./ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey } from "./ArkEnumsInterfaces"
import { Callback_Array_TouchTestInfo_TouchResult, Callback_ClickEvent_Void, Callback_Boolean_HoverEvent_Void, Callback_MouseEvent_Void, Callback_TouchEvent_Void, Callback_KeyEvent_Void, Callback_KeyEvent_Boolean, Callback_Void, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, Callback_DragEvent_String_Void, Callback_PreDragStatus_Void, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, Callback_TouchEvent_HitTestMode, Literal_Alignment_align, Callback_Boolean_Void } from "./SyntheticDeclarations"
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
import { ButtonStyle, SideBarPosition, SideBarContainerType, SideBarContainerAttribute } from "./ArkSidebarInterfaces"
import { DividerStyle } from "./ArkTabsInterfaces"
/** @memo:stable */
export class ArkSideBarContainerComponent extends ArkCommonMethodComponent {
    getPeer(): ArkSideBarContainerPeer {
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
            if (((RuntimeType.NUMBER) == (value_type)) || ((RuntimeType.STRING) == (value_type)) || (((RuntimeType.OBJECT) == (value_type)) && (TypeChecker.isResource(value, false, false, false, false, false)))) {
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
            if (((RuntimeType.NUMBER) == (value_type)) || ((RuntimeType.STRING) == (value_type)) || (((RuntimeType.OBJECT) == (value_type)) && (TypeChecker.isResource(value, false, false, false, false, false)))) {
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
            if (((RuntimeType.NUMBER) == (value_type)) || ((RuntimeType.STRING) == (value_type)) || (((RuntimeType.OBJECT) == (value_type)) && (TypeChecker.isResource(value, false, false, false, false, false)))) {
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

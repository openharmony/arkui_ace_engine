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
import { ComponentBase } from "../ComponentBase"
import { TypeChecker } from "#components"
import { ArkCommonMethodComponent } from "./ArkCommon"
import { ArkGridItemPeer } from "./peers/ArkGridItemPeer"
import { CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback } from "./../component/common"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions } from "./../component/units"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey } from "./../component/enums"
import { LengthMetrics } from "../Graphics"
import { ResizableOptions } from "./../component/image"
import { Resource } from "global/resource";
import { Callback_Void } from "./../component/abilityComponent"
import { FocusBoxStyle, FocusPriority } from "./../component/focus"
import { CircleShape } from "./ArkCircleShapeMaterialized"
import { EllipseShape } from "./ArkEllipseShapeMaterialized"
import { PathShape } from "./ArkPathShapeMaterialized"
import { RectShape } from "./ArkRectShapeMaterialized"
import { AttributeModifier } from "./../component/common" 
import { GestureInfo, BaseGestureEvent, GestureJudgeResult, GestureType, GestureMask } from "./../component/gesture"
import { PixelMap } from "./ArkPixelMapMaterialized"
import { Callback_Boolean_Void } from "./../component/checkbox"
import { GridItemOptions, GridItemAttribute } from "./../component/griditem"
/** @memo:stable */
export class ArkGridItemComponent extends ArkCommonMethodComponent implements GridItemAttribute {
    getPeer(): ArkGridItemPeer {
        return (this.peer as ArkGridItemPeer)
    }
    /** @memo */
    public setGridItemOptions(value?: GridItemOptions): this {
        if (this.checkPriority("setGridItemOptions")) {
            const value_casted = value as (GridItemOptions | undefined)
            this.getPeer()?.setGridItemOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public rowStart(value: number): this {
        if (this.checkPriority("rowStart")) {
            const value_casted = value as (number)
            this.getPeer()?.rowStartAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public rowEnd(value: number): this {
        if (this.checkPriority("rowEnd")) {
            const value_casted = value as (number)
            this.getPeer()?.rowEndAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public columnStart(value: number): this {
        if (this.checkPriority("columnStart")) {
            const value_casted = value as (number)
            this.getPeer()?.columnStartAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public columnEnd(value: number): this {
        if (this.checkPriority("columnEnd")) {
            const value_casted = value as (number)
            this.getPeer()?.columnEndAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public forceRebuild(value: boolean): this {
        if (this.checkPriority("forceRebuild")) {
            const value_casted = value as (boolean)
            this.getPeer()?.forceRebuildAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public selectable(value: boolean): this {
        if (this.checkPriority("selectable")) {
            const value_casted = value as (boolean)
            this.getPeer()?.selectableAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public selected(value: boolean): this {
        if (this.checkPriority("selected")) {
            const value_casted = value as (boolean)
            this.getPeer()?.selectedAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onSelect(value: ((parameter: boolean) => void)): this {
        if (this.checkPriority("onSelect")) {
            const value_casted = value as (((parameter: boolean) => void))
            this.getPeer()?.onSelectAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public _onChangeEvent_selected(callback: ((parameter: boolean) => void)): void {
        if (this.checkPriority("_onChangeEvent_selected")) {
            const callback_casted = callback as (((parameter: boolean) => void))
            this.getPeer()?._onChangeEvent_selectedAttribute(callback_casted)
            return
        }
        return
    }
    public applyAttributesFinish(): void {
        // we calls this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

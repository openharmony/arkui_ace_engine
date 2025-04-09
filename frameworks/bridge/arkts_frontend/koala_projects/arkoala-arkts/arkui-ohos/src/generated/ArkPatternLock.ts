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
import { ArkPatternLockPeer } from "./peers/ArkPatternLockPeer"
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
import { Callback_Array_Number_Void, CircleStyleOptions, PatternLockController, PatternLockAttribute } from "./../component/patternLock"
import { Callback_Number_Void } from "./../component/alphabetIndexer"
/** @memo:stable */
export class ArkPatternLockComponent extends ArkCommonMethodComponent implements PatternLockAttribute {
    getPeer(): ArkPatternLockPeer {
        return (this.peer as ArkPatternLockPeer)
    }
    /** @memo */
    public setPatternLockOptions(controller?: PatternLockController): this {
        if (this.checkPriority("setPatternLockOptions")) {
            const controller_casted = controller as (PatternLockController | undefined)
            this.getPeer()?.setPatternLockOptionsAttribute(controller_casted)
            return this
        }
        return this
    }
    /** @memo */
    public sideLength(value: Length): this {
        if (this.checkPriority("sideLength")) {
            const value_casted = value as (Length)
            this.getPeer()?.sideLengthAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public circleRadius(value: Length): this {
        if (this.checkPriority("circleRadius")) {
            const value_casted = value as (Length)
            this.getPeer()?.circleRadiusAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public backgroundColor(value: ResourceColor): this {
        if (this.checkPriority("backgroundColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.backgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public regularColor(value: ResourceColor): this {
        if (this.checkPriority("regularColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.regularColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public selectedColor(value: ResourceColor): this {
        if (this.checkPriority("selectedColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.selectedColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public activeColor(value: ResourceColor): this {
        if (this.checkPriority("activeColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.activeColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public pathColor(value: ResourceColor): this {
        if (this.checkPriority("pathColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.pathColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public pathStrokeWidth(value: number | string): this {
        if (this.checkPriority("pathStrokeWidth")) {
            const value_casted = value as (number | string)
            this.getPeer()?.pathStrokeWidthAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onPatternComplete(value: ((input: Array<number>) => void)): this {
        if (this.checkPriority("onPatternComplete")) {
            const value_casted = value as (((input: Array<number>) => void))
            this.getPeer()?.onPatternCompleteAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public autoReset(value: boolean): this {
        if (this.checkPriority("autoReset")) {
            const value_casted = value as (boolean)
            this.getPeer()?.autoResetAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onDotConnect(value: ((index: number) => void)): this {
        if (this.checkPriority("onDotConnect")) {
            const value_casted = value as (((index: number) => void))
            this.getPeer()?.onDotConnectAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public activateCircleStyle(value?: CircleStyleOptions): this {
        if (this.checkPriority("activateCircleStyle")) {
            const value_casted = value as (CircleStyleOptions | undefined)
            this.getPeer()?.activateCircleStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public applyAttributesFinish(): void {
        // we calls this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

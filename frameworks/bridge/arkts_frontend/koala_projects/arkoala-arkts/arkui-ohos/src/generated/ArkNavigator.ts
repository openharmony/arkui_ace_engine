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
import { ArkNavigatorPeer } from "./peers/ArkNavigatorPeer"
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
import { NavigationType, Literal_String_target_NavigationType_type, NavigatorAttribute } from "./../component/navigator"
/** @memo:stable */
export class ArkNavigatorComponent extends ArkCommonMethodComponent implements NavigatorAttribute {
    getPeer(): ArkNavigatorPeer {
        return (this.peer as ArkNavigatorPeer)
    }
    /** @memo */
    public setNavigatorOptions(value?: Literal_String_target_NavigationType_type): this {
        if (this.checkPriority("setNavigatorOptions")) {
            const value_type = runtimeType(value)
            if (RuntimeType.UNDEFINED == value_type) {
                this.getPeer()?.setNavigatorOptions1Attribute()
                return this
            }
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Literal_String_target_NavigationType_type | undefined)
                this.getPeer()?.setNavigatorOptions0Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public active(value: boolean): this {
        if (this.checkPriority("active")) {
            const value_casted = value as (boolean)
            this.getPeer()?.activeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public type(value: NavigationType): this {
        if (this.checkPriority("type")) {
            const value_casted = value as (NavigationType)
            this.getPeer()?.typeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public target(value: string): this {
        if (this.checkPriority("target")) {
            const value_casted = value as (string)
            this.getPeer()?.targetAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public params(value: Object): this {
        if (this.checkPriority("params")) {
            const value_casted = value as (Object)
            this.getPeer()?.paramsAttribute(value_casted)
            return this
        }
        return this
    }
    public applyAttributesFinish(): void {
        // we calls this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

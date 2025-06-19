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
import { ArkTextPickerPeer } from "./peers/ArkTextPickerPeer"
import { CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, PickerTextStyle } from "./../component/common"
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
import { Callback_String_Number_Void, Type_TextPickerAttribute_onChange_callback, DividerOptions, Callback_Union_Number_Array_Number_Void, Callback_Union_String_Array_String_Void, TextPickerOptions, TextPickerAttribute } from "./../component/textPicker"
/** @memo:stable */
export class ArkTextPickerComponent extends ArkCommonMethodComponent implements TextPickerAttribute {
    getPeer(): ArkTextPickerPeer {
        return (this.peer as ArkTextPickerPeer)
    }
    /** @memo */
    public setTextPickerOptions(options?: TextPickerOptions): this {
        if (this.checkPriority("setTextPickerOptions")) {
            const options_casted = options as (TextPickerOptions | undefined)
            this.getPeer()?.setTextPickerOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public defaultPickerItemHeight(value: number | string): this {
        if (this.checkPriority("defaultPickerItemHeight")) {
            const value_casted = value as (number | string)
            this.getPeer()?.defaultPickerItemHeightAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public canLoop(value: boolean): this {
        if (this.checkPriority("canLoop")) {
            const value_casted = value as (boolean)
            this.getPeer()?.canLoopAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public disappearTextStyle(value: PickerTextStyle): this {
        if (this.checkPriority("disappearTextStyle")) {
            const value_casted = value as (PickerTextStyle)
            this.getPeer()?.disappearTextStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public textStyle(value: PickerTextStyle): this {
        if (this.checkPriority("textStyle")) {
            const value_casted = value as (PickerTextStyle)
            this.getPeer()?.textStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public selectedTextStyle(value: PickerTextStyle): this {
        if (this.checkPriority("selectedTextStyle")) {
            const value_casted = value as (PickerTextStyle)
            this.getPeer()?.selectedTextStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onAccept(value: ((value: string,index: number) => void)): this {
        if (this.checkPriority("onAccept")) {
            const value_casted = value as (((value: string,index: number) => void))
            this.getPeer()?.onAcceptAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onCancel(value: (() => void)): this {
        if (this.checkPriority("onCancel")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onCancelAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onChange(value: ((value: string | Array<string>,index: number | Array<number>) => void)): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((value: string | Array<string>,index: number | Array<number>) => void))
            this.getPeer()?.onChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public selectedIndex(value: number | Array<number>): this {
        if (this.checkPriority("selectedIndex")) {
            const value_casted = value as (number | Array<number>)
            this.getPeer()?.selectedIndexAttribute(value_casted)
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
    public gradientHeight(value: Dimension): this {
        if (this.checkPriority("gradientHeight")) {
            const value_casted = value as (Dimension)
            this.getPeer()?.gradientHeightAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public _onChangeEvent_selected(callback: ((selected: number | Array<number>) => void)): void {
        if (this.checkPriority("_onChangeEvent_selected")) {
            const callback_casted = callback as (((selected: number | Array<number>) => void))
            this.getPeer()?._onChangeEvent_selectedAttribute(callback_casted)
            return
        }
        return
    }
    /** @memo */
    public _onChangeEvent_value(callback: ((value: string | Array<string>) => void)): void {
        if (this.checkPriority("_onChangeEvent_value")) {
            const callback_casted = callback as (((value: string | Array<string>) => void))
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

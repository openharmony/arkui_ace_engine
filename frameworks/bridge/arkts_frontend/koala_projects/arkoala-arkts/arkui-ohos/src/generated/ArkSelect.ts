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
import { ArkSelectPeer } from "./peers/ArkSelectPeer"
import { CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, ContentModifier } from "./../component/common"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, Font, Offset } from "./../component/units"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, OptionWidthMode } from "./../component/enums"
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
import { Callback_Number_String_Void, ArrowPosition, MenuItemConfiguration, MenuAlignType, SelectAttribute, Callback_Union_Number_Resource_Void, Callback_ResourceStr_Void, SelectOption } from "./../component/select"
import { ControlSize } from "./../component/button"
import { DividerOptions } from "./../component/textPicker"
/** @memo:stable */
export class ArkSelectComponent extends ArkCommonMethodComponent implements SelectAttribute {
    getPeer(): ArkSelectPeer {
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
    public onSelect(value: ((index: number,value: string) => void)): this {
        if (this.checkPriority("onSelect")) {
            const value_casted = value as (((index: number,value: string) => void))
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
    public menuItemContentModifier(value: ContentModifier<object>): this {
        if (this.checkPriority("menuItemContentModifier")) {
            const value_casted = value as (ContentModifier<object>)
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

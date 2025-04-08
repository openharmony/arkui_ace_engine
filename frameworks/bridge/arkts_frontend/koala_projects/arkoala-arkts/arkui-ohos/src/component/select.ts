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

import { int32, int64, float32 } from "@koalaui/common"
import { KInt, KPointer, KBoolean, KStringPtr, wrapCallback, NativeBuffer } from "@koalaui/interop"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ResourceStr, Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, AccessibilityOptions, Font, Offset } from "./units"
import { SymbolGlyphModifier, CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, ContentModifier, CommonConfiguration } from "./common"
import { Resource } from "global/resource";
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, OptionWidthMode } from "./enums"
import { LengthMetrics } from "../Graphics"
import { ResizableOptions } from "./image"
import { Callback_Void } from "./abilityComponent"
import { FocusBoxStyle, FocusPriority } from "./focus"
import { CircleShape } from "./../generated/ArkCircleShapeMaterialized"
import { EllipseShape } from "./../generated/ArkEllipseShapeMaterialized"
import { PathShape } from "./../generated/ArkPathShapeMaterialized"
import { RectShape } from "./../generated/ArkRectShapeMaterialized"
import { AttributeModifier } from "./../component/common" 
import { GestureInfo, BaseGestureEvent, GestureJudgeResult, GestureType, GestureMask } from "./gesture"
import { PixelMap } from "./../generated/ArkPixelMapMaterialized"
import { ControlSize } from "./button"
import { DividerOptions } from "./textPicker"
import { ArkSelectComponent } from "./../generated/ArkSelect"
import { ArkSelectPeer } from "./../generated/peers/ArkSelectPeer"
export interface SelectOption {
    value: ResourceStr;
    icon?: ResourceStr;
    symbolIcon?: SymbolGlyphModifier;
}
export enum ArrowPosition {
    END = 0,
    START = 1
}
export enum MenuAlignType {
    START = 0,
    CENTER = 1,
    END = 2
}
export type Callback_Number_String_Void = (index: number, value: string) => void;
export type Callback_Union_Number_Resource_Void = (selected: number | Resource) => void;
export type Callback_ResourceStr_Void = (value: ResourceStr) => void;
export interface MenuItemConfiguration extends CommonConfiguration<MenuItemConfiguration> {
    value: ResourceStr;
    icon?: ResourceStr;
    symbolIcon?: SymbolGlyphModifier;
    selected: boolean;
    index: number;
}
/** @memo:stable */
export interface SelectAttribute extends CommonMethod {
    /** @memo */
    setSelectOptions(options: Array<SelectOption>): this
    /** @memo */
    selected(value: number | Resource): this
    /** @memo */
    value(value: ResourceStr): this
    /** @memo */
    font(value: Font): this
    /** @memo */
    fontColor(value: ResourceColor): this
    /** @memo */
    selectedOptionBgColor(value: ResourceColor): this
    /** @memo */
    selectedOptionFont(value: Font): this
    /** @memo */
    selectedOptionFontColor(value: ResourceColor): this
    /** @memo */
    optionBgColor(value: ResourceColor): this
    /** @memo */
    optionFont(value: Font): this
    /** @memo */
    optionFontColor(value: ResourceColor): this
    /** @memo */
    onSelect(value: ((index: number,value: string) => void)): this
    /** @memo */
    space(value: Length): this
    /** @memo */
    arrowPosition(value: ArrowPosition): this
    /** @memo */
    optionWidth(value: Dimension | OptionWidthMode): this
    /** @memo */
    optionHeight(value: Dimension): this
    /** @memo */
    menuBackgroundColor(value: ResourceColor): this
    /** @memo */
    menuBackgroundBlurStyle(value: BlurStyle): this
    /** @memo */
    controlSize(value: ControlSize): this
    /** @memo */
    menuItemContentModifier(value: ContentModifier<object>): this
    /** @memo */
    divider(value?: DividerOptions): this
    /** @memo */
    menuAlign(alignType: MenuAlignType, offset?: Offset): this
    /** @memo */
    _onChangeEvent_selected(callback: ((selected: number | Resource) => void)): void
    /** @memo */
    _onChangeEvent_value(callback: ((value: ResourceStr) => void)): void
}
/** @memo */
export function Select(
  /** @memo */
  style: ((attributes: SelectAttribute) => void) | undefined,
  options: Array<SelectOption>, 
  /** @memo */
  content_?: () => void,
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

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
import { Length, ResourceColor, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, VoidCallback } from "./units"
import { SymbolGlyphModifier, CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback } from "./common"
import { Resource } from "global/resource";
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey } from "./enums"
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
import { ArkTabContentComponent } from "./../generated/ArkTabContent"
import { ArkTabContentPeer } from "./../generated/peers/ArkTabContentPeer"
import { IndicatorStyle } from "./swiper"
import { LabelStyle } from "./button"
import { VerticalAlign } from "./enums"

export class SubTabBarStyle {
    _content?: ResourceStr | ResourceStr | ComponentContent | undefined
    _indicator?: IndicatorStyle | undefined
    _selectedMode?: SelectedMode | undefined
    _board?: BoardStyle | undefined
    _labelStyle?: LabelStyle | undefined
    _padding?: Padding | Dimension | LocalizedPadding | undefined
    _id?: string | undefined
     constructor(content: ResourceStr | ResourceStr | ComponentContent) {
        this._content = content
    }
    public static of(content: ResourceStr | ResourceStr | ComponentContent): SubTabBarStyle {
        return new SubTabBarStyle(content)
    }
    indicator(value: IndicatorStyle): this {
        this._indicator = value
        return this
    }
    selectedMode(value: SelectedMode): this {
        this._selectedMode = value
        return this
    }
    board(value: BoardStyle): this {
        this._board = value
        return this
    }
    labelStyle(value: LabelStyle): this {
        this._labelStyle = value
        return this
    }
    public padding(value: Padding | Dimension | LocalizedPadding): this {
        this._padding = value
        return this
    }
    id(value: string): this {
        this._id = value
        return this
    }
}

export declare class BottomTabBarStyle {
    _icon?: ResourceStr | TabBarSymbol | undefined;
    _text?: ResourceStr | undefined;
    _labelStyle?: LabelStyle | undefined;
    _padding?: Padding | Dimension | LocalizedPadding | undefined;
    _layoutMode?: LayoutMode | undefined;
    _verticalAlign?: VerticalAlign | undefined;
    _symmetricExtensible?: boolean | undefined;
    _id?: string | undefined;
    _iconStyle?: TabBarIconStyle | undefined;
    constructor(icon: ResourceStr | TabBarSymbol, text: ResourceStr);
    static of(icon: ResourceStr | TabBarSymbol, text: ResourceStr): BottomTabBarStyle;
    labelStyle(value: LabelStyle): this;
    padding(value: Padding | Dimension | LocalizedPadding): this;
    layoutMode(value: LayoutMode): this;
    verticalAlign(value: VerticalAlign): this;
    symmetricExtensible(value: boolean): this;
    id(value: string): this;
    iconStyle(style: TabBarIconStyle): this;
}

export enum SelectedMode {
    INDICATOR = 0,
    BOARD = 1
}
export enum LayoutMode {
    AUTO = 0,
    VERTICAL = 1,
    HORIZONTAL = 2
}
export interface BoardStyle {
    borderRadius?: Length;
}
export interface TabBarIconStyle {
    selectedColor?: ResourceColor;
    unselectedColor?: ResourceColor;
}
export interface TabBarSymbol {
    normal: SymbolGlyphModifier;
    selected?: SymbolGlyphModifier;
}
export interface TabBarOptions {
    icon?: string | Resource;
    text?: string | Resource;
}
/** @memo:stable */
export interface TabContentAttribute extends CommonMethod {
    /** @memo */
    setTabContentOptions(): this
    /** @memo */
    tabBar(value: string | Resource | CustomBuilder | TabBarOptions | SubTabBarStyle | BottomTabBarStyle): this
    /** @memo */
    onWillShow(value: VoidCallback): this
    /** @memo */
    onWillHide(value: VoidCallback): this
}
/** @memo */
export function TabContent(
  /** @memo */
  style: ((attributes: TabContentAttribute) => void) | undefined,
  
  /** @memo */
  content_?: () => void,
) {
    const receiver = remember(() => {
        return new ArkTabContentComponent()
    })
    NodeAttach<ArkTabContentPeer>((): ArkTabContentPeer => ArkTabContentPeer.create(receiver), (_: ArkTabContentPeer) => {
        receiver.setTabContentOptions()
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

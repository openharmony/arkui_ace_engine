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
import { Tuple_Number_Number, ItemDragInfo, ScrollableCommonMethod, CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, NestedScrollOptions, ContentClipMode, EdgeEffectOptions, FadingEdgeOptions, OnScrollCallback } from "./common"
import { Scroller, ScrollOnWillScrollCallback, ScrollOnScrollCallback } from "./scroll"
import { ArkGridComponent } from "./../generated/ArkGrid"
import { ArkGridPeer } from "./../generated/peers/ArkGridPeer"
import { ScrollState } from "./list"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions } from "./units"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, BarState, EdgeEffect } from "./enums"
import { LengthMetrics } from "../Graphics"
import { ResizableOptions } from "./image"
import { Resource } from "global/resource";
import { Callback_Void } from "./abilityComponent"
import { FocusBoxStyle, FocusPriority } from "./focus"
import { CircleShape } from "./../generated/ArkCircleShapeMaterialized"
import { EllipseShape } from "./../generated/ArkEllipseShapeMaterialized"
import { PathShape } from "./../generated/ArkPathShapeMaterialized"
import { RectShape } from "./../generated/ArkRectShapeMaterialized"
import { AttributeModifier } from "./../component/common" 
import { GestureInfo, BaseGestureEvent, GestureJudgeResult, GestureType, GestureMask } from "./gesture"
import { PixelMap } from "./../generated/ArkPixelMapMaterialized"
import { onItemDragStart_event_type } from "./../generated/SyntheticDeclarations"
export type Callback_Number_Tuple_Number_Number = (index: number) => [ number, number ];
export type Tuple_Number_Number_Number_Number = [
    number,
    number,
    number,
    number
]
export type Callback_Number_Tuple_Number_Number_Number_Number = (index: number) => [ number, number, number, number ];
export interface GridLayoutOptions {
    regularSize: [ number, number ];
    irregularIndexes?: Array<number>;
    onGetIrregularSizeByIndex?: ((index: number) => [ number, number ]);
    onGetRectByIndex?: ((index: number) => [ number, number, number, number ]);
}
export enum GridDirection {
    ROW = 0,
    Row = 0,
    COLUMN = 1,
    Column = 1,
    ROW_REVERSE = 2,
    RowReverse = 2,
    COLUMN_REVERSE = 3,
    ColumnReverse = 3
}
export enum GridItemAlignment {
    DEFAULT = 0,
    STRETCH = 1
}
export interface ComputedBarAttribute {
    totalOffset: number;
    totalLength: number;
}
export type Callback_Number_Number_ComputedBarAttribute = (index: number, offset: number) => ComputedBarAttribute;
export type Callback_Number_Number_Void = (first: number, last: number) => void;
export type Callback_ItemDragInfo_Void = (event: ItemDragInfo) => void;
export type Callback_ItemDragInfo_Number_Number_Void = (event: ItemDragInfo, itemIndex: number, insertIndex: number) => void;
export type Callback_ItemDragInfo_Number_Void = (event: ItemDragInfo, itemIndex: number) => void;
export type Callback_ItemDragInfo_Number_Number_Boolean_Void = (event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void;
export interface Literal_Number_offsetRemain {
    offsetRemain: number;
}
export type Callback_Number_ScrollState_Literal_Number_offsetRemain = (offset: number, state: ScrollState) => Literal_Number_offsetRemain;
/** @memo:stable */
export interface GridAttribute extends ScrollableCommonMethod {
    /** @memo */
    setGridOptions(scroller?: Scroller, layoutOptions?: GridLayoutOptions): this
    /** @memo */
    columnsTemplate(value: string): this
    /** @memo */
    rowsTemplate(value: string): this
    /** @memo */
    columnsGap(value: Length): this
    /** @memo */
    rowsGap(value: Length): this
    /** @memo */
    scrollBarWidth(value: number | string): this
    /** @memo */
    scrollBarColor(value: Color | number | string): this
    /** @memo */
    scrollBar(value: BarState): this
    /** @memo */
    onScrollBarUpdate(value: ((index: number,offset: number) => ComputedBarAttribute)): this
    /** @memo */
    onScrollIndex(value: ((first: number,last: number) => void)): this
    /** @memo */
    cachedCount(count: number, show?: boolean): this
    /** @memo */
    editMode(value: boolean): this
    /** @memo */
    multiSelectable(value: boolean): this
    /** @memo */
    maxCount(value: number): this
    /** @memo */
    minCount(value: number): this
    /** @memo */
    cellLength(value: number): this
    /** @memo */
    layoutDirection(value: GridDirection): this
    /** @memo */
    supportAnimation(value: boolean): this
    /** @memo */
    onItemDragStart(value: ((event: ItemDragInfo,itemIndex: number) => CustomBuilder)): this
    /** @memo */
    onItemDragEnter(value: ((event: ItemDragInfo) => void)): this
    /** @memo */
    onItemDragMove(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void)): this
    /** @memo */
    onItemDragLeave(value: ((event: ItemDragInfo,itemIndex: number) => void)): this
    /** @memo */
    onItemDrop(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void)): this
    /** @memo */
    nestedScroll(value: NestedScrollOptions): this
    /** @memo */
    enableScrollInteraction(value: boolean): this
    /** @memo */
    friction(value: number | Resource): this
    /** @memo */
    alignItems(value?: GridItemAlignment): this
    /** @memo */
    onScroll(value: ((first: number,last: number) => void)): this
    /** @memo */
    onDidScroll(value: OnScrollCallback): this
    /** @memo */
    onReachStart(value: (() => void)): this
    /** @memo */
    onReachEnd(value: (() => void)): this
    /** @memo */
    onScrollStart(value: (() => void)): this
    /** @memo */
    onScrollStop(value: (() => void)): this
    /** @memo */
    onScrollFrameBegin(value: ((offset: number,state: ScrollState) => Literal_Number_offsetRemain)): this
    /** @memo */
    edgeEffect(value: EdgeEffect, options?: EdgeEffectOptions): this
}
/** @memo */
export function Grid(
  /** @memo */
  style: ((attributes: GridAttribute) => void) | undefined,
  scroller?: Scroller | undefined, layoutOptions?: GridLayoutOptions | undefined, 
  /** @memo */
  content_?: () => void,
) {
    const receiver = remember(() => {
        return new ArkGridComponent()
    })
    NodeAttach<ArkGridPeer>((): ArkGridPeer => ArkGridPeer.create(receiver), (_: ArkGridPeer) => {
        receiver.setGridOptions(scroller,layoutOptions)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

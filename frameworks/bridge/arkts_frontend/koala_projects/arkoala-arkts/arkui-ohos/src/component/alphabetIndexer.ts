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
import { CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback } from "./common"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, Font } from "./units"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey } from "./enums"
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
import { ArkAlphabetIndexerComponent } from "./../generated/ArkAlphabetIndexer"
import { ArkAlphabetIndexerPeer } from "./../generated/peers/ArkAlphabetIndexerPeer"
export enum IndexerAlign {
    LEFT = 0,
    Left = 0,
    RIGHT = 1,
    Right = 1,
    START = 2,
    END = 3
}
export interface AlphabetIndexerOptions {
    arrayValue: Array<string>;
    selected: number;
}
export type OnAlphabetIndexerSelectCallback = (index: number) => void;
export type OnAlphabetIndexerPopupSelectCallback = (index: number) => void;
export type OnAlphabetIndexerRequestPopupDataCallback = (index: number) => Array<string>;
export type Callback_Number_Void = (index: number) => void;
/** @memo:stable */
export interface AlphabetIndexerAttribute extends CommonMethod {
    /** @memo */
    setAlphabetIndexerOptions(options: AlphabetIndexerOptions): this
    /** @memo */
    onSelected(value: ((index: number) => void)): this
    /** @memo */
    color(value: ResourceColor): this
    /** @memo */
    selectedColor(value: ResourceColor): this
    /** @memo */
    popupColor(value: ResourceColor): this
    /** @memo */
    selectedBackgroundColor(value: ResourceColor): this
    /** @memo */
    popupBackground(value: ResourceColor): this
    /** @memo */
    popupSelectedColor(value: ResourceColor): this
    /** @memo */
    popupUnselectedColor(value: ResourceColor): this
    /** @memo */
    popupItemBackgroundColor(value: ResourceColor): this
    /** @memo */
    usingPopup(value: boolean): this
    /** @memo */
    selectedFont(value: Font): this
    /** @memo */
    popupFont(value: Font): this
    /** @memo */
    popupItemFont(value: Font): this
    /** @memo */
    itemSize(value: string | number): this
    /** @memo */
    font(value: Font): this
    /** @memo */
    onSelect(value: OnAlphabetIndexerSelectCallback): this
    /** @memo */
    onRequestPopupData(value: OnAlphabetIndexerRequestPopupDataCallback): this
    /** @memo */
    onPopupSelect(value: OnAlphabetIndexerPopupSelectCallback): this
    /** @memo */
    selected(value: number): this
    /** @memo */
    popupPosition(value: Position): this
    /** @memo */
    autoCollapse(value: boolean): this
    /** @memo */
    popupItemBorderRadius(value: number): this
    /** @memo */
    itemBorderRadius(value: number): this
    /** @memo */
    popupBackgroundBlurStyle(value: BlurStyle): this
    /** @memo */
    popupTitleBackground(value: ResourceColor): this
    /** @memo */
    enableHapticFeedback(value: boolean): this
    /** @memo */
    alignStyle(value: IndexerAlign, offset?: Length): this
    /** @memo */
    _onChangeEvent_selected(callback: ((index: number) => void)): void
}
/** @memo */
export function AlphabetIndexer(
  /** @memo */
  style: ((attributes: AlphabetIndexerAttribute) => void) | undefined,
  options: AlphabetIndexerOptions, 
  /** @memo */
  content_?: () => void,
) {
    const receiver = remember(() => {
        return new ArkAlphabetIndexerComponent()
    })
    NodeAttach<ArkAlphabetIndexerPeer>((): ArkAlphabetIndexerPeer => ArkAlphabetIndexerPeer.create(receiver), (_: ArkAlphabetIndexerPeer) => {
        receiver.setAlphabetIndexerOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

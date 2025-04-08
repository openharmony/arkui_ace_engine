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
import { ResourceStr, Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, AccessibilityOptions } from "./units"
import { CustomBuilder, ComponentContent, CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback } from "./common"
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
import { Callback_Number_Void } from "./alphabetIndexer"
import { Callback_Boolean_Void } from "./checkbox"
import { ArkRefreshComponent } from "./../generated/ArkRefresh"
import { ArkRefreshPeer } from "./../generated/peers/ArkRefreshPeer"
export enum RefreshStatus {
    INACTIVE = 0,
    Inactive = 0,
    DRAG = 1,
    Drag = 1,
    OVER_DRAG = 2,
    OverDrag = 2,
    REFRESH = 3,
    Refresh = 3,
    DONE = 4,
    Done = 4
}
export interface RefreshOptions {
    refreshing: boolean;
    offset?: number | string;
    friction?: number | string;
    promptText?: ResourceStr;
    builder?: CustomBuilder;
    refreshingContent?: ComponentContent;
}
export type Callback_RefreshStatus_Void = (state: RefreshStatus) => void;
/** @memo:stable */
export interface RefreshAttribute extends CommonMethod {
    /** @memo */
    setRefreshOptions(value: RefreshOptions): this
    /** @memo */
    onStateChange(value: ((state: RefreshStatus) => void)): this
    /** @memo */
    onRefreshing(value: (() => void)): this
    /** @memo */
    refreshOffset(value: number): this
    /** @memo */
    pullToRefresh(value: boolean): this
    /** @memo */
    onOffsetChange(value: ((index: number) => void)): this
    /** @memo */
    pullDownRatio(value?: number): this
    /** @memo */
    _onChangeEvent_refreshing(callback: ((parameter: boolean) => void)): void
}
/** @memo */
export function Refresh(
  /** @memo */
  style: ((attributes: RefreshAttribute) => void) | undefined,
  value: RefreshOptions, 
  /** @memo */
  content_?: () => void,
) {
    const receiver = remember(() => {
        return new ArkRefreshComponent()
    })
    NodeAttach<ArkRefreshPeer>((): ArkRefreshPeer => ArkRefreshPeer.create(receiver), (_: ArkRefreshPeer) => {
        receiver.setRefreshOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

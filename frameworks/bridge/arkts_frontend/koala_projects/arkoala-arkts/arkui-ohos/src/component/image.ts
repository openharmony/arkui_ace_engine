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
import { PixelMap } from "./../generated/ArkPixelMapMaterialized"
import { ResourceStr, Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, AccessibilityOptions, ColorFilter } from "./units"
import { ImageAIOptions, ImageAnalyzerConfig } from "./imageCommon"
import { CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, PointLightStyle } from "./common"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, ImageFit, CopyOptions } from "./enums"
import { LengthMetrics } from "../Graphics"
import { Resource } from "global/resource";
import { Callback_Void } from "./abilityComponent"
import { FocusBoxStyle, FocusPriority } from "./focus"
import { CircleShape } from "./../generated/ArkCircleShapeMaterialized"
import { EllipseShape } from "./../generated/ArkEllipseShapeMaterialized"
import { PathShape } from "./../generated/ArkPathShapeMaterialized"
import { RectShape } from "./../generated/ArkRectShapeMaterialized"
import { AttributeModifier } from "./../component/common"
import { GestureInfo, BaseGestureEvent, GestureJudgeResult, GestureType, GestureMask } from "./gesture"
import { ArkImageComponent } from "./../generated/ArkImage"
import { ArkImagePeer } from "./../generated/peers/ArkImagePeer"
import { ArkImageNode } from "../handwritten/modifiers/ArkImageNode"
export interface DrawableDescriptor {
    _DrawableDescriptorStub: string;
}
export interface DrawingColorFilter {
    _DrawingColorFilterStub: string;
}
export interface ResolutionQuality {
    _ResolutionQualityStub: string;
}
export interface DrawingLattice {
    _DrawingLatticeStub: string;
}
export enum ImageRenderMode {
    ORIGINAL = 0,
    Original = 0,
    TEMPLATE = 1,
    Template = 1
}
export enum ImageContent {
    EMPTY = 0
}
export enum DynamicRangeMode {
    HIGH = 0,
    CONSTRAINT = 1,
    STANDARD = 2
}
export enum ImageInterpolation {
    NONE = 0,
    None = 0,
    LOW = 1,
    Low = 1,
    MEDIUM = 2,
    Medium = 2,
    HIGH = 3,
    High = 3
}
export interface ImageSourceSize {
    width: number;
    height: number;
}
export interface Type_ImageAttribute_onComplete_callback_event {
    width: number;
    height: number;
    componentWidth: number;
    componentHeight: number;
    loadingStatus: number;
    contentWidth: number;
    contentHeight: number;
    contentOffsetX: number;
    contentOffsetY: number;
}
export type Callback_Type_ImageAttribute_onComplete_callback_event_Void = (event?: Type_ImageAttribute_onComplete_callback_event) => void;
export type ImageErrorCallback = (error: ImageError) => void;
export interface ImageError {
    componentWidth: number;
    componentHeight: number;
    message: string;
}
export interface ResizableOptions {
    slice?: EdgeWidths;
    lattice?: DrawingLattice;
}
/** @memo:stable */
export interface ImageAttribute extends CommonMethod {
    /** @memo */
    setImageOptions(src: PixelMap | ResourceStr | DrawableDescriptor | PixelMap | ResourceStr | DrawableDescriptor | ImageContent, imageAIOptions?: ImageAIOptions): this
    /** @memo */
    alt(value: string | Resource | PixelMap): this
    /** @memo */
    matchTextDirection(value: boolean): this
    /** @memo */
    fitOriginalSize(value: boolean): this
    /** @memo */
    fillColor(value: ResourceColor): this
    /** @memo */
    objectFit(value: ImageFit): this
    /** @memo */
    objectRepeat(value: ImageRepeat): this
    /** @memo */
    autoResize(value: boolean): this
    /** @memo */
    renderMode(value: ImageRenderMode): this
    /** @memo */
    dynamicRangeMode(value: DynamicRangeMode): this
    /** @memo */
    interpolation(value: ImageInterpolation): this
    /** @memo */
    sourceSize(value: ImageSourceSize): this
    /** @memo */
    syncLoad(value: boolean): this
    /** @memo */
    colorFilter(value: ColorFilter | DrawingColorFilter): this
    /** @memo */
    copyOption(value: CopyOptions): this
    /** @memo */
    draggable(value: boolean): this
    /** @memo */
    pointLight(value: PointLightStyle): this
    /** @memo */
    edgeAntialiasing(value: number): this
    /** @memo */
    onComplete(value: ((event?: Type_ImageAttribute_onComplete_callback_event) => void)): this
    /** @memo */
    onError(value: ImageErrorCallback): this
    /** @memo */
    onFinish(value: (() => void)): this
    /** @memo */
    enableAnalyzer(value: boolean): this
    /** @memo */
    analyzerConfig(value: ImageAnalyzerConfig): this
    /** @memo */
    resizable(value: ResizableOptions): this
    /** @memo */
    privacySensitive(value: boolean): this
    /** @memo */
    enhancedImageQuality(value: ResolutionQuality): this
}

export type ImageInterface = (...param: Object[]) => ArkImageNode

/** @memo */
export function Image(
  /** @memo */
  style: ((attributes: ImageAttribute) => void) | undefined,
  src: PixelMap | ResourceStr | DrawableDescriptor | PixelMap | ResourceStr | DrawableDescriptor | ImageContent, imageAIOptions?: ImageAIOptions | undefined,
  /** @memo */
  content_?: () => void,
) {
    const receiver = remember(() => {
        return new ArkImageComponent()
    })
    NodeAttach<ArkImagePeer>((): ArkImagePeer => ArkImagePeer.create(receiver), (_: ArkImagePeer) => {
        receiver.setImageOptions(src,imageAIOptions)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

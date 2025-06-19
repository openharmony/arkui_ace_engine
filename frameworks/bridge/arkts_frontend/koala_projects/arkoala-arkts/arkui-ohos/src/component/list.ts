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

import { Scroller, ScrollerInternal, ScrollOptions, ScrollEdgeOptions, ScrollPageOptions, Literal_Boolean_next_Axis_direction, OffsetResult, ScrollAlign, ScrollToIndexOptions, ScrollOnWillScrollCallback, ScrollOnScrollCallback } from "./scroll"
import { Edge, Axis, HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, ResponseType, FunctionKey, ModifierKey, BarState, EdgeEffect } from "./enums"
import { Length, ResourceColor, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, LengthConstrain } from "./units"
import { RectResult, ScrollableCommonMethod, CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, NestedScrollOptions, ContentClipMode, EdgeEffectOptions, FadingEdgeOptions, ChildrenMainSize, ItemDragInfo, OnScrollCallback } from "./common"
import { Resource } from "global/resource";
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, float32, int64 } from "@koalaui/common"
import { Serializer } from "./../generated/peers/Serializer"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { Deserializer } from "./../generated/peers/Deserializer"
import { CallbackTransformer } from "./../generated/peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Callback_Void } from "./abilityComponent"
import { LengthMetrics } from "../Graphics"
import { ResizableOptions } from "./image"
import { FocusBoxStyle, FocusPriority } from "./focus"
import { CircleShape } from "./../generated/ArkCircleShapeMaterialized"
import { EllipseShape } from "./../generated/ArkEllipseShapeMaterialized"
import { PathShape } from "./../generated/ArkPathShapeMaterialized"
import { RectShape } from "./../generated/ArkRectShapeMaterialized"
import { GestureInfo, BaseGestureEvent, GestureJudgeResult, GestureType, GestureMask } from "./gesture"
import { PixelMap } from "./../generated/ArkPixelMapMaterialized"
import { Callback_Number_Number_Void, Callback_ItemDragInfo_Void, Callback_ItemDragInfo_Number_Number_Void, Callback_ItemDragInfo_Number_Void, Callback_ItemDragInfo_Number_Number_Boolean_Void, Callback_Number_ScrollState_Literal_Number_offsetRemain, Literal_Number_offsetRemain } from "./grid"
import { onItemDragStart_event_type } from "./../generated/SyntheticDeclarations"
import { ArkListComponent } from "./../generated/ArkList"
import { ArkListPeer } from "./../generated/peers/ArkListPeer"
export class ListScrollerInternal {
    public static fromPtr(ptr: KPointer): ListScroller {
        const obj : ListScroller = new ListScroller()
        obj.peer = new Finalizable(ptr, ListScroller.getFinalizer())
        return obj
    }
}
export class ListScroller extends Scroller implements MaterializedBase {
    static ctor_listscroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ListScroller_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = ListScroller.ctor_listscroller()
        this.peer = new Finalizable(ctorPtr, ListScroller.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ListScroller_getFinalizer()
    }
    public getItemRectInGroup(index: number, indexInGroup: number): RectResult {
        const index_casted = index as (number)
        const indexInGroup_casted = indexInGroup as (number)
        return this.getItemRectInGroup_serialize(index_casted, indexInGroup_casted)
    }
    public scrollToItemInGroup(index: number, indexInGroup: number, smooth?: boolean, align?: ScrollAlign): void {
        const index_casted = index as (number)
        const indexInGroup_casted = indexInGroup as (number)
        const smooth_casted = smooth as (boolean | undefined)
        const align_casted = align as (ScrollAlign | undefined)
        this.scrollToItemInGroup_serialize(index_casted, indexInGroup_casted, smooth_casted, align_casted)
        return
    }
    public closeAllSwipeActions(options?: CloseSwipeActionOptions): void {
        const options_casted = options as (CloseSwipeActionOptions | undefined)
        this.closeAllSwipeActions_serialize(options_casted)
        return
    }
    public getVisibleListContentInfo(x: number, y: number): VisibleListContentInfo {
        const x_casted = x as (number)
        const y_casted = y as (number)
        return this.getVisibleListContentInfo_serialize(x_casted, y_casted)
    }
    private getItemRectInGroup_serialize(index: number, indexInGroup: number): RectResult {
        const retval  = ArkUIGeneratedNativeModule._ListScroller_getItemRectInGroup(this.peer!.ptr, index, indexInGroup)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const returnResult : RectResult = retvalDeserializer.readRectResult()
        return returnResult
    }
    private scrollToItemInGroup_serialize(index: number, indexInGroup: number, smooth?: boolean, align?: ScrollAlign): void {
        const thisSerializer : Serializer = Serializer.hold()
        let smooth_type : int32 = RuntimeType.UNDEFINED
        smooth_type = runtimeType(smooth)
        thisSerializer.writeInt8(smooth_type as int32)
        if ((RuntimeType.UNDEFINED) != (smooth_type)) {
            const smooth_value  = smooth!
            thisSerializer.writeBoolean(smooth_value)
        }
        let align_type : int32 = RuntimeType.UNDEFINED
        align_type = runtimeType(align)
        thisSerializer.writeInt8(align_type as int32)
        if ((RuntimeType.UNDEFINED) != (align_type)) {
            const align_value  = (align as ScrollAlign)
            thisSerializer.writeInt32(align_value.valueOf())
        }
        ArkUIGeneratedNativeModule._ListScroller_scrollToItemInGroup(this.peer!.ptr, index, indexInGroup, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private closeAllSwipeActions_serialize(options?: CloseSwipeActionOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeCloseSwipeActionOptions(options_value)
        }
        ArkUIGeneratedNativeModule._ListScroller_closeAllSwipeActions(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getVisibleListContentInfo_serialize(x: number, y: number): VisibleListContentInfo {
        const retval  = ArkUIGeneratedNativeModule._ListScroller_getVisibleListContentInfo(this.peer!.ptr, x, y)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const returnResult : VisibleListContentInfo = retvalDeserializer.readVisibleListContentInfo()
        return returnResult
    }
}
export enum ScrollState {
    IDLE = 0,
    Idle = 0,
    SCROLL = 1,
    Scroll = 1,
    FLING = 2,
    Fling = 2
}
export enum ListItemAlign {
    START = 0,
    Start = 0,
    CENTER = 1,
    Center = 1,
    END = 2,
    End = 2
}
export enum ListItemGroupArea {
    NONE = 0,
    IN_LIST_ITEM_AREA = 1,
    IN_HEADER_AREA = 2,
    IN_FOOTER_AREA = 3
}
export enum StickyStyle {
    NONE = 0,
    None = 0,
    HEADER = 1,
    Header = 1,
    FOOTER = 2,
    Footer = 2
}
export enum ChainEdgeEffect {
    DEFAULT = 0,
    STRETCH = 1
}
export enum ScrollSnapAlign {
    NONE = 0,
    START = 1,
    CENTER = 2,
    END = 3
}
export interface ChainAnimationOptions {
    minSpace: Length;
    maxSpace: Length;
    conductivity?: number;
    intensity?: number;
    edgeEffect?: ChainEdgeEffect;
    stiffness?: number;
    damping?: number;
}
export interface CloseSwipeActionOptions {
    onFinish?: (() => void);
}
export interface VisibleListContentInfo {
    index: number;
    itemGroupArea?: ListItemGroupArea;
    itemIndexInGroup?: number;
}
export type OnScrollVisibleContentChangeCallback = (start: VisibleListContentInfo, end: VisibleListContentInfo) => void;
export interface ListOptions {
    initialIndex?: number;
    space?: number | string;
    scroller?: Scroller;
}
export interface ListDividerOptions {
    strokeWidth: Length;
    color?: ResourceColor;
    startMargin?: Length;
    endMargin?: Length;
}
export type Callback_Number_Number_Number_Void = (start: number, end: number, center: number) => void;
export type Callback_Number_Boolean = (index: number) => boolean;
export type Callback_Number_Number_Boolean = (from: number, to: number) => boolean;
/** @memo:stable */
export interface ListAttribute extends ScrollableCommonMethod {
    /** @memo */
    setListOptions(options?: ListOptions): this
    /** @memo */
    alignListItem(value: ListItemAlign): this
    /** @memo */
    listDirection(value: Axis): this
    /** @memo */
    scrollBar(value: BarState): this
    /** @memo */
    contentStartOffset(value: number): this
    /** @memo */
    contentEndOffset(value: number): this
    /** @memo */
    divider(value?: ListDividerOptions): this
    /** @memo */
    editMode(value: boolean): this
    /** @memo */
    multiSelectable(value: boolean): this
    /** @memo */
    cachedCount(count: number, show?: boolean): this
    /** @memo */
    chainAnimation(value: boolean): this
    /** @memo */
    chainAnimationOptions(value: ChainAnimationOptions): this
    /** @memo */
    sticky(value: StickyStyle): this
    /** @memo */
    scrollSnapAlign(value: ScrollSnapAlign): this
    /** @memo */
    nestedScroll(value: NestedScrollOptions): this
    /** @memo */
    enableScrollInteraction(value: boolean): this
    /** @memo */
    friction(value: number | Resource): this
    /** @memo */
    childrenMainSize(value: ChildrenMainSize): this
    /** @memo */
    maintainVisibleContentPosition(value: boolean): this
    /** @memo */
    onScroll(value: ((first: number,last: number) => void)): this
    /** @memo */
    onScrollIndex(value: ((start: number,end: number,center: number) => void)): this
    /** @memo */
    onScrollVisibleContentChange(value: OnScrollVisibleContentChangeCallback): this
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
    onItemDelete(value: ((index: number) => boolean)): this
    /** @memo */
    onItemMove(value: ((from: number,to: number) => boolean)): this
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
    onScrollFrameBegin(value: ((offset: number,state: ScrollState) => Literal_Number_offsetRemain)): this
    /** @memo */
    lanes(value: number | LengthConstrain, gutter?: Dimension): this
    /** @memo */
    edgeEffect(value: EdgeEffect, options?: EdgeEffectOptions): this
}
/** @memo */
export function List(
  /** @memo */
  style: ((attributes: ListAttribute) => void) | undefined,
  options?: ListOptions | undefined, 
  /** @memo */
  content_?: () => void,
) {
    const receiver = remember(() => {
        return new ArkListComponent()
    })
    NodeAttach<ArkListPeer>((): ArkListPeer => ArkListPeer.create(receiver), (_: ArkListPeer) => {
        receiver.setListOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

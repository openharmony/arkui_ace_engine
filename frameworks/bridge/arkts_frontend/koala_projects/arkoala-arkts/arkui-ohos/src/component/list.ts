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
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
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
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
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
export type ListInterface = (options?: ListOptions) => ListAttribute;
export interface ListDividerOptions {
    strokeWidth: Length;
    color?: ResourceColor;
    startMargin?: Length;
    endMargin?: Length;
}
export type Callback_Number_Number_Number_Void = (start: number, end: number, center: number) => void;
export type Callback_Number_Boolean = (index: number) => boolean;
export type Callback_Number_Number_Boolean = (from: number, to: number) => boolean;
export interface ListAttribute extends ScrollableCommonMethod {
    alignListItem(value: ListItemAlign | undefined): this
    listDirection(value: Axis | undefined): this
    scrollBar(value: BarState | undefined): this
    contentStartOffset(value: number | undefined): this
    contentEndOffset(value: number | undefined): this
    divider(value: ListDividerOptions | null | undefined): this
    editMode(value: boolean | undefined): this
    multiSelectable(value: boolean | undefined): this
    cachedCount(count: number | undefined, show: boolean | undefined): this
    cachedCount(value: number | undefined): this
    chainAnimation(value: boolean | undefined): this
    chainAnimationOptions(value: ChainAnimationOptions | undefined): this
    sticky(value: StickyStyle | undefined): this
    scrollSnapAlign(value: ScrollSnapAlign | undefined): this
    nestedScroll(value: NestedScrollOptions | undefined): this
    enableScrollInteraction(value: boolean | undefined): this
    friction(value: number | Resource | undefined): this
    childrenMainSize(value: ChildrenMainSize | undefined): this
    maintainVisibleContentPosition(value: boolean | undefined): this
    stackFromEnd(value: boolean | undefined): this
    onScroll(value: ((first: number,last: number) => void) | undefined): this
    onScrollIndex(value: ((start: number,end: number,center: number) => void) | undefined): this
    onScrollVisibleContentChange(value: OnScrollVisibleContentChangeCallback | undefined): this
    onReachStart(value: (() => void) | undefined): this
    onReachEnd(value: (() => void) | undefined): this
    onScrollStart(value: (() => void) | undefined): this
    onScrollStop(value: (() => void) | undefined): this
    onItemDelete(value: ((index: number) => boolean) | undefined): this
    onItemMove(value: ((from: number,to: number) => boolean) | undefined): this
    onItemDragStart(value: ((event: ItemDragInfo,itemIndex: number) => CustomBuilder) | undefined): this
    onItemDragEnter(value: ((event: ItemDragInfo) => void) | undefined): this
    onItemDragMove(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void) | undefined): this
    onItemDragLeave(value: ((event: ItemDragInfo,itemIndex: number) => void) | undefined): this
    onItemDrop(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void) | undefined): this
    onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this
    onWillScroll(value: OnWillScrollCallback | undefined): this
    onDidScroll(value: OnScrollCallback | undefined): this
    lanes(value: number | LengthConstrain | undefined, gutter?: Dimension): this
    edgeEffect(value: EdgeEffect | undefined, options?: EdgeEffectOptions): this
}
export class ArkListStyle extends ArkScrollableCommonMethodStyle implements ListAttribute {
    alignListItem_value?: ListItemAlign | undefined
    listDirection_value?: Axis | undefined
    scrollBar_value?: BarState | undefined
    contentStartOffset_value?: number | undefined
    contentEndOffset_value?: number | undefined
    divider_value?: ListDividerOptions | null | undefined
    editMode_value?: boolean | undefined
    multiSelectable_value?: boolean | undefined
    cachedCount_value?: number | undefined
    chainAnimation_value?: boolean | undefined
    chainAnimationOptions_value?: ChainAnimationOptions | undefined
    sticky_value?: StickyStyle | undefined
    scrollSnapAlign_value?: ScrollSnapAlign | undefined
    nestedScroll_value?: NestedScrollOptions | undefined
    enableScrollInteraction_value?: boolean | undefined
    friction_value?: number | Resource | undefined
    childrenMainSize_value?: ChildrenMainSize | undefined
    maintainVisibleContentPosition_value?: boolean | undefined
    stackFromEnd_value?: boolean | undefined
    onScroll_value?: ((first: number,last: number) => void) | undefined
    onScrollIndex_value?: ((start: number,end: number,center: number) => void) | undefined
    onScrollVisibleContentChange_value?: OnScrollVisibleContentChangeCallback | undefined
    onReachStart_value?: (() => void) | undefined
    onReachEnd_value?: (() => void) | undefined
    onScrollStart_value?: (() => void) | undefined
    onScrollStop_value?: (() => void) | undefined
    onItemDelete_value?: ((index: number) => boolean) | undefined
    onItemMove_value?: ((from: number,to: number) => boolean) | undefined
    onItemDragStart_value?: ((event: ItemDragInfo,itemIndex: number) => CustomBuilder) | undefined
    onItemDragEnter_value?: ((event: ItemDragInfo) => void) | undefined
    onItemDragMove_value?: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void) | undefined
    onItemDragLeave_value?: ((event: ItemDragInfo,itemIndex: number) => void) | undefined
    onItemDrop_value?: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void) | undefined
    onScrollFrameBegin_value?: OnScrollFrameBeginCallback | undefined
    onWillScroll_value?: OnWillScrollCallback | undefined
    onDidScroll_value?: OnScrollCallback | undefined
    public alignListItem(value: ListItemAlign | undefined): this {
        return this
    }
    public listDirection(value: Axis | undefined): this {
        return this
    }
    public scrollBar(value: BarState | undefined): this {
        return this
    }
    public contentStartOffset(value: number | undefined): this {
        return this
    }
    public contentEndOffset(value: number | undefined): this {
        return this
    }
    public divider(value: ListDividerOptions | null | undefined): this {
        return this
    }
    public editMode(value: boolean | undefined): this {
        return this
    }
    public multiSelectable(value: boolean | undefined): this {
        return this
    }
    public cachedCount(count: number | undefined, show: boolean | undefined): this {
        return this
    }
    public cachedCount(value: number | undefined): this {
        return this
    }
    public chainAnimation(value: boolean | undefined): this {
        return this
    }
    public chainAnimationOptions(value: ChainAnimationOptions | undefined): this {
        return this
    }
    public sticky(value: StickyStyle | undefined): this {
        return this
    }
    public scrollSnapAlign(value: ScrollSnapAlign | undefined): this {
        return this
    }
    public nestedScroll(value: NestedScrollOptions | undefined): this {
        return this
    }
    public enableScrollInteraction(value: boolean | undefined): this {
        return this
    }
    public friction(value: number | Resource | undefined): this {
        return this
    }
    public childrenMainSize(value: ChildrenMainSize | undefined): this {
        return this
    }
    public maintainVisibleContentPosition(value: boolean | undefined): this {
        return this
    }
    public stackFromEnd(value: boolean | undefined): this {
        return this
    }
    public onScroll(value: ((first: number,last: number) => void) | undefined): this {
        return this
    }
    public onScrollIndex(value: ((start: number,end: number,center: number) => void) | undefined): this {
        return this
    }
    public onScrollVisibleContentChange(value: OnScrollVisibleContentChangeCallback | undefined): this {
        return this
    }
    public onReachStart(value: (() => void) | undefined): this {
        return this
    }
    public onReachEnd(value: (() => void) | undefined): this {
        return this
    }
    public onScrollStart(value: (() => void) | undefined): this {
        return this
    }
    public onScrollStop(value: (() => void) | undefined): this {
        return this
    }
    public onItemDelete(value: ((index: number) => boolean) | undefined): this {
        return this
    }
    public onItemMove(value: ((from: number,to: number) => boolean) | undefined): this {
        return this
    }
    public onItemDragStart(value: ((event: ItemDragInfo,itemIndex: number) => CustomBuilder) | undefined): this {
        return this
    }
    public onItemDragEnter(value: ((event: ItemDragInfo) => void) | undefined): this {
        return this
    }
    public onItemDragMove(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void) | undefined): this {
        return this
    }
    public onItemDragLeave(value: ((event: ItemDragInfo,itemIndex: number) => void) | undefined): this {
        return this
    }
    public onItemDrop(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void) | undefined): this {
        return this
    }
    public onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        return this
    }
    public onWillScroll(value: OnWillScrollCallback | undefined): this {
        return this
    }
    public onDidScroll(value: OnScrollCallback | undefined): this {
        return this
    }
    public lanes(value: number | LengthConstrain | undefined, gutter?: Dimension): this {
        return this
    }
    public edgeEffect(value: EdgeEffect | undefined, options?: EdgeEffectOptions): this {
        return this
    }
}
export class ArkListComponent extends ArkScrollableCommonMethodComponent implements ListAttribute {
    getPeer(): ArkListPeer {
        return (this.peer as ArkListPeer)
    }
    public setListOptions(options?: ListOptions): this {
        if (this.checkPriority("setListOptions")) {
            const options_casted = options as (ListOptions | undefined)
            this.getPeer()?.setListOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public alignListItem(value: ListItemAlign | undefined): this {
        if (this.checkPriority("alignListItem")) {
            const value_casted = value as (ListItemAlign | undefined)
            this.getPeer()?.alignListItemAttribute(value_casted)
            return this
        }
        return this
    }
    public listDirection(value: Axis | undefined): this {
        if (this.checkPriority("listDirection")) {
            const value_casted = value as (Axis | undefined)
            this.getPeer()?.listDirectionAttribute(value_casted)
            return this
        }
        return this
    }
    public scrollBar(value: BarState | undefined): this {
        if (this.checkPriority("scrollBar")) {
            const value_casted = value as (BarState | undefined)
            this.getPeer()?.scrollBarAttribute(value_casted)
            return this
        }
        return this
    }
    public contentStartOffset(value: number | undefined): this {
        if (this.checkPriority("contentStartOffset")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.contentStartOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    public contentEndOffset(value: number | undefined): this {
        if (this.checkPriority("contentEndOffset")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.contentEndOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    public divider(value: ListDividerOptions | null | undefined): this {
        if (this.checkPriority("divider")) {
            const value_casted = value as (ListDividerOptions | null | undefined)
            this.getPeer()?.dividerAttribute(value_casted)
            return this
        }
        return this
    }
    public editMode(value: boolean | undefined): this {
        if (this.checkPriority("editMode")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.editModeAttribute(value_casted)
            return this
        }
        return this
    }
    public multiSelectable(value: boolean | undefined): this {
        if (this.checkPriority("multiSelectable")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.multiSelectableAttribute(value_casted)
            return this
        }
        return this
    }
    public cachedCount(count: number | undefined, show: boolean | undefined): this {
        if (this.checkPriority("cachedCount")) {
            const count_type = runtimeType(count)
            const show_type = runtimeType(show)
            if (((RuntimeType.NUMBER == count_type) || (RuntimeType.UNDEFINED == count_type)) &&
                (RuntimeType.UNDEFINED == show_type)) {
                const value_casted = count as (number | undefined)
                this.getPeer()?.cachedCount0Attribute(value_casted)
                return this
            }
            if (((RuntimeType.NUMBER == count_type) || (RuntimeType.UNDEFINED == count_type)) &&
                ((RuntimeType.BOOLEAN == show_type) || (RuntimeType.UNDEFINED == show_type))) {
                const count_casted = count as (number | undefined)
                const show_casted = show as (boolean | undefined)
                this.getPeer()?.cachedCount1Attribute(count_casted, show_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public cachedCount(value: number | undefined): this {
        if (this.checkPriority("cachedCount")) {
            const count_type = runtimeType(value)
            if (((RuntimeType.NUMBER == count_type) || (RuntimeType.UNDEFINED == count_type))) {
                const value_casted = value as (number | undefined)
                this.getPeer()?.cachedCount0Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public chainAnimation(value: boolean | undefined): this {
        if (this.checkPriority("chainAnimation")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.chainAnimationAttribute(value_casted)
            return this
        }
        return this
    }
    public chainAnimationOptions(value: ChainAnimationOptions | undefined): this {
        if (this.checkPriority("chainAnimationOptions")) {
            const value_casted = value as (ChainAnimationOptions | undefined)
            this.getPeer()?.chainAnimationOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public sticky(value: StickyStyle | undefined): this {
        if (this.checkPriority("sticky")) {
            const value_casted = value as (StickyStyle | undefined)
            this.getPeer()?.stickyAttribute(value_casted)
            return this
        }
        return this
    }
    public scrollSnapAlign(value: ScrollSnapAlign | undefined): this {
        if (this.checkPriority("scrollSnapAlign")) {
            const value_casted = value as (ScrollSnapAlign | undefined)
            this.getPeer()?.scrollSnapAlignAttribute(value_casted)
            return this
        }
        return this
    }
    public nestedScroll(value: NestedScrollOptions | undefined): this {
        if (this.checkPriority("nestedScroll")) {
            const value_casted = value as (NestedScrollOptions | undefined)
            this.getPeer()?.nestedScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public enableScrollInteraction(value: boolean | undefined): this {
        if (this.checkPriority("enableScrollInteraction")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enableScrollInteractionAttribute(value_casted)
            return this
        }
        return this
    }
    public friction(value: number | Resource | undefined): this {
        if (this.checkPriority("friction")) {
            const value_casted = value as (number | Resource | undefined)
            this.getPeer()?.frictionAttribute(value_casted)
            return this
        }
        return this
    }
    public childrenMainSize(value: ChildrenMainSize | undefined): this {
        if (this.checkPriority("childrenMainSize")) {
            hookListChildrenMainSizeImpl(this, (value as ChildrenMainSize | undefined));
            return this
        }
        return this
    }
    public maintainVisibleContentPosition(value: boolean | undefined): this {
        if (this.checkPriority("maintainVisibleContentPosition")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.maintainVisibleContentPositionAttribute(value_casted)
            return this
        }
        return this
    }
    public stackFromEnd(value: boolean | undefined): this {
        if (this.checkPriority("stackFromEnd")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.stackFromEndAttribute(value_casted)
            return this
        }
        return this
    }
    public onScroll(value: ((first: number,last: number) => void) | undefined): this {
        if (this.checkPriority("onScroll")) {
            const value_casted = value as (((first: number,last: number) => void) | undefined)
            this.getPeer()?.onScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public onScrollIndex(value: ((start: number,end: number,center: number) => void) | undefined): this {
        if (this.checkPriority("onScrollIndex")) {
            const value_casted = value as (((start: number,end: number,center: number) => void) | undefined)
            this.getPeer()?.onScrollIndexAttribute(value_casted)
            return this
        }
        return this
    }
    public onScrollVisibleContentChange(value: OnScrollVisibleContentChangeCallback | undefined): this {
        if (this.checkPriority("onScrollVisibleContentChange")) {
            const value_casted = value as (OnScrollVisibleContentChangeCallback | undefined)
            this.getPeer()?.onScrollVisibleContentChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onReachStart(value: (() => void) | undefined): this {
        if (this.checkPriority("onReachStart")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onReachStartAttribute(value_casted)
            return this
        }
        return this
    }
    public onReachEnd(value: (() => void) | undefined): this {
        if (this.checkPriority("onReachEnd")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onReachEndAttribute(value_casted)
            return this
        }
        return this
    }
    public onScrollStart(value: (() => void) | undefined): this {
        if (this.checkPriority("onScrollStart")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onScrollStartAttribute(value_casted)
            return this
        }
        return this
    }
    public onScrollStop(value: (() => void) | undefined): this {
        if (this.checkPriority("onScrollStop")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onScrollStopAttribute(value_casted)
            return this
        }
        return this
    }
    public onItemDelete(value: ((index: number) => boolean) | undefined): this {
        if (this.checkPriority("onItemDelete")) {
            const value_casted = value as (((index: number) => boolean) | undefined)
            this.getPeer()?.onItemDeleteAttribute(value_casted)
            return this
        }
        return this
    }
    public onItemMove(value: ((from: number,to: number) => boolean) | undefined): this {
        if (this.checkPriority("onItemMove")) {
            const value_casted = value as (((from: number,to: number) => boolean) | undefined)
            this.getPeer()?.onItemMoveAttribute(value_casted)
            return this
        }
        return this
    }
    public onItemDragStart(value: ((event: ItemDragInfo,itemIndex: number) => CustomBuilder) | undefined): this {
        if (this.checkPriority("onItemDragStart")) {
            const value_casted = value as (((event: ItemDragInfo,itemIndex: number) => CustomBuilder) | undefined)
            this.getPeer()?.onItemDragStartAttribute(value_casted)
            return this
        }
        return this
    }
    public onItemDragEnter(value: ((event: ItemDragInfo) => void) | undefined): this {
        if (this.checkPriority("onItemDragEnter")) {
            const value_casted = value as (((event: ItemDragInfo) => void) | undefined)
            this.getPeer()?.onItemDragEnterAttribute(value_casted)
            return this
        }
        return this
    }
    public onItemDragMove(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void) | undefined): this {
        if (this.checkPriority("onItemDragMove")) {
            const value_casted = value as (((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void) | undefined)
            this.getPeer()?.onItemDragMoveAttribute(value_casted)
            return this
        }
        return this
    }
    public onItemDragLeave(value: ((event: ItemDragInfo,itemIndex: number) => void) | undefined): this {
        if (this.checkPriority("onItemDragLeave")) {
            const value_casted = value as (((event: ItemDragInfo,itemIndex: number) => void) | undefined)
            this.getPeer()?.onItemDragLeaveAttribute(value_casted)
            return this
        }
        return this
    }
    public onItemDrop(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void) | undefined): this {
        if (this.checkPriority("onItemDrop")) {
            const value_casted = value as (((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void) | undefined)
            this.getPeer()?.onItemDropAttribute(value_casted)
            return this
        }
        return this
    }
    public onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        if (this.checkPriority("onScrollFrameBegin")) {
            const value_casted = value as (OnScrollFrameBeginCallback | undefined)
            this.getPeer()?.onScrollFrameBeginAttribute(value_casted)
            return this
        }
        return this
    }
    public onWillScroll(value?: OnWillScrollCallback | undefined): this {
        if (this.checkPriority("onWillScroll")) {
            const value_casted = value as (OnWillScrollCallback | undefined)
            this.getPeer()?.onWillScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public onDidScroll(value?: OnScrollCallback | undefined): this {
        if (this.checkPriority("onDidScroll")) {
            const value_casted = value as (OnScrollCallback | undefined)
            this.getPeer()?.onDidScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public lanes(value: number | LengthConstrain | undefined, gutter?: Dimension): this {
        if (this.checkPriority("lanes")) {
            const value_casted = value as (number | LengthConstrain | undefined)
            const gutter_casted = gutter as (Dimension | undefined)
            this.getPeer()?.lanesAttribute(value_casted, gutter_casted)
            return this
        }
        return this
    }
    public edgeEffect(value: EdgeEffect | undefined, options?: EdgeEffectOptions): this {
        if (this.checkPriority("edgeEffect")) {
            const value_casted = value as (EdgeEffect | undefined)
            const options_casted = options as (EdgeEffectOptions | undefined)
            this.getPeer()?.edgeEffectAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function List(
    /** @memo */
    style: ((attributes: ListAttribute) => void) | undefined,
    options?: ListOptions,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
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
        // @ts-ignore
        const retval = ArkUIGeneratedNativeModule._ListScroller_getItemRectInGroup(this.peer!.ptr, index, indexInGroup) as FixedArray<byte>
        // @ts-ignore
        let exactRetValue: byte[] = new Array<byte>
        for (let i = 0; i < retval.length; i++) {
            // @ts-ignore
            exactRetValue.push(new Byte(retval[i]))
        }
        let retvalDeserializer : Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32)
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
            thisSerializer.writeInt32(TypeChecker.ScrollAlign_ToNumeric(align_value))
        }
        ArkUIGeneratedNativeModule._ListScroller_scrollToItemInGroup(this.peer!.ptr, index, indexInGroup, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private closeAllSwipeActions_serialize(options?: CloseSwipeActionOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeCloseSwipeActionOptions(options_value)
        }
        ArkUIGeneratedNativeModule._ListScroller_closeAllSwipeActions(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getVisibleListContentInfo_serialize(x: number, y: number): VisibleListContentInfo {
        // @ts-ignore
        const retval = ArkUIGeneratedNativeModule._ListScroller_getVisibleListContentInfo(this.peer!.ptr, x, y) as FixedArray<byte>
        // @ts-ignore
        let exactRetValue: byte[] = new Array<byte>
        for (let i = 0; i < retval.length; i++) {
            // @ts-ignore
            exactRetValue.push(new Byte(retval[i]))
        }
        let retvalDeserializer : Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32)
        const returnResult : VisibleListContentInfo = retvalDeserializer.readVisibleListContentInfo()
        return returnResult
    }
}

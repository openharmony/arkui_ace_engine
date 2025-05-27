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

import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer, Finalizable, SerializerBase, registerCallback } from "@koalaui/interop"
import { Serializer } from "./peers/Serializer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkScrollableCommonMethodPeer, ScrollableCommonMethod, NestedScrollOptions, ChildrenMainSize, ItemDragInfo, CustomBuilder, EdgeEffectOptions, ArkScrollableCommonMethodComponent, ArkScrollableCommonMethodStyle, UIScrollableCommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethod, UICommonMethod, RectResult } from "./common"
import { Axis, BarState, EdgeEffect } from "./enums"
import { Resource } from "./resource"
import { Callback_Number_Number_Void, Callback_ItemDragInfo_Void, Callback_ItemDragInfo_Number_Number_Void, Callback_ItemDragInfo_Number_Void, Callback_ItemDragInfo_Number_Number_Boolean_Void, Callback_Number_ScrollState_Literal_Number_offsetRemain, Literal_Number_offsetRemain } from "./grid"
import { Callback_Void } from "./ability_component"
import { ListAttribute_onItemDragStart_event_type } from "./type-replacements"
import { LengthConstrain, Dimension, Length, ResourceColor } from "./units"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { Scroller, ScrollerInternal, ScrollAlign } from "./scroll"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Deserializer } from "./peers/Deserializer"
export class ArkListPeer extends ArkScrollableCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkListPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._List_construct(peerId, flags)
        const _peer  = new ArkListPeer(_peerPtr, peerId, "List", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setListOptionsAttribute(options?: ListOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeListOptions(options_value)
        }
        ArkUIGeneratedNativeModule._ListInterface_setListOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    alignListItemAttribute(value: ListItemAlign): void {
        ArkUIGeneratedNativeModule._ListAttribute_alignListItem(this.peer.ptr, TypeChecker.ListItemAlign_ToNumeric(value))
    }
    listDirectionAttribute(value: Axis): void {
        ArkUIGeneratedNativeModule._ListAttribute_listDirection(this.peer.ptr, TypeChecker.Axis_ToNumeric(value))
    }
    scrollBarAttribute(value: BarState): void {
        ArkUIGeneratedNativeModule._ListAttribute_scrollBar(this.peer.ptr, TypeChecker.BarState_ToNumeric(value))
    }
    contentStartOffsetAttribute(value: number): void {
        ArkUIGeneratedNativeModule._ListAttribute_contentStartOffset(this.peer.ptr, value)
    }
    contentEndOffsetAttribute(value: number): void {
        ArkUIGeneratedNativeModule._ListAttribute_contentEndOffset(this.peer.ptr, value)
    }
    dividerAttribute(value: ListDividerOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeListDividerOptions(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_divider(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    editModeAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ListAttribute_editMode(this.peer.ptr, value ? 1 : 0)
    }
    multiSelectableAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ListAttribute_multiSelectable(this.peer.ptr, value ? 1 : 0)
    }
    cachedCount0Attribute(value: number): void {
        ArkUIGeneratedNativeModule._ListAttribute_cachedCount0(this.peer.ptr, value)
    }
    cachedCount1Attribute(count: number, show: boolean): void {
        ArkUIGeneratedNativeModule._ListAttribute_cachedCount1(this.peer.ptr, count, show ? 1 : 0)
    }
    chainAnimationAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ListAttribute_chainAnimation(this.peer.ptr, value ? 1 : 0)
    }
    chainAnimationOptionsAttribute(value: ChainAnimationOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeChainAnimationOptions(value)
        ArkUIGeneratedNativeModule._ListAttribute_chainAnimationOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    stickyAttribute(value: StickyStyle): void {
        ArkUIGeneratedNativeModule._ListAttribute_sticky(this.peer.ptr, TypeChecker.StickyStyle_ToNumeric(value))
    }
    scrollSnapAlignAttribute(value: ScrollSnapAlign): void {
        ArkUIGeneratedNativeModule._ListAttribute_scrollSnapAlign(this.peer.ptr, TypeChecker.ScrollSnapAlign_ToNumeric(value))
    }
    nestedScrollAttribute(value: NestedScrollOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeNestedScrollOptions(value)
        ArkUIGeneratedNativeModule._ListAttribute_nestedScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableScrollInteractionAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ListAttribute_enableScrollInteraction(this.peer.ptr, value ? 1 : 0)
    }
    frictionAttribute(value: number | Resource): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as Resource
            thisSerializer.writeResource(value_1)
        }
        ArkUIGeneratedNativeModule._ListAttribute_friction(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    childrenMainSizeAttribute(value: ChildrenMainSize): void {
        ArkUIGeneratedNativeModule._ListAttribute_childrenMainSize(this.peer.ptr, toPeerPtr(value))
    }
    maintainVisibleContentPositionAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ListAttribute_maintainVisibleContentPosition(this.peer.ptr, value ? 1 : 0)
    }
    onScrollAttribute(value: ((first: number,last: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollIndexAttribute(value: ((start: number,end: number,center: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onScrollIndex(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollVisibleContentChangeAttribute(value: OnScrollVisibleContentChangeCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onScrollVisibleContentChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onReachStartAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onReachStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onReachEndAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onReachEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollStartAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onScrollStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollStopAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onScrollStop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDeleteAttribute(value: ((index: number) => boolean)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onItemDelete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemMoveAttribute(value: ((from: number,to: number) => boolean)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onItemMove(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDragStartAttribute(value: ((event: ItemDragInfo,itemIndex: number) => CustomBuilder)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onItemDragStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDragEnterAttribute(value: ((event: ItemDragInfo) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onItemDragEnter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDragMoveAttribute(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onItemDragMove(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDragLeaveAttribute(value: ((event: ItemDragInfo,itemIndex: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onItemDragLeave(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDropAttribute(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onItemDrop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollFrameBeginAttribute(value: ((offset: number,state: ScrollState) => Literal_Number_offsetRemain)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onScrollFrameBegin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    lanesAttribute(value: number | LengthConstrain, gutter?: Dimension): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as LengthConstrain
            const value_1_minLength  = value_1.minLength
            let value_1_minLength_type : int32 = RuntimeType.UNDEFINED
            value_1_minLength_type = runtimeType(value_1_minLength)
            if (RuntimeType.STRING == value_1_minLength_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_1_minLength_0  = value_1_minLength as string
                thisSerializer.writeString(value_1_minLength_0)
            }
            else if (RuntimeType.NUMBER == value_1_minLength_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_1_minLength_1  = value_1_minLength as number
                thisSerializer.writeNumber(value_1_minLength_1)
            }
            else if (RuntimeType.OBJECT == value_1_minLength_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_1_minLength_2  = value_1_minLength as Resource
                thisSerializer.writeResource(value_1_minLength_2)
            }
            const value_1_maxLength  = value_1.maxLength
            let value_1_maxLength_type : int32 = RuntimeType.UNDEFINED
            value_1_maxLength_type = runtimeType(value_1_maxLength)
            if (RuntimeType.STRING == value_1_maxLength_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_1_maxLength_0  = value_1_maxLength as string
                thisSerializer.writeString(value_1_maxLength_0)
            }
            else if (RuntimeType.NUMBER == value_1_maxLength_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_1_maxLength_1  = value_1_maxLength as number
                thisSerializer.writeNumber(value_1_maxLength_1)
            }
            else if (RuntimeType.OBJECT == value_1_maxLength_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_1_maxLength_2  = value_1_maxLength as Resource
                thisSerializer.writeResource(value_1_maxLength_2)
            }
        }
        let gutter_type : int32 = RuntimeType.UNDEFINED
        gutter_type = runtimeType(gutter)
        thisSerializer.writeInt8(gutter_type as int32)
        if ((RuntimeType.UNDEFINED) != (gutter_type)) {
            const gutter_value  = gutter!
            let gutter_value_type : int32 = RuntimeType.UNDEFINED
            gutter_value_type = runtimeType(gutter_value)
            if (RuntimeType.STRING == gutter_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const gutter_value_0  = gutter_value as string
                thisSerializer.writeString(gutter_value_0)
            }
            else if (RuntimeType.NUMBER == gutter_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const gutter_value_1  = gutter_value as number
                thisSerializer.writeNumber(gutter_value_1)
            }
            else if (RuntimeType.OBJECT == gutter_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const gutter_value_2  = gutter_value as Resource
                thisSerializer.writeResource(gutter_value_2)
            }
        }
        ArkUIGeneratedNativeModule._ListAttribute_lanes(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    edgeEffectAttribute(value: EdgeEffect, options?: EdgeEffectOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeEdgeEffectOptions(options_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_edgeEffect(this.peer.ptr, TypeChecker.EdgeEffect_ToNumeric(value), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
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
export interface ListAttribute extends ScrollableCommonMethod {
    alignListItem(value: ListItemAlign): this
    listDirection(value: Axis): this
    scrollBar(value: BarState): this
    contentStartOffset(value: number): this
    contentEndOffset(value: number): this
    divider(value: ListDividerOptions | undefined): this
    editMode(value: boolean): this
    multiSelectable(value: boolean): this
    cachedCount(count: number, show?: boolean): this
    chainAnimation(value: boolean): this
    chainAnimationOptions(value: ChainAnimationOptions): this
    sticky(value: StickyStyle): this
    scrollSnapAlign(value: ScrollSnapAlign): this
    nestedScroll(value: NestedScrollOptions): this
    enableScrollInteraction(value: boolean): this
    friction(value: number | Resource): this
    childrenMainSize(value: ChildrenMainSize): this
    maintainVisibleContentPosition(value: boolean): this
    onScroll(value: ((first: number,last: number) => void)): this
    onScrollIndex(value: ((start: number,end: number,center: number) => void)): this
    onScrollVisibleContentChange(value: OnScrollVisibleContentChangeCallback): this
    onReachStart(value: (() => void)): this
    onReachEnd(value: (() => void)): this
    onScrollStart(value: (() => void)): this
    onScrollStop(value: (() => void)): this
    onItemDelete(value: ((index: number) => boolean)): this
    onItemMove(value: ((from: number,to: number) => boolean)): this
    onItemDragStart(value: ((event: ItemDragInfo,itemIndex: number) => CustomBuilder)): this
    onItemDragEnter(value: ((event: ItemDragInfo) => void)): this
    onItemDragMove(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void)): this
    onItemDragLeave(value: ((event: ItemDragInfo,itemIndex: number) => void)): this
    onItemDrop(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void)): this
    onScrollFrameBegin(value: ((offset: number,state: ScrollState) => Literal_Number_offsetRemain)): this
    lanes(value: number | LengthConstrain, gutter?: Dimension): this
    edgeEffect(value: EdgeEffect, options?: EdgeEffectOptions): this
    attributeModifier(value: AttributeModifier<ListAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIListAttribute extends UIScrollableCommonMethod {
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
    divider(value: ListDividerOptions | undefined): this
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
    /** @memo */
    attributeModifier(value: AttributeModifier<ListAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkListStyle extends ArkScrollableCommonMethodStyle implements ListAttribute {
    alignListItem_value?: ListItemAlign
    listDirection_value?: Axis
    scrollBar_value?: BarState
    contentStartOffset_value?: number
    contentEndOffset_value?: number
    divider_value?: ListDividerOptions | undefined
    editMode_value?: boolean
    multiSelectable_value?: boolean
    cachedCount_value?: number
    chainAnimation_value?: boolean
    chainAnimationOptions_value?: ChainAnimationOptions
    sticky_value?: StickyStyle
    scrollSnapAlign_value?: ScrollSnapAlign
    nestedScroll_value?: NestedScrollOptions
    enableScrollInteraction_value?: boolean
    friction_value?: number | Resource
    childrenMainSize_value?: ChildrenMainSize
    maintainVisibleContentPosition_value?: boolean
    onScroll_value?: ((first: number,last: number) => void)
    onScrollIndex_value?: ((start: number,end: number,center: number) => void)
    onScrollVisibleContentChange_value?: OnScrollVisibleContentChangeCallback
    onReachStart_value?: (() => void)
    onReachEnd_value?: (() => void)
    onScrollStart_value?: (() => void)
    onScrollStop_value?: (() => void)
    onItemDelete_value?: ((index: number) => boolean)
    onItemMove_value?: ((from: number,to: number) => boolean)
    onItemDragStart_value?: ((event: ItemDragInfo,itemIndex: number) => CustomBuilder)
    onItemDragEnter_value?: ((event: ItemDragInfo) => void)
    onItemDragMove_value?: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void)
    onItemDragLeave_value?: ((event: ItemDragInfo,itemIndex: number) => void)
    onItemDrop_value?: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void)
    onScrollFrameBegin_value?: ((offset: number,state: ScrollState) => Literal_Number_offsetRemain)
    public alignListItem(value: ListItemAlign): this {
        return this
    }
    public listDirection(value: Axis): this {
        return this
    }
    public scrollBar(value: BarState): this {
        return this
    }
    public contentStartOffset(value: number): this {
        return this
    }
    public contentEndOffset(value: number): this {
        return this
    }
    public divider(value: ListDividerOptions | undefined): this {
        return this
    }
    public editMode(value: boolean): this {
        return this
    }
    public multiSelectable(value: boolean): this {
        return this
    }
    public cachedCount(count: number, show?: boolean): this {
        return this
    }
    public chainAnimation(value: boolean): this {
        return this
    }
    public chainAnimationOptions(value: ChainAnimationOptions): this {
        return this
    }
    public sticky(value: StickyStyle): this {
        return this
    }
    public scrollSnapAlign(value: ScrollSnapAlign): this {
        return this
    }
    public nestedScroll(value: NestedScrollOptions): this {
        return this
    }
    public enableScrollInteraction(value: boolean): this {
        return this
    }
    public friction(value: number | Resource): this {
        return this
    }
    public childrenMainSize(value: ChildrenMainSize): this {
        return this
    }
    public maintainVisibleContentPosition(value: boolean): this {
        return this
    }
    public onScroll(value: ((first: number,last: number) => void)): this {
        return this
    }
    public onScrollIndex(value: ((start: number,end: number,center: number) => void)): this {
        return this
    }
    public onScrollVisibleContentChange(value: OnScrollVisibleContentChangeCallback): this {
        return this
    }
    public onReachStart(value: (() => void)): this {
        return this
    }
    public onReachEnd(value: (() => void)): this {
        return this
    }
    public onScrollStart(value: (() => void)): this {
        return this
    }
    public onScrollStop(value: (() => void)): this {
        return this
    }
    public onItemDelete(value: ((index: number) => boolean)): this {
        return this
    }
    public onItemMove(value: ((from: number,to: number) => boolean)): this {
        return this
    }
    public onItemDragStart(value: ((event: ItemDragInfo,itemIndex: number) => CustomBuilder)): this {
        return this
    }
    public onItemDragEnter(value: ((event: ItemDragInfo) => void)): this {
        return this
    }
    public onItemDragMove(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void)): this {
        return this
    }
    public onItemDragLeave(value: ((event: ItemDragInfo,itemIndex: number) => void)): this {
        return this
    }
    public onItemDrop(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void)): this {
        return this
    }
    public onScrollFrameBegin(value: ((offset: number,state: ScrollState) => Literal_Number_offsetRemain)): this {
        return this
    }
    public lanes(value: number | LengthConstrain, gutter?: Dimension): this {
        return this
    }
    public edgeEffect(value: EdgeEffect, options?: EdgeEffectOptions): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<ListAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
/** @memo:stable */
export class ArkListComponent extends ArkScrollableCommonMethodComponent implements UIListAttribute {
    getPeer(): ArkListPeer {
        return (this.peer as ArkListPeer)
    }
    /** @memo */
    public setListOptions(options?: ListOptions): this {
        if (this.checkPriority("setListOptions")) {
            const options_casted = options as (ListOptions | undefined)
            this.getPeer()?.setListOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public alignListItem(value: ListItemAlign): this {
        if (this.checkPriority("alignListItem")) {
            const value_casted = value as (ListItemAlign)
            this.getPeer()?.alignListItemAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public listDirection(value: Axis): this {
        if (this.checkPriority("listDirection")) {
            const value_casted = value as (Axis)
            this.getPeer()?.listDirectionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public scrollBar(value: BarState): this {
        if (this.checkPriority("scrollBar")) {
            const value_casted = value as (BarState)
            this.getPeer()?.scrollBarAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public contentStartOffset(value: number): this {
        if (this.checkPriority("contentStartOffset")) {
            const value_casted = value as (number)
            this.getPeer()?.contentStartOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public contentEndOffset(value: number): this {
        if (this.checkPriority("contentEndOffset")) {
            const value_casted = value as (number)
            this.getPeer()?.contentEndOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public divider(value: ListDividerOptions | undefined): this {
        if (this.checkPriority("divider")) {
            const value_casted = value as (ListDividerOptions | undefined)
            this.getPeer()?.dividerAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public editMode(value: boolean): this {
        if (this.checkPriority("editMode")) {
            const value_casted = value as (boolean)
            this.getPeer()?.editModeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public multiSelectable(value: boolean): this {
        if (this.checkPriority("multiSelectable")) {
            const value_casted = value as (boolean)
            this.getPeer()?.multiSelectableAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public cachedCount(count: number, show?: boolean): this {
        if (this.checkPriority("cachedCount")) {
            const count_type = runtimeType(count)
            const show_type = runtimeType(show)
            const value_casted = count as (number)
            this.getPeer()?.cachedCount0Attribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public chainAnimation(value: boolean): this {
        if (this.checkPriority("chainAnimation")) {
            const value_casted = value as (boolean)
            this.getPeer()?.chainAnimationAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public chainAnimationOptions(value: ChainAnimationOptions): this {
        if (this.checkPriority("chainAnimationOptions")) {
            const value_casted = value as (ChainAnimationOptions)
            this.getPeer()?.chainAnimationOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public sticky(value: StickyStyle): this {
        if (this.checkPriority("sticky")) {
            const value_casted = value as (StickyStyle)
            this.getPeer()?.stickyAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public scrollSnapAlign(value: ScrollSnapAlign): this {
        if (this.checkPriority("scrollSnapAlign")) {
            const value_casted = value as (ScrollSnapAlign)
            this.getPeer()?.scrollSnapAlignAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public nestedScroll(value: NestedScrollOptions): this {
        if (this.checkPriority("nestedScroll")) {
            const value_casted = value as (NestedScrollOptions)
            this.getPeer()?.nestedScrollAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enableScrollInteraction(value: boolean): this {
        if (this.checkPriority("enableScrollInteraction")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableScrollInteractionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public friction(value: number | Resource): this {
        if (this.checkPriority("friction")) {
            const value_casted = value as (number | Resource)
            this.getPeer()?.frictionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public childrenMainSize(value: ChildrenMainSize): this {
        if (this.checkPriority("childrenMainSize")) {
            const value_casted = value as (ChildrenMainSize)
            this.getPeer()?.childrenMainSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public maintainVisibleContentPosition(value: boolean): this {
        if (this.checkPriority("maintainVisibleContentPosition")) {
            const value_casted = value as (boolean)
            this.getPeer()?.maintainVisibleContentPositionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onScroll(value: ((first: number,last: number) => void)): this {
        if (this.checkPriority("onScroll")) {
            const value_casted = value as (((first: number,last: number) => void))
            this.getPeer()?.onScrollAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onScrollIndex(value: ((start: number,end: number,center: number) => void)): this {
        if (this.checkPriority("onScrollIndex")) {
            const value_casted = value as (((start: number,end: number,center: number) => void))
            this.getPeer()?.onScrollIndexAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onScrollVisibleContentChange(value: OnScrollVisibleContentChangeCallback): this {
        if (this.checkPriority("onScrollVisibleContentChange")) {
            const value_casted = value as (OnScrollVisibleContentChangeCallback)
            this.getPeer()?.onScrollVisibleContentChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onReachStart(value: (() => void)): this {
        if (this.checkPriority("onReachStart")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onReachStartAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onReachEnd(value: (() => void)): this {
        if (this.checkPriority("onReachEnd")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onReachEndAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onScrollStart(value: (() => void)): this {
        if (this.checkPriority("onScrollStart")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onScrollStartAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onScrollStop(value: (() => void)): this {
        if (this.checkPriority("onScrollStop")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onScrollStopAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onItemDelete(value: ((index: number) => boolean)): this {
        if (this.checkPriority("onItemDelete")) {
            const value_casted = value as (((index: number) => boolean))
            this.getPeer()?.onItemDeleteAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onItemMove(value: ((from: number,to: number) => boolean)): this {
        if (this.checkPriority("onItemMove")) {
            const value_casted = value as (((from: number,to: number) => boolean))
            this.getPeer()?.onItemMoveAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onItemDragStart(value: ((event: ItemDragInfo,itemIndex: number) => CustomBuilder)): this {
        if (this.checkPriority("onItemDragStart")) {
            const value_casted = value as (((event: ItemDragInfo,itemIndex: number) => CustomBuilder))
            this.getPeer()?.onItemDragStartAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onItemDragEnter(value: ((event: ItemDragInfo) => void)): this {
        if (this.checkPriority("onItemDragEnter")) {
            const value_casted = value as (((event: ItemDragInfo) => void))
            this.getPeer()?.onItemDragEnterAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onItemDragMove(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void)): this {
        if (this.checkPriority("onItemDragMove")) {
            const value_casted = value as (((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void))
            this.getPeer()?.onItemDragMoveAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onItemDragLeave(value: ((event: ItemDragInfo,itemIndex: number) => void)): this {
        if (this.checkPriority("onItemDragLeave")) {
            const value_casted = value as (((event: ItemDragInfo,itemIndex: number) => void))
            this.getPeer()?.onItemDragLeaveAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onItemDrop(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void)): this {
        if (this.checkPriority("onItemDrop")) {
            const value_casted = value as (((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void))
            this.getPeer()?.onItemDropAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onScrollFrameBegin(value: ((offset: number,state: ScrollState) => Literal_Number_offsetRemain)): this {
        if (this.checkPriority("onScrollFrameBegin")) {
            const value_casted = value as (((offset: number,state: ScrollState) => Literal_Number_offsetRemain))
            this.getPeer()?.onScrollFrameBeginAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public lanes(value: number | LengthConstrain, gutter?: Dimension): this {
        if (this.checkPriority("lanes")) {
            const value_casted = value as (number | LengthConstrain)
            const gutter_casted = gutter as (Dimension | undefined)
            this.getPeer()?.lanesAttribute(value_casted, gutter_casted)
            return this
        }
        return this
    }
    /** @memo */
    public edgeEffect(value: EdgeEffect, options?: EdgeEffectOptions): this {
        if (this.checkPriority("edgeEffect")) {
            const value_casted = value as (EdgeEffect)
            const options_casted = options as (EdgeEffectOptions | undefined)
            this.getPeer()?.edgeEffectAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<ListAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ArkList(
    /** @memo */
    style: ((attributes: UIListAttribute) => void) | undefined,
    /** @memo */
    content_: (() => void) | undefined,
    options?: ListOptions,
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
            thisSerializer.writeInt32(TypeChecker.ScrollAlign_ToNumeric(align_value))
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

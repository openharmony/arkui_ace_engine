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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr, Finalizable, registerCallback } from "@koalaui/interop"
import { ChildrenMainSize_serializer, ArkScrollableCommonMethodPeer, ScrollableCommonMethod, ChildrenMainSize, OnItemDragStartCallback, ItemDragInfo, OnWillScrollCallback, OnScrollCallback, CommonMethod, ArkScrollableCommonMethodComponent, ArkScrollableCommonMethodStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkScrollableCommonMethodSet, ArkCommonMethodSet, RectResult_serializer, RectResult } from "./common"
import { LengthConstrain_serializer, LengthConstrain, Dimension, Length, ResourceColor } from "./units"
import { Resource_serializer, Resource } from "./../generated/resource"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { Axis, ScrollSource, Color } from "./enums"
import { OnScrollFrameBeginCallback, Scroller, Scroller_serializer, ScrollerInternal, ScrollAlign } from "./scroll"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
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
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            ListOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._ListInterface_setListOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAlignListItemAttribute(value: ListItemAlign | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as ListItemAlign)
            thisSerializer.writeInt32(TypeChecker.ListItemAlign_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ListAttribute_setAlignListItem(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setListDirectionAttribute(value: Axis | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as Axis)
            thisSerializer.writeInt32(TypeChecker.Axis_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ListAttribute_setListDirection(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setContentStartOffsetAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setContentStartOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setContentEndOffsetAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setContentEndOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDividerAttribute(value: ListDividerOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            ListDividerOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setDivider(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMultiSelectableAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setMultiSelectable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCachedCount0Attribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setCachedCount0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setChainAnimationAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setChainAnimation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setChainAnimationOptionsAttribute(value: ChainAnimationOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            ChainAnimationOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setChainAnimationOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStickyAttribute(value: StickyStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as StickyStyle)
            thisSerializer.writeInt32(TypeChecker.StickyStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ListAttribute_setSticky(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setScrollSnapAlignAttribute(value: ScrollSnapAlign | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as ScrollSnapAlign)
            thisSerializer.writeInt32(TypeChecker.ScrollSnapAlign_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ListAttribute_setScrollSnapAlign(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setChildrenMainSizeAttribute(value: ChildrenMainSize | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            ChildrenMainSize_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setChildrenMainSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaintainVisibleContentPositionAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setMaintainVisibleContentPosition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStackFromEndAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setStackFromEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnScrollIndexAttribute(value: ((start: number,end: number,center: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setOnScrollIndex(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnScrollVisibleContentChangeAttribute(value: OnScrollVisibleContentChangeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setOnScrollVisibleContentChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnItemMoveAttribute(value: ((from: number,to: number) => boolean) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setOnItemMove(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnItemDragStartAttribute(value: OnItemDragStartCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setOnItemDragStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnItemDragEnterAttribute(value: ((event: ItemDragInfo) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setOnItemDragEnter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnItemDragMoveAttribute(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setOnItemDragMove(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnItemDragLeaveAttribute(value: ((event: ItemDragInfo,itemIndex: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setOnItemDragLeave(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnItemDropAttribute(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setOnItemDrop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnScrollFrameBeginAttribute(value: OnScrollFrameBeginCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setOnScrollFrameBegin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnWillScrollAttribute(value: OnWillScrollCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setOnWillScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnDidScrollAttribute(value: OnScrollCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setOnDidScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLanesAttribute(value: number | LengthConstrain | undefined, gutter?: Dimension): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as LengthConstrain
                LengthConstrain_serializer.write(thisSerializer, value_value_1)
            }
        }
        let gutter_type : int32 = RuntimeType.UNDEFINED
        gutter_type = runtimeType(gutter)
        thisSerializer.writeInt8((gutter_type).toChar())
        if ((gutter_type) != (RuntimeType.UNDEFINED)) {
            const gutter_value  = gutter!
            let gutter_value_type : int32 = RuntimeType.UNDEFINED
            gutter_value_type = runtimeType(gutter_value)
            if (RuntimeType.STRING == gutter_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const gutter_value_0  = gutter_value as string
                thisSerializer.writeString(gutter_value_0)
            }
            else if (RuntimeType.NUMBER == gutter_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const gutter_value_1  = gutter_value as number
                thisSerializer.writeNumber(gutter_value_1)
            }
            else if (RuntimeType.OBJECT == gutter_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const gutter_value_2  = gutter_value as Resource
                Resource_serializer.write(thisSerializer, gutter_value_2)
            }
        }
        ArkUIGeneratedNativeModule._ListAttribute_setLanes(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCachedCount1Attribute(count: number | undefined, show: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let count_type : int32 = RuntimeType.UNDEFINED
        count_type = runtimeType(count)
        thisSerializer.writeInt8((count_type).toChar())
        if ((count_type) != (RuntimeType.UNDEFINED)) {
            const count_value  = count!
            thisSerializer.writeNumber(count_value)
        }
        let show_type : int32 = RuntimeType.UNDEFINED
        show_type = runtimeType(show)
        thisSerializer.writeInt8((show_type).toChar())
        if ((show_type) != (RuntimeType.UNDEFINED)) {
            const show_value  = show!
            thisSerializer.writeBoolean(show_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setCachedCount1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
export interface ListAttribute extends ScrollableCommonMethod {
    alignListItem(value: ListItemAlign | undefined): this {
        throw new Error("Unimplemented method alignListItem")
    }
    listDirection(value: Axis | undefined): this {
        throw new Error("Unimplemented method listDirection")
    }
    contentStartOffset(value: number | undefined): this {
        throw new Error("Unimplemented method contentStartOffset")
    }
    contentEndOffset(value: number | undefined): this {
        throw new Error("Unimplemented method contentEndOffset")
    }
    divider(value: ListDividerOptions | undefined): this {
        throw new Error("Unimplemented method divider")
    }
    multiSelectable(value: boolean | undefined): this {
        throw new Error("Unimplemented method multiSelectable")
    }
    cachedCount(value: number | undefined): this {
        throw new Error("Unimplemented method cachedCount")
    }
    chainAnimation(value: boolean | undefined): this {
        throw new Error("Unimplemented method chainAnimation")
    }
    chainAnimationOptions(value: ChainAnimationOptions | undefined): this {
        throw new Error("Unimplemented method chainAnimationOptions")
    }
    sticky(value: StickyStyle | undefined): this {
        throw new Error("Unimplemented method sticky")
    }
    scrollSnapAlign(value: ScrollSnapAlign | undefined): this {
        throw new Error("Unimplemented method scrollSnapAlign")
    }
    childrenMainSize(value: ChildrenMainSize | undefined): this {
        throw new Error("Unimplemented method childrenMainSize")
    }
    maintainVisibleContentPosition(value: boolean | undefined): this {
        throw new Error("Unimplemented method maintainVisibleContentPosition")
    }
    stackFromEnd(value: boolean | undefined): this {
        throw new Error("Unimplemented method stackFromEnd")
    }
    onScrollIndex(value: ((start: number,end: number,center: number) => void) | undefined): this {
        throw new Error("Unimplemented method onScrollIndex")
    }
    onScrollVisibleContentChange(value: OnScrollVisibleContentChangeCallback | undefined): this {
        throw new Error("Unimplemented method onScrollVisibleContentChange")
    }
    onItemMove(value: ((from: number,to: number) => boolean) | undefined): this {
        throw new Error("Unimplemented method onItemMove")
    }
    onItemDragStart(value: OnItemDragStartCallback | undefined): this {
        throw new Error("Unimplemented method onItemDragStart")
    }
    onItemDragEnter(value: ((event: ItemDragInfo) => void) | undefined): this {
        throw new Error("Unimplemented method onItemDragEnter")
    }
    onItemDragMove(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void) | undefined): this {
        throw new Error("Unimplemented method onItemDragMove")
    }
    onItemDragLeave(value: ((event: ItemDragInfo,itemIndex: number) => void) | undefined): this {
        throw new Error("Unimplemented method onItemDragLeave")
    }
    onItemDrop(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void) | undefined): this {
        throw new Error("Unimplemented method onItemDrop")
    }
    onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        throw new Error("Unimplemented method onScrollFrameBegin")
    }
    onWillScroll(value: OnWillScrollCallback | undefined): this {
        throw new Error("Unimplemented method onWillScroll")
    }
    onDidScroll(value: OnScrollCallback | undefined): this {
        throw new Error("Unimplemented method onDidScroll")
    }
    lanes(value: number | LengthConstrain | undefined, gutter?: Dimension): this {
        throw new Error("Unimplemented method lanes")
    }
    cachedCount(count: number | undefined, show: boolean | undefined): this {
        throw new Error("Unimplemented method cachedCount")
    }
    attributeModifier(value: AttributeModifier<ListAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkListStyle extends ArkScrollableCommonMethodStyle implements ListAttribute {
    alignListItem_value?: ListItemAlign | undefined
    listDirection_value?: Axis | undefined
    contentStartOffset_value?: number | undefined
    contentEndOffset_value?: number | undefined
    divider_value?: ListDividerOptions | undefined
    multiSelectable_value?: boolean | undefined
    cachedCount_value?: number | undefined
    chainAnimation_value?: boolean | undefined
    chainAnimationOptions_value?: ChainAnimationOptions | undefined
    sticky_value?: StickyStyle | undefined
    scrollSnapAlign_value?: ScrollSnapAlign | undefined
    childrenMainSize_value?: ChildrenMainSize | undefined
    maintainVisibleContentPosition_value?: boolean | undefined
    stackFromEnd_value?: boolean | undefined
    onScrollIndex_value?: ((start: number,end: number,center: number) => void) | undefined
    onScrollVisibleContentChange_value?: OnScrollVisibleContentChangeCallback | undefined
    onItemMove_value?: ((from: number,to: number) => boolean) | undefined
    onItemDragStart_value?: OnItemDragStartCallback | undefined
    onItemDragEnter_value?: ((event: ItemDragInfo) => void) | undefined
    onItemDragMove_value?: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void) | undefined
    onItemDragLeave_value?: ((event: ItemDragInfo,itemIndex: number) => void) | undefined
    onItemDrop_value?: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void) | undefined
    onScrollFrameBegin_value?: OnScrollFrameBeginCallback | undefined
    onWillScroll_value?: OnWillScrollCallback | undefined
    onDidScroll_value?: OnScrollCallback | undefined
    attributeModifier_value?: AttributeModifier<ListAttribute> | AttributeModifier<CommonMethod> | undefined
    public alignListItem(value: ListItemAlign | undefined): this {
        return this
    }
    public listDirection(value: Axis | undefined): this {
        return this
    }
    public contentStartOffset(value: number | undefined): this {
        return this
    }
    public contentEndOffset(value: number | undefined): this {
        return this
    }
    public divider(value: ListDividerOptions | undefined): this {
        return this
    }
    public multiSelectable(value: boolean | undefined): this {
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
    public childrenMainSize(value: ChildrenMainSize | undefined): this {
        return this
    }
    public maintainVisibleContentPosition(value: boolean | undefined): this {
        return this
    }
    public stackFromEnd(value: boolean | undefined): this {
        return this
    }
    public onScrollIndex(value: ((start: number,end: number,center: number) => void) | undefined): this {
        return this
    }
    public onScrollVisibleContentChange(value: OnScrollVisibleContentChangeCallback | undefined): this {
        return this
    }
    public onItemMove(value: ((from: number,to: number) => boolean) | undefined): this {
        return this
    }
    public onItemDragStart(value: OnItemDragStartCallback | undefined): this {
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
    public cachedCount(count: number | undefined, show: boolean | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<ListAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: ListAttribute): void {
        super.apply(target)
        if (this.alignListItem_value !== undefined)
            target.alignListItem(this.alignListItem_value!)
        if (this.listDirection_value !== undefined)
            target.listDirection(this.listDirection_value!)
        if (this.contentStartOffset_value !== undefined)
            target.contentStartOffset(this.contentStartOffset_value!)
        if (this.contentEndOffset_value !== undefined)
            target.contentEndOffset(this.contentEndOffset_value!)
        if (this.divider_value !== undefined)
            target.divider(this.divider_value!)
        if (this.multiSelectable_value !== undefined)
            target.multiSelectable(this.multiSelectable_value!)
        if (this.cachedCount_value !== undefined)
            target.cachedCount(this.cachedCount_value!)
        if (this.chainAnimation_value !== undefined)
            target.chainAnimation(this.chainAnimation_value!)
        if (this.chainAnimationOptions_value !== undefined)
            target.chainAnimationOptions(this.chainAnimationOptions_value!)
        if (this.sticky_value !== undefined)
            target.sticky(this.sticky_value!)
        if (this.scrollSnapAlign_value !== undefined)
            target.scrollSnapAlign(this.scrollSnapAlign_value!)
        if (this.childrenMainSize_value !== undefined)
            target.childrenMainSize(this.childrenMainSize_value!)
        if (this.maintainVisibleContentPosition_value !== undefined)
            target.maintainVisibleContentPosition(this.maintainVisibleContentPosition_value!)
        if (this.stackFromEnd_value !== undefined)
            target.stackFromEnd(this.stackFromEnd_value!)
        if (this.onScrollIndex_value !== undefined)
            target.onScrollIndex(this.onScrollIndex_value!)
        if (this.onScrollVisibleContentChange_value !== undefined)
            target.onScrollVisibleContentChange(this.onScrollVisibleContentChange_value!)
        if (this.onItemMove_value !== undefined)
            target.onItemMove(this.onItemMove_value!)
        if (this.onItemDragStart_value !== undefined)
            target.onItemDragStart(this.onItemDragStart_value!)
        if (this.onItemDragEnter_value !== undefined)
            target.onItemDragEnter(this.onItemDragEnter_value!)
        if (this.onItemDragMove_value !== undefined)
            target.onItemDragMove(this.onItemDragMove_value!)
        if (this.onItemDragLeave_value !== undefined)
            target.onItemDragLeave(this.onItemDragLeave_value!)
        if (this.onItemDrop_value !== undefined)
            target.onItemDrop(this.onItemDrop_value!)
        if (this.onScrollFrameBegin_value !== undefined)
            target.onScrollFrameBegin(this.onScrollFrameBegin_value!)
        if (this.onWillScroll_value !== undefined)
            target.onWillScroll(this.onWillScroll_value!)
        if (this.onDidScroll_value !== undefined)
            target.onDidScroll(this.onDidScroll_value!)
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
            this.getPeer()?.setAlignListItemAttribute(value_casted)
            return this
        }
        return this
    }
    public listDirection(value: Axis | undefined): this {
        if (this.checkPriority("listDirection")) {
            const value_casted = value as (Axis | undefined)
            this.getPeer()?.setListDirectionAttribute(value_casted)
            return this
        }
        return this
    }
    public contentStartOffset(value: number | undefined): this {
        if (this.checkPriority("contentStartOffset")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setContentStartOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    public contentEndOffset(value: number | undefined): this {
        if (this.checkPriority("contentEndOffset")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setContentEndOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    public divider(value: ListDividerOptions | undefined): this {
        if (this.checkPriority("divider")) {
            const value_casted = value as (ListDividerOptions | undefined)
            this.getPeer()?.setDividerAttribute(value_casted)
            return this
        }
        return this
    }
    public multiSelectable(value: boolean | undefined): this {
        if (this.checkPriority("multiSelectable")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setMultiSelectableAttribute(value_casted)
            return this
        }
        return this
    }
    public cachedCount(value: number | undefined): this {
        if (this.checkPriority("cachedCount")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setCachedCount0Attribute(value_casted)
            return this
        }
        return this
    }
    public chainAnimation(value: boolean | undefined): this {
        if (this.checkPriority("chainAnimation")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setChainAnimationAttribute(value_casted)
            return this
        }
        return this
    }
    public chainAnimationOptions(value: ChainAnimationOptions | undefined): this {
        if (this.checkPriority("chainAnimationOptions")) {
            const value_casted = value as (ChainAnimationOptions | undefined)
            this.getPeer()?.setChainAnimationOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public sticky(value: StickyStyle | undefined): this {
        if (this.checkPriority("sticky")) {
            const value_casted = value as (StickyStyle | undefined)
            this.getPeer()?.setStickyAttribute(value_casted)
            return this
        }
        return this
    }
    public scrollSnapAlign(value: ScrollSnapAlign | undefined): this {
        if (this.checkPriority("scrollSnapAlign")) {
            const value_casted = value as (ScrollSnapAlign | undefined)
            this.getPeer()?.setScrollSnapAlignAttribute(value_casted)
            return this
        }
        return this
    }
    public childrenMainSize(value: ChildrenMainSize | undefined): this {
        if (this.checkPriority("childrenMainSize")) {
            const value_casted = value as (ChildrenMainSize | undefined)
            this.getPeer()?.setChildrenMainSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public maintainVisibleContentPosition(value: boolean | undefined): this {
        if (this.checkPriority("maintainVisibleContentPosition")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setMaintainVisibleContentPositionAttribute(value_casted)
            return this
        }
        return this
    }
    public stackFromEnd(value: boolean | undefined): this {
        if (this.checkPriority("stackFromEnd")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setStackFromEndAttribute(value_casted)
            return this
        }
        return this
    }
    public onScrollIndex(value: ((start: number,end: number,center: number) => void) | undefined): this {
        if (this.checkPriority("onScrollIndex")) {
            const value_casted = value as (((start: number,end: number,center: number) => void) | undefined)
            this.getPeer()?.setOnScrollIndexAttribute(value_casted)
            return this
        }
        return this
    }
    public onScrollVisibleContentChange(value: OnScrollVisibleContentChangeCallback | undefined): this {
        if (this.checkPriority("onScrollVisibleContentChange")) {
            const value_casted = value as (OnScrollVisibleContentChangeCallback | undefined)
            this.getPeer()?.setOnScrollVisibleContentChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onItemMove(value: ((from: number,to: number) => boolean) | undefined): this {
        if (this.checkPriority("onItemMove")) {
            const value_casted = value as (((from: number,to: number) => boolean) | undefined)
            this.getPeer()?.setOnItemMoveAttribute(value_casted)
            return this
        }
        return this
    }
    public onItemDragStart(value: OnItemDragStartCallback | undefined): this {
        if (this.checkPriority("onItemDragStart")) {
            const value_casted = value as (OnItemDragStartCallback | undefined)
            this.getPeer()?.setOnItemDragStartAttribute(value_casted)
            return this
        }
        return this
    }
    public onItemDragEnter(value: ((event: ItemDragInfo) => void) | undefined): this {
        if (this.checkPriority("onItemDragEnter")) {
            const value_casted = value as (((event: ItemDragInfo) => void) | undefined)
            this.getPeer()?.setOnItemDragEnterAttribute(value_casted)
            return this
        }
        return this
    }
    public onItemDragMove(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void) | undefined): this {
        if (this.checkPriority("onItemDragMove")) {
            const value_casted = value as (((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void) | undefined)
            this.getPeer()?.setOnItemDragMoveAttribute(value_casted)
            return this
        }
        return this
    }
    public onItemDragLeave(value: ((event: ItemDragInfo,itemIndex: number) => void) | undefined): this {
        if (this.checkPriority("onItemDragLeave")) {
            const value_casted = value as (((event: ItemDragInfo,itemIndex: number) => void) | undefined)
            this.getPeer()?.setOnItemDragLeaveAttribute(value_casted)
            return this
        }
        return this
    }
    public onItemDrop(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void) | undefined): this {
        if (this.checkPriority("onItemDrop")) {
            const value_casted = value as (((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void) | undefined)
            this.getPeer()?.setOnItemDropAttribute(value_casted)
            return this
        }
        return this
    }
    public onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        if (this.checkPriority("onScrollFrameBegin")) {
            const value_casted = value as (OnScrollFrameBeginCallback | undefined)
            this.getPeer()?.setOnScrollFrameBeginAttribute(value_casted)
            return this
        }
        return this
    }
    public onWillScroll(value: OnWillScrollCallback | undefined): this {
        if (this.checkPriority("onWillScroll")) {
            const value_casted = value as (OnWillScrollCallback | undefined)
            this.getPeer()?.setOnWillScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public onDidScroll(value: OnScrollCallback | undefined): this {
        if (this.checkPriority("onDidScroll")) {
            const value_casted = value as (OnScrollCallback | undefined)
            this.getPeer()?.setOnDidScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public lanes(value: number | LengthConstrain | undefined, gutter?: Dimension): this {
        if (this.checkPriority("lanes")) {
            const value_casted = value as (number | LengthConstrain | undefined)
            const gutter_casted = gutter as (Dimension | undefined)
            this.getPeer()?.setLanesAttribute(value_casted, gutter_casted)
            return this
        }
        return this
    }
    public cachedCount(count: number | undefined, show: boolean | undefined): this {
        if (this.checkPriority("cachedCount")) {
            const count_casted = count as (number | undefined)
            const show_casted = show as (boolean | undefined)
            this.getPeer()?.setCachedCount1Attribute(count_casted, show_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ListAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withListStyle(receiver: ListAttribute, modifier: AttributeModifier<ListAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkListStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("List")
// export function List(
//     options?: ListOptions,
//     @memo
//     content_?: () => void,
// ): ListAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function List(
    @memo
    style: ((attributes: ListAttribute) => void) | undefined,
    options?: ListOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkListComponent>((): ArkListComponent => {
        return new ArkListComponent()
    })
    NodeAttach<ArkListPeer>((): ArkListPeer => ArkListPeer.create(receiver), (_: ArkListPeer): void => {
        receiver.setListOptions(options)
        style?.(receiver)
        withListStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkListSet extends ArkScrollableCommonMethodSet implements ListAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _alignListItem_flag?: boolean
    _alignListItem0_value?: ListItemAlign | undefined
    _listDirection_flag?: boolean
    _listDirection0_value?: Axis | undefined
    _contentStartOffset_flag?: boolean
    _contentStartOffset0_value?: number | undefined
    _contentEndOffset_flag?: boolean
    _contentEndOffset0_value?: number | undefined
    _divider_flag?: boolean
    _divider0_value?: ListDividerOptions | undefined
    _multiSelectable_flag?: boolean
    _multiSelectable0_value?: boolean | undefined
    _cachedCount_flag?: boolean
    _cachedCount0_value?: number | undefined
    _cachedCount1_value?: boolean | undefined
    _chainAnimation_flag?: boolean
    _chainAnimation0_value?: boolean | undefined
    _chainAnimationOptions_flag?: boolean
    _chainAnimationOptions0_value?: ChainAnimationOptions | undefined
    _sticky_flag?: boolean
    _sticky0_value?: StickyStyle | undefined
    _scrollSnapAlign_flag?: boolean
    _scrollSnapAlign0_value?: ScrollSnapAlign | undefined
    _childrenMainSize_flag?: boolean
    _childrenMainSize0_value?: ChildrenMainSize | undefined
    _maintainVisibleContentPosition_flag?: boolean
    _maintainVisibleContentPosition0_value?: boolean | undefined
    _stackFromEnd_flag?: boolean
    _stackFromEnd0_value?: boolean | undefined
    _onScrollIndex_flag?: boolean
    _onScrollIndex0_value?: ((start: number,end: number,center: number) => void) | undefined
    _onScrollVisibleContentChange_flag?: boolean
    _onScrollVisibleContentChange0_value?: OnScrollVisibleContentChangeCallback | undefined
    _onItemMove_flag?: boolean
    _onItemMove0_value?: ((from: number,to: number) => boolean) | undefined
    _onItemDragStart_flag?: boolean
    _onItemDragStart0_value?: OnItemDragStartCallback | undefined
    _onItemDragEnter_flag?: boolean
    _onItemDragEnter0_value?: ((event: ItemDragInfo) => void) | undefined
    _onItemDragMove_flag?: boolean
    _onItemDragMove0_value?: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void) | undefined
    _onItemDragLeave_flag?: boolean
    _onItemDragLeave0_value?: ((event: ItemDragInfo,itemIndex: number) => void) | undefined
    _onItemDrop_flag?: boolean
    _onItemDrop0_value?: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void) | undefined
    _onScrollFrameBegin_flag?: boolean
    _onScrollFrameBegin0_value?: OnScrollFrameBeginCallback | undefined
    _onWillScroll_flag?: boolean
    _onWillScroll0_value?: OnWillScrollCallback | undefined
    _onDidScroll_flag?: boolean
    _onDidScroll0_value?: OnScrollCallback | undefined
    _lanes_flag?: boolean
    _lanes0_value?: number | LengthConstrain | undefined
    _lanes1_value?: Dimension | undefined
    applyModifierPatch(component: ListAttribute): void {
        if (this._alignListItem_flag)
            component.alignListItem((this._alignListItem0_value as ListItemAlign | undefined))
        if (this._listDirection_flag)
            component.listDirection((this._listDirection0_value as Axis | undefined))
        if (this._contentStartOffset_flag)
            component.contentStartOffset((this._contentStartOffset0_value as number | undefined))
        if (this._contentEndOffset_flag)
            component.contentEndOffset((this._contentEndOffset0_value as number | undefined))
        if (this._divider_flag)
            component.divider((this._divider0_value as ListDividerOptions | undefined))
        if (this._multiSelectable_flag)
            component.multiSelectable((this._multiSelectable0_value as boolean | undefined))
        if (this._cachedCount_flag)
            component.cachedCount((this._cachedCount0_value as number | undefined), (this._cachedCount1_value as boolean | undefined))
        if (this._chainAnimation_flag)
            component.chainAnimation((this._chainAnimation0_value as boolean | undefined))
        if (this._chainAnimationOptions_flag)
            component.chainAnimationOptions((this._chainAnimationOptions0_value as ChainAnimationOptions | undefined))
        if (this._sticky_flag)
            component.sticky((this._sticky0_value as StickyStyle | undefined))
        if (this._scrollSnapAlign_flag)
            component.scrollSnapAlign((this._scrollSnapAlign0_value as ScrollSnapAlign | undefined))
        if (this._childrenMainSize_flag)
            component.childrenMainSize((this._childrenMainSize0_value as ChildrenMainSize | undefined))
        if (this._maintainVisibleContentPosition_flag)
            component.maintainVisibleContentPosition((this._maintainVisibleContentPosition0_value as boolean | undefined))
        if (this._stackFromEnd_flag)
            component.stackFromEnd((this._stackFromEnd0_value as boolean | undefined))
        if (this._onScrollIndex_flag)
            component.onScrollIndex((this._onScrollIndex0_value as ((start: number,end: number,center: number) => void) | undefined))
        if (this._onScrollVisibleContentChange_flag)
            component.onScrollVisibleContentChange((this._onScrollVisibleContentChange0_value as OnScrollVisibleContentChangeCallback | undefined))
        if (this._onItemMove_flag)
            component.onItemMove((this._onItemMove0_value as ((from: number,to: number) => boolean) | undefined))
        if (this._onItemDragStart_flag)
            component.onItemDragStart((this._onItemDragStart0_value as OnItemDragStartCallback | undefined))
        if (this._onItemDragEnter_flag)
            component.onItemDragEnter((this._onItemDragEnter0_value as ((event: ItemDragInfo) => void) | undefined))
        if (this._onItemDragMove_flag)
            component.onItemDragMove((this._onItemDragMove0_value as ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void) | undefined))
        if (this._onItemDragLeave_flag)
            component.onItemDragLeave((this._onItemDragLeave0_value as ((event: ItemDragInfo,itemIndex: number) => void) | undefined))
        if (this._onItemDrop_flag)
            component.onItemDrop((this._onItemDrop0_value as ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void) | undefined))
        if (this._onScrollFrameBegin_flag)
            component.onScrollFrameBegin((this._onScrollFrameBegin0_value as OnScrollFrameBeginCallback | undefined))
        if (this._onWillScroll_flag)
            component.onWillScroll((this._onWillScroll0_value as OnWillScrollCallback | undefined))
        if (this._onDidScroll_flag)
            component.onDidScroll((this._onDidScroll0_value as OnScrollCallback | undefined))
        if (this._lanes_flag)
            component.lanes((this._lanes0_value as number | LengthConstrain | undefined), (this._lanes1_value as Dimension | undefined))
    }
    public alignListItem(value: ListItemAlign | undefined): this {
        this._alignListItem_flag = true
        this._alignListItem0_value = value
        return this
    }
    public listDirection(value: Axis | undefined): this {
        this._listDirection_flag = true
        this._listDirection0_value = value
        return this
    }
    public contentStartOffset(value: number | undefined): this {
        this._contentStartOffset_flag = true
        this._contentStartOffset0_value = value
        return this
    }
    public contentEndOffset(value: number | undefined): this {
        this._contentEndOffset_flag = true
        this._contentEndOffset0_value = value
        return this
    }
    public divider(value: ListDividerOptions | undefined): this {
        this._divider_flag = true
        this._divider0_value = value
        return this
    }
    public multiSelectable(value: boolean | undefined): this {
        this._multiSelectable_flag = true
        this._multiSelectable0_value = value
        return this
    }
    public cachedCount(count: number | undefined, show: boolean | undefined): this {
        this._cachedCount_flag = true
        this._cachedCount0_value = count
        this._cachedCount1_value = show
        return this
    }
    public chainAnimation(value: boolean | undefined): this {
        this._chainAnimation_flag = true
        this._chainAnimation0_value = value
        return this
    }
    public chainAnimationOptions(value: ChainAnimationOptions | undefined): this {
        this._chainAnimationOptions_flag = true
        this._chainAnimationOptions0_value = value
        return this
    }
    public sticky(value: StickyStyle | undefined): this {
        this._sticky_flag = true
        this._sticky0_value = value
        return this
    }
    public scrollSnapAlign(value: ScrollSnapAlign | undefined): this {
        this._scrollSnapAlign_flag = true
        this._scrollSnapAlign0_value = value
        return this
    }
    public childrenMainSize(value: ChildrenMainSize | undefined): this {
        this._childrenMainSize_flag = true
        this._childrenMainSize0_value = value
        return this
    }
    public maintainVisibleContentPosition(value: boolean | undefined): this {
        this._maintainVisibleContentPosition_flag = true
        this._maintainVisibleContentPosition0_value = value
        return this
    }
    public stackFromEnd(value: boolean | undefined): this {
        this._stackFromEnd_flag = true
        this._stackFromEnd0_value = value
        return this
    }
    public onScrollIndex(value: ((start: number,end: number,center: number) => void) | undefined): this {
        this._onScrollIndex_flag = true
        this._onScrollIndex0_value = value
        return this
    }
    public onScrollVisibleContentChange(value: OnScrollVisibleContentChangeCallback | undefined): this {
        this._onScrollVisibleContentChange_flag = true
        this._onScrollVisibleContentChange0_value = value
        return this
    }
    public onItemMove(value: ((from: number,to: number) => boolean) | undefined): this {
        this._onItemMove_flag = true
        this._onItemMove0_value = value
        return this
    }
    public onItemDragStart(value: OnItemDragStartCallback | undefined): this {
        this._onItemDragStart_flag = true
        this._onItemDragStart0_value = value
        return this
    }
    public onItemDragEnter(value: ((event: ItemDragInfo) => void) | undefined): this {
        this._onItemDragEnter_flag = true
        this._onItemDragEnter0_value = value
        return this
    }
    public onItemDragMove(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void) | undefined): this {
        this._onItemDragMove_flag = true
        this._onItemDragMove0_value = value
        return this
    }
    public onItemDragLeave(value: ((event: ItemDragInfo,itemIndex: number) => void) | undefined): this {
        this._onItemDragLeave_flag = true
        this._onItemDragLeave0_value = value
        return this
    }
    public onItemDrop(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void) | undefined): this {
        this._onItemDrop_flag = true
        this._onItemDrop0_value = value
        return this
    }
    public onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        this._onScrollFrameBegin_flag = true
        this._onScrollFrameBegin0_value = value
        return this
    }
    public onWillScroll(value: OnWillScrollCallback | undefined): this {
        this._onWillScroll_flag = true
        this._onWillScroll0_value = value
        return this
    }
    public onDidScroll(value: OnScrollCallback | undefined): this {
        this._onDidScroll_flag = true
        this._onDidScroll0_value = value
        return this
    }
    public lanes(value: number | LengthConstrain | undefined, gutter?: Dimension): this {
        this._lanes_flag = true
        this._lanes0_value = value
        this._lanes1_value = gutter
        return this
    }
    public attributeModifier(value: AttributeModifier<ListAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class ListScroller_serializer {
    public static write(buffer: SerializerBase, value: ListScroller): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): ListScroller {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return ListScrollerInternal.fromPtr(ptr)
    }
}
export class CloseSwipeActionOptions_serializer {
    public static write(buffer: SerializerBase, value: CloseSwipeActionOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_onFinish  = value.onFinish
        let value_onFinish_type : int32 = RuntimeType.UNDEFINED
        value_onFinish_type = runtimeType(value_onFinish)
        valueSerializer.writeInt8((value_onFinish_type).toChar())
        if ((value_onFinish_type) != (RuntimeType.UNDEFINED)) {
            const value_onFinish_value  = value_onFinish!
            valueSerializer.holdAndWriteCallback(value_onFinish_value)
        }
    }
    public static read(buffer: DeserializerBase): CloseSwipeActionOptions {
        let valueDeserializer : DeserializerBase = buffer
        const onFinish_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onFinish_buf : (() => void) | undefined
        if ((onFinish_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const onFinish_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onFinish_buf__call : KPointer = valueDeserializer.readPointer()
            const onFinish_buf__callSync : KPointer = valueDeserializer.readPointer()
            onFinish_buf = ():void => { 
    const onFinish_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onFinish_buf__argsSerializer.writeInt32(onFinish_buf__resource.resourceId);
    onFinish_buf__argsSerializer.writePointer(onFinish_buf__call);
    onFinish_buf__argsSerializer.writePointer(onFinish_buf__callSync);
    InteropNativeModule._CallCallback(-1867723152, onFinish_buf__argsSerializer.asBuffer(), onFinish_buf__argsSerializer.length());
    onFinish_buf__argsSerializer.release();
    return; }
        }
        const onFinish_result : (() => void) | undefined = onFinish_buf
        let value : CloseSwipeActionOptions = ({onFinish: onFinish_result} as CloseSwipeActionOptions)
        return value
    }
}
export class ListOptions_serializer {
    public static write(buffer: SerializerBase, value: ListOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_initialIndex  = value.initialIndex
        let value_initialIndex_type : int32 = RuntimeType.UNDEFINED
        value_initialIndex_type = runtimeType(value_initialIndex)
        valueSerializer.writeInt8((value_initialIndex_type).toChar())
        if ((value_initialIndex_type) != (RuntimeType.UNDEFINED)) {
            const value_initialIndex_value  = value_initialIndex!
            valueSerializer.writeNumber(value_initialIndex_value)
        }
        const value_space  = value.space
        let value_space_type : int32 = RuntimeType.UNDEFINED
        value_space_type = runtimeType(value_space)
        valueSerializer.writeInt8((value_space_type).toChar())
        if ((value_space_type) != (RuntimeType.UNDEFINED)) {
            const value_space_value  = value_space!
            let value_space_value_type : int32 = RuntimeType.UNDEFINED
            value_space_value_type = runtimeType(value_space_value)
            if (RuntimeType.NUMBER == value_space_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_space_value_0  = value_space_value as number
                valueSerializer.writeNumber(value_space_value_0)
            }
            else if (RuntimeType.STRING == value_space_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_space_value_1  = value_space_value as string
                valueSerializer.writeString(value_space_value_1)
            }
        }
        const value_scroller  = value.scroller
        let value_scroller_type : int32 = RuntimeType.UNDEFINED
        value_scroller_type = runtimeType(value_scroller)
        valueSerializer.writeInt8((value_scroller_type).toChar())
        if ((value_scroller_type) != (RuntimeType.UNDEFINED)) {
            const value_scroller_value  = value_scroller!
            Scroller_serializer.write(valueSerializer, value_scroller_value)
        }
    }
    public static read(buffer: DeserializerBase): ListOptions {
        let valueDeserializer : DeserializerBase = buffer
        const initialIndex_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let initialIndex_buf : number | undefined
        if ((initialIndex_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            initialIndex_buf = (valueDeserializer.readNumber() as number)
        }
        const initialIndex_result : number | undefined = initialIndex_buf
        const space_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let space_buf : number | string | undefined
        if ((space_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const space_buf__selector : int32 = valueDeserializer.readInt8()
            let space_buf_ : number | string | undefined
            if (space_buf__selector == (0).toChar()) {
                space_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (space_buf__selector == (1).toChar()) {
                space_buf_ = (valueDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for space_buf_ has to be chosen through deserialisation.")
            }
            space_buf = (space_buf_ as number | string)
        }
        const space_result : number | string | undefined = space_buf
        const scroller_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let scroller_buf : Scroller | undefined
        if ((scroller_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            scroller_buf = (Scroller_serializer.read(valueDeserializer) as Scroller)
        }
        const scroller_result : Scroller | undefined = scroller_buf
        let value : ListOptions = ({initialIndex: initialIndex_result, space: space_result, scroller: scroller_result} as ListOptions)
        return value
    }
}
export class VisibleListContentInfo_serializer {
    public static write(buffer: SerializerBase, value: VisibleListContentInfo): void {
        let valueSerializer : SerializerBase = buffer
        const value_index  = value.index
        valueSerializer.writeNumber(value_index)
        const value_itemGroupArea  = value.itemGroupArea
        let value_itemGroupArea_type : int32 = RuntimeType.UNDEFINED
        value_itemGroupArea_type = runtimeType(value_itemGroupArea)
        valueSerializer.writeInt8((value_itemGroupArea_type).toChar())
        if ((value_itemGroupArea_type) != (RuntimeType.UNDEFINED)) {
            const value_itemGroupArea_value  = (value_itemGroupArea as ListItemGroupArea)
            valueSerializer.writeInt32(TypeChecker.ListItemGroupArea_ToNumeric(value_itemGroupArea_value))
        }
        const value_itemIndexInGroup  = value.itemIndexInGroup
        let value_itemIndexInGroup_type : int32 = RuntimeType.UNDEFINED
        value_itemIndexInGroup_type = runtimeType(value_itemIndexInGroup)
        valueSerializer.writeInt8((value_itemIndexInGroup_type).toChar())
        if ((value_itemIndexInGroup_type) != (RuntimeType.UNDEFINED)) {
            const value_itemIndexInGroup_value  = value_itemIndexInGroup!
            valueSerializer.writeNumber(value_itemIndexInGroup_value)
        }
    }
    public static read(buffer: DeserializerBase): VisibleListContentInfo {
        let valueDeserializer : DeserializerBase = buffer
        const index_result : number = (valueDeserializer.readNumber() as number)
        const itemGroupArea_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let itemGroupArea_buf : ListItemGroupArea | undefined
        if ((itemGroupArea_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            itemGroupArea_buf = TypeChecker.ListItemGroupArea_FromNumeric(valueDeserializer.readInt32())
        }
        const itemGroupArea_result : ListItemGroupArea | undefined = itemGroupArea_buf
        const itemIndexInGroup_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let itemIndexInGroup_buf : number | undefined
        if ((itemIndexInGroup_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            itemIndexInGroup_buf = (valueDeserializer.readNumber() as number)
        }
        const itemIndexInGroup_result : number | undefined = itemIndexInGroup_buf
        let value : VisibleListContentInfo = ({index: index_result, itemGroupArea: itemGroupArea_result, itemIndexInGroup: itemIndexInGroup_result} as VisibleListContentInfo)
        return value
    }
}
export class ChainAnimationOptions_serializer {
    public static write(buffer: SerializerBase, value: ChainAnimationOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_minSpace  = value.minSpace
        let value_minSpace_type : int32 = RuntimeType.UNDEFINED
        value_minSpace_type = runtimeType(value_minSpace)
        if (RuntimeType.STRING == value_minSpace_type) {
            valueSerializer.writeInt8((0).toChar())
            const value_minSpace_0  = value_minSpace as string
            valueSerializer.writeString(value_minSpace_0)
        }
        else if (RuntimeType.NUMBER == value_minSpace_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_minSpace_1  = value_minSpace as number
            valueSerializer.writeNumber(value_minSpace_1)
        }
        else if (RuntimeType.OBJECT == value_minSpace_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_minSpace_2  = value_minSpace as Resource
            Resource_serializer.write(valueSerializer, value_minSpace_2)
        }
        const value_maxSpace  = value.maxSpace
        let value_maxSpace_type : int32 = RuntimeType.UNDEFINED
        value_maxSpace_type = runtimeType(value_maxSpace)
        if (RuntimeType.STRING == value_maxSpace_type) {
            valueSerializer.writeInt8((0).toChar())
            const value_maxSpace_0  = value_maxSpace as string
            valueSerializer.writeString(value_maxSpace_0)
        }
        else if (RuntimeType.NUMBER == value_maxSpace_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_maxSpace_1  = value_maxSpace as number
            valueSerializer.writeNumber(value_maxSpace_1)
        }
        else if (RuntimeType.OBJECT == value_maxSpace_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_maxSpace_2  = value_maxSpace as Resource
            Resource_serializer.write(valueSerializer, value_maxSpace_2)
        }
        const value_conductivity  = value.conductivity
        let value_conductivity_type : int32 = RuntimeType.UNDEFINED
        value_conductivity_type = runtimeType(value_conductivity)
        valueSerializer.writeInt8((value_conductivity_type).toChar())
        if ((value_conductivity_type) != (RuntimeType.UNDEFINED)) {
            const value_conductivity_value  = value_conductivity!
            valueSerializer.writeNumber(value_conductivity_value)
        }
        const value_intensity  = value.intensity
        let value_intensity_type : int32 = RuntimeType.UNDEFINED
        value_intensity_type = runtimeType(value_intensity)
        valueSerializer.writeInt8((value_intensity_type).toChar())
        if ((value_intensity_type) != (RuntimeType.UNDEFINED)) {
            const value_intensity_value  = value_intensity!
            valueSerializer.writeNumber(value_intensity_value)
        }
        const value_edgeEffect  = value.edgeEffect
        let value_edgeEffect_type : int32 = RuntimeType.UNDEFINED
        value_edgeEffect_type = runtimeType(value_edgeEffect)
        valueSerializer.writeInt8((value_edgeEffect_type).toChar())
        if ((value_edgeEffect_type) != (RuntimeType.UNDEFINED)) {
            const value_edgeEffect_value  = (value_edgeEffect as ChainEdgeEffect)
            valueSerializer.writeInt32(TypeChecker.ChainEdgeEffect_ToNumeric(value_edgeEffect_value))
        }
        const value_stiffness  = value.stiffness
        let value_stiffness_type : int32 = RuntimeType.UNDEFINED
        value_stiffness_type = runtimeType(value_stiffness)
        valueSerializer.writeInt8((value_stiffness_type).toChar())
        if ((value_stiffness_type) != (RuntimeType.UNDEFINED)) {
            const value_stiffness_value  = value_stiffness!
            valueSerializer.writeNumber(value_stiffness_value)
        }
        const value_damping  = value.damping
        let value_damping_type : int32 = RuntimeType.UNDEFINED
        value_damping_type = runtimeType(value_damping)
        valueSerializer.writeInt8((value_damping_type).toChar())
        if ((value_damping_type) != (RuntimeType.UNDEFINED)) {
            const value_damping_value  = value_damping!
            valueSerializer.writeNumber(value_damping_value)
        }
    }
    public static read(buffer: DeserializerBase): ChainAnimationOptions {
        let valueDeserializer : DeserializerBase = buffer
        const minSpace_buf_selector : int32 = valueDeserializer.readInt8()
        let minSpace_buf : string | number | Resource | undefined
        if (minSpace_buf_selector == (0).toChar()) {
            minSpace_buf = (valueDeserializer.readString() as string)
        }
        else if (minSpace_buf_selector == (1).toChar()) {
            minSpace_buf = (valueDeserializer.readNumber() as number)
        }
        else if (minSpace_buf_selector == (2).toChar()) {
            minSpace_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for minSpace_buf has to be chosen through deserialisation.")
        }
        const minSpace_result : Length = (minSpace_buf as string | number | Resource)
        const maxSpace_buf_selector : int32 = valueDeserializer.readInt8()
        let maxSpace_buf : string | number | Resource | undefined
        if (maxSpace_buf_selector == (0).toChar()) {
            maxSpace_buf = (valueDeserializer.readString() as string)
        }
        else if (maxSpace_buf_selector == (1).toChar()) {
            maxSpace_buf = (valueDeserializer.readNumber() as number)
        }
        else if (maxSpace_buf_selector == (2).toChar()) {
            maxSpace_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for maxSpace_buf has to be chosen through deserialisation.")
        }
        const maxSpace_result : Length = (maxSpace_buf as string | number | Resource)
        const conductivity_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let conductivity_buf : number | undefined
        if ((conductivity_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            conductivity_buf = (valueDeserializer.readNumber() as number)
        }
        const conductivity_result : number | undefined = conductivity_buf
        const intensity_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let intensity_buf : number | undefined
        if ((intensity_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            intensity_buf = (valueDeserializer.readNumber() as number)
        }
        const intensity_result : number | undefined = intensity_buf
        const edgeEffect_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let edgeEffect_buf : ChainEdgeEffect | undefined
        if ((edgeEffect_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            edgeEffect_buf = TypeChecker.ChainEdgeEffect_FromNumeric(valueDeserializer.readInt32())
        }
        const edgeEffect_result : ChainEdgeEffect | undefined = edgeEffect_buf
        const stiffness_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let stiffness_buf : number | undefined
        if ((stiffness_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            stiffness_buf = (valueDeserializer.readNumber() as number)
        }
        const stiffness_result : number | undefined = stiffness_buf
        const damping_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let damping_buf : number | undefined
        if ((damping_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            damping_buf = (valueDeserializer.readNumber() as number)
        }
        const damping_result : number | undefined = damping_buf
        let value : ChainAnimationOptions = ({minSpace: minSpace_result, maxSpace: maxSpace_result, conductivity: conductivity_result, intensity: intensity_result, edgeEffect: edgeEffect_result, stiffness: stiffness_result, damping: damping_result} as ChainAnimationOptions)
        return value
    }
}
export class ListDividerOptions_serializer {
    public static write(buffer: SerializerBase, value: ListDividerOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_strokeWidth  = value.strokeWidth
        let value_strokeWidth_type : int32 = RuntimeType.UNDEFINED
        value_strokeWidth_type = runtimeType(value_strokeWidth)
        if (RuntimeType.STRING == value_strokeWidth_type) {
            valueSerializer.writeInt8((0).toChar())
            const value_strokeWidth_0  = value_strokeWidth as string
            valueSerializer.writeString(value_strokeWidth_0)
        }
        else if (RuntimeType.NUMBER == value_strokeWidth_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_strokeWidth_1  = value_strokeWidth as number
            valueSerializer.writeNumber(value_strokeWidth_1)
        }
        else if (RuntimeType.OBJECT == value_strokeWidth_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_strokeWidth_2  = value_strokeWidth as Resource
            Resource_serializer.write(valueSerializer, value_strokeWidth_2)
        }
        const value_color  = value.color
        let value_color_type : int32 = RuntimeType.UNDEFINED
        value_color_type = runtimeType(value_color)
        valueSerializer.writeInt8((value_color_type).toChar())
        if ((value_color_type) != (RuntimeType.UNDEFINED)) {
            const value_color_value  = value_color!
            let value_color_value_type : int32 = RuntimeType.UNDEFINED
            value_color_value_type = runtimeType(value_color_value)
            if (TypeChecker.isColor(value_color_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_color_value_0  = value_color_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_color_value_0))
            }
            else if (RuntimeType.NUMBER == value_color_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_color_value_1  = value_color_value as number
                valueSerializer.writeNumber(value_color_value_1)
            }
            else if (RuntimeType.STRING == value_color_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_color_value_2  = value_color_value as string
                valueSerializer.writeString(value_color_value_2)
            }
            else if (RuntimeType.OBJECT == value_color_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_color_value_3  = value_color_value as Resource
                Resource_serializer.write(valueSerializer, value_color_value_3)
            }
        }
        const value_startMargin  = value.startMargin
        let value_startMargin_type : int32 = RuntimeType.UNDEFINED
        value_startMargin_type = runtimeType(value_startMargin)
        valueSerializer.writeInt8((value_startMargin_type).toChar())
        if ((value_startMargin_type) != (RuntimeType.UNDEFINED)) {
            const value_startMargin_value  = value_startMargin!
            let value_startMargin_value_type : int32 = RuntimeType.UNDEFINED
            value_startMargin_value_type = runtimeType(value_startMargin_value)
            if (RuntimeType.STRING == value_startMargin_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_startMargin_value_0  = value_startMargin_value as string
                valueSerializer.writeString(value_startMargin_value_0)
            }
            else if (RuntimeType.NUMBER == value_startMargin_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_startMargin_value_1  = value_startMargin_value as number
                valueSerializer.writeNumber(value_startMargin_value_1)
            }
            else if (RuntimeType.OBJECT == value_startMargin_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_startMargin_value_2  = value_startMargin_value as Resource
                Resource_serializer.write(valueSerializer, value_startMargin_value_2)
            }
        }
        const value_endMargin  = value.endMargin
        let value_endMargin_type : int32 = RuntimeType.UNDEFINED
        value_endMargin_type = runtimeType(value_endMargin)
        valueSerializer.writeInt8((value_endMargin_type).toChar())
        if ((value_endMargin_type) != (RuntimeType.UNDEFINED)) {
            const value_endMargin_value  = value_endMargin!
            let value_endMargin_value_type : int32 = RuntimeType.UNDEFINED
            value_endMargin_value_type = runtimeType(value_endMargin_value)
            if (RuntimeType.STRING == value_endMargin_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_endMargin_value_0  = value_endMargin_value as string
                valueSerializer.writeString(value_endMargin_value_0)
            }
            else if (RuntimeType.NUMBER == value_endMargin_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_endMargin_value_1  = value_endMargin_value as number
                valueSerializer.writeNumber(value_endMargin_value_1)
            }
            else if (RuntimeType.OBJECT == value_endMargin_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_endMargin_value_2  = value_endMargin_value as Resource
                Resource_serializer.write(valueSerializer, value_endMargin_value_2)
            }
        }
    }
    public static read(buffer: DeserializerBase): ListDividerOptions {
        let valueDeserializer : DeserializerBase = buffer
        const strokeWidth_buf_selector : int32 = valueDeserializer.readInt8()
        let strokeWidth_buf : string | number | Resource | undefined
        if (strokeWidth_buf_selector == (0).toChar()) {
            strokeWidth_buf = (valueDeserializer.readString() as string)
        }
        else if (strokeWidth_buf_selector == (1).toChar()) {
            strokeWidth_buf = (valueDeserializer.readNumber() as number)
        }
        else if (strokeWidth_buf_selector == (2).toChar()) {
            strokeWidth_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for strokeWidth_buf has to be chosen through deserialisation.")
        }
        const strokeWidth_result : Length = (strokeWidth_buf as string | number | Resource)
        const color_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let color_buf : ResourceColor | undefined
        if ((color_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const color_buf__selector : int32 = valueDeserializer.readInt8()
            let color_buf_ : Color | number | string | Resource | undefined
            if (color_buf__selector == (0).toChar()) {
                color_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (color_buf__selector == (1).toChar()) {
                color_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (color_buf__selector == (2).toChar()) {
                color_buf_ = (valueDeserializer.readString() as string)
            }
            else if (color_buf__selector == (3).toChar()) {
                color_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for color_buf_ has to be chosen through deserialisation.")
            }
            color_buf = (color_buf_ as Color | number | string | Resource)
        }
        const color_result : ResourceColor | undefined = color_buf
        const startMargin_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let startMargin_buf : Length | undefined
        if ((startMargin_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const startMargin_buf__selector : int32 = valueDeserializer.readInt8()
            let startMargin_buf_ : string | number | Resource | undefined
            if (startMargin_buf__selector == (0).toChar()) {
                startMargin_buf_ = (valueDeserializer.readString() as string)
            }
            else if (startMargin_buf__selector == (1).toChar()) {
                startMargin_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (startMargin_buf__selector == (2).toChar()) {
                startMargin_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for startMargin_buf_ has to be chosen through deserialisation.")
            }
            startMargin_buf = (startMargin_buf_ as string | number | Resource)
        }
        const startMargin_result : Length | undefined = startMargin_buf
        const endMargin_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let endMargin_buf : Length | undefined
        if ((endMargin_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const endMargin_buf__selector : int32 = valueDeserializer.readInt8()
            let endMargin_buf_ : string | number | Resource | undefined
            if (endMargin_buf__selector == (0).toChar()) {
                endMargin_buf_ = (valueDeserializer.readString() as string)
            }
            else if (endMargin_buf__selector == (1).toChar()) {
                endMargin_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (endMargin_buf__selector == (2).toChar()) {
                endMargin_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for endMargin_buf_ has to be chosen through deserialisation.")
            }
            endMargin_buf = (endMargin_buf_ as string | number | Resource)
        }
        const endMargin_result : Length | undefined = endMargin_buf
        let value : ListDividerOptions = ({strokeWidth: strokeWidth_result, color: color_result, startMargin: startMargin_result, endMargin: endMargin_result} as ListDividerOptions)
        return value
    }
}
export class ListScrollerInternal {
    public static fromPtr(ptr: KPointer): ListScroller {
        return new ListScroller(ptr)
    }
}
export class ListScroller extends Scroller implements MaterializedBase {
    constructor(peerPtr: KPointer) {
        super(peerPtr)
    }
    constructor() {
        this(ListScroller.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ListScroller_construct()
        return retval
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
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : RectResult = RectResult_serializer.read(retvalDeserializer)
        return returnResult
    }
    private scrollToItemInGroup_serialize(index: number, indexInGroup: number, smooth?: boolean, align?: ScrollAlign): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let smooth_type : int32 = RuntimeType.UNDEFINED
        smooth_type = runtimeType(smooth)
        thisSerializer.writeInt8((smooth_type).toChar())
        if ((smooth_type) != (RuntimeType.UNDEFINED)) {
            const smooth_value  = smooth!
            thisSerializer.writeBoolean(smooth_value)
        }
        let align_type : int32 = RuntimeType.UNDEFINED
        align_type = runtimeType(align)
        thisSerializer.writeInt8((align_type).toChar())
        if ((align_type) != (RuntimeType.UNDEFINED)) {
            const align_value  = (align as ScrollAlign)
            thisSerializer.writeInt32(TypeChecker.ScrollAlign_ToNumeric(align_value))
        }
        ArkUIGeneratedNativeModule._ListScroller_scrollToItemInGroup(this.peer!.ptr, index, indexInGroup, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private closeAllSwipeActions_serialize(options?: CloseSwipeActionOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            CloseSwipeActionOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._ListScroller_closeAllSwipeActions(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getVisibleListContentInfo_serialize(x: number, y: number): VisibleListContentInfo {
        const retval  = ArkUIGeneratedNativeModule._ListScroller_getVisibleListContentInfo(this.peer!.ptr, x, y)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : VisibleListContentInfo = VisibleListContentInfo_serializer.read(retvalDeserializer)
        return returnResult
    }
}

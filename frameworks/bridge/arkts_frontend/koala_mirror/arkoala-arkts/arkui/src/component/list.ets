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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr, Finalizable } from "@koalaui/interop"
import { ChildrenMainSize_serializer, ArkScrollableCommonMethodPeer, ScrollableCommonMethod, ChildrenMainSize, OnItemDragStartCallback, ItemDragInfo, OnWillScrollCallback, OnScrollCallback, CommonMethod, ArkScrollableCommonMethodComponent, ArkScrollableCommonMethodStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, ScrollableCommonMethodModifier, CommonMethodModifier, RectResult_serializer, RectResult } from "./common"
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
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
export class ArkListPeer extends ArkScrollableCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkListPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._List_construct(peerId, flags)
        const _peer  = new ArkListPeer(_peerPtr, peerId, 'List', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setListOptionsAttribute(options?: ListOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            ListOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListInterface_setListOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAlignListItemAttribute(value: ListItemAlign | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as ListItemAlign)
            thisSerializer.writeInt32(TypeChecker.ListItemAlign_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setAlignListItem(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setListDirectionAttribute(value: Axis | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as Axis)
            thisSerializer.writeInt32(TypeChecker.Axis_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setListDirection(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setContentStartOffsetAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeNumber(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setContentStartOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setContentEndOffsetAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeNumber(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setContentEndOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDividerAttribute(value: ListDividerOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            ListDividerOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setDivider(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMultiSelectableAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setMultiSelectable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCachedCount0Attribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeNumber(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setCachedCount0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setChainAnimationAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setChainAnimation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setChainAnimationOptionsAttribute(value: ChainAnimationOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            ChainAnimationOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setChainAnimationOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStickyAttribute(value: StickyStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as StickyStyle)
            thisSerializer.writeInt32(TypeChecker.StickyStyle_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setSticky(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setScrollSnapAlignAttribute(value: ScrollSnapAlign | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as ScrollSnapAlign)
            thisSerializer.writeInt32(TypeChecker.ScrollSnapAlign_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setScrollSnapAlign(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setChildrenMainSizeAttribute(value: ChildrenMainSize | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            ChildrenMainSize_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setChildrenMainSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaintainVisibleContentPositionAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setMaintainVisibleContentPosition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStackFromEndAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setStackFromEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnScrollIndexAttribute(value: ((start: number,end: number,center: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setOnScrollIndex(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnScrollVisibleContentChangeAttribute(value: OnScrollVisibleContentChangeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setOnScrollVisibleContentChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnItemMoveAttribute(value: ((from: number,to: number) => boolean) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setOnItemMove(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnItemDragStartAttribute(value: OnItemDragStartCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setOnItemDragStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnItemDragEnterAttribute(value: ((event: ItemDragInfo) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setOnItemDragEnter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnItemDragMoveAttribute(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setOnItemDragMove(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnItemDragLeaveAttribute(value: ((event: ItemDragInfo,itemIndex: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setOnItemDragLeave(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnItemDropAttribute(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setOnItemDrop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnScrollFrameBeginAttribute(value: OnScrollFrameBeginCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setOnScrollFrameBegin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnWillScrollAttribute(value: OnWillScrollCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setOnWillScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnDidScrollAttribute(value: OnScrollCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setOnDidScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLanesAttribute(value: number | LengthConstrain | undefined, gutter?: Dimension): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof LengthConstrain) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as LengthConstrain
                LengthConstrain_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (gutter !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const gutterTmpValue  = gutter!
            if (gutterTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const gutterTmpValueForIdx0  = gutterTmpValue as string
                thisSerializer.writeString(gutterTmpValueForIdx0)
            } else if (gutterTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const gutterTmpValueForIdx1  = gutterTmpValue as number
                thisSerializer.writeNumber(gutterTmpValueForIdx1)
            } else if (gutterTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
                const gutterTmpValueForIdx2  = gutterTmpValue as Resource
                Resource_serializer.write(thisSerializer, gutterTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setLanes(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCachedCount1Attribute(count: number | undefined, show: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (count !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const countTmpValue  = count!
            thisSerializer.writeNumber(countTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (show !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const showTmpValue  = show!
            thisSerializer.writeBoolean(showTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
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
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

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
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ListModifier extends ScrollableCommonMethodModifier implements ListAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _alignListItem_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _alignListItem_0_0value?: ListItemAlign | undefined
    _listDirection_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _listDirection_0_0value?: Axis | undefined
    _contentStartOffset_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _contentStartOffset_0_0value?: number | undefined
    _contentEndOffset_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _contentEndOffset_0_0value?: number | undefined
    _divider_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _divider_0_0value?: ListDividerOptions | undefined
    _multiSelectable_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _multiSelectable_0_0value?: boolean | undefined
    _cachedCount_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _cachedCount_0_0value?: number | undefined
    _chainAnimation_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _chainAnimation_0_0value?: boolean | undefined
    _chainAnimationOptions_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _chainAnimationOptions_0_0value?: ChainAnimationOptions | undefined
    _sticky_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _sticky_0_0value?: StickyStyle | undefined
    _scrollSnapAlign_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _scrollSnapAlign_0_0value?: ScrollSnapAlign | undefined
    _childrenMainSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _childrenMainSize_0_0value?: ChildrenMainSize | undefined
    _maintainVisibleContentPosition_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maintainVisibleContentPosition_0_0value?: boolean | undefined
    _stackFromEnd_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _stackFromEnd_0_0value?: boolean | undefined
    _onScrollIndex_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onScrollIndex_0_0value?: ((start: number,end: number,center: number) => void) | undefined
    _onScrollVisibleContentChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onScrollVisibleContentChange_0_0value?: OnScrollVisibleContentChangeCallback | undefined
    _onItemMove_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onItemMove_0_0value?: ((from: number,to: number) => boolean) | undefined
    _onItemDragStart_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onItemDragStart_0_0value?: OnItemDragStartCallback | undefined
    _onItemDragEnter_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onItemDragEnter_0_0value?: ((event: ItemDragInfo) => void) | undefined
    _onItemDragMove_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onItemDragMove_0_0value?: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void) | undefined
    _onItemDragLeave_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onItemDragLeave_0_0value?: ((event: ItemDragInfo,itemIndex: number) => void) | undefined
    _onItemDrop_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onItemDrop_0_0value?: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void) | undefined
    _onScrollFrameBegin_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onScrollFrameBegin_0_0value?: OnScrollFrameBeginCallback | undefined
    _onWillScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWillScroll_0_0value?: OnWillScrollCallback | undefined
    _onDidScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDidScroll_0_0value?: OnScrollCallback | undefined
    _lanes_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _lanes_0_0value?: number | LengthConstrain | undefined
    _lanes_0_1value?: Dimension | undefined
    _cachedCount_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _cachedCount_1_0value?: number | undefined
    _cachedCount_1_1value?: boolean | undefined
    applyModifierPatch(peer: ArkListPeer): void {
        super.applyModifierPatch(peer)
        if (this._alignListItem_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._alignListItem_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAlignListItemAttribute((this._alignListItem_0_0value as ListItemAlign | undefined));
                    this._alignListItem_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._alignListItem_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._alignListItem_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAlignListItemAttribute((undefined as ListItemAlign | undefined));
                }
            }
        }
        if (this._listDirection_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._listDirection_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setListDirectionAttribute((this._listDirection_0_0value as Axis | undefined));
                    this._listDirection_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._listDirection_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._listDirection_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setListDirectionAttribute((undefined as Axis | undefined));
                }
            }
        }
        if (this._contentStartOffset_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._contentStartOffset_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setContentStartOffsetAttribute((this._contentStartOffset_0_0value as number | undefined));
                    this._contentStartOffset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._contentStartOffset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._contentStartOffset_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setContentStartOffsetAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._contentEndOffset_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._contentEndOffset_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setContentEndOffsetAttribute((this._contentEndOffset_0_0value as number | undefined));
                    this._contentEndOffset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._contentEndOffset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._contentEndOffset_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setContentEndOffsetAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._divider_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._divider_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDividerAttribute((this._divider_0_0value as ListDividerOptions | undefined));
                    this._divider_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._divider_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._divider_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDividerAttribute((undefined as ListDividerOptions | undefined));
                }
            }
        }
        if (this._multiSelectable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._multiSelectable_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMultiSelectableAttribute((this._multiSelectable_0_0value as boolean | undefined));
                    this._multiSelectable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._multiSelectable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._multiSelectable_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMultiSelectableAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._cachedCount_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._cachedCount_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCachedCount0Attribute((this._cachedCount_0_0value as number | undefined));
                    this._cachedCount_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._cachedCount_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._cachedCount_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCachedCount0Attribute((undefined as number | undefined));
                }
            }
        }
        if (this._chainAnimation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._chainAnimation_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setChainAnimationAttribute((this._chainAnimation_0_0value as boolean | undefined));
                    this._chainAnimation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._chainAnimation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._chainAnimation_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setChainAnimationAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._chainAnimationOptions_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._chainAnimationOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setChainAnimationOptionsAttribute((this._chainAnimationOptions_0_0value as ChainAnimationOptions | undefined));
                    this._chainAnimationOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._chainAnimationOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._chainAnimationOptions_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setChainAnimationOptionsAttribute((undefined as ChainAnimationOptions | undefined));
                }
            }
        }
        if (this._sticky_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._sticky_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStickyAttribute((this._sticky_0_0value as StickyStyle | undefined));
                    this._sticky_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._sticky_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._sticky_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStickyAttribute((undefined as StickyStyle | undefined));
                }
            }
        }
        if (this._scrollSnapAlign_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._scrollSnapAlign_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setScrollSnapAlignAttribute((this._scrollSnapAlign_0_0value as ScrollSnapAlign | undefined));
                    this._scrollSnapAlign_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._scrollSnapAlign_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._scrollSnapAlign_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setScrollSnapAlignAttribute((undefined as ScrollSnapAlign | undefined));
                }
            }
        }
        if (this._childrenMainSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._childrenMainSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setChildrenMainSizeAttribute((this._childrenMainSize_0_0value as ChildrenMainSize | undefined));
                    this._childrenMainSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._childrenMainSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._childrenMainSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setChildrenMainSizeAttribute((undefined as ChildrenMainSize | undefined));
                }
            }
        }
        if (this._maintainVisibleContentPosition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._maintainVisibleContentPosition_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMaintainVisibleContentPositionAttribute((this._maintainVisibleContentPosition_0_0value as boolean | undefined));
                    this._maintainVisibleContentPosition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maintainVisibleContentPosition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._maintainVisibleContentPosition_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMaintainVisibleContentPositionAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._stackFromEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._stackFromEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStackFromEndAttribute((this._stackFromEnd_0_0value as boolean | undefined));
                    this._stackFromEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._stackFromEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._stackFromEnd_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStackFromEndAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._onScrollIndex_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onScrollIndex_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnScrollIndexAttribute((this._onScrollIndex_0_0value as ((start: number,end: number,center: number) => void) | undefined));
                    this._onScrollIndex_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScrollIndex_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScrollIndex_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnScrollIndexAttribute((undefined as ((start: number,end: number,center: number) => void) | undefined));
                }
            }
        }
        if (this._onScrollVisibleContentChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onScrollVisibleContentChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnScrollVisibleContentChangeAttribute((this._onScrollVisibleContentChange_0_0value as OnScrollVisibleContentChangeCallback | undefined));
                    this._onScrollVisibleContentChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScrollVisibleContentChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScrollVisibleContentChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnScrollVisibleContentChangeAttribute((undefined as OnScrollVisibleContentChangeCallback | undefined));
                }
            }
        }
        if (this._onItemMove_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onItemMove_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnItemMoveAttribute((this._onItemMove_0_0value as ((from: number,to: number) => boolean) | undefined));
                    this._onItemMove_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onItemMove_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onItemMove_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnItemMoveAttribute((undefined as ((from: number,to: number) => boolean) | undefined));
                }
            }
        }
        if (this._onItemDragStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onItemDragStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnItemDragStartAttribute((this._onItemDragStart_0_0value as OnItemDragStartCallback | undefined));
                    this._onItemDragStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onItemDragStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onItemDragStart_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnItemDragStartAttribute((undefined as OnItemDragStartCallback | undefined));
                }
            }
        }
        if (this._onItemDragEnter_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onItemDragEnter_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnItemDragEnterAttribute((this._onItemDragEnter_0_0value as ((event: ItemDragInfo) => void) | undefined));
                    this._onItemDragEnter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onItemDragEnter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onItemDragEnter_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnItemDragEnterAttribute((undefined as ((event: ItemDragInfo) => void) | undefined));
                }
            }
        }
        if (this._onItemDragMove_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onItemDragMove_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnItemDragMoveAttribute((this._onItemDragMove_0_0value as ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void) | undefined));
                    this._onItemDragMove_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onItemDragMove_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onItemDragMove_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnItemDragMoveAttribute((undefined as ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void) | undefined));
                }
            }
        }
        if (this._onItemDragLeave_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onItemDragLeave_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnItemDragLeaveAttribute((this._onItemDragLeave_0_0value as ((event: ItemDragInfo,itemIndex: number) => void) | undefined));
                    this._onItemDragLeave_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onItemDragLeave_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onItemDragLeave_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnItemDragLeaveAttribute((undefined as ((event: ItemDragInfo,itemIndex: number) => void) | undefined));
                }
            }
        }
        if (this._onItemDrop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onItemDrop_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnItemDropAttribute((this._onItemDrop_0_0value as ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void) | undefined));
                    this._onItemDrop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onItemDrop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onItemDrop_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnItemDropAttribute((undefined as ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void) | undefined));
                }
            }
        }
        if (this._onScrollFrameBegin_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onScrollFrameBegin_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnScrollFrameBeginAttribute((this._onScrollFrameBegin_0_0value as OnScrollFrameBeginCallback | undefined));
                    this._onScrollFrameBegin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScrollFrameBegin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScrollFrameBegin_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnScrollFrameBeginAttribute((undefined as OnScrollFrameBeginCallback | undefined));
                }
            }
        }
        if (this._onWillScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onWillScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnWillScrollAttribute((this._onWillScroll_0_0value as OnWillScrollCallback | undefined));
                    this._onWillScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWillScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWillScroll_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnWillScrollAttribute((undefined as OnWillScrollCallback | undefined));
                }
            }
        }
        if (this._onDidScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDidScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDidScrollAttribute((this._onDidScroll_0_0value as OnScrollCallback | undefined));
                    this._onDidScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDidScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDidScroll_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDidScrollAttribute((undefined as OnScrollCallback | undefined));
                }
            }
        }
        if (this._lanes_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._lanes_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setLanesAttribute((this._lanes_0_0value as number | LengthConstrain | undefined), (this._lanes_0_1value as Dimension | undefined));
                    this._lanes_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._lanes_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._lanes_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setLanesAttribute((undefined as number | LengthConstrain | undefined), (undefined as Dimension | undefined | undefined));
                }
            }
        }
        if (this._cachedCount_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._cachedCount_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCachedCount1Attribute((this._cachedCount_1_0value as number | undefined), (this._cachedCount_1_1value as boolean | undefined));
                    this._cachedCount_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._cachedCount_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._cachedCount_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCachedCount1Attribute((undefined as number | undefined), (undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: ListModifier): void {
        super.mergeModifier(modifier)
        if (modifier._alignListItem_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._alignListItem_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.alignListItem(modifier._alignListItem_0_0value);
                    break;
                }
                default: {
                    this.alignListItem((undefined as ListItemAlign | undefined));
                }
            }
        }
        if (modifier._listDirection_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._listDirection_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.listDirection(modifier._listDirection_0_0value);
                    break;
                }
                default: {
                    this.listDirection((undefined as Axis | undefined));
                }
            }
        }
        if (modifier._contentStartOffset_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._contentStartOffset_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.contentStartOffset(modifier._contentStartOffset_0_0value);
                    break;
                }
                default: {
                    this.contentStartOffset((undefined as number | undefined));
                }
            }
        }
        if (modifier._contentEndOffset_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._contentEndOffset_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.contentEndOffset(modifier._contentEndOffset_0_0value);
                    break;
                }
                default: {
                    this.contentEndOffset((undefined as number | undefined));
                }
            }
        }
        if (modifier._divider_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._divider_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.divider(modifier._divider_0_0value);
                    break;
                }
                default: {
                    this.divider((undefined as ListDividerOptions | undefined));
                }
            }
        }
        if (modifier._multiSelectable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._multiSelectable_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.multiSelectable(modifier._multiSelectable_0_0value);
                    break;
                }
                default: {
                    this.multiSelectable((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._cachedCount_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._cachedCount_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.cachedCount(modifier._cachedCount_0_0value);
                    break;
                }
                default: {
                    this.cachedCount((undefined as number | undefined));
                }
            }
        }
        if (modifier._chainAnimation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._chainAnimation_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.chainAnimation(modifier._chainAnimation_0_0value);
                    break;
                }
                default: {
                    this.chainAnimation((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._chainAnimationOptions_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._chainAnimationOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.chainAnimationOptions(modifier._chainAnimationOptions_0_0value);
                    break;
                }
                default: {
                    this.chainAnimationOptions((undefined as ChainAnimationOptions | undefined));
                }
            }
        }
        if (modifier._sticky_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._sticky_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.sticky(modifier._sticky_0_0value);
                    break;
                }
                default: {
                    this.sticky((undefined as StickyStyle | undefined));
                }
            }
        }
        if (modifier._scrollSnapAlign_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._scrollSnapAlign_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.scrollSnapAlign(modifier._scrollSnapAlign_0_0value);
                    break;
                }
                default: {
                    this.scrollSnapAlign((undefined as ScrollSnapAlign | undefined));
                }
            }
        }
        if (modifier._childrenMainSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._childrenMainSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.childrenMainSize(modifier._childrenMainSize_0_0value);
                    break;
                }
                default: {
                    this.childrenMainSize((undefined as ChildrenMainSize | undefined));
                }
            }
        }
        if (modifier._maintainVisibleContentPosition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._maintainVisibleContentPosition_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.maintainVisibleContentPosition(modifier._maintainVisibleContentPosition_0_0value);
                    break;
                }
                default: {
                    this.maintainVisibleContentPosition((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._stackFromEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._stackFromEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.stackFromEnd(modifier._stackFromEnd_0_0value);
                    break;
                }
                default: {
                    this.stackFromEnd((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._onScrollIndex_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onScrollIndex_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onScrollIndex(modifier._onScrollIndex_0_0value);
                    break;
                }
                default: {
                    this.onScrollIndex((undefined as ((start: number,end: number,center: number) => void) | undefined));
                }
            }
        }
        if (modifier._onScrollVisibleContentChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onScrollVisibleContentChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onScrollVisibleContentChange(modifier._onScrollVisibleContentChange_0_0value);
                    break;
                }
                default: {
                    this.onScrollVisibleContentChange((undefined as OnScrollVisibleContentChangeCallback | undefined));
                }
            }
        }
        if (modifier._onItemMove_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onItemMove_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onItemMove(modifier._onItemMove_0_0value);
                    break;
                }
                default: {
                    this.onItemMove((undefined as ((from: number,to: number) => boolean) | undefined));
                }
            }
        }
        if (modifier._onItemDragStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onItemDragStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onItemDragStart(modifier._onItemDragStart_0_0value);
                    break;
                }
                default: {
                    this.onItemDragStart((undefined as OnItemDragStartCallback | undefined));
                }
            }
        }
        if (modifier._onItemDragEnter_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onItemDragEnter_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onItemDragEnter(modifier._onItemDragEnter_0_0value);
                    break;
                }
                default: {
                    this.onItemDragEnter((undefined as ((event: ItemDragInfo) => void) | undefined));
                }
            }
        }
        if (modifier._onItemDragMove_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onItemDragMove_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onItemDragMove(modifier._onItemDragMove_0_0value);
                    break;
                }
                default: {
                    this.onItemDragMove((undefined as ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void) | undefined));
                }
            }
        }
        if (modifier._onItemDragLeave_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onItemDragLeave_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onItemDragLeave(modifier._onItemDragLeave_0_0value);
                    break;
                }
                default: {
                    this.onItemDragLeave((undefined as ((event: ItemDragInfo,itemIndex: number) => void) | undefined));
                }
            }
        }
        if (modifier._onItemDrop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onItemDrop_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onItemDrop(modifier._onItemDrop_0_0value);
                    break;
                }
                default: {
                    this.onItemDrop((undefined as ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void) | undefined));
                }
            }
        }
        if (modifier._onScrollFrameBegin_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onScrollFrameBegin_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onScrollFrameBegin(modifier._onScrollFrameBegin_0_0value);
                    break;
                }
                default: {
                    this.onScrollFrameBegin((undefined as OnScrollFrameBeginCallback | undefined));
                }
            }
        }
        if (modifier._onWillScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onWillScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onWillScroll(modifier._onWillScroll_0_0value);
                    break;
                }
                default: {
                    this.onWillScroll((undefined as OnWillScrollCallback | undefined));
                }
            }
        }
        if (modifier._onDidScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDidScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDidScroll(modifier._onDidScroll_0_0value);
                    break;
                }
                default: {
                    this.onDidScroll((undefined as OnScrollCallback | undefined));
                }
            }
        }
        if (modifier._lanes_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._lanes_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.lanes(modifier._lanes_0_0value, modifier._lanes_0_1value);
                    break;
                }
                default: {
                    this.lanes((undefined as number | LengthConstrain | undefined), (undefined as Dimension | undefined | undefined));
                }
            }
        }
        if (modifier._cachedCount_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._cachedCount_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.cachedCount(modifier._cachedCount_1_0value, modifier._cachedCount_1_1value);
                    break;
                }
                default: {
                    this.cachedCount((undefined as number | undefined), (undefined as boolean | undefined));
                }
            }
        }
    }
    alignListItem(value: ListItemAlign | undefined): this {
        if (((this._alignListItem_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._alignListItem_0_flag = AttributeUpdaterFlag.UPDATE
            this._alignListItem_0_0value = value
        } else
        {
            this._alignListItem_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    listDirection(value: Axis | undefined): this {
        if (((this._listDirection_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._listDirection_0_flag = AttributeUpdaterFlag.UPDATE
            this._listDirection_0_0value = value
        } else
        {
            this._listDirection_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    contentStartOffset(value: number | undefined): this {
        if (((this._contentStartOffset_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._contentStartOffset_0_0value) !== (value)))
        {
            this._contentStartOffset_0_flag = AttributeUpdaterFlag.UPDATE
            this._contentStartOffset_0_0value = value
        } else
        {
            this._contentStartOffset_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    contentEndOffset(value: number | undefined): this {
        if (((this._contentEndOffset_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._contentEndOffset_0_0value) !== (value)))
        {
            this._contentEndOffset_0_flag = AttributeUpdaterFlag.UPDATE
            this._contentEndOffset_0_0value = value
        } else
        {
            this._contentEndOffset_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    divider(value: ListDividerOptions | undefined): this {
        if (((this._divider_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._divider_0_flag = AttributeUpdaterFlag.UPDATE
            this._divider_0_0value = value
        } else
        {
            this._divider_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    multiSelectable(value: boolean | undefined): this {
        if (((this._multiSelectable_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._multiSelectable_0_0value) !== (value)))
        {
            this._multiSelectable_0_flag = AttributeUpdaterFlag.UPDATE
            this._multiSelectable_0_0value = value
        } else
        {
            this._multiSelectable_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    cachedCount(value: number | undefined): this {
        if (((this._cachedCount_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._cachedCount_0_0value) !== (value)))
        {
            this._cachedCount_0_flag = AttributeUpdaterFlag.UPDATE
            this._cachedCount_0_0value = value
        } else
        {
            this._cachedCount_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    chainAnimation(value: boolean | undefined): this {
        if (((this._chainAnimation_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._chainAnimation_0_0value) !== (value)))
        {
            this._chainAnimation_0_flag = AttributeUpdaterFlag.UPDATE
            this._chainAnimation_0_0value = value
        } else
        {
            this._chainAnimation_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    chainAnimationOptions(value: ChainAnimationOptions | undefined): this {
        if (((this._chainAnimationOptions_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._chainAnimationOptions_0_flag = AttributeUpdaterFlag.UPDATE
            this._chainAnimationOptions_0_0value = value
        } else
        {
            this._chainAnimationOptions_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    sticky(value: StickyStyle | undefined): this {
        if (((this._sticky_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._sticky_0_flag = AttributeUpdaterFlag.UPDATE
            this._sticky_0_0value = value
        } else
        {
            this._sticky_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    scrollSnapAlign(value: ScrollSnapAlign | undefined): this {
        if (((this._scrollSnapAlign_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._scrollSnapAlign_0_flag = AttributeUpdaterFlag.UPDATE
            this._scrollSnapAlign_0_0value = value
        } else
        {
            this._scrollSnapAlign_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    childrenMainSize(value: ChildrenMainSize | undefined): this {
        if (((this._childrenMainSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._childrenMainSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._childrenMainSize_0_0value = value
        } else
        {
            this._childrenMainSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    maintainVisibleContentPosition(value: boolean | undefined): this {
        if (((this._maintainVisibleContentPosition_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._maintainVisibleContentPosition_0_0value) !== (value)))
        {
            this._maintainVisibleContentPosition_0_flag = AttributeUpdaterFlag.UPDATE
            this._maintainVisibleContentPosition_0_0value = value
        } else
        {
            this._maintainVisibleContentPosition_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    stackFromEnd(value: boolean | undefined): this {
        if (((this._stackFromEnd_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._stackFromEnd_0_0value) !== (value)))
        {
            this._stackFromEnd_0_flag = AttributeUpdaterFlag.UPDATE
            this._stackFromEnd_0_0value = value
        } else
        {
            this._stackFromEnd_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onScrollIndex(value: ((start: number,end: number,center: number) => void) | undefined): this {
        if (((this._onScrollIndex_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onScrollIndex_0_flag = AttributeUpdaterFlag.UPDATE
            this._onScrollIndex_0_0value = value
        } else
        {
            this._onScrollIndex_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onScrollVisibleContentChange(value: OnScrollVisibleContentChangeCallback | undefined): this {
        if (((this._onScrollVisibleContentChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onScrollVisibleContentChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onScrollVisibleContentChange_0_0value = value
        } else
        {
            this._onScrollVisibleContentChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onItemMove(value: ((from: number,to: number) => boolean) | undefined): this {
        if (((this._onItemMove_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onItemMove_0_flag = AttributeUpdaterFlag.UPDATE
            this._onItemMove_0_0value = value
        } else
        {
            this._onItemMove_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onItemDragStart(value: OnItemDragStartCallback | undefined): this {
        if (((this._onItemDragStart_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onItemDragStart_0_flag = AttributeUpdaterFlag.UPDATE
            this._onItemDragStart_0_0value = value
        } else
        {
            this._onItemDragStart_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onItemDragEnter(value: ((event: ItemDragInfo) => void) | undefined): this {
        if (((this._onItemDragEnter_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onItemDragEnter_0_flag = AttributeUpdaterFlag.UPDATE
            this._onItemDragEnter_0_0value = value
        } else
        {
            this._onItemDragEnter_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onItemDragMove(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void) | undefined): this {
        if (((this._onItemDragMove_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onItemDragMove_0_flag = AttributeUpdaterFlag.UPDATE
            this._onItemDragMove_0_0value = value
        } else
        {
            this._onItemDragMove_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onItemDragLeave(value: ((event: ItemDragInfo,itemIndex: number) => void) | undefined): this {
        if (((this._onItemDragLeave_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onItemDragLeave_0_flag = AttributeUpdaterFlag.UPDATE
            this._onItemDragLeave_0_0value = value
        } else
        {
            this._onItemDragLeave_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onItemDrop(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void) | undefined): this {
        if (((this._onItemDrop_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onItemDrop_0_flag = AttributeUpdaterFlag.UPDATE
            this._onItemDrop_0_0value = value
        } else
        {
            this._onItemDrop_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        if (((this._onScrollFrameBegin_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onScrollFrameBegin_0_flag = AttributeUpdaterFlag.UPDATE
            this._onScrollFrameBegin_0_0value = value
        } else
        {
            this._onScrollFrameBegin_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onWillScroll(value: OnWillScrollCallback | undefined): this {
        if (((this._onWillScroll_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onWillScroll_0_flag = AttributeUpdaterFlag.UPDATE
            this._onWillScroll_0_0value = value
        } else
        {
            this._onWillScroll_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDidScroll(value: OnScrollCallback | undefined): this {
        if (((this._onDidScroll_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDidScroll_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDidScroll_0_0value = value
        } else
        {
            this._onDidScroll_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    lanes(value: number | LengthConstrain | undefined, gutter?: Dimension): this {
        if (((this._lanes_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._lanes_0_flag = AttributeUpdaterFlag.UPDATE
            this._lanes_0_0value = value
            this._lanes_0_1value = gutter
        } else
        {
            this._lanes_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    cachedCount(count: number | undefined, show: boolean | undefined): this {
        if (((this._cachedCount_1_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._cachedCount_1_0value) !== (count)) || ((this._cachedCount_1_1value) !== (show)))
        {
            this._cachedCount_1_flag = AttributeUpdaterFlag.UPDATE
            this._cachedCount_1_0value = count
            this._cachedCount_1_1value = show
        } else
        {
            this._cachedCount_1_flag = AttributeUpdaterFlag.SKIP
        }
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
        const valueHolderForOnFinish  = value.onFinish
        if (valueHolderForOnFinish !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnFinishTmpValue  = valueHolderForOnFinish!
            valueSerializer.holdAndWriteCallback(valueHolderForOnFinishTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): CloseSwipeActionOptions {
        let valueDeserializer : DeserializerBase = buffer
        const onFinishTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onFinishTmpBuf : (() => void) | undefined
        if ((onFinishTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onFinishTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onFinishTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onFinishTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onFinishTmpBuf = ():void => {
                const onFinishTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onFinishTmpBuf_BufArgsSerializer.writeInt32(onFinishTmpBuf_BufResource.resourceId);
                onFinishTmpBuf_BufArgsSerializer.writePointer(onFinishTmpBuf_BufCall);
                onFinishTmpBuf_BufArgsSerializer.writePointer(onFinishTmpBuf_BufCallSync);
                InteropNativeModule._CallCallback(-1867723152, onFinishTmpBuf_BufArgsSerializer.asBuffer(), onFinishTmpBuf_BufArgsSerializer.length());
                onFinishTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onFinishTmpResult : (() => void) | undefined = onFinishTmpBuf
        let value : CloseSwipeActionOptions = ({onFinish: onFinishTmpResult} as CloseSwipeActionOptions)
        return value
    }
}
export class ListOptions_serializer {
    public static write(buffer: SerializerBase, value: ListOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForInitialIndex  = value.initialIndex
        if (valueHolderForInitialIndex !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForInitialIndexTmpValue  = valueHolderForInitialIndex!
            valueSerializer.writeNumber(valueHolderForInitialIndexTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSpace  = value.space
        if (valueHolderForSpace !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSpaceTmpValue  = valueHolderForSpace!
            if (valueHolderForSpaceTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForSpaceTmpValueForIdx0  = valueHolderForSpaceTmpValue as number
                valueSerializer.writeNumber(valueHolderForSpaceTmpValueForIdx0)
            } else if (valueHolderForSpaceTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForSpaceTmpValueForIdx1  = valueHolderForSpaceTmpValue as string
                valueSerializer.writeString(valueHolderForSpaceTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForScroller  = value.scroller
        if (valueHolderForScroller !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForScrollerTmpValue  = valueHolderForScroller!
            Scroller_serializer.write(valueSerializer, valueHolderForScrollerTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ListOptions {
        let valueDeserializer : DeserializerBase = buffer
        const initialIndexTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let initialIndexTmpBuf : number | undefined
        if ((initialIndexTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            initialIndexTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const initialIndexTmpResult : number | undefined = initialIndexTmpBuf
        const spaceTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let spaceTmpBuf : number | string | undefined
        if ((spaceTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const spaceTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let spaceTmpBuf_ : number | string | undefined
            if (spaceTmpBuf_UnionSelector == (0).toChar()) {
                spaceTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (spaceTmpBuf_UnionSelector == (1).toChar()) {
                spaceTmpBuf_ = (valueDeserializer.readString() as string)
            } else {
                throw new Error("One of the branches for spaceTmpBuf_ has to be chosen through deserialisation.")
            }
            spaceTmpBuf = (spaceTmpBuf_ as number | string)
        }
        const spaceTmpResult : number | string | undefined = spaceTmpBuf
        const scrollerTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let scrollerTmpBuf : Scroller | undefined
        if ((scrollerTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            scrollerTmpBuf = (Scroller_serializer.read(valueDeserializer) as Scroller)
        }
        const scrollerTmpResult : Scroller | undefined = scrollerTmpBuf
        let value : ListOptions = ({initialIndex: initialIndexTmpResult, space: spaceTmpResult, scroller: scrollerTmpResult} as ListOptions)
        return value
    }
}
export class VisibleListContentInfo_serializer {
    public static write(buffer: SerializerBase, value: VisibleListContentInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForIndex  = value.index
        valueSerializer.writeNumber(valueHolderForIndex)
        const valueHolderForItemGroupArea  = value.itemGroupArea
        if (valueHolderForItemGroupArea !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForItemGroupAreaTmpValue  = (valueHolderForItemGroupArea as ListItemGroupArea)
            valueSerializer.writeInt32(TypeChecker.ListItemGroupArea_ToNumeric(valueHolderForItemGroupAreaTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForItemIndexInGroup  = value.itemIndexInGroup
        if (valueHolderForItemIndexInGroup !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForItemIndexInGroupTmpValue  = valueHolderForItemIndexInGroup!
            valueSerializer.writeNumber(valueHolderForItemIndexInGroupTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): VisibleListContentInfo {
        let valueDeserializer : DeserializerBase = buffer
        const indexTmpResult : number = (valueDeserializer.readNumber() as number)
        const itemGroupAreaTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let itemGroupAreaTmpBuf : ListItemGroupArea | undefined
        if ((itemGroupAreaTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            itemGroupAreaTmpBuf = TypeChecker.ListItemGroupArea_FromNumeric(valueDeserializer.readInt32())
        }
        const itemGroupAreaTmpResult : ListItemGroupArea | undefined = itemGroupAreaTmpBuf
        const itemIndexInGroupTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let itemIndexInGroupTmpBuf : number | undefined
        if ((itemIndexInGroupTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            itemIndexInGroupTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const itemIndexInGroupTmpResult : number | undefined = itemIndexInGroupTmpBuf
        let value : VisibleListContentInfo = ({index: indexTmpResult, itemGroupArea: itemGroupAreaTmpResult, itemIndexInGroup: itemIndexInGroupTmpResult} as VisibleListContentInfo)
        return value
    }
}
export class ChainAnimationOptions_serializer {
    public static write(buffer: SerializerBase, value: ChainAnimationOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForMinSpace  = value.minSpace
        if (valueHolderForMinSpace instanceof string) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForMinSpaceForIdx0  = valueHolderForMinSpace as string
            valueSerializer.writeString(valueHolderForMinSpaceForIdx0)
        } else if (valueHolderForMinSpace instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForMinSpaceForIdx1  = valueHolderForMinSpace as number
            valueSerializer.writeNumber(valueHolderForMinSpaceForIdx1)
        } else if (valueHolderForMinSpace instanceof Resource) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForMinSpaceForIdx2  = valueHolderForMinSpace as Resource
            Resource_serializer.write(valueSerializer, valueHolderForMinSpaceForIdx2)
        }
        const valueHolderForMaxSpace  = value.maxSpace
        if (valueHolderForMaxSpace instanceof string) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForMaxSpaceForIdx0  = valueHolderForMaxSpace as string
            valueSerializer.writeString(valueHolderForMaxSpaceForIdx0)
        } else if (valueHolderForMaxSpace instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForMaxSpaceForIdx1  = valueHolderForMaxSpace as number
            valueSerializer.writeNumber(valueHolderForMaxSpaceForIdx1)
        } else if (valueHolderForMaxSpace instanceof Resource) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForMaxSpaceForIdx2  = valueHolderForMaxSpace as Resource
            Resource_serializer.write(valueSerializer, valueHolderForMaxSpaceForIdx2)
        }
        const valueHolderForConductivity  = value.conductivity
        if (valueHolderForConductivity !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForConductivityTmpValue  = valueHolderForConductivity!
            valueSerializer.writeNumber(valueHolderForConductivityTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForIntensity  = value.intensity
        if (valueHolderForIntensity !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIntensityTmpValue  = valueHolderForIntensity!
            valueSerializer.writeNumber(valueHolderForIntensityTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEdgeEffect  = value.edgeEffect
        if (valueHolderForEdgeEffect !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEdgeEffectTmpValue  = (valueHolderForEdgeEffect as ChainEdgeEffect)
            valueSerializer.writeInt32(TypeChecker.ChainEdgeEffect_ToNumeric(valueHolderForEdgeEffectTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStiffness  = value.stiffness
        if (valueHolderForStiffness !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStiffnessTmpValue  = valueHolderForStiffness!
            valueSerializer.writeNumber(valueHolderForStiffnessTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDamping  = value.damping
        if (valueHolderForDamping !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDampingTmpValue  = valueHolderForDamping!
            valueSerializer.writeNumber(valueHolderForDampingTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ChainAnimationOptions {
        let valueDeserializer : DeserializerBase = buffer
        const minSpaceTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let minSpaceTmpBuf : string | number | Resource | undefined
        if (minSpaceTmpBufUnionSelector == (0).toChar()) {
            minSpaceTmpBuf = (valueDeserializer.readString() as string)
        } else if (minSpaceTmpBufUnionSelector == (1).toChar()) {
            minSpaceTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (minSpaceTmpBufUnionSelector == (2).toChar()) {
            minSpaceTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for minSpaceTmpBuf has to be chosen through deserialisation.")
        }
        const minSpaceTmpResult : Length = (minSpaceTmpBuf as string | number | Resource)
        const maxSpaceTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let maxSpaceTmpBuf : string | number | Resource | undefined
        if (maxSpaceTmpBufUnionSelector == (0).toChar()) {
            maxSpaceTmpBuf = (valueDeserializer.readString() as string)
        } else if (maxSpaceTmpBufUnionSelector == (1).toChar()) {
            maxSpaceTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (maxSpaceTmpBufUnionSelector == (2).toChar()) {
            maxSpaceTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for maxSpaceTmpBuf has to be chosen through deserialisation.")
        }
        const maxSpaceTmpResult : Length = (maxSpaceTmpBuf as string | number | Resource)
        const conductivityTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let conductivityTmpBuf : number | undefined
        if ((conductivityTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            conductivityTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const conductivityTmpResult : number | undefined = conductivityTmpBuf
        const intensityTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let intensityTmpBuf : number | undefined
        if ((intensityTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            intensityTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const intensityTmpResult : number | undefined = intensityTmpBuf
        const edgeEffectTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let edgeEffectTmpBuf : ChainEdgeEffect | undefined
        if ((edgeEffectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            edgeEffectTmpBuf = TypeChecker.ChainEdgeEffect_FromNumeric(valueDeserializer.readInt32())
        }
        const edgeEffectTmpResult : ChainEdgeEffect | undefined = edgeEffectTmpBuf
        const stiffnessTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let stiffnessTmpBuf : number | undefined
        if ((stiffnessTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            stiffnessTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const stiffnessTmpResult : number | undefined = stiffnessTmpBuf
        const dampingTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let dampingTmpBuf : number | undefined
        if ((dampingTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            dampingTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const dampingTmpResult : number | undefined = dampingTmpBuf
        let value : ChainAnimationOptions = ({minSpace: minSpaceTmpResult, maxSpace: maxSpaceTmpResult, conductivity: conductivityTmpResult, intensity: intensityTmpResult, edgeEffect: edgeEffectTmpResult, stiffness: stiffnessTmpResult, damping: dampingTmpResult} as ChainAnimationOptions)
        return value
    }
}
export class ListDividerOptions_serializer {
    public static write(buffer: SerializerBase, value: ListDividerOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStrokeWidth  = value.strokeWidth
        if (valueHolderForStrokeWidth instanceof string) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForStrokeWidthForIdx0  = valueHolderForStrokeWidth as string
            valueSerializer.writeString(valueHolderForStrokeWidthForIdx0)
        } else if (valueHolderForStrokeWidth instanceof number) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForStrokeWidthForIdx1  = valueHolderForStrokeWidth as number
            valueSerializer.writeNumber(valueHolderForStrokeWidthForIdx1)
        } else if (valueHolderForStrokeWidth instanceof Resource) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForStrokeWidthForIdx2  = valueHolderForStrokeWidth as Resource
            Resource_serializer.write(valueSerializer, valueHolderForStrokeWidthForIdx2)
        }
        const valueHolderForColor  = value.color
        if (valueHolderForColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColorTmpValue  = valueHolderForColor!
            if (valueHolderForColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForColorTmpValueForIdx0  = valueHolderForColorTmpValue as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForColorTmpValueForIdx0))
            } else if (valueHolderForColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForColorTmpValueForIdx1  = valueHolderForColorTmpValue as number
                valueSerializer.writeNumber(valueHolderForColorTmpValueForIdx1)
            } else if (valueHolderForColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForColorTmpValueForIdx2  = valueHolderForColorTmpValue as string
                valueSerializer.writeString(valueHolderForColorTmpValueForIdx2)
            } else if (valueHolderForColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toChar())
                const valueHolderForColorTmpValueForIdx3  = valueHolderForColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStartMargin  = value.startMargin
        if (valueHolderForStartMargin !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStartMarginTmpValue  = valueHolderForStartMargin!
            if (valueHolderForStartMarginTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForStartMarginTmpValueForIdx0  = valueHolderForStartMarginTmpValue as string
                valueSerializer.writeString(valueHolderForStartMarginTmpValueForIdx0)
            } else if (valueHolderForStartMarginTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForStartMarginTmpValueForIdx1  = valueHolderForStartMarginTmpValue as number
                valueSerializer.writeNumber(valueHolderForStartMarginTmpValueForIdx1)
            } else if (valueHolderForStartMarginTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForStartMarginTmpValueForIdx2  = valueHolderForStartMarginTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForStartMarginTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEndMargin  = value.endMargin
        if (valueHolderForEndMargin !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEndMarginTmpValue  = valueHolderForEndMargin!
            if (valueHolderForEndMarginTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForEndMarginTmpValueForIdx0  = valueHolderForEndMarginTmpValue as string
                valueSerializer.writeString(valueHolderForEndMarginTmpValueForIdx0)
            } else if (valueHolderForEndMarginTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForEndMarginTmpValueForIdx1  = valueHolderForEndMarginTmpValue as number
                valueSerializer.writeNumber(valueHolderForEndMarginTmpValueForIdx1)
            } else if (valueHolderForEndMarginTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForEndMarginTmpValueForIdx2  = valueHolderForEndMarginTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForEndMarginTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ListDividerOptions {
        let valueDeserializer : DeserializerBase = buffer
        const strokeWidthTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let strokeWidthTmpBuf : string | number | Resource | undefined
        if (strokeWidthTmpBufUnionSelector == (0).toChar()) {
            strokeWidthTmpBuf = (valueDeserializer.readString() as string)
        } else if (strokeWidthTmpBufUnionSelector == (1).toChar()) {
            strokeWidthTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (strokeWidthTmpBufUnionSelector == (2).toChar()) {
            strokeWidthTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for strokeWidthTmpBuf has to be chosen through deserialisation.")
        }
        const strokeWidthTmpResult : Length = (strokeWidthTmpBuf as string | number | Resource)
        const colorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let colorTmpBuf : ResourceColor | undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const colorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let colorTmpBuf_ : Color | number | string | Resource | undefined
            if (colorTmpBuf_UnionSelector == (0).toChar()) {
                colorTmpBuf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            } else if (colorTmpBuf_UnionSelector == (1).toChar()) {
                colorTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (colorTmpBuf_UnionSelector == (2).toChar()) {
                colorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (colorTmpBuf_UnionSelector == (3).toChar()) {
                colorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for colorTmpBuf_ has to be chosen through deserialisation.")
            }
            colorTmpBuf = (colorTmpBuf_ as Color | number | string | Resource)
        }
        const colorTmpResult : ResourceColor | undefined = colorTmpBuf
        const startMarginTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let startMarginTmpBuf : Length | undefined
        if ((startMarginTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const startMarginTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let startMarginTmpBuf_ : string | number | Resource | undefined
            if (startMarginTmpBuf_UnionSelector == (0).toChar()) {
                startMarginTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (startMarginTmpBuf_UnionSelector == (1).toChar()) {
                startMarginTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (startMarginTmpBuf_UnionSelector == (2).toChar()) {
                startMarginTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for startMarginTmpBuf_ has to be chosen through deserialisation.")
            }
            startMarginTmpBuf = (startMarginTmpBuf_ as string | number | Resource)
        }
        const startMarginTmpResult : Length | undefined = startMarginTmpBuf
        const endMarginTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let endMarginTmpBuf : Length | undefined
        if ((endMarginTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const endMarginTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let endMarginTmpBuf_ : string | number | Resource | undefined
            if (endMarginTmpBuf_UnionSelector == (0).toChar()) {
                endMarginTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (endMarginTmpBuf_UnionSelector == (1).toChar()) {
                endMarginTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (endMarginTmpBuf_UnionSelector == (2).toChar()) {
                endMarginTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for endMarginTmpBuf_ has to be chosen through deserialisation.")
            }
            endMarginTmpBuf = (endMarginTmpBuf_ as string | number | Resource)
        }
        const endMarginTmpResult : Length | undefined = endMarginTmpBuf
        let value : ListDividerOptions = ({strokeWidth: strokeWidthTmpResult, color: colorTmpResult, startMargin: startMarginTmpResult, endMargin: endMarginTmpResult} as ListDividerOptions)
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
        if (smooth !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const smoothTmpValue  = smooth!
            thisSerializer.writeBoolean(smoothTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (align !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const alignTmpValue  = (align as ScrollAlign)
            thisSerializer.writeInt32(TypeChecker.ScrollAlign_ToNumeric(alignTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListScroller_scrollToItemInGroup(this.peer!.ptr, index, indexInGroup, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private closeAllSwipeActions_serialize(options?: CloseSwipeActionOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            CloseSwipeActionOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
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

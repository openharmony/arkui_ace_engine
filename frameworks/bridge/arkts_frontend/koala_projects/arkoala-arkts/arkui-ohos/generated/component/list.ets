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
import { ChildrenMainSize_serializer, ArkScrollableCommonMethodPeer, ScrollableCommonMethod, ChildrenMainSize, OnItemDragStartCallback, ItemDragInfo, OnWillScrollCallback, OnScrollCallback, CommonMethod, ArkScrollableCommonMethodComponent, ArkScrollableCommonMethodStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, RectResult_serializer, RectResult } from "./common"
import { LengthConstrain_serializer, LengthConstrain, Dimension, Length, ResourceColor } from "./units"
import { Resource_serializer } from "./../framework/resource"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { Axis, ScrollSource, Color } from "./enums"
import { OnScrollFrameBeginCallback, Scroller, Scroller_serializer, ScrollerInternal, ScrollAlign } from "./scroll"
import { AttributeModifier, hookListAttributeModifier, AttributeUpdater, hookListChildrenMainSizeImpl } from "#handwritten"
import { Resource } from "global.resource"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { ListModifier } from "./../ListModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkListPeer extends ArkScrollableCommonMethodPeer {
    attributeSet?: ListModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setListDirection(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setContentStartOffsetAttribute(value: double | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeFloat64(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setContentStartOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setContentEndOffsetAttribute(value: double | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeFloat64(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListAttribute_setContentEndOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDividerAttribute(value: ListDividerOptions | null | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined && value !== null) {
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
    setCachedCount0Attribute(value: int32 | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeInt32(valueTmpValue)
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
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
    setOnScrollIndexAttribute(value: ((start: int32,end: int32,center: int32) => void) | undefined): void {
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
    setOnItemMoveAttribute(value: ((from: int32,to: int32) => boolean) | undefined): void {
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
    setOnItemDragMoveAttribute(value: ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32) => void) | undefined): void {
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
    setOnItemDragLeaveAttribute(value: ((event: ItemDragInfo,itemIndex: int32) => void) | undefined): void {
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
    setOnItemDropAttribute(value: ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32,isSuccess: boolean) => void) | undefined): void {
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
    setLanesAttribute(value: int32 | LengthConstrain | undefined, gutter?: Dimension): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx0)
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
    setCachedCount1Attribute(count: int32 | undefined, show: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (count !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const countTmpValue  = count!
            thisSerializer.writeInt32(countTmpValue)
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
    Footer = 2,
    BOTH = 3
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
    conductivity?: double;
    intensity?: double;
    edgeEffect?: ChainEdgeEffect;
    stiffness?: double;
    damping?: double;
}
export interface CloseSwipeActionOptions {
    onFinish?: (() => void);
}
export interface VisibleListContentInfo {
    index: int32;
    itemGroupArea?: ListItemGroupArea;
    itemIndexInGroup?: int32;
}
export type OnScrollVisibleContentChangeCallback = (start: VisibleListContentInfo, end: VisibleListContentInfo) => void;
export interface ListOptions {
    initialIndex?: int32;
    space?: double | string;
    scroller?: Scroller;
}
export interface ListDividerOptions {
    strokeWidth: Length;
    color?: ResourceColor;
    startMargin?: Length;
    endMargin?: Length;
}
export interface ListAttribute extends ScrollableCommonMethod {
    setListOptions(options?: ListOptions): this {
        throw new Error("Unimplemented method setListOptions")
    }
    alignListItem(value: ListItemAlign | undefined): this {
        throw new Error("Unimplemented method alignListItem")
    }
    listDirection(value: Axis | undefined): this {
        throw new Error("Unimplemented method listDirection")
    }
    contentStartOffset(value: double | undefined): this {
        throw new Error("Unimplemented method contentStartOffset")
    }
    contentEndOffset(value: double | undefined): this {
        throw new Error("Unimplemented method contentEndOffset")
    }
    divider(value: ListDividerOptions | null | undefined): this {
        throw new Error("Unimplemented method divider")
    }
    multiSelectable(value: boolean | undefined): this {
        throw new Error("Unimplemented method multiSelectable")
    }
    cachedCount(value: int32 | undefined): this {
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
    onScrollIndex(value: ((start: int32,end: int32,center: int32) => void) | undefined): this {
        throw new Error("Unimplemented method onScrollIndex")
    }
    onScrollVisibleContentChange(value: OnScrollVisibleContentChangeCallback | undefined): this {
        throw new Error("Unimplemented method onScrollVisibleContentChange")
    }
    onItemMove(value: ((from: int32,to: int32) => boolean) | undefined): this {
        throw new Error("Unimplemented method onItemMove")
    }
    onItemDragStart(value: OnItemDragStartCallback | undefined): this {
        throw new Error("Unimplemented method onItemDragStart")
    }
    onItemDragEnter(value: ((event: ItemDragInfo) => void) | undefined): this {
        throw new Error("Unimplemented method onItemDragEnter")
    }
    onItemDragMove(value: ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32) => void) | undefined): this {
        throw new Error("Unimplemented method onItemDragMove")
    }
    onItemDragLeave(value: ((event: ItemDragInfo,itemIndex: int32) => void) | undefined): this {
        throw new Error("Unimplemented method onItemDragLeave")
    }
    onItemDrop(value: ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32,isSuccess: boolean) => void) | undefined): this {
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
    lanes(value: int32 | LengthConstrain | undefined, gutter?: Dimension): this {
        throw new Error("Unimplemented method lanes")
    }
    cachedCount(count: int32 | undefined, show: boolean | undefined): this {
        throw new Error("Unimplemented method cachedCount")
    }
    attributeModifier(value: AttributeModifier<ListAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkListStyle extends ArkScrollableCommonMethodStyle implements ListAttribute {
    alignListItem_value?: ListItemAlign | undefined
    listDirection_value?: Axis | undefined
    contentStartOffset_value?: double | undefined
    contentEndOffset_value?: double | undefined
    divider_value?: ListDividerOptions | null | undefined
    multiSelectable_value?: boolean | undefined
    cachedCount_value?: int32 | undefined
    chainAnimation_value?: boolean | undefined
    chainAnimationOptions_value?: ChainAnimationOptions | undefined
    sticky_value?: StickyStyle | undefined
    scrollSnapAlign_value?: ScrollSnapAlign | undefined
    childrenMainSize_value?: ChildrenMainSize | undefined
    maintainVisibleContentPosition_value?: boolean | undefined
    stackFromEnd_value?: boolean | undefined
    onScrollIndex_value?: ((start: int32,end: int32,center: int32) => void) | undefined
    onScrollVisibleContentChange_value?: OnScrollVisibleContentChangeCallback | undefined
    onItemMove_value?: ((from: int32,to: int32) => boolean) | undefined
    onItemDragStart_value?: OnItemDragStartCallback | undefined
    onItemDragEnter_value?: ((event: ItemDragInfo) => void) | undefined
    onItemDragMove_value?: ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32) => void) | undefined
    onItemDragLeave_value?: ((event: ItemDragInfo,itemIndex: int32) => void) | undefined
    onItemDrop_value?: ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32,isSuccess: boolean) => void) | undefined
    onScrollFrameBegin_value?: OnScrollFrameBeginCallback | undefined
    onWillScroll_value?: OnWillScrollCallback | undefined
    onDidScroll_value?: OnScrollCallback | undefined
    attributeModifier_value?: AttributeModifier<ListAttribute> | AttributeModifier<CommonMethod> | undefined
    setListOptions(options?: ListOptions): this {
        return this
    }
    alignListItem(value: ListItemAlign | undefined): this {
        return this
    }
    listDirection(value: Axis | undefined): this {
        return this
    }
    contentStartOffset(value: double | undefined): this {
        return this
    }
    contentEndOffset(value: double | undefined): this {
        return this
    }
    divider(value: ListDividerOptions | null | undefined): this {
        return this
    }
    multiSelectable(value: boolean | undefined): this {
        return this
    }
    cachedCount(value: int32 | undefined): this {
        return this
    }
    chainAnimation(value: boolean | undefined): this {
        return this
    }
    chainAnimationOptions(value: ChainAnimationOptions | undefined): this {
        return this
    }
    sticky(value: StickyStyle | undefined): this {
        return this
    }
    scrollSnapAlign(value: ScrollSnapAlign | undefined): this {
        return this
    }
    childrenMainSize(value: ChildrenMainSize | undefined): this {
        return this
    }
    maintainVisibleContentPosition(value: boolean | undefined): this {
        return this
    }
    stackFromEnd(value: boolean | undefined): this {
        return this
    }
    onScrollIndex(value: ((start: int32,end: int32,center: int32) => void) | undefined): this {
        return this
    }
    onScrollVisibleContentChange(value: OnScrollVisibleContentChangeCallback | undefined): this {
        return this
    }
    onItemMove(value: ((from: int32,to: int32) => boolean) | undefined): this {
        return this
    }
    onItemDragStart(value: OnItemDragStartCallback | undefined): this {
        return this
    }
    onItemDragEnter(value: ((event: ItemDragInfo) => void) | undefined): this {
        return this
    }
    onItemDragMove(value: ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32) => void) | undefined): this {
        return this
    }
    onItemDragLeave(value: ((event: ItemDragInfo,itemIndex: int32) => void) | undefined): this {
        return this
    }
    onItemDrop(value: ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32,isSuccess: boolean) => void) | undefined): this {
        return this
    }
    onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        return this
    }
    onWillScroll(value: OnWillScrollCallback | undefined): this {
        return this
    }
    onDidScroll(value: OnScrollCallback | undefined): this {
        return this
    }
    lanes(value: int32 | LengthConstrain | undefined, gutter?: Dimension): this {
        return this
    }
    cachedCount(count: int32 | undefined, show: boolean | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<ListAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkListComponent extends ArkScrollableCommonMethodComponent implements ListAttribute {
    getPeer(): ArkListPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkListPeer)
    }
    public setListOptions(options?: ListOptions): this {
        if (this.checkPriority("setListOptions")) {
            const options_casted = options as (ListOptions | undefined)
            this.getPeer()?.setListOptionsAttribute(options_casted)
            this.applyOptionsFinish('ListAttribute');
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
    public contentStartOffset(value: double | undefined): this {
        if (this.checkPriority("contentStartOffset")) {
            const value_casted = value as (double | undefined)
            this.getPeer()?.setContentStartOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    public contentEndOffset(value: double | undefined): this {
        if (this.checkPriority("contentEndOffset")) {
            const value_casted = value as (double | undefined)
            this.getPeer()?.setContentEndOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    public divider(value: ListDividerOptions | null | undefined): this {
        if (this.checkPriority("divider")) {
            const value_casted = value as (ListDividerOptions | null | undefined)
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
    public cachedCount(value: int32 | undefined): this {
        if (this.checkPriority("cachedCount")) {
            const value_casted = value as (int32 | undefined)
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
            hookListChildrenMainSizeImpl(this, value_casted);
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
    public onScrollIndex(value: ((start: int32,end: int32,center: int32) => void) | undefined): this {
        if (this.checkPriority("onScrollIndex")) {
            const value_casted = value as (((start: int32,end: int32,center: int32) => void) | undefined)
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
    public onItemMove(value: ((from: int32,to: int32) => boolean) | undefined): this {
        if (this.checkPriority("onItemMove")) {
            const value_casted = value as (((from: int32,to: int32) => boolean) | undefined)
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
    public onItemDragMove(value: ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32) => void) | undefined): this {
        if (this.checkPriority("onItemDragMove")) {
            const value_casted = value as (((event: ItemDragInfo,itemIndex: int32,insertIndex: int32) => void) | undefined)
            this.getPeer()?.setOnItemDragMoveAttribute(value_casted)
            return this
        }
        return this
    }
    public onItemDragLeave(value: ((event: ItemDragInfo,itemIndex: int32) => void) | undefined): this {
        if (this.checkPriority("onItemDragLeave")) {
            const value_casted = value as (((event: ItemDragInfo,itemIndex: int32) => void) | undefined)
            this.getPeer()?.setOnItemDragLeaveAttribute(value_casted)
            return this
        }
        return this
    }
    public onItemDrop(value: ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32,isSuccess: boolean) => void) | undefined): this {
        if (this.checkPriority("onItemDrop")) {
            const value_casted = value as (((event: ItemDragInfo,itemIndex: int32,insertIndex: int32,isSuccess: boolean) => void) | undefined)
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
    public lanes(value: int32 | LengthConstrain | undefined, gutter?: Dimension): this {
        if (this.checkPriority("lanes")) {
            const value_casted = value as (int32 | LengthConstrain | undefined)
            const gutter_casted = gutter as (Dimension | undefined)
            this.getPeer()?.setLanesAttribute(value_casted, gutter_casted)
            return this
        }
        return this
    }
    public cachedCount(count: int32 | undefined, show: boolean | undefined): this {
        if (this.checkPriority("cachedCount")) {
            const count_casted = count as (int32 | undefined)
            const show_casted = show as (boolean | undefined)
            this.getPeer()?.setCachedCount1Attribute(count_casted, show_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ListAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        hookListAttributeModifier(this, value);
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
    public applyOptionsFinish(traceName: string): void {
        super.applyOptionsFinish(traceName)
    }
}

@memo
export function ListImpl(
    @memo
    style: ((attributes: ListAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkListComponent>((): ArkListComponent => {
        return new ArkListComponent()
    })
    NodeAttach<ArkListPeer>((): ArkListPeer => ArkListPeer.create(receiver), (peer: ArkListPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
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
        let onFinishTmpBuf : (() => void) | undefined = undefined
        if ((onFinishTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onFinishTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onFinishTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onFinishTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onFinishTmpBuf = ():void => {
                const onFinishTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onFinishTmpBuf_BufArgsSerializer.writeInt32(onFinishTmpBuf_BufResource.resourceId);
                onFinishTmpBuf_BufArgsSerializer.writePointer(onFinishTmpBuf_BufCall);
                onFinishTmpBuf_BufArgsSerializer.writePointer(onFinishTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1867723152, onFinishTmpBuf_BufArgsSerializer.asBuffer(), onFinishTmpBuf_BufArgsSerializer.length());
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
            valueSerializer.writeInt32(valueHolderForInitialIndexTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSpace  = value.space
        if (valueHolderForSpace !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSpaceTmpValue  = valueHolderForSpace!
            if (valueHolderForSpaceTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForSpaceTmpValueForIdx0  = valueHolderForSpaceTmpValue as double
                valueSerializer.writeFloat64(valueHolderForSpaceTmpValueForIdx0)
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
        let initialIndexTmpBuf : int32 | undefined = undefined
        if ((initialIndexTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            initialIndexTmpBuf = valueDeserializer.readInt32()
        }
        const initialIndexTmpResult : int32 | undefined = initialIndexTmpBuf
        const spaceTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let spaceTmpBuf : double | string | undefined = undefined
        if ((spaceTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const spaceTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let spaceTmpBuf_ : double | string | undefined
            if (spaceTmpBuf_UnionSelector == (0).toChar()) {
                spaceTmpBuf_ = valueDeserializer.readFloat64()
            } else if (spaceTmpBuf_UnionSelector == (1).toChar()) {
                spaceTmpBuf_ = (valueDeserializer.readString() as string)
            } else {
                throw new Error("One of the branches for spaceTmpBuf_ has to be chosen through deserialisation.")
            }
            spaceTmpBuf = (spaceTmpBuf_ as double | string)
        }
        const spaceTmpResult : double | string | undefined = spaceTmpBuf
        const scrollerTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let scrollerTmpBuf : Scroller | undefined = undefined
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
        valueSerializer.writeInt32(valueHolderForIndex)
        const valueHolderForItemGroupArea  = value.itemGroupArea
        if (valueHolderForItemGroupArea !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForItemGroupAreaTmpValue  = (valueHolderForItemGroupArea as ListItemGroupArea)
            valueSerializer.writeInt32(valueHolderForItemGroupAreaTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForItemIndexInGroup  = value.itemIndexInGroup
        if (valueHolderForItemIndexInGroup !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForItemIndexInGroupTmpValue  = valueHolderForItemIndexInGroup!
            valueSerializer.writeInt32(valueHolderForItemIndexInGroupTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): VisibleListContentInfo {
        let valueDeserializer : DeserializerBase = buffer
        const indexTmpResult : int32 = valueDeserializer.readInt32()
        const itemGroupAreaTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let itemGroupAreaTmpBuf : ListItemGroupArea | undefined = undefined
        if ((itemGroupAreaTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            itemGroupAreaTmpBuf = ListItemGroupArea.fromValue(valueDeserializer.readInt32())
        }
        const itemGroupAreaTmpResult : ListItemGroupArea | undefined = itemGroupAreaTmpBuf
        const itemIndexInGroupTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let itemIndexInGroupTmpBuf : int32 | undefined = undefined
        if ((itemIndexInGroupTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            itemIndexInGroupTmpBuf = valueDeserializer.readInt32()
        }
        const itemIndexInGroupTmpResult : int32 | undefined = itemIndexInGroupTmpBuf
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
        } else if (valueHolderForMinSpace instanceof double) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForMinSpaceForIdx1  = valueHolderForMinSpace as double
            valueSerializer.writeFloat64(valueHolderForMinSpaceForIdx1)
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
        } else if (valueHolderForMaxSpace instanceof double) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForMaxSpaceForIdx1  = valueHolderForMaxSpace as double
            valueSerializer.writeFloat64(valueHolderForMaxSpaceForIdx1)
        } else if (valueHolderForMaxSpace instanceof Resource) {
            valueSerializer.writeInt8((2).toChar())
            const valueHolderForMaxSpaceForIdx2  = valueHolderForMaxSpace as Resource
            Resource_serializer.write(valueSerializer, valueHolderForMaxSpaceForIdx2)
        }
        const valueHolderForConductivity  = value.conductivity
        if (valueHolderForConductivity !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForConductivityTmpValue  = valueHolderForConductivity!
            valueSerializer.writeFloat64(valueHolderForConductivityTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForIntensity  = value.intensity
        if (valueHolderForIntensity !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIntensityTmpValue  = valueHolderForIntensity!
            valueSerializer.writeFloat64(valueHolderForIntensityTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEdgeEffect  = value.edgeEffect
        if (valueHolderForEdgeEffect !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEdgeEffectTmpValue  = (valueHolderForEdgeEffect as ChainEdgeEffect)
            valueSerializer.writeInt32(valueHolderForEdgeEffectTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStiffness  = value.stiffness
        if (valueHolderForStiffness !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStiffnessTmpValue  = valueHolderForStiffness!
            valueSerializer.writeFloat64(valueHolderForStiffnessTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDamping  = value.damping
        if (valueHolderForDamping !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDampingTmpValue  = valueHolderForDamping!
            valueSerializer.writeFloat64(valueHolderForDampingTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ChainAnimationOptions {
        let valueDeserializer : DeserializerBase = buffer
        const minSpaceTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let minSpaceTmpBuf : string | double | Resource | undefined
        if (minSpaceTmpBufUnionSelector == (0).toChar()) {
            minSpaceTmpBuf = (valueDeserializer.readString() as string)
        } else if (minSpaceTmpBufUnionSelector == (1).toChar()) {
            minSpaceTmpBuf = valueDeserializer.readFloat64()
        } else if (minSpaceTmpBufUnionSelector == (2).toChar()) {
            minSpaceTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for minSpaceTmpBuf has to be chosen through deserialisation.")
        }
        const minSpaceTmpResult : Length = (minSpaceTmpBuf as string | double | Resource)
        const maxSpaceTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let maxSpaceTmpBuf : string | double | Resource | undefined
        if (maxSpaceTmpBufUnionSelector == (0).toChar()) {
            maxSpaceTmpBuf = (valueDeserializer.readString() as string)
        } else if (maxSpaceTmpBufUnionSelector == (1).toChar()) {
            maxSpaceTmpBuf = valueDeserializer.readFloat64()
        } else if (maxSpaceTmpBufUnionSelector == (2).toChar()) {
            maxSpaceTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for maxSpaceTmpBuf has to be chosen through deserialisation.")
        }
        const maxSpaceTmpResult : Length = (maxSpaceTmpBuf as string | double | Resource)
        const conductivityTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let conductivityTmpBuf : double | undefined = undefined
        if ((conductivityTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            conductivityTmpBuf = valueDeserializer.readFloat64()
        }
        const conductivityTmpResult : double | undefined = conductivityTmpBuf
        const intensityTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let intensityTmpBuf : double | undefined = undefined
        if ((intensityTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            intensityTmpBuf = valueDeserializer.readFloat64()
        }
        const intensityTmpResult : double | undefined = intensityTmpBuf
        const edgeEffectTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let edgeEffectTmpBuf : ChainEdgeEffect | undefined = undefined
        if ((edgeEffectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            edgeEffectTmpBuf = ChainEdgeEffect.fromValue(valueDeserializer.readInt32())
        }
        const edgeEffectTmpResult : ChainEdgeEffect | undefined = edgeEffectTmpBuf
        const stiffnessTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let stiffnessTmpBuf : double | undefined = undefined
        if ((stiffnessTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            stiffnessTmpBuf = valueDeserializer.readFloat64()
        }
        const stiffnessTmpResult : double | undefined = stiffnessTmpBuf
        const dampingTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let dampingTmpBuf : double | undefined = undefined
        if ((dampingTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            dampingTmpBuf = valueDeserializer.readFloat64()
        }
        const dampingTmpResult : double | undefined = dampingTmpBuf
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
        } else if (valueHolderForStrokeWidth instanceof double) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForStrokeWidthForIdx1  = valueHolderForStrokeWidth as double
            valueSerializer.writeFloat64(valueHolderForStrokeWidthForIdx1)
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
                valueSerializer.writeInt32(valueHolderForColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForColorTmpValueForIdx1  = valueHolderForColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForColorTmpValueForIdx1)
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
            } else if (valueHolderForStartMarginTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForStartMarginTmpValueForIdx1  = valueHolderForStartMarginTmpValue as double
                valueSerializer.writeFloat64(valueHolderForStartMarginTmpValueForIdx1)
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
            } else if (valueHolderForEndMarginTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForEndMarginTmpValueForIdx1  = valueHolderForEndMarginTmpValue as double
                valueSerializer.writeFloat64(valueHolderForEndMarginTmpValueForIdx1)
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
        let strokeWidthTmpBuf : string | double | Resource | undefined
        if (strokeWidthTmpBufUnionSelector == (0).toChar()) {
            strokeWidthTmpBuf = (valueDeserializer.readString() as string)
        } else if (strokeWidthTmpBufUnionSelector == (1).toChar()) {
            strokeWidthTmpBuf = valueDeserializer.readFloat64()
        } else if (strokeWidthTmpBufUnionSelector == (2).toChar()) {
            strokeWidthTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for strokeWidthTmpBuf has to be chosen through deserialisation.")
        }
        const strokeWidthTmpResult : Length = (strokeWidthTmpBuf as string | double | Resource)
        const colorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let colorTmpBuf : ResourceColor | undefined = undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const colorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let colorTmpBuf_ : Color | int32 | string | Resource | undefined
            if (colorTmpBuf_UnionSelector == (0).toChar()) {
                colorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (colorTmpBuf_UnionSelector == (1).toChar()) {
                colorTmpBuf_ = (valueDeserializer.readInt32())
            } else if (colorTmpBuf_UnionSelector == (2).toChar()) {
                colorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (colorTmpBuf_UnionSelector == (3).toChar()) {
                colorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for colorTmpBuf_ has to be chosen through deserialisation.")
            }
            colorTmpBuf = (colorTmpBuf_ as Color | int32 | string | Resource)
        }
        const colorTmpResult : ResourceColor | undefined = colorTmpBuf
        const startMarginTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let startMarginTmpBuf : Length | undefined = undefined
        if ((startMarginTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const startMarginTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let startMarginTmpBuf_ : string | double | Resource | undefined
            if (startMarginTmpBuf_UnionSelector == (0).toChar()) {
                startMarginTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (startMarginTmpBuf_UnionSelector == (1).toChar()) {
                startMarginTmpBuf_ = valueDeserializer.readFloat64()
            } else if (startMarginTmpBuf_UnionSelector == (2).toChar()) {
                startMarginTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for startMarginTmpBuf_ has to be chosen through deserialisation.")
            }
            startMarginTmpBuf = (startMarginTmpBuf_ as string | double | Resource)
        }
        const startMarginTmpResult : Length | undefined = startMarginTmpBuf
        const endMarginTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let endMarginTmpBuf : Length | undefined = undefined
        if ((endMarginTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const endMarginTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let endMarginTmpBuf_ : string | double | Resource | undefined
            if (endMarginTmpBuf_UnionSelector == (0).toChar()) {
                endMarginTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (endMarginTmpBuf_UnionSelector == (1).toChar()) {
                endMarginTmpBuf_ = valueDeserializer.readFloat64()
            } else if (endMarginTmpBuf_UnionSelector == (2).toChar()) {
                endMarginTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for endMarginTmpBuf_ has to be chosen through deserialisation.")
            }
            endMarginTmpBuf = (endMarginTmpBuf_ as string | double | Resource)
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
    public getItemRectInGroup(index: int32, indexInGroup: int32): RectResult {
        const index_casted = index as (int32)
        const indexInGroup_casted = indexInGroup as (int32)
        return this.getItemRectInGroup_serialize(index_casted, indexInGroup_casted)
    }
    public scrollToItemInGroup(index: int32, indexInGroup: int32, smooth?: boolean, align?: ScrollAlign): void {
        const index_casted = index as (int32)
        const indexInGroup_casted = indexInGroup as (int32)
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
    public getVisibleListContentInfo(x: double, y: double): VisibleListContentInfo {
        const x_casted = x as (double)
        const y_casted = y as (double)
        return this.getVisibleListContentInfo_serialize(x_casted, y_casted)
    }
    getItemRectInGroup_serialize(index: int32, indexInGroup: int32): RectResult {
        const retval  = ArkUIGeneratedNativeModule._ListScroller_getItemRectInGroup(this.peer!.ptr, index, indexInGroup)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : RectResult = RectResult_serializer.read(retvalDeserializer)
        return returnResult
    }
    scrollToItemInGroup_serialize(index: int32, indexInGroup: int32, smooth?: boolean, align?: ScrollAlign): void {
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
            thisSerializer.writeInt32(alignTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ListScroller_scrollToItemInGroup(this.peer!.ptr, index, indexInGroup, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    closeAllSwipeActions_serialize(options?: CloseSwipeActionOptions): void {
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
    getVisibleListContentInfo_serialize(x: double, y: double): VisibleListContentInfo {
        const retval  = ArkUIGeneratedNativeModule._ListScroller_getVisibleListContentInfo(this.peer!.ptr, x, y)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : VisibleListContentInfo = VisibleListContentInfo_serializer.read(retvalDeserializer)
        return returnResult
    }
}

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
import { ArkScrollableCommonMethodPeer, ScrollableCommonMethod, NestedScrollOptions, ChildrenMainSize, ItemDragInfo, CustomBuilder, EdgeEffectOptions, ArkScrollableCommonMethodComponent, ArkScrollableCommonMethodStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethod, RectResult, OnWillScrollCallback, OnScrollCallback } from "./common"
import { Axis, BarState, EdgeEffect } from "./enums"
import { Resource } from "global.resource"
import { Callback_Number_Number_Void, Callback_ItemDragInfo_Void, Callback_ItemDragInfo_Number_Number_Void, Callback_ItemDragInfo_Number_Void, Callback_ItemDragInfo_Number_Number_Boolean_Void, Callback_Number_ScrollState_Literal_Number_offsetRemain, Literal_Number_offsetRemain } from "./grid"
import { ListAttribute_onItemDragStart_event_type } from "./type-replacements"
import { LengthConstrain, Dimension, PX, VP, FP, LPX, Percentage, Length, ResourceColor } from "./units"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Scroller, ScrollerInternal, ScrollAlign } from "./scroll"

import { Deserializer } from "./peers/Deserializer"
export class ArkListPeer extends ArkScrollableCommonMethodPeer {
    constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkListPeer {
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
    alignListItemAttribute(value: ListItemAlign | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as ListItemAlign)
            thisSerializer.writeInt32(TypeChecker.ListItemAlign_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ListAttribute_alignListItem(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    listDirectionAttribute(value: Axis | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as Axis)
            thisSerializer.writeInt32(TypeChecker.Axis_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ListAttribute_listDirection(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    scrollBarAttribute(value: BarState | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as BarState)
            thisSerializer.writeInt32(TypeChecker.BarState_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ListAttribute_scrollBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    contentStartOffsetAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_contentStartOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    contentEndOffsetAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_contentEndOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
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
    editModeAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_editMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    multiSelectableAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_multiSelectable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    cachedCount0Attribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_cachedCount0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    cachedCount1Attribute(count: number | undefined, show: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let count_type : int32 = RuntimeType.UNDEFINED
        count_type = runtimeType(count)
        thisSerializer.writeInt8(count_type as int32)
        if ((RuntimeType.UNDEFINED) != (count_type)) {
            const count_value  = count!
            thisSerializer.writeNumber(count_value)
        }
        let show_type : int32 = RuntimeType.UNDEFINED
        show_type = runtimeType(show)
        thisSerializer.writeInt8(show_type as int32)
        if ((RuntimeType.UNDEFINED) != (show_type)) {
            const show_value  = show!
            thisSerializer.writeBoolean(show_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_cachedCount1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    chainAnimationAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_chainAnimation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    chainAnimationOptionsAttribute(value: ChainAnimationOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeChainAnimationOptions(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_chainAnimationOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    stickyAttribute(value: StickyStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as StickyStyle)
            thisSerializer.writeInt32(TypeChecker.StickyStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ListAttribute_sticky(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    scrollSnapAlignAttribute(value: ScrollSnapAlign | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as ScrollSnapAlign)
            thisSerializer.writeInt32(TypeChecker.ScrollSnapAlign_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ListAttribute_scrollSnapAlign(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    nestedScrollAttribute(value: NestedScrollOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNestedScrollOptions(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_nestedScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableScrollInteractionAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_enableScrollInteraction(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    frictionAttribute(value: number | Resource | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Resource
                thisSerializer.writeResource(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._ListAttribute_friction(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    childrenMainSizeAttribute(value: ChildrenMainSize | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeChildrenMainSize(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_childrenMainSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    maintainVisibleContentPositionAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_maintainVisibleContentPosition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    stackFromEndAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_stackFromEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollAttribute(value: ((first: number,last: number) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_onScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollIndexAttribute(value: ((start: number,end: number,center: number) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_onScrollIndex(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollVisibleContentChangeAttribute(value: OnScrollVisibleContentChangeCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_onScrollVisibleContentChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onReachStartAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_onReachStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onReachEndAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_onReachEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollStartAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_onScrollStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollStopAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_onScrollStop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDeleteAttribute(value: ((index: number) => boolean) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_onItemDelete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemMoveAttribute(value: ((from: number,to: number) => boolean) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_onItemMove(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDragStartAttribute(value: ((event: ItemDragInfo,itemIndex: number) => CustomBuilder) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_onItemDragStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDragEnterAttribute(value: ((event: ItemDragInfo) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_onItemDragEnter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDragMoveAttribute(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_onItemDragMove(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDragLeaveAttribute(value: ((event: ItemDragInfo,itemIndex: number) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_onItemDragLeave(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDropAttribute(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_onItemDrop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollFrameBeginAttribute(value: ((offset: number,state: ScrollState) => Literal_Number_offsetRemain) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_onScrollFrameBegin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillScrollAttribute(value: OnWillScrollCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_onWillScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDidScrollAttribute(value: OnScrollCallback | undefined): void {
        const thisSerializer: Serializer = Serializer.hold();
        let value_type: int32 = RuntimeType.UNDEFINED;
        value_type = runtimeType(value);
        thisSerializer.writeInt8(value_type as int32);
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value = value!;
            thisSerializer.holdAndWriteCallback(value_value);
        }
        ArkUIGeneratedNativeModule._ListAttribute_onDidScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length());
        thisSerializer.release();
    }
    lanesAttribute(value: number | LengthConstrain | undefined, gutter?: Dimension): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as LengthConstrain
                thisSerializer.writeLengthConstrain(value_value_1)
            }
        }
        let gutter_type : int32 = RuntimeType.UNDEFINED
        gutter_type = runtimeType(gutter)
        thisSerializer.writeInt8(gutter_type as int32)
        if ((RuntimeType.UNDEFINED) != (gutter_type)) {
            const gutter_value  = gutter!
            thisSerializer.writeLength(gutter_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_lanes(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    edgeEffectAttribute(value: EdgeEffect | undefined, options?: EdgeEffectOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as EdgeEffect)
            thisSerializer.writeInt32(TypeChecker.EdgeEffect_ToNumeric(value_value))
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeEdgeEffectOptions(options_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_edgeEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    divider(value: ListDividerOptions | undefined): this
    editMode(value: boolean | undefined): this
    multiSelectable(value: boolean | undefined): this
    cachedCount(count: number | undefined, show?: boolean): this
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
    onScrollFrameBegin(value: ((offset: number,state: ScrollState) => Literal_Number_offsetRemain) | undefined): this
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
    divider_value?: ListDividerOptions | undefined
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
    onScrollFrameBegin_value?: ((offset: number,state: ScrollState) => Literal_Number_offsetRemain) | undefined
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
    public divider(value: ListDividerOptions | undefined): this {
        return this
    }
    public editMode(value: boolean | undefined): this {
        return this
    }
    public multiSelectable(value: boolean | undefined): this {
        return this
    }
    public cachedCount(count: number | undefined, show?: boolean): this {
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
    public onScrollFrameBegin(value: ((offset: number,state: ScrollState) => Literal_Number_offsetRemain) | undefined): this {
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
    public divider(value: ListDividerOptions | undefined): this {
        if (this.checkPriority("divider")) {
            const value_casted = value as (ListDividerOptions | undefined)
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
    public cachedCount(count: number | undefined, show?: boolean): this {
        if (this.checkPriority("cachedCount")) {
            const count_type = runtimeType(count)
            const show_type = runtimeType(show)
            if (((RuntimeType.NUMBER == count_type) || (RuntimeType.UNDEFINED == count_type)) && (RuntimeType.UNDEFINED == show_type)) {
                const value_casted = count as (number | undefined)
                this.getPeer()?.cachedCount0Attribute(value_casted)
                return this
            }
            if (((RuntimeType.NUMBER == count_type) || (RuntimeType.UNDEFINED == count_type)) && ((RuntimeType.BOOLEAN == show_type) || (RuntimeType.UNDEFINED == show_type))) {
                const count_casted = count as (number | undefined)
                const show_casted = show as (boolean | undefined)
                this.getPeer()?.cachedCount1Attribute(count_casted, show_casted)
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
            const value_casted = value as (ChildrenMainSize | undefined)
            this.getPeer()?.childrenMainSizeAttribute(value_casted)
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
    public onScrollFrameBegin(value: ((offset: number,state: ScrollState) => Literal_Number_offsetRemain) | undefined): this {
        if (this.checkPriority("onScrollFrameBegin")) {
            const value_casted = value as (((offset: number,state: ScrollState) => Literal_Number_offsetRemain) | undefined)
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
            const gutter_casted = gutter as (Dimension)
            this.getPeer()?.lanesAttribute(value_casted, gutter_casted)
            return this
        }
        return this
    }
    public edgeEffect(value: EdgeEffect | undefined, options?: EdgeEffectOptions): this {
        if (this.checkPriority("edgeEffect")) {
            const value_casted = value as (EdgeEffect | undefined)
            const options_casted = options as (EdgeEffectOptions)
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
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : VisibleListContentInfo = retvalDeserializer.readVisibleListContentInfo()
        return returnResult
    }
}

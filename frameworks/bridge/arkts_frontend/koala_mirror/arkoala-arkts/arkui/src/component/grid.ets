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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { Scroller_serializer, OnScrollFrameBeginCallback, Scroller } from "./scroll"
import { Resource_serializer, Resource } from "./../generated/resource"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkScrollableCommonMethodPeer, ScrollableCommonMethod, OnItemDragStartCallback, ItemDragInfo, OnWillScrollCallback, OnScrollCallback, CommonMethod, ArkScrollableCommonMethodComponent, ArkScrollableCommonMethodStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkScrollableCommonMethodSet, ArkCommonMethodSet } from "./common"
import { Length } from "./units"
import { ScrollState } from "./list"
import { ScrollSource } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkGridPeer extends ArkScrollableCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkGridPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Grid_construct(peerId, flags)
        const _peer  = new ArkGridPeer(_peerPtr, peerId, "Grid", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setGridOptionsAttribute(scroller?: Scroller, layoutOptions?: GridLayoutOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let scroller_type : int32 = RuntimeType.UNDEFINED
        scroller_type = runtimeType(scroller)
        thisSerializer.writeInt8((scroller_type).toChar())
        if ((scroller_type) != (RuntimeType.UNDEFINED)) {
            const scroller_value  = scroller!
            Scroller_serializer.write(thisSerializer, scroller_value)
        }
        let layoutOptions_type : int32 = RuntimeType.UNDEFINED
        layoutOptions_type = runtimeType(layoutOptions)
        thisSerializer.writeInt8((layoutOptions_type).toChar())
        if ((layoutOptions_type) != (RuntimeType.UNDEFINED)) {
            const layoutOptions_value  = layoutOptions!
            GridLayoutOptions_serializer.write(thisSerializer, layoutOptions_value)
        }
        ArkUIGeneratedNativeModule._GridInterface_setGridOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setColumnsTemplateAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setColumnsTemplate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRowsTemplateAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setRowsTemplate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setColumnsGapAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._GridAttribute_setColumnsGap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRowsGapAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._GridAttribute_setRowsGap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnScrollBarUpdateAttribute(value: ((index: number,offset: number) => ComputedBarAttribute) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setOnScrollBarUpdate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnScrollIndexAttribute(value: ((first: number,last: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setOnScrollIndex(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_setCachedCount0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEditModeAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setEditMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_setMultiSelectable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxCountAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setMaxCount(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinCountAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setMinCount(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCellLengthAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setCellLength(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLayoutDirectionAttribute(value: GridDirection | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as GridDirection)
            thisSerializer.writeInt32(TypeChecker.GridDirection_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._GridAttribute_setLayoutDirection(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSupportAnimationAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setSupportAnimation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_setOnItemDragStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_setOnItemDragEnter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_setOnItemDragMove(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_setOnItemDragLeave(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_setOnItemDrop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAlignItemsAttribute(value: GridItemAlignment | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as GridItemAlignment)
            thisSerializer.writeInt32(TypeChecker.GridItemAlignment_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._GridAttribute_setAlignItems(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_setOnScrollFrameBegin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_setOnWillScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_setOnDidScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_setCachedCount1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface GridLayoutOptions {
    regularSize: [ number, number ];
    irregularIndexes?: Array<number>;
    onGetIrregularSizeByIndex?: ((index: number) => [ number, number ]);
    onGetRectByIndex?: ((index: number) => [ number, number, number, number ]);
}
export enum GridDirection {
    ROW = 0,
    Row = 0,
    COLUMN = 1,
    Column = 1,
    ROW_REVERSE = 2,
    RowReverse = 2,
    COLUMN_REVERSE = 3,
    ColumnReverse = 3
}
export enum GridItemAlignment {
    DEFAULT = 0,
    STRETCH = 1
}
export interface ComputedBarAttribute {
    totalOffset: number;
    totalLength: number;
}
export interface GridAttribute extends ScrollableCommonMethod {
    columnsTemplate(value: string | undefined): this {
        throw new Error("Unimplemented method columnsTemplate")
    }
    rowsTemplate(value: string | undefined): this {
        throw new Error("Unimplemented method rowsTemplate")
    }
    columnsGap(value: Length | undefined): this {
        throw new Error("Unimplemented method columnsGap")
    }
    rowsGap(value: Length | undefined): this {
        throw new Error("Unimplemented method rowsGap")
    }
    onScrollBarUpdate(value: ((index: number,offset: number) => ComputedBarAttribute) | undefined): this {
        throw new Error("Unimplemented method onScrollBarUpdate")
    }
    onScrollIndex(value: ((first: number,last: number) => void) | undefined): this {
        throw new Error("Unimplemented method onScrollIndex")
    }
    cachedCount(value: number | undefined): this {
        throw new Error("Unimplemented method cachedCount")
    }
    editMode(value: boolean | undefined): this {
        throw new Error("Unimplemented method editMode")
    }
    multiSelectable(value: boolean | undefined): this {
        throw new Error("Unimplemented method multiSelectable")
    }
    maxCount(value: number | undefined): this {
        throw new Error("Unimplemented method maxCount")
    }
    minCount(value: number | undefined): this {
        throw new Error("Unimplemented method minCount")
    }
    cellLength(value: number | undefined): this {
        throw new Error("Unimplemented method cellLength")
    }
    layoutDirection(value: GridDirection | undefined): this {
        throw new Error("Unimplemented method layoutDirection")
    }
    supportAnimation(value: boolean | undefined): this {
        throw new Error("Unimplemented method supportAnimation")
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
    alignItems(value: GridItemAlignment | undefined): this {
        throw new Error("Unimplemented method alignItems")
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
    cachedCount(count: number | undefined, show: boolean | undefined): this {
        throw new Error("Unimplemented method cachedCount")
    }
    attributeModifier(value: AttributeModifier<GridAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkGridStyle extends ArkScrollableCommonMethodStyle implements GridAttribute {
    columnsTemplate_value?: string | undefined
    rowsTemplate_value?: string | undefined
    columnsGap_value?: Length | undefined
    rowsGap_value?: Length | undefined
    onScrollBarUpdate_value?: ((index: number,offset: number) => ComputedBarAttribute) | undefined
    onScrollIndex_value?: ((first: number,last: number) => void) | undefined
    cachedCount_value?: number | undefined
    editMode_value?: boolean | undefined
    multiSelectable_value?: boolean | undefined
    maxCount_value?: number | undefined
    minCount_value?: number | undefined
    cellLength_value?: number | undefined
    layoutDirection_value?: GridDirection | undefined
    supportAnimation_value?: boolean | undefined
    onItemDragStart_value?: OnItemDragStartCallback | undefined
    onItemDragEnter_value?: ((event: ItemDragInfo) => void) | undefined
    onItemDragMove_value?: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void) | undefined
    onItemDragLeave_value?: ((event: ItemDragInfo,itemIndex: number) => void) | undefined
    onItemDrop_value?: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void) | undefined
    alignItems_value?: GridItemAlignment | undefined
    onScrollFrameBegin_value?: OnScrollFrameBeginCallback | undefined
    onWillScroll_value?: OnWillScrollCallback | undefined
    onDidScroll_value?: OnScrollCallback | undefined
    attributeModifier_value?: AttributeModifier<GridAttribute> | AttributeModifier<CommonMethod> | undefined
    public columnsTemplate(value: string | undefined): this {
        return this
    }
    public rowsTemplate(value: string | undefined): this {
        return this
    }
    public columnsGap(value: Length | undefined): this {
        return this
    }
    public rowsGap(value: Length | undefined): this {
        return this
    }
    public onScrollBarUpdate(value: ((index: number,offset: number) => ComputedBarAttribute) | undefined): this {
        return this
    }
    public onScrollIndex(value: ((first: number,last: number) => void) | undefined): this {
        return this
    }
    public cachedCount(value: number | undefined): this {
        return this
    }
    public editMode(value: boolean | undefined): this {
        return this
    }
    public multiSelectable(value: boolean | undefined): this {
        return this
    }
    public maxCount(value: number | undefined): this {
        return this
    }
    public minCount(value: number | undefined): this {
        return this
    }
    public cellLength(value: number | undefined): this {
        return this
    }
    public layoutDirection(value: GridDirection | undefined): this {
        return this
    }
    public supportAnimation(value: boolean | undefined): this {
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
    public alignItems(value: GridItemAlignment | undefined): this {
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
    public cachedCount(count: number | undefined, show: boolean | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<GridAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: GridAttribute): void {
        super.apply(target)
        if (this.columnsTemplate_value !== undefined)
            target.columnsTemplate(this.columnsTemplate_value!)
        if (this.rowsTemplate_value !== undefined)
            target.rowsTemplate(this.rowsTemplate_value!)
        if (this.columnsGap_value !== undefined)
            target.columnsGap(this.columnsGap_value!)
        if (this.rowsGap_value !== undefined)
            target.rowsGap(this.rowsGap_value!)
        if (this.onScrollBarUpdate_value !== undefined)
            target.onScrollBarUpdate(this.onScrollBarUpdate_value!)
        if (this.onScrollIndex_value !== undefined)
            target.onScrollIndex(this.onScrollIndex_value!)
        if (this.cachedCount_value !== undefined)
            target.cachedCount(this.cachedCount_value!)
        if (this.editMode_value !== undefined)
            target.editMode(this.editMode_value!)
        if (this.multiSelectable_value !== undefined)
            target.multiSelectable(this.multiSelectable_value!)
        if (this.maxCount_value !== undefined)
            target.maxCount(this.maxCount_value!)
        if (this.minCount_value !== undefined)
            target.minCount(this.minCount_value!)
        if (this.cellLength_value !== undefined)
            target.cellLength(this.cellLength_value!)
        if (this.layoutDirection_value !== undefined)
            target.layoutDirection(this.layoutDirection_value!)
        if (this.supportAnimation_value !== undefined)
            target.supportAnimation(this.supportAnimation_value!)
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
        if (this.alignItems_value !== undefined)
            target.alignItems(this.alignItems_value!)
        if (this.onScrollFrameBegin_value !== undefined)
            target.onScrollFrameBegin(this.onScrollFrameBegin_value!)
        if (this.onWillScroll_value !== undefined)
            target.onWillScroll(this.onWillScroll_value!)
        if (this.onDidScroll_value !== undefined)
            target.onDidScroll(this.onDidScroll_value!)
    }
}

export class ArkGridComponent extends ArkScrollableCommonMethodComponent implements GridAttribute {
    getPeer(): ArkGridPeer {
        return (this.peer as ArkGridPeer)
    }
    public setGridOptions(scroller?: Scroller, layoutOptions?: GridLayoutOptions): this {
        if (this.checkPriority("setGridOptions")) {
            const scroller_casted = scroller as (Scroller | undefined)
            const layoutOptions_casted = layoutOptions as (GridLayoutOptions | undefined)
            this.getPeer()?.setGridOptionsAttribute(scroller_casted, layoutOptions_casted)
            return this
        }
        return this
    }
    public columnsTemplate(value: string | undefined): this {
        if (this.checkPriority("columnsTemplate")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.setColumnsTemplateAttribute(value_casted)
            return this
        }
        return this
    }
    public rowsTemplate(value: string | undefined): this {
        if (this.checkPriority("rowsTemplate")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.setRowsTemplateAttribute(value_casted)
            return this
        }
        return this
    }
    public columnsGap(value: Length | undefined): this {
        if (this.checkPriority("columnsGap")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setColumnsGapAttribute(value_casted)
            return this
        }
        return this
    }
    public rowsGap(value: Length | undefined): this {
        if (this.checkPriority("rowsGap")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setRowsGapAttribute(value_casted)
            return this
        }
        return this
    }
    public onScrollBarUpdate(value: ((index: number,offset: number) => ComputedBarAttribute) | undefined): this {
        if (this.checkPriority("onScrollBarUpdate")) {
            const value_casted = value as (((index: number,offset: number) => ComputedBarAttribute) | undefined)
            this.getPeer()?.setOnScrollBarUpdateAttribute(value_casted)
            return this
        }
        return this
    }
    public onScrollIndex(value: ((first: number,last: number) => void) | undefined): this {
        if (this.checkPriority("onScrollIndex")) {
            const value_casted = value as (((first: number,last: number) => void) | undefined)
            this.getPeer()?.setOnScrollIndexAttribute(value_casted)
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
    public editMode(value: boolean | undefined): this {
        if (this.checkPriority("editMode")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEditModeAttribute(value_casted)
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
    public maxCount(value: number | undefined): this {
        if (this.checkPriority("maxCount")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setMaxCountAttribute(value_casted)
            return this
        }
        return this
    }
    public minCount(value: number | undefined): this {
        if (this.checkPriority("minCount")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setMinCountAttribute(value_casted)
            return this
        }
        return this
    }
    public cellLength(value: number | undefined): this {
        if (this.checkPriority("cellLength")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setCellLengthAttribute(value_casted)
            return this
        }
        return this
    }
    public layoutDirection(value: GridDirection | undefined): this {
        if (this.checkPriority("layoutDirection")) {
            const value_casted = value as (GridDirection | undefined)
            this.getPeer()?.setLayoutDirectionAttribute(value_casted)
            return this
        }
        return this
    }
    public supportAnimation(value: boolean | undefined): this {
        if (this.checkPriority("supportAnimation")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setSupportAnimationAttribute(value_casted)
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
    public alignItems(value: GridItemAlignment | undefined): this {
        if (this.checkPriority("alignItems")) {
            const value_casted = value as (GridItemAlignment | undefined)
            this.getPeer()?.setAlignItemsAttribute(value_casted)
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
    public cachedCount(count: number | undefined, show: boolean | undefined): this {
        if (this.checkPriority("cachedCount")) {
            const count_casted = count as (number | undefined)
            const show_casted = show as (boolean | undefined)
            this.getPeer()?.setCachedCount1Attribute(count_casted, show_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<GridAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withGridStyle(receiver: GridAttribute, modifier: AttributeModifier<GridAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkGridStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Grid")
// export function Grid(
//     scroller?: Scroller, layoutOptions?: GridLayoutOptions,
//     @memo
//     content_?: () => void,
// ): GridAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Grid(
    @memo
    style: ((attributes: GridAttribute) => void) | undefined,
    scroller?: Scroller, layoutOptions?: GridLayoutOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkGridComponent>((): ArkGridComponent => {
        return new ArkGridComponent()
    })
    NodeAttach<ArkGridPeer>((): ArkGridPeer => ArkGridPeer.create(receiver), (_: ArkGridPeer): void => {
        receiver.setGridOptions(scroller,layoutOptions)
        style?.(receiver)
        withGridStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkGridSet extends ArkScrollableCommonMethodSet implements GridAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _columnsTemplate_flag?: boolean
    _columnsTemplate0_value?: string | undefined
    _rowsTemplate_flag?: boolean
    _rowsTemplate0_value?: string | undefined
    _columnsGap_flag?: boolean
    _columnsGap0_value?: Length | undefined
    _rowsGap_flag?: boolean
    _rowsGap0_value?: Length | undefined
    _onScrollBarUpdate_flag?: boolean
    _onScrollBarUpdate0_value?: ((index: number,offset: number) => ComputedBarAttribute) | undefined
    _onScrollIndex_flag?: boolean
    _onScrollIndex0_value?: ((first: number,last: number) => void) | undefined
    _cachedCount_flag?: boolean
    _cachedCount0_value?: number | undefined
    _cachedCount1_value?: boolean | undefined
    _editMode_flag?: boolean
    _editMode0_value?: boolean | undefined
    _multiSelectable_flag?: boolean
    _multiSelectable0_value?: boolean | undefined
    _maxCount_flag?: boolean
    _maxCount0_value?: number | undefined
    _minCount_flag?: boolean
    _minCount0_value?: number | undefined
    _cellLength_flag?: boolean
    _cellLength0_value?: number | undefined
    _layoutDirection_flag?: boolean
    _layoutDirection0_value?: GridDirection | undefined
    _supportAnimation_flag?: boolean
    _supportAnimation0_value?: boolean | undefined
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
    _alignItems_flag?: boolean
    _alignItems0_value?: GridItemAlignment | undefined
    _onScrollFrameBegin_flag?: boolean
    _onScrollFrameBegin0_value?: OnScrollFrameBeginCallback | undefined
    _onWillScroll_flag?: boolean
    _onWillScroll0_value?: OnWillScrollCallback | undefined
    _onDidScroll_flag?: boolean
    _onDidScroll0_value?: OnScrollCallback | undefined
    applyModifierPatch(component: GridAttribute): void {
        if (this._columnsTemplate_flag)
            component.columnsTemplate((this._columnsTemplate0_value as string | undefined))
        if (this._rowsTemplate_flag)
            component.rowsTemplate((this._rowsTemplate0_value as string | undefined))
        if (this._columnsGap_flag)
            component.columnsGap((this._columnsGap0_value as Length | undefined))
        if (this._rowsGap_flag)
            component.rowsGap((this._rowsGap0_value as Length | undefined))
        if (this._onScrollBarUpdate_flag)
            component.onScrollBarUpdate((this._onScrollBarUpdate0_value as ((index: number,offset: number) => ComputedBarAttribute) | undefined))
        if (this._onScrollIndex_flag)
            component.onScrollIndex((this._onScrollIndex0_value as ((first: number,last: number) => void) | undefined))
        if (this._cachedCount_flag)
            component.cachedCount((this._cachedCount0_value as number | undefined), (this._cachedCount1_value as boolean | undefined))
        if (this._editMode_flag)
            component.editMode((this._editMode0_value as boolean | undefined))
        if (this._multiSelectable_flag)
            component.multiSelectable((this._multiSelectable0_value as boolean | undefined))
        if (this._maxCount_flag)
            component.maxCount((this._maxCount0_value as number | undefined))
        if (this._minCount_flag)
            component.minCount((this._minCount0_value as number | undefined))
        if (this._cellLength_flag)
            component.cellLength((this._cellLength0_value as number | undefined))
        if (this._layoutDirection_flag)
            component.layoutDirection((this._layoutDirection0_value as GridDirection | undefined))
        if (this._supportAnimation_flag)
            component.supportAnimation((this._supportAnimation0_value as boolean | undefined))
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
        if (this._alignItems_flag)
            component.alignItems((this._alignItems0_value as GridItemAlignment | undefined))
        if (this._onScrollFrameBegin_flag)
            component.onScrollFrameBegin((this._onScrollFrameBegin0_value as OnScrollFrameBeginCallback | undefined))
        if (this._onWillScroll_flag)
            component.onWillScroll((this._onWillScroll0_value as OnWillScrollCallback | undefined))
        if (this._onDidScroll_flag)
            component.onDidScroll((this._onDidScroll0_value as OnScrollCallback | undefined))
    }
    public columnsTemplate(value: string | undefined): this {
        this._columnsTemplate_flag = true
        this._columnsTemplate0_value = value
        return this
    }
    public rowsTemplate(value: string | undefined): this {
        this._rowsTemplate_flag = true
        this._rowsTemplate0_value = value
        return this
    }
    public columnsGap(value: Length | undefined): this {
        this._columnsGap_flag = true
        this._columnsGap0_value = value
        return this
    }
    public rowsGap(value: Length | undefined): this {
        this._rowsGap_flag = true
        this._rowsGap0_value = value
        return this
    }
    public onScrollBarUpdate(value: ((index: number,offset: number) => ComputedBarAttribute) | undefined): this {
        this._onScrollBarUpdate_flag = true
        this._onScrollBarUpdate0_value = value
        return this
    }
    public onScrollIndex(value: ((first: number,last: number) => void) | undefined): this {
        this._onScrollIndex_flag = true
        this._onScrollIndex0_value = value
        return this
    }
    public cachedCount(count: number | undefined, show: boolean | undefined): this {
        this._cachedCount_flag = true
        this._cachedCount0_value = count
        this._cachedCount1_value = show
        return this
    }
    public editMode(value: boolean | undefined): this {
        this._editMode_flag = true
        this._editMode0_value = value
        return this
    }
    public multiSelectable(value: boolean | undefined): this {
        this._multiSelectable_flag = true
        this._multiSelectable0_value = value
        return this
    }
    public maxCount(value: number | undefined): this {
        this._maxCount_flag = true
        this._maxCount0_value = value
        return this
    }
    public minCount(value: number | undefined): this {
        this._minCount_flag = true
        this._minCount0_value = value
        return this
    }
    public cellLength(value: number | undefined): this {
        this._cellLength_flag = true
        this._cellLength0_value = value
        return this
    }
    public layoutDirection(value: GridDirection | undefined): this {
        this._layoutDirection_flag = true
        this._layoutDirection0_value = value
        return this
    }
    public supportAnimation(value: boolean | undefined): this {
        this._supportAnimation_flag = true
        this._supportAnimation0_value = value
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
    public alignItems(value: GridItemAlignment | undefined): this {
        this._alignItems_flag = true
        this._alignItems0_value = value
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
    public attributeModifier(value: AttributeModifier<GridAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class ComputedBarAttribute_serializer {
    public static write(buffer: SerializerBase, value: ComputedBarAttribute): void {
        let valueSerializer : SerializerBase = buffer
        const value_totalOffset  = value.totalOffset
        valueSerializer.writeNumber(value_totalOffset)
        const value_totalLength  = value.totalLength
        valueSerializer.writeNumber(value_totalLength)
    }
    public static read(buffer: DeserializerBase): ComputedBarAttribute {
        let valueDeserializer : DeserializerBase = buffer
        const totalOffset_result : number = (valueDeserializer.readNumber() as number)
        const totalLength_result : number = (valueDeserializer.readNumber() as number)
        let value : ComputedBarAttribute = ({totalOffset: totalOffset_result, totalLength: totalLength_result} as ComputedBarAttribute)
        return value
    }
}
export class GridLayoutOptions_serializer {
    public static write(buffer: SerializerBase, value: GridLayoutOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_regularSize  = value.regularSize
        const value_regularSize_0  = value_regularSize[0]
        valueSerializer.writeNumber(value_regularSize_0)
        const value_regularSize_1  = value_regularSize[1]
        valueSerializer.writeNumber(value_regularSize_1)
        const value_irregularIndexes  = value.irregularIndexes
        let value_irregularIndexes_type : int32 = RuntimeType.UNDEFINED
        value_irregularIndexes_type = runtimeType(value_irregularIndexes)
        valueSerializer.writeInt8((value_irregularIndexes_type).toChar())
        if ((value_irregularIndexes_type) != (RuntimeType.UNDEFINED)) {
            const value_irregularIndexes_value  = value_irregularIndexes!
            valueSerializer.writeInt32((value_irregularIndexes_value.length).toInt())
            for (let value_irregularIndexes_value_counter_i = 0; value_irregularIndexes_value_counter_i < value_irregularIndexes_value.length; value_irregularIndexes_value_counter_i++) {
                const value_irregularIndexes_value_element : number = value_irregularIndexes_value[value_irregularIndexes_value_counter_i]
                valueSerializer.writeNumber(value_irregularIndexes_value_element)
            }
        }
        const value_onGetIrregularSizeByIndex  = value.onGetIrregularSizeByIndex
        let value_onGetIrregularSizeByIndex_type : int32 = RuntimeType.UNDEFINED
        value_onGetIrregularSizeByIndex_type = runtimeType(value_onGetIrregularSizeByIndex)
        valueSerializer.writeInt8((value_onGetIrregularSizeByIndex_type).toChar())
        if ((value_onGetIrregularSizeByIndex_type) != (RuntimeType.UNDEFINED)) {
            const value_onGetIrregularSizeByIndex_value  = value_onGetIrregularSizeByIndex!
            valueSerializer.holdAndWriteCallback(value_onGetIrregularSizeByIndex_value)
        }
        const value_onGetRectByIndex  = value.onGetRectByIndex
        let value_onGetRectByIndex_type : int32 = RuntimeType.UNDEFINED
        value_onGetRectByIndex_type = runtimeType(value_onGetRectByIndex)
        valueSerializer.writeInt8((value_onGetRectByIndex_type).toChar())
        if ((value_onGetRectByIndex_type) != (RuntimeType.UNDEFINED)) {
            const value_onGetRectByIndex_value  = value_onGetRectByIndex!
            valueSerializer.holdAndWriteCallback(value_onGetRectByIndex_value)
        }
    }
    public static read(buffer: DeserializerBase): GridLayoutOptions {
        let valueDeserializer : DeserializerBase = buffer
        const regularSize_buf_value0 : number = (valueDeserializer.readNumber() as number)
        const regularSize_buf_value1 : number = (valueDeserializer.readNumber() as number)
        const regularSize_result : [ number, number ] = ([regularSize_buf_value0, regularSize_buf_value1] as [ number, number ])
        const irregularIndexes_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let irregularIndexes_buf : Array<number> | undefined
        if ((irregularIndexes_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const irregularIndexes_buf__length : int32 = valueDeserializer.readInt32()
            let irregularIndexes_buf_ : Array<number> = new Array<number>(irregularIndexes_buf__length)
            for (let irregularIndexes_buf__i = 0; irregularIndexes_buf__i < irregularIndexes_buf__length; irregularIndexes_buf__i++) {
                irregularIndexes_buf_[irregularIndexes_buf__i] = (valueDeserializer.readNumber() as number)
            }
            irregularIndexes_buf = irregularIndexes_buf_
        }
        const irregularIndexes_result : Array<number> | undefined = irregularIndexes_buf
        const onGetIrregularSizeByIndex_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onGetIrregularSizeByIndex_buf : ((index: number) => [ number, number ]) | undefined
        if ((onGetIrregularSizeByIndex_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const onGetIrregularSizeByIndex_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onGetIrregularSizeByIndex_buf__call : KPointer = valueDeserializer.readPointer()
            const onGetIrregularSizeByIndex_buf__callSync : KPointer = valueDeserializer.readPointer()
            onGetIrregularSizeByIndex_buf = (index: number):[ number, number ] => { 
    const onGetIrregularSizeByIndex_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onGetIrregularSizeByIndex_buf__argsSerializer.writeInt32(onGetIrregularSizeByIndex_buf__resource.resourceId);
    onGetIrregularSizeByIndex_buf__argsSerializer.writePointer(onGetIrregularSizeByIndex_buf__call);
    onGetIrregularSizeByIndex_buf__argsSerializer.writePointer(onGetIrregularSizeByIndex_buf__callSync);
    onGetIrregularSizeByIndex_buf__argsSerializer.writeNumber(index);
    let onGetIrregularSizeByIndex_buf__continuationValue : [ number, number ] | undefined;
    const onGetIrregularSizeByIndex_buf__continuationCallback : ((value: [ number, number ]) => void) = (value: [ number, number ]):void => {     onGetIrregularSizeByIndex_buf__continuationValue = value; }
    onGetIrregularSizeByIndex_buf__argsSerializer.holdAndWriteCallback(onGetIrregularSizeByIndex_buf__continuationCallback);
    InteropNativeModule._CallCallback(1602877440, onGetIrregularSizeByIndex_buf__argsSerializer.asBuffer(), onGetIrregularSizeByIndex_buf__argsSerializer.length());
    onGetIrregularSizeByIndex_buf__argsSerializer.release();
    return (onGetIrregularSizeByIndex_buf__continuationValue as [ number, number ]); }
        }
        const onGetIrregularSizeByIndex_result : ((index: number) => [ number, number ]) | undefined = onGetIrregularSizeByIndex_buf
        const onGetRectByIndex_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onGetRectByIndex_buf : ((index: number) => [ number, number, number, number ]) | undefined
        if ((onGetRectByIndex_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const onGetRectByIndex_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onGetRectByIndex_buf__call : KPointer = valueDeserializer.readPointer()
            const onGetRectByIndex_buf__callSync : KPointer = valueDeserializer.readPointer()
            onGetRectByIndex_buf = (index: number):[ number, number, number, number ] => { 
    const onGetRectByIndex_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onGetRectByIndex_buf__argsSerializer.writeInt32(onGetRectByIndex_buf__resource.resourceId);
    onGetRectByIndex_buf__argsSerializer.writePointer(onGetRectByIndex_buf__call);
    onGetRectByIndex_buf__argsSerializer.writePointer(onGetRectByIndex_buf__callSync);
    onGetRectByIndex_buf__argsSerializer.writeNumber(index);
    let onGetRectByIndex_buf__continuationValue : [ number, number, number, number ] | undefined;
    const onGetRectByIndex_buf__continuationCallback : ((value: [ number, number, number, number ]) => void) = (value: [ number, number, number, number ]):void => {     onGetRectByIndex_buf__continuationValue = value; }
    onGetRectByIndex_buf__argsSerializer.holdAndWriteCallback(onGetRectByIndex_buf__continuationCallback);
    InteropNativeModule._CallCallback(1618565120, onGetRectByIndex_buf__argsSerializer.asBuffer(), onGetRectByIndex_buf__argsSerializer.length());
    onGetRectByIndex_buf__argsSerializer.release();
    return (onGetRectByIndex_buf__continuationValue as [ number, number, number, number ]); }
        }
        const onGetRectByIndex_result : ((index: number) => [ number, number, number, number ]) | undefined = onGetRectByIndex_buf
        let value : GridLayoutOptions = ({regularSize: regularSize_result, irregularIndexes: irregularIndexes_result, onGetIrregularSizeByIndex: onGetIrregularSizeByIndex_result, onGetRectByIndex: onGetRectByIndex_result} as GridLayoutOptions)
        return value
    }
}

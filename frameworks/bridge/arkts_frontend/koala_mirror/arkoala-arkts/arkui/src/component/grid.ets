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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { Scroller_serializer, OnScrollFrameBeginCallback, Scroller } from "./scroll"
import { Resource_serializer, Resource } from "./../generated/resource"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkScrollableCommonMethodPeer, ScrollableCommonMethod, OnItemDragStartCallback, ItemDragInfo, OnWillScrollCallback, OnScrollCallback, CommonMethod, ArkScrollableCommonMethodComponent, ArkScrollableCommonMethodStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, ScrollableCommonMethodModifier, CommonMethodModifier } from "./common"
import { Length } from "./units"
import { ScrollState } from "./list"
import { ScrollSource } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
export class ArkGridPeer extends ArkScrollableCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkGridPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Grid_construct(peerId, flags)
        const _peer  = new ArkGridPeer(_peerPtr, peerId, 'Grid', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setGridOptionsAttribute(scroller?: Scroller, layoutOptions?: GridLayoutOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (scroller !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const scrollerTmpValue  = scroller!
            Scroller_serializer.write(thisSerializer, scrollerTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (layoutOptions !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const layoutOptionsTmpValue  = layoutOptions!
            GridLayoutOptions_serializer.write(thisSerializer, layoutOptionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridInterface_setGridOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setColumnsTemplateAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeString(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setColumnsTemplate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRowsTemplateAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeString(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setRowsTemplate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setColumnsGapAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setColumnsGap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRowsGapAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setRowsGap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnScrollBarUpdateAttribute(value: ((index: number,offset: number) => ComputedBarAttribute) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setOnScrollBarUpdate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnScrollIndexAttribute(value: ((first: number,last: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setOnScrollIndex(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_setCachedCount0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEditModeAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setEditMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_setMultiSelectable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxCountAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeNumber(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setMaxCount(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinCountAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeNumber(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setMinCount(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCellLengthAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeNumber(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setCellLength(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLayoutDirectionAttribute(value: GridDirection | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as GridDirection)
            thisSerializer.writeInt32(TypeChecker.GridDirection_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setLayoutDirection(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSupportAnimationAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setSupportAnimation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_setOnItemDragStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_setOnItemDragEnter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_setOnItemDragMove(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_setOnItemDragLeave(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_setOnItemDrop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAlignItemsAttribute(value: GridItemAlignment | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as GridItemAlignment)
            thisSerializer.writeInt32(TypeChecker.GridItemAlignment_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setAlignItems(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_setOnScrollFrameBegin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_setOnWillScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_setOnDidScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

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
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class GridModifier extends ScrollableCommonMethodModifier implements GridAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _columnsTemplate_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _columnsTemplate_0_0value?: string | undefined
    _rowsTemplate_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _rowsTemplate_0_0value?: string | undefined
    _columnsGap_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _columnsGap_0_0value?: Length | undefined
    _rowsGap_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _rowsGap_0_0value?: Length | undefined
    _onScrollBarUpdate_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onScrollBarUpdate_0_0value?: ((index: number,offset: number) => ComputedBarAttribute) | undefined
    _onScrollIndex_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onScrollIndex_0_0value?: ((first: number,last: number) => void) | undefined
    _cachedCount_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _cachedCount_0_0value?: number | undefined
    _editMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _editMode_0_0value?: boolean | undefined
    _multiSelectable_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _multiSelectable_0_0value?: boolean | undefined
    _maxCount_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maxCount_0_0value?: number | undefined
    _minCount_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _minCount_0_0value?: number | undefined
    _cellLength_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _cellLength_0_0value?: number | undefined
    _layoutDirection_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _layoutDirection_0_0value?: GridDirection | undefined
    _supportAnimation_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _supportAnimation_0_0value?: boolean | undefined
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
    _alignItems_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _alignItems_0_0value?: GridItemAlignment | undefined
    _onScrollFrameBegin_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onScrollFrameBegin_0_0value?: OnScrollFrameBeginCallback | undefined
    _onWillScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWillScroll_0_0value?: OnWillScrollCallback | undefined
    _onDidScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDidScroll_0_0value?: OnScrollCallback | undefined
    _cachedCount_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _cachedCount_1_0value?: number | undefined
    _cachedCount_1_1value?: boolean | undefined
    applyModifierPatch(peer: ArkGridPeer): void {
        super.applyModifierPatch(peer)
        if (this._columnsTemplate_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._columnsTemplate_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setColumnsTemplateAttribute((this._columnsTemplate_0_0value as string | undefined));
                    this._columnsTemplate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._columnsTemplate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._columnsTemplate_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setColumnsTemplateAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._rowsTemplate_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._rowsTemplate_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRowsTemplateAttribute((this._rowsTemplate_0_0value as string | undefined));
                    this._rowsTemplate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._rowsTemplate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._rowsTemplate_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRowsTemplateAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._columnsGap_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._columnsGap_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setColumnsGapAttribute((this._columnsGap_0_0value as Length | undefined));
                    this._columnsGap_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._columnsGap_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._columnsGap_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setColumnsGapAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._rowsGap_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._rowsGap_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRowsGapAttribute((this._rowsGap_0_0value as Length | undefined));
                    this._rowsGap_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._rowsGap_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._rowsGap_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRowsGapAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._onScrollBarUpdate_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onScrollBarUpdate_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnScrollBarUpdateAttribute((this._onScrollBarUpdate_0_0value as ((index: number,offset: number) => ComputedBarAttribute) | undefined));
                    this._onScrollBarUpdate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScrollBarUpdate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScrollBarUpdate_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnScrollBarUpdateAttribute((undefined as ((index: number,offset: number) => ComputedBarAttribute) | undefined));
                }
            }
        }
        if (this._onScrollIndex_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onScrollIndex_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnScrollIndexAttribute((this._onScrollIndex_0_0value as ((first: number,last: number) => void) | undefined));
                    this._onScrollIndex_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScrollIndex_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScrollIndex_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnScrollIndexAttribute((undefined as ((first: number,last: number) => void) | undefined));
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
        if (this._editMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._editMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEditModeAttribute((this._editMode_0_0value as boolean | undefined));
                    this._editMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._editMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._editMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEditModeAttribute((undefined as boolean | undefined));
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
        if (this._maxCount_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._maxCount_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMaxCountAttribute((this._maxCount_0_0value as number | undefined));
                    this._maxCount_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maxCount_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._maxCount_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMaxCountAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._minCount_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._minCount_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMinCountAttribute((this._minCount_0_0value as number | undefined));
                    this._minCount_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minCount_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._minCount_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMinCountAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._cellLength_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._cellLength_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCellLengthAttribute((this._cellLength_0_0value as number | undefined));
                    this._cellLength_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._cellLength_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._cellLength_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCellLengthAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._layoutDirection_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._layoutDirection_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setLayoutDirectionAttribute((this._layoutDirection_0_0value as GridDirection | undefined));
                    this._layoutDirection_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._layoutDirection_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._layoutDirection_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setLayoutDirectionAttribute((undefined as GridDirection | undefined));
                }
            }
        }
        if (this._supportAnimation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._supportAnimation_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSupportAnimationAttribute((this._supportAnimation_0_0value as boolean | undefined));
                    this._supportAnimation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._supportAnimation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._supportAnimation_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSupportAnimationAttribute((undefined as boolean | undefined));
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
        if (this._alignItems_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._alignItems_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAlignItemsAttribute((this._alignItems_0_0value as GridItemAlignment | undefined));
                    this._alignItems_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._alignItems_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._alignItems_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAlignItemsAttribute((undefined as GridItemAlignment | undefined));
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
    mergeModifier(modifier: GridModifier): void {
        super.mergeModifier(modifier)
        if (modifier._columnsTemplate_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._columnsTemplate_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.columnsTemplate(modifier._columnsTemplate_0_0value);
                    break;
                }
                default: {
                    this.columnsTemplate((undefined as string | undefined));
                }
            }
        }
        if (modifier._rowsTemplate_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._rowsTemplate_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.rowsTemplate(modifier._rowsTemplate_0_0value);
                    break;
                }
                default: {
                    this.rowsTemplate((undefined as string | undefined));
                }
            }
        }
        if (modifier._columnsGap_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._columnsGap_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.columnsGap(modifier._columnsGap_0_0value);
                    break;
                }
                default: {
                    this.columnsGap((undefined as Length | undefined));
                }
            }
        }
        if (modifier._rowsGap_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._rowsGap_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.rowsGap(modifier._rowsGap_0_0value);
                    break;
                }
                default: {
                    this.rowsGap((undefined as Length | undefined));
                }
            }
        }
        if (modifier._onScrollBarUpdate_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onScrollBarUpdate_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onScrollBarUpdate(modifier._onScrollBarUpdate_0_0value);
                    break;
                }
                default: {
                    this.onScrollBarUpdate((undefined as ((index: number,offset: number) => ComputedBarAttribute) | undefined));
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
                    this.onScrollIndex((undefined as ((first: number,last: number) => void) | undefined));
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
        if (modifier._editMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._editMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.editMode(modifier._editMode_0_0value);
                    break;
                }
                default: {
                    this.editMode((undefined as boolean | undefined));
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
        if (modifier._maxCount_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._maxCount_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.maxCount(modifier._maxCount_0_0value);
                    break;
                }
                default: {
                    this.maxCount((undefined as number | undefined));
                }
            }
        }
        if (modifier._minCount_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._minCount_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.minCount(modifier._minCount_0_0value);
                    break;
                }
                default: {
                    this.minCount((undefined as number | undefined));
                }
            }
        }
        if (modifier._cellLength_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._cellLength_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.cellLength(modifier._cellLength_0_0value);
                    break;
                }
                default: {
                    this.cellLength((undefined as number | undefined));
                }
            }
        }
        if (modifier._layoutDirection_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._layoutDirection_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.layoutDirection(modifier._layoutDirection_0_0value);
                    break;
                }
                default: {
                    this.layoutDirection((undefined as GridDirection | undefined));
                }
            }
        }
        if (modifier._supportAnimation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._supportAnimation_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.supportAnimation(modifier._supportAnimation_0_0value);
                    break;
                }
                default: {
                    this.supportAnimation((undefined as boolean | undefined));
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
        if (modifier._alignItems_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._alignItems_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.alignItems(modifier._alignItems_0_0value);
                    break;
                }
                default: {
                    this.alignItems((undefined as GridItemAlignment | undefined));
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
    columnsTemplate(value: string | undefined): this {
        if (((this._columnsTemplate_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._columnsTemplate_0_0value) !== (value)))
        {
            this._columnsTemplate_0_flag = AttributeUpdaterFlag.UPDATE
            this._columnsTemplate_0_0value = value
        } else
        {
            this._columnsTemplate_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    rowsTemplate(value: string | undefined): this {
        if (((this._rowsTemplate_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._rowsTemplate_0_0value) !== (value)))
        {
            this._rowsTemplate_0_flag = AttributeUpdaterFlag.UPDATE
            this._rowsTemplate_0_0value = value
        } else
        {
            this._rowsTemplate_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    columnsGap(value: Length | undefined): this {
        if (((this._columnsGap_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._columnsGap_0_flag = AttributeUpdaterFlag.UPDATE
            this._columnsGap_0_0value = value
        } else
        {
            this._columnsGap_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    rowsGap(value: Length | undefined): this {
        if (((this._rowsGap_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._rowsGap_0_flag = AttributeUpdaterFlag.UPDATE
            this._rowsGap_0_0value = value
        } else
        {
            this._rowsGap_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onScrollBarUpdate(value: ((index: number,offset: number) => ComputedBarAttribute) | undefined): this {
        if (((this._onScrollBarUpdate_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onScrollBarUpdate_0_flag = AttributeUpdaterFlag.UPDATE
            this._onScrollBarUpdate_0_0value = value
        } else
        {
            this._onScrollBarUpdate_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onScrollIndex(value: ((first: number,last: number) => void) | undefined): this {
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
    editMode(value: boolean | undefined): this {
        if (((this._editMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._editMode_0_0value) !== (value)))
        {
            this._editMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._editMode_0_0value = value
        } else
        {
            this._editMode_0_flag = AttributeUpdaterFlag.SKIP
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
    maxCount(value: number | undefined): this {
        if (((this._maxCount_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._maxCount_0_0value) !== (value)))
        {
            this._maxCount_0_flag = AttributeUpdaterFlag.UPDATE
            this._maxCount_0_0value = value
        } else
        {
            this._maxCount_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    minCount(value: number | undefined): this {
        if (((this._minCount_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._minCount_0_0value) !== (value)))
        {
            this._minCount_0_flag = AttributeUpdaterFlag.UPDATE
            this._minCount_0_0value = value
        } else
        {
            this._minCount_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    cellLength(value: number | undefined): this {
        if (((this._cellLength_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._cellLength_0_0value) !== (value)))
        {
            this._cellLength_0_flag = AttributeUpdaterFlag.UPDATE
            this._cellLength_0_0value = value
        } else
        {
            this._cellLength_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    layoutDirection(value: GridDirection | undefined): this {
        if (((this._layoutDirection_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._layoutDirection_0_flag = AttributeUpdaterFlag.UPDATE
            this._layoutDirection_0_0value = value
        } else
        {
            this._layoutDirection_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    supportAnimation(value: boolean | undefined): this {
        if (((this._supportAnimation_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._supportAnimation_0_0value) !== (value)))
        {
            this._supportAnimation_0_flag = AttributeUpdaterFlag.UPDATE
            this._supportAnimation_0_0value = value
        } else
        {
            this._supportAnimation_0_flag = AttributeUpdaterFlag.SKIP
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
    alignItems(value: GridItemAlignment | undefined): this {
        if (((this._alignItems_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._alignItems_0_flag = AttributeUpdaterFlag.UPDATE
            this._alignItems_0_0value = value
        } else
        {
            this._alignItems_0_flag = AttributeUpdaterFlag.SKIP
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
    public attributeModifier(value: AttributeModifier<GridAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class ComputedBarAttribute_serializer {
    public static write(buffer: SerializerBase, value: ComputedBarAttribute): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTotalOffset  = value.totalOffset
        valueSerializer.writeNumber(valueHolderForTotalOffset)
        const valueHolderForTotalLength  = value.totalLength
        valueSerializer.writeNumber(valueHolderForTotalLength)
    }
    public static read(buffer: DeserializerBase): ComputedBarAttribute {
        let valueDeserializer : DeserializerBase = buffer
        const totalOffsetTmpResult : number = (valueDeserializer.readNumber() as number)
        const totalLengthTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : ComputedBarAttribute = ({totalOffset: totalOffsetTmpResult, totalLength: totalLengthTmpResult} as ComputedBarAttribute)
        return value
    }
}
export class GridLayoutOptions_serializer {
    public static write(buffer: SerializerBase, value: GridLayoutOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForRegularSize  = value.regularSize
        const valueHolderForRegularSize_0  = valueHolderForRegularSize[0]
        valueSerializer.writeNumber(valueHolderForRegularSize_0)
        const valueHolderForRegularSize_1  = valueHolderForRegularSize[1]
        valueSerializer.writeNumber(valueHolderForRegularSize_1)
        const valueHolderForIrregularIndexes  = value.irregularIndexes
        if (valueHolderForIrregularIndexes !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIrregularIndexesTmpValue  = valueHolderForIrregularIndexes!
            valueSerializer.writeInt32((valueHolderForIrregularIndexesTmpValue.length).toInt())
            for (let valueHolderForIrregularIndexesTmpValueCounterI = 0; valueHolderForIrregularIndexesTmpValueCounterI < valueHolderForIrregularIndexesTmpValue.length; valueHolderForIrregularIndexesTmpValueCounterI++) {
                const valueHolderForIrregularIndexesTmpValueTmpElement : number = valueHolderForIrregularIndexesTmpValue[valueHolderForIrregularIndexesTmpValueCounterI]
                valueSerializer.writeNumber(valueHolderForIrregularIndexesTmpValueTmpElement)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnGetIrregularSizeByIndex  = value.onGetIrregularSizeByIndex
        if (valueHolderForOnGetIrregularSizeByIndex !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnGetIrregularSizeByIndexTmpValue  = valueHolderForOnGetIrregularSizeByIndex!
            valueSerializer.holdAndWriteCallback(valueHolderForOnGetIrregularSizeByIndexTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnGetRectByIndex  = value.onGetRectByIndex
        if (valueHolderForOnGetRectByIndex !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnGetRectByIndexTmpValue  = valueHolderForOnGetRectByIndex!
            valueSerializer.holdAndWriteCallback(valueHolderForOnGetRectByIndexTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): GridLayoutOptions {
        let valueDeserializer : DeserializerBase = buffer
        const regularSizeTmpBufValue0 : number = (valueDeserializer.readNumber() as number)
        const regularSizeTmpBufValue1 : number = (valueDeserializer.readNumber() as number)
        const regularSizeTmpResult : [ number, number ] = ([regularSizeTmpBufValue0, regularSizeTmpBufValue1] as [ number, number ])
        const irregularIndexesTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let irregularIndexesTmpBuf : Array<number> | undefined
        if ((irregularIndexesTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const irregularIndexesTmpBuf_Length : int32 = valueDeserializer.readInt32()
            let irregularIndexesTmpBuf_ : Array<number> = new Array<number>(irregularIndexesTmpBuf_Length)
            for (let irregularIndexesTmpBuf_BufCounterI = 0; irregularIndexesTmpBuf_BufCounterI < irregularIndexesTmpBuf_Length; irregularIndexesTmpBuf_BufCounterI++) {
                irregularIndexesTmpBuf_[irregularIndexesTmpBuf_BufCounterI] = (valueDeserializer.readNumber() as number)
            }
            irregularIndexesTmpBuf = irregularIndexesTmpBuf_
        }
        const irregularIndexesTmpResult : Array<number> | undefined = irregularIndexesTmpBuf
        const onGetIrregularSizeByIndexTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onGetIrregularSizeByIndexTmpBuf : ((index: number) => [ number, number ]) | undefined
        if ((onGetIrregularSizeByIndexTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onGetIrregularSizeByIndexTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onGetIrregularSizeByIndexTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onGetIrregularSizeByIndexTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onGetIrregularSizeByIndexTmpBuf = (index: number):[ number, number ] => {
                const onGetIrregularSizeByIndexTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onGetIrregularSizeByIndexTmpBuf_BufArgsSerializer.writeInt32(onGetIrregularSizeByIndexTmpBuf_BufResource.resourceId);
                onGetIrregularSizeByIndexTmpBuf_BufArgsSerializer.writePointer(onGetIrregularSizeByIndexTmpBuf_BufCall);
                onGetIrregularSizeByIndexTmpBuf_BufArgsSerializer.writePointer(onGetIrregularSizeByIndexTmpBuf_BufCallSync);
                onGetIrregularSizeByIndexTmpBuf_BufArgsSerializer.writeNumber(index);
                let onGetIrregularSizeByIndexTmpBuf_BufContinuationValue : [ number, number ] | undefined;
                const onGetIrregularSizeByIndexTmpBuf_BufContinuationCallback : ((value: [ number, number ]) => void) = (value: [ number, number ]):void => {
                onGetIrregularSizeByIndexTmpBuf_BufContinuationValue = value;
            }
                onGetIrregularSizeByIndexTmpBuf_BufArgsSerializer.holdAndWriteCallback(onGetIrregularSizeByIndexTmpBuf_BufContinuationCallback);
                InteropNativeModule._CallCallback(1602877440, onGetIrregularSizeByIndexTmpBuf_BufArgsSerializer.asBuffer(), onGetIrregularSizeByIndexTmpBuf_BufArgsSerializer.length());
                onGetIrregularSizeByIndexTmpBuf_BufArgsSerializer.release();
                return (onGetIrregularSizeByIndexTmpBuf_BufContinuationValue as [ number, number ]);
            }
        }
        const onGetIrregularSizeByIndexTmpResult : ((index: number) => [ number, number ]) | undefined = onGetIrregularSizeByIndexTmpBuf
        const onGetRectByIndexTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onGetRectByIndexTmpBuf : ((index: number) => [ number, number, number, number ]) | undefined
        if ((onGetRectByIndexTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onGetRectByIndexTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onGetRectByIndexTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onGetRectByIndexTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onGetRectByIndexTmpBuf = (index: number):[ number, number, number, number ] => {
                const onGetRectByIndexTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onGetRectByIndexTmpBuf_BufArgsSerializer.writeInt32(onGetRectByIndexTmpBuf_BufResource.resourceId);
                onGetRectByIndexTmpBuf_BufArgsSerializer.writePointer(onGetRectByIndexTmpBuf_BufCall);
                onGetRectByIndexTmpBuf_BufArgsSerializer.writePointer(onGetRectByIndexTmpBuf_BufCallSync);
                onGetRectByIndexTmpBuf_BufArgsSerializer.writeNumber(index);
                let onGetRectByIndexTmpBuf_BufContinuationValue : [ number, number, number, number ] | undefined;
                const onGetRectByIndexTmpBuf_BufContinuationCallback : ((value: [ number, number, number, number ]) => void) = (value: [ number, number, number, number ]):void => {
                onGetRectByIndexTmpBuf_BufContinuationValue = value;
            }
                onGetRectByIndexTmpBuf_BufArgsSerializer.holdAndWriteCallback(onGetRectByIndexTmpBuf_BufContinuationCallback);
                InteropNativeModule._CallCallback(1618565120, onGetRectByIndexTmpBuf_BufArgsSerializer.asBuffer(), onGetRectByIndexTmpBuf_BufArgsSerializer.length());
                onGetRectByIndexTmpBuf_BufArgsSerializer.release();
                return (onGetRectByIndexTmpBuf_BufContinuationValue as [ number, number, number, number ]);
            }
        }
        const onGetRectByIndexTmpResult : ((index: number) => [ number, number, number, number ]) | undefined = onGetRectByIndexTmpBuf
        let value : GridLayoutOptions = ({regularSize: regularSizeTmpResult, irregularIndexes: irregularIndexesTmpResult, onGetIrregularSizeByIndex: onGetIrregularSizeByIndexTmpResult, onGetRectByIndex: onGetRectByIndexTmpResult} as GridLayoutOptions)
        return value
    }
}

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
import { Resource_serializer, Resource } from "./resource"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkScrollableCommonMethodPeer, ScrollableCommonMethod, OnItemDragStartCallback, ItemDragInfo, OnWillScrollCallback, OnScrollCallback, CommonMethod, ArkScrollableCommonMethodComponent, ArkScrollableCommonMethodStyle, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { Length } from "./units"
import { ScrollState } from "./list"
import { ScrollSource } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
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
        thisSerializer.writeInt8(scroller_type)
        if ((RuntimeType.UNDEFINED) != (scroller_type)) {
            const scroller_value  = scroller!
            Scroller_serializer.write(thisSerializer, scroller_value)
        }
        let layoutOptions_type : int32 = RuntimeType.UNDEFINED
        layoutOptions_type = runtimeType(layoutOptions)
        thisSerializer.writeInt8(layoutOptions_type)
        if ((RuntimeType.UNDEFINED) != (layoutOptions_type)) {
            const layoutOptions_value  = layoutOptions!
            GridLayoutOptions_serializer.write(thisSerializer, layoutOptions_value)
        }
        ArkUIGeneratedNativeModule._GridInterface_setGridOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    columnsTemplateAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_columnsTemplate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    rowsTemplateAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_rowsTemplate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    columnsGapAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._GridAttribute_columnsGap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    rowsGapAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._GridAttribute_rowsGap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollBarUpdateAttribute(value: ((index: number,offset: number) => ComputedBarAttribute) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_onScrollBarUpdate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollIndexAttribute(value: ((first: number,last: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_onScrollIndex(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    cachedCount0Attribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_cachedCount0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    cachedCount1Attribute(count: number | undefined, show: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let count_type : int32 = RuntimeType.UNDEFINED
        count_type = runtimeType(count)
        thisSerializer.writeInt8(count_type)
        if ((RuntimeType.UNDEFINED) != (count_type)) {
            const count_value  = count!
            thisSerializer.writeNumber(count_value)
        }
        let show_type : int32 = RuntimeType.UNDEFINED
        show_type = runtimeType(show)
        thisSerializer.writeInt8(show_type)
        if ((RuntimeType.UNDEFINED) != (show_type)) {
            const show_value  = show!
            thisSerializer.writeBoolean(show_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_cachedCount1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    editModeAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_editMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    multiSelectableAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_multiSelectable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    maxCountAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_maxCount(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    minCountAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_minCount(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    cellLengthAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_cellLength(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    layoutDirectionAttribute(value: GridDirection | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as GridDirection)
            thisSerializer.writeInt32(TypeChecker.GridDirection_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._GridAttribute_layoutDirection(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    supportAnimationAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_supportAnimation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDragStartAttribute(value: OnItemDragStartCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_onItemDragStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDragEnterAttribute(value: ((event: ItemDragInfo) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_onItemDragEnter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDragMoveAttribute(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_onItemDragMove(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDragLeaveAttribute(value: ((event: ItemDragInfo,itemIndex: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_onItemDragLeave(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDropAttribute(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_onItemDrop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    alignItemsAttribute(value: GridItemAlignment | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as GridItemAlignment)
            thisSerializer.writeInt32(TypeChecker.GridItemAlignment_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._GridAttribute_alignItems(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollFrameBeginAttribute(value: OnScrollFrameBeginCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_onScrollFrameBegin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillScrollAttribute(value: OnWillScrollCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_onWillScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDidScrollAttribute(value: OnScrollCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_onDidScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    columnsTemplate(value: string | undefined): this
    rowsTemplate(value: string | undefined): this
    columnsGap(value: Length | undefined): this
    rowsGap(value: Length | undefined): this
    onScrollBarUpdate(value: ((index: number,offset: number) => ComputedBarAttribute) | undefined): this
    onScrollIndex(value: ((first: number,last: number) => void) | undefined): this
    cachedCount(count: number | undefined, show?: boolean): this
    editMode(value: boolean | undefined): this
    multiSelectable(value: boolean | undefined): this
    maxCount(value: number | undefined): this
    minCount(value: number | undefined): this
    cellLength(value: number | undefined): this
    layoutDirection(value: GridDirection | undefined): this
    supportAnimation(value: boolean | undefined): this
    onItemDragStart(value: OnItemDragStartCallback | undefined): this
    onItemDragEnter(value: ((event: ItemDragInfo) => void) | undefined): this
    onItemDragMove(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void) | undefined): this
    onItemDragLeave(value: ((event: ItemDragInfo,itemIndex: number) => void) | undefined): this
    onItemDrop(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void) | undefined): this
    alignItems(value: GridItemAlignment | undefined): this
    onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this
    onWillScroll(value: OnWillScrollCallback | undefined): this
    onDidScroll(value: OnScrollCallback | undefined): this
    attributeModifier(value: AttributeModifier<GridAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this
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
    public cachedCount(count: number | undefined, show?: boolean): this {
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
            this.getPeer()?.columnsTemplateAttribute(value_casted)
            return this
        }
        return this
    }
    public rowsTemplate(value: string | undefined): this {
        if (this.checkPriority("rowsTemplate")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.rowsTemplateAttribute(value_casted)
            return this
        }
        return this
    }
    public columnsGap(value: Length | undefined): this {
        if (this.checkPriority("columnsGap")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.columnsGapAttribute(value_casted)
            return this
        }
        return this
    }
    public rowsGap(value: Length | undefined): this {
        if (this.checkPriority("rowsGap")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.rowsGapAttribute(value_casted)
            return this
        }
        return this
    }
    public onScrollBarUpdate(value: ((index: number,offset: number) => ComputedBarAttribute) | undefined): this {
        if (this.checkPriority("onScrollBarUpdate")) {
            const value_casted = value as (((index: number,offset: number) => ComputedBarAttribute) | undefined)
            this.getPeer()?.onScrollBarUpdateAttribute(value_casted)
            return this
        }
        return this
    }
    public onScrollIndex(value: ((first: number,last: number) => void) | undefined): this {
        if (this.checkPriority("onScrollIndex")) {
            const value_casted = value as (((first: number,last: number) => void) | undefined)
            this.getPeer()?.onScrollIndexAttribute(value_casted)
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
    public maxCount(value: number | undefined): this {
        if (this.checkPriority("maxCount")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.maxCountAttribute(value_casted)
            return this
        }
        return this
    }
    public minCount(value: number | undefined): this {
        if (this.checkPriority("minCount")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.minCountAttribute(value_casted)
            return this
        }
        return this
    }
    public cellLength(value: number | undefined): this {
        if (this.checkPriority("cellLength")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.cellLengthAttribute(value_casted)
            return this
        }
        return this
    }
    public layoutDirection(value: GridDirection | undefined): this {
        if (this.checkPriority("layoutDirection")) {
            const value_casted = value as (GridDirection | undefined)
            this.getPeer()?.layoutDirectionAttribute(value_casted)
            return this
        }
        return this
    }
    public supportAnimation(value: boolean | undefined): this {
        if (this.checkPriority("supportAnimation")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.supportAnimationAttribute(value_casted)
            return this
        }
        return this
    }
    public onItemDragStart(value: OnItemDragStartCallback | undefined): this {
        if (this.checkPriority("onItemDragStart")) {
            const value_casted = value as (OnItemDragStartCallback | undefined)
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
    public alignItems(value: GridItemAlignment | undefined): this {
        if (this.checkPriority("alignItems")) {
            const value_casted = value as (GridItemAlignment | undefined)
            this.getPeer()?.alignItemsAttribute(value_casted)
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
    public onWillScroll(value: OnWillScrollCallback | undefined): this {
        if (this.checkPriority("onWillScroll")) {
            const value_casted = value as (OnWillScrollCallback | undefined)
            this.getPeer()?.onWillScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public onDidScroll(value: OnScrollCallback | undefined): this {
        if (this.checkPriority("onDidScroll")) {
            const value_casted = value as (OnScrollCallback | undefined)
            this.getPeer()?.onDidScrollAttribute(value_casted)
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
        if (modifier!.isUpdater)
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
@memo
@BuilderLambda("GridImpl")
export function Grid(
    scroller?: Scroller | undefined, layoutOptions?: GridLayoutOptions | undefined,
    @memo
    content_?: () => void,
): GridAttribute {
    throw new Error("Not implemented")
}

@memo
export function GridImpl(
    @memo
    style: ((attributes: GridAttribute) => void) | undefined,
    scroller?: Scroller | undefined, layoutOptions?: GridLayoutOptions | undefined,
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
        valueSerializer.writeInt8(value_irregularIndexes_type)
        if ((RuntimeType.UNDEFINED) != (value_irregularIndexes_type)) {
            const value_irregularIndexes_value  = value_irregularIndexes!
            valueSerializer.writeInt32(value_irregularIndexes_value.length as int32)
            for (let i = 0; i < value_irregularIndexes_value.length; i++) {
                const value_irregularIndexes_value_element : number = value_irregularIndexes_value[i]
                valueSerializer.writeNumber(value_irregularIndexes_value_element)
            }
        }
        const value_onGetIrregularSizeByIndex  = value.onGetIrregularSizeByIndex
        let value_onGetIrregularSizeByIndex_type : int32 = RuntimeType.UNDEFINED
        value_onGetIrregularSizeByIndex_type = runtimeType(value_onGetIrregularSizeByIndex)
        valueSerializer.writeInt8(value_onGetIrregularSizeByIndex_type)
        if ((RuntimeType.UNDEFINED) != (value_onGetIrregularSizeByIndex_type)) {
            const value_onGetIrregularSizeByIndex_value  = value_onGetIrregularSizeByIndex!
            valueSerializer.holdAndWriteCallback(value_onGetIrregularSizeByIndex_value)
        }
        const value_onGetRectByIndex  = value.onGetRectByIndex
        let value_onGetRectByIndex_type : int32 = RuntimeType.UNDEFINED
        value_onGetRectByIndex_type = runtimeType(value_onGetRectByIndex)
        valueSerializer.writeInt8(value_onGetRectByIndex_type)
        if ((RuntimeType.UNDEFINED) != (value_onGetRectByIndex_type)) {
            const value_onGetRectByIndex_value  = value_onGetRectByIndex!
            valueSerializer.holdAndWriteCallback(value_onGetRectByIndex_value)
        }
    }
    public static read(buffer: DeserializerBase): GridLayoutOptions {
        let valueDeserializer : DeserializerBase = buffer
        const regularSize_buf_value0 : number = (valueDeserializer.readNumber() as number)
        const regularSize_buf_value1 : number = (valueDeserializer.readNumber() as number)
        const regularSize_result : [ number, number ] = ([regularSize_buf_value0, regularSize_buf_value1] as [ number, number ])
        const irregularIndexes_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let irregularIndexes_buf : Array<number> | undefined
        if ((RuntimeType.UNDEFINED) != (irregularIndexes_buf_runtimeType))
        {
            const irregularIndexes_buf__length : int32 = valueDeserializer.readInt32()
            let irregularIndexes_buf_ : Array<number> = new Array<number>(irregularIndexes_buf__length)
            for (let irregularIndexes_buf__i = 0; irregularIndexes_buf__i < irregularIndexes_buf__length; irregularIndexes_buf__i++) {
                irregularIndexes_buf_[irregularIndexes_buf__i] = (valueDeserializer.readNumber() as number)
            }
            irregularIndexes_buf = irregularIndexes_buf_
        }
        const irregularIndexes_result : Array<number> | undefined = irregularIndexes_buf
        const onGetIrregularSizeByIndex_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let onGetIrregularSizeByIndex_buf : ((index: number) => [ number, number ]) | undefined
        if ((RuntimeType.UNDEFINED) != (onGetIrregularSizeByIndex_buf_runtimeType))
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
        const onGetRectByIndex_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let onGetRectByIndex_buf : ((index: number) => [ number, number, number, number ]) | undefined
        if ((RuntimeType.UNDEFINED) != (onGetRectByIndex_buf_runtimeType))
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

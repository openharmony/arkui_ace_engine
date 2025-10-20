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
import { Resource_serializer } from "./../framework/resource"
import { NestedScrollOptions_serializer, EdgeEffectOptions_serializer, ArkScrollableCommonMethodPeer, ScrollableCommonMethod, OnItemDragStartCallback, ItemDragInfo, NestedScrollOptions, OnWillScrollCallback, OnScrollCallback, CommonMethod, EdgeEffectOptions, ArkScrollableCommonMethodComponent, ArkScrollableCommonMethodStyle, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { Length } from "./units"
import { Resource } from "global.resource"
import { Color, BarState, ScrollSource, EdgeEffect } from "./enums"
import { ScrollState } from "./list"
import { AttributeModifier, hookGridAttributeModifier, AttributeUpdater } from "#handwritten"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { GridModifier } from "./../GridModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkGridPeer extends ArkScrollableCommonMethodPeer {
    attributeSet?: GridModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
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
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
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
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setRowsGap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setScrollBarWidthAttribute(value: number | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setScrollBarWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setScrollBarColorAttribute(value: Color | number | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setScrollBarColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setScrollBarAttribute(value: BarState | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as BarState)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setScrollBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
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
    setNestedScrollAttribute(value: NestedScrollOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            NestedScrollOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setNestedScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableScrollInteractionAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setEnableScrollInteraction(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFrictionAttribute(value: number | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setFriction(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAlignItemsAttribute(value: GridItemAlignment | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as GridItemAlignment)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
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
    setEdgeEffectAttribute(value: EdgeEffect | undefined, options?: EdgeEffectOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as EdgeEffect)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            EdgeEffectOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setEdgeEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    setGridOptions(scroller?: Scroller, layoutOptions?: GridLayoutOptions): this {
        throw new Error("Unimplemented method setGridOptions")
    }
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
    scrollBarWidth(value: number | string | undefined): this
    scrollBarColor(value: Color | number | string | undefined): this
    scrollBar(value: BarState | undefined): this
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
    nestedScroll(value: NestedScrollOptions | undefined): this
    enableScrollInteraction(value: boolean | undefined): this
    friction(value: number | Resource | undefined): this
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
    edgeEffect(value: EdgeEffect | undefined, options?: EdgeEffectOptions): this {
        throw new Error("Unimplemented method edgeEffect")
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
    scrollBarWidth_value?: number | string | undefined
    scrollBarColor_value?: Color | number | string | undefined
    scrollBar_value?: BarState | undefined
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
    nestedScroll_value?: NestedScrollOptions | undefined
    enableScrollInteraction_value?: boolean | undefined
    friction_value?: number | Resource | undefined
    alignItems_value?: GridItemAlignment | undefined
    onScrollFrameBegin_value?: OnScrollFrameBeginCallback | undefined
    onWillScroll_value?: OnWillScrollCallback | undefined
    onDidScroll_value?: OnScrollCallback | undefined
    attributeModifier_value?: AttributeModifier<GridAttribute> | AttributeModifier<CommonMethod> | undefined
    setGridOptions(scroller?: Scroller, layoutOptions?: GridLayoutOptions): this {
        return this
    }
    columnsTemplate(value: string | undefined): this {
        return this
    }
    rowsTemplate(value: string | undefined): this {
        return this
    }
    columnsGap(value: Length | undefined): this {
        return this
    }
    rowsGap(value: Length | undefined): this {
        return this
    }
    scrollBarWidth(value: number | string | undefined): this {
        return this
    }
    scrollBarColor(value: Color | number | string | undefined): this {
        return this
    }
    scrollBar(value: BarState | undefined): this {
        return this
    }
    onScrollBarUpdate(value: ((index: number,offset: number) => ComputedBarAttribute) | undefined): this {
        return this
    }
    onScrollIndex(value: ((first: number,last: number) => void) | undefined): this {
        return this
    }
    cachedCount(value: number | undefined): this {
        return this
    }
    editMode(value: boolean | undefined): this {
        return this
    }
    multiSelectable(value: boolean | undefined): this {
        return this
    }
    maxCount(value: number | undefined): this {
        return this
    }
    minCount(value: number | undefined): this {
        return this
    }
    cellLength(value: number | undefined): this {
        return this
    }
    layoutDirection(value: GridDirection | undefined): this {
        return this
    }
    supportAnimation(value: boolean | undefined): this {
        return this
    }
    onItemDragStart(value: OnItemDragStartCallback | undefined): this {
        return this
    }
    onItemDragEnter(value: ((event: ItemDragInfo) => void) | undefined): this {
        return this
    }
    onItemDragMove(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void) | undefined): this {
        return this
    }
    onItemDragLeave(value: ((event: ItemDragInfo,itemIndex: number) => void) | undefined): this {
        return this
    }
    onItemDrop(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void) | undefined): this {
        return this
    }
    nestedScroll(value: NestedScrollOptions | undefined): this {
        return this
    }
    enableScrollInteraction(value: boolean | undefined): this {
        return this
    }
    friction(value: number | Resource | undefined): this {
        return this
    }
    alignItems(value: GridItemAlignment | undefined): this {
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
    cachedCount(count: number | undefined, show: boolean | undefined): this {
        return this
    }
    edgeEffect(value: EdgeEffect | undefined, options?: EdgeEffectOptions): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<GridAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkGridComponent extends ArkScrollableCommonMethodComponent implements GridAttribute {
    getPeer(): ArkGridPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkGridPeer)
    }
    public setGridOptions(scroller?: Scroller, layoutOptions?: GridLayoutOptions): this {
        if (this.checkPriority("setGridOptions")) {
            const scroller_casted = scroller as (Scroller | undefined)
            const layoutOptions_casted = layoutOptions as (GridLayoutOptions | undefined)
            this.getPeer()?.setGridOptionsAttribute(scroller_casted, layoutOptions_casted)
            this.applyOptionsFinish('GridAttribute');
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
    public scrollBarWidth(value: number | string | undefined): this {
        if (this.checkPriority("scrollBarWidth")) {
            const value_casted = value as (number | string | undefined)
            this.getPeer()?.setScrollBarWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public scrollBarColor(value: Color | number | string | undefined): this {
        if (this.checkPriority("scrollBarColor")) {
            const value_casted = value as (Color | number | string | undefined)
            this.getPeer()?.setScrollBarColorAttribute(value_casted)
            return this
        }
        return this
    }
    public scrollBar(value: BarState | undefined): this {
        if (this.checkPriority("scrollBar")) {
            const value_casted = value as (BarState | undefined)
            this.getPeer()?.setScrollBarAttribute(value_casted)
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
    public nestedScroll(value: NestedScrollOptions | undefined): this {
        if (this.checkPriority("nestedScroll")) {
            const value_casted = value as (NestedScrollOptions | undefined)
            this.getPeer()?.setNestedScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public enableScrollInteraction(value: boolean | undefined): this {
        if (this.checkPriority("enableScrollInteraction")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableScrollInteractionAttribute(value_casted)
            return this
        }
        return this
    }
    public friction(value: number | Resource | undefined): this {
        if (this.checkPriority("friction")) {
            const value_casted = value as (number | Resource | undefined)
            this.getPeer()?.setFrictionAttribute(value_casted)
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
    public edgeEffect(value: EdgeEffect | undefined, options?: EdgeEffectOptions): this {
        if (this.checkPriority("edgeEffect")) {
            const value_casted = value as (EdgeEffect | undefined)
            const options_casted = options as (EdgeEffectOptions | undefined)
            this.getPeer()?.setEdgeEffectAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<GridAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        hookGridAttributeModifier(this, value);
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
export function GridImpl(
    @memo
    style: ((attributes: GridAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkGridComponent>((): ArkGridComponent => {
        return new ArkGridComponent()
    })
    NodeAttach<ArkGridPeer>((): ArkGridPeer => ArkGridPeer.create(receiver), (peer: ArkGridPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
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
        let irregularIndexesTmpBuf : Array<number> | undefined = undefined
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
        let onGetIrregularSizeByIndexTmpBuf : ((index: number) => [ number, number ]) | undefined = undefined
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
                InteropNativeModule._CallCallbackSync(10, 1602877440, onGetIrregularSizeByIndexTmpBuf_BufArgsSerializer.asBuffer(), onGetIrregularSizeByIndexTmpBuf_BufArgsSerializer.length());
                onGetIrregularSizeByIndexTmpBuf_BufArgsSerializer.release();
                return (onGetIrregularSizeByIndexTmpBuf_BufContinuationValue as [ number, number ]);
            }
        }
        const onGetIrregularSizeByIndexTmpResult : ((index: number) => [ number, number ]) | undefined = onGetIrregularSizeByIndexTmpBuf
        const onGetRectByIndexTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onGetRectByIndexTmpBuf : ((index: number) => [ number, number, number, number ]) | undefined = undefined
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
                InteropNativeModule._CallCallbackSync(10, 1618565120, onGetRectByIndexTmpBuf_BufArgsSerializer.asBuffer(), onGetRectByIndexTmpBuf_BufArgsSerializer.length());
                onGetRectByIndexTmpBuf_BufArgsSerializer.release();
                return (onGetRectByIndexTmpBuf_BufContinuationValue as [ number, number, number, number ]);
            }
        }
        const onGetRectByIndexTmpResult : ((index: number) => [ number, number, number, number ]) | undefined = onGetRectByIndexTmpBuf
        let value : GridLayoutOptions = ({regularSize: regularSizeTmpResult, irregularIndexes: irregularIndexesTmpResult, onGetIrregularSizeByIndex: onGetIrregularSizeByIndexTmpResult, onGetRectByIndex: onGetRectByIndexTmpResult} as GridLayoutOptions)
        return value
    }
}

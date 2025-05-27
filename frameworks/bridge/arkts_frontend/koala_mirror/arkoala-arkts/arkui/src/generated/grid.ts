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

import { int32, int64, float32 } from "@koalaui/common"
import { nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer } from "@koalaui/interop"
import { Serializer } from "./peers/Serializer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkScrollableCommonMethodPeer, ScrollableCommonMethod, ItemDragInfo, CustomBuilder, NestedScrollOptions, EdgeEffectOptions, ArkScrollableCommonMethodComponent, ArkScrollableCommonMethodStyle, UIScrollableCommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethod, UICommonMethod } from "./common"
import { Length } from "./units"
import { Color, BarState, EdgeEffect } from "./enums"
import { GridAttribute_onItemDragStart_event_type } from "./type-replacements"
import { Resource } from "./resource"
import { Callback_Void } from "./ability_component"
import { ScrollState } from "./list"
import { Scroller } from "./scroll"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { Tuple_Number_Number } from "./arkui-synthetics"
import { UICommonBase, AttributeModifier } from "./../handwritten"
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
        const thisSerializer : Serializer = Serializer.hold()
        let scroller_type : int32 = RuntimeType.UNDEFINED
        scroller_type = runtimeType(scroller)
        thisSerializer.writeInt8(scroller_type as int32)
        if ((RuntimeType.UNDEFINED) != (scroller_type)) {
            const scroller_value  = scroller!
            thisSerializer.writeScroller(scroller_value)
        }
        let layoutOptions_type : int32 = RuntimeType.UNDEFINED
        layoutOptions_type = runtimeType(layoutOptions)
        thisSerializer.writeInt8(layoutOptions_type as int32)
        if ((RuntimeType.UNDEFINED) != (layoutOptions_type)) {
            const layoutOptions_value  = layoutOptions!
            thisSerializer.writeGridLayoutOptions(layoutOptions_value)
        }
        ArkUIGeneratedNativeModule._GridInterface_setGridOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    columnsTemplateAttribute(value: string): void {
        ArkUIGeneratedNativeModule._GridAttribute_columnsTemplate(this.peer.ptr, value)
    }
    rowsTemplateAttribute(value: string): void {
        ArkUIGeneratedNativeModule._GridAttribute_rowsTemplate(this.peer.ptr, value)
    }
    columnsGapAttribute(value: Length): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._GridAttribute_columnsGap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    rowsGapAttribute(value: Length): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._GridAttribute_rowsGap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    scrollBarWidthAttribute(value: number | string): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        ArkUIGeneratedNativeModule._GridAttribute_scrollBarWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    scrollBarColorAttribute(value: Color | number | string): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        ArkUIGeneratedNativeModule._GridAttribute_scrollBarColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    scrollBarAttribute(value: BarState): void {
        ArkUIGeneratedNativeModule._GridAttribute_scrollBar(this.peer.ptr, TypeChecker.BarState_ToNumeric(value))
    }
    onScrollBarUpdateAttribute(value: ((index: number,offset: number) => ComputedBarAttribute)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._GridAttribute_onScrollBarUpdate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollIndexAttribute(value: ((first: number,last: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._GridAttribute_onScrollIndex(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    cachedCount0Attribute(value: number): void {
        ArkUIGeneratedNativeModule._GridAttribute_cachedCount0(this.peer.ptr, value)
    }
    cachedCount1Attribute(count: number, show: boolean): void {
        ArkUIGeneratedNativeModule._GridAttribute_cachedCount1(this.peer.ptr, count, show ? 1 : 0)
    }
    editModeAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._GridAttribute_editMode(this.peer.ptr, value ? 1 : 0)
    }
    multiSelectableAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._GridAttribute_multiSelectable(this.peer.ptr, value ? 1 : 0)
    }
    maxCountAttribute(value: number): void {
        ArkUIGeneratedNativeModule._GridAttribute_maxCount(this.peer.ptr, value)
    }
    minCountAttribute(value: number): void {
        ArkUIGeneratedNativeModule._GridAttribute_minCount(this.peer.ptr, value)
    }
    cellLengthAttribute(value: number): void {
        ArkUIGeneratedNativeModule._GridAttribute_cellLength(this.peer.ptr, value)
    }
    layoutDirectionAttribute(value: GridDirection): void {
        ArkUIGeneratedNativeModule._GridAttribute_layoutDirection(this.peer.ptr, TypeChecker.GridDirection_ToNumeric(value))
    }
    supportAnimationAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._GridAttribute_supportAnimation(this.peer.ptr, value ? 1 : 0)
    }
    onItemDragStartAttribute(value: ((event: ItemDragInfo,itemIndex: number) => CustomBuilder)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._GridAttribute_onItemDragStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDragEnterAttribute(value: ((event: ItemDragInfo) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._GridAttribute_onItemDragEnter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDragMoveAttribute(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._GridAttribute_onItemDragMove(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDragLeaveAttribute(value: ((event: ItemDragInfo,itemIndex: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._GridAttribute_onItemDragLeave(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDropAttribute(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._GridAttribute_onItemDrop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    nestedScrollAttribute(value: NestedScrollOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeNestedScrollOptions(value)
        ArkUIGeneratedNativeModule._GridAttribute_nestedScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableScrollInteractionAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._GridAttribute_enableScrollInteraction(this.peer.ptr, value ? 1 : 0)
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
        ArkUIGeneratedNativeModule._GridAttribute_friction(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    alignItemsAttribute(value: GridItemAlignment | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as GridItemAlignment)
            thisSerializer.writeInt32(TypeChecker.GridItemAlignment_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._GridAttribute_alignItems(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollAttribute(value: ((first: number,last: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._GridAttribute_onScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onReachStartAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._GridAttribute_onReachStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onReachEndAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._GridAttribute_onReachEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollStartAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._GridAttribute_onScrollStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollStopAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._GridAttribute_onScrollStop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollFrameBeginAttribute(value: ((offset: number,state: ScrollState) => Literal_Number_offsetRemain)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._GridAttribute_onScrollFrameBegin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_edgeEffect(this.peer.ptr, TypeChecker.EdgeEffect_ToNumeric(value), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type Callback_Number_Tuple_Number_Number = (index: number) => [ number, number ];
export type Tuple_Number_Number_Number_Number = [
    number,
    number,
    number,
    number
]
export type Callback_Number_Tuple_Number_Number_Number_Number = (index: number) => [ number, number, number, number ];
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
export type Callback_Number_Number_ComputedBarAttribute = (index: number, offset: number) => ComputedBarAttribute;
export type Callback_Number_Number_Void = (first: number, last: number) => void;
export type Callback_ItemDragInfo_Void = (event: ItemDragInfo) => void;
export type Callback_ItemDragInfo_Number_Number_Void = (event: ItemDragInfo, itemIndex: number, insertIndex: number) => void;
export type Callback_ItemDragInfo_Number_Void = (event: ItemDragInfo, itemIndex: number) => void;
export type Callback_ItemDragInfo_Number_Number_Boolean_Void = (event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void;
export interface Literal_Number_offsetRemain {
    offsetRemain: number;
}
export type Callback_Number_ScrollState_Literal_Number_offsetRemain = (offset: number, state: ScrollState) => Literal_Number_offsetRemain;
export interface GridAttribute extends ScrollableCommonMethod {
    columnsTemplate(value: string): this
    rowsTemplate(value: string): this
    columnsGap(value: Length): this
    rowsGap(value: Length): this
    scrollBarWidth(value: number | string): this
    scrollBarColor(value: Color | number | string): this
    scrollBar(value: BarState): this
    onScrollBarUpdate(value: ((index: number,offset: number) => ComputedBarAttribute)): this
    onScrollIndex(value: ((first: number,last: number) => void)): this
    cachedCount(count: number, show?: boolean): this
    editMode(value: boolean): this
    multiSelectable(value: boolean): this
    maxCount(value: number): this
    minCount(value: number): this
    cellLength(value: number): this
    layoutDirection(value: GridDirection): this
    supportAnimation(value: boolean): this
    onItemDragStart(value: ((event: ItemDragInfo,itemIndex: number) => CustomBuilder)): this
    onItemDragEnter(value: ((event: ItemDragInfo) => void)): this
    onItemDragMove(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void)): this
    onItemDragLeave(value: ((event: ItemDragInfo,itemIndex: number) => void)): this
    onItemDrop(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void)): this
    nestedScroll(value: NestedScrollOptions): this
    enableScrollInteraction(value: boolean): this
    friction(value: number | Resource): this
    alignItems(value: GridItemAlignment | undefined): this
    onScroll(value: ((first: number,last: number) => void)): this
    onReachStart(value: (() => void)): this
    onReachEnd(value: (() => void)): this
    onScrollStart(value: (() => void)): this
    onScrollStop(value: (() => void)): this
    onScrollFrameBegin(value: ((offset: number,state: ScrollState) => Literal_Number_offsetRemain)): this
    edgeEffect(value: EdgeEffect, options?: EdgeEffectOptions): this
    attributeModifier(value: AttributeModifier<GridAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIGridAttribute extends UIScrollableCommonMethod {
    /** @memo */
    columnsTemplate(value: string): this
    /** @memo */
    rowsTemplate(value: string): this
    /** @memo */
    columnsGap(value: Length): this
    /** @memo */
    rowsGap(value: Length): this
    /** @memo */
    scrollBarWidth(value: number | string): this
    /** @memo */
    scrollBarColor(value: Color | number | string): this
    /** @memo */
    scrollBar(value: BarState): this
    /** @memo */
    onScrollBarUpdate(value: ((index: number,offset: number) => ComputedBarAttribute)): this
    /** @memo */
    onScrollIndex(value: ((first: number,last: number) => void)): this
    /** @memo */
    cachedCount(count: number, show?: boolean): this
    /** @memo */
    editMode(value: boolean): this
    /** @memo */
    multiSelectable(value: boolean): this
    /** @memo */
    maxCount(value: number): this
    /** @memo */
    minCount(value: number): this
    /** @memo */
    cellLength(value: number): this
    /** @memo */
    layoutDirection(value: GridDirection): this
    /** @memo */
    supportAnimation(value: boolean): this
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
    nestedScroll(value: NestedScrollOptions): this
    /** @memo */
    enableScrollInteraction(value: boolean): this
    /** @memo */
    friction(value: number | Resource): this
    /** @memo */
    alignItems(value: GridItemAlignment | undefined): this
    /** @memo */
    onScroll(value: ((first: number,last: number) => void)): this
    /** @memo */
    onReachStart(value: (() => void)): this
    /** @memo */
    onReachEnd(value: (() => void)): this
    /** @memo */
    onScrollStart(value: (() => void)): this
    /** @memo */
    onScrollStop(value: (() => void)): this
    /** @memo */
    onScrollFrameBegin(value: ((offset: number,state: ScrollState) => Literal_Number_offsetRemain)): this
    /** @memo */
    edgeEffect(value: EdgeEffect, options?: EdgeEffectOptions): this
    /** @memo */
    attributeModifier(value: AttributeModifier<GridAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkGridStyle extends ArkScrollableCommonMethodStyle implements GridAttribute {
    columnsTemplate_value?: string
    rowsTemplate_value?: string
    columnsGap_value?: Length
    rowsGap_value?: Length
    scrollBarWidth_value?: number | string
    scrollBarColor_value?: Color | number | string
    scrollBar_value?: BarState
    onScrollBarUpdate_value?: ((index: number,offset: number) => ComputedBarAttribute)
    onScrollIndex_value?: ((first: number,last: number) => void)
    cachedCount_value?: number
    editMode_value?: boolean
    multiSelectable_value?: boolean
    maxCount_value?: number
    minCount_value?: number
    cellLength_value?: number
    layoutDirection_value?: GridDirection
    supportAnimation_value?: boolean
    onItemDragStart_value?: ((event: ItemDragInfo,itemIndex: number) => CustomBuilder)
    onItemDragEnter_value?: ((event: ItemDragInfo) => void)
    onItemDragMove_value?: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void)
    onItemDragLeave_value?: ((event: ItemDragInfo,itemIndex: number) => void)
    onItemDrop_value?: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void)
    nestedScroll_value?: NestedScrollOptions
    enableScrollInteraction_value?: boolean
    friction_value?: number | Resource
    alignItems_value?: GridItemAlignment | undefined
    onScroll_value?: ((first: number,last: number) => void)
    onReachStart_value?: (() => void)
    onReachEnd_value?: (() => void)
    onScrollStart_value?: (() => void)
    onScrollStop_value?: (() => void)
    onScrollFrameBegin_value?: ((offset: number,state: ScrollState) => Literal_Number_offsetRemain)
    public columnsTemplate(value: string): this {
        return this
    }
    public rowsTemplate(value: string): this {
        return this
    }
    public columnsGap(value: Length): this {
        return this
    }
    public rowsGap(value: Length): this {
        return this
    }
    public scrollBarWidth(value: number | string): this {
        return this
    }
    public scrollBarColor(value: Color | number | string): this {
        return this
    }
    public scrollBar(value: BarState): this {
        return this
    }
    public onScrollBarUpdate(value: ((index: number,offset: number) => ComputedBarAttribute)): this {
        return this
    }
    public onScrollIndex(value: ((first: number,last: number) => void)): this {
        return this
    }
    public cachedCount(count: number, show?: boolean): this {
        return this
    }
    public editMode(value: boolean): this {
        return this
    }
    public multiSelectable(value: boolean): this {
        return this
    }
    public maxCount(value: number): this {
        return this
    }
    public minCount(value: number): this {
        return this
    }
    public cellLength(value: number): this {
        return this
    }
    public layoutDirection(value: GridDirection): this {
        return this
    }
    public supportAnimation(value: boolean): this {
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
    public nestedScroll(value: NestedScrollOptions): this {
        return this
    }
    public enableScrollInteraction(value: boolean): this {
        return this
    }
    public friction(value: number | Resource): this {
        return this
    }
    public alignItems(value: GridItemAlignment | undefined): this {
        return this
    }
    public onScroll(value: ((first: number,last: number) => void)): this {
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
    public onScrollFrameBegin(value: ((offset: number,state: ScrollState) => Literal_Number_offsetRemain)): this {
        return this
    }
    public edgeEffect(value: EdgeEffect, options?: EdgeEffectOptions): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<GridAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
/** @memo:stable */
export class ArkGridComponent extends ArkScrollableCommonMethodComponent implements UIGridAttribute {
    getPeer(): ArkGridPeer {
        return (this.peer as ArkGridPeer)
    }
    /** @memo */
    public setGridOptions(scroller?: Scroller, layoutOptions?: GridLayoutOptions): this {
        if (this.checkPriority("setGridOptions")) {
            const scroller_casted = scroller as (Scroller | undefined)
            const layoutOptions_casted = layoutOptions as (GridLayoutOptions | undefined)
            this.getPeer()?.setGridOptionsAttribute(scroller_casted, layoutOptions_casted)
            return this
        }
        return this
    }
    /** @memo */
    public columnsTemplate(value: string): this {
        if (this.checkPriority("columnsTemplate")) {
            const value_casted = value as (string)
            this.getPeer()?.columnsTemplateAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public rowsTemplate(value: string): this {
        if (this.checkPriority("rowsTemplate")) {
            const value_casted = value as (string)
            this.getPeer()?.rowsTemplateAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public columnsGap(value: Length): this {
        if (this.checkPriority("columnsGap")) {
            const value_casted = value as (Length)
            this.getPeer()?.columnsGapAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public rowsGap(value: Length): this {
        if (this.checkPriority("rowsGap")) {
            const value_casted = value as (Length)
            this.getPeer()?.rowsGapAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public scrollBarWidth(value: number | string): this {
        if (this.checkPriority("scrollBarWidth")) {
            const value_casted = value as (number | string)
            this.getPeer()?.scrollBarWidthAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public scrollBarColor(value: Color | number | string): this {
        if (this.checkPriority("scrollBarColor")) {
            const value_casted = value as (Color | number | string)
            this.getPeer()?.scrollBarColorAttribute(value_casted)
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
    public onScrollBarUpdate(value: ((index: number,offset: number) => ComputedBarAttribute)): this {
        if (this.checkPriority("onScrollBarUpdate")) {
            const value_casted = value as (((index: number,offset: number) => ComputedBarAttribute))
            this.getPeer()?.onScrollBarUpdateAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onScrollIndex(value: ((first: number,last: number) => void)): this {
        if (this.checkPriority("onScrollIndex")) {
            const value_casted = value as (((first: number,last: number) => void))
            this.getPeer()?.onScrollIndexAttribute(value_casted)
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
    public maxCount(value: number): this {
        if (this.checkPriority("maxCount")) {
            const value_casted = value as (number)
            this.getPeer()?.maxCountAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public minCount(value: number): this {
        if (this.checkPriority("minCount")) {
            const value_casted = value as (number)
            this.getPeer()?.minCountAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public cellLength(value: number): this {
        if (this.checkPriority("cellLength")) {
            const value_casted = value as (number)
            this.getPeer()?.cellLengthAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public layoutDirection(value: GridDirection): this {
        if (this.checkPriority("layoutDirection")) {
            const value_casted = value as (GridDirection)
            this.getPeer()?.layoutDirectionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public supportAnimation(value: boolean): this {
        if (this.checkPriority("supportAnimation")) {
            const value_casted = value as (boolean)
            this.getPeer()?.supportAnimationAttribute(value_casted)
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
    public alignItems(value: GridItemAlignment | undefined): this {
        if (this.checkPriority("alignItems")) {
            const value_casted = value as (GridItemAlignment | undefined)
            this.getPeer()?.alignItemsAttribute(value_casted)
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
    public onScrollFrameBegin(value: ((offset: number,state: ScrollState) => Literal_Number_offsetRemain)): this {
        if (this.checkPriority("onScrollFrameBegin")) {
            const value_casted = value as (((offset: number,state: ScrollState) => Literal_Number_offsetRemain))
            this.getPeer()?.onScrollFrameBeginAttribute(value_casted)
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
    public attributeModifier(value: AttributeModifier<GridAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ArkGrid(
    /** @memo */
    style: ((attributes: UIGridAttribute) => void) | undefined,
    /** @memo */
    content_: (() => void) | undefined,
    scroller?: Scroller, layoutOptions?: GridLayoutOptions,
): void {
    const receiver = remember(() => {
        return new ArkGridComponent()
    })
    NodeAttach<ArkGridPeer>((): ArkGridPeer => ArkGridPeer.create(receiver), (_: ArkGridPeer) => {
        receiver.setGridOptions(scroller,layoutOptions)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

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
import { ArkScrollableCommonMethodPeer, ScrollableCommonMethod, ItemDragInfo, CustomBuilder, NestedScrollOptions, EdgeEffectOptions, ArkScrollableCommonMethodComponent, ArkScrollableCommonMethodStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethod, OnWillScrollCallback, OnScrollCallback } from "./common"
import { Length } from "./units"
import { Color, BarState, EdgeEffect } from "./enums"
import { GridAttribute_onItemDragStart_event_type } from "./type-replacements"
import { Resource } from "global/resource"
import { ScrollState } from "./list"
import { OnScrollFrameBeginCallback, Scroller } from "./scroll"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Tuple_Number_Number } from "./arkui-synthetics"

export class ArkGridPeer extends ArkScrollableCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkGridPeer {
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
    columnsTemplateAttribute(value: string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_columnsTemplate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    rowsTemplateAttribute(value: string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_rowsTemplate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    columnsGapAttribute(value: Length | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_columnsGap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    rowsGapAttribute(value: Length | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_rowsGap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    scrollBarWidthAttribute(value: number | string | undefined): void {
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
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._GridAttribute_scrollBarWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    scrollBarColorAttribute(value: Color | number | string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._GridAttribute_scrollBarColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_scrollBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollBarUpdateAttribute(value: ((index: number,offset: number) => ComputedBarAttribute) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_onScrollBarUpdate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollIndexAttribute(value: ((first: number,last: number) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_onScrollIndex(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_cachedCount0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_cachedCount1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_editMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_multiSelectable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    maxCountAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_maxCount(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    minCountAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_minCount(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    cellLengthAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_cellLength(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    layoutDirectionAttribute(value: GridDirection | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as GridDirection)
            thisSerializer.writeInt32(TypeChecker.GridDirection_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._GridAttribute_layoutDirection(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    supportAnimationAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_supportAnimation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_onItemDragStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_onItemDragEnter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_onItemDragMove(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_onItemDragLeave(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_onItemDrop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_nestedScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_enableScrollInteraction(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    onScrollAttribute(value: ((first: number,last: number) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_onScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_onReachStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_onReachEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_onScrollStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_onScrollStop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollFrameBeginAttribute(value: OnScrollFrameBeginCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_onScrollFrameBegin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_onWillScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GridAttribute_onDidScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length());
        thisSerializer.release();
    }
    edgeEffectAttribute(value: EdgeEffect | undefined, options?: EdgeEffectOptions | undefined): void {
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
        ArkUIGeneratedNativeModule._GridAttribute_edgeEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
export type GridInterface = (scroller?: Scroller, layoutOptions?: GridLayoutOptions) => GridAttribute;
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
    columnsTemplate(value: string | undefined): this
    rowsTemplate(value: string | undefined): this
    columnsGap(value: Length | undefined): this
    rowsGap(value: Length | undefined): this
    scrollBarWidth(value: number | string | undefined): this
    scrollBarColor(value: Color | number | string | undefined): this
    scrollBar(value: BarState | undefined): this
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
    onItemDragStart(value: ((event: ItemDragInfo,itemIndex: number) => CustomBuilder) | undefined): this
    onItemDragEnter(value: ((event: ItemDragInfo) => void) | undefined): this
    onItemDragMove(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void) | undefined): this
    onItemDragLeave(value: ((event: ItemDragInfo,itemIndex: number) => void) | undefined): this
    onItemDrop(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void) | undefined): this
    nestedScroll(value: NestedScrollOptions | undefined): this
    enableScrollInteraction(value: boolean | undefined): this
    friction(value: number | Resource | undefined): this
    alignItems(value: GridItemAlignment | undefined): this
    onScroll(value: ((first: number,last: number) => void) | undefined): this
    onReachStart(value: (() => void) | undefined): this
    onReachEnd(value: (() => void) | undefined): this
    onScrollStart(value: (() => void) | undefined): this
    onScrollStop(value: (() => void) | undefined): this
    onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this
    onWillScroll(value: OnWillScrollCallback | undefined): this
    onDidScroll(value: OnScrollCallback | undefined): this
    edgeEffect(value: EdgeEffect | undefined, options?: EdgeEffectOptions | undefined): this
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
    onItemDragStart_value?: ((event: ItemDragInfo,itemIndex: number) => CustomBuilder) | undefined
    onItemDragEnter_value?: ((event: ItemDragInfo) => void) | undefined
    onItemDragMove_value?: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void) | undefined
    onItemDragLeave_value?: ((event: ItemDragInfo,itemIndex: number) => void) | undefined
    onItemDrop_value?: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void) | undefined
    nestedScroll_value?: NestedScrollOptions | undefined
    enableScrollInteraction_value?: boolean | undefined
    friction_value?: number | Resource | undefined
    alignItems_value?: GridItemAlignment | undefined
    onScroll_value?: ((first: number,last: number) => void) | undefined
    onReachStart_value?: (() => void) | undefined
    onReachEnd_value?: (() => void) | undefined
    onScrollStart_value?: (() => void) | undefined
    onScrollStop_value?: (() => void) | undefined
    onScrollFrameBegin_value?: OnScrollFrameBeginCallback | undefined
    onWillScroll_value?: OnWillScrollCallback | undefined
    onDidScroll_value?: OnScrollCallback | undefined
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
    public scrollBarWidth(value: number | string | undefined): this {
        return this
    }
    public scrollBarColor(value: Color | number | string | undefined): this {
        return this
    }
    public scrollBar(value: BarState | undefined): this {
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
    public nestedScroll(value: NestedScrollOptions | undefined): this {
        return this
    }
    public enableScrollInteraction(value: boolean | undefined): this {
        return this
    }
    public friction(value: number | Resource | undefined): this {
        return this
    }
    public alignItems(value: GridItemAlignment | undefined): this {
        return this
    }
    public onScroll(value: ((first: number,last: number) => void) | undefined): this {
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
    public onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        return this
    }
    public onWillScroll(value: OnWillScrollCallback | undefined): this {
        return this
    }
    public onDidScroll(value: OnScrollCallback | undefined): this {
        return this
    }
    public edgeEffect(value: EdgeEffect | undefined, options?: EdgeEffectOptions | undefined): this {
        return this
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
    public scrollBarWidth(value: number | string | undefined): this {
        if (this.checkPriority("scrollBarWidth")) {
            const value_casted = value as (number | string | undefined)
            this.getPeer()?.scrollBarWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public scrollBarColor(value: Color | number | string | undefined): this {
        if (this.checkPriority("scrollBarColor")) {
            const value_casted = value as (Color | number | string | undefined)
            this.getPeer()?.scrollBarColorAttribute(value_casted)
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
    public alignItems(value: GridItemAlignment | undefined): this {
        if (this.checkPriority("alignItems")) {
            const value_casted = value as (GridItemAlignment | undefined)
            this.getPeer()?.alignItemsAttribute(value_casted)
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
    public onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        if (this.checkPriority("onScrollFrameBegin")) {
            const value_casted = value as (OnScrollFrameBeginCallback | undefined)
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
    public edgeEffect(value: EdgeEffect | undefined, options?: EdgeEffectOptions | undefined): this {
        if (this.checkPriority("edgeEffect")) {
            const value_casted = value as (EdgeEffect | undefined)
            const options_casted = options as (EdgeEffectOptions | undefined)
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
export function Grid(
    /** @memo */
    style: ((attributes: GridAttribute) => void) | undefined,
    scroller?: Scroller, layoutOptions?: GridLayoutOptions,
    /** @memo */
    content_?: (() => void) | undefined,
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

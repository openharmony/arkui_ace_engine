/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { RuntimeType, runtimeType } from '@koalaui/interop';
import { ArkScrollableNode } from './ArkScrollableNode';
import { Length } from '../component/units';
import { Color, BarState, EdgeEffect } from '../component/enums';
import { CustomBuilder } from '../component/builder';
import {
  ItemDragInfo,
  NestedScrollOptions,
  OnWillScrollCallback,
  OnScrollCallback,
  EdgeEffectOptions,
  AttributeModifier,
  ScrollableCommonMethod,
  CommonMethod
} from '../component/common';
import { Scroller, OnScrollFrameBeginCallback } from '../component/scroll';
import { ArkGridPeer, ComputedBarAttribute, GridDirection, GridItemAlignment,
    GridAttribute, GridLayoutOptions } from '../component/grid';
import { Resource } from 'global.resource'
export class ArkGridNode extends ArkScrollableNode implements GridAttribute {
    constructParam(...param: Object[]): this {
        if (param.length > 2) {
            throw new Error('more than 2 parameters');
        }
        let scroller_casted: Scroller | undefined = undefined;
        let options_casted: GridLayoutOptions | undefined = undefined;
        if (param.length === 1) {
            scroller_casted = param[0] as (Scroller | undefined)
        }
        if (param.length === 2) {
            scroller_casted = param[0] as (Scroller | undefined)
            options_casted = param[1] as (GridLayoutOptions | undefined)
        }
        this.getPeer()?.setGridOptionsAttribute(scroller_casted, options_casted)
        this.markDirty()
        return this;
    }
    getPeer() : ArkGridPeer {
        return this.peer as ArkGridPeer
    }
    initialize(scroller?: Object, layoutOptions?: Object): this {
        const scroller_casted = scroller as (Scroller | undefined)
        const options_casted = layoutOptions as (GridLayoutOptions | undefined)
        this.getPeer()?.setGridOptionsAttribute(scroller_casted, options_casted)
        this.markDirty()
        return this;
    }
    allowChildTypes(): string[] {
        return ['GridItem'];
    }
    columnsTemplate(value: string | undefined): this {
        const value_casted = value as (string | undefined)
        this.getPeer()?.setColumnsTemplateAttribute(value_casted)
        this.markDirty()
        return this
    }
    rowsTemplate(value: string | undefined): this {
        const value_casted = value as (string | undefined)
        this.getPeer()?.setRowsTemplateAttribute(value_casted)
        this.markDirty()
        return this
    }
    columnsGap(value: Length | undefined): this {
        const value_casted = value as (Length | undefined)
        this.getPeer()?.setColumnsGapAttribute(value_casted)
        this.markDirty()
        return this
    }
    rowsGap(value: Length | undefined): this {
        const value_casted = value as (Length | undefined)
        this.getPeer()?.setRowsGapAttribute(value_casted)
        this.markDirty()
        return this
    }
    scrollBarWidth(value: number | string | undefined): this {
        const value_casted = value as (number | string | undefined)
        this.getPeer()?.setScrollBarWidthAttribute(value_casted)
        this.markDirty()
        return this
    }
    scrollBarColor(value: Color | number | string | undefined): this {
        const value_casted = value as (Color | number | string | undefined)
        this.getPeer()?.setScrollBarColorAttribute(value_casted)
        this.markDirty()
        return this
    }
    scrollBar(value: BarState | undefined): this {
        const value_casted = value as (BarState | undefined)
        this.getPeer()?.setScrollBarAttribute(value_casted)
        this.markDirty()
        return this
    }
    onScrollBarUpdate(value: ((index: number, offset: number) => ComputedBarAttribute) | undefined): this {
        const value_casted = value as (((index: number,offset: number) => ComputedBarAttribute) | undefined)
        this.getPeer()?.setOnScrollBarUpdateAttribute(value_casted)
        this.markDirty()
        return this
    }
    onScrollIndex(value: ((first: number, last: number) => void) | undefined): this {
        const value_casted = value as (((first: number, last: number) => void) | undefined)
        this.getPeer()?.setOnScrollIndexAttribute(value_casted)
        this.markDirty()
        return this
    }
    cachedCount(value: number | undefined): this  {
        const value_casted = value as (number | undefined)
        this.getPeer()?.setCachedCount0Attribute(value_casted)
        this.markDirty()
        return this
    }
    cachedCount(count: number | undefined, show: boolean | undefined): this {
        const count_type = runtimeType(count)
        const show_type = runtimeType(show)
        if (((RuntimeType.NUMBER == count_type) || (RuntimeType.UNDEFINED == count_type)) &&
            (RuntimeType.UNDEFINED == show_type)) {
            const value_casted = count as (number | undefined)
            this.getPeer()?.setCachedCount0Attribute(value_casted)
            this.markDirty()
            return this
        }
        if (((RuntimeType.NUMBER == count_type) || (RuntimeType.UNDEFINED == count_type)) &&
            ((RuntimeType.BOOLEAN == show_type) || (RuntimeType.UNDEFINED == show_type))) {
            const count_casted = count as (number | undefined)
            const show_casted = show as (boolean | undefined)
            this.getPeer()?.setCachedCount1Attribute(count_casted, show_casted)
            this.markDirty()
            return this
        }
        throw new Error('Can not select appropriate overload')
    }
    editMode(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setEditModeAttribute(value_casted)
        this.markDirty()
        return this
    }
    multiSelectable(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setMultiSelectableAttribute(value_casted)
        this.markDirty()
        return this
    }
    maxCount(value: number | undefined): this {
        const value_casted = value as (number | undefined)
        this.getPeer()?.setMaxCountAttribute(value_casted)
        this.markDirty()
        return this
    }
    minCount(value: number | undefined): this {
        const value_casted = value as (number | undefined)
        this.getPeer()?.setMinCountAttribute(value_casted)
        this.markDirty()
        return this
    }
    cellLength(value: number | undefined): this {
        const value_casted = value as (number | undefined)
        this.getPeer()?.setCellLengthAttribute(value_casted)
        this.markDirty()
        return this
    }
    layoutDirection(value: GridDirection | undefined): this {
        const value_casted = value as (GridDirection | undefined)
        this.getPeer()?.setLayoutDirectionAttribute(value_casted)
        this.markDirty()
        return this
    }
    supportAnimation(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setSupportAnimationAttribute(value_casted)
        this.markDirty()
        return this
    }
    onItemDragStart(value: ((event: ItemDragInfo, itemIndex: number) => CustomBuilder) | undefined): this {
        const value_casted = value as (((event: ItemDragInfo, itemIndex: number) => CustomBuilder) | undefined)
        this.getPeer()?.setOnItemDragStartAttribute(value_casted)
        this.markDirty()
        return this
    }
    onItemDragEnter(value: ((event: ItemDragInfo) => void) | undefined): this {
        const value_casted = value as (((event: ItemDragInfo) => void) | undefined)
        this.getPeer()?.setOnItemDragEnterAttribute(value_casted)
        this.markDirty()
        return this
    }
    onItemDragMove(value: ((event: ItemDragInfo, itemIndex: number, insertIndex: number) => void) | undefined): this {
        const value_casted = value as (((event: ItemDragInfo, itemIndex: number, insertIndex: number) => void) | undefined)
        this.getPeer()?.setOnItemDragMoveAttribute(value_casted)
        this.markDirty()
        return this
    }
    onItemDragLeave(value: ((event: ItemDragInfo, itemIndex: number) => void) | undefined): this {
        const value_casted = value as (((event: ItemDragInfo, itemIndex: number) => void) | undefined)
        this.getPeer()?.setOnItemDragLeaveAttribute(value_casted)
        this.markDirty()
        return this
    }
    onItemDrop(value: ((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void) | undefined): this {
        const value_casted = value as (((event: ItemDragInfo, itemIndex: number,
        insertIndex: number, isSuccess: boolean) => void) | undefined)
        this.getPeer()?.setOnItemDropAttribute(value_casted)
        this.markDirty()
        return this
    }
    nestedScroll(value: NestedScrollOptions | undefined): this {
        const value_casted = value as (NestedScrollOptions | undefined)
        this.getPeer()?.setNestedScrollAttribute(value_casted)
        this.markDirty()
        return this
    }
    enableScrollInteraction(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setEnableScrollInteractionAttribute(value_casted)
        this.markDirty()
        return this
    }
    friction(value: number | Resource | undefined): this {
        const value_casted = value as (number | Resource | undefined)
        this.getPeer()?.setFrictionAttribute(value_casted)
        this.markDirty()
        return this
    }
    alignItems(value: GridItemAlignment | undefined): this {
        const value_casted = value as (GridItemAlignment | undefined)
        this.getPeer()?.setAlignItemsAttribute(value_casted)
        this.markDirty()
        return this
    }
    onReachStart(value: (() => void) | undefined): this {
        const value_casted = value as ((() => void) | undefined)
        this.getPeer()?.setOnReachStartAttribute(value_casted)
        this.markDirty()
        return this
    }
    onReachEnd(value: (() => void) | undefined): this {
        const value_casted = value as ((() => void) | undefined)
        this.getPeer()?.setOnReachEndAttribute(value_casted)
        this.markDirty()
        return this
    }
    onScrollStart(value: (() => void) | undefined): this {
        const value_casted = value as ((() => void) | undefined)
        this.getPeer()?.setOnScrollStartAttribute(value_casted)
        this.markDirty()
        return this
    }
    onScrollStop(value: (() => void) | undefined): this {
        const value_casted = value as ((() => void) | undefined)
        this.getPeer()?.setOnScrollStopAttribute(value_casted)
        this.markDirty()
        return this
    }
    onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        const value_casted = value as (OnScrollFrameBeginCallback | undefined)
        this.getPeer()?.setOnScrollFrameBeginAttribute(value_casted)
        this.markDirty()
        return this
    }
    onWillScroll(value: OnWillScrollCallback | undefined): this {
        const value_casted = value as (OnWillScrollCallback | undefined)
        this.getPeer()?.setOnWillScrollAttribute(value_casted)
        this.markDirty()
        return this
    }
    onDidScroll(value: OnScrollCallback | undefined): this {
        const value_casted = value as (OnScrollCallback | undefined)
        this.getPeer()?.setOnDidScrollAttribute(value_casted)
        this.markDirty()
        return this
    }
    edgeEffect(value: EdgeEffect | undefined, options?: EdgeEffectOptions | undefined): this {
        const value_casted = value as (EdgeEffect | undefined)
        const options_casted = options as (EdgeEffectOptions | undefined)
        this.getPeer()?.setEdgeEffectAttribute(value_casted, options_casted)
        this.markDirty()
        return this
    }
    attributeModifier(value: AttributeModifier<GridAttribute> | AttributeModifier<ScrollableCommonMethod> |
        AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}
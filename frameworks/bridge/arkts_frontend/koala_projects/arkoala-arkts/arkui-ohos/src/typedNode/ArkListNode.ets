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

import { int32 } from '@koalaui/common';
import { RuntimeType, runtimeType } from '@koalaui/interop';
import { ArkScrollableNode } from './ArkScrollableNode';
import {
  ListAttribute,
  ArkListPeer,
  ListOptions,
  ListItemAlign,
  Axis,
  BarState,
  ListDividerOptions,
  ChainAnimationOptions,
  StickyStyle,
  ScrollSnapAlign,
  NestedScrollOptions,
  ChildrenMainSize,
  OnScrollVisibleContentChangeCallback,
  ItemDragInfo,
  CustomBuilder,
  OnScrollFrameBeginCallback,
  OnWillScrollCallback,
  OnScrollCallback,
  LengthConstrain,
  Dimension,
  EdgeEffect,
  EdgeEffectOptions,
  AttributeModifier,
  ScrollableCommonMethod,
  CommonMethod
} from '../framework';
import { Resource } from 'global.resource'
export class ArkListNode extends ArkScrollableNode implements ListAttribute {
    constructParam(...param: Object[]): this {
        if (param.length > 1) {
            throw new Error('more than 1 parameters');
        }
        let options_casted : ListOptions | undefined = undefined;
        if (param.length === 1) {
            options_casted = param[0] as (ListOptions | undefined);
        }
        this.getPeer()?.setListOptionsAttribute(options_casted)
        this.markDirty()
        return this;
    }
    getPeer() : ArkListPeer {
        return this.peer as ArkListPeer
    }
    initialize(options?: ListOptions): this {
        const options_casted = options as (ListOptions | undefined)
        this.getPeer()?.setListOptionsAttribute(options_casted)
        this.markDirty()
        return this;
    }
    allowChildTypes(): string[] {
        return ['ListItem', 'ListItemGroup'];
    }
    alignListItem(value: ListItemAlign | undefined): this {
        const value_casted = value as (ListItemAlign | undefined)
        this.getPeer()?.setAlignListItemAttribute(value_casted)
        this.markDirty()
        return this
    }
    listDirection(value: Axis | undefined): this {
        const value_casted = value as (Axis | undefined)
        this.getPeer()?.setListDirectionAttribute(value_casted)
        this.markDirty()
        return this
    }
    scrollBar(value: BarState | undefined): this {
        const value_casted = value as (BarState | undefined)
        this.getPeer()?.setScrollBarAttribute(value_casted)
        this.markDirty()
        return this
}
    contentStartOffset(value: double | undefined): this {
        const value_casted = value as (double | undefined)
        this.getPeer()?.setContentStartOffsetAttribute(value_casted)
        this.markDirty()
        return this
    }
    contentEndOffset(value: double | undefined): this {
        const value_casted = value as (double | undefined)
        this.getPeer()?.setContentEndOffsetAttribute(value_casted)
        this.markDirty()
        return this
    }
    divider(value: ListDividerOptions | null | undefined): this {
        const value_casted = value as (ListDividerOptions | null | undefined)
        this.getPeer()?.setDividerAttribute(value_casted)
        this.markDirty()
        return this
    }
    multiSelectable(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setMultiSelectableAttribute(value_casted)
        this.markDirty()
        return this
    }
    cachedCount(count: int32 | undefined, show: boolean | undefined): this {
        const count_type = runtimeType(count)
        const show_type = runtimeType(show)
        if (((RuntimeType.NUMBER == count_type) || (RuntimeType.UNDEFINED == count_type)) &&
            (RuntimeType.UNDEFINED == show_type)) {
            const value_casted = count as (int32 | undefined)
            this.getPeer()?.setCachedCount0Attribute(value_casted)
            this.markDirty()
            return this
        }
        if (((RuntimeType.NUMBER == count_type) || (RuntimeType.UNDEFINED == count_type)) &&
            ((RuntimeType.BOOLEAN == show_type) || (RuntimeType.UNDEFINED == show_type))) {
            const count_casted = count as (int32 | undefined)
            const show_casted = show as (boolean | undefined)
            this.getPeer()?.setCachedCount1Attribute(count_casted, show_casted)
            this.markDirty()
            return this
        }
        throw new Error('Can not select appropriate overload')
    }
    cachedCount(value: int32 | undefined): this {
        const count_type = runtimeType(value)
        if (((RuntimeType.NUMBER == count_type) || (RuntimeType.UNDEFINED == count_type))) {
            const value_casted = value as (int32 | undefined)
            this.getPeer()?.setCachedCount0Attribute(value_casted)
            this.markDirty()
            return this
        }
        throw new Error('Can not select appropriate overload')
    }
    chainAnimation(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setChainAnimationAttribute(value_casted)
        this.markDirty()
        return this
    }
    chainAnimationOptions(value: ChainAnimationOptions | undefined): this {
        const value_casted = value as (ChainAnimationOptions | undefined)
        this.getPeer()?.setChainAnimationOptionsAttribute(value_casted)
        this.markDirty()
        return this
    }
    sticky(value: StickyStyle | undefined): this {
        const value_casted = value as (StickyStyle | undefined)
        this.getPeer()?.setStickyAttribute(value_casted)
        this.markDirty()
        return this
    }
    scrollSnapAlign(value: ScrollSnapAlign | undefined): this {
        const value_casted = value as (ScrollSnapAlign | undefined)
        this.getPeer()?.setScrollSnapAlignAttribute(value_casted)
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
    friction(value: double | Resource | undefined): this {
        const value_casted = value as (double | Resource | undefined)
        this.getPeer()?.setFrictionAttribute(value_casted)
        this.markDirty()
        return this
    }
    childrenMainSize(value: ChildrenMainSize | undefined): this {
        const value_casted = value as (ChildrenMainSize | undefined)
        this.getPeer()?.setChildrenMainSizeAttribute(value_casted);
        this.markDirty()
        return this
    }
    maintainVisibleContentPosition(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setMaintainVisibleContentPositionAttribute(value_casted)
        this.markDirty()
        return this
    }
    stackFromEnd(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setStackFromEndAttribute(value_casted)
        this.markDirty()
        return this
    }
    onScrollIndex(value: ((start: int32, end: int32, center: int32) => void) | undefined): this {
        const value_casted = value as (((start: int32, end: int32, center: int32) => void) | undefined)
        this.getPeer()?.setOnScrollIndexAttribute(value_casted)
        this.markDirty()
        return this
    }
    onScrollVisibleContentChange(value: OnScrollVisibleContentChangeCallback | undefined): this {
        const value_casted = value as (OnScrollVisibleContentChangeCallback | undefined)
        this.getPeer()?.setOnScrollVisibleContentChangeAttribute(value_casted)
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
    onItemMove(value: ((from: int32, to: int32) => boolean) | undefined): this {
        const value_casted = value as (((from: int32, to: int32) => boolean) | undefined)
        this.getPeer()?.setOnItemMoveAttribute(value_casted)
        this.markDirty()
        return this
    }
    onItemDragStart(value: ((event: ItemDragInfo, itemIndex: int32) => CustomBuilder) | undefined): this {
        const value_casted = value as (((event: ItemDragInfo, itemIndex: int32) => CustomBuilder) | undefined)
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
    onItemDragMove(value: ((event: ItemDragInfo, itemIndex: int32, insertIndex: int32) => void) | undefined): this {
        const value_casted = value as (((event: ItemDragInfo, itemIndex: int32, insertIndex: int32) => void) | undefined)
        this.getPeer()?.setOnItemDragMoveAttribute(value_casted)
        this.markDirty()
        return this
    }
    onItemDragLeave(value: ((event: ItemDragInfo, itemIndex: int32) => void) | undefined): this {
        const value_casted = value as (((event: ItemDragInfo, itemIndex: int32) => void) | undefined)
        this.getPeer()?.setOnItemDragLeaveAttribute(value_casted)
        this.markDirty()
        return this
    }
    onItemDrop(value: ((event: ItemDragInfo, itemIndex: int32, insertIndex: int32, isSuccess: boolean) => void) | undefined): this {
        const value_casted = value as (((event: ItemDragInfo, itemIndex: int32, insertIndex: int32, isSuccess: boolean) => void) | undefined)
        this.getPeer()?.setOnItemDropAttribute(value_casted)
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
    lanes(value: int32 | LengthConstrain | undefined, gutter?: Dimension): this {
        const value_casted = value as (int32 | LengthConstrain | undefined)
        const gutter_casted = gutter as (Dimension | undefined)
        this.getPeer()?.setLanesAttribute(value_casted, gutter_casted)
        this.markDirty()
        return this
    }
    edgeEffect(value: EdgeEffect | undefined, options?: EdgeEffectOptions): this {
        const value_casted = value as (EdgeEffect | undefined)
        const options_casted = options as (EdgeEffectOptions | undefined)
        this.getPeer()?.setEdgeEffectAttribute(value_casted, options_casted)
        this.markDirty()
        return this
    }
    multiSelectable(value: boolean | undefined): this {
        this.getPeer()?.setSupportEmptyBranchInLazyLoadingAttribute(value)
        this.markDirty()
        return this
    }
    attributeModifier(
        value: AttributeModifier<ListAttribute> |
        AttributeModifier<ScrollableCommonMethod> |
        AttributeModifier<CommonMethod> |
        undefined
    ): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}
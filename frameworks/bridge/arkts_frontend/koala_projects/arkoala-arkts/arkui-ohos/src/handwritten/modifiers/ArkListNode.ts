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

import { RuntimeType, runtimeType } from "@koalaui/interop";
import { ArkScrollableNode } from "./ArkScrollableNode";
import { ListAttribute, ArkListPeer, ListOptions, ListItemAlign, Axis, BarState, ListDividerOptions, ChainAnimationOptions, StickyStyle,
    ScrollSnapAlign, NestedScrollOptions, ChildrenMainSize, OnScrollVisibleContentChangeCallback, ItemDragInfo, CustomBuilder,
    OnScrollFrameBeginCallback, OnWillScrollCallback, OnScrollCallback, LengthConstrain, Dimension, EdgeEffect, EdgeEffectOptions
} from "../../component";
import { Resource } from "global.resource"
import { hookListNodeChildrenMainSizeImpl } from "../../handwritten"
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
        return this;
    }
    getPeer() : ArkListPeer {
        return this.peer as ArkListPeer
    }
    initialize(options?: ListOptions): this {
        const options_casted = options as (ListOptions | undefined)
        this.getPeer()?.setListOptionsAttribute(options_casted)
        return this;
    }
    allowChildTypes(): string[] {
        return ["ListItem", "ListItemGroup"];
    }
    alignListItem(value: ListItemAlign | undefined): this {
        const value_casted = value as (ListItemAlign | undefined)
        this.getPeer()?.alignListItemAttribute(value_casted)
        return this
    }
    listDirection(value: Axis | undefined): this {
        const value_casted = value as (Axis | undefined)
        this.getPeer()?.listDirectionAttribute(value_casted)
        return this
    }
    scrollBar(value: BarState | undefined): this {
        const value_casted = value as (BarState | undefined)
        this.getPeer()?.scrollBarAttribute(value_casted)
        return this
}
    contentStartOffset(value: number | undefined): this {
        const value_casted = value as (number | undefined)
        this.getPeer()?.contentStartOffsetAttribute(value_casted)
        return this
    }
    contentEndOffset(value: number | undefined): this {
        const value_casted = value as (number | undefined)
        this.getPeer()?.contentEndOffsetAttribute(value_casted)
        return this
    }
    divider(value: ListDividerOptions | null | undefined): this {
        const value_casted = value as (ListDividerOptions | null | undefined)
        this.getPeer()?.dividerAttribute(value_casted)
        return this
    }
    editMode(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.editModeAttribute(value_casted)
        return this
    }
    multiSelectable(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.multiSelectableAttribute(value_casted)
        return this
    }
    cachedCount(count: number | undefined, show: boolean | undefined): this {
        const count_type = runtimeType(count)
        const show_type = runtimeType(show)
        if (((RuntimeType.NUMBER == count_type) || (RuntimeType.UNDEFINED == count_type)) &&
            (RuntimeType.UNDEFINED == show_type)) {
            const value_casted = count as (number | undefined)
            this.getPeer()?.cachedCount0Attribute(value_casted)
            return this
        }
        if (((RuntimeType.NUMBER == count_type) || (RuntimeType.UNDEFINED == count_type)) &&
            ((RuntimeType.BOOLEAN == show_type) || (RuntimeType.UNDEFINED == show_type))) {
            const count_casted = count as (number | undefined)
            const show_casted = show as (boolean | undefined)
            this.getPeer()?.cachedCount1Attribute(count_casted, show_casted)
            return this
        }
        throw new Error("Can not select appropriate overload")
    }
    cachedCount(value: number | undefined): this {
        const count_type = runtimeType(value)
        if (((RuntimeType.NUMBER == count_type) || (RuntimeType.UNDEFINED == count_type))) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.cachedCount0Attribute(value_casted)
            return this
        }
        throw new Error("Can not select appropriate overload")
    }
    chainAnimation(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.chainAnimationAttribute(value_casted)
        return this
    }
    chainAnimationOptions(value: ChainAnimationOptions | undefined): this {
        const value_casted = value as (ChainAnimationOptions | undefined)
        this.getPeer()?.chainAnimationOptionsAttribute(value_casted)
        return this
    }
    sticky(value: StickyStyle | undefined): this {
        const value_casted = value as (StickyStyle | undefined)
        this.getPeer()?.stickyAttribute(value_casted)
        return this
    }
    scrollSnapAlign(value: ScrollSnapAlign | undefined): this {
        const value_casted = value as (ScrollSnapAlign | undefined)
        this.getPeer()?.scrollSnapAlignAttribute(value_casted)
        return this
    }
    nestedScroll(value: NestedScrollOptions | undefined): this {
        const value_casted = value as (NestedScrollOptions | undefined)
        this.getPeer()?.nestedScrollAttribute(value_casted)
        return this
    }
    enableScrollInteraction(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.enableScrollInteractionAttribute(value_casted)
        return this
    }
    friction(value: number | Resource | undefined): this {
        const value_casted = value as (number | Resource | undefined)
        this.getPeer()?.frictionAttribute(value_casted)
        return this
    }
    childrenMainSize(value: ChildrenMainSize | undefined): this {
        const value_casted = value as (ChildrenMainSize | undefined)
        hookListNodeChildrenMainSizeImpl(this, value_casted);
        return this
    }
    maintainVisibleContentPosition(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.maintainVisibleContentPositionAttribute(value_casted)
        return this
    }
    stackFromEnd(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.stackFromEndAttribute(value_casted)
        return this
    }
    onScroll(value: ((first: number, last: number) => void) | undefined): this {
        const value_casted = value as (((first: number, last: number) => void) | undefined)
        this.getPeer()?.onScrollAttribute(value_casted)
        return this
    }
    onScrollIndex(value: ((start: number, end: number, center: number) => void) | undefined): this {
        const value_casted = value as (((start: number, end: number, center: number) => void) | undefined)
        this.getPeer()?.onScrollIndexAttribute(value_casted)
        return this
    }
    onScrollVisibleContentChange(value: OnScrollVisibleContentChangeCallback | undefined): this {
        const value_casted = value as (OnScrollVisibleContentChangeCallback | undefined)
        this.getPeer()?.onScrollVisibleContentChangeAttribute(value_casted)
        return this
    }
    onReachStart(value: (() => void) | undefined): this {
        const value_casted = value as ((() => void) | undefined)
        this.getPeer()?.onReachStartAttribute(value_casted)
        return this
    }
    onReachEnd(value: (() => void) | undefined): this {
        const value_casted = value as ((() => void) | undefined)
        this.getPeer()?.onReachEndAttribute(value_casted)
        return this
    }
    onScrollStart(value: (() => void) | undefined): this {
        const value_casted = value as ((() => void) | undefined)
        this.getPeer()?.onScrollStartAttribute(value_casted)
        return this
    }
    onScrollStop(value: (() => void) | undefined): this {
        const value_casted = value as ((() => void) | undefined)
        this.getPeer()?.onScrollStopAttribute(value_casted)
        return this
    }
    onItemDelete(value: ((index: number) => boolean) | undefined): this {
        const value_casted = value as (((index: number) => boolean) | undefined)
        this.getPeer()?.onItemDeleteAttribute(value_casted)
        return this
    }
    onItemMove(value: ((from: number, to: number) => boolean) | undefined): this {
        const value_casted = value as (((from: number, to: number) => boolean) | undefined)
        this.getPeer()?.onItemMoveAttribute(value_casted)
        return this
    }
    onItemDragStart(value: ((event: ItemDragInfo, itemIndex: number) => CustomBuilder) | undefined): this {
        const value_casted = value as (((event: ItemDragInfo, itemIndex: number) => CustomBuilder) | undefined)
        this.getPeer()?.onItemDragStartAttribute(value_casted)
        return this
    }
    onItemDragEnter(value: ((event: ItemDragInfo) => void) | undefined): this {
        const value_casted = value as (((event: ItemDragInfo) => void) | undefined)
        this.getPeer()?.onItemDragEnterAttribute(value_casted)
        return this
    }
    onItemDragMove(value: ((event: ItemDragInfo, itemIndex: number, insertIndex: number) => void) | undefined): this {
        const value_casted = value as (((event: ItemDragInfo, itemIndex: number, insertIndex: number) => void) | undefined)
        this.getPeer()?.onItemDragMoveAttribute(value_casted)
        return this
    }
    onItemDragLeave(value: ((event: ItemDragInfo, itemIndex: number) => void) | undefined): this {
        const value_casted = value as (((event: ItemDragInfo, itemIndex: number) => void) | undefined)
        this.getPeer()?.onItemDragLeaveAttribute(value_casted)
        return this
    }
    onItemDrop(value: ((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void) | undefined): this {
        const value_casted = value as (((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void) | undefined)
        this.getPeer()?.onItemDropAttribute(value_casted)
        return this
    }
    onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        const value_casted = value as (OnScrollFrameBeginCallback | undefined)
        this.getPeer()?.onScrollFrameBeginAttribute(value_casted)
        return this
    }
    onWillScroll(value: OnWillScrollCallback | undefined): this {
        const value_casted = value as (OnWillScrollCallback | undefined)
        this.getPeer()?.onWillScrollAttribute(value_casted)
        return this
    }
    onDidScroll(value: OnScrollCallback | undefined): this {
        const value_casted = value as (OnScrollCallback | undefined)
        this.getPeer()?.onDidScrollAttribute(value_casted)
        return this
    }
    lanes(value: number | LengthConstrain | undefined, gutter?: Dimension): this {
        const value_casted = value as (number | LengthConstrain | undefined)
        const gutter_casted = gutter as (Dimension | undefined)
        this.getPeer()?.lanesAttribute(value_casted, gutter_casted)
        return this
    }
    edgeEffect(value: EdgeEffect | undefined, options?: EdgeEffectOptions): this {
        const value_casted = value as (EdgeEffect | undefined)
        const options_casted = options as (EdgeEffectOptions | undefined)
        this.getPeer()?.edgeEffectAttribute(value_casted, options_casted)
        return this
    }
}
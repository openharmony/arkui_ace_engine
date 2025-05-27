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

import { InteropNativeModule } from "@koalaui/interop";

import { ArkBaseNode } from "./ArkBaseNode";
import { CustomBuilder, ListAttribute, ListItemAlign, Axis, BarState, ListDividerOptions, ChainAnimationOptions, StickyStyle, ScrollSnapAlign,
    NestedScrollOptions, ChildrenMainSize, OnScrollVisibleContentChangeCallback, OnScrollCallback, ItemDragInfo, OnWillScrollCallback, ScrollState,
    Literal_Number_offsetRemain, Dimension, LengthConstrain, EdgeEffect, Color, ContentClipMode, RectShape, CrownSensitivity, FadingEdgeOptions,
    EdgeEffectOptions
} from "../../component";
import { ArkListPeer, ListOptions } from "../../component";
import { Resource } from "global/resource"
export class ArkListNode extends ArkBaseNode  implements ListAttribute  {

    constructParam(...param: Object[]): this {
        InteropNativeModule._NativeLog("list constructParam enter")
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
        return this;
    }
    listDirection(value: Axis | undefined): this {
        return this;
    }
    scrollBar(value: BarState | undefined): this {
        return this;
    }
    contentStartOffset(value: number | undefined): this {
        return this;
    }
    contentEndOffset(value: number | undefined): this {
        return this;
    }
    divider(value: ListDividerOptions | undefined): this {
        return this;
    }
    editMode(value: boolean | undefined): this {
        return this;
    }
    multiSelectable(value: boolean | undefined): this {
        return this;
    }
    cachedCount(count: number | undefined, show?: boolean): this {
        return this;
    }
    chainAnimation(value: boolean | undefined): this {
        return this;
    }
    chainAnimationOptions(value: ChainAnimationOptions | undefined): this {
        return this;
    }
    sticky(value: StickyStyle | undefined): this {
        return this;
    }
    scrollSnapAlign(value: ScrollSnapAlign | undefined): this {
        return this;
    }
    nestedScroll(value: NestedScrollOptions | undefined): this {
        return this;
    }
    enableScrollInteraction(value: boolean | undefined): this {
        return this;
    }
    friction(value: number | Resource | undefined): this {
        return this;
    }
    childrenMainSize(value: ChildrenMainSize | undefined): this {
        return this;
    }
    maintainVisibleContentPosition(value: boolean | undefined): this {
        return this;
    }
    stackFromEnd(value: boolean | undefined): this {
        return this;
    }
    onScroll(value: ((first: number,last: number) => void) | undefined): this {
        return this;
    }
    onScrollIndex(value: ((start: number,end: number,center: number) => void) | undefined): this {
        return this;
    }
    onScrollVisibleContentChange(value: OnScrollVisibleContentChangeCallback | undefined): this {
        return this;
    }
    onReachStart(value: (() => void) | undefined): this {
        return this;
    }
    onReachEnd(value: (() => void) | undefined): this {
        return this;
    }
    onDidScroll(value: OnScrollCallback | undefined): this {
        return this;
    }
    onScrollStart(value: (() => void) | undefined): this {
        return this;
    }
    onScrollStop(value: (() => void) | undefined): this {
        return this;
    }
    onItemDelete(value: ((index: number) => boolean) | undefined): this {
        return this;
    }
    onItemMove(value: ((from: number,to: number) => boolean) | undefined): this {
        return this;
    }
    onItemDragStart(value: ((event: ItemDragInfo,itemIndex: number) => CustomBuilder) | undefined): this {
        return this;
    }
    onItemDragEnter(value: ((event: ItemDragInfo) => void) | undefined): this {
        return this;
    }
    onItemDragMove(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void) | undefined): this {
        return this;
    }
    onItemDragLeave(value: ((event: ItemDragInfo,itemIndex: number) => void) | undefined): this {
        return this;
    }
    onItemDrop(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void) | undefined): this {
        return this;
    }
    onWillScroll(value: OnWillScrollCallback | undefined): this {
        return this;
    }
    onScrollFrameBegin(value: ((offset: number,state: ScrollState) => Literal_Number_offsetRemain) | undefined): this {
        return this;
    }
    lanes(value: number | LengthConstrain | undefined, gutter?: Dimension): this {
        return this;
    }
    edgeEffect(value: EdgeEffect | undefined, options?: EdgeEffectOptions): this {
        return this;
    }
    scrollBarColor(value: Color | number | string | undefined): this {
        return this;
    }
    scrollBarWidth(value: number | string | undefined): this {
        return this;
    }
    flingSpeedLimit(value: number | undefined): this {
        return this;
    }
    clipContent(value: ContentClipMode | RectShape | undefined): this {
        return this;
    }
    digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        return this;
    }
    backToTop(value: boolean | undefined): this {
        return this;
    }
    fadingEdge(enabled: boolean | undefined, options?: FadingEdgeOptions): this {
        return this;
    }
}
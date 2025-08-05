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

import { ArkScrollableNode } from "./ArkScrollableNode";
import { ScrollAttribute, ArkScrollPeer, Scroller, ScrollDirection, ScrollOnWillScrollCallback, ScrollOnScrollCallback,
    OnScrollEdgeCallback, VoidCallback, BarState, Color, OnScrollFrameBeginCallback, NestedScrollOptions, ScrollSnapOptions,
    OffsetOptions, EdgeEffect, EdgeEffectOptions } from "../../component";
import { Resource } from "global.resource"
export class ArkScrollNode extends ArkScrollableNode implements ScrollAttribute {
    constructParam(...param: Object[]): this {
        if (param.length > 1) {
            throw new Error('more than 1 parameters');
        }
        let scroller_casted: Scroller | undefined = undefined;
        if (param.length === 1) {
            scroller_casted = param[0] as (Scroller | undefined);
        }
        this.getPeer()?.setScrollOptionsAttribute(scroller_casted)
        return this;
    }
    getPeer() : ArkScrollPeer {
        return this.peer as ArkScrollPeer
    }
    initialize(scroller?: Object): this {
        const scroller_casted = scroller as (Scroller | undefined)
        this.getPeer()?.setScrollOptionsAttribute(scroller_casted)
        return this;
    }
    scrollable(value: ScrollDirection | undefined): this {
        const value_casted = value as (ScrollDirection | undefined)
        this.getPeer()?.scrollableAttribute(value_casted)
        return this
    }
    onScroll(value: ((first: number,last: number) => void) | undefined): this {
        const value_casted = value as (((first: number,last: number) => void) | undefined)
        this.getPeer()?.onScrollAttribute(value_casted)
        return this
    }
    onWillScroll(value: ScrollOnWillScrollCallback | undefined): this {
        const value_casted = value as (ScrollOnWillScrollCallback | undefined)
        this.getPeer()?.onWillScrollAttribute(value_casted)
        return this
    }
    onDidScroll(value: ScrollOnScrollCallback | undefined): this {
        const value_casted = value as (ScrollOnScrollCallback | undefined)
        this.getPeer()?.onDidScrollAttribute(value_casted)
        return this
    }
    onScrollEdge(value: OnScrollEdgeCallback | undefined): this {
        const value_casted = value as (OnScrollEdgeCallback | undefined)
        this.getPeer()?.onScrollEdgeAttribute(value_casted)
        return this
    }
    onScrollStart(value: VoidCallback | undefined): this {
        const value_casted = value as (VoidCallback | undefined)
        this.getPeer()?.onScrollStartAttribute(value_casted)
        return this
    }
    onScrollEnd(value: (() => void) | undefined): this {
        const value_casted = value as ((() => void) | undefined)
        this.getPeer()?.onScrollEndAttribute(value_casted)
        return this
    }
    onScrollStop(value: VoidCallback | undefined): this {
        const value_casted = value as (VoidCallback | undefined)
        this.getPeer()?.onScrollStopAttribute(value_casted)
        return this
    }
    scrollBar(value: BarState | undefined): this {
        const value_casted = value as (BarState | undefined)
        this.getPeer()?.scrollBarAttribute(value_casted)
        return this
    }
    scrollBarColor(value: Color | number | string | undefined): this {
        const value_casted = value as (Color | number | string | undefined)
        this.getPeer()?.scrollBarColorAttribute(value_casted)
        return this
    }
    scrollBarWidth(value: number | string | undefined): this {
        const value_casted = value as (number | string | undefined)
        this.getPeer()?.scrollBarWidthAttribute(value_casted)
        return this
    }
    onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        const value_casted = value as (OnScrollFrameBeginCallback | undefined)
        this.getPeer()?.onScrollFrameBeginAttribute(value_casted)
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
    scrollSnap(value: ScrollSnapOptions | undefined): this {
        const value_casted = value as (ScrollSnapOptions | undefined)
        this.getPeer()?.scrollSnapAttribute(value_casted)
        return this
    }
    enablePaging(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.enablePagingAttribute(value_casted)
        return this
    }
    initialOffset(value: OffsetOptions | undefined): this {
        const value_casted = value as (OffsetOptions | undefined)
        this.getPeer()?.initialOffsetAttribute(value_casted)
        return this
    }
    edgeEffect(edgeEffect: EdgeEffect | undefined, options?: EdgeEffectOptions | undefined): this {
        const edgeEffect_casted = edgeEffect as (EdgeEffect | undefined)
        const options_casted = options as (EdgeEffectOptions | undefined)
        this.getPeer()?.edgeEffectAttribute(edgeEffect_casted, options_casted)
        return this
    }
}
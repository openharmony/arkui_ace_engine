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
import { ArkScrollableNode } from './ArkScrollableNode';
import {
  ScrollAttribute,
  ArkScrollPeer,
  Scroller,
  ScrollDirection,
  ScrollOnWillScrollCallback,
  ScrollOnScrollCallback,
  OnScrollEdgeCallback,
  VoidCallback,
  BarState,
  Color,
  OnScrollFrameBeginCallback,
  NestedScrollOptions,
  ScrollSnapOptions,
  OffsetOptions,
  EdgeEffect,
  EdgeEffectOptions,
  AttributeModifier,
  ScrollableCommonMethod,
  CommonMethod,
  SizeResult,
  Bindable,
  ScrollOnDidZoomCallback
} from '../framework';
import { Resource } from 'global.resource'
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
        this.markDirty()
        return this;
    }
    getPeer() : ArkScrollPeer {
        return this.peer as ArkScrollPeer
    }
    initialize(scroller?: Object): this {
        const scroller_casted = scroller as (Scroller | undefined)
        this.getPeer()?.setScrollOptionsAttribute(scroller_casted)
        this.markDirty()
        return this;
    }
    allowChildCount(): number {
        return 1;
    }
    scrollable(value: ScrollDirection | undefined): this {
        const value_casted = value as (ScrollDirection | undefined)
        this.getPeer()?.setScrollableAttribute(value_casted)
        this.markDirty()
        return this
    }
    maxZoomScale(value: double | undefined): this {
        const value_casted = value as (double | undefined)
        this.getPeer()?.setMaxZoomScaleAttribute(value_casted)
        this.markDirty()
        return this
    }
    minZoomScale(value: double | undefined): this {
        const value_casted = value as (double | undefined)
        this.getPeer()?.setMinZoomScaleAttribute(value_casted)
        this.markDirty()
        return this
    }
    zoomScale(value: double | Bindable<double> | undefined): this {
        const value_casted = value as (double | Bindable<double> | undefined)
        this.getPeer()?.setZoomScaleAttribute(value_casted)
        this.markDirty()
        return this
    }
    enableBouncesZoom(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setEnableBouncesZoomAttribute(value_casted)
        this.markDirty()
        return this
    }
    onWillScroll(value: ScrollOnWillScrollCallback | undefined): this {
        const value_casted = value as (ScrollOnWillScrollCallback | undefined)
        this.getPeer()?.setOnWillScrollAttribute(value_casted)
        this.markDirty()
        return this
    }
    onDidScroll(value: ScrollOnScrollCallback | undefined): this {
        const value_casted = value as (ScrollOnScrollCallback | undefined)
        this.getPeer()?.setOnDidScrollAttribute(value_casted)
        this.markDirty()
        return this
    }
    onScrollEdge(value: OnScrollEdgeCallback | undefined): this {
        const value_casted = value as (OnScrollEdgeCallback | undefined)
        this.getPeer()?.setOnScrollEdgeAttribute(value_casted)
        this.markDirty()
        return this
    }
    onScrollStart(value: VoidCallback | undefined): this {
        const value_casted = value as (VoidCallback | undefined)
        this.getPeer()?.setOnScrollStartAttribute(value_casted)
        this.markDirty()
        return this
    }
    onScrollStop(value: VoidCallback | undefined): this {
        const value_casted = value as (VoidCallback | undefined)
        this.getPeer()?.setOnScrollStopAttribute(value_casted)
        this.markDirty()
        return this
    }
    onDidZoom(value: ScrollOnDidZoomCallback | undefined): this {
        const value_casted = value as (ScrollOnDidZoomCallback | undefined)
        this.getPeer()?.setOnDidZoomAttribute(value_casted)
        this.markDirty()
        return this
    }
    onZoomStart(value: VoidCallback | undefined): this {
        const value_casted = value as (VoidCallback | undefined)
        this.getPeer()?.setOnZoomStartAttribute(value_casted)
        this.markDirty()
        return this
    }
    onZoomStop(value: VoidCallback | undefined): this {
        const value_casted = value as (VoidCallback | undefined)
        this.getPeer()?.setOnZoomStopAttribute(value_casted)
        this.markDirty()
        return this
    }
    scrollBar(value: BarState | undefined): this {
        const value_casted = value as (BarState | undefined)
        this.getPeer()?.setScrollBarAttribute(value_casted)
        this.markDirty()
        return this
    }
    scrollBarColor(value: Color | int32 | string | Resource | undefined): this {
        const value_casted = value as (Color | int32 | string | Resource | undefined)
        this.getPeer()?.setScrollBarColorAttribute(value_casted)
        this.markDirty()
        return this
    }
    scrollBarWidth(value: double | string | undefined): this {
        const value_casted = value as (double | string | undefined)
        this.getPeer()?.setScrollBarWidthAttribute(value_casted)
        this.markDirty()
        return this
    }
    onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        const value_casted = value as (OnScrollFrameBeginCallback | undefined)
        this.getPeer()?.setOnScrollFrameBeginAttribute(value_casted)
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
    scrollSnap(value: ScrollSnapOptions | undefined): this {
        const value_casted = value as (ScrollSnapOptions | undefined)
        this.getPeer()?.setScrollSnapAttribute(value_casted)
        this.markDirty()
        return this
    }
    enablePaging(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setEnablePagingAttribute(value_casted)
        this.markDirty()
        return this
    }
    initialOffset(value: OffsetOptions | undefined): this {
        const value_casted = value as (OffsetOptions | undefined)
        this.getPeer()?.setInitialOffsetAttribute(value_casted)
        this.markDirty()
        return this
    }
    edgeEffect(edgeEffect: EdgeEffect | undefined, options?: EdgeEffectOptions | undefined): this {
        const edgeEffect_casted = edgeEffect as (EdgeEffect | undefined)
        const options_casted = options as (EdgeEffectOptions | undefined)
        this.getPeer()?.setEdgeEffectAttribute(edgeEffect_casted, options_casted)
        this.markDirty()
        return this
    }
    attributeModifier(value: AttributeModifier<ScrollAttribute> | AttributeModifier<ScrollableCommonMethod> |
        AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}
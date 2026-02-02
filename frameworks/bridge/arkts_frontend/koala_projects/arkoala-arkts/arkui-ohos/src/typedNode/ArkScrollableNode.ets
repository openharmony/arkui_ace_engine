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

import { int32 } from '@koalaui/common'
import { ArkBaseNode } from './ArkBaseNode';
import {
  ScrollableCommonMethod,
  ArkScrollableCommonMethodPeer,
  BarState,
  Color,
  NestedScrollOptions,
  ContentClipMode,
  CrownSensitivity,
  EdgeEffect,
  EdgeEffectOptions,
  FadingEdgeOptions,
  AttributeModifier,
  CommonMethod,
  ScrollBarMargin,
  VoidCallback,
  OnWillStopDraggingCallback,
  OnDidStopDraggingCallback
} from '../framework';
import { RectShape } from '@ohos.arkui.shape'
import { Resource } from 'global.resource'
export class ArkScrollableNode extends ArkBaseNode implements ScrollableCommonMethod {
    getPeer() : ArkScrollableCommonMethodPeer {
        return this.peer as ArkScrollableCommonMethodPeer
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
    scrollBarMargin(value: ScrollBarMargin | undefined): this {
        const value_casted = value as (ScrollBarMargin | undefined)
        this.getPeer()?.setScrollBarMarginAttribute(value_casted)
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
    contentStartOffset(value: double | Resource | undefined): this {
        const value_casted = value as (double | Resource | undefined)
        this.getPeer()?.setContentStartOffsetAttribute(value_casted)
        this.markDirty()
        return this
    }
    contentEndOffset(value: double | Resource | undefined): this {
        const value_casted = value as (double | Resource | undefined)
        this.getPeer()?.setContentEndOffsetAttribute(value_casted)
        this.markDirty()
        return this
    }
    onWillStartDragging(value: VoidCallback | undefined): this {
        const value_casted = value as (VoidCallback | undefined)
        this.getPeer()?.setOnWillStartDraggingAttribute(value_casted)
        this.markDirty()
        return this
    }
    onWillStopDragging(value: OnWillStopDraggingCallback | undefined): this {
        const value_casted = value as (OnWillStopDraggingCallback | undefined)
        this.getPeer()?.setOnWillStopDraggingAttribute(value_casted)
        this.markDirty()
        return this
    }
    onDidStopDragging(value: OnDidStopDraggingCallback | undefined): this {
        const value_casted = value as (OnDidStopDraggingCallback | undefined)
        this.getPeer()?.setOnDidStopDraggingAttribute(value_casted)
        this.markDirty()
        return this
    }
    onWillStartFling(value: VoidCallback | undefined): this {
        const value_casted = value as (VoidCallback | undefined)
        this.getPeer()?.setOnWillStartFlingAttribute(value_casted)
        this.markDirty()
        return this
    }
    onDidStopFling(value: VoidCallback | undefined): this {
        const value_casted = value as (VoidCallback | undefined)
        this.getPeer()?.setOnDidStopFlingAttribute(value_casted)
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
    flingSpeedLimit(value: double | undefined): this {
        const value_casted = value as (double | undefined)
        this.getPeer()?.setFlingSpeedLimitAttribute(value_casted)
        this.markDirty()
        return this
    }
    clipContent(value: ContentClipMode | RectShape | undefined): this {
        const value_casted = value as (ContentClipMode | RectShape | undefined)
        this.getPeer()?.setClipContentAttribute(value_casted)
        this.markDirty()
        return this
    }
    digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        const value_casted = value as (CrownSensitivity | undefined)
        this.getPeer()?.setDigitalCrownSensitivityAttribute(value_casted)
        this.markDirty()
        return this
    }
    backToTop(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setBackToTopAttribute(value_casted)
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
    fadingEdge(enabled: boolean | undefined, options?: FadingEdgeOptions | undefined): this {
        const enabled_casted = enabled as (boolean | undefined)
        const options_casted = options as (FadingEdgeOptions | undefined)
        this.getPeer()?.setFadingEdgeAttribute(enabled_casted, options_casted)
        this.markDirty()
        return this
    }
    attributeModifier(value: AttributeModifier<ScrollableCommonMethod> |
        AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}
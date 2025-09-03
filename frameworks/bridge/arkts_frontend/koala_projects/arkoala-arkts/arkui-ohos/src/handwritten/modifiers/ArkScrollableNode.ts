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

import { ArkBaseNode } from "./ArkBaseNode";
import { ScrollableCommonMethod, ArkScrollableCommonMethodPeer, BarState, Color, NestedScrollOptions, ContentClipMode,
    CrownSensitivity, EdgeEffect, EdgeEffectOptions, FadingEdgeOptions } from "../../component";
import { RectShape } from "@ohos/arkui/shape"
import { Resource } from "global.resource"
export class ArkScrollableNode extends ArkBaseNode implements ScrollableCommonMethod {
    getPeer() : ArkScrollableCommonMethodPeer {
        return this.peer as ArkScrollableCommonMethodPeer
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
    onScroll(value: ((first: number,last: number) => void) | undefined): this {
        const value_casted = value as (((first: number,last: number) => void) | undefined)
        this.getPeer()?.onScrollAttribute(value_casted)
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
    flingSpeedLimit(value: number | undefined): this {
        const value_casted = value as (number | undefined)
        this.getPeer()?.flingSpeedLimitAttribute(value_casted)
        return this
    }
    clipContent(value: ContentClipMode | RectShape | undefined): this {
        const value_casted = value as (ContentClipMode | RectShape | undefined)
        this.getPeer()?.clipContentAttribute(value_casted)
        return this
    }
    digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        const value_casted = value as (CrownSensitivity | undefined)
        this.getPeer()?.digitalCrownSensitivityAttribute(value_casted)
        return this
    }
    backToTop(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.backToTopAttribute(value_casted)
        return this
    }
    edgeEffect(edgeEffect: EdgeEffect | undefined, options?: EdgeEffectOptions | undefined): this {
        const edgeEffect_casted = edgeEffect as (EdgeEffect | undefined)
        const options_casted = options as (EdgeEffectOptions | undefined)
        this.getPeer()?.edgeEffectAttribute(edgeEffect_casted, options_casted)
        return this
    }
    fadingEdge(enabled: boolean | undefined, options?: FadingEdgeOptions | undefined): this {
        const enabled_casted = enabled as (boolean | undefined)
        const options_casted = options as (FadingEdgeOptions | undefined)
        this.getPeer()?.fadingEdgeAttribute(enabled_casted, options_casted)
        return this
    }
}
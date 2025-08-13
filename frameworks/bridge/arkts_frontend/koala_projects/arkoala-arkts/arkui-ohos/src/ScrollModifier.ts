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

import { ScrollableCommonMethodModifier } from './ScrollableCommonMethodModifier';
import { AttributeUpdaterFlag } from './CommonMethodModifier';
import {
    ArkScrollPeer,
    ScrollDirection,
    ScrollOnWillScrollCallback,
    ScrollOnScrollCallback,
    OnScrollEdgeCallback,
    OnScrollFrameBeginCallback,
    ScrollSnapOptions,
    OffsetOptions,
    ScrollAttribute
} from './component/scroll';
import { ScrollableCommonMethod, NestedScrollOptions, CommonMethod, EdgeEffectOptions, AttributeModifier } from './component/common';
import { ScrollState } from './component/list';
import { ScrollSource, Edge, BarState, Color, EdgeEffect } from './component/enums';
import { VoidCallback } from './component/units';
import { Resource } from 'global.resource';
export class ScrollModifier extends ScrollableCommonMethodModifier implements ScrollAttribute, AttributeModifier<ScrollAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId;
    }
    isUpdater: () => boolean = () => false;
    applyNormalAttribute(instance: ScrollAttribute): void {}
    applyPressedAttribute(instance: ScrollAttribute): void {}
    applyFocusedAttribute(instance: ScrollAttribute): void {}
    applyDisabledAttribute(instance: ScrollAttribute): void {}
    applySelectedAttribute(instance: ScrollAttribute): void {}
    _scrollable_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _scrollable_0_0value?: ScrollDirection | undefined;
    _onWillScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _onWillScroll_0_0value?: ScrollOnWillScrollCallback | undefined;
    _onDidScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _onDidScroll_0_0value?: ScrollOnScrollCallback | undefined;
    _onScrollEdge_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _onScrollEdge_0_0value?: OnScrollEdgeCallback | undefined;
    _onScrollStart_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _onScrollStart_0_0value?: VoidCallback | undefined;
    _onScrollStop_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _onScrollStop_0_0value?: VoidCallback | undefined;
    _scrollBar_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _scrollBar_0_0value?: BarState | undefined;
    _scrollBarColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _scrollBarColor_0_0value?: Color | number | string | undefined;
    _scrollBarWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _scrollBarWidth_0_0value?: number | string | undefined;
    _onScrollFrameBegin_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _onScrollFrameBegin_0_0value?: OnScrollFrameBeginCallback | undefined;
    _nestedScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _nestedScroll_0_0value?: NestedScrollOptions | undefined;
    _enableScrollInteraction_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _enableScrollInteraction_0_0value?: boolean | undefined;
    _friction_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _friction_0_0value?: number | Resource | undefined;
    _scrollSnap_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _scrollSnap_0_0value?: ScrollSnapOptions | undefined;
    _enablePaging_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _enablePaging_0_0value?: boolean | undefined;
    _initialOffset_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _initialOffset_0_0value?: OffsetOptions | undefined;
    _edgeEffect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _edgeEffect_0_0value?: EdgeEffect | undefined;
    _edgeEffect_0_1value?: EdgeEffectOptions | undefined;
    applyModifierPatch(peer: ArkScrollPeer): void {
        super.applyModifierPatch(peer);
        if (this._scrollable_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._scrollable_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.scrollableAttribute(this._scrollable_0_0value as ScrollDirection | undefined);
                    this._scrollable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._scrollable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._scrollable_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.scrollableAttribute(undefined as ScrollDirection | undefined);
                }
            }
        }
        if (this._onWillScroll_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onWillScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onWillScrollAttribute(this._onWillScroll_0_0value as ScrollOnWillScrollCallback | undefined);
                    this._onWillScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWillScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWillScroll_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onWillScrollAttribute(undefined as ScrollOnWillScrollCallback | undefined);
                }
            }
        }
        if (this._onDidScroll_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onDidScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onDidScrollAttribute(this._onDidScroll_0_0value as ScrollOnScrollCallback | undefined);
                    this._onDidScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDidScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDidScroll_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onDidScrollAttribute(undefined as ScrollOnScrollCallback | undefined);
                }
            }
        }
        if (this._onScrollEdge_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onScrollEdge_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onScrollEdgeAttribute(this._onScrollEdge_0_0value as OnScrollEdgeCallback | undefined);
                    this._onScrollEdge_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScrollEdge_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScrollEdge_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onScrollEdgeAttribute(undefined as OnScrollEdgeCallback | undefined);
                }
            }
        }
        if (this._onScrollStart_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onScrollStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onScrollStartAttribute(this._onScrollStart_0_0value as VoidCallback | undefined);
                    this._onScrollStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScrollStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScrollStart_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onScrollStartAttribute(undefined as VoidCallback | undefined);
                }
            }
        }
        if (this._onScrollStop_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onScrollStop_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onScrollStopAttribute(this._onScrollStop_0_0value as VoidCallback | undefined);
                    this._onScrollStop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScrollStop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScrollStop_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onScrollStopAttribute(undefined as VoidCallback | undefined);
                }
            }
        }
        if (this._scrollBar_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._scrollBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.scrollBarAttribute(this._scrollBar_0_0value as BarState | undefined);
                    this._scrollBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._scrollBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._scrollBar_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.scrollBarAttribute(undefined as BarState | undefined);
                }
            }
        }
        if (this._scrollBarColor_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._scrollBarColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.scrollBarColorAttribute(this._scrollBarColor_0_0value as Color | number | string | undefined);
                    this._scrollBarColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._scrollBarColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._scrollBarColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.scrollBarColorAttribute(undefined as Color | number | string | undefined);
                }
            }
        }
        if (this._scrollBarWidth_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._scrollBarWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.scrollBarWidthAttribute(this._scrollBarWidth_0_0value as number | string | undefined);
                    this._scrollBarWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._scrollBarWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._scrollBarWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.scrollBarWidthAttribute(undefined as number | string | undefined);
                }
            }
        }
        if (this._onScrollFrameBegin_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onScrollFrameBegin_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onScrollFrameBeginAttribute(this._onScrollFrameBegin_0_0value as OnScrollFrameBeginCallback | undefined);
                    this._onScrollFrameBegin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScrollFrameBegin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScrollFrameBegin_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onScrollFrameBeginAttribute(undefined as OnScrollFrameBeginCallback | undefined);
                }
            }
        }
        if (this._nestedScroll_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._nestedScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.nestedScrollAttribute(this._nestedScroll_0_0value as NestedScrollOptions | undefined);
                    this._nestedScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._nestedScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._nestedScroll_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.nestedScrollAttribute(undefined as NestedScrollOptions | undefined);
                }
            }
        }
        if (this._enableScrollInteraction_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._enableScrollInteraction_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.enableScrollInteractionAttribute(this._enableScrollInteraction_0_0value as boolean | undefined);
                    this._enableScrollInteraction_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableScrollInteraction_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableScrollInteraction_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.enableScrollInteractionAttribute(undefined as boolean | undefined);
                }
            }
        }
        if (this._friction_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._friction_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.frictionAttribute(this._friction_0_0value as number | Resource | undefined);
                    this._friction_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._friction_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._friction_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.frictionAttribute(undefined as number | Resource | undefined);
                }
            }
        }
        if (this._scrollSnap_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._scrollSnap_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.scrollSnapAttribute(this._scrollSnap_0_0value as ScrollSnapOptions | undefined);
                    this._scrollSnap_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._scrollSnap_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._scrollSnap_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.scrollSnapAttribute(undefined as ScrollSnapOptions | undefined);
                }
            }
        }
        if (this._enablePaging_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._enablePaging_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.enablePagingAttribute(this._enablePaging_0_0value as boolean | undefined);
                    this._enablePaging_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enablePaging_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enablePaging_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.enablePagingAttribute(undefined as boolean | undefined);
                }
            }
        }
        if (this._initialOffset_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._initialOffset_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.initialOffsetAttribute(this._initialOffset_0_0value as OffsetOptions | undefined);
                    this._initialOffset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._initialOffset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._initialOffset_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.initialOffsetAttribute(undefined as OffsetOptions | undefined);
                }
            }
        }
        if (this._edgeEffect_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._edgeEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.edgeEffectAttribute(
                        this._edgeEffect_0_0value as EdgeEffect | undefined,
                        this._edgeEffect_0_1value as EdgeEffectOptions | undefined
                    );
                    this._edgeEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._edgeEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._edgeEffect_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.edgeEffectAttribute(undefined as EdgeEffect | undefined, undefined as EdgeEffectOptions | undefined | undefined);
                }
            }
        }
    }
    mergeModifier(modifier: ScrollModifier): void {
        super.mergeModifier(modifier);
        if (modifier._scrollable_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._scrollable_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.scrollable(modifier._scrollable_0_0value);
                    break;
                }
                default: {
                    this.scrollable(undefined as ScrollDirection | undefined);
                }
            }
        }
        if (modifier._onWillScroll_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onWillScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onWillScroll(modifier._onWillScroll_0_0value);
                    break;
                }
                default: {
                    this.onWillScroll(undefined as ScrollOnWillScrollCallback | undefined);
                }
            }
        }
        if (modifier._onDidScroll_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onDidScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDidScroll(modifier._onDidScroll_0_0value);
                    break;
                }
                default: {
                    this.onDidScroll(undefined as ScrollOnScrollCallback | undefined);
                }
            }
        }
        if (modifier._onScrollEdge_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onScrollEdge_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onScrollEdge(modifier._onScrollEdge_0_0value);
                    break;
                }
                default: {
                    this.onScrollEdge(undefined as OnScrollEdgeCallback | undefined);
                }
            }
        }
        if (modifier._onScrollStart_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onScrollStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onScrollStart(modifier._onScrollStart_0_0value);
                    break;
                }
                default: {
                    this.onScrollStart(undefined as VoidCallback | undefined);
                }
            }
        }
        if (modifier._onScrollStop_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onScrollStop_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onScrollStop(modifier._onScrollStop_0_0value);
                    break;
                }
                default: {
                    this.onScrollStop(undefined as VoidCallback | undefined);
                }
            }
        }
        if (modifier._scrollBar_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._scrollBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.scrollBar(modifier._scrollBar_0_0value);
                    break;
                }
                default: {
                    this.scrollBar(undefined as BarState | undefined);
                }
            }
        }
        if (modifier._scrollBarColor_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._scrollBarColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.scrollBarColor(modifier._scrollBarColor_0_0value);
                    break;
                }
                default: {
                    this.scrollBarColor(undefined as Color | number | string | undefined);
                }
            }
        }
        if (modifier._scrollBarWidth_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._scrollBarWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.scrollBarWidth(modifier._scrollBarWidth_0_0value);
                    break;
                }
                default: {
                    this.scrollBarWidth(undefined as number | string | undefined);
                }
            }
        }
        if (modifier._onScrollFrameBegin_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onScrollFrameBegin_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onScrollFrameBegin(modifier._onScrollFrameBegin_0_0value);
                    break;
                }
                default: {
                    this.onScrollFrameBegin(undefined as OnScrollFrameBeginCallback | undefined);
                }
            }
        }
        if (modifier._nestedScroll_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._nestedScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.nestedScroll(modifier._nestedScroll_0_0value);
                    break;
                }
                default: {
                    this.nestedScroll(undefined as NestedScrollOptions | undefined);
                }
            }
        }
        if (modifier._enableScrollInteraction_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._enableScrollInteraction_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableScrollInteraction(modifier._enableScrollInteraction_0_0value);
                    break;
                }
                default: {
                    this.enableScrollInteraction(undefined as boolean | undefined);
                }
            }
        }
        if (modifier._friction_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._friction_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.friction(modifier._friction_0_0value);
                    break;
                }
                default: {
                    this.friction(undefined as number | Resource | undefined);
                }
            }
        }
        if (modifier._scrollSnap_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._scrollSnap_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.scrollSnap(modifier._scrollSnap_0_0value);
                    break;
                }
                default: {
                    this.scrollSnap(undefined as ScrollSnapOptions | undefined);
                }
            }
        }
        if (modifier._enablePaging_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._enablePaging_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enablePaging(modifier._enablePaging_0_0value);
                    break;
                }
                default: {
                    this.enablePaging(undefined as boolean | undefined);
                }
            }
        }
        if (modifier._initialOffset_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._initialOffset_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.initialOffset(modifier._initialOffset_0_0value);
                    break;
                }
                default: {
                    this.initialOffset(undefined as OffsetOptions | undefined);
                }
            }
        }
        if (modifier._edgeEffect_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._edgeEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.edgeEffect(modifier._edgeEffect_0_0value, modifier._edgeEffect_0_1value);
                    break;
                }
                default: {
                    this.edgeEffect(undefined as EdgeEffect | undefined, undefined as EdgeEffectOptions | undefined | undefined);
                }
            }
        }
    }
    scrollable(value: ScrollDirection | undefined): this {
        if (this._scrollable_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._scrollable_0_flag = AttributeUpdaterFlag.UPDATE;
            this._scrollable_0_0value = value;
        } else {
            this._scrollable_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    onWillScroll(value: ScrollOnWillScrollCallback | undefined): this {
        if (this._onWillScroll_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._onWillScroll_0_flag = AttributeUpdaterFlag.UPDATE;
            this._onWillScroll_0_0value = value;
        } else {
            this._onWillScroll_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    onDidScroll(value: ScrollOnScrollCallback | undefined): this {
        if (this._onDidScroll_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._onDidScroll_0_flag = AttributeUpdaterFlag.UPDATE;
            this._onDidScroll_0_0value = value;
        } else {
            this._onDidScroll_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    onScrollEdge(value: OnScrollEdgeCallback | undefined): this {
        if (this._onScrollEdge_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._onScrollEdge_0_flag = AttributeUpdaterFlag.UPDATE;
            this._onScrollEdge_0_0value = value;
        } else {
            this._onScrollEdge_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    onScrollStart(value: VoidCallback | undefined): this {
        if (this._onScrollStart_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._onScrollStart_0_flag = AttributeUpdaterFlag.UPDATE;
            this._onScrollStart_0_0value = value;
        } else {
            this._onScrollStart_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    onScrollStop(value: VoidCallback | undefined): this {
        if (this._onScrollStop_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._onScrollStop_0_flag = AttributeUpdaterFlag.UPDATE;
            this._onScrollStop_0_0value = value;
        } else {
            this._onScrollStop_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    scrollBar(value: BarState | undefined): this {
        if (this._scrollBar_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._scrollBar_0_flag = AttributeUpdaterFlag.UPDATE;
            this._scrollBar_0_0value = value;
        } else {
            this._scrollBar_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    scrollBarColor(value: Color | number | string | undefined): this {
        if (this._scrollBarColor_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._scrollBarColor_0_flag = AttributeUpdaterFlag.UPDATE;
            this._scrollBarColor_0_0value = value;
        } else {
            this._scrollBarColor_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    scrollBarWidth(value: number | string | undefined): this {
        if (this._scrollBarWidth_0_flag == AttributeUpdaterFlag.INITIAL || this._scrollBarWidth_0_0value !== value) {
            this._scrollBarWidth_0_flag = AttributeUpdaterFlag.UPDATE;
            this._scrollBarWidth_0_0value = value;
        } else {
            this._scrollBarWidth_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        if (this._onScrollFrameBegin_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._onScrollFrameBegin_0_flag = AttributeUpdaterFlag.UPDATE;
            this._onScrollFrameBegin_0_0value = value;
        } else {
            this._onScrollFrameBegin_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    nestedScroll(value: NestedScrollOptions | undefined): this {
        if (this._nestedScroll_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._nestedScroll_0_flag = AttributeUpdaterFlag.UPDATE;
            this._nestedScroll_0_0value = value;
        } else {
            this._nestedScroll_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    enableScrollInteraction(value: boolean | undefined): this {
        if (this._enableScrollInteraction_0_flag == AttributeUpdaterFlag.INITIAL || this._enableScrollInteraction_0_0value !== value) {
            this._enableScrollInteraction_0_flag = AttributeUpdaterFlag.UPDATE;
            this._enableScrollInteraction_0_0value = value;
        } else {
            this._enableScrollInteraction_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    friction(value: number | Resource | undefined): this {
        if (this._friction_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._friction_0_flag = AttributeUpdaterFlag.UPDATE;
            this._friction_0_0value = value;
        } else {
            this._friction_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    scrollSnap(value: ScrollSnapOptions | undefined): this {
        if (this._scrollSnap_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._scrollSnap_0_flag = AttributeUpdaterFlag.UPDATE;
            this._scrollSnap_0_0value = value;
        } else {
            this._scrollSnap_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    enablePaging(value: boolean | undefined): this {
        if (this._enablePaging_0_flag == AttributeUpdaterFlag.INITIAL || this._enablePaging_0_0value !== value) {
            this._enablePaging_0_flag = AttributeUpdaterFlag.UPDATE;
            this._enablePaging_0_0value = value;
        } else {
            this._enablePaging_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    initialOffset(value: OffsetOptions | undefined): this {
        if (this._initialOffset_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._initialOffset_0_flag = AttributeUpdaterFlag.UPDATE;
            this._initialOffset_0_0value = value;
        } else {
            this._initialOffset_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    edgeEffect(edgeEffect: EdgeEffect | undefined, options?: EdgeEffectOptions): this {
        if (this._edgeEffect_0_flag == AttributeUpdaterFlag.INITIAL || true || true) {
            this._edgeEffect_0_flag = AttributeUpdaterFlag.UPDATE;
            this._edgeEffect_0_0value = edgeEffect;
            this._edgeEffect_0_1value = options;
        } else {
            this._edgeEffect_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
}

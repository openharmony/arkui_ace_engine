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

import { CommonMethodModifier } from "./CommonMethodModifier"
import { ModifierState } from './CommonModifier'
import { AttributeModifier, extractors } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkScrollableCommonMethodPeer, CommonMethod, NestedScrollOptions, OnWillStopDraggingCallback, OnDidStopDraggingCallback, ContentClipMode, EdgeEffectOptions, FadingEdgeOptions, ScrollableCommonMethod } from "./component/common"
import { int32 } from "@koalaui/common"
import { BarState, Color, CrownSensitivity, EdgeEffect } from "./component/enums"
import { Resource } from "global.resource"
import { VoidCallback, ScrollBarMargin } from "./component/units"
import { RectShape } from "@ohos.arkui.shape"
export class ScrollableCommonMethodModifier extends CommonMethodModifier implements ScrollableCommonMethod,AttributeModifier<ScrollableCommonMethod> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: ScrollableCommonMethod): void { }
    applyPressedAttribute(instance: ScrollableCommonMethod): void { }
    applyFocusedAttribute(instance: ScrollableCommonMethod): void { }
    applyDisabledAttribute(instance: ScrollableCommonMethod): void { }
    applySelectedAttribute(instance: ScrollableCommonMethod): void { }
    _scrollBar_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _scrollBar_0_0value?: BarState | undefined
    _scrollBarColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _scrollBarColor_0_0value?: Color | int32 | string | Resource | undefined
    _scrollBarWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _scrollBarWidth_0_0value?: double | string | undefined
    _scrollBarMargin_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _scrollBarMargin_0_0value?: ScrollBarMargin | undefined
    _nestedScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _nestedScroll_0_0value?: NestedScrollOptions | undefined
    _enableScrollInteraction_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableScrollInteraction_0_0value?: boolean | undefined
    _friction_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _friction_0_0value?: double | Resource | undefined
    _contentStartOffset_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _contentStartOffset_0_0value?: double | Resource | undefined
    _contentEndOffset_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _contentEndOffset_0_0value?: double | Resource | undefined
    _onWillStartDragging_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWillStartDragging_0_0value?: VoidCallback | undefined
    _onWillStopDragging_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWillStopDragging_0_0value?: OnWillStopDraggingCallback | undefined
    _onDidStopDragging_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDidStopDragging_0_0value?: OnDidStopDraggingCallback | undefined
    _onWillStartFling_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWillStartFling_0_0value?: VoidCallback | undefined
    _onDidStopFling_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDidStopFling_0_0value?: VoidCallback | undefined
    _onReachStart_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onReachStart_0_0value?: (() => void) | undefined
    _onReachEnd_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onReachEnd_0_0value?: (() => void) | undefined
    _onScrollStart_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onScrollStart_0_0value?: (() => void) | undefined
    _onScrollStop_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onScrollStop_0_0value?: (() => void) | undefined
    _flingSpeedLimit_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _flingSpeedLimit_0_0value?: double | undefined
    _clipContent_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _clipContent_0_0value?: ContentClipMode | RectShape | undefined
    _digitalCrownSensitivity_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _digitalCrownSensitivity_0_0value?: CrownSensitivity | undefined
    _backToTop_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _backToTop_0_0value?: boolean | undefined
    _edgeEffect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _edgeEffect_0_0value?: EdgeEffect | undefined
    _edgeEffect_0_1value?: EdgeEffectOptions | undefined
    _fadingEdge_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fadingEdge_0_0value?: boolean | undefined
    _fadingEdge_0_1value?: FadingEdgeOptions | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkScrollableCommonMethodPeer;
        if (this._scrollBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._scrollBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setScrollBarAttribute((this._scrollBar_0_0value as BarState | undefined));
                    this._scrollBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._scrollBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._scrollBar_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setScrollBarAttribute((undefined as BarState | undefined));
                }
            }
        }
        if (this._scrollBarColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._scrollBarColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setScrollBarColorAttribute((this._scrollBarColor_0_0value as Color | int32 | string | Resource | undefined));
                    this._scrollBarColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._scrollBarColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._scrollBarColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setScrollBarColorAttribute((undefined as Color | int32 | string | Resource | undefined));
                }
            }
        }
        if (this._scrollBarWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._scrollBarWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setScrollBarWidthAttribute((this._scrollBarWidth_0_0value as double | string | undefined));
                    this._scrollBarWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._scrollBarWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._scrollBarWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setScrollBarWidthAttribute((undefined as double | string | undefined));
                }
            }
        }
        if (this._scrollBarMargin_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._scrollBarMargin_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setScrollBarMarginAttribute((this._scrollBarMargin_0_0value as ScrollBarMargin | undefined));
                    this._scrollBarMargin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._scrollBarMargin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._scrollBarMargin_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setScrollBarMarginAttribute((undefined as ScrollBarMargin | undefined));
                }
            }
        }
        if (this._nestedScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._nestedScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setNestedScrollAttribute((this._nestedScroll_0_0value as NestedScrollOptions | undefined));
                    this._nestedScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._nestedScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._nestedScroll_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setNestedScrollAttribute((undefined as NestedScrollOptions | undefined));
                }
            }
        }
        if (this._enableScrollInteraction_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableScrollInteraction_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableScrollInteractionAttribute((this._enableScrollInteraction_0_0value as boolean | undefined));
                    this._enableScrollInteraction_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableScrollInteraction_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableScrollInteraction_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableScrollInteractionAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._friction_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._friction_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFrictionAttribute((this._friction_0_0value as double | Resource | undefined));
                    this._friction_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._friction_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._friction_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFrictionAttribute((undefined as double | Resource | undefined));
                }
            }
        }
        if (this._contentStartOffset_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._contentStartOffset_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setContentStartOffsetAttribute((this._contentStartOffset_0_0value as double | Resource | undefined));
                    this._contentStartOffset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._contentStartOffset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._contentStartOffset_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setContentStartOffsetAttribute((undefined as double | Resource | undefined));
                }
            }
        }
        if (this._contentEndOffset_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._contentEndOffset_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setContentEndOffsetAttribute((this._contentEndOffset_0_0value as double | Resource | undefined));
                    this._contentEndOffset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._contentEndOffset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._contentEndOffset_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setContentEndOffsetAttribute((undefined as double | Resource | undefined));
                }
            }
        }
        if (this._onWillStartDragging_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onWillStartDragging_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnWillStartDraggingAttribute((this._onWillStartDragging_0_0value as VoidCallback | undefined));
                    this._onWillStartDragging_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWillStartDragging_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWillStartDragging_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnWillStartDraggingAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (this._onWillStopDragging_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onWillStopDragging_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnWillStopDraggingAttribute((this._onWillStopDragging_0_0value as OnWillStopDraggingCallback | undefined));
                    this._onWillStopDragging_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWillStopDragging_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWillStopDragging_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnWillStopDraggingAttribute((undefined as OnWillStopDraggingCallback | undefined));
                }
            }
        }
        if (this._onDidStopDragging_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDidStopDragging_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDidStopDraggingAttribute((this._onDidStopDragging_0_0value as OnDidStopDraggingCallback | undefined));
                    this._onDidStopDragging_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDidStopDragging_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDidStopDragging_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDidStopDraggingAttribute((undefined as OnDidStopDraggingCallback | undefined));
                }
            }
        }
        if (this._onWillStartFling_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onWillStartFling_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnWillStartFlingAttribute((this._onWillStartFling_0_0value as VoidCallback | undefined));
                    this._onWillStartFling_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWillStartFling_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWillStartFling_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnWillStartFlingAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (this._onDidStopFling_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDidStopFling_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDidStopFlingAttribute((this._onDidStopFling_0_0value as VoidCallback | undefined));
                    this._onDidStopFling_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDidStopFling_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDidStopFling_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDidStopFlingAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (this._onReachStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onReachStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnReachStartAttribute((this._onReachStart_0_0value as (() => void) | undefined));
                    this._onReachStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onReachStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onReachStart_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnReachStartAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onReachEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onReachEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnReachEndAttribute((this._onReachEnd_0_0value as (() => void) | undefined));
                    this._onReachEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onReachEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onReachEnd_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnReachEndAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onScrollStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onScrollStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnScrollStartAttribute((this._onScrollStart_0_0value as (() => void) | undefined));
                    this._onScrollStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScrollStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScrollStart_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnScrollStartAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onScrollStop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onScrollStop_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnScrollStopAttribute((this._onScrollStop_0_0value as (() => void) | undefined));
                    this._onScrollStop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScrollStop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScrollStop_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnScrollStopAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._flingSpeedLimit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._flingSpeedLimit_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFlingSpeedLimitAttribute((this._flingSpeedLimit_0_0value as double | undefined));
                    this._flingSpeedLimit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._flingSpeedLimit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._flingSpeedLimit_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFlingSpeedLimitAttribute((undefined as double | undefined));
                }
            }
        }
        if (this._clipContent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._clipContent_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setClipContentAttribute((this._clipContent_0_0value as ContentClipMode | RectShape | undefined));
                    this._clipContent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._clipContent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._clipContent_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setClipContentAttribute((undefined as ContentClipMode | RectShape | undefined));
                }
            }
        }
        if (this._digitalCrownSensitivity_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._digitalCrownSensitivity_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDigitalCrownSensitivityAttribute((this._digitalCrownSensitivity_0_0value as CrownSensitivity | undefined));
                    this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDigitalCrownSensitivityAttribute((undefined as CrownSensitivity | undefined));
                }
            }
        }
        if (this._backToTop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._backToTop_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBackToTopAttribute((this._backToTop_0_0value as boolean | undefined));
                    this._backToTop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._backToTop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._backToTop_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBackToTopAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._edgeEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._edgeEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEdgeEffectAttribute((this._edgeEffect_0_0value as EdgeEffect | undefined), (this._edgeEffect_0_1value as EdgeEffectOptions | undefined | undefined));
                    this._edgeEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._edgeEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._edgeEffect_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEdgeEffectAttribute((undefined as EdgeEffect | undefined), (undefined as EdgeEffectOptions | undefined | undefined));
                }
            }
        }
        if (this._fadingEdge_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fadingEdge_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFadingEdgeAttribute((this._fadingEdge_0_0value as boolean | undefined), (this._fadingEdge_0_1value as FadingEdgeOptions | undefined | undefined));
                    this._fadingEdge_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fadingEdge_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fadingEdge_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFadingEdgeAttribute((undefined as boolean | undefined), (undefined as FadingEdgeOptions | undefined | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: ScrollableCommonMethodModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._scrollBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._scrollBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.scrollBar(modifier._scrollBar_0_0value);
                    break;
                }
                default: {
                    this.scrollBar((undefined as BarState | undefined));
                }
            }
        }
        if (modifier._scrollBarColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._scrollBarColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.scrollBarColor(modifier._scrollBarColor_0_0value);
                    break;
                }
                default: {
                    this.scrollBarColor((undefined as Color | int32 | string | Resource | undefined));
                }
            }
        }
        if (modifier._scrollBarWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._scrollBarWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.scrollBarWidth(modifier._scrollBarWidth_0_0value);
                    break;
                }
                default: {
                    this.scrollBarWidth((undefined as double | string | undefined));
                }
            }
        }
        if (modifier._scrollBarMargin_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._scrollBarMargin_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.scrollBarMargin(modifier._scrollBarMargin_0_0value);
                    break;
                }
                default: {
                    this.scrollBarMargin((undefined as ScrollBarMargin | undefined));
                }
            }
        }
        if (modifier._nestedScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._nestedScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.nestedScroll(modifier._nestedScroll_0_0value);
                    break;
                }
                default: {
                    this.nestedScroll((undefined as NestedScrollOptions | undefined));
                }
            }
        }
        if (modifier._enableScrollInteraction_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableScrollInteraction_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableScrollInteraction(modifier._enableScrollInteraction_0_0value);
                    break;
                }
                default: {
                    this.enableScrollInteraction((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._friction_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._friction_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.friction(modifier._friction_0_0value);
                    break;
                }
                default: {
                    this.friction((undefined as double | Resource | undefined));
                }
            }
        }
        if (modifier._contentStartOffset_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._contentStartOffset_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.contentStartOffset(modifier._contentStartOffset_0_0value);
                    break;
                }
                default: {
                    this.contentStartOffset((undefined as double | Resource | undefined));
                }
            }
        }
        if (modifier._contentEndOffset_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._contentEndOffset_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.contentEndOffset(modifier._contentEndOffset_0_0value);
                    break;
                }
                default: {
                    this.contentEndOffset((undefined as double | Resource | undefined));
                }
            }
        }
        if (modifier._onWillStartDragging_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onWillStartDragging_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onWillStartDragging(modifier._onWillStartDragging_0_0value);
                    break;
                }
                default: {
                    this.onWillStartDragging((undefined as VoidCallback | undefined));
                }
            }
        }
        if (modifier._onWillStopDragging_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onWillStopDragging_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onWillStopDragging(modifier._onWillStopDragging_0_0value);
                    break;
                }
                default: {
                    this.onWillStopDragging((undefined as OnWillStopDraggingCallback | undefined));
                }
            }
        }
        if (modifier._onDidStopDragging_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDidStopDragging_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDidStopDragging(modifier._onDidStopDragging_0_0value);
                    break;
                }
                default: {
                    this.onDidStopDragging((undefined as OnDidStopDraggingCallback | undefined));
                }
            }
        }
        if (modifier._onWillStartFling_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onWillStartFling_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onWillStartFling(modifier._onWillStartFling_0_0value);
                    break;
                }
                default: {
                    this.onWillStartFling((undefined as VoidCallback | undefined));
                }
            }
        }
        if (modifier._onDidStopFling_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDidStopFling_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDidStopFling(modifier._onDidStopFling_0_0value);
                    break;
                }
                default: {
                    this.onDidStopFling((undefined as VoidCallback | undefined));
                }
            }
        }
        if (modifier._onReachStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onReachStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onReachStart(modifier._onReachStart_0_0value);
                    break;
                }
                default: {
                    this.onReachStart((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onReachEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onReachEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onReachEnd(modifier._onReachEnd_0_0value);
                    break;
                }
                default: {
                    this.onReachEnd((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onScrollStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onScrollStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onScrollStart(modifier._onScrollStart_0_0value);
                    break;
                }
                default: {
                    this.onScrollStart((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onScrollStop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onScrollStop_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onScrollStop(modifier._onScrollStop_0_0value);
                    break;
                }
                default: {
                    this.onScrollStop((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._flingSpeedLimit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._flingSpeedLimit_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.flingSpeedLimit(modifier._flingSpeedLimit_0_0value);
                    break;
                }
                default: {
                    this.flingSpeedLimit((undefined as double | undefined));
                }
            }
        }
        if (modifier._clipContent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._clipContent_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.clipContent(modifier._clipContent_0_0value);
                    break;
                }
                default: {
                    this.clipContent((undefined as ContentClipMode | RectShape | undefined));
                }
            }
        }
        if (modifier._digitalCrownSensitivity_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._digitalCrownSensitivity_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.digitalCrownSensitivity(modifier._digitalCrownSensitivity_0_0value);
                    break;
                }
                default: {
                    this.digitalCrownSensitivity((undefined as CrownSensitivity | undefined));
                }
            }
        }
        if (modifier._backToTop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._backToTop_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.backToTop(modifier._backToTop_0_0value);
                    break;
                }
                default: {
                    this.backToTop((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._edgeEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._edgeEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.edgeEffect(modifier._edgeEffect_0_0value, modifier._edgeEffect_0_1value);
                    break;
                }
                default: {
                    this.edgeEffect((undefined as EdgeEffect | undefined), (undefined as EdgeEffectOptions | undefined | undefined));
                }
            }
        }
        if (modifier._fadingEdge_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fadingEdge_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fadingEdge(modifier._fadingEdge_0_0value, modifier._fadingEdge_0_1value);
                    break;
                }
                default: {
                    this.fadingEdge((undefined as boolean | undefined), (undefined as FadingEdgeOptions | undefined | undefined));
                }
            }
        }
    }
    scrollBar(value: BarState | undefined): this {
        if (((this._scrollBar_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._scrollBar_0_flag = AttributeUpdaterFlag.UPDATE
            this._scrollBar_0_0value = value
        } else
        {
            this._scrollBar_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    scrollBarColor(value: Color | int32 | string | Resource | undefined): this {
        if (((this._scrollBarColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._scrollBarColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._scrollBarColor_0_0value = value
        } else
        {
            this._scrollBarColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    scrollBarWidth(value: double | string | undefined): this {
        if (((this._scrollBarWidth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._scrollBarWidth_0_0value) !== (value)))
        {
            this._scrollBarWidth_0_flag = AttributeUpdaterFlag.UPDATE
            this._scrollBarWidth_0_0value = value
        } else
        {
            this._scrollBarWidth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    scrollBarMargin(value: ScrollBarMargin | undefined): this {
        if (((this._scrollBarMargin_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._scrollBarMargin_0_0value) !== (value)))
        {
            this._scrollBarMargin_0_flag = AttributeUpdaterFlag.UPDATE
            this._scrollBarMargin_0_0value = value
        } else
        {
            this._scrollBarMargin_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    nestedScroll(value: NestedScrollOptions | undefined): this {
        if (((this._nestedScroll_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._nestedScroll_0_flag = AttributeUpdaterFlag.UPDATE
            this._nestedScroll_0_0value = value
        } else
        {
            this._nestedScroll_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableScrollInteraction(value: boolean | undefined): this {
        if (((this._enableScrollInteraction_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableScrollInteraction_0_0value) !== (value)))
        {
            this._enableScrollInteraction_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableScrollInteraction_0_0value = value
        } else
        {
            this._enableScrollInteraction_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    friction(value: double | Resource | undefined): this {
        if (((this._friction_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._friction_0_flag = AttributeUpdaterFlag.UPDATE
            this._friction_0_0value = value
        } else
        {
            this._friction_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    contentStartOffset(value: double | Resource | undefined): this {
        if (((this._contentStartOffset_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._contentStartOffset_0_flag = AttributeUpdaterFlag.UPDATE
            this._contentStartOffset_0_0value = value
        } else
        {
            this._contentStartOffset_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    contentEndOffset(value: double | Resource | undefined): this {
        if (((this._contentEndOffset_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._contentEndOffset_0_flag = AttributeUpdaterFlag.UPDATE
            this._contentEndOffset_0_0value = value
        } else
        {
            this._contentEndOffset_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onWillStartDragging(value: VoidCallback | undefined): this {
        if (((this._onWillStartDragging_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onWillStartDragging_0_flag = AttributeUpdaterFlag.UPDATE
            this._onWillStartDragging_0_0value = value
        } else
        {
            this._onWillStartDragging_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onWillStopDragging(value: OnWillStopDraggingCallback | undefined): this {
        if (((this._onWillStopDragging_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onWillStopDragging_0_flag = AttributeUpdaterFlag.UPDATE
            this._onWillStopDragging_0_0value = value
        } else
        {
            this._onWillStopDragging_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDidStopDragging(value: OnDidStopDraggingCallback | undefined): this {
        if (((this._onDidStopDragging_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDidStopDragging_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDidStopDragging_0_0value = value
        } else
        {
            this._onDidStopDragging_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onWillStartFling(value: VoidCallback | undefined): this {
        if (((this._onWillStartFling_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onWillStartFling_0_flag = AttributeUpdaterFlag.UPDATE
            this._onWillStartFling_0_0value = value
        } else
        {
            this._onWillStartFling_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDidStopFling(value: VoidCallback | undefined): this {
        if (((this._onDidStopFling_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDidStopFling_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDidStopFling_0_0value = value
        } else
        {
            this._onDidStopFling_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onReachStart(value: (() => void) | undefined): this {
        if (((this._onReachStart_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onReachStart_0_flag = AttributeUpdaterFlag.UPDATE
            this._onReachStart_0_0value = value
        } else
        {
            this._onReachStart_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onReachEnd(value: (() => void) | undefined): this {
        if (((this._onReachEnd_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onReachEnd_0_flag = AttributeUpdaterFlag.UPDATE
            this._onReachEnd_0_0value = value
        } else
        {
            this._onReachEnd_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onScrollStart(value: (() => void) | undefined): this {
        if (((this._onScrollStart_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onScrollStart_0_flag = AttributeUpdaterFlag.UPDATE
            this._onScrollStart_0_0value = value
        } else
        {
            this._onScrollStart_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onScrollStop(value: (() => void) | undefined): this {
        if (((this._onScrollStop_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onScrollStop_0_flag = AttributeUpdaterFlag.UPDATE
            this._onScrollStop_0_0value = value
        } else
        {
            this._onScrollStop_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    flingSpeedLimit(value: double | undefined): this {
        if (((this._flingSpeedLimit_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._flingSpeedLimit_0_0value) !== (value)))
        {
            this._flingSpeedLimit_0_flag = AttributeUpdaterFlag.UPDATE
            this._flingSpeedLimit_0_0value = value
        } else
        {
            this._flingSpeedLimit_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    clipContent(value: ContentClipMode | RectShape | undefined): this {
        if (((this._clipContent_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._clipContent_0_flag = AttributeUpdaterFlag.UPDATE
            this._clipContent_0_0value = value
        } else
        {
            this._clipContent_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        if (((this._digitalCrownSensitivity_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.UPDATE
            this._digitalCrownSensitivity_0_0value = value
        } else
        {
            this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    backToTop(value: boolean | undefined): this {
        if (((this._backToTop_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._backToTop_0_0value) !== (value)))
        {
            this._backToTop_0_flag = AttributeUpdaterFlag.UPDATE
            this._backToTop_0_0value = value
        } else
        {
            this._backToTop_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    edgeEffect(edgeEffect: EdgeEffect | undefined, options?: EdgeEffectOptions): this {
        if (((this._edgeEffect_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._edgeEffect_0_flag = AttributeUpdaterFlag.UPDATE
            this._edgeEffect_0_0value = edgeEffect
            this._edgeEffect_0_1value = options
        } else
        {
            this._edgeEffect_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fadingEdge(enabled: boolean | undefined, options?: FadingEdgeOptions): this {
        if (((this._fadingEdge_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._fadingEdge_0_0value) !== (enabled)) || (true))
        {
            this._fadingEdge_0_flag = AttributeUpdaterFlag.UPDATE
            this._fadingEdge_0_0value = enabled
            this._fadingEdge_0_1value = options
        } else
        {
            this._fadingEdge_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

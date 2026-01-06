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

import { CommonMethod, NestedScrollOptions, OnWillStopDraggingCallback, OnDidStopDraggingCallback, ContentClipMode, EdgeEffectOptions, FadingEdgeOptions, ScrollableCommonMethod, Bindable } from "./component/common"
import { BarState, Color, CrownSensitivity, EdgeEffect, ScrollSource, Edge } from "./component/enums"
import { Resource } from "global.resource"
import { VoidCallback } from "./component/units"
import { extractors, AttributeModifier } from "#handwritten"
import { RectShape } from "@ohos.arkui.shape"
import { ScrollableCommonMethodModifier } from "./ScrollableCommonMethodModifier"
import { CommonMethodModifier } from "./CommonMethodModifier"
import { ModifierState } from './CommonModifier'
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkScrollPeer, ScrollDirection, ScrollOnWillScrollCallback, ScrollOnScrollCallback, OnScrollEdgeCallback, ScrollOnDidZoomCallback, OnScrollFrameBeginCallback, ScrollSnapOptions, OffsetOptions, ScrollAttribute } from "./component/scroll"
import { int32 } from "@koalaui/common"
import { ScrollState } from "./component/list"
import { VoidCallback, ScrollBarMargin } from "./component/units"
export class ScrollModifier extends CommonMethodModifier implements ScrollAttribute,AttributeModifier<ScrollAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: ScrollAttribute): void { }
    applyPressedAttribute(instance: ScrollAttribute): void { }
    applyFocusedAttribute(instance: ScrollAttribute): void { }
    applyDisabledAttribute(instance: ScrollAttribute): void { }
    applySelectedAttribute(instance: ScrollAttribute): void { }
    _scrollable_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _scrollable_0_0value?: ScrollDirection | undefined
    _maxZoomScale_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maxZoomScale_0_0value?: double | undefined
    _minZoomScale_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _minZoomScale_0_0value?: double | undefined
    _zoomScale_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _zoomScale_0_0value?: double | Bindable<double> | undefined
    _enableBouncesZoom_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableBouncesZoom_0_0value?: boolean | undefined
    _onWillScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWillScroll_0_0value?: ScrollOnWillScrollCallback | undefined
    _onDidScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDidScroll_0_0value?: ScrollOnScrollCallback | undefined
    _onScrollEdge_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onScrollEdge_0_0value?: OnScrollEdgeCallback | undefined
    _onScrollStart_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onScrollStart_0_0value?: VoidCallback | undefined
    _onScrollStop_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onScrollStop_0_0value?: VoidCallback | undefined
    _onDidZoom_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDidZoom_0_0value?: ScrollOnDidZoomCallback | undefined
    _onZoomStart_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onZoomStart_0_0value?: VoidCallback | undefined
    _onZoomStop_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onZoomStop_0_0value?: VoidCallback | undefined
    _scrollBar_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _scrollBar_0_0value?: BarState | undefined
    _scrollBarColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _scrollBarColor_0_0value?: Color | int32 | string | Resource | undefined
    _scrollBarWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _scrollBarWidth_0_0value?: double | string | undefined
    _onScrollFrameBegin_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onScrollFrameBegin_0_0value?: OnScrollFrameBeginCallback | undefined
    _nestedScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _nestedScroll_0_0value?: NestedScrollOptions | undefined
    _enableScrollInteraction_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableScrollInteraction_0_0value?: boolean | undefined
    _friction_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _friction_0_0value?: double | Resource | undefined
    _scrollSnap_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _scrollSnap_0_0value?: ScrollSnapOptions | undefined
    _enablePaging_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enablePaging_0_0value?: boolean | undefined
    _initialOffset_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _initialOffset_0_0value?: OffsetOptions | undefined
    _edgeEffect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _edgeEffect_0_0value?: EdgeEffect | undefined
    _edgeEffect_0_1value?: EdgeEffectOptions | undefined
    _scrollBarMargin_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _scrollBarMargin_0_0value?: ScrollBarMargin | undefined
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
    _flingSpeedLimit_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _flingSpeedLimit_0_0value?: number | undefined
    _clipContent_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _clipContent_0_0value?: ContentClipMode | RectShape | undefined
    _digitalCrownSensitivity_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _digitalCrownSensitivity_0_0value?: CrownSensitivity | undefined
    _backToTop_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _backToTop_0_0value?: boolean | undefined
    _fadingEdge_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fadingEdge_0_0value?: boolean | undefined
    _fadingEdge_0_1value?: FadingEdgeOptions | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkScrollPeer;
        if (this._scrollable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._scrollable_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setScrollableAttribute((this._scrollable_0_0value as ScrollDirection | undefined));
                    this._scrollable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._scrollable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._scrollable_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setScrollableAttribute((undefined as ScrollDirection | undefined));
                }
            }
        }
        if (this._maxZoomScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._maxZoomScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMaxZoomScaleAttribute((this._maxZoomScale_0_0value as double | undefined));
                    this._maxZoomScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maxZoomScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._maxZoomScale_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMaxZoomScaleAttribute((undefined as double | undefined));
                }
            }
        }
        if (this._minZoomScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._minZoomScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMinZoomScaleAttribute((this._minZoomScale_0_0value as double | undefined));
                    this._minZoomScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minZoomScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._minZoomScale_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMinZoomScaleAttribute((undefined as double | undefined));
                }
            }
        }
        if (this._zoomScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._zoomScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setZoomScaleAttribute((this._zoomScale_0_0value as double | Bindable<double> | undefined));
                    this._zoomScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._zoomScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._zoomScale_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setZoomScaleAttribute((undefined as double | Bindable<double> | undefined));
                }
            }
        }
        if (this._enableBouncesZoom_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableBouncesZoom_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableBouncesZoomAttribute((this._enableBouncesZoom_0_0value as boolean | undefined));
                    this._enableBouncesZoom_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableBouncesZoom_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableBouncesZoom_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableBouncesZoomAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._onWillScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onWillScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnWillScrollAttribute((this._onWillScroll_0_0value as ScrollOnWillScrollCallback | undefined));
                    this._onWillScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWillScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWillScroll_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnWillScrollAttribute((undefined as ScrollOnWillScrollCallback | undefined));
                }
            }
        }
        if (this._onDidScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDidScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDidScrollAttribute((this._onDidScroll_0_0value as ScrollOnScrollCallback | undefined));
                    this._onDidScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDidScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDidScroll_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDidScrollAttribute((undefined as ScrollOnScrollCallback | undefined));
                }
            }
        }
        if (this._onScrollEdge_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onScrollEdge_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnScrollEdgeAttribute((this._onScrollEdge_0_0value as OnScrollEdgeCallback | undefined));
                    this._onScrollEdge_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScrollEdge_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScrollEdge_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnScrollEdgeAttribute((undefined as OnScrollEdgeCallback | undefined));
                }
            }
        }
        if (this._onScrollStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onScrollStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnScrollStartAttribute((this._onScrollStart_0_0value as VoidCallback | undefined));
                    this._onScrollStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScrollStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScrollStart_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnScrollStartAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (this._onScrollStop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onScrollStop_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnScrollStopAttribute((this._onScrollStop_0_0value as VoidCallback | undefined));
                    this._onScrollStop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScrollStop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScrollStop_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnScrollStopAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (this._onDidZoom_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDidZoom_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDidZoomAttribute((this._onDidZoom_0_0value as ScrollOnDidZoomCallback | undefined));
                    this._onDidZoom_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDidZoom_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDidZoom_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDidZoomAttribute((undefined as ScrollOnDidZoomCallback | undefined));
                }
            }
        }
        if (this._onZoomStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onZoomStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnZoomStartAttribute((this._onZoomStart_0_0value as VoidCallback | undefined));
                    this._onZoomStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onZoomStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onZoomStart_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnZoomStartAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (this._onZoomStop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onZoomStop_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnZoomStopAttribute((this._onZoomStop_0_0value as VoidCallback | undefined));
                    this._onZoomStop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onZoomStop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onZoomStop_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnZoomStopAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
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
        if (this._onScrollFrameBegin_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onScrollFrameBegin_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnScrollFrameBeginAttribute((this._onScrollFrameBegin_0_0value as OnScrollFrameBeginCallback | undefined));
                    this._onScrollFrameBegin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScrollFrameBegin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScrollFrameBegin_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnScrollFrameBeginAttribute((undefined as OnScrollFrameBeginCallback | undefined));
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
        if (this._scrollSnap_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._scrollSnap_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setScrollSnapAttribute((this._scrollSnap_0_0value as ScrollSnapOptions | undefined));
                    this._scrollSnap_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._scrollSnap_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._scrollSnap_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setScrollSnapAttribute((undefined as ScrollSnapOptions | undefined));
                }
            }
        }
        if (this._enablePaging_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enablePaging_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnablePagingAttribute((this._enablePaging_0_0value as boolean | undefined));
                    this._enablePaging_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enablePaging_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enablePaging_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnablePagingAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._initialOffset_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._initialOffset_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setInitialOffsetAttribute((this._initialOffset_0_0value as OffsetOptions | undefined));
                    this._initialOffset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._initialOffset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._initialOffset_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setInitialOffsetAttribute((undefined as OffsetOptions | undefined));
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
        if (this._flingSpeedLimit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._flingSpeedLimit_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFlingSpeedLimitAttribute((this._flingSpeedLimit_0_0value as number | undefined));
                    this._flingSpeedLimit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._flingSpeedLimit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._flingSpeedLimit_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFlingSpeedLimitAttribute((undefined as number | undefined));
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
    mergeModifier(modifier: ScrollModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._scrollable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._scrollable_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.scrollable(modifier._scrollable_0_0value);
                    break;
                }
                default: {
                    this.scrollable((undefined as ScrollDirection | undefined));
                }
            }
        }
        if (modifier._maxZoomScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._maxZoomScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.maxZoomScale(modifier._maxZoomScale_0_0value);
                    break;
                }
                default: {
                    this.maxZoomScale((undefined as double | undefined));
                }
            }
        }
        if (modifier._minZoomScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._minZoomScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.minZoomScale(modifier._minZoomScale_0_0value);
                    break;
                }
                default: {
                    this.minZoomScale((undefined as double | undefined));
                }
            }
        }
        if (modifier._zoomScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._zoomScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.zoomScale(modifier._zoomScale_0_0value);
                    break;
                }
                default: {
                    this.zoomScale((undefined as double | Bindable<double> | undefined));
                }
            }
        }
        if (modifier._enableBouncesZoom_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableBouncesZoom_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableBouncesZoom(modifier._enableBouncesZoom_0_0value);
                    break;
                }
                default: {
                    this.enableBouncesZoom((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._onWillScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onWillScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onWillScroll(modifier._onWillScroll_0_0value);
                    break;
                }
                default: {
                    this.onWillScroll((undefined as ScrollOnWillScrollCallback | undefined));
                }
            }
        }
        if (modifier._onDidScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDidScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDidScroll(modifier._onDidScroll_0_0value);
                    break;
                }
                default: {
                    this.onDidScroll((undefined as ScrollOnScrollCallback | undefined));
                }
            }
        }
        if (modifier._onScrollEdge_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onScrollEdge_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onScrollEdge(modifier._onScrollEdge_0_0value);
                    break;
                }
                default: {
                    this.onScrollEdge((undefined as OnScrollEdgeCallback | undefined));
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
                    this.onScrollStart((undefined as VoidCallback | undefined));
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
                    this.onScrollStop((undefined as VoidCallback | undefined));
                }
            }
        }
        if (modifier._onDidZoom_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDidZoom_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDidZoom(modifier._onDidZoom_0_0value);
                    break;
                }
                default: {
                    this.onDidZoom((undefined as ScrollOnDidZoomCallback | undefined));
                }
            }
        }
        if (modifier._onZoomStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onZoomStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onZoomStart(modifier._onZoomStart_0_0value);
                    break;
                }
                default: {
                    this.onZoomStart((undefined as VoidCallback | undefined));
                }
            }
        }
        if (modifier._onZoomStop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onZoomStop_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onZoomStop(modifier._onZoomStop_0_0value);
                    break;
                }
                default: {
                    this.onZoomStop((undefined as VoidCallback | undefined));
                }
            }
        }
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
        if (modifier._onScrollFrameBegin_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onScrollFrameBegin_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onScrollFrameBegin(modifier._onScrollFrameBegin_0_0value);
                    break;
                }
                default: {
                    this.onScrollFrameBegin((undefined as OnScrollFrameBeginCallback | undefined));
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
        if (modifier._scrollSnap_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._scrollSnap_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.scrollSnap(modifier._scrollSnap_0_0value);
                    break;
                }
                default: {
                    this.scrollSnap((undefined as ScrollSnapOptions | undefined));
                }
            }
        }
        if (modifier._enablePaging_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enablePaging_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enablePaging(modifier._enablePaging_0_0value);
                    break;
                }
                default: {
                    this.enablePaging((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._initialOffset_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._initialOffset_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.initialOffset(modifier._initialOffset_0_0value);
                    break;
                }
                default: {
                    this.initialOffset((undefined as OffsetOptions | undefined));
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
        if (modifier._flingSpeedLimit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._flingSpeedLimit_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.flingSpeedLimit(modifier._flingSpeedLimit_0_0value);
                    break;
                }
                default: {
                    this.flingSpeedLimit((undefined as number | undefined));
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
    scrollable(value: ScrollDirection | undefined): this {
        if (((this._scrollable_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._scrollable_0_flag = AttributeUpdaterFlag.UPDATE
            this._scrollable_0_0value = value
        } else
        {
            this._scrollable_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    maxZoomScale(value: double | undefined): this {
        if (((this._maxZoomScale_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._maxZoomScale_0_0value) !== (value)))
        {
            this._maxZoomScale_0_flag = AttributeUpdaterFlag.UPDATE
            this._maxZoomScale_0_0value = value
        } else
        {
            this._maxZoomScale_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    minZoomScale(value: double | undefined): this {
        if (((this._minZoomScale_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._minZoomScale_0_0value) !== (value)))
        {
            this._minZoomScale_0_flag = AttributeUpdaterFlag.UPDATE
            this._minZoomScale_0_0value = value
        } else
        {
            this._minZoomScale_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    zoomScale(value: double | Bindable<double> | undefined): this {
        if (((this._zoomScale_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._zoomScale_0_flag = AttributeUpdaterFlag.UPDATE
            this._zoomScale_0_0value = value
        } else
        {
            this._zoomScale_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableBouncesZoom(value: boolean | undefined): this {
        if (((this._enableBouncesZoom_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableBouncesZoom_0_0value) !== (value)))
        {
            this._enableBouncesZoom_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableBouncesZoom_0_0value = value
        } else
        {
            this._enableBouncesZoom_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onWillScroll(value: ScrollOnWillScrollCallback | undefined): this {
        if (((this._onWillScroll_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onWillScroll_0_flag = AttributeUpdaterFlag.UPDATE
            this._onWillScroll_0_0value = value
        } else
        {
            this._onWillScroll_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDidScroll(value: ScrollOnScrollCallback | undefined): this {
        if (((this._onDidScroll_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDidScroll_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDidScroll_0_0value = value
        } else
        {
            this._onDidScroll_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onScrollEdge(value: OnScrollEdgeCallback | undefined): this {
        if (((this._onScrollEdge_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onScrollEdge_0_flag = AttributeUpdaterFlag.UPDATE
            this._onScrollEdge_0_0value = value
        } else
        {
            this._onScrollEdge_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onScrollStart(value: VoidCallback | undefined): this {
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
    onScrollStop(value: VoidCallback | undefined): this {
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
    onDidZoom(value: ScrollOnDidZoomCallback | undefined): this {
        if (((this._onDidZoom_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDidZoom_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDidZoom_0_0value = value
        } else
        {
            this._onDidZoom_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onZoomStart(value: VoidCallback | undefined): this {
        if (((this._onZoomStart_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onZoomStart_0_flag = AttributeUpdaterFlag.UPDATE
            this._onZoomStart_0_0value = value
        } else
        {
            this._onZoomStart_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onZoomStop(value: VoidCallback | undefined): this {
        if (((this._onZoomStop_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onZoomStop_0_flag = AttributeUpdaterFlag.UPDATE
            this._onZoomStop_0_0value = value
        } else
        {
            this._onZoomStop_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
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
    onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        if (((this._onScrollFrameBegin_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onScrollFrameBegin_0_flag = AttributeUpdaterFlag.UPDATE
            this._onScrollFrameBegin_0_0value = value
        } else
        {
            this._onScrollFrameBegin_0_flag = AttributeUpdaterFlag.SKIP
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
    scrollSnap(value: ScrollSnapOptions | undefined): this {
        if (((this._scrollSnap_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._scrollSnap_0_flag = AttributeUpdaterFlag.UPDATE
            this._scrollSnap_0_0value = value
        } else
        {
            this._scrollSnap_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enablePaging(value: boolean | undefined): this {
        if (((this._enablePaging_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enablePaging_0_0value) !== (value)))
        {
            this._enablePaging_0_flag = AttributeUpdaterFlag.UPDATE
            this._enablePaging_0_0value = value
        } else
        {
            this._enablePaging_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    initialOffset(value: OffsetOptions | undefined): this {
        if (((this._initialOffset_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._initialOffset_0_flag = AttributeUpdaterFlag.UPDATE
            this._initialOffset_0_0value = value
        } else
        {
            this._initialOffset_0_flag = AttributeUpdaterFlag.SKIP
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
    flingSpeedLimit(value: number | undefined): this {
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
    public attributeModifier(value: AttributeModifier<ScrollAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

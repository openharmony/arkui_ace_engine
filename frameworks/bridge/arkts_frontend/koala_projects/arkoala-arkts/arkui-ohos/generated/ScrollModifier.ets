/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

import { CommonMethod, NestedScrollOptions, OnWillStopDraggingCallback, OnDidStopDraggingCallback, ContentClipMode, EdgeEffectOptions, FadingEdgeOptions, ScrollableCommonMethod, Bindable } from './component/common'
import { BarState, Color as arkui_component_enums_Color, CrownSensitivity, EdgeEffect, ScrollSource, Edge } from './component/enums'
import { Resource as global_resource_Resource } from 'global.resource'
import { ScrollBarMargin, VoidCallback, Resource as arkui_component_units_Resource } from './component/units'
import { extractors, AttributeModifier } from '#handwritten'
import { RectShape } from '@ohos.arkui.shape'
import { ScrollableCommonMethodModifier } from './ScrollableCommonMethodModifier'
import { CommonMethodModifier } from './CommonMethodModifier'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkScrollPeer, ScrollDirection, ScrollOnWillScrollCallback, ScrollOnScrollCallback, OnScrollEdgeCallback, ScrollOnDidZoomCallback, OnScrollFrameBeginCallback, ScrollSnapOptions, OffsetOptions, ScrollAttribute } from './component/scroll'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { ScrollState } from './component/list'
export class ScrollModifier extends CommonMethodModifier implements ScrollAttribute,AttributeModifier<ScrollAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState;
    _addr: ArrayBuffer = new ArrayBuffer(4096);
    private _flagArray: Uint8Array = new Uint8Array(this._addr);
    constructor() {
        super();
        this._flagArray.fill(0);
    }
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: ScrollAttribute): void { }
    applyPressedAttribute(instance: ScrollAttribute): void { }
    applyFocusedAttribute(instance: ScrollAttribute): void { }
    applyDisabledAttribute(instance: ScrollAttribute): void { }
    applySelectedAttribute(instance: ScrollAttribute): void { }
    public _scrollable_0_0value?: ScrollDirection | undefined
    public _maxZoomScale_0_0value?: double | undefined
    public _minZoomScale_0_0value?: double | undefined
    public _zoomScale_0_0value?: double | Bindable<double> | undefined
    public _enableBouncesZoom_0_0value?: boolean | undefined
    public _onWillScroll_0_0value?: ScrollOnWillScrollCallback | undefined
    public _onDidScroll_0_0value?: ScrollOnScrollCallback | undefined
    public _onScrollEdge_0_0value?: OnScrollEdgeCallback | undefined
    public _onScrollStart_0_0value?: VoidCallback | undefined
    public _onScrollStop_0_0value?: VoidCallback | undefined
    public _onDidZoom_0_0value?: ScrollOnDidZoomCallback | undefined
    public _onZoomStart_0_0value?: VoidCallback | undefined
    public _onZoomStop_0_0value?: VoidCallback | undefined
    public _scrollBar_0_0value?: BarState | undefined
    public _scrollBarColor_0_0value?: arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
    public _scrollBarWidth_0_0value?: double | string | undefined
    public _onScrollFrameBegin_0_0value?: OnScrollFrameBeginCallback | undefined
    public _nestedScroll_0_0value?: NestedScrollOptions | undefined
    public _enableScrollInteraction_0_0value?: boolean | undefined
    public _friction_0_0value?: double | arkui_component_units_Resource | undefined
    public _scrollSnap_0_0value?: ScrollSnapOptions | undefined
    public _enablePaging_0_0value?: boolean | undefined
    public _initialOffset_0_0value?: OffsetOptions | undefined
    public _edgeEffect_0_0value?: EdgeEffect | undefined
    public _edgeEffect_0_1value?: EdgeEffectOptions | undefined
    public _scrollBarMargin_0_0value?: ScrollBarMargin | undefined
    public _contentStartOffset_0_0value?: double | global_resource_Resource | undefined
    public _contentEndOffset_0_0value?: double | global_resource_Resource | undefined
    public _onWillStartDragging_0_0value?: VoidCallback | undefined
    public _onWillStopDragging_0_0value?: OnWillStopDraggingCallback | undefined
    public _onDidStopDragging_0_0value?: OnDidStopDraggingCallback | undefined
    public _onWillStartFling_0_0value?: VoidCallback | undefined
    public _onDidStopFling_0_0value?: VoidCallback | undefined
    public _onReachStart_0_0value?: (() => void) | undefined
    public _onReachEnd_0_0value?: (() => void) | undefined
    public _flingSpeedLimit_0_0value?: double | undefined
    public _clipContent_0_0value?: ContentClipMode | RectShape | undefined
    public _digitalCrownSensitivity_0_0value?: CrownSensitivity | undefined
    public _backToTop_0_0value?: boolean | undefined
    public _fadingEdge_0_0value?: boolean | undefined
    public _fadingEdge_0_1value?: FadingEdgeOptions | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkScrollPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
        this.applyModifierPatch1(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkScrollPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setScrollableAttribute((this._scrollable_0_0value as ScrollDirection | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setScrollableAttribute((undefined as ScrollDirection | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setMaxZoomScaleAttribute((this._maxZoomScale_0_0value as double | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setMaxZoomScaleAttribute((undefined as double | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setMinZoomScaleAttribute((this._minZoomScale_0_0value as double | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setMinZoomScaleAttribute((undefined as double | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setZoomScaleAttribute((this._zoomScale_0_0value as double | Bindable<double> | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setZoomScaleAttribute((undefined as double | Bindable<double> | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setEnableBouncesZoomAttribute((this._enableBouncesZoom_0_0value as boolean | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setEnableBouncesZoomAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setOnWillScrollAttribute((this._onWillScroll_0_0value as ScrollOnWillScrollCallback | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setOnWillScrollAttribute((undefined as ScrollOnWillScrollCallback | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1: {
                    peer.setOnDidScrollAttribute((this._onDidScroll_0_0value as ScrollOnScrollCallback | undefined));
                    flagArray[6] = 2;
                    break;
                }
                case 3: {
                    flagArray[6] = 2;
                    break;
                }
                default: {
                    flagArray[6] = 0;
                    peer.setOnDidScrollAttribute((undefined as ScrollOnScrollCallback | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1: {
                    peer.setOnScrollEdgeAttribute((this._onScrollEdge_0_0value as OnScrollEdgeCallback | undefined));
                    flagArray[7] = 2;
                    break;
                }
                case 3: {
                    flagArray[7] = 2;
                    break;
                }
                default: {
                    flagArray[7] = 0;
                    peer.setOnScrollEdgeAttribute((undefined as OnScrollEdgeCallback | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1: {
                    peer.setOnScrollStartAttribute((this._onScrollStart_0_0value as VoidCallback | undefined));
                    flagArray[8] = 2;
                    break;
                }
                case 3: {
                    flagArray[8] = 2;
                    break;
                }
                default: {
                    flagArray[8] = 0;
                    peer.setOnScrollStartAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1: {
                    peer.setOnScrollStopAttribute((this._onScrollStop_0_0value as VoidCallback | undefined));
                    flagArray[9] = 2;
                    break;
                }
                case 3: {
                    flagArray[9] = 2;
                    break;
                }
                default: {
                    flagArray[9] = 0;
                    peer.setOnScrollStopAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1: {
                    peer.setOnDidZoomAttribute((this._onDidZoom_0_0value as ScrollOnDidZoomCallback | undefined));
                    flagArray[10] = 2;
                    break;
                }
                case 3: {
                    flagArray[10] = 2;
                    break;
                }
                default: {
                    flagArray[10] = 0;
                    peer.setOnDidZoomAttribute((undefined as ScrollOnDidZoomCallback | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1: {
                    peer.setOnZoomStartAttribute((this._onZoomStart_0_0value as VoidCallback | undefined));
                    flagArray[11] = 2;
                    break;
                }
                case 3: {
                    flagArray[11] = 2;
                    break;
                }
                default: {
                    flagArray[11] = 0;
                    peer.setOnZoomStartAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1: {
                    peer.setOnZoomStopAttribute((this._onZoomStop_0_0value as VoidCallback | undefined));
                    flagArray[12] = 2;
                    break;
                }
                case 3: {
                    flagArray[12] = 2;
                    break;
                }
                default: {
                    flagArray[12] = 0;
                    peer.setOnZoomStopAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1: {
                    peer.setScrollBarAttribute((this._scrollBar_0_0value as BarState | undefined));
                    flagArray[13] = 2;
                    break;
                }
                case 3: {
                    flagArray[13] = 2;
                    break;
                }
                default: {
                    flagArray[13] = 0;
                    peer.setScrollBarAttribute((undefined as BarState | undefined));
                }
            }
        }
        if (flagArray[14] != 0) {
            switch (flagArray[14]) {
                case 1: {
                    peer.setScrollBarColorAttribute((this._scrollBarColor_0_0value as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined));
                    flagArray[14] = 2;
                    break;
                }
                case 3: {
                    flagArray[14] = 2;
                    break;
                }
                default: {
                    flagArray[14] = 0;
                    peer.setScrollBarColorAttribute((undefined as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined));
                }
            }
        }
        if (flagArray[15] != 0) {
            switch (flagArray[15]) {
                case 1: {
                    peer.setScrollBarWidthAttribute((this._scrollBarWidth_0_0value as double | string | undefined));
                    flagArray[15] = 2;
                    break;
                }
                case 3: {
                    flagArray[15] = 2;
                    break;
                }
                default: {
                    flagArray[15] = 0;
                    peer.setScrollBarWidthAttribute((undefined as double | string | undefined));
                }
            }
        }
        if (flagArray[16] != 0) {
            switch (flagArray[16]) {
                case 1: {
                    peer.setOnScrollFrameBeginAttribute((this._onScrollFrameBegin_0_0value as OnScrollFrameBeginCallback | undefined));
                    flagArray[16] = 2;
                    break;
                }
                case 3: {
                    flagArray[16] = 2;
                    break;
                }
                default: {
                    flagArray[16] = 0;
                    peer.setOnScrollFrameBeginAttribute((undefined as OnScrollFrameBeginCallback | undefined));
                }
            }
        }
        if (flagArray[17] != 0) {
            switch (flagArray[17]) {
                case 1: {
                    peer.setNestedScrollAttribute((this._nestedScroll_0_0value as NestedScrollOptions | undefined));
                    flagArray[17] = 2;
                    break;
                }
                case 3: {
                    flagArray[17] = 2;
                    break;
                }
                default: {
                    flagArray[17] = 0;
                    peer.setNestedScrollAttribute((undefined as NestedScrollOptions | undefined));
                }
            }
        }
        if (flagArray[18] != 0) {
            switch (flagArray[18]) {
                case 1: {
                    peer.setEnableScrollInteractionAttribute((this._enableScrollInteraction_0_0value as boolean | undefined));
                    flagArray[18] = 2;
                    break;
                }
                case 3: {
                    flagArray[18] = 2;
                    break;
                }
                default: {
                    flagArray[18] = 0;
                    peer.setEnableScrollInteractionAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[19] != 0) {
            switch (flagArray[19]) {
                case 1: {
                    peer.setFrictionAttribute((this._friction_0_0value as double | arkui_component_units_Resource | undefined));
                    flagArray[19] = 2;
                    break;
                }
                case 3: {
                    flagArray[19] = 2;
                    break;
                }
                default: {
                    flagArray[19] = 0;
                    peer.setFrictionAttribute((undefined as double | arkui_component_units_Resource | undefined));
                }
            }
        }
    }
    applyModifierPatch1(peer: ArkScrollPeer, flagArray: Uint8Array): void {
        if (flagArray[20] != 0) {
            switch (flagArray[20]) {
                case 1: {
                    peer.setScrollSnapAttribute((this._scrollSnap_0_0value as ScrollSnapOptions | undefined));
                    flagArray[20] = 2;
                    break;
                }
                case 3: {
                    flagArray[20] = 2;
                    break;
                }
                default: {
                    flagArray[20] = 0;
                    peer.setScrollSnapAttribute((undefined as ScrollSnapOptions | undefined));
                }
            }
        }
        if (flagArray[21] != 0) {
            switch (flagArray[21]) {
                case 1: {
                    peer.setEnablePagingAttribute((this._enablePaging_0_0value as boolean | undefined));
                    flagArray[21] = 2;
                    break;
                }
                case 3: {
                    flagArray[21] = 2;
                    break;
                }
                default: {
                    flagArray[21] = 0;
                    peer.setEnablePagingAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[22] != 0) {
            switch (flagArray[22]) {
                case 1: {
                    peer.setInitialOffsetAttribute((this._initialOffset_0_0value as OffsetOptions | undefined));
                    flagArray[22] = 2;
                    break;
                }
                case 3: {
                    flagArray[22] = 2;
                    break;
                }
                default: {
                    flagArray[22] = 0;
                    peer.setInitialOffsetAttribute((undefined as OffsetOptions | undefined));
                }
            }
        }
        if (flagArray[23] != 0) {
            switch (flagArray[23]) {
                case 1: {
                    peer.setEdgeEffectAttribute((this._edgeEffect_0_0value as EdgeEffect | undefined), (this._edgeEffect_0_1value as EdgeEffectOptions | undefined | undefined));
                    flagArray[23] = 2;
                    break;
                }
                case 3: {
                    flagArray[23] = 2;
                    break;
                }
                default: {
                    flagArray[23] = 0;
                    peer.setEdgeEffectAttribute((undefined as EdgeEffect | undefined), (undefined as EdgeEffectOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[24] != 0) {
            switch (flagArray[24]) {
                case 1: {
                    peer.setScrollBarMarginAttribute((this._scrollBarMargin_0_0value as ScrollBarMargin | undefined));
                    flagArray[24] = 2;
                    break;
                }
                case 3: {
                    flagArray[24] = 2;
                    break;
                }
                default: {
                    flagArray[24] = 0;
                    peer.setScrollBarMarginAttribute((undefined as ScrollBarMargin | undefined));
                }
            }
        }
        if (flagArray[25] != 0) {
            switch (flagArray[25]) {
                case 1: {
                    peer.setContentStartOffsetAttribute((this._contentStartOffset_0_0value as double | global_resource_Resource | undefined));
                    flagArray[25] = 2;
                    break;
                }
                case 3: {
                    flagArray[25] = 2;
                    break;
                }
                default: {
                    flagArray[25] = 0;
                    peer.setContentStartOffsetAttribute((undefined as double | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[26] != 0) {
            switch (flagArray[26]) {
                case 1: {
                    peer.setContentEndOffsetAttribute((this._contentEndOffset_0_0value as double | global_resource_Resource | undefined));
                    flagArray[26] = 2;
                    break;
                }
                case 3: {
                    flagArray[26] = 2;
                    break;
                }
                default: {
                    flagArray[26] = 0;
                    peer.setContentEndOffsetAttribute((undefined as double | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[27] != 0) {
            switch (flagArray[27]) {
                case 1: {
                    peer.setOnWillStartDraggingAttribute((this._onWillStartDragging_0_0value as VoidCallback | undefined));
                    flagArray[27] = 2;
                    break;
                }
                case 3: {
                    flagArray[27] = 2;
                    break;
                }
                default: {
                    flagArray[27] = 0;
                    peer.setOnWillStartDraggingAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[28] != 0) {
            switch (flagArray[28]) {
                case 1: {
                    peer.setOnWillStopDraggingAttribute((this._onWillStopDragging_0_0value as OnWillStopDraggingCallback | undefined));
                    flagArray[28] = 2;
                    break;
                }
                case 3: {
                    flagArray[28] = 2;
                    break;
                }
                default: {
                    flagArray[28] = 0;
                    peer.setOnWillStopDraggingAttribute((undefined as OnWillStopDraggingCallback | undefined));
                }
            }
        }
        if (flagArray[29] != 0) {
            switch (flagArray[29]) {
                case 1: {
                    peer.setOnDidStopDraggingAttribute((this._onDidStopDragging_0_0value as OnDidStopDraggingCallback | undefined));
                    flagArray[29] = 2;
                    break;
                }
                case 3: {
                    flagArray[29] = 2;
                    break;
                }
                default: {
                    flagArray[29] = 0;
                    peer.setOnDidStopDraggingAttribute((undefined as OnDidStopDraggingCallback | undefined));
                }
            }
        }
        if (flagArray[30] != 0) {
            switch (flagArray[30]) {
                case 1: {
                    peer.setOnWillStartFlingAttribute((this._onWillStartFling_0_0value as VoidCallback | undefined));
                    flagArray[30] = 2;
                    break;
                }
                case 3: {
                    flagArray[30] = 2;
                    break;
                }
                default: {
                    flagArray[30] = 0;
                    peer.setOnWillStartFlingAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[31] != 0) {
            switch (flagArray[31]) {
                case 1: {
                    peer.setOnDidStopFlingAttribute((this._onDidStopFling_0_0value as VoidCallback | undefined));
                    flagArray[31] = 2;
                    break;
                }
                case 3: {
                    flagArray[31] = 2;
                    break;
                }
                default: {
                    flagArray[31] = 0;
                    peer.setOnDidStopFlingAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[32] != 0) {
            switch (flagArray[32]) {
                case 1: {
                    peer.setOnReachStartAttribute((this._onReachStart_0_0value as (() => void) | undefined));
                    flagArray[32] = 2;
                    break;
                }
                case 3: {
                    flagArray[32] = 2;
                    break;
                }
                default: {
                    flagArray[32] = 0;
                    peer.setOnReachStartAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[33] != 0) {
            switch (flagArray[33]) {
                case 1: {
                    peer.setOnReachEndAttribute((this._onReachEnd_0_0value as (() => void) | undefined));
                    flagArray[33] = 2;
                    break;
                }
                case 3: {
                    flagArray[33] = 2;
                    break;
                }
                default: {
                    flagArray[33] = 0;
                    peer.setOnReachEndAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[34] != 0) {
            switch (flagArray[34]) {
                case 1: {
                    peer.setFlingSpeedLimitAttribute((this._flingSpeedLimit_0_0value as double | undefined));
                    flagArray[34] = 2;
                    break;
                }
                case 3: {
                    flagArray[34] = 2;
                    break;
                }
                default: {
                    flagArray[34] = 0;
                    peer.setFlingSpeedLimitAttribute((undefined as double | undefined));
                }
            }
        }
        if (flagArray[35] != 0) {
            switch (flagArray[35]) {
                case 1: {
                    peer.setClipContentAttribute((this._clipContent_0_0value as ContentClipMode | RectShape | undefined));
                    flagArray[35] = 2;
                    break;
                }
                case 3: {
                    flagArray[35] = 2;
                    break;
                }
                default: {
                    flagArray[35] = 0;
                    peer.setClipContentAttribute((undefined as ContentClipMode | RectShape | undefined));
                }
            }
        }
        if (flagArray[36] != 0) {
            switch (flagArray[36]) {
                case 1: {
                    peer.setDigitalCrownSensitivityAttribute((this._digitalCrownSensitivity_0_0value as CrownSensitivity | undefined));
                    flagArray[36] = 2;
                    break;
                }
                case 3: {
                    flagArray[36] = 2;
                    break;
                }
                default: {
                    flagArray[36] = 0;
                    peer.setDigitalCrownSensitivityAttribute((undefined as CrownSensitivity | undefined));
                }
            }
        }
        if (flagArray[37] != 0) {
            switch (flagArray[37]) {
                case 1: {
                    peer.setBackToTopAttribute((this._backToTop_0_0value as boolean | undefined));
                    flagArray[37] = 2;
                    break;
                }
                case 3: {
                    flagArray[37] = 2;
                    break;
                }
                default: {
                    flagArray[37] = 0;
                    peer.setBackToTopAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[38] != 0) {
            switch (flagArray[38]) {
                case 1: {
                    peer.setFadingEdgeAttribute((this._fadingEdge_0_0value as boolean | undefined), (this._fadingEdge_0_1value as FadingEdgeOptions | undefined));
                    flagArray[38] = 2;
                    break;
                }
                case 3: {
                    flagArray[38] = 2;
                    break;
                }
                default: {
                    flagArray[38] = 0;
                    peer.setFadingEdgeAttribute((undefined as boolean | undefined), (undefined as FadingEdgeOptions | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: ScrollModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
        this.mergeModifier1(modifier, flagArray);
    }
    mergeModifier0(modifier: ScrollModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.scrollable((modifier._scrollable_0_0value as ScrollDirection | undefined));
                    break;
                }
                default: {
                    this.scrollable((undefined as ScrollDirection | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.maxZoomScale((modifier._maxZoomScale_0_0value as double | undefined));
                    break;
                }
                default: {
                    this.maxZoomScale((undefined as double | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.minZoomScale((modifier._minZoomScale_0_0value as double | undefined));
                    break;
                }
                default: {
                    this.minZoomScale((undefined as double | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.zoomScale((modifier._zoomScale_0_0value as double | Bindable<double> | undefined));
                    break;
                }
                default: {
                    this.zoomScale((undefined as double | Bindable<double> | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.enableBouncesZoom((modifier._enableBouncesZoom_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.enableBouncesZoom((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1:
                case 3: {
                    this.onWillScroll((modifier._onWillScroll_0_0value as ScrollOnWillScrollCallback | undefined));
                    break;
                }
                default: {
                    this.onWillScroll((undefined as ScrollOnWillScrollCallback | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1:
                case 3: {
                    this.onDidScroll((modifier._onDidScroll_0_0value as ScrollOnScrollCallback | undefined));
                    break;
                }
                default: {
                    this.onDidScroll((undefined as ScrollOnScrollCallback | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1:
                case 3: {
                    this.onScrollEdge((modifier._onScrollEdge_0_0value as OnScrollEdgeCallback | undefined));
                    break;
                }
                default: {
                    this.onScrollEdge((undefined as OnScrollEdgeCallback | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1:
                case 3: {
                    this.onScrollStart((modifier._onScrollStart_0_0value as VoidCallback | undefined));
                    break;
                }
                default: {
                    this.onScrollStart((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1:
                case 3: {
                    this.onScrollStop((modifier._onScrollStop_0_0value as VoidCallback | undefined));
                    break;
                }
                default: {
                    this.onScrollStop((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1:
                case 3: {
                    this.onDidZoom((modifier._onDidZoom_0_0value as ScrollOnDidZoomCallback | undefined));
                    break;
                }
                default: {
                    this.onDidZoom((undefined as ScrollOnDidZoomCallback | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1:
                case 3: {
                    this.onZoomStart((modifier._onZoomStart_0_0value as VoidCallback | undefined));
                    break;
                }
                default: {
                    this.onZoomStart((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1:
                case 3: {
                    this.onZoomStop((modifier._onZoomStop_0_0value as VoidCallback | undefined));
                    break;
                }
                default: {
                    this.onZoomStop((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1:
                case 3: {
                    this.scrollBar((modifier._scrollBar_0_0value as BarState | undefined));
                    break;
                }
                default: {
                    this.scrollBar((undefined as BarState | undefined));
                }
            }
        }
        if (flagArray[14] != 0) {
            switch (flagArray[14]) {
                case 1:
                case 3: {
                    this.scrollBarColor((modifier._scrollBarColor_0_0value as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined));
                    break;
                }
                default: {
                    this.scrollBarColor((undefined as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined));
                }
            }
        }
        if (flagArray[15] != 0) {
            switch (flagArray[15]) {
                case 1:
                case 3: {
                    this.scrollBarWidth((modifier._scrollBarWidth_0_0value as double | string | undefined));
                    break;
                }
                default: {
                    this.scrollBarWidth((undefined as double | string | undefined));
                }
            }
        }
        if (flagArray[16] != 0) {
            switch (flagArray[16]) {
                case 1:
                case 3: {
                    this.onScrollFrameBegin((modifier._onScrollFrameBegin_0_0value as OnScrollFrameBeginCallback | undefined));
                    break;
                }
                default: {
                    this.onScrollFrameBegin((undefined as OnScrollFrameBeginCallback | undefined));
                }
            }
        }
        if (flagArray[17] != 0) {
            switch (flagArray[17]) {
                case 1:
                case 3: {
                    this.nestedScroll((modifier._nestedScroll_0_0value as NestedScrollOptions | undefined));
                    break;
                }
                default: {
                    this.nestedScroll((undefined as NestedScrollOptions | undefined));
                }
            }
        }
        if (flagArray[18] != 0) {
            switch (flagArray[18]) {
                case 1:
                case 3: {
                    this.enableScrollInteraction((modifier._enableScrollInteraction_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.enableScrollInteraction((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[19] != 0) {
            switch (flagArray[19]) {
                case 1:
                case 3: {
                    this.friction((modifier._friction_0_0value as double | arkui_component_units_Resource | undefined));
                    break;
                }
                default: {
                    this.friction((undefined as double | arkui_component_units_Resource | undefined));
                }
            }
        }
    }
    mergeModifier1(modifier: ScrollModifier, flagArray: Uint8Array): void {
        if (flagArray[20] != 0) {
            switch (flagArray[20]) {
                case 1:
                case 3: {
                    this.scrollSnap((modifier._scrollSnap_0_0value as ScrollSnapOptions | undefined));
                    break;
                }
                default: {
                    this.scrollSnap((undefined as ScrollSnapOptions | undefined));
                }
            }
        }
        if (flagArray[21] != 0) {
            switch (flagArray[21]) {
                case 1:
                case 3: {
                    this.enablePaging((modifier._enablePaging_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.enablePaging((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[22] != 0) {
            switch (flagArray[22]) {
                case 1:
                case 3: {
                    this.initialOffset((modifier._initialOffset_0_0value as OffsetOptions | undefined));
                    break;
                }
                default: {
                    this.initialOffset((undefined as OffsetOptions | undefined));
                }
            }
        }
        if (flagArray[23] != 0) {
            switch (flagArray[23]) {
                case 1:
                case 3: {
                    this.edgeEffect((modifier._edgeEffect_0_0value as EdgeEffect | undefined), (modifier._edgeEffect_0_1value as EdgeEffectOptions | undefined));
                    break;
                }
                default: {
                    this.edgeEffect((undefined as EdgeEffect | undefined), (undefined as EdgeEffectOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[24] != 0) {
            switch (flagArray[24]) {
                case 1:
                case 3: {
                    this.scrollBarMargin((modifier._scrollBarMargin_0_0value as ScrollBarMargin | undefined));
                    break;
                }
                default: {
                    this.scrollBarMargin((undefined as ScrollBarMargin | undefined));
                }
            }
        }
        if (flagArray[25] != 0) {
            switch (flagArray[25]) {
                case 1:
                case 3: {
                    this.contentStartOffset((modifier._contentStartOffset_0_0value as double | global_resource_Resource | undefined));
                    break;
                }
                default: {
                    this.contentStartOffset((undefined as double | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[26] != 0) {
            switch (flagArray[26]) {
                case 1:
                case 3: {
                    this.contentEndOffset((modifier._contentEndOffset_0_0value as double | global_resource_Resource | undefined));
                    break;
                }
                default: {
                    this.contentEndOffset((undefined as double | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[27] != 0) {
            switch (flagArray[27]) {
                case 1:
                case 3: {
                    this.onWillStartDragging((modifier._onWillStartDragging_0_0value as VoidCallback | undefined));
                    break;
                }
                default: {
                    this.onWillStartDragging((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[28] != 0) {
            switch (flagArray[28]) {
                case 1:
                case 3: {
                    this.onWillStopDragging((modifier._onWillStopDragging_0_0value as OnWillStopDraggingCallback | undefined));
                    break;
                }
                default: {
                    this.onWillStopDragging((undefined as OnWillStopDraggingCallback | undefined));
                }
            }
        }
        if (flagArray[29] != 0) {
            switch (flagArray[29]) {
                case 1:
                case 3: {
                    this.onDidStopDragging((modifier._onDidStopDragging_0_0value as OnDidStopDraggingCallback | undefined));
                    break;
                }
                default: {
                    this.onDidStopDragging((undefined as OnDidStopDraggingCallback | undefined));
                }
            }
        }
        if (flagArray[30] != 0) {
            switch (flagArray[30]) {
                case 1:
                case 3: {
                    this.onWillStartFling((modifier._onWillStartFling_0_0value as VoidCallback | undefined));
                    break;
                }
                default: {
                    this.onWillStartFling((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[31] != 0) {
            switch (flagArray[31]) {
                case 1:
                case 3: {
                    this.onDidStopFling((modifier._onDidStopFling_0_0value as VoidCallback | undefined));
                    break;
                }
                default: {
                    this.onDidStopFling((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[32] != 0) {
            switch (flagArray[32]) {
                case 1:
                case 3: {
                    this.onReachStart((modifier._onReachStart_0_0value as (() => void) | undefined));
                    break;
                }
                default: {
                    this.onReachStart((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[33] != 0) {
            switch (flagArray[33]) {
                case 1:
                case 3: {
                    this.onReachEnd((modifier._onReachEnd_0_0value as (() => void) | undefined));
                    break;
                }
                default: {
                    this.onReachEnd((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[34] != 0) {
            switch (flagArray[34]) {
                case 1:
                case 3: {
                    this.flingSpeedLimit((modifier._flingSpeedLimit_0_0value as double | undefined));
                    break;
                }
                default: {
                    this.flingSpeedLimit((undefined as double | undefined));
                }
            }
        }
        if (flagArray[35] != 0) {
            switch (flagArray[35]) {
                case 1:
                case 3: {
                    this.clipContent((modifier._clipContent_0_0value as ContentClipMode | RectShape | undefined));
                    break;
                }
                default: {
                    this.clipContent((undefined as ContentClipMode | RectShape | undefined));
                }
            }
        }
        if (flagArray[36] != 0) {
            switch (flagArray[36]) {
                case 1:
                case 3: {
                    this.digitalCrownSensitivity((modifier._digitalCrownSensitivity_0_0value as CrownSensitivity | undefined));
                    break;
                }
                default: {
                    this.digitalCrownSensitivity((undefined as CrownSensitivity | undefined));
                }
            }
        }
        if (flagArray[37] != 0) {
            switch (flagArray[37]) {
                case 1:
                case 3: {
                    this.backToTop((modifier._backToTop_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.backToTop((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[38] != 0) {
            switch (flagArray[38]) {
                case 1:
                case 3: {
                    this.fadingEdge((modifier._fadingEdge_0_0value as boolean | undefined), (modifier._fadingEdge_0_1value as FadingEdgeOptions | undefined));
                    break;
                }
                default: {
                    this.fadingEdge((undefined as boolean | undefined), (undefined as FadingEdgeOptions | undefined));
                }
            }
        }
    }
    scrollable(value: ScrollDirection | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._scrollable_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    maxZoomScale(value: double | undefined): this {
        if (((this._flagArray[1]) == (0)) || ((this._maxZoomScale_0_0value) !== (value))) {
            this._flagArray[1] = 1
            this._maxZoomScale_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    minZoomScale(value: double | undefined): this {
        if (((this._flagArray[2]) == (0)) || ((this._minZoomScale_0_0value) !== (value))) {
            this._flagArray[2] = 1
            this._minZoomScale_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    zoomScale(value: double | Bindable<double> | undefined): this {
        if (((this._flagArray[3]) == (0)) || (true)) {
            this._flagArray[3] = 1
            this._zoomScale_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    enableBouncesZoom(value: boolean | undefined): this {
        if (((this._flagArray[4]) == (0)) || ((this._enableBouncesZoom_0_0value) !== (value))) {
            this._flagArray[4] = 1
            this._enableBouncesZoom_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    onWillScroll(value: ScrollOnWillScrollCallback | undefined): this {
        if (((this._flagArray[5]) == (0)) || (true)) {
            this._flagArray[5] = 1
            this._onWillScroll_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    onDidScroll(value: ScrollOnScrollCallback | undefined): this {
        if (((this._flagArray[6]) == (0)) || (true)) {
            this._flagArray[6] = 1
            this._onDidScroll_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[6] = 3
        }
        return this
    }
    onScrollEdge(value: OnScrollEdgeCallback | undefined): this {
        if (((this._flagArray[7]) == (0)) || (true)) {
            this._flagArray[7] = 1
            this._onScrollEdge_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[7] = 3
        }
        return this
    }
    onScrollStart(value: VoidCallback | undefined): this {
        if (((this._flagArray[8]) == (0)) || (true)) {
            this._flagArray[8] = 1
            this._onScrollStart_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[8] = 3
        }
        return this
    }
    onScrollStop(value: VoidCallback | undefined): this {
        if (((this._flagArray[9]) == (0)) || (true)) {
            this._flagArray[9] = 1
            this._onScrollStop_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[9] = 3
        }
        return this
    }
    onDidZoom(value: ScrollOnDidZoomCallback | undefined): this {
        if (((this._flagArray[10]) == (0)) || (true)) {
            this._flagArray[10] = 1
            this._onDidZoom_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[10] = 3
        }
        return this
    }
    onZoomStart(value: VoidCallback | undefined): this {
        if (((this._flagArray[11]) == (0)) || (true)) {
            this._flagArray[11] = 1
            this._onZoomStart_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[11] = 3
        }
        return this
    }
    onZoomStop(value: VoidCallback | undefined): this {
        if (((this._flagArray[12]) == (0)) || (true)) {
            this._flagArray[12] = 1
            this._onZoomStop_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[12] = 3
        }
        return this
    }
    scrollBar(value: BarState | undefined): this {
        if (((this._flagArray[13]) == (0)) || (true)) {
            this._flagArray[13] = 1
            this._scrollBar_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[13] = 3
        }
        return this
    }
    scrollBarColor(value: arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined): this {
        if (((this._flagArray[14]) == (0)) || (true)) {
            this._flagArray[14] = 1
            this._scrollBarColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[14] = 3
        }
        return this
    }
    scrollBarWidth(value: double | string | undefined): this {
        if (((this._flagArray[15]) == (0)) || ((this._scrollBarWidth_0_0value) !== (value))) {
            this._flagArray[15] = 1
            this._scrollBarWidth_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[15] = 3
        }
        return this
    }
    onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        if (((this._flagArray[16]) == (0)) || (true)) {
            this._flagArray[16] = 1
            this._onScrollFrameBegin_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[16] = 3
        }
        return this
    }
    nestedScroll(value: NestedScrollOptions | undefined): this {
        if (((this._flagArray[17]) == (0)) || (true)) {
            this._flagArray[17] = 1
            this._nestedScroll_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[17] = 3
        }
        return this
    }
    enableScrollInteraction(value: boolean | undefined): this {
        if (((this._flagArray[18]) == (0)) || ((this._enableScrollInteraction_0_0value) !== (value))) {
            this._flagArray[18] = 1
            this._enableScrollInteraction_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[18] = 3
        }
        return this
    }
    friction(value: double | arkui_component_units_Resource | undefined): this {
        if (((this._flagArray[19]) == (0)) || (true)) {
            this._flagArray[19] = 1
            this._friction_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[19] = 3
        }
        return this
    }
    scrollSnap(value: ScrollSnapOptions | undefined): this {
        if (((this._flagArray[20]) == (0)) || (true)) {
            this._flagArray[20] = 1
            this._scrollSnap_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[20] = 3
        }
        return this
    }
    enablePaging(value: boolean | undefined): this {
        if (((this._flagArray[21]) == (0)) || ((this._enablePaging_0_0value) !== (value))) {
            this._flagArray[21] = 1
            this._enablePaging_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[21] = 3
        }
        return this
    }
    initialOffset(value: OffsetOptions | undefined): this {
        if (((this._flagArray[22]) == (0)) || (true)) {
            this._flagArray[22] = 1
            this._initialOffset_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[22] = 3
        }
        return this
    }
    edgeEffect(edgeEffect: EdgeEffect | undefined, options?: EdgeEffectOptions): this {
        if (((this._flagArray[23]) == (0)) || (true) || (true)) {
            this._flagArray[23] = 1
            this._edgeEffect_0_0value = edgeEffect
            this._edgeEffect_0_1value = options
            this._state.fireChange()
        } else {
            this._flagArray[23] = 3
        }
        return this
    }
    scrollBarMargin(value: ScrollBarMargin | undefined): this {
        if (((this._flagArray[24]) == (0)) || (true)) {
            this._flagArray[24] = 1
            this._scrollBarMargin_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[24] = 3
        }
        return this
    }
    contentStartOffset(value: double | global_resource_Resource | undefined): this {
        if (((this._flagArray[25]) == (0)) || (true)) {
            this._flagArray[25] = 1
            this._contentStartOffset_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[25] = 3
        }
        return this
    }
    contentEndOffset(value: double | global_resource_Resource | undefined): this {
        if (((this._flagArray[26]) == (0)) || (true)) {
            this._flagArray[26] = 1
            this._contentEndOffset_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[26] = 3
        }
        return this
    }
    onWillStartDragging(value: VoidCallback | undefined): this {
        if (((this._flagArray[27]) == (0)) || (true)) {
            this._flagArray[27] = 1
            this._onWillStartDragging_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[27] = 3
        }
        return this
    }
    onWillStopDragging(value: OnWillStopDraggingCallback | undefined): this {
        if (((this._flagArray[28]) == (0)) || (true)) {
            this._flagArray[28] = 1
            this._onWillStopDragging_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[28] = 3
        }
        return this
    }
    onDidStopDragging(value: OnDidStopDraggingCallback | undefined): this {
        if (((this._flagArray[29]) == (0)) || (true)) {
            this._flagArray[29] = 1
            this._onDidStopDragging_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[29] = 3
        }
        return this
    }
    onWillStartFling(value: VoidCallback | undefined): this {
        if (((this._flagArray[30]) == (0)) || (true)) {
            this._flagArray[30] = 1
            this._onWillStartFling_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[30] = 3
        }
        return this
    }
    onDidStopFling(value: VoidCallback | undefined): this {
        if (((this._flagArray[31]) == (0)) || (true)) {
            this._flagArray[31] = 1
            this._onDidStopFling_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[31] = 3
        }
        return this
    }
    onReachStart(value: (() => void) | undefined): this {
        if (((this._flagArray[32]) == (0)) || (true)) {
            this._flagArray[32] = 1
            this._onReachStart_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[32] = 3
        }
        return this
    }
    onReachEnd(value: (() => void) | undefined): this {
        if (((this._flagArray[33]) == (0)) || (true)) {
            this._flagArray[33] = 1
            this._onReachEnd_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[33] = 3
        }
        return this
    }
    flingSpeedLimit(value: double | undefined): this {
        if (((this._flagArray[34]) == (0)) || ((this._flingSpeedLimit_0_0value) !== (value))) {
            this._flagArray[34] = 1
            this._flingSpeedLimit_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[34] = 3
        }
        return this
    }
    clipContent(value: ContentClipMode | RectShape | undefined): this {
        if (((this._flagArray[35]) == (0)) || (true)) {
            this._flagArray[35] = 1
            this._clipContent_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[35] = 3
        }
        return this
    }
    digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        if (((this._flagArray[36]) == (0)) || (true)) {
            this._flagArray[36] = 1
            this._digitalCrownSensitivity_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[36] = 3
        }
        return this
    }
    backToTop(value: boolean | undefined): this {
        if (((this._flagArray[37]) == (0)) || ((this._backToTop_0_0value) !== (value))) {
            this._flagArray[37] = 1
            this._backToTop_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[37] = 3
        }
        return this
    }
    fadingEdge(enabled: boolean | undefined, options?: FadingEdgeOptions): this {
        if (((this._flagArray[38]) == (0)) || ((this._fadingEdge_0_0value) !== (enabled)) || (true)) {
            this._flagArray[38] = 1
            this._fadingEdge_0_0value = enabled
            this._fadingEdge_0_1value = options
            this._state.fireChange()
        } else {
            this._flagArray[38] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ScrollAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

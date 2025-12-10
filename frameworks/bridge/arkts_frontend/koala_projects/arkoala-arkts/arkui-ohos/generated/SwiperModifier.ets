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

import { CommonMethodModifier } from './CommonMethodModifier'
import { AttributeModifier, extractors } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkSwiperPeer, DotIndicator, DigitIndicator, SwiperDisplayMode, OnSwiperAnimationStartCallback, SwiperAnimationEvent, OnSwiperAnimationEndCallback, OnSwiperGestureSwipeCallback, SwiperNestedScrollMode, SwiperContentAnimatedTransition, ContentDidScrollCallback, ContentWillScrollCallback, SwiperContentWillScrollResult, SwiperAttribute, AutoPlayOptions, ArrowStyle, SwiperAutoFill } from './component/swiper'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod, Bindable, ICurve, Callback as arkui_component_common_Callback } from './component/common'
import { IndicatorComponentController } from './component/indicatorcomponent'
import { EdgeEffect, Curve, PageFlipMode } from './component/enums'
import { default as curves } from '@ohos.curves'
import { Length, Resource as arkui_component_units_Resource } from './component/units'
import { Resource as global_resource_Resource } from 'global.resource'
export class SwiperModifier extends CommonMethodModifier implements SwiperAttribute,AttributeModifier<SwiperAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState;
    _addr: ArrayBuffer = new ArrayBuffer(4096);
    _flagArray: Uint8Array = new Uint8Array(this._addr);
    constructor() {
        super();
        this._flagArray.fill(0);
    }
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: SwiperAttribute): void { }
    applyPressedAttribute(instance: SwiperAttribute): void { }
    applyFocusedAttribute(instance: SwiperAttribute): void { }
    applyDisabledAttribute(instance: SwiperAttribute): void { }
    applySelectedAttribute(instance: SwiperAttribute): void { }
    public _index_0_0value?: int32 | Bindable<int32> | undefined
    public _autoPlay_0_0value?: boolean | undefined
    public _interval_0_0value?: int32 | undefined
    public _indicator_0_0value?: IndicatorComponentController | DotIndicator | DigitIndicator | boolean | undefined
    public _loop_0_0value?: boolean | undefined
    public _duration_0_0value?: int32 | undefined
    public _vertical_0_0value?: boolean | undefined
    public _itemSpace_0_0value?: double | string | undefined
    public _displayMode_0_0value?: SwiperDisplayMode | undefined
    public _cachedCount_0_0value?: int32 | undefined
    public _effectMode_0_0value?: EdgeEffect | undefined
    public _disableSwipe_0_0value?: boolean | undefined
    public _curve_0_0value?: Curve | string | ICurve | undefined
    public _onChange_0_0value?: arkui_component_common_Callback<int32, void> | undefined
    public _onSelected_0_0value?: arkui_component_common_Callback<int32, void> | undefined
    public _onUnselected_0_0value?: arkui_component_common_Callback<int32, void> | undefined
    public _onAnimationStart_0_0value?: OnSwiperAnimationStartCallback | undefined
    public _onAnimationEnd_0_0value?: OnSwiperAnimationEndCallback | undefined
    public _onGestureSwipe_0_0value?: OnSwiperGestureSwipeCallback | undefined
    public _nestedScroll_0_0value?: SwiperNestedScrollMode | undefined
    public _customContentTransition_0_0value?: SwiperContentAnimatedTransition | undefined
    public _onContentDidScroll_0_0value?: ContentDidScrollCallback | undefined
    public _indicatorInteractive_0_0value?: boolean | undefined
    public _pageFlipMode_0_0value?: PageFlipMode | undefined
    public _onContentWillScroll_0_0value?: ContentWillScrollCallback | undefined
    public _autoPlay_1_0value?: boolean | undefined
    public _autoPlay_1_1value?: AutoPlayOptions | undefined
    public _displayArrow_0_0value?: ArrowStyle | boolean | undefined
    public _displayArrow_0_1value?: boolean | undefined
    public _cachedCount_1_0value?: int32 | undefined
    public _cachedCount_1_1value?: boolean | undefined
    public _displayCount_0_0value?: int32 | string | SwiperAutoFill | undefined
    public _displayCount_0_1value?: boolean | undefined
    public _prevMargin_0_0value?: Length | undefined
    public _prevMargin_0_1value?: boolean | undefined
    public _nextMargin_0_0value?: Length | undefined
    public _nextMargin_0_1value?: boolean | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkSwiperPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
        this.applyModifierPatch1(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkSwiperPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setIndexAttribute((this._index_0_0value as int32 | Bindable<int32> | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setIndexAttribute((undefined as int32 | Bindable<int32> | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setAutoPlay0Attribute((this._autoPlay_0_0value as boolean | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setAutoPlay0Attribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setIntervalAttribute((this._interval_0_0value as int32 | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setIntervalAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setIndicatorAttribute((this._indicator_0_0value as IndicatorComponentController | DotIndicator | DigitIndicator | boolean | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setIndicatorAttribute((undefined as IndicatorComponentController | DotIndicator | DigitIndicator | boolean | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setLoopAttribute((this._loop_0_0value as boolean | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setLoopAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setDurationAttribute((this._duration_0_0value as int32 | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setDurationAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1: {
                    peer.setVerticalAttribute((this._vertical_0_0value as boolean | undefined));
                    flagArray[6] = 2;
                    break;
                }
                case 3: {
                    flagArray[6] = 2;
                    break;
                }
                default: {
                    flagArray[6] = 0;
                    peer.setVerticalAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1: {
                    peer.setItemSpaceAttribute((this._itemSpace_0_0value as double | string | undefined));
                    flagArray[7] = 2;
                    break;
                }
                case 3: {
                    flagArray[7] = 2;
                    break;
                }
                default: {
                    flagArray[7] = 0;
                    peer.setItemSpaceAttribute((undefined as double | string | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1: {
                    peer.setDisplayModeAttribute((this._displayMode_0_0value as SwiperDisplayMode | undefined));
                    flagArray[8] = 2;
                    break;
                }
                case 3: {
                    flagArray[8] = 2;
                    break;
                }
                default: {
                    flagArray[8] = 0;
                    peer.setDisplayModeAttribute((undefined as SwiperDisplayMode | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1: {
                    peer.setCachedCount0Attribute((this._cachedCount_0_0value as int32 | undefined));
                    flagArray[9] = 2;
                    break;
                }
                case 3: {
                    flagArray[9] = 2;
                    break;
                }
                default: {
                    flagArray[9] = 0;
                    peer.setCachedCount0Attribute((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1: {
                    peer.setEffectModeAttribute((this._effectMode_0_0value as EdgeEffect | undefined));
                    flagArray[10] = 2;
                    break;
                }
                case 3: {
                    flagArray[10] = 2;
                    break;
                }
                default: {
                    flagArray[10] = 0;
                    peer.setEffectModeAttribute((undefined as EdgeEffect | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1: {
                    peer.setDisableSwipeAttribute((this._disableSwipe_0_0value as boolean | undefined));
                    flagArray[11] = 2;
                    break;
                }
                case 3: {
                    flagArray[11] = 2;
                    break;
                }
                default: {
                    flagArray[11] = 0;
                    peer.setDisableSwipeAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1: {
                    peer.setCurveAttribute((this._curve_0_0value as Curve | string | ICurve | undefined));
                    flagArray[12] = 2;
                    break;
                }
                case 3: {
                    flagArray[12] = 2;
                    break;
                }
                default: {
                    flagArray[12] = 0;
                    peer.setCurveAttribute((undefined as Curve | string | ICurve | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as arkui_component_common_Callback<int32, void> | undefined));
                    flagArray[13] = 2;
                    break;
                }
                case 3: {
                    flagArray[13] = 2;
                    break;
                }
                default: {
                    flagArray[13] = 0;
                    peer.setOnChangeAttribute((undefined as arkui_component_common_Callback<int32, void> | undefined));
                }
            }
        }
        if (flagArray[14] != 0) {
            switch (flagArray[14]) {
                case 1: {
                    peer.setOnSelectedAttribute((this._onSelected_0_0value as arkui_component_common_Callback<int32, void> | undefined));
                    flagArray[14] = 2;
                    break;
                }
                case 3: {
                    flagArray[14] = 2;
                    break;
                }
                default: {
                    flagArray[14] = 0;
                    peer.setOnSelectedAttribute((undefined as arkui_component_common_Callback<int32, void> | undefined));
                }
            }
        }
        if (flagArray[15] != 0) {
            switch (flagArray[15]) {
                case 1: {
                    peer.setOnUnselectedAttribute((this._onUnselected_0_0value as arkui_component_common_Callback<int32, void> | undefined));
                    flagArray[15] = 2;
                    break;
                }
                case 3: {
                    flagArray[15] = 2;
                    break;
                }
                default: {
                    flagArray[15] = 0;
                    peer.setOnUnselectedAttribute((undefined as arkui_component_common_Callback<int32, void> | undefined));
                }
            }
        }
        if (flagArray[16] != 0) {
            switch (flagArray[16]) {
                case 1: {
                    peer.setOnAnimationStartAttribute((this._onAnimationStart_0_0value as OnSwiperAnimationStartCallback | undefined));
                    flagArray[16] = 2;
                    break;
                }
                case 3: {
                    flagArray[16] = 2;
                    break;
                }
                default: {
                    flagArray[16] = 0;
                    peer.setOnAnimationStartAttribute((undefined as OnSwiperAnimationStartCallback | undefined));
                }
            }
        }
        if (flagArray[17] != 0) {
            switch (flagArray[17]) {
                case 1: {
                    peer.setOnAnimationEndAttribute((this._onAnimationEnd_0_0value as OnSwiperAnimationEndCallback | undefined));
                    flagArray[17] = 2;
                    break;
                }
                case 3: {
                    flagArray[17] = 2;
                    break;
                }
                default: {
                    flagArray[17] = 0;
                    peer.setOnAnimationEndAttribute((undefined as OnSwiperAnimationEndCallback | undefined));
                }
            }
        }
        if (flagArray[18] != 0) {
            switch (flagArray[18]) {
                case 1: {
                    peer.setOnGestureSwipeAttribute((this._onGestureSwipe_0_0value as OnSwiperGestureSwipeCallback | undefined));
                    flagArray[18] = 2;
                    break;
                }
                case 3: {
                    flagArray[18] = 2;
                    break;
                }
                default: {
                    flagArray[18] = 0;
                    peer.setOnGestureSwipeAttribute((undefined as OnSwiperGestureSwipeCallback | undefined));
                }
            }
        }
        if (flagArray[19] != 0) {
            switch (flagArray[19]) {
                case 1: {
                    peer.setNestedScrollAttribute((this._nestedScroll_0_0value as SwiperNestedScrollMode | undefined));
                    flagArray[19] = 2;
                    break;
                }
                case 3: {
                    flagArray[19] = 2;
                    break;
                }
                default: {
                    flagArray[19] = 0;
                    peer.setNestedScrollAttribute((undefined as SwiperNestedScrollMode | undefined));
                }
            }
        }
    }
    applyModifierPatch1(peer: ArkSwiperPeer, flagArray: Uint8Array): void {
        if (flagArray[20] != 0) {
            switch (flagArray[20]) {
                case 1: {
                    peer.setCustomContentTransitionAttribute((this._customContentTransition_0_0value as SwiperContentAnimatedTransition | undefined));
                    flagArray[20] = 2;
                    break;
                }
                case 3: {
                    flagArray[20] = 2;
                    break;
                }
                default: {
                    flagArray[20] = 0;
                    peer.setCustomContentTransitionAttribute((undefined as SwiperContentAnimatedTransition | undefined));
                }
            }
        }
        if (flagArray[21] != 0) {
            switch (flagArray[21]) {
                case 1: {
                    peer.setOnContentDidScrollAttribute((this._onContentDidScroll_0_0value as ContentDidScrollCallback | undefined));
                    flagArray[21] = 2;
                    break;
                }
                case 3: {
                    flagArray[21] = 2;
                    break;
                }
                default: {
                    flagArray[21] = 0;
                    peer.setOnContentDidScrollAttribute((undefined as ContentDidScrollCallback | undefined));
                }
            }
        }
        if (flagArray[22] != 0) {
            switch (flagArray[22]) {
                case 1: {
                    peer.setIndicatorInteractiveAttribute((this._indicatorInteractive_0_0value as boolean | undefined));
                    flagArray[22] = 2;
                    break;
                }
                case 3: {
                    flagArray[22] = 2;
                    break;
                }
                default: {
                    flagArray[22] = 0;
                    peer.setIndicatorInteractiveAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[23] != 0) {
            switch (flagArray[23]) {
                case 1: {
                    peer.setPageFlipModeAttribute((this._pageFlipMode_0_0value as PageFlipMode | undefined));
                    flagArray[23] = 2;
                    break;
                }
                case 3: {
                    flagArray[23] = 2;
                    break;
                }
                default: {
                    flagArray[23] = 0;
                    peer.setPageFlipModeAttribute((undefined as PageFlipMode | undefined));
                }
            }
        }
        if (flagArray[24] != 0) {
            switch (flagArray[24]) {
                case 1: {
                    peer.setOnContentWillScrollAttribute((this._onContentWillScroll_0_0value as ContentWillScrollCallback | undefined));
                    flagArray[24] = 2;
                    break;
                }
                case 3: {
                    flagArray[24] = 2;
                    break;
                }
                default: {
                    flagArray[24] = 0;
                    peer.setOnContentWillScrollAttribute((undefined as ContentWillScrollCallback | undefined));
                }
            }
        }
        if (flagArray[25] != 0) {
            switch (flagArray[25]) {
                case 1: {
                    peer.setAutoPlay1Attribute((this._autoPlay_1_0value as boolean | undefined), (this._autoPlay_1_1value as AutoPlayOptions | undefined));
                    flagArray[25] = 2;
                    break;
                }
                case 3: {
                    flagArray[25] = 2;
                    break;
                }
                default: {
                    flagArray[25] = 0;
                    peer.setAutoPlay1Attribute((undefined as boolean | undefined), (undefined as AutoPlayOptions | undefined));
                }
            }
        }
        if (flagArray[26] != 0) {
            switch (flagArray[26]) {
                case 1: {
                    peer.setDisplayArrowAttribute((this._displayArrow_0_0value as ArrowStyle | boolean | undefined), (this._displayArrow_0_1value as boolean | undefined | undefined));
                    flagArray[26] = 2;
                    break;
                }
                case 3: {
                    flagArray[26] = 2;
                    break;
                }
                default: {
                    flagArray[26] = 0;
                    peer.setDisplayArrowAttribute((undefined as ArrowStyle | boolean | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
        if (flagArray[27] != 0) {
            switch (flagArray[27]) {
                case 1: {
                    peer.setCachedCount1Attribute((this._cachedCount_1_0value as int32 | undefined), (this._cachedCount_1_1value as boolean | undefined));
                    flagArray[27] = 2;
                    break;
                }
                case 3: {
                    flagArray[27] = 2;
                    break;
                }
                default: {
                    flagArray[27] = 0;
                    peer.setCachedCount1Attribute((undefined as int32 | undefined), (undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[28] != 0) {
            switch (flagArray[28]) {
                case 1: {
                    peer.setDisplayCountAttribute((this._displayCount_0_0value as int32 | string | SwiperAutoFill | undefined), (this._displayCount_0_1value as boolean | undefined | undefined));
                    flagArray[28] = 2;
                    break;
                }
                case 3: {
                    flagArray[28] = 2;
                    break;
                }
                default: {
                    flagArray[28] = 0;
                    peer.setDisplayCountAttribute((undefined as int32 | string | SwiperAutoFill | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
        if (flagArray[29] != 0) {
            switch (flagArray[29]) {
                case 1: {
                    peer.setPrevMarginAttribute((this._prevMargin_0_0value as Length | undefined), (this._prevMargin_0_1value as boolean | undefined | undefined));
                    flagArray[29] = 2;
                    break;
                }
                case 3: {
                    flagArray[29] = 2;
                    break;
                }
                default: {
                    flagArray[29] = 0;
                    peer.setPrevMarginAttribute((undefined as Length | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
        if (flagArray[30] != 0) {
            switch (flagArray[30]) {
                case 1: {
                    peer.setNextMarginAttribute((this._nextMargin_0_0value as Length | undefined), (this._nextMargin_0_1value as boolean | undefined | undefined));
                    flagArray[30] = 2;
                    break;
                }
                case 3: {
                    flagArray[30] = 2;
                    break;
                }
                default: {
                    flagArray[30] = 0;
                    peer.setNextMarginAttribute((undefined as Length | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: SwiperModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
        this.mergeModifier1(modifier, flagArray);
    }
    mergeModifier0(modifier: SwiperModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.index(modifier._index_0_0value);
                    break;
                }
                default: {
                    this.index((undefined as int32 | Bindable<int32> | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.autoPlay(modifier._autoPlay_0_0value);
                    break;
                }
                default: {
                    this.autoPlay((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.interval(modifier._interval_0_0value);
                    break;
                }
                default: {
                    this.interval((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.indicator(modifier._indicator_0_0value);
                    break;
                }
                default: {
                    this.indicator((undefined as IndicatorComponentController | DotIndicator | DigitIndicator | boolean | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.loop(modifier._loop_0_0value);
                    break;
                }
                default: {
                    this.loop((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1:
                case 3: {
                    this.duration(modifier._duration_0_0value);
                    break;
                }
                default: {
                    this.duration((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1:
                case 3: {
                    this.vertical(modifier._vertical_0_0value);
                    break;
                }
                default: {
                    this.vertical((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1:
                case 3: {
                    this.itemSpace(modifier._itemSpace_0_0value);
                    break;
                }
                default: {
                    this.itemSpace((undefined as double | string | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1:
                case 3: {
                    this.displayMode(modifier._displayMode_0_0value);
                    break;
                }
                default: {
                    this.displayMode((undefined as SwiperDisplayMode | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1:
                case 3: {
                    this.cachedCount(modifier._cachedCount_0_0value);
                    break;
                }
                default: {
                    this.cachedCount((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1:
                case 3: {
                    this.effectMode(modifier._effectMode_0_0value);
                    break;
                }
                default: {
                    this.effectMode((undefined as EdgeEffect | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1:
                case 3: {
                    this.disableSwipe(modifier._disableSwipe_0_0value);
                    break;
                }
                default: {
                    this.disableSwipe((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1:
                case 3: {
                    this.curve(modifier._curve_0_0value);
                    break;
                }
                default: {
                    this.curve((undefined as Curve | string | ICurve | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1:
                case 3: {
                    this.onChange(modifier._onChange_0_0value);
                    break;
                }
                default: {
                    this.onChange((undefined as arkui_component_common_Callback<int32, void> | undefined));
                }
            }
        }
        if (flagArray[14] != 0) {
            switch (flagArray[14]) {
                case 1:
                case 3: {
                    this.onSelected(modifier._onSelected_0_0value);
                    break;
                }
                default: {
                    this.onSelected((undefined as arkui_component_common_Callback<int32, void> | undefined));
                }
            }
        }
        if (flagArray[15] != 0) {
            switch (flagArray[15]) {
                case 1:
                case 3: {
                    this.onUnselected(modifier._onUnselected_0_0value);
                    break;
                }
                default: {
                    this.onUnselected((undefined as arkui_component_common_Callback<int32, void> | undefined));
                }
            }
        }
        if (flagArray[16] != 0) {
            switch (flagArray[16]) {
                case 1:
                case 3: {
                    this.onAnimationStart(modifier._onAnimationStart_0_0value);
                    break;
                }
                default: {
                    this.onAnimationStart((undefined as OnSwiperAnimationStartCallback | undefined));
                }
            }
        }
        if (flagArray[17] != 0) {
            switch (flagArray[17]) {
                case 1:
                case 3: {
                    this.onAnimationEnd(modifier._onAnimationEnd_0_0value);
                    break;
                }
                default: {
                    this.onAnimationEnd((undefined as OnSwiperAnimationEndCallback | undefined));
                }
            }
        }
        if (flagArray[18] != 0) {
            switch (flagArray[18]) {
                case 1:
                case 3: {
                    this.onGestureSwipe(modifier._onGestureSwipe_0_0value);
                    break;
                }
                default: {
                    this.onGestureSwipe((undefined as OnSwiperGestureSwipeCallback | undefined));
                }
            }
        }
        if (flagArray[19] != 0) {
            switch (flagArray[19]) {
                case 1:
                case 3: {
                    this.nestedScroll(modifier._nestedScroll_0_0value);
                    break;
                }
                default: {
                    this.nestedScroll((undefined as SwiperNestedScrollMode | undefined));
                }
            }
        }
    }
    mergeModifier1(modifier: SwiperModifier, flagArray: Uint8Array): void {
        if (flagArray[20] != 0) {
            switch (flagArray[20]) {
                case 1:
                case 3: {
                    this.customContentTransition(modifier._customContentTransition_0_0value);
                    break;
                }
                default: {
                    this.customContentTransition((undefined as SwiperContentAnimatedTransition | undefined));
                }
            }
        }
        if (flagArray[21] != 0) {
            switch (flagArray[21]) {
                case 1:
                case 3: {
                    this.onContentDidScroll(modifier._onContentDidScroll_0_0value);
                    break;
                }
                default: {
                    this.onContentDidScroll((undefined as ContentDidScrollCallback | undefined));
                }
            }
        }
        if (flagArray[22] != 0) {
            switch (flagArray[22]) {
                case 1:
                case 3: {
                    this.indicatorInteractive(modifier._indicatorInteractive_0_0value);
                    break;
                }
                default: {
                    this.indicatorInteractive((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[23] != 0) {
            switch (flagArray[23]) {
                case 1:
                case 3: {
                    this.pageFlipMode(modifier._pageFlipMode_0_0value);
                    break;
                }
                default: {
                    this.pageFlipMode((undefined as PageFlipMode | undefined));
                }
            }
        }
        if (flagArray[24] != 0) {
            switch (flagArray[24]) {
                case 1:
                case 3: {
                    this.onContentWillScroll(modifier._onContentWillScroll_0_0value);
                    break;
                }
                default: {
                    this.onContentWillScroll((undefined as ContentWillScrollCallback | undefined));
                }
            }
        }
        if (flagArray[25] != 0) {
            switch (flagArray[25]) {
                case 1:
                case 3: {
                    this.autoPlay(modifier._autoPlay_1_0value, modifier._autoPlay_1_1value);
                    break;
                }
                default: {
                    this.autoPlay((undefined as boolean | undefined), (undefined as AutoPlayOptions | undefined));
                }
            }
        }
        if (flagArray[26] != 0) {
            switch (flagArray[26]) {
                case 1:
                case 3: {
                    this.displayArrow(modifier._displayArrow_0_0value, modifier._displayArrow_0_1value);
                    break;
                }
                default: {
                    this.displayArrow((undefined as ArrowStyle | boolean | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
        if (flagArray[27] != 0) {
            switch (flagArray[27]) {
                case 1:
                case 3: {
                    this.cachedCount(modifier._cachedCount_1_0value, modifier._cachedCount_1_1value);
                    break;
                }
                default: {
                    this.cachedCount((undefined as int32 | undefined), (undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[28] != 0) {
            switch (flagArray[28]) {
                case 1:
                case 3: {
                    this.displayCount(modifier._displayCount_0_0value, modifier._displayCount_0_1value);
                    break;
                }
                default: {
                    this.displayCount((undefined as int32 | string | SwiperAutoFill | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
        if (flagArray[29] != 0) {
            switch (flagArray[29]) {
                case 1:
                case 3: {
                    this.prevMargin(modifier._prevMargin_0_0value, modifier._prevMargin_0_1value);
                    break;
                }
                default: {
                    this.prevMargin((undefined as Length | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
        if (flagArray[30] != 0) {
            switch (flagArray[30]) {
                case 1:
                case 3: {
                    this.nextMargin(modifier._nextMargin_0_0value, modifier._nextMargin_0_1value);
                    break;
                }
                default: {
                    this.nextMargin((undefined as Length | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
    }
    index(value: int32 | Bindable<int32> | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._index_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    autoPlay(value: boolean | undefined): this {
        if (((this._flagArray[1]) == (0)) || ((this._autoPlay_0_0value) !== (value))) {
            this._flagArray[1] = 1
            this._autoPlay_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    interval(value: int32 | undefined): this {
        if (((this._flagArray[2]) == (0)) || ((this._interval_0_0value) !== (value))) {
            this._flagArray[2] = 1
            this._interval_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    indicator(value: IndicatorComponentController | DotIndicator | DigitIndicator | boolean | undefined): this {
        if (((this._flagArray[3]) == (0)) || (true)) {
            this._flagArray[3] = 1
            this._indicator_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    loop(value: boolean | undefined): this {
        if (((this._flagArray[4]) == (0)) || ((this._loop_0_0value) !== (value))) {
            this._flagArray[4] = 1
            this._loop_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    duration(value: int32 | undefined): this {
        if (((this._flagArray[5]) == (0)) || ((this._duration_0_0value) !== (value))) {
            this._flagArray[5] = 1
            this._duration_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    vertical(value: boolean | undefined): this {
        if (((this._flagArray[6]) == (0)) || ((this._vertical_0_0value) !== (value))) {
            this._flagArray[6] = 1
            this._vertical_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[6] = 3
        }
        return this
    }
    itemSpace(value: double | string | undefined): this {
        if (((this._flagArray[7]) == (0)) || ((this._itemSpace_0_0value) !== (value))) {
            this._flagArray[7] = 1
            this._itemSpace_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[7] = 3
        }
        return this
    }
    displayMode(value: SwiperDisplayMode | undefined): this {
        if (((this._flagArray[8]) == (0)) || (true)) {
            this._flagArray[8] = 1
            this._displayMode_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[8] = 3
        }
        return this
    }
    cachedCount(value: int32 | undefined): this {
        if (((this._flagArray[9]) == (0)) || ((this._cachedCount_0_0value) !== (value))) {
            this._flagArray[9] = 1
            this._cachedCount_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[9] = 3
        }
        return this
    }
    effectMode(value: EdgeEffect | undefined): this {
        if (((this._flagArray[10]) == (0)) || (true)) {
            this._flagArray[10] = 1
            this._effectMode_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[10] = 3
        }
        return this
    }
    disableSwipe(value: boolean | undefined): this {
        if (((this._flagArray[11]) == (0)) || ((this._disableSwipe_0_0value) !== (value))) {
            this._flagArray[11] = 1
            this._disableSwipe_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[11] = 3
        }
        return this
    }
    curve(value: Curve | string | ICurve | undefined): this {
        if (((this._flagArray[12]) == (0)) || (true)) {
            this._flagArray[12] = 1
            this._curve_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[12] = 3
        }
        return this
    }
    onChange(value: arkui_component_common_Callback<int32, void> | undefined): this {
        if (((this._flagArray[13]) == (0)) || (true)) {
            this._flagArray[13] = 1
            this._onChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[13] = 3
        }
        return this
    }
    onSelected(value: arkui_component_common_Callback<int32, void> | undefined): this {
        if (((this._flagArray[14]) == (0)) || (true)) {
            this._flagArray[14] = 1
            this._onSelected_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[14] = 3
        }
        return this
    }
    onUnselected(value: arkui_component_common_Callback<int32, void> | undefined): this {
        if (((this._flagArray[15]) == (0)) || (true)) {
            this._flagArray[15] = 1
            this._onUnselected_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[15] = 3
        }
        return this
    }
    onAnimationStart(value: OnSwiperAnimationStartCallback | undefined): this {
        if (((this._flagArray[16]) == (0)) || (true)) {
            this._flagArray[16] = 1
            this._onAnimationStart_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[16] = 3
        }
        return this
    }
    onAnimationEnd(value: OnSwiperAnimationEndCallback | undefined): this {
        if (((this._flagArray[17]) == (0)) || (true)) {
            this._flagArray[17] = 1
            this._onAnimationEnd_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[17] = 3
        }
        return this
    }
    onGestureSwipe(value: OnSwiperGestureSwipeCallback | undefined): this {
        if (((this._flagArray[18]) == (0)) || (true)) {
            this._flagArray[18] = 1
            this._onGestureSwipe_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[18] = 3
        }
        return this
    }
    nestedScroll(value: SwiperNestedScrollMode | undefined): this {
        if (((this._flagArray[19]) == (0)) || (true)) {
            this._flagArray[19] = 1
            this._nestedScroll_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[19] = 3
        }
        return this
    }
    customContentTransition(value: SwiperContentAnimatedTransition | undefined): this {
        if (((this._flagArray[20]) == (0)) || (true)) {
            this._flagArray[20] = 1
            this._customContentTransition_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[20] = 3
        }
        return this
    }
    onContentDidScroll(value: ContentDidScrollCallback | undefined): this {
        if (((this._flagArray[21]) == (0)) || (true)) {
            this._flagArray[21] = 1
            this._onContentDidScroll_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[21] = 3
        }
        return this
    }
    indicatorInteractive(value: boolean | undefined): this {
        if (((this._flagArray[22]) == (0)) || ((this._indicatorInteractive_0_0value) !== (value))) {
            this._flagArray[22] = 1
            this._indicatorInteractive_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[22] = 3
        }
        return this
    }
    pageFlipMode(value: PageFlipMode | undefined): this {
        if (((this._flagArray[23]) == (0)) || (true)) {
            this._flagArray[23] = 1
            this._pageFlipMode_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[23] = 3
        }
        return this
    }
    onContentWillScroll(value: ContentWillScrollCallback | undefined): this {
        if (((this._flagArray[24]) == (0)) || (true)) {
            this._flagArray[24] = 1
            this._onContentWillScroll_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[24] = 3
        }
        return this
    }
    autoPlay(autoPlay: boolean | undefined, options: AutoPlayOptions | undefined): this {
        if (((this._flagArray[25]) == (0)) || ((this._autoPlay_1_0value) !== (autoPlay)) || (true)) {
            this._flagArray[25] = 1
            this._autoPlay_1_0value = autoPlay
            this._autoPlay_1_1value = options
            this._state.fireChange()
        } else {
            this._flagArray[25] = 3
        }
        return this
    }
    displayArrow(value: ArrowStyle | boolean | undefined, isHoverShow?: boolean): this {
        if (((this._flagArray[26]) == (0)) || (true) || ((this._displayArrow_0_1value) !== (isHoverShow))) {
            this._flagArray[26] = 1
            this._displayArrow_0_0value = value
            this._displayArrow_0_1value = isHoverShow
            this._state.fireChange()
        } else {
            this._flagArray[26] = 3
        }
        return this
    }
    cachedCount(count: int32 | undefined, isShown: boolean | undefined): this {
        if (((this._flagArray[27]) == (0)) || ((this._cachedCount_1_0value) !== (count)) || ((this._cachedCount_1_1value) !== (isShown))) {
            this._flagArray[27] = 1
            this._cachedCount_1_0value = count
            this._cachedCount_1_1value = isShown
            this._state.fireChange()
        } else {
            this._flagArray[27] = 3
        }
        return this
    }
    displayCount(value: int32 | string | SwiperAutoFill | undefined, swipeByGroup?: boolean): this {
        if (((this._flagArray[28]) == (0)) || (true) || ((this._displayCount_0_1value) !== (swipeByGroup))) {
            this._flagArray[28] = 1
            this._displayCount_0_0value = value
            this._displayCount_0_1value = swipeByGroup
            this._state.fireChange()
        } else {
            this._flagArray[28] = 3
        }
        return this
    }
    prevMargin(value: Length | undefined, ignoreBlank?: boolean): this {
        if (((this._flagArray[29]) == (0)) || (true) || ((this._prevMargin_0_1value) !== (ignoreBlank))) {
            this._flagArray[29] = 1
            this._prevMargin_0_0value = value
            this._prevMargin_0_1value = ignoreBlank
            this._state.fireChange()
        } else {
            this._flagArray[29] = 3
        }
        return this
    }
    nextMargin(value: Length | undefined, ignoreBlank?: boolean): this {
        if (((this._flagArray[30]) == (0)) || (true) || ((this._nextMargin_0_1value) !== (ignoreBlank))) {
            this._flagArray[30] = 1
            this._nextMargin_0_0value = value
            this._nextMargin_0_1value = ignoreBlank
            this._state.fireChange()
        } else {
            this._flagArray[30] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<SwiperAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

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
import { ArkSwiperPeer, DotIndicator, DigitIndicator, SwiperDisplayMode, OnSwiperAnimationStartCallback, SwiperAnimationEvent, OnSwiperAnimationEndCallback, OnSwiperGestureSwipeCallback, SwiperNestedScrollMode, SwiperContentAnimatedTransition, ContentDidScrollCallback, ContentWillScrollCallback, SwiperContentWillScrollResult, SwiperAttribute, AutoPlayOptions, ArrowStyle, SwiperAutoFill } from "./component/swiper"
import { int32 } from "@koalaui/common"
import { CommonMethod, Bindable } from "./component/common"
import { IndicatorComponentController } from "./component/indicatorcomponent"
import { EdgeEffect, PageFlipMode } from "./component/enums"
import { default as curves } from "@ohos.curves"
import { Length } from "./component/units"
import { Resource } from "global.resource"
export class SwiperModifier extends CommonMethodModifier implements SwiperAttribute,AttributeModifier<SwiperAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: SwiperAttribute): void { }
    applyPressedAttribute(instance: SwiperAttribute): void { }
    applyFocusedAttribute(instance: SwiperAttribute): void { }
    applyDisabledAttribute(instance: SwiperAttribute): void { }
    applySelectedAttribute(instance: SwiperAttribute): void { }
    _index_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _index_0_0value?: int32 | Bindable<int32> | undefined
    _autoPlay_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _autoPlay_0_0value?: boolean | undefined
    _interval_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _interval_0_0value?: int32 | undefined
    _indicator_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _indicator_0_0value?: IndicatorComponentController | DotIndicator | DigitIndicator | boolean | undefined
    _loop_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _loop_0_0value?: boolean | undefined
    _duration_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _duration_0_0value?: int32 | undefined
    _vertical_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _vertical_0_0value?: boolean | undefined
    _itemSpace_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _itemSpace_0_0value?: double | string | undefined
    _displayMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _displayMode_0_0value?: SwiperDisplayMode | undefined
    _cachedCount_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _cachedCount_0_0value?: int32 | undefined
    _effectMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _effectMode_0_0value?: EdgeEffect | undefined
    _disableSwipe_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _disableSwipe_0_0value?: boolean | undefined
    _curve_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _curve_0_0value?: curves.Curve | string | curves.ICurve | undefined
    _onChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onChange_0_0value?: ((value0: int32) => void) | undefined
    _onSelected_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onSelected_0_0value?: ((value0: int32) => void) | undefined
    _onUnselected_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onUnselected_0_0value?: ((value0: int32) => void) | undefined
    _onAnimationStart_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onAnimationStart_0_0value?: OnSwiperAnimationStartCallback | undefined
    _onAnimationEnd_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onAnimationEnd_0_0value?: OnSwiperAnimationEndCallback | undefined
    _onGestureSwipe_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onGestureSwipe_0_0value?: OnSwiperGestureSwipeCallback | undefined
    _nestedScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _nestedScroll_0_0value?: SwiperNestedScrollMode | undefined
    _customContentTransition_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _customContentTransition_0_0value?: SwiperContentAnimatedTransition | undefined
    _onContentDidScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onContentDidScroll_0_0value?: ContentDidScrollCallback | undefined
    _indicatorInteractive_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _indicatorInteractive_0_0value?: boolean | undefined
    _pageFlipMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _pageFlipMode_0_0value?: PageFlipMode | undefined
    _onContentWillScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onContentWillScroll_0_0value?: ContentWillScrollCallback | undefined
    _autoPlay_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _autoPlay_1_0value?: boolean | undefined
    _autoPlay_1_1value?: AutoPlayOptions | undefined
    _displayArrow_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _displayArrow_0_0value?: ArrowStyle | boolean | undefined
    _displayArrow_0_1value?: boolean | undefined
    _cachedCount_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _cachedCount_1_0value?: int32 | undefined
    _cachedCount_1_1value?: boolean | undefined
    _displayCount_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _displayCount_0_0value?: int32 | string | SwiperAutoFill | undefined
    _displayCount_0_1value?: boolean | undefined
    _prevMargin_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _prevMargin_0_0value?: Length | undefined
    _prevMargin_0_1value?: boolean | undefined
    _nextMargin_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _nextMargin_0_0value?: Length | undefined
    _nextMargin_0_1value?: boolean | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkSwiperPeer;
        if (this._index_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._index_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setIndexAttribute((this._index_0_0value as int32 | Bindable<int32> | undefined));
                    this._index_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._index_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._index_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setIndexAttribute((undefined as int32 | Bindable<int32> | undefined));
                }
            }
        }
        if (this._autoPlay_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._autoPlay_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAutoPlay0Attribute((this._autoPlay_0_0value as boolean | undefined));
                    this._autoPlay_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._autoPlay_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._autoPlay_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAutoPlay0Attribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._interval_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._interval_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setIntervalAttribute((this._interval_0_0value as int32 | undefined));
                    this._interval_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._interval_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._interval_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setIntervalAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (this._indicator_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._indicator_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setIndicatorAttribute((this._indicator_0_0value as IndicatorComponentController | DotIndicator | DigitIndicator | boolean | undefined));
                    this._indicator_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._indicator_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._indicator_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setIndicatorAttribute((undefined as IndicatorComponentController | DotIndicator | DigitIndicator | boolean | undefined));
                }
            }
        }
        if (this._loop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._loop_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setLoopAttribute((this._loop_0_0value as boolean | undefined));
                    this._loop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._loop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._loop_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setLoopAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._duration_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._duration_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDurationAttribute((this._duration_0_0value as int32 | undefined));
                    this._duration_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._duration_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._duration_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDurationAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (this._vertical_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._vertical_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setVerticalAttribute((this._vertical_0_0value as boolean | undefined));
                    this._vertical_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._vertical_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._vertical_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setVerticalAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._itemSpace_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._itemSpace_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setItemSpaceAttribute((this._itemSpace_0_0value as double | string | undefined));
                    this._itemSpace_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._itemSpace_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._itemSpace_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setItemSpaceAttribute((undefined as double | string | undefined));
                }
            }
        }
        if (this._displayMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._displayMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDisplayModeAttribute((this._displayMode_0_0value as SwiperDisplayMode | undefined));
                    this._displayMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._displayMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._displayMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDisplayModeAttribute((undefined as SwiperDisplayMode | undefined));
                }
            }
        }
        if (this._cachedCount_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._cachedCount_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCachedCount0Attribute((this._cachedCount_0_0value as int32 | undefined));
                    this._cachedCount_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._cachedCount_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._cachedCount_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCachedCount0Attribute((undefined as int32 | undefined));
                }
            }
        }
        if (this._effectMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._effectMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEffectModeAttribute((this._effectMode_0_0value as EdgeEffect | undefined));
                    this._effectMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._effectMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._effectMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEffectModeAttribute((undefined as EdgeEffect | undefined));
                }
            }
        }
        if (this._disableSwipe_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._disableSwipe_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDisableSwipeAttribute((this._disableSwipe_0_0value as boolean | undefined));
                    this._disableSwipe_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._disableSwipe_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._disableSwipe_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDisableSwipeAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._curve_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._curve_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCurveAttribute((this._curve_0_0value as curves.Curve | string | curves.ICurve | undefined));
                    this._curve_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._curve_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._curve_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCurveAttribute((undefined as curves.Curve | string | curves.ICurve | undefined));
                }
            }
        }
        if (this._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as ((value0: int32) => void) | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnChangeAttribute((undefined as ((value0: int32) => void) | undefined));
                }
            }
        }
        if (this._onSelected_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onSelected_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnSelectedAttribute((this._onSelected_0_0value as ((value0: int32) => void) | undefined));
                    this._onSelected_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onSelected_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onSelected_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnSelectedAttribute((undefined as ((value0: int32) => void) | undefined));
                }
            }
        }
        if (this._onUnselected_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onUnselected_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnUnselectedAttribute((this._onUnselected_0_0value as ((value0: int32) => void) | undefined));
                    this._onUnselected_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onUnselected_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onUnselected_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnUnselectedAttribute((undefined as ((value0: int32) => void) | undefined));
                }
            }
        }
        if (this._onAnimationStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onAnimationStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnAnimationStartAttribute((this._onAnimationStart_0_0value as OnSwiperAnimationStartCallback | undefined));
                    this._onAnimationStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onAnimationStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onAnimationStart_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnAnimationStartAttribute((undefined as OnSwiperAnimationStartCallback | undefined));
                }
            }
        }
        if (this._onAnimationEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onAnimationEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnAnimationEndAttribute((this._onAnimationEnd_0_0value as OnSwiperAnimationEndCallback | undefined));
                    this._onAnimationEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onAnimationEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onAnimationEnd_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnAnimationEndAttribute((undefined as OnSwiperAnimationEndCallback | undefined));
                }
            }
        }
        if (this._onGestureSwipe_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onGestureSwipe_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnGestureSwipeAttribute((this._onGestureSwipe_0_0value as OnSwiperGestureSwipeCallback | undefined));
                    this._onGestureSwipe_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onGestureSwipe_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onGestureSwipe_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnGestureSwipeAttribute((undefined as OnSwiperGestureSwipeCallback | undefined));
                }
            }
        }
        if (this._nestedScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._nestedScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setNestedScrollAttribute((this._nestedScroll_0_0value as SwiperNestedScrollMode | undefined));
                    this._nestedScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._nestedScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._nestedScroll_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setNestedScrollAttribute((undefined as SwiperNestedScrollMode | undefined));
                }
            }
        }
        if (this._customContentTransition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._customContentTransition_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCustomContentTransitionAttribute((this._customContentTransition_0_0value as SwiperContentAnimatedTransition | undefined));
                    this._customContentTransition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._customContentTransition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._customContentTransition_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCustomContentTransitionAttribute((undefined as SwiperContentAnimatedTransition | undefined));
                }
            }
        }
        if (this._onContentDidScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onContentDidScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnContentDidScrollAttribute((this._onContentDidScroll_0_0value as ContentDidScrollCallback | undefined));
                    this._onContentDidScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onContentDidScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onContentDidScroll_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnContentDidScrollAttribute((undefined as ContentDidScrollCallback | undefined));
                }
            }
        }
        if (this._indicatorInteractive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._indicatorInteractive_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setIndicatorInteractiveAttribute((this._indicatorInteractive_0_0value as boolean | undefined));
                    this._indicatorInteractive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._indicatorInteractive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._indicatorInteractive_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setIndicatorInteractiveAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._pageFlipMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._pageFlipMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPageFlipModeAttribute((this._pageFlipMode_0_0value as PageFlipMode | undefined));
                    this._pageFlipMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._pageFlipMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._pageFlipMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPageFlipModeAttribute((undefined as PageFlipMode | undefined));
                }
            }
        }
        if (this._onContentWillScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onContentWillScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnContentWillScrollAttribute((this._onContentWillScroll_0_0value as ContentWillScrollCallback | undefined));
                    this._onContentWillScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onContentWillScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onContentWillScroll_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnContentWillScrollAttribute((undefined as ContentWillScrollCallback | undefined));
                }
            }
        }
        if (this._autoPlay_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._autoPlay_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAutoPlay1Attribute((this._autoPlay_1_0value as boolean | undefined), (this._autoPlay_1_1value as AutoPlayOptions | undefined));
                    this._autoPlay_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._autoPlay_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._autoPlay_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAutoPlay1Attribute((undefined as boolean | undefined), (undefined as AutoPlayOptions | undefined));
                }
            }
        }
        if (this._displayArrow_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._displayArrow_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDisplayArrowAttribute((this._displayArrow_0_0value as ArrowStyle | boolean | undefined), (this._displayArrow_0_1value as boolean | undefined | undefined));
                    this._displayArrow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._displayArrow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._displayArrow_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDisplayArrowAttribute((undefined as ArrowStyle | boolean | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
        if (this._cachedCount_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._cachedCount_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCachedCount1Attribute((this._cachedCount_1_0value as int32 | undefined), (this._cachedCount_1_1value as boolean | undefined));
                    this._cachedCount_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._cachedCount_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._cachedCount_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCachedCount1Attribute((undefined as int32 | undefined), (undefined as boolean | undefined));
                }
            }
        }
        if (this._displayCount_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._displayCount_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDisplayCountAttribute((this._displayCount_0_0value as int32 | string | SwiperAutoFill | undefined), (this._displayCount_0_1value as boolean | undefined | undefined));
                    this._displayCount_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._displayCount_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._displayCount_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDisplayCountAttribute((undefined as int32 | string | SwiperAutoFill | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
        if (this._prevMargin_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._prevMargin_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPrevMarginAttribute((this._prevMargin_0_0value as Length | undefined), (this._prevMargin_0_1value as boolean | undefined | undefined));
                    this._prevMargin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._prevMargin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._prevMargin_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPrevMarginAttribute((undefined as Length | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
        if (this._nextMargin_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._nextMargin_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setNextMarginAttribute((this._nextMargin_0_0value as Length | undefined), (this._nextMargin_0_1value as boolean | undefined | undefined));
                    this._nextMargin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._nextMargin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._nextMargin_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setNextMarginAttribute((undefined as Length | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: SwiperModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._index_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._index_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.index(modifier._index_0_0value);
                    break;
                }
                default: {
                    this.index((undefined as int32 | Bindable<int32> | undefined));
                }
            }
        }
        if (modifier._autoPlay_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._autoPlay_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.autoPlay(modifier._autoPlay_0_0value);
                    break;
                }
                default: {
                    this.autoPlay((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._interval_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._interval_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.interval(modifier._interval_0_0value);
                    break;
                }
                default: {
                    this.interval((undefined as int32 | undefined));
                }
            }
        }
        if (modifier._indicator_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._indicator_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.indicator(modifier._indicator_0_0value);
                    break;
                }
                default: {
                    this.indicator((undefined as IndicatorComponentController | DotIndicator | DigitIndicator | boolean | undefined));
                }
            }
        }
        if (modifier._loop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._loop_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.loop(modifier._loop_0_0value);
                    break;
                }
                default: {
                    this.loop((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._duration_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._duration_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.duration(modifier._duration_0_0value);
                    break;
                }
                default: {
                    this.duration((undefined as int32 | undefined));
                }
            }
        }
        if (modifier._vertical_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._vertical_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.vertical(modifier._vertical_0_0value);
                    break;
                }
                default: {
                    this.vertical((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._itemSpace_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._itemSpace_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.itemSpace(modifier._itemSpace_0_0value);
                    break;
                }
                default: {
                    this.itemSpace((undefined as double | string | undefined));
                }
            }
        }
        if (modifier._displayMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._displayMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.displayMode(modifier._displayMode_0_0value);
                    break;
                }
                default: {
                    this.displayMode((undefined as SwiperDisplayMode | undefined));
                }
            }
        }
        if (modifier._cachedCount_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._cachedCount_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.cachedCount(modifier._cachedCount_0_0value);
                    break;
                }
                default: {
                    this.cachedCount((undefined as int32 | undefined));
                }
            }
        }
        if (modifier._effectMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._effectMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.effectMode(modifier._effectMode_0_0value);
                    break;
                }
                default: {
                    this.effectMode((undefined as EdgeEffect | undefined));
                }
            }
        }
        if (modifier._disableSwipe_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._disableSwipe_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.disableSwipe(modifier._disableSwipe_0_0value);
                    break;
                }
                default: {
                    this.disableSwipe((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._curve_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._curve_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.curve(modifier._curve_0_0value);
                    break;
                }
                default: {
                    this.curve((undefined as curves.Curve | string | curves.ICurve | undefined));
                }
            }
        }
        if (modifier._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onChange(modifier._onChange_0_0value);
                    break;
                }
                default: {
                    this.onChange((undefined as ((value0: int32) => void) | undefined));
                }
            }
        }
        if (modifier._onSelected_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onSelected_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onSelected(modifier._onSelected_0_0value);
                    break;
                }
                default: {
                    this.onSelected((undefined as ((value0: int32) => void) | undefined));
                }
            }
        }
        if (modifier._onUnselected_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onUnselected_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onUnselected(modifier._onUnselected_0_0value);
                    break;
                }
                default: {
                    this.onUnselected((undefined as ((value0: int32) => void) | undefined));
                }
            }
        }
        if (modifier._onAnimationStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onAnimationStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onAnimationStart(modifier._onAnimationStart_0_0value);
                    break;
                }
                default: {
                    this.onAnimationStart((undefined as OnSwiperAnimationStartCallback | undefined));
                }
            }
        }
        if (modifier._onAnimationEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onAnimationEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onAnimationEnd(modifier._onAnimationEnd_0_0value);
                    break;
                }
                default: {
                    this.onAnimationEnd((undefined as OnSwiperAnimationEndCallback | undefined));
                }
            }
        }
        if (modifier._onGestureSwipe_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onGestureSwipe_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onGestureSwipe(modifier._onGestureSwipe_0_0value);
                    break;
                }
                default: {
                    this.onGestureSwipe((undefined as OnSwiperGestureSwipeCallback | undefined));
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
                    this.nestedScroll((undefined as SwiperNestedScrollMode | undefined));
                }
            }
        }
        if (modifier._customContentTransition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._customContentTransition_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.customContentTransition(modifier._customContentTransition_0_0value);
                    break;
                }
                default: {
                    this.customContentTransition((undefined as SwiperContentAnimatedTransition | undefined));
                }
            }
        }
        if (modifier._onContentDidScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onContentDidScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onContentDidScroll(modifier._onContentDidScroll_0_0value);
                    break;
                }
                default: {
                    this.onContentDidScroll((undefined as ContentDidScrollCallback | undefined));
                }
            }
        }
        if (modifier._indicatorInteractive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._indicatorInteractive_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.indicatorInteractive(modifier._indicatorInteractive_0_0value);
                    break;
                }
                default: {
                    this.indicatorInteractive((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._pageFlipMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._pageFlipMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.pageFlipMode(modifier._pageFlipMode_0_0value);
                    break;
                }
                default: {
                    this.pageFlipMode((undefined as PageFlipMode | undefined));
                }
            }
        }
        if (modifier._onContentWillScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onContentWillScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onContentWillScroll(modifier._onContentWillScroll_0_0value);
                    break;
                }
                default: {
                    this.onContentWillScroll((undefined as ContentWillScrollCallback | undefined));
                }
            }
        }
        if (modifier._autoPlay_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._autoPlay_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.autoPlay(modifier._autoPlay_1_0value, modifier._autoPlay_1_1value);
                    break;
                }
                default: {
                    this.autoPlay((undefined as boolean | undefined), (undefined as AutoPlayOptions | undefined));
                }
            }
        }
        if (modifier._displayArrow_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._displayArrow_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.displayArrow(modifier._displayArrow_0_0value, modifier._displayArrow_0_1value);
                    break;
                }
                default: {
                    this.displayArrow((undefined as ArrowStyle | boolean | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
        if (modifier._cachedCount_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._cachedCount_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.cachedCount(modifier._cachedCount_1_0value, modifier._cachedCount_1_1value);
                    break;
                }
                default: {
                    this.cachedCount((undefined as int32 | undefined), (undefined as boolean | undefined));
                }
            }
        }
        if (modifier._displayCount_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._displayCount_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.displayCount(modifier._displayCount_0_0value, modifier._displayCount_0_1value);
                    break;
                }
                default: {
                    this.displayCount((undefined as int32 | string | SwiperAutoFill | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
        if (modifier._prevMargin_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._prevMargin_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.prevMargin(modifier._prevMargin_0_0value, modifier._prevMargin_0_1value);
                    break;
                }
                default: {
                    this.prevMargin((undefined as Length | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
        if (modifier._nextMargin_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._nextMargin_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
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
        if (((this._index_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._index_0_flag = AttributeUpdaterFlag.UPDATE
            this._index_0_0value = value
        } else
        {
            this._index_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    autoPlay(value: boolean | undefined): this {
        if (((this._autoPlay_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._autoPlay_0_0value) !== (value)))
        {
            this._autoPlay_0_flag = AttributeUpdaterFlag.UPDATE
            this._autoPlay_0_0value = value
        } else
        {
            this._autoPlay_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    interval(value: int32 | undefined): this {
        if (((this._interval_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._interval_0_0value) !== (value)))
        {
            this._interval_0_flag = AttributeUpdaterFlag.UPDATE
            this._interval_0_0value = value
        } else
        {
            this._interval_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    indicator(value: IndicatorComponentController | DotIndicator | DigitIndicator | boolean | undefined): this {
        if (((this._indicator_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._indicator_0_flag = AttributeUpdaterFlag.UPDATE
            this._indicator_0_0value = value
        } else
        {
            this._indicator_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    loop(value: boolean | undefined): this {
        if (((this._loop_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._loop_0_0value) !== (value)))
        {
            this._loop_0_flag = AttributeUpdaterFlag.UPDATE
            this._loop_0_0value = value
        } else
        {
            this._loop_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    duration(value: int32 | undefined): this {
        if (((this._duration_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._duration_0_0value) !== (value)))
        {
            this._duration_0_flag = AttributeUpdaterFlag.UPDATE
            this._duration_0_0value = value
        } else
        {
            this._duration_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    vertical(value: boolean | undefined): this {
        if (((this._vertical_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._vertical_0_0value) !== (value)))
        {
            this._vertical_0_flag = AttributeUpdaterFlag.UPDATE
            this._vertical_0_0value = value
        } else
        {
            this._vertical_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    itemSpace(value: double | string | undefined): this {
        if (((this._itemSpace_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._itemSpace_0_0value) !== (value)))
        {
            this._itemSpace_0_flag = AttributeUpdaterFlag.UPDATE
            this._itemSpace_0_0value = value
        } else
        {
            this._itemSpace_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    displayMode(value: SwiperDisplayMode | undefined): this {
        if (((this._displayMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._displayMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._displayMode_0_0value = value
        } else
        {
            this._displayMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    cachedCount(value: int32 | undefined): this {
        if (((this._cachedCount_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._cachedCount_0_0value) !== (value)))
        {
            this._cachedCount_0_flag = AttributeUpdaterFlag.UPDATE
            this._cachedCount_0_0value = value
        } else
        {
            this._cachedCount_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    effectMode(value: EdgeEffect | undefined): this {
        if (((this._effectMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._effectMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._effectMode_0_0value = value
        } else
        {
            this._effectMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    disableSwipe(value: boolean | undefined): this {
        if (((this._disableSwipe_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._disableSwipe_0_0value) !== (value)))
        {
            this._disableSwipe_0_flag = AttributeUpdaterFlag.UPDATE
            this._disableSwipe_0_0value = value
        } else
        {
            this._disableSwipe_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    curve(value: curves.Curve | string | curves.ICurve | undefined): this {
        if (((this._curve_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._curve_0_flag = AttributeUpdaterFlag.UPDATE
            this._curve_0_0value = value
        } else
        {
            this._curve_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onChange(value: ((value0: int32) => void) | undefined): this {
        if (((this._onChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onChange_0_0value = value
        } else
        {
            this._onChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onSelected(value: ((value0: int32) => void) | undefined): this {
        if (((this._onSelected_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onSelected_0_flag = AttributeUpdaterFlag.UPDATE
            this._onSelected_0_0value = value
        } else
        {
            this._onSelected_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onUnselected(value: ((value0: int32) => void) | undefined): this {
        if (((this._onUnselected_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onUnselected_0_flag = AttributeUpdaterFlag.UPDATE
            this._onUnselected_0_0value = value
        } else
        {
            this._onUnselected_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onAnimationStart(value: OnSwiperAnimationStartCallback | undefined): this {
        if (((this._onAnimationStart_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onAnimationStart_0_flag = AttributeUpdaterFlag.UPDATE
            this._onAnimationStart_0_0value = value
        } else
        {
            this._onAnimationStart_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onAnimationEnd(value: OnSwiperAnimationEndCallback | undefined): this {
        if (((this._onAnimationEnd_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onAnimationEnd_0_flag = AttributeUpdaterFlag.UPDATE
            this._onAnimationEnd_0_0value = value
        } else
        {
            this._onAnimationEnd_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onGestureSwipe(value: OnSwiperGestureSwipeCallback | undefined): this {
        if (((this._onGestureSwipe_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onGestureSwipe_0_flag = AttributeUpdaterFlag.UPDATE
            this._onGestureSwipe_0_0value = value
        } else
        {
            this._onGestureSwipe_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    nestedScroll(value: SwiperNestedScrollMode | undefined): this {
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
    customContentTransition(value: SwiperContentAnimatedTransition | undefined): this {
        if (((this._customContentTransition_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._customContentTransition_0_flag = AttributeUpdaterFlag.UPDATE
            this._customContentTransition_0_0value = value
        } else
        {
            this._customContentTransition_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onContentDidScroll(value: ContentDidScrollCallback | undefined): this {
        if (((this._onContentDidScroll_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onContentDidScroll_0_flag = AttributeUpdaterFlag.UPDATE
            this._onContentDidScroll_0_0value = value
        } else
        {
            this._onContentDidScroll_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    indicatorInteractive(value: boolean | undefined): this {
        if (((this._indicatorInteractive_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._indicatorInteractive_0_0value) !== (value)))
        {
            this._indicatorInteractive_0_flag = AttributeUpdaterFlag.UPDATE
            this._indicatorInteractive_0_0value = value
        } else
        {
            this._indicatorInteractive_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    pageFlipMode(value: PageFlipMode | undefined): this {
        if (((this._pageFlipMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._pageFlipMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._pageFlipMode_0_0value = value
        } else
        {
            this._pageFlipMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onContentWillScroll(value: ContentWillScrollCallback | undefined): this {
        if (((this._onContentWillScroll_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onContentWillScroll_0_flag = AttributeUpdaterFlag.UPDATE
            this._onContentWillScroll_0_0value = value
        } else
        {
            this._onContentWillScroll_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    autoPlay(autoPlay: boolean | undefined, options: AutoPlayOptions | undefined): this {
        if (((this._autoPlay_1_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._autoPlay_1_0value) !== (autoPlay)) || (true))
        {
            this._autoPlay_1_flag = AttributeUpdaterFlag.UPDATE
            this._autoPlay_1_0value = autoPlay
            this._autoPlay_1_1value = options
        } else
        {
            this._autoPlay_1_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    displayArrow(value: ArrowStyle | boolean | undefined, isHoverShow?: boolean): this {
        if (((this._displayArrow_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || ((this._displayArrow_0_1value) !== (isHoverShow)))
        {
            this._displayArrow_0_flag = AttributeUpdaterFlag.UPDATE
            this._displayArrow_0_0value = value
            this._displayArrow_0_1value = isHoverShow
        } else
        {
            this._displayArrow_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    cachedCount(count: int32 | undefined, isShown: boolean | undefined): this {
        if (((this._cachedCount_1_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._cachedCount_1_0value) !== (count)) || ((this._cachedCount_1_1value) !== (isShown)))
        {
            this._cachedCount_1_flag = AttributeUpdaterFlag.UPDATE
            this._cachedCount_1_0value = count
            this._cachedCount_1_1value = isShown
        } else
        {
            this._cachedCount_1_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    displayCount(value: int32 | string | SwiperAutoFill | undefined, swipeByGroup?: boolean): this {
        if (((this._displayCount_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || ((this._displayCount_0_1value) !== (swipeByGroup)))
        {
            this._displayCount_0_flag = AttributeUpdaterFlag.UPDATE
            this._displayCount_0_0value = value
            this._displayCount_0_1value = swipeByGroup
        } else
        {
            this._displayCount_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    prevMargin(value: Length | undefined, ignoreBlank?: boolean): this {
        if (((this._prevMargin_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || ((this._prevMargin_0_1value) !== (ignoreBlank)))
        {
            this._prevMargin_0_flag = AttributeUpdaterFlag.UPDATE
            this._prevMargin_0_0value = value
            this._prevMargin_0_1value = ignoreBlank
        } else
        {
            this._prevMargin_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    nextMargin(value: Length | undefined, ignoreBlank?: boolean): this {
        if (((this._nextMargin_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || ((this._nextMargin_0_1value) !== (ignoreBlank)))
        {
            this._nextMargin_0_flag = AttributeUpdaterFlag.UPDATE
            this._nextMargin_0_0value = value
            this._nextMargin_0_1value = ignoreBlank
        } else
        {
            this._nextMargin_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<SwiperAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

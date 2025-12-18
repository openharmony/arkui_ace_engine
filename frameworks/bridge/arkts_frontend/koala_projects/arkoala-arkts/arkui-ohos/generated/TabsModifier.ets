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
import { AttributeModifier } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkTabsPeer, BarPosition, AnimationMode, OnTabsAnimationStartCallback, TabsAnimationEvent, OnTabsAnimationEndCallback, OnTabsGestureSwipeCallback, BarGridColumnOptions, TabsCustomContentTransitionCallback, OnTabsContentWillChangeCallback, TabsAttribute, BarMode, ScrollableBarModeOptions, TabsCacheMode } from './component/tabs'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod, Callback as arkui_component_common_Callback, DividerStyle, BlurStyle, BackgroundEffectOptions, BackgroundBlurStyleOptions } from './component/common'
import { Length, Resource as arkui_component_units_Resource, ResourceColor } from './component/units'
import { Resource as global_resource_Resource } from 'global.resource'
import { EdgeEffect, Color as arkui_component_enums_Color, PageFlipMode } from './component/enums'
export class TabsModifier extends CommonMethodModifier implements TabsAttribute,AttributeModifier<TabsAttribute> {
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
    applyNormalAttribute(instance: TabsAttribute): void { }
    applyPressedAttribute(instance: TabsAttribute): void { }
    applyFocusedAttribute(instance: TabsAttribute): void { }
    applyDisabledAttribute(instance: TabsAttribute): void { }
    applySelectedAttribute(instance: TabsAttribute): void { }
    public _vertical_0_0value?: boolean | undefined
    public _barPosition_0_0value?: BarPosition | undefined
    public _scrollable_0_0value?: boolean | undefined
    public _barWidth_0_0value?: Length | undefined
    public _barHeight_0_0value?: Length | undefined
    public _animationDuration_0_0value?: int32 | undefined
    public _animationMode_0_0value?: AnimationMode | undefined
    public _edgeEffect_0_0value?: EdgeEffect | undefined
    public _onChange_0_0value?: arkui_component_common_Callback<int32, void> | undefined
    public _onSelected_0_0value?: arkui_component_common_Callback<int32, void> | undefined
    public _onTabBarClick_0_0value?: arkui_component_common_Callback<int32, void> | undefined
    public _onUnselected_0_0value?: arkui_component_common_Callback<int32, void> | undefined
    public _onAnimationStart_0_0value?: OnTabsAnimationStartCallback | undefined
    public _onAnimationEnd_0_0value?: OnTabsAnimationEndCallback | undefined
    public _onGestureSwipe_0_0value?: OnTabsGestureSwipeCallback | undefined
    public _fadingEdge_0_0value?: boolean | undefined
    public _divider_0_0value?: DividerStyle | null | undefined
    public _barOverlap_0_0value?: boolean | undefined
    public _barBackgroundColor_0_0value?: ResourceColor | undefined
    public _barGridAlign_0_0value?: BarGridColumnOptions | undefined
    public _customContentTransition_0_0value?: TabsCustomContentTransitionCallback | undefined
    public _barBackgroundBlurStyle_0_0value?: BlurStyle | undefined
    public _pageFlipMode_0_0value?: PageFlipMode | undefined
    public _barBackgroundEffect_0_0value?: BackgroundEffectOptions | undefined
    public _onContentWillChange_0_0value?: OnTabsContentWillChangeCallback | undefined
    public _barMode_0_0value?: BarMode | undefined
    public _barMode_0_1value?: ScrollableBarModeOptions | undefined
    public _barBackgroundBlurStyle_1_0value?: BlurStyle | undefined
    public _barBackgroundBlurStyle_1_1value?: BackgroundBlurStyleOptions | undefined
    public _cachedMaxCount_0_0value?: int32 | undefined
    public _cachedMaxCount_0_1value?: TabsCacheMode | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkTabsPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
        this.applyModifierPatch1(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkTabsPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setVerticalAttribute((this._vertical_0_0value as boolean | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setVerticalAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setBarPositionAttribute((this._barPosition_0_0value as BarPosition | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setBarPositionAttribute((undefined as BarPosition | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setScrollableAttribute((this._scrollable_0_0value as boolean | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setScrollableAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setBarWidthAttribute((this._barWidth_0_0value as Length | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setBarWidthAttribute((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setBarHeightAttribute((this._barHeight_0_0value as Length | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setBarHeightAttribute((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setAnimationDurationAttribute((this._animationDuration_0_0value as int32 | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setAnimationDurationAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1: {
                    peer.setAnimationModeAttribute((this._animationMode_0_0value as AnimationMode | undefined));
                    flagArray[6] = 2;
                    break;
                }
                case 3: {
                    flagArray[6] = 2;
                    break;
                }
                default: {
                    flagArray[6] = 0;
                    peer.setAnimationModeAttribute((undefined as AnimationMode | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1: {
                    peer.setEdgeEffectAttribute((this._edgeEffect_0_0value as EdgeEffect | undefined));
                    flagArray[7] = 2;
                    break;
                }
                case 3: {
                    flagArray[7] = 2;
                    break;
                }
                default: {
                    flagArray[7] = 0;
                    peer.setEdgeEffectAttribute((undefined as EdgeEffect | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as arkui_component_common_Callback<int32, void> | undefined));
                    flagArray[8] = 2;
                    break;
                }
                case 3: {
                    flagArray[8] = 2;
                    break;
                }
                default: {
                    flagArray[8] = 0;
                    peer.setOnChangeAttribute((undefined as arkui_component_common_Callback<int32, void> | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1: {
                    peer.setOnSelectedAttribute((this._onSelected_0_0value as arkui_component_common_Callback<int32, void> | undefined));
                    flagArray[9] = 2;
                    break;
                }
                case 3: {
                    flagArray[9] = 2;
                    break;
                }
                default: {
                    flagArray[9] = 0;
                    peer.setOnSelectedAttribute((undefined as arkui_component_common_Callback<int32, void> | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1: {
                    peer.setOnTabBarClickAttribute((this._onTabBarClick_0_0value as arkui_component_common_Callback<int32, void> | undefined));
                    flagArray[10] = 2;
                    break;
                }
                case 3: {
                    flagArray[10] = 2;
                    break;
                }
                default: {
                    flagArray[10] = 0;
                    peer.setOnTabBarClickAttribute((undefined as arkui_component_common_Callback<int32, void> | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1: {
                    peer.setOnUnselectedAttribute((this._onUnselected_0_0value as arkui_component_common_Callback<int32, void> | undefined));
                    flagArray[11] = 2;
                    break;
                }
                case 3: {
                    flagArray[11] = 2;
                    break;
                }
                default: {
                    flagArray[11] = 0;
                    peer.setOnUnselectedAttribute((undefined as arkui_component_common_Callback<int32, void> | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1: {
                    peer.setOnAnimationStartAttribute((this._onAnimationStart_0_0value as OnTabsAnimationStartCallback | undefined));
                    flagArray[12] = 2;
                    break;
                }
                case 3: {
                    flagArray[12] = 2;
                    break;
                }
                default: {
                    flagArray[12] = 0;
                    peer.setOnAnimationStartAttribute((undefined as OnTabsAnimationStartCallback | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1: {
                    peer.setOnAnimationEndAttribute((this._onAnimationEnd_0_0value as OnTabsAnimationEndCallback | undefined));
                    flagArray[13] = 2;
                    break;
                }
                case 3: {
                    flagArray[13] = 2;
                    break;
                }
                default: {
                    flagArray[13] = 0;
                    peer.setOnAnimationEndAttribute((undefined as OnTabsAnimationEndCallback | undefined));
                }
            }
        }
        if (flagArray[14] != 0) {
            switch (flagArray[14]) {
                case 1: {
                    peer.setOnGestureSwipeAttribute((this._onGestureSwipe_0_0value as OnTabsGestureSwipeCallback | undefined));
                    flagArray[14] = 2;
                    break;
                }
                case 3: {
                    flagArray[14] = 2;
                    break;
                }
                default: {
                    flagArray[14] = 0;
                    peer.setOnGestureSwipeAttribute((undefined as OnTabsGestureSwipeCallback | undefined));
                }
            }
        }
        if (flagArray[15] != 0) {
            switch (flagArray[15]) {
                case 1: {
                    peer.setFadingEdgeAttribute((this._fadingEdge_0_0value as boolean | undefined));
                    flagArray[15] = 2;
                    break;
                }
                case 3: {
                    flagArray[15] = 2;
                    break;
                }
                default: {
                    flagArray[15] = 0;
                    peer.setFadingEdgeAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[16] != 0) {
            switch (flagArray[16]) {
                case 1: {
                    peer.setDividerAttribute((this._divider_0_0value as DividerStyle | null | undefined));
                    flagArray[16] = 2;
                    break;
                }
                case 3: {
                    flagArray[16] = 2;
                    break;
                }
                default: {
                    flagArray[16] = 0;
                    peer.setDividerAttribute((undefined as DividerStyle | null | undefined));
                }
            }
        }
        if (flagArray[17] != 0) {
            switch (flagArray[17]) {
                case 1: {
                    peer.setBarOverlapAttribute((this._barOverlap_0_0value as boolean | undefined));
                    flagArray[17] = 2;
                    break;
                }
                case 3: {
                    flagArray[17] = 2;
                    break;
                }
                default: {
                    flagArray[17] = 0;
                    peer.setBarOverlapAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[18] != 0) {
            switch (flagArray[18]) {
                case 1: {
                    peer.setBarBackgroundColorAttribute((this._barBackgroundColor_0_0value as ResourceColor | undefined));
                    flagArray[18] = 2;
                    break;
                }
                case 3: {
                    flagArray[18] = 2;
                    break;
                }
                default: {
                    flagArray[18] = 0;
                    peer.setBarBackgroundColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[19] != 0) {
            switch (flagArray[19]) {
                case 1: {
                    peer.setBarGridAlignAttribute((this._barGridAlign_0_0value as BarGridColumnOptions | undefined));
                    flagArray[19] = 2;
                    break;
                }
                case 3: {
                    flagArray[19] = 2;
                    break;
                }
                default: {
                    flagArray[19] = 0;
                    peer.setBarGridAlignAttribute((undefined as BarGridColumnOptions | undefined));
                }
            }
        }
    }
    applyModifierPatch1(peer: ArkTabsPeer, flagArray: Uint8Array): void {
        if (flagArray[20] != 0) {
            switch (flagArray[20]) {
                case 1: {
                    peer.setCustomContentTransitionAttribute((this._customContentTransition_0_0value as TabsCustomContentTransitionCallback | undefined));
                    flagArray[20] = 2;
                    break;
                }
                case 3: {
                    flagArray[20] = 2;
                    break;
                }
                default: {
                    flagArray[20] = 0;
                    peer.setCustomContentTransitionAttribute((undefined as TabsCustomContentTransitionCallback | undefined));
                }
            }
        }
        if (flagArray[21] != 0) {
            switch (flagArray[21]) {
                case 1: {
                    peer.setBarBackgroundBlurStyle0Attribute((this._barBackgroundBlurStyle_0_0value as BlurStyle | undefined));
                    flagArray[21] = 2;
                    break;
                }
                case 3: {
                    flagArray[21] = 2;
                    break;
                }
                default: {
                    flagArray[21] = 0;
                    peer.setBarBackgroundBlurStyle0Attribute((undefined as BlurStyle | undefined));
                }
            }
        }
        if (flagArray[22] != 0) {
            switch (flagArray[22]) {
                case 1: {
                    peer.setPageFlipModeAttribute((this._pageFlipMode_0_0value as PageFlipMode | undefined));
                    flagArray[22] = 2;
                    break;
                }
                case 3: {
                    flagArray[22] = 2;
                    break;
                }
                default: {
                    flagArray[22] = 0;
                    peer.setPageFlipModeAttribute((undefined as PageFlipMode | undefined));
                }
            }
        }
        if (flagArray[23] != 0) {
            switch (flagArray[23]) {
                case 1: {
                    peer.setBarBackgroundEffectAttribute((this._barBackgroundEffect_0_0value as BackgroundEffectOptions | undefined));
                    flagArray[23] = 2;
                    break;
                }
                case 3: {
                    flagArray[23] = 2;
                    break;
                }
                default: {
                    flagArray[23] = 0;
                    peer.setBarBackgroundEffectAttribute((undefined as BackgroundEffectOptions | undefined));
                }
            }
        }
        if (flagArray[24] != 0) {
            switch (flagArray[24]) {
                case 1: {
                    peer.setOnContentWillChangeAttribute((this._onContentWillChange_0_0value as OnTabsContentWillChangeCallback | undefined));
                    flagArray[24] = 2;
                    break;
                }
                case 3: {
                    flagArray[24] = 2;
                    break;
                }
                default: {
                    flagArray[24] = 0;
                    peer.setOnContentWillChangeAttribute((undefined as OnTabsContentWillChangeCallback | undefined));
                }
            }
        }
        if (flagArray[25] != 0) {
            switch (flagArray[25]) {
                case 1: {
                    peer.setBarModeAttribute((this._barMode_0_0value as BarMode | undefined), (this._barMode_0_1value as ScrollableBarModeOptions | undefined | undefined));
                    flagArray[25] = 2;
                    break;
                }
                case 3: {
                    flagArray[25] = 2;
                    break;
                }
                default: {
                    flagArray[25] = 0;
                    peer.setBarModeAttribute((undefined as BarMode | undefined), (undefined as ScrollableBarModeOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[26] != 0) {
            switch (flagArray[26]) {
                case 1: {
                    peer.setBarBackgroundBlurStyle1Attribute((this._barBackgroundBlurStyle_1_0value as BlurStyle | undefined), (this._barBackgroundBlurStyle_1_1value as BackgroundBlurStyleOptions | undefined));
                    flagArray[26] = 2;
                    break;
                }
                case 3: {
                    flagArray[26] = 2;
                    break;
                }
                default: {
                    flagArray[26] = 0;
                    peer.setBarBackgroundBlurStyle1Attribute((undefined as BlurStyle | undefined), (undefined as BackgroundBlurStyleOptions | undefined));
                }
            }
        }
        if (flagArray[27] != 0) {
            switch (flagArray[27]) {
                case 1: {
                    peer.setCachedMaxCountAttribute((this._cachedMaxCount_0_0value as int32 | undefined), (this._cachedMaxCount_0_1value as TabsCacheMode | undefined));
                    flagArray[27] = 2;
                    break;
                }
                case 3: {
                    flagArray[27] = 2;
                    break;
                }
                default: {
                    flagArray[27] = 0;
                    peer.setCachedMaxCountAttribute((undefined as int32 | undefined), (undefined as TabsCacheMode | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: TabsModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
        this.mergeModifier1(modifier, flagArray);
    }
    mergeModifier0(modifier: TabsModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
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
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.barPosition(modifier._barPosition_0_0value);
                    break;
                }
                default: {
                    this.barPosition((undefined as BarPosition | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.scrollable(modifier._scrollable_0_0value);
                    break;
                }
                default: {
                    this.scrollable((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.barWidth(modifier._barWidth_0_0value);
                    break;
                }
                default: {
                    this.barWidth((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.barHeight(modifier._barHeight_0_0value);
                    break;
                }
                default: {
                    this.barHeight((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1:
                case 3: {
                    this.animationDuration(modifier._animationDuration_0_0value);
                    break;
                }
                default: {
                    this.animationDuration((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1:
                case 3: {
                    this.animationMode(modifier._animationMode_0_0value);
                    break;
                }
                default: {
                    this.animationMode((undefined as AnimationMode | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1:
                case 3: {
                    this.edgeEffect(modifier._edgeEffect_0_0value);
                    break;
                }
                default: {
                    this.edgeEffect((undefined as EdgeEffect | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
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
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
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
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1:
                case 3: {
                    this.onTabBarClick(modifier._onTabBarClick_0_0value);
                    break;
                }
                default: {
                    this.onTabBarClick((undefined as arkui_component_common_Callback<int32, void> | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
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
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1:
                case 3: {
                    this.onAnimationStart(modifier._onAnimationStart_0_0value);
                    break;
                }
                default: {
                    this.onAnimationStart((undefined as OnTabsAnimationStartCallback | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1:
                case 3: {
                    this.onAnimationEnd(modifier._onAnimationEnd_0_0value);
                    break;
                }
                default: {
                    this.onAnimationEnd((undefined as OnTabsAnimationEndCallback | undefined));
                }
            }
        }
        if (flagArray[14] != 0) {
            switch (flagArray[14]) {
                case 1:
                case 3: {
                    this.onGestureSwipe(modifier._onGestureSwipe_0_0value);
                    break;
                }
                default: {
                    this.onGestureSwipe((undefined as OnTabsGestureSwipeCallback | undefined));
                }
            }
        }
        if (flagArray[15] != 0) {
            switch (flagArray[15]) {
                case 1:
                case 3: {
                    this.fadingEdge(modifier._fadingEdge_0_0value);
                    break;
                }
                default: {
                    this.fadingEdge((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[16] != 0) {
            switch (flagArray[16]) {
                case 1:
                case 3: {
                    this.divider(modifier._divider_0_0value);
                    break;
                }
                default: {
                    this.divider((undefined as DividerStyle | null | undefined));
                }
            }
        }
        if (flagArray[17] != 0) {
            switch (flagArray[17]) {
                case 1:
                case 3: {
                    this.barOverlap(modifier._barOverlap_0_0value);
                    break;
                }
                default: {
                    this.barOverlap((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[18] != 0) {
            switch (flagArray[18]) {
                case 1:
                case 3: {
                    this.barBackgroundColor(modifier._barBackgroundColor_0_0value);
                    break;
                }
                default: {
                    this.barBackgroundColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[19] != 0) {
            switch (flagArray[19]) {
                case 1:
                case 3: {
                    this.barGridAlign(modifier._barGridAlign_0_0value);
                    break;
                }
                default: {
                    this.barGridAlign((undefined as BarGridColumnOptions | undefined));
                }
            }
        }
    }
    mergeModifier1(modifier: TabsModifier, flagArray: Uint8Array): void {
        if (flagArray[20] != 0) {
            switch (flagArray[20]) {
                case 1:
                case 3: {
                    this.customContentTransition(modifier._customContentTransition_0_0value);
                    break;
                }
                default: {
                    this.customContentTransition((undefined as TabsCustomContentTransitionCallback | undefined));
                }
            }
        }
        if (flagArray[21] != 0) {
            switch (flagArray[21]) {
                case 1:
                case 3: {
                    this.barBackgroundBlurStyle(modifier._barBackgroundBlurStyle_0_0value);
                    break;
                }
                default: {
                    this.barBackgroundBlurStyle((undefined as BlurStyle | undefined));
                }
            }
        }
        if (flagArray[22] != 0) {
            switch (flagArray[22]) {
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
        if (flagArray[23] != 0) {
            switch (flagArray[23]) {
                case 1:
                case 3: {
                    this.barBackgroundEffect(modifier._barBackgroundEffect_0_0value);
                    break;
                }
                default: {
                    this.barBackgroundEffect((undefined as BackgroundEffectOptions | undefined));
                }
            }
        }
        if (flagArray[24] != 0) {
            switch (flagArray[24]) {
                case 1:
                case 3: {
                    this.onContentWillChange(modifier._onContentWillChange_0_0value);
                    break;
                }
                default: {
                    this.onContentWillChange((undefined as OnTabsContentWillChangeCallback | undefined));
                }
            }
        }
        if (flagArray[25] != 0) {
            switch (flagArray[25]) {
                case 1:
                case 3: {
                    this.barMode(modifier._barMode_0_0value, modifier._barMode_0_1value);
                    break;
                }
                default: {
                    this.barMode((undefined as BarMode | undefined), (undefined as ScrollableBarModeOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[26] != 0) {
            switch (flagArray[26]) {
                case 1:
                case 3: {
                    this.barBackgroundBlurStyle(modifier._barBackgroundBlurStyle_1_0value, modifier._barBackgroundBlurStyle_1_1value);
                    break;
                }
                default: {
                    this.barBackgroundBlurStyle((undefined as BlurStyle | undefined), (undefined as BackgroundBlurStyleOptions | undefined));
                }
            }
        }
        if (flagArray[27] != 0) {
            switch (flagArray[27]) {
                case 1:
                case 3: {
                    this.cachedMaxCount(modifier._cachedMaxCount_0_0value, modifier._cachedMaxCount_0_1value);
                    break;
                }
                default: {
                    this.cachedMaxCount((undefined as int32 | undefined), (undefined as TabsCacheMode | undefined));
                }
            }
        }
    }
    vertical(value: boolean | undefined): this {
        if (((this._flagArray[0]) == (0)) || ((this._vertical_0_0value) !== (value))) {
            this._flagArray[0] = 1
            this._vertical_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    barPosition(value: BarPosition | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._barPosition_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    scrollable(value: boolean | undefined): this {
        if (((this._flagArray[2]) == (0)) || ((this._scrollable_0_0value) !== (value))) {
            this._flagArray[2] = 1
            this._scrollable_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    barWidth(value: Length | undefined): this {
        if (((this._flagArray[3]) == (0)) || (true)) {
            this._flagArray[3] = 1
            this._barWidth_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    barHeight(value: Length | undefined): this {
        if (((this._flagArray[4]) == (0)) || (true)) {
            this._flagArray[4] = 1
            this._barHeight_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    animationDuration(value: int32 | undefined): this {
        if (((this._flagArray[5]) == (0)) || ((this._animationDuration_0_0value) !== (value))) {
            this._flagArray[5] = 1
            this._animationDuration_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    animationMode(value: AnimationMode | undefined): this {
        if (((this._flagArray[6]) == (0)) || (true)) {
            this._flagArray[6] = 1
            this._animationMode_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[6] = 3
        }
        return this
    }
    edgeEffect(value: EdgeEffect | undefined): this {
        if (((this._flagArray[7]) == (0)) || (true)) {
            this._flagArray[7] = 1
            this._edgeEffect_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[7] = 3
        }
        return this
    }
    onChange(value: arkui_component_common_Callback<int32, void> | undefined): this {
        if (((this._flagArray[8]) == (0)) || (true)) {
            this._flagArray[8] = 1
            this._onChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[8] = 3
        }
        return this
    }
    onSelected(value: arkui_component_common_Callback<int32, void> | undefined): this {
        if (((this._flagArray[9]) == (0)) || (true)) {
            this._flagArray[9] = 1
            this._onSelected_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[9] = 3
        }
        return this
    }
    onTabBarClick(value: arkui_component_common_Callback<int32, void> | undefined): this {
        if (((this._flagArray[10]) == (0)) || (true)) {
            this._flagArray[10] = 1
            this._onTabBarClick_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[10] = 3
        }
        return this
    }
    onUnselected(value: arkui_component_common_Callback<int32, void> | undefined): this {
        if (((this._flagArray[11]) == (0)) || (true)) {
            this._flagArray[11] = 1
            this._onUnselected_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[11] = 3
        }
        return this
    }
    onAnimationStart(value: OnTabsAnimationStartCallback | undefined): this {
        if (((this._flagArray[12]) == (0)) || (true)) {
            this._flagArray[12] = 1
            this._onAnimationStart_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[12] = 3
        }
        return this
    }
    onAnimationEnd(value: OnTabsAnimationEndCallback | undefined): this {
        if (((this._flagArray[13]) == (0)) || (true)) {
            this._flagArray[13] = 1
            this._onAnimationEnd_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[13] = 3
        }
        return this
    }
    onGestureSwipe(value: OnTabsGestureSwipeCallback | undefined): this {
        if (((this._flagArray[14]) == (0)) || (true)) {
            this._flagArray[14] = 1
            this._onGestureSwipe_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[14] = 3
        }
        return this
    }
    fadingEdge(value: boolean | undefined): this {
        if (((this._flagArray[15]) == (0)) || ((this._fadingEdge_0_0value) !== (value))) {
            this._flagArray[15] = 1
            this._fadingEdge_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[15] = 3
        }
        return this
    }
    divider(value: DividerStyle | null | undefined): this {
        if (((this._flagArray[16]) == (0)) || (true)) {
            this._flagArray[16] = 1
            this._divider_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[16] = 3
        }
        return this
    }
    barOverlap(value: boolean | undefined): this {
        if (((this._flagArray[17]) == (0)) || ((this._barOverlap_0_0value) !== (value))) {
            this._flagArray[17] = 1
            this._barOverlap_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[17] = 3
        }
        return this
    }
    barBackgroundColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[18]) == (0)) || (true)) {
            this._flagArray[18] = 1
            this._barBackgroundColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[18] = 3
        }
        return this
    }
    barGridAlign(value: BarGridColumnOptions | undefined): this {
        if (((this._flagArray[19]) == (0)) || (true)) {
            this._flagArray[19] = 1
            this._barGridAlign_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[19] = 3
        }
        return this
    }
    customContentTransition(value: TabsCustomContentTransitionCallback | undefined): this {
        if (((this._flagArray[20]) == (0)) || (true)) {
            this._flagArray[20] = 1
            this._customContentTransition_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[20] = 3
        }
        return this
    }
    barBackgroundBlurStyle(value: BlurStyle | undefined): this {
        if (((this._flagArray[21]) == (0)) || (true)) {
            this._flagArray[21] = 1
            this._barBackgroundBlurStyle_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[21] = 3
        }
        return this
    }
    pageFlipMode(value: PageFlipMode | undefined): this {
        if (((this._flagArray[22]) == (0)) || (true)) {
            this._flagArray[22] = 1
            this._pageFlipMode_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[22] = 3
        }
        return this
    }
    barBackgroundEffect(value: BackgroundEffectOptions | undefined): this {
        if (((this._flagArray[23]) == (0)) || (true)) {
            this._flagArray[23] = 1
            this._barBackgroundEffect_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[23] = 3
        }
        return this
    }
    onContentWillChange(value: OnTabsContentWillChangeCallback | undefined): this {
        if (((this._flagArray[24]) == (0)) || (true)) {
            this._flagArray[24] = 1
            this._onContentWillChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[24] = 3
        }
        return this
    }
    barMode(value: BarMode | undefined, options?: ScrollableBarModeOptions): this {
        if (((this._flagArray[25]) == (0)) || (true) || (true)) {
            this._flagArray[25] = 1
            this._barMode_0_0value = value
            this._barMode_0_1value = options
            this._state.fireChange()
        } else {
            this._flagArray[25] = 3
        }
        return this
    }
    barBackgroundBlurStyle(style: BlurStyle | undefined, options: BackgroundBlurStyleOptions | undefined): this {
        if (((this._flagArray[26]) == (0)) || (true) || (true)) {
            this._flagArray[26] = 1
            this._barBackgroundBlurStyle_1_0value = style
            this._barBackgroundBlurStyle_1_1value = options
            this._state.fireChange()
        } else {
            this._flagArray[26] = 3
        }
        return this
    }
    cachedMaxCount(count: int32 | undefined, mode: TabsCacheMode | undefined): this {
        if (((this._flagArray[27]) == (0)) || ((this._cachedMaxCount_0_0value) !== (count)) || (true)) {
            this._flagArray[27] = 1
            this._cachedMaxCount_0_0value = count
            this._cachedMaxCount_0_1value = mode
            this._state.fireChange()
        } else {
            this._flagArray[27] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<TabsAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

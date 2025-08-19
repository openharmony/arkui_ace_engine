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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { AttributeUpdaterFlag, CommonMethodModifier } from './CommonMethodModifier'
import { ArkTabsPeer, BarPosition, AnimationMode, OnTabsAnimationStartCallback, TabsAnimationEvent, OnTabsAnimationEndCallback, OnTabsGestureSwipeCallback, BarGridColumnOptions, TabsCustomContentTransitionCallback, OnTabsContentWillChangeCallback, TabsAttribute, BarMode, ScrollableBarModeOptions, TabsCacheMode } from "./component/tabs"
import { AttributeModifier, CommonMethod, DividerStyle, BlurStyle, BackgroundEffectOptions, BackgroundBlurStyleOptions } from "./component/common"
import { Length, ResourceColor } from "./component/units"
import { Resource } from "global.resource"
import { EdgeEffect, Color, PageFlipMode } from "./component/enums"
import { PeerNode } from './PeerNode'

export class TabsModifier extends CommonMethodModifier implements TabsAttribute,AttributeModifier<TabsAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: TabsAttribute): void { }
    applyPressedAttribute(instance: TabsAttribute): void { }
    applyFocusedAttribute(instance: TabsAttribute): void { }
    applyDisabledAttribute(instance: TabsAttribute): void { }
    applySelectedAttribute(instance: TabsAttribute): void { }
    _vertical_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _vertical_0_0value?: boolean | undefined
    _barPosition_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _barPosition_0_0value?: BarPosition | undefined
    _scrollable_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _scrollable_0_0value?: boolean | undefined
    _barWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _barWidth_0_0value?: Length | undefined
    _barHeight_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _barHeight_0_0value?: Length | undefined
    _animationDuration_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _animationDuration_0_0value?: number | undefined
    _animationMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _animationMode_0_0value?: AnimationMode | undefined
    _edgeEffect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _edgeEffect_0_0value?: EdgeEffect | undefined
    _onChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onChange_0_0value?: ((value0: number) => void) | undefined
    _onSelected_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onSelected_0_0value?: ((value0: number) => void) | undefined
    _onTabBarClick_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onTabBarClick_0_0value?: ((value0: number) => void) | undefined
    _onUnselected_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onUnselected_0_0value?: ((value0: number) => void) | undefined
    _onAnimationStart_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onAnimationStart_0_0value?: OnTabsAnimationStartCallback | undefined
    _onAnimationEnd_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onAnimationEnd_0_0value?: OnTabsAnimationEndCallback | undefined
    _onGestureSwipe_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onGestureSwipe_0_0value?: OnTabsGestureSwipeCallback | undefined
    _fadingEdge_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fadingEdge_0_0value?: boolean | undefined
    _divider_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _divider_0_0value?: DividerStyle | null | undefined
    _barOverlap_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _barOverlap_0_0value?: boolean | undefined
    _barBackgroundColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _barBackgroundColor_0_0value?: ResourceColor | undefined
    _barGridAlign_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _barGridAlign_0_0value?: BarGridColumnOptions | undefined
    _customContentTransition_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _customContentTransition_0_0value?: TabsCustomContentTransitionCallback | undefined
    _barBackgroundBlurStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _barBackgroundBlurStyle_0_0value?: BlurStyle | undefined
    _pageFlipMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _pageFlipMode_0_0value?: PageFlipMode | undefined
    _barBackgroundEffect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _barBackgroundEffect_0_0value?: BackgroundEffectOptions | undefined
    _onContentWillChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onContentWillChange_0_0value?: OnTabsContentWillChangeCallback | undefined
    _barMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _barMode_0_0value?: BarMode | undefined
    _barMode_0_1value?: ScrollableBarModeOptions | undefined
    _barBackgroundBlurStyle_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _barBackgroundBlurStyle_1_0value?: BlurStyle | undefined
    _barBackgroundBlurStyle_1_1value?: BackgroundBlurStyleOptions | undefined
    _cachedMaxCount_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _cachedMaxCount_0_0value?: number | undefined
    _cachedMaxCount_0_1value?: TabsCacheMode | undefined
    applyModifierPatch(peerNode: PeerNode): void {
        super.applyModifierPatch(peerNode)
        const peer = peerNode as ArkTabsPeer
        if (this._vertical_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._vertical_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.verticalAttribute((this._vertical_0_0value as boolean | undefined));
                    this._vertical_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._vertical_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._vertical_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.verticalAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._barPosition_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._barPosition_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.barPositionAttribute((this._barPosition_0_0value as BarPosition | undefined));
                    this._barPosition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._barPosition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._barPosition_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.barPositionAttribute((undefined as BarPosition | undefined));
                }
            }
        }
        if (this._scrollable_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._scrollable_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.scrollableAttribute((this._scrollable_0_0value as boolean | undefined));
                    this._scrollable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._scrollable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._scrollable_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.scrollableAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._barWidth_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._barWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.barWidthAttribute((this._barWidth_0_0value as Length | undefined));
                    this._barWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._barWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._barWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.barWidthAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._barHeight_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._barHeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.barHeightAttribute((this._barHeight_0_0value as Length | undefined));
                    this._barHeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._barHeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._barHeight_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.barHeightAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._animationDuration_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._animationDuration_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.animationDurationAttribute((this._animationDuration_0_0value as number | undefined));
                    this._animationDuration_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._animationDuration_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._animationDuration_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.animationDurationAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._animationMode_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._animationMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.animationModeAttribute((this._animationMode_0_0value as AnimationMode | undefined));
                    this._animationMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._animationMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._animationMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.animationModeAttribute((undefined as AnimationMode | undefined));
                }
            }
        }
        if (this._edgeEffect_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._edgeEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.edgeEffectAttribute((this._edgeEffect_0_0value as EdgeEffect | undefined));
                    this._edgeEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._edgeEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._edgeEffect_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.edgeEffectAttribute((undefined as EdgeEffect | undefined));
                }
            }
        }
        if (this._onChange_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onChangeAttribute((this._onChange_0_0value as ((value0: number) => void) | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onChangeAttribute((undefined as ((value0: number) => void) | undefined));
                }
            }
        }
        if (this._onSelected_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onSelected_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onSelectedAttribute((this._onSelected_0_0value as ((value0: number) => void) | undefined));
                    this._onSelected_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onSelected_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onSelected_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onSelectedAttribute((undefined as ((value0: number) => void) | undefined));
                }
            }
        }
        if (this._onTabBarClick_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onTabBarClick_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onTabBarClickAttribute((this._onTabBarClick_0_0value as ((value0: number) => void) | undefined));
                    this._onTabBarClick_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onTabBarClick_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onTabBarClick_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onTabBarClickAttribute((undefined as ((value0: number) => void) | undefined));
                }
            }
        }
        if (this._onUnselected_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onUnselected_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onUnselectedAttribute((this._onUnselected_0_0value as ((value0: number) => void) | undefined));
                    this._onUnselected_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onUnselected_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onUnselected_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onUnselectedAttribute((undefined as ((value0: number) => void) | undefined));
                }
            }
        }
        if (this._onAnimationStart_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onAnimationStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onAnimationStartAttribute((this._onAnimationStart_0_0value as OnTabsAnimationStartCallback | undefined));
                    this._onAnimationStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onAnimationStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onAnimationStart_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onAnimationStartAttribute((undefined as OnTabsAnimationStartCallback | undefined));
                }
            }
        }
        if (this._onAnimationEnd_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onAnimationEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onAnimationEndAttribute((this._onAnimationEnd_0_0value as OnTabsAnimationEndCallback | undefined));
                    this._onAnimationEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onAnimationEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onAnimationEnd_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onAnimationEndAttribute((undefined as OnTabsAnimationEndCallback | undefined));
                }
            }
        }
        if (this._onGestureSwipe_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onGestureSwipe_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onGestureSwipeAttribute((this._onGestureSwipe_0_0value as OnTabsGestureSwipeCallback | undefined));
                    this._onGestureSwipe_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onGestureSwipe_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onGestureSwipe_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onGestureSwipeAttribute((undefined as OnTabsGestureSwipeCallback | undefined));
                }
            }
        }
        if (this._fadingEdge_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._fadingEdge_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.fadingEdgeAttribute((this._fadingEdge_0_0value as boolean | undefined));
                    this._fadingEdge_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fadingEdge_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fadingEdge_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.fadingEdgeAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._divider_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._divider_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.dividerAttribute((this._divider_0_0value as DividerStyle | undefined));
                    this._divider_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._divider_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._divider_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.dividerAttribute((undefined as DividerStyle | undefined));
                }
            }
        }
        if (this._barOverlap_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._barOverlap_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.barOverlapAttribute((this._barOverlap_0_0value as boolean | undefined));
                    this._barOverlap_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._barOverlap_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._barOverlap_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.barOverlapAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._barBackgroundColor_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._barBackgroundColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.barBackgroundColorAttribute((this._barBackgroundColor_0_0value as ResourceColor | undefined));
                    this._barBackgroundColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._barBackgroundColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._barBackgroundColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.barBackgroundColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._barGridAlign_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._barGridAlign_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.barGridAlignAttribute((this._barGridAlign_0_0value as BarGridColumnOptions | undefined));
                    this._barGridAlign_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._barGridAlign_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._barGridAlign_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.barGridAlignAttribute((undefined as BarGridColumnOptions | undefined));
                }
            }
        }
        if (this._customContentTransition_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._customContentTransition_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.customContentTransitionAttribute((this._customContentTransition_0_0value as TabsCustomContentTransitionCallback | undefined));
                    this._customContentTransition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._customContentTransition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._customContentTransition_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.customContentTransitionAttribute((undefined as TabsCustomContentTransitionCallback | undefined));
                }
            }
        }
        if (this._barBackgroundBlurStyle_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._barBackgroundBlurStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.barBackgroundBlurStyle0Attribute((this._barBackgroundBlurStyle_0_0value as BlurStyle | undefined));
                    this._barBackgroundBlurStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._barBackgroundBlurStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._barBackgroundBlurStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.barBackgroundBlurStyle0Attribute((undefined as BlurStyle | undefined));
                }
            }
        }
        if (this._pageFlipMode_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._pageFlipMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.pageFlipModeAttribute((this._pageFlipMode_0_0value as PageFlipMode | undefined));
                    this._pageFlipMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._pageFlipMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._pageFlipMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.pageFlipModeAttribute((undefined as PageFlipMode | undefined));
                }
            }
        }
        if (this._barBackgroundEffect_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._barBackgroundEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.barBackgroundEffectAttribute((this._barBackgroundEffect_0_0value as BackgroundEffectOptions | undefined));
                    this._barBackgroundEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._barBackgroundEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._barBackgroundEffect_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.barBackgroundEffectAttribute((undefined as BackgroundEffectOptions | undefined));
                }
            }
        }
        if (this._onContentWillChange_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onContentWillChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onContentWillChangeAttribute((this._onContentWillChange_0_0value as OnTabsContentWillChangeCallback | undefined));
                    this._onContentWillChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onContentWillChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onContentWillChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onContentWillChangeAttribute((undefined as OnTabsContentWillChangeCallback | undefined));
                }
            }
        }
        if (this._barMode_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._barMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.barMode1Attribute((this._barMode_0_0value as BarMode | undefined), (this._barMode_0_1value as ScrollableBarModeOptions | undefined));
                    this._barMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._barMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._barMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.barMode1Attribute((undefined as BarMode | undefined), (undefined as ScrollableBarModeOptions | undefined | undefined));
                }
            }
        }
        if (this._barBackgroundBlurStyle_1_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._barBackgroundBlurStyle_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.barBackgroundBlurStyle1Attribute((this._barBackgroundBlurStyle_1_0value as BlurStyle | undefined), (this._barBackgroundBlurStyle_1_1value as BackgroundBlurStyleOptions | undefined));
                    this._barBackgroundBlurStyle_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._barBackgroundBlurStyle_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._barBackgroundBlurStyle_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.barBackgroundBlurStyle1Attribute((undefined as BlurStyle | undefined), (undefined as BackgroundBlurStyleOptions | undefined));
                }
            }
        }
        if (this._cachedMaxCount_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._cachedMaxCount_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.cachedMaxCountAttribute((this._cachedMaxCount_0_0value as number | undefined), (this._cachedMaxCount_0_1value as TabsCacheMode | undefined));
                    this._cachedMaxCount_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._cachedMaxCount_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._cachedMaxCount_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.cachedMaxCountAttribute((undefined as number | undefined), (undefined as TabsCacheMode | undefined));
                }
            }
        }
    }
    mergeModifier(value: TabsModifier): void {
        super.mergeModifier(value)
        if (!(value instanceof TabsModifier)) {
            return;
        }
        const modifier = value as TabsModifier;
        if (modifier._vertical_0_flag != AttributeUpdaterFlag.INITIAL) {
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
        if (modifier._barPosition_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._barPosition_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.barPosition(modifier._barPosition_0_0value);
                    break;
                }
                default: {
                    this.barPosition((undefined as BarPosition | undefined));
                }
            }
        }
        if (modifier._scrollable_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._scrollable_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.scrollable(modifier._scrollable_0_0value);
                    break;
                }
                default: {
                    this.scrollable((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._barWidth_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._barWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.barWidth(modifier._barWidth_0_0value);
                    break;
                }
                default: {
                    this.barWidth((undefined as Length | undefined));
                }
            }
        }
        if (modifier._barHeight_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._barHeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.barHeight(modifier._barHeight_0_0value);
                    break;
                }
                default: {
                    this.barHeight((undefined as Length | undefined));
                }
            }
        }
        if (modifier._animationDuration_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._animationDuration_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.animationDuration(modifier._animationDuration_0_0value);
                    break;
                }
                default: {
                    this.animationDuration((undefined as number | undefined));
                }
            }
        }
        if (modifier._animationMode_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._animationMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.animationMode(modifier._animationMode_0_0value);
                    break;
                }
                default: {
                    this.animationMode((undefined as AnimationMode | undefined));
                }
            }
        }
        if (modifier._edgeEffect_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._edgeEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.edgeEffect(modifier._edgeEffect_0_0value);
                    break;
                }
                default: {
                    this.edgeEffect((undefined as EdgeEffect | undefined));
                }
            }
        }
        if (modifier._onChange_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onChange(modifier._onChange_0_0value);
                    break;
                }
                default: {
                    this.onChange((undefined as ((value0: number) => void) | undefined));
                }
            }
        }
        if (modifier._onSelected_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onSelected_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onSelected(modifier._onSelected_0_0value);
                    break;
                }
                default: {
                    this.onSelected((undefined as ((value0: number) => void) | undefined));
                }
            }
        }
        if (modifier._onTabBarClick_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onTabBarClick_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onTabBarClick(modifier._onTabBarClick_0_0value);
                    break;
                }
                default: {
                    this.onTabBarClick((undefined as ((value0: number) => void) | undefined));
                }
            }
        }
        if (modifier._onUnselected_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onUnselected_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onUnselected(modifier._onUnselected_0_0value);
                    break;
                }
                default: {
                    this.onUnselected((undefined as ((value0: number) => void) | undefined));
                }
            }
        }
        if (modifier._onAnimationStart_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onAnimationStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onAnimationStart(modifier._onAnimationStart_0_0value);
                    break;
                }
                default: {
                    this.onAnimationStart((undefined as OnTabsAnimationStartCallback | undefined));
                }
            }
        }
        if (modifier._onAnimationEnd_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onAnimationEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onAnimationEnd(modifier._onAnimationEnd_0_0value);
                    break;
                }
                default: {
                    this.onAnimationEnd((undefined as OnTabsAnimationEndCallback | undefined));
                }
            }
        }
        if (modifier._onGestureSwipe_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onGestureSwipe_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onGestureSwipe(modifier._onGestureSwipe_0_0value);
                    break;
                }
                default: {
                    this.onGestureSwipe((undefined as OnTabsGestureSwipeCallback | undefined));
                }
            }
        }
        if (modifier._fadingEdge_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._fadingEdge_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fadingEdge(modifier._fadingEdge_0_0value);
                    break;
                }
                default: {
                    this.fadingEdge((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._divider_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._divider_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.divider(modifier._divider_0_0value);
                    break;
                }
                default: {
                    this.divider((undefined as DividerStyle | null | undefined));
                }
            }
        }
        if (modifier._barOverlap_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._barOverlap_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.barOverlap(modifier._barOverlap_0_0value);
                    break;
                }
                default: {
                    this.barOverlap((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._barBackgroundColor_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._barBackgroundColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.barBackgroundColor(modifier._barBackgroundColor_0_0value);
                    break;
                }
                default: {
                    this.barBackgroundColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._barGridAlign_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._barGridAlign_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.barGridAlign(modifier._barGridAlign_0_0value);
                    break;
                }
                default: {
                    this.barGridAlign((undefined as BarGridColumnOptions | undefined));
                }
            }
        }
        if (modifier._customContentTransition_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._customContentTransition_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.customContentTransition(modifier._customContentTransition_0_0value);
                    break;
                }
                default: {
                    this.customContentTransition((undefined as TabsCustomContentTransitionCallback | undefined));
                }
            }
        }
        if (modifier._barBackgroundBlurStyle_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._barBackgroundBlurStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.barBackgroundBlurStyle(modifier._barBackgroundBlurStyle_0_0value);
                    break;
                }
                default: {
                    this.barBackgroundBlurStyle((undefined as BlurStyle | undefined));
                }
            }
        }
        if (modifier._pageFlipMode_0_flag != AttributeUpdaterFlag.INITIAL) {
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
        if (modifier._barBackgroundEffect_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._barBackgroundEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.barBackgroundEffect(modifier._barBackgroundEffect_0_0value);
                    break;
                }
                default: {
                    this.barBackgroundEffect((undefined as BackgroundEffectOptions | undefined));
                }
            }
        }
        if (modifier._onContentWillChange_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onContentWillChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onContentWillChange(modifier._onContentWillChange_0_0value);
                    break;
                }
                default: {
                    this.onContentWillChange((undefined as OnTabsContentWillChangeCallback | undefined));
                }
            }
        }
        if (modifier._barMode_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._barMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.barMode(modifier._barMode_0_0value, modifier._barMode_0_1value);
                    break;
                }
                default: {
                    this.barMode((undefined as BarMode | undefined), (undefined as ScrollableBarModeOptions | undefined | undefined));
                }
            }
        }
        if (modifier._barBackgroundBlurStyle_1_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._barBackgroundBlurStyle_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.barBackgroundBlurStyle(modifier._barBackgroundBlurStyle_1_0value, modifier._barBackgroundBlurStyle_1_1value);
                    break;
                }
                default: {
                    this.barBackgroundBlurStyle((undefined as BlurStyle | undefined), (undefined as BackgroundBlurStyleOptions | undefined));
                }
            }
        }
        if (modifier._cachedMaxCount_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._cachedMaxCount_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.cachedMaxCount(modifier._cachedMaxCount_0_0value, modifier._cachedMaxCount_0_1value);
                    break;
                }
                default: {
                    this.cachedMaxCount((undefined as number | undefined), (undefined as TabsCacheMode | undefined));
                }
            }
        }
    }
    vertical(value: boolean | undefined): this {
        if (((this._vertical_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._vertical_0_0value) !== (value))) {
            this._vertical_0_flag = AttributeUpdaterFlag.UPDATE
            this._vertical_0_0value = value
        } else {
            this._vertical_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    barPosition(value: BarPosition | undefined): this {
        if (((this._barPosition_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._barPosition_0_flag = AttributeUpdaterFlag.UPDATE
            this._barPosition_0_0value = value
        } else {
            this._barPosition_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    scrollable(value: boolean | undefined): this {
        if (((this._scrollable_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._scrollable_0_0value) !== (value))) {
            this._scrollable_0_flag = AttributeUpdaterFlag.UPDATE
            this._scrollable_0_0value = value
        } else {
            this._scrollable_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    barWidth(value: Length | undefined): this {
        if (((this._barWidth_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._barWidth_0_flag = AttributeUpdaterFlag.UPDATE
            this._barWidth_0_0value = value
        } else {
            this._barWidth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    barHeight(value: Length | undefined): this {
        if (((this._barHeight_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._barHeight_0_flag = AttributeUpdaterFlag.UPDATE
            this._barHeight_0_0value = value
        } else {
            this._barHeight_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    animationDuration(value: number | undefined): this {
        if (((this._animationDuration_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._animationDuration_0_0value) !== (value))) {
            this._animationDuration_0_flag = AttributeUpdaterFlag.UPDATE
            this._animationDuration_0_0value = value
        } else {
            this._animationDuration_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    animationMode(value: AnimationMode | undefined): this {
        if (((this._animationMode_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._animationMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._animationMode_0_0value = value
        } else {
            this._animationMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    edgeEffect(value: EdgeEffect | undefined): this {
        if (((this._edgeEffect_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._edgeEffect_0_flag = AttributeUpdaterFlag.UPDATE
            this._edgeEffect_0_0value = value
        } else {
            this._edgeEffect_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onChange(value: ((value0: number) => void) | undefined): this {
        if (((this._onChange_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._onChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onChange_0_0value = value
        } else {
            this._onChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onSelected(value: ((value0: number) => void) | undefined): this {
        if (((this._onSelected_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._onSelected_0_flag = AttributeUpdaterFlag.UPDATE
            this._onSelected_0_0value = value
        } else {
            this._onSelected_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onTabBarClick(value: ((value0: number) => void) | undefined): this {
        if (((this._onTabBarClick_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._onTabBarClick_0_flag = AttributeUpdaterFlag.UPDATE
            this._onTabBarClick_0_0value = value
        } else {
            this._onTabBarClick_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onUnselected(value: ((value0: number) => void) | undefined): this {
        if (((this._onUnselected_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._onUnselected_0_flag = AttributeUpdaterFlag.UPDATE
            this._onUnselected_0_0value = value
        } else {
            this._onUnselected_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onAnimationStart(value: OnTabsAnimationStartCallback | undefined): this {
        if (((this._onAnimationStart_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._onAnimationStart_0_flag = AttributeUpdaterFlag.UPDATE
            this._onAnimationStart_0_0value = value
        } else {
            this._onAnimationStart_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onAnimationEnd(value: OnTabsAnimationEndCallback | undefined): this {
        if (((this._onAnimationEnd_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._onAnimationEnd_0_flag = AttributeUpdaterFlag.UPDATE
            this._onAnimationEnd_0_0value = value
        } else {
            this._onAnimationEnd_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onGestureSwipe(value: OnTabsGestureSwipeCallback | undefined): this {
        if (((this._onGestureSwipe_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._onGestureSwipe_0_flag = AttributeUpdaterFlag.UPDATE
            this._onGestureSwipe_0_0value = value
        } else {
            this._onGestureSwipe_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fadingEdge(value: boolean | undefined): this {
        if (((this._fadingEdge_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._fadingEdge_0_0value) !== (value))) {
            this._fadingEdge_0_flag = AttributeUpdaterFlag.UPDATE
            this._fadingEdge_0_0value = value
        } else {
            this._fadingEdge_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    divider(value: DividerStyle | null | undefined): this {
        if (((this._divider_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._divider_0_flag = AttributeUpdaterFlag.UPDATE
            this._divider_0_0value = value
        } else {
            this._divider_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    barOverlap(value: boolean | undefined): this {
        if (((this._barOverlap_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._barOverlap_0_0value) !== (value))) {
            this._barOverlap_0_flag = AttributeUpdaterFlag.UPDATE
            this._barOverlap_0_0value = value
        } else {
            this._barOverlap_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    barBackgroundColor(value: ResourceColor | undefined): this {
        if (((this._barBackgroundColor_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._barBackgroundColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._barBackgroundColor_0_0value = value
        } else {
            this._barBackgroundColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    barGridAlign(value: BarGridColumnOptions | undefined): this {
        if (((this._barGridAlign_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._barGridAlign_0_flag = AttributeUpdaterFlag.UPDATE
            this._barGridAlign_0_0value = value
        } else {
            this._barGridAlign_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    customContentTransition(value: TabsCustomContentTransitionCallback | undefined): this {
        if (((this._customContentTransition_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._customContentTransition_0_flag = AttributeUpdaterFlag.UPDATE
            this._customContentTransition_0_0value = value
        } else {
            this._customContentTransition_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    barBackgroundBlurStyle(value: BlurStyle | undefined): this {
        if (((this._barBackgroundBlurStyle_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._barBackgroundBlurStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._barBackgroundBlurStyle_0_0value = value
        } else {
            this._barBackgroundBlurStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    pageFlipMode(value: PageFlipMode | undefined): this {
        if (((this._pageFlipMode_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._pageFlipMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._pageFlipMode_0_0value = value
        } else {
            this._pageFlipMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    barBackgroundEffect(value: BackgroundEffectOptions | undefined): this {
        if (((this._barBackgroundEffect_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._barBackgroundEffect_0_flag = AttributeUpdaterFlag.UPDATE
            this._barBackgroundEffect_0_0value = value
        } else {
            this._barBackgroundEffect_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onContentWillChange(value: OnTabsContentWillChangeCallback | undefined): this {
        if (((this._onContentWillChange_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._onContentWillChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onContentWillChange_0_0value = value
        } else {
            this._onContentWillChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    barMode(value: BarMode | undefined, options?: ScrollableBarModeOptions): this {
        if (((this._barMode_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._barMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._barMode_0_0value = value
            this._barMode_0_1value = options
        } else {
            this._barMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    barBackgroundBlurStyle(style: BlurStyle | undefined, options: BackgroundBlurStyleOptions | undefined): this {
        if (((this._barBackgroundBlurStyle_1_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._barBackgroundBlurStyle_1_flag = AttributeUpdaterFlag.UPDATE
            this._barBackgroundBlurStyle_1_0value = style
            this._barBackgroundBlurStyle_1_1value = options
        } else {
            this._barBackgroundBlurStyle_1_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    cachedMaxCount(count: number | undefined, mode: TabsCacheMode | undefined): this {
        if (((this._cachedMaxCount_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._cachedMaxCount_0_0value) !== (count))) {
            this._cachedMaxCount_0_flag = AttributeUpdaterFlag.UPDATE
            this._cachedMaxCount_0_0value = count
            this._cachedMaxCount_0_1value = mode
        } else {
            this._cachedMaxCount_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public barModeScrollable(options: ScrollableBarModeOptions | undefined): this {
        throw new Error("Not implemented")
    }
    public _onChangeEvent_index(callback: ((index: number) => void)): void {
        throw new Error("Not implemented")
    }
    public attributeModifier(value: AttributeModifier<TabsAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

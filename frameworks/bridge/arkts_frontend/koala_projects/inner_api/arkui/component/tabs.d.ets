/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { memo_stable } from '@koalaui/runtime/annotations';
import {
    ArkCommonMethodPeer,
    ArkCommonMethodComponent,
    CommonMethod
} from 'arkui/component/common';
import {
    BlurStyle,
    BackgroundEffectOptions,
    BackgroundBlurStyleOptions,
    DividerStyle,
} from 'arkui.component.common';
import { int32 } from '@koalaui/compat';
import { KPointer } from '@koalaui/interop';
import { ComponentBase } from 'arkui/ComponentBase';
import { ResourceColor, Length } from 'arkui.component.units';
import { PageFlipMode, EdgeEffect } from 'arkui.component.enums';
import {
    OnTabsAnimationEndCallback,
    OnTabsAnimationStartCallback,
    OnTabsContentWillChangeCallback,
    OnTabsGestureSwipeCallback,
    TabsCustomContentTransitionCallback,
    AnimationMode,
    BarMode,
    BarPosition,
    TabsAttribute,
    BarGridColumnOptions,
    ScrollableBarModeOptions,
    TabsOptions,
} from 'arkui.component.tabs';

export enum TabsCacheMode {
    CACHE_BOTH_SIDE = 0,
    CACHE_LATEST_SWITCHED = 1,
}

export declare class ArkTabsPeer extends ArkCommonMethodPeer {
    constructor(peerPtr: KPointer, id: int32, name: string);
    constructor(peerPtr: KPointer, id: int32);
    protected constructor(peerPtr: KPointer, id: int32, name: string, flags: int32);
    public static create(component: ComponentBase | undefined, flags?: int32): ArkTabsPeer;
    public setTabsOptionsAttribute(options?: TabsOptions): void;
    public verticalAttribute(value: boolean | undefined): void;
    public barPositionAttribute(value: BarPosition | undefined): void;
    public scrollableAttribute(value: boolean | undefined): void;
    public barMode0Attribute(value: BarMode | undefined): void;
    public barMode1Attribute(value: BarMode | undefined, options?: ScrollableBarModeOptions): void;
    public barWidthAttribute(value: Length | undefined): void;
    public barHeightAttribute(value: Length | undefined): void;
    public animationDurationAttribute(value: number | undefined): void;
    public animationModeAttribute(value: AnimationMode | undefined): void;
    public edgeEffectAttribute(value: EdgeEffect | undefined): void;
    public onChangeAttribute(value: ((index: number) => void) | undefined): void;
    public onSelectedAttribute(value: ((index: number) => void) | undefined): void;
    public onTabBarClickAttribute(value: ((index: number) => void) | undefined): void;
    public onUnselectedAttribute(value: ((index: number) => void) | undefined): void;
    public onAnimationStartAttribute(value: OnTabsAnimationStartCallback | undefined): void;
    public onAnimationEndAttribute(value: OnTabsAnimationEndCallback | undefined): void;
    public onGestureSwipeAttribute(value: OnTabsGestureSwipeCallback | undefined): void;
    public fadingEdgeAttribute(value: boolean | undefined): void;
    public dividerAttribute(value: DividerStyle | undefined): void;
    public barOverlapAttribute(value: boolean | undefined): void;
    public barBackgroundColorAttribute(value: ResourceColor | undefined): void;
    public barGridAlignAttribute(value: BarGridColumnOptions | undefined): void;
    public customContentTransitionAttribute(value: TabsCustomContentTransitionCallback | undefined): void;
    public barBackgroundBlurStyle0Attribute(value: BlurStyle | undefined): void;
    public barBackgroundBlurStyle1Attribute(
        style: BlurStyle | undefined,
        options: BackgroundBlurStyleOptions | undefined
    ): void;
    public barBackgroundEffectAttribute(value: BackgroundEffectOptions | undefined): void;
    public pageFlipModeAttribute(value: PageFlipMode | undefined): void;
    public onContentWillChangeAttribute(value: OnTabsContentWillChangeCallback | undefined): void;
    public barModeScrollableAttribute(options: ScrollableBarModeOptions | undefined): void;
    public cachedMaxCountAttribute(count: number | undefined, mode: TabsCacheMode | undefined): void;
    public _onChangeEvent_indexAttribute(callback: (index: number) => void): void;
}

export interface TabsAttribute extends CommonMethod {
    vertical(value: boolean | undefined): this;
    barPosition(value: BarPosition | undefined): this;
    scrollable(value: boolean | undefined): this;
    barMode(value: BarMode | undefined, options?: ScrollableBarModeOptions): this;
    barWidth(value: Length | undefined): this;
    barHeight(value: Length | undefined): this;
    animationDuration(value: number | undefined): this;
    animationMode(value: AnimationMode | undefined): this;
    edgeEffect(value: EdgeEffect | undefined): this;
    onChange(value: ((index: number) => void) | undefined): this;
    onSelected(value: ((index: number) => void) | undefined): this;
    onTabBarClick(value: ((index: number) => void) | undefined): this;
    onUnselected(value: ((index: number) => void) | undefined): this;
    onAnimationStart(value: OnTabsAnimationStartCallback | undefined): this;
    onAnimationEnd(value: OnTabsAnimationEndCallback | undefined): this;
    onGestureSwipe(value: OnTabsGestureSwipeCallback | undefined): this;
    fadingEdge(value: boolean | undefined): this;
    divider(value: DividerStyle | undefined): this;
    barOverlap(value: boolean | undefined): this;
    barBackgroundColor(value: ResourceColor | undefined): this;
    barGridAlign(value: BarGridColumnOptions | undefined): this;
    customContentTransition(value: TabsCustomContentTransitionCallback | undefined): this;
    barBackgroundBlurStyle(style: BlurStyle | undefined, options?: BackgroundBlurStyleOptions): this;
    barBackgroundEffect(value: BackgroundEffectOptions | undefined): this;
    pageFlipMode(value: PageFlipMode | undefined): this;
    onContentWillChange(value: OnTabsContentWillChangeCallback | undefined): this;
    barModeScrollable(options: ScrollableBarModeOptions | undefined): this;
    cachedMaxCount(count: number | undefined, mode: TabsCacheMode | undefined): this;
    _onChangeEvent_index(callback: (index: number) => void): void;
}

@memo_stable() export declare class ArkTabsComponent extends ArkCommonMethodComponent implements TabsAttribute {
    public getPeer(): ArkTabsPeer;
    public setTabsOptions(options?: TabsOptions): this;
    public vertical(value: boolean | undefined): this;
    public barPosition(value: BarPosition | undefined): this;
    public scrollable(value: boolean | undefined): this;
    public barMode(value: BarMode | undefined, options?: ScrollableBarModeOptions): this;
    public barWidth(value: Length | undefined): this;
    public barHeight(value: Length | undefined): this;
    public animationDuration(value: number | undefined): this;
    public animationMode(value: AnimationMode | undefined): this;
    public edgeEffect(value: EdgeEffect | undefined): this;
    public onChange(value: ((index: number) => void) | undefined): this;
    public onSelected(value: ((index: number) => void) | undefined): this;
    public onTabBarClick(value: ((index: number) => void) | undefined): this;
    public onUnselected(value: ((index: number) => void) | undefined): this;
    public onAnimationStart(value: OnTabsAnimationStartCallback | undefined): this;
    public onAnimationEnd(value: OnTabsAnimationEndCallback | undefined): this;
    public onGestureSwipe(value: OnTabsGestureSwipeCallback | undefined): this;
    public fadingEdge(value: boolean | undefined): this;
    public divider(value: DividerStyle | undefined): this;
    public barOverlap(value: boolean | undefined): this;
    public barBackgroundColor(value: ResourceColor | undefined): this;
    public barGridAlign(value: BarGridColumnOptions | undefined): this;
    public customContentTransition(value: TabsCustomContentTransitionCallback | undefined): this;
    public barBackgroundBlurStyle(style: BlurStyle | undefined, options?: BackgroundBlurStyleOptions): this;
    public barBackgroundEffect(value: BackgroundEffectOptions | undefined): this;
    public pageFlipMode(value: PageFlipMode | undefined): this;
    public onContentWillChange(value: OnTabsContentWillChangeCallback | undefined): this;
    public barModeScrollable(options: ScrollableBarModeOptions | undefined): this;
    public cachedMaxCount(count: number | undefined, mode: TabsCacheMode | undefined): this;
    public _onChangeEvent_index(callback: (index: number) => void): void;
    public applyAttributesFinish(): void;
}

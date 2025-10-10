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
import { InteropNativeModule } from "@koalaui/interop";

import { Length } from "../component/units"
import { ICurve, Bindable } from "../component/common"
import { IndicatorComponentController } from "../component/indicatorcomponent"
import { EdgeEffect, Curve, PageFlipMode } from "../component/enums"
import { runtimeType, RuntimeType } from '@koalaui/interop';
import { ArkBaseNode } from "./ArkBaseNode";
import { default as curves } from "@ohos.curves"
import { ArkSwiperPeer, SwiperController, SwiperAttribute, AutoPlayOptions, DotIndicator, DigitIndicator,
    SwiperDisplayMode, OnSwiperAnimationStartCallback, OnSwiperAnimationEndCallback, OnSwiperGestureSwipeCallback,
    SwiperNestedScrollMode, SwiperContentAnimatedTransition, ContentDidScrollCallback, ContentWillScrollCallback,
    ArrowStyle, SwiperAutoFill
} from "../framework";
import { int32 } from "@koalaui/common"
export class ArkSwiperNode extends ArkBaseNode implements SwiperAttribute  {

    constructParam(...param: Object[]): this {
        if (param.length > 1) {
            throw new Error('more than 1 parameters');
        }
        let controller_casted : SwiperController | undefined = undefined;
        if (param.length === 1) {
            controller_casted = param[0] as (SwiperController | undefined);
        }
        this.getPeer()?.setSwiperOptionsAttribute(controller_casted)
        return this;
    }
    getPeer() : ArkSwiperPeer {
        return this.peer as ArkSwiperPeer
    }
    initialize(controller?: SwiperController): this {
        const controller_casted = controller as (SwiperController | undefined)
        this.getPeer()?.setSwiperOptionsAttribute(controller_casted)
        return this;
    }
    setSwiperOptions(controller?: SwiperController): this {
        const controller_casted = controller as (SwiperController | undefined)
        this.getPeer()?.setSwiperOptionsAttribute(controller_casted)
        return this;
    }
    index(value: int32 | Bindable<int32> | undefined): this {
        const index_type = runtimeType(value);
        if (value instanceof int32 || (RuntimeType.UNDEFINED === index_type)) {
            const value_casted = value as (int32 | undefined);
            this.getPeer()?.setIndexAttribute(value_casted)
            return this
        }
        return this
    }
    autoPlay(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setAutoPlay0Attribute(value_casted)
        return this
    }
    autoPlay(autoPlay: boolean | undefined, options: AutoPlayOptions | undefined): this {
        const autoPlay_casted = autoPlay as (boolean | undefined)
        const options_casted = options as (AutoPlayOptions | undefined)
        this.getPeer()?.setAutoPlay1Attribute(autoPlay_casted, options_casted)
        return this
    }
    interval(value: int32 | undefined): this {
        const value_casted = value as (int32 | undefined)
        this.getPeer()?.setIntervalAttribute(value_casted)
        return this
    }
    indicator(value: IndicatorComponentController | DotIndicator | DigitIndicator | boolean | undefined): this {
        const value_casted = value as (IndicatorComponentController | DotIndicator | DigitIndicator | boolean | undefined)
        this.getPeer()?.setIndicatorAttribute(value_casted)
        this.markDirty();
        return this
    }
    loop(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setLoopAttribute(value_casted)
        return this
    }
    duration(value: int32 | undefined): this {
        const value_casted = value as (int32 | undefined)
        this.getPeer()?.setDurationAttribute(value_casted)
        return this
    }
    vertical(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setVerticalAttribute(value_casted)
        return this
    }
    itemSpace(value: double | string | undefined): this {
        const value_casted = value as (double | string | undefined)
        this.getPeer()?.setItemSpaceAttribute(value_casted)
        return this
    }
    displayMode(value: SwiperDisplayMode | undefined): this {
        const value_casted = value as (SwiperDisplayMode | undefined)
        this.getPeer()?.setDisplayModeAttribute(value_casted)
        return this
    }
    cachedCount(value: int32 | undefined): this {
        const value_casted = value as (int32 | undefined)
        this.getPeer()?.setCachedCount0Attribute(value_casted)
        return this
    }
    cachedCount(count: int32 | undefined, isShown?: boolean): this {
        const count_casted = count as (int32 | undefined)
        const isShown_casted = isShown as (boolean | undefined)
        this.getPeer()?.setCachedCount1Attribute(count_casted, isShown_casted)
        return this
    }
    effectMode(value: EdgeEffect | undefined): this {
        const value_casted = value as (EdgeEffect | undefined)
        this.getPeer()?.setEffectModeAttribute(value_casted)
        return this
    }
    disableSwipe(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setDisableSwipeAttribute(value_casted)
        return this
    }
    curve(value: curves.Curve | string | curves.ICurve | undefined): this {
        const value_casted = value as (curves.Curve | string | curves.ICurve | undefined)
        this.getPeer()?.setCurveAttribute(value_casted)
        return this
    }
    onChange(value: ((index: int32) => void) | undefined): this {
        const value_casted = value as (((index: int32) => void) | undefined)
        this.getPeer()?.setOnChangeAttribute(value_casted)
        return this
    }
    onSelected(value: ((index: int32) => void) | undefined): this {
        const value_casted = value as (((index: int32) => void) | undefined)
        this.getPeer()?.setOnSelectedAttribute(value_casted)
        return this
    }
    onUnselected(value: ((index: int32) => void) | undefined): this {
        const value_casted = value as (((index: int32) => void) | undefined)
        this.getPeer()?.setOnUnselectedAttribute(value_casted)
        return this
    }
    onAnimationStart(value: OnSwiperAnimationStartCallback | undefined): this {
        const value_casted = value as (OnSwiperAnimationStartCallback | undefined)
        this.getPeer()?.setOnAnimationStartAttribute(value_casted)
        return this
    }
    onAnimationEnd(value: OnSwiperAnimationEndCallback | undefined): this {
        const value_casted = value as (OnSwiperAnimationEndCallback | undefined)
        this.getPeer()?.setOnAnimationEndAttribute(value_casted)
        return this
    }
    onGestureSwipe(value: OnSwiperGestureSwipeCallback | undefined): this {
        const value_casted = value as (OnSwiperGestureSwipeCallback | undefined)
        this.getPeer()?.setOnGestureSwipeAttribute(value_casted)
        return this
    }
    nestedScroll(value: SwiperNestedScrollMode | undefined): this {
        const value_casted = value as (SwiperNestedScrollMode | undefined)
        this.getPeer()?.setNestedScrollAttribute(value_casted)
        return this
    }
    customContentTransition(value: SwiperContentAnimatedTransition | undefined): this {
        const value_casted = value as (SwiperContentAnimatedTransition | undefined)
        this.getPeer()?.setCustomContentTransitionAttribute(value_casted)
        return this
    }
    onContentDidScroll(value: ContentDidScrollCallback | undefined): this {
        const value_casted = value as (ContentDidScrollCallback | undefined)
        this.getPeer()?.setOnContentDidScrollAttribute(value_casted)
        return this
    }
    indicatorInteractive(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setIndicatorInteractiveAttribute(value_casted)
        return this
    }
    pageFlipMode(value: PageFlipMode | undefined): this {
        const value_casted = value as (PageFlipMode | undefined)
        this.getPeer()?.setPageFlipModeAttribute(value_casted)
        return this
    }
    onContentWillScroll(value: ContentWillScrollCallback | undefined): this {
        const value_casted = value as (ContentWillScrollCallback | undefined)
        this.getPeer()?.setOnContentWillScrollAttribute(value_casted)
        return this
    }
    displayArrow(value: ArrowStyle | boolean | undefined, isHoverShow?: boolean): this {
        const value_casted = value as (ArrowStyle | boolean | undefined)
        const isHoverShow_casted = isHoverShow as (boolean | undefined)
        this.getPeer()?.setDisplayArrowAttribute(value_casted, isHoverShow_casted)
        this.markDirty();
        return this
    }
    displayCount(value: int32 | string | SwiperAutoFill | undefined, swipeByGroup?: boolean): this {
        const value_casted = value as (int32 | string | SwiperAutoFill | undefined)
        const swipeByGroup_casted = swipeByGroup as (boolean | undefined)
        this.getPeer()?.setDisplayCountAttribute(value_casted, swipeByGroup_casted)
        return this
    }
    prevMargin(value: Length | undefined, ignoreBlank?: boolean): this {
        const value_casted = value as (Length | undefined)
        const ignoreBlank_casted = ignoreBlank as (boolean | undefined)
        this.getPeer()?.setPrevMarginAttribute(value_casted, ignoreBlank_casted)
        return this
    }
    nextMargin(value: Length | undefined, ignoreBlank?: boolean): this {
        const value_casted = value as (Length | undefined)
        const ignoreBlank_casted = ignoreBlank as (boolean | undefined)
        this.getPeer()?.setNextMarginAttribute(value_casted, ignoreBlank_casted)
        return this
    }
}
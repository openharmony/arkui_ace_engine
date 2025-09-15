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

import { Length } from "../../component/units"
import { ICurve, Bindable } from "../../component/common"
import { IndicatorComponentController } from "../../component/indicatorcomponent"
import { EdgeEffect, Curve, PageFlipMode } from "../../component/enums"
import { IndicatorStyle } from "../../component/arkui-external"
import { runtimeType, RuntimeType } from '@koalaui/interop';
import { ArkBaseNode } from "./ArkBaseNode";
import { ArkSwiperPeer, SwiperController, SwiperAttribute, AutoPlayOptions, DotIndicator, DigitIndicator,
    SwiperDisplayMode, OnSwiperAnimationStartCallback, OnSwiperAnimationEndCallback, OnSwiperGestureSwipeCallback,
    SwiperNestedScrollMode, SwiperContentAnimatedTransition, ContentDidScrollCallback, ContentWillScrollCallback,
    ArrowStyle, SwiperAutoFill
} from "../../component";
import { SwiperOpsHandWritten } from "../../handwritten"
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
    index(value: number | Bindable<number> | undefined): this {
        const index_type = runtimeType(value);
        if ((RuntimeType.NUMBER === index_type) || (RuntimeType.UNDEFINED === index_type)) {
            const value_casted = value as (number | undefined);
            this.getPeer()?.indexAttribute(value_casted)
            return this
        }
        SwiperOpsHandWritten.hookSwiperAttributeIndexImpl(this.getPeer().peer.ptr,
            (value as Bindable<number>));
        return this
    }
    autoPlay(autoPlay: boolean | undefined, options?: AutoPlayOptions): this {
        const autoPlay_casted = autoPlay as (boolean | undefined)
        const options_casted = options as (AutoPlayOptions | undefined)
        this.getPeer()?.autoPlay1Attribute(autoPlay_casted, options_casted)
        return this
    }
    interval(value: number | undefined): this {
        const value_casted = value as (number | undefined)
        this.getPeer()?.intervalAttribute(value_casted)
        return this
    }
    indicator(value: IndicatorComponentController | DotIndicator | DigitIndicator | boolean | undefined): this {
        const value_casted = value as (IndicatorComponentController | DotIndicator | DigitIndicator | boolean | undefined)
        this.getPeer()?.indicator1Attribute(value_casted)
        return this
    }
    loop(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.loopAttribute(value_casted)
        return this
    }
    duration(value: number | undefined): this {
        const value_casted = value as (number | undefined)
        this.getPeer()?.durationAttribute(value_casted)
        return this
    }
    vertical(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.verticalAttribute(value_casted)
        return this
    }
    itemSpace(value: number | string | undefined): this {
        const value_casted = value as (number | string | undefined)
        this.getPeer()?.itemSpaceAttribute(value_casted)
        return this
    }
    displayMode(value: SwiperDisplayMode | undefined): this {
        const value_casted = value as (SwiperDisplayMode | undefined)
        this.getPeer()?.displayModeAttribute(value_casted)
        return this
    }
    cachedCount(count: number | undefined, isShown?: boolean): this {
        const count_casted = count as (number | undefined)
        const isShown_casted = isShown as (boolean | undefined)
        this.getPeer()?.cachedCount1Attribute(count_casted, isShown_casted)
        return this
    }
    effectMode(value: EdgeEffect | undefined): this {
        const value_casted = value as (EdgeEffect | undefined)
        this.getPeer()?.effectModeAttribute(value_casted)
        return this
    }
    disableSwipe(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.disableSwipeAttribute(value_casted)
        return this
    }
    curve(value: Curve | string | ICurve | undefined): this {
        const value_casted = value as (Curve | string | ICurve | undefined)
        this.getPeer()?.curveAttribute(value_casted)
        return this
    }
    onChange(value: ((index: number) => void) | undefined): this {
        const value_casted = value as (((index: number) => void) | undefined)
        this.getPeer()?.onChangeAttribute(value_casted)
        return this
    }
    onSelected(value: ((index: number) => void) | undefined): this {
        const value_casted = value as (((index: number) => void) | undefined)
        this.getPeer()?.onSelectedAttribute(value_casted)
        return this
    }
    indicatorStyle(value: IndicatorStyle | undefined): this {
        const value_casted = value as (IndicatorStyle | undefined)
        this.getPeer()?.indicatorStyleAttribute(value_casted)
        return this
    }
    onUnselected(value: ((index: number) => void) | undefined): this {
        const value_casted = value as (((index: number) => void) | undefined)
        this.getPeer()?.onUnselectedAttribute(value_casted)
        return this
    }
    onAnimationStart(value: OnSwiperAnimationStartCallback | undefined): this {
        const value_casted = value as (OnSwiperAnimationStartCallback | undefined)
        this.getPeer()?.onAnimationStartAttribute(value_casted)
        return this
    }
    onAnimationEnd(value: OnSwiperAnimationEndCallback | undefined): this {
        const value_casted = value as (OnSwiperAnimationEndCallback | undefined)
        this.getPeer()?.onAnimationEndAttribute(value_casted)
        return this
    }
    onGestureSwipe(value: OnSwiperGestureSwipeCallback | undefined): this {
        const value_casted = value as (OnSwiperGestureSwipeCallback | undefined)
        this.getPeer()?.onGestureSwipeAttribute(value_casted)
        return this
    }
    nestedScroll(value: SwiperNestedScrollMode | undefined): this {
        const value_casted = value as (SwiperNestedScrollMode | undefined)
        this.getPeer()?.nestedScrollAttribute(value_casted)
        return this
    }
    customContentTransition(value: SwiperContentAnimatedTransition | undefined): this {
        const value_casted = value as (SwiperContentAnimatedTransition | undefined)
        this.getPeer()?.customContentTransitionAttribute(value_casted)
        return this
    }
    onContentDidScroll(value: ContentDidScrollCallback | undefined): this {
        const value_casted = value as (ContentDidScrollCallback | undefined)
        this.getPeer()?.onContentDidScrollAttribute(value_casted)
        return this
    }
    indicatorInteractive(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.indicatorInteractiveAttribute(value_casted)
        return this
    }
    pageFlipMode(value: PageFlipMode | undefined): this {
        const value_casted = value as (PageFlipMode | undefined)
        this.getPeer()?.pageFlipModeAttribute(value_casted)
        return this
    }
    onContentWillScroll(value: ContentWillScrollCallback | undefined): this {
        const value_casted = value as (ContentWillScrollCallback | undefined)
        this.getPeer()?.onContentWillScrollAttribute(value_casted)
        return this
    }
    displayArrow(value: ArrowStyle | boolean | undefined, isHoverShow?: boolean): this {
        const value_casted = value as (ArrowStyle | boolean | undefined)
        const isHoverShow_casted = isHoverShow as (boolean)
        this.getPeer()?.displayArrowAttribute(value_casted, isHoverShow_casted)
        return this
    }
    displayCount(value: number | string | SwiperAutoFill | undefined, swipeByGroup?: boolean): this {
        const value_casted = value as (number | string | SwiperAutoFill | undefined)
        const swipeByGroup_casted = swipeByGroup as (boolean)
        this.getPeer()?.displayCountAttribute(value_casted, swipeByGroup_casted)
        return this
    }
    prevMargin(value: Length | undefined, ignoreBlank?: boolean): this {
        const value_casted = value as (Length | undefined)
        const ignoreBlank_casted = ignoreBlank as (boolean)
        this.getPeer()?.prevMarginAttribute(value_casted, ignoreBlank_casted)
        return this
    }
    nextMargin(value: Length | undefined, ignoreBlank?: boolean): this {
        const value_casted = value as (Length | undefined)
        const ignoreBlank_casted = ignoreBlank as (boolean)
        this.getPeer()?.nextMarginAttribute(value_casted, ignoreBlank_casted)
        return this
    }
    _onChangeEvent_index(callback: ((selected: number | undefined) => void)): void {
        const callback_casted = callback as (((selected: number | undefined) => void))
        this.getPeer()?._onChangeEvent_indexAttribute(callback_casted)
        return
    }
}
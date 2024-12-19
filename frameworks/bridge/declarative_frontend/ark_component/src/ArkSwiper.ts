/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

/// <reference path='./import.ts' />
class ArkSwiperComponent extends ArkComponent implements SwiperAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  initialize(value: Object[]): SwiperAttribute {
    if (value[0] !== undefined) {
      modifierWithKey(this._modifiersWithKeys, SwiperInitializeModifier.identity, SwiperInitializeModifier, value[0]);
    }
    return this;
  }
  index(value: number): this {
    modifierWithKey(this._modifiersWithKeys, SwiperIndexModifier.identity, SwiperIndexModifier, value);
    return this;
  }
  autoPlay(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, SwiperAutoPlayModifier.identity, SwiperAutoPlayModifier, value);
    return this;
  }
  interval(value: number): this {
    modifierWithKey(this._modifiersWithKeys, SwiperIntervalModifier.identity, SwiperIntervalModifier, value);
    return this;
  }

  indicator(value: boolean | DotIndicator | DigitIndicator): this {
    modifierWithKey(this._modifiersWithKeys, SwiperIndicatorModifier.identity, SwiperIndicatorModifier, value);
    return this;
  }

  displayArrow(value: boolean | ArrowStyle, isHoverShow?: boolean | undefined): this {
    let arkDisplayArrow = new ArkDisplayArrow();
    arkDisplayArrow.value = value;
    arkDisplayArrow.isHoverShow = isHoverShow;
    modifierWithKey(
      this._modifiersWithKeys,
      SwiperDisplayArrowModifier.identity,
      SwiperDisplayArrowModifier,
      arkDisplayArrow
    );
    return this;
  }
  loop(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, SwiperLoopModifier.identity, SwiperLoopModifier, value);
    return this;
  }
  duration(value: number): this {
    modifierWithKey(this._modifiersWithKeys, SwiperDurationModifier.identity, SwiperDurationModifier, value);
    return this;
  }
  vertical(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, SwiperVerticalModifier.identity, SwiperVerticalModifier, value);
    return this;
  }
  itemSpace(value: string | number): this {
    modifierWithKey(this._modifiersWithKeys, SwiperItemSpaceModifier.identity, SwiperItemSpaceModifier, value);
    return this;
  }
  displayMode(value: SwiperDisplayMode): this {
    modifierWithKey(this._modifiersWithKeys, SwiperDisplayModeModifier.identity, SwiperDisplayModeModifier, value);
    return this;
  }
  cachedCount(value: number): this {
    modifierWithKey(this._modifiersWithKeys, SwiperCachedCountModifier.identity, SwiperCachedCountModifier, value);
    return this;
  }
  displayCount(value: string | number | SwiperAutoFill, swipeByGroup?: boolean | undefined): this {
    let arkDisplayCount = new ArkDisplayCount();
    arkDisplayCount.value = value;
    arkDisplayCount.swipeByGroup = swipeByGroup;
    modifierWithKey(
      this._modifiersWithKeys,
      SwiperDisplayCountModifier.identity,
      SwiperDisplayCountModifier,
      arkDisplayCount
    );
    return this;
  }
  effectMode(value: EdgeEffect): this {
    modifierWithKey(this._modifiersWithKeys, SwiperEffectModeModifier.identity, SwiperEffectModeModifier, value);
    return this;
  }
  disableSwipe(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, SwiperDisableSwipeModifier.identity, SwiperDisableSwipeModifier, value);
    return this;
  }

  curve(value: string | Curve | ICurve): this {
    modifierWithKey(this._modifiersWithKeys, SwiperCurveModifier.identity, SwiperCurveModifier, value);
    return this;
  }
  onChange(event: (index: number) => void): this {
    modifierWithKey(this._modifiersWithKeys, SwiperOnChangeModifier.identity, SwiperOnChangeModifier, event);
    return this;
  }
  indicatorStyle(value?: IndicatorStyle | undefined): this {
    throw new Error('Method not implemented.');
  }
  prevMargin(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, SwiperPrevMarginModifier.identity, SwiperPrevMarginModifier, value);
    return this;
  }
  nextMargin(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, SwiperNextMarginModifier.identity, SwiperNextMarginModifier, value);
    return this;
  }
  enabled(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, SwiperEnabledModifier.identity, SwiperEnabledModifier, value);
    return this;
  }
  onAnimationStart(event: (index: number, targetIndex: number, extraInfo: SwiperAnimationEvent) => void): this {
    modifierWithKey(this._modifiersWithKeys, SwiperOnAnimationStartModifier.identity, SwiperOnAnimationStartModifier, event);
    return this;
  }
  onAnimationEnd(event: (index: number, extraInfo: SwiperAnimationEvent) => void): this {
    modifierWithKey(this._modifiersWithKeys, SwiperOnAnimationEndModifier.identity, SwiperOnAnimationEndModifier, event);
    return this;
  }
  onGestureSwipe(event: (index: number, extraInfo: SwiperAnimationEvent) => void): this {
    modifierWithKey(this._modifiersWithKeys, SwiperOnGestureSwipeModifier.identity, SwiperOnGestureSwipeModifier, event);
    return this;
  }
  nestedScroll(value: SwiperNestedScrollMode): this {
    modifierWithKey(this._modifiersWithKeys, SwiperNestedScrollModifier.identity, SwiperNestedScrollModifier, value);
    return this;
  }
  indicatorInteractive(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, SwiperIndicatorInteractiveModifier.identity, SwiperIndicatorInteractiveModifier, value);
    return this;
  }
  customContentTransition(transition: SwiperContentAnimatedTransition): this {
    modifierWithKey(this._modifiersWithKeys, SwiperCustomContentTransitionModifier.identity, SwiperCustomContentTransitionModifier, transition);
    return this;
  }
  onContentDidScroll(handler: ContentDidScrollCallback): this {
    modifierWithKey(this._modifiersWithKeys, SwiperOnContentDidScrollModifier.identity, SwiperOnContentDidScrollModifier, handler);
    return this;
  }
  pageFlipMode(value: PageFlipMode): this {
    modifierWithKey(this._modifiersWithKeys, SwiperPageFlipModeModifier.identity, SwiperPageFlipModeModifier, value);
    return this;
  }
}
class SwiperInitializeModifier extends ModifierWithKey<SwiperController> {
  static identity: Symbol = Symbol('swiperInitialize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().swiper.resetSwiperInitialize(node);
    } else {
      getUINativeModule().swiper.setSwiperInitialize(node, this.value);
    }
  }
}
class SwiperNextMarginModifier extends ModifierWithKey<Length> {
  static identity: Symbol = Symbol('swiperNextMargin');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().swiper.resetSwiperNextMargin(node);
    } else {
      getUINativeModule().swiper.setSwiperNextMargin(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class SwiperPrevMarginModifier extends ModifierWithKey<Length> {
  static identity: Symbol = Symbol('swiperPrevMargin');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().swiper.resetSwiperPrevMargin(node);
    } else {
      getUINativeModule().swiper.setSwiperPrevMargin(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SwiperDisplayCountModifier extends ModifierWithKey<ArkDisplayCount> {
  static identity: Symbol = Symbol('swiperDisplayCount');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().swiper.resetSwiperSwipeByGroup(node);
      getUINativeModule().swiper.resetSwiperDisplayCount(node);
    } else {
      if (!isNull(this.value) && !isUndefined(this.value)) {
        let swipeByGroup;
        if (typeof this.value.swipeByGroup === 'boolean') {
          swipeByGroup = this.value.swipeByGroup;
        }

        getUINativeModule().swiper.setSwiperSwipeByGroup(node, swipeByGroup);

        if (typeof this.value.value === 'object') {
          let minSize = (this.value.value as SwiperAutoFill).minSize.toString();
          getUINativeModule().swiper.setSwiperDisplayCount(node, minSize, typeof this.value.value);
        } else {
          getUINativeModule().swiper.setSwiperDisplayCount(node, this.value.value, typeof this.value.value);
        }
      } else {
        getUINativeModule().swiper.resetSwiperSwipeByGroup(node);
        getUINativeModule().swiper.resetSwiperDisplayCount(node);
      }
    }
  }
  checkObjectDiff(): boolean {
    if (
      this.stageValue.swipeByGroup !== this.value.swipeByGroup ||
      typeof this.stageValue.value !== typeof this.value.value
    ) {
      return true;
    } else if (
      typeof this.stageValue.value === 'object' &&
      typeof this.value.value === 'object'
    ) {
      return (this.stageValue.value as SwiperAutoFill).minSize !== (this.value.value as SwiperAutoFill).minSize;
    } else {
      return !isBaseOrResourceEqual(this.stageValue.value, this.value.value);
    }
  }
}

class SwiperDisplayArrowModifier extends ModifierWithKey<ArkDisplayArrow> {
  static identity: Symbol = Symbol('swiperDisplayArrow');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().swiper.resetSwiperDisplayArrow(node);
    } else {
      if (!isNull(this.value.value) && !isUndefined(this.value.value) && typeof this.value === 'object') {
        let displayArrowValue = 3;
        let showBackground;
        let isSidebarMiddle;
        let backgroundSize;
        let backgroundColor;
        let arrowSize;
        let arrowColor;
        if (typeof this.value.value === 'boolean') {
          if (this.value.value) {
            displayArrowValue = 1;
          } else {
            displayArrowValue = 0;
          }
        } else if (typeof this.value.value === 'object') {
          displayArrowValue = 2;
          showBackground = this.value.value.showBackground;
          isSidebarMiddle = this.value.value.isSidebarMiddle;
          backgroundSize = this.value.value.backgroundSize;
          backgroundColor = this.value.value.backgroundColor;
          arrowSize = this.value.value.arrowSize;
          arrowColor = this.value.value.arrowColor;
        }
        let isHoverShow;
        if (typeof this.value.isHoverShow === 'boolean') {
          isHoverShow = this.value.isHoverShow;
        }
        getUINativeModule().swiper.setSwiperDisplayArrow(
          node,
          displayArrowValue,
          showBackground,
          isSidebarMiddle,
          backgroundSize,
          backgroundColor,
          arrowSize,
          arrowColor,
          isHoverShow
        );
      } else {
        getUINativeModule().swiper.resetSwiperDisplayArrow(node);
      }
    }
  }
  checkObjectDiff(): boolean {
    if (
      this.stageValue.isHoverShow !== this.value.isHoverShow ||
      typeof this.stageValue.value !== typeof this.value.value
    ) {
      return true;
    }
    if (
      typeof this.stageValue.value === 'boolean' &&
      typeof this.value.value === 'boolean' &&
      this.stageValue.value !== this.value.value
    ) {
      return true;
    } else if (typeof this.stageValue.value === 'object' && typeof this.value.value === 'object') {
      return (
        !isBaseOrResourceEqual(
          (this.stageValue.value as ArrowStyle).showBackground,
          (this.value.value as ArrowStyle).showBackground
        ) ||
        !isBaseOrResourceEqual(
          (this.stageValue.value as ArrowStyle).isSidebarMiddle,
          (this.value.value as ArrowStyle).isSidebarMiddle
        ) ||
        !isBaseOrResourceEqual(
          (this.stageValue.value as ArrowStyle).backgroundSize,
          (this.value.value as ArrowStyle).backgroundSize
        ) ||
        !isBaseOrResourceEqual(
          (this.stageValue.value as ArrowStyle).backgroundColor,
          (this.value.value as ArrowStyle).backgroundColor
        ) ||
        !isBaseOrResourceEqual(
          (this.stageValue.value as ArrowStyle).arrowSize,
          (this.value.value as ArrowStyle).arrowSize
        ) ||
        !isBaseOrResourceEqual(
          (this.stageValue.value as ArrowStyle).arrowColor,
          (this.value.value as ArrowStyle).arrowColor
        )
      );
    } else {
      return true;
    }
  }
}

class SwiperIndicatorModifier extends ModifierWithKey<boolean | DotIndicator | DigitIndicator> {
  static identity: Symbol = Symbol('swiperIndicator');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().swiper.resetSwiperIndicator(node);
    } else {
      let left;
      let top;
      let right;
      let bottom;
      let itemWidth;
      let itemHeight;
      let selectedItemWidth;
      let selectedItemHeight;
      let mask;
      let color;
      let selectedColor;
      let maxDisplayCount;
      let fontColor;
      let selectedFontColor;
      let digitFontSize;
      let digitFontWeight;
      let selectedDigitFontSize;
      let selectedDigitFontWeight;
      if (typeof this.value === 'boolean') {
        getUINativeModule().swiper.setSwiperIndicator(node, 'boolean', this.value);
      } else if (typeof this.value === 'object' && (this.value as ArkDotIndicator).type === 'DotIndicator') {
        left = (this.value as ArkDotIndicator).leftValue;
        top = (this.value as ArkDotIndicator).topValue;
        right = (this.value as ArkDotIndicator).rightValue;
        bottom = (this.value as ArkDotIndicator).bottomValue;
        itemWidth = (this.value as ArkDotIndicator).itemWidthValue;
        itemHeight = (this.value as ArkDotIndicator).itemHeightValue;
        selectedItemWidth = (this.value as ArkDotIndicator).selectedItemWidthValue;
        selectedItemHeight = (this.value as ArkDotIndicator).selectedItemHeightValue;
        mask = (this.value as ArkDotIndicator).maskValue;
        color = (this.value as ArkDotIndicator).colorValue;
        selectedColor = (this.value as ArkDotIndicator).selectedColorValue;
        maxDisplayCount = (this.value as ArkDotIndicator).maxDisplayCountValue;
        getUINativeModule().swiper.setSwiperIndicator(
          node,
          'ArkDotIndicator',
          itemWidth,
          itemHeight,
          selectedItemWidth,
          selectedItemHeight,
          mask,
          color,
          selectedColor,
          maxDisplayCount,
          left,
          top,
          right,
          bottom
        );
      } else if (typeof this.value === 'object' && (this.value as ArkDigitIndicator).type === 'DigitIndicator') {
        left = (this.value as ArkDigitIndicator).leftValue;
        top = (this.value as ArkDigitIndicator).topValue;
        right = (this.value as ArkDigitIndicator).rightValue;
        bottom = (this.value as ArkDigitIndicator).bottomValue;
        fontColor = (this.value as ArkDigitIndicator).fontColorValue;
        selectedFontColor = (this.value as ArkDigitIndicator).selectedFontColorValue;
        let arkDigitFont = new ArkDigitFont();
        if (typeof (this.value as ArkDigitIndicator).digitFontValue === 'object') {
          digitFontSize = ((this.value as ArkDigitIndicator).digitFontValue as Font).size;
          digitFontWeight = arkDigitFont.parseFontWeight(
            ((this.value as ArkDigitIndicator).digitFontValue as Font).weight
          );
        }
        if (typeof (this.value as ArkDigitIndicator).selectedDigitFontValue === 'object') {
          selectedDigitFontSize = ((this.value as ArkDigitIndicator).selectedDigitFontValue as Font).size;
          selectedDigitFontWeight = arkDigitFont.parseFontWeight(
            ((this.value as ArkDigitIndicator).selectedDigitFontValue as Font).weight
          );
        }
        getUINativeModule().swiper.setSwiperIndicator(
          node,
          'ArkDigitIndicator',
          fontColor,
          selectedFontColor,
          digitFontSize,
          digitFontWeight,
          selectedDigitFontSize,
          selectedDigitFontWeight,
          left,
          top,
          right,
          bottom
        );
      } else {
        getUINativeModule().swiper.setSwiperIndicator(node, 'boolean', true);
      }
    }
  }
  checkObjectDiff(): boolean {
    if (typeof this.stageValue !== typeof this.value) {
      return true;
    }
    if (typeof this.stageValue === 'boolean' && typeof this.value === 'boolean') {
      return this.stageValue !== this.value;
    }
    if (this.stageValue instanceof ArkDotIndicator && this.value instanceof ArkDotIndicator) {
      return (
        !isBaseOrResourceEqual(
          (this.stageValue as ArkDotIndicator).itemWidthValue,
          (this.value as ArkDotIndicator).itemWidthValue
        ) ||
        !isBaseOrResourceEqual(
          (this.stageValue as ArkDotIndicator).itemHeightValue,
          (this.value as ArkDotIndicator).itemHeightValue
        ) ||
        !isBaseOrResourceEqual(
          (this.stageValue as ArkDotIndicator).selectedItemWidthValue,
          (this.value as ArkDotIndicator).selectedItemWidthValue
        ) ||
        !isBaseOrResourceEqual(
          (this.stageValue as ArkDotIndicator).selectedItemHeightValue,
          (this.value as ArkDotIndicator).selectedItemHeightValue
        ) ||
        !isBaseOrResourceEqual(
          (this.stageValue as ArkDotIndicator).maskValue,
          (this.value as ArkDotIndicator).maskValue
        ) ||
        !isBaseOrResourceEqual(
          (this.stageValue as ArkDotIndicator).colorValue,
          (this.value as ArkDotIndicator).colorValue
        ) ||
        !isBaseOrResourceEqual(
          (this.stageValue as ArkDotIndicator).selectedColorValue,
          (this.value as ArkDotIndicator).selectedColorValue
        ) ||
        !isBaseOrResourceEqual(
          (this.stageValue as ArkDotIndicator).maxDisplayCountValue,
          (this.value as ArkDotIndicator).maxDisplayCountValue
        )
      );
    } else if (this.stageValue instanceof ArkDigitIndicator && this.value instanceof ArkDigitIndicator) {
      return (
        !isBaseOrResourceEqual(
          (this.stageValue as ArkDigitIndicator).fontColorValue,
          (this.value as ArkDigitIndicator).fontColorValue
        ) ||
        !isBaseOrResourceEqual(
          (this.stageValue as ArkDigitIndicator).selectedFontColorValue,
          (this.value as ArkDigitIndicator).selectedFontColorValue
        ) ||
        !isBaseOrResourceEqual(
          ((this.stageValue as ArkDigitIndicator).digitFontValue as Font).size,
          ((this.value as ArkDigitIndicator).digitFontValue as Font).size
        ) ||
        !isBaseOrResourceEqual(
          ((this.stageValue as ArkDigitIndicator).digitFontValue as Font).weight,
          ((this.value as ArkDigitIndicator).digitFontValue as Font).weight
        ) ||
        !isBaseOrResourceEqual(
          ((this.stageValue as ArkDigitIndicator).selectedDigitFontValue as Font).size,
          ((this.value as ArkDigitIndicator).selectedDigitFontValue as Font).size
        ) ||
        !isBaseOrResourceEqual(
          ((this.stageValue as ArkDigitIndicator).selectedDigitFontValue as Font).weight,
          ((this.value as ArkDigitIndicator).selectedDigitFontValue as Font).weight
        )
      );
    } else {
      return true;
    }
  }
}

class SwiperCurveModifier extends ModifierWithKey<string | Curve | ICurve> {
  static identity: Symbol = Symbol('swiperCurve');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().swiper.resetSwiperCurve(node);
    } else {
      const curveMap = {
        [0]: 'linear',
        [1]: 'ease',
        [2]: 'ease-in',
        [3]: 'ease-out',
        [4]: 'ease-in-out',
        [5]: 'fast-out-slow-in',
        [6]: 'linear-out-slow-in',
        [7]: 'fast-out-linear-in',
        [8]: 'extreme-deceleration',
        [9]: 'sharp',
        [10]: 'rhythm',
        [11]: 'smooth',
        [12]: 'friction'
      };
      if (typeof this.value === 'number') {
        if (this.value in curveMap) {
          this.value = curveMap[this.value];
        } else {
          this.value = this.value.toString();
        }
      }
      getUINativeModule().swiper.setSwiperCurve(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class SwiperOnChangeModifier extends ModifierWithKey<Callback<number>> {
  constructor(value: Callback<number>) {
    super(value);
  }
  static identity: Symbol = Symbol('swiperOnChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().swiper.resetSwiperOnChange(node);
    } else {
      getUINativeModule().swiper.setSwiperOnChange(node, this.value);
    }
  }
}
class SwiperDisableSwipeModifier extends ModifierWithKey<boolean> {
  static identity: Symbol = Symbol('swiperDisableSwipe');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().swiper.resetSwiperDisableSwipe(node);
    } else {
      getUINativeModule().swiper.setSwiperDisableSwipe(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class SwiperEffectModeModifier extends ModifierWithKey<EdgeEffect> {
  static identity: Symbol = Symbol('swiperEffectMode');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().swiper.resetSwiperEffectMode(node);
    } else {
      getUINativeModule().swiper.setSwiperEffectMode(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class SwiperCachedCountModifier extends ModifierWithKey<number> {
  static identity: Symbol = Symbol('swiperCachedCount');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().swiper.resetSwiperCachedCount(node);
    } else {
      getUINativeModule().swiper.setSwiperCachedCount(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class SwiperDisplayModeModifier extends ModifierWithKey<number> {
  static identity: Symbol = Symbol('swiperDisplayMode');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().swiper.resetSwiperDisplayMode(node);
    } else {
      getUINativeModule().swiper.setSwiperDisplayMode(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class SwiperItemSpaceModifier extends ModifierWithKey<string | number> {
  static identity: Symbol = Symbol('swiperItemSpace');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().swiper.resetSwiperItemSpace(node);
    } else {
      getUINativeModule().swiper.setSwiperItemSpace(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class SwiperVerticalModifier extends ModifierWithKey<boolean> {
  static identity: Symbol = Symbol('swiperVertical');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().swiper.resetSwiperVertical(node);
    } else {
      getUINativeModule().swiper.setSwiperVertical(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class SwiperLoopModifier extends ModifierWithKey<boolean> {
  static identity: Symbol = Symbol('swiperLoop');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().swiper.resetSwiperLoop(node);
    } else {
      getUINativeModule().swiper.setSwiperLoop(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class SwiperIntervalModifier extends ModifierWithKey<number> {
  static identity: Symbol = Symbol('swiperInterval');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().swiper.resetSwiperInterval(node);
    } else {
      getUINativeModule().swiper.setSwiperInterval(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class SwiperAutoPlayModifier extends ModifierWithKey<boolean> {
  static identity: Symbol = Symbol('swiperAutoPlay');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().swiper.resetSwiperAutoPlay(node);
    } else {
      getUINativeModule().swiper.setSwiperAutoPlay(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class SwiperIndexModifier extends ModifierWithKey<number> {
  static identity: Symbol = Symbol('swiperIndex');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().swiper.resetSwiperIndex(node);
    } else {
      getUINativeModule().swiper.setSwiperIndex(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class SwiperDurationModifier extends ModifierWithKey<number> {
  static identity: Symbol = Symbol('swiperDuration');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().swiper.resetSwiperDuration(node);
    } else {
      getUINativeModule().swiper.setSwiperDuration(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SwiperEnabledModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('swiperenabled');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().swiper.resetSwiperEnabled(node);

    } else {
      getUINativeModule().swiper.setSwiperEnabled(node, this.value);
    }
  }
}

class SwiperNestedScrollModifier extends ModifierWithKey<SwiperNestedScrollMode> {
  constructor(value: SwiperNestedScrollMode) {
    super(value);
  }
  static identity: Symbol = Symbol('nestedScroll');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().swiper.resetNestedScroll(node);
    } else {
      getUINativeModule().swiper.setNestedScroll(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class SwiperOnAnimationStartModifier extends ModifierWithKey<(index: number, targetIndex: number,
    extraInfo: SwiperAnimationEvent) => void> {
  constructor(value: (index: number, targetIndex: number, extraInfo: SwiperAnimationEvent) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('swiperOnAnimationStart');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().swiper.resetSwiperOnAnimationStart(node);
    } else {
      getUINativeModule().swiper.setSwiperOnAnimationStart(node, this.value);
    }
  }
}
class SwiperOnAnimationEndModifier extends ModifierWithKey<Callback<number, SwiperAnimationEvent>> {
  constructor(value: Callback<number, SwiperAnimationEvent>) {
    super(value);
  }
  static identity: Symbol = Symbol('swiperOnAnimationEnd');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().swiper.resetSwiperOnAnimationEnd(node);
    } else {
      getUINativeModule().swiper.setSwiperOnAnimationEnd(node, this.value);
    }
  }
}
class SwiperOnGestureSwipeModifier extends ModifierWithKey<Callback<number, SwiperAnimationEvent>> {
  constructor(value: Callback<number, SwiperAnimationEvent>) {
    super(value);
  }
  static identity: Symbol = Symbol('swiperOnGestureSwipe');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().swiper.resetSwiperOnGestureSwipe(node);
    } else {
      getUINativeModule().swiper.setSwiperOnGestureSwipe(node, this.value);
    }
  }
}
class SwiperIndicatorInteractiveModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('indicatorInteractive');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().swiper.resetIndicatorInteractive(node);
    } else {
      getUINativeModule().swiper.setIndicatorInteractive(node, this.value);
    }
  }
}
class SwiperCustomContentTransitionModifier extends ModifierWithKey<SwiperContentAnimatedTransition> {
  constructor(value: SwiperContentAnimatedTransition) {
    super(value);
  }
  static identity: Symbol = Symbol('swiperCustomContentTransition');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().swiper.resetSwiperCustomContentTransition(node);
    } else {
      getUINativeModule().swiper.setSwiperCustomContentTransition(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class SwiperOnContentDidScrollModifier extends ModifierWithKey<(selectedIndex: number, index: number,
  position: number, mainAxisLength: number) => void> {
  constructor(value: (selectedIndex: number, index: number, position: number, mainAxisLength: number) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('swiperOnContentDidScroll');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().swiper.resetSwiperOnContentDidScroll(node);
    } else {
      getUINativeModule().swiper.setSwiperOnContentDidScroll(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class SwiperPageFlipModeModifier extends ModifierWithKey<PageFlipMode> {
  constructor(value: PageFlipMode) {
    super(value);
  }
  static identity: Symbol = Symbol('swiperPageFlipMode');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().swiper.resetSwiperPageFlipMode(node);
    } else {
      getUINativeModule().swiper.setSwiperPageFlipMode(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
// @ts-ignore
globalThis.Swiper.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkSwiperComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.SwiperModifier(nativePtr, classType);
  });
};

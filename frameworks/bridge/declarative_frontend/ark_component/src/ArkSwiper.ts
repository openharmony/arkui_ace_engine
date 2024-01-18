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
  constructor(nativePtr: KNode) {
    super(nativePtr);
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
  displayCount(value: string | number | SwiperAutoFill): this {
    modifierWithKey(this._modifiersWithKeys, SwiperDisplayCountModifier.identity, SwiperDisplayCountModifier, value);
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
    throw new Error('Method not implemented.');
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
    throw new Error('Method not implemented.');
  }
  onAnimationEnd(event: (index: number, extraInfo: SwiperAnimationEvent) => void): this {
    throw new Error('Method not implemented.');
  }
  onGestureSwipe(event: (index: number, extraInfo: SwiperAnimationEvent) => void): this {
    throw new Error('Method not implemented.');
  }
  nestedScroll(value: SwiperNestedScrollMode): this {
    throw new Error('Method not implemented.');
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

class SwiperDisplayCountModifier extends ModifierWithKey<string | number | SwiperAutoFill> {
  static identity: Symbol = Symbol('swiperDisplayCount');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().swiper.resetSwiperDisplayCount(node);
    } else {
      if (isNull(this.value) || isUndefined(this.value)) {
        getUINativeModule().swiper.resetSwiperDisplayCount(node);
      } else if (typeof this.value === 'object') {
        let minSize = (this.value as SwiperAutoFill).minSize.toString();
        getUINativeModule().swiper.setSwiperDisplayCount(node, minSize, typeof this.value);
      } else {
        getUINativeModule().swiper.setSwiperDisplayCount(node, this.value, typeof this.value);
      }
    }
  }
  checkObjectDiff(): boolean {
    if (typeof this.stageValue !== typeof this.value) {
      return true;
    } else if (typeof this.stageValue === 'object' && typeof this.stageValue === 'object') {
      return (this.stageValue as SwiperAutoFill).minSize !== (this.value as SwiperAutoFill).minSize;
    } else {
      return !isBaseOrResourceEqual(this.stageValue, this.value);
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

// @ts-ignore
globalThis.Swiper.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkSwiperComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

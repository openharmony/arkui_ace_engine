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
    if (typeof value === 'number') {
      modifier(this._modifiers, SwiperIndexModifier, value);
    } else {
      modifier(this._modifiers, SwiperIndexModifier, undefined);
    }
    return this;
  }
  autoPlay(value: boolean): this {
    if (typeof value === 'boolean') {
      modifier(this._modifiers, SwiperAutoPlayModifier, value);
    } else {
      modifier(this._modifiers, SwiperAutoPlayModifier, undefined);
    }
    return this;
  }
  interval(value: number): this {
    if (typeof value === 'number') {
      modifier(this._modifiers, SwiperIntervalModifier, value);
    } else {
      modifier(this._modifiers, SwiperIntervalModifier, undefined);
    }
    return this;
  }

  indicator(value: boolean | DotIndicator | DigitIndicator): this {
    if (typeof value === 'boolean' || typeof value === 'object') {
      modifierWithKey(this._modifiersWithKeys, SwiperIndicatorModifier.identity, SwiperIndicatorModifier, value);
    } else {
      modifierWithKey(this._modifiersWithKeys, SwiperIndicatorModifier.identity, SwiperIndicatorModifier, undefined);
    }
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
    if (typeof value === 'boolean') {
      modifier(this._modifiers, SwiperLoopModifier, value);
    } else {
      modifier(this._modifiers, SwiperLoopModifier, undefined);
    }
    return this;
  }
  duration(value: number): this {
    if (typeof value === 'number') {
      modifier(this._modifiers, SwiperDurationModifier, value);
    } else {
      modifier(this._modifiers, SwiperDurationModifier, undefined);
    }
    return this;
  }
  vertical(value: boolean): this {
    if (typeof value === 'boolean') {
      modifier(this._modifiers, SwiperVerticalModifier, value);
    } else {
      modifier(this._modifiers, SwiperVerticalModifier, undefined);
    }
    return this;
  }
  itemSpace(value: string | number): this {
    if (typeof value === 'number' || typeof value === 'string') {
      modifier(this._modifiers, SwiperItemSpaceModifier, value);
    } else {
      modifier(this._modifiers, SwiperItemSpaceModifier, undefined);
    }
    return this;
  }
  displayMode(value: SwiperDisplayMode): this {
    if (typeof value === 'number') {
      modifier(this._modifiers, SwiperDisplayModeModifier, value);
    } else {
      modifier(this._modifiers, SwiperDisplayModeModifier, undefined);
    }
    return this;
  }
  cachedCount(value: number): this {
    if (typeof value === 'number') {
      modifier(this._modifiers, SwiperCachedCountModifier, value);
    } else {
      modifier(this._modifiers, SwiperCachedCountModifier, undefined);
    }
    return this;
  }
  displayCount(value: string | number | SwiperAutoFill): this {
    if (typeof value === 'number' || typeof value === 'string' || typeof value === 'object') {
      modifierWithKey(this._modifiersWithKeys, SwiperDisplayCountModifier.identity, SwiperDisplayCountModifier, value);
    } else {
      modifierWithKey(
        this._modifiersWithKeys,
        SwiperDisplayCountModifier.identity,
        SwiperDisplayCountModifier,
        undefined
      );
    }
    return this;
  }
  effectMode(value: EdgeEffect): this {
    if (typeof value === 'number') {
      modifier(this._modifiers, SwiperEffectModeModifier, value);
    } else {
      modifier(this._modifiers, SwiperEffectModeModifier, undefined);
    }
    return this;
  }
  disableSwipe(value: boolean): this {
    if (typeof value === 'boolean') {
      modifier(this._modifiers, SwiperDisableSwipeModifier, value);
    } else {
      modifier(this._modifiers, SwiperDisableSwipeModifier, undefined);
    }
    return this;
  }

  curve(value: string | Curve | ICurve): this {
    if (typeof value === 'number' || typeof value === 'string') {
      modifier(this._modifiers, SwiperCurveModifier, value);
    } else {
      modifier(this._modifiers, SwiperCurveModifier, undefined);
    }
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
  monopolizeEvents(monopolize: boolean): this {
    throw new Error('Method not implemented.');
  }
}
class SwiperNextMarginModifier extends ModifierWithKey<Length> {
  static identity: Symbol = Symbol('swiperNextMargin');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().swiper.resetSwiperNextMargin(node);
    } else {
      GetUINativeModule().swiper.setSwiperNextMargin(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else {
      return true;
    }
  }
}
class SwiperPrevMarginModifier extends ModifierWithKey<Length> {
  static identity: Symbol = Symbol('swiperPrevMargin');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().swiper.resetSwiperPrevMargin(node);
    } else {
      GetUINativeModule().swiper.setSwiperPrevMargin(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else {
      return true;
    }
  }
}

class SwiperDisplayCountModifier extends ModifierWithKey<string | number | SwiperAutoFill> {
  static identity: Symbol = Symbol('swiperDisplayCount');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().swiper.resetSwiperDisplayCount(node);
    } else {
      if (isNull(this.value)) {
        GetUINativeModule().swiper.resetSwiperDisplayCount(node);
      } else if (typeof this.value === 'object') {
        let minSize = (this.value as SwiperAutoFill).minSize.toString();
        GetUINativeModule().swiper.setSwiperDisplayCount(node, minSize, typeof this.value);
      } else {
        GetUINativeModule().swiper.setSwiperDisplayCount(node, this.value, typeof this.value);
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
      GetUINativeModule().swiper.resetSwiperDisplayArrow(node);
    } else {
      if (!isNull(this.value.value) && typeof this.value === 'object') {
        let displayArrowValue = 3;
        let showBackground = undefined;
        let isSidebarMiddle = undefined;
        let backgroundSize = undefined;
        let backgroundColor = undefined;
        let arrowSize = undefined;
        let arrowColor = undefined;
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
        let isHoverShow = undefined;
        if (typeof this.value.isHoverShow === 'boolean') {
          isHoverShow = this.value.isHoverShow;
        }
        GetUINativeModule().swiper.setSwiperDisplayArrow(
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
        GetUINativeModule().swiper.resetSwiperDisplayArrow(node);
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
      GetUINativeModule().swiper.resetSwiperIndicator(node);
    } else {
      let left = undefined;
      let top = undefined;
      let right = undefined;
      let bottom = undefined;
      let itemWidth = undefined;
      let itemHeight = undefined;
      let selectedItemWidth = undefined;
      let selectedItemHeight = undefined;
      let mask = undefined;
      let color = undefined;
      let selectedColor = undefined;
      let fontColor = undefined;
      let selectedFontColor = undefined;
      let digitFontSize = undefined;
      let digitFontWeight = undefined;
      let selectedDigitFontSize = undefined;
      let selectedDigitFontWeight = undefined;
      if (typeof this.value === 'boolean') {
        GetUINativeModule().swiper.setSwiperIndicator(node, 'boolean', this.value);
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
        GetUINativeModule().swiper.setSwiperIndicator(
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
        GetUINativeModule().swiper.setSwiperIndicator(
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
        GetUINativeModule().swiper.setSwiperIndicator(node, 'boolean', true);
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
        !isBaseOrResourceEqual((this.stageValue as ArkDotIndicator).itemWidth, (this.value as ArkDotIndicator).itemWidth) ||
        !isBaseOrResourceEqual((this.stageValue as ArkDotIndicator).itemHeight, (this.value as ArkDotIndicator).itemHeight) ||
        !isBaseOrResourceEqual(
          (this.stageValue as ArkDotIndicator).selectedItemWidth,
          (this.value as ArkDotIndicator).selectedItemWidth
        ) ||
        !isBaseOrResourceEqual(
          (this.stageValue as ArkDotIndicator).selectedItemHeight,
          (this.value as ArkDotIndicator).selectedItemHeight
        ) ||
        !isBaseOrResourceEqual((this.stageValue as ArkDotIndicator).mask, (this.value as ArkDotIndicator).mask) ||
        !isBaseOrResourceEqual((this.stageValue as ArkDotIndicator).color, (this.value as ArkDotIndicator).color) ||
        !isBaseOrResourceEqual(
          (this.stageValue as ArkDotIndicator).selectedColor,
          (this.value as ArkDotIndicator).selectedColor
        )
      );
    } else if (this.stageValue instanceof ArkDigitIndicator && this.value instanceof ArkDigitIndicator) {
      return (
        !isBaseOrResourceEqual(
          (this.stageValue as ArkDigitIndicator).fontColor,
          (this.value as ArkDigitIndicator).fontColor
        ) ||
        !isBaseOrResourceEqual(
          (this.stageValue as ArkDigitIndicator).selectedFontColor,
          (this.value as ArkDigitIndicator).selectedFontColor
        ) ||
        !isBaseOrResourceEqual(
          ((this.stageValue as ArkDigitIndicator).digitFont as Font).size,
          ((this.value as ArkDigitIndicator).digitFont as Font).size
        ) ||
        !isBaseOrResourceEqual(
          ((this.stageValue as ArkDigitIndicator).digitFont as Font).weight,
          ((this.value as ArkDigitIndicator).digitFont as Font).weight
        ) ||
        !isBaseOrResourceEqual(
          ((this.stageValue as ArkDigitIndicator).selectedDigitFont as Font).size,
          ((this.value as ArkDigitIndicator).selectedDigitFont as Font).size
        ) ||
        !isBaseOrResourceEqual(
          ((this.stageValue as ArkDigitIndicator).selectedDigitFont as Font).weight,
          ((this.value as ArkDigitIndicator).selectedDigitFont as Font).weight
        )
      );
    } else {
      return true;
    }
  }
}

class SwiperCurveModifier extends Modifier<number | string> {
  static identity: Symbol = Symbol('swiperCurve');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().swiper.resetSwiperCurve(node);
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
      GetUINativeModule().swiper.setSwiperCurve(node, this.value);
    }
  }
}
class SwiperDisableSwipeModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('swiperDisableSwipe');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().swiper.resetSwiperDisableSwipe(node);
    } else {
      GetUINativeModule().swiper.setSwiperDisableSwipe(node, this.value);
    }
  }
}
class SwiperEffectModeModifier extends Modifier<number> {
  static identity: Symbol = Symbol('swiperEffectMode');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().swiper.resetSwiperEffectMode(node);
    } else {
      GetUINativeModule().swiper.setSwiperEffectMode(node, this.value);
    }
  }
}
class SwiperCachedCountModifier extends Modifier<number> {
  static identity: Symbol = Symbol('swiperCachedCount');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().swiper.resetSwiperCachedCount(node);
    } else {
      GetUINativeModule().swiper.setSwiperCachedCount(node, this.value);
    }
  }
}
class SwiperDisplayModeModifier extends Modifier<number> {
  static identity: Symbol = Symbol('swiperDisplayMode');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().swiper.resetSwiperDisplayMode(node);
    } else {
      GetUINativeModule().swiper.setSwiperDisplayMode(node, this.value);
    }
  }
}
class SwiperItemSpaceModifier extends Modifier<string | number> {
  static identity: Symbol = Symbol('swiperItemSpace');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().swiper.resetSwiperItemSpace(node);
    } else {
      GetUINativeModule().swiper.setSwiperItemSpace(node, this.value);
    }
  }
}
class SwiperVerticalModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('swiperVertical');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().swiper.resetSwiperVertical(node);
    } else {
      GetUINativeModule().swiper.setSwiperVertical(node, this.value);
    }
  }
}
class SwiperLoopModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('swiperLoop');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().swiper.resetSwiperLoop(node);
    } else {
      GetUINativeModule().swiper.setSwiperLoop(node, this.value);
    }
  }
}
class SwiperIntervalModifier extends Modifier<number> {
  static identity: Symbol = Symbol('swiperInterval');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().swiper.resetSwiperInterval(node);
    } else {
      GetUINativeModule().swiper.setSwiperInterval(node, this.value);
    }
  }
}
class SwiperAutoPlayModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('swiperAutoPlay');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().swiper.resetSwiperAutoPlay(node);
    } else {
      GetUINativeModule().swiper.setSwiperAutoPlay(node, this.value);
    }
  }
}
class SwiperIndexModifier extends Modifier<number> {
  static identity: Symbol = Symbol('swiperIndex');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().swiper.resetSwiperIndex(node);
    } else {
      GetUINativeModule().swiper.setSwiperIndex(node, this.value);
    }
  }
}
class SwiperDurationModifier extends Modifier<number> {
  static identity: Symbol = Symbol('swiperDuration');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().swiper.resetSwiperDuration(node);
    } else {
      GetUINativeModule().swiper.setSwiperDuration(node, this.value);
    }
  }
}
// @ts-ignore
globalThis.Swiper.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkSwiperComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

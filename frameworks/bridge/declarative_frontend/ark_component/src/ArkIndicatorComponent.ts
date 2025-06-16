/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

class IndicatorComponentInitialIndexModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('indicatorComponentInitialIndex');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().indicatorComponent.resetInitialIndex(node);
    } else {
      getUINativeModule().indicatorComponent.setInitialIndex(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class IndicatorComponentCountModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('indicatorComponentCount');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().indicatorComponent.resetCount(node);
    } else {
      getUINativeModule().indicatorComponent.setCount(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class IndicatorComponentStyleModifier extends ModifierWithKey<DotIndicator | DigitIndicator> {
  constructor(value: DotIndicator | DigitIndicator) {
    super(value);
  }
  static identity: Symbol = Symbol('indicatorComponentStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().indicatorComponent.resetStyle(node);
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
      if (typeof this.value === 'object' && (this.value as ArkDigitIndicator).type === 'DigitIndicator') {
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
        getUINativeModule().indicatorComponent.setStyle(
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
        getUINativeModule().indicatorComponent.setStyle(
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
      }
    }
  }
  checkObjectDiff(): boolean {
    if (typeof this.stageValue !== typeof this.value) {
      return true;
    }
    if (this.stageValue instanceof ArkDigitIndicator && this.value instanceof ArkDigitIndicator) {
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
    } else if (this.stageValue instanceof ArkDotIndicator && this.value instanceof ArkDotIndicator) {
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
    } else {
      return true;
    }
  }
}

class IndicatorComponentLoopModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('indicatorComponentLoop');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().indicatorComponent.resetLoop(node);
    } else {
      getUINativeModule().indicatorComponent.setLoop(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class IndicatorComponentVerticalModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('indicatorComponentVertical');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().indicatorComponent.resetVertical(node);
    } else {
      getUINativeModule().indicatorComponent.setVertical(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class IndicatorComponentOnChangeModifier extends ModifierWithKey<Callback<number>> {
  constructor(value: Callback<number>) {
    super(value);
  }
  static identity: Symbol = Symbol('indicatorComponentOnChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().indicatorComponent.resetOnChange(node);
    } else {
      getUINativeModule().indicatorComponent.setOnChange(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class ArkIndicatorComponentComponent extends ArkComponent implements CommonMethod<IndicatorComponentAttribute> {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }

  initialIndex(value: number): IndicatorComponentAttribute {
    modifierWithKey(this._modifiersWithKeys, IndicatorComponentInitialIndexModifier.identity, IndicatorComponentInitialIndexModifier, value);
    return this;
  }

  count(value: number): IndicatorComponentAttribute {
    modifierWithKey(this._modifiersWithKeys, IndicatorComponentCountModifier.identity, IndicatorComponentCountModifier, value);
    return this;
  }

  style(value: DotIndicator | DigitIndicator): IndicatorComponentAttribute {
    modifierWithKey(this._modifiersWithKeys, IndicatorComponentStyleModifier.identity, IndicatorComponentStyleModifier, value);
    return this;
  }

  loop(value: boolean): IndicatorComponentAttribute {
    modifierWithKey(this._modifiersWithKeys, IndicatorComponentLoopModifier.identity, IndicatorComponentLoopModifier, value);
    return this;
  }

  vertical(value: boolean): IndicatorComponentAttribute {
    modifierWithKey(this._modifiersWithKeys, IndicatorComponentVerticalModifier.identity, IndicatorComponentVerticalModifier, value);
    return this;
  }

  onChange(value: Callback<number>): IndicatorComponentAttribute {
    modifierWithKey(this._modifiersWithKeys, IndicatorComponentOnChangeModifier.identity, IndicatorComponentOnChangeModifier, value);
    return this;
  }
}

// @ts-ignore
globalThis.IndicatorComponent.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkIndicatorComponentComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.IndicatorComponentModifier(nativePtr, classType);
  });
};

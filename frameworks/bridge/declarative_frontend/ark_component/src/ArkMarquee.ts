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

class ArkMarqueeComponent extends ArkComponent implements MarqueeAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  allowChildCount(): number {
    return 0;
  }
  initialize(value: Object[]): this {
    if (value.length === 1 && isObject(value[0])) {
      modifierWithKey(this._modifiersWithKeys, MarqueeInitializeModifier.identity, MarqueeInitializeModifier, value[0]);
    } else {
      modifierWithKey(this._modifiersWithKeys, MarqueeInitializeModifier.identity, MarqueeInitializeModifier, undefined);
    }
    return this;
  }
  fontSize(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, MarqueeFontSizeModifier.identity, MarqueeFontSizeModifier, value);
    return this;
  }
  fontColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, MarqueeFontColorModifier.identity, MarqueeFontColorModifier, value);
    return this;
  }
  allowScale(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, MarqueeAllowScaleModifier.identity, MarqueeAllowScaleModifier, value);
    return this;
  }
  fontWeight(value: string | number | FontWeight): this {
    modifierWithKey(this._modifiersWithKeys, MarqueeFontWeightModifier.identity, MarqueeFontWeightModifier, value);
    return this;
  }
  fontFamily(value: any): this {
    modifierWithKey(this._modifiersWithKeys, MarqueeFontFamilyModifier.identity, MarqueeFontFamilyModifier, value as string);
    return this;
  }
  onStart(event: () => void): this {
    modifierWithKey(this._modifiersWithKeys, MarqueeOnStartModifier.identity, MarqueeOnStartModifier, event);
    return this;
  }
  onBounce(event: () => void): this {
    modifierWithKey(this._modifiersWithKeys, MarqueeOnBounceModifier.identity, MarqueeOnBounceModifier, event);
    return this;
  }
  onFinish(event: () => void): this {
    modifierWithKey(this._modifiersWithKeys, MarqueeOnFinishModifier.identity, MarqueeOnFinishModifier, event);
    return this;
  }
  marqueeUpdateStrategy(value: MarqueeUpdateStrategy): this {
    modifierWithKey(this._modifiersWithKeys, MarqueeUpdateStrategyModifier.identity, MarqueeUpdateStrategyModifier, value);
    return this;
  }
}

class MarqueeInitializeModifier extends ModifierWithKey<Object> {
  constructor(value: Object) {
    super(value);
  }
  static identity: Symbol = Symbol('marqueeInitialize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().marquee.setInitialize(node, undefined, undefined, undefined, undefined, undefined);
    } else {
      getUINativeModule().marquee.setInitialize(node, this.value?.start, this.value?.step, this.value?.loop,
        this.value?.fromStart, this.value?.src);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue?.start, this.value?.start) ||
          !isBaseOrResourceEqual(this.stageValue?.step, this.value?.step) ||
          !isBaseOrResourceEqual(this.stageValue?.loop, this.value?.loop) ||
          !isBaseOrResourceEqual(this.stageValue?.fromStart, this.value?.fromStart) ||
          !isBaseOrResourceEqual(this.stageValue?.src, this.value?.src);
  }
}

class MarqueeFontColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('fontColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().marquee.resetFontColor(node);
    } else {
      getUINativeModule().marquee.setFontColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class MarqueeFontSizeModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('fontSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().marquee.resetFontSize(node);
    } else {
      getUINativeModule().marquee.setFontSize(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class MarqueeAllowScaleModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('allowScale');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().marquee.resetAllowScale(node);
    } else {
      getUINativeModule().marquee.setAllowScale(node, this.value);
    }
  }
}
class MarqueeFontWeightModifier extends ModifierWithKey<string | number | FontWeight> {
  static identity: Symbol = Symbol('fontWeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().marquee.resetFontWeight(node);
    } else {
      getUINativeModule().marquee.setFontWeight(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}
class MarqueeFontFamilyModifier extends ModifierWithKey<string> {
  constructor(value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('fontFamily');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().marquee.resetFontFamily(node);
    } else {
      getUINativeModule().marquee.setFontFamily(node, this.value);
    }
  }
}

class MarqueeUpdateStrategyModifier extends ModifierWithKey<MarqueeUpdateStrategy> {
  constructor(value: MarqueeUpdateStrategy) {
    super(value);
  }
  static identity: Symbol = Symbol('marqueeUpdateStrategy');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().marquee.resetMarqueeUpdateStrategy(node);
    } else {
      getUINativeModule().marquee.setMarqueeUpdateStrategy(node, this.value);
    }
  }
}

class MarqueeOnStartModifier extends ModifierWithKey<() => void> {
  constructor(value: () => void) {
    super(value);
  }
  static identity: Symbol = Symbol('marqueeOnStart');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().marquee.resetMarqueeOnStart(node);
    } else {
      getUINativeModule().marquee.setMarqueeOnStart(node, this.value);
    }
  }
}

class MarqueeOnBounceModifier extends ModifierWithKey<() => void> {
  constructor(value: () => void) {
    super(value);
  }
  static identity: Symbol = Symbol('marqueeOnBounce');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().marquee.resetMarqueeOnBounce(node);
    } else {
      getUINativeModule().marquee.setMarqueeOnBounce(node, this.value);
    }
  }
}

class MarqueeOnFinishModifier extends ModifierWithKey<() => void> {
  constructor(value: () => void) {
    super(value);
  }
  static identity: Symbol = Symbol('marqueeOnFinish');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().marquee.resetMarqueeOnFinish(node);
    } else {
      getUINativeModule().marquee.setMarqueeOnFinish(node, this.value);
    }
  }
}

// @ts-ignore
globalThis.Marquee.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkMarqueeComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.MarqueeModifier(nativePtr, classType);
  });
};

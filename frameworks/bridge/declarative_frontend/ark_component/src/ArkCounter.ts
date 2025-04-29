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
class ArkCounterComponent extends ArkComponent implements CounterAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  onInc(event: () => void): this {
    modifierWithKey(this._modifiersWithKeys, CounterOnIncModifier.identity, CounterOnIncModifier, event);
    return this;
  }
  onDec(event: () => void): this {
    modifierWithKey(this._modifiersWithKeys, CounterOnDecModifier.identity, CounterOnDecModifier, event);
    return this;
  }
  enableDec(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, EnableDecModifier.identity, EnableDecModifier, value);
    return this;
  }
  enableInc(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, EnableIncModifier.identity, EnableIncModifier, value);
    return this;
  }
  backgroundColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, CounterBackgroundColorModifier.identity, CounterBackgroundColorModifier, value);
    return this;
  }
  width(value: Length): this {
    modifierWithKey(
      this._modifiersWithKeys, CounterWidthModifier.identity, CounterWidthModifier, value);
    return this;
  }
  height(value: Length): this {
    modifierWithKey(
      this._modifiersWithKeys, CounterHeightModifier.identity, CounterHeightModifier, value);
    return this;
  }
  size(value: SizeOptions): this {
    modifierWithKey(this._modifiersWithKeys, CounterSizeModifier.identity, CounterSizeModifier, value);
    return this;
  }
}

declare type OnIncCallback = () => void;
class CounterOnIncModifier extends ModifierWithKey<OnIncCallback> {
  constructor(value: OnIncCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('counterOnInc');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().counter.resetCounterOnInc(node);
    } else {
      getUINativeModule().counter.setCounterOnInc(node, this.value);
    }
  }
}

declare type OnDecCallback = () => void;
class CounterOnDecModifier extends ModifierWithKey<OnDecCallback> {
  constructor(value: OnDecCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('counterOnDec');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().counter.resetCounterOnDec(node);
    } else {
      getUINativeModule().counter.setCounterOnDec(node, this.value);
    }
  }
}
class CounterHeightModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('CounterHeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().counter.resetCounterHeight(node);
    } else {
      getUINativeModule().counter.setCounterHeight(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class CounterWidthModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('CounterWidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().counter.resetCounterWidth(node);
    } else {
      getUINativeModule().counter.setCounterWidth(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class CounterBackgroundColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('CounterBackgroundColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().counter.resetCounterBackgroundColor(node);
    } else {
      getUINativeModule().counter.setCounterBackgroundColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class CounterSizeModifier extends ModifierWithKey<SizeOptions> {
  constructor(value: SizeOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('CounterSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().counter.resetCounterSize(node);
    } else {
      getUINativeModule().counter.setCounterSize(node, this.value.width, this.value.height);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.width, this.value.width) ||
      !isBaseOrResourceEqual(this.stageValue.height, this.value.height);
  }
}
class EnableIncModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity = Symbol('enableInc');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().counter.resetEnableInc(node);
    } else {
      getUINativeModule().counter.setEnableInc(node, this.value);
    }
  }
}
class EnableDecModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity = Symbol('enableDec');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().counter.resetEnableDec(node);
    } else {
      getUINativeModule().counter.setEnableDec(node, this.value);
    }
  }
}

// @ts-ignore
globalThis.Counter.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkCounterComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.CounterModifier(nativePtr, classType);
  });
};

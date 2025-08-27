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
class ArkStepperComponent extends ArkComponent implements StepperAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  onFinish(callback: () => void): this {
    modifierWithKey(this._modifiersWithKeys, StepperOnFinishModifier.identity, StepperOnFinishModifier, callback);
    return this;
  }
  onSkip(callback: () => void): this {
    modifierWithKey(this._modifiersWithKeys, StepperOnSkipModifier.identity, StepperOnSkipModifier, callback);
    return this;
  }
  onChange(callback: (prevIndex: number, index: number) => void): this {
    modifierWithKey(this._modifiersWithKeys, StepperOnChangeModifier.identity, StepperOnChangeModifier, callback);
    return this;
  }
  onNext(callback: (index: number, pendingIndex: number) => void): this {
    modifierWithKey(this._modifiersWithKeys, StepperOnNextModifier.identity, StepperOnNextModifier, callback);
    return this;
  }
  onPrevious(callback: (index: number, pendingIndex: number) => void): this {
    modifierWithKey(this._modifiersWithKeys, StepperOnPreviousModifier.identity, StepperOnPreviousModifier, callback);
    return this;
  }
}

class StepperOnFinishModifier extends ModifierWithKey<() => void> {
  constructor(value: () => void) {
    super(value);
  }
  static identity = Symbol('onFinish');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().stepper.resetOnFinish(node);
    } else {
      getUINativeModule().stepper.setOnFinish(node, this.value);
    }
  }
}

class StepperOnSkipModifier extends ModifierWithKey<() => void> {
  constructor(value: () => void) {
    super(value);
  }
  static identity = Symbol('onSkip');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().stepper.resetOnSkip(node);
    } else {
      getUINativeModule().stepper.setOnSkip(node, this.value);
    }
  }
}

class StepperOnChangeModifier extends ModifierWithKey<(prevIndex: number, index: number) => void> {
  constructor(value: (prevIndex: number, index: number) => void) {
    super(value);
  }
  static identity = Symbol('onChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().stepper.resetOnChange(node);
    } else {
      getUINativeModule().stepper.setOnChange(node, this.value);
    }
  }
}

class StepperOnNextModifier extends ModifierWithKey<(index: number, pendingIndex: number) => void> {
  constructor(value: (index: number, pendingIndex: number) => void) {
    super(value);
  }
  static identity = Symbol('onNext');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().stepper.resetOnNext(node);
    } else {
      getUINativeModule().stepper.setOnNext(node, this.value);
    }
  }
}

class StepperOnPreviousModifier extends ModifierWithKey<(index: number, pendingIndex: number) => void> {
  constructor(value: (index: number, pendingIndex: number) => void) {
    super(value);
  }
  static identity = Symbol('onPrevious');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().stepper.resetOnPrevious(node);
    } else {
      getUINativeModule().stepper.setOnPrevious(node, this.value);
    }
  }
}

// @ts-ignore
globalThis.Stepper.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkStepperComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.StepperModifier(nativePtr, classType);
  });
};

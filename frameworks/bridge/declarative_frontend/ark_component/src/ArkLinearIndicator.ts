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
class LinearIndicatorIndicatorStyleModifier extends ModifierWithKey<LinearIndicatorStyle> {
  constructor(value: LinearIndicatorStyle) {
    super(value);
  }
  static identity = Symbol('linearIndicatorIndicatorStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().linearIndicator.resetIndicatorStyle(node);
    } else {
      getUINativeModule().linearIndicator.setIndicatorStyle(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class LinearIndicatorIndicatorLoopModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity = Symbol('linearIndicatorIndicatorLoop');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().linearIndicator.resetIndicatorLoop(node);
    } else {
      getUINativeModule().linearIndicator.setIndicatorLoop(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class LinearIndicatorOnChangeModifier extends ModifierWithKey<OnLinearIndicatorChangeCallback> {
  constructor(value: OnLinearIndicatorChangeCallback) {
    super(value);
  }
  static identity = Symbol('linearIndicatorOnChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().linearIndicator.resetOnChange(node);
    } else {
      getUINativeModule().linearIndicator.setOnChange(node, this.value);
    }
  }
}

class ArkLinearIndicatorComponent extends ArkComponent implements CommonMethod<LinearIndicatorAttribute> {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }

  indicatorStyle(value: LinearIndicatorStyle): LinearIndicatorAttribute {
    modifierWithKey(this._modifiersWithKeys, LinearIndicatorIndicatorStyleModifier.identity, LinearIndicatorIndicatorStyleModifier, value);
    return this;
  }

  indicatorLoop(value: boolean): LinearIndicatorAttribute {
    modifierWithKey(this._modifiersWithKeys, LinearIndicatorIndicatorLoopModifier.identity, LinearIndicatorIndicatorLoopModifier, value);
    return this;
  }

  onChange(value: OnLinearIndicatorChangeCallback): LinearIndicatorAttribute {
    modifierWithKey(this._modifiersWithKeys, LinearIndicatorOnChangeModifier.identity, LinearIndicatorOnChangeModifier, value);
    return this;
  }

}

// @ts-ignore
globalThis.LinearIndicator.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkLinearIndicatorComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.LinearIndicatorModifier(nativePtr, classType);
  });
};

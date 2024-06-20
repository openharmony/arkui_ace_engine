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
class ArkStepperItemComponent extends ArkComponent implements StepperItemAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  prevLabel(value: string): this {
    modifierWithKey(this._modifiersWithKeys, PrevLabelModifier.identity, PrevLabelModifier, value);
    return this;
  }
  nextLabel(value: string): this {
    modifierWithKey(this._modifiersWithKeys, NextLabelModifier.identity, NextLabelModifier, value);
    return this;
  }
  status(value?: ItemState | undefined): this {
    modifierWithKey(this._modifiersWithKeys, StatusModifier.identity, StatusModifier, value);
    return this;
  }
}

class NextLabelModifier extends ModifierWithKey<string> {
  constructor(value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('NextLabel');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().stepperItem.resetNextLabel(node);
    } else {
      getUINativeModule().stepperItem.setNextLabel(node, this.value);
    }
  }
}

class PrevLabelModifier extends ModifierWithKey<string> {
  constructor(value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('prevLabel');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().stepperItem.resetPrevLabel(node);
    } else {
      getUINativeModule().stepperItem.setPrevLabel(node, this.value);
    }
  }
}

class StatusModifier extends ModifierWithKey<ItemState | undefined> {
  constructor(value: ItemState | undefined) {
    super(value);
  }
  static identity: Symbol = Symbol('status');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().stepperItem.resetStatus(node);
    } else {
      getUINativeModule().stepperItem.setStatus(node, this.value);
    }
  }
}
// @ts-ignore
globalThis.StepperItem.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkStepperItemComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.StepperItemModifier(nativePtr, classType);
  });
};

/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
class ScrollBarEnableNestedScrollModifier extends ModifierWithKey<boolean> {
  static identity: Symbol = Symbol('enableNestedScroll');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().ScrollBar.resetScrollBarEnableNestedScroll(node);
    } else {
      getUINativeModule().ScrollBar.setScrollBarEnableNestedScroll(node, this.value);
    }
  }
}
class ArkScrollBarComponent extends ArkComponent implements ScrollBarAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  enableNestedScroll(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, ScrollBarEnableNestedScrollModifier.identity,
      ScrollBarEnableNestedScrollModifier, value);
    return this;
  }
}

// @ts-ignore
globalThis.ScrollBar.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkScrollBarComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.CommonModifier(nativePtr, classType);
  });
};

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

class ArkNavDestinationComponent extends ArkComponent implements NavDestinationAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  title(value: any): this {
    throw new Error('Method not implemented.');
  }
  hideTitleBar(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, HideTitleBarModifier.identity, HideTitleBarModifier, value);
    return this;
  }
  backButtonIcon(value: any): this {
    modifierWithKey(this._modifiersWithKeys, NavDestinationBackButtonIconModifier.identity,
      NavDestinationBackButtonIconModifier, value);
    return this;
  }
  mode(value: number): this {
    modifierWithKey(this._modifiersWithKeys, NavDestinationModeModifier.identity,
      NavDestinationModeModifier, value);
    return this;
  }
  onShown(callback: () => void): this {
    throw new Error('Method not implemented.');
  }
  onHidden(callback: () => void): this {
    throw new Error('Method not implemented.');
  }
  onBackPressed(callback: () => boolean): this {
    throw new Error('Method not implemented.');
  }
}

class HideTitleBarModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('hideTitleBar');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navDestination.resetHideTitleBar(node);
    } else {
      getUINativeModule().navDestination.setHideTitleBar(node, this.value!);
    }
  }
}

class NavDestinationBackButtonIconModifier extends ModifierWithKey<object> {
  constructor(value: object) {
    super(value);
  }
  static identity: Symbol = Symbol('backButtonIcon');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navDestination.resetBackButtonIcon(node);
    } else {
      getUINativeModule().navDestination.setBackButtonIcon(node, this.value);
    }
  }
}

class NavDestinationModeModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('mode');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navDestination.resetMode(node);
    } else {
      getUINativeModule().navDestination.setMode(node, this.value);
    }
  }
}
//@ts-ignore
globalThis.NavDestination.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkNavDestinationComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.NavDestinationModifier(nativePtr, classType);
  });
};

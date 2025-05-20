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
class ArkNavRouterComponent extends ArkComponent implements NavRouterAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  onStateChange(callback: (isActivated: boolean) => void): NavRouterAttribute {
    modifierWithKey(this._modifiersWithKeys, OnStateChangeModifier.identity, OnStateChangeModifier, callback);
    return this;
  }
  mode(mode: NavRouteMode): NavRouterAttribute {
    modifierWithKey(this._modifiersWithKeys, NavRouterModeModifier.identity, NavRouterModeModifier, mode);
    return this;
  }
}

class OnStateChangeModifier extends ModifierWithKey<((isActivated: boolean) => void)> {
  constructor(value: (isActivated: boolean) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('onStateChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navRouter.resetOnStateChange(node);
    } else {
      getUINativeModule().navRouter.setOnStateChange(node, this.value);
    }
  }
}

class NavRouterModeModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('mode');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navRouter.resetMode(node);
    } else {
      getUINativeModule().navRouter.setMode(node, this.value);
    }
  }
}

// @ts-ignore
globalThis.NavRouter.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkNavRouterComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.NavRouterModifier(nativePtr, classType);
  });
};

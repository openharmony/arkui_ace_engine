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

class ArkNavigatorComponent extends ArkComponent implements NavigatorAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  active(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, ActiveModifier.identity, ActiveModifier, value);
    return this;
  }
  type(value: NavigationType): this {
    modifierWithKey(this._modifiersWithKeys, TypeModifier.identity, TypeModifier, value);
    return this;
  }
  target(value: string): this {
    modifierWithKey(this._modifiersWithKeys, TargetModifier.identity, TargetModifier, value);
    return this;
  }
  params(value: object): this {
    modifierWithKey(this._modifiersWithKeys, ParamsModifier.identity, ParamsModifier, JSON.stringify(value));
    return this;
  }
}

class ParamsModifier extends ModifierWithKey<string> {
  constructor(value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('params');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigator.resetParams(node);
    } else {
      getUINativeModule().navigator.setParams(node, this.value);
    }
  }
}

class TypeModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('type');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigator.resetType(node);
    } else {
      getUINativeModule().navigator.setType(node, this.value);
    }
  }
}

class ActiveModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('active');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigator.resetActive(node);
    } else {
      getUINativeModule().navigator.setActive(node, this.value);
    }
  }
}

class TargetModifier extends ModifierWithKey<string> {
  constructor(value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('target');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().navigator.resetTarget(node);
    } else {
      getUINativeModule().navigator.setTarget(node, this.value);
    }
  }
}

// @ts-ignore
globalThis.Navigator.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkNavigatorComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.NavigatorModifier(nativePtr, classType);
  });
};

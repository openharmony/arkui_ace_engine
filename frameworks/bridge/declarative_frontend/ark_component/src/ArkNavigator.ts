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
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  active(value: boolean): NavigatorAttribute {
    modifier(this._modifiers, ActiveModifier, value);
    return this;
  }
  type(value: NavigationType): NavigatorAttribute {
    modifier(this._modifiers, TypeModifier, value);
    return this;
  }
  target(value: string): NavigatorAttribute {
    modifier(this._modifiers, TargetModifier, value);
    return this;
  }
  params(value: object): NavigatorAttribute {
    modifier(this._modifiers, ParamsModifier, JSON.stringify(value));
    return this;
  }
}

class ParamsModifier extends Modifier<string> {
  constructor(value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('params');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().navigator.resetParams(node);
    } else {
      GetUINativeModule().navigator.setParams(node, this.value);
    }
  }
}

class TypeModifier extends Modifier<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('type');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().navigator.resetType(node);
    } else {
      GetUINativeModule().navigator.setType(node, this.value);
    }
  }
}

class ActiveModifier extends Modifier<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('active');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().navigator.resetActive(node);
    } else {
      GetUINativeModule().navigator.setActive(node, this.value);
    }
  }
}

class TargetModifier extends Modifier<string> {
  constructor(value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('target');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().navigator.resetTarget(node);
    } else {
      GetUINativeModule().navigator.setTarget(node, this.value);
    }
  }
}

// @ts-ignore
globalThis.Navigator.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkNavigatorComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
}

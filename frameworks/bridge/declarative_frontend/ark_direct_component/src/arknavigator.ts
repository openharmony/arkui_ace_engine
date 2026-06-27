/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

/// <reference path='./../../ark_component/src/import.ts' />
type ComponentObj = { component: any }

function loadComponent(): ComponentObj | undefined {
  if (loadComponent.componentObj === undefined && globalThis.__ArkComponent__ !== undefined) {
    class ArkNavigatorComponent extends globalThis.__ArkComponent__ {
      constructor(nativePtr: any, classType: any) {
        super(nativePtr, classType);
      }
      target(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TargetModifier.identity, TargetModifier, value);
        return this;
      }
      type(value: any): this {
        modifierWithKey(this._modifiersWithKeys, TypeModifier.identity, TypeModifier, value);
        return this;
      }
      active(value: any): this {
        modifierWithKey(this._modifiersWithKeys, ActiveModifier.identity, ActiveModifier, value);
        return this;
      }
      params(value: any): this {
        modifierWithKey(this._modifiersWithKeys, ParamsModifier.identity, ParamsModifier, JSON.stringify(value));
        return this;
      }
    }

    class ParamsModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().navigator.resetParams(node);
        } else {
          getUINativeModule().navigator.setParams(node, this.value);
        }
      }
    }
    (ParamsModifier as any).identity = Symbol('params');

    class TypeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().navigator.resetType(node);
        } else {
          getUINativeModule().navigator.setType(node, this.value);
        }
      }
    }
    (TypeModifier as any).identity = Symbol('type');

    class ActiveModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().navigator.resetActive(node);
        } else {
          getUINativeModule().navigator.setActive(node, this.value);
        }
      }
    }
    (ActiveModifier as any).identity = Symbol('active');

    class TargetModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().navigator.resetTarget(node);
        } else {
          getUINativeModule().navigator.setTarget(node, this.value);
        }
      }
    }
    (TargetModifier as any).identity = Symbol('target');

    loadComponent.componentObj = { 'component': ArkNavigatorComponent };
  }
  return loadComponent.componentObj;
}

class JSNavigator extends JSContainerBase {
  static create(params: any): void {
    getUINativeModule().navigator.create(params);
  }

  static target(value: any): void {
    getUINativeModule().navigator.setTarget(true, value);
  }

  static type(value: any): void {
    getUINativeModule().navigator.setType(true, value);
  }

  static active(value: any): void {
    getUINativeModule().navigator.setActive(true, value);
  }

  static params(value: any): void {
    getUINativeModule().navigator.setParams(true, JSON.stringify(value));
  }

  static width(value: any): void {
    getUINativeModule().navigator.setWidth(value);
  }

  static height(value: any): void {
    getUINativeModule().navigator.setHeight(value);
  }

  static size(value: any): void {
    getUINativeModule().navigator.setSize(value);
  }

  static attributeModifier(modifier: any): void {
    attributeModifierFunc.call(this, modifier, (nativePtr: any) => {
      return new (loadComponent as any).componentObj?.component(nativePtr);
    }, (nativePtr: any, classType: any, modifierJS: any) => {
      return new modifierJS.NavigatorModifier(nativePtr, classType);
    });
  }

  static onAttach(value: any): void {
    __Common__.onAttach(value);
  }

  static onAppear(value: any): void {
    __Common__.onAppear(value);
  }

  static onDetach(value: any): void {
    __Common__.onDetach(value);
  }

  static onDisAppear(value: any): void {
    __Common__.onDisAppear(value);
  }

  static onTouch(value: any): void {
    __Common__.onTouch(value);
  }

  static onHover(value: any): void {
    __Common__.onHover(value);
  }

  static onClick(value: any): void {
    __Common__.onClick(value);
  }

  static onKeyEvent(value: any): void {
    __Common__.onKeyEvent(value);
  }

  static onDeleteEvent(value: any): void {
    __Common__.onDeleteEvent(value);
  }

  static remoteMessage(value: any): void {
    __Common__.remoteMessage(value);
  }
}

function createComponent(nativePtr: any, classType: any): any {
  loadComponent();
  if (loadComponent.componentObj !== undefined) {
    return new loadComponent.componentObj.component(nativePtr, classType);
  }
  return undefined;
}

function exportComponent(): void {
  globalThis.ArkNavigatorComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
  globalThis.Navigator = JSNavigator;
}

export default { loadComponent, createComponent, exportComponent, exportView };

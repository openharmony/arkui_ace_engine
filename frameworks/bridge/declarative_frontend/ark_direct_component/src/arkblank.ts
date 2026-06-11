/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

class BlankColorModifier extends ModifierWithKey<any> {
  constructor(value: any) {
    super(value);
  }

  applyPeer(node: any, reset: boolean): void {
    if (reset) {
      getUINativeModule().blank.resetColor(node);
    } else {
      getUINativeModule().blank.setColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
(BlankColorModifier as any).identity = Symbol('blankColor');

class BlankHeightModifier extends ModifierWithKey<any> {
  constructor(value: any) {
    super(value);
  }

  applyPeer(node: any, reset: boolean): void {
    if (reset) {
      getUINativeModule().blank.resetBlankHeight(node);
    } else {
      getUINativeModule().blank.setBlankHeight(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
(BlankHeightModifier as any).identity = Symbol('blankHeight');

class BlankMinModifier extends ModifierWithKey<any> {
  constructor(value: any) {
    super(value);
  }

  applyPeer(node: any, reset: boolean): void {
    if (reset) {
      getUINativeModule().blank.resetBlankMin(node);
    } else {
      getUINativeModule().blank.setBlankMin(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
(BlankMinModifier as any).identity = Symbol('blankMin');

function loadComponent(): ComponentObj | undefined {
  if (loadComponent.componentObj === undefined && globalThis.__ArkComponent__ !== undefined) {
    class ArkBlankComponent extends globalThis.__ArkComponent__ {
      constructor(nativePtr: any, classType: any) {
        super(nativePtr, classType);
      }

      color(value: any): this {
        modifierWithKey(this._modifiersWithKeys, BlankColorModifier.identity, BlankColorModifier, value);
        return this;
      }

      height(value: any): this {
        modifierWithKey(this._modifiersWithKeys, BlankHeightModifier.identity, BlankHeightModifier, value);
        return this;
      }

      initialize(value: any): this {
        if (value[0] !== undefined) {
          modifierWithKey(this._modifiersWithKeys, BlankMinModifier.identity, BlankMinModifier, value[0]);
        }
        return this;
      }

      allowChildCount(): number {
        return 0;
      }
    }

    loadComponent.componentObj = { 'component': ArkBlankComponent };
  }
  return loadComponent.componentObj;
}

class JSBlank extends JSViewAbstract {
  static create(value: any): void {
    getUINativeModule().blank.create(value);
  }

  static color(value: any): void {
    getUINativeModule().blank.setColor(true, value);
  }

  static height(value: any): void {
    JSViewAbstract.height(value);
    getUINativeModule().blank.setBlankHeight(true, value);
  }

  static attributeModifier(modifier: any): void {
    attributeModifierFunc.call(this, modifier, (nativePtr: any) => {
      return createComponent(nativePtr, undefined);
    }, (nativePtr: any, classType: any, modifierJS: any) => {
      return new modifierJS.BlankModifier(nativePtr, classType);
    });
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
  globalThis.ArkBlankComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
  globalThis.Blank = JSBlank;
}

export default { loadComponent, createComponent, exportComponent, exportView };

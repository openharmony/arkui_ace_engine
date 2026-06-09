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

class DividerVerticalModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }

  static identity: Symbol = Symbol('dividerVertical');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().divider.resetVertical(node);
    } else {
      getUINativeModule().divider.setVertical(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class DividerStrokeWidthModifier extends ModifierWithKey<number | string> {
  constructor(value: number | string) {
    super(value);
  }

  static identity: Symbol = Symbol('dividerStrokeWidth');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().divider.resetStrokeWidth(node);
    } else {
      getUINativeModule().divider.setStrokeWidth(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class DividerLineCapModifier extends ModifierWithKey<LineCapStyle> {
  constructor(value: LineCapStyle) {
    super(value);
  }

  static identity: Symbol = Symbol('dividerLineCap');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().divider.resetLineCap(node);
    } else {
      getUINativeModule().divider.setLineCap(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class DividerColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }

  static identity: Symbol = Symbol('dividerColor');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().divider.resetColor(node);
    } else {
      getUINativeModule().divider.setColor(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

function loadComponent(): ComponentObj | undefined {
  if (loadComponent.componentObj === undefined && globalThis.__ArkComponent__ !== undefined) {
    class ArkDividerComponent extends globalThis.__ArkComponent__ {
      constructor(nativePtr: any, classType: any) {
        super(nativePtr, classType);
      }

      initialize(value: any): this {
        return this;
      }

      allowChildCount(): number {
        return 0;
      }

      vertical(value: any): this {
        modifierWithKey(this._modifiersWithKeys, DividerVerticalModifier.identity, DividerVerticalModifier, value);
        return this;
      }

      color(value: any): this {
        modifierWithKey(this._modifiersWithKeys, DividerColorModifier.identity, DividerColorModifier, value);
        return this;
      }

      strokeWidth(value: any): this {
        modifierWithKey(this._modifiersWithKeys, DividerStrokeWidthModifier.identity, DividerStrokeWidthModifier, value);
        return this;
      }

      lineCap(value: any): this {
        modifierWithKey(this._modifiersWithKeys, DividerLineCapModifier.identity, DividerLineCapModifier, value);
        return this;
      }
    }

    loadComponent.componentObj = { 'component': ArkDividerComponent };
  }
  return loadComponent.componentObj;
}

class JSDivider extends JSViewAbstract {
  static create(value: any): void {
    getUINativeModule().divider.create(value);
  }

  static vertical(value: any): void {
    getUINativeModule().divider.setVertical(true, value);
  }

  static lineCap(value: any): void {
    getUINativeModule().divider.setLineCap(true, value);
  }

  static color(value: any): void {
    getUINativeModule().divider.setColor(true, value);
  }

  static strokeWidth(value: any): void {
    getUINativeModule().divider.setStrokeWidth(true, value);
  }

  static attributeModifier(modifier: any): void {
    attributeModifierFunc.call(this, modifier, (nativePtr: any) => {
      return createComponent(nativePtr, undefined);
    }, (nativePtr: any, classType: any, modifierJS: any) => {
      return new modifierJS.DividerModifier(nativePtr, classType);
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
  globalThis.ArkDividerComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
  globalThis.Divider = JSDivider;
}

export default { loadComponent, createComponent, exportComponent, exportView };

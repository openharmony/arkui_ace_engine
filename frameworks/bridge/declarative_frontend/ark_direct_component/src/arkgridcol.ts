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

function setColumnOption(node: any, value: any, setter: string, resetter: string): void {
  if (value === undefined || value === null) {
    getUINativeModule().gridCol[resetter](node);
  } else if (isNumber(value)) {
    getUINativeModule().gridCol[setter](node, value, value, value, value, value, value);
  } else {
    getUINativeModule().gridCol[setter](node, value.xs, value.sm, value.md, value.lg, value.xl, value.xxl);
  }
}

function loadComponent(): ComponentObj | undefined {
  if (loadComponent.componentObj === undefined && globalThis.__ArkComponent__ !== undefined) {
    class GridColSpanModifier extends ModifierWithKey<any> {
      applyPeer(node: any, reset: boolean): void {
        reset ? getUINativeModule().gridCol.resetSpan(node) : setColumnOption(node, this.value, 'setSpan', 'resetSpan');
      }
      checkObjectDiff(): boolean {
        if (isNumber(this.stageValue) && isNumber(this.value)) {
          return this.stageValue !== this.value;
        }
        else if (isObject(this.stageValue) && isObject(this.value)) {
          return this.stageValue?.xs !== this.value?.xs ||
            this.stageValue?.sm !== this.value?.sm ||
            this.stageValue?.md !== this.value?.md ||
            this.stageValue?.lg !== this.value?.lg ||
            this.stageValue?.xl !== this.value?.xl ||
            this.stageValue?.xxl !== this.value?.xxl;
        }
        else {
          return true;
        }
      }
    }
    (GridColSpanModifier as any).identity = Symbol('gridColSpan');

    class GridColOffsetModifier extends ModifierWithKey<any> {
      applyPeer(node: any, reset: boolean): void {
        reset ? getUINativeModule().gridCol.resetGridColOffset(node) :
          setColumnOption(node, this.value, 'setGridColOffset', 'resetGridColOffset');
      }
      checkObjectDiff(): boolean {
        if (isNumber(this.stageValue) && isNumber(this.value)) {
          return this.stageValue !== this.value;
        }
        else if (isObject(this.stageValue) && isObject(this.value)) {
          return this.stageValue?.xs !== this.value?.xs ||
            this.stageValue?.sm !== this.value?.sm ||
            this.stageValue?.md !== this.value?.md ||
            this.stageValue?.lg !== this.value?.lg ||
            this.stageValue?.xl !== this.value?.xl ||
            this.stageValue?.xxl !== this.value?.xxl;
        }
        else {
          return true;
        }
      }
    }
    (GridColOffsetModifier as any).identity = Symbol('gridColOffset');

    class GridColOrderModifier extends ModifierWithKey<any> {
      applyPeer(node: any, reset: boolean): void {
        reset ? getUINativeModule().gridCol.resetOrder(node) : setColumnOption(node, this.value, 'setOrder', 'resetOrder');
      }
      checkObjectDiff(): boolean {
        if (isNumber(this.stageValue) && isNumber(this.value)) {
          return this.stageValue !== this.value;
        }
        else if (isObject(this.stageValue) && isObject(this.value)) {
          return this.stageValue?.xs !== this.value?.xs ||
            this.stageValue?.sm !== this.value?.sm ||
            this.stageValue?.md !== this.value?.md ||
            this.stageValue?.lg !== this.value?.lg ||
            this.stageValue?.xl !== this.value?.xl ||
            this.stageValue?.xxl !== this.value?.xxl;
        }
        else {
          return true;
        }
      }
    }
    (GridColOrderModifier as any).identity = Symbol('gridColOrder');

    class ArkGridColComponent extends globalThis.__ArkComponent__ {
      constructor(nativePtr: any, classType?: any) {
        super(nativePtr, classType);
      }
      allowChildCount(): number {
        return 1;
      }
      span(value: any): this {
        modifierWithKey(this._modifiersWithKeys, (GridColSpanModifier as any).identity, GridColSpanModifier, value);
        return this;
      }
      gridColOffset(value: any): this {
        modifierWithKey(this._modifiersWithKeys, (GridColOffsetModifier as any).identity, GridColOffsetModifier, value);
        return this;
      }
      order(value: any): this {
        modifierWithKey(this._modifiersWithKeys, (GridColOrderModifier as any).identity, GridColOrderModifier, value);
        return this;
      }
      initialize(value: any[]): this {
        if (value[0] !== undefined) {
          this.span(value[0].span);
          this.gridColOffset(value[0].offset);
          this.order(value[0].order);
        } else {
          this.span(null);
          this.gridColOffset(null);
          this.order(null);
        }
        return this;
      }
    }
    loadComponent.componentObj = { component: ArkGridColComponent };
  }
  return loadComponent.componentObj;
}

class JSGridCol extends JSContainerBase {
  static create(params: any): void {
    getUINativeModule().gridCol.create(params);
  }
  static span(value: any): void {
    setColumnOption(true, value, 'setSpan', 'resetSpan');
  }
  static offset(value: any): void {
    if (arguments.length < 1) {
      return;
    }
    if (value !== undefined && value !== null && typeof value === 'object') {
      const xVal = value.x;
      const yVal = value.y;
      if (xVal !== undefined || yVal !== undefined) {
        __Common__.offset(value);
        return;
      }
    }
    getUINativeModule().gridCol.offset(true, value);
  }
  static gridColOffset(value: any): void {
    if (arguments.length < 1) {
      return;
    }
    if (value !== undefined && value !== null && typeof value === 'object') {
      const xVal = value.x;
      const yVal = value.y;
      if (xVal !== undefined || yVal !== undefined) {
        JSViewAbstract.offset(value);
        return;
      }
    }
    getUINativeModule().gridCol.offset(true, value);
  }
  static order(value: any): void {
    setColumnOption(true, value, 'setOrder', 'resetOrder');
  }
  static attributeModifier(modifier: any): void {
    attributeModifierFunc.call(this, modifier, (nativePtr: any) => createComponent(nativePtr),
      (nativePtr: any, classType: any, modifierJS: any) => new modifierJS.GridColModifier(nativePtr, classType));
  }
  static onAttach(value: any): void { __Common__.onAttach(value); }
  static onAppear(value: any): void { __Common__.onAppear(value); }
  static onDetach(value: any): void { __Common__.onDetach(value); }
  static onDisAppear(value: any): void { __Common__.onDisAppear(value); }
  static onTouch(value: any): void { __Common__.onTouch(value); }
}

function createComponent(nativePtr: any, classType?: any): any {
  loadComponent();
  if (loadComponent.componentObj !== undefined) {
    return new loadComponent.componentObj.component(nativePtr, classType);
  }
  return undefined;
}

function exportComponent(): void {
  loadComponent();
  globalThis.ArkGridColComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
  globalThis.GridCol = JSGridCol;
}

export default { loadComponent, createComponent, exportComponent, exportView };
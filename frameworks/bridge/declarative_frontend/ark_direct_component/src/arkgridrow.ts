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

const XS = 0;
const SM = 1;
const MD = 2;
const LG = 3;
const XL = 4;
const XXL = 5;

function setColumns(node: any, value: any): void {
  if (value === undefined || value === null) {
    getUINativeModule().gridRow.resetColumns(node);
  } else if (isNumber(value)) {
    getUINativeModule().gridRow.setColumns(node, value, value, value, value, value, value);
  } else {
    getUINativeModule().gridRow.setColumns(node, value.xs, value.sm, value.md, value.lg, value.xl, value.xxl);
  }
}

function parseGutter(value: any): any[] {
  let gutters = [undefined, undefined, undefined, undefined, undefined, undefined];
  if (isNumber(value)) {
    gutters[XS] = value;
    gutters[SM] = value;
    gutters[MD] = value;
    gutters[LG] = value;
    gutters[XL] = value;
    gutters[XXL] = value;
  } else if (value !== undefined && value !== null) {
    gutters[XS] = value.xs;
    gutters[SM] = value.sm;
    gutters[MD] = value.md;
    gutters[LG] = value.lg;
    gutters[XL] = value.xl;
    gutters[XXL] = value.xxl;
  }
  return gutters;
}

function setGutter(node: any, value: any): void {
  if (value === undefined || value === null) {
    getUINativeModule().gridRow.resetGutter(node);
    return;
  }
  if (isNumber(value)) {
    getUINativeModule().gridRow.setGutter(node, value, value, value, value, value, value,
      value, value, value, value, value, value);
    return;
  }
  let xGutters = parseGutter(value.x);
  let yGutters = parseGutter(value.y);
  getUINativeModule().gridRow.setGutter(node,
    xGutters[XS], xGutters[SM], xGutters[MD], xGutters[LG], xGutters[XL], xGutters[XXL],
    yGutters[XS], yGutters[SM], yGutters[MD], yGutters[LG], yGutters[XL], yGutters[XXL]);
}

function setBreakpoints(node: any, value: any): void {
  if (value === undefined || value === null) {
    getUINativeModule().gridRow.resetBreakpoints(node);
  } else {
    getUINativeModule().gridRow.setBreakpoints(node, value.value, value.reference);
  }
}

function setDirection(node: any, value: any): void {
  if (value === undefined || value === null) {
    getUINativeModule().gridRow.resetDirection(node);
  } else {
    getUINativeModule().gridRow.setDirection(node, value);
  }
}

function loadComponent(): ComponentObj | undefined {
  if (loadComponent.componentObj === undefined && globalThis.__ArkComponent__ !== undefined) {
    class GridRowAlignItemsModifier extends ModifierWithKey<any> {
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().gridRow.resetAlignItems(node);
        } else {
          getUINativeModule().gridRow.setAlignItems(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (GridRowAlignItemsModifier as any).identity = Symbol('gridRowAlignItems');

    class GridRowOnBreakpointChangeModifier extends ModifierWithKey<any> {
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().gridRow.resetOnBreakpointChange(node);
        } else {
          getUINativeModule().gridRow.setOnBreakpointChange(node, this.value);
        }
      }
    }
    (GridRowOnBreakpointChangeModifier as any).identity = Symbol('gridRowOnBreakpointChange');

    class SetDirectionModifier extends ModifierWithKey<any> {
      applyPeer(node: any, reset: boolean): void {
        reset ? getUINativeModule().gridRow.resetDirection(node) : setDirection(node, this.value);
      }
    }
    (SetDirectionModifier as any).identity = Symbol('gridRowDirection');

    class SetBreakpointsModifier extends ModifierWithKey<any> {
      applyPeer(node: any, reset: boolean): void {
        reset ? getUINativeModule().gridRow.resetBreakpoints(node) : setBreakpoints(node, this.value);
      }
    }
    (SetBreakpointsModifier as any).identity = Symbol('gridRowBreakpoints');

    class SetColumnsModifier extends ModifierWithKey<any> {
      applyPeer(node: any, reset: boolean): void {
        reset ? getUINativeModule().gridRow.resetColumns(node) : setColumns(node, this.value);
      }
    }
    (SetColumnsModifier as any).identity = Symbol('gridRowColumns');

    class SetGutterModifier extends ModifierWithKey<any> {
      applyPeer(node: any, reset: boolean): void {
        reset ? getUINativeModule().gridRow.resetGutter(node) : setGutter(node, this.value);
      }
    }
    (SetGutterModifier as any).identity = Symbol('gridRowGutter');

    class ArkGridRowComponent extends globalThis.__ArkComponent__ {
      constructor(nativePtr: any, classType?: any) {
        super(nativePtr, classType);
      }
      allowChildTypes(): string[] {
        return ['GridCol'];
      }
      onBreakpointChange(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, (GridRowOnBreakpointChangeModifier as any).identity,
          GridRowOnBreakpointChangeModifier, callback);
        return this;
      }
      alignItems(value: any): this {
        modifierWithKey(this._modifiersWithKeys, (GridRowAlignItemsModifier as any).identity,
          GridRowAlignItemsModifier, value);
        return this;
      }
      setDirection(value: any): this {
        modifierWithKey(this._modifiersWithKeys, (SetDirectionModifier as any).identity, SetDirectionModifier, value);
        return this;
      }
      setBreakpoints(value: any): this {
        modifierWithKey(this._modifiersWithKeys, (SetBreakpointsModifier as any).identity, SetBreakpointsModifier, value);
        return this;
      }
      setColumns(value: any): this {
        modifierWithKey(this._modifiersWithKeys, (SetColumnsModifier as any).identity, SetColumnsModifier, value);
        return this;
      }
      setGutter(value: any): this {
        modifierWithKey(this._modifiersWithKeys, (SetGutterModifier as any).identity, SetGutterModifier, value);
        return this;
      }
      initialize(value: any[]): this {
        if (value[0] !== undefined) {
          this.setGutter(value[0].gutter);
          this.setColumns(value[0].columns);
          this.setBreakpoints(value[0].breakpoints);
          this.setDirection(value[0].direction);
        } else {
          this.setGutter(null);
          this.setColumns(null);
          this.setBreakpoints(null);
          this.setDirection(null);
        }
        return this;
      }
    }
    loadComponent.componentObj = { component: ArkGridRowComponent };
  }
  return loadComponent.componentObj;
}

class JSGridRow extends JSContainerBase {
  static create(params: any): void {
    getUINativeModule().gridRow.create(params);
  }
  static onBreakpointChange(callback: any): void {
    getUINativeModule().gridRow.setOnBreakpointChange(true, callback);
  }
  static height(value: any): void {
    __Common__.height(value);
    getUINativeModule().gridRow.setHeight(true);
  }
  static alignItems(value: any): void {
    if (value === undefined || value === null) {
      getUINativeModule().gridRow.resetAlignItems(true);
    } else {
      getUINativeModule().gridRow.setAlignItems(true, value);
    }
  }
  static attributeModifier(modifier: any): void {
    attributeModifierFunc.call(this, modifier, (nativePtr: any) => createComponent(nativePtr),
      (nativePtr: any, classType: any, modifierJS: any) => new modifierJS.GridRowModifier(nativePtr, classType));
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
  globalThis.ArkGridRowComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
  globalThis.GridRow = JSGridRow;
}

export default { loadComponent, createComponent, exportComponent, exportView };
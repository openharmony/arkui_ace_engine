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
namespace BreakpointConstants {
  export const XS = 0;
  export const SM = 1;
  export const MD = 2;
  export const LG = 3;
  export const XL = 4;
  export const XXL = 5;
};
class GridRowAlignItemsModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('gridRowAlignItems');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().gridRow.resetAlignItems(node);
    } else {
      getUINativeModule().gridRow.setAlignItems(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class SetDirectionModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('gridRowDirection');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().gridRow.resetDirection(node);
    } else {
      getUINativeModule().gridRow.setDirection(node, this.value);
    }
  }
}
class SetBreakpointsModifier extends ModifierWithKey<BreakPoints> {
  constructor(value: BreakPoints) {
    super(value);
  }
  static identity: Symbol = Symbol('gridRowBreakpoints');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().gridRow.resetBreakpoints(node);
    } else {
      getUINativeModule().gridRow.setBreakpoints(node, this.value.value, this.value.reference);
    }
  }
}
class SetColumnsModifier extends ModifierWithKey<number | GridRowColumnOption> {
  constructor(value: number | GridRowColumnOption) {
    super(value);
  }
  static identity: Symbol = Symbol('gridRowColumns');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().gridRow.resetColumns(node);
    } else {
      if (isNumber(this.value)) {
        getUINativeModule().gridRow.setColumns(node, this.value,
          this.value, this.value, this.value, this.value, this.value);
      } else {
        getUINativeModule().gridRow.setColumns(node, this.value.xs,
          this.value.sm, this.value.md, this.value.lg, this.value.xl, this.value.xxl);
      }
    }
  }
}
class SetGutterModifier extends ModifierWithKey<number | GutterOption> {
  constructor(value: number | GutterOption) {
    super(value);
  }
  static identity: Symbol = Symbol('gridRowGutter');
  parseGutter(value: number | GridRowSizeOption): number[] {
    let gutters: number[] = [0, 0, 0, 0, 0, 0];
    if (isNumber(value)) {
      gutters[BreakpointConstants.XS] = value;
      gutters[BreakpointConstants.SM] = value;
      gutters[BreakpointConstants.MD] = value;
      gutters[BreakpointConstants.LG] = value;
      gutters[BreakpointConstants.XL] = value;
      gutters[BreakpointConstants.XXL] = value;
    } else {
      gutters[BreakpointConstants.XS] = value?.xs;
      gutters[BreakpointConstants.SM] = value?.sm;
      gutters[BreakpointConstants.MD] = value?.md;
      gutters[BreakpointConstants.LG] = value?.lg;
      gutters[BreakpointConstants.XL] = value?.xl;
      gutters[BreakpointConstants.XXL] = value?.xxl;
    }
    return gutters;
  }
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().gridRow.resetGutter(node);
      return;
    }
    if (isNumber(this.value)) {
      getUINativeModule().gridRow.setGutter(node, this.value,
        this.value, this.value, this.value, this.value, this.value,
        this.value, this.value, this.value, this.value, this.value, this.value);
      return;
    }
    let xGutters: number[] = this.parseGutter(this.value.x);
    let yGutters: number[] = this.parseGutter(this.value.y);
    getUINativeModule().gridRow.setGutter(node,
      xGutters[BreakpointConstants.XS], xGutters[BreakpointConstants.SM], xGutters[BreakpointConstants.MD],
      xGutters[BreakpointConstants.LG], xGutters[BreakpointConstants.XL], xGutters[BreakpointConstants.XXL],
      yGutters[BreakpointConstants.XS], yGutters[BreakpointConstants.SM], yGutters[BreakpointConstants.MD],
      yGutters[BreakpointConstants.LG], yGutters[BreakpointConstants.XL], yGutters[BreakpointConstants.XXL]
    );
  }
}
class GridRowOnBreakpointChangeModifier extends ModifierWithKey<(breakpoints: string) => void> {
  constructor(value: (breakpoints: string) => void) {
    super(value);
  }
  static identity = Symbol('gridRowOnBreakpointChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().gridRow.resetOnBreakpointChange(node);
    } else {
      getUINativeModule().gridRow.setOnBreakpointChange(node, this.value);
    }
  }
}
interface GridRowParam {
  gutter?: number | GutterOption;
  columns?: number | GridRowColumnOption;
  breakpoints?: BreakPoints;
  direction?: number;
}
class ArkGridRowComponent extends ArkComponent implements CommonMethod<GridRowAttribute> {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  allowChildTypes(): string[] {
    return ["GridCol"];
  }
  onBreakpointChange(callback: (breakpoints: string) => void): GridRowAttribute {
    modifierWithKey(this._modifiersWithKeys, GridRowOnBreakpointChangeModifier.identity, GridRowOnBreakpointChangeModifier, callback);
    return this;
  }
  alignItems(value: ItemAlign): GridRowAttribute {
    modifierWithKey(this._modifiersWithKeys, GridRowAlignItemsModifier.identity, GridRowAlignItemsModifier, value);
    return this;
  }
  setDirection(value: number): GridRowAttribute {
    modifierWithKey(this._modifiersWithKeys, SetDirectionModifier.identity, SetDirectionModifier, value);
    return this;
  }
  setBreakpoints(value: BreakPoints): GridRowAttribute {
    modifierWithKey(this._modifiersWithKeys, SetBreakpointsModifier.identity, SetBreakpointsModifier, value);
    return this;
  }
  setColumns(value: number | GridRowColumnOption): GridRowAttribute {
    modifierWithKey(this._modifiersWithKeys, SetColumnsModifier.identity, SetColumnsModifier, value);
    return this;
  }
  setGutter(value: number | GutterOption): GridRowAttribute {
    modifierWithKey(this._modifiersWithKeys, SetGutterModifier.identity, SetGutterModifier, value);
    return this;
  }
  initialize(value: Object[]): GridRowAttribute {
    if (value[0] !== undefined) {
      this.setGutter((value[0] as GridRowParam).gutter);
      this.setColumns((value[0] as GridRowParam).columns);
      this.setBreakpoints((value[0] as GridRowParam).breakpoints);
      this.setDirection((value[0] as GridRowParam).direction);
    } else {
      this.setGutter(null);
      this.setColumns(null);
      this.setBreakpoints(null);
      this.setDirection(null);
    }
    return this;
  }
}
// @ts-ignore
globalThis.GridRow.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkGridRowComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.GridRowModifier(nativePtr, classType);
  });
};

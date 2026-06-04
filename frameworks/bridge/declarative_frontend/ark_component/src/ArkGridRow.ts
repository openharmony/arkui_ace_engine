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
      if (isUndefined(this.value) || isNull(this.value)) {
        getUINativeModule().gridRow.resetColumns(node);
      } else if (isNumber(this.value)) {
        getUINativeModule().gridRow.setColumns(node, this.value,
          this.value, this.value, this.value, this.value, this.value);
      } else {
        getUINativeModule().gridRow.setColumns(node, (this.value as any).xs,
          (this.value as any).sm, (this.value as any).md, (this.value as any).lg, (this.value as any).xl, (this.value as any).xxl);
      }
    }
  }
}
class SetGutterModifier extends ModifierWithKey<number | GutterOption> {
  constructor(value: number | GutterOption) {
    super(value);
  }
  static identity: Symbol = Symbol('gridRowGutter');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().gridRow.resetGutter(node);
    }
    else {
      if (isUndefined(this.value) || isNull(this.value)) {
        getUINativeModule().gridRow.resetGutter(node);
      }
      if (isNumber(this.value)) {
        getUINativeModule().gridRow.setGutter(node, this.value,
          this.value, this.value, this.value, this.value, this.value,
          this.value, this.value, this.value, this.value, this.value, this.value);
      }
      else {
        if (isNumber((this.value as any).x)) {
          if (isNumber((this.value as any).y)) {
            getUINativeModule().gridRow.setGutter(node,
              (this.value as any).x, (this.value as any).x, (this.value as any).x, (this.value as any).x, (this.value as any).x, (this.value as any).x,
              (this.value as any).y, (this.value as any).y, (this.value as any).y, (this.value as any).y, (this.value as any).y, (this.value as any).y);
          }
          else {
            getUINativeModule().gridRow.setGutter(node,
              (this.value as any).x, (this.value as any).x, (this.value as any).x, (this.value as any).x, (this.value as any).x, (this.value as any).x,
              (this.value as any).y?.xs, (this.value as any).y?.sm, (this.value as any).y?.md, (this.value as any).y?.lg, (this.value as any).y?.xl, (this.value as any).y?.xxl);
          }
        }
        else {
          if (isNumber((this.value as any).y)) {
            getUINativeModule().gridRow.setGutter(node,
              (this.value as any).x?.xs, (this.value as any).x?.sm, (this.value as any).x?.md, (this.value as any).x?.lg, (this.value as any).x?.xl, (this.value as any).x?.xxl,
              (this.value as any).y, (this.value as any).y, (this.value as any).y, (this.value as any).y, (this.value as any).y, (this.value as any).y);
          }
          else {
            getUINativeModule().gridRow.setGutter(node,
              (this.value as any).x?.xs, (this.value as any).x?.sm, (this.value as any).x?.md, (this.value as any).x?.lg, (this.value as any).x?.xl, (this.value as any).x?.xxl,
              (this.value as any).y?.xs, (this.value as any).y?.sm, (this.value as any).y?.md, (this.value as any).y?.lg, (this.value as any).y?.xl, (this.value as any).y?.xxl);
          }
        }
      }
    }
  }
}
interface GridRowParam {
  gutter?: number | GutterOption;
  columns?: number | GridRowColumnOption;
  breakpoints?: BreakPoints;
  direction?: number;
}
class ArkGridRowComponent extends ArkComponent {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  allowChildTypes(): string[] {
    return ["GridCol"];
  }
  onBreakpointChange(callback: (breakpoints: string) => void): this {
    modifierWithKey(this._modifiersWithKeys, GridRowOnBreakpointChangeModifier.identity, GridRowOnBreakpointChangeModifier, callback);
    return this;
  }
  alignItems(value: ItemAlign): this {
    modifierWithKey(this._modifiersWithKeys, GridRowAlignItemsModifier.identity, GridRowAlignItemsModifier, value);
    return this;
  }
  setDirection(value: number): this {
    modifierWithKey(this._modifiersWithKeys, SetDirectionModifier.identity, SetDirectionModifier, value);
    return this;
  }
  setBreakpoints(value: BreakPoints): this {
    modifierWithKey(this._modifiersWithKeys, SetBreakpointsModifier.identity, SetBreakpointsModifier, value);
    return this;
  }
  setColumns(value: number | GridRowColumnOption): this {
    modifierWithKey(this._modifiersWithKeys, SetColumnsModifier.identity, SetColumnsModifier, value);
    return this;
  }
  setGutter(value: number | GutterOption): this {
    modifierWithKey(this._modifiersWithKeys, SetGutterModifier.identity, SetGutterModifier, value);
    return this;
  }
  initialize(value: Object[]): this {
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
if (globalThis.GridRow !== undefined) {
  (globalThis as any).GridRow.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkGridRowComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.GridRowModifier(nativePtr, classType);
    });
  };
}

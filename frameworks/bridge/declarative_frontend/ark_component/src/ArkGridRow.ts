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
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().gridRow.resetGutter(node);
    } else {
      if (isNumber(this.value)) {
        getUINativeModule().gridRow.setGutter(node, this.value,
          this.value, this.value, this.value, this.value, this.value,
          this.value, this.value, this.value, this.value, this.value, this.value);
      } else {
        if (isNumber(this.value.x)) {
          if (isNumber(this.value.y)) {
            getUINativeModule().gridRow.setGutter(node,
              this.value.x, this.value.x, this.value.x, this.value.x, this.value.x, this.value.x,
              this.value.y, this.value.y, this.value.y, this.value.y, this.value.y, this.value.y);
          } else {
            getUINativeModule().gridRow.setGutter(node,
              this.value.x, this.value.x, this.value.x, this.value.x, this.value.x, this.value.x,
              this.value.y.xs, this.value.y.sm, this.value.y.md, this.value.y.lg, this.value.y.xl, this.value.y.xxl);
          }
        } else {
          if (isNumber(this.value.y)) {
            getUINativeModule().gridRow.setGutter(node,
              this.value.x.xs, this.value.x.sm, this.value.x.md, this.value.x.lg, this.value.x.xl, this.value.x.xxl,
              this.value.y, this.value.y, this.value.y, this.value.y, this.value.y, this.value.y);
          } else {
            getUINativeModule().gridRow.setGutter(node,
              this.value.x.xs, this.value.x.sm, this.value.x.md, this.value.x.lg, this.value.x.xl, this.value.x.xxl,
              this.value.y.xs, this.value.y.sm, this.value.y.md, this.value.y.lg, this.value.y.xl, this.value.y.xxl);
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
class ArkGridRowComponent extends ArkComponent implements CommonMethod<GridRowAttribute> {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  onBreakpointChange(callback: (breakpoints: string) => void): GridRowAttribute {
    throw new Error('Method not implemented.');
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

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
class GridColSpanModifier extends ModifierWithKey<ArkGridColColumnOption> {
  constructor(value: ArkGridColColumnOption) {
    super(value);
  }
  static identity: Symbol = Symbol('gridColSpan');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().gridCol.resetSpan(node);
    } else {
      if (isNumber(this.value)) {
        getUINativeModule().gridCol.setSpan(node, this.value,
          this.value, this.value, this.value, this.value, this.value);
      } else {
        getUINativeModule().gridCol.setSpan(node, this.value.xs,
          this.value.sm, this.value.md, this.value.lg, this.value.xl, this.value.xxl);
      }
    }
  }
  checkObjectDiff(): boolean {
    if (isNumber(this.stageValue) && isNumber(this.value)) {
      return this.stageValue !== this.value;
    } else if (isObject(this.stageValue) && isObject(this.value)) {
      return this.stageValue.xs !== this.value.xs ||
        this.stageValue.sm !== this.value.sm ||
        this.stageValue.md !== this.value.md ||
        this.stageValue.lg !== this.value.lg ||
        this.stageValue.xl !== this.value.xl ||
        this.stageValue.xxl !== this.value.xxl;
    } else {
      return true;
    }
  }
}
class GridColOffsetModifier extends ModifierWithKey<ArkGridColColumnOption> {
  constructor(value: ArkGridColColumnOption) {
    super(value);
  }
  static identity: Symbol = Symbol('gridColOffset');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().gridCol.resetGridColOffset(node);
    } else {
      if (isNumber(this.value)) {
        getUINativeModule().gridCol.setGridColOffset(node, this.value,
          this.value, this.value, this.value, this.value, this.value);
      } else {
        getUINativeModule().gridCol.setGridColOffset(node, this.value.xs,
          this.value.sm, this.value.md, this.value.lg, this.value.xl, this.value.xxl);
      }
    }
  }
  checkObjectDiff(): boolean {
    if (isNumber(this.stageValue) && isNumber(this.value)) {
      return this.stageValue !== this.value;
    } else if (isObject(this.stageValue) && isObject(this.value)) {
      return this.stageValue.xs !== this.value.xs ||
        this.stageValue.sm !== this.value.sm ||
        this.stageValue.md !== this.value.md ||
        this.stageValue.lg !== this.value.lg ||
        this.stageValue.xl !== this.value.xl ||
        this.stageValue.xxl !== this.value.xxl;
    } else {
      return true;
    }
  }
}
class GridColOrderModifier extends ModifierWithKey<ArkGridColColumnOption> {
  constructor(value: ArkGridColColumnOption) {
    super(value);
  }
  static identity: Symbol = Symbol('gridColOrder');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().gridCol.resetOrder(node);
    } else {
      if (isNumber(this.value)) {
        getUINativeModule().gridCol.setOrder(node, this.value,
          this.value, this.value, this.value, this.value, this.value);
      } else {
        getUINativeModule().gridCol.setOrder(node, this.value.xs,
          this.value.sm, this.value.md, this.value.lg, this.value.xl, this.value.xxl);
      }
    }
  }
  checkObjectDiff(): boolean {
    if (isNumber(this.stageValue) && isNumber(this.value)) {
      return this.stageValue !== this.value;
    } else if (isObject(this.stageValue) && isObject(this.value)) {
      return this.stageValue.xs !== this.value.xs ||
        this.stageValue.sm !== this.value.sm ||
        this.stageValue.md !== this.value.md ||
        this.stageValue.lg !== this.value.lg ||
        this.stageValue.xl !== this.value.xl ||
        this.stageValue.xxl !== this.value.xxl;
    } else {
      return true;
    }
  }
}
interface GridColParam {
  span?: number | GridColColumnOption;
  offset?: number | GridColColumnOption;
  order?: number | GridColColumnOption;
}
class ArkGridColComponent extends ArkComponent implements GridColAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  allowChildCount(): number {
    return 1;
  }
  span(value: number | GridColColumnOption): GridColAttribute {
    modifierWithKey(this._modifiersWithKeys, GridColSpanModifier.identity, GridColSpanModifier, value);
    return this;
  }
  gridColOffset(value: number | GridColColumnOption): GridColAttribute {
    modifierWithKey(this._modifiersWithKeys, GridColOffsetModifier.identity, GridColOffsetModifier, value);
    return this;
  }
  order(value: number | GridColColumnOption): GridColAttribute {
    modifierWithKey(this._modifiersWithKeys, GridColOrderModifier.identity, GridColOrderModifier, value);
    return this;
  }
  initialize(value: Object[]): GridColAttribute {
    if (value[0] !== undefined) {
      modifierWithKey(this._modifiersWithKeys, GridColSpanModifier.identity,
        GridColSpanModifier, (value[0] as GridColParam).span);
      modifierWithKey(this._modifiersWithKeys, GridColOffsetModifier.identity,
        GridColOffsetModifier, (value[0] as GridColParam).offset);
      modifierWithKey(this._modifiersWithKeys, GridColOrderModifier.identity,
        GridColOrderModifier, (value[0] as GridColParam).order);
    } else {
      modifierWithKey(this._modifiersWithKeys, GridColSpanModifier.identity,
        GridColSpanModifier, null);
      modifierWithKey(this._modifiersWithKeys, GridColOffsetModifier.identity,
        GridColOffsetModifier, null);
      modifierWithKey(this._modifiersWithKeys, GridColOrderModifier.identity,
        GridColOrderModifier, null);
    }
    return this;
  }
}

// @ts-ignore
globalThis.GridCol.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkGridColComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.GridColModifier(nativePtr, classType);
  });
};

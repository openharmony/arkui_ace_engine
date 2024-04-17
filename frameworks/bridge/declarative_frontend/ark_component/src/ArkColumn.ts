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
class ColumnAlignItemsModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('columnAlignItems');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().column.resetAlignItems(node);
    } else {
      getUINativeModule().column.setAlignItems(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class ColumnJustifyContentModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('columnJustifyContent');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().column.resetJustifyContent(node);
    } else {
      getUINativeModule().column.setJustifyContent(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class ColumnSpaceModifier extends ModifierWithKey<string | number> {
  constructor(value: string | number) {
    super(value);
  }
  static identity:Symbol = Symbol('columnSpace');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().column.resetSapce(node);
    }
    else {
      getUINativeModule().column.setSpace(node, this.value);
    }
  }
  checkObjectDiff() : boolean {
    return this.stageValue !== this.value;
  }
}
interface ColumnParam {
  space: string | number;
}
class ArkColumnComponent extends ArkComponent implements CommonMethod<ColumnAttribute> {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  initialize(value: Object[]): ColumnAttribute {
    if (value[0] !== undefined) {
      modifierWithKey(this._modifiersWithKeys, ColumnSpaceModifier.identity, ColumnSpaceModifier, (value[0] as ColumnParam).space);
    }
    return this
  }
  alignItems(value: HorizontalAlign): ColumnAttribute {
    modifierWithKey(this._modifiersWithKeys, ColumnAlignItemsModifier.identity, ColumnAlignItemsModifier, value);
    return this;
  }
  justifyContent(value: FlexAlign): ColumnAttribute {
    modifierWithKey(this._modifiersWithKeys, ColumnJustifyContentModifier.identity, ColumnJustifyContentModifier, value);
    return this;
  }
  pointLight(value: PointLightStyle): ColumnAttribute {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.Column.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkColumnComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.ColumnModifier(nativePtr, classType);
  });
};

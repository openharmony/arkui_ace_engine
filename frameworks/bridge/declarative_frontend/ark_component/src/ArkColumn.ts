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

/// <reference path="./import.ts" />
class ColumnAlignItemsModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('columnAlignItems');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().column.resetAlignItems(node);
    } else {
      GetUINativeModule().column.setAlignItems(node, this.value!);
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
      GetUINativeModule().column.resetJustifyContent(node);
    } else {
      GetUINativeModule().column.setJustifyContent(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class ArkColumnComponent extends ArkComponent implements CommonMethod<ColumnAttribute>{
  constructor(nativePtr: KNode) {
    super(nativePtr);
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
  monopolizeEvents(monopolize: boolean): this {
    throw new Error("Method not implemented.");
  }
}
// @ts-ignore
globalThis.Column.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkColumnComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
}
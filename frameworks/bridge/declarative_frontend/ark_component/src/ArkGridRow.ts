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
class ArkGridRowComponent extends ArkComponent implements CommonMethod<GridRowAttribute> {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  onBreakpointChange(callback: (breakpoints: string) => void): GridRowAttribute {
    throw new Error('Method not implemented.');
  }
  alignItems(value: ItemAlign): GridRowAttribute {
    modifierWithKey(this._modifiersWithKeys, GridRowAlignItemsModifier.identity, GridRowAlignItemsModifier, value);
    return this;
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.GridRow.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkGridRowComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};
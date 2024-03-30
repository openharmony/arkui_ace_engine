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

class RowSplitResizeableModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('rowSplitResizeable');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().rowSplit.resetResizeable(node);
    } else {
      getUINativeModule().rowSplit.setResizeable(node, this.value);
    }
  }
}
class RowSplitClipModifier extends ModifierWithKey<boolean | object> {
  constructor(value: boolean | object) {
    super(value);
  }
  static identity: Symbol = Symbol('rowSplitClip');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetClipWithEdge(node);
    } else {
      getUINativeModule().common.setClipWithEdge(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return true;
  }
}

class ArkRowSplitComponent extends ArkComponent implements RowSplitAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  resizeable(value: boolean): RowSplitAttribute {
    modifierWithKey(this._modifiersWithKeys, RowSplitResizeableModifier.identity, RowSplitResizeableModifier, value);
    return this;
  }
  clip(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): this {
    modifierWithKey(this._modifiersWithKeys, RowSplitClipModifier.identity, RowSplitClipModifier, value);
    return this;
  }
}
// @ts-ignore
globalThis.RowSplit.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkRowSplitComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.RowSplitModifier(nativePtr, classType);
  });
};

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
class ColumnSplitDividerModifier extends ModifierWithKey<ColumnSplitDividerStyle | null> {
  constructor(value: ColumnSplitDividerStyle | null) {
    super(value);
  }
  static identity: Symbol = Symbol('columnSplitDivider');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().columnSplit.resetDivider(node);
    } else {
      getUINativeModule().columnSplit.setDivider(node, this.value.startMargin, this.value.endMargin);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.startMargin, this.value.startMargin) ||
      !isBaseOrResourceEqual(this.stageValue.endMargin, this.value.endMargin);
  }
}
class ColumnSplitResizeableModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('columnSplitResizeable');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().columnSplit.resetResizeable(node);
    } else {
      getUINativeModule().columnSplit.setResizeable(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}
class ColumnSplitClipModifier extends ModifierWithKey<boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute> {
  constructor(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute) {
    super(value);
  }
  static identity: Symbol = Symbol('columnSplitClip');
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
class ArkColumnSplitComponent extends ArkComponent implements CommonMethod<ColumnSplitAttribute> {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  resizeable(value: boolean): ColumnSplitAttribute {
    modifierWithKey(this._modifiersWithKeys, ColumnSplitResizeableModifier.identity, ColumnSplitResizeableModifier, value);
    return this;
  }
  divider(value: ColumnSplitDividerStyle | null): ColumnSplitAttribute {
    modifierWithKey(this._modifiersWithKeys, ColumnSplitDividerModifier.identity, ColumnSplitDividerModifier, value);
    return this;
  }
  clip(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): this {
    modifierWithKey(this._modifiersWithKeys, ColumnSplitClipModifier.identity, ColumnSplitClipModifier, value);
    return this;
  }
}
// @ts-ignore
globalThis.ColumnSplit.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkColumnSplitComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.ColumnSplitModifier(nativePtr, classType);
  });
};

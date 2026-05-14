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

/// <reference path='./import.ts' />

class ArkLazyVWaterFlowLayoutComponent extends ArkComponent implements LazyVWaterFlowLayoutAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  columnsGap(value: LengthMetrics): this {
    modifierWithKey(this._modifiersWithKeys, LazyWaterFlowColumnsGapModifier.identity, LazyWaterFlowColumnsGapModifier, value);
    return this;
  }
  rowsGap(value: LengthMetrics): this {
    modifierWithKey(this._modifiersWithKeys, LazyWaterFlowRowsGapModifier.identity, LazyWaterFlowRowsGapModifier, value);
    return this;
  }
  columnsTemplate(value: string | ItemFillPolicy): this {
    modifierWithKey(this._modifiersWithKeys, LazyWaterFlowColumnsTemplateModifier.identity, LazyWaterFlowColumnsTemplateModifier, value);
    return this;
  }
  onVisibleIndexesChange(callback: ((start: number, end: number) => void) | undefined): this {
    modifierWithKey(this._modifiersWithKeys, LazyWaterFlowOnVisibleIndexesChangeModifier.identity,
      LazyWaterFlowOnVisibleIndexesChangeModifier, callback);
    return this;
  }
}

class LazyWaterFlowColumnsTemplateModifier extends ModifierWithKey<string | ItemFillPolicy> {
  constructor(value: string | ItemFillPolicy) {
    super(value);
  }
  static identity: Symbol = Symbol('lazyVWaterFlowColumnsTemplate');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().lazyVWaterFlowLayout.resetColumnsTemplate(node);
    } else if (isObject(this.value)) {
      getUINativeModule().lazyVWaterFlowLayout.setItemFillPolicy(node, this.value);
    } else if (isString(this.value)) {
      getUINativeModule().lazyVWaterFlowLayout.setColumnsTemplate(node, this.value);
    } else {
      getUINativeModule().lazyVWaterFlowLayout.resetColumnsTemplate(node);
    }
  }
}

class LazyWaterFlowColumnsGapModifier extends ModifierWithKey<LengthMetrics> {
  constructor(value: LengthMetrics) {
    super(value);
  }
  static identity: Symbol = Symbol('lazyVWaterFlowColumnsGap');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset || !isObject(this.value)) {
      getUINativeModule().lazyVWaterFlowLayout.resetColumnsGap(node);
    } else {
      getUINativeModule().lazyVWaterFlowLayout.setColumnsGap(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class LazyWaterFlowRowsGapModifier extends ModifierWithKey<LengthMetrics> {
  constructor(value: LengthMetrics) {
    super(value);
  }
  static identity: Symbol = Symbol('lazyVWaterFlowRowsGap');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset || !isObject(this.value)) {
      getUINativeModule().lazyVWaterFlowLayout.resetRowsGap(node);
    } else {
      getUINativeModule().lazyVWaterFlowLayout.setRowsGap(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class LazyWaterFlowOnVisibleIndexesChangeModifier extends ModifierWithKey<((start: number, end: number) => void) | undefined> {
  constructor(value: ((start: number, end: number) => void) | undefined) {
    super(value);
  }
  static identity: Symbol = Symbol('lazyVWaterFlowOnVisibleIndexesChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset || !isFunction(this.value)) {
      getUINativeModule().lazyVWaterFlowLayout.resetOnVisibleIndexesChange(node);
    } else {
      getUINativeModule().lazyVWaterFlowLayout.setOnVisibleIndexesChange(node, this.value);
    }
  }
}

// @ts-ignore
if (globalThis.LazyVWaterFlowLayout !== undefined) {
  // @ts-ignore
  globalThis.LazyVWaterFlowLayout.attributeModifier = function (modifier: ArkComponent): void {
    attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
      return new ArkLazyVWaterFlowLayoutComponent(nativePtr);
    }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
      return new modifierJS.LazyVWaterFlowLayoutModifier(nativePtr, classType);
    });
  };
}

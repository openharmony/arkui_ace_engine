/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

class ArkLazyGridLayout<T> extends ArkComponent implements LazyGridLayoutAttribute<T> {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  columnsGap(value: LengthMetrics): this {
    modifierWithKey(this._modifiersWithKeys, LazyGridColumnsGapModifier.identity, LazyGridColumnsGapModifier, value);
    return this;
  }
  rowsGap(value: LengthMetrics): this {
    modifierWithKey(this._modifiersWithKeys, LazyGridRowsGapModifier.identity, LazyGridRowsGapModifier, value);
    return this;
  }
}

class ArkLazyVGridLayoutComponent extends ArkLazyGridLayout<ArkLazyVGridLayoutComponent> implements LazyVGridLayoutAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  columnsTemplate(value: string): this {
    modifierWithKey(this._modifiersWithKeys, LazyGridColumnsTemplateModifier.identity, LazyGridColumnsTemplateModifier, value);
    return this;
  }
}

class LazyGridColumnsTemplateModifier extends ModifierWithKey<string> {
  constructor(value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('lazyGridColumnsTemplate');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().lazyVGridLayout.resetColumnsTemplate(node);
    } else {
      getUINativeModule().lazyVGridLayout.setColumnsTemplate(node, this.value);
    }
  }
}

class LazyGridColumnsGapModifier extends ModifierWithKey<LengthMetrics> {
  constructor(value: LengthMetrics) {
    super(value);
  }
  static identity: Symbol = Symbol('lazyGridColumnsGap');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset || !isObject(this.value)) {
      getUINativeModule().lazyGridLayout.resetColumnsGap(node);
    } else {
      getUINativeModule().lazyGridLayout.setColumnsGap(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class LazyGridRowsGapModifier extends ModifierWithKey<LengthMetrics> {
  constructor(value: LengthMetrics) {
    super(value);
  }
  static identity: Symbol = Symbol('lazyGridRowsGap');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset || !isObject(this.value)) {
      getUINativeModule().lazyGridLayout.resetRowsGap(node);
    } else {
      getUINativeModule().lazyGridLayout.setRowsGap(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

// @ts-ignore
globalThis.LazyVGridLayout.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkLazyVGridLayoutComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.LazyVGridLayoutModifier(nativePtr, classType);
  });
};

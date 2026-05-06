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

class ArkLazyVWaterFlowLayoutComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  columnsGap(value) {
    modifierWithKey(this._modifiersWithKeys, LazyVWaterFlowColumnsGapModifier.identity,
      LazyVWaterFlowColumnsGapModifier, value);
    return this;
  }
  rowsGap(value) {
    modifierWithKey(this._modifiersWithKeys, LazyVWaterFlowRowsGapModifier.identity,
      LazyVWaterFlowRowsGapModifier, value);
    return this;
  }
  columnsTemplate(value) {
    modifierWithKey(this._modifiersWithKeys, LazyVWaterFlowColumnsTemplateModifier.identity,
      LazyVWaterFlowColumnsTemplateModifier, value);
    return this;
  }
  onVisibleIndexesChange(callback) {
    modifierWithKey(this._modifiersWithKeys, LazyVWaterFlowOnVisibleIndexesChangeModifier.identity,
      LazyVWaterFlowOnVisibleIndexesChangeModifier, callback);
    return this;
  }
}

class LazyVWaterFlowColumnsTemplateModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().lazyVWaterFlowLayout.resetColumnsTemplate(node);
    } else if (isObject(this.value)) {
      getUINativeModule().lazyVWaterFlowLayout.setItemFillPolicy(node, this.value);
    } else if (typeof this.value === 'string') {
      getUINativeModule().lazyVWaterFlowLayout.setColumnsTemplate(node, this.value);
    } else {
      getUINativeModule().lazyVWaterFlowLayout.resetColumnsTemplate(node);
    }
  }
}
LazyVWaterFlowColumnsTemplateModifier.identity = Symbol('lazyVWaterFlowColumnsTemplate');

class LazyVWaterFlowColumnsGapModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset || !isObject(this.value)) {
      getUINativeModule().lazyVWaterFlowLayout.resetColumnsGap(node);
    } else {
      getUINativeModule().lazyVWaterFlowLayout.setColumnsGap(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
LazyVWaterFlowColumnsGapModifier.identity = Symbol('lazyVWaterFlowColumnsGap');

class LazyVWaterFlowRowsGapModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset || !isObject(this.value)) {
      getUINativeModule().lazyVWaterFlowLayout.resetRowsGap(node);
    } else {
      getUINativeModule().lazyVWaterFlowLayout.setRowsGap(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
LazyVWaterFlowRowsGapModifier.identity = Symbol('lazyVWaterFlowRowsGap');

class LazyVWaterFlowOnVisibleIndexesChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset || !isFunction(this.value)) {
      getUINativeModule().lazyVWaterFlowLayout.resetOnVisibleIndexesChange(node);
    } else {
      getUINativeModule().lazyVWaterFlowLayout.setOnVisibleIndexesChange(node, this.value);
    }
  }
}
LazyVWaterFlowOnVisibleIndexesChangeModifier.identity = Symbol('lazyVWaterFlowOnVisibleIndexesChange');

class LazyVWaterFlowLayout extends JSContainerBase {
  static create() {
    getUINativeModule().loadNativeModule('LazyVWaterFlowLayout');
    getUINativeModule().lazyVWaterFlowLayout.create();
  }
  static columnsGap(value) {
    getUINativeModule().lazyVWaterFlowLayout.setColumnsGap(true, value);
    return this;
  }
  static rowsGap(value) {
    getUINativeModule().lazyVWaterFlowLayout.setRowsGap(true, value);
    return this;
  }
  static columnsTemplate(value) {
    if (isObject(value)) {
      getUINativeModule().lazyVWaterFlowLayout.setItemFillPolicy(true, value);
    } else {
      getUINativeModule().lazyVWaterFlowLayout.setColumnsTemplate(true, value);
    }
    return this;
  }
  static onVisibleIndexesChange(callback) {
    getUINativeModule().lazyVWaterFlowLayout.setOnVisibleIndexesChange(true, callback);
    return this;
  }
  static attributeModifier(modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkLazyVWaterFlowLayoutComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.LazyVWaterFlowLayoutModifier(nativePtr, classType);
    });
  }
}

function createComponent(nativePtr, classType) {
  return new ArkLazyVWaterFlowLayoutComponent(nativePtr, classType);
}

function exportComponent() {
  globalThis.ArkLazyVWaterFlowLayoutComponent = ArkLazyVWaterFlowLayoutComponent;
}

function exportView() {
  globalThis.LazyVWaterFlowLayout = LazyVWaterFlowLayout;
}

function loadComponent() {}

export default {
  LazyVWaterFlowLayout,
  ArkLazyVWaterFlowLayoutComponent,
  createComponent,
  exportComponent,
  exportView,
  loadComponent
};

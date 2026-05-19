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

class SpaceModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().lazyColumnLayout.resetSpace(node);
    } else {
      getUINativeModule().lazyColumnLayout.setSpace(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SpaceModifier.identity = Symbol('space');

class AlignItemsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().lazyColumnLayout.resetAlignItems(node);
    } else {
      getUINativeModule().lazyColumnLayout.setAlignItems(node, this.value);
    }
  }
}
AlignItemsModifier.identity = Symbol('alignItems');

class OnVisibleIndexesChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().lazyColumnLayout.resetOnVisibleIndexesChange(node);
    } else {
      getUINativeModule().lazyColumnLayout.setOnVisibleIndexesChange(node, this.value);
    }
  }
}
OnVisibleIndexesChangeModifier.identity = Symbol('onVisibleIndexesChange');

class ArkLazyColumnLayoutComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  space(value) {
    modifierWithKey(this._modifiersWithKeys, SpaceModifier.identity, SpaceModifier, value);
    return this;
  }
  alignItems(value) {
    modifierWithKey(this._modifiersWithKeys, AlignItemsModifier.identity, AlignItemsModifier, value);
    return this;
  }
  onVisibleIndexesChange(event) {
    modifierWithKey(this._modifiersWithKeys, OnVisibleIndexesChangeModifier.identity, OnVisibleIndexesChangeModifier, event);
    return this;
  }
}

class LazyColumnLayout extends JSContainerBase {
  static create() {
    getUINativeModule().loadNativeModule('LazyColumnLayout');
    getUINativeModule().lazyColumnLayout.create();
  }
  static space(value) {
    getUINativeModule().lazyColumnLayout.setSpace(true, value);
    return this;
  }
  static alignItems(value) {
    getUINativeModule().lazyColumnLayout.setAlignItems(true, value);
    return this;
  }
  static onVisibleIndexesChange(value) {
    getUINativeModule().lazyColumnLayout.setOnVisibleIndexesChange(true, value);
    return this;
  }
  static attributeModifier(modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
        return new ArkLazyColumnLayoutComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
        return new modifierJS.LazyColumnLayoutModifier(nativePtr, classType);
    });
  }
  static onClick(value) {
    __Common__.onClick(value);
  }
  static onKeyEvent(value) {
    __Common__.onKeyEvent(value);
  }
  static onDeleteEvent(value) {
    __Common__.onDeleteEvent(value);
  }
  static onAttach(value) {
    __Common__.onAttach(value);
  }
  static onAppear(value) {
    __Common__.onAppear(value);
  }
  static onDetach(value) {
    __Common__.onDetach(value);
  }
  static onDisAppear(value) {
    __Common__.onDisAppear(value);
  }
  static onTouch(value) {
    __Common__.onTouch(value);
  }
  static onHover(value) {
    __Common__.onHover(value);
  }
}

function createComponent(nativePtr, classType) {
  return new ArkLazyColumnLayoutComponent(nativePtr, classType);
}

function exportComponent() {
  globalThis.ArkLazyColumnLayoutComponent = ArkLazyColumnLayoutComponent;
}

function exportView() {
  globalThis.LazyColumnLayout = LazyColumnLayout;
}

function loadComponent() {}

export default { ArkLazyColumnLayoutComponent, LazyColumnLayout,
  createComponent, exportComponent, exportView, loadComponent };

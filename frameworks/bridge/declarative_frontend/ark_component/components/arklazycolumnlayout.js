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

class LazyColumnStickyModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset || !isNumber(this.value)) {
      getUINativeModule().lazyColumnLayout.resetSticky(node);
    } else {
      getUINativeModule().lazyColumnLayout.setSticky(node, this.value);
    }
  }
}
LazyColumnStickyModifier.identity = Symbol('lazyColumnLayoutSticky');

class LazyColumnHeaderModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset || (!isObject(this.value) && !isFunction(this.value))) {
      getUINativeModule().lazyColumnLayout.resetHeader(node);
    } else {
      getUINativeModule().lazyColumnLayout.setHeader(node, this.value);
    }
  }
}
LazyColumnHeaderModifier.identity = Symbol('lazyColumnLayoutHeader');

class LazyColumnFooterModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset || (!isObject(this.value) && !isFunction(this.value))) {
      getUINativeModule().lazyColumnLayout.resetFooter(node);
    } else {
      getUINativeModule().lazyColumnLayout.setFooter(node, this.value);
    }
  }
}
LazyColumnFooterModifier.identity = Symbol('lazyColumnLayoutFooter');

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
  sticky(value) {
    modifierWithKey(this._modifiersWithKeys, LazyColumnStickyModifier.identity, LazyColumnStickyModifier, value);
    return this;
  }
  header(value) {
    modifierWithKey(this._modifiersWithKeys, LazyColumnHeaderModifier.identity, LazyColumnHeaderModifier, value);
    return this;
  }
  footer(value) {
    modifierWithKey(this._modifiersWithKeys, LazyColumnFooterModifier.identity, LazyColumnFooterModifier, value);
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
  static sticky(value) {
    getUINativeModule().lazyColumnLayout.setSticky(true, value);
    return this;
  }
  static header(value) {
    getUINativeModule().lazyColumnLayout.setHeader(true, value);
    return this;
  }
  static footer(value) {
    getUINativeModule().lazyColumnLayout.setFooter(true, value);
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

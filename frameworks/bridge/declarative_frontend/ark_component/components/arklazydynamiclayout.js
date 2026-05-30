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

class OnVisibleIndexesChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().dynamiclayout.setOnVisibleIndexesChange(node, undefined);
    } else {
      getUINativeModule().dynamiclayout.setOnVisibleIndexesChange(node, this.value);
    }
  }
}
OnVisibleIndexesChangeModifier.identity = Symbol('onVisibleIndexesChange');

class ArkLazyDynamicLayoutComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  onVisibleIndexesChange(value) {
    modifierWithKey(this._modifiersWithKeys, OnVisibleIndexesChangeModifier.identity, OnVisibleIndexesChangeModifier, value);
    return this;
  }
}

class LazyDynamicLayout extends JSContainerBase {
  static create(params) {
    getUINativeModule().loadNativeModule('DynamicLayout');
    getUINativeModule().dynamiclayout.createLazyDynamicLayout(params);
  }
  static attributeModifier(modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
        return new ArkLazyDynamicLayoutComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
        return new modifierJS.LazyDynamicLayoutModifier(nativePtr, classType);
    });
  }
  static onVisibleIndexesChange(value) {
    getUINativeModule().dynamiclayout.setOnVisibleIndexesChange(true, value);
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
  return new ArkLazyDynamicLayoutComponent(nativePtr, classType);
}

export default { LazyDynamicLayout, createComponent };
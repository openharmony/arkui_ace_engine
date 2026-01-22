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
class ArkMenuItemGroupComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
}

class JSMenuItemGroup extends JSViewAbstract {
  static create(params) {
    getUINativeModule().menuitemgroup.create(params);
  }
  static attributeModifier(modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkMenuItemGroupComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.MenuItemGroupModifier(nativePtr, classType);
    });
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
}

function createComponent(nativePtr, classType) {
  return new ArkMenuItemGroupComponent(nativePtr, classType);
}

function exportComponent() {
  globalThis.ArkMenuItemGroupComponent = ArkMenuItemGroupComponent;
}

function exportView() {
  globalThis.MenuItemGroup = JSMenuItemGroup;
}

export default { ArkMenuItemGroupComponent, createComponent, exportComponent, exportView };
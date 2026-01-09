/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/// <reference path='./import.ts' />
class ArkFlowItemComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  initialize(value) {
    return this;
  }
  allowChildCount() {
    return 1;
  }
}

class JSFlowItem extends JSContainerBase {
  static create(params) {
    getUINativeModule().flowItem.create();
  }
  static onClick(value) {
    __Common__.onClick(value);
  }
  static onTouch(value) {
    __Common__.onTouch(value);
  }
  static onHover(value) {
    __Common__.onHover(value);
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
  static remoteMessage(value) {
    __Common__.remoteMessage(value);
  }
  static attributeModifier(modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkFlowItemComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.CommonModifier(nativePtr, classType);
    });
  };
}

function createComponent(nativePtr, classType) {
  return new ArkFlowItemComponent(nativePtr, classType);
}

function exportComponent() {
  globalThis.ArkFlowItemComponent = ArkFlowItemComponent;
}

function exportView() {
  globalThis.FlowItem = JSFlowItem;
}

export default { ArkFlowItemComponent, createComponent, exportComponent, exportView };
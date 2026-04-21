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
class RowSplitResizeableModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().rowSplit.resetResizeable(node);
    }
    else {
      getUINativeModule().rowSplit.setResizeable(node, this.value);
    }
  }
}
RowSplitResizeableModifier.identity = Symbol('rowSplitResizeable');
class RowSplitClipModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetClipWithEdge(node);
    }
    else {
      getUINativeModule().common.setClipWithEdge(node, this.value);
    }
  }
  checkObjectDiff() {
    return true;
  }
}
RowSplitClipModifier.identity = Symbol('rowSplitClip');
class ArkRowSplitComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  resizeable(value) {
    modifierWithKey(this._modifiersWithKeys, RowSplitResizeableModifier.identity, RowSplitResizeableModifier, value);
    return this;
  }
  clip(value) {
    modifierWithKey(this._modifiersWithKeys, RowSplitClipModifier.identity, RowSplitClipModifier, value);
    return this;
  }
}

class JSRowSplit extends JSContainerBase {
  static create() {
    getUINativeModule().rowSplit.create();
  }
  static resizeable(value) {
    getUINativeModule().rowSplit.setResizeable(true, value);
  }
  static clip(value) {
    getUINativeModule().rowSplit.setRowSplitClip(true, value);
  }
  static attributeModifier(modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkRowSplitComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.RowSplitModifier(nativePtr, classType);
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
    __Common__.onAttach(value);
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
  static remoteMessage(value) {
    __Common__.remoteMessage(value);
  }
}

function createComponent(nativePtr, classType) {
  return new ArkRowSplitComponent(nativePtr, classType);
}

function exportComponent() {
  globalThis.ArkRowSplitComponent = ArkRowSplitComponent;
}

function exportView() {
  globalThis.RowSplit = JSRowSplit;
}
function loadComponent() {}
export default { ArkRowSplitComponent, createComponent, exportComponent, exportView, loadComponent };
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
class ArkFolderStackComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  alignContent(value) {
    modifierWithKey(this._modifiersWithKeys, FolderStackAlignContentModifier.identity, FolderStackAlignContentModifier, value);
    return this;
  }
  enableAnimation(value) {
    modifierWithKey(this._modifiersWithKeys, FolderStackEnableAnimationModifier.identity, FolderStackEnableAnimationModifier, value);
    return this;
  }
  autoHalfFold(value) {
    modifierWithKey(this._modifiersWithKeys, FolderStackAutoHalfFoldModifier.identity, FolderStackAutoHalfFoldModifier, value);
    return this;
  }
  onFolderStateChange(callback) {
    modifierWithKey(this._modifiersWithKeys, FolderStackOnFolderStateChangeModifier.identity,
      FolderStackOnFolderStateChangeModifier, callback);
    return this;
  }
  onHoverStatusChange(handler) {
    modifierWithKey(this._modifiersWithKeys, FolderStackOnHoverStatusChangeModifier.identity,
      FolderStackOnHoverStatusChangeModifier, handler);
    return this;
  }
}

class FolderStackAlignContentModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().stack.resetAlignContent(node);
    } else {
      getUINativeModule().stack.setAlignContent(node, this.value);
    }
  }
}
FolderStackAlignContentModifier.identity = Symbol('folderStackAlignContent');

class FolderStackEnableAnimationModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().folderStack.resetEnableAnimation(node);
    } else {
      getUINativeModule().folderStack.setEnableAnimation(node, this.value);
    }
  }
}
FolderStackEnableAnimationModifier.identity = Symbol('folderStackEnableAnimation');

class FolderStackAutoHalfFoldModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().folderStack.resetAutoHalfFold(node);
    } else {
      getUINativeModule().folderStack.setAutoHalfFold(node, this.value);
    }
  }
}
FolderStackAutoHalfFoldModifier.identity = Symbol('folderStackAutoHalfFold');

class FolderStackOnFolderStateChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().folderStack.resetOnFolderStateChange(node);
    } else {
      getUINativeModule().folderStack.setOnFolderStateChange(node, this.value);
    }
  }
}
FolderStackOnFolderStateChangeModifier.identity = Symbol('folderStackOnFolderStateChange');

class FolderStackOnHoverStatusChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().folderStack.resetOnHoverStatusChange(node);
    } else {
      getUINativeModule().folderStack.setOnHoverStatusChange(node, this.value);
    }
  }
}
FolderStackOnHoverStatusChangeModifier.identity = Symbol('folderStackOnHoverStatusChange');

class JSFolderStack extends JSContainerBase {
  static create(params) {
    getUINativeModule().folderStack.create(params);
  }
  static alignContent(value) {
    getUINativeModule().folderStack.setAlignContent(true, value);
  }
  static enableAnimation(value) {
    getUINativeModule().folderStack.setEnableAnimation(true, value);
  }
  static autoHalfFold(value) {
    getUINativeModule().folderStack.setAutoHalfFold(true, value);
  }
  static onFolderStateChange(callback) {
    getUINativeModule().folderStack.setOnFolderStateChange(true, callback);
  }
  static onHoverStatusChange(handler) {
    getUINativeModule().folderStack.setOnHoverStatusChange(true, handler);
  }
  static attributeModifier(modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkFolderStackComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.FolderStackModifier(nativePtr, classType);
    });
  }
  static onDetach(value) {
    __Common__.onAttach(value);
  }
  static onDisAppear(value) {
    __Common__.onDisAppear(value);
  }  
}

function createComponent(nativePtr, classType) {
  return new ArkFolderStackComponent(nativePtr, classType);
}

function exportComponent() {
  globalThis.ArkFolderStackComponent = ArkFolderStackComponent;
}

function exportView() {
  globalThis.FolderStack = JSFolderStack;
}
function loadComponent() {}
export default { ArkFolderStackComponent, createComponent, exportComponent, exportView, loadComponent };

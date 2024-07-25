/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

interface FolderStackParam {
  alignContent?: Alignment;
  enableAnimation?: boolean;
  autoHalfFold?: boolean;
}

class ArkFolderStackComponent extends ArkComponent implements FolderStackAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  alignContent(value: Alignment): FolderStackAttribute {
    modifierWithKey(this._modifiersWithKeys, FolderStackAlignContentModifier.identity, FolderStackAlignContentModifier, value);
    return this;
  }
  enableAnimation(value: boolean): FolderStackAttribute {
    modifierWithKey(this._modifiersWithKeys, FolderStackEnableAnimationModifier.identity, FolderStackEnableAnimationModifier, value);
    return this;
  }
  autoHalfFold(value: boolean): FolderStackAttribute {
    modifierWithKey(this._modifiersWithKeys, FolderStackAutoHalfFoldModifier.identity, FolderStackAutoHalfFoldModifier, value);
    return this;
  }
}

class FolderStackAlignContentModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('folderStackAlignContent');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().stack.resetAlignContent(node);
    } else {
      getUINativeModule().stack.setAlignContent(node, this.value!);
    }
  }
}

class FolderStackEnableAnimationModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('folderStackEnableAnimation');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().folderStack.resetEnableAnimation(node);
    } else {
      getUINativeModule().folderStack.setEnableAnimation(node, this.value!);
    }
  }
}

class FolderStackAutoHalfFoldModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('folderStackAutoHalfFold');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().folderStack.resetAutoHalfFold(node);
    } else {
      getUINativeModule().folderStack.setAutoHalfFold(node, this.value!);
    }
  }
}
// @ts-ignore
globalThis.FolderStack.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkFolderStackComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.FolderStackModifier(nativePtr, classType);
  });
};

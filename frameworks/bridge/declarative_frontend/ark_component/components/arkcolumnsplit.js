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
class ColumnSplitDividerModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().columnSplit.resetDivider(node);
    }
    else {
      getUINativeModule().columnSplit.setDivider(node, this.value.startMargin, this.value.endMargin);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.startMargin, this.value.startMargin) ||
      !isBaseOrResourceEqual(this.stageValue.endMargin, this.value.endMargin);
  }
}
ColumnSplitDividerModifier.identity = Symbol('columnSplitDivider');
class ColumnSplitResizeableModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().columnSplit.resetResizeable(node);
    }
    else {
      getUINativeModule().columnSplit.setResizeable(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ColumnSplitResizeableModifier.identity = Symbol('columnSplitResizeable');
class ColumnSplitClipModifier extends ModifierWithKey {
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
ColumnSplitClipModifier.identity = Symbol('columnSplitClip');
class ArkColumnSplitComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  resizeable(value) {
    modifierWithKey(this._modifiersWithKeys, ColumnSplitResizeableModifier.identity, ColumnSplitResizeableModifier, value);
    return this;
  }
  divider(value) {
    modifierWithKey(this._modifiersWithKeys, ColumnSplitDividerModifier.identity, ColumnSplitDividerModifier, value);
    return this;
  }
  clip(value) {
    modifierWithKey(this._modifiersWithKeys, ColumnSplitClipModifier.identity, ColumnSplitClipModifier, value);
    return this;
  }
}

class JSColumnSplit extends JSContainerBase {
  static create() {
    getUINativeModule().columnSplit.create();
  }
  static resizeable(value) {
    getUINativeModule().columnSplit.setResizeable(true, value);
  }
  static divider(value) {
    if (!isUndefined(value) && !isNull(value)) {
      getUINativeModule().columnSplit.setDivider(true, value.startMargin, value.endMargin);
    }
  }
  static clip(value) {
    getUINativeModule().columnSplit.setColumnSplitClip(true, value);
  }
  static attributeModifier(modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkColumnSplitComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.ColumnSplitModifier(nativePtr, classType);
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
  return new ArkColumnSplitComponent(nativePtr, classType);
}

function exportComponent() {
  globalThis.ArkColumnSplitComponent = ArkColumnSplitComponent;
}

function exportView() {
  globalThis.ColumnSplit = JSColumnSplit;
}

export default { ArkColumnSplitComponent, createComponent, exportComponent, exportView };
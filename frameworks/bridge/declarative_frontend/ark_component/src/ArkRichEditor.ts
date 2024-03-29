/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
class RichEditorEnableDataDetectorModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('richEditorEnableDataDetector');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().richEditor.resetEnableDataDetector(node);
    } else {
      getUINativeModule().richEditor.setEnableDataDetector(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class RichEditorCopyOptionsModifier extends ModifierWithKey<CopyOptions> {
  constructor(value: CopyOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('richEditorCopyOptions');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().richEditor.resetCopyOptions(node);
    } else {
      getUINativeModule().richEditor.setCopyOptions(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class RichEditorSelectedBackgroundColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('richEditorSelectedBackgroundColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().richEditor.resetSelectedBackgroundColor(node);
    } else {
      getUINativeModule().richEditor.setSelectedBackgroundColor(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class RichEditorCaretColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('richEditorCaretColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().richEditor.resetCaretColor(node);
    } else {
      getUINativeModule().richEditor.setCaretColor(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class ArkRichEditorComponent extends ArkComponent implements CommonMethod<RichEditorAttribute> {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  enableDataDetector(value: boolean): RichEditorAttribute {
    modifierWithKey(this._modifiersWithKeys, RichEditorEnableDataDetectorModifier.identity, RichEditorEnableDataDetectorModifier, value);
    return this;
  }

  dataDetectorConfig(config: any): RichEditorAttribute {
    throw new Error('Method not implemented.');
  }

  copyOptions(value: CopyOptions): RichEditorAttribute {
    modifierWithKey(this._modifiersWithKeys, RichEditorCopyOptionsModifier.identity, RichEditorCopyOptionsModifier, value);
    return this;
  }

  caretColor(value: ResourceColor): RichEditorAttribute {
    modifierWithKey(this._modifiersWithKeys, RichEditorCaretColorModifier.identity, RichEditorCaretColorModifier, value);
    return this;
  }

  selectedBackgroundColor(value: ResourceColor): RichEditorAttribute {
    modifierWithKey(this._modifiersWithKeys, RichEditorSelectedBackgroundColorModifier.identity, RichEditorSelectedBackgroundColorModifier, value);
    return this;
  }

  onPaste(callback: (event?: PasteEvent) => void): RichEditorAttribute {
    throw new Error('Method not implemented.');
  }
  onReady(callback: () => void): RichEditorAttribute {
    throw new Error('Method not implemented.');
  }
  onSelect(callback: (value: RichEditorSelection) => void): RichEditorAttribute {
    throw new Error('Method not implemented.');
  }
  aboutToIMEInput(callback: (value: RichEditorInsertValue) => boolean): RichEditorAttribute {
    throw new Error('Method not implemented.');
  }
  onIMEInputComplete(callback: (value: RichEditorTextSpanResult) => void): RichEditorAttribute {
    throw new Error('Method not implemented.');
  }
  aboutToDelete(callback: (value: RichEditorDeleteValue) => boolean): RichEditorAttribute {
    throw new Error('Method not implemented.');
  }
  onDeleteComplete(callback: () => void): RichEditorAttribute {
    throw new Error('Method not implemented.');
  }
  bindSelectionMenu(spanType: RichEditorSpanType, content: CustomBuilder, responseType: ResponseType, options?: SelectionMenuOptions): RichEditorAttribute {
    throw new Error('Method not implemented.');
  }
  customKeyboard(value: CustomBuilder): RichEditorAttribute {
    throw new Error('Method not implemented.');
  }
}

// @ts-ignore
globalThis.RichEditor.attributeModifier = function (modifier: ArkComponent) {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkRichEditorComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.RichEditorModifier(nativePtr, classType);
  });
};

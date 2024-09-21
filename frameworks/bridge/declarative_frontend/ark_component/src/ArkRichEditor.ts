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

class RichEditorDataDetectorConfigModifier extends ModifierWithKey<TextDataDetectorConfig> {
  constructor(value: TextDataDetectorConfig) {
    super(value);
  }
  static identity: Symbol = Symbol('richEditorDataDetectorConfig');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().richEditor.resetDataDetectorConfig(node);
    } else {
      getUINativeModule().richEditor.setDataDetectorConfig(node, this.value.types, this.value.onDetectResultUpdate);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.types, this.value.types) ||
    !isBaseOrResourceEqual(this.stageValue.onDetectResultUpdate, this.value.onDetectResultUpdate);
  }
}

class RichEditorOnIMEInputCompleteModifier extends ModifierWithKey<(value:RichEditorTextSpanResult) => void> {
  constructor(value: (value:RichEditorTextSpanResult) => void) {
    super(value);
  }
  static identity = Symbol('richEditorOnIMEInputComplete');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().richEditor.resetOnIMEInputComplete(node);
    } else {
      getUINativeModule().richEditor.setOnIMEInputComplete(node, this.value);
    }
  }
}

class RichEditorCopyOptionsModifier extends ModifierWithKey<CopyOptions> {
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

class RichEditorOnSelectionChangeModifier extends ModifierWithKey<(value: RichEditorRange) => void> {
  constructor(value: (value: RichEditorRange) => void) {
    super(value);
  }
  static identity = Symbol('richEditorOnSelectionChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().richEditor.resetOnSelectionChange(node);
    } else {
      getUINativeModule().richEditor.setOnSelectionChange(node, this.value);
    }
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

class RichEditorOnSelectModifier extends ModifierWithKey<(value: RichEditorSelection) => void> {
  constructor(value: (value: RichEditorSelection) => void) {
    super(value);
  }
  static identity = Symbol('richEditorOnSelect');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().richEditor.resetOnSelect(node);
    } else {
      getUINativeModule().richEditor.setOnSelect(node, this.value);
    }
  }
}

class RichEditorOnSubmitModifier extends ModifierWithKey<SubmitCallback> {
  constructor(value: SubmitCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('richEditorOnSubmit');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().richEditor.resetOnSubmit(node);
    } else {
      getUINativeModule().richEditor.setOnSubmit(node, this.value);
    }
  }
}

class RichEditorAboutToIMEInputModifier extends ModifierWithKey<(value: RichEditorInsertValue) => boolean> {
  constructor(value: (value: RichEditorInsertValue) => boolean) {
    super(value);
  }
  static identity = Symbol('richEditorAboutToIMEInput');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().richEditor.resetAboutToIMEInput(node);
    } else {
      getUINativeModule().richEditor.setAboutToIMEInput(node, this.value);
    }
  }
}

class RichEditorOnReadyModifier extends ModifierWithKey<() => void> {
  constructor(value: () => void) {
    super(value);
  }
  static identity = Symbol('richEditorOnReady');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().richEditor.resetOnReady(node);
    } else {
      getUINativeModule().richEditor.setOnReady(node, this.value);
    }
  }
}

class RichEditorOnDeleteCompleteModifier extends ModifierWithKey<() => void> {
  constructor(value: () => void) {
    super(value);
  }
  static identity = Symbol('richEditorOnDeleteComplete');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().richEditor.resetOnDeleteComplete(node);
    } else {
      getUINativeModule().richEditor.setOnDeleteComplete(node, this.value);
    }
  }
}

class RichEditorOnEditingChangeModifier extends ModifierWithKey<(value: boolean) => void> {
  constructor(value: (value: boolean) => void) {
    super(value);
  }
  static identity = Symbol('richEditorOnEditingChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().richEditor.resetEditingChange(node);
    } else {
      getUINativeModule().richEditor.setEditingChange(node, this.value);
    }
  }
}

class RichEditorOnPasteModifier extends ModifierWithKey<(event?: PasteEvent) => void> {
  constructor(value: (event?: PasteEvent) => void) {
    super(value);
  }
  static identity = Symbol('richEditorOnPaste');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().richEditor.resetOnPaste(node);
    } else {
      getUINativeModule().richEditor.setOnPaste(node, this.value);
    }
  }
}

class RichEditorOnCutModifier extends ModifierWithKey<Callback<CutEvent>> {
  constructor(value: Callback<CutEvent>) {
    super(value);
  }
  static identity = Symbol('richEditorOnCut');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().richEditor.resetOnCut(node);
    } else {
      getUINativeModule().richEditor.setOnCut(node, this.value);
    }
  }
}

class RichEditorOnCopyModifier extends ModifierWithKey<Callback<CopyEvent>> {
  constructor(value: Callback<CopyEvent>) {
    super(value);
  }
  static identity = Symbol('richEditorOnCopy');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().richEditor.resetOnCopy(node);
    } else {
      getUINativeModule().richEditor.setOnCopy(node, this.value);
    }
  }
}


class RichEditorEnterKeyTypeModifier extends ModifierWithKey<EnterKeyType> {
  constructor(value: EnterKeyType) {
    super(value);
  }
  static identity: Symbol = Symbol('richEditorEnterKeyType');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().richEditor.resetEnterKeyType(node);
    } else {
      getUINativeModule().richEditor.setEnterKeyType(node, this.value!);
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

  dataDetectorConfig(config: TextDataDetectorConfig): this {
    let detectorConfig = new TextDataDetectorConfig();
    detectorConfig.types = config.types;
    detectorConfig.onDetectResultUpdate = config.onDetectResultUpdate;
    modifierWithKey(this._modifiersWithKeys, RichEditorDataDetectorConfigModifier.identity, RichEditorDataDetectorConfigModifier, detectorConfig);
    return this;
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
    modifierWithKey(this._modifiersWithKeys, RichEditorOnPasteModifier.identity, RichEditorOnPasteModifier, callback);
    return this;
  }

  onReady(callback: () => void): RichEditorAttribute {
    modifierWithKey(this._modifiersWithKeys, RichEditorOnReadyModifier.identity, RichEditorOnReadyModifier, callback);
    return this;
  }
  onSelect(callback: (value: RichEditorSelection) => void): RichEditorAttribute {
    modifierWithKey(this._modifiersWithKeys, RichEditorOnSelectModifier.identity, RichEditorOnSelectModifier, callback);
    return this;
  }

  onSubmit(callback: SubmitCallback): RichEditorAttribute {
    modifierWithKey(this._modifiersWithKeys, RichEditorOnSubmitModifier.identity, RichEditorOnSubmitModifier, callback);
    return this;
  }
  onSelectionChange(callback: (value: RichEditorRange) => void): RichEditorAttribute {
    modifierWithKey(this._modifiersWithKeys, RichEditorOnSelectionChangeModifier.identity, RichEditorOnSelectionChangeModifier, callback);
    return this;
  }
  onSubmit(callback: SubmitCallback): RichEditorAttribute {
    modifierWithKey(this._modifiersWithKeys, RichEditorOnSubmitModifier.identity, RichEditorOnSubmitModifier, callback);
    return this;
  }
  aboutToIMEInput(callback: (value: RichEditorInsertValue) => boolean): RichEditorAttribute {
    modifierWithKey(this._modifiersWithKeys, RichEditorAboutToIMEInputModifier.identity, RichEditorAboutToIMEInputModifier, callback);
    return this;
  }
  onIMEInputComplete(callback: (value: RichEditorTextSpanResult) => void): RichEditorAttribute {
    modifierWithKey(this._modifiersWithKeys, RichEditorOnIMEInputCompleteModifier.identity, RichEditorOnIMEInputCompleteModifier, callback);
    return this;
  }
  aboutToDelete(callback: (value: RichEditorDeleteValue) => boolean): RichEditorAttribute {
    throw new Error('Method not implemented.');
  }
  onDeleteComplete(callback: () => void): RichEditorAttribute {
    modifierWithKey(this._modifiersWithKeys, RichEditorOnDeleteCompleteModifier.identity, RichEditorOnDeleteCompleteModifier, callback);
    return this;
  }
  bindSelectionMenu(spanType: RichEditorSpanType, content: CustomBuilder, responseType: ResponseType, options?: SelectionMenuOptions): RichEditorAttribute {
    throw new Error('Method not implemented.');
  }
  customKeyboard(value: CustomBuilder): RichEditorAttribute {
    throw new Error('Method not implemented.');
  }
  onEditingChange(callback: (value: boolean) => void): RichEditorAttribute {
    modifierWithKey(this._modifiersWithKeys, RichEditorOnEditingChangeModifier.identity, RichEditorOnEditingChangeModifier, callback);
    return this;
  }
  onCut(callback: Callback<CutEvent>): RichEditorAttribute {
    modifierWithKey(this._modifiersWithKeys, RichEditorOnCutModifier.identity, RichEditorOnCutModifier, callback);
    return this;
  }
  onCopy(callback: Callback<CopyEvent>): RichEditorAttribute {
    modifierWithKey(this._modifiersWithKeys, RichEditorOnCopyModifier.identity, RichEditorOnCopyModifier, callback);
    return this;
  }
  enterKeyType(value: EnterKeyType): RichEditorAttribute {
    modifierWithKey(this._modifiersWithKeys, RichEditorEnterKeyTypeModifier.identity, RichEditorEnterKeyTypeModifier, value);
    return this;
  }
}

// @ts-ignore
globalThis.RichEditor.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkRichEditorComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.RichEditorModifier(nativePtr, classType);
  });
};

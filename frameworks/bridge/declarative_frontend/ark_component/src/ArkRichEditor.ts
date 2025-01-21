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

class RichEditorOnWillChangeModifier extends ModifierWithKey<(value: RichEditorChangeValue) => boolean> {
  constructor(value: (value: RichEditorChangeValue) => boolean) {
    super(value);
  }
  static identity = Symbol('richEditorOnWillChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().richEditor.resetOnWillChange(node);
    } else {
      getUINativeModule().richEditor.setOnWillChange(node, this.value);
    }
  }
}

class RichEditorOnDidChangeModifier extends ModifierWithKey<OnDidChangeCallback> {
  constructor(value: OnDidChangeCallback) {
    super(value);
  }
  static identity = Symbol('richEditorOnDidChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().richEditor.resetOnDidChange(node);
    } else {
      getUINativeModule().richEditor.setOnDidChange(node, this.value);
    }
  }
}

class RichEditorPlaceholderModifier extends ModifierWithKey<ArkPlaceholder> {
  constructor(value: ArkPlaceholder) {
    super(value);
  }
  static identity = Symbol('richEditorPlaceholder');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().richEditor.resetPlaceholder(node);
    } else {
      getUINativeModule().richEditor.setPlaceholder(node, this.value.value, this.value.style);
    }
  }
  checkObjectDiff(): boolean {
    return !(this.stageValue as ArkPlaceholder).isEqual(this.value as ArkPlaceholder);
  }
}

class RichEditorAboutToDeleteModifier extends ModifierWithKey<(value: RichEditorDeleteValue) => boolean> {
  constructor(value: (value: RichEditorDeleteValue) => boolean) {
    super(value);
  }
  static identity = Symbol('richEditorAboutToDelete');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().richEditor.resetAboutToDelete(node);
    } else {
      getUINativeModule().richEditor.setAboutToDelete(node, this.value);
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

class RichEditorEnableKeyboardOnFocusModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity = Symbol('richEditorEnableKeyboardOnFocus');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().richEditor.resetEnableKeyboardOnFocus(node);
    } else {
      getUINativeModule().richEditor.setEnableKeyboardOnFocus(node, this.value);
    }
  }
}

class RichEditorEnablePreviewTextModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity = Symbol('richEditorEnablePreviewText');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().richEditor.resetEnablePreviewText(node);
    } else {
      getUINativeModule().richEditor.setEnablePreviewText(node, this.value);
    }
  }
}

class RichEditorEditMenuOptionsModifier extends ModifierWithKey<EditMenuOptions> {
  constructor(value: EditMenuOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('richEditorEditMenuOptions');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().richEditor.resetEditMenuOptions(node);
    } else {
      getUINativeModule().richEditor.setEditMenuOptions(node, this.value);
    }
  }
}

class RichEditorBarStateModifier extends ModifierWithKey<BarState> {
  constructor(value: BarState) {
    super(value);
  }
  static identity: Symbol = Symbol('richEditorBarState');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().richEditor.resetBarState(node);
    } else {
      getUINativeModule().richEditor.setBarState(node, this.value);
    }
  }
}

class RichEditorMaxLengthModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('richEditorMaxLength');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().richEditor.resetMaxLength(node);
    } else {
      getUINativeModule().richEditor.setMaxLength(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class RichEditorMaxLinesModifier extends ModifierWithKey<number | undefined> {
  constructor(value: number | undefined) {
    super(value);
  }
  static identity: Symbol = Symbol('richEditorMaxLines');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().richEditor.resetMaxLines(node);
    } else {
      getUINativeModule().richEditor.setMaxLines(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
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
  aboutToIMEInput(callback: (value: RichEditorInsertValue) => boolean): RichEditorAttribute {
    modifierWithKey(this._modifiersWithKeys, RichEditorAboutToIMEInputModifier.identity, RichEditorAboutToIMEInputModifier, callback);
    return this;
  }
  onIMEInputComplete(callback: (value: RichEditorTextSpanResult) => void): RichEditorAttribute {
    modifierWithKey(this._modifiersWithKeys, RichEditorOnIMEInputCompleteModifier.identity, RichEditorOnIMEInputCompleteModifier, callback);
    return this;
  }
  onWillChange(callback: (value: RichEditorChangeValue) => boolean): RichEditorAttribute {
    modifierWithKey(this._modifiersWithKeys, RichEditorOnWillChangeModifier.identity, RichEditorOnWillChangeModifier, callback);
    return this;
  }
  onDidChange(callback: OnDidChangeCallback): RichEditorAttribute {
    modifierWithKey(this._modifiersWithKeys, RichEditorOnDidChangeModifier.identity, RichEditorOnDidChangeModifier, callback);
    return this;
  }
  placeholder(value: ResourceStr, style?: PlaceholderStyle): RichEditorAttribute {
    let placeholder: ArkPlaceholder = new ArkPlaceholder();
    placeholder.value = value;
    placeholder.style = style;
    modifierWithKey(this._modifiersWithKeys, RichEditorPlaceholderModifier.identity, RichEditorPlaceholderModifier, placeholder);
    return this;
  }
  aboutToDelete(callback: (value: RichEditorDeleteValue) => boolean): RichEditorAttribute {
    modifierWithKey(this._modifiersWithKeys, RichEditorAboutToDeleteModifier.identity, RichEditorAboutToDeleteModifier, callback);
    return this;
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
  enableKeyboardOnFocus(value: boolean): RichEditorAttribute {
    modifierWithKey(this._modifiersWithKeys, RichEditorEnableKeyboardOnFocusModifier.identity, RichEditorEnableKeyboardOnFocusModifier, value);
    return this;
  }
  enablePreviewText(value: boolean): RichEditorAttribute {
    modifierWithKey(this._modifiersWithKeys, RichEditorEnablePreviewTextModifier.identity, RichEditorEnablePreviewTextModifier, value);
    return this;
  }
  editMenuOptions(value: EditMenuOptions): RichEditorAttribute {
    modifierWithKey(this._modifiersWithKeys, RichEditorEditMenuOptionsModifier.identity, RichEditorEditMenuOptionsModifier, value);
    return this;
  }
  barState(value: BarState): RichEditorAttribute {
    modifierWithKey(this._modifiersWithKeys, RichEditorBarStateModifier.identity, RichEditorBarStateModifier, value);
    return this;
  }
  maxLength(value: number): RichEditorAttribute {
    modifierWithKey(this._modifiersWithKeys, RichEditorMaxLengthModifier.identity, RichEditorMaxLengthModifier, value);
    return this;
  }
  maxLines(value: number): RichEditorAttribute {
    modifierWithKey(this._modifiersWithKeys, RichEditorMaxLinesModifier.identity, RichEditorMaxLinesModifier, value);
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

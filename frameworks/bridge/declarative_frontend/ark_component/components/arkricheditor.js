/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
class ArkRichEditorComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  enableDataDetector(value) {
    modifierWithKey(this._modifiersWithKeys, RichEditorEnableDataDetectorModifier.identity, RichEditorEnableDataDetectorModifier, value);
    return this;
  }
  dataDetectorConfig(config) {
    if (config === undefined || config === null) {
      return this;
    }
    let detectorConfig = new TextDataDetectorConfig();
    detectorConfig.types = config.types;
    detectorConfig.onDetectResultUpdate = config.onDetectResultUpdate;
    detectorConfig.color = config.color;
    if (config.decoration) {
      detectorConfig.decorationType = config.decoration.type;
      detectorConfig.decorationColor = config.decoration.color;
      detectorConfig.decorationStyle = config.decoration.style;
    }
    modifierWithKey(this._modifiersWithKeys, RichEditorDataDetectorConfigModifier.identity, RichEditorDataDetectorConfigModifier, detectorConfig);
    return this;
  }
  copyOptions(value) {
    modifierWithKey(this._modifiersWithKeys, RichEditorCopyOptionsModifier.identity, RichEditorCopyOptionsModifier, value);
    return this;
  }

  caretColor(value) {
    modifierWithKey(this._modifiersWithKeys, RichEditorCaretColorModifier.identity, RichEditorCaretColorModifier, value);
    return this;
  }

  onSelectionChange(callback) {
    modifierWithKey(this._modifiersWithKeys, RichEditorOnSelectionChangeModifier.identity, RichEditorOnSelectionChangeModifier, callback);
    return this;
  }

  selectedBackgroundColor(value) {
    modifierWithKey(this._modifiersWithKeys, RichEditorSelectedBackgroundColorModifier.identity, RichEditorSelectedBackgroundColorModifier, value);
    return this;
  }

  enterKeyType(value) {
    modifierWithKey(this._modifiersWithKeys, RichEditorEnterKeyTypeModifier.identity, RichEditorEnterKeyTypeModifier, value);
    return this;
  }

  onPaste(callback) {
    modifierWithKey(this._modifiersWithKeys, RichEditorOnPasteModifier.identity, RichEditorOnPasteModifier, callback);
    return this;
  }
  onReady(callback) {
    modifierWithKey(this._modifiersWithKeys, RichEditorOnReadyModifier.identity, RichEditorOnReadyModifier, callback);
    return this;
  }
  onSelect(callback) {
    modifierWithKey(this._modifiersWithKeys, RichEditorOnSelectModifier.identity, RichEditorOnSelectModifier, callback);
    return this;
  }
  onSubmit(callback) {
    modifierWithKey(this._modifiersWithKeys, RichEditorOnSubmitModifier.identity, RichEditorOnSubmitModifier, callback);
    return this;
  }
  aboutToIMEInput(callback) {
    modifierWithKey(this._modifiersWithKeys, RichEditorAboutToIMEInputModifier.identity, RichEditorAboutToIMEInputModifier, callback);
    return this;
  }
  onIMEInputComplete(callback) {
    modifierWithKey(this._modifiersWithKeys, RichEditorOnIMEInputCompleteModifier.identity, RichEditorOnIMEInputCompleteModifier, callback);
    return this;
  }
  onWillChange(callback) {
    modifierWithKey(this._modifiersWithKeys, RichEditorOnWillChangeModifier.identity, RichEditorOnWillChangeModifier, callback);
    return this;
  }
  onDidChange(callback) {
    modifierWithKey(this._modifiersWithKeys, RichEditorOnDidChangeModifier.identity, RichEditorOnDidChangeModifier, callback);
    return this;
  }
  placeholder(value, style) {
    let placeholder = new ArkPlaceholder();
    placeholder.value = value;
    placeholder.style = style;
    modifierWithKey(this._modifiersWithKeys, RichEditorPlaceholderModifier.identity, RichEditorPlaceholderModifier, placeholder);
    return this;
  }
  aboutToDelete(callback) {
    modifierWithKey(this._modifiersWithKeys, RichEditorAboutToDeleteModifier.identity, RichEditorAboutToDeleteModifier, callback);
    return this;
  }
  onDeleteComplete(callback) {
    modifierWithKey(this._modifiersWithKeys, RichEditorOnDeleteCompleteModifier.identity, RichEditorOnDeleteCompleteModifier, callback);
    return this;
  }
  bindSelectionMenu(spanType, content, responseType, options) {
    throw new BusinessError(100201, 'bindSelectionMenu function not supported in RichEditorModifier class');
  }
  customKeyboard(value, options) {
    let arkValue = new ArkCustomKeyboard();
    arkValue.value = value;
    arkValue.supportAvoidance = options?.supportAvoidance;
    modifierWithKey(this._modifiersWithKeys, RichEditorCustomKeyboardModifier.identity,
      RichEditorCustomKeyboardModifier, arkValue);
    return this;
  }
  onEditingChange(callback) {
    modifierWithKey(this._modifiersWithKeys, RichEditorOnEditingChangeModifier.identity, RichEditorOnEditingChangeModifier, callback);
    return this;
  }
  onCut(callback) {
    modifierWithKey(this._modifiersWithKeys, RichEditorOnCutModifier.identity, RichEditorOnCutModifier, callback);
    return this;
  }
  onCopy(callback) {
    modifierWithKey(this._modifiersWithKeys, RichEditorOnCopyModifier.identity, RichEditorOnCopyModifier, callback);
    return this;
  }
  enableKeyboardOnFocus(value) {
    modifierWithKey(this._modifiersWithKeys, RichEditorEnableKeyboardOnFocusModifier.identity, RichEditorEnableKeyboardOnFocusModifier, value);
    return this;
  }
  enablePreviewText(value) {
    modifierWithKey(this._modifiersWithKeys, RichEditorEnablePreviewTextModifier.identity, RichEditorEnablePreviewTextModifier, value);
    return this;
  }
  editMenuOptions(value) {
    modifierWithKey(this._modifiersWithKeys, RichEditorEditMenuOptionsModifier.identity, RichEditorEditMenuOptionsModifier, value);
    return this;
  }
  barState(value) {
    modifierWithKey(this._modifiersWithKeys, RichEditorBarStateModifier.identity, RichEditorBarStateModifier, value);
    return this;
  }
  maxLength(value) {
    modifierWithKey(this._modifiersWithKeys, RichEditorMaxLengthModifier.identity, RichEditorMaxLengthModifier, value);
    return this;
  }
  maxLines(value) {
    modifierWithKey(this._modifiersWithKeys, RichEditorMaxLinesModifier.identity, RichEditorMaxLinesModifier, value);
    return this;
  }
  stopBackPress(value) {
    modifierWithKey(this._modifiersWithKeys, RichEditorStopBackPressModifier.identity, RichEditorStopBackPressModifier, value);
    return this;
  }
  keyboardAppearance(value) {
    modifierWithKey(this._modifiersWithKeys, RichEditorKeyboardAppearanceModifier.identity, RichEditorKeyboardAppearanceModifier, value);
    return this;
  }
  onDidIMEInput(callback) {
    modifierWithKey(this._modifiersWithKeys, RichEditorOnDidIMEInputModifier.identity, RichEditorOnDidIMEInputModifier, callback);
    return this;
  }
  onWillAttachIME(callback) {
    modifierWithKey(this._modifiersWithKeys, RichEditorOnWillAttachIMEModifier.identity, RichEditorOnWillAttachIMEModifier, callback);
    return this;
  }
  enableHapticFeedback(value) {
    modifierWithKey(this._modifiersWithKeys, RichEditorEnableHapticFeedbackModifier.identity, RichEditorEnableHapticFeedbackModifier, value);
    return this;
  }
  enableAutoSpacing(enable) {
    modifierWithKey(this._modifiersWithKeys, RichEditorEnableAutoSpacingModifier.identity, RichEditorEnableAutoSpacingModifier, enable);
    return this;
  }
  compressLeadingPunctuation(enable) {
    modifierWithKey(this._modifiersWithKeys, RichEditorCompressLeadingPunctuationModifier.identity, RichEditorCompressLeadingPunctuationModifier, enable);
    return this;
  }
  undoStyle(style) {
    modifierWithKey(this._modifiersWithKeys, RichEditorUndoStyleModifier.identity, RichEditorUndoStyleModifier, style);
    return this;
  }
  scrollBarColor(style) {
    modifierWithKey(this._modifiersWithKeys, RichEditorScrollBarColorModifier.identity, RichEditorScrollBarColorModifier, style);
    return this;
  }
  selectedDragPreviewStyle(value) {
    let arkSelectedDragPreviewStyle = new ArkSelectedDragPreviewStyle();
    arkSelectedDragPreviewStyle.color = value?.color;
    modifierWithKey(this._modifiersWithKeys, RichEditorSelectedDragPreviewStyleModifier.identity,
      RichEditorSelectedDragPreviewStyleModifier, arkSelectedDragPreviewStyle);
    return this;
  }
  includeFontPadding(enable) {
    modifierWithKey(this._modifiersWithKeys, RichEditorIncludeFontPaddingModifier.identity, RichEditorIncludeFontPaddingModifier, enable);
    return this;
  }
  fallbackLineSpacing(enable) {
    modifierWithKey(this._modifiersWithKeys, RichEditorFallbackLineSpacingModifier.identity, RichEditorFallbackLineSpacingModifier, enable);
    return this;
  }
  singleLine(value) {
    modifierWithKey(this._modifiersWithKeys, RichEditorSingleLineModifier.identity, RichEditorSingleLineModifier, value);
    return this;
  }
}

class RichEditorEnableDataDetectorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetEnableDataDetector(node);
    }
    else {
      getUINativeModule().richEditor.setEnableDataDetector(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
RichEditorEnableDataDetectorModifier.identity = Symbol('richEditorEnableDataDetector');

class RichEditorDataDetectorConfigModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetDataDetectorConfig(node);
    } else {
      getUINativeModule().richEditor.setDataDetectorConfig(node, this.value.types, this.value.onDetectResultUpdate,
        this.value.color, this.value.decorationType, this.value.decorationColor, this.value.decorationStyle);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.types, this.value.types) ||
    !isBaseOrResourceEqual(this.stageValue.onDetectResultUpdate, this.value.onDetectResultUpdate) ||
    !isBaseOrResourceEqual(this.stageValue.color, this.value.color) ||
    !isBaseOrResourceEqual(this.stageValue.decorationType, this.value.decorationType) ||
    !isBaseOrResourceEqual(this.stageValue.decorationColor, this.value.decorationColor) ||
    !isBaseOrResourceEqual(this.stageValue.decorationStyle, this.value.decorationStyle);
  }
}
RichEditorDataDetectorConfigModifier.identity = Symbol('richEditorDataDetectorConfig');

class RichEditorOnIMEInputCompleteModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetOnIMEInputComplete(node);
    } else {
      getUINativeModule().richEditor.setOnIMEInputComplete(node, this.value);
    }
  }
}
RichEditorOnIMEInputCompleteModifier.identity = Symbol('richEditorOnIMEInputComplete');

class RichEditorCopyOptionsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetCopyOptions(node);
    }
    else {
      getUINativeModule().richEditor.setCopyOptions(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
RichEditorCopyOptionsModifier.identity = Symbol('richEditorCopyOptions');

class RichEditorCaretColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetCaretColor(node);
    }
    else {
      getUINativeModule().richEditor.setCaretColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
RichEditorCaretColorModifier.identity = Symbol('richEditorCaretColor');

class RichEditorOnSelectionChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetOnSelectionChange(node);
    } else {
      getUINativeModule().richEditor.setOnSelectionChange(node, this.value);
    }
  }
}
RichEditorOnSelectionChangeModifier.identity = Symbol('richEditorOnSelectionChange');

class RichEditorOnSubmitModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetOnSubmit(node);
    } else {
      getUINativeModule().richEditor.setOnSubmit(node, this.value);
    }
  }
}
RichEditorOnSubmitModifier.identity = Symbol('richEditorOnSubmit');

class RichEditorAboutToIMEInputModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetAboutToIMEInput(node);
    } else {
      getUINativeModule().richEditor.setAboutToIMEInput(node, this.value);
    }
  }
}
RichEditorAboutToIMEInputModifier.identity = Symbol('richEditorAboutToIMEInput');

class RichEditorSelectedBackgroundColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetSelectedBackgroundColor(node);
    }
    else {
      getUINativeModule().richEditor.setSelectedBackgroundColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
RichEditorSelectedBackgroundColorModifier.identity = Symbol('richEditorSelectedBackgroundColor');

class RichEditorOnSelectModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetOnSelect(node);
    } else {
      getUINativeModule().richEditor.setOnSelect(node, this.value);
    }
  }
}
RichEditorOnSelectModifier.identity = Symbol('richEditorOnSelect');

class RichEditorOnWillChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetOnWillChange(node);
    } else {
      getUINativeModule().richEditor.setOnWillChange(node, this.value);
    }
  }
}
RichEditorOnWillChangeModifier.identity = Symbol('richEditorOnWillChange');

class RichEditorSelectedDragPreviewStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetSelectedDragPreviewStyle(node);
    }
    else {
      getUINativeModule().richEditor.setSelectedDragPreviewStyle(node, this.value.color);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value) ||
    !isBaseOrResourceEqual(this.stageValue.color, this.value.color);
  }
}
RichEditorSelectedDragPreviewStyleModifier.identity = Symbol('richEditorSelectedDragPreviewStyle');

class RichEditorOnDidChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetOnDidChange(node);
    } else {
      getUINativeModule().richEditor.setOnDidChange(node, this.value);
    }
  }
}
RichEditorOnDidChangeModifier.identity = Symbol('richEditorOnDidChange');

class RichEditorPlaceholderModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetPlaceholder(node);
    } else {
      getUINativeModule().richEditor.setPlaceholder(node, this.value.value, this.value.style);
    }
  }
  checkObjectDiff() {
    return !(this.stageValue).isEqual(this.value);
  }
}
RichEditorPlaceholderModifier.identity = Symbol('richEditorPlaceholder');

class RichEditorAboutToDeleteModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetAboutToDelete(node);
    } else {
      getUINativeModule().richEditor.setAboutToDelete(node, this.value);
    }
  }
}
RichEditorAboutToDeleteModifier.identity = Symbol('richEditorAboutToDelete');

class RichEditorOnReadyModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetOnReady(node);
    } else {
      getUINativeModule().richEditor.setOnReady(node, this.value);
    }
  }
}
RichEditorOnReadyModifier.identity = Symbol('richEditorOnReady');

class RichEditorOnDeleteCompleteModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetOnDeleteComplete(node);
    } else {
      getUINativeModule().richEditor.setOnDeleteComplete(node, this.value);
    }
  }
}
RichEditorOnDeleteCompleteModifier.identity = Symbol('richEditorOnDeleteComplete');

class RichEditorOnEditingChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetOnEditingChange(node);
    } else {
      getUINativeModule().richEditor.setOnEditingChange(node, this.value);
    }
  }
}
RichEditorOnEditingChangeModifier.identity = Symbol('richEditorOnEditingChange');

class RichEditorOnPasteModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetOnPaste(node);
    } else {
      getUINativeModule().richEditor.setOnPaste(node, this.value);
    }
  }
}
RichEditorOnPasteModifier.identity = Symbol('richEditorOnPaste');

class RichEditorOnCutModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetOnCut(node);
    } else {
      getUINativeModule().richEditor.setOnCut(node, this.value);
    }
  }
}
RichEditorOnCutModifier.identity = Symbol('richEditorOnCut');

class RichEditorOnCopyModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetOnCopy(node);
    } else {
      getUINativeModule().richEditor.setOnCopy(node, this.value);
    }
  }
}
RichEditorOnCopyModifier.identity = Symbol('richEditorOnCopy');

class RichEditorEnableKeyboardOnFocusModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetEnableKeyboardOnFocus(node);
    } else {
      getUINativeModule().richEditor.setEnableKeyboardOnFocus(node, this.value);
    }
  }
}
RichEditorEnableKeyboardOnFocusModifier.identity = Symbol('richEditorEnableKeyboardOnFocus');

class RichEditorEnablePreviewTextModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetEnablePreviewText(node);
    } else {
      getUINativeModule().richEditor.setEnablePreviewText(node, this.value);
    }
  }
}
RichEditorEnablePreviewTextModifier.identity = Symbol('richEditorEnablePreviewText');

class RichEditorEditMenuOptionsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetEditMenuOptions(node);
    } else {
      getUINativeModule().richEditor.setEditMenuOptions(node, this.value);
    }
  }
}
RichEditorEditMenuOptionsModifier.identity = Symbol('richEditorEditMenuOptions');

class RichEditorEnterKeyTypeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetEnterKeyType(node);
    }
    else {
      getUINativeModule().richEditor.setEnterKeyType(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
RichEditorEnterKeyTypeModifier.identity = Symbol('richEditorEnterKeyType');

class RichEditorBarStateModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetBarState(node);
    }
    else {
      getUINativeModule().richEditor.setBarState(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
RichEditorBarStateModifier.identity = Symbol('richEditorBarState');

class RichEditorMaxLengthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetMaxLength(node);
    }
    else {
      getUINativeModule().richEditor.setMaxLength(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
RichEditorMaxLengthModifier.identity = Symbol('richEditorMaxLength');

class RichEditorMaxLinesModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetMaxLines(node);
    }
    else {
      getUINativeModule().richEditor.setMaxLines(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
RichEditorMaxLinesModifier.identity = Symbol('richEditorMaxLines');

class RichEditorStopBackPressModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetStopBackPress(node);
    }
    else {
      getUINativeModule().richEditor.setStopBackPress(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
RichEditorStopBackPressModifier.identity = Symbol('richEditorStopBackPress');

class RichEditorKeyboardAppearanceModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetKeyboardAppearance(node);
    }
    else {
      getUINativeModule().richEditor.setKeyboardAppearance(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
RichEditorKeyboardAppearanceModifier.identity = Symbol('richEditorKeyboardAppearance');
class RichEditorCustomKeyboardModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetCustomKeyboard(node);
    } else {
      getUINativeModule().richEditor.setCustomKeyboard(node, this.value.value, this.value.supportAvoidance);
    }
  }
}
RichEditorCustomKeyboardModifier.identity = Symbol('richEditorCustomKeyboard');
class RichEditorOnDidIMEInputModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetOnDidIMEInput(node);
    } else {
      getUINativeModule().richEditor.setOnDidIMEInput(node, this.value);
    }
  }
}
RichEditorOnDidIMEInputModifier.identity = Symbol('richEditorOnDidIMEInput');

class RichEditorOnWillAttachIMEModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetOnWillAttachIME(node);
    } else {
      getUINativeModule().richEditor.setOnWillAttachIME(node, this.value);
    }
  }
}
RichEditorOnWillAttachIMEModifier.identity = Symbol('richEditorOnWillAttachIME');

class RichEditorEnableHapticFeedbackModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetEnableHapticFeedback(node);
    }
    else {
      getUINativeModule().richEditor.setEnableHapticFeedback(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
RichEditorEnableHapticFeedbackModifier.identity = Symbol('richEditorEnableHapticFeedback');

class RichEditorEnableAutoSpacingModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetEnableAutoSpacing(node);
    } else {
      getUINativeModule().richEditor.setEnableAutoSpacing(node, this.value);
    }
  }
}
RichEditorEnableAutoSpacingModifier.identity = Symbol('richEditorEnableAutoSpacing');

class RichEditorCompressLeadingPunctuationModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetCompressLeadingPunctuation(node);
    } else {
      getUINativeModule().richEditor.setCompressLeadingPunctuation(node, this.value);
    }
  }
}
RichEditorCompressLeadingPunctuationModifier.identity = Symbol('richEditorCompressLeadingPunctuation');

class RichEditorUndoStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetUndoStyle(node);
    } else {
      getUINativeModule().richEditor.setUndoStyle(node, this.value);
    }
  }
}
RichEditorUndoStyleModifier.identity = Symbol('richEditorUndoStyle');

class RichEditorScrollBarColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetScrollBarColor(node);
    } else {
      getUINativeModule().richEditor.setScrollBarColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
RichEditorScrollBarColorModifier.identity = Symbol('richEditorScrollBarColor');

class RichEditorIncludeFontPaddingModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetIncludeFontPadding(node);
    } else {
      getUINativeModule().richEditor.setIncludeFontPadding(node, this.value);
    }
  }
}
RichEditorIncludeFontPaddingModifier.identity = Symbol('richEditorIncludeFontPadding');

class RichEditorFallbackLineSpacingModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetFallbackLineSpacing(node);
    } else {
      getUINativeModule().richEditor.setFallbackLineSpacing(node, this.value);
    }
  }
}
RichEditorFallbackLineSpacingModifier.identity = Symbol('richEditorFallbackLineSpacing');

class RichEditorSingleLineModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetSingleLine(node);
    }
    else {
      getUINativeModule().richEditor.setSingleLine(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
RichEditorSingleLineModifier.identity = Symbol('richEditorSingleLine');

class JSRichEditor extends JSContainerBase {
    static create(params) {
        getUINativeModule().richEditor.create(params);
    }
    static onReady(callback) {
        getUINativeModule().richEditor.setOnReady(true, callback);
    }
    static onSelect(callback) {
        getUINativeModule().richEditor.setOnSelect(true, callback);
    }
    static onSelectionChange(callback) {
        getUINativeModule().richEditor.setOnSelectionChange(true, callback);
    }
    static aboutToIMEInput(callback) {
        getUINativeModule().richEditor.setAboutToIMEInput(true, callback);
    }
    static onIMEInputComplete(callback) {
        getUINativeModule().richEditor.setOnIMEInputComplete(true, callback);
    }
    static onDidIMEInput(callback) {
        getUINativeModule().richEditor.setOnDidIMEInput(true, callback);
    }
    static aboutToDelete(callback) {
        getUINativeModule().richEditor.setAboutToDelete(true, callback);
    }
    static onDeleteComplete(callback) {
        getUINativeModule().richEditor.setOnDeleteComplete(true, callback);
    }
    static customKeyboard(value, options) {
        getUINativeModule().richEditor.setCustomKeyboardJS(true, value, options?.supportAvoidance);
    }
    static copyOptions(value) {
        getUINativeModule().richEditor.setCopyOptions(true, value);
    }
    static bindSelectionMenu(spanType, content, responseType, options) {
        getUINativeModule().richEditor.setBindSelectionMenu(true, spanType, content, responseType, options);
    }
    static onPaste(callback) {
        getUINativeModule().richEditor.setOnPaste(true, callback);
    }
    static enableSelectedDataDetector(value) {
        getUINativeModule().richEditor.setEnableSelectedDataDetector(true, value);
    }
    static selectedDataDetectorConfig(value) {
        getUINativeModule().richEditor.setSelectedDataDetectorConfig(true, value);
    }
    static enableDataDetector(value) {
        getUINativeModule().richEditor.setEnableDataDetector(true, value);
    }
    static enablePreviewText(value) {
        getUINativeModule().richEditor.setEnablePreviewText(true, value);
    }
    static dataDetectorConfig(config) {
        if (config !== undefined && config !== null) {
          if (config.decoration) {
            getUINativeModule().richEditor.setDataDetectorConfig(true, config.types, config.onDetectResultUpdate,
              config.color, config.decoration.type, config.decoration.color, config.decoration.style,
              config.enablePreviewMenu);
          } else {
            getUINativeModule().richEditor.setDataDetectorConfig(true, config.types, config.onDetectResultUpdate,
              config.color, undefined, undefined, undefined,
              config.enablePreviewMenu);
          }
        }
    }
    static placeholder(value, style) {
        getUINativeModule().richEditor.setPlaceholder(true, value, style);
    }
    static caretColor(value) {
        getUINativeModule().richEditor.setCaretColor(true, value);
    }
    static selectedDragPreviewStyle(value) {
        let arkSelectedDragPreviewStyle = new ArkSelectedDragPreviewStyle();
        arkSelectedDragPreviewStyle.color = value?.color;
        getUINativeModule().richEditor.setSelectedDragPreviewStyle(true, arkSelectedDragPreviewStyle);
    }
    static selectedBackgroundColor(value) {
        getUINativeModule().richEditor.setSelectedBackgroundColor(true, value);
    }
    static onEditingChange(callback) {
        getUINativeModule().richEditor.setOnEditingChange(true, callback);
    }
    static enterKeyType(callback) {
        getUINativeModule().richEditor.setEnterKeyType(true, callback);
    }
    static onSubmit(callback) {
        getUINativeModule().richEditor.setOnSubmit(true, callback);
    }
    static onWillChange(callback) {
        getUINativeModule().richEditor.setOnWillChange(true, callback);
    }
    static onDidChange(callback) {
        getUINativeModule().richEditor.setOnDidChange(true, callback);
    }
    static onCut(callback) {
        getUINativeModule().richEditor.setOnCut(true, callback);
    }
    static onCopy(callback) {
        getUINativeModule().richEditor.setOnCopy(true, callback);
    }
    static onShare(callback) {
        getUINativeModule().richEditor.setOnShare(true, callback);
    }
    static onWillAttachIME(callback) {
        getUINativeModule().richEditor.setOnWillAttachIME(true, callback);
    }
    static editMenuOptions(value) {
        getUINativeModule().richEditor.setEditMenuOptions(true, value);
    }
    static enableKeyboardOnFocus(value) {
        getUINativeModule().richEditor.setEnableKeyboardOnFocus(true, value);
    }
    static enableHapticFeedback(value) {
        getUINativeModule().richEditor.setEnableHapticFeedback(true, value);
    }
    static barState(value) {
        getUINativeModule().richEditor.setBarState(true, value);
    }
    static maxLength(value) {
        getUINativeModule().richEditor.setMaxLength(true, value);
    }
    static maxLines(value) {
        getUINativeModule().richEditor.setMaxLines(true, value);
    }
    static enableAutoSpacing(enable) {
        getUINativeModule().richEditor.setEnableAutoSpacing(true, enable);
    }
    static compressLeadingPunctuation(enable) {
        getUINativeModule().richEditor.setCompressLeadingPunctuation(true, enable);
    }
    static stopBackPress(value) {
        getUINativeModule().richEditor.setStopBackPress(true, value);
    }
    static keyboardAppearance(value) {
        getUINativeModule().richEditor.setKeyboardAppearance(true, value);
    }
    static undoStyle(style) {
        getUINativeModule().richEditor.setUndoStyle(true, style);
    }
    static scrollBarColor(style) {
        getUINativeModule().richEditor.setScrollBarColor(true, style);
    }
    static includeFontPadding(enable) {
        getUINativeModule().richEditor.setIncludeFontPadding(true, enable);
    }
    static fallbackLineSpacing(enable) {
        getUINativeModule().richEditor.setFallbackLineSpacing(true, enable);
    }
    static singleLine(callback) {
        getUINativeModule().richEditor.setSingleLine(true, callback);
    }
    static clip(callback) {
      if (callback === undefined) {
          getUINativeModule().richEditor.setClip(true, callback);
          return;
      }
      JSViewAbstract.clip(callback);
    }
    static focusable(callback) {
        getUINativeModule().richEditor.setFocusable(true, callback);
    }
    static attributeModifier(modifier) {
        attributeModifierFunc.call(this, modifier, (nativePtr) => {
            return new ArkRichEditorComponent(nativePtr);
        }, (nativePtr, classType, modifierJS) => {
            return new modifierJS.RichEditorModifier(nativePtr, classType);
        });
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
}

function createComponent(nativePtr, classType) {
    return new ArkRichEditorComponent(nativePtr, classType);
}

function exportComponent() {
    globalThis.ArkRichEditorComponent = ArkRichEditorComponent;
}

function exportView() {
    globalThis.RichEditor = JSRichEditor;
}

export default { ArkRichEditorComponent, createComponent, exportComponent, exportView };
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

// ===== Part A: Modifier classes =====

class SelectionContainerCopyOptionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().selectionContainer.resetCopyOption(node);
    } else {
      getUINativeModule().selectionContainer.setCopyOption(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
SelectionContainerCopyOptionModifier.identity = Symbol('selectionContainerCopyOption');

class SelectionContainerEnableHapticFeedbackModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().selectionContainer.resetEnableHapticFeedback(node);
    } else {
      getUINativeModule().selectionContainer.setEnableHapticFeedback(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
SelectionContainerEnableHapticFeedbackModifier.identity = Symbol('selectionContainerEnableHapticFeedback');

class SelectionContainerTextJoinStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().selectionContainer.resetTextJoinStyle(node);
    } else {
      getUINativeModule().selectionContainer.setTextJoinStyle(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
SelectionContainerTextJoinStyleModifier.identity = Symbol('selectionContainerTextJoinStyle');

class SelectionContainerCaretColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().selectionContainer.resetCaretColor(node);
    } else {
      getUINativeModule().selectionContainer.setCaretColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SelectionContainerCaretColorModifier.identity = Symbol('selectionContainerCaretColor');

class SelectionContainerSelectedBackgroundColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().selectionContainer.resetSelectedBackgroundColor(node);
    } else {
      getUINativeModule().selectionContainer.setSelectedBackgroundColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SelectionContainerSelectedBackgroundColorModifier.identity = Symbol('selectionContainerSelectedBackgroundColor');

class SelectionContainerEditMenuOptionsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().selectionContainer.resetSelectionMenuOptions(node);
    } else {
      getUINativeModule().selectionContainer.setSelectionMenuOptions(node, this.value);
    }
  }
}
SelectionContainerEditMenuOptionsModifier.identity = Symbol('selectionContainerEditMenuOptions');

class SelectionContainerOnWillCopyModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().selectionContainer.resetOnWillCopy(node);
    } else {
      getUINativeModule().selectionContainer.setOnWillCopy(node, this.value);
    }
  }
}
SelectionContainerOnWillCopyModifier.identity = Symbol('selectionContainerOnWillCopy');

class SelectionContainerOnCopyModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().selectionContainer.resetOnCopy(node);
    } else {
      getUINativeModule().selectionContainer.setOnCopy(node, this.value);
    }
  }
}
SelectionContainerOnCopyModifier.identity = Symbol('selectionContainerOnCopy');

class SelectionContainerOnTextSelectionChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().selectionContainer.resetOnTextSelectionChange(node);
    } else {
      getUINativeModule().selectionContainer.setOnTextSelectionChange(node, this.value);
    }
  }
}
SelectionContainerOnTextSelectionChangeModifier.identity = Symbol('selectionContainerOnTextSelectionChange');

// ===== Part B: ArkSelectionContainerComponent =====

class ArkSelectionContainerComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  copyOption(value) {
    modifierWithKey(this._modifiersWithKeys, SelectionContainerCopyOptionModifier.identity,
      SelectionContainerCopyOptionModifier, value);
    return this;
  }
  enableHapticFeedback(value) {
    modifierWithKey(this._modifiersWithKeys, SelectionContainerEnableHapticFeedbackModifier.identity,
      SelectionContainerEnableHapticFeedbackModifier, value);
    return this;
  }
  textJoinStyle(value) {
    modifierWithKey(this._modifiersWithKeys, SelectionContainerTextJoinStyleModifier.identity,
      SelectionContainerTextJoinStyleModifier, value);
    return this;
  }
  caretColor(value) {
    modifierWithKey(this._modifiersWithKeys, SelectionContainerCaretColorModifier.identity,
      SelectionContainerCaretColorModifier, value);
    return this;
  }
  selectedBackgroundColor(value) {
    modifierWithKey(this._modifiersWithKeys, SelectionContainerSelectedBackgroundColorModifier.identity,
      SelectionContainerSelectedBackgroundColorModifier, value);
    return this;
  }
  editMenuOptions(value) {
    modifierWithKey(this._modifiersWithKeys, SelectionContainerEditMenuOptionsModifier.identity,
      SelectionContainerEditMenuOptionsModifier, value);
    return this;
  }
  onWillCopy(callback) {
    modifierWithKey(this._modifiersWithKeys, SelectionContainerOnWillCopyModifier.identity,
      SelectionContainerOnWillCopyModifier, callback);
    return this;
  }
  onCopy(callback) {
    modifierWithKey(this._modifiersWithKeys, SelectionContainerOnCopyModifier.identity,
      SelectionContainerOnCopyModifier, callback);
    return this;
  }
  onTextSelectionChange(callback) {
    modifierWithKey(this._modifiersWithKeys, SelectionContainerOnTextSelectionChangeModifier.identity,
      SelectionContainerOnTextSelectionChangeModifier, callback);
    return this;
  }
  bindSelectionMenu(spanType, content, responseType, options) {
    getUINativeModule().selectionContainer.bindSelectionMenu(this.nativePtr_, spanType, content, responseType, options);
    return this;
  }

  resetBindSelectionMenu(spanType, responseType) {
    getUINativeModule().selectionContainer.resetBindSelectionMenu(this.nativePtr_, spanType, responseType);
    return this;
  }
}

// ===== Part C: JSSelectionContainer (static API) =====

class SelectionContainer extends JSContainerBase {
  static create() {
    getUINativeModule().selectionContainer.create();
  }

  static copyOption(value) {
    getUINativeModule().selectionContainer.setCopyOption(true, value);
  }

  static enableHapticFeedback(value) {
    getUINativeModule().selectionContainer.setEnableHapticFeedback(true, value);
  }

  static textJoinStyle(value) {
    getUINativeModule().selectionContainer.setTextJoinStyle(true, value);
  }

  static caretColor(value) {
    getUINativeModule().selectionContainer.setCaretColor(true, value);
  }

  static selectedBackgroundColor(value) {
    getUINativeModule().selectionContainer.setSelectedBackgroundColor(true, value);
  }

  static onWillCopy(value) {
    getUINativeModule().selectionContainer.setOnWillCopy(true, value);
  }

  static onCopy(value) {
    getUINativeModule().selectionContainer.setOnCopy(true, value);
  }

  static onTextSelectionChange(value) {
    getUINativeModule().selectionContainer.setOnTextSelectionChange(true, value);
  }

  static editMenuOptions(value) {
    getUINativeModule().selectionContainer.setSelectionMenuOptions(true, value);
  }

  static bindSelectionMenu(spanType, content, responseType, options) {
    getUINativeModule().selectionContainer.bindSelectionMenu(true, spanType, content, responseType, options);
  }

  static attributeModifier(modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkSelectionContainerComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.SelectionContainerModifier(nativePtr, classType);
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
    __Common__.onDetach(value);
  }
  static onDisAppear(value) {
    __Common__.onDisAppear(value);
  }
  static onTouch(value) {
    __Common__.onTouch(value);
  }
}

const SelectionContainerTextJoinStyle = {
  NEWLINE: 0,
  DIRECT: 1,
};

// ===== Part D: Exports =====

function createComponent(nativePtr, classType) {
  return new ArkSelectionContainerComponent(nativePtr, classType);
}

export default { SelectionContainer, createComponent, SelectionContainerTextJoinStyle };

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

/// <reference path="./import.ts" />
class TextAreaFontStyleModifier extends ModifierWithKey<FontStyle> {
  constructor(value: FontStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaFontStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textArea.resetFontStyle(node);
    } else {
      GetUINativeModule().textArea.setFontStyle(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaCopyOptionModifier extends ModifierWithKey<CopyOptions> {
  constructor(value: CopyOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaCopyOption');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textArea.resetCopyOption(node);
    } else {
      GetUINativeModule().textArea.setCopyOption(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaMaxLinesModifier extends ModifierWithKey<number | undefined> {
  constructor(value: number | undefined) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaMaxLines');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textArea.resetMaxLines(node);
    } else {
      GetUINativeModule().textArea.setMaxLines(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaFontSizeModifier extends ModifierWithKey<string | number> {
  constructor(value: string | number) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaFontSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textArea.resetFontSize(node);
    } else {
      GetUINativeModule().textArea.setFontSize(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaPlaceholderColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaPlaceholderColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textArea.resetPlaceholderColor(node);
    } else {
      GetUINativeModule().textArea.setPlaceholderColor(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else {
      return true;
    }
  }
}

class TextAreaFontColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaFontColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textArea.resetFontColor(node);
    } else {
      GetUINativeModule().textArea.setFontColor(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else {
      return true;
    }
  }
}

class TextAreaFontWeightModifier extends ModifierWithKey<number | FontWeight | string> {
  constructor(value: number | FontWeight | string) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaFontWeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textArea.resetFontWeight(node);
    } else {
      GetUINativeModule().textArea.setFontWeight(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaBarStateModifier extends ModifierWithKey<BarState> {
  constructor(value: BarState) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaBarState');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textArea.resetBarState(node);
    } else {
      GetUINativeModule().textArea.setBarState(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaEnableKeyboardOnFocusModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaEnableKeyboardOnFocus');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textArea.resetEnableKeyboardOnFocus(node);
    } else {
      GetUINativeModule().textArea.setEnableKeyboardOnFocus(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaFontFamilyModifier extends ModifierWithKey<ResourceColor | string> {
  constructor(value: ResourceColor | string) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaFontFamily');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textArea.resetFontFamily(node);
    } else {
      GetUINativeModule().textArea.setFontFamily(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaCaretColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaCaretColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textArea.resetCaretColor(node);
    } else {
      GetUINativeModule().textArea.setCaretColor(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else {
      return true;
    }
  }
}

class TextAreaMaxLengthModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaMaxLength');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textArea.resetMaxLength(node);
    } else {
      GetUINativeModule().textArea.setMaxLength(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaStyleModifier extends ModifierWithKey<TextContentStyle> {
  constructor(value: TextContentStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textArea.resetStyle(node);
    } else {
      GetUINativeModule().textArea.setStyle(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaSelectionMenuHiddenModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaSelectionMenuHidden');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textArea.resetSelectionMenuHidden(node);
    } else {
      GetUINativeModule().textArea.setSelectionMenuHidden(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaPlaceholderFontModifier extends ModifierWithKey<Font> {
  constructor(value: Font) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaPlaceholderFont');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textArea.resetPlaceholderFont(node);
    } else {
      GetUINativeModule().textArea.setPlaceholderFont(node, this.value.size,
        this.value.weight, this.value.family, this.value.style);
    }
  }

  checkObjectDiff(): boolean {
    if (!(this.stageValue.weight === this.value.weight &&
      this.stageValue.style === this.value.style)) {
      return true;
    } else {
      return !isBaseOrResourceEqual(this.stageValue.size, this.value.size) ||
        !isBaseOrResourceEqual(this.stageValue.family, this.value.family);
    }
  }
}

class TextAreaTextAlignModifier extends ModifierWithKey<TextAlign> {
  constructor(value: TextAlign) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaTextAlign');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textArea.resetTextAlign(node);
    } else {
      GetUINativeModule().textArea.setTextAlign(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextAreaShowCounterModifier extends ModifierWithKey<ArkTextAreaShowCounter> {
  constructor(value: ArkTextAreaShowCounter) {
    super(value);
  }
  static identity: Symbol = Symbol('textAreaShowCounter');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textArea.resetShowCounter(node);
    } else {
      GetUINativeModule().textArea.setShowCounter(node, this.value.value!, this.value.options);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.value, this.value.value) ||
      !isBaseOrResourceEqual(this.stageValue.options, this.value.options)
  }
}

class ArkTextAreaComponent extends ArkComponent implements CommonMethod<TextAreaAttribute> {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  type(value: TextAreaType): TextAreaAttribute {
    throw new Error('Method not implemented.');
  }
  placeholderColor(value: ResourceColor): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaPlaceholderColorModifier.identity, TextAreaPlaceholderColorModifier, value);
    return this;
  }
  placeholderFont(value: Font): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaPlaceholderFontModifier.identity, TextAreaPlaceholderFontModifier, value);
    return this;
  }

  textAlign(value: TextAlign): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaTextAlignModifier.identity, TextAreaTextAlignModifier, value);
    return this;
  }
  caretColor(value: ResourceColor): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaCaretColorModifier.identity, TextAreaCaretColorModifier, value);
    return this;
  }
  fontColor(value: ResourceColor): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaFontColorModifier.identity, TextAreaFontColorModifier, value);
    return this;
  }
  fontSize(value: Length): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaFontSizeModifier.identity, TextAreaFontSizeModifier, value);
    return this;
  }
  fontStyle(value: FontStyle): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaFontStyleModifier.identity, TextAreaFontStyleModifier, value);
    return this;
  }
  fontWeight(value: number | FontWeight | string): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaFontWeightModifier.identity, TextAreaFontWeightModifier, value);
    return this;
  }
  fontFamily(value: ResourceStr): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaFontFamilyModifier.identity, TextAreaFontFamilyModifier, value);
    return this;
  }
  inputFilter(value: ResourceStr, error?: (value: string) => void): TextAreaAttribute {
    throw new Error('Method not implemented.');
  }
  onChange(callback: (value: string) => void): TextAreaAttribute {
    throw new Error('Method not implemented.');
  }
  onTextSelectionChange(callback: (selectionStart: number, selectionEnd: number) => void): TextAreaAttribute {
    throw new Error('Method not implemented.');
  }
  onContentScroll(callback: (totalOffsetX: number, totalOffsetY: number) => void): TextAreaAttribute {
    throw new Error('Method not implemented.');
  }
  onEditChange(callback: (isEditing: boolean) => void): TextAreaAttribute {
    throw new Error('Method not implemented.');
  }
  onCopy(callback: (value: string) => void): TextAreaAttribute {
    throw new Error('Method not implemented.');
  }
  onCut(callback: (value: string) => void): TextAreaAttribute {
    throw new Error('Method not implemented.');
  }
  onPaste(callback: (value: string) => void): TextAreaAttribute {
    throw new Error('Method not implemented.');
  }
  copyOption(value: CopyOptions): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaCopyOptionModifier.identity, TextAreaCopyOptionModifier, value);
    return this;
  }

  enableKeyboardOnFocus(value: boolean): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaEnableKeyboardOnFocusModifier.identity, TextAreaEnableKeyboardOnFocusModifier, value);
    return this;
  }

  maxLength(value: number): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaMaxLengthModifier.identity, TextAreaMaxLengthModifier, value);
    return this;
  }
  showCounter(value: boolean, options?: InputCounterOptions): TextAreaAttribute {
    let arkValue: ArkTextAreaShowCounter = new ArkTextAreaShowCounter();
    arkValue.value = value;
    arkValue.options = options;
    modifierWithKey(this._modifiersWithKeys, TextAreaShowCounterModifier.identity, TextAreaShowCounterModifier, arkValue);
    return this;
  }
  style(value: TextContentStyle): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaStyleModifier.identity, TextAreaStyleModifier, value);
    return this;
  }
  barState(value: BarState): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaBarStateModifier.identity, TextAreaBarStateModifier, value);
    return this;
  }
  selectionMenuHidden(value: boolean): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaSelectionMenuHiddenModifier.identity, TextAreaSelectionMenuHiddenModifier, value);
    return this;
  }
  maxLines(value: number): TextAreaAttribute {
    modifierWithKey(this._modifiersWithKeys, TextAreaMaxLinesModifier.identity, TextAreaMaxLinesModifier, value);
    return this;
  }
  customKeyboard(value: CustomBuilder): TextAreaAttribute {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.TextArea.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);

  let component = this.createOrGetNode(elmtId, () => {
    return new ArkTextAreaComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

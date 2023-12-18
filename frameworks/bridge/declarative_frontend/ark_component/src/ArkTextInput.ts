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
class TextInputStyleModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetStyle(node);
    } else {
      GetUINativeModule().textInput.setStyle(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class TextInputMaxLengthModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputMaxLength');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetMaxLength(node);
    } else {
      GetUINativeModule().textInput.setMaxLength(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class TextInputMaxLinesModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputMaxLines');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetMaxLines(node);
    } else {
      GetUINativeModule().textInput.setMaxLines(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class TextInputShowPasswordIconModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputShowPasswordIcon');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetShowPasswordIcon(node);
    } else {
      GetUINativeModule().textInput.setShowPasswordIcon(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class TextInputTextAlignModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputTextAlign');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetTextAlign(node);
    } else {
      GetUINativeModule().textInput.setTextAlign(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputPlaceholderFontModifier extends ModifierWithKey<Font> {
  constructor(value: Font) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputPlaceholderFont');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetPlaceholderFont(node);
    } else {
      GetUINativeModule().textInput.setPlaceholderFont(node, this.value.size,
        this.value.weight, this.value.family, this.value.style);
    }
  }

  checkObjectDiff(): boolean {
    if (!(this.stageValue.weight === this.value.weight &&
      this.stageValue.style === this.value.style)) {
      return true;
    } else {
      if (((isResource(this.stageValue.size) && isResource(this.value.size) &&
        isResourceEqual(this.stageValue.size, this.value.size)) ||
        (!isResource(this.stageValue.size) && !isResource(this.value.size) &&
          this.stageValue.size === this.value.size)) &&
        ((isResource(this.stageValue.family) && isResource(this.value.family) &&
          isResourceEqual(this.stageValue.family, this.value.family)) ||
          (!isResource(this.stageValue.family) && !isResource(this.value.family) &&
            this.stageValue.family === this.value.family))) {
        return false;
      } else {
        return true;
      }
    }
  }
}

class TextInputPlaceholderColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputPlaceholderColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetPlaceholderColor(node);
    } else {
      GetUINativeModule().textInput.setPlaceholderColor(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputPasswordIconModifier extends ModifierWithKey<PasswordIcon> {
  constructor(value: PasswordIcon) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputPasswordIcon');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetPasswordIcon(node);
    } else {
      GetUINativeModule().textInput.setPasswordIcon(node, this.value.onIconSrc, this.value.offIconSrc);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.onIconSrc, this.value.onIconSrc) ||
      !isBaseOrResourceEqual(this.stageValue.offIconSrc, this.value.offIconSrc);
  }
}

class TextInputSelectedBackgroundColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputSelectedBackgroundColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetSelectedBackgroundColor(node);
    } else {
      GetUINativeModule().textInput.setSelectedBackgroundColor(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputSelectionMenuHiddenModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputSelectionMenuHidden');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetSelectionMenuHidden(node);
    } else {
      GetUINativeModule().textInput.setSelectionMenuHidden(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class TextInputShowUnderlineModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputShowUnderLine');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetShowUnderline(node);
    } else {
      GetUINativeModule().textInput.setShowUnderline(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class TextInputShowErrorModifier extends ModifierWithKey<string | undefined> {
  constructor(value: string | undefined) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputShowError');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetShowError(node);
    } else {
      GetUINativeModule().textInput.setShowError(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class TextInputTypeModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputType');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetType(node);
    } else {
      GetUINativeModule().textInput.setType(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputCaretPositionModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputCaretPosition');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetCaretPosition(node);
    } else {
      GetUINativeModule().textInput.setCaretPosition(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputCopyOptionModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputCopyOption');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetCopyOption(node);
    } else {
      GetUINativeModule().textInput.setCopyOption(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputEnableKeyboardOnFocusModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputEnableKeyboardOnFocus');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetEnableKeyboardOnFocus(node);
    } else {
      GetUINativeModule().textInput.setEnableKeyboardOnFocus(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputCaretStyleModifier extends ModifierWithKey<CaretStyle> {
  constructor(value: CaretStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputCaretStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetCaretStyle(node);
    } else {
      GetUINativeModule().textInput.setCaretStyle(node, this.value!.width);
    }
  }

  checkObjectDiff(): boolean {
    if (isObject(this.stageValue) && isObject(this.value)) {
      return !isBaseOrResourceEqual(this.stageValue.width, this.value.width)
    } else {
      return true;
    }
  }
}

class TextInputEnterKeyTypeModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputEnterKeyType');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetEnterKeyType(node);
    } else {
      GetUINativeModule().textInput.setEnterKeyType(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputBarStateModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputBarState');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetBarState(node);
    } else {
      GetUINativeModule().textInput.setBarState(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputCaretColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('textinputCaretColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetCaretColor(node);
    } else {
      GetUINativeModule().textInput.setCaretColor(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class TextInputFontColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputFontColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetFontColor(node);
    } else {
      GetUINativeModule().textInput.setFontColor(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}


class TextInputFontSizeModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputFontSize');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetFontSize(node);
    } else {
      GetUINativeModule().textInput.setFontSize(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class TextInputFontStyleModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputFontStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetFontStyle(node);
    } else {
      GetUINativeModule().textInput.setFontStyle(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputFontWeightModifier extends ModifierWithKey<number | string> {
  constructor(value: number | string) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputFontWeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetFontWeight(node);
    } else {
      GetUINativeModule().textInput.setFontWeight(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class TextInputFontFamilyModifier extends ModifierWithKey<ResourceStr> {
  constructor(value: ResourceStr) {
    super(value);
  }
  static identity: Symbol = Symbol('textInputFontFamily');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetFontFamily(node);
    } else {
      GetUINativeModule().textInput.setFontFamily(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class ArkTextInputComponent extends ArkComponent implements CommonMethod<TextInputAttribute>{
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  cancelButton(value: { style?: CancelButtonStyle, icon?: IconOptions }): TextInputAttribute {
    throw new Error('Method not implemented.');
  }
  onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
    throw new Error("Method not implemented.");
  }
  selectAll(value: boolean): TextInputAttribute {
    throw new Error('Method not implemented.')
  }
  enableAutoFill(value: boolean): TextInputAttribute {
    throw new Error('Method not implemented.')
  }
  passwordRules(value: string): TextInputAttribute {
    throw new Error('Method not implemented.')
  }
  showCounter(value: boolean): TextInputAttribute {
    throw new Error('Method not implemented.');
  }

  type(value: InputType): TextInputAttribute {

    modifierWithKey(this._modifiersWithKeys, TextInputTypeModifier.identity,
      TextInputTypeModifier, value);
    return this;
  }

  placeholderColor(value: ResourceColor): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputPlaceholderColorModifier.identity,
      TextInputPlaceholderColorModifier, value);
    return this;
  }

  placeholderFont(value?: Font): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputPlaceholderFontModifier.identity,
      TextInputPlaceholderFontModifier, value);
    return this;
  }
  enterKeyType(value: EnterKeyType): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputEnterKeyTypeModifier.identity,
      TextInputEnterKeyTypeModifier, value);
    return this;
  }
  caretColor(value: ResourceColor): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputCaretColorModifier.identity,
      TextInputCaretColorModifier, value);
    return this;
  }
  onEditChanged(callback: (isEditing: boolean) => void): TextInputAttribute {
    throw new Error('Method not implemented.');
  }
  onEditChange(callback: (isEditing: boolean) => void): TextInputAttribute {
    throw new Error('Method not implemented.');
  }
  onSubmit(callback: (enterKey: EnterKeyType) => void): TextInputAttribute {
    throw new Error('Method not implemented.');
  }
  onChange(callback: (value: string) => void): TextInputAttribute {
    throw new Error('Method not implemented.');
  }
  onTextSelectionChange(callback: (selectionStart: number, selectionEnd: number) => void): TextInputAttribute {
    throw new Error('Method not implemented.');
  }
  onContentScroll(callback: (totalOffsetX: number, totalOffsetY: number) => void): TextInputAttribute {
    throw new Error('Method not implemented.');
  }
  maxLength(value: number): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputMaxLengthModifier.identity,
      TextInputMaxLengthModifier, value);
    return this;
  }
  fontColor(value: ResourceColor): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputFontColorModifier.identity,
      TextInputFontColorModifier, value);
    return this;
  }

  fontSize(value: Length): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputFontSizeModifier.identity,
      TextInputFontSizeModifier, value);
    return this;
  }
  fontStyle(value: FontStyle): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputFontStyleModifier.identity,
      TextInputFontStyleModifier, value);
    return this;
  }
  fontWeight(value: number | FontWeight | string): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputFontWeightModifier.identity,
      TextInputFontWeightModifier, value);
    return this;
  }

  fontFamily(value: ResourceStr): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputFontFamilyModifier.identity,
      TextInputFontFamilyModifier, value);
    return this;
  }
  inputFilter(value: ResourceStr, error?: (value: string) => void): TextInputAttribute {
    throw new Error('Method not implemented.');
  }
  onCopy(callback: (value: string) => void): TextInputAttribute {
    throw new Error('Method not implemented.');
  }
  onCut(callback: (value: string) => void): TextInputAttribute {
    throw new Error('Method not implemented.');
  }
  onPaste(callback: (value: string) => void): TextInputAttribute {
    throw new Error('Method not implemented.');
  }
  copyOption(value: CopyOptions): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputCopyOptionModifier.identity,
      TextInputCopyOptionModifier, value);
    return this;
  }

  showPasswordIcon(value: boolean): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputShowPasswordIconModifier.identity,
      TextInputShowPasswordIconModifier, value);
    return this;
  }
  textAlign(value: TextAlign): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputTextAlignModifier.identity,
      TextInputTextAlignModifier, value);
    return this;
  }
  style(value: TextInputStyle | TextContentStyle): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputStyleModifier.identity,
      TextInputStyleModifier, value);
    return this;
  }
  caretStyle(value: CaretStyle) {
    modifierWithKey(this._modifiersWithKeys, TextInputCaretStyleModifier.identity,
      TextInputCaretStyleModifier, value);
    return this;
  }

  selectedBackgroundColor(value: ResourceColor): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputSelectedBackgroundColorModifier.identity,
      TextInputSelectedBackgroundColorModifier, value);
    return this;
  }
  caretPosition(value: number): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputCaretPositionModifier.identity,
      TextInputCaretPositionModifier, value);
    return this;
  }
  enableKeyboardOnFocus(value: boolean): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputEnableKeyboardOnFocusModifier.identity,
      TextInputEnableKeyboardOnFocusModifier, value);
    return this;
  }

  passwordIcon(value: PasswordIcon): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputPasswordIconModifier.identity,
      TextInputPasswordIconModifier, value);
    return this;
  }
  showError(value: string | undefined): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputShowErrorModifier.identity,
      TextInputShowErrorModifier, value);
    return this;
  }
  showUnit(event: () => void): TextInputAttribute {
    throw new Error('Method not implemented.');
  }
  showUnderline(value: boolean): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputShowUnderlineModifier.identity,
      TextInputShowUnderlineModifier, value);
    return this;
  }
  selectionMenuHidden(value: boolean): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputSelectionMenuHiddenModifier.identity, TextInputSelectionMenuHiddenModifier, value);
    return this;
  }
  barState(value: BarState): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputBarStateModifier.identity, TextInputBarStateModifier, value);
    return this;
  }
  maxLines(value: number): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputMaxLinesModifier.identity, TextInputMaxLinesModifier, value);
    return this;
  }
  customKeyboard(event: () => void): TextInputAttribute {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.TextInput.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkTextInputComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
}

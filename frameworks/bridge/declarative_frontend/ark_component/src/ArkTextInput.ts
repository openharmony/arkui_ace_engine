/// <reference path="./import.ts" />
class TextInputStyleModifier extends Modifier<TextInputStyle | TextContentStyle> {
  static identity: Symbol = Symbol('textInputStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetStyle(node);
    } else {
      GetUINativeModule().textInput.setStyle(node, this.value!);
    }
  }
}
class TextInputMaxLengthModifier extends Modifier<number> {
  static identity: Symbol = Symbol('textInputMaxLength');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetMaxLength(node);
    } else {
      GetUINativeModule().textInput.setMaxLength(node, this.value!);
    }
  }
}
class TextInputMaxLinesModifier extends Modifier<number> {
  static identity: Symbol = Symbol('textInputMaxLines');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetMaxLines(node);
    } else {
      GetUINativeModule().textInput.setMaxLines(node, this.value!);
    }
  }
}
class TextInputShowPasswordIconModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('textInputShowPasswordIcon');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetShowPasswordIcon(node);
    } else {
      GetUINativeModule().textInput.setShowPasswordIcon(node, this.value!);
    }
  }
}
class TextInputTextAlignModifier extends Modifier<TextAlign> {
  static identity: Symbol = Symbol('textInputTextAlign');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetTextAlign(node);
    } else {
      GetUINativeModule().textInput.setTextAlign(node, this.value!);
    }
  }
}

class TextInputPlaceholderFontModifier extends ModifierWithKey<Font> {
  static identity: Symbol = Symbol('textInputPlaceholderFont');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetPlaceholderFont(node);
    } else {
      if (!(isNumber(this.value.size)) && !(isString(this.value.size)) &&
        !(isResource(this.value.size))) {
        this.value.size = undefined;
      }
      if (!(isString(this.value.family)) && !(isResource(this.value.family))) {
        this.value.family = undefined;
      }
      GetUINativeModule().textInput.setPlaceholderFont(node, this.value.size,
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

class TextInputPlaceholderColorModifier extends ModifierWithKey<ResourceColor> {
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

class TextInputSelectionMenuHiddenModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('textInputSelectionMenuHidden');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetSelectionMenuHidden(node);
    } else {
      GetUINativeModule().textInput.setSelectionMenuHidden(node, this.value!);
    }
  }
}
class TextInputShowUnderlineModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('textInputShowUnderLine');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetShowUnderline(node);
    } else {
      GetUINativeModule().textInput.setShowUnderline(node, this.value!);
    }
  }
}
class TextInputShowErrorModifier extends Modifier<string | undefined> {
  static identity: Symbol = Symbol('textInputShowError');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetShowError(node);
    } else {
      GetUINativeModule().textInput.setShowError(node, this.value!);
    }
  }
}
class TextInputTypeModifier extends Modifier<InputType> {
  static identity: Symbol = Symbol('textInputType');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetType(node);
    } else {
      GetUINativeModule().textInput.setType(node, this.value!);
    }
  }
}

class TextInputCaretPositionModifier extends Modifier<number> {
  static identity: Symbol = Symbol('textInputCaretPosition');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetCaretPosition(node);
    } else {
      GetUINativeModule().textInput.setCaretPosition(node, this.value);
    }
  }
}

class TextInputCopyOptionModifier extends Modifier<number> {
  static identity: Symbol = Symbol('textInputCopyOption');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetCopyOption(node);
    } else {
      GetUINativeModule().textInput.setCopyOption(node, this.value);
    }
  }
}

class TextInputEnableKeyboardOnFocusModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('textInputEnableKeyboardOnFocus');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetEnableKeyboardOnFocus(node);
    } else {
      GetUINativeModule().textInput.setEnableKeyboardOnFocus(node, this.value);
    }
  }
}

class TextInputCaretStyleModifier extends ModifierWithKey<CaretStyle> {
  static identity: Symbol = Symbol('textInputCaretStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetCaretStyle(node);
    } else if (!isObject(this.value) && !isString(this.value.width) &&
      !isNumber(this.value.width) && !isResource(this.value.width)) {
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

class TextInputEnterKeyTypeModifier extends Modifier<number> {
  static identity: Symbol = Symbol('textInputEnterKeyType');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetEnterKeyType(node);
    } else {
      GetUINativeModule().textInput.setEnterKeyType(node, this.value);
    }
  }
}

class TextInputBarStateModifier extends Modifier<number> {
  static identity: Symbol = Symbol('textInputBarState');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetBarState(node);
    } else {
      GetUINativeModule().textInput.setBarState(node, this.value);
    }
  }
}

class TextInputCaretColorModifier extends ModifierWithKey<ResourceColor> {
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
  static identity: Symbol = Symbol('textInputFontSize');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetFontSize(node);
    } else if (!isString(this.value) && !isNumber(this.value) && !isResource(this.value)) {
      GetUINativeModule().textInput.resetFontSize(node);
    } else {
      GetUINativeModule().textInput.setFontSize(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class TextInputFontStyleModifier extends Modifier<number> {
  static identity: Symbol = Symbol('textInputFontStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetFontStyle(node);
    } else {
      GetUINativeModule().textInput.setFontStyle(node, this.value!);
    }
  }
}

class TextInputFontWeightModifier extends Modifier<number | string> {
  static identity: Symbol = Symbol('textInputFontWeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textInput.resetFontWeight(node);
    } else {
      GetUINativeModule().textInput.setFontWeight(node, this.value!);
    }
  }
}

class TextInputFontFamilyModifier extends ModifierWithKey<ResourceStr> {
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
    if (value in InputType) {
      modifier(this._modifiers, TextInputTypeModifier, value);
    } else {
      modifier(this._modifiers, TextInputTypeModifier, undefined);
    }
    return this;
  }

  placeholderColor(value: ResourceColor): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputPlaceholderColorModifier.identity,
      TextInputPlaceholderColorModifier, value);
    return this;
  }

  placeholderFont(value?: Font): TextInputAttribute {
    if (!isLengthType(value.weight)) {
      value.weight = undefined;
    }
    if (!(value.style in FontStyle)) {
      value.style = undefined;
    }
    modifierWithKey(this._modifiersWithKeys, TextInputPlaceholderFontModifier.identity,
      TextInputPlaceholderFontModifier, value);
    return this;
  }
  enterKeyType(value: EnterKeyType): TextInputAttribute {
    if (value in EnterKeyType) {
      modifier(this._modifiers, TextInputEnterKeyTypeModifier, value);
    } else {
      modifier(this._modifiers, TextInputEnterKeyTypeModifier, EnterKeyType.Done);
    }
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
    if (!isNumber(value) || value === undefined || value === null) {
      modifier(this._modifiers, TextInputMaxLengthModifier, undefined);
    } else {
      modifier(this._modifiers, TextInputMaxLengthModifier, value);
    }
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
    if (!(value in FontStyle)) {
      value = undefined;
    }
    modifier(this._modifiers, TextInputFontStyleModifier, value);
    return this;
  }
  fontWeight(value: number | FontWeight | string): TextInputAttribute {
    if (!isLengthType(value)) {
      modifier(this._modifiers, TextInputFontWeightModifier, undefined);
    } else {
      modifier(this._modifiers, TextInputFontWeightModifier, value);
    }
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
    if (isNumber(value)) {
      modifier(this._modifiers, TextInputCopyOptionModifier, value);
    } else {
      modifier(this._modifiers, TextInputCopyOptionModifier, undefined);
    }
    return this;
  }

  showPasswordIcon(value: boolean): TextInputAttribute {
    if (isBoolean(value)) {
      modifier(this._modifiers, TextInputShowPasswordIconModifier, value);
    } else {
      modifier(this._modifiers, TextInputShowPasswordIconModifier, undefined);
    }
    return this;
  }
  textAlign(value: TextAlign): TextInputAttribute {
    if (value) {
      modifier(this._modifiers, TextInputTextAlignModifier, value);
    } else {
      modifier(this._modifiers, TextInputTextAlignModifier, undefined);
    }
    return this;
  }
  style(value: TextInputStyle | TextContentStyle): TextInputAttribute {
    if (value) {
      modifier(this._modifiers, TextInputStyleModifier, value);
    } else {
      modifier(this._modifiers, TextInputStyleModifier, undefined);
    }
    return this;
  }
  caretStyle(value: CaretStyle) {
    if (value) {
      modifierWithKey(this._modifiersWithKeys, TextInputCaretStyleModifier.identity,
        TextInputCaretStyleModifier, value);
    } else {
      modifierWithKey(this._modifiersWithKeys, TextInputCaretStyleModifier.identity,
        TextInputCaretStyleModifier, undefined);
    }
    return this;
  }

  selectedBackgroundColor(value: ResourceColor): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputSelectedBackgroundColorModifier.identity,
      TextInputSelectedBackgroundColorModifier, value);
    return this;
  }
  caretPosition(value: number): TextInputAttribute {
    modifier(this._modifiers, TextInputCaretPositionModifier, value);
    return this;
  }
  enableKeyboardOnFocus(value: boolean): TextInputAttribute {
    modifier(this._modifiers, TextInputEnableKeyboardOnFocusModifier, value);
    return this;
  }

  passwordIcon(value: PasswordIcon): TextInputAttribute {
    modifierWithKey(this._modifiersWithKeys, TextInputPasswordIconModifier.identity,
      TextInputPasswordIconModifier, value);
    return this;
  }
  showError(value: string | undefined): TextInputAttribute {
    if (isString(value)) {
      modifier(this._modifiers, TextInputShowErrorModifier, value);
    } else {
      modifier(this._modifiers, TextInputShowErrorModifier, undefined);
    }
    return this;
  }
  showUnit(event: () => void): TextInputAttribute {
    throw new Error('Method not implemented.');
  }
  showUnderline(value: boolean): TextInputAttribute {
    if (isBoolean(value)) {
      modifier(this._modifiers, TextInputShowUnderlineModifier, value);
    } else {
      modifier(this._modifiers, TextInputShowUnderlineModifier, undefined);
    }
    return this;
  }
  selectionMenuHidden(value: boolean): TextInputAttribute {
    if (isBoolean(value)) {
      modifier(this._modifiers, TextInputSelectionMenuHiddenModifier, value);
    } else {
      modifier(this._modifiers, TextInputSelectionMenuHiddenModifier, undefined);
    }

    return this;
  }
  barState(value: BarState): TextInputAttribute {
    if (value in BarState) {
      modifier(this._modifiers, TextInputBarStateModifier, value);
    } else {
      modifier(this._modifiers, TextInputBarStateModifier, undefined);
    }
    return this;
  }

  maxLines(value: number): TextInputAttribute {
    if (typeof value === "number") {
      modifier(this._modifiers, TextInputMaxLinesModifier, value);
    } else {
      modifier(this._modifiers, TextInputMaxLinesModifier, undefined);
    }
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
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
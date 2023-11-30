/// <reference path="./import.ts" />
class TextAreaFontStyleModifier extends Modifier<number> {
  static identity: Symbol = Symbol('textAreaFontStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textArea.resetFontStyle(node);
    } else {
      GetUINativeModule().textArea.setFontStyle(node, this.value!);
    }
  }
}

class TextAreaCopyOptionModifier extends Modifier<CopyOptions> {
  static identity: Symbol = Symbol('textAreaCopyOption');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textArea.resetCopyOption(node);
    } else {
      GetUINativeModule().textArea.setCopyOption(node, this.value!);
    }
  }
}

class TextAreaMaxLinesModifier extends Modifier<number | undefined> {
  static identity: Symbol = Symbol('textAreaMaxLines');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textArea.resetMaxLines(node);
    } else {
      GetUINativeModule().textArea.setMaxLines(node, this.value!);
    }
  }
}

class TextAreaFontSizeModifier extends Modifier<string | number> {
  static identity: Symbol = Symbol('textAreaFontSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textArea.resetFontSize(node);
    } else {
      GetUINativeModule().textArea.setFontSize(node, this.value!);
    }
  }
}

class TextAreaPlaceholderColorModifier extends Modifier<number> {
  static identity: Symbol = Symbol('textAreaPlaceholderColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textArea.resetPlaceholderColor(node);
    } else {
      GetUINativeModule().textArea.setPlaceholderColor(node, this.value!);
    }
  }
}

class TextAreaFontColorModifier extends Modifier<number> {
  static identity: Symbol = Symbol('textAreaFontColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textArea.resetFontColor(node);
    } else {
      GetUINativeModule().textArea.setFontColor(node, this.value!);
    }
  }
}

class TextAreaFontWeightModifier extends Modifier<number> {
  static identity: Symbol = Symbol('textAreaFontWeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textArea.resetFontWeight(node);
    } else {
      GetUINativeModule().textArea.setFontWeight(node, this.value!);
    }
  }
}

class TextAreaBarStateModifier extends Modifier<number> {
  static identity: Symbol = Symbol('textAreaBarState');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textArea.resetBarState(node);
    } else {
      GetUINativeModule().textArea.setBarState(node, this.value!);
    }
  }
}

class TextAreaEnableKeyboardOnFocusModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('textAreaEnableKeyboardOnFocus');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textArea.resetEnableKeyboardOnFocus(node);
    } else {
      GetUINativeModule().textArea.setEnableKeyboardOnFocus(node, this.value!);
    }
  }
}

class TextAreaFontFamilyModifier extends Modifier<string> {
  static identity: Symbol = Symbol('textAreaFontFamily');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textArea.resetFontFamily(node);
    } else {
      GetUINativeModule().textArea.setFontFamily(node, this.value!);
    }
  }
}

class TextAreaCaretColorModifier extends Modifier<number> {
  static identity: Symbol = Symbol('textAreaCaretColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textArea.resetCaretColor(node);
    } else {
      GetUINativeModule().textArea.setCaretColor(node, this.value!);
    }
  }
}

class TextAreaMaxLengthModifier extends Modifier<number> {
  static identity: Symbol = Symbol('textAreaMaxLength');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textArea.resetMaxLength(node);
    } else {
      GetUINativeModule().textArea.setMaxLength(node, this.value!);
    }
  }
}

class TextAreaStyleModifier extends Modifier<number> {
  static identity: Symbol = Symbol('textAreaStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textArea.resetStyle(node);
    } else {
      GetUINativeModule().textArea.setStyle(node, this.value!);
    }
  }
}

class TextAreaSelectionMenuHiddenModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('textAreaSelectionMenuHidden');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textArea.resetSelectionMenuHidden(node);
    } else {
      GetUINativeModule().textArea.setSelectionMenuHidden(node, this.value!);
    }
  }
}

class TextAreaPlaceholderFontModifier extends Modifier<ArkFont> {
  static identity: Symbol = Symbol('textAreaPlaceholderFont');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textArea.resetPlaceholderFont(node);
    } else {
      GetUINativeModule().textArea.setPlaceholderFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
}

class TextAreaTextAlignModifier extends Modifier<number> {
  static identity: Symbol = Symbol('textAreaTextAlign');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textArea.resetTextAlign(node);
    } else {
      GetUINativeModule().textArea.setTextAlign(node, this.value!);
    }
  }
}

class TextAreaShowCounterModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('textAreaShowCounter');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textArea.resetShowCounter(node);
    } else {
      GetUINativeModule().textArea.setShowCounter(node, this.value!);
    }
  }
}

class ArkTextAreaComponent extends ArkComponent implements CommonMethod<TextAreaAttribute> {
  type(value: TextAreaType): TextAreaAttribute {
    throw new Error('Method not implemented.');
  }
  placeholderColor(value: ResourceColor): TextAreaAttribute {
    let arkColor = new ArkColor();
    if (arkColor.parseColorValue(value)) {
      modifier(this._modifiers, TextAreaPlaceholderColorModifier, arkColor.color);
    }
    return this;
  }
  placeholderFont(value: Font): TextAreaAttribute {
    let arkValue: ArkFont = new ArkFont();
    if (isLengthType(value.size)) {
      arkValue.size = <string | number>value.size;
    }
    if (isLengthType(value.weight)) {
      arkValue.weight = value.weight;
    }
    if (isString(value.family)) {
      arkValue.family = <string>value.family;
    }
    if (value.style in FontStyle) {
      arkValue.style = value.style;
    }
    modifier(this._modifiers, TextAreaPlaceholderFontModifier, arkValue);
    return this;
  }


  textAlign(value: TextAlign): TextAreaAttribute {
    if (value) {
      modifier(this._modifiers, TextAreaTextAlignModifier, value);
    } else {
      modifier(this._modifiers, TextAreaTextAlignModifier, TextAlign.Start);
    }
    return this;
  }
  caretColor(value: ResourceColor): TextAreaAttribute {
    let arkColor = new ArkColor();
    if (arkColor.parseColorValue(value)) {
      modifier(this._modifiers, TextAreaCaretColorModifier, arkColor.color);
    }
    return this;
  }
  fontColor(value: ResourceColor): TextAreaAttribute {
    let arkColor = new ArkColor();
    if (arkColor.parseColorValue(value)) {
      modifier(this._modifiers, TextAreaFontColorModifier, arkColor.color);
    }
    return this;
  }
  fontSize(value: Length): TextAreaAttribute {
    if (isLengthType(value)) {
      modifier(this._modifiers, TextAreaFontSizeModifier, <string | number>value);
    } else {
      modifier(this._modifiers, TextAreaFontSizeModifier, 16);
    }
    return this;
  }
  fontStyle(value: FontStyle): TextAreaAttribute {
    let arkValue = FontStyle.Normal;
    if (value) {
      arkValue = value;
    }
    modifier(this._modifiers, TextAreaFontStyleModifier, arkValue);
    return this;
  }
  fontWeight(value: number | FontWeight | string): TextAreaAttribute {
    if (!isLengthType(value)) {
      modifier(this._modifiers, TextAreaFontWeightModifier, undefined);
    } else {
      modifier(this._modifiers, TextAreaFontWeightModifier, value);
    }
    return this;
  }
  fontFamily(value: ResourceStr): TextAreaAttribute {
    let arkValue = 'HarmonyOS Sans';
    if (isString(value)) {
      arkValue = <string>value;
    }
    modifier(this._modifiers, TextAreaFontFamilyModifier, arkValue);
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
    if (value === undefined) {
      value = CopyOptions.LocalDevice;
      modifier(this._modifiers, TextAreaCopyOptionModifier, value);
    }
    let copyOptions = CopyOptions.None;
    if (isNumber(value)) {
      copyOptions = value;
    }
    modifier(this._modifiers, TextAreaCopyOptionModifier, copyOptions);
    return this;
  }

  enableKeyboardOnFocus(value: boolean): TextAreaAttribute {
    if (value === undefined) {
      return this;
    }
    if (isUndefined(value) || !isBoolean(value)) {
      modifier(this._modifiers, TextAreaEnableKeyboardOnFocusModifier, true);
      return this;
    }
    modifier(this._modifiers, TextAreaEnableKeyboardOnFocusModifier, Boolean(value));
    return this;
  }

  maxLength(value: number): TextAreaAttribute {
    if (!value || isNaN(value)) {
      modifier(this._modifiers, TextAreaMaxLengthModifier, undefined);
      return this;
    }
    modifier(this._modifiers, TextAreaMaxLengthModifier, value);
    return this;
  }
  showCounter(value: boolean): TextAreaAttribute {
    let showCounter = false;
    if (isBoolean(value)) {
      showCounter = value;
    }
    modifier(this._modifiers, TextAreaShowCounterModifier, showCounter);
    return this;
  }
  style(value: TextContentStyle): TextAreaAttribute {
    if (value) {
      modifier(this._modifiers, TextAreaStyleModifier, value);
    } else {
      modifier(this._modifiers, TextAreaStyleModifier, undefined);
    }
    return this;
  }
  barState(value: BarState): TextAreaAttribute {
    if (value === null || value === undefined || !isNumber(value)) {
      modifier(this._modifiers, TextAreaBarStateModifier, BarState.Auto);
      return this;
    }
    modifier(this._modifiers, TextAreaBarStateModifier, value);
    return this;
  }
  selectionMenuHidden(value: boolean): TextAreaAttribute {
    let selectionMenuHidden = false;
    if (isBoolean(value)) {
      selectionMenuHidden = value;
    }
    modifier(this._modifiers, TextAreaSelectionMenuHiddenModifier, selectionMenuHidden);
    return this;
  }
  maxLines(value: number): TextAreaAttribute {
    if (!isNumber(value)) {
      modifier(this._modifiers, TextAreaMaxLinesModifier, undefined);
      return this;
    }
    if (Number(value) <= 0) {
      modifier(this._modifiers, TextAreaMaxLinesModifier, undefined);
      return this;
    }
    modifier(this._modifiers, TextAreaMaxLinesModifier, Number(value));
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
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();

}
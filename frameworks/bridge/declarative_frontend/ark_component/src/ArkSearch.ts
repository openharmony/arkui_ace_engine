/// <reference path="./import.ts" />

class SearchSelectionMenuHiddenModifier extends Modifier<boolean> {
  static identity = Symbol('searchSelectionMenuHidden');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().search.resetSelectionMenuHidden(node);
    } else {
      GetUINativeModule().search.setSelectionMenuHidden(node, this.value!);
    }
  }
}

class SearchCaretStyleModifier extends Modifier<ArkCaretStyle> {
  static identity = Symbol('searchCaretStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().search.resetCaretStyle(node);
    } else {
      GetUINativeModule().search.setCaretStyle(node, this.value.width, this.value.color);
    }
  }
}

class SearchEnableKeyboardOnFocusModifier extends Modifier<boolean> {
  static identity = Symbol('searchEnableKeyboardOnFocus');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().search.resetEnableKeyboardOnFocus(node);
    } else {
      GetUINativeModule().search.setEnableKeyboardOnFocus(node, this.value!);
    }
  }
}

class SearchSearchIconModifier extends Modifier<ArkIconOptions> {
  static identity = Symbol('searchSearchIcon');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().search.resetSearchIcon(node);
    } else {
      GetUINativeModule().search.setSearchIcon(node, this.value.size,
        this.value.color, this.value.src);
    }
  }
}

class SearchPlaceholderFontModifier extends Modifier<ArkFont> {
  static identity = Symbol('searchPlaceholderFont');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().search.resetPlaceholderFont(node);
    } else {
      GetUINativeModule().search.setPlaceholderFont(node, this.value.size,
        this.value.weight, this.value.family, this.value.style);
    }
  }
}

class SearchSearchButtonModifier extends Modifier<ArkSearchButton> {
  static identity = Symbol('searchSearchButton');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().search.resetSearchButton(node);
    } else {
      GetUINativeModule().search.setSearchButton(node, this.value.value,
        this.value.fontSize, this.value.fontColor);
    }
  }
}

class SearchFontColorModifier extends Modifier<number> {
  static identity = Symbol('searchFontColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().search.resetFontColor(node);
    } else {
      GetUINativeModule().search.setFontColor(node, this.value!);
    }
  }
}

class SearchCopyOptionModifier extends Modifier<CopyOptions> {
  static identity = Symbol('searchCopyOption');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().search.resetCopyOption(node);
    } else {
      GetUINativeModule().search.setCopyOption(node, this.value!);
    }
  }
}

class SearchTextFontModifier extends Modifier<ArkFont> {
  static identity = Symbol('searchTextFont');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().search.resetTextFont(node);
    } else {
      GetUINativeModule().search.setTextFont(node, this.value.size,
        this.value.weight, this.value.family, this.value.style);
    }
  }
}

class SearchPlaceholderColorModifier extends Modifier<number> {
  static identity = Symbol('searchPlaceholderColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().search.resetPlaceholderColor(node);
    } else {
      GetUINativeModule().search.setPlaceholderColor(node, this.value!);
    }
  }
}

class SearchCancelButtonModifier extends Modifier<ArkCancelButton> {
  static identity = Symbol('searchCancelButton');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().search.resetCancelButton(node);
    } else {
      GetUINativeModule().search.setCancelButton(node, this.value.style,
        this.value.size, this.value.color, this.value.src);
    }
  }
}

class SearchTextAlignModifier extends Modifier<TextAlign> {
  static identity = Symbol('searchTextAlign');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().search.resetTextAlign(node);
    } else {
      GetUINativeModule().search.setTextAlign(node, this.value!);
    }
  }
}

class ArkSearchComponent extends ArkComponent implements CommonMethod<SearchAttribute>{
  onEditChange(callback: (isEditing: boolean) => void): SearchAttribute {
    throw new Error('Method not implemented.');
  }
  type(value: SearchType): SearchAttribute {
    throw new Error('Method not implemented.');
  }
  maxLength(value: number): SearchAttribute {
    throw new Error('Method not implemented.');
  }
  onEditChanged(callback: (isEditing: boolean) => void): SearchAttribute {
    throw new Error('Method not implemented.');
  }
  customKeyboard(event: () => void): SearchAttribute {
    throw new Error('Method not implemented.');
  }
  showUnit(event: () => void): SearchAttribute {
    throw new Error('Method not implemented.');
  }
  onContentScroll(callback: (totalOffsetX: number, totalOffsetY: number) => void): SearchAttribute {
    throw new Error('Method not implemented.');
  }
  onChange(callback: (value: string) => void): SearchAttribute {
    throw new Error('Method not implemented.');
  }
  onTextSelectionChange(callback: (selectionStart: number, selectionEnd: number) => void): SearchAttribute {
    throw new Error('Method not implemented.');
  }
  onCopy(callback: (value: string) => void): SearchAttribute {
    throw new Error('Method not implemented.');
  }
  onCut(callback: (value: string) => void): SearchAttribute {
    throw new Error('Method not implemented.');
  }
  onSubmit(callback: (value: string) => void): SearchAttribute {
    throw new Error('Method not implemented.');
  }
  onPaste(callback: (value: string) => void): SearchAttribute {
    throw new Error('Method not implemented.');
  }
  showCounter(value: boolean): SearchAttribute {
    throw new Error('Method not implemented.');
  }
  searchButton(value: string, option?: SearchButtonOptions): SearchAttribute {
    let searchButton = new ArkSearchButton();
    if (!isString(value)) {
      value = '';
    }
    if (isObject(option)) {
      if (!isLengthType(option.fontSize)) {
        option.fontSize = '';
      }
      let fontColor = option.fontColor;
      let arkColor: ArkColor = new ArkColor();
      if (fontColor === undefined || fontColor === null || !arkColor.parseColorValue(fontColor)) {
        option.fontColor = undefined;
      } else {
        option.fontColor = arkColor.color;
      }
    } else {
      option.fontSize = '';
      option.fontColor = undefined;
    }
    searchButton.value = value;
    searchButton.fontColor = <number>option.fontColor;
    searchButton.fontSize = <number | string>option.fontSize;
    modifier(this._modifiers, SearchSearchButtonModifier, searchButton);
    return this;
  }
  selectionMenuHidden(value: boolean): SearchAttribute {
    if (value === undefined || !isBoolean(value)) {
      modifier(this._modifiers, SearchSelectionMenuHiddenModifier, false);
      return this;
    }
    modifier(this._modifiers, SearchSelectionMenuHiddenModifier, value);
    return this;
  }
  enableKeyboardOnFocus(value: boolean): SearchAttribute {
    if (value === undefined || !isBoolean(value)) {
      modifier(this._modifiers, SearchEnableKeyboardOnFocusModifier, true);
      return this;
    }
    modifier(this._modifiers, SearchEnableKeyboardOnFocusModifier, value);
    return this;
  }
  caretStyle(value: CaretStyle): SearchAttribute {
    let arkCaretStyle: ArkCaretStyle = new ArkCaretStyle();
    if (isObject(value)) {
      let caretWidth = <string | number>value.width;
      if (!isLengthType(caretWidth)) {
        arkCaretStyle.width = undefined;
      } else {
        arkCaretStyle.width = caretWidth;
      }
      let caretColor = <number>value.color;
      let arkColor: ArkColor = new ArkColor();
      if (!caretColor || !arkColor.parseColorValue(caretColor)) {
        caretColor = undefined;
      } else {
        caretColor = arkColor.color;
      }
      arkCaretStyle.color = caretColor;
      modifier(this._modifiers, SearchCaretStyleModifier, arkCaretStyle);
    }
    return this;
  }
  cancelButton(value: { style?: CancelButtonStyle, icon?: IconOptions }): SearchAttribute {
    let cancelButton = new ArkCancelButton();
    if (!isObject(value)) {
      return this;
    }
    let style = value.style;
    if (!style || isNaN(style)) {
      style = CancelButtonStyle.INPUT;
    }
    value.style = style;
    cancelButton.style = value.style;
    let icon = value.icon;
    if (!icon || !isObject(icon)) {
      icon.size = '';
      icon.color = undefined;
      icon.src = '';
    } else {
      if (!icon.size || !isLengthType(icon.size)) {
        icon.size = '';
      }
      if (!icon.src || !isString(icon.src)) {
        icon.src = '';
      }
      let arkColor: ArkColor = new ArkColor();
      if (!icon.color || !arkColor.parseColorValue(icon.color)) {
        icon.color = undefined;
      } else {
        icon.color = arkColor.color;
      }
    }
    cancelButton.color = <number>icon.color;
    cancelButton.size = <number | string>icon.size;
    cancelButton.src = <string>icon.src;
    modifier(this._modifiers, SearchCancelButtonModifier, cancelButton);
    return this;
  }
  searchIcon(value: IconOptions): SearchAttribute {
    let iconOptions = new ArkIconOptions();
    if (!isObject(value)) {
      iconOptions.size = '';
      iconOptions.color = undefined;
      iconOptions.src = '';
    } else {
      iconOptions.size = <number | string>value.size;
      iconOptions.color = <number>value.color;
      iconOptions.src = <string>value.src;
      if (!iconOptions.size || !isLengthType(iconOptions.size)) {
        iconOptions.size = '';
      }
      if (!iconOptions.src || !isString(iconOptions.src)) {
        iconOptions.src = '';
      }
      let arkColor: ArkColor = new ArkColor();
      if (!iconOptions.color || !arkColor.parseColorValue(iconOptions.color)) {
        iconOptions.color = undefined;
      } else {
        iconOptions.color = arkColor.color;
      }
      modifier(this._modifiers, SearchSearchIconModifier, iconOptions);
    }
    return this;
  }
  fontColor(value: ResourceColor): SearchAttribute {
    let arkColor: ArkColor = new ArkColor();
    if (arkColor.parseColorValue(value)) {
      modifier(this._modifiers, SearchFontColorModifier, arkColor.color);
    } else {
      modifier(this._modifiers, SearchFontColorModifier, undefined);
    }
    return this;
  }
  placeholderColor(value: ResourceColor): SearchAttribute {
    let arkColor: ArkColor = new ArkColor();
    if (arkColor.parseColorValue(value)) {
      modifier(this._modifiers, SearchPlaceholderColorModifier, arkColor.color);
    } else {
      modifier(this._modifiers, SearchPlaceholderColorModifier, undefined);
    }
    return this;
  }
  placeholderFont(value?: Font): SearchAttribute {
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
    modifier(this._modifiers, SearchPlaceholderFontModifier, arkValue);
    return this;
  }
  textFont(value?: Font): SearchAttribute {
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
    modifier(this._modifiers, SearchTextFontModifier, arkValue);
    return this;
  }
  copyOption(value: CopyOptions): SearchAttribute {
    if (value === undefined) {
      value = CopyOptions.LocalDevice;
      modifier(this._modifiers, SearchCopyOptionModifier, value);
    }
    let copyOptions = CopyOptions.None;
    if (isNumber(value)) {
      copyOptions = value;
    }
    modifier(this._modifiers, SearchCopyOptionModifier, copyOptions);
    return this;
  }
  textAlign(value: TextAlign): SearchAttribute {
    let TEXT_ALIGNS: TextAlign[] = [
      TextAlign.Start, TextAlign.Center, TextAlign.End, TextAlign.JUSTIFY];
    if (value >= 0 && value <= TEXT_ALIGNS.length) {
      modifier(this._modifiers, SearchTextAlignModifier, value);
    }
    return this;
  }
}
// @ts-ignore
globalThis.Search.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkSearchComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}

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

class SearchCaretStyleModifier extends ModifierWithKey<CaretStyle> {
  static identity = Symbol('searchCaretStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().search.resetCaretStyle(node);
    } else {
      if (this.value === null || !isObject(this.value)) {
        GetUINativeModule().search.resetCaretStyle(node);
      } else {
        GetUINativeModule().search.setCaretStyle(node, this.value.width,
          this.value.color);
      }
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.width, this.value.width) ||
      !isBaseOrResourceEqual(this.stageValue.color, this.value.color)
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

class SearchSearchIconModifier extends ModifierWithKey<IconOptions> {
  static identity = Symbol('searchSearchIcon');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().search.resetSearchIcon(node);
    } else {
      if (this.value === null || !isObject(this.value)) {
        GetUINativeModule().search.resetSearchIcon(node);
      } else {
        GetUINativeModule().search.setSearchIcon(node, this.value.size,
          this.value.color, this.value.src);
      }
    }
  }
  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !(this.stageValue.size === this.value.size &&
        this.stageValue.color === this.value.color &&
        this.stageValue.src === this.value.src);
    } else {
      return true;
    }
  }
}

class SearchPlaceholderFontModifier extends ModifierWithKey<Font> {
  static identity = Symbol('searchPlaceholderFont');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().search.resetPlaceholderFont(node);
    } else {
      if (!(isNumber(this.value.size)) && !(isString(this.value.size)) && !(isResource(this.value.size))) {
        this.value.size = undefined;
      }
      if (!(isString(this.value.family)) && !(isResource(this.value.family))) {
        this.value.family = undefined;
      }
      GetUINativeModule().search.setPlaceholderFont(node, this.value.size,
        this.value.weight, this.value.family, this.value.style);
    }
  }
  checkObjectDiff(): boolean {
    if (this.stageValue.weight !== this.value.weight || this.stageValue.style !== this.value.style) {
      return true;
    }
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

class SearchSearchButtonModifier extends ModifierWithKey<ArkSearchButton> {
  static identity = Symbol('searchSearchButton');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().search.resetSearchButton(node);
    } else {
      if (this.value === null || !isObject(this.value)) {
        GetUINativeModule().search.resetSearchButton(node);
      } else {
        GetUINativeModule().search.setSearchButton(node, this.value.value,
          this.value.fontSize, this.value.fontColor);
      }
    }
  }
  checkObjectDiff(): boolean {
    if (!(this.stageValue.value === this.value.value)) {
      return true;
    }
    else {
      return !isBaseOrResourceEqual(this.stageValue.fontSize, this.value.fontSize) ||
        !isBaseOrResourceEqual(this.stageValue.fontColor, this.value.fontColor);
    }
  }
}

class SearchFontColorModifier extends ModifierWithKey<ResourceColor> {
  static identity = Symbol('searchFontColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().search.resetFontColor(node);
    } else {
      GetUINativeModule().search.setFontColor(node, this.value!);
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

class SearchTextFontModifier extends ModifierWithKey<Font> {
  static identity = Symbol('searchTextFont');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().search.resetTextFont(node);
    } else {
      if (!(isNumber(this.value.size)) && !(isString(this.value.size)) && !(isResource(this.value.size))) {
        this.value.size = undefined;
      }
      if (!(isString(this.value.family)) && !(isResource(this.value.family))) {
        this.value.family = undefined;
      }
      GetUINativeModule().search.setTextFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
  checkObjectDiff(): boolean {
    if (this.stageValue.weight !== this.value.weight || this.stageValue.style !== this.value.style) {
      return true;
    }
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

class SearchPlaceholderColorModifier extends ModifierWithKey<ResourceColor> {
  static identity = Symbol('searchPlaceholderColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().search.resetPlaceholderColor(node);
    } else {
      GetUINativeModule().search.setPlaceholderColor(node, this.value!);
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

class SearchCancelButtonModifier extends ModifierWithKey<{ style?: CancelButtonStyle, icon?: IconOptions }> {
  static identity = Symbol('searchCancelButton');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().search.resetCancelButton(node);
    } else {
      if (this.value === null || !isObject(this.value)) {
        GetUINativeModule().search.resetCancelButton(node);
      } else {
        GetUINativeModule().search.setCancelButton(node, this.value.style,
          this.value.icon?.size, this.value.icon?.color, this.value.icon?.src);
      }
    }
  }
  checkObjectDiff(): boolean {
    if (!(this.stageValue.style === this.value.style)) {
      return true;
    }
    else {
      return !isBaseOrResourceEqual(this.stageValue.icon?.size, this.value.icon?.size) ||
        !isBaseOrResourceEqual(this.stageValue.icon?.color, this.value.icon?.color) ||
        !isBaseOrResourceEqual(this.stageValue.icon?.src, this.value.icon?.src)
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
    searchButton.value = value;
    searchButton.fontColor = option?.fontColor;
    searchButton.fontSize = option?.fontSize;
    modifierWithKey(this._modifiersWithKeys, SearchSearchButtonModifier.identity, SearchSearchButtonModifier, searchButton);
    return this;
  }
  selectionMenuHidden(value: boolean): SearchAttribute {
    if (value === undefined || !isBoolean(value)) {
      modifier(this._modifiers, SearchSelectionMenuHiddenModifier, undefined);
      return this;
    }
    modifier(this._modifiers, SearchSelectionMenuHiddenModifier, value);
    return this;
  }
  enableKeyboardOnFocus(value: boolean): SearchAttribute {
    if (value === undefined || !isBoolean(value)) {
      modifier(this._modifiers, SearchEnableKeyboardOnFocusModifier, undefined);
      return this;
    }
    modifier(this._modifiers, SearchEnableKeyboardOnFocusModifier, value);
    return this;
  }
  caretStyle(value: CaretStyle): SearchAttribute {
    modifierWithKey(this._modifiersWithKeys, SearchCaretStyleModifier.identity, SearchCaretStyleModifier, value);
    return this;
  }
  cancelButton(value: { style?: CancelButtonStyle, icon?: IconOptions }): SearchAttribute {
    if (!value) {
      modifierWithKey(this._modifiersWithKeys, SearchCancelButtonModifier.identity,
        SearchCancelButtonModifier, undefined);
    } else {
      switch (value?.style) {
        case CancelButtonStyle.CONSTANT: value.style = 0; break;
        case CancelButtonStyle.INVISIBLE: value.style = 1; break;
        case CancelButtonStyle.INPUT: value.style = 2; break;
        default: value.style = undefined; break;
      }
      modifierWithKey(this._modifiersWithKeys, SearchCancelButtonModifier.identity,
        SearchCancelButtonModifier, value);
    }
    return this;
  }
  searchIcon(value: IconOptions): SearchAttribute {
    modifierWithKey(this._modifiersWithKeys, SearchSearchIconModifier.identity, SearchSearchIconModifier, value);
    return this;
  }
  fontColor(value: ResourceColor): SearchAttribute {
    modifierWithKey(this._modifiersWithKeys, SearchFontColorModifier.identity, SearchFontColorModifier, value);
    return this;
  }
  placeholderColor(value: ResourceColor): SearchAttribute {
    modifierWithKey(this._modifiersWithKeys, SearchPlaceholderColorModifier.identity, SearchPlaceholderColorModifier, value);
    return this;
  }
  placeholderFont(value?: Font): SearchAttribute {
    modifierWithKey(this._modifiersWithKeys, SearchPlaceholderFontModifier.identity, SearchPlaceholderFontModifier, value);
    return this;
  }
  textFont(value?: Font): SearchAttribute {
    modifierWithKey(this._modifiersWithKeys, SearchTextFontModifier.identity, SearchTextFontModifier, value);
    return this;
  }
  copyOption(value: CopyOptions): SearchAttribute {
    if (value === null || value === undefined) {
      modifier(this._modifiers, SearchCopyOptionModifier, undefined);
    } else if (!(value in CopyOptions)) {
      modifier(this._modifiers, SearchCopyOptionModifier, undefined);
    } else {
      modifier(this._modifiers, SearchCopyOptionModifier, value);
    }
    return this;
  }
  textAlign(value: TextAlign): SearchAttribute {
    let TEXT_ALIGNS: TextAlign[] = [
      TextAlign.Start, TextAlign.Center, TextAlign.End, TextAlign.JUSTIFY];
    if (value >= 0 && value <= TEXT_ALIGNS.length) {
      modifier(this._modifiers, SearchTextAlignModifier, value);
    } else {
      modifier(this._modifiers, SearchTextAlignModifier, undefined);
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

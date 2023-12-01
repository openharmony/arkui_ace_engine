/// <reference path='./import.ts' />
class ArkAlphabetIndexerComponent extends ArkComponent implements AlphabetIndexerAttribute {
  onSelected(callback: (index: number) => void): this {
    throw new Error('Method not implemented.');
  }
  color(value: ResourceColor): this {
    let arkResourceColor = new ArkResourceColor()
    arkResourceColor.color = value;
    if (value) {
      modifier(this._modifiers, ColorModifier, arkResourceColor);
    } else {
      modifier(this._modifiers, ColorModifier, undefined);
    }
    return this;
  }
  selectedColor(value: ResourceColor): this {
    let arkResourceColor = new ArkResourceColor()
    arkResourceColor.color = value;
    if (value) {
      modifier(this._modifiers, SelectedColorModifier, arkResourceColor);
    } else {
      modifier(this._modifiers, SelectedColorModifier, undefined);
    }
    return this;
  }
  popupColor(value: ResourceColor): this {
    let arkResourceColor = new ArkResourceColor()
    arkResourceColor.color = value;
    if (value) {
      modifier(this._modifiers, PopupColorModifier, arkResourceColor);
    } else {
      modifier(this._modifiers, PopupColorModifier, undefined);
    }
    return this;
  }
  selectedBackgroundColor(value: ResourceColor): this {
    let arkResourceColor = new ArkResourceColor()
    arkResourceColor.color = value;
    if (value) {
      modifier(this._modifiers, SelectedBackgroundColorModifier, arkResourceColor);
    } else {
      modifier(this._modifiers, SelectedBackgroundColorModifier, undefined);
    }
    return this;
  }
  popupBackground(value: ResourceColor): this {
    let arkResourceColor = new ArkResourceColor()
    arkResourceColor.color = value;
    if (value) {
      modifier(this._modifiers, PopupBackgroundModifier, arkResourceColor);
    } else {
      modifier(this._modifiers, PopupBackgroundModifier, undefined);
    }
    return this;
  }
  popupSelectedColor(value: ResourceColor): this {
    let arkResourceColor = new ArkResourceColor()
    arkResourceColor.color = value;
    if (value) {
      modifier(this._modifiers, PopupSelectedColorModifier, arkResourceColor);
    } else {
      modifier(this._modifiers, PopupSelectedColorModifier, undefined);
    }
    return this;
  }
  popupUnselectedColor(value: ResourceColor): this {
    let arkResourceColor = new ArkResourceColor()
    arkResourceColor.color = value;
    if (value) {
      modifier(this._modifiers, PopupUnselectedColorModifier, arkResourceColor);
    } else {
      modifier(this._modifiers, PopupUnselectedColorModifier, undefined);
    }
    return this;
  }
  popupItemBackgroundColor(value: ResourceColor): this {
    let arkResourceColor = new ArkResourceColor()
    arkResourceColor.color = value;
    if (value) {
      modifier(this._modifiers, PopupItemBackgroundColorModifier, arkResourceColor);
    } else {
      modifier(this._modifiers, PopupItemBackgroundColorModifier, undefined);
    }
    return this;
  }
  usingPopup(value: boolean): this {
    if (typeof value === 'boolean') {
      modifier(this._modifiers, UsingPopupModifier, value);
    } else {
      modifier(this._modifiers, UsingPopupModifier, undefined);
    }
    return this;
  }
  selectedFont(value: Font): this {
    let font = new ArkFont();
    if (isObject(value)) {
      font.setSize(value.size);
      font.parseFontWeight(value.weight);
      font.setFamily(value.family);
      font.setStyle(value.style);
      modifier(this._modifiers, SelectedFontModifier, font);
    } else {
      modifier(this._modifiers, SelectedFontModifier, undefined);
    }
    return this;
  }
  popupFont(value: Font): this {
    let font = new ArkFont();
    if (isObject(value)) {
      font.setSize(value.size);
      font.parseFontWeight(value.weight);
      font.setFamily(value.family);
      font.setStyle(value.style);
      modifier(this._modifiers, PopupFontModifier, font);
    } else {
      modifier(this._modifiers, PopupFontModifier, undefined);
    }
    return this;
  }
  popupItemFont(value: Font): this {
    let font = new ArkFont();
    if (isObject(value)) {
      font.setSize(value.size);
      font.setStyle(value.style);
      modifier(this._modifiers, PopupItemFontModifier, font);
    } else {
      modifier(this._modifiers, PopupItemFontModifier, undefined);
    }
    return this;
  }
  itemSize(value: string | number): this {
    if (typeof value !== 'number' && typeof value !== 'string') {
      modifier(this._modifiers, ItemSizeModifier, undefined);
    }
    else {
      modifier(this._modifiers, ItemSizeModifier, value);
    }
    return this;
  }
  font(value: Font): this {
    let font = new ArkFont();
    if (isObject(value)) {
      font.setSize(value.size);
      font.parseFontWeight(value.weight);
      font.setFamily(value.family);
      font.setStyle(value.style);
      modifier(this._modifiers, AlphabetIndexerFontModifier, font);
    } else {
      modifier(this._modifiers, AlphabetIndexerFontModifier, font);
    }
    return this;
  }
  alignStyle(value: IndexerAlign, offset?: any): this {
    let alignStyle = new ArkAlignStyle
    if (typeof value === 'number') {
      alignStyle.indexerAlign = value;
      alignStyle.offset = offset;
      modifier(this._modifiers, AlignStyleModifier, alignStyle);
    } else {
      modifier(this._modifiers, AlignStyleModifier, undefined);
    }
    return this;
  }
  onSelect(callback: (index: number) => void): this {
    throw new Error('Method not implemented.');
  }
  onRequestPopupData(callback: (index: number) => string[]): this {
    throw new Error('Method not implemented.');
  }
  onPopupSelect(callback: (index: number) => void): this {
    throw new Error('Method not implemented.');
  }
  selected(index: number): this {
    if (typeof index === 'number') {
      modifier(this._modifiers, AlphabetIndexerSelectedModifier, index);
    } else {
      modifier(this._modifiers, AlphabetIndexerSelectedModifier, undefined);
    }
    return this;
  }
  popupPosition(value: Position): this {
    if (!value || (!!value?.x && typeof value?.x != 'number' && typeof value?.x != 'string') ||
      (!!value?.y && typeof value?.y != 'number' && typeof value?.x != 'string')) {
      modifier(this._modifiers, PopupPositionModifier, undefined);
    }
    else {
      let position = new ArkPosition()
      position.x = value?.x;
      position.y = value?.y;
      modifier(this._modifiers, PopupPositionModifier, position);
    }
    return this;
  }
}
// @ts-ignore
globalThis.AlphabetIndexer.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkAlphabetIndexerComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}

class PopupItemFontModifier extends Modifier<ArkFont> {
  static identity: Symbol = Symbol('popupItemFont');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetPopupItemFont(node);
    }
    else {
      GetUINativeModule().alphabetIndexer.setPopupItemFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
}

class SelectedFontModifier extends Modifier<ArkFont> {
  static identity: Symbol = Symbol('alphaBetIndexerSelectedFont');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetSelectedFont(node);
    }
    else {
      GetUINativeModule().alphabetIndexer.setSelectedFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
}

class PopupFontModifier extends Modifier<ArkFont> {
  static identity: Symbol = Symbol('popupFont');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetPopupFont(node);
    }
    else {
      GetUINativeModule().alphabetIndexer.setPopupFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
}

class AlphabetIndexerFontModifier extends Modifier<ArkFont> {
  static identity: Symbol = Symbol('alphaBetIndexerFont');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetFont(node);
    }
    else {
      GetUINativeModule().alphabetIndexer.setFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
}

class PopupItemBackgroundColorModifier extends Modifier<ArkResourceColor> {
  static identity = Symbol('popupItemBackgroundColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetPopupItemBackgroundColor(node);
    } else {
      GetUINativeModule().alphabetIndexer.setPopupItemBackgroundColor(node, this.value.color);
    }
  }
}

class ColorModifier extends Modifier<ArkResourceColor> {
  static identity = Symbol('alphabetColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetColor(node);
    } else {
      GetUINativeModule().alphabetIndexer.setColor(node, this.value.color);
    }
  }
}

class PopupColorModifier extends Modifier<ArkResourceColor> {
  static identity = Symbol('popupColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetPopupColor(node);
    } else {
      GetUINativeModule().alphabetIndexer.setPopupColor(node, this.value.color);
    }
  }
}

class SelectedColorModifier extends Modifier<ArkResourceColor> {
  static identity = Symbol('selectedColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetSelectedColor(node);
    } else {
      GetUINativeModule().alphabetIndexer.setSelectedColor(node, this.value.color);
    }
  }
}

class PopupBackgroundModifier extends Modifier<ArkResourceColor> {
  static identity = Symbol('popupBackground');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetPopupBackground(node);
    } else {
      GetUINativeModule().alphabetIndexer.setPopupBackground(node, this.value.color);
    }
  }
}

class SelectedBackgroundColorModifier extends Modifier<ArkResourceColor> {
  static identity = Symbol('selectedBackgroundColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetSelectedBackgroundColor(node);
    } else {
      GetUINativeModule().alphabetIndexer.setSelectedBackgroundColor(node, this.value.color);
    }
  }
}

class PopupUnselectedColorModifier extends Modifier<ArkResourceColor> {
  static identity = Symbol('popupUnselectedColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetPopupUnselectedColor(node);
    } else {
      GetUINativeModule().alphabetIndexer.setPopupUnselectedColor(node, this.value.color);
    }
  }
}

class PopupSelectedColorModifier extends Modifier<ArkResourceColor> {
  static identity = Symbol('popupSelectedColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetPopupSelectedColor(node);
    } else {
      GetUINativeModule().alphabetIndexer.setPopupSelectedColor(node, this.value.color);
    }
  }
}

class AlignStyleModifier extends Modifier<ArkAlignStyle> {
  static identity = Symbol('alignStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetAlignStyle(node);
    } else {
      GetUINativeModule().alphabetIndexer.setAlignStyle(node, this.value.indexerAlign, this.value.offset);
    }
  }
}

class UsingPopupModifier extends Modifier<boolean> {
  static identity = Symbol('usingPopup');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetUsingPopup(node);
    } else {
      GetUINativeModule().alphabetIndexer.setUsingPopup(node, this.value);
    }
  }
}

class AlphabetIndexerSelectedModifier extends Modifier<number> {
  static identity = Symbol('alphabetIndexerSelected');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetSelected(node);
    } else {
      GetUINativeModule().alphabetIndexer.setSelected(node, this.value);
    }
  }
}

class ItemSizeModifier extends Modifier<number | string> {
  static identity: Symbol = Symbol('itemSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetItemSize(node);
    }
    else {
      GetUINativeModule().alphabetIndexer.setItemSize(node, this.value);
    }
  }
}

class PopupPositionModifier extends Modifier<ArkPosition> {
  static identity: Symbol = Symbol('popupPosition');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetPopupPosition(node);
    }
    else {
      GetUINativeModule().alphabetIndexer.setPopupPosition(node, this.value.x, this.value.y);
    }
  }
}

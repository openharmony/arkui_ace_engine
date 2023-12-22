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
class ArkAlphabetIndexerComponent extends ArkComponent implements AlphabetIndexerAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  onSelected(callback: (index: number) => void): this {
    throw new Error('Method not implemented.');
  }
  color(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, ColorModifier.identity, ColorModifier, value);
    return this;
  }
  selectedColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, SelectedColorModifier.identity, SelectedColorModifier, value);
    return this;
  }
  popupColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, PopupColorModifier.identity, PopupColorModifier, value);
    return this;
  }
  selectedBackgroundColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, SelectedBackgroundColorModifier.identity, SelectedBackgroundColorModifier, value);
    return this;
  }
  popupBackground(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, PopupBackgroundModifier.identity, PopupBackgroundModifier, value);
    return this;
  }
  popupSelectedColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, PopupSelectedColorModifier.identity, PopupSelectedColorModifier, value);
    return this;
  }
  popupUnselectedColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, PopupUnselectedColorModifier.identity, PopupUnselectedColorModifier, value);
    return this;
  }
  popupItemBackgroundColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, PopupItemBackgroundColorModifier.identity, PopupItemBackgroundColorModifier, value);
    return this;
  }
  usingPopup(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, UsingPopupModifier.identity, UsingPopupModifier, value);
    return this;
  }
  selectedFont(value: Font): this {
    modifierWithKey(this._modifiersWithKeys, SelectedFontModifier.identity, SelectedFontModifier, value);
    return this;
  }
  popupFont(value: Font): this {
    modifierWithKey(this._modifiersWithKeys, PopupFontModifier.identity, PopupFontModifier, value);
    return this;
  }
  popupItemFont(value: Font): this {
    modifierWithKey(this._modifiersWithKeys, PopupItemFontModifier.identity, PopupItemFontModifier, value);
    return this;
  }
  itemSize(value: string | number): this {
    modifierWithKey(this._modifiersWithKeys, ItemSizeModifier.identity, ItemSizeModifier, value);
    return this;
  }
  font(value: Font): this {
    modifierWithKey(this._modifiersWithKeys, AlphabetIndexerFontModifier.identity, AlphabetIndexerFontModifier, value);
    return this;
  }
  alignStyle(value: IndexerAlign, offset?: any): this {
    let alignStyle = new ArkAlignStyle;
    alignStyle.indexerAlign = value;
    alignStyle.offset = offset;
    modifierWithKey(this._modifiersWithKeys, AlignStyleModifier.identity, AlignStyleModifier, alignStyle);
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
    modifierWithKey(this._modifiersWithKeys, AlphabetIndexerSelectedModifier.identity, AlphabetIndexerSelectedModifier, index);
    return this;
  }
  popupPosition(value: Position): this {
    modifierWithKey(this._modifiersWithKeys, PopupPositionModifier.identity, PopupPositionModifier, value);
    return this;
  }
}
// @ts-ignore
globalThis.AlphabetIndexer.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkAlphabetIndexerComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

class PopupItemFontModifier extends ModifierWithKey<Font> {
  constructor(value: Font) {
    super(value);
  }
  static identity: Symbol = Symbol('popupItemFont');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetPopupItemFont(node);
    } else {
      getUINativeModule().alphabetIndexer.setPopupItemFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }

  checkObjectDiff(): boolean {
    let sizeEQ = isBaseOrResourceEqual(this.stageValue.size, this.value.size);
    let weightEQ = this.stageValue.weight === this.value.weight;
    let familyEQ = isBaseOrResourceEqual(this.stageValue.family, this.value.family);
    let styleEQ = this.stageValue.style === this.value.style;
    return !sizeEQ || !weightEQ || !familyEQ || !styleEQ;
  }
}

class SelectedFontModifier extends ModifierWithKey<Font> {
  constructor(value: Font) {
    super(value);
  }
  static identity: Symbol = Symbol('alphaBetIndexerSelectedFont');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetSelectedFont(node);
    } else {
      getUINativeModule().alphabetIndexer.setSelectedFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }

  checkObjectDiff(): boolean {
    let sizeEQ = isBaseOrResourceEqual(this.stageValue.size, this.value.size);
    let weightEQ = this.stageValue.weight === this.value.weight;
    let familyEQ = isBaseOrResourceEqual(this.stageValue.family, this.value.family);
    let styleEQ = this.stageValue.style === this.value.style;
    return !sizeEQ || !weightEQ || !familyEQ || !styleEQ;
  }
}

class PopupFontModifier extends ModifierWithKey<Font> {
  constructor(value: Font) {
    super(value);
  }
  static identity: Symbol = Symbol('popupFont');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetPopupFont(node);
    } else {
      getUINativeModule().alphabetIndexer.setPopupFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }

  checkObjectDiff(): boolean {
    let sizeEQ = isBaseOrResourceEqual(this.stageValue.size, this.value.size);
    let weightEQ = this.stageValue.weight === this.value.weight;
    let familyEQ = isBaseOrResourceEqual(this.stageValue.family, this.value.family);
    let styleEQ = this.stageValue.style === this.value.style;
    return !sizeEQ || !weightEQ || !familyEQ || !styleEQ;
  }
}

class AlphabetIndexerFontModifier extends ModifierWithKey<Font> {
  constructor(value: Font) {
    super(value);
  }
  static identity: Symbol = Symbol('alphaBetIndexerFont');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetFont(node);
    } else {
      getUINativeModule().alphabetIndexer.setFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }

  checkObjectDiff(): boolean {
    let sizeEQ = isBaseOrResourceEqual(this.stageValue.size, this.value.size);
    let weightEQ = this.stageValue.weight === this.value.weight;
    let familyEQ = isBaseOrResourceEqual(this.stageValue.family, this.value.family);
    let styleEQ = this.stageValue.style === this.value.style;
    return !sizeEQ || !weightEQ || !familyEQ || !styleEQ;
  }
}

class PopupItemBackgroundColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('popupItemBackgroundColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetPopupItemBackgroundColor(node);
    } else {
      getUINativeModule().alphabetIndexer.setPopupItemBackgroundColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class ColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('alphabetColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetColor(node);
    } else {
      getUINativeModule().alphabetIndexer.setColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class PopupColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('popupColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetPopupColor(node);
    } else {
      getUINativeModule().alphabetIndexer.setPopupColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SelectedColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('selectedColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetSelectedColor(node);
    } else {
      getUINativeModule().alphabetIndexer.setSelectedColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class PopupBackgroundModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('popupBackground');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetPopupBackground(node);
    } else {
      getUINativeModule().alphabetIndexer.setPopupBackground(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SelectedBackgroundColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('selectedBackgroundColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetSelectedBackgroundColor(node);
    } else {
      getUINativeModule().alphabetIndexer.setSelectedBackgroundColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class PopupUnselectedColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('popupUnselectedColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetPopupUnselectedColor(node);
    } else {
      getUINativeModule().alphabetIndexer.setPopupUnselectedColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class PopupSelectedColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('popupSelectedColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetPopupSelectedColor(node);
    } else {
      getUINativeModule().alphabetIndexer.setPopupSelectedColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class AlignStyleModifier extends ModifierWithKey<ArkAlignStyle> {
  constructor(value: ArkAlignStyle) {
    super(value);
  }
  static identity = Symbol('alignStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetAlignStyle(node);
    } else {
      getUINativeModule().alphabetIndexer.setAlignStyle(node, this.value.indexerAlign, this.value.offset);
    }
  }

  checkObjectDiff(): boolean {
    let indexerAlignEQ = isBaseOrResourceEqual(this.stageValue.indexerAlign, this.value.indexerAlign);
    let offsetEQ = isBaseOrResourceEqual(this.stageValue.offset, this.value.offset);
    return !indexerAlignEQ || !offsetEQ;
  }
}

class UsingPopupModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity = Symbol('usingPopup');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetUsingPopup(node);
    } else {
      getUINativeModule().alphabetIndexer.setUsingPopup(node, this.value);
    }
  }
}

class AlphabetIndexerSelectedModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity = Symbol('alphabetIndexerSelected');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetSelected(node);
    } else {
      getUINativeModule().alphabetIndexer.setSelected(node, this.value);
    }
  }
}

class ItemSizeModifier extends ModifierWithKey<number | string> {
  constructor(value: number | string) {
    super(value);
  }
  static identity: Symbol = Symbol('itemSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetItemSize(node);
    } else {
      getUINativeModule().alphabetIndexer.setItemSize(node, this.value);
    }
  }
}

class PopupPositionModifier extends ModifierWithKey<Position> {
  constructor(value: Position) {
    super(value);
  }
  static identity: Symbol = Symbol('popupPosition');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetPopupPosition(node);
    } else {
      getUINativeModule().alphabetIndexer.setPopupPosition(node, this.value.x, this.value.y);
    }
  }

  checkObjectDiff(): boolean {
    let xEQ = isBaseOrResourceEqual(this.stageValue.x, this.value.x);
    let yEQ = isBaseOrResourceEqual(this.stageValue.y, this.value.y);
    return !xEQ || !yEQ;
  }
}

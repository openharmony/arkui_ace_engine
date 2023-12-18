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
    if (typeof value === 'boolean') {
      modifier(this._modifiers, UsingPopupModifier, value);
    } else {
      modifier(this._modifiers, UsingPopupModifier, undefined);
    }
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
    if (typeof value !== 'number' && typeof value !== 'string') {
      modifier(this._modifiers, ItemSizeModifier, undefined);
    }
    else {
      modifier(this._modifiers, ItemSizeModifier, value);
    }
    return this;
  }
  font(value: Font): this {
    modifierWithKey(this._modifiersWithKeys, AlphabetIndexerFontModifier.identity, AlphabetIndexerFontModifier, value);
    return this;
  }
  alignStyle(value: IndexerAlign, offset?: any): this {
    let alignStyle = new ArkAlignStyle
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
    if (typeof index === 'number') {
      modifier(this._modifiers, AlphabetIndexerSelectedModifier, index);
    } else {
      modifier(this._modifiers, AlphabetIndexerSelectedModifier, undefined);
    }
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkAlphabetIndexerComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
}

class PopupItemFontModifier extends ModifierWithKey<Font> {
  constructor(value: Font) {
    super(value);
  }
  static identity: Symbol = Symbol('popupItemFont');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetPopupItemFont(node);
    } else {
      GetUINativeModule().alphabetIndexer.setPopupItemFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
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
      GetUINativeModule().alphabetIndexer.resetSelectedFont(node);
    }
    else {
      GetUINativeModule().alphabetIndexer.setSelectedFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
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
      GetUINativeModule().alphabetIndexer.resetPopupFont(node);
    }
    else {
      GetUINativeModule().alphabetIndexer.setPopupFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
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
      GetUINativeModule().alphabetIndexer.resetFont(node);
    }
    else {
      GetUINativeModule().alphabetIndexer.setFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
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
  static identity: Symbol = Symbol("popupItemBackgroundColor");
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetPopupItemBackgroundColor(node);
    } else {
      GetUINativeModule().alphabetIndexer.setPopupItemBackgroundColor(node, this.value);
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

class ColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol("alphabetColor");
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetColor(node);
    } else {
      GetUINativeModule().alphabetIndexer.setColor(node, this.value);
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

class PopupColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol("popupColor");
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetPopupColor(node);
    } else {
      GetUINativeModule().alphabetIndexer.setPopupColor(node, this.value);
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

class SelectedColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol("selectedColor");
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetSelectedColor(node);
    } else {
      GetUINativeModule().alphabetIndexer.setSelectedColor(node, this.value);
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

class PopupBackgroundModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol("popupBackground");
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetPopupBackground(node);
    } else {
      GetUINativeModule().alphabetIndexer.setPopupBackground(node, this.value);
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

class SelectedBackgroundColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol("selectedBackgroundColor");
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetSelectedBackgroundColor(node);
    } else {
      GetUINativeModule().alphabetIndexer.setSelectedBackgroundColor(node, this.value);
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

class PopupUnselectedColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol("popupUnselectedColor");
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetPopupUnselectedColor(node);
    } else {
      GetUINativeModule().alphabetIndexer.setPopupUnselectedColor(node, this.value);
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

class PopupSelectedColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol("popupSelectedColor");
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetPopupSelectedColor(node);
    } else {
      GetUINativeModule().alphabetIndexer.setPopupSelectedColor(node, this.value);
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

class AlignStyleModifier extends ModifierWithKey<ArkAlignStyle> {
  constructor(value: ArkAlignStyle) {
    super(value);
  }
  static identity = Symbol('alignStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetAlignStyle(node);
    } else {
      GetUINativeModule().alphabetIndexer.setAlignStyle(node, this.value.indexerAlign, this.value.offset);
    }
  }

  checkObjectDiff(): boolean {
    let indexerAlignEQ = isBaseOrResourceEqual(this.stageValue.indexerAlign, this.value.indexerAlign);
    let offsetEQ = isBaseOrResourceEqual(this.stageValue.offset, this.value.offset);
    return !indexerAlignEQ || !offsetEQ;
  }
}

class UsingPopupModifier extends Modifier<boolean> {
  constructor(value: boolean) {
    super(value);
  }
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
  constructor(value: number) {
    super(value);
  }
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
  constructor(value: number | string) {
    super(value);
  }
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

class PopupPositionModifier extends ModifierWithKey<Position> {
  constructor(value: Position) {
    super(value);
  }
  static identity: Symbol = Symbol('popupPosition');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetPopupPosition(node);
    } else {
      GetUINativeModule().alphabetIndexer.setPopupPosition(node, this.value.x, this.value.y);
    }
  }

  checkObjectDiff(): boolean {
    let xEQ = isBaseOrResourceEqual(this.stageValue.x, this.value.x);
    let yEQ = isBaseOrResourceEqual(this.stageValue.y, this.value.y);
    return !xEQ || !yEQ;
  }
}

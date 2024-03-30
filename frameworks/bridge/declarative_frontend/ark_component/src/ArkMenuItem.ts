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
class MenuItemSelectedModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('menuItemSelected');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      getUINativeModule().menuitem.resetMenuItemSelected(node);
    } else {
      getUINativeModule().menuitem.setMenuItemSelected(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class LabelFontColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('labelfontColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().menuitem.resetLabelFontColor(node);
    } else {
      getUINativeModule().menuitem.setLabelFontColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class ContentFontColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('contentfontColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().menuitem.resetContentFontColor(node);
    } else {
      getUINativeModule().menuitem.setContentFontColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class LabelFontModifier extends ModifierWithKey<Font> {
  constructor(value: Font) {
    super(value);
  }
  static identity: Symbol = Symbol('labelFont');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset || !this.value) {
      getUINativeModule().menuitem.resetLabelFont(node);
    } else {
      getUINativeModule().menuitem.setLabelFont(node, (this.value as Font).size,
        (this.value as Font).weight, (this.value as Font).family,
        (this.value as Font).style);
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

class ContentFontModifier extends ModifierWithKey<Font> {
  constructor(value: Font) {
    super(value);
  }
  static identity: Symbol = Symbol('contentFont');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset || !this.value) {
      getUINativeModule().menuitem.resetContentFont(node);
    } else {
      getUINativeModule().menuitem.setContentFont(node, (this.value as Font).size,
        (this.value as Font).weight, (this.value as Font).family,
        (this.value as Font).style);
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

class MenuItemSelectIconModifier extends ModifierWithKey<boolean | ResourceStr> {
  constructor(value: boolean | ResourceStr) {
    super(value);
  }
  static identity: Symbol = Symbol('selectIcon');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset || !this.value) {
      getUINativeModule().menuitem.resetSelectIcon(node);
    } else {
      getUINativeModule().menuitem.setSelectIcon(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class ArkMenuItemComponent extends ArkComponent implements MenuItemAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  selected(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, MenuItemSelectedModifier.identity, MenuItemSelectedModifier, value);
    return this;
  }
  selectIcon(value: boolean | ResourceStr): this {
    modifierWithKey(this._modifiersWithKeys, MenuItemSelectIconModifier.identity, MenuItemSelectIconModifier, value);
    return this;
  }
  onChange(callback: (selected: boolean) => void): this {
    throw new Error('Method not implemented.');
  }
  contentFont(value: Font): this {
    modifierWithKey(this._modifiersWithKeys, ContentFontModifier.identity, ContentFontModifier, value);
    return this;
  }
  contentFontColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, ContentFontColorModifier.identity, ContentFontColorModifier, value);
    return this;
  }
  labelFont(value: Font): this {
    modifierWithKey(this._modifiersWithKeys, LabelFontModifier.identity, LabelFontModifier, value);
    return this;
  }
  labelFontColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, LabelFontColorModifier.identity, LabelFontColorModifier, value);
    return this;
  }
}
// @ts-ignore
globalThis.MenuItem.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkMenuItemComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.MenuItemModifier(nativePtr, classType);
  });
};

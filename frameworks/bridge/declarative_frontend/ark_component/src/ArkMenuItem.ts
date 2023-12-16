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
      GetUINativeModule().menuitem.resetMenuItemSelected(node);
    } else {
      GetUINativeModule().menuitem.setMenuItemSelected(node, this.value);
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
  static identity: Symbol = Symbol("labelfontColor");
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().menuitem.resetLabelFontColor(node);
    } else {
      GetUINativeModule().menuitem.setLabelFontColor(node, this.value);
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

class ContentFontColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol("contentfontColor");
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().menuitem.resetContentFontColor(node);
    } else {
      GetUINativeModule().menuitem.setContentFontColor(node, this.value);
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

class LabelFontModifier extends ModifierWithKey<Font> {
  constructor(value: Font) {
    super(value);
  }
  static identity: Symbol = Symbol("labelFont");
  applyPeer(node: KNode, reset: boolean): void {
    if (reset || !this.value) {
      GetUINativeModule().menuitem.resetLabelFont(node);
    }
    else {
      GetUINativeModule().menuitem.setLabelFont(node, (this.value as Font).size,
        (this.value as Font).weight, (this.value as Font).family,
        (this.value as Font).style);
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !((this.stageValue as Font).size === (this.value as Font).size &&
        (this.stageValue as Font).weight === (this.value as Font).weight &&
        (this.stageValue as Font).family === (this.value as Font).family &&
        (this.stageValue as Font).style === (this.value as Font).style);
    } else {
      return true;
    }
  }
}

class ContentFontModifier extends ModifierWithKey<Font> {
  constructor(value: Font) {
    super(value);
  }
  static identity: Symbol = Symbol("contentFont");
  applyPeer(node: KNode, reset: boolean): void {
    if (reset || !this.value) {
      GetUINativeModule().menuitem.resetContentFont(node);
    }
    else {
      GetUINativeModule().menuitem.setContentFont(node, (this.value as Font).size,
        (this.value as Font).weight, (this.value as Font).family,
        (this.value as Font).style);
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !((this.stageValue as Font).size === (this.value as Font).size &&
        (this.stageValue as Font).weight === (this.value as Font).weight &&
        (this.stageValue as Font).family === (this.value as Font).family &&
        (this.stageValue as Font).style === (this.value as Font).style);
    } else {
      return true;
    }
  }
}

class ArkMenuItemComponent extends ArkComponent implements MenuItemAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  selected(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, MenuItemSelectedModifier.identity, MenuItemSelectedModifier, value);
    return this;
  }
  selectIcon(value: any): MenuItemAttribute {
    throw new Error('Method not implemented.');
  }
  onChange(callback: (selected: boolean) => void): MenuItemAttribute {
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
globalThis.MenuItem.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkMenuItemComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
}

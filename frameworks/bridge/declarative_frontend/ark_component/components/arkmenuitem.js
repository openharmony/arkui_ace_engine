/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
class MenuItemSelectedModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().menuitem.resetMenuItemSelected(node);
    }
    else {
      getUINativeModule().menuitem.setMenuItemSelected(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
MenuItemSelectedModifier.identity = Symbol('menuItemSelected');
class LabelFontColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().menuitem.resetLabelFontColor(node);
    }
    else {
      getUINativeModule().menuitem.setLabelFontColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
LabelFontColorModifier.identity = Symbol('labelfontColor');
class ContentFontColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().menuitem.resetContentFontColor(node);
    }
    else {
      getUINativeModule().menuitem.setContentFontColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
ContentFontColorModifier.identity = Symbol('contentfontColor');
class LabelFontModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset || !this.value) {
      getUINativeModule().menuitem.resetLabelFont(node);
    }
    else {
      getUINativeModule().menuitem.setLabelFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
  checkObjectDiff() {
    let sizeEQ = isBaseOrResourceEqual(this.stageValue.size, this.value.size);
    let weightEQ = this.stageValue.weight === this.value.weight;
    let familyEQ = isBaseOrResourceEqual(this.stageValue.family, this.value.family);
    let styleEQ = this.stageValue.style === this.value.style;
    return !sizeEQ || !weightEQ || !familyEQ || !styleEQ;
  }
}
LabelFontModifier.identity = Symbol('labelFont');
class ContentFontModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset || !this.value) {
      getUINativeModule().menuitem.resetContentFont(node);
    }
    else {
      getUINativeModule().menuitem.setContentFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
  checkObjectDiff() {
    let sizeEQ = isBaseOrResourceEqual(this.stageValue.size, this.value.size);
    let weightEQ = this.stageValue.weight === this.value.weight;
    let familyEQ = isBaseOrResourceEqual(this.stageValue.family, this.value.family);
    let styleEQ = this.stageValue.style === this.value.style;
    return !sizeEQ || !weightEQ || !familyEQ || !styleEQ;
  }
}
ContentFontModifier.identity = Symbol('contentFont');
class MenuItemSelectIconModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset || !this.value) {
      getUINativeModule().menuitem.resetSelectIcon(node);
    } else {
      getUINativeModule().menuitem.setSelectIcon(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
MenuItemSelectIconModifier.identity = Symbol('selectIcon');
class MenuItemOnChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().menuitem.resetOnChange(node);
    } else {
      getUINativeModule().menuitem.setOnChange(node, this.value);
    }
  }
}
MenuItemOnChangeModifier.identity = Symbol('menuItemOnChange');
class ArkMenuItemComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  selected(value) {
    modifierWithKey(this._modifiersWithKeys, MenuItemSelectedModifier.identity, MenuItemSelectedModifier, value);
    return this;
  }
  selectIcon(value) {
    modifierWithKey(this._modifiersWithKeys, MenuItemSelectIconModifier.identity, MenuItemSelectIconModifier, value);
    return this;
  }
  onChange(callback) {
    modifierWithKey(this._modifiersWithKeys, MenuItemOnChangeModifier.identity, MenuItemOnChangeModifier, callback);
    return this;
  }
  contentFont(value) {
    modifierWithKey(this._modifiersWithKeys, ContentFontModifier.identity, ContentFontModifier, value);
    return this;
  }
  contentFontColor(value) {
    modifierWithKey(this._modifiersWithKeys, ContentFontColorModifier.identity, ContentFontColorModifier, value);
    return this;
  }
  labelFont(value) {
    modifierWithKey(this._modifiersWithKeys, LabelFontModifier.identity, LabelFontModifier, value);
    return this;
  }
  labelFontColor(value) {
    modifierWithKey(this._modifiersWithKeys, LabelFontColorModifier.identity, LabelFontColorModifier, value);
    return this;
  }
}

class JSMenuItem extends JSContainerBase {
  static create(params) {
    getUINativeModule().menuitem.create(params);
  }
  static selected(value, callback) {
    getUINativeModule().menuitem.setMenuItemSelected(true, value, callback);
  }
  static selectIcon(value) {
    getUINativeModule().menuitem.setSelectIcon(true, value);
  }
  static contentFont(value) {
    getUINativeModule().menuitem.setContentFont(true, value);
  }
  static contentFontColor(value) {
    getUINativeModule().menuitem.setContentFontColor(true, value);
  }
  static labelFont(value) {
    getUINativeModule().menuitem.setLabelFont(true, value);
  }
  static labelFontColor(value) {
    getUINativeModule().menuitem.setLabelFontColor(true, value);
  }
  static onChange(callback) {
    getUINativeModule().menuitem.setOnChange(true, callback);
  }
  static attributeModifier(modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkMenuItemComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.MenuItemModifier(nativePtr, classType);
    });
  }
  static onClick(value) {
    __Common__.onClick(value);
  }
  static onKeyEvent(value) {
    __Common__.onKeyEvent(value);
  }
  static onTouch(value) {
    __Common__.onTouch(value);
  }
  static onHover(value) {
    __Common__.onHover(value);
  }
  static onAppear(value) {
    __Common__.onAppear(value);
  }
  static onDisAppear(value) {
    __Common__.onDisAppear(value);
  }
}

function createComponent(nativePtr, classType) {
  return new ArkMenuItemComponent(nativePtr, classType);
}

function exportComponent() {
  globalThis.ArkMenuItemComponent = ArkMenuItemComponent;
}

function exportView() {
  globalThis.MenuItem = JSMenuItem;
}

export default { ArkMenuItemComponent, createComponent, exportComponent, exportView };
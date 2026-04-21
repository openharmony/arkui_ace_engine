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
class MenuFontColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().menu.resetMenuFontColor(node);
    }
    else {
      getUINativeModule().menu.setMenuFontColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
MenuFontColorModifier.identity = Symbol('fontColor');
class MenuWidthModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().menu.resetWidth(node);
    } else {
      getUINativeModule().menu.setWidth(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
MenuWidthModifier.identity = Symbol('menuWidth');
class MenuFontSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().menu.resetFontSize(node);
    } else {
      getUINativeModule().menu.setFontSize(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
MenuFontSizeModifier.identity = Symbol('menuFontSize');
class MenuFontModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset || !this.value) {
      getUINativeModule().menu.resetFont(node);
    }
    else {
      getUINativeModule().menu.setFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
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
MenuFontModifier.identity = Symbol('font');
class RadiusModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().menu.resetRadius(node);
    }
    else {
      if (isNumber(this.value) || isString(this.value) || isResource(this.value)) {
        getUINativeModule().menu.setRadius(node, this.value, this.value, this.value, this.value, false);
      }
      else {
        getUINativeModule().menu.setRadius(node, this.value.topLeft, this.value.topRight, this.value.bottomLeft, this.value.bottomRight, true);
      }
    }
  }
  checkObjectDiff() {
    if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !(this.stageValue.topLeft === this.value.topLeft &&
        this.stageValue.topRight === this.value.topRight &&
        this.stageValue.bottomLeft === this.value.bottomLeft &&
        this.stageValue.bottomRight === this.value.bottomRight);
    }
    else {
      return true;
    }
  }
}
RadiusModifier.identity = Symbol('radius');
class MenuItemDividerModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset || !this.value) {
      getUINativeModule().menu.resetMenuItemDivider(node);
    } else {
      getUINativeModule().menu.setMenuItemDivider(node, this.value.strokeWidth,
        this.value.color, this.value.startMargin, this.value.endMargin, this.value.mode);
    }
  }
  checkObjectDiff() {
    if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !(this.stageValue.strokeWidth === this.value.strokeWidth &&
        this.stageValue.color === this.value.color &&
        this.stageValue.startMargin === this.value.startMargin &&
        this.stageValue.endMargin === this.value.endMargin &&
        this.stageValue.mode === this.value.mode);
    } else {
      return true;
    }
  }
}
MenuItemDividerModifier.identity = Symbol('menuItemDivider');
class MenuItemGroupDividerModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset || !this.value) {
      getUINativeModule().menu.resetMenuItemGroupDivider(node);
    } else {
      getUINativeModule().menu.setMenuItemGroupDivider(node, this.value.strokeWidth, this.value.color,
        this.value.startMargin, this.value.endMargin, this.value.mode);
    }
  }
  checkObjectDiff() {
    if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !(this.stageValue.strokeWidth === this.value.strokeWidth &&
        this.stageValue.color === this.value.color &&
        this.stageValue.startMargin === this.value.startMargin &&
        this.stageValue.endMargin === this.value.endMargin &&
        this.stageValue.mode === this.value.mode);
    } else {
      return true;
    }
  }
}
MenuItemGroupDividerModifier.identity = Symbol('menuItemGroupDivider');
class SubMenuExpandingModeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().menu.resetSubMenuExpandingMode(node);
    } else {
      getUINativeModule().menu.setSubMenuExpandingMode(node, this.value);
    }
  }
}
SubMenuExpandingModeModifier.identity = Symbol('subMenuExpandingMode');
class SubMenuExpandSymbolModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset || !this.value) {
      getUINativeModule().menu.resetSubMenuExpandSymbol(node);
    } else {
      getUINativeModule().menu.setSubMenuExpandSymbol(node, this.value);
    }
  }
}
SubMenuExpandSymbolModifier.identity = Symbol('subMenuExpandSymbol');
class MenuInitializeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().menu.resetMenuInitialize(node);
    } else {
      getUINativeModule().menu.setMenuInitialize(node,
        this.value?.scroller, this.value?.sections, this.value?.layoutMode, this.value?.footerContent, this.value?.footer);
    }
  }
}
MenuInitializeModifier.identity = Symbol('menuInitialize');
class ArkMenuComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  width(value) {
    modifierWithKey(this._modifiersWithKeys, MenuWidthModifier.identity, MenuWidthModifier, value);
    return this;
  }
  fontSize(value) {
    modifierWithKey(this._modifiersWithKeys, MenuFontSizeModifier.identity, MenuFontSizeModifier, value);
    return this;
  }
  font(value) {
    modifierWithKey(this._modifiersWithKeys, MenuFontModifier.identity, MenuFontModifier, value);
    return this;
  }
  fontColor(value) {
    modifierWithKey(this._modifiersWithKeys, MenuFontColorModifier.identity, MenuFontColorModifier, value);
    return this;
  }
  radius(value) {
    modifierWithKey(this._modifiersWithKeys, RadiusModifier.identity, RadiusModifier, value);
    return this;
  }
  menuItemDivider(value) {
    modifierWithKey(this._modifiersWithKeys, MenuItemDividerModifier.identity, MenuItemDividerModifier, value);
    return this;
  }
  menuItemGroupDivider(value) {
    modifierWithKey(this._modifiersWithKeys, MenuItemGroupDividerModifier.identity, MenuItemGroupDividerModifier, value);
    return this;
  }
  subMenuExpandingMode(value) {
    modifierWithKey(this._modifiersWithKeys, SubMenuExpandingModeModifier.identity, SubMenuExpandingModeModifier, value);
    return this;
  }
  subMenuExpandSymbol(value) {
    modifierWithKey(this._modifiersWithKeys, SubMenuExpandSymbolModifier.identity, SubMenuExpandSymbolModifier, value);
    return this;
  }
}

class JSMenu extends JSViewAbstract {
  static create() {
    getUINativeModule().menu.create();
  }
  static width(value) {
    getUINativeModule().menu.setWidth(true, value);
  }
  static fontSize(value) {
    getUINativeModule().menu.setFontSize(true, value);
  }
  static font(value) {
    getUINativeModule().menu.setFont(true, value);
  }
  static fontColor(value) {
    getUINativeModule().menu.setMenuFontColor(true, value);
  }
  static radius(value) {
    getUINativeModule().menu.setRadius(true, value);
  }
  static menuItemDivider(value) {
    getUINativeModule().menu.setMenuItemDivider(true, value);
  }
  static menuItemGroupDivider(value) {
    getUINativeModule().menu.setMenuItemGroupDivider(true, value);
  }
  static subMenuExpandingMode(value) {
    getUINativeModule().menu.setSubMenuExpandingMode(true, value);
  }
  static subMenuExpandSymbol(value) {
    getUINativeModule().menu.setSubMenuExpandSymbol(true, value);
  }
  static attributeModifier(modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkMenuComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.MenuModifier(nativePtr, classType);
    });
  }
  static onAppear(value) {
    __Common__.onAppear(value);
  }
  static onDisAppear(value) {
    __Common__.onDisAppear(value);
  }
  static onAttach(value) {
    __Common__.onAttach(value);
  }
  static onDetach(value) {
    __Common__.onDetach(value);
  }
  static onTouch(value) {
    __Common__.onTouch(value);
  }
}

function createComponent(nativePtr, classType) {
  return new ArkMenuComponent(nativePtr, classType);
}

function exportComponent() {
  globalThis.ArkMenuComponent = ArkMenuComponent;
}

function exportView() {
  globalThis.Menu = JSMenu;
}
function loadComponent() {}
export default { ArkMenuComponent, createComponent, exportComponent, exportView, loadComponent };
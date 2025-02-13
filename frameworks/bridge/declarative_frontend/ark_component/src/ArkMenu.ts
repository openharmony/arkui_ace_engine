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
class MenuFontColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('fontColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().menu.resetMenuFontColor(node);
    } else {
      getUINativeModule().menu.setMenuFontColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class MenuFontModifier extends ModifierWithKey<Font> {
  constructor(value: Font) {
    super(value);
  }
  static identity: Symbol = Symbol('font');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset || !this.value) {
      getUINativeModule().menu.resetFont(node);
    } else {
      getUINativeModule().menu.setFont(node,
        this.value.size,
        this.value.weight,
        this.value.family,
        this.value.style);
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

class RadiusModifier extends ModifierWithKey<Dimension | BorderRadiuses> {
  constructor(value: Dimension | BorderRadiuses) {
    super(value);
  }
  static identity: Symbol = Symbol('radius');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().menu.resetRadius(node);
    } else {
      if (isNumber(this.value) || isString(this.value) || isResource(this.value)) {
        getUINativeModule().menu.setRadius(node, this.value, this.value, this.value, this.value, false);
      } else {
        getUINativeModule().menu.setRadius(node,
          (this.value as BorderRadiuses).topLeft,
          (this.value as BorderRadiuses).topRight,
          (this.value as BorderRadiuses).bottomLeft,
          (this.value as BorderRadiuses).bottomRight,
          true);
      }
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !((this.stageValue as BorderRadiuses).topLeft === (this.value as BorderRadiuses).topLeft &&
        (this.stageValue as BorderRadiuses).topRight === (this.value as BorderRadiuses).topRight &&
        (this.stageValue as BorderRadiuses).bottomLeft === (this.value as BorderRadiuses).bottomLeft &&
        (this.stageValue as BorderRadiuses).bottomRight === (this.value as BorderRadiuses).bottomRight);
    } else {
      return true;
    }
  }
}

class MenuWidthModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('menuWidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().menu.resetWidth(node);
    } else {
      getUINativeModule().menu.setWidth(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class MenuFontSizeModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('menuFontSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().menu.resetFontSize(node);
    } else {
      getUINativeModule().menu.setFontSize(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class MenuItemDividerModifier extends ModifierWithKey<DividerStyleOptions> {
  constructor(value: DividerStyleOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('menuItemDivider');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset || !this.value) {
      getUINativeModule().menu.resetMenuItemDivider(node);
    } else {
      getUINativeModule().menu.setMenuItemDivider(node, this.value.strokeWidth, this.value.color, this.value.startMargin, this.value.endMargin);
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !((this.stageValue as DividerStyleOptions).strokeWidth === (this.value as DividerStyleOptions).strokeWidth &&
        (this.stageValue as DividerStyleOptions).color === (this.value as DividerStyleOptions).color &&
        (this.stageValue as DividerStyleOptions).startMargin === (this.value as DividerStyleOptions).startMargin &&
        (this.stageValue as DividerStyleOptions).endMargin === (this.value as DividerStyleOptions).endMargin);
    } else {
      return true;
    }
  }
}

class MenuItemGroupDividerModifier extends ModifierWithKey<DividerStyleOptions> {
  constructor(value: DividerStyleOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('menuItemGroupDivider');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset || !this.value) {
      getUINativeModule().menu.resetMenuItemGroupDivider(node);
    } else {
      getUINativeModule().menu.setMenuItemGroupDivider(node, this.value.strokeWidth, this.value.color, this.value.startMargin, this.value.endMargin);
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !((this.stageValue as DividerStyleOptions).strokeWidth === (this.value as DividerStyleOptions).strokeWidth &&
        (this.stageValue as DividerStyleOptions).color === (this.value as DividerStyleOptions).color &&
        (this.stageValue as DividerStyleOptions).startMargin === (this.value as DividerStyleOptions).startMargin &&
        (this.stageValue as DividerStyleOptions).endMargin === (this.value as DividerStyleOptions).endMargin);
    } else {
      return true;
    }
  }
}

class SubMenuExpandingModeModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('subMenuExpandingMode');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().menu.resetSubMenuExpandingMode(node);
    } else {
      getUINativeModule().menu.setSubMenuExpandingMode(node, this.value);
    }
  }
}

class ArkMenuComponent extends ArkComponent implements MenuAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  width(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, MenuWidthModifier.identity, MenuWidthModifier, value);
    return this;
  }
  fontSize(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, MenuFontSizeModifier.identity, MenuFontSizeModifier, value);
    return this;
  }
  font(value: Font): this {
    modifierWithKey(this._modifiersWithKeys, MenuFontModifier.identity, MenuFontModifier, value);
    return this;
  }
  fontColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, MenuFontColorModifier.identity, MenuFontColorModifier, value);
    return this;
  }
  radius(value: any): this {
    modifierWithKey(this._modifiersWithKeys, RadiusModifier.identity, RadiusModifier, value);
    return this;
  }
  menuItemDivider(value: DividerStyleOptions): this {
    modifierWithKey(this._modifiersWithKeys, MenuItemDividerModifier.identity, MenuItemDividerModifier, value);
    return this;
  }
  menuItemGroupDivider(value: DividerStyleOptions): this {
    modifierWithKey(this._modifiersWithKeys, MenuItemGroupDividerModifier.identity, MenuItemGroupDividerModifier, value);
    return this;
  }
  subMenuExpandingMode(value: SubMenuExpandingMode): this {
    modifierWithKey(this._modifiersWithKeys, SubMenuExpandingModeModifier.identity, SubMenuExpandingModeModifier, value);
    return this;
  }
}

// @ts-ignore
globalThis.Menu.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkMenuComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.MenuModifier(nativePtr, classType);
  });
};

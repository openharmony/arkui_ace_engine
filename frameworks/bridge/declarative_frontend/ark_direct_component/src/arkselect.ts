/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

/// <reference path='./../../ark_component/src/import.ts' />
type ComponentObj = { component: any }

function loadComponent(): ComponentObj | undefined {
  if (loadComponent.componentObj === undefined && globalThis.__ArkComponent__ !== undefined) {
    class ArkSelectComponent extends ArkComponent {
      constructor(nativePtr: any, classType: any) {
        super(nativePtr, classType);
        this._menuItemMap = new Map();
      }
      allowChildCount(): number {
        return 0;
      }
      initialize(value: any): this {
        if (!value.length) {
          return this;
        }
        if (!isUndefined(value[0]) && !isNull(value[0]) && isObject(value[0])) {
          modifierWithKey(this._modifiersWithKeys, SelectOptionsModifier.identity, SelectOptionsModifier, value[0]);
        } else {
          modifierWithKey(this._modifiersWithKeys, SelectOptionsModifier.identity, SelectOptionsModifier, undefined);
        }
        return this;
      }
      optionWidth(value: any): this {
        modifierWithKey(this._modifiersWithKeys, SelectOptionWidthModifier.identity, SelectOptionWidthModifier, value);
        return this;
      }
      optionHeight(value: any): this {
        modifierWithKey(this._modifiersWithKeys, SelectOptionHeightModifier.identity, SelectOptionHeightModifier, value);
        return this;
      }
      width(value: any): this {
        modifierWithKey(this._modifiersWithKeys, SelectWidthModifier.identity, SelectWidthModifier, value);
        return this;
      }
      height(value: any): this {
        modifierWithKey(this._modifiersWithKeys, SelectHeightModifier.identity, SelectHeightModifier, value);
        return this;
      }
      size(value: any): this {
        modifierWithKey(this._modifiersWithKeys, SelectSizeModifier.identity, SelectSizeModifier, value);
        return this;
      }
      selected(value: any): this {
        modifierWithKey(this._modifiersWithKeys, SelectedModifier.identity, SelectedModifier, value);
        return this;
      }
      value(value: any): this {
        modifierWithKey(this._modifiersWithKeys, ValueModifier.identity, ValueModifier, value);
        return this;
      }
      font(value: any): this {
        modifierWithKey(this._modifiersWithKeys, FontModifier.identity, FontModifier, value);
        return this;
      }
      fontColor(value: any): this {
        modifierWithKey(this._modifiersWithKeys, SelectFontColorModifier.identity, SelectFontColorModifier, value);
        return this;
      }
      selectedOptionBgColor(value: any): this {
        modifierWithKey(this._modifiersWithKeys, SelectedOptionBgColorModifier.identity, SelectedOptionBgColorModifier, value);
        return this;
      }
      selectedOptionFont(value: any): this {
        modifierWithKey(this._modifiersWithKeys, SelectedOptionFontModifier.identity, SelectedOptionFontModifier, value);
        return this;
      }
      selectedOptionFontColor(value: any): this {
        modifierWithKey(this._modifiersWithKeys, SelectedOptionFontColorModifier.identity, SelectedOptionFontColorModifier, value);
        return this;
      }
      optionBgColor(value: any): this {
        modifierWithKey(this._modifiersWithKeys, OptionBgColorModifier.identity, OptionBgColorModifier, value);
        return this;
      }
      optionFont(value: any): this {
        modifierWithKey(this._modifiersWithKeys, OptionFontModifier.identity, OptionFontModifier, value);
        return this;
      }
      optionFontColor(value: any): this {
        modifierWithKey(this._modifiersWithKeys, OptionFontColorModifier.identity, OptionFontColorModifier, value);
        return this;
      }
      onSelect(callback: any): this {
        modifierWithKey(this._modifiersWithKeys, SelectOnSelectModifier.identity, SelectOnSelectModifier, callback);
        return this;
      }
      space(value: any): this {
        modifierWithKey(this._modifiersWithKeys, SpaceModifier.identity, SpaceModifier, value);
        return this;
      }
      arrowPosition(value: any): this {
        modifierWithKey(this._modifiersWithKeys, ArrowPositionModifier.identity, ArrowPositionModifier, value);
        return this;
      }
      menuAlign(alignType: any, offset: any): this {
        let menuAlign = new ArkMenuAlignType(alignType, offset);
        modifierWithKey(this._modifiersWithKeys, MenuAlignModifier.identity, MenuAlignModifier, menuAlign);
        return this;
      }
      menuBackgroundColor(value: any): this {
        modifierWithKey(
          this._modifiersWithKeys, MenuBackgroundColorModifier.identity, MenuBackgroundColorModifier, value);
        return this;
      }
      menuBackgroundBlurStyle(value: any): this {
        modifierWithKey(
          this._modifiersWithKeys, MenuBackgroundBlurStyleModifier.identity, MenuBackgroundBlurStyleModifier, value);
        return this;
      }
      controlSize(controlSize: any): this {
        modifierWithKey(this._modifiersWithKeys, ControlSizeModifier.identity, ControlSizeModifier, controlSize);
        return this;
      }
      menuItemContentModifier(modifier: any): this {
        if (modifier === undefined || modifier === null) {
          getUINativeModule().select.setContentModifierBuilder(this.nativePtr, false);
          return;
        }
        this.applyContent = modifier.applyContent();
        if (this.builder !== this.applyContent) {
          this._menuItemMap.clear();
          this.builder = this.applyContent;
        }
        this.modifier = modifier;
        getUINativeModule().select.setContentModifierBuilder(this.nativePtr, this);
      }
      makeContentModifierNode(context: any, menuItemConfiguration: any): any {
        menuItemConfiguration.contentModifier = this.modifier;
        const index = menuItemConfiguration.index;
        const xNode = globalThis.requireNapi('arkui.node');
        if (!this._menuItemMap.has(index)) {
          this._menuItemMap.set(index, new xNode.BuilderNode(context));
          this._menuItemMap.get(index).build(this.builder, menuItemConfiguration);
        } else {
          this._menuItemMap.get(index).update(menuItemConfiguration);
        }
        return this._menuItemMap.get(index).getFrameNode();
      }
      divider(value: any): this {
        modifierWithKey(this._modifiersWithKeys, SelectDividerModifier.identity, SelectDividerModifier, value);
        return this;
      }
      dividerStyle(value: any): this {
        modifierWithKey(this._modifiersWithKeys, SelectDividerStyleModifier.identity, SelectDividerStyleModifier, value);
        return this;
      }
      direction(value: any): this {
        modifierWithKey(this._modifiersWithKeys, SelectDirectionModifier.identity, SelectDirectionModifier, value);
        return this;
      }
      menuOutline(outline: any): this {
        modifierWithKey(
          this._modifiersWithKeys, MenuOutlineModifier.identity, MenuOutlineModifier, outline);
        return this;
      }
      avoidance(mode: any): this {
        modifierWithKey(this._modifiersWithKeys, AvoidanceModifier.identity, AvoidanceModifier, mode);
        return this;
      }
      backgroundColor(value: any): this {
        modifierWithKey(this._modifiersWithKeys, SelectBackgroundColorModifier.identity, SelectBackgroundColorModifier, value);
        return this;
      }
      keyboardAvoidMode(mode: any): this {
        modifierWithKey(
          this._modifiersWithKeys, MenuKeyboardAvoidModeModifier.identity, MenuKeyboardAvoidModeModifier, mode);
        return this;
      }
      minKeyboardAvoidDistance(distance: any): this {
        modifierWithKey(
          this._modifiersWithKeys, MinKeyboardAvoidDistanceModifier.identity, MinKeyboardAvoidDistanceModifier, distance);
        return this;
      }
      menuSystemMaterial(menuSystemMaterial: any): this {
        modifierWithKey(
          this._modifiersWithKeys, MenuSystemMaterialModifier.identity, MenuSystemMaterialModifier, menuSystemMaterial);
        return this;
      }
      menuBackgroundBlurStyleOptions(menuBackgroundBlurStyleOptions: any): this {
        modifierWithKey(
          this._modifiersWithKeys, MenuBackgroundBlurStyleOptionsModifier.identity, MenuBackgroundBlurStyleOptionsModifier, menuBackgroundBlurStyleOptions);
        return this;
      }
      menuBackgroundEffect(menuBackgroundEffect: any): this {
        modifierWithKey(
          this._modifiersWithKeys, MenuBackgroundEffectModifier.identity, MenuBackgroundEffectModifier, menuBackgroundEffect);
        return this;
      }
      menuDistortionMode(mode: any): this {
        modifierWithKey(
          this._modifiersWithKeys, MenuDistortionModeModifier.identity, MenuDistortionModeModifier, mode);
        return this;
      }
      menuEdgeLightMode(mode: any): this {
        modifierWithKey(
          this._modifiersWithKeys, MenuEdgeLightModeModifier.identity, MenuEdgeLightModeModifier, mode);
        return this;
      }
    }

    class SelectOptionsModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().select.setOptions(node, undefined, undefined, undefined, undefined);
        } else {
          const valueArray = [];
          const iconArray = [];
          const symbolIconArray = [];
          const length = this.value?.length;
          for (let i = 0; i < length; i++) {
            valueArray.push(this.value[i]?.value);
            iconArray.push(this.value[i]?.icon);
            symbolIconArray.push(this.value[i]?.symbolIcon);
          }
          getUINativeModule().select.setOptions(node, valueArray, iconArray, symbolIconArray, length);
        }
      }

      checkObjectDiff(): boolean {
        return !(Array.isArray(this.stageValue) && Array.isArray(this.value) &&
          this.stageValue.length === this.value.length &&
          this.stageValue.every((eachValue, index) => {
            return isBaseOrResourceEqual(eachValue.value, this.value[index].value) &&
              isBaseOrResourceEqual(eachValue.icon, this.value[index].icon) &&
              isBaseOrResourceEqual(eachValue.symbolIcon, this.value[index].symbolIcon);
          }));
      }
    }
    (SelectOptionsModifier.identity as any) = Symbol('SelectOptions');

    class MenuBackgroundColorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().select.resetMenuBackgroundColor(node);
        }
        else {
          getUINativeModule().select.setMenuBackgroundColor(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (MenuBackgroundColorModifier.identity as any) = Symbol('selectMenuBackgroundColor');
    class MenuBackgroundBlurStyleModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().select.resetMenuBackgroundBlurStyle(node);
        }
        else {
          getUINativeModule().select.setMenuBackgroundBlurStyle(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (MenuBackgroundBlurStyleModifier.identity as any) = Symbol('selectMenuBackgroundBlurStyle');
    class MenuOutlineModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().select.resetMenuOutline(node);
        }
        else {
          let widthLeft;
          let widthRight;
          let widthTop;
          let widthBottom;
          if (!isUndefined(this.value.width) && this.value.width != null) {
            if (isNumber(this.value.width) || isString(this.value.width) || isResource(this.value.width)) {
              widthLeft = this.value.width;
              widthRight = this.value.width;
              widthTop = this.value.width;
              widthBottom = this.value.width;
            }
            else {
              widthLeft = this.value.width.left;
              widthRight = this.value.width.right;
              widthTop = this.value.width.top;
              widthBottom = this.value.width.bottom;
            }
          }
          let leftColor;
          let rightColor;
          let topColor;
          let bottomColor;
          if (!isUndefined(this.value.color) && this.value.color != null) {
            if (isNumber(this.value.color) || isString(this.value.color) || isResource(this.value.color)) {
              leftColor = this.value.color;
              rightColor = this.value.color;
              topColor = this.value.color;
              bottomColor = this.value.color;
            }
            else {
              leftColor = this.value.color.left;
              rightColor = this.value.color.right;
              topColor = this.value.color.top;
              bottomColor = this.value.color.bottom;
            }
          }
          getUINativeModule().select.setMenuOutline(node, widthLeft, widthRight, widthTop, widthBottom,
            leftColor, rightColor, topColor, bottomColor);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue.width, this.value.width) ||
          !isBaseOrResourceEqual(this.stageValue.color, this.value.color);
      }
    }
    (MenuOutlineModifier.identity as any) = Symbol('selectMenuOutline');
    class FontModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().select.resetFont(node);
        }
        else {
          getUINativeModule().select.setFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
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
    (FontModifier.identity as any) = Symbol('selectFont');
    class OptionFontModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().select.resetOptionFont(node);
        }
        else {
          getUINativeModule().select.setOptionFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
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
    (OptionFontModifier.identity as any) = Symbol('selectOptionFont');
    class SelectedOptionFontModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().select.resetSelectedOptionFont(node);
        }
        else {
          getUINativeModule().select.setSelectedOptionFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
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
    (SelectedOptionFontModifier.identity as any) = Symbol('selectSelectedOptionFont');
    class MenuAlignModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().select.resetMenuAlign(node);
        }
        else {
          getUINativeModule().select.setMenuAlign(node, this.value.alignType, this.value.dx, this.value.dy);
        }
      }
      checkObjectDiff(): boolean {
        let alignTypeEQ = this.stageValue.alignType === this.value.alignType;
        let dxEQ = isBaseOrResourceEqual(this.stageValue, this.value);
        let dyEQ = isBaseOrResourceEqual(this.stageValue, this.value);
        return !alignTypeEQ || !dxEQ || !dyEQ;
      }
      isEqual(stageValue: any, value: any) {
        if ((!isUndefined(stageValue) && isResource(stageValue)) &&
          (!isUndefined(value) && isResource(value))) {
          return true;
        }
        else {
          return stageValue !== value;
        }
      }
    }
    (MenuAlignModifier.identity as any) = Symbol('selectMenuAlign');
    class SelectDividerModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        var _a, _b, _c, _d;
        if (reset) {
          getUINativeModule().select.resetDivider(node, this.value);
        }
        else {
          getUINativeModule().select.setDivider(node, (_a = this.value) === null || _a === void 0 ? void 0 : _a.strokeWidth,
            (_b = this.value) === null || _b === void 0 ? void 0 : _b.color, (_c = this.value) === null || _c === void 0 ? void 0 : _c.startMargin,
            (_d = this.value) === null || _d === void 0 ? void 0 : _d.endMargin);
        }
      }
      checkObjectDiff(): boolean {
        var _a, _b, _c, _d, _e, _f, _g, _h;
        return !(((_a = this.stageValue) === null || _a === void 0 ? void 0 : _a.strokeWidth) === ((_b = this.value) === null || _b === void 0 ? void 0 : _b.strokeWidth) &&
          ((_c = this.stageValue) === null || _c === void 0 ? void 0 : _c.color) === ((_d = this.value) === null || _d === void 0 ? void 0 : _d.color) &&
          ((_e = this.stageValue) === null || _e === void 0 ? void 0 : _e.startMargin) === ((_f = this.value) === null || _f === void 0 ? void 0 : _f.startMargin) &&
          ((_g = this.stageValue) === null || _g === void 0 ? void 0 : _g.endMargin) === ((_h = this.value) === null || _h === void 0 ? void 0 : _h.endMargin));
      }
    }
    (SelectDividerModifier.identity as any) = Symbol('selectDivider');
    class SelectDividerStyleModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().select.resetDividerStyle(node);
        } else {
          getUINativeModule().select.setDividerStyle(node, this.value.strokeWidth, this.value.color, this.value.startMargin, this.value.endMargin, this.value.mode);
        }
      }
      checkObjectDiff(): boolean {
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
    (SelectDividerStyleModifier.identity as any) = Symbol('selectDividerStyle');
    class ControlSizeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().select.resetControlSize(node);
        }
        else {
          getUINativeModule().select.setControlSize(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return this.stageValue !== this.value;
      }
    }
    (ControlSizeModifier.identity as any) = Symbol('controlSize');
    class ArrowPositionModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().select.resetArrowPosition(node);
        }
        else {
          getUINativeModule().select.setArrowPosition(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return this.stageValue !== this.value;
      }
    }
    (ArrowPositionModifier.identity as any) = Symbol('selectArrowPosition');
    class SpaceModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().select.resetSpace(node);
        }
        else {
          getUINativeModule().select.setSpace(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (SpaceModifier.identity as any) = Symbol('selectSpace');
    class ValueModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().select.resetValue(node);
        }
        else {
          getUINativeModule().select.setValue(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (ValueModifier.identity as any) = Symbol('selectValue');
    class SelectedModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().select.resetSelected(node);
        }
        else {
          getUINativeModule().select.setSelected(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (SelectedModifier.identity as any) = Symbol('selectSelected');
    class SelectFontColorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().select.resetFontColor(node);
        }
        else {
          getUINativeModule().select.setFontColor(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (SelectFontColorModifier.identity as any) = Symbol('selectFontColor');
    class SelectedOptionBgColorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().select.resetSelectedOptionBgColor(node);
        }
        else {
          getUINativeModule().select.setSelectedOptionBgColor(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (SelectedOptionBgColorModifier.identity as any) = Symbol('selectSelectedOptionBgColor');
    class OptionBgColorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().select.resetOptionBgColor(node);
        }
        else {
          getUINativeModule().select.setOptionBgColor(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (OptionBgColorModifier.identity as any) = Symbol('selectOptionBgColor');
    class OptionFontColorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().select.resetOptionFontColor(node);
        }
        else {
          getUINativeModule().select.setOptionFontColor(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (OptionFontColorModifier.identity as any) = Symbol('selectOptionFontColor');
    class SelectedOptionFontColorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().select.resetSelectedOptionFontColor(node);
        }
        else {
          getUINativeModule().select.setSelectedOptionFontColor(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (SelectedOptionFontColorModifier.identity as any) = Symbol('selectSelectedOptionFontColor');
    class SelectOptionWidthModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().select.resetOptionWidth(node);
        } else {
          getUINativeModule().select.setOptionWidth(node, this.value);
        }
      }

      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (SelectOptionWidthModifier.identity as any) = Symbol('selectOptionWidth');
    class SelectOptionHeightModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().select.resetOptionHeight(node);
        } else {
          getUINativeModule().select.setOptionHeight(node, this.value);
        }
      }

      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (SelectOptionHeightModifier.identity as any) = Symbol('selectOptionHeight');
    class SelectWidthModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().select.resetWidth(node);
        } else {
          getUINativeModule().select.setWidth(node, this.value);
        }
      }

      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (SelectWidthModifier.identity as any) = Symbol('selectWidth');
    class SelectHeightModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().select.resetHeight(node);
        } else {
          getUINativeModule().select.setHeight(node, this.value);
        }
      }

      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (SelectHeightModifier.identity as any) = Symbol('selectHeight');
    class SelectSizeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().select.resetSize(node);
        } else {
          getUINativeModule().select.setSize(node, this.value.width, this.value.height);
        }
      }

      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue.width, this.value.width) ||
          !isBaseOrResourceEqual(this.stageValue.height, this.value.height);
      }
    }
    (SelectSizeModifier.identity as any) = Symbol('selectSize');
    class SelectDirectionModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().select.resetSelectDirection(node);
        }
        else {
          getUINativeModule().select.setSelectDirection(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (SelectDirectionModifier.identity as any) = Symbol('selectDirection');
    class AvoidanceModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().select.resetAvoidance(node);
        } else {
          getUINativeModule().select.setAvoidance(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return this.stageValue !== this.value;
      }
    }
    (AvoidanceModifier.identity as any) = Symbol('selectAvoidance');
    class SelectBackgroundColorModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().select.resetBackgroundColor(node);
        }
        else {
          getUINativeModule().select.setBackgroundColor(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (SelectBackgroundColorModifier.identity as any) = Symbol('selectBackgroundColor');
    class MenuKeyboardAvoidModeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().select.resetMenuKeyboardAvoidMode(node);
        } else {
          getUINativeModule().select.setMenuKeyboardAvoidMode(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return this.stageValue !== this.value;
      }
    }
    (MenuKeyboardAvoidModeModifier.identity as any) = Symbol('menuKeyboardAvoidMode');
    class MinKeyboardAvoidDistanceModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset || !this.value) {
          getUINativeModule().select.resetMinKeyboardAvoidDistance(node);
        } else {
          getUINativeModule().select.setMinKeyboardAvoidDistance(node, this.value);
        }
      }

      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (MinKeyboardAvoidDistanceModifier.identity as any) = Symbol('minKeyboardAvoidDistance');
    class MenuSystemMaterialModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset || !this.value) {
          getUINativeModule().select.resetMenuSystemMaterial(node);
        } else {
          getUINativeModule().select.setMenuSystemMaterial(node, this.value);
        }
      }

      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (MenuSystemMaterialModifier.identity as any) = Symbol('menuSystemMaterial');
    class MenuBackgroundBlurStyleOptionsModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset || !this.value) {
          getUINativeModule().select.resetMenuBackgroundBlurStyleOptions(node);
        } else {
          getUINativeModule().select.setMenuBackgroundBlurStyleOptions(node, this.value);
        }
      }

      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (MenuBackgroundBlurStyleOptionsModifier.identity as any) = Symbol('menuBackgroundBlurStyleOptions');
    class MenuBackgroundEffectModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset || !this.value) {
          getUINativeModule().select.resetMenuBackgroundEffect(node);
        } else {
          getUINativeModule().select.setMenuBackgroundEffect(node, this.value);
        }
      }

      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (MenuBackgroundEffectModifier.identity as any) = Symbol('menuBackgroundEffect');
    class SelectOnSelectModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().select.resetOnSelect(node);
        } else {
          getUINativeModule().select.setOnSelect(node, this.value);
        }
      }
    }
    (SelectOnSelectModifier.identity as any) = Symbol('selectOnSelect');

    class MenuDistortionModeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().select.resetMenuDistortionMode(node);
        } else {
          getUINativeModule().select.setMenuDistortionMode(node, this.value);
        }
      }

      checkObjectDiff(): boolean {
        return this.stageValue !== this.value;
      }
    }
    (MenuDistortionModeModifier.identity as any) = Symbol('menuDistortionMode');
    class MenuEdgeLightModeModifier extends ModifierWithKey<any> {
      constructor(value: any) {
        super(value);
      }
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().select.resetMenuEdgeLightMode(node);
        } else {
          getUINativeModule().select.setMenuEdgeLightMode(node, this.value);
        }
      }

      checkObjectDiff(): boolean {
        return this.stageValue !== this.value;
      }
    }
    (MenuEdgeLightModeModifier as any).identity = Symbol('menuEdgeLightMode');

    loadComponent.componentObj = { 'component': ArkSelectComponent };
  }
  return loadComponent.componentObj;
}
class JSSelect extends JSViewAbstract {
  static create(params: any): void {
    getUINativeModule().select.create(params);
  }
  static selected(value: any, callback: any): void {
    getUINativeModule().select.setJsSelected(true, value, callback);
  }
  static value(value: any, callback: any): void {
    getUINativeModule().select.setJsValue(true, value, callback);
  }
  static font(value: any): void {
    getUINativeModule().select.setJsFont(true, value);
  }
  static fontColor(value: any): void {
    getUINativeModule().select.setFontColor(true, value);
  }
  static backgroundColor(value: any): void {
    getUINativeModule().select.setBackgroundColor(true, value);
  }
  static selectedOptionBgColor(value: any): void {
    getUINativeModule().select.setSelectedOptionBgColor(true, value);
  }
  static selectedOptionFont(value: any): void {
    getUINativeModule().select.setJsSelectedOptionFont(true, value);
  }
  static selectedOptionFontColor(value: any): void {
    getUINativeModule().select.setSelectedOptionFontColor(true, value);
  }
  static optionBgColor(value: any): void {
    getUINativeModule().select.setOptionBgColor(true, value);
  }
  static optionFont(value: any): void {
    getUINativeModule().select.setJsOptionFont(true, value);
  }
  static optionFontColor(value: any): void {
    getUINativeModule().select.setOptionFontColor(true, value);
  }
  static onSelect(value: any): void {
    getUINativeModule().select.setOnSelect(true, value);
  }
  static space(value: any): void {
    getUINativeModule().select.setSpace(true, value);
  }
  static arrowPosition(value: any): void {
    getUINativeModule().select.setArrowPosition(true, value);
  }
  static menuAlign(alignType, offset: any): void {
    getUINativeModule().select.setJsMenuAlign(true, alignType, offset);
  }
  static avoidance(value: any): void {
    getUINativeModule().select.setAvoidance(true, value);
  }
  static onSelected(value: any): void {
    getUINativeModule().select.setOnSelect(true, value);
  }
  static size(value: any): void {
    if (value) {
      JSViewAbstract.width(value.width);
      JSViewAbstract.height(value.height);
    } else {
      JSViewAbstract.width(null);
      JSViewAbstract.height(null);
    }
  }
  static padding(value: any): void {
    getUINativeModule().select.setPadding(true, value);
  }
  static paddingTop(value: any): void {
    getUINativeModule().select.setPaddingTop(true, value);
  }
  static paddingBottom(value: any): void {
    getUINativeModule().select.setPaddingBottom(true, value);
  }
  static paddingLeft(value: any): void {
    getUINativeModule().select.setPaddingLeft(true, value);
  }
  static paddingRight(value: any): void {
    getUINativeModule().select.setPaddingRight(true, value);
  }
  static optionWidth(value: any): void {
    getUINativeModule().select.setJsOptionWidth(true, value);
  }
  static optionHeight(value: any): void {
    getUINativeModule().select.setOptionHeight(true, value);
  }
  static optionWidthFitTrigger(value: any): void {
    getUINativeModule().select.setOptionWidthFitTrigger(true, value);
  }
  static menuBackgroundColor(value: any): void {
    getUINativeModule().select.setMenuBackgroundColor(true, value);
  }
  static menuBackgroundBlurStyle(value: any): void {
    getUINativeModule().select.setMenuBackgroundBlurStyle(true, value);
  }
  static divider(value: any): void {
    getUINativeModule().select.setJsDivider(true, value);
  }
  static controlSize(value: any): void {
    getUINativeModule().select.setControlSize(true, value);
  }
  static direction(value: any): void {
    getUINativeModule().select.setSelectDirection(true, value);
  }
  static dividerStyle(value: any): void {
    getUINativeModule().select.setJsDividerStyle(true, value);
  }
  static arrowModifier(value: any): void {
    getUINativeModule().select.setArrowModifier(true, value);
  }
  static textModifier(value: any): void {
    getUINativeModule().select.setTextModifier(true, value);
  }
  static optionTextModifier(value: any): void {
    getUINativeModule().select.setOptionTextModifier(true, value);
  }
  static selectedOptionTextModifier(value: any): void {
    getUINativeModule().select.setSelectedOptionTextModifier(true, value);
  }
  static menuOutline(value: any): void {
    getUINativeModule().select.setJsMenuOutline(true, value);
  }
  static showInSubWindow(value: boolean): void {
    getUINativeModule().select.setShowInSubWindow(true, value);
  }
  static showDefaultSelectedIcon(value: boolean): void {
    getUINativeModule().select.setShowDefaultSelectedIcon(true, value);
  }
  static keyboardAvoidMode(value: any): void {
    getUINativeModule().select.setMenuKeyboardAvoidMode(true, value);
  }
  static minKeyboardAvoidDistance(value: any): void {
    getUINativeModule().select.setMinKeyboardAvoidDistance(true, value);
  }
  static menuSystemMaterial(value: any): void {
    getUINativeModule().select.setMenuSystemMaterial(true, value);
  }
  static menuBackgroundBlurStyleOptions(value: any): void {
    getUINativeModule().select.setMenuBackgroundBlurStyleOptions(true, value);
  }
  static menuBackgroundEffect(value: any): void {
    getUINativeModule().select.setMenuBackgroundEffect(true, value);
  }
  static menuDistortionMode(value: any): void {
    getUINativeModule().select.setMenuDistortionMode(true, value);
  }
  static menuEdgeLightMode(value: any): void {
    getUINativeModule().select.setMenuEdgeLightMode(true, value);
  }
  static attributeModifier(modifier: any): void {
    attributeModifierFunc.call(this, modifier, (nativePtr: any) => {
      return createComponent(nativePtr);
    }, (nativePtr: any, classType: any, modifierJS: any) => {
      return new modifierJS.SelectModifier(nativePtr, classType);
    });
  }
  static menuItemContentModifier(modifier: any): void {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
      return createComponent(nativeNode, 'select');
    });
    component.menuItemContentModifier(modifier);
  }
  static onClick(value: any): void {
    __Common__.onClick(value);
  }
  static onTouch(value: any): void {
    __Common__.onTouch(value);
  }
  static onKeyEvent(value: any): void {
    __Common__.onKeyEvent(value);
  }
  static onDeleteEvent(value: any): void {
    __Common__.onDeleteEvent(value);
  }
  static onAttach(value: any): void {
    __Common__.onAttach(value);
  }
  static onAppear(value: any): void {
    __Common__.onAppear(value);
  }
  static onDetach(value: any): void {
    __Common__.onDetach(value);
  }
  static onDisAppear(value: any): void {
    __Common__.onDisAppear(value);
  }
}

function createComponent(nativePtr: any, classType: any): any {
  loadComponent();
  if (loadComponent.componentObj !== undefined) {
    return new loadComponent.componentObj.component(nativePtr, classType);
  }
  return undefined;
}

function exportComponent(): void {
  globalThis.ArkSelectComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
  globalThis.Select = JSSelect;
}
export default { createComponent, exportComponent, exportView, loadComponent };
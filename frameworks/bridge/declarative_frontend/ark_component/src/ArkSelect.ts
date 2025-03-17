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
class ArkSelectComponent extends ArkComponent implements SelectAttribute {
  builder: WrappedBuilder<Object[]> | null = null;
  menuItemNodes: Array<BuilderNode<[MenuItemConfiguration]>> | null = null;
  modifier: ContentModifier<MenuItemConfiguration>;
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  allowChildCount(): number {
    return 0;
  }
  initialize(value: Object[]): this {
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
  optionWidth(value: Dimension | OptionWidthMode): this {
    modifierWithKey(
      this._modifiersWithKeys, SelectOptionWidthModifier.identity, SelectOptionWidthModifier, value);
    return this;
  }
  optionHeight(value: Dimension): this {
    modifierWithKey(
      this._modifiersWithKeys, SelectOptionHeightModifier.identity, SelectOptionHeightModifier, value);
    return this;
  }
  width(value: Length): this {
    modifierWithKey(
      this._modifiersWithKeys, SelectWidthModifier.identity, SelectWidthModifier, value);
    return this;
  }
  height(value: Length): this {
    modifierWithKey(
      this._modifiersWithKeys, SelectHeightModifier.identity, SelectHeightModifier, value);
    return this;
  }
  size(value: SizeOptions): this {
    modifierWithKey(
      this._modifiersWithKeys, SelectSizeModifier.identity, SelectSizeModifier, value);
    return this;
  }
  selected(value: number | Resource): this {
    modifierWithKey(
      this._modifiersWithKeys, SelectedModifier.identity, SelectedModifier, value);
    return this;
  }
  value(value: ResourceStr): this {
    modifierWithKey(
      this._modifiersWithKeys, ValueModifier.identity, ValueModifier, value);
    return this;
  }
  font(value: Font): this {
    modifierWithKey(
      this._modifiersWithKeys, FontModifier.identity, FontModifier, value);
    return this;
  }
  fontColor(value: ResourceColor): this {
    modifierWithKey(
      this._modifiersWithKeys, SelectFontColorModifier.identity, SelectFontColorModifier, value);
    return this;
  }
  selectedOptionBgColor(value: ResourceColor): this {
    modifierWithKey(
      this._modifiersWithKeys, SelectedOptionBgColorModifier.identity, SelectedOptionBgColorModifier, value);
    return this;
  }
  selectedOptionFont(value: Font): this {
    modifierWithKey(
      this._modifiersWithKeys, SelectedOptionFontModifier.identity, SelectedOptionFontModifier, value);
    return this;
  }
  selectedOptionFontColor(value: ResourceColor): this {
    modifierWithKey(
      this._modifiersWithKeys, SelectedOptionFontColorModifier.identity, SelectedOptionFontColorModifier, value);
    return this;
  }
  optionBgColor(value: ResourceColor): this {
    modifierWithKey(
      this._modifiersWithKeys, OptionBgColorModifier.identity, OptionBgColorModifier, value);
    return this;
  }
  optionFont(value: Font): this {
    modifierWithKey(
      this._modifiersWithKeys, OptionFontModifier.identity, OptionFontModifier, value);
    return this;
  }
  optionFontColor(value: ResourceColor): this {
    modifierWithKey(
      this._modifiersWithKeys, OptionFontColorModifier.identity, OptionFontColorModifier, value);
    return this;
  }
  onSelect(callback: (index: number, value: string) => void): this {
    throw new Error('Method not implemented.');
  }
  space(value: Length): this {
    modifierWithKey(
      this._modifiersWithKeys, SpaceModifier.identity, SpaceModifier, value);
    return this;
  }
  arrowPosition(value: ArrowPosition): this {
    modifierWithKey(
      this._modifiersWithKeys, ArrowPositionModifier.identity, ArrowPositionModifier, value);
    return this;
  }
  menuAlign(alignType: MenuAlignType, offset?: Offset): this {
    let menuAlign = new ArkMenuAlignType(alignType, offset);
    modifierWithKey(
      this._modifiersWithKeys, MenuAlignModifier.identity, MenuAlignModifier, menuAlign);
    return this;
  }
  avoidance(mode: AvoidanceMode): this {
    modifierWithKey(
      this._modifiersWithKeys, AvoidanceModifier.identity, AvoidanceModifier, mode);
    return this;
  }
  menuBackgroundColor(value: ResourceColor): this {
    modifierWithKey(
      this._modifiersWithKeys, MenuBackgroundColorModifier.identity, MenuBackgroundColorModifier, value);
    return this;
  }
  menuBackgroundBlurStyle(value: BlurStyle): this {
    modifierWithKey(
      this._modifiersWithKeys, MenuBackgroundBlurStyleModifier.identity, MenuBackgroundBlurStyleModifier, value);
    return this;
  }
  controlSize(controlSize: ControlSize): this {
    modifierWithKey(
      this._modifiersWithKeys, ControlSizeModifier.identity, ControlSizeModifier, controlSize);
    return this;
  }
  menuItemContentModifier(modifier: ContentModifier<MenuItemConfiguration>): this {
    if (modifier === undefined || modifier === null) {
      getUINativeModule().select.setContentModifierBuilder(this.nativePtr, false);
      return;
    }
    this.builder = modifier.applyContent();
    this.modifier = modifier;
    getUINativeModule().select.setContentModifierBuilder(this.nativePtr, this);
  }
  makeContentModifierNode(context: UIContext, menuItemConfiguration: MenuItemConfiguration): FrameNode | null {
    menuItemConfiguration.contentModifier = this.modifier;
    const index = menuItemConfiguration.index;
    const xNode = globalThis.requireNapi('arkui.node');
    this.menuItemNodes = new xNode.BuilderNode(context);
    this.menuItemNodes.build(this.builder, menuItemConfiguration);
    return this.menuItemNodes.getFrameNode();
  }
  divider(value: DividerOptions | null): this {
    modifierWithKey(
      this._modifiersWithKeys, SelectDividerModifier.identity, SelectDividerModifier, value);
    return this;
  }
  dividerStyle(value: Optional<DividerStyleOptions>): this {
    modifierWithKey(
      this._modifiersWithKeys, SelectDividerStyleModifier.identity, SelectDividerStyleModifier, value);
    return this;
  }
  direction(value: Direction): this {
    modifierWithKey(this._modifiersWithKeys, SelectDirectionModifier.identity, SelectDirectionModifier, value);
    return this;
  }
}

class SelectOptionsModifier extends ModifierWithKey<SelectOption[]> {
  constructor(value: SelectOption[]) {
    super(value);
  }
  static identity: Symbol = Symbol('selectOptions');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().select.setOptions(node, undefined, undefined, undefined, undefined);
    } else {
      let valueArray: string[] = [];
      let iconArray: string[] = [];
      let symbolIconArray: object[] = [];
      let length: number = 0;
      if (this.value) {
        length = this.value.length;
        for (let i = 0; i < length; i++) {
          valueArray.push(this.value[i]?.value);
          iconArray.push(this.value[i]?.icon);
          symbolIconArray.push(this.value[i]?.symbolIcon);
        }
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

class MenuBackgroundColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('selectMenuBackgroundColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().select.resetMenuBackgroundColor(node);
    } else {
      getUINativeModule().select.setMenuBackgroundColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class MenuBackgroundBlurStyleModifier extends ModifierWithKey<BlurStyle> {
  constructor(value: BlurStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('selectMenuBackgroundBlurStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().select.resetMenuBackgroundBlurStyle(node);
    } else {
      getUINativeModule().select.setMenuBackgroundBlurStyle(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class FontModifier extends ModifierWithKey<Font> {
  constructor(value: Font) {
    super(value);
  }
  static identity: Symbol = Symbol('selectFont');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().select.resetFont(node);
    } else {
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

class OptionFontModifier extends ModifierWithKey<Font> {
  constructor(value: Font) {
    super(value);
  }
  static identity: Symbol = Symbol('selectOptionFont');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().select.resetOptionFont(node);
    } else {
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

class SelectedOptionFontModifier extends ModifierWithKey<Font> {
  constructor(value: Font) {
    super(value);
  }
  static identity: Symbol = Symbol('selectSelectedOptionFont');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().select.resetSelectedOptionFont(node);
    } else {
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

class MenuAlignModifier extends ModifierWithKey<ArkMenuAlignType> {
  constructor(value: ArkMenuAlignType) {
    super(value);
  }
  static identity: Symbol = Symbol('selectMenuAlign');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().select.resetMenuAlign(node);
    } else {
      getUINativeModule().select.setMenuAlign(node, this.value.alignType, this.value.dx, this.value.dy);
    }
  }

  checkObjectDiff(): boolean {
    let alignTypeEQ = this.stageValue.alignType === this.value.alignType;
    let dxEQ = isBaseOrResourceEqual(this.stageValue, this.value);
    let dyEQ = isBaseOrResourceEqual(this.stageValue, this.value);

    return !alignTypeEQ || !dxEQ || !dyEQ;
  }

  private isEqual(stageValue: Length, value: Length): boolean {
    if ((!isUndefined(stageValue) && isResource(stageValue)) &&
      (!isUndefined(value) && isResource(value))) {
      return !isResourceEqual(stageValue, value);
    } else {
      return stageValue !== value;
    }
  }
}

class AvoidanceModifier extends ModifierWithKey<AvoidanceMode> {
  constructor(value: AvoidanceMode) {
    super(value);
  }
  static identity: Symbol = Symbol('selectAvoidance');
  applyPeer(node: KNode, reset: boolean): void {
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

class ControlSizeModifier extends ModifierWithKey<ControlSize> {
  constructor(value: ControlSize) {
    super(value);
  }
  static identity: Symbol = Symbol('controlSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().select.resetControlSize(node);
    } else {
      getUINativeModule().select.setControlSize(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class ArrowPositionModifier extends ModifierWithKey<ArrowPosition> {
  constructor(value: ArrowPosition) {
    super(value);
  }
  static identity: Symbol = Symbol('selectArrowPosition');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().select.resetArrowPosition(node);
    } else {
      getUINativeModule().select.setArrowPosition(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}
class SpaceModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('selectSpace');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().select.resetSpace(node);
    } else {
      getUINativeModule().select.setSpace(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class ValueModifier extends ModifierWithKey<ResourceStr> {
  constructor(value: ResourceStr) {
    super(value);
  }
  static identity: Symbol = Symbol('selectValue');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().select.resetValue(node);
    } else {
      getUINativeModule().select.setValue(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class SelectedModifier extends ModifierWithKey<number | Resource> {
  constructor(value: number | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('selectSelected');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().select.resetSelected(node);
    } else {
      getUINativeModule().select.setSelected(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class SelectFontColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('selectFontColor');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().select.resetFontColor(node);
    } else {
      getUINativeModule().select.setFontColor(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class SelectedOptionBgColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('selectSelectedOptionBgColor');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().select.resetSelectedOptionBgColor(node);
    } else {
      getUINativeModule().select.setSelectedOptionBgColor(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class OptionBgColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('selectOptionBgColor');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().select.resetOptionBgColor(node);
    } else {
      getUINativeModule().select.setOptionBgColor(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class OptionFontColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('selectOptionFontColor');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().select.resetOptionFontColor(node);
    } else {
      getUINativeModule().select.setOptionFontColor(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class SelectedOptionFontColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('selectSelectedOptionFontColor');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().select.resetSelectedOptionFontColor(node);
    } else {
      getUINativeModule().select.setSelectedOptionFontColor(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class SelectOptionWidthModifier extends ModifierWithKey<Dimension | OptionWidthMode> {
  constructor(value: Dimension | OptionWidthMode) {
    super(value);
  }
  static identity: Symbol = Symbol('selectOptionWidth');

  applyPeer(node: KNode, reset: boolean): void {
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

class SelectOptionHeightModifier extends ModifierWithKey<Dimension> {
  constructor(value: Dimension) {
    super(value);
  }
  static identity: Symbol = Symbol('selectOptionHeight');

  applyPeer(node: KNode, reset: boolean): void {
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

class SelectWidthModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('selectWidth');

  applyPeer(node: KNode, reset: boolean): void {
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

class SelectDividerModifier extends ModifierWithKey<DividerOptions | null> {
  constructor(value: DividerOptions | null) {
    super(value);
  }
  static identity: Symbol = Symbol('selectDivider');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().select.resetDivider(node, this.value);
    } else {
      getUINativeModule().select.setDivider(node, this.value?.strokeWidth, this.value?.color, this.value?.startMargin, this.value?.endMargin);
    }
  }

  checkObjectDiff(): boolean {
    return !(this.stageValue?.strokeWidth === this.value?.strokeWidth &&
      this.stageValue?.color === this.value?.color &&
      this.stageValue?.startMargin === this.value?.startMargin &&
      this.stageValue?.endMargin === this.value?.endMargin);
  }
}

class SelectDividerStyleModifier extends ModifierWithKey<Optional<DividerStyleOptions>> {
  constructor(value: Optional<DividerStyleOptions>) {
    super(value);
  }
  static identity: Symbol = Symbol('selectDividerStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset || !this.value) {
      getUINativeModule().select.resetDividerStyle(node);
    } else {
      getUINativeModule().select.setDividerStyle(node, this.value.strokeWidth, this.value.color, this.value.startMargin, this.value.endMargin, this.value.mode);
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !((this.stageValue as DividerStyleOptions).strokeWidth === (this.value as DividerStyleOptions).strokeWidth &&
        (this.stageValue as DividerStyleOptions).color === (this.value as DividerStyleOptions).color &&
        (this.stageValue as DividerStyleOptions).startMargin === (this.value as DividerStyleOptions).startMargin &&
        (this.stageValue as DividerStyleOptions).endMargin === (this.value as DividerStyleOptions).endMargin &&
        (this.stageValue as DividerStyleOptions).mode === (this.value as DividerStyleOptions).mode);
    } else {
      return true;
    }
  }
}

class SelectHeightModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('selectHeight');

  applyPeer(node: KNode, reset: boolean): void {
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

class SelectSizeModifier extends ModifierWithKey<SizeOptions> {
  constructor(value: SizeOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('selectSize');

  applyPeer(node: KNode, reset: boolean): void {
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

class SelectDirectionModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('selectDirection');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().select.resetSelectDirection(node);
    } else {
      getUINativeModule().select.setSelectDirection(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

// @ts-ignore
globalThis.Select.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkSelectComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.SelectModifier(nativePtr, classType);
  });
};

// @ts-ignore
globalThis.Select.menuItemContentModifier = function (modifier): void {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkSelectComponent(nativeNode);
  });
  component.menuItemContentModifier(modifier);
};

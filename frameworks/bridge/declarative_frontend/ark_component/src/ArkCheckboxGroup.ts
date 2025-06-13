/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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
class CheckboxGroupSelectAllModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('checkboxgroupSelectAll');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      getUINativeModule().checkboxgroup.resetCheckboxGroupSelectAll(node);
    } else {
      getUINativeModule().checkboxgroup.setCheckboxGroupSelectAll(node, this.value);
    }
  }
}

class CheckboxGroupSelectedColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('checkboxgroupSelectedColor');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      getUINativeModule().checkboxgroup.resetCheckboxGroupSelectedColor(node);
    } else {
      getUINativeModule().checkboxgroup.setCheckboxGroupSelectedColor(node, this.value);
    }
  }

  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}


class CheckboxGroupUnselectedColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('checkboxgroupUnselectedColor');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      getUINativeModule().checkboxgroup.resetCheckboxGroupUnSelectedColor(node);
    } else {
      getUINativeModule().checkboxgroup.setCheckboxGroupUnSelectedColor(node, this.value);
    }
  }

  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class CheckboxGroupMarkModifier extends ModifierWithKey<MarkStyle> {
  constructor(value: MarkStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('checkboxgroupMark');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().checkboxgroup.resetCheckboxGroupMark(node);
    } else {
      getUINativeModule().checkboxgroup.setCheckboxGroupMark(node, this.value?.strokeColor, this.value?.size, this.value?.strokeWidth);
    }
  }

  checkObjectDiff(): boolean {
    let colorEQ = isBaseOrResourceEqual(this.stageValue.strokeColor, this.value.strokeColor);
    let sizeEQ = isBaseOrResourceEqual(this.stageValue.size, this.value.size);
    let widthEQ = isBaseOrResourceEqual(this.stageValue.strokeWidth, this.value.strokeWidth);
    return !colorEQ || !sizeEQ || !widthEQ;
  }
}

class CheckboxGroupWidthModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('checkboxGroupWidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().checkboxgroup.resetCheckboxGroupWidth(node);
    } else {
      getUINativeModule().checkboxgroup.setCheckboxGroupWidth(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class CheckboxGroupSizeModifier extends ModifierWithKey<SizeOptions> {
  constructor(value: SizeOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('checkboxGroupSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().checkboxgroup.resetCheckboxGroupSize(node);
    } else {
      getUINativeModule().checkboxgroup.setCheckboxGroupSize(node, this.value.width, this.value.height);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.width, this.value.width) ||
      !isBaseOrResourceEqual(this.stageValue.height, this.value.height);
  }
}

class CheckboxGroupHeightModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('checkboxGroupHeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().checkboxgroup.resetCheckboxGroupHeight(node);
    } else {
      getUINativeModule().checkboxgroup.setCheckboxGroupHeight(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class CheckboxGroupStyleModifier extends ModifierWithKey<CheckBoxShape> {
  constructor(value: CheckBoxShape) {
    super(value);
  }
  static identity: Symbol = Symbol('checkboxgroupStyle');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      getUINativeModule().checkboxgroup.resetCheckboxGroupStyle(node);
    } else {
      getUINativeModule().checkboxgroup.setCheckboxGroupStyle(node, this.value);
    }
  }

  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class CheckBoxGroupOptionsModifier extends ModifierWithKey<CheckboxGroupOptions> {
  constructor(value: CheckboxGroupOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('checkboxGroupOptions');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().checkbox.setCheckboxGroupOptions(node, undefined);
    } else {
      getUINativeModule().checkbox.setCheckboxGroupOptions(node, this.value.group);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.group, this.value.group);
  }
}

class CheckboxGroupOnChangeModifier extends ModifierWithKey<OnCheckboxGroupChangeCallback> {
  constructor(value: OnCheckboxGroupChangeCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('checkboxOnChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().checkboxgroup.resetCheckboxGroupOnChange(node);
    } else {
      getUINativeModule().checkboxgroup.setCheckboxGroupOnChange(node, this.value);
    }
  }
}

class ArkCheckboxGroupComponent extends ArkComponent implements CheckboxGroupAttribute {
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
      modifierWithKey(this._modifiersWithKeys, CheckBoxGroupOptionsModifier.identity, CheckBoxGroupOptionsModifier,
        value[0]);
    } else {
      modifierWithKey(this._modifiersWithKeys, CheckBoxGroupOptionsModifier.identity, CheckBoxGroupOptionsModifier,
        undefined);
    }
    return this;
  }
  selectAll(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, CheckboxGroupSelectAllModifier.identity, CheckboxGroupSelectAllModifier, value);
    return this;
  }
  selectedColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, CheckboxGroupSelectedColorModifier.identity, CheckboxGroupSelectedColorModifier, value);
    return this;
  }
  unselectedColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, CheckboxGroupUnselectedColorModifier.identity, CheckboxGroupUnselectedColorModifier, value);
    return this;
  }
  mark(value: MarkStyle): this {
    modifierWithKey(
      this._modifiersWithKeys, CheckboxGroupMarkModifier.identity, CheckboxGroupMarkModifier, value);
    return this;
  }
  onChange(callback: OnCheckboxGroupChangeCallback ): this {
    modifierWithKey(this._modifiersWithKeys, CheckboxGroupOnChangeModifier.identity, CheckboxGroupOnChangeModifier, callback);
    return this;
  }
  size(value: SizeOptions): this {
    modifierWithKey(
      this._modifiersWithKeys, CheckboxGroupSizeModifier.identity, CheckboxGroupSizeModifier, value);
    return this;
  }
  width(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, CheckboxGroupWidthModifier.identity, CheckboxGroupWidthModifier, value);
    return this;
  }
  height(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, CheckboxGroupHeightModifier.identity,
      CheckboxGroupHeightModifier, value);
    return this;
  }
  checkboxShape(value: CheckBoxShape): this {
    modifierWithKey(this._modifiersWithKeys, CheckboxGroupStyleModifier.identity, CheckboxGroupStyleModifier, value);
    return this;
  }
}
// @ts-ignore
globalThis.CheckboxGroup.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkCheckboxGroupComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.CheckboxGroupModifier(nativePtr, classType);
  });
};

globalThis.CheckboxGroup.onChange = function (value: (selected: boolean) => void): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().checkboxgroup.setCheckboxGroupOnChange(nodePtr, value);
};

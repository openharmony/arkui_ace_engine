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
class ArkCheckboxComponent extends ArkComponent implements CheckboxAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  shape(value: CheckBoxShape): this {
    throw new Error('Method not implemented.');
  }
  width(value: Length): this {
    modifierWithKey(
      this._modifiersWithKeys, CheckboxWidthModifier.identity, CheckboxWidthModifier, value);
    return this;
  }
  height(value: Length): this {
    modifierWithKey(
      this._modifiersWithKeys, CheckboxHeightModifier.identity, CheckboxHeightModifier, value);
    return this;
  }
  select(value: boolean): this {
    modifierWithKey(
      this._modifiersWithKeys, CheckboxSelectModifier.identity, CheckboxSelectModifier, value);
    return this;
  }
  selectedColor(value: ResourceColor): this {
    modifierWithKey(
      this._modifiersWithKeys, CheckboxSelectedColorModifier.identity, CheckboxSelectedColorModifier, value);

    return this;
  }
  unselectedColor(value: ResourceColor): this {
    modifierWithKey(
      this._modifiersWithKeys, CheckboxUnselectedColorModifier.identity, CheckboxUnselectedColorModifier, value);
    return this;
  }
  mark(value: MarkStyle): this {
    modifierWithKey(
      this._modifiersWithKeys, CheckboxMarkModifier.identity, CheckboxMarkModifier, value);
    return this;
  }
  onChange(callback: (value: boolean) => void): this {
    throw new Error('Method not implemented.');
  }
}

class CheckboxMarkModifier extends ModifierWithKey<MarkStyle> {
  constructor(value: MarkStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('checkboxMark');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().checkbox.resetMark(node);
    }
    else {
      GetUINativeModule().checkbox.setMark(node, this.value?.strokeColor, this.value?.size, this.value?.strokeWidth);
    }
  }

  checkObjectDiff(): boolean {
    let colorEQ = isBaseOrResourceEqual(this.stageValue.strokeColor, this.value.strokeColor);
    let sizeEQ = isBaseOrResourceEqual(this.stageValue.size, this.value.size);
    let widthEQ = isBaseOrResourceEqual(this.stageValue.strokeWidth, this.value.strokeWidth);
    return !colorEQ || !sizeEQ || !widthEQ;
  }
}

class CheckboxSelectModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('checkboxSelect');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().checkbox.resetSelect(node);
    }
    else {
      GetUINativeModule().checkbox.setSelect(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class CheckboxHeightModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('checkboxHeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().checkbox.resetHeight(node);
    }
    else {
      GetUINativeModule().checkbox.setHeight(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class CheckboxWidthModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('checkboxWidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().checkbox.resetWidth(node);
    }
    else {
      GetUINativeModule().checkbox.setWidth(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class CheckboxSelectedColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('checkboxSelectedColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().checkbox.resetSelectedColor(node);
    }
    else {
      GetUINativeModule().checkbox.setSelectedColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class CheckboxUnselectedColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('checkboxUnselectedColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().checkbox.resetUnSelectedColor(node);
    }
    else {
      GetUINativeModule().checkbox.setUnSelectedColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

// @ts-ignore
globalThis.Checkbox.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkCheckboxComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

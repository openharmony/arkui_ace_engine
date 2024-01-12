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

class ArkCheckboxGroupComponent extends ArkComponent implements CheckboxGroupAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
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
  onChange(callback: (event: CheckboxGroupResult) => void): CheckboxGroupAttribute {
    throw new Error('Method not implemented.');
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
}
// @ts-ignore
globalThis.CheckboxGroup.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkCheckboxGroupComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};


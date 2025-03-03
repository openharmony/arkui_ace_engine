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
  builder: WrappedBuilder<Object[]> | null = null;
  checkboxNode: BuilderNode<[CheckBoxConfiguration]> | null = null;
  modifier: ContentModifier<CheckBoxConfiguration>;
  needRebuild: boolean = false;
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
      modifierWithKey(this._modifiersWithKeys, CheckboxOptionsModifier.identity, CheckboxOptionsModifier, value[0]);
    } else {
      modifierWithKey(this._modifiersWithKeys, CheckboxOptionsModifier.identity, CheckboxOptionsModifier, undefined);
    }
    return this;
  }
  shape(value: CheckBoxShape): this {
    modifierWithKey(this._modifiersWithKeys, CheckBoxShapeModifier.identity, CheckBoxShapeModifier, value);
    return this;
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
  padding(value: Padding | Length): this {
    let arkValue = new ArkPadding();
    if (value !== null && value !== undefined) {
      if (isLengthType(value) || isResource(value)) {
        arkValue.top = <Length>value;
        arkValue.right = <Length>value;
        arkValue.bottom = <Length>value;
        arkValue.left = <Length>value;
      } else {
        arkValue.top = (<Padding>value).top;
        arkValue.right = (<Padding>value).right;
        arkValue.bottom = (<Padding>value).bottom;
        arkValue.left = (<Padding>value).left;
      }
      modifierWithKey(this._modifiersWithKeys, CheckBoxPaddingModifier.identity, CheckBoxPaddingModifier, arkValue);
    } else {
      modifierWithKey(this._modifiersWithKeys, CheckBoxPaddingModifier.identity, CheckBoxPaddingModifier, undefined);
    }
    return this;
  }
  size(value: SizeOptions): this {
    modifierWithKey(this._modifiersWithKeys, CheckBoxSizeModifier.identity, CheckBoxSizeModifier, value);
    return this;
  }
  responseRegion(value: Array<Rectangle> | Rectangle): this {
    modifierWithKey(
      this._modifiersWithKeys, CheckBoxResponseRegionModifier.identity, CheckBoxResponseRegionModifier, value);
    return this;
  }
  contentModifier(value: ContentModifier<CheckBoxConfiguration>): this {
    modifierWithKey(this._modifiersWithKeys, CheckBoxContentModifier.identity, CheckBoxContentModifier, value);
    return this;
  }
  setContentModifier(modifier: ContentModifier<CheckBoxConfiguration>): this {
    if (modifier === undefined || modifier === null) {
      getUINativeModule().checkbox.setContentModifierBuilder(this.nativePtr, false);
      return;
    }
    this.needRebuild = false;
    if (this.builder !== modifier.applyContent()) {
      this.needRebuild = true;
    }
    this.builder = modifier.applyContent();
    this.modifier = modifier;
    getUINativeModule().checkbox.setContentModifierBuilder(this.nativePtr, this);
  }
  makeContentModifierNode(context: UIContext, checkBoxConfiguration: CheckBoxConfiguration): FrameNode | null {
    checkBoxConfiguration.contentModifier = this.modifier;
    if (isUndefined(this.checkboxNode) || this.needRebuild) {
      const xNode = globalThis.requireNapi('arkui.node');
      this.checkboxNode = new xNode.BuilderNode(context);
      this.checkboxNode.build(this.builder, checkBoxConfiguration);
      this.needRebuild = false;
    } else {
      this.checkboxNode.update(checkBoxConfiguration);
    }
    return this.checkboxNode.getFrameNode();
  }
  onChange(callback:OnCheckboxChangeCallback):this{
    modifierWithKey(this._modifiersWithKeys, CheckBoxOnChangeModifier.identity,CheckBoxOnChangeModifier, callback);
    return this;
  }
}

class CheckboxOptionsModifier extends ModifierWithKey<CheckboxOptions> {
  constructor(value: CheckboxOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('checkBoxOptions');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().checkbox.setCheckboxOptions(node, undefined, undefined);
    } else {
      getUINativeModule().checkbox.setCheckboxOptions(node, this.value.name, this.value.group);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.name, this.value.name) ||
      !isBaseOrResourceEqual(this.stageValue.group, this.value.group);
  }
}

class CheckBoxResponseRegionModifier extends ModifierWithKey<Array<Rectangle> | Rectangle> {
  constructor(value: Array<Rectangle> | Rectangle) {
    super(value);
  }
  static identity = Symbol('responseRegion');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().checkbox.resetCheckboxResponseRegion(node);
    } else {
      let responseRegion: (number | string | Resource)[] = [];
      if (Array.isArray(this.value)) {
        for (let i = 0; i < this.value.length; i++) {
          responseRegion.push(this.value[i].x ?? 'PLACEHOLDER');
          responseRegion.push(this.value[i].y ?? 'PLACEHOLDER');
          responseRegion.push(this.value[i].width ?? 'PLACEHOLDER');
          responseRegion.push(this.value[i].height ?? 'PLACEHOLDER');
        }
      } else {
        responseRegion.push(this.value.x ?? 'PLACEHOLDER');
        responseRegion.push(this.value.y ?? 'PLACEHOLDER');
        responseRegion.push(this.value.width ?? 'PLACEHOLDER');
        responseRegion.push(this.value.height ?? 'PLACEHOLDER');
      }
      getUINativeModule().checkbox.setCheckboxResponseRegion(node, responseRegion, responseRegion.length);
    }
  }

  checkObjectDiff(): boolean {
    if (Array.isArray(this.value) && Array.isArray(this.stageValue)) {
      if (this.value.length !== this.stageValue.length) {
        return true;
      } else {
        for (let i = 0; i < this.value.length; i++) {
          if (!(isBaseOrResourceEqual(this.stageValue[i].x, this.value[i].x) &&
            isBaseOrResourceEqual(this.stageValue[i].y, this.value[i].y) &&
            isBaseOrResourceEqual(this.stageValue[i].width, this.value[i].width) &&
            isBaseOrResourceEqual(this.stageValue[i].height, this.value[i].height)
          )) {
            return true;
          }
        }
        return false;
      }
    } else if (!Array.isArray(this.value) && !Array.isArray(this.stageValue)) {
      return (!(isBaseOrResourceEqual(this.stageValue.x, this.value.x) &&
        isBaseOrResourceEqual(this.stageValue.y, this.value.y) &&
        isBaseOrResourceEqual(this.stageValue.width, this.value.width) &&
        isBaseOrResourceEqual(this.stageValue.height, this.value.height)
      ));
    } else {
      return true;
    }
  }
}

class CheckBoxContentModifier extends ModifierWithKey<ContentModifier<CheckBoxConfiguration>> {
  constructor(value: ContentModifier<CheckBoxConfiguration>) {
    super(value);
  }
  static identity: Symbol = Symbol('checkBoxContentModifier');
  applyPeer(node: KNode, reset: boolean, component: ArkComponent): void {
    let checkboxComponent = component as ArkCheckboxComponent;
    checkboxComponent.setContentModifier(this.value);
  }
}

class CheckBoxShapeModifier extends ModifierWithKey<CheckBoxShape> {
  constructor(value: CheckBoxShape) {
    super(value);
  }
  static identity: Symbol = Symbol('checkboxShape');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().checkbox.resetCheckboxShape(node);
    } else {
      getUINativeModule().checkbox.setCheckboxShape(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class CheckBoxSizeModifier extends ModifierWithKey<SizeOptions> {
  constructor(value: SizeOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('size');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().checkbox.resetCheckboxSize(node);
    } else {
      getUINativeModule().checkbox.setCheckboxSize(node, this.value.width, this.value.height);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.width, this.value.width) ||
      !isBaseOrResourceEqual(this.stageValue.height, this.value.height);
  }
}

class CheckBoxPaddingModifier extends ModifierWithKey<ArkPadding> {
  constructor(value: ArkPadding) {
    super(value);
  }
  static identity: Symbol = Symbol('padding');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().checkbox.resetCheckboxPadding(node);
    } else {
      getUINativeModule().checkbox.setCheckboxPadding(node, this.value.top,
        this.value.right, this.value.bottom, this.value.left);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.top, this.value.top) ||
      !isBaseOrResourceEqual(this.stageValue.right, this.value.right) ||
      !isBaseOrResourceEqual(this.stageValue.bottom, this.value.bottom) ||
      !isBaseOrResourceEqual(this.stageValue.left, this.value.left);
  }
}

class CheckboxMarkModifier extends ModifierWithKey<MarkStyle> {
  constructor(value: MarkStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('checkboxMark');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().checkbox.resetMark(node);
    } else {
      getUINativeModule().checkbox.setMark(node, this.value?.strokeColor, this.value?.size, this.value?.strokeWidth);
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
      getUINativeModule().checkbox.resetSelect(node);
    } else {
      getUINativeModule().checkbox.setSelect(node, this.value);
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
      getUINativeModule().checkbox.resetHeight(node);
    } else {
      getUINativeModule().checkbox.setHeight(node, this.value);
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
      getUINativeModule().checkbox.resetWidth(node);
    } else {
      getUINativeModule().checkbox.setWidth(node, this.value);
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
      getUINativeModule().checkbox.resetSelectedColor(node);
    } else {
      getUINativeModule().checkbox.setSelectedColor(node, this.value);
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
      getUINativeModule().checkbox.resetUnSelectedColor(node);
    } else {
      getUINativeModule().checkbox.setUnSelectedColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class CheckBoxOnChangeModifier extends ModifierWithKey<OnCheckboxChangeCallback>{
  constructor(value: OnCheckboxChangeCallback){
    super(value);
  }
  static identity: Symbol = Symbol('CheckboxOnchange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().checkbox.resetOnChange(node);
    } else {
      getUINativeModule().checkbox.setOnChange(node, this.value);
    }
  }
}

// @ts-ignore
globalThis.Checkbox.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkCheckboxComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.CheckboxModifier(nativePtr, classType);
  });
};

// @ts-ignore
globalThis.Checkbox.contentModifier = function (modifier: ContentModifier<CheckBoxConfiguration>): void {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkCheckboxComponent(nativeNode);
  });
  component.setContentModifier(modifier);
};

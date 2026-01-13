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
class CheckboxGroupSelectAllModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().checkboxgroup.resetCheckboxGroupSelectAll(node);
    }
    else {
      getUINativeModule().checkboxgroup.setCheckboxGroupSelectAll(node, this.value);
    }
  }
}
CheckboxGroupSelectAllModifier.identity = Symbol('checkboxgroupSelectAll');
class CheckboxGroupSelectedColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().checkboxgroup.resetCheckboxGroupSelectedColor(node);
    }
    else {
      getUINativeModule().checkboxgroup.setCheckboxGroupSelectedColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
CheckboxGroupSelectedColorModifier.identity = Symbol('checkboxgroupSelectedColor');
class CheckboxGroupUnselectedColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().checkboxgroup.resetCheckboxGroupUnSelectedColor(node);
    }
    else {
      getUINativeModule().checkboxgroup.setCheckboxGroupUnSelectedColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
CheckboxGroupUnselectedColorModifier.identity = Symbol('checkboxgroupUnselectedColor');
class CheckboxGroupMarkModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c;
    if (reset) {
      getUINativeModule().checkboxgroup.resetCheckboxGroupMark(node);
    }
    else {
      getUINativeModule().checkboxgroup.setCheckboxGroupMark(node, (_a = this.value) === null ||
      _a === void 0 ? void 0 : _a.strokeColor, (_b = this.value) === null ||
      _b === void 0 ? void 0 : _b.size, (_c = this.value) === null ||
      _c === void 0 ? void 0 : _c.strokeWidth);
    }
  }
  checkObjectDiff() {
    let colorEQ = isBaseOrResourceEqual(this.stageValue.strokeColor, this.value.strokeColor);
    let sizeEQ = isBaseOrResourceEqual(this.stageValue.size, this.value.size);
    let widthEQ = isBaseOrResourceEqual(this.stageValue.strokeWidth, this.value.strokeWidth);
    return !colorEQ || !sizeEQ || !widthEQ;
  }
}
CheckboxGroupMarkModifier.identity = Symbol('checkboxgroupMark');
class CheckboxGroupOnChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().checkboxgroup.resetCheckboxGroupOnChange(node);
    }
    else {
      getUINativeModule().checkboxgroup.setCheckboxGroupOnChange(node, this.value);
    }
  }
}
CheckboxGroupOnChangeModifier.identity = Symbol('checkboxGroupOnChange');

class CheckboxGroupWidthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().checkboxgroup.resetCheckboxGroupWidth(node);
    }
    else {
      getUINativeModule().checkboxgroup.setCheckboxGroupWidth(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
CheckboxGroupWidthModifier.identity = Symbol('checkboxGroupWidth');
class CheckboxGroupSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().checkboxgroup.resetCheckboxGroupSize(node);
    }
    else {
      getUINativeModule().checkboxgroup.setCheckboxGroupSize(node, this.value.width, this.value.height);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.width, this.value.width) ||
      !isBaseOrResourceEqual(this.stageValue.height, this.value.height);
  }
}
CheckboxGroupSizeModifier.identity = Symbol('checkboxGroupSize');
class CheckboxGroupHeightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().checkboxgroup.resetCheckboxGroupHeight(node);
    }
    else {
      getUINativeModule().checkboxgroup.setCheckboxGroupHeight(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
CheckboxGroupHeightModifier.identity = Symbol('checkboxGroupHeight');
class CheckboxGroupStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
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
CheckboxGroupStyleModifier.identity = Symbol('checkboxgroupStyle');
class ArkCheckboxGroupComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  allowChildCount() {
    return 0;
  }
  initialize(value) {
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
  selectAll(value) {
    modifierWithKey(this._modifiersWithKeys, CheckboxGroupSelectAllModifier.identity, CheckboxGroupSelectAllModifier, value);
    return this;
  }
  selectedColor(value) {
    modifierWithKey(this._modifiersWithKeys, CheckboxGroupSelectedColorModifier.identity, CheckboxGroupSelectedColorModifier, value);
    return this;
  }
  unselectedColor(value) {
    modifierWithKey(this._modifiersWithKeys, CheckboxGroupUnselectedColorModifier.identity, CheckboxGroupUnselectedColorModifier, value);
    return this;
  }
  mark(value) {
    modifierWithKey(this._modifiersWithKeys, CheckboxGroupMarkModifier.identity, CheckboxGroupMarkModifier, value);
    return this;
  }
  onChange(callback) {
    modifierWithKey(this._modifiersWithKeys, CheckboxGroupOnChangeModifier.identity, CheckboxGroupOnChangeModifier, callback);
    return this;
  }
  size(value) {
    modifierWithKey(this._modifiersWithKeys, CheckboxGroupSizeModifier.identity, CheckboxGroupSizeModifier, value);
    return this;
  }
  width(value) {
    modifierWithKey(this._modifiersWithKeys, CheckboxGroupWidthModifier.identity, CheckboxGroupWidthModifier, value);
    return this;
  }
  height(value) {
    modifierWithKey(this._modifiersWithKeys, CheckboxGroupHeightModifier.identity, CheckboxGroupHeightModifier, value);
    return this;
  }
  checkboxShape(value) {
    modifierWithKey(this._modifiersWithKeys, CheckboxGroupStyleModifier.identity, CheckboxGroupStyleModifier, value);
    return this;
  }
  setContentModifier(modifier) {
    if (modifier === undefined || modifier === null) {
      getUINativeModule().checkboxgroup.setContentModifierBuilder(this.nativePtr, false);
      this.builder = undefined;
      this.modifier = undefined;
      return;
    }
    this.needRebuild = false;
    const appliedContent = modifier.applyContent();
    if (this.builder !== appliedContent) {
      this.needRebuild = true;
    }
    this.builder = appliedContent;
    this.modifier = modifier;
    getUINativeModule().checkboxgroup.setContentModifierBuilder(this.nativePtr, this);
  }
  makeContentModifierNode(context, checkBoxGroupConfiguration) {
    checkBoxGroupConfiguration.contentModifier = this.modifier;
    if (this.checkboxgroupNode === undefined || this.needRebuild) {
      if (this.checkboxgroupNode !== undefined) {
        this.checkboxgroupNode = null;
      }
      const xNode = globalThis.requireNapi('arkui.node');
      this.checkboxgroupNode = new xNode.BuilderNode(context);
      this.checkboxgroupNode.build(this.builder, checkBoxGroupConfiguration);
      this.needRebuild = false;
    } else {
      this.checkboxgroupNode.update(checkBoxGroupConfiguration);
    }
    return this.checkboxgroupNode.getFrameNode();
  }
}

class CheckBoxGroupOptionsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().checkboxgroup.setCheckboxGroupOptions(node, undefined);
    } else {
      getUINativeModule().checkboxgroup.setCheckboxGroupOptions(node, this.value.group);
    }
  }

  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.group, this.value.group);
  }
}
CheckBoxGroupOptionsModifier.identity = Symbol('checkBoxGroupOptions');

class CheckBoxGroupContentModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset, component) {
    let checkboxgroupComponent = component;
    checkboxgroupComponent.setContentModifier(this.value);
  }
}
CheckBoxGroupContentModifier.identity = Symbol('checkBoxGroupContentModifier');

class JSCheckboxGroup extends JSViewAbstract {
  static create(params) {
    getUINativeModule().checkboxgroup.create(params);
  }
  static allowChildCount() {
    return 0;
  }
  static selectAll(value, callback) {
    getUINativeModule().checkboxgroup.setCheckboxGroupSelectAll(true, value, callback);
  }
  static onChange(value) {
    getUINativeModule().checkboxgroup.setCheckboxGroupOnChange(true, value);
  }
  static selectedColor(value) {
    getUINativeModule().checkboxgroup.setCheckboxGroupSelectedColor(true, value);
  }
  static unselectedColor(value) {
    getUINativeModule().checkboxgroup.setCheckboxGroupUnSelectedColor(true, value);
  }
  static mark(value) {
    getUINativeModule().checkboxgroup.setCheckboxGroupMark(true, value);
  }
  static responseRegion(value) {
    getUINativeModule().checkboxgroup.setCheckboxGroupResponseRegion(true, value);
  }
  static size(value) {
    getUINativeModule().checkboxgroup.setCheckboxGroupSize(true, value);
  
  }
  static padding(value) {
    getUINativeModule().checkboxgroup.setCheckboxGroupPadding(true, value);  
  }
  static checkboxShape(value) {
    getUINativeModule().checkboxgroup.setCheckboxGroupStyle(true, value);
  }
  static attributeModifier(modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkCheckboxGroupComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.CheckboxGroupModifier(nativePtr, classType);
    });
  }
  static contentModifier(modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
      return createComponent(nativeNode, 'checkboxgroup');
    });
    component.setContentModifier(modifier);
  }
  static onClick(value) {
    __Common__.onClick(value);
  }
  static onTouch(value) {
    __Common__.onTouch(value);
  }
  static onKeyEvent(value) {
    __Common__.onKeyEvent(value);
  }
  static onDeleteEvent(value) {
    __Common__.onDeleteEvent(value);
  }
  static onAttach(value) {
    __Common__.onAttach(value);
  }
  static onAppear(value) {
    __Common__.onAppear(value);
  }
  static onDetach(value) {
    __Common__.onAttach(value);
  }
  static onDisAppear(value) {
    __Common__.onDisAppear(value);
  }
}

function createComponent(nativePtr, classType) {
  return new ArkCheckboxGroupComponent(nativePtr, classType);
}

function exportComponent() {
  globalThis.ArkCheckboxGroupComponent = ArkCheckboxGroupComponent;
}

function exportView() {
  globalThis.CheckboxGroup = JSCheckboxGroup;
}

export default { ArkCheckboxGroupComponent, createComponent, exportComponent, exportView };
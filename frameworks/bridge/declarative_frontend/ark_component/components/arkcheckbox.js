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
class ArkCheckboxComponent extends ArkComponent {
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
      modifierWithKey(this._modifiersWithKeys, CheckboxOptionsModifier.identity, CheckboxOptionsModifier, value[0]);
    } else {
      modifierWithKey(this._modifiersWithKeys, CheckboxOptionsModifier.identity, CheckboxOptionsModifier, undefined);
    }
    return this;
  }
  shape(value) {
    modifierWithKey(this._modifiersWithKeys, CheckBoxShapeModifier.identity, CheckBoxShapeModifier, value);
    return this;
  }
  width(value) {
    modifierWithKey(this._modifiersWithKeys, CheckboxWidthModifier.identity, CheckboxWidthModifier, value);
    return this;
  }
  height(value) {
    modifierWithKey(this._modifiersWithKeys, CheckboxHeightModifier.identity, CheckboxHeightModifier, value);
    return this;
  }
  select(value) {
    modifierWithKey(this._modifiersWithKeys, CheckboxSelectModifier.identity, CheckboxSelectModifier, value);
    return this;
  }
  selectedColor(value) {
    modifierWithKey(this._modifiersWithKeys, CheckboxSelectedColorModifier.identity, CheckboxSelectedColorModifier, value);
    return this;
  }
  unselectedColor(value) {
    modifierWithKey(this._modifiersWithKeys, CheckboxUnselectedColorModifier.identity, CheckboxUnselectedColorModifier, value);
    return this;
  }
  mark(value) {
    modifierWithKey(this._modifiersWithKeys, CheckboxMarkModifier.identity, CheckboxMarkModifier, value);
    return this;
  }
  padding(value) {
    let arkValue = new ArkPadding();
    if (value !== null && value !== undefined) {
      if (isLengthType(value) || isResource(value)) {
        arkValue.top = value;
        arkValue.right = value;
        arkValue.bottom = value;
        arkValue.left = value;
      }
      else {
        arkValue.top = value.top;
        arkValue.right = value.right;
        arkValue.bottom = value.bottom;
        arkValue.left = value.left;
      }
      modifierWithKey(this._modifiersWithKeys, CheckBoxPaddingModifier.identity, CheckBoxPaddingModifier, arkValue);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, CheckBoxPaddingModifier.identity, CheckBoxPaddingModifier, undefined);
    }
    return this;
  }
  size(value) {
    modifierWithKey(this._modifiersWithKeys, CheckBoxSizeModifier.identity, CheckBoxSizeModifier, value);
    return this;
  }
  responseRegion(value) {
    modifierWithKey(this._modifiersWithKeys, CheckBoxResponseRegionModifier.identity, CheckBoxResponseRegionModifier, value);
    return this;
  }
  margin(value) {
    let arkValue = new ArkPadding();
    if (value !== null && value !== undefined) {
      if (isLengthType(value) || isResource(value)) {
        arkValue.top = value;
        arkValue.right = value;
        arkValue.bottom = value;
        arkValue.left = value;
      }
      else {
        arkValue.top = value.top;
        arkValue.bottom = value.bottom;
        if (Object.keys(value).indexOf('right') >= 0) {
          arkValue.right = value.right;
        }
        if (Object.keys(value).indexOf('end') >= 0) {
          arkValue.right = value.end;
        }
        if (Object.keys(value).indexOf('left') >= 0) {
          arkValue.left = value.left;
        }
        if (Object.keys(value).indexOf('start') >= 0) {
          arkValue.left = value.start;
        }
      }
      modifierWithKey(this._modifiersWithKeys, CheckboxMarginModifier.identity, CheckboxMarginModifier, arkValue);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, CheckboxMarginModifier.identity, CheckboxMarginModifier, undefined);
    }
    return this;
  }
  contentModifier(value) {
    modifierWithKey(this._modifiersWithKeys, CheckBoxContentModifier.identity, CheckBoxContentModifier, value);
    return this;
  }
  setContentModifier(modifier) {
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
  makeContentModifierNode(context, checkBoxConfiguration) {
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
  onChange(callback) {
    modifierWithKey(this._modifiersWithKeys, CheckBoxOnChangeModifier.identity, CheckBoxOnChangeModifier, callback);
    return this;
  }
}
class CheckboxOptionsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().checkbox.setCheckboxOptions(node, undefined, undefined);
    } else {
      getUINativeModule().checkbox.setCheckboxOptions(node, this.value.name, this.value?.group);
    }
  }

  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.name, this.value.name) ||
      !isBaseOrResourceEqual(this.stageValue.group, this.value.group);
  }
}
CheckboxOptionsModifier.identity = Symbol('checkBoxOptions');
class CheckBoxResponseRegionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c, _d, _e, _f, _g, _h;
    if (reset) {
      getUINativeModule().checkbox.resetCheckboxResponseRegion(node);
    }
    else {
      let responseRegion = [];
      if (Array.isArray(this.value)) {
        for (let i = 0; i < this.value.length; i++) {
          responseRegion.push((_a = this.value[i].x) !== null && _a !== void 0 ? _a : 'PLACEHOLDER');
          responseRegion.push((_b = this.value[i].y) !== null && _b !== void 0 ? _b : 'PLACEHOLDER');
          responseRegion.push((_c = this.value[i].width) !== null && _c !== void 0 ? _c : 'PLACEHOLDER');
          responseRegion.push((_d = this.value[i].height) !== null && _d !== void 0 ? _d : 'PLACEHOLDER');
        }
      }
      else {
        responseRegion.push((_e = this.value.x) !== null && _e !== void 0 ? _e : 'PLACEHOLDER');
        responseRegion.push((_f = this.value.y) !== null && _f !== void 0 ? _f : 'PLACEHOLDER');
        responseRegion.push((_g = this.value.width) !== null && _g !== void 0 ? _g : 'PLACEHOLDER');
        responseRegion.push((_h = this.value.height) !== null && _h !== void 0 ? _h : 'PLACEHOLDER');
      }
      getUINativeModule().checkbox.setCheckboxResponseRegion(node, responseRegion, responseRegion.length);
    }
  }
  checkObjectDiff() {
    if (Array.isArray(this.value) && Array.isArray(this.stageValue)) {
      if (this.value.length !== this.stageValue.length) {
        return true;
      }
      else {
        for (let i = 0; i < this.value.length; i++) {
          if (!(isBaseOrResourceEqual(this.stageValue[i].x, this.value[i].x) &&
            isBaseOrResourceEqual(this.stageValue[i].y, this.value[i].y) &&
            isBaseOrResourceEqual(this.stageValue[i].width, this.value[i].width) &&
            isBaseOrResourceEqual(this.stageValue[i].height, this.value[i].height))) {
            return true;
          }
        }
        return false;
      }
    }
    else if (!Array.isArray(this.value) && !Array.isArray(this.stageValue)) {
      return (!(isBaseOrResourceEqual(this.stageValue.x, this.value.x) &&
        isBaseOrResourceEqual(this.stageValue.y, this.value.y) &&
        isBaseOrResourceEqual(this.stageValue.width, this.value.width) &&
        isBaseOrResourceEqual(this.stageValue.height, this.value.height)));
    }
    else {
      return true;
    }
  }
}
CheckBoxResponseRegionModifier.identity = Symbol('responseRegion');
class CheckboxMarginModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().checkbox.resetMargin(node);
    }
    else {
      getUINativeModule().checkbox.setMargin(node, this.value.top, this.value.right, this.value.bottom, this.value.left);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.top, this.value.top) ||
      !isBaseOrResourceEqual(this.stageValue.right, this.value.right) ||
      !isBaseOrResourceEqual(this.stageValue.bottom, this.value.bottom) ||
      !isBaseOrResourceEqual(this.stageValue.left, this.value.left);
  }
}
CheckboxMarginModifier.identity = Symbol('checkboxMargin');
class CheckBoxContentModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset, component) {
    let checkboxComponent = component;
    checkboxComponent.setContentModifier(this.value);
  }
}
CheckBoxContentModifier.identity = Symbol('checkBoxContentModifier');
class CheckBoxShapeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().checkbox.resetCheckboxShape(node);
    } else {
      getUINativeModule().checkbox.setCheckboxShape(node, this.value);
    }
  }

  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
CheckBoxShapeModifier.identity = Symbol('checkboxShape');
class CheckBoxSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().checkbox.resetCheckboxSize(node);
    }
    else {
      getUINativeModule().checkbox.setCheckboxSize(node, this.value.width, this.value.height);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.width, this.value.width) ||
      !isBaseOrResourceEqual(this.stageValue.height, this.value.height);
  }
}
CheckBoxSizeModifier.identity = Symbol('size');
class CheckBoxPaddingModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().checkbox.resetCheckboxPadding(node);
    }
    else {
      getUINativeModule().checkbox.setCheckboxPadding(node, this.value.top, this.value.right, this.value.bottom, this.value.left);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.top, this.value.top) ||
      !isBaseOrResourceEqual(this.stageValue.right, this.value.right) ||
      !isBaseOrResourceEqual(this.stageValue.bottom, this.value.bottom) ||
      !isBaseOrResourceEqual(this.stageValue.left, this.value.left);
  }
}
CheckBoxPaddingModifier.identity = Symbol('padding');
class CheckboxMarkModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c;
    if (reset) {
      getUINativeModule().checkbox.resetMark(node);
    }
    else {
      getUINativeModule().checkbox.setMark(node, (_a = this.value) === null ||
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
CheckboxMarkModifier.identity = Symbol('checkboxMark');
class CheckboxSelectModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().checkbox.resetSelect(node);
    }
    else {
      getUINativeModule().checkbox.setSelect(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
CheckboxSelectModifier.identity = Symbol('checkboxSelect');
class CheckboxHeightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().checkbox.resetCheckboxHeight(node);
    }
    else {
      getUINativeModule().checkbox.setCheckboxHeight(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
CheckboxHeightModifier.identity = Symbol('checkboxHeight');
class CheckboxWidthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().checkbox.resetCheckboxWidth(node);
    }
    else {
      getUINativeModule().checkbox.setCheckboxWidth(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
CheckboxWidthModifier.identity = Symbol('checkboxWidth');
class CheckboxSelectedColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().checkbox.resetSelectedColor(node);
    }
    else {
      getUINativeModule().checkbox.setSelectedColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
CheckboxSelectedColorModifier.identity = Symbol('checkboxSelectedColor');
class CheckboxUnselectedColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().checkbox.resetUnSelectedColor(node);
    }
    else {
      getUINativeModule().checkbox.setUnSelectedColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
CheckboxUnselectedColorModifier.identity = Symbol('checkboxUnselectedColor');
class CheckBoxOnChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().checkbox.resetCheckboxOnChange(node);
    } else {
      getUINativeModule().checkbox.setCheckboxOnChange(node, this.value);
    }
  }
}
CheckBoxOnChangeModifier.identity = Symbol('checkboxOnChange');

class JSCheckbox extends JSViewAbstract {
  static create(params) {
    getUINativeModule().checkbox.create(params);
  }
  static allowChildCount() {
    return 0;
  }
  static shape(value) {
    getUINativeModule().checkbox.setCheckboxShape(true, value);
  }
  static select(value, callback) {
    getUINativeModule().checkbox.setSelect(true, value, callback);
  }
  static selectedColor(value) {
    getUINativeModule().checkbox.setSelectedColor(true, value);
  }
  static unselectedColor(value) {
    getUINativeModule().checkbox.setUnSelectedColor(true, value);
  }
  static mark(value) {
    getUINativeModule().checkbox.setMark(true, value);
  }
  static padding(value) {
    getUINativeModule().checkbox.setCheckboxPadding(true, value);
  }
  static responseRegion(value) {
    getUINativeModule().checkbox.setCheckboxResponseRegion(true, value);
  }
  static margin(value) {
    getUINativeModule().checkbox.setMargin(true, value);

  }
  static onChange(callback) {
    getUINativeModule().checkbox.setCheckboxOnChange(true, callback);
  }
  static attributeModifier(modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkCheckboxComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.CheckboxModifier(nativePtr, classType);
    });
  }
  static contentModifier(modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
      return createComponent(nativeNode, 'checkbox');
    });
    component.setContentModifier(modifier);
  }  
  static onClick(value) {
    __Common__.onClick(value);
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
  static onTouch(value) {
    __Common__.onTouch(value);
  }
}

function createComponent(nativePtr, classType) {
  return new ArkCheckboxComponent(nativePtr, classType);
}

function exportComponent() {
  globalThis.ArkCheckboxComponent = ArkCheckboxComponent;
}

function exportView() {
  globalThis.Checkbox = JSCheckbox;
}

export default { ArkCheckboxComponent, createComponent, exportComponent, exportView };
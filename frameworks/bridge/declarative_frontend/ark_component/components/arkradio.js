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
class ArkRadioComponent extends ArkComponent {
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
      modifierWithKey(this._modifiersWithKeys, RadioOptionsModifier.identity, RadioOptionsModifier, value[0]);
    } else {
      modifierWithKey(this._modifiersWithKeys, RadioOptionsModifier.identity, RadioOptionsModifier, undefined);
    }
    return this;
  }
  checked(value) {
    modifierWithKey(this._modifiersWithKeys, RadioCheckedModifier.identity, RadioCheckedModifier, value);
    return this;
  }
  onChange(callback) {
    modifierWithKey(this._modifiersWithKeys, RadioOnChangeModifier.identity, RadioOnChangeModifier, callback);
    return this;
  }
  radioStyle(value) {
    modifierWithKey(this._modifiersWithKeys, RadioStyleModifier.identity, RadioStyleModifier, value);
    return this;
  }
  width(value) {
    modifierWithKey(this._modifiersWithKeys, RadioWidthModifier.identity, RadioWidthModifier, value);
    return this;
  }
  height(value) {
    modifierWithKey(this._modifiersWithKeys, RadioHeightModifier.identity, RadioHeightModifier, value);
    return this;
  }
  size(value) {
    modifierWithKey(this._modifiersWithKeys, RadioSizeModifier.identity, RadioSizeModifier, value);
    return this;
  }
  hoverEffect(value) {
    modifierWithKey(this._modifiersWithKeys, RadioHoverEffectModifier.identity, RadioHoverEffectModifier, value);
    return this;
  }
  padding(value) {
    modifierWithKey(this._modifiersWithKeys, RadioPaddingModifier.identity, RadioPaddingModifier, value);
    return this;
  }
  responseRegion(value) {
    modifierWithKey(this._modifiersWithKeys, RadioResponseRegionModifier.identity, RadioResponseRegionModifier, value);
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
      modifierWithKey(this._modifiersWithKeys, RadioMarginModifier.identity, RadioMarginModifier, arkValue);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, RadioMarginModifier.identity, RadioMarginModifier, undefined);
    }
    return this;
  }
  contentModifier(value) {
    modifierWithKey(this._modifiersWithKeys, RadioContentModifier.identity, RadioContentModifier, value);
    return this;
  }
  setContentModifier(modifier) {
    if (modifier === undefined || modifier === null) {
      getUINativeModule().radio.setContentModifierBuilder(this.nativePtr, false);
      return;
    }
    this.needRebuild = false;
    if (this.builder !== modifier.applyContent()) {
      this.needRebuild = true;
    }
    this.builder = modifier.applyContent();
    this.modifier = modifier;
    getUINativeModule().radio.setContentModifierBuilder(this.nativePtr, this);
  }
  makeContentModifierNode(context, radioConfiguration) {
    radioConfiguration.contentModifier = this.modifier;
    if (isUndefined(this.radioNode) || this.needRebuild) {
      const xNode = globalThis.requireNapi('arkui.node');
      this.radioNode = new xNode.BuilderNode(context);
      this.radioNode.build(this.builder, radioConfiguration);
      this.needRebuild = false;
    } else {
      this.radioNode.update(radioConfiguration);
    }
    return this.radioNode.getFrameNode();
  }
}
class RadioOptionsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().radio.setRadioOptions(node, undefined, undefined, undefined);
    } else {
      getUINativeModule().radio.setRadioOptions(node, this.value.value, this.value.group, this.value.indicatorType);
    }
  }

  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.value, this.value.value) ||
      !isBaseOrResourceEqual(this.stageValue.group, this.value.group) ||
      !isBaseOrResourceEqual(this.stageValue.indicatorType, this.value.indicatorType);
  }
}
RadioOptionsModifier.identity = Symbol('radioOptions');
class RadioCheckedModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().radio.resetRadioChecked(node);
    }
    else {
      getUINativeModule().radio.setRadioChecked(node, this.value);
    }
  }
}
RadioCheckedModifier.identity = Symbol('radioChecked');
class RadioOnChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().radio.resetRadioOnChange(node);
    }
    else {
      getUINativeModule().radio.setRadioOnChange(node, this.value);
    }
  }
}
RadioOnChangeModifier.identity = Symbol('radioOnChange');
class RadioStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().radio.resetRadioStyle(node);
    }
    else {
      getUINativeModule().radio.setRadioStyle(node, this.value.checkedBackgroundColor, this.value.uncheckedBorderColor, this.value.indicatorColor);
    }
  }
  checkObjectDiff() {
    let checkedBackgroundColorEQ = isBaseOrResourceEqual(this.stageValue.checkedBackgroundColor, this.value.checkedBackgroundColor);
    let uncheckedBorderColorEQ = isBaseOrResourceEqual(this.stageValue.uncheckedBorderColor, this.value.uncheckedBorderColor);
    let indicatorColorEQ = isBaseOrResourceEqual(this.stageValue.indicatorColor, this.value.indicatorColor);
    return !checkedBackgroundColorEQ ||
      !uncheckedBorderColorEQ ||
      !indicatorColorEQ;
  }
}
RadioStyleModifier.identity = Symbol('radioStyle');
class RadioWidthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().radio.resetRadioWidth(node);
    }
    else {
      getUINativeModule().radio.setRadioWidth(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
RadioWidthModifier.identity = Symbol('radioWidth');
class RadioHeightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().radio.resetRadioHeight(node);
    }
    else {
      getUINativeModule().radio.setRadioHeight(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
RadioHeightModifier.identity = Symbol('radioHeight');
class RadioSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().radio.resetRadioSize(node);
    }
    else {
      getUINativeModule().radio.setRadioSize(node, this.value.width, this.value.height);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.width, this.value.width) ||
      !isBaseOrResourceEqual(this.stageValue.height, this.value.height);
  }
}
RadioSizeModifier.identity = Symbol('radioSize');
class RadioHoverEffectModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().radio.resetRadioHoverEffect(node);
    }
    else {
      getUINativeModule().radio.setRadioHoverEffect(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
RadioHoverEffectModifier.identity = Symbol('radioHoverEffect');
class RadioPaddingModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().radio.resetRadioPadding(node);
    }
    else {
      let paddingTop;
      let paddingRight;
      let paddingBottom;
      let paddingLeft;
      if (this.value !== null && this.value !== undefined) {
        if (isLengthType(this.value) || isResource(this.value)) {
          paddingTop = this.value;
          paddingRight = this.value;
          paddingBottom = this.value;
          paddingLeft = this.value;
        }
        else {
          paddingTop = this.value.top;
          paddingRight = this.value.right;
          paddingBottom = this.value.bottom;
          paddingLeft = this.value.left;
        }
      }
      getUINativeModule().radio.setRadioPadding(node, paddingTop, paddingRight, paddingBottom, paddingLeft);
    }
  }
  checkObjectDiff() {
    if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !(this.stageValue.left === this.value.left &&
        this.stageValue.right === this.value.right &&
        this.stageValue.top === this.value.top &&
        this.stageValue.bottom === this.value.bottom);
    } else {
      return true;
    }
  }
}
RadioPaddingModifier.identity = Symbol('radioPadding');
class RadioResponseRegionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c, _d, _e, _f, _g, _h;
    if (reset) {
      getUINativeModule().radio.resetRadioResponseRegion(node);
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
      getUINativeModule().radio.setRadioResponseRegion(node, responseRegion, responseRegion.length);
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
RadioResponseRegionModifier.identity = Symbol('radioResponseRegion');
class RadioMarginModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().radio.resetMargin(node);
    }
    else {
      getUINativeModule().radio.setMargin(node, this.value.top, this.value.right, this.value.bottom, this.value.left);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.top, this.value.top) ||
      !isBaseOrResourceEqual(this.stageValue.right, this.value.right) ||
      !isBaseOrResourceEqual(this.stageValue.bottom, this.value.bottom) ||
      !isBaseOrResourceEqual(this.stageValue.left, this.value.left);
  }
}
RadioMarginModifier.identity = Symbol('radioMargin');
class RadioContentModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset, component) {
    let radioComponent = component;
    radioComponent.setContentModifier(this.value);
  }
}
RadioContentModifier.identity = Symbol('radioContentModifier');

class JSRadio extends JSViewAbstract {
  static create(params) {
    getUINativeModule().radio.create(params);
  }
  static checked(checked, callback) {
    getUINativeModule().radio.setRadioChecked(true, checked, callback);
  }
  static size(size) {
    JSViewAbstract.width(size?.width);
    JSViewAbstract.height(size?.height);
  }
  static padding(padding) {
    getUINativeModule().radio.setRadioPadding(true, padding);
  }
  static margin(margin) {
    getUINativeModule().radio.setMargin(true, margin);
    JSViewAbstract.margin(margin);
  }
  static radioStyle(radioStyle) {
    getUINativeModule().radio.setRadioStyle(true, radioStyle);
  }
  static responseRegion(responseRegion) {
    getUINativeModule().radio.setRadioResponseRegion(true, responseRegion);
  }
  static hoverEffect(hoverEffect) {
    getUINativeModule().radio.setRadioHoverEffect(true, hoverEffect);
  }
  static onChange(callback) {
    getUINativeModule().radio.setRadioOnChange(true, callback);
  }
  static attributeModifier(modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkRadioComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.RadioModifier(nativePtr, classType);
    });
  }
  static contentModifier(modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
      return createComponent(nativeNode, 'radio');
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
    __Common__.onDetach(value);
  }
  static onDisAppear(value) {
    __Common__.onDisAppear(value);
  }  
  static onTouch(value) {
    __Common__.onTouch(value);
  }
}

function createComponent(nativePtr, classType) {
    return new ArkRadioComponent(nativePtr, classType);
}

function exportComponent() {
    globalThis.ArkRadioComponent = ArkRadioComponent;
}

function exportView() {
    globalThis.Radio = JSRadio;
}

export default { ArkRadioComponent, createComponent, exportComponent, exportView };
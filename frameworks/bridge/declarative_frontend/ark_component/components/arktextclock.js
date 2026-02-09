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
class ArkTextClockComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  allowChildCount() {
    return 0;
  }
  initialize(value) {
    let _a, _b;
    if (value.length === 1 && isObject(value[0])) {
      if (((_a = value[0]) === null || _a === void 0 ? void 0 : _a.timeZoneOffset) !== undefined) {
        modifierWithKey(this._modifiersWithKeys, TextClockTimeZoneOffsetModifier.identity, TextClockTimeZoneOffsetModifier, value[0].timeZoneOffset);
      } else {
        modifierWithKey(this._modifiersWithKeys, TextClockTimeZoneOffsetModifier.identity, TextClockTimeZoneOffsetModifier, undefined);
      }
      if (((_b = value[0]) === null || _b === void 0 ? void 0 : _b.controller) !== undefined) {
        modifierWithKey(this._modifiersWithKeys, TextClockControllerModifier.identity, TextClockControllerModifier, value[0].controller);
      } else {
        modifierWithKey(this._modifiersWithKeys, TextClockControllerModifier.identity, TextClockControllerModifier, undefined);
      }
    }
    else {
      modifierWithKey(this._modifiersWithKeys, TextClockTimeZoneOffsetModifier.identity, TextClockTimeZoneOffsetModifier, undefined);
      modifierWithKey(this._modifiersWithKeys, TextClockControllerModifier.identity, TextClockControllerModifier, undefined);
    }
    return this;
  }
  format(value) {
    modifierWithKey(this._modifiersWithKeys, TextClockFormatModifier.identity, TextClockFormatModifier, value);
    return this;
  }
  onDateChange(event) {
    modifierWithKey(this._modifiersWithKeys, TextClockOnDateChangeModifier.identity, TextClockOnDateChangeModifier, event);
    return this;
  }
  fontColor(value) {
    modifierWithKey(this._modifiersWithKeys, TextClockFontColorModifier.identity, TextClockFontColorModifier, value);
    return this;
  }
  fontSize(value) {
    modifierWithKey(this._modifiersWithKeys, TextClockFontSizeModifier.identity, TextClockFontSizeModifier, value);
    return this;
  }
  fontStyle(value) {
    modifierWithKey(this._modifiersWithKeys, TextClockFontStyleModifier.identity, TextClockFontStyleModifier, value);
    return this;
  }
  fontWeight(value) {
    modifierWithKey(this._modifiersWithKeys, TextClockFontWeightModifier.identity, TextClockFontWeightModifier, value);
    return this;
  }
  fontFamily(value) {
    modifierWithKey(this._modifiersWithKeys, TextClockFontFamilyModifier.identity, TextClockFontFamilyModifier, value);
    return this;
  }
  textShadow(value) {
    modifierWithKey(this._modifiersWithKeys, TextClockTextShadowModifier.identity, TextClockTextShadowModifier, value);
    return this;
  }
  fontFeature(value) {
    modifierWithKey(this._modifiersWithKeys, TextClockFontFeatureModifier.identity, TextClockFontFeatureModifier, value);
    return this;
  }
  contentModifier(value) {
    modifierWithKey(this._modifiersWithKeys, TextClockContentModifier.identity, TextClockContentModifier, value);
    return this;
  }
  setContentModifier(modifier) {
    if (modifier === undefined || modifier === null) {
      getUINativeModule().textclock.setContentModifierBuilder(this.nativePtr, false);
      return;
    }
    this.needRebuild = false;
    if (this.builder !== modifier.applyContent()) {
      this.needRebuild = true;
    }
    this.builder = modifier.applyContent();
    this.modifier = modifier;
    getUINativeModule().textclock.setContentModifierBuilder(this.nativePtr, this);
  }
  makeContentModifierNode(context, textClockConfiguration) {
    textClockConfiguration.contentModifier = this.modifier;
    if (isUndefined(this.textClockNode) || this.needRebuild) {
      const xNode = globalThis.requireNapi('arkui.node');
      this.textClockNode = new xNode.BuilderNode(context);
      this.textClockNode.build(this.builder, textClockConfiguration);
      this.needRebuild = false;
    } else {
      this.textClockNode.update(textClockConfiguration);
    }
    return this.textClockNode.getFrameNode();
  }
  dateTimeOptions(value) {
    modifierWithKey(this._modifiersWithKeys, TextClockDateTimeOptionsModifier.identity, TextClockDateTimeOptionsModifier, value);
    return this;
  }
}
class TextClockOnDateChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textclock.resetTextClockOnDateChange(node);
    } else {
      getUINativeModule().textclock.setTextClockOnDateChange(node, this.value);
    }
  }
}
TextClockOnDateChangeModifier.identity = Symbol('textClockOnDateChange');
class TextClockTimeZoneOffsetModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textclock.setTextClockTimeZoneOffset(node, undefined);
    } else {
      getUINativeModule().textclock.setTextClockTimeZoneOffset(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextClockTimeZoneOffsetModifier.identity = Symbol('textClockTimeZoneOffset');
class TextClockControllerModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textclock.setTextClockController(node, undefined);
    } else {
      getUINativeModule().textclock.setTextClockController(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextClockControllerModifier.identity = Symbol('textClockController');
class TextClockFormatModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textclock.resetFormat(node);
    }
    else {
      getUINativeModule().textclock.setFormat(node, this.value);
    }
  }
}
TextClockFormatModifier.identity = Symbol('textClockFormat');
class TextClockFontColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textclock.resetFontColor(node);
    }
    else {
      getUINativeModule().textclock.setFontColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextClockFontColorModifier.identity = Symbol('textClockFontColor');
class TextClockFontSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textclock.resetFontSize(node);
    }
    else {
      getUINativeModule().textclock.setFontSize(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextClockFontSizeModifier.identity = Symbol('textClockFontSize');
class TextClockFontStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textclock.resetFontStyle(node);
    }
    else {
      getUINativeModule().textclock.setFontStyle(node, this.value);
    }
  }
}
TextClockFontStyleModifier.identity = Symbol('textClockFontStyle');
class TextClockFontWeightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textclock.resetFontWeight(node);
    }
    else {
      getUINativeModule().textclock.setFontWeight(node, this.value);
    }
  }
}
TextClockFontWeightModifier.identity = Symbol('textClockFontWeight');
class TextClockFontFamilyModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textclock.resetFontFamily(node);
    }
    else {
      getUINativeModule().textclock.setFontFamily(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextClockFontFamilyModifier.identity = Symbol('textClockFontFamily');
class TextClockFontFeatureModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textclock.resetFontFeature(node);
    }
    else {
      getUINativeModule().textclock.setFontFeature(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextClockFontFeatureModifier.identity = Symbol('textClockFontFeature');
class TextClockContentModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset, component) {
    let textClockComponent = component;
    textClockComponent.setContentModifier(this.value);
  }
}
TextClockContentModifier.identity = Symbol('textClockContentModifier');
class TextClockTextShadowModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textclock.resetTextShadow(node);
    }
    else {
      let shadow = new ArkShadowInfoToArray();
      if (!shadow.convertShadowOptions(this.value)) {
        getUINativeModule().textclock.resetTextShadow(node);
      }
      else {
        getUINativeModule().textclock.setTextShadow(node, shadow.radius, shadow.type, shadow.color,
          shadow.offsetX, shadow.offsetY, shadow.fill, shadow.radius.length);
      }
    }
  }
  checkObjectDiff() {
    let checkDiff = true;
    let arkShadow = new ArkShadowInfoToArray();
    if (Object.getPrototypeOf(this.stageValue).constructor === Object &&
      Object.getPrototypeOf(this.value).constructor === Object) {
      checkDiff = arkShadow.checkDiff(this.stageValue, this.value);
    }
    else if (Object.getPrototypeOf(this.stageValue).constructor === Array &&
      Object.getPrototypeOf(this.value).constructor === Array &&
      this.stageValue.length === this.value.length) {
      let isDiffItem = false;
      for (let i = 0; i < this.value.length; i++) {
        if (arkShadow.checkDiff(this.stageValue[i], this.value[1])) {
          isDiffItem = true;
          break;
        }
      }
      if (!isDiffItem) {
        checkDiff = false;
      }
    }
    return checkDiff;
  }
}
TextClockTextShadowModifier.identity = Symbol('textClockTextShadow');

class TextClockDateTimeOptionsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textclock.resetDateTimeOptions(node);
    }
    else {
      getUINativeModule().textclock.setDateTimeOptions(node, this.value.hour);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextClockDateTimeOptionsModifier.identity = Symbol('textClockDateTimeOptions');

class JSTextClock extends JSViewAbstract {
    static create(params) {
        getUINativeModule().textclock.create(params);
    }
    static format(value) {
        getUINativeModule().textclock.setFormat(true, value);
    }
    static onDateChange(event) {
        getUINativeModule().textclock.setTextClockOnDateChange(true, event);
    }
    static fontColor(value) {
        getUINativeModule().textclock.setFontColor(true, value);
    }
    static fontSize(value) {
        getUINativeModule().textclock.setFontSize(true, value);
    }
    static fontStyle(value) {
        getUINativeModule().textclock.setFontStyle(true, value);
    }
    static fontWeight(value) {
        getUINativeModule().textclock.setFontWeight(true, value);
    }
    static fontFamily(value) {
        getUINativeModule().textclock.setFontFamily(true, value);
    }
    static textShadow(value) {
        let shadow = new ArkShadowInfoToArray();
        if (value !== undefined && value !== null) {
            shadow.convertShadowOptions(value);
        }
        getUINativeModule().textclock.setTextShadow(true, shadow.radius, shadow.type, shadow.color,
            shadow.offsetX, shadow.offsetY, shadow.fill, shadow.radius.length);
    }
    static fontFeature(value) {
        getUINativeModule().textclock.setFontFeature(true, value);
    }
    static contentModifier(modifier) {
        const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
        let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
        let component = this.createOrGetNode(elmtId, () => {
            return createComponent(nativeNode, 'textclock');
        });
        component.setContentModifier(modifier);
    }
    static dateTimeOptions(dateTimeOptions) {
        getUINativeModule().textclock.setDateTimeOptions(true, dateTimeOptions.hour);
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
    static attributeModifier(modifier) {
      attributeModifierFunc.call(this, modifier, (nativePtr) => {
        return new ArkTextClockComponent(nativePtr);
      }, (nativePtr, classType, modifierJS) => {
        return new modifierJS.TextClockModifier(nativePtr, classType);
      });
    }
}

function createComponent(nativePtr, classType) {
    return new ArkTextClockComponent(nativePtr, classType);
}

function exportComponent() {
    globalThis.ArkTextClockComponent = ArkTextClockComponent;
}

function exportView() {
    globalThis.TextClock = JSTextClock;
}

export default { ArkTextClockComponent, createComponent, exportComponent, exportView };


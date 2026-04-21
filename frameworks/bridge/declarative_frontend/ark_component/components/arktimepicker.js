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
class ArkTimePickerComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  loop(value) {
    modifierWithKey(this._modifiersWithKeys, TimepickerLoopModifier.identity, TimepickerLoopModifier, value);
    return this;
  }
  digitalCrownSensitivity(value) {
    modifierWithKey(this._modifiersWithKeys, TimepickerDigitalCrownSensitivityModifier.identity, TimepickerDigitalCrownSensitivityModifier, value);
    return this;
  }
  useMilitaryTime(value) {
    modifierWithKey(this._modifiersWithKeys, TimepickerUseMilitaryTimeModifier.identity, TimepickerUseMilitaryTimeModifier, value);
    return this;
  }
  disappearTextStyle(value) {
    modifierWithKey(this._modifiersWithKeys, TimepickerDisappearTextStyleModifier.identity, TimepickerDisappearTextStyleModifier, value);
    return this;
  }
  textStyle(value) {
    modifierWithKey(this._modifiersWithKeys, TimepickerTextStyleModifier.identity, TimepickerTextStyleModifier, value);
    return this;
  }
  selectedTextStyle(value) {
    modifierWithKey(this._modifiersWithKeys, TimepickerSelectedTextStyleModifier.identity, TimepickerSelectedTextStyleModifier, value);
    return this;
  }
  enableCascade(value) {
    modifierWithKey(this._modifiersWithKeys, TimepickerEnableCascadeModifier.identity, TimepickerEnableCascadeModifier, value);
    return this;
  }
  onChange(callback) {
    modifierWithKey(this._modifiersWithKeys, TimepickerOnChangeModifier.identity, TimepickerOnChangeModifier, callback);
    return this;
  }
  dateTimeOptions(value) {
    modifierWithKey(this._modifiersWithKeys, TimepickerDateTimeOptionsModifier.identity, TimepickerDateTimeOptionsModifier, value);
    return this;
  }
  enableHapticFeedback(value) {
    modifierWithKey(this._modifiersWithKeys, TimepickerEnableHapticFeedbackModifier.identity, TimepickerEnableHapticFeedbackModifier, value);
    return this;
  }
}

class TimepickerDigitalCrownSensitivityModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().timePicker.resetDigitalCrownSensitivity(node);
    }
    else {
      getUINativeModule().timePicker.setDigitalCrownSensitivity(node, this.value);
    }
  }
}
TimepickerDigitalCrownSensitivityModifier.identity = Symbol('DigitalCrownSensitivity');

class TimepickerTextStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c, _d, _e, _f, _g, _h, _j, _k, _l, _m, _o, _p;
    if (reset) {
      getUINativeModule().timePicker.resetTextStyle(node);
    }
    else {
      getUINativeModule().timePicker.setTextStyle(node, (_b = (_a = this.value) === null ||
        _a === void 0 ? void 0 : _a.color) !== null && _b !== void 0 ? _b : undefined,
        (_e = (_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.font) === null ||
          _d === void 0 ? void 0 : _d.size) !== null && _e !== void 0 ? _e : undefined,
        (_h = (_g = (_f = this.value) === null || _f === void 0 ? void 0 : _f.font) === null ||
          _g === void 0 ? void 0 : _g.weight) !== null && _h !== void 0 ? _h : undefined,
        (_l = (_k = (_j = this.value) === null || _j === void 0 ? void 0 : _j.font) === null ||
          _k === void 0 ? void 0 : _k.family) !== null && _l !== void 0 ? _l : undefined,
        (_p = (_o = (_m = this.value) === null || _m === void 0 ? void 0 : _m.font) === null ||
          _o === void 0 ? void 0 : _o.style) !== null && _p !== void 0 ? _p : undefined);
    }
  }
  checkObjectDiff() {
    return true;
  }
}
TimepickerTextStyleModifier.identity = Symbol('textStyle');
class TimepickerSelectedTextStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c, _d, _e, _f, _g, _h, _j, _k, _l, _m, _o, _p;
    if (reset) {
      getUINativeModule().timePicker.resetSelectedTextStyle(node);
    }
    else {
      getUINativeModule().timePicker.setSelectedTextStyle(node, (_b = (_a = this.value) === null ||
        _a === void 0 ? void 0 : _a.color) !== null && _b !== void 0 ? _b : undefined,
        (_e = (_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.font) === null ||
          _d === void 0 ? void 0 : _d.size) !== null && _e !== void 0 ? _e : undefined,
        (_h = (_g = (_f = this.value) === null || _f === void 0 ? void 0 : _f.font) === null ||
          _g === void 0 ? void 0 : _g.weight) !== null && _h !== void 0 ? _h : undefined,
        (_l = (_k = (_j = this.value) === null || _j === void 0 ? void 0 : _j.font) === null ||
          _k === void 0 ? void 0 : _k.family) !== null && _l !== void 0 ? _l : undefined,
        (_p = (_o = (_m = this.value) === null || _m === void 0 ? void 0 : _m.font) === null ||
          _o === void 0 ? void 0 : _o.style) !== null && _p !== void 0 ? _p : undefined);
    }
  }
  checkObjectDiff() {
    return true;
  }
}
TimepickerSelectedTextStyleModifier.identity = Symbol('selectedTextStyle');
class TimepickerDisappearTextStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c, _d, _e, _f, _g, _h, _j, _k, _l, _m, _o, _p;
    if (reset) {
      getUINativeModule().timePicker.resetDisappearTextStyle(node);
    }
    else {
      getUINativeModule().timePicker.setDisappearTextStyle(node, (_b = (_a = this.value) === null ||
        _a === void 0 ? void 0 : _a.color) !== null && _b !== void 0 ? _b : undefined,
        (_e = (_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.font) === null ||
          _d === void 0 ? void 0 : _d.size) !== null && _e !== void 0 ? _e : undefined,
        (_h = (_g = (_f = this.value) === null || _f === void 0 ? void 0 : _f.font) === null ||
          _g === void 0 ? void 0 : _g.weight) !== null && _h !== void 0 ? _h : undefined,
        (_l = (_k = (_j = this.value) === null || _j === void 0 ? void 0 : _j.font) === null ||
          _k === void 0 ? void 0 : _k.family) !== null && _l !== void 0 ? _l : undefined,
        (_p = (_o = (_m = this.value) === null || _m === void 0 ? void 0 : _m.font) === null ||
          _o === void 0 ? void 0 : _o.style) !== null && _p !== void 0 ? _p : undefined);
    }
  }
  checkObjectDiff() {
    return true;
  }
}
TimepickerDisappearTextStyleModifier.identity = Symbol('disappearTextStyle');
class TimepickerUseMilitaryTimeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().timePicker.resetTimepickerUseMilitaryTime(node);
    }
    else {
      getUINativeModule().timePicker.setTimepickerUseMilitaryTime(node, this.value);
    }
  }
}
TimepickerUseMilitaryTimeModifier.identity = Symbol('timepickerUseMilitaryTime');

class TimepickerLoopModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().timePicker.resetTimepickerLoop(node);
    }
    else {
      getUINativeModule().timePicker.setTimepickerLoop(node, this.value);
    }
  }
}
TimepickerLoopModifier.identity = Symbol('timepickerLoop');

class TimepickerEnableCascadeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().timePicker.resetTimepickerEnableCascade(node);
    }
    else {
      getUINativeModule().timePicker.setTimepickerEnableCascade(node, this.value);
    }
  }
}
TimepickerEnableCascadeModifier.identity = Symbol('timepickerEnableCascade');

class TimepickerDateTimeOptionsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().timePicker.resetTimepickerDateTimeOptions(node);
    }
    else {
      getUINativeModule().timePicker.setTimepickerDateTimeOptions(node, this.value.hour, this.value.minute, this.value.second);
    }
  }
}
TimepickerDateTimeOptionsModifier.identity = Symbol('timepickerDateTimeOptions');

class TimepickerEnableHapticFeedbackModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().timePicker.resetTimepickerEnableHapticFeedback(node);
    }
    else {
      getUINativeModule().timePicker.setTimepickerEnableHapticFeedback(node, this.value);
    }
  }
}
TimepickerEnableHapticFeedbackModifier.identity = Symbol('timepickerEnableHapticFeedback');

class TimepickerOnChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().timePicker.resetTimepickerOnChange(node);
    } else {
      getUINativeModule().timePicker.setTimepickerOnChange(node, this.value);
    }
  }
}
TimepickerOnChangeModifier.identity = Symbol('timePickerOnChange');

class JSTimePicker extends JSViewAbstract {
  static create(params) {
    getUINativeModule().timePicker.create(params);
  }
  static onChange(value) {
    getUINativeModule().timePicker.setTimepickerOnChange(true, value);
  }
  static backgroundColor(value) {
    getUINativeModule().timePicker.setBackgroundColor(true, value);
  }
  static loop(value) {
    getUINativeModule().timePicker.setTimepickerLoop(true, value);
  }
  static useMilitaryTime(value) {
    getUINativeModule().timePicker.setTimepickerUseMilitaryTime(true, value);
  }
  static enableHapticFeedback(value) {
    getUINativeModule().timePicker.setTimepickerEnableHapticFeedback(true, value);
  }
  static disappearTextStyle(value) {
    getUINativeModule().timePicker.setDisappearTextStyle(true, value?.color ?? undefined,
      value?.font?.size ?? undefined,
      value?.font?.weight ?? undefined,
      value?.font?.family ?? undefined,
      value?.font?.style ?? undefined);
  }
  static textStyle(value) {
    getUINativeModule().timePicker.setTextStyle(true, value?.color ?? undefined,
      value?.font?.size ?? undefined,
      value?.font?.weight ?? undefined,
      value?.font?.family ?? undefined,
      value?.font?.style ?? undefined);
  }
  static selectedTextStyle(value) {
    getUINativeModule().timePicker.setSelectedTextStyle(true, value?.color ?? undefined,
      value?.font?.size ?? undefined,
      value?.font?.weight ?? undefined,
      value?.font?.family ?? undefined,
      value?.font?.style ?? undefined);
  }
  static dateTimeOptions(value) {
    getUINativeModule().timePicker.setTimepickerDateTimeOptions(true, value);
  }
  static opacity(value) {
    getUINativeModule().timePicker.setOpacity(true, value);
  }
  static enableCascade(value) {
    getUINativeModule().timePicker.setTimepickerEnableCascade(true, value);
  }
  static onEnterSelectedArea(value) {
    getUINativeModule().timePicker.setOnEnterSelectedArea(true, value);
  }
  static digitalCrownSensitivity(value) {
    getUINativeModule().timePicker.setDigitalCrownSensitivity(true, value);
  }
  static attributeModifier(modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkTimePickerComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.TimePickerModifier(nativePtr, classType);
    });
  }
  static contentModifier(modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
      return createComponent(nativeNode, 'timePicker');
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

class JSTimePickerDialog extends JSViewAbstract {
  static show(value) {
    getUINativeModule().timePickerDialog.show(value);
  }
}

function createComponent(nativePtr, classType) {
  return new ArkTimePickerComponent(nativePtr, classType);
}

function exportComponent() {
  globalThis.ArkTimePickerComponent = ArkTimePickerComponent;
}

function exportView() {
  globalThis.TimePicker = JSTimePicker;
}

function exportViewDialog() {
  globalThis.TimePickerDialog = JSTimePickerDialog;
}
function loadComponent() {}
export default { ArkTimePickerComponent, createComponent, exportComponent, exportView, exportViewDialog,
    loadComponent
};
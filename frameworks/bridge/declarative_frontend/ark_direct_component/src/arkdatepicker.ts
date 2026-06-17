/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

/// <reference path='./../../ark_component/src/import.ts' />

class ArkDatePickerComponent extends ArkComponent {
  constructor(nativePtr: any, classType: any) {
    super(nativePtr, classType);
  }
  lunar(value: any): this {
    modifierWithKey(this._modifiersWithKeys, DatePickerLunarModifier.identity, DatePickerLunarModifier, value);
    return this;
  }
  digitalCrownSensitivity(value: any): this {
    modifierWithKey(this._modifiersWithKeys, DatePickerDigitalCrownSensitivityModifier.identity,
      DatePickerDigitalCrownSensitivityModifier, value);
    return this;
  }
  disappearTextStyle(value: any): this {
    modifierWithKey(this._modifiersWithKeys, DatePickerDisappearTextStyleModifier.identity,
      DatePickerDisappearTextStyleModifier, value);
    return this;
  }
  textStyle(value: any): this {
    modifierWithKey(this._modifiersWithKeys, DatePickerTextStyleModifier.identity, DatePickerTextStyleModifier,
      value);
    return this;
  }
  selectedTextStyle(value: any): this {
    modifierWithKey(this._modifiersWithKeys, DatePickerSelectedTextStyleModifier.identity,
      DatePickerSelectedTextStyleModifier, value);
    return this;
  }
  onChange(callback: any): this {
    modifierWithKey(this._modifiersWithKeys, DatePickerOnChangeModifier.identity, DatePickerOnChangeModifier,
      callback);
    return this;
  }
  onDateChange(callback: any): this {
    modifierWithKey(this._modifiersWithKeys, DatePickerOnDateChangeModifier.identity,
      DatePickerOnDateChangeModifier, callback);
    return this;
  }
  backgroundColor(value: any): this {
    modifierWithKey(this._modifiersWithKeys, DatePickerBackgroundColorModifier.identity,
      DatePickerBackgroundColorModifier, value);
    return this;
  }
  enableHapticFeedback(value: any): this {
    modifierWithKey(this._modifiersWithKeys, DatePickerEnableHapticFeedbackModifier.identity,
      DatePickerEnableHapticFeedbackModifier, value);
    return this;
  }
  canLoop(value: any): this {
    modifierWithKey(this._modifiersWithKeys, DatePickerCanLoopModifier.identity, DatePickerCanLoopModifier,
      value);
    return this;
  }
}
class DatePickerDigitalCrownSensitivityModifier extends ModifierWithKey<any> {
  constructor(value: any) {
    super(value);
  }
  applyPeer(node: any, reset: boolean): void {
    if (reset) {
      getUINativeModule().datePicker.resetDigitalCrownSensitivity(node);
    } else {
      getUINativeModule().datePicker.setDigitalCrownSensitivity(node, this.value);
    }
  }
}
(DatePickerDigitalCrownSensitivityModifier as any).identity = Symbol('DigitalCrownSensitivity');
class DatePickerLunarModifier extends ModifierWithKey<any> {
  constructor(value: any) {
    super(value);
  }
  applyPeer(node: any, reset: boolean): void {
    if (reset) {
      getUINativeModule().datePicker.resetLunar(node);
    } else {
      getUINativeModule().datePicker.setLunar(node, this.value);
    }
  }
}
(DatePickerLunarModifier as any).identity = Symbol('lunar');
class DatePickerTextStyleModifier extends ModifierWithKey<any> {
  constructor(value: any) {
    super(value);
  }
  applyPeer(node: any, reset: boolean): void {
    if (reset) {
      getUINativeModule().datePicker.resetTextStyle(node);
    } else {
      getUINativeModule().datePicker.setTextStyle(node, this.value?.color ?? undefined,
        this.value?.font?.size ?? undefined, this.value?.font?.weight ?? undefined,
        this.value?.font?.family ?? undefined, this.value?.font?.style ?? undefined);
    }
  }
  checkObjectDiff(): boolean {
    return true;
  }
}
(DatePickerTextStyleModifier as any).identity = Symbol('textStyle');
class DatePickerSelectedTextStyleModifier extends ModifierWithKey<any> {
  constructor(value: any) {
    super(value);
  }
  applyPeer(node: any, reset: boolean): void {
    if (reset) {
      getUINativeModule().datePicker.resetSelectedTextStyle(node);
    } else {
      getUINativeModule().datePicker.setSelectedTextStyle(node, this.value?.color ?? undefined,
        this.value?.font?.size ?? undefined, this.value?.font?.weight ?? undefined,
        this.value?.font?.family ?? undefined, this.value?.font?.style ?? undefined);
    }
  }
  checkObjectDiff(): boolean {
    return true;
  }
}
(DatePickerSelectedTextStyleModifier as any).identity = Symbol('selectedTextStyle');
class DatePickerDisappearTextStyleModifier extends ModifierWithKey<any> {
  constructor(value: any) {
    super(value);
  }
  applyPeer(node: any, reset: boolean): void {
    if (reset) {
      getUINativeModule().datePicker.resetDisappearTextStyle(node);
    } else {
      getUINativeModule().datePicker.setDisappearTextStyle(node, this.value?.color ?? undefined,
        this.value?.font?.size ?? undefined, this.value?.font?.weight ?? undefined,
        this.value?.font?.family ?? undefined, this.value?.font?.style ?? undefined);
    }
  }
  checkObjectDiff(): boolean {
    return true;
  }
}
(DatePickerDisappearTextStyleModifier as any).identity = Symbol('disappearTextStyle');
class DatePickerOnChangeModifier extends ModifierWithKey<any> {
  constructor(value: any) {
    super(value);
  }
  applyPeer(node: any, reset: boolean): void {
    if (reset) {
      getUINativeModule().datePicker.resetDatePickerOnChange(node);
    } else {
      getUINativeModule().datePicker.setDatePickerOnChange(node, this.value);
    }
  }
}
(DatePickerOnChangeModifier as any).identity = Symbol('datePickerOnChange');
class DatePickerOnDateChangeModifier extends ModifierWithKey<any> {
  constructor(value: any) {
    super(value);
  }
  applyPeer(node: any, reset: boolean): void {
    if (reset) {
      getUINativeModule().datePicker.resetDatePickerOnDateChange(node);
    } else {
      getUINativeModule().datePicker.setDatePickerOnDateChange(node, this.value);
    }
  }
}
(DatePickerOnDateChangeModifier as any).identity = Symbol('datePickerOnDateChange');
class DatePickerBackgroundColorModifier extends ModifierWithKey<any> {
  constructor(value: any) {
    super(value);
  }
  applyPeer(node: any, reset: boolean): void {
    if (reset) {
      getUINativeModule().datePicker.resetBackgroundColor(node);
    } else {
      getUINativeModule().datePicker.setBackgroundColor(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
(DatePickerBackgroundColorModifier as any).identity = Symbol('datePickerBackgroundColor');
class DatePickerEnableHapticFeedbackModifier extends ModifierWithKey<any> {
  constructor(value: any) {
    super(value);
  }
  applyPeer(node: any, reset: boolean): void {
    if (reset) {
      getUINativeModule().datePicker.resetEnableHapticFeedback(node);
    } else {
      getUINativeModule().datePicker.setEnableHapticFeedback(node, this.value);
    }
  }
}
(DatePickerEnableHapticFeedbackModifier as any).identity = Symbol('datePickerEnableHapticFeedback');
class DatePickerCanLoopModifier extends ModifierWithKey<any> {
  constructor(value: any) {
    super(value);
  }
  applyPeer(node: any, reset: boolean): void {
    if (reset) {
      getUINativeModule().datePicker.resetCanLoop(node);
    } else {
      getUINativeModule().datePicker.setCanLoop(node, this.value);
    }
  }
}
(DatePickerCanLoopModifier as any).identity = Symbol('canLoop');

class JSDatePicker extends JSViewAbstract {
  static create(params: any): void {
    getUINativeModule().datePicker.create(params);
  }
  static selectedTextStyle(value: any): void {
    getUINativeModule().datePicker.setSelectedTextStyle(true, value?.color ?? undefined,
      value?.font?.size ?? undefined, value?.font?.weight ?? undefined,
      value?.font?.family ?? undefined, value?.font?.style ?? undefined);
  }
  static textStyle(value: any): void {
    getUINativeModule().datePicker.setTextStyle(true, value?.color ?? undefined,
      value?.font?.size ?? undefined, value?.font?.weight ?? undefined,
      value?.font?.family ?? undefined, value?.font?.style ?? undefined);
  }
  static disappearTextStyle(value: any): void {
    getUINativeModule().datePicker.setDisappearTextStyle(true, value?.color ?? undefined,
      value?.font?.size ?? undefined, value?.font?.weight ?? undefined,
      value?.font?.family ?? undefined, value?.font?.style ?? undefined);
  }
  static lunar(value: any): void {
    getUINativeModule().datePicker.setLunar(true, value);
  }
  static backgroundColor(value: any): void {
    getUINativeModule().datePicker.setBackgroundColor(true, value);
  }
  static enableHapticFeedback(value: any): void {
    getUINativeModule().datePicker.setEnableHapticFeedback(true, value);
  }
  static onChange(value: any): void {
    getUINativeModule().datePicker.setDatePickerOnChange(true, value);
  }
  static onDateChange(value: any): void {
    getUINativeModule().datePicker.setDatePickerOnDateChange(true, value);
  }
  static digitalCrownSensitivity(value: any): void {
    getUINativeModule().datePicker.setDigitalCrownSensitivity(true, value);
  }
  static canLoop(value: any): void {
    getUINativeModule().datePicker.setCanLoop(true, value);
  }
  static opacity(value: any): void {
    getUINativeModule().datePicker.setOpacity(true, value);
  }
  static useMilitaryTime(value: any): void {
    getUINativeModule().datePicker.setUseMilitaryTime(true, value);
  }
  static attributeModifier(modifier: any): void {
    attributeModifierFunc.call(this, modifier, (nativePtr: any) => {
      return createComponent(nativePtr);
    }, (nativePtr: any, classType: any, modifierJS: any) => {
      return new modifierJS.DatePickerModifier(nativePtr, classType);
    });
  }
  static contentModifier(modifier: any): void {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
      return createComponent(nativeNode, 'datePicker');
    });
    component.setContentModifier(modifier);
  }
  static onClick(value: any): void {
    __Common__.onClick(value);
  }
  static onTouch(value: any): void {
    __Common__.onTouch(value);
  }
  static onKeyEvent(value: any): void {
    __Common__.onKeyEvent(value);
  }
  static onDeleteEvent(value: any): void {
    __Common__.onDeleteEvent(value);
  }
  static onAttach(value: any): void {
    __Common__.onAttach(value);
  }
  static onAppear(value: any): void {
    __Common__.onAppear(value);
  }
  static onDetach(value: any): void {
    __Common__.onDetach(value);
  }
  static onDisAppear(value: any): void {
    __Common__.onDisAppear(value);
  }
}

class JSDatePickerDialog extends JSViewAbstract {
  static show(value: any): void {
    getUINativeModule().datePickerDialog.show(value);
  }
}

function createComponent(nativePtr: any, classType: any): any {
  return new ArkDatePickerComponent(nativePtr, classType);
}

function exportComponent(): void {
  globalThis.ArkDatePickerComponent = ArkDatePickerComponent;
}

function exportView(): void {
  globalThis.DatePicker = JSDatePicker;
}

function exportViewDialog(): void {
  globalThis.DatePickerDialog = JSDatePickerDialog;
}
function loadComponent() {}
export default { ArkDatePickerComponent, createComponent, exportComponent, exportView, exportViewDialog,
    loadComponent
};

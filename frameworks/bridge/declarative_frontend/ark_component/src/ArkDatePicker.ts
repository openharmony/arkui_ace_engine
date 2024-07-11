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
class ArkDatePickerComponent extends ArkComponent implements DatePickerAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  lunar(value: boolean): DatePickerAttribute {
    modifierWithKey(this._modifiersWithKeys, DatePickerLunarModifier.identity, DatePickerLunarModifier, value);
    return this;
  }
  digitalCrownSensitivity(value: Optional<CrownSensitivity>): DatePickerAttribute {
    modifierWithKey(this._modifiersWithKeys, DatePickerDigitalCrownSensitivityModifier.identity, DatePickerDigitalCrownSensitivityModifier, value);
    return this;
  }
  disappearTextStyle(value: PickerTextStyle): DatePickerAttribute {
    modifierWithKey(this._modifiersWithKeys, DatePickerDisappearTextStyleModifier.identity,
      DatePickerDisappearTextStyleModifier, value);
    return this;
  }
  textStyle(value: PickerTextStyle): DatePickerAttribute {
    modifierWithKey(this._modifiersWithKeys, DatePickerTextStyleModifier.identity,
      DatePickerTextStyleModifier, value);
    return this;
  }
  selectedTextStyle(value: PickerTextStyle): DatePickerAttribute {
    modifierWithKey(this._modifiersWithKeys, DatePickerSelectedTextStyleModifier.identity,
      DatePickerSelectedTextStyleModifier, value);
    return this;
  }
  onChange(callback: (value: DatePickerResult) => void): DatePickerAttribute {
    throw new Error('Method not implemented.');
  }
  onDateChange(callback: (value: Date) => void): DatePickerAttribute {
    throw new Error('Method not implemented.');
  }
  backgroundColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, DatePickerBackgroundColorModifier.identity, DatePickerBackgroundColorModifier, value);
    return this;
  }
  enableHapticFeedback(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, DatePickerEnableHapticFeedbackModifier.identity, DatePickerEnableHapticFeedbackModifier, value);
    return this;
  }
}

class DatePickerLunarModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('lunar');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      getUINativeModule().datePicker.resetLunar(node);
    } else {
      getUINativeModule().datePicker.setLunar(node, this.value);
    }
  }
}

class DatePickerDigitalCrownSensitivityModifier extends ModifierWithKey<Optional<CrownSensitivity>> {
  constructor(value: Optional<CrownSensitivity>) {
    super(value);
  }
  static identity: Symbol = Symbol('digitalCrownSensitivity');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      getUINativeModule().datePicker.resetDigitalCrownSensitivity(node);
    } else {
      getUINativeModule().datePicker.setDigitalCrownSensitivity(node, this.value);
    }
  }
}

class DatePickerTextStyleModifier extends ModifierWithKey<PickerTextStyle> {
  constructor(value: PickerTextStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('textStyle');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      getUINativeModule().datePicker.resetTextStyle(node);
    } else {
      getUINativeModule().datePicker.setTextStyle(node, this.value?.color ?? undefined,
        this.value?.font?.size ?? undefined,
        this.value?.font?.weight ?? undefined,
        this.value?.font?.family ?? undefined,
        this.value?.font?.style ?? undefined);
    }
  }

  checkObjectDiff(): boolean {
    if (!(this.stageValue?.font?.weight === this.value?.font?.weight &&
      this.stageValue?.font?.style === this.value?.font?.style)) {
      return true;
    } else {
      return !isBaseOrResourceEqual(this.stageValue?.color, this.value?.color) ||
        !isBaseOrResourceEqual(this.stageValue?.font?.size, this.value?.font?.size) ||
        !isBaseOrResourceEqual(this.stageValue?.font?.family, this.value?.font?.family);
    }
  }
}

class DatePickerSelectedTextStyleModifier extends ModifierWithKey<PickerTextStyle> {
  constructor(value: PickerTextStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('selectedTextStyle');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      getUINativeModule().datePicker.resetSelectedTextStyle(node);
    } else {
      getUINativeModule().datePicker.setSelectedTextStyle(node, this.value?.color ?? undefined,
        this.value?.font?.size ?? undefined,
        this.value?.font?.weight ?? undefined,
        this.value?.font?.family ?? undefined,
        this.value?.font?.style ?? undefined);
    }
  }

  checkObjectDiff(): boolean {
    if (!(this.stageValue?.font?.weight === this.value?.font?.weight &&
      this.stageValue?.font?.style === this.value?.font?.style)) {
      return true;
    } else {
      return !isBaseOrResourceEqual(this.stageValue?.color, this.value?.color) ||
        !isBaseOrResourceEqual(this.stageValue?.font?.size, this.value?.font?.size) ||
        !isBaseOrResourceEqual(this.stageValue?.font?.family, this.value?.font?.family);
    }
  }
}

class DatePickerDisappearTextStyleModifier extends ModifierWithKey<PickerTextStyle> {
  constructor(value: PickerTextStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('disappearTextStyle');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      getUINativeModule().datePicker.resetDisappearTextStyle(node);
    } else {
      getUINativeModule().datePicker.setDisappearTextStyle(node, this.value?.color ?? undefined,
        this.value?.font?.size ?? undefined,
        this.value?.font?.weight ?? undefined,
        this.value?.font?.family ?? undefined,
        this.value?.font?.style ?? undefined);
    }
  }

  checkObjectDiff(): boolean {
    if (!(this.stageValue?.font?.weight === this.value?.font?.weight &&
      this.stageValue?.font?.style === this.value?.font?.style)) {
      return true;
    } else {
      return !isBaseOrResourceEqual(this.stageValue?.color, this.value?.color) ||
        !isBaseOrResourceEqual(this.stageValue?.font?.size, this.value?.font?.size) ||
        !isBaseOrResourceEqual(this.stageValue?.font?.family, this.value?.font?.family);
    }
  }
}

class DatePickerBackgroundColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('datePickerBackgroundColor');
  applyPeer(node: KNode, reset: boolean): void {
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
class DatePickerEnableHapticFeedbackModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('datePickerEnableHapticFeedback');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().datePicker.resetEnableHapticFeedback(node);
    } else {
      getUINativeModule().datePicker.setEnableHapticFeedback(node, this.value);
    }
  }
}

//@ts-ignore
globalThis.DatePicker.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkDatePickerComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.DatePickerModifier(nativePtr, classType);
  });
};

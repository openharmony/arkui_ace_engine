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
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  lunar(value: boolean): DatePickerAttribute {
    modifier(this._modifiers, DatePickerLunarModifier, isBoolean(value) ? value : false);
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
}

class DatePickerLunarModifier extends Modifier<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('lunar');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      GetUINativeModule().datePicker.resetLunar(node);
    }
    else {
      GetUINativeModule().datePicker.setLunar(node, this.value);
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
      GetUINativeModule().datePicker.resetTextStyle(node);
    }
    else {
      GetUINativeModule().datePicker.setTextStyle(node, this.value?.color ?? undefined,
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
      GetUINativeModule().datePicker.resetSelectedTextStyle(node);
    }
    else {
      GetUINativeModule().datePicker.setSelectedTextStyle(node, this.value?.color ?? undefined,
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
      GetUINativeModule().datePicker.resetDisappearTextStyle(node);
    }
    else {
      GetUINativeModule().datePicker.setDisappearTextStyle(node, this.value?.color ?? undefined,
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

//@ts-ignore
globalThis.DatePicker.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkDatePickerComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
}

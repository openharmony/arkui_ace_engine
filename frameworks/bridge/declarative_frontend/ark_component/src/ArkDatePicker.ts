/// <reference path='./import.ts' />
class ArkDatePickerComponent extends ArkComponent implements DatePickerAttribute {
  lunar(value: boolean): DatePickerAttribute {
    modifier(this._modifiers, DatePickerLunarModifier, isBoolean(value) ? value : false);
    return this;
  }
  disappearTextStyle(value: PickerTextStyle): DatePickerAttribute {
    let pickerText: ArkDatePickerTextStyle = new ArkDatePickerTextStyle();
    pickerText.color = value?.color ?? undefined;
    pickerText.font = value?.font ?? undefined;

    modifier(this._modifiers, DatePickerDisappearTextStyleModifier, pickerText);

    return this;
  }
  textStyle(value: PickerTextStyle): DatePickerAttribute {
    let pickerText: ArkDatePickerTextStyle = new ArkDatePickerTextStyle();
    pickerText.color = value?.color ?? undefined;
    pickerText.font = value?.font ?? undefined;

    modifier(this._modifiers, DatePickerTextStyleModifier, pickerText);

    return this;
  }
  selectedTextStyle(value: PickerTextStyle): DatePickerAttribute {
    let pickerText: ArkDatePickerTextStyle = new ArkDatePickerTextStyle();
    pickerText.color = value?.color ?? undefined;
    pickerText.font = value?.font ?? undefined;

    modifier(this._modifiers, DatePickerSelectedTextStyleModifier, pickerText);

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

class DatePickerTextStyleModifier extends Modifier<ArkDatePickerTextStyle> {
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
}

class DatePickerSelectedTextStyleModifier extends Modifier<ArkDatePickerTextStyle> {
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
}

class DatePickerDisappearTextStyleModifier extends Modifier<ArkDatePickerTextStyle> {
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
}

//@ts-ignore
globalThis.DatePicker.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkDatePickerComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}

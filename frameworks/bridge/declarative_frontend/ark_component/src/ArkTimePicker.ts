/// <reference path='./import.ts' />
class ArkTimePickerComponent extends ArkComponent implements TimePickerAttribute {
  onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
    throw new Error('Method not implemented.');
  }
  loop(value: boolean): this {
    throw new Error('Method not implemented.');
  }
  useMilitaryTime(value: boolean): this {
    throw new Error('Method not implemented.');
  }
  disappearTextStyle(value: PickerTextStyle): this {
    modifierWithKey(this._modifiersWithKeys, TimepickerDisappearTextStyleModifier.identity,
      TimepickerDisappearTextStyleModifier, value);
    return this;
  }
  textStyle(value: PickerTextStyle): this {
    modifierWithKey(this._modifiersWithKeys, TimepickerTextStyleModifier.identity,
      TimepickerTextStyleModifier, value);
    return this;
  }
  selectedTextStyle(value: PickerTextStyle): this {
    modifierWithKey(this._modifiersWithKeys, TimepickerSelectedTextStyleModifier.identity,
      TimepickerSelectedTextStyleModifier, value);
    return this;
  }
  onChange(callback: (value: TimePickerResult) => void): this {
    throw new Error('Method not implemented.');
  }
}

class TimepickerTextStyleModifier extends ModifierWithKey<PickerTextStyle> {
  static identity: Symbol = Symbol('textStyle');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().timepicker.resetTextStyle(node);
    }
    else {
      GetUINativeModule().timepicker.setTextStyle(node,
        this.value.color, this.value.font?.size, this.value.font?.weight, this.value.font?.family, this.value.font?.style);
    }
  }

  checkObjectDiff(): boolean {
    let colorEQ = isBaseOrResourceEqual((this.stageValue as PickerTextStyle).color,
      (this.value as PickerTextStyle).color);
    let sizeEQ = isBaseOrResourceEqual((this.stageValue as PickerTextStyle).font?.size,
      (this.value as PickerTextStyle).font?.size);
    let weightEQ = isBaseOrResourceEqual((this.stageValue as PickerTextStyle).font?.weight,
      (this.value as PickerTextStyle).font?.weight);
    let familyEQ = isBaseOrResourceEqual((this.stageValue as PickerTextStyle).font?.family,
      (this.value as PickerTextStyle).font?.family);
    let styleEQ = isBaseOrResourceEqual((this.stageValue as PickerTextStyle).font?.style,
      (this.value as PickerTextStyle).font?.style);
    return !colorEQ || !sizeEQ || !weightEQ || !familyEQ || !styleEQ;
  }
}

class TimepickerSelectedTextStyleModifier extends ModifierWithKey<PickerTextStyle> {
  static identity: Symbol = Symbol('selectedTextStyle');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().timepicker.resetSelectedTextStyle(node);
    }
    else {
      GetUINativeModule().timepicker.setSelectedTextStyle(node,
        this.value.color, this.value.font?.size, this.value.font?.weight, this.value.font?.family, this.value.font?.style);
    }
  }

  checkObjectDiff(): boolean {
    let colorEQ = isBaseOrResourceEqual((this.stageValue as PickerTextStyle).color,
      (this.value as PickerTextStyle).color);
    let sizeEQ = isBaseOrResourceEqual((this.stageValue as PickerTextStyle).font?.size,
      (this.value as PickerTextStyle).font?.size);
    let weightEQ = isBaseOrResourceEqual((this.stageValue as PickerTextStyle).font?.weight,
      (this.value as PickerTextStyle).font?.weight);
    let familyEQ = isBaseOrResourceEqual((this.stageValue as PickerTextStyle).font?.family,
      (this.value as PickerTextStyle).font?.family);
    let styleEQ = isBaseOrResourceEqual((this.stageValue as PickerTextStyle).font?.style,
      (this.value as PickerTextStyle).font?.style);
    return !colorEQ || !sizeEQ || !weightEQ || !familyEQ || !styleEQ;
  }
}

class TimepickerDisappearTextStyleModifier extends ModifierWithKey<PickerTextStyle> {
  static identity: Symbol = Symbol('disappearTextStyle');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().timepicker.resetDisappearTextStyle(node);
    }
    else {
      GetUINativeModule().timepicker.setDisappearTextStyle(node,
        this.value.color, this.value.font?.size, this.value.font?.weight, this.value.font?.family, this.value.font?.style);
    }
  }

  checkObjectDiff(): boolean {
    let colorEQ = isBaseOrResourceEqual((this.stageValue as PickerTextStyle).color,
      (this.value as PickerTextStyle).color);
    let sizeEQ = isBaseOrResourceEqual((this.stageValue as PickerTextStyle).font?.size,
      (this.value as PickerTextStyle).font?.size);
    let weightEQ = isBaseOrResourceEqual((this.stageValue as PickerTextStyle).font?.weight,
      (this.value as PickerTextStyle).font?.weight);
    let familyEQ = isBaseOrResourceEqual((this.stageValue as PickerTextStyle).font?.family,
      (this.value as PickerTextStyle).font?.family);
    let styleEQ = isBaseOrResourceEqual((this.stageValue as PickerTextStyle).font?.style,
      (this.value as PickerTextStyle).font?.style);
    return !colorEQ || !sizeEQ || !weightEQ || !familyEQ || !styleEQ;
  }
}

// @ts-ignore
globalThis.TimePicker.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkTimePickerComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
};

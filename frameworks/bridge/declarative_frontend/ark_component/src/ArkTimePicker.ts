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
    let textStyle = new ArkTextStyle();
    if (isObject(value)) {
      textStyle.parseTextStyle(value);
      modifier(this._modifiers, TimepickerDisappearTextStyleModifier, textStyle);
    } else {
      modifier(this._modifiers, TimepickerDisappearTextStyleModifier, undefined);
    }
    return this;
  }
  textStyle(value: PickerTextStyle): this {
    let textStyle = new ArkTextStyle();
    if (isObject(value)) {
      textStyle.parseTextStyle(value);
      modifier(this._modifiers, TimepickerTextStyleModifier, textStyle);
    } else {
      modifier(this._modifiers, TimepickerTextStyleModifier, undefined);
    }
    return this;
  }
  selectedTextStyle(value: PickerTextStyle): this {
    let textStyle = new ArkTextStyle();
    if (isObject(value)) {
      textStyle.parseTextStyle(value);
      modifier(this._modifiers, TimepickerSelectedTextStyleModifier, textStyle);
    } else {
      modifier(this._modifiers, TimepickerSelectedTextStyleModifier, undefined);
    }
    return this;
  }
  onChange(callback: (value: TimePickerResult) => void): this {
    throw new Error('Method not implemented.');
  }
}

class TimepickerTextStyleModifier extends Modifier<ArkTextStyle> {
  static identity: Symbol = Symbol('textStyle');

  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      GetUINativeModule().timepicker.resetTextStyle(node);
    }
    else {
      GetUINativeModule().timepicker.setTextStyle(node,
        this.value.color, this.value.font?.size, this.value.font?.weight, this.value.font?.family, this.value.font?.style);
    }
  }
}
class TimepickerSelectedTextStyleModifier extends Modifier<ArkTextStyle> {
  static identity: Symbol = Symbol('selectedTextStyle');

  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      GetUINativeModule().timepicker.resetSelectedTextStyle(node);
    }
    else {
      GetUINativeModule().timepicker.setSelectedTextStyle(node,
        this.value.color, this.value.font?.size, this.value.font?.weight, this.value.font?.family, this.value.font?.style);
    }
  }
}
class TimepickerDisappearTextStyleModifier extends Modifier<ArkTextStyle> {
  static identity: Symbol = Symbol('disappearTextStyle');

  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      GetUINativeModule().timepicker.resetDisappearTextStyle(node);
    }
    else {
      GetUINativeModule().timepicker.setDisappearTextStyle(node,
        this.value.color, this.value.font?.size, this.value.font?.weight, this.value.font?.family, this.value.font?.style);
    }
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
}

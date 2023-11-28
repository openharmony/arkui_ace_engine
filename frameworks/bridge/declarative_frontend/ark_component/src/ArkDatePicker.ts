/// <reference path="./import.ts" />
class ArkDatePickerComponent extends ArkComponent implements DatePickerAttribute {
  lunar(value: boolean): this {
    throw new Error("Method not implemented.");
  }
  disappearTextStyle(value: PickerTextStyle): this {
    throw new Error("Method not implemented.");
  }
  textStyle(value: PickerTextStyle): this {
    throw new Error("Method not implemented.");
  }
  selectedTextStyle(value: PickerTextStyle): this {
    throw new Error("Method not implemented.");
  }
  onChange(callback: (value: DatePickerResult) => void): this {
    throw new Error("Method not implemented.");
  }
  onDateChange(callback: (value: Date) => void): this {
    throw new Error("Method not implemented.");
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error("Method not implemented.");
  }
}

// @ts-ignore
globalThis.DatePicker.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, ()=> {
    return new ArkDatePickerComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}

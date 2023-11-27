/// <reference path="./import.ts" />
class ArkCalendarPickerComponent extends ArkComponent implements CalendarPickerAttribute {
  edgeAlign(alignType: CalendarAlign, offset?: Offset | undefined): this {
    throw new Error("Method not implemented.");
  }
  textStyle(value: PickerTextStyle): this {
    throw new Error("Method not implemented.");
  }
  onChange(callback: (value: Date) => void): this {
    throw new Error("Method not implemented.");
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error("Method not implemented.");
  }
}

// @ts-ignore
globalThis.CalendarPicker.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, ()=> {
    return new ArkCalendarPickerComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}

/// <reference path="./import.ts" />
class TextStyleModifier extends Modifier<ArkPickerTextStyle> {
    static identity: Symbol = Symbol("textStyle");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().calendarPicker.resetTextStyle(node);
        } else {
            GetUINativeModule().calendarPicker.setTextStyle(node, this.value.color, this.value.size, this.value.weight);
        }
    }
}

class EdgeAlignModifier extends Modifier<ArkEdgeAlign> {
    static identity: Symbol = Symbol("edgeAlign");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().calendarPicker.resetEdgeAlign(node);
        } else {
            GetUINativeModule().calendarPicker.setEdgeAlign(node, this.value.alignType, this.value.offset);
        }
    }
}

class ArkCalendarPickerComponent extends ArkComponent implements CalendarPickerAttribute {
  edgeAlign(alignType: CalendarAlign, offset?: Offset | undefined): this {
    if (typeof alignType === "object") {
        modifier(this._modifiers, EdgeAlignModifier, alignType);
    } else {
        modifier(this._modifiers, EdgeAlignModifier, undefined);
    }
    return this;
  }
  textStyle(value: PickerTextStyle): this {
    if (typeof value === "object") {
        let pickerTextStyle = new ArkPickerTextStyle();
        pickerTextStyle.setColor(value.color);
        pickerTextStyle.setSize(value.font.size);
        pickerTextStyle.setWeight(value.font.weight);
        modifier(this._modifiers, TextStyleModifier, pickerTextStyle);
    } else {
        modifier(this._modifiers, TextStyleModifier, undefined);
    }
    return this;
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

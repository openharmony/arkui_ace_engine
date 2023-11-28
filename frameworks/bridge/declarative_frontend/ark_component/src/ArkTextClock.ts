/// <reference path="./import.ts" />
class ArkTextClockComponent extends ArkComponent implements TextClockAttribute {
  format(value: string): this {
    throw new Error("Method not implemented.");
  }
  onDateChange(event: (value: number) => void): this {
    throw new Error("Method not implemented.");
  }
  fontColor(value: any): this {
    throw new Error("Method not implemented.");
  }
  fontSize(value: any): this {
    throw new Error("Method not implemented.");
  }
  fontStyle(value: FontStyle): this {
    throw new Error("Method not implemented.");
  }
  fontWeight(value: string | number | FontWeight): this {
    throw new Error("Method not implemented.");
  }
  fontFamily(value: any): this {
    throw new Error("Method not implemented.");
  }
  textShadow(value: ShadowOptions): this {
    throw new Error("Method not implemented.");
  }
  fontFeature(value: string): this {
    throw new Error("Method not implemented.");
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error("Method not implemented.");
  }
}

// @ts-ignore
globalThis.TextClock.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, ()=> {
    return new ArkTextClockComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}

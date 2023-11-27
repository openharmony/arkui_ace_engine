/// <reference path="./import.ts" />
class ArkSpanComponent extends ArkComponent implements SpanAttribute {
  font(value: Font): this {
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
  decoration(value: { type: TextDecorationType; color?: any; }): this {
    throw new Error("Method not implemented.");
  }
  letterSpacing(value: string | number): this {
    throw new Error("Method not implemented.");
  }
  textCase(value: TextCase): this {
    throw new Error("Method not implemented.");
  }
  lineHeight(value: any): this {
    throw new Error("Method not implemented.");
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error("Method not implemented.");
  }
}

// @ts-ignore
globalThis.Span.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, ()=> {
    return new ArkSpanComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}

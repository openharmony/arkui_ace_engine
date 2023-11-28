/// <reference path="./import.ts" />
class ArkGaugeComponent extends ArkComponent implements GaugeAttribute {
  value(value: number): this {
    throw new Error("Method not implemented.");
  }
  startAngle(angle: number): this {
    throw new Error("Method not implemented.");
  }
  endAngle(angle: number): this {
    throw new Error("Method not implemented.");
  }
  colors(colors: any): this {
    throw new Error("Method not implemented.");
  }
  strokeWidth(length: any): this {
    throw new Error("Method not implemented.");
  }
  description(value: CustomBuilder): this {
    throw new Error("Method not implemented.");
  }
  trackShadow(value: GaugeShadowOptions): this {
    throw new Error("Method not implemented.");
  }
  indicator(value: GaugeIndicatorOptions): this {
    throw new Error("Method not implemented.");
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error("Method not implemented.");
  }
}

// @ts-ignore
globalThis.Gauge.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, ()=> {
    return new ArkGaugeComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}

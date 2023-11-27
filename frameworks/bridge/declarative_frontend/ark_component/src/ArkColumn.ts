/// <reference path="./import.ts" />
class ArkColumnComponent extends ArkComponent implements ColumnAttribute {
  alignItems(value: HorizontalAlign): this {
    throw new Error("Method not implemented.");
  }
  justifyContent(value: FlexAlign): this {
    throw new Error("Method not implemented.");
  }
  pointLight(value: PointLightStyle): this {
    throw new Error("Method not implemented.");
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error("Method not implemented.");
  }
}

// @ts-ignore
globalThis.Column.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, ()=> {
    return new ArkColumnComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}

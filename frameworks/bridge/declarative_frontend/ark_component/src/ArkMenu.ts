/// <reference path="./import.ts" />
class ArkMenuComponent extends ArkComponent implements MenuAttribute {
  fontSize(value: any): this {
    throw new Error("Method not implemented.");
  }
  font(value: Font): this {
    throw new Error("Method not implemented.");
  }
  fontColor(value: any): this {
    throw new Error("Method not implemented.");
  }
  radius(value: any): this {
    throw new Error("Method not implemented.");
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error("Method not implemented.");
  }
}

// @ts-ignore
globalThis.Menu.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, ()=> {
    return new ArkMenuComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}

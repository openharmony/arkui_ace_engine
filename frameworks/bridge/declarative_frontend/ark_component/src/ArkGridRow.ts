/// <reference path="./import.ts" />
class ArkGridRowComponent extends ArkComponent implements GridRowAttribute {
  onBreakpointChange(callback: (breakpoints: string) => void): this {
    throw new Error("Method not implemented.");
  }
  alignItems(value: ItemAlign): this {
    throw new Error("Method not implemented.");
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error("Method not implemented.");
  }
}

// @ts-ignore
globalThis.GridRow.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, ()=> {
    return new ArkGridRowComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}

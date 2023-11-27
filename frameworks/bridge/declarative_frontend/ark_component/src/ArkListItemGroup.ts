/// <reference path="./import.ts" />
class ArkListItemGroupComponent extends ArkComponent implements ListItemGroupAttribute {
  divider(value: { strokeWidth: any; color?: any; startMargin?: any; endMargin?: any; } | null): this {
    throw new Error("Method not implemented.");
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error("Method not implemented.");
  }
}

// @ts-ignore
globalThis.ListItemGroup.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, ()=> {
    return new ArkListItemGroupComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}

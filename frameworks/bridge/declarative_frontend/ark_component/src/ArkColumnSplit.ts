/// <reference path="./import.ts" />
class ArkColumnSplitComponent extends ArkComponent implements ColumnSplitAttribute {
  resizeable(value: boolean): this {
    throw new Error("Method not implemented.");
  }
  divider(value: ColumnSplitDividerStyle | null): this {
    throw new Error("Method not implemented.");
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error("Method not implemented.");
  }
}

// @ts-ignore
globalThis.ColumnSplit.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, ()=> {
    return new ArkColumnSplitComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}

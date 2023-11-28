/// <reference path="./import.ts" />
class ArkGridItemComponent extends ArkComponent implements GridItemAttribute {
  rowStart(value: number): this {
    throw new Error("Method not implemented.");
  }
  rowEnd(value: number): this {
    throw new Error("Method not implemented.");
  }
  columnStart(value: number): this {
    throw new Error("Method not implemented.");
  }
  columnEnd(value: number): this {
    throw new Error("Method not implemented.");
  }
  forceRebuild(value: boolean): this {
    throw new Error("Method not implemented.");
  }
  selectable(value: boolean): this {
    throw new Error("Method not implemented.");
  }
  selected(value: boolean): this {
    throw new Error("Method not implemented.");
  }
  onSelect(event: (isSelected: boolean) => void): this {
    throw new Error("Method not implemented.");
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error("Method not implemented.");
  }
}

// @ts-ignore
globalThis.GridItem.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, ()=> {
    return new ArkGridItemComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}

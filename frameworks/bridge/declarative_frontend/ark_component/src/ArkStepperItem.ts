/// <reference path="./import.ts" />
class ArkStepperItemComponent extends ArkComponent implements StepperItemAttribute {
  prevLabel(value: string): this {
    throw new Error("Method not implemented.");
  }
  nextLabel(value: string): this {
    throw new Error("Method not implemented.");
  }
  status(value?: ItemState | undefined): this {
    throw new Error("Method not implemented.");
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error("Method not implemented.");
  }
}

// @ts-ignore
globalThis.StepperItem.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, ()=> {
    return new ArkStepperItemComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}

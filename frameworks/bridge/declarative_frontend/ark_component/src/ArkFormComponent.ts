/// <reference path="./import.ts" />
class ArkFormComponentComponent extends ArkComponent implements FormComponentAttribute {
  moduleName(value: string): this {
    throw new Error("Method not implemented.");
  }
  dimension(value: FormDimension): this {
    throw new Error("Method not implemented.");
  }
  allowUpdate(value: boolean): this {
    throw new Error("Method not implemented.");
  }
  onAcquired(callback: (info: { id: number; }) => void): this {
    throw new Error("Method not implemented.");
  }
  onError(callback: (info: { errcode: number; msg: string; }) => void): this {
    throw new Error("Method not implemented.");
  }
  onRouter(callback: (info: any) => void): this {
    throw new Error("Method not implemented.");
  }
  onUninstall(callback: (info: { id: number; }) => void): this {
    throw new Error("Method not implemented.");
  }
  onLoad(callback: () => void): this {
    throw new Error("Method not implemented.");
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error("Method not implemented.");
  }
}

// @ts-ignore
globalThis.FormComponent.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, ()=> {
    return new ArkFormComponentComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}

/// <reference path="./import.ts" />
class ArkUIExtensionComponentComponent extends ArkComponent implements UIExtensionComponentAttribute {
  onRemoteReady(callback: any): this {
    throw new Error("Method not implemented.");
  }
  onReceive(callback: any): this {
    throw new Error("Method not implemented.");
  }
  onResult(callback: any): this {
    throw new Error("Method not implemented.");
  }
  onRelease(callback: any): this {
    throw new Error("Method not implemented.");
  }
  onError(callback: any): this {
    throw new Error("Method not implemented.");
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error("Method not implemented.");
  }
}

// @ts-ignore
globalThis.UIExtensionComponent.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, ()=> {
    return new ArkUIExtensionComponentComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}

/// <reference path='./import.ts' />
class ArkPluginComponentComponent extends ArkComponent implements PluginComponentAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  onComplete(callback: () => void): this {
    throw new Error('Method not implemented.');
  }
  onError(callback: (info: { errcode: number; msg: string; }) => void): this {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error('Method not implemented.');
  }
}

// @ts-ignore
globalThis.PluginComponent.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkPluginComponentComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}

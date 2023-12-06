/// <reference path='./import.ts' />

class ArkUIExtensionComponentComponent extends ArkComponent implements UIExtensionComponentAttribute {
  onRemoteReady(callback: any): UIExtensionComponentAttribute {
    throw new Error('Method not implemented.');
  }
  onReceive(callback: any): UIExtensionComponentAttribute {
    throw new Error('Method not implemented.');
  }
  onResult(callback: any): UIExtensionComponentAttribute {
    throw new Error('Method not implemented.');
  }
  onRelease(callback: any): UIExtensionComponentAttribute {
    throw new Error('Method not implemented.');
  }
  onError(callback: any): UIExtensionComponentAttribute {
    throw new Error('Method not implemented.');
  }
}

// @ts-ignore
globalThis.UIExtensionComponent.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = globalThis.getArkUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkUIExtensionComponentComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}

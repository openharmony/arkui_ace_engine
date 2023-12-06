/// <reference path='./import.ts' />
class ArkDataPanelComponent extends ArkComponent implements DataPanelAttribute {
  closeEffect(value: boolean): this {
    throw new Error('Method not implemented.');
  }
  valueColors(value: any[]): this {
    throw new Error('Method not implemented.');
  }
  trackBackgroundColor(value: any): this {
    throw new Error('Method not implemented.');
  }
  strokeWidth(value: any): this {
    throw new Error('Method not implemented.');
  }
  trackShadow(value: DataPanelShadowOptions): this {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error('Method not implemented.');
  }
}

// @ts-ignore
globalThis.DataPanel.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, ()=> {
    return new ArkDataPanelComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}

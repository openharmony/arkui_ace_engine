/// <reference path='./import.ts' />
class ArkGridContainerComponent extends ArkComponent implements ColumnAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  alignItems(value: HorizontalAlign): ColumnAttribute {
    throw new Error('Method not implemented.');
  }
  justifyContent(value: FlexAlign): ColumnAttribute {
    throw new Error('Method not implemented.');
  }
  pointLight(value: PointLightStyle): ColumnAttribute {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.GridContainer.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);

  let component = this.createOrGetNode(elmtId, () => {
    return new ArkGridContainerComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
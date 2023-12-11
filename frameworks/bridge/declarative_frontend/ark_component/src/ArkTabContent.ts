/// <reference path='./import.ts' />
class ArkTabContentComponent extends ArkComponent implements TabContentAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  tabBar(value: any): this;
  tabBar(value: SubTabBarStyle | BottomTabBarStyle): this;
  tabBar(value: unknown): this {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error('Method not implemented.');
  }
}

// @ts-ignore
globalThis.TabContent.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkTabContentComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}

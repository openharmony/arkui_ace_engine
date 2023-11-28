/// <reference path="./import.ts" />
class ArkMenuItemComponent extends ArkComponent implements MenuItemAttribute {
  selected(value: boolean): this {
    throw new Error("Method not implemented.");
  }
  selectIcon(value: any): this {
    throw new Error("Method not implemented.");
  }
  onChange(callback: (selected: boolean) => void): this {
    throw new Error("Method not implemented.");
  }
  contentFont(value: Font): this {
    throw new Error("Method not implemented.");
  }
  contentFontColor(value: any): this {
    throw new Error("Method not implemented.");
  }
  labelFont(value: Font): this {
    throw new Error("Method not implemented.");
  }
  labelFontColor(value: any): this {
    throw new Error("Method not implemented.");
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error("Method not implemented.");
  }
}

// @ts-ignore
globalThis.MenuItem.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, ()=> {
    return new ArkMenuItemComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}

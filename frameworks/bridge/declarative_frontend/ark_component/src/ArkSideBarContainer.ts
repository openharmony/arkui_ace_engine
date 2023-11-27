/// <reference path="./import.ts" />
class ArkSideBarContainerComponent extends ArkComponent implements SideBarContainerAttribute {
  showSideBar(value: boolean): this {
    throw new Error("Method not implemented.");
  }
  controlButton(value: ButtonStyle): this {
    throw new Error("Method not implemented.");
  }
  showControlButton(value: boolean): this {
    throw new Error("Method not implemented.");
  }
  onChange(callback: (value: boolean) => void): this {
    throw new Error("Method not implemented.");
  }
  sideBarWidth(value: number): this;
  sideBarWidth(value: any): this;
  sideBarWidth(value: unknown): this {
    throw new Error("Method not implemented.");
  }
  minSideBarWidth(value: number): this;
  minSideBarWidth(value: any): this;
  minSideBarWidth(value: unknown): this {
    throw new Error("Method not implemented.");
  }
  maxSideBarWidth(value: number): this;
  maxSideBarWidth(value: any): this;
  maxSideBarWidth(value: unknown): this {
    throw new Error("Method not implemented.");
  }
  autoHide(value: boolean): this {
    throw new Error("Method not implemented.");
  }
  sideBarPosition(value: SideBarPosition): this {
    throw new Error("Method not implemented.");
  }
  divider(value: DividerStyle | null): this {
    throw new Error("Method not implemented.");
  }
  minContentWidth(value: any): this {
    throw new Error("Method not implemented.");
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error("Method not implemented.");
  }
}

// @ts-ignore
globalThis.SideBarContainer.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, ()=> {
    return new ArkSideBarContainerComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}

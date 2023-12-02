/// <reference path="./import.ts" />
class GridRowAlignItemsModifier extends Modifier<number> {
  static identity: Symbol = Symbol('gridRowAlignItems');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().gridRow.resetAlignItems(node);
    } else {
      GetUINativeModule().gridRow.setAlignItems(node, this.value!);
    }
  }
}
class ArkGridRowComponent extends ArkComponent implements CommonMethod<GridRowAttribute>{
  onBreakpointChange(callback: (breakpoints: string) => void): GridRowAttribute {
    throw new Error("Method not implemented.");
  }
  alignItems(value: ItemAlign): GridRowAttribute {
    if (value in ItemAlign) {
      modifier(this._modifiers, GridRowAlignItemsModifier, value);
    } else {
      modifier(this._modifiers, GridRowAlignItemsModifier, undefined);
    }
    return this;
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error("Method not implemented.");
  }
}
// @ts-ignore
globalThis.GridRow.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkGridRowComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
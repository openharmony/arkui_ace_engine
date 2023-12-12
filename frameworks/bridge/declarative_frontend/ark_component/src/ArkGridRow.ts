/// <reference path="./import.ts" />
class GridRowAlignItemsModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('gridRowAlignItems');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().gridRow.resetAlignItems(node);
    } else {
      GetUINativeModule().gridRow.setAlignItems(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class ArkGridRowComponent extends ArkComponent implements CommonMethod<GridRowAttribute>{
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  onBreakpointChange(callback: (breakpoints: string) => void): GridRowAttribute {
    throw new Error("Method not implemented.");
  }
  alignItems(value: ItemAlign): GridRowAttribute {
    modifierWithKey(this._modifiersWithKeys, GridRowAlignItemsModifier.identity, GridRowAlignItemsModifier, value);
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

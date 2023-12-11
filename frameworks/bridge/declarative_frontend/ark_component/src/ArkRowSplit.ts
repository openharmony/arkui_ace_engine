/// <reference path="./import.ts" />

class RowSplitResizeableModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('rowSplitResizeable');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().rowSplit.resetResizeable(node);
    } else {
      GetUINativeModule().rowSplit.setResizeable(node, this.value);
    }
  }
}

class ArkRowSplitComponent extends ArkComponent implements RowSplitAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  resizeable(value: boolean): RowSplitAttribute {
    modifierWithKey(this._modifiersWithKeys, RowSplitResizeableModifier.identity, RowSplitResizeableModifier, value);
    return this;
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error("Method not implemented.");
  }
}
// @ts-ignore
globalThis.RowSplit.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkRowSplitComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}

/// <reference path="./import.ts" />

class RowSplitResizeableModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('rowSplitResizeable');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().rowSplit.ResetResizeable(node);
    } else {
      GetUINativeModule().rowSplit.setResizeable(node, this.value);
    }
  }
}

class ArkRowSplitComponent extends ArkComponent implements RowSplitAttribute {
  resizeable(value: boolean): RowSplitAttribute {
    if (isBoolean(value)) {
      modifier(this._modifiers, PatternLockAutoResetModifier, value);
    } else {
      modifier(this._modifiers, PatternLockAutoResetModifier, undefined);
    }
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
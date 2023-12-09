/// <reference path="./import.ts" />
class ColumnSplitDividerModifier extends ModifierWithKey<ColumnSplitDividerStyle | null> {
  static identity: Symbol = Symbol('columnSplitDivider');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().columnSplit.resetDivider(node);
    } else {
      GetUINativeModule().columnSplit.setDivider(node, this.value.startMargin, this.value.endMargin);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.startMargin, this.value.startMargin) ||
      !isBaseOrResourceEqual(this.stageValue.endMargin, this.value.endMargin)
  }
}
class ColumnSplitResizeableModifier extends ModifierWithKey<boolean> {
  static identity: Symbol = Symbol('columnSplitResizeable');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().columnSplit.resetResizeable(node);
    } else {
      GetUINativeModule().columnSplit.setResizeable(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}
class ArkColumnSplitComponent extends ArkComponent implements CommonMethod<ColumnSplitAttribute> {
  resizeable(value: boolean): ColumnSplitAttribute {
    modifierWithKey(this._modifiersWithKeys, ColumnSplitResizeableModifier.identity, ColumnSplitResizeableModifier, value);
    return this;
  }
  divider(value: ColumnSplitDividerStyle | null): ColumnSplitAttribute {
    modifierWithKey(this._modifiersWithKeys, ColumnSplitDividerModifier.identity, ColumnSplitDividerModifier, value);
    return this;
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error("Method not implemented.");
  }
}
// @ts-ignore
globalThis.ColumnSplit.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkColumnSplitComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}

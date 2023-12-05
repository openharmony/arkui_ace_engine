/// <reference path="./import.ts" />
class ColumnSplitDividerModifier extends ModifierWithKey<ArkColumnSplitDividerStyle> {
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
class ColumnSplitResizeableModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('columnSplitResizeable');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().columnSplit.resetResizeable(node);
    } else {
      GetUINativeModule().columnSplit.setResizeable(node, this.value);
    }

  }
}
class ArkColumnSplitComponent extends ArkComponent implements CommonMethod<ColumnSplitAttribute> {
  resizeable(value: boolean): ColumnSplitAttribute {
    if (isBoolean(value)) {
      modifier(this._modifiers, ColumnSplitResizeableModifier, value);
    } else {
      modifier(this._modifiers, ColumnSplitResizeableModifier, undefined);
    }
    return this;
  }
  divider(value: ColumnSplitDividerStyle | null): ColumnSplitAttribute {
    let arkValue = new ArkColumnSplitDividerStyle();
    if (!value) {
      modifierWithKey(this._modifiersWithKeys, ColumnSplitDividerModifier.identity, ColumnSplitDividerModifier, undefined);
      return this;
    } else {
      arkValue.startMargin = value?.startMargin;
      arkValue.endMargin = value?.endMargin;
      modifierWithKey(this._modifiersWithKeys, ColumnSplitDividerModifier.identity, ColumnSplitDividerModifier, arkValue);
      return this;
    }
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
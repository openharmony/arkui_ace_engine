/// <reference path="./import.ts" />
class ColumnSplitDividerModifier extends Modifier<ArkColumnSplitDividerStyle> {
  static identity: Symbol = Symbol('columnSplitDivider');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().columnSplit.resetDivider(node);
    } else {
      GetUINativeModule().columnSplit.setDivider(node, this.value.startMargin, this.value.endMargin);
    }
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
    let arkResizeable: boolean = false;
    if (isBoolean(value)) {
      arkResizeable = value;
    }
    modifier(this._modifiers, ColumnSplitResizeableModifier, arkResizeable);
    return this;
  }
  divider(value: ColumnSplitDividerStyle | null): ColumnSplitAttribute {
    let arkValue = new ArkColumnSplitDividerStyle();
    if (!value || (!isLengthType(value.startMargin) && !isLengthType(value.endMargin))) {
      modifier(this._modifiers, ColumnSplitDividerModifier, undefined);
      return this;
    }
    if (value.startMargin && isLengthType(value.startMargin)) {
      arkValue.startMargin = value.startMargin.toString();
    }
    if (value.endMargin && isLengthType(value.endMargin)) {
      arkValue.endMargin = value.endMargin.toString();
    }
    modifier(this._modifiers, ColumnSplitDividerModifier, arkValue);
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
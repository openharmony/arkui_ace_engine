/// <reference path='./import.ts' />
class ListItemGroupDividerModifier extends ModifierWithKey<{ strokeWidth: any; color?: any; startMargin?: any; endMargin?: any; } | null> {
  constructor(value: { strokeWidth: any; color?: any; startMargin?: any; endMargin?: any; } | null) {
    super(value);
  }
  static identity: Symbol = Symbol('listItemGroupDivider');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().listItemGroup.resetDivider(node);
    } else {
      GetUINativeModule().listItemGroup.setDivider(node, this.value?.strokeWidth!, this.value?.color, this.value?.startMargin, this.value?.endMargin);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue?.strokeWidth, this.value?.strokeWidth) ||
      !isBaseOrResourceEqual(this.stageValue?.color, this.value?.color) ||
      !isBaseOrResourceEqual(this.stageValue?.startMargin, this.value?.startMargin) ||
      !isBaseOrResourceEqual(this.stageValue?.endMargin, this.value?.endMargin);
  }
}

class ArkListItemGroupComponent extends ArkComponent implements ListItemGroupAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  divider(value: { strokeWidth: any; color?: any; startMargin?: any; endMargin?: any; } | null): this {
    modifierWithKey(this._modifiersWithKeys, ListItemGroupDividerModifier.identity, ListItemGroupDividerModifier, value);
    return this;
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error('Method not implemented.');
  }
}

// @ts-ignore
globalThis.ListItemGroup.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkListItemGroupComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}

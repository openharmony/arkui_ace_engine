/// <reference path='./import.ts' />
class ListItemSelectedModifier extends ModifierWithKey<boolean> {
  static identity: Symbol = Symbol('listItemSelected');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().listItem.resetListItemSelected(node);
    } else {
      GetUINativeModule().listItem.setListItemSelected(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return false;
  }
}

class ListItemSelectableModifier extends ModifierWithKey<boolean> {
  static identity: Symbol = Symbol('listItemSelectable');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().listItem.resetSelectable(node);
    } else {
      GetUINativeModule().listItem.setSelectable(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return false;
  }
}
class ArkListItemComponent extends ArkComponent implements ListItemAttribute {
  sticky(value: Sticky): this {
    throw new Error('Method not implemented.');
  }
  editable(value: boolean | EditMode): this {
    throw new Error('Method not implemented.');
  }
  selectable(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, ListItemSelectableModifier.identity, ListItemSelectableModifier, value);
    return this;
  }
  selected(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, ListItemSelectedModifier.identity, ListItemSelectedModifier, value);
    return this;
  }
  swipeAction(value: SwipeActionOptions): this {
    throw new Error('Method not implemented.');
  }
  onSelect(event: (isSelected: boolean) => void): this {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error('Method not implemented.');
  }
}

// @ts-ignore
globalThis.ListItem.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkListItemComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}

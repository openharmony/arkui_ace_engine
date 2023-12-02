/// <reference path='./import.ts' />
class ArkListItemComponent extends ArkComponent implements ListItemAttribute {
  sticky(value: Sticky): this {
    throw new Error('Method not implemented.');
  }
  editable(value: boolean | EditMode): this {
    throw new Error('Method not implemented.');
  }
  selectable(value: boolean): this {
    throw new Error('Method not implemented.');
  }
  selected(value: boolean): this {
    throw new Error('Method not implemented.');
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

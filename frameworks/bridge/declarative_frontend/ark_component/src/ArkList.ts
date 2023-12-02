/// <reference path='./import.ts' />
class ArkListComponent extends ArkComponent implements ListAttribute {
  lanes(value: number | LengthConstrain, gutter?: any): this {
    throw new Error('Method not implemented.');
  }
  alignListItem(value: ListItemAlign): this {
    throw new Error('Method not implemented.');
  }
  listDirection(value: Axis): this {
    throw new Error('Method not implemented.');
  }
  scrollBar(value: BarState): this {
    throw new Error('Method not implemented.');
  }
  edgeEffect(value: EdgeEffect, options?: EdgeEffectOptions | undefined): this {
    throw new Error('Method not implemented.');
  }
  contentStartOffset(value: number): this {
    throw new Error('Method not implemented.');
  }
  contentEndOffset(value: number): this {
    throw new Error('Method not implemented.');
  }
  divider(value: { strokeWidth: any; color?: any; startMargin?: any; endMargin?: any; } | null): this {
    throw new Error('Method not implemented.');
  }
  editMode(value: boolean): this {
    throw new Error('Method not implemented.');
  }
  multiSelectable(value: boolean): this {
    throw new Error('Method not implemented.');
  }
  cachedCount(value: number): this {
    throw new Error('Method not implemented.');
  }
  chainAnimation(value: boolean): this {
    throw new Error('Method not implemented.');
  }
  chainAnimationOptions(value: ChainAnimationOptions): this {
    throw new Error('Method not implemented.');
  }
  sticky(value: StickyStyle): this {
    throw new Error('Method not implemented.');
  }
  scrollSnapAlign(value: ScrollSnapAlign): this {
    throw new Error('Method not implemented.');
  }
  nestedScroll(value: NestedScrollOptions): this {
    throw new Error('Method not implemented.');
  }
  enableScrollInteraction(value: boolean): this {
    throw new Error('Method not implemented.');
  }
  friction(value: any): this {
    throw new Error('Method not implemented.');
  }
  onScroll(event: (scrollOffset: number, scrollState: ScrollState) => void): this {
    throw new Error('Method not implemented.');
  }
  onScrollIndex(event: (start: number, end: number, center: number) => void): this {
    throw new Error('Method not implemented.');
  }
  onReachStart(event: () => void): this {
    throw new Error('Method not implemented.');
  }
  onReachEnd(event: () => void): this {
    throw new Error('Method not implemented.');
  }
  onScrollStart(event: () => void): this {
    throw new Error('Method not implemented.');
  }
  onScrollStop(event: () => void): this {
    throw new Error('Method not implemented.');
  }
  onItemDelete(event: (index: number) => boolean): this {
    throw new Error('Method not implemented.');
  }
  onItemMove(event: (from: number, to: number) => boolean): this {
    throw new Error('Method not implemented.');
  }
  onItemDragStart(event: (event: ItemDragInfo, itemIndex: number) => void | (() => any)): this {
    throw new Error('Method not implemented.');
  }
  onItemDragEnter(event: (event: ItemDragInfo) => void): this {
    throw new Error('Method not implemented.');
  }
  onItemDragMove(event: (event: ItemDragInfo, itemIndex: number, insertIndex: number) => void): this {
    throw new Error('Method not implemented.');
  }
  onItemDragLeave(event: (event: ItemDragInfo, itemIndex: number) => void): this {
    throw new Error('Method not implemented.');
  }
  onItemDrop(event: (event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void): this {
    throw new Error('Method not implemented.');
  }
  onScrollFrameBegin(event: (offset: number, state: ScrollState) => { offsetRemain: number; }): this {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error('Method not implemented.');
  }
}

// @ts-ignore
globalThis.List.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkListComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}

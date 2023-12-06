/// <reference path='./import.ts' />
class ArkGridComponent extends ArkComponent implements GridAttribute {
  columnsTemplate(value: string): this {
    throw new Error('Method not implemented.');
  }
  rowsTemplate(value: string): this {
    throw new Error('Method not implemented.');
  }
  columnsGap(value: any): this {
    throw new Error('Method not implemented.');
  }
  rowsGap(value: any): this {
    throw new Error('Method not implemented.');
  }
  scrollBarWidth(value: string | number): this {
    throw new Error('Method not implemented.');
  }
  scrollBarColor(value: string | number | Color): this {
    throw new Error('Method not implemented.');
  }
  scrollBar(value: BarState): this {
    throw new Error('Method not implemented.');
  }
  onScrollBarUpdate(event: (index: number, offset: number) => ComputedBarAttribute): this {
    throw new Error('Method not implemented.');
  }
  onScrollIndex(event: (first: number, last: number) => void): this {
    throw new Error('Method not implemented.');
  }
  cachedCount(value: number): this {
    throw new Error('Method not implemented.');
  }
  editMode(value: boolean): this {
    throw new Error('Method not implemented.');
  }
  multiSelectable(value: boolean): this {
    throw new Error('Method not implemented.');
  }
  maxCount(value: number): this {
    throw new Error('Method not implemented.');
  }
  minCount(value: number): this {
    throw new Error('Method not implemented.');
  }
  cellLength(value: number): this {
    throw new Error('Method not implemented.');
  }
  layoutDirection(value: GridDirection): this {
    throw new Error('Method not implemented.');
  }
  supportAnimation(value: boolean): this {
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
  edgeEffect(value: EdgeEffect, options?: EdgeEffectOptions | undefined): this {
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
  onScrollFrameBegin(event: (offset: number, state: ScrollState) => { offsetRemain: number; }): this {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error('Method not implemented.');
  }
}

// @ts-ignore
globalThis.Grid.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkGridComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}

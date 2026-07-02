/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

class LazyArkGridComponent extends ArkScrollable {
  static module: GridComponentModule | undefined = undefined;

  constructor(nativePtr: KNode, classType: ModifierType) {
   super(nativePtr, classType);
   if (LazyArkGridComponent.module === undefined) {
     LazyArkGridComponent.module = globalThis.requireNapi('arkui.components.arkgrid');
   }

   this.lazyComponent = LazyArkGridComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
   this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  initialize(value: Object[]): this {
    this.lazyComponent.initialize(value);
    return this;
  }
  columnsTemplate(value: string | ItemFillPolicy): this {
    this.lazyComponent.columnsTemplate(value);
    return this;
  }
  rowsTemplate(value: string): this {
    this.lazyComponent.rowsTemplate(value);
    return this;
  }
  columnsGap(value: Length): this {
    this.lazyComponent.columnsGap(value);
    return this;
  }
  rowsGap(value: Length): this {
    this.lazyComponent.rowsGap(value);
    return this;
  }
  scrollBarWidth(value: string | number | Resource): this {
    this.lazyComponent.scrollBarWidth(value);
    return this;
  }
  scrollBarColor(value: string | number | Color): this {
    this.lazyComponent.scrollBarColor(value);
    return this;
  }
  scrollBar(value: BarState): this {
    this.lazyComponent.scrollBar(value);
    return this;
  }
  onScrollBarUpdate(event: (index: number, offset: number) => ComputedBarAttribute): this {
    this.lazyComponent.onScrollBarUpdate(event);
    return this;
  }
  onScrollIndex(event: (first: number, last: number) => void): this {
    this.lazyComponent.onScrollIndex(event);
    return this;
  }
  cachedCount(count: number, show?: boolean): this {
    this.lazyComponent.cachedCount(count, show);
    return this;
  }
  editMode(value: boolean): this {
    this.lazyComponent.editMode(value);
    return this;
  }
  multiSelectable(value: boolean): this {
    this.lazyComponent.multiSelectable(value);
    return this;
  }
  maxCount(value: number): this {
    this.lazyComponent.maxCount(value);
    return this;
  }
  minCount(value: number): this {
    this.lazyComponent.minCount(value);
    return this;
  }
  cellLength(value: number): this {
    this.lazyComponent.cellLength(value);
    return this;
  }
  layoutDirection(value: GridDirection): this {
    this.lazyComponent.layoutDirection(value);
    return this;
  }
  supportAnimation(value: boolean): this {
    this.lazyComponent.supportAnimation(value);
    return this;
  }
  onItemDragStart(event: (event: ItemDragInfo, itemIndex: number) => void | (() => any)): this {
    this.lazyComponent.onItemDragStart(event);
    return this;
  }
  onItemDragEnter(event: (event: ItemDragInfo) => void): this {
    this.lazyComponent.onItemDragEnter(event);
    return this;
  }
  onItemDragMove(event: (event: ItemDragInfo, itemIndex: number, insertIndex: number) => void): this {
    this.lazyComponent.onItemDragMove(event);
    return this;
  }
  onItemDragLeave(event: (event: ItemDragInfo, itemIndex: number) => void): this {
    this.lazyComponent.onItemDragLeave(event);
    return this;
  }
  onItemDrop(event: (event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void): this {
    this.lazyComponent.onItemDrop(event);
    return this;
  }
  nestedScroll(value: NestedScrollOptions): this {
    this.lazyComponent.nestedScroll(value);
    return this;
  }
  enableScrollInteraction(value: boolean): this {
    this.lazyComponent.enableScrollInteraction(value);
    return this;
  }
  friction(value: number | Resource): this {
    this.lazyComponent.friction(value);
    return this;
  }
  focusWrapMode(value: FocusWrapMode): this {
    this.lazyComponent.focusWrapMode(value);
    return this;
  }
  onScroll(event: (scrollOffset: number, scrollState: ScrollState) => void): this {
    this.lazyComponent.onScroll(event);
    return this;
  }
  onReachStart(event: () => void): this {
    this.lazyComponent.onReachStart(event);
    return this;
  }
  onReachEnd(event: () => void): this {
    this.lazyComponent.onReachEnd(event);
    return this;
  }
  onScrollStart(event: () => void): this {
    this.lazyComponent.onScrollStart(event);
    return this;
  }
  onScrollStop(event: () => void): this {
    this.lazyComponent.onScrollStop(event);
    return this;
  }
  onScrollFrameBegin(callback: (offset: number, state: ScrollState) => { offsetRemain: number; }): this {
    this.lazyComponent.onScrollFrameBegin(callback);
    return this;
  }
  clip(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): this {
    this.lazyComponent.clip(value);
    return this;
  }
  alignItems(value: GridItemAlignment): this {
    this.lazyComponent.alignItems(value);
    return this;
  }
  syncLoad(value: boolean): this {
    this.lazyComponent.syncLoad(value);
    return this;
  }
  editModeOptions(options: EditModeOptions | undefined): this {
    this.lazyComponent.editModeOptions(options);
    return this;
  }
  onEditModeChange(callback: Callback<boolean> | undefined): this {
    this.lazyComponent.onEditModeChange(callback);
    return this;
  }
  enableEditMode(value: boolean): this {
    this.lazyComponent.enableEditMode(value);
    return this;
  }
  onWillScroll(callback: (xOffset: number, yOffset: number,
    scrollState: ScrollState, scrollSource: ScrollSource) => void | OffsetResult): this {
    this.lazyComponent.onWillScroll(callback);
    return this;
  }
  onDidScroll(callback: (xOffset: number, yOffset: number, scrollState: ScrollState) => void): this {
    this.lazyComponent.onDidScroll(callback);
    return this;
  }
  supportEmptyBranchInLazyLoading(value: any): this {
    this.lazyComponent.supportEmptyBranchInLazyLoading(value);
    return this;
  }
}
class GridModifier extends LazyArkGridComponent implements AttributeModifier<GridAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: GridAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<GridAttribute, ArkGridComponent, ArkComponent>(instance, this);
  }
}

/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

/// <reference path='./import.ts' />

import { ArkScrollable } from "./ArkScrollable";

class ArkGridComponent extends ArkScrollable<GridAttribute> implements GridAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  allowChildTypes(): string[] {
    return ['GridItem'];
  }
  initialize(value: Object[]): void {
    if (value.length === 1 && isObject(value[0])) {
      modifierWithKey(this._modifiersWithKeys, GridScrollerModifier.identity, GridScrollerModifier, value[0]);
      modifierWithKey(this._modifiersWithKeys, GridLayoutOptionsModifier.identity, GridLayoutOptionsModifier, undefined);
    } else if (value.length === 2 && isObject(value[0]) && isObject(value[1])) {
      modifierWithKey(this._modifiersWithKeys, GridScrollerModifier.identity, GridScrollerModifier, value[0]);
      modifierWithKey(this._modifiersWithKeys, GridLayoutOptionsModifier.identity, GridLayoutOptionsModifier, value[1]);
    } else {
      modifierWithKey(this._modifiersWithKeys, GridScrollerModifier.identity, GridScrollerModifier, undefined);
      modifierWithKey(this._modifiersWithKeys, GridLayoutOptionsModifier.identity, GridLayoutOptionsModifier, undefined);
    }
  }
  columnsTemplate(value: string): this {
    modifierWithKey(this._modifiersWithKeys, GridColumnsTemplateModifier.identity, GridColumnsTemplateModifier, value);
    return this;
  }
  rowsTemplate(value: string): this {
    modifierWithKey(this._modifiersWithKeys, GridRowsTemplateModifier.identity, GridRowsTemplateModifier, value);
    return this;
  }
  columnsGap(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, GridColumnsGapModifier.identity, GridColumnsGapModifier, value);
    return this;
  }
  rowsGap(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, GridRowsGapModifier.identity, GridRowsGapModifier, value);
    return this;
  }
  scrollBarWidth(value: string | number): this {
    modifierWithKey(this._modifiersWithKeys, GridScrollBarWidthModifier.identity, GridScrollBarWidthModifier, value);
    return this;
  }
  scrollBarColor(value: string | number | Color): this {
    modifierWithKey(this._modifiersWithKeys, GridScrollBarColorModifier.identity, GridScrollBarColorModifier, value);
    return this;
  }
  scrollBar(value: BarState): this {
    modifierWithKey(this._modifiersWithKeys, GridScrollBarModifier.identity, GridScrollBarModifier, value);
    return this;
  }
  onScrollBarUpdate(event: (index: number, offset: number) => ComputedBarAttribute): this {
    modifierWithKey(this._modifiersWithKeys, GridOnScrollBarUpdateModifier.identity, GridOnScrollBarUpdateModifier, event);
    return this;
  }
  onScrollIndex(event: (first: number, last: number) => void): this {
    modifierWithKey(this._modifiersWithKeys, GridOnScrollIndexModifier.identity, GridOnScrollIndexModifier, event);
    return this;
  }
  cachedCount(count: number, show?: boolean): GridAttribute {
    let opt = new ArkScrollableCacheOptions(count, show ? show : false);
    modifierWithKey(this._modifiersWithKeys, GridCachedCountModifier.identity, GridCachedCountModifier, opt);
    return this;
  }
  editMode(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, GridEditModeModifier.identity, GridEditModeModifier, value);
    return this;
  }
  multiSelectable(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, GridMultiSelectableModifier.identity, GridMultiSelectableModifier, value);
    return this;
  }
  maxCount(value: number): this {
    modifierWithKey(this._modifiersWithKeys, GridMaxCountModifier.identity, GridMaxCountModifier, value);
    return this;
  }
  minCount(value: number): this {
    modifierWithKey(this._modifiersWithKeys, GridMinCountModifier.identity, GridMinCountModifier, value);
    return this;
  }
  cellLength(value: number): this {
    modifierWithKey(this._modifiersWithKeys, GridCellLengthModifier.identity, GridCellLengthModifier, value);
    return this;
  }
  layoutDirection(value: GridDirection): this {
    modifierWithKey(this._modifiersWithKeys, GridLayoutDirectionModifier.identity, GridLayoutDirectionModifier, value);
    return this;
  }
  supportAnimation(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, GridSupportAnimationModifier.identity, GridSupportAnimationModifier, value);
    return this;
  }
  onItemDragStart(event: (event: ItemDragInfo, itemIndex: number) => void | (() => any)): this {
    modifierWithKey(this._modifiersWithKeys, GridOnItemDragStartModifier.identity, GridOnItemDragStartModifier, event);
    return this;
  }
  onItemDragEnter(event: (event: ItemDragInfo) => void): this {
    modifierWithKey(this._modifiersWithKeys, GridOnItemDragEnterModifier.identity, GridOnItemDragEnterModifier, event);
    return this;
  }
  onItemDragMove(event: (event: ItemDragInfo, itemIndex: number, insertIndex: number) => void): this {
    modifierWithKey(this._modifiersWithKeys, GridOnItemDragMoveModifier.identity, GridOnItemDragMoveModifier, event);
    return this;
  }
  onItemDragLeave(event: (event: ItemDragInfo, itemIndex: number) => void): this {
    modifierWithKey(this._modifiersWithKeys, GridOnItemDragLeaveModifier.identity, GridOnItemDragLeaveModifier, event);
    return this;
  }
  onItemDrop(event: (event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void): this {
    modifierWithKey(this._modifiersWithKeys, GridOnItemDropModifier.identity, GridOnItemDropModifier, event);
    return this;
  }
  nestedScroll(value: NestedScrollOptions): this {
    modifierWithKey(this._modifiersWithKeys, GridNestedScrollModifier.identity, GridNestedScrollModifier, value);
    return this;
  }
  enableScrollInteraction(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, GridEnableScrollModifier.identity, GridEnableScrollModifier, value);
    return this;
  }
  friction(value: number | Resource): this {
    modifierWithKey(this._modifiersWithKeys, GridFrictionModifier.identity, GridFrictionModifier, value);
    return this;
  }
  focusWrapMode(value: FocusWrapMode): this {
    modifierWithKey(this._modifiersWithKeys, GridFocusWrapModeModifier.identity, GridFocusWrapModeModifier, value);
    return this;
  }
  onScroll(event: (scrollOffset: number, scrollState: ScrollState) => void): this {
    throw new Error('Method not implemented.');
  }
  onReachStart(event: () => void): this {
    modifierWithKey(this._modifiersWithKeys, GridOnReachStartModifier.identity, GridOnReachStartModifier, event);
    return this;
  }
  onReachEnd(event: () => void): this {
    modifierWithKey(this._modifiersWithKeys, GridOnReachEndModifier.identity, GridOnReachEndModifier, event);
    return this;
  }
  onScrollStart(event: () => void): this {
    modifierWithKey(this._modifiersWithKeys, GridOnScrollStartModifier.identity, GridOnScrollStartModifier, event);
    return this;
  }
  onScrollStop(event: () => void): this {
    modifierWithKey(this._modifiersWithKeys, GridOnScrollStopModifier.identity, GridOnScrollStopModifier, event);
    return this;
  }
  onScrollFrameBegin(callback: (offset: number, state: ScrollState) => { offsetRemain: number; }): this {
    modifierWithKey(this._modifiersWithKeys, GridOnScrollFrameBeginModifier.identity, GridOnScrollFrameBeginModifier, callback);
    return this;
  }
  clip(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): this {
    modifierWithKey(this._modifiersWithKeys, GridClipModifier.identity, GridClipModifier, value);
    return this;
  }
  flingSpeedLimit(value: number): this {
    modifierWithKey(this._modifiersWithKeys, GridFlingSpeedLimitModifier.identity, GridFlingSpeedLimitModifier, value);
    return this;
  }
  alignItems(value: GridItemAlignment): this {
    modifierWithKey(this._modifiersWithKeys, GridAlignItemsModifier.identity, GridAlignItemsModifier, value);
    return this;
  }
  onWillScroll(callback: (xOffset: number, yOffset: number,
    scrollState: ScrollState, scrollSource: ScrollSource) => void | OffsetResult): this {
    modifierWithKey(this._modifiersWithKeys, GridOnWillScrollModifier.identity, GridOnWillScrollModifier, callback);
    return this;
  }
  onDidScroll(callback: (xOffset: number, yOffset: number, scrollState: ScrollState) => void): this {
    modifierWithKey(this._modifiersWithKeys, GridOnDidScrollModifier.identity, GridOnDidScrollModifier, callback);
    return this;
  }
}

class GridScrollerModifier extends ModifierWithKey<Scroller> {
  constructor(value: Scroller) {
    super(value);
  }
  static identity: Symbol = Symbol('gridScroller');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.setGridScroller(node, undefined);
    } else {
      getUINativeModule().grid.setGridScroller(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class GridLayoutOptionsModifier extends ModifierWithKey<GridLayoutOptions> {
  constructor(value: GridLayoutOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('gridLayoutOptions');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.setGridLayoutOptions(node, undefined, undefined, undefined, undefined, undefined);
    } else {
      getUINativeModule().grid.setGridLayoutOptions(node,
        isArray(this.value.regularSize) ? this.value.regularSize : undefined,
        isArray(this.value?.irregularIndexes) ? this.value.irregularIndexes : undefined,
        isArray(this.value?.irregularIndexes) ? this.value.irregularIndexes.length : undefined,
        isFunction(this.value?.onGetIrregularSizeByIndex) ? this.value.onGetIrregularSizeByIndex : undefined,
        isFunction(this.value?.onGetRectByIndex) ? this.value.onGetRectByIndex : undefined);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue?.regularSize, this.value?.regularSize) ||
      !isBaseOrResourceEqual(this.stageValue?.irregularIndexes, this.value?.irregularIndexes) ||
      !isBaseOrResourceEqual(this.stageValue?.onGetIrregularSizeByIndex, this.value?.onGetIrregularSizeByIndex) ||
      !isBaseOrResourceEqual(this.stageValue?.onGetRectByIndex, this.value?.onGetRectByIndex);
  }
}

class GridColumnsTemplateModifier extends ModifierWithKey<string> {
  constructor(value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('gridColumnsTemplate');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetColumnsTemplate(node);
    } else {
      getUINativeModule().grid.setColumnsTemplate(node, this.value);
    }
  }
}

class GridRowsTemplateModifier extends ModifierWithKey<string> {
  constructor(value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('gridRowsTemplate');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetRowsTemplate(node);
    } else {
      getUINativeModule().grid.setRowsTemplate(node, this.value);
    }
  }
}

class GridColumnsGapModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('gridColumnsGap');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetColumnsGap(node);
    } else {
      getUINativeModule().grid.setColumnsGap(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class GridRowsGapModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('gridRowsGap');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetRowsGap(node);
    } else {
      getUINativeModule().grid.setRowsGap(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class GridScrollBarWidthModifier extends ModifierWithKey<string | number> {
  constructor(value: string | number) {
    super(value);
  }
  static identity: Symbol = Symbol('gridScrollBarWidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetScrollBarWidth(node);
    } else {
      getUINativeModule().grid.setScrollBarWidth(node, this.value);
    }
  }
}

class GridScrollBarModifier extends ModifierWithKey<BarState> {
  constructor(value: BarState) {
    super(value);
  }
  static identity: Symbol = Symbol('gridScrollBar');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetScrollBar(node);
    } else {
      getUINativeModule().grid.setScrollBar(node, this.value);
    }
  }
}

class GridScrollBarColorModifier extends ModifierWithKey<string | number | Color> {
  constructor(value: string | number | Color) {
    super(value);
  }
  static identity: Symbol = Symbol('gridScrollBarColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetScrollBarColor(node);
    } else {
      getUINativeModule().grid.setScrollBarColor(node, this.value);
    }
  }
}

class GridEditModeModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('gridEditMode');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetEditMode(node);
    } else {
      getUINativeModule().grid.setEditMode(node, this.value);
    }
  }
}

class GridCachedCountModifier extends ModifierWithKey<ArkScrollableCacheOptions> {
  constructor(value: ArkScrollableCacheOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('gridCachedCount');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetCachedCount(node);
    } else {
      getUINativeModule().grid.setCachedCount(node, this.value.count, this.value.show);
    }
  }
}

class GridMultiSelectableModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('gridMultiSelectable');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetMultiSelectable(node);
    } else {
      getUINativeModule().grid.setMultiSelectable(node, this.value);
    }
  }
}

class GridNestedScrollModifier extends ModifierWithKey<NestedScrollOptions> {
  constructor(value: NestedScrollOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('gridNestedScroll');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetNestedScroll(node);
    } else {
      getUINativeModule().grid.setNestedScroll(node, this.value?.scrollForward, this.value?.scrollBackward);
    }
  }

  checkObjectDiff(): boolean {
    return !((this.stageValue.scrollForward === this.value.scrollForward) &&
      (this.stageValue.scrollBackward === this.value.scrollBackward));
  }
}

class GridEnableScrollModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('gridEnableScroll');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetEnableScroll(node);
    } else {
      getUINativeModule().grid.setEnableScroll(node, this.value);
    }
  }
}

class GridFrictionModifier extends ModifierWithKey<number | Resource> {
  constructor(value: number | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('gridFriction');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetFriction(node);
    } else {
      getUINativeModule().grid.setFriction(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class GridFocusWrapModeModifier extends ModifierWithKey<FocusWrapMode> {
  constructor(value: FocusWrapMode) {
    super(value);
  }
  static identity: Symbol = Symbol('gridFocusWrapMode');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetFocusWrapMode(node);
    } else {
      getUINativeModule().grid.setFocusWrapMode(node, this.value);
    }
  }
}

class GridOnScrollFrameBeginModifier extends ModifierWithKey<(offset: number, state: ScrollState) => { offsetRemain: number }> {
  constructor(value: (offset: number, state: ScrollState) => { offsetRemain: number; }) {
    super(value);
  }
  static identity: Symbol = Symbol('gridOnScrollFrameBegin');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetOnScrollFrameBegin(node);
    } else {
      getUINativeModule().grid.setOnScrollFrameBegin(node, this.value);
    }
  }
}

class GridOnWillScrollModifier extends ModifierWithKey<(xOffset: number, yOffset: number,
  scrollState: ScrollState, scrollSource: ScrollSource) => void | OffsetResult> {
  constructor(value: (xOffset: number, yOffset: number,
    scrollState: ScrollState, scrollSource: ScrollSource) => void | OffsetResult) {
    super(value);
  }
  static identity: Symbol = Symbol('gridOnWillScroll');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetOnWillScroll(node);
    } else {
      getUINativeModule().grid.setOnWillScroll(node, this.value);
    }
  }
}

class GridOnDidScrollModifier extends ModifierWithKey<(xOffset: number, yOffset: number, scrollState: ScrollState) => void> {
  constructor(value: (xOffset: number, yOffset: number, scrollState: ScrollState) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('gridOnDidScroll');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetOnDidScroll(node);
    } else {
      getUINativeModule().grid.setOnDidScroll(node, this.value);
    }
  }
}

class GridOnReachStartModifier extends ModifierWithKey<() => void> {
  constructor(value: () => void) {
    super(value);
  }
  static identity: Symbol = Symbol('gridOnReachStart');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetOnReachStart(node);
    } else {
      getUINativeModule().grid.setOnReachStart(node, this.value);
    }
  }
}

class GridOnReachEndModifier extends ModifierWithKey<() => void> {
  constructor(value: () => void) {
    super(value);
  }
  static identity: Symbol = Symbol('gridOnReachEnd');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetOnReachEnd(node);
    } else {
      getUINativeModule().grid.setOnReachEnd(node, this.value);
    }
  }
}

class GridOnScrollStartModifier extends ModifierWithKey<() => void> {
  constructor(value: () => void) {
    super(value);
  }
  static identity: Symbol = Symbol('gridOnScrollStart');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetOnScrollStart(node);
    } else {
      getUINativeModule().grid.setOnScrollStart(node, this.value);
    }
  }
}

class GridOnScrollStopModifier extends ModifierWithKey<() => void> {
  constructor(value: () => void) {
    super(value);
  }
  static identity: Symbol = Symbol('gridOnScrollStop');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetOnScrollStop(node);
    } else {
      getUINativeModule().grid.setOnScrollStop(node, this.value);
    }
  }
}

class GridOnScrollBarUpdateModifier extends ModifierWithKey<(index: number, offset: number) => ComputedBarAttribute> {
  constructor(value: (index: number, offset: number) => ComputedBarAttribute) {
    super(value);
  }
  static identity: Symbol = Symbol('gridOnScrollBarUpdate');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetOnScrollBarUpdate(node);
    } else {
      getUINativeModule().grid.setOnScrollBarUpdate(node, this.value);
    }
  }
}

class GridOnScrollIndexModifier extends ModifierWithKey<(first: number, last: number) => void> {
  constructor(value: (first: number, last: number) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('gridOnScrollIndex');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetOnScrollIndex(node);
    } else {
      getUINativeModule().grid.setOnScrollIndex(node, this.value);
    }
  }
}

class GridOnItemDragStartModifier extends ModifierWithKey<(event: ItemDragInfo, itemIndex: number) => void | (() => any)> {
  constructor(value: (event: ItemDragInfo, itemIndex: number) => void | (() => any)) {
    super(value);
  }
  static identity: Symbol = Symbol('gridOnItemDragStart');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetOnItemDragStart(node);
    } else {
      getUINativeModule().grid.setOnItemDragStart(node, this.value);
    }
  }
}

class GridOnItemDragEnterModifier extends ModifierWithKey<(event: ItemDragInfo) => void> {
  constructor(value: (event: ItemDragInfo) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('gridOnItemDragEnter');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetOnItemDragEnter(node);
    } else {
      getUINativeModule().grid.setOnItemDragEnter(node, this.value);
    }
  }
}

class GridOnItemDragMoveModifier extends ModifierWithKey<(event: ItemDragInfo, itemIndex: number, insertIndex: number) => void> {
  constructor(value: (event: ItemDragInfo, itemIndex: number, insertIndex: number) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('gridOnItemDragMove');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetOnItemDragMove(node);
    } else {
      getUINativeModule().grid.setOnItemDragMove(node, this.value);
    }
  }
}

class GridOnItemDragLeaveModifier extends ModifierWithKey<(event: ItemDragInfo, itemIndex: number) => void> {
  constructor(value: (event: ItemDragInfo, itemIndex: number) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('gridOnItemDragLeave');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetOnItemDragLeave(node);
    } else {
      getUINativeModule().grid.setOnItemDragLeave(node, this.value);
    }
  }
}

class GridOnItemDropModifier extends ModifierWithKey<(event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void> {
  constructor(value: (event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('gridOnItemDrop');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetOnItemDrop(node);
    } else {
      getUINativeModule().grid.setOnItemDrop(node, this.value);
    }
  }
}

class GridMaxCountModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('gridMaxCount');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetMaxCount(node);
    } else {
      getUINativeModule().grid.setMaxCount(node, this.value);
    }
  }
}

class GridMinCountModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('gridMinCount');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetMinCount(node);
    } else {
      getUINativeModule().grid.setMinCount(node, this.value);
    }
  }
}

class GridCellLengthModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('gridCellLength');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetCellLength(node);
    } else {
      getUINativeModule().grid.setCellLength(node, this.value);
    }
  }
}

class GridLayoutDirectionModifier extends ModifierWithKey<GridDirection> {
  constructor(value: GridDirection) {
    super(value);
  }
  static identity: Symbol = Symbol('gridLayoutDirection');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetLayoutDirection(node);
    } else {
      getUINativeModule().grid.setLayoutDirection(node, this.value);
    }
  }
}

class GridSupportAnimationModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('gridSupportAnimation');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetSupportAnimation(node);
    } else {
      getUINativeModule().grid.setSupportAnimation(node, this.value);
    }
  }
}

class GridClipModifier extends ModifierWithKey<boolean | object> {
  constructor(value: boolean | object) {
    super(value);
  }
  static identity: Symbol = Symbol('gridClip');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().common.resetClipWithEdge(node);
    } else {
      getUINativeModule().common.setClipWithEdge(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return true;
  }
}

class GridFlingSpeedLimitModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('gridFlingSpeedLimit');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetFlingSpeedLimit(node);
    } else {
      getUINativeModule().grid.setFlingSpeedLimit(node, this.value);
    }
  }
}

class GridAlignItemsModifier extends ModifierWithKey<GridItemAlignment> {
  constructor(value: GridItemAlignment) {
    super(value);
  }
  static identity: Symbol = Symbol('gridAlignItems');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetAlignItems(node);
    } else {
      getUINativeModule().grid.setAlignItems(node, this.value);
    }
  }
}

// @ts-ignore
globalThis.Grid.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkGridComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.GridModifier(nativePtr, classType);
  });
};

globalThis.Grid.onScrollBarUpdate = function (value: (index: number, offset: number) => ComputedBarAttribute): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().grid.setOnScrollBarUpdate(nodePtr, value);
};
globalThis.Grid.onItemDragEnter = function (value: (event: ItemDragInfo) => void): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().grid.setOnItemDragEnter(nodePtr, value);
};
globalThis.Grid.onItemDragMove = function (value: (event: ItemDragInfo, itemIndex: number, insertIndex: number) => void): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().grid.setOnItemDragMove(nodePtr, value);
};
globalThis.Grid.onItemDragLeave = function (value: (event: ItemDragInfo, itemIndex: number) => void): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().grid.setOnItemDragLeave(nodePtr, value);
};
globalThis.Grid.onItemDragStart = function (value: (event: ItemDragInfo, itemIndex: number) => void | (() => any)): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().grid.setOnItemDragStart(nodePtr, value);
};
globalThis.Grid.onItemDrop = function (value: (event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().grid.setOnItemDrop(nodePtr, value);
};
globalThis.Grid.onReachStart = function (value: () => void): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().grid.setOnReachStart(nodePtr, value);
};
globalThis.Grid.onReachEnd = function (value: () => void): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().grid.setOnReachEnd(nodePtr, value);
};
globalThis.Grid.onScrollStart = function (value: () => void): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().grid.setOnScrollStart(nodePtr, value);
};
globalThis.Grid.onScrollStop = function (value: () => void): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().grid.setOnScrollStop(nodePtr, value);
};
globalThis.Grid.onScrollIndex = function (value: (first: number, last: number) => void): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().grid.setOnScrollIndex(nodePtr, value);
};
globalThis.Grid.onScrollFrameBegin = function (value: (offset: number, state: ScrollState) => { offsetRemain: number; }): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().grid.setOnScrollFrameBegin(nodePtr, value);
};
globalThis.Grid.onWillScroll = function (value: (xOffset: number, yOffset: number,
  scrollState: ScrollState, scrollSource: ScrollSource) => void | OffsetResult): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().grid.setOnWillScroll(nodePtr, value);
};
globalThis.Grid.onDidScroll = function (value: (xOffset: number, yOffset: number, scrollState: ScrollState) => void): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().grid.setOnDidScroll(nodePtr, value);
};
globalThis.Grid.onWillStopDragging = function (value: (velocity: number) => void) {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().scrollable.setOnWillStopDragging(nodePtr, value);
};

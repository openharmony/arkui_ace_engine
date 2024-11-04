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
    throw new Error('Method not implemented.');
  }
  onScrollIndex(event: (first: number, last: number) => void): this {
    throw new Error('Method not implemented.');
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
    let effect: ArkGridEdgeEffect = new ArkGridEdgeEffect();
    effect.value = value;
    effect.options = options;
    modifierWithKey(this._modifiersWithKeys, GridEdgeEffectModifier.identity, GridEdgeEffectModifier, effect);
    return this;
  }
  fadingEdge(value: boolean, options?: FadingEdgeOptions | undefined): this {
    let fadingEdge: ArkFadingEdge = new ArkFadingEdge();
    fadingEdge.value = value;
    fadingEdge.options = options;
    modifierWithKey(this._modifiersWithKeys, GridFadingEdgeModifier.identity, GridFadingEdgeModifier, fadingEdge);
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

class GridEdgeEffectModifier extends ModifierWithKey<ArkGridEdgeEffect> {
  constructor(value: ArkGridEdgeEffect) {
    super(value);
  }
  static identity: Symbol = Symbol('gridEdgeEffect');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetEdgeEffect(node);
    } else {
      getUINativeModule().grid.setEdgeEffect(node, this.value?.value, this.value.options?.alwaysEnabled);
    }
  }

  checkObjectDiff(): boolean {
    return !((this.stageValue.value === this.value.value) &&
      (this.stageValue.options === this.value.options));
  }
}

class GridFadingEdgeModifier extends ModifierWithKey<ArkFadingEdge> {
  constructor(value: ArkFadingEdge) {
    super(value);
  }
  static identity: Symbol = Symbol('gridFadingEdge');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().grid.resetFadingEdge(node);
    } else {
      getUINativeModule().grid.setFadingEdge(node, this.value.value!, this.value.options?.fadingEdgeLength);
    }
  }
  checkObjectDiff(): boolean {
    return !((this.stageValue.value === this.value.value) &&
      (this.stageValue.options === this.value.options));
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

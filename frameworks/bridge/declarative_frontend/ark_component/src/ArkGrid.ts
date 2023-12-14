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
class ArkGridComponent extends ArkComponent implements GridAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
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
  cachedCount(value: number): this {
    modifierWithKey(this._modifiersWithKeys, GridCachedCountModifier.identity, GridCachedCountModifier, value);
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
  monopolizeEvents(monopolize: boolean): this {
    throw new Error('Method not implemented.');
  }
}

class GridColumnsTemplateModifier extends ModifierWithKey<string> {
  constructor(value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('gridColumnsTemplate');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().grid.resetColumnsTemplate(node);
    }
    else {
      GetUINativeModule().grid.setColumnsTemplate(node, this.value);
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
      GetUINativeModule().grid.resetRowsTemplate(node);
    }
    else {
      GetUINativeModule().grid.setRowsTemplate(node, this.value);
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
      GetUINativeModule().grid.resetColumnsGap(node);
    } else {
      GetUINativeModule().grid.setColumnsGap(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !(this.stageValue === this.value);
    } else {
      return true;
    }
  }
}

class GridRowsGapModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('gridRowsGap');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().grid.resetRowsGap(node);
    } else {
      GetUINativeModule().grid.setRowsGap(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !(this.stageValue === this.value);
    } else {
      return true;
    }
  }
}

class GridScrollBarWidthModifier extends ModifierWithKey<string | number> {
  constructor(value: string | number) {
    super(value);
  }
  static identity: Symbol = Symbol('gridScrollBarWidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().grid.resetScrollBarWidth(node);
    }
    else {
      GetUINativeModule().grid.setScrollBarWidth(node, this.value);
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
      GetUINativeModule().grid.resetScrollBar(node);
    }
    else {
      GetUINativeModule().grid.setScrollBar(node, this.value);
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
      GetUINativeModule().grid.resetScrollBarColor(node);
    }
    else {
      GetUINativeModule().grid.setScrollBarColor(node, this.value);
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
      GetUINativeModule().grid.resetEditMode(node);
    }
    else {
      GetUINativeModule().grid.setEditMode(node, this.value);
    }
  }
}

class GridCachedCountModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('gridCachedCount');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().grid.resetCachedCount(node);
    }
    else {
      GetUINativeModule().grid.setCachedCount(node, this.value);
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
      GetUINativeModule().grid.resetMultiSelectable(node);
    }
    else {
      GetUINativeModule().grid.setMultiSelectable(node, this.value);
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
      GetUINativeModule().grid.resetEdgeEffect(node);
    } else {
      GetUINativeModule().grid.setEdgeEffect(node, this.value?.value, this.value.options?.alwaysEnabled);
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
      GetUINativeModule().grid.resetNestedScroll(node);
    } else {
      GetUINativeModule().grid.setNestedScroll(node, this.value?.scrollForward, this.value?.scrollBackward);
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
      GetUINativeModule().grid.resetEnableScroll(node);
    } else {
      GetUINativeModule().grid.setEnableScroll(node, this.value);
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
      GetUINativeModule().grid.resetFriction(node);
    } else {
      GetUINativeModule().grid.setFriction(node, this.value);
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
      GetUINativeModule().grid.resetMaxCount(node);
    }
    else {
      GetUINativeModule().grid.setMaxCount(node, this.value);
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
      GetUINativeModule().grid.resetMinCount(node);
    }
    else {
      GetUINativeModule().grid.setMinCount(node, this.value);
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
      GetUINativeModule().grid.resetCellLength(node);
    }
    else {
      GetUINativeModule().grid.setCellLength(node, this.value);
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
      GetUINativeModule().grid.resetLayoutDirection(node);
    }
    else {
      GetUINativeModule().grid.setLayoutDirection(node, this.value);
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
      GetUINativeModule().grid.resetSupportAnimation(node);
    }
    else {
      GetUINativeModule().grid.setSupportAnimation(node, this.value);
    }
  }
}

// @ts-ignore
globalThis.Grid.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkGridComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
}

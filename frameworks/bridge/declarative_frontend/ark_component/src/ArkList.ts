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
class ListEditModeModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('editMode');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().list.resetEditMode(node);
    } else {
      GetUINativeModule().list.setEditMode(node, this.value!);
    }
  }
}

class ListMultiSelectableModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('listMultiSelectable');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().list.resetMultiSelectable(node);
    } else {
      GetUINativeModule().list.setMultiSelectable(node, this.value!);
    }
  }
}

class ListAlignListItemModifier extends ModifierWithKey<ListItemAlign> {
  constructor(value: ListItemAlign) {
    super(value);
  }
  static identity: Symbol = Symbol('listAlignListItem');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().list.resetAlignListItem(node);
    } else {
      GetUINativeModule().list.setAlignListItem(node, this.value!);
    }
  }
}

class ListScrollSnapAlignModifier extends ModifierWithKey<ScrollSnapAlign> {
  constructor(value: ScrollSnapAlign) {
    super(value);
  }
  static identity: Symbol = Symbol('listScrollSnapAlign');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().list.resetScrollSnapAlign(node);
    } else {
      GetUINativeModule().list.setScrollSnapAlign(node, this.value!);
    }
  }
}

class ListDividerModifier extends ModifierWithKey<{ strokeWidth: any; color?: any; startMargin?: any; endMargin?: any; } | null> {
  constructor(value: { strokeWidth: any; color?: any; startMargin?: any; endMargin?: any; } | null) {
    super(value);
  }
  static identity: Symbol = Symbol('listDivider');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().list.resetDivider(node);
    } else {
      GetUINativeModule().list.setDivider(node, this.value?.strokeWidth!, this.value?.color, this.value?.startMargin, this.value?.endMargin);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.strokeWidth, this.value.strokeWidth);
  }
}

class ChainAnimationOptionsModifier extends ModifierWithKey<ChainAnimationOptions> {
  constructor(value: ChainAnimationOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('chainAnimationOptions');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().list.resetChainAnimationOptions(node);
    } else {
      GetUINativeModule().list.setChainAnimationOptions(node, this.value?.minSpace!, this.value?.maxSpace!, this.value?.conductivity, this.value?.intensity, this.value?.edgeEffect, this.value?.stiffness, this.value?.damping);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.minSpace, this.value.minSpace) || !isBaseOrResourceEqual(this.stageValue.maxSpace, this.value.maxSpace) ||
    !isBaseOrResourceEqual(this.stageValue.conductivity, this.value.conductivity) || !isBaseOrResourceEqual(this.stageValue.intensity, this.value.intensity) ||
    !isBaseOrResourceEqual(this.stageValue.edgeEffect, this.value.edgeEffect) || !isBaseOrResourceEqual(this.stageValue.stiffness, this.value.stiffness) ||
    !isBaseOrResourceEqual(this.stageValue.damping, this.value.damping);
}
}

class ListChainAnimationModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('listChainAnimation');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().list.resetChainAnimation(node);
    } else {
      GetUINativeModule().list.setChainAnimation(node, this.value!);
    }
  }
}

class ListCachedCountModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('listCachedCount');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().list.resetCachedCount(node);
    } else {
      GetUINativeModule().list.setCachedCount(node, this.value!);
    }
  }
}

class ListEnableScrollInteractionModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('listEnableScrollInteraction');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().list.resetEnableScrollInteraction(node);
    } else {
      GetUINativeModule().list.setEnableScrollInteraction(node, this.value!);
    }
  }
}

class ListStickyModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('listSticky');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().list.resetSticky(node);
    } else {
      GetUINativeModule().list.setSticky(node, this.value!);
    }
  }
}

class ListEdgeEffectModifier extends ModifierWithKey<ArkListEdgeEffect> {
  constructor(value: ArkListEdgeEffect) {
    super(value);
  }
  static identity: Symbol = Symbol('listEdgeEffect');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().list.resetListEdgeEffect(node);
    } else {
      GetUINativeModule().list.setListEdgeEffect(node, this.value.value!, this.value.options?.alwaysEnabled);
    }
  }
  checkObjectDiff(): boolean {
    return !((this.stageValue.value === this.value.value) &&
      (this.stageValue.options === this.value.options));
  }
}

class ListListDirectionModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('listListDirection');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().list.resetListDirection(node);
    } else {
      GetUINativeModule().list.setListDirection(node, this.value!);
    }
  }
}

class ListFrictionModifier extends ModifierWithKey<number | Resource> {
  constructor(value: number | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('listFriction');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().list.resetListFriction(node);
    } else {
      if (!isNumber(this.value) && !isResource(this.value)) {
        GetUINativeModule().list.resetListFriction(node);
      } else {
        GetUINativeModule().list.setListFriction(node, this.value);
      }
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

class ListNestedScrollModifier extends ModifierWithKey<NestedScrollOptions> {
  constructor(value: NestedScrollOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('listNestedScroll');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().list.resetListNestedScroll(node);
    } else {
      GetUINativeModule().list.setListNestedScroll(node, this.value?.scrollForward, this.value?.scrollBackward);
    }
  }
}

class ListScrollBarModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('listScrollBar');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().list.resetListScrollBar(node);
    } else {
      GetUINativeModule().list.setListScrollBar(node, this.value!);
    }
  }
}

class ListLanesModifier extends ModifierWithKey<ArkLanesOpt> {
  constructor(value: ArkLanesOpt) {
    super(value);
  }
  static identity: Symbol = Symbol('listLanes');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().list.resetListLanes(node);
    } else {
      GetUINativeModule().list.setListLanes(node, this.value.lanesNum,
        this.value.minLength, this.value.maxLength, this.value.gutter);
    }
  }
  checkObjectDiff(): boolean {
    return true;
  }
}

class ArkListComponent extends ArkComponent implements ListAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  lanes(value: number | LengthConstrain, gutter?: any): this {
    let opt: ArkLanesOpt = new ArkLanesOpt();
    opt.gutter = gutter;
    opt.lanesNum = value as number;
    const lc = value as LengthConstrain;
    opt.minLength = lc.minLength;
    opt.maxLength = lc.maxLength;
    modifierWithKey(this._modifiersWithKeys, ListLanesModifier.identity, ListLanesModifier, opt);
    return this;
  }
  alignListItem(value: ListItemAlign): this {
    modifierWithKey(this._modifiersWithKeys, ListAlignListItemModifier.identity, ListAlignListItemModifier, value);
    return this;
  }
  listDirection(value: Axis): this {
    modifierWithKey(this._modifiersWithKeys, ListListDirectionModifier.identity, ListListDirectionModifier, value);
    return this;
  }
  scrollBar(value: BarState): this {
    modifierWithKey(this._modifiersWithKeys, ListScrollBarModifier.identity, ListScrollBarModifier, value);
    return this;
  }
  edgeEffect(value: EdgeEffect, options?: EdgeEffectOptions | undefined): this {
    let effect: ArkListEdgeEffect = new ArkListEdgeEffect();
    effect.value = value;
    effect.options = options;
    modifierWithKey(this._modifiersWithKeys, ListEdgeEffectModifier.identity, ListEdgeEffectModifier, effect);
    return this;
  }
  contentStartOffset(value: number): this {
    throw new Error('Method not implemented.');
  }
  contentEndOffset(value: number): this {
    throw new Error('Method not implemented.');
  }
  divider(value: { strokeWidth: any; color?: any; startMargin?: any; endMargin?: any; } | null): this {
    modifierWithKey(this._modifiersWithKeys, ListDividerModifier.identity, ListDividerModifier, value);
    return this;
  }
  editMode(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, ListEditModeModifier.identity, ListEditModeModifier, value);
    return this;
  }
  multiSelectable(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, ListMultiSelectableModifier.identity, ListMultiSelectableModifier, value);
    return this;
  }
  cachedCount(value: number): this {
    modifierWithKey(this._modifiersWithKeys, ListCachedCountModifier.identity, ListCachedCountModifier, value);
    return this;
  }
  chainAnimation(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, ListChainAnimationModifier.identity, ListChainAnimationModifier, value);
    return this;
  }
  chainAnimationOptions(value: ChainAnimationOptions): this {
    modifierWithKey(this._modifiersWithKeys, ChainAnimationOptionsModifier.identity, ChainAnimationOptionsModifier, value);
    return this;
  }
  sticky(value: StickyStyle): this {
    modifierWithKey(this._modifiersWithKeys, ListStickyModifier.identity, ListStickyModifier, value);
    return this;
  }
  scrollSnapAlign(value: ScrollSnapAlign): this {
    modifierWithKey(this._modifiersWithKeys, ListScrollSnapAlignModifier.identity, ListScrollSnapAlignModifier, value);
    return this;
  }
  nestedScroll(value: NestedScrollOptions): this {
    modifierWithKey(this._modifiersWithKeys, ListNestedScrollModifier.identity, ListNestedScrollModifier, value);
    return this;
  }
  enableScrollInteraction(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, ListEnableScrollInteractionModifier.identity, ListEnableScrollInteractionModifier, value);
    return this;
  }
  friction(value: any): this {
    modifierWithKey(this._modifiersWithKeys, ListFrictionModifier.identity, ListFrictionModifier, value);
    return this;
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
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
}

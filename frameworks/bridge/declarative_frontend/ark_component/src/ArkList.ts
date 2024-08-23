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
      getUINativeModule().list.resetEditMode(node);
    } else {
      getUINativeModule().list.setEditMode(node, this.value!);
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
      getUINativeModule().list.resetMultiSelectable(node);
    } else {
      getUINativeModule().list.setMultiSelectable(node, this.value!);
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
      getUINativeModule().list.resetAlignListItem(node);
    } else {
      getUINativeModule().list.setAlignListItem(node, this.value!);
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
      getUINativeModule().list.resetScrollSnapAlign(node);
    } else {
      getUINativeModule().list.setScrollSnapAlign(node, this.value!);
    }
  }
}

class ContentStartOffsetModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('contentStartOffset');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().list.resetContentStartOffset(node);
    } else {
      getUINativeModule().list.setContentStartOffset(node, this.value);
    }
  }
}

class ContentEndOffsetModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('contentEndOffset');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().list.resetContentEndOffset(node);
    } else {
      getUINativeModule().list.setContentEndOffset(node, this.value);
    }
  }
}

class ListDividerModifier extends ModifierWithKey<DividerStyle> {
  constructor(value: DividerStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('listDivider');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().list.resetDivider(node);
    } else {
      getUINativeModule().list.setDivider(node, this.value?.strokeWidth!, this.value?.color, this.value?.startMargin, this.value?.endMargin);
    }
  }

  checkObjectDiff(): boolean {
    return !(this.stageValue?.strokeWidth === this.value?.strokeWidth &&
      this.stageValue?.color === this.value?.color &&
      this.stageValue?.startMargin === this.value?.startMargin &&
      this.stageValue?.endMargin === this.value?.endMargin);
  }
}

class ChainAnimationOptionsModifier extends ModifierWithKey<ChainAnimationOptions> {
  constructor(value: ChainAnimationOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('chainAnimationOptions');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().list.resetChainAnimationOptions(node);
    } else {
      getUINativeModule().list.setChainAnimationOptions(node, this.value?.minSpace!,
        this.value?.maxSpace!, this.value?.conductivity, this.value?.intensity,
        this.value?.edgeEffect, this.value?.stiffness, this.value?.damping);
    }
  }

  checkObjectDiff(): boolean {
    return !(this.stageValue.minSpace === this.value.minSpace && this.stageValue.maxSpace === this.value.maxSpace &&
      this.stageValue.conductivity === this.value.conductivity && this.stageValue.intensity === this.value.intensity &&
      this.stageValue.edgeEffect === this.value.edgeEffect && this.stageValue.stiffness === this.value.stiffness &&
      this.stageValue.damping === this.value.damping);
  }
}

class ListChainAnimationModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('listChainAnimation');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().list.resetChainAnimation(node);
    } else {
      getUINativeModule().list.setChainAnimation(node, this.value!);
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
      getUINativeModule().list.resetCachedCount(node);
    } else {
      getUINativeModule().list.setCachedCount(node, this.value!);
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
      getUINativeModule().list.resetEnableScrollInteraction(node);
    } else {
      getUINativeModule().list.setEnableScrollInteraction(node, this.value!);
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
      getUINativeModule().list.resetSticky(node);
    } else {
      getUINativeModule().list.setSticky(node, this.value!);
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
      getUINativeModule().list.resetListEdgeEffect(node);
    } else {
      getUINativeModule().list.setListEdgeEffect(node, this.value.value!, this.value.options?.alwaysEnabled);
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
      getUINativeModule().list.resetListDirection(node);
    } else {
      getUINativeModule().list.setListDirection(node, this.value!);
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
      getUINativeModule().list.resetListFriction(node);
    } else {
      if (!isNumber(this.value) && !isResource(this.value)) {
        getUINativeModule().list.resetListFriction(node);
      } else {
        getUINativeModule().list.setListFriction(node, this.value);
      }
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class ListMaintainVisibleContentPositionModifier extends ModifierWithKey<boolean | undefined> {
  constructor(value: boolean | undefined) {
    super(value);
  }
  static identity: Symbol = Symbol('listMaintainVisibleContentPosition');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().list.resetListMaintainVisibleContentPosition(node);
    } else {
      getUINativeModule().list.setListMaintainVisibleContentPosition(node, this.value);
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
      getUINativeModule().list.resetListNestedScroll(node);
    } else {
      getUINativeModule().list.setListNestedScroll(node, this.value?.scrollForward, this.value?.scrollBackward);
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
      getUINativeModule().list.resetListScrollBar(node);
    } else {
      getUINativeModule().list.setListScrollBar(node, this.value!);
    }
  }
}

class ListScrollBarWidthModifier extends ModifierWithKey<string | number> {
  constructor(value: string | number) {
    super(value);
  }
  static identity: Symbol = Symbol('listScrollBarWidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().list.resetScrollBarWidth(node);
    } else {
      getUINativeModule().list.setScrollBarWidth(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class ListScrollBarColorModifier extends ModifierWithKey<string | number | Color> {
  constructor(value: string | number | Color) {
    super(value);
  }
  static identity: Symbol = Symbol('listScrollBarColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().list.resetScrollBarColor(node);
    } else {
      getUINativeModule().list.setScrollBarColor(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class ListFlingSpeedLimitModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('listFlingSpeedLimit');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().list.resetFlingSpeedLimit(node);
    } else {
      getUINativeModule().list.setFlingSpeedLimit(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class ListLanesModifier extends ModifierWithKey<ArkLanesOpt> {
  constructor(value: ArkLanesOpt) {
    super(value);
  }
  static identity: Symbol = Symbol('listLanes');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().list.resetListLanes(node);
    } else {
      getUINativeModule().list.setListLanes(node, this.value.lanesNum,
        this.value.minLength, this.value.maxLength, this.value.gutter);
    }
  }
  checkObjectDiff(): boolean {
    return true;
  }
}

class ListClipModifier extends ModifierWithKey<boolean | object> {
  constructor(value: boolean | object) {
    super(value);
  }
  static identity: Symbol = Symbol('listClip');
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

class ListFadingEdgeModifier extends ModifierWithKey<ArkFadingEdge> {
  constructor(value: ArkFadingEdge) {
    super(value);
  }
  static identity: Symbol = Symbol('listFadingEdge');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().list.resetFadingEdge(node);
    } else {
      getUINativeModule().list.setFadingEdge(node, this.value.value!, this.value.options?.fadingEdgeLength);
    }
  }
  checkObjectDiff(): boolean {
    return !((this.stageValue.value === this.value.value) &&
      (this.stageValue.options === this.value.options));
  }
}

class ListChildrenMainSizeModifier extends ModifierWithKey<ChildrenMainSize> {
  constructor(value: ChildrenMainSize) {
    super(value);
  }
  static identity: Symbol = Symbol('listChildrenMainSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().list.resetListChildrenMainSize(node);
    } else {
      getUINativeModule().list.setListChildrenMainSize(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return true;
  }
}

class ListSpaceModifier extends ModifierWithKey<number | string> {
  constructor(value: number | string) {
    super(value);
  }
  static identity: Symbol = Symbol('listSpace');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().list.resetSpace(node);
    }
    else {
      getUINativeModule().list.setSpace(node, this.value);
    }
  }
}

class ListInitialIndexModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('listInitialIndex');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().list.resetInitialIndex(node);
    }
    else {
      getUINativeModule().list.setInitialIndex(node, this.value);
    }
  }
}

class ListInitialScrollerModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('listInitialScroller');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().list.resetInitialScroller(node);
    }
    else {
      getUINativeModule().list.setInitialScroller(node, this.value);
    }
  }
}

interface ListParam {
  initialIndex?: number;
  space?: number | string;
  scroller?: Scroller;
}

class ArkListComponent extends ArkComponent implements ListAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  initialize(value: Object[]): this {
    if (value[0] !== undefined) {
      if ((value[0] as ListParam).initialIndex !== undefined) {
        modifierWithKey(this._modifiersWithKeys, ListInitialIndexModifier.identity, ListInitialIndexModifier, (value[0] as ListParam).initialIndex);
      }
      if ((value[0] as ListParam).space !== undefined) {
        modifierWithKey(this._modifiersWithKeys, ListSpaceModifier.identity, ListSpaceModifier, (value[0] as ListParam).space);
      }
      if ((value[0] as ListParam).scroller !== undefined) {
        modifierWithKey(this._modifiersWithKeys, ListInitialScrollerModifier.identity, ListInitialScrollerModifier, (value[0] as ListParam).scroller);
      }
    }
    return this;
  }
  allowChildTypes(): string[] {
    return ["ListItem", "ListItemGroup"];
  }
  lanes(value: number | LengthConstrain, gutter?: any): this {
    let opt: ArkLanesOpt = new ArkLanesOpt();
    opt.gutter = gutter;
    if (isUndefined(value)) {
      opt.lanesNum = undefined;
    } else if (isNumber(value)) {
      opt.lanesNum = value as number;
    } else {
      const lc = value as LengthConstrain;
      opt.minLength = lc.minLength;
      opt.maxLength = lc.maxLength;
    }
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
  scrollBarWidth(value: string | number): this {
    modifierWithKey(this._modifiersWithKeys, ListScrollBarWidthModifier.identity, ListScrollBarWidthModifier, value);
    return this;
  }
  scrollBarColor(value: string | number | Color): this {
    modifierWithKey(this._modifiersWithKeys, ListScrollBarColorModifier.identity, ListScrollBarColorModifier, value);
    return this;
  }
  flingSpeedLimit(value: number): this {
    modifierWithKey(this._modifiersWithKeys, ListFlingSpeedLimitModifier.identity, ListFlingSpeedLimitModifier, value);
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
    modifierWithKey(this._modifiersWithKeys, ContentStartOffsetModifier.identity, ContentStartOffsetModifier, value);
    return this;
  }
  contentEndOffset(value: number): this {
    modifierWithKey(this._modifiersWithKeys, ContentEndOffsetModifier.identity, ContentEndOffsetModifier, value);
    return this;
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
  maintainVisibleContentPosition(value: boolean | undefined): this {
    modifierWithKey(this._modifiersWithKeys, ListMaintainVisibleContentPositionModifier.identity,
      ListMaintainVisibleContentPositionModifier, value);
    return this;
  }
  clip(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): this {
    modifierWithKey(this._modifiersWithKeys, ListClipModifier.identity, ListClipModifier, value);
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
  fadingEdge(value: boolean, options?: FadingEdgeOptions | undefined): this {
    let fadingEdge: ArkFadingEdge = new ArkFadingEdge();
    fadingEdge.value = value;
    fadingEdge.options = options;
    modifierWithKey(this._modifiersWithKeys, ListFadingEdgeModifier.identity, ListFadingEdgeModifier, fadingEdge);
    return this;
  }
  childrenMainSize(value: ChildrenMainSize): this {
    modifierWithKey(this._modifiersWithKeys, ListChildrenMainSizeModifier.identity, ListChildrenMainSizeModifier, value);
    return this;
  }
}

// @ts-ignore
globalThis.List.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkListComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.ListModifier(nativePtr, classType);
  });
};

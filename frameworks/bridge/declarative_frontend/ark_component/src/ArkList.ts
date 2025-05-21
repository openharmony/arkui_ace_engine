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

class ListOnScrollIndexModifier extends ModifierWithKey<(start: number, end: number, center: number) => void> {
  constructor(value: (start: number, end: number, center: number) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('listOnScrollIndex');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().list.resetOnScrollIndex(node);
    } else {
      getUINativeModule().list.setOnScrollIndex(node, this.value);
    }
  }
}

class ListOnScrollVisibleContentChangeModifier extends ModifierWithKey<OnScrollVisibleContentChangeCallback> {
  constructor(value: OnScrollVisibleContentChangeCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('listOnScrollVisibleContentChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().list.resetOnScrollVisibleContentChange(node);
    } else {
      getUINativeModule().list.setOnScrollVisibleContentChange(node, this.value);
    }
  }
}

class ListOnReachStartModifier extends ModifierWithKey<() => void> {
  constructor(value: () => void) {
    super(value);
  }
  static identity: Symbol = Symbol('listOnReachStart');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().list.resetOnReachStart(node);
    } else {
      getUINativeModule().list.setOnReachStart(node, this.value);
    }
  }
}

class ListOnReachEndModifier extends ModifierWithKey<() => void> {
  constructor(value: () => void) {
    super(value);
  }
  static identity: Symbol = Symbol('listOnReachEnd');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().list.resetOnReachEnd(node);
    } else {
      getUINativeModule().list.setOnReachEnd(node, this.value);
    }
  }
}

class ListOnScrollStartModifier extends ModifierWithKey<() => void> {
  constructor(value: () => void) {
    super(value);
  }
  static identity: Symbol = Symbol('listOnScrollStart');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().list.resetOnScrollStart(node);
    } else {
      getUINativeModule().list.setOnScrollStart(node, this.value);
    }
  }
}

class ListOnScrollStopModifier extends ModifierWithKey<() => void> {
  constructor(value: () => void) {
    super(value);
  }
  static identity: Symbol = Symbol('listOnScrollStop');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().list.resetOnScrollStop(node);
    } else {
      getUINativeModule().list.setOnScrollStop(node, this.value);
    }
  }
}

class ListOnItemMoveModifier extends ModifierWithKey<(from: number, to: number) => boolean> {
  constructor(value: (from: number, to: number) => boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('listOnItemMove');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().list.resetOnItemMove(node);
    } else {
      getUINativeModule().list.setOnItemMove(node, this.value);
    }
  }
}

class ListOnItemDragStartModifier extends ModifierWithKey<(event: ItemDragInfo, itemIndex: number) => void | (() => any)> {
  constructor(value: (event: ItemDragInfo, itemIndex: number) => void | (() => any)) {
    super(value);
  }
  static identity: Symbol = Symbol('listOnItemDragStart');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().list.resetOnItemDragStart(node);
    } else {
      getUINativeModule().list.setOnItemDragStart(node, this.value);
    }
  }
}

class ListOnItemDragEnterModifier extends ModifierWithKey<(event: ItemDragInfo) => void> {
  constructor(value: (event: ItemDragInfo) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('listOnItemDragEnter');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().list.resetOnItemDragEnter(node);
    } else {
      getUINativeModule().list.setOnItemDragEnter(node, this.value);
    }
  }
}

class ListOnItemDragMoveModifier extends ModifierWithKey<(event: ItemDragInfo, itemIndex: number, insertIndex: number) => void> {
  constructor(value: (event: ItemDragInfo, itemIndex: number, insertIndex: number) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('listOnItemDragMove');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().list.resetOnItemDragMove(node);
    } else {
      getUINativeModule().list.setOnItemDragMove(node, this.value);
    }
  }
}

class ListOnItemDragLeaveModifier extends ModifierWithKey<(event: ItemDragInfo, itemIndex: number) => void> {
  constructor(value: (event: ItemDragInfo, itemIndex: number) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('listOnItemDragLeave');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().list.resetOnItemDragLeave(node);
    } else {
      getUINativeModule().list.setOnItemDragLeave(node, this.value);
    }
  }
}

class ListOnItemDropModifier extends ModifierWithKey<(event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void> {
  constructor(value: (event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('listOnItemDrop');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().list.resetOnItemDrop(node);
    } else {
      getUINativeModule().list.setOnItemDrop(node, this.value);
    }
  }
}

class ListOnScrollFrameBeginModifier extends ModifierWithKey<(offset: number, state: ScrollState) => { offsetRemain: number }> {
  constructor(value: (offset: number, state: ScrollState) => { offsetRemain: number; }) {
    super(value);
  }
  static identity: Symbol = Symbol('listOnScrollFrameBegin');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().list.resetOnScrollFrameBegin(node);
    } else {
      getUINativeModule().list.setOnScrollFrameBegin(node, this.value);
    }
  }
}

class ListOnWillScrollModifier extends ModifierWithKey<(xOffset: number, yOffset: number,
  scrollState: ScrollState, scrollSource: ScrollSource) => void | OffsetResult> {
  constructor(value: (xOffset: number, yOffset: number,
    scrollState: ScrollState, scrollSource: ScrollSource) => void | OffsetResult) {
    super(value);
  }
  static identity: Symbol = Symbol('listOnWillScroll');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().list.resetOnWillScroll(node);
    } else {
      getUINativeModule().list.setOnWillScroll(node, this.value);
    }
  }
}

class ListOnDidScrollModifier extends ModifierWithKey<(xOffset: number, yOffset: number, scrollState: ScrollState) => void> {
  constructor(value: (xOffset: number, yOffset: number, scrollState: ScrollState) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('listOnDidScroll');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().list.resetOnDidScroll(node);
    } else {
      getUINativeModule().list.setOnDidScroll(node, this.value);
    }
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

class ArkListComponent extends ArkScrollable<ListAttribute> implements ListAttribute {
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
  cachedCount(count: number, show?: boolean): this {
    let opt = new ArkScrollableCacheOptions(count, show ? show : false);
    modifierWithKey(this._modifiersWithKeys, ListCachedCountModifier.identity, ListCachedCountModifier, opt);
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
    modifierWithKey(this._modifiersWithKeys, ListOnScrollIndexModifier.identity, ListOnScrollIndexModifier, event);
    return this;
  }
  onScrollVisibleContentChange(callback: OnScrollVisibleContentChangeCallback): this {
    modifierWithKey(this._modifiersWithKeys, ListOnScrollVisibleContentChangeModifier.identity, ListOnScrollVisibleContentChangeModifier, callback);
    return this;
  }
  onItemDelete(event: (index: number) => boolean): this {
    throw new Error('Method not implemented.');
  }
  onItemMove(callback: (from: number, to: number) => boolean): this {
    modifierWithKey(this._modifiersWithKeys, ListOnItemMoveModifier.identity, ListOnItemMoveModifier, callback);
    return this;
  }
  onItemDragStart(event: (event: ItemDragInfo, itemIndex: number) => void | (() => any)): this {
    modifierWithKey(this._modifiersWithKeys, ListOnItemDragStartModifier.identity, ListOnItemDragStartModifier, event);
    return this;
  }
  onItemDragEnter(event: (event: ItemDragInfo) => void): this {
    modifierWithKey(this._modifiersWithKeys, ListOnItemDragEnterModifier.identity, ListOnItemDragEnterModifier, event);
    return this;
  }
  onItemDragMove(event: (event: ItemDragInfo, itemIndex: number, insertIndex: number) => void): this {
    modifierWithKey(this._modifiersWithKeys, ListOnItemDragMoveModifier.identity, ListOnItemDragMoveModifier, event);
    return this;
  }
  onItemDragLeave(event: (event: ItemDragInfo, itemIndex: number) => void): this {
    modifierWithKey(this._modifiersWithKeys, ListOnItemDragLeaveModifier.identity, ListOnItemDragLeaveModifier, event);
    return this;
  }
  onItemDrop(event: (event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void): this {
    modifierWithKey(this._modifiersWithKeys, ListOnItemDropModifier.identity, ListOnItemDropModifier, event);
    return this;
  }
  onScrollFrameBegin(callback: (offset: number, state: ScrollState) => { offsetRemain: number }): this {
    modifierWithKey(this._modifiersWithKeys, ListOnScrollFrameBeginModifier.identity, ListOnScrollFrameBeginModifier, callback);
    return this;
  }
  onWillScroll(callback: (xOffset: number, yOffset: number,
    scrollState: ScrollState, scrollSource: ScrollSource) => void | OffsetResult): this {
    modifierWithKey(this._modifiersWithKeys, ListOnWillScrollModifier.identity, ListOnWillScrollModifier, callback);
    return this;
  }
  onDidScroll(callback: (xOffset: number, yOffset: number, scrollState: ScrollState) => void): this {
    modifierWithKey(this._modifiersWithKeys, ListOnDidScrollModifier.identity, ListOnDidScrollModifier, callback);
    return this;
  }
  onReachStart(event: () => void): this {
    modifierWithKey(this._modifiersWithKeys, ListOnReachStartModifier.identity, ListOnReachStartModifier, event);
    return this;
  }
  onReachEnd(event: () => void): this {
    modifierWithKey(this._modifiersWithKeys, ListOnReachEndModifier.identity, ListOnReachEndModifier, event);
    return this;
  }
  onScrollStart(event: () => void): this {
    modifierWithKey(this._modifiersWithKeys, ListOnScrollStartModifier.identity, ListOnScrollStartModifier, event);
    return this;
  }
  onScrollStop(event: () => void): this {
    modifierWithKey(this._modifiersWithKeys, ListOnScrollStopModifier.identity, ListOnScrollStopModifier, event);
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

globalThis.List.onReachStart = function (value: () => void): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().list.setOnReachStart(nodePtr, value);
};
globalThis.List.onReachEnd = function (value: () => void): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().list.setOnReachEnd(nodePtr, value);
};
globalThis.List.onScrollStart = function (value: () => void): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().list.setOnScrollStart(nodePtr, value);
};
globalThis.List.onScrollStop = function (value: () => void): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().list.setOnScrollStop(nodePtr, value);
};
globalThis.List.onItemMove = function (value: (from: number, to: number) => boolean): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().list.setOnItemMove(nodePtr, value);
};
globalThis.List.onScrollIndex = function (value: (start: number, end: number, center: number) => void): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().list.setOnScrollIndex(nodePtr, value);
};
globalThis.List.onScrollVisibleContentChange = function (value: OnScrollVisibleContentChangeCallback): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().list.setOnScrollVisibleContentChange(nodePtr, value);
};
globalThis.List.onScrollFrameBegin = function (value: (offset: number, state: ScrollState) => { offsetRemain: number; }): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().list.setOnScrollFrameBegin(nodePtr, value);
};
globalThis.List.onItemDragStart = function (value: (event: ItemDragInfo, itemIndex: number) => void | (() => any)): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().list.setOnItemDragStart(nodePtr, value);
};
globalThis.List.onItemDragEnter = function (value: (event: ItemDragInfo) => void): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().list.setOnItemDragEnter(nodePtr, value);
};
globalThis.List.onItemDragMove = function (value: (event: ItemDragInfo, itemIndex: number, insertIndex: number) => void): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().list.setOnItemDragMove(nodePtr, value);
};
globalThis.List.onItemDragLeave = function (value: (event: ItemDragInfo, itemIndex: number) => void): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().list.setOnItemDragLeave(nodePtr, value);
};
globalThis.List.onItemDrop = function (value: (event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().list.setOnItemDrop(nodePtr, value);
};
globalThis.List.onWillScroll = function (value: (xOffset: number, yOffset: number,
  scrollState: ScrollState, scrollSource: ScrollSource) => void | OffsetResult): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().list.setOnWillScroll(nodePtr, value);
};
globalThis.List.onDidScroll = function (value: (xOffset: number, yOffset: number, scrollState: ScrollState) => void): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().list.setOnDidScroll(nodePtr, value);
};

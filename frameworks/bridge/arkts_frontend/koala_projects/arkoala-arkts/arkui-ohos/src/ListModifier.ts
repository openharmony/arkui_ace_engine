/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { ScrollableCommonMethodModifier } from './ScrollableCommonMethodModifier';
import { AttributeUpdaterFlag } from './CommonMethodModifier';
import {
    ArkListPeer,
    ListItemAlign,
    ListDividerOptions,
    ChainAnimationOptions,
    StickyStyle,
    ScrollSnapAlign,
    OnScrollVisibleContentChangeCallback,
    ListAttribute
} from './component/list';
import { AttributeModifier, ItemDragInfo, OnWillScrollCallback, OnScrollCallback, CustomBuilder, ChildrenMainSize } from './component/common';
import { Axis, ScrollSource } from './component/enums';
import { OnScrollFrameBeginCallback } from './component/scroll';
import { LengthConstrain, Dimension } from './component/units';
export class ListModifier extends ScrollableCommonMethodModifier implements ListAttribute, AttributeModifier<ListAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId;
    }
    isUpdater: () => boolean = () => false;
    applyNormalAttribute(instance: ListAttribute): void {}
    applyPressedAttribute(instance: ListAttribute): void {}
    applyFocusedAttribute(instance: ListAttribute): void {}
    applyDisabledAttribute(instance: ListAttribute): void {}
    applySelectedAttribute(instance: ListAttribute): void {}
    _alignListItem_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _alignListItem_0_0value?: ListItemAlign | undefined;
    _listDirection_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _listDirection_0_0value?: Axis | undefined;
    _contentStartOffset_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _contentStartOffset_0_0value?: number | undefined;
    _contentEndOffset_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _contentEndOffset_0_0value?: number | undefined;
    _divider_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _divider_0_0value?: ListDividerOptions | undefined;
    _multiSelectable_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _multiSelectable_0_0value?: boolean | undefined;
    _cachedCount_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _cachedCount_0_0value?: number | undefined;
    _chainAnimation_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _chainAnimation_0_0value?: boolean | undefined;
    _chainAnimationOptions_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _chainAnimationOptions_0_0value?: ChainAnimationOptions | undefined;
    _sticky_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _sticky_0_0value?: StickyStyle | undefined;
    _scrollSnapAlign_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _scrollSnapAlign_0_0value?: ScrollSnapAlign | undefined;
    _childrenMainSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _childrenMainSize_0_0value?: ChildrenMainSize | undefined;
    _maintainVisibleContentPosition_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _maintainVisibleContentPosition_0_0value?: boolean | undefined;
    _stackFromEnd_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _stackFromEnd_0_0value?: boolean | undefined;
    _onScrollIndex_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _onScrollIndex_0_0value?: ((start: number, end: number, center: number) => void) | undefined;
    _onScrollVisibleContentChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _onScrollVisibleContentChange_0_0value?: OnScrollVisibleContentChangeCallback | undefined;
    _onItemMove_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _onItemMove_0_0value?: ((from: number, to: number) => boolean) | undefined;
    _onItemDragStart_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _onItemDragStart_0_0value?: ((event: ItemDragInfo, itemIndex: number) => CustomBuilder) | undefined;
    _onItemDragEnter_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _onItemDragEnter_0_0value?: ((event: ItemDragInfo) => void) | undefined;
    _onItemDragMove_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _onItemDragMove_0_0value?: ((event: ItemDragInfo, itemIndex: number, insertIndex: number) => void) | undefined;
    _onItemDragLeave_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _onItemDragLeave_0_0value?: ((event: ItemDragInfo, itemIndex: number) => void) | undefined;
    _onItemDrop_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _onItemDrop_0_0value?: ((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void) | undefined;
    _onScrollFrameBegin_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _onScrollFrameBegin_0_0value?: OnScrollFrameBeginCallback | undefined;
    _onWillScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _onWillScroll_0_0value?: OnWillScrollCallback | undefined;
    _onDidScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _onDidScroll_0_0value?: OnScrollCallback | undefined;
    _lanes_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _lanes_0_0value?: number | LengthConstrain | undefined;
    _lanes_0_1value?: Dimension | undefined;
    _cachedCount_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _cachedCount_1_0value?: number | undefined;
    _cachedCount_1_1value?: boolean | undefined;
    applyModifierPatch(peer: ArkListPeer): void {
        super.applyModifierPatch(peer);
        if (this._alignListItem_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._alignListItem_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.alignListItemAttribute(this._alignListItem_0_0value as ListItemAlign | undefined);
                    this._alignListItem_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._alignListItem_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._alignListItem_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.alignListItemAttribute(undefined as ListItemAlign | undefined);
                }
            }
        }
        if (this._listDirection_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._listDirection_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.listDirectionAttribute(this._listDirection_0_0value as Axis | undefined);
                    this._listDirection_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._listDirection_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._listDirection_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.listDirectionAttribute(undefined as Axis | undefined);
                }
            }
        }
        if (this._contentStartOffset_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._contentStartOffset_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.contentStartOffsetAttribute(this._contentStartOffset_0_0value as number | undefined);
                    this._contentStartOffset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._contentStartOffset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._contentStartOffset_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.contentStartOffsetAttribute(undefined as number | undefined);
                }
            }
        }
        if (this._contentEndOffset_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._contentEndOffset_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.contentEndOffsetAttribute(this._contentEndOffset_0_0value as number | undefined);
                    this._contentEndOffset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._contentEndOffset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._contentEndOffset_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.contentEndOffsetAttribute(undefined as number | undefined);
                }
            }
        }
        if (this._divider_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._divider_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.dividerAttribute(this._divider_0_0value as ListDividerOptions | undefined);
                    this._divider_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._divider_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._divider_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.dividerAttribute(undefined as ListDividerOptions | undefined);
                }
            }
        }
        if (this._multiSelectable_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._multiSelectable_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.multiSelectableAttribute(this._multiSelectable_0_0value as boolean | undefined);
                    this._multiSelectable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._multiSelectable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._multiSelectable_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.multiSelectableAttribute(undefined as boolean | undefined);
                }
            }
        }
        if (this._cachedCount_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._cachedCount_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.cachedCount0Attribute(this._cachedCount_0_0value as number | undefined);
                    this._cachedCount_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._cachedCount_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._cachedCount_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.cachedCount0Attribute(undefined as number | undefined);
                }
            }
        }

        if (this._chainAnimation_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._chainAnimation_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.chainAnimationAttribute(this._chainAnimation_0_0value as boolean | undefined);
                    this._chainAnimation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._chainAnimation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._chainAnimation_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.chainAnimationAttribute(undefined as boolean | undefined);
                }
            }
        }
        if (this._chainAnimationOptions_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._chainAnimationOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.chainAnimationOptionsAttribute(this._chainAnimationOptions_0_0value as ChainAnimationOptions | undefined);
                    this._chainAnimationOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._chainAnimationOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._chainAnimationOptions_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.chainAnimationOptionsAttribute(undefined as ChainAnimationOptions | undefined);
                }
            }
        }
        if (this._sticky_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._sticky_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.stickyAttribute(this._sticky_0_0value as StickyStyle | undefined);
                    this._sticky_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._sticky_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._sticky_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.stickyAttribute(undefined as StickyStyle | undefined);
                }
            }
        }
        if (this._scrollSnapAlign_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._scrollSnapAlign_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.scrollSnapAlignAttribute(this._scrollSnapAlign_0_0value as ScrollSnapAlign | undefined);
                    this._scrollSnapAlign_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._scrollSnapAlign_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._scrollSnapAlign_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.scrollSnapAlignAttribute(undefined as ScrollSnapAlign | undefined);
                }
            }
        }
        if (this._childrenMainSize_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._childrenMainSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.childrenMainSizeAttribute(this._childrenMainSize_0_0value as ChildrenMainSize | undefined);
                    this._childrenMainSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._childrenMainSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._childrenMainSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.childrenMainSizeAttribute(undefined as ChildrenMainSize | undefined);
                }
            }
        }
        if (this._maintainVisibleContentPosition_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._maintainVisibleContentPosition_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.maintainVisibleContentPositionAttribute(this._maintainVisibleContentPosition_0_0value as boolean | undefined);
                    this._maintainVisibleContentPosition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maintainVisibleContentPosition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._maintainVisibleContentPosition_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.maintainVisibleContentPositionAttribute(undefined as boolean | undefined);
                }
            }
        }
        if (this._stackFromEnd_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._stackFromEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.stackFromEndAttribute(this._stackFromEnd_0_0value as boolean | undefined);
                    this._stackFromEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._stackFromEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._stackFromEnd_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.stackFromEndAttribute(undefined as boolean | undefined);
                }
            }
        }
        if (this._onScrollIndex_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onScrollIndex_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onScrollIndexAttribute(this._onScrollIndex_0_0value as ((start: number, end: number, center: number) => void) | undefined);
                    this._onScrollIndex_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScrollIndex_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScrollIndex_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onScrollIndexAttribute(undefined as ((start: number, end: number, center: number) => void) | undefined);
                }
            }
        }
        if (this._onScrollVisibleContentChange_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onScrollVisibleContentChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onScrollVisibleContentChangeAttribute(
                        this._onScrollVisibleContentChange_0_0value as OnScrollVisibleContentChangeCallback | undefined
                    );
                    this._onScrollVisibleContentChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScrollVisibleContentChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScrollVisibleContentChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onScrollVisibleContentChangeAttribute(undefined as OnScrollVisibleContentChangeCallback | undefined);
                }
            }
        }
        if (this._onItemMove_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onItemMove_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onItemMoveAttribute(this._onItemMove_0_0value as ((from: number, to: number) => boolean) | undefined);
                    this._onItemMove_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onItemMove_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onItemMove_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onItemMoveAttribute(undefined as ((from: number, to: number) => boolean) | undefined);
                }
            }
        }
        if (this._onItemDragStart_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onItemDragStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onItemDragStartAttribute(
                        this._onItemDragStart_0_0value as ((event: ItemDragInfo, itemIndex: number) => CustomBuilder) | undefined
                    );
                    this._onItemDragStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onItemDragStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onItemDragStart_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onItemDragStartAttribute(undefined as ((event: ItemDragInfo, itemIndex: number) => CustomBuilder) | undefined);
                }
            }
        }
        if (this._onItemDragEnter_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onItemDragEnter_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onItemDragEnterAttribute(this._onItemDragEnter_0_0value as ((event: ItemDragInfo) => void) | undefined);
                    this._onItemDragEnter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onItemDragEnter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onItemDragEnter_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onItemDragEnterAttribute(undefined as ((event: ItemDragInfo) => void) | undefined);
                }
            }
        }
        if (this._onItemDragMove_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onItemDragMove_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onItemDragMoveAttribute(
                        this._onItemDragMove_0_0value as ((event: ItemDragInfo, itemIndex: number, insertIndex: number) => void) | undefined
                    );
                    this._onItemDragMove_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onItemDragMove_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onItemDragMove_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onItemDragMoveAttribute(undefined as ((event: ItemDragInfo, itemIndex: number, insertIndex: number) => void) | undefined);
                }
            }
        }
        if (this._onItemDragLeave_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onItemDragLeave_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onItemDragLeaveAttribute(this._onItemDragLeave_0_0value as ((event: ItemDragInfo, itemIndex: number) => void) | undefined);
                    this._onItemDragLeave_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onItemDragLeave_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onItemDragLeave_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onItemDragLeaveAttribute(undefined as ((event: ItemDragInfo, itemIndex: number) => void) | undefined);
                }
            }
        }
        if (this._onItemDrop_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onItemDrop_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onItemDropAttribute(this._onItemDrop_0_0value as ((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void) | undefined);
                    this._onItemDrop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onItemDrop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onItemDrop_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onItemDropAttribute(
                        undefined as ((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void) | undefined
                    );
                }
            }
        }
        if (this._onScrollFrameBegin_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onScrollFrameBegin_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onScrollFrameBeginAttribute(this._onScrollFrameBegin_0_0value as OnScrollFrameBeginCallback | undefined);
                    this._onScrollFrameBegin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScrollFrameBegin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScrollFrameBegin_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onScrollFrameBeginAttribute(undefined as OnScrollFrameBeginCallback | undefined);
                }
            }
        }
        if (this._onWillScroll_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onWillScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onWillScrollAttribute(this._onWillScroll_0_0value as OnWillScrollCallback | undefined);
                    this._onWillScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWillScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWillScroll_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onWillScrollAttribute(undefined as OnWillScrollCallback | undefined);
                }
            }
        }
        if (this._onDidScroll_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onDidScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onDidScrollAttribute(this._onDidScroll_0_0value as OnScrollCallback | undefined);
                    this._onDidScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDidScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDidScroll_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onDidScrollAttribute(undefined as OnScrollCallback | undefined);
                }
            }
        }
        if (this._lanes_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._lanes_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.lanesAttribute(this._lanes_0_0value as number | LengthConstrain | undefined, this._lanes_0_1value as Dimension | undefined);
                    this._lanes_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._lanes_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._lanes_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.lanesAttribute(undefined as number | LengthConstrain | undefined, undefined as Dimension | undefined | undefined);
                }
            }
        }
        if (this._cachedCount_1_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._cachedCount_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.cachedCount1Attribute(this._cachedCount_1_0value as number | undefined, this._cachedCount_1_1value as boolean | undefined);
                    this._cachedCount_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._cachedCount_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._cachedCount_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.cachedCount1Attribute(undefined as number | undefined, undefined as boolean | undefined);
                }
            }
        }
    }
    mergeModifier(modifier: ListModifier): void {
        super.mergeModifier(modifier);
        if (modifier._alignListItem_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._alignListItem_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.alignListItem(modifier._alignListItem_0_0value);
                    break;
                }
                default: {
                    this.alignListItem(undefined as ListItemAlign | undefined);
                }
            }
        }
        if (modifier._listDirection_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._listDirection_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.listDirection(modifier._listDirection_0_0value);
                    break;
                }
                default: {
                    this.listDirection(undefined as Axis | undefined);
                }
            }
        }
        if (modifier._contentStartOffset_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._contentStartOffset_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.contentStartOffset(modifier._contentStartOffset_0_0value);
                    break;
                }
                default: {
                    this.contentStartOffset(undefined as number | undefined);
                }
            }
        }
        if (modifier._contentEndOffset_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._contentEndOffset_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.contentEndOffset(modifier._contentEndOffset_0_0value);
                    break;
                }
                default: {
                    this.contentEndOffset(undefined as number | undefined);
                }
            }
        }
        if (modifier._divider_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._divider_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.divider(modifier._divider_0_0value);
                    break;
                }
                default: {
                    this.divider(undefined as ListDividerOptions | undefined);
                }
            }
        }
        if (modifier._multiSelectable_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._multiSelectable_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.multiSelectable(modifier._multiSelectable_0_0value);
                    break;
                }
                default: {
                    this.multiSelectable(undefined as boolean | undefined);
                }
            }
        }
        if (modifier._cachedCount_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._cachedCount_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.cachedCount(modifier._cachedCount_0_0value);
                    break;
                }
                default: {
                    this.cachedCount(undefined as number | undefined);
                }
            }
        }
        if (modifier._chainAnimation_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._chainAnimation_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.chainAnimation(modifier._chainAnimation_0_0value);
                    break;
                }
                default: {
                    this.chainAnimation(undefined as boolean | undefined);
                }
            }
        }
        if (modifier._chainAnimationOptions_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._chainAnimationOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.chainAnimationOptions(modifier._chainAnimationOptions_0_0value);
                    break;
                }
                default: {
                    this.chainAnimationOptions(undefined as ChainAnimationOptions | undefined);
                }
            }
        }
        if (modifier._sticky_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._sticky_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.sticky(modifier._sticky_0_0value);
                    break;
                }
                default: {
                    this.sticky(undefined as StickyStyle | undefined);
                }
            }
        }
        if (modifier._scrollSnapAlign_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._scrollSnapAlign_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.scrollSnapAlign(modifier._scrollSnapAlign_0_0value);
                    break;
                }
                default: {
                    this.scrollSnapAlign(undefined as ScrollSnapAlign | undefined);
                }
            }
        }
        if (modifier._childrenMainSize_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._childrenMainSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.childrenMainSize(modifier._childrenMainSize_0_0value);
                    break;
                }
                default: {
                    this.childrenMainSize(undefined as ChildrenMainSize | undefined);
                }
            }
        }
        if (modifier._maintainVisibleContentPosition_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._maintainVisibleContentPosition_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.maintainVisibleContentPosition(modifier._maintainVisibleContentPosition_0_0value);
                    break;
                }
                default: {
                    this.maintainVisibleContentPosition(undefined as boolean | undefined);
                }
            }
        }
        if (modifier._stackFromEnd_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._stackFromEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.stackFromEnd(modifier._stackFromEnd_0_0value);
                    break;
                }
                default: {
                    this.stackFromEnd(undefined as boolean | undefined);
                }
            }
        }
        if (modifier._onScrollIndex_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onScrollIndex_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onScrollIndex(modifier._onScrollIndex_0_0value);
                    break;
                }
                default: {
                    this.onScrollIndex(undefined as ((start: number, end: number, center: number) => void) | undefined);
                }
            }
        }
        if (modifier._onScrollVisibleContentChange_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onScrollVisibleContentChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onScrollVisibleContentChange(modifier._onScrollVisibleContentChange_0_0value);
                    break;
                }
                default: {
                    this.onScrollVisibleContentChange(undefined as OnScrollVisibleContentChangeCallback | undefined);
                }
            }
        }
        if (modifier._onItemMove_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onItemMove_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onItemMove(modifier._onItemMove_0_0value);
                    break;
                }
                default: {
                    this.onItemMove(undefined as ((from: number, to: number) => boolean) | undefined);
                }
            }
        }
        if (modifier._onItemDragStart_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onItemDragStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onItemDragStart(modifier._onItemDragStart_0_0value);
                    break;
                }
                default: {
                    this.onItemDragStart(undefined as ((event: ItemDragInfo, itemIndex: number) => CustomBuilder) | undefined);
                }
            }
        }
        if (modifier._onItemDragEnter_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onItemDragEnter_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onItemDragEnter(modifier._onItemDragEnter_0_0value);
                    break;
                }
                default: {
                    this.onItemDragEnter(undefined as ((event: ItemDragInfo) => void) | undefined);
                }
            }
        }
        if (modifier._onItemDragMove_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onItemDragMove_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onItemDragMove(modifier._onItemDragMove_0_0value);
                    break;
                }
                default: {
                    this.onItemDragMove(undefined as ((event: ItemDragInfo, itemIndex: number, insertIndex: number) => void) | undefined);
                }
            }
        }
        if (modifier._onItemDragLeave_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onItemDragLeave_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onItemDragLeave(modifier._onItemDragLeave_0_0value);
                    break;
                }
                default: {
                    this.onItemDragLeave(undefined as ((event: ItemDragInfo, itemIndex: number) => void) | undefined);
                }
            }
        }
        if (modifier._onItemDrop_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onItemDrop_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onItemDrop(modifier._onItemDrop_0_0value);
                    break;
                }
                default: {
                    this.onItemDrop(
                        undefined as ((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void) | undefined
                    );
                }
            }
        }
        if (modifier._onScrollFrameBegin_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onScrollFrameBegin_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onScrollFrameBegin(modifier._onScrollFrameBegin_0_0value);
                    break;
                }
                default: {
                    this.onScrollFrameBegin(undefined as OnScrollFrameBeginCallback | undefined);
                }
            }
        }
        if (modifier._onWillScroll_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onWillScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onWillScroll(modifier._onWillScroll_0_0value);
                    break;
                }
                default: {
                    this.onWillScroll(undefined as OnWillScrollCallback | undefined);
                }
            }
        }
        if (modifier._onDidScroll_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onDidScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDidScroll(modifier._onDidScroll_0_0value);
                    break;
                }
                default: {
                    this.onDidScroll(undefined as OnScrollCallback | undefined);
                }
            }
        }
        if (modifier._lanes_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._lanes_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.lanes(modifier._lanes_0_0value, modifier._lanes_0_1value);
                    break;
                }
                default: {
                    this.lanes(undefined as number | LengthConstrain | undefined, undefined as Dimension | undefined | undefined);
                }
            }
        }
        if (modifier._cachedCount_1_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._cachedCount_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.cachedCount(modifier._cachedCount_1_0value, modifier._cachedCount_1_1value);
                    break;
                }
                default: {
                    this.cachedCount(undefined as number | undefined, undefined as boolean | undefined);
                }
            }
        }
    }
    alignListItem(value: ListItemAlign | undefined): this {
        if (this._alignListItem_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._alignListItem_0_flag = AttributeUpdaterFlag.UPDATE;
            this._alignListItem_0_0value = value;
        } else {
            this._alignListItem_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    listDirection(value: Axis | undefined): this {
        if (this._listDirection_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._listDirection_0_flag = AttributeUpdaterFlag.UPDATE;
            this._listDirection_0_0value = value;
        } else {
            this._listDirection_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    contentStartOffset(value: number | undefined): this {
        if (this._contentStartOffset_0_flag == AttributeUpdaterFlag.INITIAL || this._contentStartOffset_0_0value !== value) {
            this._contentStartOffset_0_flag = AttributeUpdaterFlag.UPDATE;
            this._contentStartOffset_0_0value = value;
        } else {
            this._contentStartOffset_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    contentEndOffset(value: number | undefined): this {
        if (this._contentEndOffset_0_flag == AttributeUpdaterFlag.INITIAL || this._contentEndOffset_0_0value !== value) {
            this._contentEndOffset_0_flag = AttributeUpdaterFlag.UPDATE;
            this._contentEndOffset_0_0value = value;
        } else {
            this._contentEndOffset_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    divider(value: ListDividerOptions | undefined): this {
        if (this._divider_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._divider_0_flag = AttributeUpdaterFlag.UPDATE;
            this._divider_0_0value = value;
        } else {
            this._divider_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    multiSelectable(value: boolean | undefined): this {
        if (this._multiSelectable_0_flag == AttributeUpdaterFlag.INITIAL || this._multiSelectable_0_0value !== value) {
            this._multiSelectable_0_flag = AttributeUpdaterFlag.UPDATE;
            this._multiSelectable_0_0value = value;
        } else {
            this._multiSelectable_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    cachedCount(value: number | undefined): this {
        if (this._cachedCount_0_flag == AttributeUpdaterFlag.INITIAL || this._cachedCount_0_0value !== value) {
            this._cachedCount_0_flag = AttributeUpdaterFlag.UPDATE;
            this._cachedCount_0_0value = value;
        } else {
            this._cachedCount_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    chainAnimation(value: boolean | undefined): this {
        if (this._chainAnimation_0_flag == AttributeUpdaterFlag.INITIAL || this._chainAnimation_0_0value !== value) {
            this._chainAnimation_0_flag = AttributeUpdaterFlag.UPDATE;
            this._chainAnimation_0_0value = value;
        } else {
            this._chainAnimation_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    chainAnimationOptions(value: ChainAnimationOptions | undefined): this {
        if (this._chainAnimationOptions_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._chainAnimationOptions_0_flag = AttributeUpdaterFlag.UPDATE;
            this._chainAnimationOptions_0_0value = value;
        } else {
            this._chainAnimationOptions_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    sticky(value: StickyStyle | undefined): this {
        if (this._sticky_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._sticky_0_flag = AttributeUpdaterFlag.UPDATE;
            this._sticky_0_0value = value;
        } else {
            this._sticky_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    scrollSnapAlign(value: ScrollSnapAlign | undefined): this {
        if (this._scrollSnapAlign_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._scrollSnapAlign_0_flag = AttributeUpdaterFlag.UPDATE;
            this._scrollSnapAlign_0_0value = value;
        } else {
            this._scrollSnapAlign_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    childrenMainSize(value: ChildrenMainSize | undefined): this {
        if (this._childrenMainSize_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._childrenMainSize_0_flag = AttributeUpdaterFlag.UPDATE;
            this._childrenMainSize_0_0value = value;
        } else {
            this._childrenMainSize_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    maintainVisibleContentPosition(value: boolean | undefined): this {
        if (this._maintainVisibleContentPosition_0_flag == AttributeUpdaterFlag.INITIAL || this._maintainVisibleContentPosition_0_0value !== value) {
            this._maintainVisibleContentPosition_0_flag = AttributeUpdaterFlag.UPDATE;
            this._maintainVisibleContentPosition_0_0value = value;
        } else {
            this._maintainVisibleContentPosition_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    stackFromEnd(value: boolean | undefined): this {
        if (this._stackFromEnd_0_flag == AttributeUpdaterFlag.INITIAL || this._stackFromEnd_0_0value !== value) {
            this._stackFromEnd_0_flag = AttributeUpdaterFlag.UPDATE;
            this._stackFromEnd_0_0value = value;
        } else {
            this._stackFromEnd_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    onScrollIndex(value: ((start: number, end: number, center: number) => void) | undefined): this {
        if (this._onScrollIndex_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._onScrollIndex_0_flag = AttributeUpdaterFlag.UPDATE;
            this._onScrollIndex_0_0value = value;
        } else {
            this._onScrollIndex_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    onScrollVisibleContentChange(value: OnScrollVisibleContentChangeCallback | undefined): this {
        if (this._onScrollVisibleContentChange_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._onScrollVisibleContentChange_0_flag = AttributeUpdaterFlag.UPDATE;
            this._onScrollVisibleContentChange_0_0value = value;
        } else {
            this._onScrollVisibleContentChange_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    onItemMove(value: ((from: number, to: number) => boolean) | undefined): this {
        if (this._onItemMove_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._onItemMove_0_flag = AttributeUpdaterFlag.UPDATE;
            this._onItemMove_0_0value = value;
        } else {
            this._onItemMove_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    onItemDragStart(value: ((event: ItemDragInfo, itemIndex: number) => CustomBuilder) | undefined): this {
        if (this._onItemDragStart_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._onItemDragStart_0_flag = AttributeUpdaterFlag.UPDATE;
            this._onItemDragStart_0_0value = value;
        } else {
            this._onItemDragStart_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    onItemDragEnter(value: ((event: ItemDragInfo) => void) | undefined): this {
        if (this._onItemDragEnter_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._onItemDragEnter_0_flag = AttributeUpdaterFlag.UPDATE;
            this._onItemDragEnter_0_0value = value;
        } else {
            this._onItemDragEnter_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    onItemDragMove(value: ((event: ItemDragInfo, itemIndex: number, insertIndex: number) => void) | undefined): this {
        if (this._onItemDragMove_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._onItemDragMove_0_flag = AttributeUpdaterFlag.UPDATE;
            this._onItemDragMove_0_0value = value;
        } else {
            this._onItemDragMove_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    onItemDragLeave(value: ((event: ItemDragInfo, itemIndex: number) => void) | undefined): this {
        if (this._onItemDragLeave_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._onItemDragLeave_0_flag = AttributeUpdaterFlag.UPDATE;
            this._onItemDragLeave_0_0value = value;
        } else {
            this._onItemDragLeave_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    onItemDrop(value: ((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void) | undefined): this {
        if (this._onItemDrop_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._onItemDrop_0_flag = AttributeUpdaterFlag.UPDATE;
            this._onItemDrop_0_0value = value;
        } else {
            this._onItemDrop_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        if (this._onScrollFrameBegin_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._onScrollFrameBegin_0_flag = AttributeUpdaterFlag.UPDATE;
            this._onScrollFrameBegin_0_0value = value;
        } else {
            this._onScrollFrameBegin_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    onWillScroll(value: OnWillScrollCallback | undefined): this {
        if (this._onWillScroll_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._onWillScroll_0_flag = AttributeUpdaterFlag.UPDATE;
            this._onWillScroll_0_0value = value;
        } else {
            this._onWillScroll_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    onDidScroll(value: OnScrollCallback | undefined): this {
        if (this._onDidScroll_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._onDidScroll_0_flag = AttributeUpdaterFlag.UPDATE;
            this._onDidScroll_0_0value = value;
        } else {
            this._onDidScroll_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    lanes(value: number | LengthConstrain | undefined, gutter?: Dimension): this {
        if (this._lanes_0_flag == AttributeUpdaterFlag.INITIAL || true || true) {
            this._lanes_0_flag = AttributeUpdaterFlag.UPDATE;
            this._lanes_0_0value = value;
            this._lanes_0_1value = gutter;
        } else {
            this._lanes_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    cachedCount(count: number | undefined, show: boolean | undefined): this {
        if (this._cachedCount_1_flag == AttributeUpdaterFlag.INITIAL || this._cachedCount_1_0value !== count || this._cachedCount_1_1value !== show) {
            this._cachedCount_1_flag = AttributeUpdaterFlag.UPDATE;
            this._cachedCount_1_0value = count;
            this._cachedCount_1_1value = show;
        } else {
            this._cachedCount_1_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
}

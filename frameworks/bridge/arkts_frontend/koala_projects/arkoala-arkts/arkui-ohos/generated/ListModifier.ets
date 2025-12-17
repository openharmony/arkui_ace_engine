/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { CommonMethod, NestedScrollOptions, ContentClipMode, EdgeEffectOptions, FadingEdgeOptions, ScrollableCommonMethod, ChildrenMainSize, OnItemDragStartCallback, ItemDragInfo, OnWillScrollCallback, OnScrollCallback } from "./component/common"
import { BarState, Color, CrownSensitivity, EdgeEffect, Axis, ScrollSource } from "./component/enums"
import { Resource } from "global.resource"
import { extractors, AttributeModifier } from "#handwritten"
import { RectShape } from "@ohos.arkui.shape"
import { ScrollableCommonMethodModifier } from "./ScrollableCommonMethodModifier"
import { CommonMethodModifier } from "./CommonMethodModifier"
import { ModifierState } from './CommonModifier'
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkListPeer, ListItemAlign, ListDividerOptions, ChainAnimationOptions, StickyStyle, ScrollSnapAlign, OnScrollVisibleContentChangeCallback, VisibleListContentInfo, ScrollState, ListAttribute } from "./component/list"
import { int32 } from "@koalaui/common"
import { OnScrollFrameBeginCallback } from "./component/scroll"
import { LengthConstrain, Dimension } from "./component/units"
export class ListModifier extends CommonMethodModifier implements ListAttribute,AttributeModifier<ListAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: ListAttribute): void { }
    applyPressedAttribute(instance: ListAttribute): void { }
    applyFocusedAttribute(instance: ListAttribute): void { }
    applyDisabledAttribute(instance: ListAttribute): void { }
    applySelectedAttribute(instance: ListAttribute): void { }
    _alignListItem_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _alignListItem_0_0value?: ListItemAlign | undefined
    _listDirection_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _listDirection_0_0value?: Axis | undefined
    _contentStartOffset_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _contentStartOffset_0_0value?: double | undefined
    _contentEndOffset_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _contentEndOffset_0_0value?: double | undefined
    _divider_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _divider_0_0value?: ListDividerOptions | null | undefined
    _multiSelectable_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _multiSelectable_0_0value?: boolean | undefined
    _cachedCount_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _cachedCount_0_0value?: int32 | undefined
    _chainAnimation_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _chainAnimation_0_0value?: boolean | undefined
    _chainAnimationOptions_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _chainAnimationOptions_0_0value?: ChainAnimationOptions | undefined
    _sticky_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _sticky_0_0value?: StickyStyle | undefined
    _scrollSnapAlign_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _scrollSnapAlign_0_0value?: ScrollSnapAlign | undefined
    _childrenMainSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _childrenMainSize_0_0value?: ChildrenMainSize | undefined
    _maintainVisibleContentPosition_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maintainVisibleContentPosition_0_0value?: boolean | undefined
    _supportEmptyBranchInLazyLoading_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _supportEmptyBranchInLazyLoading_0_0value?: boolean | undefined
    _stackFromEnd_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _stackFromEnd_0_0value?: boolean | undefined
    _onScrollIndex_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onScrollIndex_0_0value?: ((start: int32,end: int32,center: int32) => void) | undefined
    _onScrollVisibleContentChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onScrollVisibleContentChange_0_0value?: OnScrollVisibleContentChangeCallback | undefined
    _onItemMove_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onItemMove_0_0value?: ((from: int32,to: int32) => boolean) | undefined
    _onItemDragStart_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onItemDragStart_0_0value?: OnItemDragStartCallback | undefined
    _onItemDragEnter_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onItemDragEnter_0_0value?: ((event: ItemDragInfo) => void) | undefined
    _onItemDragMove_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onItemDragMove_0_0value?: ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32) => void) | undefined
    _onItemDragLeave_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onItemDragLeave_0_0value?: ((event: ItemDragInfo,itemIndex: int32) => void) | undefined
    _onItemDrop_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onItemDrop_0_0value?: ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32,isSuccess: boolean) => void) | undefined
    _onScrollFrameBegin_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onScrollFrameBegin_0_0value?: OnScrollFrameBeginCallback | undefined
    _onWillScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWillScroll_0_0value?: OnWillScrollCallback | undefined
    _onDidScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDidScroll_0_0value?: OnScrollCallback | undefined
    _lanes_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _lanes_0_0value?: int32 | LengthConstrain | undefined
    _lanes_0_1value?: Dimension | undefined
    _cachedCount_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _cachedCount_1_0value?: int32 | undefined
    _cachedCount_1_1value?: boolean | undefined
    _scrollBar_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _scrollBar_0_0value?: BarState | undefined
    _scrollBarColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _scrollBarColor_0_0value?: Color | int32 | string | undefined
    _scrollBarWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _scrollBarWidth_0_0value?: double | string | undefined
    _nestedScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _nestedScroll_0_0value?: NestedScrollOptions | undefined
    _enableScrollInteraction_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableScrollInteraction_0_0value?: boolean | undefined
    _friction_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _friction_0_0value?: double | Resource | undefined
    _onReachStart_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onReachStart_0_0value?: (() => void) | undefined
    _onReachEnd_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onReachEnd_0_0value?: (() => void) | undefined
    _onScrollStart_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onScrollStart_0_0value?: (() => void) | undefined
    _onScrollStop_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onScrollStop_0_0value?: (() => void) | undefined
    _flingSpeedLimit_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _flingSpeedLimit_0_0value?: double | undefined
    _clipContent_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _clipContent_0_0value?: ContentClipMode | RectShape | undefined
    _digitalCrownSensitivity_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _digitalCrownSensitivity_0_0value?: CrownSensitivity | undefined
    _backToTop_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _backToTop_0_0value?: boolean | undefined
    _edgeEffect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _edgeEffect_0_0value?: EdgeEffect | undefined
    _edgeEffect_0_1value?: EdgeEffectOptions | undefined
    _fadingEdge_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fadingEdge_0_0value?: boolean | undefined
    _fadingEdge_0_1value?: FadingEdgeOptions | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkListPeer;
        if (this._alignListItem_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._alignListItem_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAlignListItemAttribute((this._alignListItem_0_0value as ListItemAlign | undefined));
                    this._alignListItem_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._alignListItem_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._alignListItem_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAlignListItemAttribute((undefined as ListItemAlign | undefined));
                }
            }
        }
        if (this._listDirection_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._listDirection_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setListDirectionAttribute((this._listDirection_0_0value as Axis | undefined));
                    this._listDirection_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._listDirection_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._listDirection_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setListDirectionAttribute((undefined as Axis | undefined));
                }
            }
        }
        if (this._contentStartOffset_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._contentStartOffset_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setContentStartOffsetAttribute((this._contentStartOffset_0_0value as double | undefined));
                    this._contentStartOffset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._contentStartOffset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._contentStartOffset_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setContentStartOffsetAttribute((undefined as double | undefined));
                }
            }
        }
        if (this._contentEndOffset_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._contentEndOffset_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setContentEndOffsetAttribute((this._contentEndOffset_0_0value as double | undefined));
                    this._contentEndOffset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._contentEndOffset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._contentEndOffset_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setContentEndOffsetAttribute((undefined as double | undefined));
                }
            }
        }
        if (this._divider_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._divider_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDividerAttribute((this._divider_0_0value as ListDividerOptions | null | undefined));
                    this._divider_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._divider_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._divider_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDividerAttribute((undefined as ListDividerOptions | null | undefined));
                }
            }
        }
        if (this._multiSelectable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._multiSelectable_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMultiSelectableAttribute((this._multiSelectable_0_0value as boolean | undefined));
                    this._multiSelectable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._multiSelectable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._multiSelectable_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMultiSelectableAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._cachedCount_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._cachedCount_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCachedCount0Attribute((this._cachedCount_0_0value as int32 | undefined));
                    this._cachedCount_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._cachedCount_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._cachedCount_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCachedCount0Attribute((undefined as int32 | undefined));
                }
            }
        }
        if (this._chainAnimation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._chainAnimation_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setChainAnimationAttribute((this._chainAnimation_0_0value as boolean | undefined));
                    this._chainAnimation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._chainAnimation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._chainAnimation_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setChainAnimationAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._chainAnimationOptions_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._chainAnimationOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setChainAnimationOptionsAttribute((this._chainAnimationOptions_0_0value as ChainAnimationOptions | undefined));
                    this._chainAnimationOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._chainAnimationOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._chainAnimationOptions_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setChainAnimationOptionsAttribute((undefined as ChainAnimationOptions | undefined));
                }
            }
        }
        if (this._sticky_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._sticky_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStickyAttribute((this._sticky_0_0value as StickyStyle | undefined));
                    this._sticky_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._sticky_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._sticky_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStickyAttribute((undefined as StickyStyle | undefined));
                }
            }
        }
        if (this._scrollSnapAlign_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._scrollSnapAlign_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setScrollSnapAlignAttribute((this._scrollSnapAlign_0_0value as ScrollSnapAlign | undefined));
                    this._scrollSnapAlign_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._scrollSnapAlign_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._scrollSnapAlign_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setScrollSnapAlignAttribute((undefined as ScrollSnapAlign | undefined));
                }
            }
        }
        if (this._childrenMainSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._childrenMainSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setChildrenMainSizeAttribute((this._childrenMainSize_0_0value as ChildrenMainSize | undefined));
                    this._childrenMainSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._childrenMainSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._childrenMainSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setChildrenMainSizeAttribute((undefined as ChildrenMainSize | undefined));
                }
            }
        }
        if (this._maintainVisibleContentPosition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._maintainVisibleContentPosition_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMaintainVisibleContentPositionAttribute((this._maintainVisibleContentPosition_0_0value as boolean | undefined));
                    this._maintainVisibleContentPosition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maintainVisibleContentPosition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._maintainVisibleContentPosition_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMaintainVisibleContentPositionAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._supportEmptyBranchInLazyLoading_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._supportEmptyBranchInLazyLoading_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSupportEmptyBranchInLazyLoadingAttribute((this._supportEmptyBranchInLazyLoading_0_0value as boolean | undefined));
                    this._supportEmptyBranchInLazyLoading_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._supportEmptyBranchInLazyLoading_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._supportEmptyBranchInLazyLoading_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSupportEmptyBranchInLazyLoadingAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._stackFromEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._stackFromEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStackFromEndAttribute((this._stackFromEnd_0_0value as boolean | undefined));
                    this._stackFromEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._stackFromEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._stackFromEnd_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStackFromEndAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._onScrollIndex_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onScrollIndex_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnScrollIndexAttribute((this._onScrollIndex_0_0value as ((start: int32,end: int32,center: int32) => void) | undefined));
                    this._onScrollIndex_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScrollIndex_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScrollIndex_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnScrollIndexAttribute((undefined as ((start: int32,end: int32,center: int32) => void) | undefined));
                }
            }
        }
        if (this._onScrollVisibleContentChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onScrollVisibleContentChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnScrollVisibleContentChangeAttribute((this._onScrollVisibleContentChange_0_0value as OnScrollVisibleContentChangeCallback | undefined));
                    this._onScrollVisibleContentChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScrollVisibleContentChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScrollVisibleContentChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnScrollVisibleContentChangeAttribute((undefined as OnScrollVisibleContentChangeCallback | undefined));
                }
            }
        }
        if (this._onItemMove_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onItemMove_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnItemMoveAttribute((this._onItemMove_0_0value as ((from: int32,to: int32) => boolean) | undefined));
                    this._onItemMove_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onItemMove_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onItemMove_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnItemMoveAttribute((undefined as ((from: int32,to: int32) => boolean) | undefined));
                }
            }
        }
        if (this._onItemDragStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onItemDragStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnItemDragStartAttribute((this._onItemDragStart_0_0value as OnItemDragStartCallback | undefined));
                    this._onItemDragStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onItemDragStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onItemDragStart_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnItemDragStartAttribute((undefined as OnItemDragStartCallback | undefined));
                }
            }
        }
        if (this._onItemDragEnter_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onItemDragEnter_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnItemDragEnterAttribute((this._onItemDragEnter_0_0value as ((event: ItemDragInfo) => void) | undefined));
                    this._onItemDragEnter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onItemDragEnter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onItemDragEnter_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnItemDragEnterAttribute((undefined as ((event: ItemDragInfo) => void) | undefined));
                }
            }
        }
        if (this._onItemDragMove_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onItemDragMove_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnItemDragMoveAttribute((this._onItemDragMove_0_0value as ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32) => void) | undefined));
                    this._onItemDragMove_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onItemDragMove_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onItemDragMove_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnItemDragMoveAttribute((undefined as ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32) => void) | undefined));
                }
            }
        }
        if (this._onItemDragLeave_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onItemDragLeave_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnItemDragLeaveAttribute((this._onItemDragLeave_0_0value as ((event: ItemDragInfo,itemIndex: int32) => void) | undefined));
                    this._onItemDragLeave_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onItemDragLeave_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onItemDragLeave_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnItemDragLeaveAttribute((undefined as ((event: ItemDragInfo,itemIndex: int32) => void) | undefined));
                }
            }
        }
        if (this._onItemDrop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onItemDrop_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnItemDropAttribute((this._onItemDrop_0_0value as ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32,isSuccess: boolean) => void) | undefined));
                    this._onItemDrop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onItemDrop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onItemDrop_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnItemDropAttribute((undefined as ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32,isSuccess: boolean) => void) | undefined));
                }
            }
        }
        if (this._onScrollFrameBegin_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onScrollFrameBegin_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnScrollFrameBeginAttribute((this._onScrollFrameBegin_0_0value as OnScrollFrameBeginCallback | undefined));
                    this._onScrollFrameBegin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScrollFrameBegin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScrollFrameBegin_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnScrollFrameBeginAttribute((undefined as OnScrollFrameBeginCallback | undefined));
                }
            }
        }
        if (this._onWillScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onWillScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnWillScrollAttribute((this._onWillScroll_0_0value as OnWillScrollCallback | undefined));
                    this._onWillScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWillScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWillScroll_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnWillScrollAttribute((undefined as OnWillScrollCallback | undefined));
                }
            }
        }
        if (this._onDidScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDidScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDidScrollAttribute((this._onDidScroll_0_0value as OnScrollCallback | undefined));
                    this._onDidScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDidScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDidScroll_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDidScrollAttribute((undefined as OnScrollCallback | undefined));
                }
            }
        }
        if (this._lanes_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._lanes_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setLanesAttribute((this._lanes_0_0value as int32 | LengthConstrain | undefined), (this._lanes_0_1value as Dimension | undefined | undefined));
                    this._lanes_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._lanes_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._lanes_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setLanesAttribute((undefined as int32 | LengthConstrain | undefined), (undefined as Dimension | undefined | undefined));
                }
            }
        }
        if (this._cachedCount_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._cachedCount_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCachedCount1Attribute((this._cachedCount_1_0value as int32 | undefined), (this._cachedCount_1_1value as boolean | undefined));
                    this._cachedCount_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._cachedCount_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._cachedCount_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCachedCount1Attribute((undefined as int32 | undefined), (undefined as boolean | undefined));
                }
            }
        }
        if (this._scrollBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._scrollBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setScrollBarAttribute((this._scrollBar_0_0value as BarState | undefined));
                    this._scrollBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._scrollBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._scrollBar_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setScrollBarAttribute((undefined as BarState | undefined));
                }
            }
        }
        if (this._scrollBarColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._scrollBarColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setScrollBarColorAttribute((this._scrollBarColor_0_0value as Color | int32 | string | undefined));
                    this._scrollBarColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._scrollBarColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._scrollBarColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setScrollBarColorAttribute((undefined as Color | int32 | string | undefined));
                }
            }
        }
        if (this._scrollBarWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._scrollBarWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setScrollBarWidthAttribute((this._scrollBarWidth_0_0value as double | string | undefined));
                    this._scrollBarWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._scrollBarWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._scrollBarWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setScrollBarWidthAttribute((undefined as double | string | undefined));
                }
            }
        }
        if (this._nestedScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._nestedScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setNestedScrollAttribute((this._nestedScroll_0_0value as NestedScrollOptions | undefined));
                    this._nestedScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._nestedScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._nestedScroll_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setNestedScrollAttribute((undefined as NestedScrollOptions | undefined));
                }
            }
        }
        if (this._enableScrollInteraction_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableScrollInteraction_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableScrollInteractionAttribute((this._enableScrollInteraction_0_0value as boolean | undefined));
                    this._enableScrollInteraction_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableScrollInteraction_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableScrollInteraction_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableScrollInteractionAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._friction_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._friction_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFrictionAttribute((this._friction_0_0value as double | Resource | undefined));
                    this._friction_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._friction_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._friction_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFrictionAttribute((undefined as double | Resource | undefined));
                }
            }
        }
        if (this._onReachStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onReachStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnReachStartAttribute((this._onReachStart_0_0value as (() => void) | undefined));
                    this._onReachStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onReachStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onReachStart_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnReachStartAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onReachEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onReachEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnReachEndAttribute((this._onReachEnd_0_0value as (() => void) | undefined));
                    this._onReachEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onReachEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onReachEnd_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnReachEndAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onScrollStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onScrollStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnScrollStartAttribute((this._onScrollStart_0_0value as (() => void) | undefined));
                    this._onScrollStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScrollStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScrollStart_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnScrollStartAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onScrollStop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onScrollStop_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnScrollStopAttribute((this._onScrollStop_0_0value as (() => void) | undefined));
                    this._onScrollStop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScrollStop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScrollStop_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnScrollStopAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._flingSpeedLimit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._flingSpeedLimit_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFlingSpeedLimitAttribute((this._flingSpeedLimit_0_0value as double | undefined));
                    this._flingSpeedLimit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._flingSpeedLimit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._flingSpeedLimit_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFlingSpeedLimitAttribute((undefined as double | undefined));
                }
            }
        }
        if (this._clipContent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._clipContent_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setClipContentAttribute((this._clipContent_0_0value as ContentClipMode | RectShape | undefined));
                    this._clipContent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._clipContent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._clipContent_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setClipContentAttribute((undefined as ContentClipMode | RectShape | undefined));
                }
            }
        }
        if (this._digitalCrownSensitivity_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._digitalCrownSensitivity_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDigitalCrownSensitivityAttribute((this._digitalCrownSensitivity_0_0value as CrownSensitivity | undefined));
                    this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDigitalCrownSensitivityAttribute((undefined as CrownSensitivity | undefined));
                }
            }
        }
        if (this._backToTop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._backToTop_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBackToTopAttribute((this._backToTop_0_0value as boolean | undefined));
                    this._backToTop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._backToTop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._backToTop_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBackToTopAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._edgeEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._edgeEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEdgeEffectAttribute((this._edgeEffect_0_0value as EdgeEffect | undefined), (this._edgeEffect_0_1value as EdgeEffectOptions | undefined | undefined));
                    this._edgeEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._edgeEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._edgeEffect_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEdgeEffectAttribute((undefined as EdgeEffect | undefined), (undefined as EdgeEffectOptions | undefined | undefined));
                }
            }
        }
        if (this._fadingEdge_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fadingEdge_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFadingEdgeAttribute((this._fadingEdge_0_0value as boolean | undefined), (this._fadingEdge_0_1value as FadingEdgeOptions | undefined | undefined));
                    this._fadingEdge_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fadingEdge_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fadingEdge_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFadingEdgeAttribute((undefined as boolean | undefined), (undefined as FadingEdgeOptions | undefined | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: ListModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._alignListItem_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._alignListItem_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.alignListItem(modifier._alignListItem_0_0value);
                    break;
                }
                default: {
                    this.alignListItem((undefined as ListItemAlign | undefined));
                }
            }
        }
        if (modifier._listDirection_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._listDirection_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.listDirection(modifier._listDirection_0_0value);
                    break;
                }
                default: {
                    this.listDirection((undefined as Axis | undefined));
                }
            }
        }
        if (modifier._contentStartOffset_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._contentStartOffset_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.contentStartOffset(modifier._contentStartOffset_0_0value);
                    break;
                }
                default: {
                    this.contentStartOffset((undefined as double | undefined));
                }
            }
        }
        if (modifier._contentEndOffset_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._contentEndOffset_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.contentEndOffset(modifier._contentEndOffset_0_0value);
                    break;
                }
                default: {
                    this.contentEndOffset((undefined as double | undefined));
                }
            }
        }
        if (modifier._divider_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._divider_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.divider(modifier._divider_0_0value);
                    break;
                }
                default: {
                    this.divider((undefined as ListDividerOptions | null | undefined));
                }
            }
        }
        if (modifier._multiSelectable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._multiSelectable_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.multiSelectable(modifier._multiSelectable_0_0value);
                    break;
                }
                default: {
                    this.multiSelectable((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._cachedCount_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._cachedCount_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.cachedCount(modifier._cachedCount_0_0value);
                    break;
                }
                default: {
                    this.cachedCount((undefined as int32 | undefined));
                }
            }
        }
        if (modifier._chainAnimation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._chainAnimation_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.chainAnimation(modifier._chainAnimation_0_0value);
                    break;
                }
                default: {
                    this.chainAnimation((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._chainAnimationOptions_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._chainAnimationOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.chainAnimationOptions(modifier._chainAnimationOptions_0_0value);
                    break;
                }
                default: {
                    this.chainAnimationOptions((undefined as ChainAnimationOptions | undefined));
                }
            }
        }
        if (modifier._sticky_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._sticky_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.sticky(modifier._sticky_0_0value);
                    break;
                }
                default: {
                    this.sticky((undefined as StickyStyle | undefined));
                }
            }
        }
        if (modifier._scrollSnapAlign_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._scrollSnapAlign_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.scrollSnapAlign(modifier._scrollSnapAlign_0_0value);
                    break;
                }
                default: {
                    this.scrollSnapAlign((undefined as ScrollSnapAlign | undefined));
                }
            }
        }
        if (modifier._childrenMainSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._childrenMainSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.childrenMainSize(modifier._childrenMainSize_0_0value);
                    break;
                }
                default: {
                    this.childrenMainSize((undefined as ChildrenMainSize | undefined));
                }
            }
        }
        if (modifier._maintainVisibleContentPosition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._maintainVisibleContentPosition_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.maintainVisibleContentPosition(modifier._maintainVisibleContentPosition_0_0value);
                    break;
                }
                default: {
                    this.maintainVisibleContentPosition((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._supportEmptyBranchInLazyLoading_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._supportEmptyBranchInLazyLoading_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.supportEmptyBranchInLazyLoading(modifier._supportEmptyBranchInLazyLoading_0_0value);
                    break;
                }
                default: {
                    this.supportEmptyBranchInLazyLoading((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._stackFromEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._stackFromEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.stackFromEnd(modifier._stackFromEnd_0_0value);
                    break;
                }
                default: {
                    this.stackFromEnd((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._onScrollIndex_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onScrollIndex_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onScrollIndex(modifier._onScrollIndex_0_0value);
                    break;
                }
                default: {
                    this.onScrollIndex((undefined as ((start: int32,end: int32,center: int32) => void) | undefined));
                }
            }
        }
        if (modifier._onScrollVisibleContentChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onScrollVisibleContentChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onScrollVisibleContentChange(modifier._onScrollVisibleContentChange_0_0value);
                    break;
                }
                default: {
                    this.onScrollVisibleContentChange((undefined as OnScrollVisibleContentChangeCallback | undefined));
                }
            }
        }
        if (modifier._onItemMove_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onItemMove_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onItemMove(modifier._onItemMove_0_0value);
                    break;
                }
                default: {
                    this.onItemMove((undefined as ((from: int32,to: int32) => boolean) | undefined));
                }
            }
        }
        if (modifier._onItemDragStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onItemDragStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onItemDragStart(modifier._onItemDragStart_0_0value);
                    break;
                }
                default: {
                    this.onItemDragStart((undefined as OnItemDragStartCallback | undefined));
                }
            }
        }
        if (modifier._onItemDragEnter_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onItemDragEnter_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onItemDragEnter(modifier._onItemDragEnter_0_0value);
                    break;
                }
                default: {
                    this.onItemDragEnter((undefined as ((event: ItemDragInfo) => void) | undefined));
                }
            }
        }
        if (modifier._onItemDragMove_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onItemDragMove_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onItemDragMove(modifier._onItemDragMove_0_0value);
                    break;
                }
                default: {
                    this.onItemDragMove((undefined as ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32) => void) | undefined));
                }
            }
        }
        if (modifier._onItemDragLeave_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onItemDragLeave_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onItemDragLeave(modifier._onItemDragLeave_0_0value);
                    break;
                }
                default: {
                    this.onItemDragLeave((undefined as ((event: ItemDragInfo,itemIndex: int32) => void) | undefined));
                }
            }
        }
        if (modifier._onItemDrop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onItemDrop_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onItemDrop(modifier._onItemDrop_0_0value);
                    break;
                }
                default: {
                    this.onItemDrop((undefined as ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32,isSuccess: boolean) => void) | undefined));
                }
            }
        }
        if (modifier._onScrollFrameBegin_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onScrollFrameBegin_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onScrollFrameBegin(modifier._onScrollFrameBegin_0_0value);
                    break;
                }
                default: {
                    this.onScrollFrameBegin((undefined as OnScrollFrameBeginCallback | undefined));
                }
            }
        }
        if (modifier._onWillScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onWillScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onWillScroll(modifier._onWillScroll_0_0value);
                    break;
                }
                default: {
                    this.onWillScroll((undefined as OnWillScrollCallback | undefined));
                }
            }
        }
        if (modifier._onDidScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDidScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDidScroll(modifier._onDidScroll_0_0value);
                    break;
                }
                default: {
                    this.onDidScroll((undefined as OnScrollCallback | undefined));
                }
            }
        }
        if (modifier._lanes_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._lanes_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.lanes(modifier._lanes_0_0value, modifier._lanes_0_1value);
                    break;
                }
                default: {
                    this.lanes((undefined as int32 | LengthConstrain | undefined), (undefined as Dimension | undefined | undefined));
                }
            }
        }
        if (modifier._cachedCount_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._cachedCount_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.cachedCount(modifier._cachedCount_1_0value, modifier._cachedCount_1_1value);
                    break;
                }
                default: {
                    this.cachedCount((undefined as int32 | undefined), (undefined as boolean | undefined));
                }
            }
        }
        if (modifier._scrollBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._scrollBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.scrollBar(modifier._scrollBar_0_0value);
                    break;
                }
                default: {
                    this.scrollBar((undefined as BarState | undefined));
                }
            }
        }
        if (modifier._scrollBarColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._scrollBarColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.scrollBarColor(modifier._scrollBarColor_0_0value);
                    break;
                }
                default: {
                    this.scrollBarColor((undefined as Color | int32 | string | undefined));
                }
            }
        }
        if (modifier._scrollBarWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._scrollBarWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.scrollBarWidth(modifier._scrollBarWidth_0_0value);
                    break;
                }
                default: {
                    this.scrollBarWidth((undefined as double | string | undefined));
                }
            }
        }
        if (modifier._nestedScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._nestedScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.nestedScroll(modifier._nestedScroll_0_0value);
                    break;
                }
                default: {
                    this.nestedScroll((undefined as NestedScrollOptions | undefined));
                }
            }
        }
        if (modifier._enableScrollInteraction_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableScrollInteraction_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableScrollInteraction(modifier._enableScrollInteraction_0_0value);
                    break;
                }
                default: {
                    this.enableScrollInteraction((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._friction_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._friction_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.friction(modifier._friction_0_0value);
                    break;
                }
                default: {
                    this.friction((undefined as double | Resource | undefined));
                }
            }
        }
        if (modifier._onReachStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onReachStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onReachStart(modifier._onReachStart_0_0value);
                    break;
                }
                default: {
                    this.onReachStart((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onReachEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onReachEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onReachEnd(modifier._onReachEnd_0_0value);
                    break;
                }
                default: {
                    this.onReachEnd((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onScrollStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onScrollStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onScrollStart(modifier._onScrollStart_0_0value);
                    break;
                }
                default: {
                    this.onScrollStart((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onScrollStop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onScrollStop_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onScrollStop(modifier._onScrollStop_0_0value);
                    break;
                }
                default: {
                    this.onScrollStop((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._flingSpeedLimit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._flingSpeedLimit_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.flingSpeedLimit(modifier._flingSpeedLimit_0_0value);
                    break;
                }
                default: {
                    this.flingSpeedLimit((undefined as double | undefined));
                }
            }
        }
        if (modifier._clipContent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._clipContent_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.clipContent(modifier._clipContent_0_0value);
                    break;
                }
                default: {
                    this.clipContent((undefined as ContentClipMode | RectShape | undefined));
                }
            }
        }
        if (modifier._digitalCrownSensitivity_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._digitalCrownSensitivity_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.digitalCrownSensitivity(modifier._digitalCrownSensitivity_0_0value);
                    break;
                }
                default: {
                    this.digitalCrownSensitivity((undefined as CrownSensitivity | undefined));
                }
            }
        }
        if (modifier._backToTop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._backToTop_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.backToTop(modifier._backToTop_0_0value);
                    break;
                }
                default: {
                    this.backToTop((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._edgeEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._edgeEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.edgeEffect(modifier._edgeEffect_0_0value, modifier._edgeEffect_0_1value);
                    break;
                }
                default: {
                    this.edgeEffect((undefined as EdgeEffect | undefined), (undefined as EdgeEffectOptions | undefined | undefined));
                }
            }
        }
        if (modifier._fadingEdge_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fadingEdge_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fadingEdge(modifier._fadingEdge_0_0value, modifier._fadingEdge_0_1value);
                    break;
                }
                default: {
                    this.fadingEdge((undefined as boolean | undefined), (undefined as FadingEdgeOptions | undefined | undefined));
                }
            }
        }
    }
    alignListItem(value: ListItemAlign | undefined): this {
        if (((this._alignListItem_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._alignListItem_0_flag = AttributeUpdaterFlag.UPDATE
            this._alignListItem_0_0value = value
        } else
        {
            this._alignListItem_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    listDirection(value: Axis | undefined): this {
        if (((this._listDirection_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._listDirection_0_flag = AttributeUpdaterFlag.UPDATE
            this._listDirection_0_0value = value
        } else
        {
            this._listDirection_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    contentStartOffset(value: double | undefined): this {
        if (((this._contentStartOffset_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._contentStartOffset_0_0value) !== (value)))
        {
            this._contentStartOffset_0_flag = AttributeUpdaterFlag.UPDATE
            this._contentStartOffset_0_0value = value
        } else
        {
            this._contentStartOffset_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    contentEndOffset(value: double | undefined): this {
        if (((this._contentEndOffset_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._contentEndOffset_0_0value) !== (value)))
        {
            this._contentEndOffset_0_flag = AttributeUpdaterFlag.UPDATE
            this._contentEndOffset_0_0value = value
        } else
        {
            this._contentEndOffset_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    divider(value: ListDividerOptions | null | undefined): this {
        if (((this._divider_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._divider_0_flag = AttributeUpdaterFlag.UPDATE
            this._divider_0_0value = value
        } else
        {
            this._divider_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    multiSelectable(value: boolean | undefined): this {
        if (((this._multiSelectable_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._multiSelectable_0_0value) !== (value)))
        {
            this._multiSelectable_0_flag = AttributeUpdaterFlag.UPDATE
            this._multiSelectable_0_0value = value
        } else
        {
            this._multiSelectable_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    cachedCount(value: int32 | undefined): this {
        if (((this._cachedCount_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._cachedCount_0_0value) !== (value)))
        {
            this._cachedCount_0_flag = AttributeUpdaterFlag.UPDATE
            this._cachedCount_0_0value = value
        } else
        {
            this._cachedCount_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    chainAnimation(value: boolean | undefined): this {
        if (((this._chainAnimation_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._chainAnimation_0_0value) !== (value)))
        {
            this._chainAnimation_0_flag = AttributeUpdaterFlag.UPDATE
            this._chainAnimation_0_0value = value
        } else
        {
            this._chainAnimation_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    chainAnimationOptions(value: ChainAnimationOptions | undefined): this {
        if (((this._chainAnimationOptions_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._chainAnimationOptions_0_flag = AttributeUpdaterFlag.UPDATE
            this._chainAnimationOptions_0_0value = value
        } else
        {
            this._chainAnimationOptions_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    sticky(value: StickyStyle | undefined): this {
        if (((this._sticky_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._sticky_0_flag = AttributeUpdaterFlag.UPDATE
            this._sticky_0_0value = value
        } else
        {
            this._sticky_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    scrollSnapAlign(value: ScrollSnapAlign | undefined): this {
        if (((this._scrollSnapAlign_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._scrollSnapAlign_0_flag = AttributeUpdaterFlag.UPDATE
            this._scrollSnapAlign_0_0value = value
        } else
        {
            this._scrollSnapAlign_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    childrenMainSize(value: ChildrenMainSize | undefined): this {
        if (((this._childrenMainSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._childrenMainSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._childrenMainSize_0_0value = value
        } else
        {
            this._childrenMainSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    maintainVisibleContentPosition(value: boolean | undefined): this {
        if (((this._maintainVisibleContentPosition_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._maintainVisibleContentPosition_0_0value) !== (value)))
        {
            this._maintainVisibleContentPosition_0_flag = AttributeUpdaterFlag.UPDATE
            this._maintainVisibleContentPosition_0_0value = value
        } else
        {
            this._maintainVisibleContentPosition_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    supportEmptyBranchInLazyLoading(value: boolean | undefined): this {
        if (((this._supportEmptyBranchInLazyLoading_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._supportEmptyBranchInLazyLoading_0_0value) !== (value)))
        {
            this._supportEmptyBranchInLazyLoading_0_flag = AttributeUpdaterFlag.UPDATE
            this._supportEmptyBranchInLazyLoading_0_0value = value
        } else
        {
            this._supportEmptyBranchInLazyLoading_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    stackFromEnd(value: boolean | undefined): this {
        if (((this._stackFromEnd_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._stackFromEnd_0_0value) !== (value)))
        {
            this._stackFromEnd_0_flag = AttributeUpdaterFlag.UPDATE
            this._stackFromEnd_0_0value = value
        } else
        {
            this._stackFromEnd_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onScrollIndex(value: ((start: int32,end: int32,center: int32) => void) | undefined): this {
        if (((this._onScrollIndex_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onScrollIndex_0_flag = AttributeUpdaterFlag.UPDATE
            this._onScrollIndex_0_0value = value
        } else
        {
            this._onScrollIndex_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onScrollVisibleContentChange(value: OnScrollVisibleContentChangeCallback | undefined): this {
        if (((this._onScrollVisibleContentChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onScrollVisibleContentChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onScrollVisibleContentChange_0_0value = value
        } else
        {
            this._onScrollVisibleContentChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onItemMove(value: ((from: int32,to: int32) => boolean) | undefined): this {
        if (((this._onItemMove_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onItemMove_0_flag = AttributeUpdaterFlag.UPDATE
            this._onItemMove_0_0value = value
        } else
        {
            this._onItemMove_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onItemDragStart(value: OnItemDragStartCallback | undefined): this {
        if (((this._onItemDragStart_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onItemDragStart_0_flag = AttributeUpdaterFlag.UPDATE
            this._onItemDragStart_0_0value = value
        } else
        {
            this._onItemDragStart_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onItemDragEnter(value: ((event: ItemDragInfo) => void) | undefined): this {
        if (((this._onItemDragEnter_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onItemDragEnter_0_flag = AttributeUpdaterFlag.UPDATE
            this._onItemDragEnter_0_0value = value
        } else
        {
            this._onItemDragEnter_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onItemDragMove(value: ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32) => void) | undefined): this {
        if (((this._onItemDragMove_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onItemDragMove_0_flag = AttributeUpdaterFlag.UPDATE
            this._onItemDragMove_0_0value = value
        } else
        {
            this._onItemDragMove_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onItemDragLeave(value: ((event: ItemDragInfo,itemIndex: int32) => void) | undefined): this {
        if (((this._onItemDragLeave_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onItemDragLeave_0_flag = AttributeUpdaterFlag.UPDATE
            this._onItemDragLeave_0_0value = value
        } else
        {
            this._onItemDragLeave_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onItemDrop(value: ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32,isSuccess: boolean) => void) | undefined): this {
        if (((this._onItemDrop_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onItemDrop_0_flag = AttributeUpdaterFlag.UPDATE
            this._onItemDrop_0_0value = value
        } else
        {
            this._onItemDrop_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        if (((this._onScrollFrameBegin_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onScrollFrameBegin_0_flag = AttributeUpdaterFlag.UPDATE
            this._onScrollFrameBegin_0_0value = value
        } else
        {
            this._onScrollFrameBegin_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onWillScroll(value: OnWillScrollCallback | undefined): this {
        if (((this._onWillScroll_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onWillScroll_0_flag = AttributeUpdaterFlag.UPDATE
            this._onWillScroll_0_0value = value
        } else
        {
            this._onWillScroll_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDidScroll(value: OnScrollCallback | undefined): this {
        if (((this._onDidScroll_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDidScroll_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDidScroll_0_0value = value
        } else
        {
            this._onDidScroll_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    lanes(value: int32 | LengthConstrain | undefined, gutter?: Dimension): this {
        if (((this._lanes_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._lanes_0_flag = AttributeUpdaterFlag.UPDATE
            this._lanes_0_0value = value
            this._lanes_0_1value = gutter
        } else
        {
            this._lanes_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    cachedCount(count: int32 | undefined, show: boolean | undefined): this {
        if (((this._cachedCount_1_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._cachedCount_1_0value) !== (count)) || ((this._cachedCount_1_1value) !== (show)))
        {
            this._cachedCount_1_flag = AttributeUpdaterFlag.UPDATE
            this._cachedCount_1_0value = count
            this._cachedCount_1_1value = show
        } else
        {
            this._cachedCount_1_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    scrollBar(value: BarState | undefined): this {
        if (((this._scrollBar_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._scrollBar_0_flag = AttributeUpdaterFlag.UPDATE
            this._scrollBar_0_0value = value
        } else
        {
            this._scrollBar_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    scrollBarColor(value: Color | int32 | string | undefined): this {
        if (((this._scrollBarColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._scrollBarColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._scrollBarColor_0_0value = value
        } else
        {
            this._scrollBarColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    scrollBarWidth(value: double | string | undefined): this {
        if (((this._scrollBarWidth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._scrollBarWidth_0_0value) !== (value)))
        {
            this._scrollBarWidth_0_flag = AttributeUpdaterFlag.UPDATE
            this._scrollBarWidth_0_0value = value
        } else
        {
            this._scrollBarWidth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    nestedScroll(value: NestedScrollOptions | undefined): this {
        if (((this._nestedScroll_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._nestedScroll_0_flag = AttributeUpdaterFlag.UPDATE
            this._nestedScroll_0_0value = value
        } else
        {
            this._nestedScroll_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableScrollInteraction(value: boolean | undefined): this {
        if (((this._enableScrollInteraction_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableScrollInteraction_0_0value) !== (value)))
        {
            this._enableScrollInteraction_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableScrollInteraction_0_0value = value
        } else
        {
            this._enableScrollInteraction_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    friction(value: double | Resource | undefined): this {
        if (((this._friction_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._friction_0_flag = AttributeUpdaterFlag.UPDATE
            this._friction_0_0value = value
        } else
        {
            this._friction_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onReachStart(value: (() => void) | undefined): this {
        if (((this._onReachStart_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onReachStart_0_flag = AttributeUpdaterFlag.UPDATE
            this._onReachStart_0_0value = value
        } else
        {
            this._onReachStart_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onReachEnd(value: (() => void) | undefined): this {
        if (((this._onReachEnd_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onReachEnd_0_flag = AttributeUpdaterFlag.UPDATE
            this._onReachEnd_0_0value = value
        } else
        {
            this._onReachEnd_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onScrollStart(value: (() => void) | undefined): this {
        if (((this._onScrollStart_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onScrollStart_0_flag = AttributeUpdaterFlag.UPDATE
            this._onScrollStart_0_0value = value
        } else
        {
            this._onScrollStart_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onScrollStop(value: (() => void) | undefined): this {
        if (((this._onScrollStop_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onScrollStop_0_flag = AttributeUpdaterFlag.UPDATE
            this._onScrollStop_0_0value = value
        } else
        {
            this._onScrollStop_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    flingSpeedLimit(value: double | undefined): this {
        if (((this._flingSpeedLimit_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._flingSpeedLimit_0_0value) !== (value)))
        {
            this._flingSpeedLimit_0_flag = AttributeUpdaterFlag.UPDATE
            this._flingSpeedLimit_0_0value = value
        } else
        {
            this._flingSpeedLimit_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    clipContent(value: ContentClipMode | RectShape | undefined): this {
        if (((this._clipContent_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._clipContent_0_flag = AttributeUpdaterFlag.UPDATE
            this._clipContent_0_0value = value
        } else
        {
            this._clipContent_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        if (((this._digitalCrownSensitivity_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.UPDATE
            this._digitalCrownSensitivity_0_0value = value
        } else
        {
            this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    backToTop(value: boolean | undefined): this {
        if (((this._backToTop_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._backToTop_0_0value) !== (value)))
        {
            this._backToTop_0_flag = AttributeUpdaterFlag.UPDATE
            this._backToTop_0_0value = value
        } else
        {
            this._backToTop_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    edgeEffect(edgeEffect: EdgeEffect | undefined, options?: EdgeEffectOptions): this {
        if (((this._edgeEffect_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._edgeEffect_0_flag = AttributeUpdaterFlag.UPDATE
            this._edgeEffect_0_0value = edgeEffect
            this._edgeEffect_0_1value = options
        } else
        {
            this._edgeEffect_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fadingEdge(enabled: boolean | undefined, options?: FadingEdgeOptions): this {
        if (((this._fadingEdge_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._fadingEdge_0_0value) !== (enabled)) || (true))
        {
            this._fadingEdge_0_flag = AttributeUpdaterFlag.UPDATE
            this._fadingEdge_0_0value = enabled
            this._fadingEdge_0_1value = options
        } else
        {
            this._fadingEdge_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ListAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

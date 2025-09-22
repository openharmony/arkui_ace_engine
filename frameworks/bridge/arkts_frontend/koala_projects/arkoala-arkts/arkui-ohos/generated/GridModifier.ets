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

import { ScrollableCommonMethodModifier } from "./ScrollableCommonMethodModifier"
import { CommonMethodModifier } from "./CommonMethodModifier"
import { AttributeModifier } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkGridPeer, ComputedBarAttribute, GridDirection, GridItemAlignment, GridAttribute } from "./component/grid"
import { int32 } from "@koalaui/common"
import { ScrollableCommonMethod, OnItemDragStartCallback, ItemDragInfo, NestedScrollOptions, OnWillScrollCallback, OnScrollCallback, CommonMethod, EdgeEffectOptions } from "./component/common"
import { Length } from "./component/units"
import { Resource } from "global.resource"
import { Color, BarState, ScrollSource, EdgeEffect } from "./component/enums"
import { OnScrollFrameBeginCallback } from "./component/scroll"
import { ScrollState } from "./component/list"
export class GridModifier extends ScrollableCommonMethodModifier implements GridAttribute,AttributeModifier<GridAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: GridAttribute): void { }
    applyPressedAttribute(instance: GridAttribute): void { }
    applyFocusedAttribute(instance: GridAttribute): void { }
    applyDisabledAttribute(instance: GridAttribute): void { }
    applySelectedAttribute(instance: GridAttribute): void { }
    _columnsTemplate_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _columnsTemplate_0_0value?: string | undefined
    _rowsTemplate_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _rowsTemplate_0_0value?: string | undefined
    _columnsGap_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _columnsGap_0_0value?: Length | undefined
    _rowsGap_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _rowsGap_0_0value?: Length | undefined
    _scrollBarWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _scrollBarWidth_0_0value?: number | string | undefined
    _scrollBarColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _scrollBarColor_0_0value?: Color | number | string | undefined
    _scrollBar_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _scrollBar_0_0value?: BarState | undefined
    _onScrollBarUpdate_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onScrollBarUpdate_0_0value?: ((index: number,offset: number) => ComputedBarAttribute) | undefined
    _onScrollIndex_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onScrollIndex_0_0value?: ((first: number,last: number) => void) | undefined
    _cachedCount_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _cachedCount_0_0value?: number | undefined
    _editMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _editMode_0_0value?: boolean | undefined
    _multiSelectable_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _multiSelectable_0_0value?: boolean | undefined
    _maxCount_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maxCount_0_0value?: number | undefined
    _minCount_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _minCount_0_0value?: number | undefined
    _cellLength_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _cellLength_0_0value?: number | undefined
    _layoutDirection_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _layoutDirection_0_0value?: GridDirection | undefined
    _supportAnimation_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _supportAnimation_0_0value?: boolean | undefined
    _onItemDragStart_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onItemDragStart_0_0value?: OnItemDragStartCallback | undefined
    _onItemDragEnter_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onItemDragEnter_0_0value?: ((event: ItemDragInfo) => void) | undefined
    _onItemDragMove_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onItemDragMove_0_0value?: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void) | undefined
    _onItemDragLeave_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onItemDragLeave_0_0value?: ((event: ItemDragInfo,itemIndex: number) => void) | undefined
    _onItemDrop_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onItemDrop_0_0value?: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void) | undefined
    _nestedScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _nestedScroll_0_0value?: NestedScrollOptions | undefined
    _enableScrollInteraction_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableScrollInteraction_0_0value?: boolean | undefined
    _friction_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _friction_0_0value?: number | Resource | undefined
    _alignItems_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _alignItems_0_0value?: GridItemAlignment | undefined
    _onScrollFrameBegin_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onScrollFrameBegin_0_0value?: OnScrollFrameBeginCallback | undefined
    _onWillScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWillScroll_0_0value?: OnWillScrollCallback | undefined
    _onDidScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDidScroll_0_0value?: OnScrollCallback | undefined
    _cachedCount_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _cachedCount_1_0value?: number | undefined
    _cachedCount_1_1value?: boolean | undefined
    _edgeEffect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _edgeEffect_0_0value?: EdgeEffect | undefined
    _edgeEffect_0_1value?: EdgeEffectOptions | undefined
    applyModifierPatch(node: PeerNode): void {
        super.applyModifierPatch(node)
        const peer = node as ArkGridPeer;
        if (this._columnsTemplate_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._columnsTemplate_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setColumnsTemplateAttribute((this._columnsTemplate_0_0value as string | undefined));
                    this._columnsTemplate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._columnsTemplate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._columnsTemplate_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setColumnsTemplateAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._rowsTemplate_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._rowsTemplate_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRowsTemplateAttribute((this._rowsTemplate_0_0value as string | undefined));
                    this._rowsTemplate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._rowsTemplate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._rowsTemplate_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRowsTemplateAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._columnsGap_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._columnsGap_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setColumnsGapAttribute((this._columnsGap_0_0value as Length | undefined));
                    this._columnsGap_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._columnsGap_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._columnsGap_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setColumnsGapAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._rowsGap_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._rowsGap_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRowsGapAttribute((this._rowsGap_0_0value as Length | undefined));
                    this._rowsGap_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._rowsGap_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._rowsGap_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRowsGapAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._scrollBarWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._scrollBarWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setScrollBarWidthAttribute((this._scrollBarWidth_0_0value as number | string | undefined));
                    this._scrollBarWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._scrollBarWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._scrollBarWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setScrollBarWidthAttribute((undefined as number | string | undefined));
                }
            }
        }
        if (this._scrollBarColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._scrollBarColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setScrollBarColorAttribute((this._scrollBarColor_0_0value as Color | number | string | undefined));
                    this._scrollBarColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._scrollBarColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._scrollBarColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setScrollBarColorAttribute((undefined as Color | number | string | undefined));
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
        if (this._onScrollBarUpdate_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onScrollBarUpdate_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnScrollBarUpdateAttribute((this._onScrollBarUpdate_0_0value as ((index: number,offset: number) => ComputedBarAttribute) | undefined));
                    this._onScrollBarUpdate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScrollBarUpdate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScrollBarUpdate_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnScrollBarUpdateAttribute((undefined as ((index: number,offset: number) => ComputedBarAttribute) | undefined));
                }
            }
        }
        if (this._onScrollIndex_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onScrollIndex_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnScrollIndexAttribute((this._onScrollIndex_0_0value as ((first: number,last: number) => void) | undefined));
                    this._onScrollIndex_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScrollIndex_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScrollIndex_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnScrollIndexAttribute((undefined as ((first: number,last: number) => void) | undefined));
                }
            }
        }
        if (this._cachedCount_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._cachedCount_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCachedCount0Attribute((this._cachedCount_0_0value as number | undefined));
                    this._cachedCount_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._cachedCount_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._cachedCount_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCachedCount0Attribute((undefined as number | undefined));
                }
            }
        }
        if (this._editMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._editMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEditModeAttribute((this._editMode_0_0value as boolean | undefined));
                    this._editMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._editMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._editMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEditModeAttribute((undefined as boolean | undefined));
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
        if (this._maxCount_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._maxCount_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMaxCountAttribute((this._maxCount_0_0value as number | undefined));
                    this._maxCount_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maxCount_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._maxCount_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMaxCountAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._minCount_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._minCount_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMinCountAttribute((this._minCount_0_0value as number | undefined));
                    this._minCount_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minCount_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._minCount_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMinCountAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._cellLength_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._cellLength_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCellLengthAttribute((this._cellLength_0_0value as number | undefined));
                    this._cellLength_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._cellLength_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._cellLength_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCellLengthAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._layoutDirection_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._layoutDirection_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setLayoutDirectionAttribute((this._layoutDirection_0_0value as GridDirection | undefined));
                    this._layoutDirection_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._layoutDirection_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._layoutDirection_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setLayoutDirectionAttribute((undefined as GridDirection | undefined));
                }
            }
        }
        if (this._supportAnimation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._supportAnimation_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSupportAnimationAttribute((this._supportAnimation_0_0value as boolean | undefined));
                    this._supportAnimation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._supportAnimation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._supportAnimation_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSupportAnimationAttribute((undefined as boolean | undefined));
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
                    peer.setOnItemDragMoveAttribute((this._onItemDragMove_0_0value as ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void) | undefined));
                    this._onItemDragMove_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onItemDragMove_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onItemDragMove_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnItemDragMoveAttribute((undefined as ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void) | undefined));
                }
            }
        }
        if (this._onItemDragLeave_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onItemDragLeave_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnItemDragLeaveAttribute((this._onItemDragLeave_0_0value as ((event: ItemDragInfo,itemIndex: number) => void) | undefined));
                    this._onItemDragLeave_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onItemDragLeave_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onItemDragLeave_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnItemDragLeaveAttribute((undefined as ((event: ItemDragInfo,itemIndex: number) => void) | undefined));
                }
            }
        }
        if (this._onItemDrop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onItemDrop_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnItemDropAttribute((this._onItemDrop_0_0value as ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void) | undefined));
                    this._onItemDrop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onItemDrop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onItemDrop_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnItemDropAttribute((undefined as ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void) | undefined));
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
                    peer.setFrictionAttribute((this._friction_0_0value as number | Resource | undefined));
                    this._friction_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._friction_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._friction_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFrictionAttribute((undefined as number | Resource | undefined));
                }
            }
        }
        if (this._alignItems_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._alignItems_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAlignItemsAttribute((this._alignItems_0_0value as GridItemAlignment | undefined));
                    this._alignItems_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._alignItems_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._alignItems_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAlignItemsAttribute((undefined as GridItemAlignment | undefined));
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
        if (this._cachedCount_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._cachedCount_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCachedCount1Attribute((this._cachedCount_1_0value as number | undefined), (this._cachedCount_1_1value as boolean | undefined));
                    this._cachedCount_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._cachedCount_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._cachedCount_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCachedCount1Attribute((undefined as number | undefined), (undefined as boolean | undefined));
                }
            }
        }
        if (this._edgeEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._edgeEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEdgeEffectAttribute((this._edgeEffect_0_0value as EdgeEffect | undefined), (this._edgeEffect_0_1value as EdgeEffectOptions));
                    this._edgeEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._edgeEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._edgeEffect_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEdgeEffectAttribute((undefined as EdgeEffect | undefined), (undefined as EdgeEffectOptions | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: GridModifier): void {
        super.mergeModifier(modifier)
        if (modifier._columnsTemplate_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._columnsTemplate_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.columnsTemplate(modifier._columnsTemplate_0_0value);
                    break;
                }
                default: {
                    this.columnsTemplate((undefined as string | undefined));
                }
            }
        }
        if (modifier._rowsTemplate_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._rowsTemplate_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.rowsTemplate(modifier._rowsTemplate_0_0value);
                    break;
                }
                default: {
                    this.rowsTemplate((undefined as string | undefined));
                }
            }
        }
        if (modifier._columnsGap_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._columnsGap_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.columnsGap(modifier._columnsGap_0_0value);
                    break;
                }
                default: {
                    this.columnsGap((undefined as Length | undefined));
                }
            }
        }
        if (modifier._rowsGap_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._rowsGap_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.rowsGap(modifier._rowsGap_0_0value);
                    break;
                }
                default: {
                    this.rowsGap((undefined as Length | undefined));
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
                    this.scrollBarWidth((undefined as number | string | undefined));
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
                    this.scrollBarColor((undefined as Color | number | string | undefined));
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
        if (modifier._onScrollBarUpdate_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onScrollBarUpdate_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onScrollBarUpdate(modifier._onScrollBarUpdate_0_0value);
                    break;
                }
                default: {
                    this.onScrollBarUpdate((undefined as ((index: number,offset: number) => ComputedBarAttribute) | undefined));
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
                    this.onScrollIndex((undefined as ((first: number,last: number) => void) | undefined));
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
                    this.cachedCount((undefined as number | undefined));
                }
            }
        }
        if (modifier._editMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._editMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.editMode(modifier._editMode_0_0value);
                    break;
                }
                default: {
                    this.editMode((undefined as boolean | undefined));
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
        if (modifier._maxCount_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._maxCount_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.maxCount(modifier._maxCount_0_0value);
                    break;
                }
                default: {
                    this.maxCount((undefined as number | undefined));
                }
            }
        }
        if (modifier._minCount_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._minCount_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.minCount(modifier._minCount_0_0value);
                    break;
                }
                default: {
                    this.minCount((undefined as number | undefined));
                }
            }
        }
        if (modifier._cellLength_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._cellLength_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.cellLength(modifier._cellLength_0_0value);
                    break;
                }
                default: {
                    this.cellLength((undefined as number | undefined));
                }
            }
        }
        if (modifier._layoutDirection_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._layoutDirection_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.layoutDirection(modifier._layoutDirection_0_0value);
                    break;
                }
                default: {
                    this.layoutDirection((undefined as GridDirection | undefined));
                }
            }
        }
        if (modifier._supportAnimation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._supportAnimation_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.supportAnimation(modifier._supportAnimation_0_0value);
                    break;
                }
                default: {
                    this.supportAnimation((undefined as boolean | undefined));
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
                    this.onItemDragMove((undefined as ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void) | undefined));
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
                    this.onItemDragLeave((undefined as ((event: ItemDragInfo,itemIndex: number) => void) | undefined));
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
                    this.onItemDrop((undefined as ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void) | undefined));
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
                    this.friction((undefined as number | Resource | undefined));
                }
            }
        }
        if (modifier._alignItems_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._alignItems_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.alignItems(modifier._alignItems_0_0value);
                    break;
                }
                default: {
                    this.alignItems((undefined as GridItemAlignment | undefined));
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
        if (modifier._cachedCount_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._cachedCount_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.cachedCount(modifier._cachedCount_1_0value, modifier._cachedCount_1_1value);
                    break;
                }
                default: {
                    this.cachedCount((undefined as number | undefined), (undefined as boolean | undefined));
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
                    this.edgeEffect((undefined as EdgeEffect | undefined), (undefined as EdgeEffectOptions | undefined));
                }
            }
        }
    }
    columnsTemplate(value: string | undefined): this {
        if (((this._columnsTemplate_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._columnsTemplate_0_0value) !== (value)))
        {
            this._columnsTemplate_0_flag = AttributeUpdaterFlag.UPDATE
            this._columnsTemplate_0_0value = value
        } else
        {
            this._columnsTemplate_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    rowsTemplate(value: string | undefined): this {
        if (((this._rowsTemplate_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._rowsTemplate_0_0value) !== (value)))
        {
            this._rowsTemplate_0_flag = AttributeUpdaterFlag.UPDATE
            this._rowsTemplate_0_0value = value
        } else
        {
            this._rowsTemplate_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    columnsGap(value: Length | undefined): this {
        if (((this._columnsGap_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._columnsGap_0_flag = AttributeUpdaterFlag.UPDATE
            this._columnsGap_0_0value = value
        } else
        {
            this._columnsGap_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    rowsGap(value: Length | undefined): this {
        if (((this._rowsGap_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._rowsGap_0_flag = AttributeUpdaterFlag.UPDATE
            this._rowsGap_0_0value = value
        } else
        {
            this._rowsGap_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    scrollBarWidth(value: number | string | undefined): this {
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
    scrollBarColor(value: Color | number | string | undefined): this {
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
    onScrollBarUpdate(value: ((index: number,offset: number) => ComputedBarAttribute) | undefined): this {
        if (((this._onScrollBarUpdate_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onScrollBarUpdate_0_flag = AttributeUpdaterFlag.UPDATE
            this._onScrollBarUpdate_0_0value = value
        } else
        {
            this._onScrollBarUpdate_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onScrollIndex(value: ((first: number,last: number) => void) | undefined): this {
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
    cachedCount(value: number | undefined): this {
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
    editMode(value: boolean | undefined): this {
        if (((this._editMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._editMode_0_0value) !== (value)))
        {
            this._editMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._editMode_0_0value = value
        } else
        {
            this._editMode_0_flag = AttributeUpdaterFlag.SKIP
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
    maxCount(value: number | undefined): this {
        if (((this._maxCount_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._maxCount_0_0value) !== (value)))
        {
            this._maxCount_0_flag = AttributeUpdaterFlag.UPDATE
            this._maxCount_0_0value = value
        } else
        {
            this._maxCount_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    minCount(value: number | undefined): this {
        if (((this._minCount_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._minCount_0_0value) !== (value)))
        {
            this._minCount_0_flag = AttributeUpdaterFlag.UPDATE
            this._minCount_0_0value = value
        } else
        {
            this._minCount_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    cellLength(value: number | undefined): this {
        if (((this._cellLength_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._cellLength_0_0value) !== (value)))
        {
            this._cellLength_0_flag = AttributeUpdaterFlag.UPDATE
            this._cellLength_0_0value = value
        } else
        {
            this._cellLength_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    layoutDirection(value: GridDirection | undefined): this {
        if (((this._layoutDirection_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._layoutDirection_0_flag = AttributeUpdaterFlag.UPDATE
            this._layoutDirection_0_0value = value
        } else
        {
            this._layoutDirection_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    supportAnimation(value: boolean | undefined): this {
        if (((this._supportAnimation_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._supportAnimation_0_0value) !== (value)))
        {
            this._supportAnimation_0_flag = AttributeUpdaterFlag.UPDATE
            this._supportAnimation_0_0value = value
        } else
        {
            this._supportAnimation_0_flag = AttributeUpdaterFlag.SKIP
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
    onItemDragMove(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void) | undefined): this {
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
    onItemDragLeave(value: ((event: ItemDragInfo,itemIndex: number) => void) | undefined): this {
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
    onItemDrop(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void) | undefined): this {
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
    friction(value: number | Resource | undefined): this {
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
    alignItems(value: GridItemAlignment | undefined): this {
        if (((this._alignItems_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._alignItems_0_flag = AttributeUpdaterFlag.UPDATE
            this._alignItems_0_0value = value
        } else
        {
            this._alignItems_0_flag = AttributeUpdaterFlag.SKIP
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
    cachedCount(count: number | undefined, show: boolean | undefined): this {
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
    edgeEffect(value: EdgeEffect | undefined, options?: EdgeEffectOptions): this {
        if (((this._edgeEffect_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._edgeEffect_0_flag = AttributeUpdaterFlag.UPDATE
            this._edgeEffect_0_0value = value
            this._edgeEffect_0_1value = options
        } else
        {
            this._edgeEffect_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<GridAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

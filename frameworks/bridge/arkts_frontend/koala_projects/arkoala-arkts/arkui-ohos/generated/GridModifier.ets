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

import { CommonMethod, NestedScrollOptions, ContentClipMode, EdgeEffectOptions, FadingEdgeOptions, ScrollableCommonMethod, OnItemDragStartCallback, ItemDragInfo, OnWillScrollCallback, OnScrollCallback } from './component/common'
import { BarState, Color as arkui_component_enums_Color, CrownSensitivity, EdgeEffect, ScrollSource } from './component/enums'
import { Resource as global_resource_Resource } from 'global.resource'
import { extractors, AttributeModifier } from '#handwritten'
import { RectShape } from '@ohos.arkui.shape'
import { ScrollableCommonMethodModifier } from './ScrollableCommonMethodModifier'
import { CommonMethodModifier } from './CommonMethodModifier'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkGridPeer, ComputedBarAttribute, GridDirection, GridItemAlignment, GridAttribute } from './component/grid'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { Length, Resource as arkui_component_units_Resource } from './component/units'
import { OnScrollFrameBeginCallback } from './component/scroll'
import { ScrollState } from './component/list'
export class GridModifier extends CommonMethodModifier implements GridAttribute,AttributeModifier<GridAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState;
    _addr: ArrayBuffer = new ArrayBuffer(4096);
    _flagArray: Uint8Array = new Uint8Array(this._addr);
    constructor() {
        super();
        this._flagArray.fill(0);
    }
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: GridAttribute): void { }
    applyPressedAttribute(instance: GridAttribute): void { }
    applyFocusedAttribute(instance: GridAttribute): void { }
    applyDisabledAttribute(instance: GridAttribute): void { }
    applySelectedAttribute(instance: GridAttribute): void { }
    public _columnsTemplate_0_0value?: string | undefined
    public _rowsTemplate_0_0value?: string | undefined
    public _columnsGap_0_0value?: Length | undefined
    public _rowsGap_0_0value?: Length | undefined
    public _scrollBarWidth_0_0value?: double | string | undefined
    public _scrollBarColor_0_0value?: arkui_component_enums_Color | int32 | string | undefined
    public _scrollBar_0_0value?: BarState | undefined
    public _onScrollBarUpdate_0_0value?: ((index: int32,offset: double) => ComputedBarAttribute) | undefined
    public _onScrollIndex_0_0value?: ((first: int32,last: int32) => void) | undefined
    public _cachedCount_0_0value?: int32 | undefined
    public _editMode_0_0value?: boolean | undefined
    public _multiSelectable_0_0value?: boolean | undefined
    public _maxCount_0_0value?: int32 | undefined
    public _minCount_0_0value?: int32 | undefined
    public _cellLength_0_0value?: double | undefined
    public _layoutDirection_0_0value?: GridDirection | undefined
    public _supportAnimation_0_0value?: boolean | undefined
    public _onItemDragStart_0_0value?: OnItemDragStartCallback | undefined
    public _onItemDragEnter_0_0value?: ((event: ItemDragInfo) => void) | undefined
    public _onItemDragMove_0_0value?: ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32) => void) | undefined
    public _onItemDragLeave_0_0value?: ((event: ItemDragInfo,itemIndex: int32) => void) | undefined
    public _onItemDrop_0_0value?: ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32,isSuccess: boolean) => void) | undefined
    public _nestedScroll_0_0value?: NestedScrollOptions | undefined
    public _enableScrollInteraction_0_0value?: boolean | undefined
    public _friction_0_0value?: double | arkui_component_units_Resource | undefined
    public _alignItems_0_0value?: GridItemAlignment | undefined
    public _onScrollFrameBegin_0_0value?: OnScrollFrameBeginCallback | undefined
    public _onWillScroll_0_0value?: OnWillScrollCallback | undefined
    public _onDidScroll_0_0value?: OnScrollCallback | undefined
    public _cachedCount_1_0value?: int32 | undefined
    public _cachedCount_1_1value?: boolean | undefined
    public _edgeEffect_0_0value?: EdgeEffect | undefined
    public _edgeEffect_0_1value?: EdgeEffectOptions | undefined
    public _onReachStart_0_0value?: (() => void) | undefined
    public _onReachEnd_0_0value?: (() => void) | undefined
    public _onScrollStart_0_0value?: (() => void) | undefined
    public _onScrollStop_0_0value?: (() => void) | undefined
    public _flingSpeedLimit_0_0value?: double | undefined
    public _clipContent_0_0value?: ContentClipMode | RectShape | undefined
    public _digitalCrownSensitivity_0_0value?: CrownSensitivity | undefined
    public _backToTop_0_0value?: boolean | undefined
    public _fadingEdge_0_0value?: boolean | undefined
    public _fadingEdge_0_1value?: FadingEdgeOptions | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkGridPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
        this.applyModifierPatch1(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkGridPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setColumnsTemplateAttribute((this._columnsTemplate_0_0value as string | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setColumnsTemplateAttribute((undefined as string | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setRowsTemplateAttribute((this._rowsTemplate_0_0value as string | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setRowsTemplateAttribute((undefined as string | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setColumnsGapAttribute((this._columnsGap_0_0value as Length | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setColumnsGapAttribute((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setRowsGapAttribute((this._rowsGap_0_0value as Length | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setRowsGapAttribute((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setScrollBarWidthAttribute((this._scrollBarWidth_0_0value as double | string | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setScrollBarWidthAttribute((undefined as double | string | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setScrollBarColorAttribute((this._scrollBarColor_0_0value as arkui_component_enums_Color | int32 | string | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setScrollBarColorAttribute((undefined as arkui_component_enums_Color | int32 | string | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1: {
                    peer.setScrollBarAttribute((this._scrollBar_0_0value as BarState | undefined));
                    flagArray[6] = 2;
                    break;
                }
                case 3: {
                    flagArray[6] = 2;
                    break;
                }
                default: {
                    flagArray[6] = 0;
                    peer.setScrollBarAttribute((undefined as BarState | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1: {
                    peer.setOnScrollBarUpdateAttribute((this._onScrollBarUpdate_0_0value as ((index: int32,offset: double) => ComputedBarAttribute) | undefined));
                    flagArray[7] = 2;
                    break;
                }
                case 3: {
                    flagArray[7] = 2;
                    break;
                }
                default: {
                    flagArray[7] = 0;
                    peer.setOnScrollBarUpdateAttribute((undefined as ((index: int32,offset: double) => ComputedBarAttribute) | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1: {
                    peer.setOnScrollIndexAttribute((this._onScrollIndex_0_0value as ((first: int32,last: int32) => void) | undefined));
                    flagArray[8] = 2;
                    break;
                }
                case 3: {
                    flagArray[8] = 2;
                    break;
                }
                default: {
                    flagArray[8] = 0;
                    peer.setOnScrollIndexAttribute((undefined as ((first: int32,last: int32) => void) | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1: {
                    peer.setCachedCount0Attribute((this._cachedCount_0_0value as int32 | undefined));
                    flagArray[9] = 2;
                    break;
                }
                case 3: {
                    flagArray[9] = 2;
                    break;
                }
                default: {
                    flagArray[9] = 0;
                    peer.setCachedCount0Attribute((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1: {
                    peer.setEditModeAttribute((this._editMode_0_0value as boolean | undefined));
                    flagArray[10] = 2;
                    break;
                }
                case 3: {
                    flagArray[10] = 2;
                    break;
                }
                default: {
                    flagArray[10] = 0;
                    peer.setEditModeAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1: {
                    peer.setMultiSelectableAttribute((this._multiSelectable_0_0value as boolean | undefined));
                    flagArray[11] = 2;
                    break;
                }
                case 3: {
                    flagArray[11] = 2;
                    break;
                }
                default: {
                    flagArray[11] = 0;
                    peer.setMultiSelectableAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1: {
                    peer.setMaxCountAttribute((this._maxCount_0_0value as int32 | undefined));
                    flagArray[12] = 2;
                    break;
                }
                case 3: {
                    flagArray[12] = 2;
                    break;
                }
                default: {
                    flagArray[12] = 0;
                    peer.setMaxCountAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1: {
                    peer.setMinCountAttribute((this._minCount_0_0value as int32 | undefined));
                    flagArray[13] = 2;
                    break;
                }
                case 3: {
                    flagArray[13] = 2;
                    break;
                }
                default: {
                    flagArray[13] = 0;
                    peer.setMinCountAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[14] != 0) {
            switch (flagArray[14]) {
                case 1: {
                    peer.setCellLengthAttribute((this._cellLength_0_0value as double | undefined));
                    flagArray[14] = 2;
                    break;
                }
                case 3: {
                    flagArray[14] = 2;
                    break;
                }
                default: {
                    flagArray[14] = 0;
                    peer.setCellLengthAttribute((undefined as double | undefined));
                }
            }
        }
        if (flagArray[15] != 0) {
            switch (flagArray[15]) {
                case 1: {
                    peer.setLayoutDirectionAttribute((this._layoutDirection_0_0value as GridDirection | undefined));
                    flagArray[15] = 2;
                    break;
                }
                case 3: {
                    flagArray[15] = 2;
                    break;
                }
                default: {
                    flagArray[15] = 0;
                    peer.setLayoutDirectionAttribute((undefined as GridDirection | undefined));
                }
            }
        }
        if (flagArray[16] != 0) {
            switch (flagArray[16]) {
                case 1: {
                    peer.setSupportAnimationAttribute((this._supportAnimation_0_0value as boolean | undefined));
                    flagArray[16] = 2;
                    break;
                }
                case 3: {
                    flagArray[16] = 2;
                    break;
                }
                default: {
                    flagArray[16] = 0;
                    peer.setSupportAnimationAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[17] != 0) {
            switch (flagArray[17]) {
                case 1: {
                    peer.setOnItemDragStartAttribute((this._onItemDragStart_0_0value as OnItemDragStartCallback | undefined));
                    flagArray[17] = 2;
                    break;
                }
                case 3: {
                    flagArray[17] = 2;
                    break;
                }
                default: {
                    flagArray[17] = 0;
                    peer.setOnItemDragStartAttribute((undefined as OnItemDragStartCallback | undefined));
                }
            }
        }
        if (flagArray[18] != 0) {
            switch (flagArray[18]) {
                case 1: {
                    peer.setOnItemDragEnterAttribute((this._onItemDragEnter_0_0value as ((event: ItemDragInfo) => void) | undefined));
                    flagArray[18] = 2;
                    break;
                }
                case 3: {
                    flagArray[18] = 2;
                    break;
                }
                default: {
                    flagArray[18] = 0;
                    peer.setOnItemDragEnterAttribute((undefined as ((event: ItemDragInfo) => void) | undefined));
                }
            }
        }
        if (flagArray[19] != 0) {
            switch (flagArray[19]) {
                case 1: {
                    peer.setOnItemDragMoveAttribute((this._onItemDragMove_0_0value as ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32) => void) | undefined));
                    flagArray[19] = 2;
                    break;
                }
                case 3: {
                    flagArray[19] = 2;
                    break;
                }
                default: {
                    flagArray[19] = 0;
                    peer.setOnItemDragMoveAttribute((undefined as ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32) => void) | undefined));
                }
            }
        }
    }
    applyModifierPatch1(peer: ArkGridPeer, flagArray: Uint8Array): void {
        if (flagArray[20] != 0) {
            switch (flagArray[20]) {
                case 1: {
                    peer.setOnItemDragLeaveAttribute((this._onItemDragLeave_0_0value as ((event: ItemDragInfo,itemIndex: int32) => void) | undefined));
                    flagArray[20] = 2;
                    break;
                }
                case 3: {
                    flagArray[20] = 2;
                    break;
                }
                default: {
                    flagArray[20] = 0;
                    peer.setOnItemDragLeaveAttribute((undefined as ((event: ItemDragInfo,itemIndex: int32) => void) | undefined));
                }
            }
        }
        if (flagArray[21] != 0) {
            switch (flagArray[21]) {
                case 1: {
                    peer.setOnItemDropAttribute((this._onItemDrop_0_0value as ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32,isSuccess: boolean) => void) | undefined));
                    flagArray[21] = 2;
                    break;
                }
                case 3: {
                    flagArray[21] = 2;
                    break;
                }
                default: {
                    flagArray[21] = 0;
                    peer.setOnItemDropAttribute((undefined as ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32,isSuccess: boolean) => void) | undefined));
                }
            }
        }
        if (flagArray[22] != 0) {
            switch (flagArray[22]) {
                case 1: {
                    peer.setNestedScrollAttribute((this._nestedScroll_0_0value as NestedScrollOptions | undefined));
                    flagArray[22] = 2;
                    break;
                }
                case 3: {
                    flagArray[22] = 2;
                    break;
                }
                default: {
                    flagArray[22] = 0;
                    peer.setNestedScrollAttribute((undefined as NestedScrollOptions | undefined));
                }
            }
        }
        if (flagArray[23] != 0) {
            switch (flagArray[23]) {
                case 1: {
                    peer.setEnableScrollInteractionAttribute((this._enableScrollInteraction_0_0value as boolean | undefined));
                    flagArray[23] = 2;
                    break;
                }
                case 3: {
                    flagArray[23] = 2;
                    break;
                }
                default: {
                    flagArray[23] = 0;
                    peer.setEnableScrollInteractionAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[24] != 0) {
            switch (flagArray[24]) {
                case 1: {
                    peer.setFrictionAttribute((this._friction_0_0value as double | arkui_component_units_Resource | undefined));
                    flagArray[24] = 2;
                    break;
                }
                case 3: {
                    flagArray[24] = 2;
                    break;
                }
                default: {
                    flagArray[24] = 0;
                    peer.setFrictionAttribute((undefined as double | arkui_component_units_Resource | undefined));
                }
            }
        }
        if (flagArray[25] != 0) {
            switch (flagArray[25]) {
                case 1: {
                    peer.setAlignItemsAttribute((this._alignItems_0_0value as GridItemAlignment | undefined));
                    flagArray[25] = 2;
                    break;
                }
                case 3: {
                    flagArray[25] = 2;
                    break;
                }
                default: {
                    flagArray[25] = 0;
                    peer.setAlignItemsAttribute((undefined as GridItemAlignment | undefined));
                }
            }
        }
        if (flagArray[26] != 0) {
            switch (flagArray[26]) {
                case 1: {
                    peer.setOnScrollFrameBeginAttribute((this._onScrollFrameBegin_0_0value as OnScrollFrameBeginCallback | undefined));
                    flagArray[26] = 2;
                    break;
                }
                case 3: {
                    flagArray[26] = 2;
                    break;
                }
                default: {
                    flagArray[26] = 0;
                    peer.setOnScrollFrameBeginAttribute((undefined as OnScrollFrameBeginCallback | undefined));
                }
            }
        }
        if (flagArray[27] != 0) {
            switch (flagArray[27]) {
                case 1: {
                    peer.setOnWillScrollAttribute((this._onWillScroll_0_0value as OnWillScrollCallback | undefined));
                    flagArray[27] = 2;
                    break;
                }
                case 3: {
                    flagArray[27] = 2;
                    break;
                }
                default: {
                    flagArray[27] = 0;
                    peer.setOnWillScrollAttribute((undefined as OnWillScrollCallback | undefined));
                }
            }
        }
        if (flagArray[28] != 0) {
            switch (flagArray[28]) {
                case 1: {
                    peer.setOnDidScrollAttribute((this._onDidScroll_0_0value as OnScrollCallback | undefined));
                    flagArray[28] = 2;
                    break;
                }
                case 3: {
                    flagArray[28] = 2;
                    break;
                }
                default: {
                    flagArray[28] = 0;
                    peer.setOnDidScrollAttribute((undefined as OnScrollCallback | undefined));
                }
            }
        }
        if (flagArray[29] != 0) {
            switch (flagArray[29]) {
                case 1: {
                    peer.setCachedCount1Attribute((this._cachedCount_1_0value as int32 | undefined), (this._cachedCount_1_1value as boolean | undefined));
                    flagArray[29] = 2;
                    break;
                }
                case 3: {
                    flagArray[29] = 2;
                    break;
                }
                default: {
                    flagArray[29] = 0;
                    peer.setCachedCount1Attribute((undefined as int32 | undefined), (undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[30] != 0) {
            switch (flagArray[30]) {
                case 1: {
                    peer.setEdgeEffectAttribute((this._edgeEffect_0_0value as EdgeEffect | undefined), (this._edgeEffect_0_1value as EdgeEffectOptions | undefined));
                    flagArray[30] = 2;
                    break;
                }
                case 3: {
                    flagArray[30] = 2;
                    break;
                }
                default: {
                    flagArray[30] = 0;
                    peer.setEdgeEffectAttribute((undefined as EdgeEffect | undefined), (undefined as EdgeEffectOptions | undefined));
                }
            }
        }
        if (flagArray[31] != 0) {
            switch (flagArray[31]) {
                case 1: {
                    peer.setOnReachStartAttribute((this._onReachStart_0_0value as (() => void) | undefined));
                    flagArray[31] = 2;
                    break;
                }
                case 3: {
                    flagArray[31] = 2;
                    break;
                }
                default: {
                    flagArray[31] = 0;
                    peer.setOnReachStartAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[32] != 0) {
            switch (flagArray[32]) {
                case 1: {
                    peer.setOnReachEndAttribute((this._onReachEnd_0_0value as (() => void) | undefined));
                    flagArray[32] = 2;
                    break;
                }
                case 3: {
                    flagArray[32] = 2;
                    break;
                }
                default: {
                    flagArray[32] = 0;
                    peer.setOnReachEndAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[33] != 0) {
            switch (flagArray[33]) {
                case 1: {
                    peer.setOnScrollStartAttribute((this._onScrollStart_0_0value as (() => void) | undefined));
                    flagArray[33] = 2;
                    break;
                }
                case 3: {
                    flagArray[33] = 2;
                    break;
                }
                default: {
                    flagArray[33] = 0;
                    peer.setOnScrollStartAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[34] != 0) {
            switch (flagArray[34]) {
                case 1: {
                    peer.setOnScrollStopAttribute((this._onScrollStop_0_0value as (() => void) | undefined));
                    flagArray[34] = 2;
                    break;
                }
                case 3: {
                    flagArray[34] = 2;
                    break;
                }
                default: {
                    flagArray[34] = 0;
                    peer.setOnScrollStopAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[35] != 0) {
            switch (flagArray[35]) {
                case 1: {
                    peer.setFlingSpeedLimitAttribute((this._flingSpeedLimit_0_0value as double | undefined));
                    flagArray[35] = 2;
                    break;
                }
                case 3: {
                    flagArray[35] = 2;
                    break;
                }
                default: {
                    flagArray[35] = 0;
                    peer.setFlingSpeedLimitAttribute((undefined as double | undefined));
                }
            }
        }
        if (flagArray[36] != 0) {
            switch (flagArray[36]) {
                case 1: {
                    peer.setClipContentAttribute((this._clipContent_0_0value as ContentClipMode | RectShape | undefined));
                    flagArray[36] = 2;
                    break;
                }
                case 3: {
                    flagArray[36] = 2;
                    break;
                }
                default: {
                    flagArray[36] = 0;
                    peer.setClipContentAttribute((undefined as ContentClipMode | RectShape | undefined));
                }
            }
        }
        if (flagArray[37] != 0) {
            switch (flagArray[37]) {
                case 1: {
                    peer.setDigitalCrownSensitivityAttribute((this._digitalCrownSensitivity_0_0value as CrownSensitivity | undefined));
                    flagArray[37] = 2;
                    break;
                }
                case 3: {
                    flagArray[37] = 2;
                    break;
                }
                default: {
                    flagArray[37] = 0;
                    peer.setDigitalCrownSensitivityAttribute((undefined as CrownSensitivity | undefined));
                }
            }
        }
        if (flagArray[38] != 0) {
            switch (flagArray[38]) {
                case 1: {
                    peer.setBackToTopAttribute((this._backToTop_0_0value as boolean | undefined));
                    flagArray[38] = 2;
                    break;
                }
                case 3: {
                    flagArray[38] = 2;
                    break;
                }
                default: {
                    flagArray[38] = 0;
                    peer.setBackToTopAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[39] != 0) {
            switch (flagArray[39]) {
                case 1: {
                    peer.setFadingEdgeAttribute((this._fadingEdge_0_0value as boolean | undefined), (this._fadingEdge_0_1value as FadingEdgeOptions | undefined));
                    flagArray[39] = 2;
                    break;
                }
                case 3: {
                    flagArray[39] = 2;
                    break;
                }
                default: {
                    flagArray[39] = 0;
                    peer.setFadingEdgeAttribute((undefined as boolean | undefined), (undefined as FadingEdgeOptions | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: GridModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
        this.mergeModifier1(modifier, flagArray);
    }
    mergeModifier0(modifier: GridModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.columnsTemplate(modifier._columnsTemplate_0_0value);
                    break;
                }
                default: {
                    this.columnsTemplate((undefined as string | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.rowsTemplate(modifier._rowsTemplate_0_0value);
                    break;
                }
                default: {
                    this.rowsTemplate((undefined as string | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.columnsGap(modifier._columnsGap_0_0value);
                    break;
                }
                default: {
                    this.columnsGap((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.rowsGap(modifier._rowsGap_0_0value);
                    break;
                }
                default: {
                    this.rowsGap((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.scrollBarWidth(modifier._scrollBarWidth_0_0value);
                    break;
                }
                default: {
                    this.scrollBarWidth((undefined as double | string | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1:
                case 3: {
                    this.scrollBarColor(modifier._scrollBarColor_0_0value);
                    break;
                }
                default: {
                    this.scrollBarColor((undefined as arkui_component_enums_Color | int32 | string | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1:
                case 3: {
                    this.scrollBar(modifier._scrollBar_0_0value);
                    break;
                }
                default: {
                    this.scrollBar((undefined as BarState | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1:
                case 3: {
                    this.onScrollBarUpdate(modifier._onScrollBarUpdate_0_0value);
                    break;
                }
                default: {
                    this.onScrollBarUpdate((undefined as ((index: int32,offset: double) => ComputedBarAttribute) | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1:
                case 3: {
                    this.onScrollIndex(modifier._onScrollIndex_0_0value);
                    break;
                }
                default: {
                    this.onScrollIndex((undefined as ((first: int32,last: int32) => void) | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1:
                case 3: {
                    this.cachedCount(modifier._cachedCount_0_0value);
                    break;
                }
                default: {
                    this.cachedCount((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1:
                case 3: {
                    this.editMode(modifier._editMode_0_0value);
                    break;
                }
                default: {
                    this.editMode((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1:
                case 3: {
                    this.multiSelectable(modifier._multiSelectable_0_0value);
                    break;
                }
                default: {
                    this.multiSelectable((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1:
                case 3: {
                    this.maxCount(modifier._maxCount_0_0value);
                    break;
                }
                default: {
                    this.maxCount((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1:
                case 3: {
                    this.minCount(modifier._minCount_0_0value);
                    break;
                }
                default: {
                    this.minCount((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[14] != 0) {
            switch (flagArray[14]) {
                case 1:
                case 3: {
                    this.cellLength(modifier._cellLength_0_0value);
                    break;
                }
                default: {
                    this.cellLength((undefined as double | undefined));
                }
            }
        }
        if (flagArray[15] != 0) {
            switch (flagArray[15]) {
                case 1:
                case 3: {
                    this.layoutDirection(modifier._layoutDirection_0_0value);
                    break;
                }
                default: {
                    this.layoutDirection((undefined as GridDirection | undefined));
                }
            }
        }
        if (flagArray[16] != 0) {
            switch (flagArray[16]) {
                case 1:
                case 3: {
                    this.supportAnimation(modifier._supportAnimation_0_0value);
                    break;
                }
                default: {
                    this.supportAnimation((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[17] != 0) {
            switch (flagArray[17]) {
                case 1:
                case 3: {
                    this.onItemDragStart(modifier._onItemDragStart_0_0value);
                    break;
                }
                default: {
                    this.onItemDragStart((undefined as OnItemDragStartCallback | undefined));
                }
            }
        }
        if (flagArray[18] != 0) {
            switch (flagArray[18]) {
                case 1:
                case 3: {
                    this.onItemDragEnter(modifier._onItemDragEnter_0_0value);
                    break;
                }
                default: {
                    this.onItemDragEnter((undefined as ((event: ItemDragInfo) => void) | undefined));
                }
            }
        }
        if (flagArray[19] != 0) {
            switch (flagArray[19]) {
                case 1:
                case 3: {
                    this.onItemDragMove(modifier._onItemDragMove_0_0value);
                    break;
                }
                default: {
                    this.onItemDragMove((undefined as ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32) => void) | undefined));
                }
            }
        }
    }
    mergeModifier1(modifier: GridModifier, flagArray: Uint8Array): void {
        if (flagArray[20] != 0) {
            switch (flagArray[20]) {
                case 1:
                case 3: {
                    this.onItemDragLeave(modifier._onItemDragLeave_0_0value);
                    break;
                }
                default: {
                    this.onItemDragLeave((undefined as ((event: ItemDragInfo,itemIndex: int32) => void) | undefined));
                }
            }
        }
        if (flagArray[21] != 0) {
            switch (flagArray[21]) {
                case 1:
                case 3: {
                    this.onItemDrop(modifier._onItemDrop_0_0value);
                    break;
                }
                default: {
                    this.onItemDrop((undefined as ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32,isSuccess: boolean) => void) | undefined));
                }
            }
        }
        if (flagArray[22] != 0) {
            switch (flagArray[22]) {
                case 1:
                case 3: {
                    this.nestedScroll(modifier._nestedScroll_0_0value);
                    break;
                }
                default: {
                    this.nestedScroll((undefined as NestedScrollOptions | undefined));
                }
            }
        }
        if (flagArray[23] != 0) {
            switch (flagArray[23]) {
                case 1:
                case 3: {
                    this.enableScrollInteraction(modifier._enableScrollInteraction_0_0value);
                    break;
                }
                default: {
                    this.enableScrollInteraction((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[24] != 0) {
            switch (flagArray[24]) {
                case 1:
                case 3: {
                    this.friction(modifier._friction_0_0value);
                    break;
                }
                default: {
                    this.friction((undefined as double | arkui_component_units_Resource | undefined));
                }
            }
        }
        if (flagArray[25] != 0) {
            switch (flagArray[25]) {
                case 1:
                case 3: {
                    this.alignItems(modifier._alignItems_0_0value);
                    break;
                }
                default: {
                    this.alignItems((undefined as GridItemAlignment | undefined));
                }
            }
        }
        if (flagArray[26] != 0) {
            switch (flagArray[26]) {
                case 1:
                case 3: {
                    this.onScrollFrameBegin(modifier._onScrollFrameBegin_0_0value);
                    break;
                }
                default: {
                    this.onScrollFrameBegin((undefined as OnScrollFrameBeginCallback | undefined));
                }
            }
        }
        if (flagArray[27] != 0) {
            switch (flagArray[27]) {
                case 1:
                case 3: {
                    this.onWillScroll(modifier._onWillScroll_0_0value);
                    break;
                }
                default: {
                    this.onWillScroll((undefined as OnWillScrollCallback | undefined));
                }
            }
        }
        if (flagArray[28] != 0) {
            switch (flagArray[28]) {
                case 1:
                case 3: {
                    this.onDidScroll(modifier._onDidScroll_0_0value);
                    break;
                }
                default: {
                    this.onDidScroll((undefined as OnScrollCallback | undefined));
                }
            }
        }
        if (flagArray[29] != 0) {
            switch (flagArray[29]) {
                case 1:
                case 3: {
                    this.cachedCount(modifier._cachedCount_1_0value, modifier._cachedCount_1_1value);
                    break;
                }
                default: {
                    this.cachedCount((undefined as int32 | undefined), (undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[30] != 0) {
            switch (flagArray[30]) {
                case 1:
                case 3: {
                    this.edgeEffect(modifier._edgeEffect_0_0value, modifier._edgeEffect_0_1value);
                    break;
                }
                default: {
                    this.edgeEffect((undefined as EdgeEffect | undefined), (undefined as EdgeEffectOptions | undefined));
                }
            }
        }
        if (flagArray[31] != 0) {
            switch (flagArray[31]) {
                case 1:
                case 3: {
                    this.onReachStart(modifier._onReachStart_0_0value);
                    break;
                }
                default: {
                    this.onReachStart((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[32] != 0) {
            switch (flagArray[32]) {
                case 1:
                case 3: {
                    this.onReachEnd(modifier._onReachEnd_0_0value);
                    break;
                }
                default: {
                    this.onReachEnd((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[33] != 0) {
            switch (flagArray[33]) {
                case 1:
                case 3: {
                    this.onScrollStart(modifier._onScrollStart_0_0value);
                    break;
                }
                default: {
                    this.onScrollStart((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[34] != 0) {
            switch (flagArray[34]) {
                case 1:
                case 3: {
                    this.onScrollStop(modifier._onScrollStop_0_0value);
                    break;
                }
                default: {
                    this.onScrollStop((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[35] != 0) {
            switch (flagArray[35]) {
                case 1:
                case 3: {
                    this.flingSpeedLimit(modifier._flingSpeedLimit_0_0value);
                    break;
                }
                default: {
                    this.flingSpeedLimit((undefined as double | undefined));
                }
            }
        }
        if (flagArray[36] != 0) {
            switch (flagArray[36]) {
                case 1:
                case 3: {
                    this.clipContent(modifier._clipContent_0_0value);
                    break;
                }
                default: {
                    this.clipContent((undefined as ContentClipMode | RectShape | undefined));
                }
            }
        }
        if (flagArray[37] != 0) {
            switch (flagArray[37]) {
                case 1:
                case 3: {
                    this.digitalCrownSensitivity(modifier._digitalCrownSensitivity_0_0value);
                    break;
                }
                default: {
                    this.digitalCrownSensitivity((undefined as CrownSensitivity | undefined));
                }
            }
        }
        if (flagArray[38] != 0) {
            switch (flagArray[38]) {
                case 1:
                case 3: {
                    this.backToTop(modifier._backToTop_0_0value);
                    break;
                }
                default: {
                    this.backToTop((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[39] != 0) {
            switch (flagArray[39]) {
                case 1:
                case 3: {
                    this.fadingEdge(modifier._fadingEdge_0_0value, modifier._fadingEdge_0_1value);
                    break;
                }
                default: {
                    this.fadingEdge((undefined as boolean | undefined), (undefined as FadingEdgeOptions | undefined));
                }
            }
        }
    }
    columnsTemplate(value: string | undefined): this {
        if (((this._flagArray[0]) == (0)) || ((this._columnsTemplate_0_0value) !== (value))) {
            this._flagArray[0] = 1
            this._columnsTemplate_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    rowsTemplate(value: string | undefined): this {
        if (((this._flagArray[1]) == (0)) || ((this._rowsTemplate_0_0value) !== (value))) {
            this._flagArray[1] = 1
            this._rowsTemplate_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    columnsGap(value: Length | undefined): this {
        if (((this._flagArray[2]) == (0)) || (true)) {
            this._flagArray[2] = 1
            this._columnsGap_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    rowsGap(value: Length | undefined): this {
        if (((this._flagArray[3]) == (0)) || (true)) {
            this._flagArray[3] = 1
            this._rowsGap_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    scrollBarWidth(value: double | string | undefined): this {
        if (((this._flagArray[4]) == (0)) || ((this._scrollBarWidth_0_0value) !== (value))) {
            this._flagArray[4] = 1
            this._scrollBarWidth_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    scrollBarColor(value: arkui_component_enums_Color | int32 | string | undefined): this {
        if (((this._flagArray[5]) == (0)) || (true)) {
            this._flagArray[5] = 1
            this._scrollBarColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    scrollBar(value: BarState | undefined): this {
        if (((this._flagArray[6]) == (0)) || (true)) {
            this._flagArray[6] = 1
            this._scrollBar_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[6] = 3
        }
        return this
    }
    onScrollBarUpdate(value: ((index: int32,offset: double) => ComputedBarAttribute) | undefined): this {
        if (((this._flagArray[7]) == (0)) || (true)) {
            this._flagArray[7] = 1
            this._onScrollBarUpdate_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[7] = 3
        }
        return this
    }
    onScrollIndex(value: ((first: int32,last: int32) => void) | undefined): this {
        if (((this._flagArray[8]) == (0)) || (true)) {
            this._flagArray[8] = 1
            this._onScrollIndex_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[8] = 3
        }
        return this
    }
    cachedCount(value: int32 | undefined): this {
        if (((this._flagArray[9]) == (0)) || ((this._cachedCount_0_0value) !== (value))) {
            this._flagArray[9] = 1
            this._cachedCount_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[9] = 3
        }
        return this
    }
    editMode(value: boolean | undefined): this {
        if (((this._flagArray[10]) == (0)) || ((this._editMode_0_0value) !== (value))) {
            this._flagArray[10] = 1
            this._editMode_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[10] = 3
        }
        return this
    }
    multiSelectable(value: boolean | undefined): this {
        if (((this._flagArray[11]) == (0)) || ((this._multiSelectable_0_0value) !== (value))) {
            this._flagArray[11] = 1
            this._multiSelectable_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[11] = 3
        }
        return this
    }
    maxCount(value: int32 | undefined): this {
        if (((this._flagArray[12]) == (0)) || ((this._maxCount_0_0value) !== (value))) {
            this._flagArray[12] = 1
            this._maxCount_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[12] = 3
        }
        return this
    }
    minCount(value: int32 | undefined): this {
        if (((this._flagArray[13]) == (0)) || ((this._minCount_0_0value) !== (value))) {
            this._flagArray[13] = 1
            this._minCount_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[13] = 3
        }
        return this
    }
    cellLength(value: double | undefined): this {
        if (((this._flagArray[14]) == (0)) || ((this._cellLength_0_0value) !== (value))) {
            this._flagArray[14] = 1
            this._cellLength_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[14] = 3
        }
        return this
    }
    layoutDirection(value: GridDirection | undefined): this {
        if (((this._flagArray[15]) == (0)) || (true)) {
            this._flagArray[15] = 1
            this._layoutDirection_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[15] = 3
        }
        return this
    }
    supportAnimation(value: boolean | undefined): this {
        if (((this._flagArray[16]) == (0)) || ((this._supportAnimation_0_0value) !== (value))) {
            this._flagArray[16] = 1
            this._supportAnimation_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[16] = 3
        }
        return this
    }
    onItemDragStart(value: OnItemDragStartCallback | undefined): this {
        if (((this._flagArray[17]) == (0)) || (true)) {
            this._flagArray[17] = 1
            this._onItemDragStart_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[17] = 3
        }
        return this
    }
    onItemDragEnter(value: ((event: ItemDragInfo) => void) | undefined): this {
        if (((this._flagArray[18]) == (0)) || (true)) {
            this._flagArray[18] = 1
            this._onItemDragEnter_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[18] = 3
        }
        return this
    }
    onItemDragMove(value: ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32) => void) | undefined): this {
        if (((this._flagArray[19]) == (0)) || (true)) {
            this._flagArray[19] = 1
            this._onItemDragMove_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[19] = 3
        }
        return this
    }
    onItemDragLeave(value: ((event: ItemDragInfo,itemIndex: int32) => void) | undefined): this {
        if (((this._flagArray[20]) == (0)) || (true)) {
            this._flagArray[20] = 1
            this._onItemDragLeave_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[20] = 3
        }
        return this
    }
    onItemDrop(value: ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32,isSuccess: boolean) => void) | undefined): this {
        if (((this._flagArray[21]) == (0)) || (true)) {
            this._flagArray[21] = 1
            this._onItemDrop_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[21] = 3
        }
        return this
    }
    nestedScroll(value: NestedScrollOptions | undefined): this {
        if (((this._flagArray[22]) == (0)) || (true)) {
            this._flagArray[22] = 1
            this._nestedScroll_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[22] = 3
        }
        return this
    }
    enableScrollInteraction(value: boolean | undefined): this {
        if (((this._flagArray[23]) == (0)) || ((this._enableScrollInteraction_0_0value) !== (value))) {
            this._flagArray[23] = 1
            this._enableScrollInteraction_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[23] = 3
        }
        return this
    }
    friction(value: double | arkui_component_units_Resource | undefined): this {
        if (((this._flagArray[24]) == (0)) || (true)) {
            this._flagArray[24] = 1
            this._friction_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[24] = 3
        }
        return this
    }
    alignItems(value: GridItemAlignment | undefined): this {
        if (((this._flagArray[25]) == (0)) || (true)) {
            this._flagArray[25] = 1
            this._alignItems_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[25] = 3
        }
        return this
    }
    onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        if (((this._flagArray[26]) == (0)) || (true)) {
            this._flagArray[26] = 1
            this._onScrollFrameBegin_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[26] = 3
        }
        return this
    }
    onWillScroll(value: OnWillScrollCallback | undefined): this {
        if (((this._flagArray[27]) == (0)) || (true)) {
            this._flagArray[27] = 1
            this._onWillScroll_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[27] = 3
        }
        return this
    }
    onDidScroll(value: OnScrollCallback | undefined): this {
        if (((this._flagArray[28]) == (0)) || (true)) {
            this._flagArray[28] = 1
            this._onDidScroll_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[28] = 3
        }
        return this
    }
    cachedCount(count: int32 | undefined, show: boolean | undefined): this {
        if (((this._flagArray[29]) == (0)) || ((this._cachedCount_1_0value) !== (count)) || ((this._cachedCount_1_1value) !== (show))) {
            this._flagArray[29] = 1
            this._cachedCount_1_0value = count
            this._cachedCount_1_1value = show
            this._state.fireChange()
        } else {
            this._flagArray[29] = 3
        }
        return this
    }
    edgeEffect(value: EdgeEffect | undefined, options?: EdgeEffectOptions): this {
        if (((this._flagArray[30]) == (0)) || (true) || (true)) {
            this._flagArray[30] = 1
            this._edgeEffect_0_0value = value
            this._edgeEffect_0_1value = options
            this._state.fireChange()
        } else {
            this._flagArray[30] = 3
        }
        return this
    }
    onReachStart(value: (() => void) | undefined): this {
        if (((this._flagArray[31]) == (0)) || (true)) {
            this._flagArray[31] = 1
            this._onReachStart_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[31] = 3
        }
        return this
    }
    onReachEnd(value: (() => void) | undefined): this {
        if (((this._flagArray[32]) == (0)) || (true)) {
            this._flagArray[32] = 1
            this._onReachEnd_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[32] = 3
        }
        return this
    }
    onScrollStart(value: (() => void) | undefined): this {
        if (((this._flagArray[33]) == (0)) || (true)) {
            this._flagArray[33] = 1
            this._onScrollStart_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[33] = 3
        }
        return this
    }
    onScrollStop(value: (() => void) | undefined): this {
        if (((this._flagArray[34]) == (0)) || (true)) {
            this._flagArray[34] = 1
            this._onScrollStop_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[34] = 3
        }
        return this
    }
    flingSpeedLimit(value: double | undefined): this {
        if (((this._flagArray[35]) == (0)) || ((this._flingSpeedLimit_0_0value) !== (value))) {
            this._flagArray[35] = 1
            this._flingSpeedLimit_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[35] = 3
        }
        return this
    }
    clipContent(value: ContentClipMode | RectShape | undefined): this {
        if (((this._flagArray[36]) == (0)) || (true)) {
            this._flagArray[36] = 1
            this._clipContent_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[36] = 3
        }
        return this
    }
    digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        if (((this._flagArray[37]) == (0)) || (true)) {
            this._flagArray[37] = 1
            this._digitalCrownSensitivity_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[37] = 3
        }
        return this
    }
    backToTop(value: boolean | undefined): this {
        if (((this._flagArray[38]) == (0)) || ((this._backToTop_0_0value) !== (value))) {
            this._flagArray[38] = 1
            this._backToTop_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[38] = 3
        }
        return this
    }
    fadingEdge(enabled: boolean | undefined, options?: FadingEdgeOptions): this {
        if (((this._flagArray[39]) == (0)) || ((this._fadingEdge_0_0value) !== (enabled)) || (true)) {
            this._flagArray[39] = 1
            this._fadingEdge_0_0value = enabled
            this._fadingEdge_0_1value = options
            this._state.fireChange()
        } else {
            this._flagArray[39] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<GridAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

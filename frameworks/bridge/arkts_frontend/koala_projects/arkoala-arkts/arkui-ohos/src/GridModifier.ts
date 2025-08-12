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

// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { ScrollableCommonMethodModifier } from './ScrollableCommonMethodModifier';
import { AttributeUpdaterFlag, CommonMethodModifier } from './CommonMethodModifier';
import { ArkGridPeer, ComputedBarAttribute, GridDirection, GridItemAlignment, GridAttribute } from './component/grid';
import { CustomBuilder, ItemDragInfo, OnWillScrollCallback, OnScrollCallback, AttributeModifier } from './component/common';
import { Length } from './component/units';
import { OnScrollFrameBeginCallback } from './component/scroll';
export class GridModifier extends ScrollableCommonMethodModifier implements GridAttribute, AttributeModifier<GridAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId;
    }
    isUpdater: () => boolean = () => false;
    applyNormalAttribute(instance: GridAttribute): void {}
    applyPressedAttribute(instance: GridAttribute): void {}
    applyFocusedAttribute(instance: GridAttribute): void {}
    applyDisabledAttribute(instance: GridAttribute): void {}
    applySelectedAttribute(instance: GridAttribute): void {}
    _columnsTemplate_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _columnsTemplate_0_0value?: string | undefined;
    _rowsTemplate_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _rowsTemplate_0_0value?: string | undefined;
    _columnsGap_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _columnsGap_0_0value?: Length | undefined;
    _rowsGap_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _rowsGap_0_0value?: Length | undefined;
    _onScrollBarUpdate_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _onScrollBarUpdate_0_0value?: ((index: number, offset: number) => ComputedBarAttribute) | undefined;
    _onScrollIndex_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _onScrollIndex_0_0value?: ((first: number, last: number) => void) | undefined;
    _cachedCount_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _cachedCount_0_0value?: number | undefined;
    _editMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _editMode_0_0value?: boolean | undefined;
    _multiSelectable_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _multiSelectable_0_0value?: boolean | undefined;
    _maxCount_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _maxCount_0_0value?: number | undefined;
    _minCount_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _minCount_0_0value?: number | undefined;
    _cellLength_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _cellLength_0_0value?: number | undefined;
    _layoutDirection_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _layoutDirection_0_0value?: GridDirection | undefined;
    _supportAnimation_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _supportAnimation_0_0value?: boolean | undefined;
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
    _alignItems_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _alignItems_0_0value?: GridItemAlignment | undefined;
    _onScrollFrameBegin_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _onScrollFrameBegin_0_0value?: OnScrollFrameBeginCallback | undefined;
    _onWillScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _onWillScroll_0_0value?: OnWillScrollCallback | undefined;
    _onDidScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _onDidScroll_0_0value?: OnScrollCallback | undefined;
    _cachedCount_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL;
    _cachedCount_1_0value?: number | undefined;
    _cachedCount_1_1value?: boolean | undefined;
    applyModifierPatch(peer: ArkGridPeer): void {
        super.applyModifierPatch(peer);
        if (this._columnsTemplate_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._columnsTemplate_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.columnsTemplateAttribute(this._columnsTemplate_0_0value as string | undefined);
                    this._columnsTemplate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._columnsTemplate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._columnsTemplate_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.columnsTemplateAttribute(undefined as string | undefined);
                }
            }
        }
        if (this._rowsTemplate_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._rowsTemplate_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.rowsTemplateAttribute(this._rowsTemplate_0_0value as string | undefined);
                    this._rowsTemplate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._rowsTemplate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._rowsTemplate_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.rowsTemplateAttribute(undefined as string | undefined);
                }
            }
        }
        if (this._columnsGap_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._columnsGap_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.columnsGapAttribute(this._columnsGap_0_0value as Length | undefined);
                    this._columnsGap_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._columnsGap_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._columnsGap_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.columnsGapAttribute(undefined as Length | undefined);
                }
            }
        }
        if (this._rowsGap_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._rowsGap_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.rowsGapAttribute(this._rowsGap_0_0value as Length | undefined);
                    this._rowsGap_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._rowsGap_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._rowsGap_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.rowsGapAttribute(undefined as Length | undefined);
                }
            }
        }
        if (this._onScrollBarUpdate_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onScrollBarUpdate_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onScrollBarUpdateAttribute(
                        this._onScrollBarUpdate_0_0value as ((index: number, offset: number) => ComputedBarAttribute) | undefined
                    );
                    this._onScrollBarUpdate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScrollBarUpdate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScrollBarUpdate_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onScrollBarUpdateAttribute(undefined as ((index: number, offset: number) => ComputedBarAttribute) | undefined);
                }
            }
        }
        if (this._onScrollIndex_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onScrollIndex_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onScrollIndexAttribute(this._onScrollIndex_0_0value as ((first: number, last: number) => void) | undefined);
                    this._onScrollIndex_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onScrollIndex_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onScrollIndex_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onScrollIndexAttribute(undefined as ((first: number, last: number) => void) | undefined);
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
        if (this._editMode_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._editMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.editModeAttribute(this._editMode_0_0value as boolean | undefined);
                    this._editMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._editMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._editMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.editModeAttribute(undefined as boolean | undefined);
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
        if (this._maxCount_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._maxCount_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.maxCountAttribute(this._maxCount_0_0value as number | undefined);
                    this._maxCount_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maxCount_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._maxCount_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.maxCountAttribute(undefined as number | undefined);
                }
            }
        }
        if (this._minCount_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._minCount_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.minCountAttribute(this._minCount_0_0value as number | undefined);
                    this._minCount_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minCount_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._minCount_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.minCountAttribute(undefined as number | undefined);
                }
            }
        }
        if (this._cellLength_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._cellLength_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.cellLengthAttribute(this._cellLength_0_0value as number | undefined);
                    this._cellLength_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._cellLength_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._cellLength_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.cellLengthAttribute(undefined as number | undefined);
                }
            }
        }
        if (this._layoutDirection_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._layoutDirection_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.layoutDirectionAttribute(this._layoutDirection_0_0value as GridDirection | undefined);
                    this._layoutDirection_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._layoutDirection_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._layoutDirection_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.layoutDirectionAttribute(undefined as GridDirection | undefined);
                }
            }
        }
        if (this._supportAnimation_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._supportAnimation_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.supportAnimationAttribute(this._supportAnimation_0_0value as boolean | undefined);
                    this._supportAnimation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._supportAnimation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._supportAnimation_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.supportAnimationAttribute(undefined as boolean | undefined);
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
        if (this._alignItems_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._alignItems_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.alignItemsAttribute(this._alignItems_0_0value as GridItemAlignment | undefined);
                    this._alignItems_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._alignItems_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._alignItems_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.alignItemsAttribute(undefined as GridItemAlignment | undefined);
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
    mergeModifier(modifier: GridModifier): void {
        super.mergeModifier(modifier);
        if (modifier._columnsTemplate_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._columnsTemplate_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.columnsTemplate(modifier._columnsTemplate_0_0value);
                    break;
                }
                default: {
                    this.columnsTemplate(undefined as string | undefined);
                }
            }
        }
        if (modifier._rowsTemplate_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._rowsTemplate_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.rowsTemplate(modifier._rowsTemplate_0_0value);
                    break;
                }
                default: {
                    this.rowsTemplate(undefined as string | undefined);
                }
            }
        }
        if (modifier._columnsGap_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._columnsGap_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.columnsGap(modifier._columnsGap_0_0value);
                    break;
                }
                default: {
                    this.columnsGap(undefined as Length | undefined);
                }
            }
        }
        if (modifier._rowsGap_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._rowsGap_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.rowsGap(modifier._rowsGap_0_0value);
                    break;
                }
                default: {
                    this.rowsGap(undefined as Length | undefined);
                }
            }
        }
        if (modifier._onScrollBarUpdate_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onScrollBarUpdate_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onScrollBarUpdate(modifier._onScrollBarUpdate_0_0value);
                    break;
                }
                default: {
                    this.onScrollBarUpdate(undefined as ((index: number, offset: number) => ComputedBarAttribute) | undefined);
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
                    this.onScrollIndex(undefined as ((first: number, last: number) => void) | undefined);
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
        if (modifier._editMode_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._editMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.editMode(modifier._editMode_0_0value);
                    break;
                }
                default: {
                    this.editMode(undefined as boolean | undefined);
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
        if (modifier._maxCount_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._maxCount_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.maxCount(modifier._maxCount_0_0value);
                    break;
                }
                default: {
                    this.maxCount(undefined as number | undefined);
                }
            }
        }
        if (modifier._minCount_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._minCount_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.minCount(modifier._minCount_0_0value);
                    break;
                }
                default: {
                    this.minCount(undefined as number | undefined);
                }
            }
        }
        if (modifier._cellLength_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._cellLength_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.cellLength(modifier._cellLength_0_0value);
                    break;
                }
                default: {
                    this.cellLength(undefined as number | undefined);
                }
            }
        }
        if (modifier._layoutDirection_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._layoutDirection_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.layoutDirection(modifier._layoutDirection_0_0value);
                    break;
                }
                default: {
                    this.layoutDirection(undefined as GridDirection | undefined);
                }
            }
        }
        if (modifier._supportAnimation_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._supportAnimation_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.supportAnimation(modifier._supportAnimation_0_0value);
                    break;
                }
                default: {
                    this.supportAnimation(undefined as boolean | undefined);
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
        if (modifier._alignItems_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._alignItems_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.alignItems(modifier._alignItems_0_0value);
                    break;
                }
                default: {
                    this.alignItems(undefined as GridItemAlignment | undefined);
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
    columnsTemplate(value: string | undefined): this {
        if (this._columnsTemplate_0_flag == AttributeUpdaterFlag.INITIAL || this._columnsTemplate_0_0value !== value) {
            this._columnsTemplate_0_flag = AttributeUpdaterFlag.UPDATE;
            this._columnsTemplate_0_0value = value;
        } else {
            this._columnsTemplate_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    rowsTemplate(value: string | undefined): this {
        if (this._rowsTemplate_0_flag == AttributeUpdaterFlag.INITIAL || this._rowsTemplate_0_0value !== value) {
            this._rowsTemplate_0_flag = AttributeUpdaterFlag.UPDATE;
            this._rowsTemplate_0_0value = value;
        } else {
            this._rowsTemplate_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    columnsGap(value: Length | undefined): this {
        if (this._columnsGap_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._columnsGap_0_flag = AttributeUpdaterFlag.UPDATE;
            this._columnsGap_0_0value = value;
        } else {
            this._columnsGap_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    rowsGap(value: Length | undefined): this {
        if (this._rowsGap_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._rowsGap_0_flag = AttributeUpdaterFlag.UPDATE;
            this._rowsGap_0_0value = value;
        } else {
            this._rowsGap_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    onScrollBarUpdate(value: ((index: number, offset: number) => ComputedBarAttribute) | undefined): this {
        if (this._onScrollBarUpdate_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._onScrollBarUpdate_0_flag = AttributeUpdaterFlag.UPDATE;
            this._onScrollBarUpdate_0_0value = value;
        } else {
            this._onScrollBarUpdate_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    onScrollIndex(value: ((first: number, last: number) => void) | undefined): this {
        if (this._onScrollIndex_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._onScrollIndex_0_flag = AttributeUpdaterFlag.UPDATE;
            this._onScrollIndex_0_0value = value;
        } else {
            this._onScrollIndex_0_flag = AttributeUpdaterFlag.SKIP;
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
    editMode(value: boolean | undefined): this {
        if (this._editMode_0_flag == AttributeUpdaterFlag.INITIAL || this._editMode_0_0value !== value) {
            this._editMode_0_flag = AttributeUpdaterFlag.UPDATE;
            this._editMode_0_0value = value;
        } else {
            this._editMode_0_flag = AttributeUpdaterFlag.SKIP;
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
    maxCount(value: number | undefined): this {
        if (this._maxCount_0_flag == AttributeUpdaterFlag.INITIAL || this._maxCount_0_0value !== value) {
            this._maxCount_0_flag = AttributeUpdaterFlag.UPDATE;
            this._maxCount_0_0value = value;
        } else {
            this._maxCount_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    minCount(value: number | undefined): this {
        if (this._minCount_0_flag == AttributeUpdaterFlag.INITIAL || this._minCount_0_0value !== value) {
            this._minCount_0_flag = AttributeUpdaterFlag.UPDATE;
            this._minCount_0_0value = value;
        } else {
            this._minCount_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    cellLength(value: number | undefined): this {
        if (this._cellLength_0_flag == AttributeUpdaterFlag.INITIAL || this._cellLength_0_0value !== value) {
            this._cellLength_0_flag = AttributeUpdaterFlag.UPDATE;
            this._cellLength_0_0value = value;
        } else {
            this._cellLength_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    layoutDirection(value: GridDirection | undefined): this {
        if (this._layoutDirection_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._layoutDirection_0_flag = AttributeUpdaterFlag.UPDATE;
            this._layoutDirection_0_0value = value;
        } else {
            this._layoutDirection_0_flag = AttributeUpdaterFlag.SKIP;
        }
        return this;
    }
    supportAnimation(value: boolean | undefined): this {
        if (this._supportAnimation_0_flag == AttributeUpdaterFlag.INITIAL || this._supportAnimation_0_0value !== value) {
            this._supportAnimation_0_flag = AttributeUpdaterFlag.UPDATE;
            this._supportAnimation_0_0value = value;
        } else {
            this._supportAnimation_0_flag = AttributeUpdaterFlag.SKIP;
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
    alignItems(value: GridItemAlignment | undefined): this {
        if (this._alignItems_0_flag == AttributeUpdaterFlag.INITIAL || true) {
            this._alignItems_0_flag = AttributeUpdaterFlag.UPDATE;
            this._alignItems_0_0value = value;
        } else {
            this._alignItems_0_flag = AttributeUpdaterFlag.SKIP;
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

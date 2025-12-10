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

import { CommonMethodModifier } from './CommonMethodModifier'
import { AttributeModifier } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkAlphabetIndexerPeer, OnAlphabetIndexerSelectCallback, OnAlphabetIndexerRequestPopupDataCallback, OnAlphabetIndexerPopupSelectCallback, AlphabetIndexerAttribute, IndexerAlign } from './component/alphabetIndexer'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod, Bindable, BlurStyle } from './component/common'
import { ResourceColor, Resource as arkui_component_units_Resource, Font as arkui_component_units_Font, Position, Length } from './component/units'
import { Color as arkui_component_enums_Color } from './component/enums'
import { Resource as global_resource_Resource } from 'global.resource'
export class AlphabetIndexerModifier extends CommonMethodModifier implements AlphabetIndexerAttribute,AttributeModifier<AlphabetIndexerAttribute> {
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
    applyNormalAttribute(instance: AlphabetIndexerAttribute): void { }
    applyPressedAttribute(instance: AlphabetIndexerAttribute): void { }
    applyFocusedAttribute(instance: AlphabetIndexerAttribute): void { }
    applyDisabledAttribute(instance: AlphabetIndexerAttribute): void { }
    applySelectedAttribute(instance: AlphabetIndexerAttribute): void { }
    public _color_0_0value?: ResourceColor | undefined
    public _selectedColor_0_0value?: ResourceColor | undefined
    public _popupColor_0_0value?: ResourceColor | undefined
    public _selectedBackgroundColor_0_0value?: ResourceColor | undefined
    public _popupBackground_0_0value?: ResourceColor | undefined
    public _popupSelectedColor_0_0value?: ResourceColor | undefined
    public _popupUnselectedColor_0_0value?: ResourceColor | undefined
    public _popupItemBackgroundColor_0_0value?: ResourceColor | undefined
    public _usingPopup_0_0value?: boolean | undefined
    public _selectedFont_0_0value?: arkui_component_units_Font | undefined
    public _popupFont_0_0value?: arkui_component_units_Font | undefined
    public _popupItemFont_0_0value?: arkui_component_units_Font | undefined
    public _itemSize_0_0value?: string | double | undefined
    public _font_0_0value?: arkui_component_units_Font | undefined
    public _onSelect_0_0value?: OnAlphabetIndexerSelectCallback | undefined
    public _onRequestPopupData_0_0value?: OnAlphabetIndexerRequestPopupDataCallback | undefined
    public _onPopupSelect_0_0value?: OnAlphabetIndexerPopupSelectCallback | undefined
    public _selected_0_0value?: int32 | Bindable<int32> | undefined
    public _popupPosition_0_0value?: Position | undefined
    public _autoCollapse_0_0value?: boolean | undefined
    public _popupItemBorderRadius_0_0value?: double | undefined
    public _itemBorderRadius_0_0value?: double | undefined
    public _popupBackgroundBlurStyle_0_0value?: BlurStyle | undefined
    public _popupTitleBackground_0_0value?: ResourceColor | undefined
    public _enableHapticFeedback_0_0value?: boolean | undefined
    public _alignStyle_0_0value?: IndexerAlign | undefined
    public _alignStyle_0_1value?: Length | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkAlphabetIndexerPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
        this.applyModifierPatch1(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkAlphabetIndexerPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setColorAttribute((this._color_0_0value as ResourceColor | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setSelectedColorAttribute((this._selectedColor_0_0value as ResourceColor | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setSelectedColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setPopupColorAttribute((this._popupColor_0_0value as ResourceColor | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setPopupColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setSelectedBackgroundColorAttribute((this._selectedBackgroundColor_0_0value as ResourceColor | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setSelectedBackgroundColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setPopupBackgroundAttribute((this._popupBackground_0_0value as ResourceColor | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setPopupBackgroundAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setPopupSelectedColorAttribute((this._popupSelectedColor_0_0value as ResourceColor | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setPopupSelectedColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1: {
                    peer.setPopupUnselectedColorAttribute((this._popupUnselectedColor_0_0value as ResourceColor | undefined));
                    flagArray[6] = 2;
                    break;
                }
                case 3: {
                    flagArray[6] = 2;
                    break;
                }
                default: {
                    flagArray[6] = 0;
                    peer.setPopupUnselectedColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1: {
                    peer.setPopupItemBackgroundColorAttribute((this._popupItemBackgroundColor_0_0value as ResourceColor | undefined));
                    flagArray[7] = 2;
                    break;
                }
                case 3: {
                    flagArray[7] = 2;
                    break;
                }
                default: {
                    flagArray[7] = 0;
                    peer.setPopupItemBackgroundColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1: {
                    peer.setUsingPopupAttribute((this._usingPopup_0_0value as boolean | undefined));
                    flagArray[8] = 2;
                    break;
                }
                case 3: {
                    flagArray[8] = 2;
                    break;
                }
                default: {
                    flagArray[8] = 0;
                    peer.setUsingPopupAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1: {
                    peer.setSelectedFontAttribute((this._selectedFont_0_0value as arkui_component_units_Font | undefined));
                    flagArray[9] = 2;
                    break;
                }
                case 3: {
                    flagArray[9] = 2;
                    break;
                }
                default: {
                    flagArray[9] = 0;
                    peer.setSelectedFontAttribute((undefined as arkui_component_units_Font | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1: {
                    peer.setPopupFontAttribute((this._popupFont_0_0value as arkui_component_units_Font | undefined));
                    flagArray[10] = 2;
                    break;
                }
                case 3: {
                    flagArray[10] = 2;
                    break;
                }
                default: {
                    flagArray[10] = 0;
                    peer.setPopupFontAttribute((undefined as arkui_component_units_Font | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1: {
                    peer.setPopupItemFontAttribute((this._popupItemFont_0_0value as arkui_component_units_Font | undefined));
                    flagArray[11] = 2;
                    break;
                }
                case 3: {
                    flagArray[11] = 2;
                    break;
                }
                default: {
                    flagArray[11] = 0;
                    peer.setPopupItemFontAttribute((undefined as arkui_component_units_Font | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1: {
                    peer.setItemSizeAttribute((this._itemSize_0_0value as string | double | undefined));
                    flagArray[12] = 2;
                    break;
                }
                case 3: {
                    flagArray[12] = 2;
                    break;
                }
                default: {
                    flagArray[12] = 0;
                    peer.setItemSizeAttribute((undefined as string | double | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1: {
                    peer.setFontAttribute((this._font_0_0value as arkui_component_units_Font | undefined));
                    flagArray[13] = 2;
                    break;
                }
                case 3: {
                    flagArray[13] = 2;
                    break;
                }
                default: {
                    flagArray[13] = 0;
                    peer.setFontAttribute((undefined as arkui_component_units_Font | undefined));
                }
            }
        }
        if (flagArray[14] != 0) {
            switch (flagArray[14]) {
                case 1: {
                    peer.setOnSelectAttribute((this._onSelect_0_0value as OnAlphabetIndexerSelectCallback | undefined));
                    flagArray[14] = 2;
                    break;
                }
                case 3: {
                    flagArray[14] = 2;
                    break;
                }
                default: {
                    flagArray[14] = 0;
                    peer.setOnSelectAttribute((undefined as OnAlphabetIndexerSelectCallback | undefined));
                }
            }
        }
        if (flagArray[15] != 0) {
            switch (flagArray[15]) {
                case 1: {
                    peer.setOnRequestPopupDataAttribute((this._onRequestPopupData_0_0value as OnAlphabetIndexerRequestPopupDataCallback | undefined));
                    flagArray[15] = 2;
                    break;
                }
                case 3: {
                    flagArray[15] = 2;
                    break;
                }
                default: {
                    flagArray[15] = 0;
                    peer.setOnRequestPopupDataAttribute((undefined as OnAlphabetIndexerRequestPopupDataCallback | undefined));
                }
            }
        }
        if (flagArray[16] != 0) {
            switch (flagArray[16]) {
                case 1: {
                    peer.setOnPopupSelectAttribute((this._onPopupSelect_0_0value as OnAlphabetIndexerPopupSelectCallback | undefined));
                    flagArray[16] = 2;
                    break;
                }
                case 3: {
                    flagArray[16] = 2;
                    break;
                }
                default: {
                    flagArray[16] = 0;
                    peer.setOnPopupSelectAttribute((undefined as OnAlphabetIndexerPopupSelectCallback | undefined));
                }
            }
        }
        if (flagArray[17] != 0) {
            switch (flagArray[17]) {
                case 1: {
                    peer.setSelectedAttribute((this._selected_0_0value as int32 | Bindable<int32> | undefined));
                    flagArray[17] = 2;
                    break;
                }
                case 3: {
                    flagArray[17] = 2;
                    break;
                }
                default: {
                    flagArray[17] = 0;
                    peer.setSelectedAttribute((undefined as int32 | Bindable<int32> | undefined));
                }
            }
        }
        if (flagArray[18] != 0) {
            switch (flagArray[18]) {
                case 1: {
                    peer.setPopupPositionAttribute((this._popupPosition_0_0value as Position | undefined));
                    flagArray[18] = 2;
                    break;
                }
                case 3: {
                    flagArray[18] = 2;
                    break;
                }
                default: {
                    flagArray[18] = 0;
                    peer.setPopupPositionAttribute((undefined as Position | undefined));
                }
            }
        }
        if (flagArray[19] != 0) {
            switch (flagArray[19]) {
                case 1: {
                    peer.setAutoCollapseAttribute((this._autoCollapse_0_0value as boolean | undefined));
                    flagArray[19] = 2;
                    break;
                }
                case 3: {
                    flagArray[19] = 2;
                    break;
                }
                default: {
                    flagArray[19] = 0;
                    peer.setAutoCollapseAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    applyModifierPatch1(peer: ArkAlphabetIndexerPeer, flagArray: Uint8Array): void {
        if (flagArray[20] != 0) {
            switch (flagArray[20]) {
                case 1: {
                    peer.setPopupItemBorderRadiusAttribute((this._popupItemBorderRadius_0_0value as double | undefined));
                    flagArray[20] = 2;
                    break;
                }
                case 3: {
                    flagArray[20] = 2;
                    break;
                }
                default: {
                    flagArray[20] = 0;
                    peer.setPopupItemBorderRadiusAttribute((undefined as double | undefined));
                }
            }
        }
        if (flagArray[21] != 0) {
            switch (flagArray[21]) {
                case 1: {
                    peer.setItemBorderRadiusAttribute((this._itemBorderRadius_0_0value as double | undefined));
                    flagArray[21] = 2;
                    break;
                }
                case 3: {
                    flagArray[21] = 2;
                    break;
                }
                default: {
                    flagArray[21] = 0;
                    peer.setItemBorderRadiusAttribute((undefined as double | undefined));
                }
            }
        }
        if (flagArray[22] != 0) {
            switch (flagArray[22]) {
                case 1: {
                    peer.setPopupBackgroundBlurStyleAttribute((this._popupBackgroundBlurStyle_0_0value as BlurStyle | undefined));
                    flagArray[22] = 2;
                    break;
                }
                case 3: {
                    flagArray[22] = 2;
                    break;
                }
                default: {
                    flagArray[22] = 0;
                    peer.setPopupBackgroundBlurStyleAttribute((undefined as BlurStyle | undefined));
                }
            }
        }
        if (flagArray[23] != 0) {
            switch (flagArray[23]) {
                case 1: {
                    peer.setPopupTitleBackgroundAttribute((this._popupTitleBackground_0_0value as ResourceColor | undefined));
                    flagArray[23] = 2;
                    break;
                }
                case 3: {
                    flagArray[23] = 2;
                    break;
                }
                default: {
                    flagArray[23] = 0;
                    peer.setPopupTitleBackgroundAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[24] != 0) {
            switch (flagArray[24]) {
                case 1: {
                    peer.setEnableHapticFeedbackAttribute((this._enableHapticFeedback_0_0value as boolean | undefined));
                    flagArray[24] = 2;
                    break;
                }
                case 3: {
                    flagArray[24] = 2;
                    break;
                }
                default: {
                    flagArray[24] = 0;
                    peer.setEnableHapticFeedbackAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[25] != 0) {
            switch (flagArray[25]) {
                case 1: {
                    peer.setAlignStyleAttribute((this._alignStyle_0_0value as IndexerAlign | undefined), (this._alignStyle_0_1value as Length | undefined | undefined));
                    flagArray[25] = 2;
                    break;
                }
                case 3: {
                    flagArray[25] = 2;
                    break;
                }
                default: {
                    flagArray[25] = 0;
                    peer.setAlignStyleAttribute((undefined as IndexerAlign | undefined), (undefined as Length | undefined | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: AlphabetIndexerModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
        this.mergeModifier1(modifier, flagArray);
    }
    mergeModifier0(modifier: AlphabetIndexerModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.color(modifier._color_0_0value);
                    break;
                }
                default: {
                    this.color((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.selectedColor(modifier._selectedColor_0_0value);
                    break;
                }
                default: {
                    this.selectedColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.popupColor(modifier._popupColor_0_0value);
                    break;
                }
                default: {
                    this.popupColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.selectedBackgroundColor(modifier._selectedBackgroundColor_0_0value);
                    break;
                }
                default: {
                    this.selectedBackgroundColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.popupBackground(modifier._popupBackground_0_0value);
                    break;
                }
                default: {
                    this.popupBackground((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1:
                case 3: {
                    this.popupSelectedColor(modifier._popupSelectedColor_0_0value);
                    break;
                }
                default: {
                    this.popupSelectedColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1:
                case 3: {
                    this.popupUnselectedColor(modifier._popupUnselectedColor_0_0value);
                    break;
                }
                default: {
                    this.popupUnselectedColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1:
                case 3: {
                    this.popupItemBackgroundColor(modifier._popupItemBackgroundColor_0_0value);
                    break;
                }
                default: {
                    this.popupItemBackgroundColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1:
                case 3: {
                    this.usingPopup(modifier._usingPopup_0_0value);
                    break;
                }
                default: {
                    this.usingPopup((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1:
                case 3: {
                    this.selectedFont(modifier._selectedFont_0_0value);
                    break;
                }
                default: {
                    this.selectedFont((undefined as arkui_component_units_Font | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1:
                case 3: {
                    this.popupFont(modifier._popupFont_0_0value);
                    break;
                }
                default: {
                    this.popupFont((undefined as arkui_component_units_Font | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1:
                case 3: {
                    this.popupItemFont(modifier._popupItemFont_0_0value);
                    break;
                }
                default: {
                    this.popupItemFont((undefined as arkui_component_units_Font | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1:
                case 3: {
                    this.itemSize(modifier._itemSize_0_0value);
                    break;
                }
                default: {
                    this.itemSize((undefined as string | double | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1:
                case 3: {
                    this.font(modifier._font_0_0value);
                    break;
                }
                default: {
                    this.font((undefined as arkui_component_units_Font | undefined));
                }
            }
        }
        if (flagArray[14] != 0) {
            switch (flagArray[14]) {
                case 1:
                case 3: {
                    this.onSelect(modifier._onSelect_0_0value);
                    break;
                }
                default: {
                    this.onSelect((undefined as OnAlphabetIndexerSelectCallback | undefined));
                }
            }
        }
        if (flagArray[15] != 0) {
            switch (flagArray[15]) {
                case 1:
                case 3: {
                    this.onRequestPopupData(modifier._onRequestPopupData_0_0value);
                    break;
                }
                default: {
                    this.onRequestPopupData((undefined as OnAlphabetIndexerRequestPopupDataCallback | undefined));
                }
            }
        }
        if (flagArray[16] != 0) {
            switch (flagArray[16]) {
                case 1:
                case 3: {
                    this.onPopupSelect(modifier._onPopupSelect_0_0value);
                    break;
                }
                default: {
                    this.onPopupSelect((undefined as OnAlphabetIndexerPopupSelectCallback | undefined));
                }
            }
        }
        if (flagArray[17] != 0) {
            switch (flagArray[17]) {
                case 1:
                case 3: {
                    this.selected(modifier._selected_0_0value);
                    break;
                }
                default: {
                    this.selected((undefined as int32 | Bindable<int32> | undefined));
                }
            }
        }
        if (flagArray[18] != 0) {
            switch (flagArray[18]) {
                case 1:
                case 3: {
                    this.popupPosition(modifier._popupPosition_0_0value);
                    break;
                }
                default: {
                    this.popupPosition((undefined as Position | undefined));
                }
            }
        }
        if (flagArray[19] != 0) {
            switch (flagArray[19]) {
                case 1:
                case 3: {
                    this.autoCollapse(modifier._autoCollapse_0_0value);
                    break;
                }
                default: {
                    this.autoCollapse((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier1(modifier: AlphabetIndexerModifier, flagArray: Uint8Array): void {
        if (flagArray[20] != 0) {
            switch (flagArray[20]) {
                case 1:
                case 3: {
                    this.popupItemBorderRadius(modifier._popupItemBorderRadius_0_0value);
                    break;
                }
                default: {
                    this.popupItemBorderRadius((undefined as double | undefined));
                }
            }
        }
        if (flagArray[21] != 0) {
            switch (flagArray[21]) {
                case 1:
                case 3: {
                    this.itemBorderRadius(modifier._itemBorderRadius_0_0value);
                    break;
                }
                default: {
                    this.itemBorderRadius((undefined as double | undefined));
                }
            }
        }
        if (flagArray[22] != 0) {
            switch (flagArray[22]) {
                case 1:
                case 3: {
                    this.popupBackgroundBlurStyle(modifier._popupBackgroundBlurStyle_0_0value);
                    break;
                }
                default: {
                    this.popupBackgroundBlurStyle((undefined as BlurStyle | undefined));
                }
            }
        }
        if (flagArray[23] != 0) {
            switch (flagArray[23]) {
                case 1:
                case 3: {
                    this.popupTitleBackground(modifier._popupTitleBackground_0_0value);
                    break;
                }
                default: {
                    this.popupTitleBackground((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[24] != 0) {
            switch (flagArray[24]) {
                case 1:
                case 3: {
                    this.enableHapticFeedback(modifier._enableHapticFeedback_0_0value);
                    break;
                }
                default: {
                    this.enableHapticFeedback((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[25] != 0) {
            switch (flagArray[25]) {
                case 1:
                case 3: {
                    this.alignStyle(modifier._alignStyle_0_0value, modifier._alignStyle_0_1value);
                    break;
                }
                default: {
                    this.alignStyle((undefined as IndexerAlign | undefined), (undefined as Length | undefined | undefined));
                }
            }
        }
    }
    color(value: ResourceColor | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._color_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    selectedColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._selectedColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    popupColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[2]) == (0)) || (true)) {
            this._flagArray[2] = 1
            this._popupColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    selectedBackgroundColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[3]) == (0)) || (true)) {
            this._flagArray[3] = 1
            this._selectedBackgroundColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    popupBackground(value: ResourceColor | undefined): this {
        if (((this._flagArray[4]) == (0)) || (true)) {
            this._flagArray[4] = 1
            this._popupBackground_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    popupSelectedColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[5]) == (0)) || (true)) {
            this._flagArray[5] = 1
            this._popupSelectedColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    popupUnselectedColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[6]) == (0)) || (true)) {
            this._flagArray[6] = 1
            this._popupUnselectedColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[6] = 3
        }
        return this
    }
    popupItemBackgroundColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[7]) == (0)) || (true)) {
            this._flagArray[7] = 1
            this._popupItemBackgroundColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[7] = 3
        }
        return this
    }
    usingPopup(value: boolean | undefined): this {
        if (((this._flagArray[8]) == (0)) || ((this._usingPopup_0_0value) !== (value))) {
            this._flagArray[8] = 1
            this._usingPopup_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[8] = 3
        }
        return this
    }
    selectedFont(value: arkui_component_units_Font | undefined): this {
        if (((this._flagArray[9]) == (0)) || (true)) {
            this._flagArray[9] = 1
            this._selectedFont_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[9] = 3
        }
        return this
    }
    popupFont(value: arkui_component_units_Font | undefined): this {
        if (((this._flagArray[10]) == (0)) || (true)) {
            this._flagArray[10] = 1
            this._popupFont_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[10] = 3
        }
        return this
    }
    popupItemFont(value: arkui_component_units_Font | undefined): this {
        if (((this._flagArray[11]) == (0)) || (true)) {
            this._flagArray[11] = 1
            this._popupItemFont_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[11] = 3
        }
        return this
    }
    itemSize(value: string | double | undefined): this {
        if (((this._flagArray[12]) == (0)) || ((this._itemSize_0_0value) !== (value))) {
            this._flagArray[12] = 1
            this._itemSize_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[12] = 3
        }
        return this
    }
    font(value: arkui_component_units_Font | undefined): this {
        if (((this._flagArray[13]) == (0)) || (true)) {
            this._flagArray[13] = 1
            this._font_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[13] = 3
        }
        return this
    }
    onSelect(value: OnAlphabetIndexerSelectCallback | undefined): this {
        if (((this._flagArray[14]) == (0)) || (true)) {
            this._flagArray[14] = 1
            this._onSelect_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[14] = 3
        }
        return this
    }
    onRequestPopupData(value: OnAlphabetIndexerRequestPopupDataCallback | undefined): this {
        if (((this._flagArray[15]) == (0)) || (true)) {
            this._flagArray[15] = 1
            this._onRequestPopupData_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[15] = 3
        }
        return this
    }
    onPopupSelect(value: OnAlphabetIndexerPopupSelectCallback | undefined): this {
        if (((this._flagArray[16]) == (0)) || (true)) {
            this._flagArray[16] = 1
            this._onPopupSelect_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[16] = 3
        }
        return this
    }
    selected(value: int32 | Bindable<int32> | undefined): this {
        if (((this._flagArray[17]) == (0)) || (true)) {
            this._flagArray[17] = 1
            this._selected_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[17] = 3
        }
        return this
    }
    popupPosition(value: Position | undefined): this {
        if (((this._flagArray[18]) == (0)) || (true)) {
            this._flagArray[18] = 1
            this._popupPosition_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[18] = 3
        }
        return this
    }
    autoCollapse(value: boolean | undefined): this {
        if (((this._flagArray[19]) == (0)) || ((this._autoCollapse_0_0value) !== (value))) {
            this._flagArray[19] = 1
            this._autoCollapse_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[19] = 3
        }
        return this
    }
    popupItemBorderRadius(value: double | undefined): this {
        if (((this._flagArray[20]) == (0)) || ((this._popupItemBorderRadius_0_0value) !== (value))) {
            this._flagArray[20] = 1
            this._popupItemBorderRadius_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[20] = 3
        }
        return this
    }
    itemBorderRadius(value: double | undefined): this {
        if (((this._flagArray[21]) == (0)) || ((this._itemBorderRadius_0_0value) !== (value))) {
            this._flagArray[21] = 1
            this._itemBorderRadius_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[21] = 3
        }
        return this
    }
    popupBackgroundBlurStyle(value: BlurStyle | undefined): this {
        if (((this._flagArray[22]) == (0)) || (true)) {
            this._flagArray[22] = 1
            this._popupBackgroundBlurStyle_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[22] = 3
        }
        return this
    }
    popupTitleBackground(value: ResourceColor | undefined): this {
        if (((this._flagArray[23]) == (0)) || (true)) {
            this._flagArray[23] = 1
            this._popupTitleBackground_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[23] = 3
        }
        return this
    }
    enableHapticFeedback(value: boolean | undefined): this {
        if (((this._flagArray[24]) == (0)) || ((this._enableHapticFeedback_0_0value) !== (value))) {
            this._flagArray[24] = 1
            this._enableHapticFeedback_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[24] = 3
        }
        return this
    }
    alignStyle(value: IndexerAlign | undefined, offset?: Length): this {
        if (((this._flagArray[25]) == (0)) || (true) || (true)) {
            this._flagArray[25] = 1
            this._alignStyle_0_0value = value
            this._alignStyle_0_1value = offset
            this._state.fireChange()
        } else {
            this._flagArray[25] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<AlphabetIndexerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

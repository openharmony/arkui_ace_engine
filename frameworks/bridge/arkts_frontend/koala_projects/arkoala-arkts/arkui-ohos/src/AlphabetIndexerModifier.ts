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

import { AttributeModifier, CommonMethod, Bindable, BlurStyle } from "./component/common"
import { AttributeUpdaterFlag, CommonMethodModifier } from './CommonMethodModifier'
import { ResourceColor, Font, Position, Length } from "./component/units"
import { Color } from "./component/enums"
import { Resource } from "global.resource"
import { OnAlphabetIndexerSelectCallback, OnAlphabetIndexerRequestPopupDataCallback, OnAlphabetIndexerPopupSelectCallback, AlphabetIndexerAttribute, ArkAlphabetIndexerPeer, IndexerAlign } from "./component/alphabetIndexer"
import { PeerNode } from './PeerNode'

export class AlphabetIndexerModifier extends CommonMethodModifier implements AlphabetIndexerAttribute,AttributeModifier<AlphabetIndexerAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyNormalAttribute(instance: AlphabetIndexerAttribute): void { }
    applyPressedAttribute(instance: AlphabetIndexerAttribute): void { }
    applyFocusedAttribute(instance: AlphabetIndexerAttribute): void { }
    applyDisabledAttribute(instance: AlphabetIndexerAttribute): void { }
    applySelectedAttribute(instance: AlphabetIndexerAttribute): void { }
    _color_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _color_0_0value?: ResourceColor | undefined
    _selectedColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedColor_0_0value?: ResourceColor | undefined
    _popupColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _popupColor_0_0value?: ResourceColor | undefined
    _selectedBackgroundColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedBackgroundColor_0_0value?: ResourceColor | undefined
    _popupBackground_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _popupBackground_0_0value?: ResourceColor | undefined
    _popupSelectedColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _popupSelectedColor_0_0value?: ResourceColor | undefined
    _popupUnselectedColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _popupUnselectedColor_0_0value?: ResourceColor | undefined
    _popupItemBackgroundColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _popupItemBackgroundColor_0_0value?: ResourceColor | undefined
    _usingPopup_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _usingPopup_0_0value?: boolean | undefined
    _selectedFont_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedFont_0_0value?: Font | undefined
    _popupFont_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _popupFont_0_0value?: Font | undefined
    _popupItemFont_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _popupItemFont_0_0value?: Font | undefined
    _itemSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _itemSize_0_0value?: string | number | undefined
    _font_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _font_0_0value?: Font | undefined
    _onSelect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onSelect_0_0value?: OnAlphabetIndexerSelectCallback | undefined
    _onRequestPopupData_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onRequestPopupData_0_0value?: OnAlphabetIndexerRequestPopupDataCallback | undefined
    _onPopupSelect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onPopupSelect_0_0value?: OnAlphabetIndexerPopupSelectCallback | undefined
    _selected_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selected_0_0value?: number | Bindable<number> | undefined
    _popupPosition_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _popupPosition_0_0value?: Position | undefined
    _autoCollapse_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _autoCollapse_0_0value?: boolean | undefined
    _popupItemBorderRadius_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _popupItemBorderRadius_0_0value?: number | undefined
    _itemBorderRadius_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _itemBorderRadius_0_0value?: number | undefined
    _popupBackgroundBlurStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _popupBackgroundBlurStyle_0_0value?: BlurStyle | undefined
    _popupTitleBackground_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _popupTitleBackground_0_0value?: ResourceColor | undefined
    _enableHapticFeedback_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableHapticFeedback_0_0value?: boolean | undefined
    _alignStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _alignStyle_0_0value?: IndexerAlign | undefined
    _alignStyle_0_1value?: Length | undefined
    applyModifierPatch(peerNode: PeerNode): void {
        super.applyModifierPatch(peerNode)
        const peer = peerNode as ArkAlphabetIndexerPeer
        if (this._color_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._color_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.colorAttribute((this._color_0_0value as ResourceColor | undefined));
                    this._color_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._color_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._color_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.colorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._selectedColor_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._selectedColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.selectedColorAttribute((this._selectedColor_0_0value as ResourceColor | undefined));
                    this._selectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectedColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.selectedColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._popupColor_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._popupColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.popupColorAttribute((this._popupColor_0_0value as ResourceColor | undefined));
                    this._popupColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._popupColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._popupColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.popupColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._selectedBackgroundColor_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._selectedBackgroundColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.selectedBackgroundColorAttribute((this._selectedBackgroundColor_0_0value as ResourceColor | undefined));
                    this._selectedBackgroundColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectedBackgroundColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectedBackgroundColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.selectedBackgroundColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._popupBackground_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._popupBackground_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.popupBackgroundAttribute((this._popupBackground_0_0value as ResourceColor | undefined));
                    this._popupBackground_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._popupBackground_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._popupBackground_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.popupBackgroundAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._popupSelectedColor_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._popupSelectedColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.popupSelectedColorAttribute((this._popupSelectedColor_0_0value as ResourceColor | undefined));
                    this._popupSelectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._popupSelectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._popupSelectedColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.popupSelectedColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._popupUnselectedColor_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._popupUnselectedColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.popupUnselectedColorAttribute((this._popupUnselectedColor_0_0value as ResourceColor | undefined));
                    this._popupUnselectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._popupUnselectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._popupUnselectedColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.popupUnselectedColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._popupItemBackgroundColor_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._popupItemBackgroundColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.popupItemBackgroundColorAttribute((this._popupItemBackgroundColor_0_0value as ResourceColor | undefined));
                    this._popupItemBackgroundColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._popupItemBackgroundColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._popupItemBackgroundColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.popupItemBackgroundColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._usingPopup_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._usingPopup_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.usingPopupAttribute((this._usingPopup_0_0value as boolean | undefined));
                    this._usingPopup_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._usingPopup_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._usingPopup_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.usingPopupAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._selectedFont_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._selectedFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.selectedFontAttribute((this._selectedFont_0_0value as Font | undefined));
                    this._selectedFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectedFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectedFont_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.selectedFontAttribute((undefined as Font | undefined));
                }
            }
        }
        if (this._popupFont_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._popupFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.popupFontAttribute((this._popupFont_0_0value as Font | undefined));
                    this._popupFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._popupFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._popupFont_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.popupFontAttribute((undefined as Font | undefined));
                }
            }
        }
        if (this._popupItemFont_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._popupItemFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.popupItemFontAttribute((this._popupItemFont_0_0value as Font | undefined));
                    this._popupItemFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._popupItemFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._popupItemFont_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.popupItemFontAttribute((undefined as Font | undefined));
                }
            }
        }
        if (this._itemSize_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._itemSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.itemSizeAttribute((this._itemSize_0_0value as string | number | undefined));
                    this._itemSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._itemSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._itemSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.itemSizeAttribute((undefined as string | number | undefined));
                }
            }
        }
        if (this._font_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._font_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.fontAttribute((this._font_0_0value as Font | undefined));
                    this._font_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._font_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._font_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.fontAttribute((undefined as Font | undefined));
                }
            }
        }
        if (this._onSelect_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onSelect_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onSelectAttribute((this._onSelect_0_0value as OnAlphabetIndexerSelectCallback | undefined));
                    this._onSelect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onSelect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onSelect_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onSelectAttribute((undefined as OnAlphabetIndexerSelectCallback | undefined));
                }
            }
        }
        if (this._onRequestPopupData_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onRequestPopupData_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onRequestPopupDataAttribute((this._onRequestPopupData_0_0value as OnAlphabetIndexerRequestPopupDataCallback | undefined));
                    this._onRequestPopupData_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onRequestPopupData_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onRequestPopupData_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onRequestPopupDataAttribute((undefined as OnAlphabetIndexerRequestPopupDataCallback | undefined));
                }
            }
        }
        if (this._onPopupSelect_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onPopupSelect_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onPopupSelectAttribute((this._onPopupSelect_0_0value as OnAlphabetIndexerPopupSelectCallback | undefined));
                    this._onPopupSelect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onPopupSelect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onPopupSelect_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onPopupSelectAttribute((undefined as OnAlphabetIndexerPopupSelectCallback | undefined));
                }
            }
        }
        if (this._selected_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._selected_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.selectedAttribute((this._selected_0_0value as number | undefined));
                    this._selected_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selected_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selected_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.selectedAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._popupPosition_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._popupPosition_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.popupPositionAttribute((this._popupPosition_0_0value as Position | undefined));
                    this._popupPosition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._popupPosition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._popupPosition_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.popupPositionAttribute((undefined as Position | undefined));
                }
            }
        }
        if (this._autoCollapse_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._autoCollapse_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.autoCollapseAttribute((this._autoCollapse_0_0value as boolean | undefined));
                    this._autoCollapse_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._autoCollapse_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._autoCollapse_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.autoCollapseAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._popupItemBorderRadius_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._popupItemBorderRadius_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.popupItemBorderRadiusAttribute((this._popupItemBorderRadius_0_0value as number | undefined));
                    this._popupItemBorderRadius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._popupItemBorderRadius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._popupItemBorderRadius_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.popupItemBorderRadiusAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._itemBorderRadius_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._itemBorderRadius_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.itemBorderRadiusAttribute((this._itemBorderRadius_0_0value as number | undefined));
                    this._itemBorderRadius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._itemBorderRadius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._itemBorderRadius_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.itemBorderRadiusAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._popupBackgroundBlurStyle_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._popupBackgroundBlurStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.popupBackgroundBlurStyleAttribute((this._popupBackgroundBlurStyle_0_0value as BlurStyle | undefined));
                    this._popupBackgroundBlurStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._popupBackgroundBlurStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._popupBackgroundBlurStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.popupBackgroundBlurStyleAttribute((undefined as BlurStyle | undefined));
                }
            }
        }
        if (this._popupTitleBackground_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._popupTitleBackground_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.popupTitleBackgroundAttribute((this._popupTitleBackground_0_0value as ResourceColor | undefined));
                    this._popupTitleBackground_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._popupTitleBackground_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._popupTitleBackground_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.popupTitleBackgroundAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._enableHapticFeedback_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._enableHapticFeedback_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.enableHapticFeedbackAttribute((this._enableHapticFeedback_0_0value as boolean | undefined));
                    this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.enableHapticFeedbackAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._alignStyle_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._alignStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.alignStyleAttribute((this._alignStyle_0_0value as IndexerAlign | undefined), (this._alignStyle_0_1value as Length | undefined));
                    this._alignStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._alignStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._alignStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.alignStyleAttribute((undefined as IndexerAlign | undefined), (undefined as Length | undefined | undefined));
                }
            }
        }
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
        if (!(value instanceof AlphabetIndexerModifier)) {
            return;
        }
        const modifier = value as AlphabetIndexerModifier;

        if (modifier._color_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._color_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.color(modifier._color_0_0value);
                    break;
                }
                default: {
                    this.color((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._selectedColor_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._selectedColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selectedColor(modifier._selectedColor_0_0value);
                    break;
                }
                default: {
                    this.selectedColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._popupColor_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._popupColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.popupColor(modifier._popupColor_0_0value);
                    break;
                }
                default: {
                    this.popupColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._selectedBackgroundColor_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._selectedBackgroundColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selectedBackgroundColor(modifier._selectedBackgroundColor_0_0value);
                    break;
                }
                default: {
                    this.selectedBackgroundColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._popupBackground_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._popupBackground_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.popupBackground(modifier._popupBackground_0_0value);
                    break;
                }
                default: {
                    this.popupBackground((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._popupSelectedColor_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._popupSelectedColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.popupSelectedColor(modifier._popupSelectedColor_0_0value);
                    break;
                }
                default: {
                    this.popupSelectedColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._popupUnselectedColor_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._popupUnselectedColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.popupUnselectedColor(modifier._popupUnselectedColor_0_0value);
                    break;
                }
                default: {
                    this.popupUnselectedColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._popupItemBackgroundColor_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._popupItemBackgroundColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.popupItemBackgroundColor(modifier._popupItemBackgroundColor_0_0value);
                    break;
                }
                default: {
                    this.popupItemBackgroundColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._usingPopup_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._usingPopup_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.usingPopup(modifier._usingPopup_0_0value);
                    break;
                }
                default: {
                    this.usingPopup((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._selectedFont_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._selectedFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selectedFont(modifier._selectedFont_0_0value);
                    break;
                }
                default: {
                    this.selectedFont((undefined as Font | undefined));
                }
            }
        }
        if (modifier._popupFont_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._popupFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.popupFont(modifier._popupFont_0_0value);
                    break;
                }
                default: {
                    this.popupFont((undefined as Font | undefined));
                }
            }
        }
        if (modifier._popupItemFont_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._popupItemFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.popupItemFont(modifier._popupItemFont_0_0value);
                    break;
                }
                default: {
                    this.popupItemFont((undefined as Font | undefined));
                }
            }
        }
        if (modifier._itemSize_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._itemSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.itemSize(modifier._itemSize_0_0value);
                    break;
                }
                default: {
                    this.itemSize((undefined as string | number | undefined));
                }
            }
        }
        if (modifier._font_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._font_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.font(modifier._font_0_0value);
                    break;
                }
                default: {
                    this.font((undefined as Font | undefined));
                }
            }
        }
        if (modifier._onSelect_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onSelect_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onSelect(modifier._onSelect_0_0value);
                    break;
                }
                default: {
                    this.onSelect((undefined as OnAlphabetIndexerSelectCallback | undefined));
                }
            }
        }
        if (modifier._onRequestPopupData_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onRequestPopupData_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onRequestPopupData(modifier._onRequestPopupData_0_0value);
                    break;
                }
                default: {
                    this.onRequestPopupData((undefined as OnAlphabetIndexerRequestPopupDataCallback | undefined));
                }
            }
        }
        if (modifier._onPopupSelect_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._onPopupSelect_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onPopupSelect(modifier._onPopupSelect_0_0value);
                    break;
                }
                default: {
                    this.onPopupSelect((undefined as OnAlphabetIndexerPopupSelectCallback | undefined));
                }
            }
        }
        if (modifier._selected_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._selected_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selected(modifier._selected_0_0value);
                    break;
                }
                default: {
                    this.selected((undefined as number | Bindable<number> | undefined));
                }
            }
        }
        if (modifier._popupPosition_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._popupPosition_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.popupPosition(modifier._popupPosition_0_0value);
                    break;
                }
                default: {
                    this.popupPosition((undefined as Position | undefined));
                }
            }
        }
        if (modifier._autoCollapse_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._autoCollapse_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.autoCollapse(modifier._autoCollapse_0_0value);
                    break;
                }
                default: {
                    this.autoCollapse((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._popupItemBorderRadius_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._popupItemBorderRadius_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.popupItemBorderRadius(modifier._popupItemBorderRadius_0_0value);
                    break;
                }
                default: {
                    this.popupItemBorderRadius((undefined as number | undefined));
                }
            }
        }
        if (modifier._itemBorderRadius_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._itemBorderRadius_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.itemBorderRadius(modifier._itemBorderRadius_0_0value);
                    break;
                }
                default: {
                    this.itemBorderRadius((undefined as number | undefined));
                }
            }
        }
        if (modifier._popupBackgroundBlurStyle_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._popupBackgroundBlurStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.popupBackgroundBlurStyle(modifier._popupBackgroundBlurStyle_0_0value);
                    break;
                }
                default: {
                    this.popupBackgroundBlurStyle((undefined as BlurStyle | undefined));
                }
            }
        }
        if (modifier._popupTitleBackground_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._popupTitleBackground_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.popupTitleBackground(modifier._popupTitleBackground_0_0value);
                    break;
                }
                default: {
                    this.popupTitleBackground((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._enableHapticFeedback_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._enableHapticFeedback_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableHapticFeedback(modifier._enableHapticFeedback_0_0value);
                    break;
                }
                default: {
                    this.enableHapticFeedback((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._alignStyle_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._alignStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
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
        if (((this._color_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._color_0_flag = AttributeUpdaterFlag.UPDATE
            this._color_0_0value = value
        } else {
            this._color_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selectedColor(value: ResourceColor | undefined): this {
        if (((this._selectedColor_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._selectedColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectedColor_0_0value = value
        } else {
            this._selectedColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    popupColor(value: ResourceColor | undefined): this {
        if (((this._popupColor_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._popupColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._popupColor_0_0value = value
        } else {
            this._popupColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selectedBackgroundColor(value: ResourceColor | undefined): this {
        if (((this._selectedBackgroundColor_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._selectedBackgroundColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectedBackgroundColor_0_0value = value
        } else {
            this._selectedBackgroundColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    popupBackground(value: ResourceColor | undefined): this {
        if (((this._popupBackground_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._popupBackground_0_flag = AttributeUpdaterFlag.UPDATE
            this._popupBackground_0_0value = value
        } else {
            this._popupBackground_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    popupSelectedColor(value: ResourceColor | undefined): this {
        if (((this._popupSelectedColor_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._popupSelectedColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._popupSelectedColor_0_0value = value
        } else {
            this._popupSelectedColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    popupUnselectedColor(value: ResourceColor | undefined): this {
        if (((this._popupUnselectedColor_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._popupUnselectedColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._popupUnselectedColor_0_0value = value
        } else {
            this._popupUnselectedColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    popupItemBackgroundColor(value: ResourceColor | undefined): this {
        if (((this._popupItemBackgroundColor_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._popupItemBackgroundColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._popupItemBackgroundColor_0_0value = value
        } else {
            this._popupItemBackgroundColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    usingPopup(value: boolean | undefined): this {
        if (((this._usingPopup_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._usingPopup_0_0value) !== (value))) {
            this._usingPopup_0_flag = AttributeUpdaterFlag.UPDATE
            this._usingPopup_0_0value = value
        } else {
            this._usingPopup_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selectedFont(value: Font | undefined): this {
        if (((this._selectedFont_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._selectedFont_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectedFont_0_0value = value
        } else {
            this._selectedFont_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    popupFont(value: Font | undefined): this {
        if (((this._popupFont_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._popupFont_0_flag = AttributeUpdaterFlag.UPDATE
            this._popupFont_0_0value = value
        } else {
            this._popupFont_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    popupItemFont(value: Font | undefined): this {
        if (((this._popupItemFont_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._popupItemFont_0_flag = AttributeUpdaterFlag.UPDATE
            this._popupItemFont_0_0value = value
        } else {
            this._popupItemFont_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    itemSize(value: string | number | undefined): this {
        if (((this._itemSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._itemSize_0_0value) !== (value))) {
            this._itemSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._itemSize_0_0value = value
        } else {
            this._itemSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    font(value: Font | undefined): this {
        if (((this._font_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._font_0_flag = AttributeUpdaterFlag.UPDATE
            this._font_0_0value = value
        } else {
            this._font_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onSelected(value: ((index: number) => void) | undefined): this {
        throw new Error("Not implemented")
    }
    onSelect(value: OnAlphabetIndexerSelectCallback | undefined): this {
        if (((this._onSelect_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._onSelect_0_flag = AttributeUpdaterFlag.UPDATE
            this._onSelect_0_0value = value
        } else {
            this._onSelect_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onRequestPopupData(value: OnAlphabetIndexerRequestPopupDataCallback | undefined): this {
        if (((this._onRequestPopupData_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._onRequestPopupData_0_flag = AttributeUpdaterFlag.UPDATE
            this._onRequestPopupData_0_0value = value
        } else {
            this._onRequestPopupData_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onPopupSelect(value: OnAlphabetIndexerPopupSelectCallback | undefined): this {
        if (((this._onPopupSelect_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._onPopupSelect_0_flag = AttributeUpdaterFlag.UPDATE
            this._onPopupSelect_0_0value = value
        } else {
            this._onPopupSelect_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selected(value: number | Bindable<number> | undefined): this {
        if (((this._selected_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._selected_0_flag = AttributeUpdaterFlag.UPDATE
            this._selected_0_0value = value
        } else {
            this._selected_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    popupPosition(value: Position | undefined): this {
        if (((this._popupPosition_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._popupPosition_0_flag = AttributeUpdaterFlag.UPDATE
            this._popupPosition_0_0value = value
        } else {
            this._popupPosition_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    autoCollapse(value: boolean | undefined): this {
        if (((this._autoCollapse_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._autoCollapse_0_0value) !== (value))) {
            this._autoCollapse_0_flag = AttributeUpdaterFlag.UPDATE
            this._autoCollapse_0_0value = value
        } else {
            this._autoCollapse_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    popupItemBorderRadius(value: number | undefined): this {
        if (((this._popupItemBorderRadius_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._popupItemBorderRadius_0_0value) !== (value))) {
            this._popupItemBorderRadius_0_flag = AttributeUpdaterFlag.UPDATE
            this._popupItemBorderRadius_0_0value = value
        } else {
            this._popupItemBorderRadius_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    itemBorderRadius(value: number | undefined): this {
        if (((this._itemBorderRadius_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._itemBorderRadius_0_0value) !== (value))) {
            this._itemBorderRadius_0_flag = AttributeUpdaterFlag.UPDATE
            this._itemBorderRadius_0_0value = value
        } else {
            this._itemBorderRadius_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    popupBackgroundBlurStyle(value: BlurStyle | undefined): this {
        if (((this._popupBackgroundBlurStyle_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._popupBackgroundBlurStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._popupBackgroundBlurStyle_0_0value = value
        } else {
            this._popupBackgroundBlurStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    popupTitleBackground(value: ResourceColor | undefined): this {
        if (((this._popupTitleBackground_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._popupTitleBackground_0_flag = AttributeUpdaterFlag.UPDATE
            this._popupTitleBackground_0_0value = value
        } else {
            this._popupTitleBackground_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableHapticFeedback(value: boolean | undefined): this {
        if (((this._enableHapticFeedback_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableHapticFeedback_0_0value) !== (value))) {
            this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableHapticFeedback_0_0value = value
        } else {
            this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    alignStyle(value: IndexerAlign | undefined, offset?: Length): this {
        if (((this._alignStyle_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._alignStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._alignStyle_0_0value = value
            this._alignStyle_0_1value = offset
        } else {
            this._alignStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public _onChangeEvent_selected(callback: ((selected: number | undefined) => void)): void {
        throw new Error("Not implemented")
    }
    public attributeModifier(value: AttributeModifier<AlphabetIndexerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

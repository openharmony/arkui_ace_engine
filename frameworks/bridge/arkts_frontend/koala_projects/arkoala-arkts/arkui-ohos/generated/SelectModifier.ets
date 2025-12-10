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
import { AttributeModifier, ContentModifier, extractors, hookSelectContentModifier, hookSelectSetDividerMethod } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkSelectPeer, OnSelectCallback, ArrowPosition, MenuItemConfiguration, AvoidanceMode, MenuOutlineOptions, SelectAttribute, MenuAlignType } from './component/select'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod, Bindable, BlurStyle } from './component/common'
import { Resource as arkui_component_units_Resource, ResourceStr as arkui_component_units_ResourceStr, Font as arkui_component_units_Font, ResourceColor, Length, Dimension, DividerStyleOptions, Offset } from './component/units'
import { Resource as global_resource_Resource } from 'global.resource'
import { Color as arkui_component_enums_Color, OptionWidthMode } from './component/enums'
import { ControlSize } from './component/button'
import { DividerOptions } from './component/textPicker'
import { TextModifier } from 'arkui.TextModifier'
import { SymbolGlyphModifier } from '@arkui.SymbolGlyphModifier'
export class SelectModifier extends CommonMethodModifier implements SelectAttribute,AttributeModifier<SelectAttribute> {
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
    applyNormalAttribute(instance: SelectAttribute): void { }
    applyPressedAttribute(instance: SelectAttribute): void { }
    applyFocusedAttribute(instance: SelectAttribute): void { }
    applyDisabledAttribute(instance: SelectAttribute): void { }
    applySelectedAttribute(instance: SelectAttribute): void { }
    public _selected_0_0value?: int32 | arkui_component_units_Resource | Bindable<int32> | Bindable<global_resource_Resource> | undefined
    public _value_0_0value?: arkui_component_units_ResourceStr | Bindable<string> | Bindable<global_resource_Resource> | undefined
    public _font_0_0value?: arkui_component_units_Font | undefined
    public _fontColor_0_0value?: ResourceColor | undefined
    public _selectedOptionBgColor_0_0value?: ResourceColor | undefined
    public _selectedOptionFont_0_0value?: arkui_component_units_Font | undefined
    public _selectedOptionFontColor_0_0value?: ResourceColor | undefined
    public _optionBgColor_0_0value?: ResourceColor | undefined
    public _optionFont_0_0value?: arkui_component_units_Font | undefined
    public _optionFontColor_0_0value?: ResourceColor | undefined
    public _onSelect_0_0value?: OnSelectCallback | undefined
    public _space_0_0value?: Length | undefined
    public _arrowPosition_0_0value?: ArrowPosition | undefined
    public _optionWidth_0_0value?: Dimension | OptionWidthMode | undefined
    public _optionHeight_0_0value?: Dimension | undefined
    public _menuBackgroundColor_0_0value?: ResourceColor | undefined
    public _menuBackgroundBlurStyle_0_0value?: BlurStyle | undefined
    public _controlSize_0_0value?: ControlSize | undefined
    public _menuItemContentModifier_0_0value?: ContentModifier<MenuItemConfiguration> | undefined
    public _divider_0_0value?: DividerOptions | null | undefined
    public _textModifier_0_0value?: TextModifier | undefined
    public _arrowModifier_0_0value?: SymbolGlyphModifier | undefined
    public _optionTextModifier_0_0value?: TextModifier | undefined
    public _selectedOptionTextModifier_0_0value?: TextModifier | undefined
    public _dividerStyle_0_0value?: DividerStyleOptions | undefined
    public _avoidance_0_0value?: AvoidanceMode | undefined
    public _menuOutline_0_0value?: MenuOutlineOptions | undefined
    public _menuAlign_0_0value?: MenuAlignType | undefined
    public _menuAlign_0_1value?: Offset | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkSelectPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
        this.applyModifierPatch1(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkSelectPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setSelectedAttribute((this._selected_0_0value as int32 | arkui_component_units_Resource | Bindable<int32> | Bindable<global_resource_Resource> | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setSelectedAttribute((undefined as int32 | arkui_component_units_Resource | Bindable<int32> | Bindable<global_resource_Resource> | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setValueAttribute((this._value_0_0value as arkui_component_units_ResourceStr | Bindable<string> | Bindable<global_resource_Resource> | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setValueAttribute((undefined as arkui_component_units_ResourceStr | Bindable<string> | Bindable<global_resource_Resource> | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setFontAttribute((this._font_0_0value as arkui_component_units_Font | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setFontAttribute((undefined as arkui_component_units_Font | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setFontColorAttribute((this._fontColor_0_0value as ResourceColor | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setFontColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setSelectedOptionBgColorAttribute((this._selectedOptionBgColor_0_0value as ResourceColor | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setSelectedOptionBgColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setSelectedOptionFontAttribute((this._selectedOptionFont_0_0value as arkui_component_units_Font | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setSelectedOptionFontAttribute((undefined as arkui_component_units_Font | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1: {
                    peer.setSelectedOptionFontColorAttribute((this._selectedOptionFontColor_0_0value as ResourceColor | undefined));
                    flagArray[6] = 2;
                    break;
                }
                case 3: {
                    flagArray[6] = 2;
                    break;
                }
                default: {
                    flagArray[6] = 0;
                    peer.setSelectedOptionFontColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1: {
                    peer.setOptionBgColorAttribute((this._optionBgColor_0_0value as ResourceColor | undefined));
                    flagArray[7] = 2;
                    break;
                }
                case 3: {
                    flagArray[7] = 2;
                    break;
                }
                default: {
                    flagArray[7] = 0;
                    peer.setOptionBgColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1: {
                    peer.setOptionFontAttribute((this._optionFont_0_0value as arkui_component_units_Font | undefined));
                    flagArray[8] = 2;
                    break;
                }
                case 3: {
                    flagArray[8] = 2;
                    break;
                }
                default: {
                    flagArray[8] = 0;
                    peer.setOptionFontAttribute((undefined as arkui_component_units_Font | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1: {
                    peer.setOptionFontColorAttribute((this._optionFontColor_0_0value as ResourceColor | undefined));
                    flagArray[9] = 2;
                    break;
                }
                case 3: {
                    flagArray[9] = 2;
                    break;
                }
                default: {
                    flagArray[9] = 0;
                    peer.setOptionFontColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1: {
                    peer.setOnSelectAttribute((this._onSelect_0_0value as OnSelectCallback | undefined));
                    flagArray[10] = 2;
                    break;
                }
                case 3: {
                    flagArray[10] = 2;
                    break;
                }
                default: {
                    flagArray[10] = 0;
                    peer.setOnSelectAttribute((undefined as OnSelectCallback | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1: {
                    peer.setSpaceAttribute((this._space_0_0value as Length | undefined));
                    flagArray[11] = 2;
                    break;
                }
                case 3: {
                    flagArray[11] = 2;
                    break;
                }
                default: {
                    flagArray[11] = 0;
                    peer.setSpaceAttribute((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1: {
                    peer.setArrowPositionAttribute((this._arrowPosition_0_0value as ArrowPosition | undefined));
                    flagArray[12] = 2;
                    break;
                }
                case 3: {
                    flagArray[12] = 2;
                    break;
                }
                default: {
                    flagArray[12] = 0;
                    peer.setArrowPositionAttribute((undefined as ArrowPosition | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1: {
                    peer.setOptionWidthAttribute((this._optionWidth_0_0value as Dimension | OptionWidthMode | undefined));
                    flagArray[13] = 2;
                    break;
                }
                case 3: {
                    flagArray[13] = 2;
                    break;
                }
                default: {
                    flagArray[13] = 0;
                    peer.setOptionWidthAttribute((undefined as Dimension | OptionWidthMode | undefined));
                }
            }
        }
        if (flagArray[14] != 0) {
            switch (flagArray[14]) {
                case 1: {
                    peer.setOptionHeightAttribute((this._optionHeight_0_0value as Dimension | undefined));
                    flagArray[14] = 2;
                    break;
                }
                case 3: {
                    flagArray[14] = 2;
                    break;
                }
                default: {
                    flagArray[14] = 0;
                    peer.setOptionHeightAttribute((undefined as Dimension | undefined));
                }
            }
        }
        if (flagArray[15] != 0) {
            switch (flagArray[15]) {
                case 1: {
                    peer.setMenuBackgroundColorAttribute((this._menuBackgroundColor_0_0value as ResourceColor | undefined));
                    flagArray[15] = 2;
                    break;
                }
                case 3: {
                    flagArray[15] = 2;
                    break;
                }
                default: {
                    flagArray[15] = 0;
                    peer.setMenuBackgroundColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[16] != 0) {
            switch (flagArray[16]) {
                case 1: {
                    peer.setMenuBackgroundBlurStyleAttribute((this._menuBackgroundBlurStyle_0_0value as BlurStyle | undefined));
                    flagArray[16] = 2;
                    break;
                }
                case 3: {
                    flagArray[16] = 2;
                    break;
                }
                default: {
                    flagArray[16] = 0;
                    peer.setMenuBackgroundBlurStyleAttribute((undefined as BlurStyle | undefined));
                }
            }
        }
        if (flagArray[17] != 0) {
            switch (flagArray[17]) {
                case 1: {
                    peer.setControlSizeAttribute((this._controlSize_0_0value as ControlSize | undefined));
                    flagArray[17] = 2;
                    break;
                }
                case 3: {
                    flagArray[17] = 2;
                    break;
                }
                default: {
                    flagArray[17] = 0;
                    peer.setControlSizeAttribute((undefined as ControlSize | undefined));
                }
            }
        }
        if (flagArray[18] != 0) {
            switch (flagArray[18]) {
                case 1: {
                    hookSelectContentModifier(peer, (this._menuItemContentModifier_0_0value as ContentModifier<MenuItemConfiguration> | undefined));
                    flagArray[18] = 2;
                    break;
                }
                case 3: {
                    flagArray[18] = 2;
                    break;
                }
                default: {
                    flagArray[18] = 0;
                    hookSelectContentModifier(peer, (undefined as ContentModifier<MenuItemConfiguration> | undefined));
                }
            }
        }
        if (flagArray[19] != 0) {
            switch (flagArray[19]) {
                case 1: {
                    hookSelectSetDividerMethod(peer, (this._divider_0_0value as DividerOptions | null | undefined));
                    flagArray[19] = 2;
                    break;
                }
                case 3: {
                    flagArray[19] = 2;
                    break;
                }
                default: {
                    flagArray[19] = 0;
                    hookSelectSetDividerMethod(peer, (undefined as DividerOptions | null | undefined));
                }
            }
        }
    }
    applyModifierPatch1(peer: ArkSelectPeer, flagArray: Uint8Array): void {
        if (flagArray[20] != 0) {
            switch (flagArray[20]) {
                case 1: {
                    peer.setTextModifierAttribute((this._textModifier_0_0value as TextModifier | undefined));
                    flagArray[20] = 2;
                    break;
                }
                case 3: {
                    flagArray[20] = 2;
                    break;
                }
                default: {
                    flagArray[20] = 0;
                    peer.setTextModifierAttribute((undefined as TextModifier | undefined));
                }
            }
        }
        if (flagArray[21] != 0) {
            switch (flagArray[21]) {
                case 1: {
                    peer.setArrowModifierAttribute((this._arrowModifier_0_0value as SymbolGlyphModifier | undefined));
                    flagArray[21] = 2;
                    break;
                }
                case 3: {
                    flagArray[21] = 2;
                    break;
                }
                default: {
                    flagArray[21] = 0;
                    peer.setArrowModifierAttribute((undefined as SymbolGlyphModifier | undefined));
                }
            }
        }
        if (flagArray[22] != 0) {
            switch (flagArray[22]) {
                case 1: {
                    peer.setOptionTextModifierAttribute((this._optionTextModifier_0_0value as TextModifier | undefined));
                    flagArray[22] = 2;
                    break;
                }
                case 3: {
                    flagArray[22] = 2;
                    break;
                }
                default: {
                    flagArray[22] = 0;
                    peer.setOptionTextModifierAttribute((undefined as TextModifier | undefined));
                }
            }
        }
        if (flagArray[23] != 0) {
            switch (flagArray[23]) {
                case 1: {
                    peer.setSelectedOptionTextModifierAttribute((this._selectedOptionTextModifier_0_0value as TextModifier | undefined));
                    flagArray[23] = 2;
                    break;
                }
                case 3: {
                    flagArray[23] = 2;
                    break;
                }
                default: {
                    flagArray[23] = 0;
                    peer.setSelectedOptionTextModifierAttribute((undefined as TextModifier | undefined));
                }
            }
        }
        if (flagArray[24] != 0) {
            switch (flagArray[24]) {
                case 1: {
                    peer.setDividerStyleAttribute((this._dividerStyle_0_0value as DividerStyleOptions | undefined));
                    flagArray[24] = 2;
                    break;
                }
                case 3: {
                    flagArray[24] = 2;
                    break;
                }
                default: {
                    flagArray[24] = 0;
                    peer.setDividerStyleAttribute((undefined as DividerStyleOptions | undefined));
                }
            }
        }
        if (flagArray[25] != 0) {
            switch (flagArray[25]) {
                case 1: {
                    peer.setAvoidanceAttribute((this._avoidance_0_0value as AvoidanceMode | undefined));
                    flagArray[25] = 2;
                    break;
                }
                case 3: {
                    flagArray[25] = 2;
                    break;
                }
                default: {
                    flagArray[25] = 0;
                    peer.setAvoidanceAttribute((undefined as AvoidanceMode | undefined));
                }
            }
        }
        if (flagArray[26] != 0) {
            switch (flagArray[26]) {
                case 1: {
                    peer.setMenuOutlineAttribute((this._menuOutline_0_0value as MenuOutlineOptions | undefined));
                    flagArray[26] = 2;
                    break;
                }
                case 3: {
                    flagArray[26] = 2;
                    break;
                }
                default: {
                    flagArray[26] = 0;
                    peer.setMenuOutlineAttribute((undefined as MenuOutlineOptions | undefined));
                }
            }
        }
        if (flagArray[27] != 0) {
            switch (flagArray[27]) {
                case 1: {
                    peer.setMenuAlignAttribute((this._menuAlign_0_0value as MenuAlignType | undefined), (this._menuAlign_0_1value as Offset | undefined | undefined));
                    flagArray[27] = 2;
                    break;
                }
                case 3: {
                    flagArray[27] = 2;
                    break;
                }
                default: {
                    flagArray[27] = 0;
                    peer.setMenuAlignAttribute((undefined as MenuAlignType | undefined), (undefined as Offset | undefined | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: SelectModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
        this.mergeModifier1(modifier, flagArray);
    }
    mergeModifier0(modifier: SelectModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.selected(modifier._selected_0_0value);
                    break;
                }
                default: {
                    this.selected((undefined as int32 | arkui_component_units_Resource | Bindable<int32> | Bindable<global_resource_Resource> | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.value(modifier._value_0_0value);
                    break;
                }
                default: {
                    this.value((undefined as arkui_component_units_ResourceStr | Bindable<string> | Bindable<global_resource_Resource> | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
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
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.fontColor(modifier._fontColor_0_0value);
                    break;
                }
                default: {
                    this.fontColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.selectedOptionBgColor(modifier._selectedOptionBgColor_0_0value);
                    break;
                }
                default: {
                    this.selectedOptionBgColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1:
                case 3: {
                    this.selectedOptionFont(modifier._selectedOptionFont_0_0value);
                    break;
                }
                default: {
                    this.selectedOptionFont((undefined as arkui_component_units_Font | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1:
                case 3: {
                    this.selectedOptionFontColor(modifier._selectedOptionFontColor_0_0value);
                    break;
                }
                default: {
                    this.selectedOptionFontColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1:
                case 3: {
                    this.optionBgColor(modifier._optionBgColor_0_0value);
                    break;
                }
                default: {
                    this.optionBgColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1:
                case 3: {
                    this.optionFont(modifier._optionFont_0_0value);
                    break;
                }
                default: {
                    this.optionFont((undefined as arkui_component_units_Font | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1:
                case 3: {
                    this.optionFontColor(modifier._optionFontColor_0_0value);
                    break;
                }
                default: {
                    this.optionFontColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1:
                case 3: {
                    this.onSelect(modifier._onSelect_0_0value);
                    break;
                }
                default: {
                    this.onSelect((undefined as OnSelectCallback | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1:
                case 3: {
                    this.space(modifier._space_0_0value);
                    break;
                }
                default: {
                    this.space((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1:
                case 3: {
                    this.arrowPosition(modifier._arrowPosition_0_0value);
                    break;
                }
                default: {
                    this.arrowPosition((undefined as ArrowPosition | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1:
                case 3: {
                    this.optionWidth(modifier._optionWidth_0_0value);
                    break;
                }
                default: {
                    this.optionWidth((undefined as Dimension | OptionWidthMode | undefined));
                }
            }
        }
        if (flagArray[14] != 0) {
            switch (flagArray[14]) {
                case 1:
                case 3: {
                    this.optionHeight(modifier._optionHeight_0_0value);
                    break;
                }
                default: {
                    this.optionHeight((undefined as Dimension | undefined));
                }
            }
        }
        if (flagArray[15] != 0) {
            switch (flagArray[15]) {
                case 1:
                case 3: {
                    this.menuBackgroundColor(modifier._menuBackgroundColor_0_0value);
                    break;
                }
                default: {
                    this.menuBackgroundColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[16] != 0) {
            switch (flagArray[16]) {
                case 1:
                case 3: {
                    this.menuBackgroundBlurStyle(modifier._menuBackgroundBlurStyle_0_0value);
                    break;
                }
                default: {
                    this.menuBackgroundBlurStyle((undefined as BlurStyle | undefined));
                }
            }
        }
        if (flagArray[17] != 0) {
            switch (flagArray[17]) {
                case 1:
                case 3: {
                    this.controlSize(modifier._controlSize_0_0value);
                    break;
                }
                default: {
                    this.controlSize((undefined as ControlSize | undefined));
                }
            }
        }
        if (flagArray[18] != 0) {
            switch (flagArray[18]) {
                case 1:
                case 3: {
                    this.menuItemContentModifier(modifier._menuItemContentModifier_0_0value);
                    break;
                }
                default: {
                    this.menuItemContentModifier((undefined as ContentModifier<MenuItemConfiguration> | undefined));
                }
            }
        }
        if (flagArray[19] != 0) {
            switch (flagArray[19]) {
                case 1:
                case 3: {
                    this.divider(modifier._divider_0_0value);
                    break;
                }
                default: {
                    this.divider((undefined as DividerOptions | null | undefined));
                }
            }
        }
    }
    mergeModifier1(modifier: SelectModifier, flagArray: Uint8Array): void {
        if (flagArray[20] != 0) {
            switch (flagArray[20]) {
                case 1:
                case 3: {
                    this.textModifier(modifier._textModifier_0_0value);
                    break;
                }
                default: {
                    this.textModifier((undefined as TextModifier | undefined));
                }
            }
        }
        if (flagArray[21] != 0) {
            switch (flagArray[21]) {
                case 1:
                case 3: {
                    this.arrowModifier(modifier._arrowModifier_0_0value);
                    break;
                }
                default: {
                    this.arrowModifier((undefined as SymbolGlyphModifier | undefined));
                }
            }
        }
        if (flagArray[22] != 0) {
            switch (flagArray[22]) {
                case 1:
                case 3: {
                    this.optionTextModifier(modifier._optionTextModifier_0_0value);
                    break;
                }
                default: {
                    this.optionTextModifier((undefined as TextModifier | undefined));
                }
            }
        }
        if (flagArray[23] != 0) {
            switch (flagArray[23]) {
                case 1:
                case 3: {
                    this.selectedOptionTextModifier(modifier._selectedOptionTextModifier_0_0value);
                    break;
                }
                default: {
                    this.selectedOptionTextModifier((undefined as TextModifier | undefined));
                }
            }
        }
        if (flagArray[24] != 0) {
            switch (flagArray[24]) {
                case 1:
                case 3: {
                    this.dividerStyle(modifier._dividerStyle_0_0value);
                    break;
                }
                default: {
                    this.dividerStyle((undefined as DividerStyleOptions | undefined));
                }
            }
        }
        if (flagArray[25] != 0) {
            switch (flagArray[25]) {
                case 1:
                case 3: {
                    this.avoidance(modifier._avoidance_0_0value);
                    break;
                }
                default: {
                    this.avoidance((undefined as AvoidanceMode | undefined));
                }
            }
        }
        if (flagArray[26] != 0) {
            switch (flagArray[26]) {
                case 1:
                case 3: {
                    this.menuOutline(modifier._menuOutline_0_0value);
                    break;
                }
                default: {
                    this.menuOutline((undefined as MenuOutlineOptions | undefined));
                }
            }
        }
        if (flagArray[27] != 0) {
            switch (flagArray[27]) {
                case 1:
                case 3: {
                    this.menuAlign(modifier._menuAlign_0_0value, modifier._menuAlign_0_1value);
                    break;
                }
                default: {
                    this.menuAlign((undefined as MenuAlignType | undefined), (undefined as Offset | undefined | undefined));
                }
            }
        }
    }
    selected(value: int32 | arkui_component_units_Resource | Bindable<int32> | Bindable<global_resource_Resource> | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._selected_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    value(value: arkui_component_units_ResourceStr | Bindable<string> | Bindable<global_resource_Resource> | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._value_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    font(value: arkui_component_units_Font | undefined): this {
        if (((this._flagArray[2]) == (0)) || (true)) {
            this._flagArray[2] = 1
            this._font_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    fontColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[3]) == (0)) || (true)) {
            this._flagArray[3] = 1
            this._fontColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    selectedOptionBgColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[4]) == (0)) || (true)) {
            this._flagArray[4] = 1
            this._selectedOptionBgColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    selectedOptionFont(value: arkui_component_units_Font | undefined): this {
        if (((this._flagArray[5]) == (0)) || (true)) {
            this._flagArray[5] = 1
            this._selectedOptionFont_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    selectedOptionFontColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[6]) == (0)) || (true)) {
            this._flagArray[6] = 1
            this._selectedOptionFontColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[6] = 3
        }
        return this
    }
    optionBgColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[7]) == (0)) || (true)) {
            this._flagArray[7] = 1
            this._optionBgColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[7] = 3
        }
        return this
    }
    optionFont(value: arkui_component_units_Font | undefined): this {
        if (((this._flagArray[8]) == (0)) || (true)) {
            this._flagArray[8] = 1
            this._optionFont_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[8] = 3
        }
        return this
    }
    optionFontColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[9]) == (0)) || (true)) {
            this._flagArray[9] = 1
            this._optionFontColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[9] = 3
        }
        return this
    }
    onSelect(value: OnSelectCallback | undefined): this {
        if (((this._flagArray[10]) == (0)) || (true)) {
            this._flagArray[10] = 1
            this._onSelect_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[10] = 3
        }
        return this
    }
    space(value: Length | undefined): this {
        if (((this._flagArray[11]) == (0)) || (true)) {
            this._flagArray[11] = 1
            this._space_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[11] = 3
        }
        return this
    }
    arrowPosition(value: ArrowPosition | undefined): this {
        if (((this._flagArray[12]) == (0)) || (true)) {
            this._flagArray[12] = 1
            this._arrowPosition_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[12] = 3
        }
        return this
    }
    optionWidth(value: Dimension | OptionWidthMode | undefined): this {
        if (((this._flagArray[13]) == (0)) || (true)) {
            this._flagArray[13] = 1
            this._optionWidth_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[13] = 3
        }
        return this
    }
    optionHeight(value: Dimension | undefined): this {
        if (((this._flagArray[14]) == (0)) || (true)) {
            this._flagArray[14] = 1
            this._optionHeight_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[14] = 3
        }
        return this
    }
    menuBackgroundColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[15]) == (0)) || (true)) {
            this._flagArray[15] = 1
            this._menuBackgroundColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[15] = 3
        }
        return this
    }
    menuBackgroundBlurStyle(value: BlurStyle | undefined): this {
        if (((this._flagArray[16]) == (0)) || (true)) {
            this._flagArray[16] = 1
            this._menuBackgroundBlurStyle_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[16] = 3
        }
        return this
    }
    controlSize(value: ControlSize | undefined): this {
        if (((this._flagArray[17]) == (0)) || (true)) {
            this._flagArray[17] = 1
            this._controlSize_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[17] = 3
        }
        return this
    }
    menuItemContentModifier(value: ContentModifier<MenuItemConfiguration> | undefined): this {
        if (((this._flagArray[18]) == (0)) || (true)) {
            this._flagArray[18] = 1
            this._menuItemContentModifier_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[18] = 3
        }
        return this
    }
    divider(value: DividerOptions | null | undefined): this {
        if (((this._flagArray[19]) == (0)) || (true)) {
            this._flagArray[19] = 1
            this._divider_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[19] = 3
        }
        return this
    }
    textModifier(value: TextModifier | undefined): this {
        if (((this._flagArray[20]) == (0)) || (true)) {
            this._flagArray[20] = 1
            this._textModifier_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[20] = 3
        }
        return this
    }
    arrowModifier(value: SymbolGlyphModifier | undefined): this {
        if (((this._flagArray[21]) == (0)) || (true)) {
            this._flagArray[21] = 1
            this._arrowModifier_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[21] = 3
        }
        return this
    }
    optionTextModifier(value: TextModifier | undefined): this {
        if (((this._flagArray[22]) == (0)) || (true)) {
            this._flagArray[22] = 1
            this._optionTextModifier_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[22] = 3
        }
        return this
    }
    selectedOptionTextModifier(value: TextModifier | undefined): this {
        if (((this._flagArray[23]) == (0)) || (true)) {
            this._flagArray[23] = 1
            this._selectedOptionTextModifier_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[23] = 3
        }
        return this
    }
    dividerStyle(value: DividerStyleOptions | undefined): this {
        if (((this._flagArray[24]) == (0)) || (true)) {
            this._flagArray[24] = 1
            this._dividerStyle_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[24] = 3
        }
        return this
    }
    avoidance(value: AvoidanceMode | undefined): this {
        if (((this._flagArray[25]) == (0)) || (true)) {
            this._flagArray[25] = 1
            this._avoidance_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[25] = 3
        }
        return this
    }
    menuOutline(value: MenuOutlineOptions | undefined): this {
        if (((this._flagArray[26]) == (0)) || (true)) {
            this._flagArray[26] = 1
            this._menuOutline_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[26] = 3
        }
        return this
    }
    menuAlign(alignType: MenuAlignType | undefined, offset?: Offset): this {
        if (((this._flagArray[27]) == (0)) || (true) || (true)) {
            this._flagArray[27] = 1
            this._menuAlign_0_0value = alignType
            this._menuAlign_0_1value = offset
            this._state.fireChange()
        } else {
            this._flagArray[27] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<SelectAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

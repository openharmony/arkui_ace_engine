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

import { AttributeModifier, ResourceColor, SelectAttribute, Bindable, ResourceStr, Font, Length, OnSelectCallback, ArrowPosition, Dimension, OptionWidthMode, BlurStyle, ControlSize, DividerOptions, DividerStyleOptions, AvoidanceMode, MenuOutlineOptions, MenuAlignType, Offset } from './component';
import { CommonMethodModifier, AttributeUpdaterFlag } from './CommonMethodModifier';
import { TextModifier } from './TextModifier';
import { SymbolGlyphModifier } from './SymbolGlyphModifier';
import { Resource } from 'global.resource';
import { ArkSelectPeer } from './component/select';
import { TypeChecker } from '#components';
import { SelectOpsHandWritten } from './handwritten';
import { PeerNode } from './PeerNode';

export class SelectModifier extends CommonMethodModifier implements SelectAttribute, AttributeModifier<SelectAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyNormalAttribute(instance: SelectAttribute): void {}
    applyPressedAttribute(instance: SelectAttribute): void {}
    applyFocusedAttribute(instance: SelectAttribute): void {}
    applyDisabledAttribute(instance: SelectAttribute): void {}
    applySelectedAttribute(instance: SelectAttribute): void {}
    _selected_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selected_0_0value?: number | Resource | Bindable<number> | Bindable<Resource> | undefined
    _value_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _value_0_0value?: ResourceStr | Bindable<string> | Bindable<Resource> | undefined
    _font_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _font_0_0value?: Font | undefined
    _fontColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontColor_0_0value?: ResourceColor | undefined
    _selectedOptionBgColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedOptionBgColor_0_0value?: ResourceColor | undefined
    _selectedOptionFont_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedOptionFont_0_0value?: Font | undefined
    _selectedOptionFontColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedOptionFontColor_0_0value?: ResourceColor | undefined
    _optionBgColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _optionBgColor_0_0value?: ResourceColor | undefined
    _optionFont_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _optionFont_0_0value?: Font | undefined
    _optionFontColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _optionFontColor_0_0value?: ResourceColor | undefined
    _onSelect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onSelect_0_0value?: OnSelectCallback | undefined
    _space_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _space_0_0value?: Length | undefined
    _arrowPosition_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _arrowPosition_0_0value?: ArrowPosition | undefined
    _optionWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _optionWidth_0_0value?: Dimension | OptionWidthMode | undefined
    _optionHeight_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _optionHeight_0_0value?: Dimension | undefined
    _menuBackgroundColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _menuBackgroundColor_0_0value?: ResourceColor | undefined
    _menuBackgroundBlurStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _menuBackgroundBlurStyle_0_0value?: BlurStyle | undefined
    _controlSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _controlSize_0_0value?: ControlSize | undefined
    _divider_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _divider_0_0value?: DividerOptions | undefined
    _textModifier_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textModifier_0_0value?: TextModifier | undefined
    _arrowModifier_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _arrowModifier_0_0value?: SymbolGlyphModifier | undefined
    _optionTextModifier_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _optionTextModifier_0_0value?: TextModifier | undefined
    _selectedOptionTextModifier_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedOptionTextModifier_0_0value?: TextModifier | undefined
    _dividerStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _dividerStyle_0_0value?: DividerStyleOptions | undefined
    _avoidance_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _avoidance_0_0value?: AvoidanceMode | undefined
    _menuOutline_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _menuOutline_0_0value?: MenuOutlineOptions | undefined
    _menuAlign_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _menuAlign_0_0value?: MenuAlignType | undefined
    _menuAlign_0_1value?: Offset | undefined
    applyModifierPatch(value: PeerNode): void {
        super.applyModifierPatch(value)
        const peer = value as ArkSelectPeer
        if (this._selected_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selected_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    if (typeof this._selected_0_0value === "number" || TypeChecker.isResource(this._selected_0_0value, false, false, false, false, false) || typeof this._selected_0_0value === "undefined") {
                        peer.selected0Attribute((this._selected_0_0value as number | Resource | undefined));
                    } else {
                        SelectOpsHandWritten.hookSelectAttributeSelectedImpl(peer.peer.ptr, (this._selected_0_0value as Bindable<number | Resource>));
                    }
                    this._selected_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selected_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selected_0_flag = AttributeUpdaterFlag.INITIAL;
                    if (typeof this._selected_0_0value === "number" || TypeChecker.isResource(this._selected_0_0value, false, false, false, false, false) || typeof this._selected_0_0value === "undefined") {
                        peer.selected0Attribute((this._selected_0_0value as number | Resource | undefined));
                    } else {
                        SelectOpsHandWritten.hookSelectAttributeSelectedImpl(peer.peer.ptr, (this._selected_0_0value as Bindable<number | Resource>));
                    }
                }
            }
        }
        if (this._value_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._value_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    if (TypeChecker.isBindableString(this._value_0_0value) || TypeChecker.isBindableResource(this._value_0_0value)) {
                        SelectOpsHandWritten.hookSelectAttributeValueImpl(peer.peer.ptr, (this._value_0_0value as Bindable<ResourceStr>));
                    } else {
                        peer.value0Attribute((this._value_0_0value as ResourceStr | undefined));
                    }
                    this._value_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._value_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._value_0_flag = AttributeUpdaterFlag.INITIAL;
                    if (TypeChecker.isBindableString(this._value_0_0value) || TypeChecker.isBindableResource(this._value_0_0value)) {
                        SelectOpsHandWritten.hookSelectAttributeValueImpl(peer.peer.ptr, (this._value_0_0value as Bindable<ResourceStr>));
                    } else {
                        peer.value0Attribute((this._value_0_0value as ResourceStr | undefined));
                    }
                }
            }
        }
        if (this._font_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._font_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.font0Attribute((this._font_0_0value as Font | undefined));
                    this._font_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._font_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._font_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.font0Attribute((undefined as Font | undefined));
                }
            }
        }
        if (this._fontColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.fontColor0Attribute((this._fontColor_0_0value as ResourceColor | undefined));
                    this._fontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.fontColor0Attribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._selectedOptionBgColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectedOptionBgColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.selectedOptionBgColor0Attribute((this._selectedOptionBgColor_0_0value as ResourceColor | undefined));
                    this._selectedOptionBgColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectedOptionBgColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectedOptionBgColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.selectedOptionBgColor0Attribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._selectedOptionFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectedOptionFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.selectedOptionFont0Attribute((this._selectedOptionFont_0_0value as Font | undefined));
                    this._selectedOptionFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectedOptionFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectedOptionFont_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.selectedOptionFont0Attribute((undefined as Font | undefined));
                }
            }
        }
        if (this._selectedOptionFontColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectedOptionFontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.selectedOptionFontColor0Attribute((this._selectedOptionFontColor_0_0value as ResourceColor | undefined));
                    this._selectedOptionFontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectedOptionFontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectedOptionFontColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.selectedOptionFontColor0Attribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._optionBgColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._optionBgColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.optionBgColor0Attribute((this._optionBgColor_0_0value as ResourceColor | undefined));
                    this._optionBgColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._optionBgColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._optionBgColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.optionBgColor0Attribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._optionFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._optionFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.optionFont0Attribute((this._optionFont_0_0value as Font | undefined));
                    this._optionFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._optionFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._optionFont_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.optionFont0Attribute((undefined as Font | undefined));
                }
            }
        }
        if (this._optionFontColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._optionFontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.optionFontColor0Attribute((this._optionFontColor_0_0value as ResourceColor | undefined));
                    this._optionFontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._optionFontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._optionFontColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.optionFontColor0Attribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._onSelect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onSelect_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onSelect1Attribute((this._onSelect_0_0value as OnSelectCallback | undefined));
                    this._onSelect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onSelect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onSelect_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onSelect1Attribute((undefined as OnSelectCallback | undefined));
                }
            }
        }
        if (this._space_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._space_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.space0Attribute((this._space_0_0value as Length | undefined));
                    this._space_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._space_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._space_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.space0Attribute((undefined as Length | undefined));
                }
            }
        }
        if (this._arrowPosition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._arrowPosition_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.arrowPosition0Attribute((this._arrowPosition_0_0value as ArrowPosition | undefined));
                    this._arrowPosition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._arrowPosition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._arrowPosition_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.arrowPosition0Attribute((undefined as ArrowPosition | undefined));
                }
            }
        }
        if (this._optionWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._optionWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.optionWidth1Attribute((this._optionWidth_0_0value as Dimension | OptionWidthMode | undefined));
                    this._optionWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._optionWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._optionWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.optionWidth1Attribute((undefined as Dimension | OptionWidthMode | undefined));
                }
            }
        }
        if (this._optionHeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._optionHeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.optionHeight1Attribute((this._optionHeight_0_0value as Dimension | undefined));
                    this._optionHeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._optionHeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._optionHeight_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.optionHeight1Attribute((undefined as Dimension | undefined));
                }
            }
        }
        if (this._menuBackgroundColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._menuBackgroundColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.menuBackgroundColor1Attribute((this._menuBackgroundColor_0_0value as ResourceColor | undefined));
                    this._menuBackgroundColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._menuBackgroundColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._menuBackgroundColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.menuBackgroundColor1Attribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._menuBackgroundBlurStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._menuBackgroundBlurStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.menuBackgroundBlurStyle1Attribute((this._menuBackgroundBlurStyle_0_0value as BlurStyle | undefined));
                    this._menuBackgroundBlurStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._menuBackgroundBlurStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._menuBackgroundBlurStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.menuBackgroundBlurStyle1Attribute((undefined as BlurStyle | undefined));
                }
            }
        }
        if (this._controlSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._controlSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.controlSize1Attribute((this._controlSize_0_0value as ControlSize | undefined));
                    this._controlSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._controlSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._controlSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.controlSize1Attribute((undefined as ControlSize | undefined));
                }
            }
        }
        if (this._divider_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._divider_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.dividerAttribute((this._divider_0_0value as DividerOptions | undefined));
                    this._divider_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._divider_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._divider_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.dividerAttribute((undefined as DividerOptions | undefined));
                }
            }
        }
        if (this._textModifier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._textModifier_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.textModifierAttribute((this._textModifier_0_0value as TextModifier | undefined));
                    this._textModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._textModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._textModifier_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.textModifierAttribute((undefined as TextModifier | undefined));
                }
            }
        }
        if (this._arrowModifier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._arrowModifier_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.arrowModifierAttribute((this._arrowModifier_0_0value as SymbolGlyphModifier | undefined));
                    this._arrowModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._arrowModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._arrowModifier_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.arrowModifierAttribute((undefined as SymbolGlyphModifier | undefined));
                }
            }
        }
        if (this._optionTextModifier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._optionTextModifier_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.optionTextModifierAttribute((this._optionTextModifier_0_0value as TextModifier | undefined));
                    this._optionTextModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._optionTextModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._optionTextModifier_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.optionTextModifierAttribute((undefined as TextModifier | undefined));
                }
            }
        }
        if (this._selectedOptionTextModifier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectedOptionTextModifier_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.selectedOptionTextModifierAttribute((this._selectedOptionTextModifier_0_0value as TextModifier | undefined));
                    this._selectedOptionTextModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectedOptionTextModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectedOptionTextModifier_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.selectedOptionTextModifierAttribute((undefined as TextModifier | undefined));
                }
            }
        }
        if (this._dividerStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._dividerStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.dividerStyleAttribute((this._dividerStyle_0_0value as DividerStyleOptions | undefined));
                    this._dividerStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._dividerStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._dividerStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.dividerStyleAttribute((undefined as DividerStyleOptions | undefined));
                }
            }
        }
        if (this._avoidance_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._avoidance_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.avoidanceAttribute((this._avoidance_0_0value as AvoidanceMode | undefined));
                    this._avoidance_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._avoidance_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._avoidance_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.avoidanceAttribute((undefined as AvoidanceMode | undefined));
                }
            }
        }
        if (this._menuOutline_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._menuOutline_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.menuOutlineAttribute((this._menuOutline_0_0value as MenuOutlineOptions | undefined));
                    this._menuOutline_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._menuOutline_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._menuOutline_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.menuOutlineAttribute((undefined as MenuOutlineOptions | undefined));
                }
            }
        }
        if (this._menuAlign_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._menuAlign_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.menuAlign0Attribute((this._menuAlign_0_0value as MenuAlignType | undefined), (this._menuAlign_0_1value as Offset | undefined));
                    this._menuAlign_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._menuAlign_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._menuAlign_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.menuAlign0Attribute((undefined as MenuAlignType | undefined), (undefined as Offset | undefined));
                }
            }
        }
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
        if (!(value instanceof SelectModifier)) {
            return
        }
        const modifier = value as SelectModifier;
        if (modifier._selected_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selected_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selected(modifier._selected_0_0value);
                    break;
                }
                default: {
                    this.selected((undefined as number | Resource | Bindable<number> | Bindable<Resource> | undefined));
                }
            }
        }
        if (modifier._value_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._value_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.value(modifier._value_0_0value);
                    break;
                }
                default: {
                    this.value((undefined as ResourceStr | Bindable<string> | Bindable<Resource> | undefined));
                }
            }
        }
        if (modifier._font_0_flag != AttributeUpdaterFlag.INITIAL)
        {
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
        if (modifier._fontColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontColor(modifier._fontColor_0_0value);
                    break;
                }
                default: {
                    this.fontColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._selectedOptionBgColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selectedOptionBgColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selectedOptionBgColor(modifier._selectedOptionBgColor_0_0value);
                    break;
                }
                default: {
                    this.selectedOptionBgColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._selectedOptionFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selectedOptionFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selectedOptionFont(modifier._selectedOptionFont_0_0value);
                    break;
                }
                default: {
                    this.selectedOptionFont((undefined as Font | undefined));
                }
            }
        }
        if (modifier._selectedOptionFontColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selectedOptionFontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selectedOptionFontColor(modifier._selectedOptionFontColor_0_0value);
                    break;
                }
                default: {
                    this.selectedOptionFontColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._optionBgColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._optionBgColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.optionBgColor(modifier._optionBgColor_0_0value);
                    break;
                }
                default: {
                    this.optionBgColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._optionFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._optionFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.optionFont(modifier._optionFont_0_0value);
                    break;
                }
                default: {
                    this.optionFont((undefined as Font | undefined));
                }
            }
        }
        if (modifier._optionFontColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._optionFontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.optionFontColor(modifier._optionFontColor_0_0value);
                    break;
                }
                default: {
                    this.optionFontColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._onSelect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onSelect_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onSelect(modifier._onSelect_0_0value);
                    break;
                }
                default: {
                    this.onSelect((undefined as OnSelectCallback | undefined));
                }
            }
        }
        if (modifier._space_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._space_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.space(modifier._space_0_0value);
                    break;
                }
                default: {
                    this.space((undefined as Length | undefined));
                }
            }
        }
        if (modifier._arrowPosition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._arrowPosition_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.arrowPosition(modifier._arrowPosition_0_0value);
                    break;
                }
                default: {
                    this.arrowPosition((undefined as ArrowPosition | undefined));
                }
            }
        }
        if (modifier._optionWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._optionWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.optionWidth(modifier._optionWidth_0_0value);
                    break;
                }
                default: {
                    this.optionWidth((undefined as Dimension | OptionWidthMode | undefined));
                }
            }
        }
        if (modifier._optionHeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._optionHeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.optionHeight(modifier._optionHeight_0_0value);
                    break;
                }
                default: {
                    this.optionHeight((undefined as Dimension | undefined));
                }
            }
        }
        if (modifier._menuBackgroundColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._menuBackgroundColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.menuBackgroundColor(modifier._menuBackgroundColor_0_0value);
                    break;
                }
                default: {
                    this.menuBackgroundColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._menuBackgroundBlurStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._menuBackgroundBlurStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.menuBackgroundBlurStyle(modifier._menuBackgroundBlurStyle_0_0value);
                    break;
                }
                default: {
                    this.menuBackgroundBlurStyle((undefined as BlurStyle | undefined));
                }
            }
        }
        if (modifier._controlSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._controlSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.controlSize(modifier._controlSize_0_0value);
                    break;
                }
                default: {
                    this.controlSize((undefined as ControlSize | undefined));
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
                    this.divider((undefined as DividerOptions | undefined));
                }
            }
        }
        if (modifier._textModifier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._textModifier_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.textModifier(modifier._textModifier_0_0value);
                    break;
                }
                default: {
                    this.textModifier((undefined as TextModifier | undefined));
                }
            }
        }
        if (modifier._arrowModifier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._arrowModifier_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.arrowModifier(modifier._arrowModifier_0_0value);
                    break;
                }
                default: {
                    this.arrowModifier((undefined as SymbolGlyphModifier | undefined));
                }
            }
        }
        if (modifier._optionTextModifier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._optionTextModifier_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.optionTextModifier(modifier._optionTextModifier_0_0value);
                    break;
                }
                default: {
                    this.optionTextModifier((undefined as TextModifier | undefined));
                }
            }
        }
        if (modifier._selectedOptionTextModifier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selectedOptionTextModifier_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selectedOptionTextModifier(modifier._selectedOptionTextModifier_0_0value);
                    break;
                }
                default: {
                    this.selectedOptionTextModifier((undefined as TextModifier | undefined));
                }
            }
        }
        if (modifier._dividerStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._dividerStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.dividerStyle(modifier._dividerStyle_0_0value);
                    break;
                }
                default: {
                    this.dividerStyle((undefined as DividerStyleOptions | undefined));
                }
            }
        }
        if (modifier._avoidance_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._avoidance_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.avoidance(modifier._avoidance_0_0value);
                    break;
                }
                default: {
                    this.avoidance((undefined as AvoidanceMode | undefined));
                }
            }
        }
        if (modifier._menuOutline_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._menuOutline_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.menuOutline(modifier._menuOutline_0_0value);
                    break;
                }
                default: {
                    this.menuOutline((undefined as MenuOutlineOptions | undefined));
                }
            }
        }
        if (modifier._menuAlign_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._menuAlign_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.menuAlign(modifier._menuAlign_0_0value, modifier._menuAlign_0_1value);
                    break;
                }
                default: {
                    this.menuAlign((undefined as MenuAlignType | undefined), (undefined as Offset | undefined | undefined));
                }
            }
        }
    }
    selected(value: number | Resource | Bindable<number> | Bindable<Resource> | undefined): this {
        if (((this._selected_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._selected_0_flag = AttributeUpdaterFlag.UPDATE
            this._selected_0_0value = value
        } else
        {
            this._selected_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    value(value: ResourceStr | Bindable<string> | Bindable<Resource> | undefined): this {
        if (((this._value_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._value_0_flag = AttributeUpdaterFlag.UPDATE
            this._value_0_0value = value
        } else
        {
            this._value_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    font(value: Font | undefined): this {
        if (((this._font_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._font_0_flag = AttributeUpdaterFlag.UPDATE
            this._font_0_0value = value
        } else
        {
            this._font_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontColor(value: ResourceColor | undefined): this {
        if (((this._fontColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fontColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontColor_0_0value = value
        } else
        {
            this._fontColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selectedOptionBgColor(value: ResourceColor | undefined): this {
        if (((this._selectedOptionBgColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._selectedOptionBgColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectedOptionBgColor_0_0value = value
        } else
        {
            this._selectedOptionBgColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selectedOptionFont(value: Font | undefined): this {
        if (((this._selectedOptionFont_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._selectedOptionFont_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectedOptionFont_0_0value = value
        } else
        {
            this._selectedOptionFont_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selectedOptionFontColor(value: ResourceColor | undefined): this {
        if (((this._selectedOptionFontColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._selectedOptionFontColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectedOptionFontColor_0_0value = value
        } else
        {
            this._selectedOptionFontColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    optionBgColor(value: ResourceColor | undefined): this {
        if (((this._optionBgColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._optionBgColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._optionBgColor_0_0value = value
        } else
        {
            this._optionBgColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    optionFont(value: Font | undefined): this {
        if (((this._optionFont_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._optionFont_0_flag = AttributeUpdaterFlag.UPDATE
            this._optionFont_0_0value = value
        } else
        {
            this._optionFont_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    optionFontColor(value: ResourceColor | undefined): this {
        if (((this._optionFontColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._optionFontColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._optionFontColor_0_0value = value
        } else
        {
            this._optionFontColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onSelect(value: OnSelectCallback | undefined): this {
        if (((this._onSelect_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onSelect_0_flag = AttributeUpdaterFlag.UPDATE
            this._onSelect_0_0value = value
        } else
        {
            this._onSelect_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    space(value: Length | undefined): this {
        if (((this._space_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._space_0_flag = AttributeUpdaterFlag.UPDATE
            this._space_0_0value = value
        } else
        {
            this._space_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    arrowPosition(value: ArrowPosition | undefined): this {
        if (((this._arrowPosition_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._arrowPosition_0_flag = AttributeUpdaterFlag.UPDATE
            this._arrowPosition_0_0value = value
        } else
        {
            this._arrowPosition_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    optionWidth(value: Dimension | OptionWidthMode | undefined): this {
        if (((this._optionWidth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._optionWidth_0_flag = AttributeUpdaterFlag.UPDATE
            this._optionWidth_0_0value = value
        } else
        {
            this._optionWidth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    optionHeight(value: Dimension | undefined): this {
        if (((this._optionHeight_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._optionHeight_0_flag = AttributeUpdaterFlag.UPDATE
            this._optionHeight_0_0value = value
        } else
        {
            this._optionHeight_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    menuBackgroundColor(value: ResourceColor | undefined): this {
        if (((this._menuBackgroundColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._menuBackgroundColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._menuBackgroundColor_0_0value = value
        } else
        {
            this._menuBackgroundColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    menuBackgroundBlurStyle(value: BlurStyle | undefined): this {
        if (((this._menuBackgroundBlurStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._menuBackgroundBlurStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._menuBackgroundBlurStyle_0_0value = value
        } else
        {
            this._menuBackgroundBlurStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    controlSize(value: ControlSize | undefined): this {
        if (((this._controlSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._controlSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._controlSize_0_0value = value
        } else
        {
            this._controlSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    divider(value: DividerOptions | undefined): this {
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
    textModifier(value: TextModifier | undefined): this {
        if (((this._textModifier_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._textModifier_0_flag = AttributeUpdaterFlag.UPDATE
            this._textModifier_0_0value = value
        } else
        {
            this._textModifier_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    arrowModifier(value: SymbolGlyphModifier | undefined): this {
        if (((this._arrowModifier_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._arrowModifier_0_flag = AttributeUpdaterFlag.UPDATE
            this._arrowModifier_0_0value = value
        } else
        {
            this._arrowModifier_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    optionTextModifier(value: TextModifier | undefined): this {
        if (((this._optionTextModifier_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._optionTextModifier_0_flag = AttributeUpdaterFlag.UPDATE
            this._optionTextModifier_0_0value = value
        } else
        {
            this._optionTextModifier_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selectedOptionTextModifier(value: TextModifier | undefined): this {
        if (((this._selectedOptionTextModifier_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._selectedOptionTextModifier_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectedOptionTextModifier_0_0value = value
        } else
        {
            this._selectedOptionTextModifier_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    dividerStyle(value: DividerStyleOptions | undefined): this {
        if (((this._dividerStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._dividerStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._dividerStyle_0_0value = value
        } else
        {
            this._dividerStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    avoidance(value: AvoidanceMode | undefined): this {
        if (((this._avoidance_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._avoidance_0_flag = AttributeUpdaterFlag.UPDATE
            this._avoidance_0_0value = value
        } else
        {
            this._avoidance_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    menuOutline(value: MenuOutlineOptions | undefined): this {
        if (((this._menuOutline_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._menuOutline_0_flag = AttributeUpdaterFlag.UPDATE
            this._menuOutline_0_0value = value
        } else
        {
            this._menuOutline_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    menuAlign(alignType: MenuAlignType | undefined, offset?: Offset): this {
        if (((this._menuAlign_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._menuAlign_0_flag = AttributeUpdaterFlag.UPDATE
            this._menuAlign_0_0value = alignType
            this._menuAlign_0_1value = offset
        } else
        {
            this._menuAlign_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
}

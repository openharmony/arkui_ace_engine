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
 
import { AttributeModifier } from 'arkui/component/common'
import { MenuItemAttribute } from 'arkui/component/menuItem'
 
import { AttributeUpdaterFlag, CommonMethodModifier } from './CommonMethodModifier';
import { Font, ResourceStr, ResourceColor } from './component/units';
import { PeerNode } from './PeerNode';
import { ArkMenuItemPeer } from './component/menuItem';
import { SymbolGlyphModifier } from "./SymbolGlyphModifier"
export class MenuItemModifier extends CommonMethodModifier implements MenuItemAttribute, AttributeModifier<MenuItemAttribute> {
    applyNormalAttribute(instance: MenuItemAttribute): void { }
    applyPressedAttribute(instance: MenuItemAttribute): void { }
    applyFocusedAttribute(instance: MenuItemAttribute): void { }
    applyDisabledAttribute(instance: MenuItemAttribute): void { }
    applySelectedAttribute(instance: MenuItemAttribute): void { }
    _selected_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selected_0_0value?: boolean | undefined
    _selectIcon_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectIcon_0_0value?:boolean | ResourceStr | SymbolGlyphModifier | undefined
    _contentFont_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _contentFont_0_0value?:Font | undefined
    _contentFontColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _contentFontColor_0_0value?:ResourceColor | undefined
    _labelFont_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _labelFont_0_0value?:Font | undefined
    _labelFontColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _labelFontColor_0_0value?:ResourceColor | undefined
    _onChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onChange_0_0value?:((selected: boolean) => void) | undefined
 
    public selected(value: boolean | undefined): this {
        if (((this._selected_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._selected_0_flag = AttributeUpdaterFlag.UPDATE
            this._selected_0_0value = value
        } else {
            this._selected_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public selectIcon(value: boolean | ResourceStr | SymbolGlyphModifier | undefined): this {
        if (((this._selectIcon_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._selectIcon_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectIcon_0_0value = value
        } else {
            this._selectIcon_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public contentFont(value: Font | undefined): this {
        if (((this._contentFont_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._contentFont_0_flag = AttributeUpdaterFlag.UPDATE
            this._contentFont_0_0value = value
        } else {
            this._contentFont_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public contentFontColor(value: ResourceColor | undefined): this {
        if (((this._contentFontColor_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._contentFontColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._contentFontColor_0_0value = value
        } else {
            this._contentFontColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public labelFont(value: Font | undefined): this {
        if (((this._labelFont_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._labelFont_0_flag = AttributeUpdaterFlag.UPDATE
            this._labelFont_0_0value = value
        } else {
            this._labelFont_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public labelFontColor(value: ResourceColor | undefined): this {
        if (((this._labelFontColor_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._labelFontColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._labelFontColor_0_0value = value
        } else {
            this._labelFontColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public onChange(value: ((selected: boolean) => void) | undefined): this {
        if (((this._onChange_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._onChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onChange_0_0value = value
        } else {
            this._onChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
 
    applyModifierPatch(value: PeerNode): void {
        super.applyModifierPatch(value)
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
    }
}
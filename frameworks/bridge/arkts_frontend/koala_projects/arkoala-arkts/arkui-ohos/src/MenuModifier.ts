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
import { MenuAttribute, SubMenuExpandingMode } from 'arkui/component/menu'
 
import { AttributeUpdaterFlag, CommonMethodModifier } from './CommonMethodModifier';
import { ResourceColor, Font, Dimension, BorderRadiuses, DividerStyleOptions, Length } from './component/units';
import { PeerNode } from './PeerNode';
import { ArkMenuPeer } from './component/menu';
import { SymbolGlyphModifier } from "./SymbolGlyphModifier"
 
export class MenuModifier extends CommonMethodModifier implements MenuAttribute, AttributeModifier<MenuAttribute> {
    applyNormalAttribute(instance: MenuAttribute): void { }
    applyPressedAttribute(instance: MenuAttribute): void { }
    applyFocusedAttribute(instance: MenuAttribute): void { }
    applyDisabledAttribute(instance: MenuAttribute): void { }
    applySelectedAttribute(instance: MenuAttribute): void { }
    
    applyModifierPatch(value: PeerNode): void {
        super.applyModifierPatch(value)
        const peerNode: ArkMenuPeer = value as ArkMenuPeer
        if (this._font_0_flag !== AttributeUpdaterFlag.INITIAL) {
            switch (this._font_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peerNode.fontAttribute((this._font_0_0value as Font | undefined))
                    this._font_0_flag = AttributeUpdaterFlag.RESET
                    break
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._font_0_flag = AttributeUpdaterFlag.RESET
                    break
                }
                default: {
                    this._font_0_flag = AttributeUpdaterFlag.INITIAL
                    peerNode.fontAttribute(undefined)
                }
            }
        }
        if (this._fontColor_0_flag !== AttributeUpdaterFlag.INITIAL) {
            switch (this._fontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peerNode.fontColorAttribute((this._fontColor_0_0value as ResourceColor | undefined))
                    this._fontColor_0_flag = AttributeUpdaterFlag.RESET
                    break
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontColor_0_flag = AttributeUpdaterFlag.RESET
                    break
                }
                default: {
                    this._fontColor_0_flag = AttributeUpdaterFlag.INITIAL
                    peerNode.fontColorAttribute(undefined)
                }
            }
        }
        if (this._radius_0_flag !== AttributeUpdaterFlag.INITIAL) {
            switch (this._radius_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peerNode.radiusAttribute((this._radius_0_0value as Dimension | BorderRadiuses | undefined))
                    this._radius_0_flag = AttributeUpdaterFlag.RESET
                    break
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._radius_0_flag = AttributeUpdaterFlag.RESET
                    break
                }
                default: {
                    this._radius_0_flag = AttributeUpdaterFlag.INITIAL
                    peerNode.radiusAttribute(undefined)
                }
            }
        }
        if (this._menuItemDivider_0_flag !== AttributeUpdaterFlag.INITIAL) {
            switch (this._menuItemDivider_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peerNode.menuItemDividerAttribute((this._menuItemDivider_0_0value as DividerStyleOptions | undefined))
                    this._menuItemDivider_0_flag = AttributeUpdaterFlag.RESET
                    break
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._menuItemDivider_0_flag = AttributeUpdaterFlag.RESET
                    break
                }
                default: {
                    this._menuItemDivider_0_flag = AttributeUpdaterFlag.INITIAL
                    peerNode.menuItemDividerAttribute(undefined)
                }
            }
        }
        if (this._menuItemGroupDivider_0_flag !== AttributeUpdaterFlag.INITIAL) {
            switch (this._menuItemGroupDivider_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peerNode.menuItemGroupDividerAttribute((this._menuItemGroupDivider_0_0value as DividerStyleOptions | undefined))
                    this._menuItemGroupDivider_0_flag = AttributeUpdaterFlag.RESET
                    break
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._menuItemGroupDivider_0_flag = AttributeUpdaterFlag.RESET
                    break
                }
                default: {
                    this._menuItemGroupDivider_0_flag = AttributeUpdaterFlag.INITIAL
                    peerNode.menuItemGroupDividerAttribute(undefined)
                }
            }
        }
        if (this._subMenuExpandingMode_0_flag !== AttributeUpdaterFlag.INITIAL) {
            switch (this._subMenuExpandingMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peerNode.subMenuExpandingModeAttribute((this._subMenuExpandingMode_0_0value as SubMenuExpandingMode | undefined))
                    this._subMenuExpandingMode_0_flag = AttributeUpdaterFlag.RESET
                    break
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._subMenuExpandingMode_0_flag = AttributeUpdaterFlag.RESET
                    break
                }
                default: {
                    this._subMenuExpandingMode_0_flag = AttributeUpdaterFlag.INITIAL
                    peerNode.subMenuExpandingModeAttribute(undefined)
                }
            }
        }
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
        if (value instanceof MenuModifier) {
            const modifier = value as MenuModifier;
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
            if (modifier._radius_0_flag != AttributeUpdaterFlag.INITIAL)
            {
                switch (modifier._radius_0_flag) {
                    case AttributeUpdaterFlag.UPDATE:
                    case AttributeUpdaterFlag.SKIP: {
                        this.radius(modifier._radius_0_0value);
                        break;
                    }
                    default: {
                        this.radius((undefined as Dimension | BorderRadiuses | undefined));
                    }
                }
            }
            if (modifier._menuItemDivider_0_flag != AttributeUpdaterFlag.INITIAL)
            {
                switch (modifier._menuItemDivider_0_flag) {
                    case AttributeUpdaterFlag.UPDATE:
                    case AttributeUpdaterFlag.SKIP: {
                        this.menuItemDivider(modifier._menuItemDivider_0_0value);
                        break;
                    }
                    default: {
                        this.menuItemDivider((undefined as DividerStyleOptions | undefined));
                    }
                }
            }
            if (modifier._menuItemGroupDivider_0_flag != AttributeUpdaterFlag.INITIAL)
            {
                switch (modifier._menuItemGroupDivider_0_flag) {
                    case AttributeUpdaterFlag.UPDATE:
                    case AttributeUpdaterFlag.SKIP: {
                        this.menuItemGroupDivider(modifier._menuItemGroupDivider_0_0value);
                        break;
                    }
                    default: {
                        this.menuItemGroupDivider((undefined as DividerStyleOptions | undefined));
                    }
                }
            }
            if (modifier._subMenuExpandingMode_0_flag != AttributeUpdaterFlag.INITIAL)
            {
                switch (modifier._subMenuExpandingMode_0_flag) {
                    case AttributeUpdaterFlag.UPDATE:
                    case AttributeUpdaterFlag.SKIP: {
                        this.subMenuExpandingMode(modifier._subMenuExpandingMode_0_0value);
                        break;
                    }
                    default: {
                        this.subMenuExpandingMode((undefined as SubMenuExpandingMode | undefined));
                    }
                }
            }
        }
    }
 
    _font_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _font_0_0value?: Font | undefined
    _fontColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontColor_0_0value?: ResourceColor | undefined
    _radius_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _radius_0_0value?: Dimension | BorderRadiuses | undefined
    _menuItemDivider_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _menuItemDivider_0_0value?: DividerStyleOptions | undefined
    _menuItemGroupDivider_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _menuItemGroupDivider_0_0value?: DividerStyleOptions | undefined
    _subMenuExpandingMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _subMenuExpandingMode_0_0value?: SubMenuExpandingMode | undefined
    _subMenuExpandSymbol_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _subMenuExpandSymbol_0_0value?: SymbolGlyphModifier | undefined
 
    public font(value: Font | undefined): this {
        if (((this._font_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._font_0_flag = AttributeUpdaterFlag.UPDATE
            this._font_0_0value = value
        } else {
            this._font_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public fontColor(value: ResourceColor | undefined): this {
        if (((this._fontColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            this._fontColor_0_0value !== value || !Type.of(value).isPrimitive()) {
            this._fontColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontColor_0_0value = value
        } else {
            this._fontColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public radius(value: Dimension | BorderRadiuses | undefined): this {
        if (((this._radius_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._radius_0_flag = AttributeUpdaterFlag.UPDATE
            this._radius_0_0value = value
        } else {
            this._radius_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public menuItemDivider(value: DividerStyleOptions | undefined): this {
        if (((this._menuItemDivider_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._menuItemDivider_0_flag = AttributeUpdaterFlag.UPDATE
            this._menuItemDivider_0_0value = value
        } else {
            this._menuItemDivider_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public menuItemGroupDivider(value: DividerStyleOptions | undefined): this {
        if (((this._menuItemGroupDivider_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._menuItemGroupDivider_0_flag = AttributeUpdaterFlag.UPDATE
            this._menuItemGroupDivider_0_0value = value
        } else {
            this._menuItemGroupDivider_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public subMenuExpandingMode(value: SubMenuExpandingMode | undefined): this {
        if (((this._subMenuExpandingMode_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._subMenuExpandingMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._subMenuExpandingMode_0_0value = value
        } else {
            this._subMenuExpandingMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public subMenuExpandSymbol(value: SymbolGlyphModifier | undefined): this {
        if (((this._subMenuExpandSymbol_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._subMenuExpandSymbol_0_flag = AttributeUpdaterFlag.UPDATE
            this._subMenuExpandSymbol_0_0value = value
        } else {
            this._subMenuExpandSymbol_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
}
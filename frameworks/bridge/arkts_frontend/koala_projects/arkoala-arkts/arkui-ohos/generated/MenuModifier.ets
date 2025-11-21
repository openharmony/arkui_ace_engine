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

import { CommonMethodModifier } from "./CommonMethodModifier"
import { ModifierState } from './CommonModifier'
import { AttributeModifier } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkMenuPeer, SubMenuExpandingMode, MenuAttribute } from "./component/menu"
import { int32 } from "@koalaui/common"
import { CommonMethod } from "./component/common"
import { Font, ResourceColor, Dimension, BorderRadiuses, DividerStyleOptions } from "./component/units"
import { Color } from "./component/enums"
import { Resource } from "global.resource"
export class MenuModifier extends CommonMethodModifier implements MenuAttribute,AttributeModifier<MenuAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: MenuAttribute): void { }
    applyPressedAttribute(instance: MenuAttribute): void { }
    applyFocusedAttribute(instance: MenuAttribute): void { }
    applyDisabledAttribute(instance: MenuAttribute): void { }
    applySelectedAttribute(instance: MenuAttribute): void { }
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
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkMenuPeer;
        if (this._font_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._font_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontAttribute((this._font_0_0value as Font | undefined));
                    this._font_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._font_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._font_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontAttribute((undefined as Font | undefined));
                }
            }
        }
        if (this._fontColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontColorAttribute((this._fontColor_0_0value as ResourceColor | undefined));
                    this._fontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._radius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._radius_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRadiusAttribute((this._radius_0_0value as Dimension | BorderRadiuses | undefined));
                    this._radius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._radius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._radius_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRadiusAttribute((undefined as Dimension | BorderRadiuses | undefined));
                }
            }
        }
        if (this._menuItemDivider_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._menuItemDivider_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMenuItemDividerAttribute((this._menuItemDivider_0_0value as DividerStyleOptions | undefined));
                    this._menuItemDivider_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._menuItemDivider_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._menuItemDivider_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMenuItemDividerAttribute((undefined as DividerStyleOptions | undefined));
                }
            }
        }
        if (this._menuItemGroupDivider_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._menuItemGroupDivider_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMenuItemGroupDividerAttribute((this._menuItemGroupDivider_0_0value as DividerStyleOptions | undefined));
                    this._menuItemGroupDivider_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._menuItemGroupDivider_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._menuItemGroupDivider_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMenuItemGroupDividerAttribute((undefined as DividerStyleOptions | undefined));
                }
            }
        }
        if (this._subMenuExpandingMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._subMenuExpandingMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSubMenuExpandingModeAttribute((this._subMenuExpandingMode_0_0value as SubMenuExpandingMode | undefined));
                    this._subMenuExpandingMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._subMenuExpandingMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._subMenuExpandingMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSubMenuExpandingModeAttribute((undefined as SubMenuExpandingMode | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: MenuModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
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
    radius(value: Dimension | BorderRadiuses | undefined): this {
        if (((this._radius_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._radius_0_flag = AttributeUpdaterFlag.UPDATE
            this._radius_0_0value = value
        } else
        {
            this._radius_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    menuItemDivider(value: DividerStyleOptions | undefined): this {
        if (((this._menuItemDivider_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._menuItemDivider_0_flag = AttributeUpdaterFlag.UPDATE
            this._menuItemDivider_0_0value = value
        } else
        {
            this._menuItemDivider_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    menuItemGroupDivider(value: DividerStyleOptions | undefined): this {
        if (((this._menuItemGroupDivider_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._menuItemGroupDivider_0_flag = AttributeUpdaterFlag.UPDATE
            this._menuItemGroupDivider_0_0value = value
        } else
        {
            this._menuItemGroupDivider_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    subMenuExpandingMode(value: SubMenuExpandingMode | undefined): this {
        if (((this._subMenuExpandingMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._subMenuExpandingMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._subMenuExpandingMode_0_0value = value
        } else
        {
            this._subMenuExpandingMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<MenuAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

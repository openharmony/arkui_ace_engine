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
import { AttributeModifier, extractors } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkMenuItemPeer, MenuItemAttribute } from "./component/menuItem"
import { int32 } from "@koalaui/common"
import { CommonMethod, Bindable } from "./component/common"
import { ResourceStr, Font, ResourceColor } from "./component/units"
import { Resource } from "global.resource"
import { SymbolGlyphModifier } from "arkui.SymbolGlyphModifier"
import { Color } from "./component/enums"
export class MenuItemModifier extends CommonMethodModifier implements MenuItemAttribute,AttributeModifier<MenuItemAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: MenuItemAttribute): void { }
    applyPressedAttribute(instance: MenuItemAttribute): void { }
    applyFocusedAttribute(instance: MenuItemAttribute): void { }
    applyDisabledAttribute(instance: MenuItemAttribute): void { }
    applySelectedAttribute(instance: MenuItemAttribute): void { }
    _selected_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selected_0_0value?: boolean | Bindable<boolean> | undefined
    _selectIcon_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectIcon_0_0value?: boolean | ResourceStr | SymbolGlyphModifier | undefined
    _onChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onChange_0_0value?: ((selected: boolean) => void) | undefined
    _contentFont_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _contentFont_0_0value?: Font | undefined
    _contentFontColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _contentFontColor_0_0value?: ResourceColor | undefined
    _labelFont_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _labelFont_0_0value?: Font | undefined
    _labelFontColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _labelFontColor_0_0value?: ResourceColor | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkMenuItemPeer;
        if (this._selected_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selected_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSelectedAttribute((this._selected_0_0value as boolean | Bindable<boolean> | undefined));
                    this._selected_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selected_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selected_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSelectedAttribute((undefined as boolean | Bindable<boolean> | undefined));
                }
            }
        }
        if (this._selectIcon_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectIcon_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSelectIconAttribute((this._selectIcon_0_0value as boolean | ResourceStr | SymbolGlyphModifier | undefined));
                    this._selectIcon_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectIcon_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectIcon_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSelectIconAttribute((undefined as boolean | ResourceStr | SymbolGlyphModifier | undefined));
                }
            }
        }
        if (this._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as ((selected: boolean) => void) | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnChangeAttribute((undefined as ((selected: boolean) => void) | undefined));
                }
            }
        }
        if (this._contentFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._contentFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setContentFontAttribute((this._contentFont_0_0value as Font | undefined));
                    this._contentFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._contentFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._contentFont_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setContentFontAttribute((undefined as Font | undefined));
                }
            }
        }
        if (this._contentFontColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._contentFontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setContentFontColorAttribute((this._contentFontColor_0_0value as ResourceColor | undefined));
                    this._contentFontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._contentFontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._contentFontColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setContentFontColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._labelFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._labelFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setLabelFontAttribute((this._labelFont_0_0value as Font | undefined));
                    this._labelFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._labelFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._labelFont_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setLabelFontAttribute((undefined as Font | undefined));
                }
            }
        }
        if (this._labelFontColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._labelFontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setLabelFontColorAttribute((this._labelFontColor_0_0value as ResourceColor | undefined));
                    this._labelFontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._labelFontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._labelFontColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setLabelFontColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: MenuItemModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._selected_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selected_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selected(modifier._selected_0_0value);
                    break;
                }
                default: {
                    this.selected((undefined as boolean | Bindable<boolean> | undefined));
                }
            }
        }
        if (modifier._selectIcon_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selectIcon_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selectIcon(modifier._selectIcon_0_0value);
                    break;
                }
                default: {
                    this.selectIcon((undefined as boolean | ResourceStr | SymbolGlyphModifier | undefined));
                }
            }
        }
        if (modifier._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onChange(modifier._onChange_0_0value);
                    break;
                }
                default: {
                    this.onChange((undefined as ((selected: boolean) => void) | undefined));
                }
            }
        }
        if (modifier._contentFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._contentFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.contentFont(modifier._contentFont_0_0value);
                    break;
                }
                default: {
                    this.contentFont((undefined as Font | undefined));
                }
            }
        }
        if (modifier._contentFontColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._contentFontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.contentFontColor(modifier._contentFontColor_0_0value);
                    break;
                }
                default: {
                    this.contentFontColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._labelFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._labelFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.labelFont(modifier._labelFont_0_0value);
                    break;
                }
                default: {
                    this.labelFont((undefined as Font | undefined));
                }
            }
        }
        if (modifier._labelFontColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._labelFontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.labelFontColor(modifier._labelFontColor_0_0value);
                    break;
                }
                default: {
                    this.labelFontColor((undefined as ResourceColor | undefined));
                }
            }
        }
    }
    selected(value: boolean | Bindable<boolean> | undefined): this {
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
    selectIcon(value: boolean | ResourceStr | SymbolGlyphModifier | undefined): this {
        if (((this._selectIcon_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._selectIcon_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectIcon_0_0value = value
        } else
        {
            this._selectIcon_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onChange(value: ((selected: boolean) => void) | undefined): this {
        if (((this._onChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onChange_0_0value = value
        } else
        {
            this._onChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    contentFont(value: Font | undefined): this {
        if (((this._contentFont_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._contentFont_0_flag = AttributeUpdaterFlag.UPDATE
            this._contentFont_0_0value = value
        } else
        {
            this._contentFont_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    contentFontColor(value: ResourceColor | undefined): this {
        if (((this._contentFontColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._contentFontColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._contentFontColor_0_0value = value
        } else
        {
            this._contentFontColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    labelFont(value: Font | undefined): this {
        if (((this._labelFont_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._labelFont_0_flag = AttributeUpdaterFlag.UPDATE
            this._labelFont_0_0value = value
        } else
        {
            this._labelFont_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    labelFontColor(value: ResourceColor | undefined): this {
        if (((this._labelFontColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._labelFontColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._labelFontColor_0_0value = value
        } else
        {
            this._labelFontColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<MenuItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

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
import { AttributeModifier, extractors } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkMenuItemPeer, MenuItemAttribute } from './component/menuItem'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod, Bindable } from './component/common'
import { ResourceStr as arkui_component_units_ResourceStr, Resource as arkui_component_units_Resource, Font as arkui_component_units_Font, ResourceColor } from './component/units'
import { Resource as global_resource_Resource } from 'global.resource'
import { SymbolGlyphModifier } from '@arkui.SymbolGlyphModifier'
import { Color as arkui_component_enums_Color } from './component/enums'
export class MenuItemModifier extends CommonMethodModifier implements MenuItemAttribute,AttributeModifier<MenuItemAttribute> {
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
    applyNormalAttribute(instance: MenuItemAttribute): void { }
    applyPressedAttribute(instance: MenuItemAttribute): void { }
    applyFocusedAttribute(instance: MenuItemAttribute): void { }
    applyDisabledAttribute(instance: MenuItemAttribute): void { }
    applySelectedAttribute(instance: MenuItemAttribute): void { }
    public _selected_0_0value?: boolean | Bindable<boolean> | undefined
    public _selectIcon_0_0value?: boolean | arkui_component_units_ResourceStr | SymbolGlyphModifier | undefined
    public _onChange_0_0value?: ((isSelected: boolean) => void) | undefined
    public _contentFont_0_0value?: arkui_component_units_Font | undefined
    public _contentFontColor_0_0value?: ResourceColor | undefined
    public _labelFont_0_0value?: arkui_component_units_Font | undefined
    public _labelFontColor_0_0value?: ResourceColor | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkMenuItemPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkMenuItemPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setSelectedAttribute((this._selected_0_0value as boolean | Bindable<boolean> | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setSelectedAttribute((undefined as boolean | Bindable<boolean> | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setSelectIconAttribute((this._selectIcon_0_0value as boolean | arkui_component_units_ResourceStr | SymbolGlyphModifier | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setSelectIconAttribute((undefined as boolean | arkui_component_units_ResourceStr | SymbolGlyphModifier | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as ((isSelected: boolean) => void) | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setOnChangeAttribute((undefined as ((isSelected: boolean) => void) | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setContentFontAttribute((this._contentFont_0_0value as arkui_component_units_Font | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setContentFontAttribute((undefined as arkui_component_units_Font | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setContentFontColorAttribute((this._contentFontColor_0_0value as ResourceColor | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setContentFontColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setLabelFontAttribute((this._labelFont_0_0value as arkui_component_units_Font | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setLabelFontAttribute((undefined as arkui_component_units_Font | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1: {
                    peer.setLabelFontColorAttribute((this._labelFontColor_0_0value as ResourceColor | undefined));
                    flagArray[6] = 2;
                    break;
                }
                case 3: {
                    flagArray[6] = 2;
                    break;
                }
                default: {
                    flagArray[6] = 0;
                    peer.setLabelFontColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: MenuItemModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: MenuItemModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.selected(modifier._selected_0_0value);
                    break;
                }
                default: {
                    this.selected((undefined as boolean | Bindable<boolean> | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.selectIcon(modifier._selectIcon_0_0value);
                    break;
                }
                default: {
                    this.selectIcon((undefined as boolean | arkui_component_units_ResourceStr | SymbolGlyphModifier | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.onChange(modifier._onChange_0_0value);
                    break;
                }
                default: {
                    this.onChange((undefined as ((isSelected: boolean) => void) | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.contentFont(modifier._contentFont_0_0value);
                    break;
                }
                default: {
                    this.contentFont((undefined as arkui_component_units_Font | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.contentFontColor(modifier._contentFontColor_0_0value);
                    break;
                }
                default: {
                    this.contentFontColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1:
                case 3: {
                    this.labelFont(modifier._labelFont_0_0value);
                    break;
                }
                default: {
                    this.labelFont((undefined as arkui_component_units_Font | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1:
                case 3: {
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
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._selected_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    selectIcon(value: boolean | arkui_component_units_ResourceStr | SymbolGlyphModifier | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._selectIcon_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    onChange(value: ((isSelected: boolean) => void) | undefined): this {
        if (((this._flagArray[2]) == (0)) || (true)) {
            this._flagArray[2] = 1
            this._onChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    contentFont(value: arkui_component_units_Font | undefined): this {
        if (((this._flagArray[3]) == (0)) || (true)) {
            this._flagArray[3] = 1
            this._contentFont_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    contentFontColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[4]) == (0)) || (true)) {
            this._flagArray[4] = 1
            this._contentFontColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    labelFont(value: arkui_component_units_Font | undefined): this {
        if (((this._flagArray[5]) == (0)) || (true)) {
            this._flagArray[5] = 1
            this._labelFont_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    labelFontColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[6]) == (0)) || (true)) {
            this._flagArray[6] = 1
            this._labelFontColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[6] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<MenuItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

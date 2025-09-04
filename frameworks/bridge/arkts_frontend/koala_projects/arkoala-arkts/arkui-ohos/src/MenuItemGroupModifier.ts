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
import { MenuItemGroupAttribute } from 'arkui/component/menuItemGroup'
 
import { AttributeUpdaterFlag, CommonMethodModifier } from './CommonMethodModifier';
import { Font, ResourceStr, ResourceColor } from './component/units';
import { PeerNode } from './PeerNode';
import { ArkMenuItemGroupPeer } from './component/menuItemGroup';
import { SymbolGlyphModifier } from "./SymbolGlyphModifier"
export class MenuItemGroupModifier extends CommonMethodModifier implements MenuItemGroupAttribute, AttributeModifier<MenuItemGroupAttribute> {
    applyNormalAttribute(instance: MenuItemGroupAttribute): void { }
    applyPressedAttribute(instance: MenuItemGroupAttribute): void { }
    applyFocusedAttribute(instance: MenuItemGroupAttribute): void { }
    applyDisabledAttribute(instance: MenuItemGroupAttribute): void { }
    applySelectedAttribute(instance: MenuItemGroupAttribute): void { }
 
    applyModifierPatch(value: PeerNode): void {
        super.applyModifierPatch(value)
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
    }
}
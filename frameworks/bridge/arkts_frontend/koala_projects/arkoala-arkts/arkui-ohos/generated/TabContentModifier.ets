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
import { ArkTabContentPeer, SubTabBarStyle, BottomTabBarStyle, TabBarOptions, TabContentAttribute } from "./component/tabContent"
import { int32 } from "@koalaui/common"
import { CommonMethod } from "./component/common"
import { ComponentContentBase } from "arkui.ComponentContent"
import { Resource } from "global.resource"
import { CustomBuilder } from "./component/builder"
import { VoidCallback } from "./component/units"
export class TabContentModifier extends CommonMethodModifier implements TabContentAttribute,AttributeModifier<TabContentAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: TabContentAttribute): void { }
    applyPressedAttribute(instance: TabContentAttribute): void { }
    applyFocusedAttribute(instance: TabContentAttribute): void { }
    applyDisabledAttribute(instance: TabContentAttribute): void { }
    applySelectedAttribute(instance: TabContentAttribute): void { }
    _tabBar_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _tabBar_0_0value?: ComponentContentBase | SubTabBarStyle | BottomTabBarStyle | string | Resource | CustomBuilder | TabBarOptions | undefined
    _onWillShow_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWillShow_0_0value?: VoidCallback | undefined
    _onWillHide_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWillHide_0_0value?: VoidCallback | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkTabContentPeer;
        if (this._tabBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._tabBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTabBarAttribute((this._tabBar_0_0value as ComponentContentBase | SubTabBarStyle | BottomTabBarStyle | string | Resource | CustomBuilder | TabBarOptions | undefined));
                    this._tabBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._tabBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._tabBar_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTabBarAttribute((undefined as ComponentContentBase | SubTabBarStyle | BottomTabBarStyle | string | Resource | CustomBuilder | TabBarOptions | undefined));
                }
            }
        }
        if (this._onWillShow_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onWillShow_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnWillShowAttribute((this._onWillShow_0_0value as VoidCallback | undefined));
                    this._onWillShow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWillShow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWillShow_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnWillShowAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (this._onWillHide_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onWillHide_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnWillHideAttribute((this._onWillHide_0_0value as VoidCallback | undefined));
                    this._onWillHide_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWillHide_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWillHide_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnWillHideAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: TabContentModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._tabBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._tabBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.tabBar(modifier._tabBar_0_0value);
                    break;
                }
                default: {
                    this.tabBar((undefined as ComponentContentBase | SubTabBarStyle | BottomTabBarStyle | string | Resource | CustomBuilder | TabBarOptions | undefined));
                }
            }
        }
        if (modifier._onWillShow_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onWillShow_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onWillShow(modifier._onWillShow_0_0value);
                    break;
                }
                default: {
                    this.onWillShow((undefined as VoidCallback | undefined));
                }
            }
        }
        if (modifier._onWillHide_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onWillHide_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onWillHide(modifier._onWillHide_0_0value);
                    break;
                }
                default: {
                    this.onWillHide((undefined as VoidCallback | undefined));
                }
            }
        }
    }
    tabBar(value: ComponentContentBase | SubTabBarStyle | BottomTabBarStyle | string | Resource | CustomBuilder | TabBarOptions | undefined): this {
        if (((this._tabBar_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._tabBar_0_flag = AttributeUpdaterFlag.UPDATE
            this._tabBar_0_0value = value
            this._state.fireChange()
        } else
        {
            this._tabBar_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onWillShow(value: VoidCallback | undefined): this {
        if (((this._onWillShow_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onWillShow_0_flag = AttributeUpdaterFlag.UPDATE
            this._onWillShow_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onWillShow_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onWillHide(value: VoidCallback | undefined): this {
        if (((this._onWillHide_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onWillHide_0_flag = AttributeUpdaterFlag.UPDATE
            this._onWillHide_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onWillHide_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<TabContentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

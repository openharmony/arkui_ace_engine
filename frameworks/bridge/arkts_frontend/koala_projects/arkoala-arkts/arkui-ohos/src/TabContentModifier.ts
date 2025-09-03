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

import { AttributeUpdaterFlag, CommonMethodModifier } from "./CommonMethodModifier"
import { ArkTabContentPeer, SubTabBarStyle, BottomTabBarStyle, TabBarOptions, TabContentAttribute } from "./component/tabContent"
import { AttributeModifier, CommonMethod, CustomBuilder } from "./component/common"
import { ComponentContent } from "./ComponentContent"
import { Resource } from "global.resource"
import { VoidCallback } from "./component/units"
import { PeerNode } from './PeerNode'
import { runtimeType, RuntimeType } from "@koalaui/interop"

export class TabContentModifier extends CommonMethodModifier implements TabContentAttribute,AttributeModifier<TabContentAttribute> {
    _instanceId: number = -1;
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
    _tabBar_0_0value?: string | Resource | CustomBuilder | TabBarOptions | SubTabBarStyle | BottomTabBarStyle | ComponentContent | undefined
    _onWillShow_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWillShow_0_0value?: VoidCallback | undefined
    _onWillHide_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWillHide_0_0value?: VoidCallback | undefined
    applyModifierPatch(peerNode: PeerNode): void {
        super.applyModifierPatch(peerNode)
        const peer = peerNode as ArkTabContentPeer
        if (this._tabBar_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._tabBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.tabBarAttribute(this._tabBar_0_0value)
                    this._tabBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._tabBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._tabBar_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.tabBarAttribute((undefined as ComponentContent | SubTabBarStyle | BottomTabBarStyle | string | Resource | CustomBuilder | TabBarOptions | undefined));
                }
            }
        }
        if (this._onWillShow_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onWillShow_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onWillShowAttribute((this._onWillShow_0_0value as VoidCallback | undefined));
                    this._onWillShow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWillShow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWillShow_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onWillShowAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (this._onWillHide_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._onWillHide_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onWillHideAttribute((this._onWillHide_0_0value as VoidCallback | undefined));
                    this._onWillHide_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWillHide_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWillHide_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onWillHideAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
        if (!(value instanceof TabContentModifier)) {
            return;
        }
        const modifier = value as TabContentModifier;
        if (modifier._tabBar_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._tabBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.tabBar(modifier._tabBar_0_0value);
                    break;
                }
                default: {
                    this.tabBar((undefined as string | Resource | CustomBuilder | TabBarOptions | SubTabBarStyle | BottomTabBarStyle | ComponentContent | undefined));
                }
            }
        }
        if (modifier._onWillShow_0_flag != AttributeUpdaterFlag.INITIAL) {
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
        if (modifier._onWillHide_0_flag != AttributeUpdaterFlag.INITIAL) {
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
    tabBar(value: string | Resource | CustomBuilder | TabBarOptions | SubTabBarStyle | BottomTabBarStyle | ComponentContent | undefined): this {
        if (((this._tabBar_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._tabBar_0_flag = AttributeUpdaterFlag.UPDATE
            this._tabBar_0_0value = value
        } else {
            this._tabBar_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onWillShow(value: VoidCallback | undefined): this {
        if (((this._onWillShow_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._onWillShow_0_flag = AttributeUpdaterFlag.UPDATE
            this._onWillShow_0_0value = value
        } else {
            this._onWillShow_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onWillHide(value: VoidCallback | undefined): this {
        if (((this._onWillHide_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
            this._onWillHide_0_flag = AttributeUpdaterFlag.UPDATE
            this._onWillHide_0_0value = value
        } else {
            this._onWillHide_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<TabContentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

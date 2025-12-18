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
import { ArkTabContentPeer, SubTabBarStyle, BottomTabBarStyle, TabBarOptions, TabContentAttribute } from './component/tabContent'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod } from './component/common'
import { ComponentContent } from '@arkui.ComponentContent'
import { Resource as arkui_component_units_Resource, VoidCallback } from './component/units'
import { Resource as global_resource_Resource } from 'global.resource'
import { CustomBuilder } from './component/builder'
export class TabContentModifier extends CommonMethodModifier implements TabContentAttribute,AttributeModifier<TabContentAttribute> {
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
    applyNormalAttribute(instance: TabContentAttribute): void { }
    applyPressedAttribute(instance: TabContentAttribute): void { }
    applyFocusedAttribute(instance: TabContentAttribute): void { }
    applyDisabledAttribute(instance: TabContentAttribute): void { }
    applySelectedAttribute(instance: TabContentAttribute): void { }
    public _tabBar_0_0value?: ComponentContent<undefined> | SubTabBarStyle | BottomTabBarStyle | string | arkui_component_units_Resource | CustomBuilder | TabBarOptions | undefined
    public _onWillShow_0_0value?: VoidCallback | undefined
    public _onWillHide_0_0value?: VoidCallback | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkTabContentPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkTabContentPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setTabBarAttribute((this._tabBar_0_0value as ComponentContent<undefined> | SubTabBarStyle | BottomTabBarStyle | string | arkui_component_units_Resource | CustomBuilder | TabBarOptions | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setTabBarAttribute((undefined as ComponentContent<undefined> | SubTabBarStyle | BottomTabBarStyle | string | arkui_component_units_Resource | CustomBuilder | TabBarOptions | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setOnWillShowAttribute((this._onWillShow_0_0value as VoidCallback | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setOnWillShowAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setOnWillHideAttribute((this._onWillHide_0_0value as VoidCallback | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setOnWillHideAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: TabContentModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: TabContentModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.tabBar(modifier._tabBar_0_0value);
                    break;
                }
                default: {
                    this.tabBar((undefined as ComponentContent<undefined> | SubTabBarStyle | BottomTabBarStyle | string | arkui_component_units_Resource | CustomBuilder | TabBarOptions | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.onWillShow(modifier._onWillShow_0_0value);
                    break;
                }
                default: {
                    this.onWillShow((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.onWillHide(modifier._onWillHide_0_0value);
                    break;
                }
                default: {
                    this.onWillHide((undefined as VoidCallback | undefined));
                }
            }
        }
    }
    tabBar(value: ComponentContent<undefined> | SubTabBarStyle | BottomTabBarStyle | string | arkui_component_units_Resource | CustomBuilder | TabBarOptions | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._tabBar_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    onWillShow(value: VoidCallback | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._onWillShow_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    onWillHide(value: VoidCallback | undefined): this {
        if (((this._flagArray[2]) == (0)) || (true)) {
            this._flagArray[2] = 1
            this._onWillHide_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<TabContentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

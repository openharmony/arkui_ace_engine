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
import { AttributeModifier } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkBlankPeer, BlankAttribute } from "./component/blank"
import { int32 } from "@koalaui/common"
import { ModifierState } from "./CommonModifier"
import { CommonMethod } from "./component/common"
import { ResourceColor } from "./component/units"
import { Color } from "./component/enums"
import { Resource } from "global.resource"
export class BlankModifier extends CommonMethodModifier implements BlankAttribute,AttributeModifier<BlankAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: BlankAttribute): void { }
    applyPressedAttribute(instance: BlankAttribute): void { }
    applyFocusedAttribute(instance: BlankAttribute): void { }
    applyDisabledAttribute(instance: BlankAttribute): void { }
    applySelectedAttribute(instance: BlankAttribute): void { }
    _color_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _color_0_0value?: ResourceColor | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkBlankPeer;
        if (this._color_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._color_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setColorAttribute((this._color_0_0value as ResourceColor | undefined));
                    this._color_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._color_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._color_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: BlankModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state
        if (modifier._color_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._color_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.color(modifier._color_0_0value);
                    break;
                }
                default: {
                    this.color((undefined as ResourceColor | undefined));
                }
            }
        }
    }
    color(value: ResourceColor | undefined): this {
        if (((this._color_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._color_0_flag = AttributeUpdaterFlag.UPDATE
            this._color_0_0value = value
            this._state.fireChange()
        } else
        {
            this._color_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<BlankAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

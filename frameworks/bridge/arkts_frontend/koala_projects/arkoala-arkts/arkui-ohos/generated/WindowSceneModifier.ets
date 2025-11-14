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
import { ArkWindowScenePeer, WindowSceneAttribute } from "./component/windowScene"
import { int32 } from "@koalaui/common"
import { ModifierState } from "./CommonModifier"
import { CommonMethod } from "./component/common"
import { Position } from "./component/units"
export class WindowSceneModifier extends CommonMethodModifier implements WindowSceneAttribute,AttributeModifier<WindowSceneAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: WindowSceneAttribute): void { }
    applyPressedAttribute(instance: WindowSceneAttribute): void { }
    applyFocusedAttribute(instance: WindowSceneAttribute): void { }
    applyDisabledAttribute(instance: WindowSceneAttribute): void { }
    applySelectedAttribute(instance: WindowSceneAttribute): void { }
    _attractionEffect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _attractionEffect_0_0value?: Position | undefined
    _attractionEffect_0_1value?: number | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkWindowScenePeer;
        if (this._attractionEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._attractionEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAttractionEffectAttribute((this._attractionEffect_0_0value as Position | undefined), (this._attractionEffect_0_1value as number | undefined));
                    this._attractionEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._attractionEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._attractionEffect_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAttractionEffectAttribute((undefined as Position | undefined), (undefined as number | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: WindowSceneModifier): void {
       super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._attractionEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._attractionEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.attractionEffect(modifier._attractionEffect_0_0value, modifier._attractionEffect_0_1value);
                    break;
                }
                default: {
                    this.attractionEffect((undefined as Position | undefined), (undefined as number | undefined));
                }
            }
        }
    }
    attractionEffect(destination: Position | undefined, fraction: number | undefined): this {
        if (((this._attractionEffect_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || ((this._attractionEffect_0_1value) !== (fraction)))
        {
            this._attractionEffect_0_flag = AttributeUpdaterFlag.UPDATE
            this._attractionEffect_0_0value = destination
            this._attractionEffect_0_1value = fraction
            this._state.fireChange()
        } else
        {
            this._attractionEffect_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<WindowSceneAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

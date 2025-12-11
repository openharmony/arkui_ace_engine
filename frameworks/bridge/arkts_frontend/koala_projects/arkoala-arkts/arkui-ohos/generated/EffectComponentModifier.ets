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
import { ArkEffectComponentPeer, EffectComponentAttribute } from "./component/effectComponent"
import { int32 } from "@koalaui/common"
import { CommonMethod } from "./component/common"
export class EffectComponentModifier extends CommonMethodModifier implements EffectComponentAttribute,AttributeModifier<EffectComponentAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: EffectComponentAttribute): void { }
    applyPressedAttribute(instance: EffectComponentAttribute): void { }
    applyFocusedAttribute(instance: EffectComponentAttribute): void { }
    applyDisabledAttribute(instance: EffectComponentAttribute): void { }
    applySelectedAttribute(instance: EffectComponentAttribute): void { }
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkEffectComponentPeer;
    }
    mergeModifier(modifier: EffectComponentModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
    }
    public attributeModifier(value: AttributeModifier<EffectComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

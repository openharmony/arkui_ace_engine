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
import { ArkEffectComponentPeer, EffectComponentAttribute } from "./component/effectComponent"
import { int32 } from "@koalaui/common"
import { ModifierState } from "./CommonModifier"
import { CommonMethod } from "./component/common"
export class EffectComponentModifier extends CommonMethodModifier implements EffectComponentAttribute,AttributeModifier<EffectComponentAttribute> {
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
    applyNormalAttribute(instance: EffectComponentAttribute): void { }
    applyPressedAttribute(instance: EffectComponentAttribute): void { }
    applyFocusedAttribute(instance: EffectComponentAttribute): void { }
    applyDisabledAttribute(instance: EffectComponentAttribute): void { }
    applySelectedAttribute(instance: EffectComponentAttribute): void { }
    _alwaysSnapshot_0_0value?: boolean | undefined
    applyModifierPatch(node: PeerNode): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkEffectComponentPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkEffectComponentPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0)
        {
            switch (flagArray[0]) {
                case 1: {
                    peer.setAlwaysSnapshotAttribute((this._alwaysSnapshot_0_0value as boolean | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setAlwaysSnapshotAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: EffectComponentModifier): void {
        super.mergeModifier(modifier)
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: EffectComponentModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0)
        {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.alwaysSnapshot(modifier._alwaysSnapshot_0_0value);
                    break;
                }
                default: {
                    this.alwaysSnapshot((undefined as boolean | undefined));
                }
            }
        }
    }
    alwaysSnapshot(value: boolean | undefined): this {
        if (((this._flagArray[0]) == (0)) || ((this._alwaysSnapshot_0_0value) !== (value)))
        {
            this._flagArray[0] = 1;
            this._alwaysSnapshot_0_0value = value;
            this._state.fireChange()
        } else
        {
            this._flagArray[0] = 3
        }
        return this
     }
    public attributeModifier(value: AttributeModifier<EffectComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

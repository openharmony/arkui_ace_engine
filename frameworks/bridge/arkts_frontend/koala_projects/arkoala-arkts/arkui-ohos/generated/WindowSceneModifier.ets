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
import { AttributeModifier } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkWindowScenePeer, WindowSceneAttribute } from './component/windowScene'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod } from './component/common'
import { Position } from './component/units'
export class WindowSceneModifier extends CommonMethodModifier implements WindowSceneAttribute,AttributeModifier<WindowSceneAttribute> {
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
    applyNormalAttribute(instance: WindowSceneAttribute): void { }
    applyPressedAttribute(instance: WindowSceneAttribute): void { }
    applyFocusedAttribute(instance: WindowSceneAttribute): void { }
    applyDisabledAttribute(instance: WindowSceneAttribute): void { }
    applySelectedAttribute(instance: WindowSceneAttribute): void { }
    public _attractionEffect_0_0value?: Position | undefined
    public _attractionEffect_0_1value?: double | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkWindowScenePeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkWindowScenePeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setAttractionEffectAttribute((this._attractionEffect_0_0value as Position | undefined), (this._attractionEffect_0_1value as double | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setAttractionEffectAttribute((undefined as Position | undefined), (undefined as double | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: WindowSceneModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: WindowSceneModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.attractionEffect(modifier._attractionEffect_0_0value, modifier._attractionEffect_0_1value);
                    break;
                }
                default: {
                    this.attractionEffect((undefined as Position | undefined), (undefined as double | undefined));
                }
            }
        }
    }
    attractionEffect(destination: Position | undefined, fraction: double | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true) || ((this._attractionEffect_0_1value) !== (fraction))) {
            this._flagArray[0] = 1
            this._attractionEffect_0_0value = destination
            this._attractionEffect_0_1value = fraction
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<WindowSceneAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

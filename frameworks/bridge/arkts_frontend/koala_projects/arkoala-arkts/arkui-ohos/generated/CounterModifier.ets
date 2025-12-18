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
import { ArkCounterPeer, CounterAttribute } from './component/counter'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod } from './component/common'
import { VoidCallback } from './component/units'
export class CounterModifier extends CommonMethodModifier implements CounterAttribute,AttributeModifier<CounterAttribute> {
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
    applyNormalAttribute(instance: CounterAttribute): void { }
    applyPressedAttribute(instance: CounterAttribute): void { }
    applyFocusedAttribute(instance: CounterAttribute): void { }
    applyDisabledAttribute(instance: CounterAttribute): void { }
    applySelectedAttribute(instance: CounterAttribute): void { }
    public _onInc_0_0value?: VoidCallback | undefined
    public _onDec_0_0value?: VoidCallback | undefined
    public _enableDec_0_0value?: boolean | undefined
    public _enableInc_0_0value?: boolean | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkCounterPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkCounterPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setOnIncAttribute((this._onInc_0_0value as VoidCallback | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setOnIncAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setOnDecAttribute((this._onDec_0_0value as VoidCallback | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setOnDecAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setEnableDecAttribute((this._enableDec_0_0value as boolean | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setEnableDecAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setEnableIncAttribute((this._enableInc_0_0value as boolean | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setEnableIncAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: CounterModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: CounterModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.onInc(modifier._onInc_0_0value);
                    break;
                }
                default: {
                    this.onInc((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.onDec(modifier._onDec_0_0value);
                    break;
                }
                default: {
                    this.onDec((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.enableDec(modifier._enableDec_0_0value);
                    break;
                }
                default: {
                    this.enableDec((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.enableInc(modifier._enableInc_0_0value);
                    break;
                }
                default: {
                    this.enableInc((undefined as boolean | undefined));
                }
            }
        }
    }
    onInc(value: VoidCallback | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._onInc_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    onDec(value: VoidCallback | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._onDec_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    enableDec(value: boolean | undefined): this {
        if (((this._flagArray[2]) == (0)) || ((this._enableDec_0_0value) !== (value))) {
            this._flagArray[2] = 1
            this._enableDec_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    enableInc(value: boolean | undefined): this {
        if (((this._flagArray[3]) == (0)) || ((this._enableInc_0_0value) !== (value))) {
            this._flagArray[3] = 1
            this._enableInc_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<CounterAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

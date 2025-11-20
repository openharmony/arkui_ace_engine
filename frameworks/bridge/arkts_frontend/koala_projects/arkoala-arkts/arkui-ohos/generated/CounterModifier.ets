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
import { ArkCounterPeer, CounterAttribute } from "./component/counter"
import { int32 } from "@koalaui/common"
import { CommonMethod } from "./component/common"
import { VoidCallback } from "./component/units"
export class CounterModifier extends CommonMethodModifier implements CounterAttribute,AttributeModifier<CounterAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: CounterAttribute): void { }
    applyPressedAttribute(instance: CounterAttribute): void { }
    applyFocusedAttribute(instance: CounterAttribute): void { }
    applyDisabledAttribute(instance: CounterAttribute): void { }
    applySelectedAttribute(instance: CounterAttribute): void { }
    _onInc_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onInc_0_0value?: VoidCallback | undefined
    _onDec_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDec_0_0value?: VoidCallback | undefined
    _enableDec_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableDec_0_0value?: boolean | undefined
    _enableInc_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableInc_0_0value?: boolean | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkCounterPeer;
        if (this._onInc_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onInc_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnIncAttribute((this._onInc_0_0value as VoidCallback | undefined));
                    this._onInc_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onInc_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onInc_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnIncAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (this._onDec_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDec_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDecAttribute((this._onDec_0_0value as VoidCallback | undefined));
                    this._onDec_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDec_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDec_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDecAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (this._enableDec_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableDec_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableDecAttribute((this._enableDec_0_0value as boolean | undefined));
                    this._enableDec_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableDec_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableDec_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableDecAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._enableInc_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableInc_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableIncAttribute((this._enableInc_0_0value as boolean | undefined));
                    this._enableInc_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableInc_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableInc_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableIncAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: CounterModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._onInc_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onInc_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onInc(modifier._onInc_0_0value);
                    break;
                }
                default: {
                    this.onInc((undefined as VoidCallback | undefined));
                }
            }
        }
        if (modifier._onDec_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDec_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDec(modifier._onDec_0_0value);
                    break;
                }
                default: {
                    this.onDec((undefined as VoidCallback | undefined));
                }
            }
        }
        if (modifier._enableDec_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableDec_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableDec(modifier._enableDec_0_0value);
                    break;
                }
                default: {
                    this.enableDec((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._enableInc_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableInc_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
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
        if (((this._onInc_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onInc_0_flag = AttributeUpdaterFlag.UPDATE
            this._onInc_0_0value = value
        } else
        {
            this._onInc_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDec(value: VoidCallback | undefined): this {
        if (((this._onDec_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDec_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDec_0_0value = value
        } else
        {
            this._onDec_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableDec(value: boolean | undefined): this {
        if (((this._enableDec_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableDec_0_0value) !== (value)))
        {
            this._enableDec_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableDec_0_0value = value
        } else
        {
            this._enableDec_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableInc(value: boolean | undefined): this {
        if (((this._enableInc_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableInc_0_0value) !== (value)))
        {
            this._enableInc_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableInc_0_0value = value
        } else
        {
            this._enableInc_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<CounterAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

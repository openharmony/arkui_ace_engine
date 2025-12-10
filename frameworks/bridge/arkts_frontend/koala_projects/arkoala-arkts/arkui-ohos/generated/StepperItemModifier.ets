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
import { ArkStepperItemPeer, ItemState, StepperItemAttribute } from './component/stepperItem'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod } from './component/common'
export class StepperItemModifier extends CommonMethodModifier implements StepperItemAttribute,AttributeModifier<StepperItemAttribute> {
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
    applyNormalAttribute(instance: StepperItemAttribute): void { }
    applyPressedAttribute(instance: StepperItemAttribute): void { }
    applyFocusedAttribute(instance: StepperItemAttribute): void { }
    applyDisabledAttribute(instance: StepperItemAttribute): void { }
    applySelectedAttribute(instance: StepperItemAttribute): void { }
    public _prevLabel_0_0value?: string | undefined
    public _nextLabel_0_0value?: string | undefined
    public _status_0_0value?: ItemState | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkStepperItemPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkStepperItemPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setPrevLabelAttribute((this._prevLabel_0_0value as string | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setPrevLabelAttribute((undefined as string | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setNextLabelAttribute((this._nextLabel_0_0value as string | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setNextLabelAttribute((undefined as string | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setStatusAttribute((this._status_0_0value as ItemState | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setStatusAttribute((undefined as ItemState | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: StepperItemModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: StepperItemModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.prevLabel(modifier._prevLabel_0_0value);
                    break;
                }
                default: {
                    this.prevLabel((undefined as string | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.nextLabel(modifier._nextLabel_0_0value);
                    break;
                }
                default: {
                    this.nextLabel((undefined as string | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.status(modifier._status_0_0value);
                    break;
                }
                default: {
                    this.status((undefined as ItemState | undefined));
                }
            }
        }
    }
    prevLabel(value: string | undefined): this {
        if (((this._flagArray[0]) == (0)) || ((this._prevLabel_0_0value) !== (value))) {
            this._flagArray[0] = 1
            this._prevLabel_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    nextLabel(value: string | undefined): this {
        if (((this._flagArray[1]) == (0)) || ((this._nextLabel_0_0value) !== (value))) {
            this._flagArray[1] = 1
            this._nextLabel_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    status(value: ItemState | undefined): this {
        if (((this._flagArray[2]) == (0)) || (true)) {
            this._flagArray[2] = 1
            this._status_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<StepperItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

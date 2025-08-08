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

import { AttributeModifier, CommonMethod } from "arkui/component/common"
import { ItemState, StepperItemAttribute, ArkStepperItemPeer } from "arkui/component/stepperItem"
import { AttributeUpdaterFlag, CommonMethodModifier } from './CommonMethodModifier';
import { PeerNode } from './PeerNode'

export class StepperItemModifier extends CommonMethodModifier implements StepperItemAttribute,AttributeModifier<StepperItemAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyNormalAttribute(instance: StepperItemAttribute): void { }
    applyPressedAttribute(instance: StepperItemAttribute): void { }
    applyFocusedAttribute(instance: StepperItemAttribute): void { }
    applyDisabledAttribute(instance: StepperItemAttribute): void { }
    applySelectedAttribute(instance: StepperItemAttribute): void { }
    _prevLabel_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _prevLabel_0_0value?: string | undefined
    _nextLabel_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _nextLabel_0_0value?: string | undefined
    _status_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _status_0_0value?: ItemState | undefined
    applyModifierPatch(peerNode: PeerNode): void {
        super.applyModifierPatch(peerNode)
        const peer = peerNode as ArkStepperItemPeer
        if (this._prevLabel_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._prevLabel_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.prevLabelAttribute((this._prevLabel_0_0value as string | undefined));
                    this._prevLabel_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._prevLabel_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._prevLabel_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.prevLabelAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._nextLabel_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._nextLabel_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.nextLabelAttribute((this._nextLabel_0_0value as string | undefined));
                    this._nextLabel_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._nextLabel_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._nextLabel_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.nextLabelAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._status_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._status_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.statusAttribute((this._status_0_0value as ItemState | undefined));
                    this._status_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._status_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._status_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.statusAttribute((undefined as ItemState | undefined));
                }
            }
        }
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
        if (!(value instanceof StepperItemModifier)) {
            return;
        }
        const modifier = value as StepperItemModifier;
        if (modifier._prevLabel_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._prevLabel_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.prevLabel(modifier._prevLabel_0_0value);
                    break;
                }
                default: {
                    this.prevLabel((undefined as string | undefined));
                }
            }
        }
        if (modifier._nextLabel_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._nextLabel_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.nextLabel(modifier._nextLabel_0_0value);
                    break;
                }
                default: {
                    this.nextLabel((undefined as string | undefined));
                }
            }
        }
        if (modifier._status_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._status_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
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
        if (((this._prevLabel_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._prevLabel_0_0value) !== (value)))
        {
            this._prevLabel_0_flag = AttributeUpdaterFlag.UPDATE
            this._prevLabel_0_0value = value
        } else
        {
            this._prevLabel_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    nextLabel(value: string | undefined): this {
        if (((this._nextLabel_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._nextLabel_0_0value) !== (value)))
        {
            this._nextLabel_0_flag = AttributeUpdaterFlag.UPDATE
            this._nextLabel_0_0value = value
        } else
        {
            this._nextLabel_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    status(value: ItemState | undefined): this {
        if (((this._status_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._status_0_flag = AttributeUpdaterFlag.UPDATE
            this._status_0_0value = value
        } else
        {
            this._status_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<StepperItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

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
import { ArkStepperPeer, StepperAttribute } from "./component/stepper"
import { int32 } from "@koalaui/common"
import { CommonMethod } from "./component/common"
export class StepperModifier extends CommonMethodModifier implements StepperAttribute,AttributeModifier<StepperAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: StepperAttribute): void { }
    applyPressedAttribute(instance: StepperAttribute): void { }
    applyFocusedAttribute(instance: StepperAttribute): void { }
    applyDisabledAttribute(instance: StepperAttribute): void { }
    applySelectedAttribute(instance: StepperAttribute): void { }
    _onFinish_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onFinish_0_0value?: (() => void) | undefined
    _onSkip_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onSkip_0_0value?: (() => void) | undefined
    _onChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onChange_0_0value?: ((prevIndex: int32,index: int32) => void) | undefined
    _onNext_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onNext_0_0value?: ((prevIndex: int32,index: int32) => void) | undefined
    _onPrevious_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onPrevious_0_0value?: ((prevIndex: int32,index: int32) => void) | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkStepperPeer;
        if (this._onFinish_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onFinish_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnFinishAttribute((this._onFinish_0_0value as (() => void) | undefined));
                    this._onFinish_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onFinish_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onFinish_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnFinishAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onSkip_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onSkip_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnSkipAttribute((this._onSkip_0_0value as (() => void) | undefined));
                    this._onSkip_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onSkip_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onSkip_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnSkipAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as ((prevIndex: int32,index: int32) => void) | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnChangeAttribute((undefined as ((prevIndex: int32,index: int32) => void) | undefined));
                }
            }
        }
        if (this._onNext_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onNext_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnNextAttribute((this._onNext_0_0value as ((prevIndex: int32,index: int32) => void) | undefined));
                    this._onNext_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onNext_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onNext_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnNextAttribute((undefined as ((prevIndex: int32,index: int32) => void) | undefined));
                }
            }
        }
        if (this._onPrevious_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onPrevious_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnPreviousAttribute((this._onPrevious_0_0value as ((prevIndex: int32,index: int32) => void) | undefined));
                    this._onPrevious_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onPrevious_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onPrevious_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnPreviousAttribute((undefined as ((prevIndex: int32,index: int32) => void) | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: StepperModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._onFinish_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onFinish_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onFinish(modifier._onFinish_0_0value);
                    break;
                }
                default: {
                    this.onFinish((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onSkip_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onSkip_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onSkip(modifier._onSkip_0_0value);
                    break;
                }
                default: {
                    this.onSkip((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onChange(modifier._onChange_0_0value);
                    break;
                }
                default: {
                    this.onChange((undefined as ((prevIndex: int32,index: int32) => void) | undefined));
                }
            }
        }
        if (modifier._onNext_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onNext_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onNext(modifier._onNext_0_0value);
                    break;
                }
                default: {
                    this.onNext((undefined as ((prevIndex: int32,index: int32) => void) | undefined));
                }
            }
        }
        if (modifier._onPrevious_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onPrevious_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onPrevious(modifier._onPrevious_0_0value);
                    break;
                }
                default: {
                    this.onPrevious((undefined as ((prevIndex: int32,index: int32) => void) | undefined));
                }
            }
        }
    }
    onFinish(value: (() => void) | undefined): this {
        if (((this._onFinish_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onFinish_0_flag = AttributeUpdaterFlag.UPDATE
            this._onFinish_0_0value = value
        } else
        {
            this._onFinish_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onSkip(value: (() => void) | undefined): this {
        if (((this._onSkip_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onSkip_0_flag = AttributeUpdaterFlag.UPDATE
            this._onSkip_0_0value = value
        } else
        {
            this._onSkip_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onChange(value: ((prevIndex: int32,index: int32) => void) | undefined): this {
        if (((this._onChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onChange_0_0value = value
        } else
        {
            this._onChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onNext(value: ((prevIndex: int32,index: int32) => void) | undefined): this {
        if (((this._onNext_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onNext_0_flag = AttributeUpdaterFlag.UPDATE
            this._onNext_0_0value = value
        } else
        {
            this._onNext_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onPrevious(value: ((prevIndex: int32,index: int32) => void) | undefined): this {
        if (((this._onPrevious_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onPrevious_0_flag = AttributeUpdaterFlag.UPDATE
            this._onPrevious_0_0value = value
        } else
        {
            this._onPrevious_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<StepperAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

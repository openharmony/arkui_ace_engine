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
import { ArkLinearIndicatorPeer, LinearIndicatorStyle, OnLinearIndicatorChangeCallback, LinearIndicatorAttribute } from "./component/linearindicator"
import { int32 } from "@koalaui/common"
import { CommonMethod } from "./component/common"
export class LinearIndicatorModifier extends CommonMethodModifier implements LinearIndicatorAttribute,AttributeModifier<LinearIndicatorAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: LinearIndicatorAttribute): void { }
    applyPressedAttribute(instance: LinearIndicatorAttribute): void { }
    applyFocusedAttribute(instance: LinearIndicatorAttribute): void { }
    applyDisabledAttribute(instance: LinearIndicatorAttribute): void { }
    applySelectedAttribute(instance: LinearIndicatorAttribute): void { }
    _indicatorStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _indicatorStyle_0_0value?: LinearIndicatorStyle | undefined
    _indicatorLoop_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _indicatorLoop_0_0value?: boolean | undefined
    _onChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onChange_0_0value?: OnLinearIndicatorChangeCallback | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkLinearIndicatorPeer;
        if (this._indicatorStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._indicatorStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setIndicatorStyleAttribute((this._indicatorStyle_0_0value as LinearIndicatorStyle | undefined));
                    this._indicatorStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._indicatorStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._indicatorStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setIndicatorStyleAttribute((undefined as LinearIndicatorStyle | undefined));
                }
            }
        }
        if (this._indicatorLoop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._indicatorLoop_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setIndicatorLoopAttribute((this._indicatorLoop_0_0value as boolean | undefined));
                    this._indicatorLoop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._indicatorLoop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._indicatorLoop_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setIndicatorLoopAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as OnLinearIndicatorChangeCallback | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnChangeAttribute((undefined as OnLinearIndicatorChangeCallback | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: LinearIndicatorModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._indicatorStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._indicatorStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.indicatorStyle(modifier._indicatorStyle_0_0value);
                    break;
                }
                default: {
                    this.indicatorStyle((undefined as LinearIndicatorStyle | undefined));
                }
            }
        }
        if (modifier._indicatorLoop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._indicatorLoop_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.indicatorLoop(modifier._indicatorLoop_0_0value);
                    break;
                }
                default: {
                    this.indicatorLoop((undefined as boolean | undefined));
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
                    this.onChange((undefined as OnLinearIndicatorChangeCallback | undefined));
                }
            }
        }
    }
    indicatorStyle(value: LinearIndicatorStyle | undefined): this {
        if (((this._indicatorStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._indicatorStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._indicatorStyle_0_0value = value
            this._state.fireChange()
        } else
        {
            this._indicatorStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    indicatorLoop(value: boolean | undefined): this {
        if (((this._indicatorLoop_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._indicatorLoop_0_0value) !== (value)))
        {
            this._indicatorLoop_0_flag = AttributeUpdaterFlag.UPDATE
            this._indicatorLoop_0_0value = value
            this._state.fireChange()
        } else
        {
            this._indicatorLoop_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onChange(value: OnLinearIndicatorChangeCallback | undefined): this {
        if (((this._onChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onChange_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<LinearIndicatorAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

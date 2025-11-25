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
import { ArkStackPeer, StackAttribute } from "./component/stack"
import { int32 } from "@koalaui/common"
import { CommonMethod } from "./component/common"
import { Alignment } from "./component/enums"
export class StackModifier extends CommonMethodModifier implements StackAttribute,AttributeModifier<StackAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: StackAttribute): void { }
    applyPressedAttribute(instance: StackAttribute): void { }
    applyFocusedAttribute(instance: StackAttribute): void { }
    applyDisabledAttribute(instance: StackAttribute): void { }
    applySelectedAttribute(instance: StackAttribute): void { }
    _alignContent_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _alignContent_0_0value?: Alignment | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkStackPeer;
        if (this._alignContent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._alignContent_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAlignContentAttribute((this._alignContent_0_0value as Alignment | undefined));
                    this._alignContent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._alignContent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._alignContent_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAlignContentAttribute((undefined as Alignment | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: StackModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._alignContent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._alignContent_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.alignContent(modifier._alignContent_0_0value);
                    break;
                }
                default: {
                    this.alignContent((undefined as Alignment | undefined));
                }
            }
        }
    }
    alignContent(value: Alignment | undefined): this {
        if (((this._alignContent_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._alignContent_0_flag = AttributeUpdaterFlag.UPDATE
            this._alignContent_0_0value = value
        } else
        {
            this._alignContent_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<StackAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

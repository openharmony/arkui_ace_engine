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
import { ArkRowSplitPeer, RowSplitAttribute } from "./component/rowSplit"
import { int32 } from "@koalaui/common"
import { ModifierState } from "./CommonModifier"
import { CommonMethod } from "./component/common"
export class RowSplitModifier extends CommonMethodModifier implements RowSplitAttribute,AttributeModifier<RowSplitAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: RowSplitAttribute): void { }
    applyPressedAttribute(instance: RowSplitAttribute): void { }
    applyFocusedAttribute(instance: RowSplitAttribute): void { }
    applyDisabledAttribute(instance: RowSplitAttribute): void { }
    applySelectedAttribute(instance: RowSplitAttribute): void { }
    _resizeable_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _resizeable_0_0value?: boolean | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkRowSplitPeer;
        if (this._resizeable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._resizeable_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setResizeableAttribute((this._resizeable_0_0value as boolean | undefined));
                    this._resizeable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._resizeable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._resizeable_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setResizeableAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: RowSplitModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._resizeable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._resizeable_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.resizeable(modifier._resizeable_0_0value);
                    break;
                }
                default: {
                    this.resizeable((undefined as boolean | undefined));
                }
            }
        }
    }
    resizeable(value: boolean | undefined): this {
        if (((this._resizeable_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._resizeable_0_0value) !== (value)))
        {
            this._resizeable_0_flag = AttributeUpdaterFlag.UPDATE
            this._resizeable_0_0value = value
            this._state.fireChange()
        } else
        {
            this._resizeable_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RowSplitAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

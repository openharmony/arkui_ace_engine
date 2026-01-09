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
import { ArkColumnPeer, ColumnAttribute } from "./component/column"
import { int32 } from "@koalaui/common"
import { CommonMethod } from "./component/common"
import { HorizontalAlign, FlexAlign } from "./component/enums"
export class ColumnModifier extends CommonMethodModifier implements ColumnAttribute,AttributeModifier<ColumnAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: ColumnAttribute): void { }
    applyPressedAttribute(instance: ColumnAttribute): void { }
    applyFocusedAttribute(instance: ColumnAttribute): void { }
    applyDisabledAttribute(instance: ColumnAttribute): void { }
    applySelectedAttribute(instance: ColumnAttribute): void { }
    _alignItems_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _alignItems_0_0value?: HorizontalAlign | undefined
    _justifyContent_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _justifyContent_0_0value?: FlexAlign | undefined
    _reverse_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _reverse_0_0value?: boolean | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkColumnPeer;
        if (this._alignItems_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._alignItems_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAlignItemsAttribute((this._alignItems_0_0value as HorizontalAlign | undefined));
                    this._alignItems_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._alignItems_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._alignItems_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAlignItemsAttribute((undefined as HorizontalAlign | undefined));
                }
            }
        }
        if (this._justifyContent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._justifyContent_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setJustifyContentAttribute((this._justifyContent_0_0value as FlexAlign | undefined));
                    this._justifyContent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._justifyContent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._justifyContent_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setJustifyContentAttribute((undefined as FlexAlign | undefined));
                }
            }
        }
        if (this._reverse_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._reverse_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setReverseAttribute((this._reverse_0_0value as boolean | undefined));
                    this._reverse_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._reverse_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._reverse_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setReverseAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: ColumnModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._alignItems_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._alignItems_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.alignItems(modifier._alignItems_0_0value);
                    break;
                }
                default: {
                    this.alignItems((undefined as HorizontalAlign | undefined));
                }
            }
        }
        if (modifier._justifyContent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._justifyContent_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.justifyContent(modifier._justifyContent_0_0value);
                    break;
                }
                default: {
                    this.justifyContent((undefined as FlexAlign | undefined));
                }
            }
        }
        if (modifier._reverse_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._reverse_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.reverse(modifier._reverse_0_0value);
                    break;
                }
                default: {
                    this.reverse((undefined as boolean | undefined));
                }
            }
        }
    }
    alignItems(value: HorizontalAlign | undefined): this {
        if (((this._alignItems_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._alignItems_0_flag = AttributeUpdaterFlag.UPDATE
            this._alignItems_0_0value = value
            this._state.fireChange()
        } else
        {
            this._alignItems_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    justifyContent(value: FlexAlign | undefined): this {
        if (((this._justifyContent_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._justifyContent_0_flag = AttributeUpdaterFlag.UPDATE
            this._justifyContent_0_0value = value
            this._state.fireChange()
        } else
        {
            this._justifyContent_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    reverse(value: boolean | undefined): this {
        if (((this._reverse_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._reverse_0_0value) !== (value)))
        {
            this._reverse_0_flag = AttributeUpdaterFlag.UPDATE
            this._reverse_0_0value = value
            this._state.fireChange()
        } else
        {
            this._reverse_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ColumnAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

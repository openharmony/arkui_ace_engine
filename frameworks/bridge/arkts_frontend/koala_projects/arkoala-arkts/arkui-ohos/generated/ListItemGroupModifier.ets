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
import { ArkListItemGroupPeer, ListItemGroupAttribute } from "./component/listItemGroup"
import { int32 } from "@koalaui/common"
import { CommonMethod, ChildrenMainSize } from "./component/common"
import { ListDividerOptions } from "./component/list"
export class ListItemGroupModifier extends CommonMethodModifier implements ListItemGroupAttribute,AttributeModifier<ListItemGroupAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: ListItemGroupAttribute): void { }
    applyPressedAttribute(instance: ListItemGroupAttribute): void { }
    applyFocusedAttribute(instance: ListItemGroupAttribute): void { }
    applyDisabledAttribute(instance: ListItemGroupAttribute): void { }
    applySelectedAttribute(instance: ListItemGroupAttribute): void { }
    _divider_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _divider_0_0value?: ListDividerOptions | null | undefined
    _childrenMainSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _childrenMainSize_0_0value?: ChildrenMainSize | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkListItemGroupPeer;
        if (this._divider_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._divider_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDividerAttribute((this._divider_0_0value as ListDividerOptions | null | undefined));
                    this._divider_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._divider_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._divider_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDividerAttribute((undefined as ListDividerOptions | null | undefined));
                }
            }
        }
        if (this._childrenMainSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._childrenMainSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setChildrenMainSizeAttribute((this._childrenMainSize_0_0value as ChildrenMainSize | undefined));
                    this._childrenMainSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._childrenMainSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._childrenMainSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setChildrenMainSizeAttribute((undefined as ChildrenMainSize | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: ListItemGroupModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._divider_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._divider_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.divider(modifier._divider_0_0value);
                    break;
                }
                default: {
                    this.divider((undefined as ListDividerOptions | null | undefined));
                }
            }
        }
        if (modifier._childrenMainSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._childrenMainSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.childrenMainSize(modifier._childrenMainSize_0_0value);
                    break;
                }
                default: {
                    this.childrenMainSize((undefined as ChildrenMainSize | undefined));
                }
            }
        }
    }
    divider(value: ListDividerOptions | null | undefined): this {
        if (((this._divider_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._divider_0_flag = AttributeUpdaterFlag.UPDATE
            this._divider_0_0value = value
        } else
        {
            this._divider_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    childrenMainSize(value: ChildrenMainSize | undefined): this {
        if (((this._childrenMainSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._childrenMainSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._childrenMainSize_0_0value = value
        } else
        {
            this._childrenMainSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ListItemGroupAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

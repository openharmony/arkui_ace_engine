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
import { AttributeModifier, extractors } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkLazyGridLayoutAttributePeer, LazyGridLayoutAttribute } from "./component/lazyGridLayout"
import { int32 } from "@koalaui/common"
import { CommonMethod } from "./component/common"
import { LengthMetrics } from "arkui.Graphics"
export class LazyGridLayoutModifier extends CommonMethodModifier implements LazyGridLayoutAttribute,AttributeModifier<LazyGridLayoutAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: LazyGridLayoutAttribute): void { }
    applyPressedAttribute(instance: LazyGridLayoutAttribute): void { }
    applyFocusedAttribute(instance: LazyGridLayoutAttribute): void { }
    applyDisabledAttribute(instance: LazyGridLayoutAttribute): void { }
    applySelectedAttribute(instance: LazyGridLayoutAttribute): void { }
    _rowsGap_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _rowsGap_0_0value?: LengthMetrics | undefined
    _columnsGap_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _columnsGap_0_0value?: LengthMetrics | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkLazyGridLayoutAttributePeer;
        if (this._rowsGap_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._rowsGap_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRowsGapAttribute((this._rowsGap_0_0value as LengthMetrics | undefined));
                    this._rowsGap_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._rowsGap_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._rowsGap_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRowsGapAttribute((undefined as LengthMetrics | undefined));
                }
            }
        }
        if (this._columnsGap_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._columnsGap_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setColumnsGapAttribute((this._columnsGap_0_0value as LengthMetrics | undefined));
                    this._columnsGap_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._columnsGap_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._columnsGap_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setColumnsGapAttribute((undefined as LengthMetrics | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: LazyGridLayoutModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._rowsGap_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._rowsGap_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.rowsGap(modifier._rowsGap_0_0value);
                    break;
                }
                default: {
                    this.rowsGap((undefined as LengthMetrics | undefined));
                }
            }
        }
        if (modifier._columnsGap_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._columnsGap_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.columnsGap(modifier._columnsGap_0_0value);
                    break;
                }
                default: {
                    this.columnsGap((undefined as LengthMetrics | undefined));
                }
            }
        }
    }
    rowsGap(value: LengthMetrics | undefined): this {
        if (((this._rowsGap_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._rowsGap_0_flag = AttributeUpdaterFlag.UPDATE
            this._rowsGap_0_0value = value
        } else
        {
            this._rowsGap_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    columnsGap(value: LengthMetrics | undefined): this {
        if (((this._columnsGap_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._columnsGap_0_flag = AttributeUpdaterFlag.UPDATE
            this._columnsGap_0_0value = value
        } else
        {
            this._columnsGap_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<LazyGridLayoutAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

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
import { ArkRelativeContainerPeer, GuideLineStyle, BarrierStyle, LocalizedBarrierStyle, RelativeContainerAttribute } from "./component/relativeContainer"
import { int32 } from "@koalaui/common"
import { CommonMethod } from "./component/common"
export class RelativeContainerModifier extends CommonMethodModifier implements RelativeContainerAttribute,AttributeModifier<RelativeContainerAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: RelativeContainerAttribute): void { }
    applyPressedAttribute(instance: RelativeContainerAttribute): void { }
    applyFocusedAttribute(instance: RelativeContainerAttribute): void { }
    applyDisabledAttribute(instance: RelativeContainerAttribute): void { }
    applySelectedAttribute(instance: RelativeContainerAttribute): void { }
    _guideLine_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _guideLine_0_0value?: Array<GuideLineStyle> | undefined
    _barrier_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _barrier_0_0value?: Array<BarrierStyle> | Array<LocalizedBarrierStyle> | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkRelativeContainerPeer;
        if (this._guideLine_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._guideLine_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setGuideLineAttribute((this._guideLine_0_0value as Array<GuideLineStyle> | undefined));
                    this._guideLine_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._guideLine_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._guideLine_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setGuideLineAttribute((undefined as Array<GuideLineStyle> | undefined));
                }
            }
        }
        if (this._barrier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._barrier_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBarrierAttribute((this._barrier_0_0value as Array<BarrierStyle> | Array<LocalizedBarrierStyle> | undefined));
                    this._barrier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._barrier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._barrier_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBarrierAttribute((undefined as Array<BarrierStyle> | Array<LocalizedBarrierStyle> | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: RelativeContainerModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._guideLine_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._guideLine_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.guideLine(modifier._guideLine_0_0value);
                    break;
                }
                default: {
                    this.guideLine((undefined as Array<GuideLineStyle> | undefined));
                }
            }
        }
        if (modifier._barrier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._barrier_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.barrier(modifier._barrier_0_0value);
                    break;
                }
                default: {
                    this.barrier((undefined as Array<BarrierStyle> | Array<LocalizedBarrierStyle> | undefined));
                }
            }
        }
    }
    guideLine(value: Array<GuideLineStyle> | undefined): this {
        if (((this._guideLine_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._guideLine_0_flag = AttributeUpdaterFlag.UPDATE
            this._guideLine_0_0value = value
        } else
        {
            this._guideLine_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    barrier(value: Array<BarrierStyle> | Array<LocalizedBarrierStyle> | undefined): this {
        if (((this._barrier_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._barrier_0_flag = AttributeUpdaterFlag.UPDATE
            this._barrier_0_0value = value
        } else
        {
            this._barrier_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RelativeContainerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

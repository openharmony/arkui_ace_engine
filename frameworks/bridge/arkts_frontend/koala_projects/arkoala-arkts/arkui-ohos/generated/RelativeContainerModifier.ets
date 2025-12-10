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
import { ArkRelativeContainerPeer, GuideLineStyle, BarrierStyle, LocalizedBarrierStyle, RelativeContainerAttribute } from './component/relativeContainer'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod } from './component/common'
export class RelativeContainerModifier extends CommonMethodModifier implements RelativeContainerAttribute,AttributeModifier<RelativeContainerAttribute> {
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
    applyNormalAttribute(instance: RelativeContainerAttribute): void { }
    applyPressedAttribute(instance: RelativeContainerAttribute): void { }
    applyFocusedAttribute(instance: RelativeContainerAttribute): void { }
    applyDisabledAttribute(instance: RelativeContainerAttribute): void { }
    applySelectedAttribute(instance: RelativeContainerAttribute): void { }
    public _guideLine_0_0value?: Array<GuideLineStyle> | undefined
    public _barrier_0_0value?: Array<BarrierStyle> | Array<LocalizedBarrierStyle> | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkRelativeContainerPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkRelativeContainerPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setGuideLineAttribute((this._guideLine_0_0value as Array<GuideLineStyle> | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setGuideLineAttribute((undefined as Array<GuideLineStyle> | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setBarrierAttribute((this._barrier_0_0value as Array<BarrierStyle> | Array<LocalizedBarrierStyle> | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setBarrierAttribute((undefined as Array<BarrierStyle> | Array<LocalizedBarrierStyle> | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: RelativeContainerModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: RelativeContainerModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.guideLine(modifier._guideLine_0_0value);
                    break;
                }
                default: {
                    this.guideLine((undefined as Array<GuideLineStyle> | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
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
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._guideLine_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    barrier(value: Array<BarrierStyle> | Array<LocalizedBarrierStyle> | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._barrier_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RelativeContainerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

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

import { AttributeModifier } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkCustomLayoutRootPeer, Callback_onMeasureSize_SizeResult, Callback_onPlaceChildren_Void, CustomLayoutRoot } from './component/idlize'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { GeometryInfo, Measurable, Layoutable } from './component/common'
import { ConstraintSizeOptions } from './component/units'
export class CustomLayoutRootModifier implements CustomLayoutRoot,AttributeModifier<CustomLayoutRoot> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState;
    _addr: ArrayBuffer = new ArrayBuffer(4096);
    _flagArray: Uint8Array = new Uint8Array(this._addr);
    constructor() {
        this._flagArray.fill(0);
    }
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: CustomLayoutRoot): void { }
    applyPressedAttribute(instance: CustomLayoutRoot): void { }
    applyFocusedAttribute(instance: CustomLayoutRoot): void { }
    applyDisabledAttribute(instance: CustomLayoutRoot): void { }
    applySelectedAttribute(instance: CustomLayoutRoot): void { }
    public _subscribeOnMeasureSize_0_0value?: Callback_onMeasureSize_SizeResult
    public _subscribeOnPlaceChildren_0_0value?: Callback_onPlaceChildren_Void
    applyModifierPatch(node: object): void {
        this._state.addRef()
        const peer = node as ArkCustomLayoutRootPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkCustomLayoutRootPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setSubscribeOnMeasureSizeAttribute((this._subscribeOnMeasureSize_0_0value as Callback_onMeasureSize_SizeResult));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setSubscribeOnPlaceChildrenAttribute((this._subscribeOnPlaceChildren_0_0value as Callback_onPlaceChildren_Void));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                }
            }
        }
    }
    mergeModifier(modifier: CustomLayoutRootModifier): void {
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: CustomLayoutRootModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    break;
                }
                default: {
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    break;
                }
                default: {
                }
            }
        }
    }
    subscribeOnMeasureSize(value: Callback_onMeasureSize_SizeResult): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._subscribeOnMeasureSize_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    subscribeOnPlaceChildren(value: Callback_onPlaceChildren_Void): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._subscribeOnPlaceChildren_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<CustomLayoutRoot> | undefined): this {
        throw new Error('Not implemented')
    }
}

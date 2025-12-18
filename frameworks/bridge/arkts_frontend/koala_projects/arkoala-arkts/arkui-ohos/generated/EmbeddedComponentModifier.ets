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
import { AttributeModifier, ArkEmbeddedComponentPeer, extractors, EmbeddedComponentAttribute } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod, TerminationInfo } from './component/common'
import { Callback as ohos_base_Callback, ErrorCallback, BusinessError } from '@ohos.base'
export class EmbeddedComponentModifier extends CommonMethodModifier implements EmbeddedComponentAttribute,AttributeModifier<EmbeddedComponentAttribute> {
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
    applyNormalAttribute(instance: EmbeddedComponentAttribute): void { }
    applyPressedAttribute(instance: EmbeddedComponentAttribute): void { }
    applyFocusedAttribute(instance: EmbeddedComponentAttribute): void { }
    applyDisabledAttribute(instance: EmbeddedComponentAttribute): void { }
    applySelectedAttribute(instance: EmbeddedComponentAttribute): void { }
    public _onTerminated_0_0value?: ohos_base_Callback<TerminationInfo> | undefined
    public _onError_0_0value?: ErrorCallback<BusinessError<void>> | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkEmbeddedComponentPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkEmbeddedComponentPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setOnTerminatedAttribute((this._onTerminated_0_0value as ohos_base_Callback<TerminationInfo> | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setOnTerminatedAttribute((undefined as ohos_base_Callback<TerminationInfo> | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setOnErrorAttribute((this._onError_0_0value as ErrorCallback<BusinessError<void>> | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setOnErrorAttribute((undefined as ErrorCallback<BusinessError<void>> | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: EmbeddedComponentModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: EmbeddedComponentModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.onTerminated(modifier._onTerminated_0_0value);
                    break;
                }
                default: {
                    this.onTerminated((undefined as ohos_base_Callback<TerminationInfo> | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.onError(modifier._onError_0_0value);
                    break;
                }
                default: {
                    this.onError((undefined as ErrorCallback<BusinessError<void>> | undefined));
                }
            }
        }
    }
    onTerminated(value: ohos_base_Callback<TerminationInfo> | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._onTerminated_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    onError(value: ErrorCallback<BusinessError<void>> | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._onError_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<EmbeddedComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

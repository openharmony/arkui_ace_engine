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
import { AttributeModifier, extractors } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkUIExtensionComponentPeer, UIExtensionProxy, ReceiveCallback, UIExtensionComponentAttribute } from './component/uiExtensionComponent'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod, TerminationInfo } from './component/common'
import { Callback as ohos_base_Callback, RecordData, ErrorCallback, BusinessError } from '@ohos.base'
import { VoidCallback } from './component/units'
export class UIExtensionComponentModifier extends CommonMethodModifier implements UIExtensionComponentAttribute,AttributeModifier<UIExtensionComponentAttribute> {
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
    applyNormalAttribute(instance: UIExtensionComponentAttribute): void { }
    applyPressedAttribute(instance: UIExtensionComponentAttribute): void { }
    applyFocusedAttribute(instance: UIExtensionComponentAttribute): void { }
    applyDisabledAttribute(instance: UIExtensionComponentAttribute): void { }
    applySelectedAttribute(instance: UIExtensionComponentAttribute): void { }
    public _onRemoteReady_0_0value?: ohos_base_Callback<UIExtensionProxy> | undefined
    public _onReceive_0_0value?: ReceiveCallback | undefined
    public _onError_0_0value?: ErrorCallback<BusinessError<void>> | undefined
    public _onTerminated_0_0value?: ohos_base_Callback<TerminationInfo> | undefined
    public _onDrawReady_0_0value?: VoidCallback | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkUIExtensionComponentPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkUIExtensionComponentPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setOnRemoteReadyAttribute((this._onRemoteReady_0_0value as ohos_base_Callback<UIExtensionProxy> | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setOnRemoteReadyAttribute((undefined as ohos_base_Callback<UIExtensionProxy> | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setOnReceiveAttribute((this._onReceive_0_0value as ReceiveCallback | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setOnReceiveAttribute((undefined as ReceiveCallback | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setOnErrorAttribute((this._onError_0_0value as ErrorCallback<BusinessError<void>> | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setOnErrorAttribute((undefined as ErrorCallback<BusinessError<void>> | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setOnTerminatedAttribute((this._onTerminated_0_0value as ohos_base_Callback<TerminationInfo> | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setOnTerminatedAttribute((undefined as ohos_base_Callback<TerminationInfo> | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setOnDrawReadyAttribute((this._onDrawReady_0_0value as VoidCallback | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setOnDrawReadyAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: UIExtensionComponentModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: UIExtensionComponentModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.onRemoteReady(modifier._onRemoteReady_0_0value);
                    break;
                }
                default: {
                    this.onRemoteReady((undefined as ohos_base_Callback<UIExtensionProxy> | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.onReceive(modifier._onReceive_0_0value);
                    break;
                }
                default: {
                    this.onReceive((undefined as ReceiveCallback | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
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
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
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
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.onDrawReady(modifier._onDrawReady_0_0value);
                    break;
                }
                default: {
                    this.onDrawReady((undefined as VoidCallback | undefined));
                }
            }
        }
    }
    onRemoteReady(value: ohos_base_Callback<UIExtensionProxy> | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._onRemoteReady_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    onReceive(value: ReceiveCallback | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._onReceive_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    onError(value: ErrorCallback<BusinessError<void>> | undefined): this {
        if (((this._flagArray[2]) == (0)) || (true)) {
            this._flagArray[2] = 1
            this._onError_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    onTerminated(value: ohos_base_Callback<TerminationInfo> | undefined): this {
        if (((this._flagArray[3]) == (0)) || (true)) {
            this._flagArray[3] = 1
            this._onTerminated_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    onDrawReady(value: VoidCallback | undefined): this {
        if (((this._flagArray[4]) == (0)) || (true)) {
            this._flagArray[4] = 1
            this._onDrawReady_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<UIExtensionComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

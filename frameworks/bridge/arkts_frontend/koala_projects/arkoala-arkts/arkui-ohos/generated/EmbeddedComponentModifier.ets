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
import { ArkEmbeddedComponentPeer, EmbeddedComponentAttribute } from "./component/embeddedComponent"
import { int32 } from "@koalaui/common"
import { CommonMethod, TerminationInfo } from "./component/common"
import { ErrorCallback, BusinessError } from "@ohos.base"
export class EmbeddedComponentModifier extends CommonMethodModifier implements EmbeddedComponentAttribute,AttributeModifier<EmbeddedComponentAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: EmbeddedComponentAttribute): void { }
    applyPressedAttribute(instance: EmbeddedComponentAttribute): void { }
    applyFocusedAttribute(instance: EmbeddedComponentAttribute): void { }
    applyDisabledAttribute(instance: EmbeddedComponentAttribute): void { }
    applySelectedAttribute(instance: EmbeddedComponentAttribute): void { }
    _onTerminated_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onTerminated_0_0value?: ((value0: TerminationInfo) => void) | undefined
    _onError_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onError_0_0value?: ErrorCallback<BusinessError> | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkEmbeddedComponentPeer;
        if (this._onTerminated_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onTerminated_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnTerminatedAttribute((this._onTerminated_0_0value as ((value0: TerminationInfo) => void) | undefined));
                    this._onTerminated_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onTerminated_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onTerminated_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnTerminatedAttribute((undefined as ((value0: TerminationInfo) => void) | undefined));
                }
            }
        }
        if (this._onError_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onError_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnErrorAttribute((this._onError_0_0value as ErrorCallback<BusinessError> | undefined));
                    this._onError_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onError_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onError_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnErrorAttribute((undefined as ErrorCallback<BusinessError> | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: EmbeddedComponentModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._onTerminated_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onTerminated_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onTerminated(modifier._onTerminated_0_0value);
                    break;
                }
                default: {
                    this.onTerminated((undefined as ((value0: TerminationInfo) => void) | undefined));
                }
            }
        }
        if (modifier._onError_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onError_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onError(modifier._onError_0_0value);
                    break;
                }
                default: {
                    this.onError((undefined as ErrorCallback<BusinessError> | undefined));
                }
            }
        }
    }
    onTerminated(value: ((value0: TerminationInfo) => void) | undefined): this {
        if (((this._onTerminated_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onTerminated_0_flag = AttributeUpdaterFlag.UPDATE
            this._onTerminated_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onTerminated_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onError(value: ErrorCallback<BusinessError> | undefined): this {
        if (((this._onError_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onError_0_flag = AttributeUpdaterFlag.UPDATE
            this._onError_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onError_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<EmbeddedComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

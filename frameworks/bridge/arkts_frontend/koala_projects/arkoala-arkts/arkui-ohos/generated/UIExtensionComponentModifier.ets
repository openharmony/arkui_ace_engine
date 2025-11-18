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
import { AttributeModifier, extractors } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkUIExtensionComponentPeer, UIExtensionProxy, UIExtensionComponentAttribute } from "./component/uiExtensionComponent"
import { int32 } from "@koalaui/common"
import { ModifierState } from "./CommonModifier"
import { CommonMethod, TerminationInfo } from "./component/common"
import { RecordData } from "./component/pluginComponent"
import { ErrorCallback, BusinessError } from "@ohos.base"
import { VoidCallback } from "./component/units"
export class UIExtensionComponentModifier extends CommonMethodModifier implements UIExtensionComponentAttribute,AttributeModifier<UIExtensionComponentAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: UIExtensionComponentAttribute): void { }
    applyPressedAttribute(instance: UIExtensionComponentAttribute): void { }
    applyFocusedAttribute(instance: UIExtensionComponentAttribute): void { }
    applyDisabledAttribute(instance: UIExtensionComponentAttribute): void { }
    applySelectedAttribute(instance: UIExtensionComponentAttribute): void { }
    _onRemoteReady_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onRemoteReady_0_0value?: ((value0: UIExtensionProxy) => void) | undefined
    _onReceive_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onReceive_0_0value?: ((value0: Map<string, RecordData>) => void) | undefined
    _onError_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onError_0_0value?: ErrorCallback<BusinessError> | undefined
    _onTerminated_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onTerminated_0_0value?: ((value0: TerminationInfo) => void) | undefined
    _onDrawReady_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDrawReady_0_0value?: VoidCallback | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkUIExtensionComponentPeer;
        if (this._onRemoteReady_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onRemoteReady_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnRemoteReadyAttribute((this._onRemoteReady_0_0value as ((value0: UIExtensionProxy) => void) | undefined));
                    this._onRemoteReady_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onRemoteReady_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onRemoteReady_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnRemoteReadyAttribute((undefined as ((value0: UIExtensionProxy) => void) | undefined));
                }
            }
        }
        if (this._onReceive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onReceive_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnReceiveAttribute((this._onReceive_0_0value as ((value0: Record<string, RecordData>) => void) | undefined));
                    this._onReceive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onReceive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onReceive_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnReceiveAttribute((undefined as ((value0: Record<string, RecordData>) => void) | undefined));
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
        if (this._onDrawReady_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDrawReady_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDrawReadyAttribute((this._onDrawReady_0_0value as VoidCallback | undefined));
                    this._onDrawReady_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDrawReady_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDrawReady_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDrawReadyAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: UIExtensionComponentModifier): void {
       super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._onRemoteReady_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onRemoteReady_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onRemoteReady(modifier._onRemoteReady_0_0value);
                    break;
                }
                default: {
                    this.onRemoteReady((undefined as ((value0: UIExtensionProxy) => void) | undefined));
                }
            }
        }
        if (modifier._onReceive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onReceive_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onReceive(modifier._onReceive_0_0value);
                    break;
                }
                default: {
                    this.onReceive((undefined as ((value0: Map<string, RecordData>) => void) | undefined));
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
        if (modifier._onDrawReady_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDrawReady_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDrawReady(modifier._onDrawReady_0_0value);
                    break;
                }
                default: {
                    this.onDrawReady((undefined as VoidCallback | undefined));
                }
            }
        }
    }
    onRemoteReady(value: ((value0: UIExtensionProxy) => void) | undefined): this {
        if (((this._onRemoteReady_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onRemoteReady_0_flag = AttributeUpdaterFlag.UPDATE
            this._onRemoteReady_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onRemoteReady_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onReceive(value: ((value0: Map<string, RecordData>) => void) | undefined): this {
        if (((this._onReceive_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onReceive_0_flag = AttributeUpdaterFlag.UPDATE
            this._onReceive_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onReceive_0_flag = AttributeUpdaterFlag.SKIP
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
    onDrawReady(value: VoidCallback | undefined): this {
        if (((this._onDrawReady_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDrawReady_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDrawReady_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onDrawReady_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<UIExtensionComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

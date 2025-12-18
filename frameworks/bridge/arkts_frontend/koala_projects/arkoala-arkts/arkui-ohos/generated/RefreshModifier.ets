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
import { ArkRefreshPeer, RefreshStatus, RefreshAttribute } from './component/refresh'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod, Callback as arkui_component_common_Callback } from './component/common'
export class RefreshModifier extends CommonMethodModifier implements RefreshAttribute,AttributeModifier<RefreshAttribute> {
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
    applyNormalAttribute(instance: RefreshAttribute): void { }
    applyPressedAttribute(instance: RefreshAttribute): void { }
    applyFocusedAttribute(instance: RefreshAttribute): void { }
    applyDisabledAttribute(instance: RefreshAttribute): void { }
    applySelectedAttribute(instance: RefreshAttribute): void { }
    public _onStateChange_0_0value?: ((state: RefreshStatus) => void) | undefined
    public _onRefreshing_0_0value?: (() => void) | undefined
    public _refreshOffset_0_0value?: double | undefined
    public _pullToRefresh_0_0value?: boolean | undefined
    public _onOffsetChange_0_0value?: arkui_component_common_Callback<double, void> | undefined
    public _pullDownRatio_0_0value?: double | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkRefreshPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkRefreshPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setOnStateChangeAttribute((this._onStateChange_0_0value as ((state: RefreshStatus) => void) | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setOnStateChangeAttribute((undefined as ((state: RefreshStatus) => void) | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setOnRefreshingAttribute((this._onRefreshing_0_0value as (() => void) | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setOnRefreshingAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setRefreshOffsetAttribute((this._refreshOffset_0_0value as double | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setRefreshOffsetAttribute((undefined as double | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setPullToRefreshAttribute((this._pullToRefresh_0_0value as boolean | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setPullToRefreshAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setOnOffsetChangeAttribute((this._onOffsetChange_0_0value as arkui_component_common_Callback<double, void> | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setOnOffsetChangeAttribute((undefined as arkui_component_common_Callback<double, void> | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setPullDownRatioAttribute((this._pullDownRatio_0_0value as double | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setPullDownRatioAttribute((undefined as double | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: RefreshModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: RefreshModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.onStateChange(modifier._onStateChange_0_0value);
                    break;
                }
                default: {
                    this.onStateChange((undefined as ((state: RefreshStatus) => void) | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.onRefreshing(modifier._onRefreshing_0_0value);
                    break;
                }
                default: {
                    this.onRefreshing((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.refreshOffset(modifier._refreshOffset_0_0value);
                    break;
                }
                default: {
                    this.refreshOffset((undefined as double | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.pullToRefresh(modifier._pullToRefresh_0_0value);
                    break;
                }
                default: {
                    this.pullToRefresh((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.onOffsetChange(modifier._onOffsetChange_0_0value);
                    break;
                }
                default: {
                    this.onOffsetChange((undefined as arkui_component_common_Callback<double, void> | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1:
                case 3: {
                    this.pullDownRatio(modifier._pullDownRatio_0_0value);
                    break;
                }
                default: {
                    this.pullDownRatio((undefined as double | undefined));
                }
            }
        }
    }
    onStateChange(value: ((state: RefreshStatus) => void) | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._onStateChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    onRefreshing(value: (() => void) | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._onRefreshing_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    refreshOffset(value: double | undefined): this {
        if (((this._flagArray[2]) == (0)) || ((this._refreshOffset_0_0value) !== (value))) {
            this._flagArray[2] = 1
            this._refreshOffset_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    pullToRefresh(value: boolean | undefined): this {
        if (((this._flagArray[3]) == (0)) || ((this._pullToRefresh_0_0value) !== (value))) {
            this._flagArray[3] = 1
            this._pullToRefresh_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    onOffsetChange(value: arkui_component_common_Callback<double, void> | undefined): this {
        if (((this._flagArray[4]) == (0)) || (true)) {
            this._flagArray[4] = 1
            this._onOffsetChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    pullDownRatio(value: double | undefined): this {
        if (((this._flagArray[5]) == (0)) || ((this._pullDownRatio_0_0value) !== (value))) {
            this._flagArray[5] = 1
            this._pullDownRatio_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RefreshAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

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
import { ArkXComponentPeer, XComponentAttribute } from './component/xcomponent'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod } from './component/common'
import { VoidCallback } from './component/units'
export class XComponentModifier extends CommonMethodModifier implements XComponentAttribute,AttributeModifier<XComponentAttribute> {
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
    applyNormalAttribute(instance: XComponentAttribute): void { }
    applyPressedAttribute(instance: XComponentAttribute): void { }
    applyFocusedAttribute(instance: XComponentAttribute): void { }
    applyDisabledAttribute(instance: XComponentAttribute): void { }
    applySelectedAttribute(instance: XComponentAttribute): void { }
    public _onLoad_0_0value?: VoidCallback | undefined
    public _onDestroy_0_0value?: VoidCallback | undefined
    public _enableAnalyzer_0_0value?: boolean | undefined
    public _enableSecure_0_0value?: boolean | undefined
    public _enableTransparentLayer_0_0value?: boolean | undefined
    public _hdrBrightness_0_0value?: double | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkXComponentPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkXComponentPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setOnLoadAttribute((this._onLoad_0_0value as VoidCallback | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setOnLoadAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setOnDestroyAttribute((this._onDestroy_0_0value as VoidCallback | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setOnDestroyAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setEnableAnalyzerAttribute((this._enableAnalyzer_0_0value as boolean | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setEnableAnalyzerAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setEnableSecureAttribute((this._enableSecure_0_0value as boolean | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setEnableSecureAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setEnableTransparentLayerAttribute((this._enableTransparentLayer_0_0value as boolean | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setEnableTransparentLayerAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setHdrBrightnessAttribute((this._hdrBrightness_0_0value as double | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setHdrBrightnessAttribute((undefined as double | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: XComponentModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: XComponentModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.onLoad(modifier._onLoad_0_0value);
                    break;
                }
                default: {
                    this.onLoad((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.onDestroy(modifier._onDestroy_0_0value);
                    break;
                }
                default: {
                    this.onDestroy((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.enableAnalyzer(modifier._enableAnalyzer_0_0value);
                    break;
                }
                default: {
                    this.enableAnalyzer((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.enableSecure(modifier._enableSecure_0_0value);
                    break;
                }
                default: {
                    this.enableSecure((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.enableTransparentLayer(modifier._enableTransparentLayer_0_0value);
                    break;
                }
                default: {
                    this.enableTransparentLayer((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1:
                case 3: {
                    this.hdrBrightness(modifier._hdrBrightness_0_0value);
                    break;
                }
                default: {
                    this.hdrBrightness((undefined as double | undefined));
                }
            }
        }
    }
    onLoad(value: VoidCallback | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._onLoad_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    onDestroy(value: VoidCallback | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._onDestroy_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    enableAnalyzer(value: boolean | undefined): this {
        if (((this._flagArray[2]) == (0)) || ((this._enableAnalyzer_0_0value) !== (value))) {
            this._flagArray[2] = 1
            this._enableAnalyzer_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    enableSecure(value: boolean | undefined): this {
        if (((this._flagArray[3]) == (0)) || ((this._enableSecure_0_0value) !== (value))) {
            this._flagArray[3] = 1
            this._enableSecure_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    enableTransparentLayer(value: boolean | undefined): this {
        if (((this._flagArray[4]) == (0)) || ((this._enableTransparentLayer_0_0value) !== (value))) {
            this._flagArray[4] = 1
            this._enableTransparentLayer_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    hdrBrightness(value: double | undefined): this {
        if (((this._flagArray[5]) == (0)) || ((this._hdrBrightness_0_0value) !== (value))) {
            this._flagArray[5] = 1
            this._hdrBrightness_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<XComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

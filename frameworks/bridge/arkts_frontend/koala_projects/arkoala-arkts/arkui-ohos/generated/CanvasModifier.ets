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
import { ArkCanvasPeer, CanvasAttribute } from './component/canvas'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod } from './component/common'
import { VoidCallback } from './component/units'
export class CanvasModifier extends CommonMethodModifier implements CanvasAttribute,AttributeModifier<CanvasAttribute> {
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
    applyNormalAttribute(instance: CanvasAttribute): void { }
    applyPressedAttribute(instance: CanvasAttribute): void { }
    applyFocusedAttribute(instance: CanvasAttribute): void { }
    applyDisabledAttribute(instance: CanvasAttribute): void { }
    applySelectedAttribute(instance: CanvasAttribute): void { }
    public _onReady_0_0value?: VoidCallback | undefined
    public _enableAnalyzer_0_0value?: boolean | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkCanvasPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkCanvasPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setOnReadyAttribute((this._onReady_0_0value as VoidCallback | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setOnReadyAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setEnableAnalyzerAttribute((this._enableAnalyzer_0_0value as boolean | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setEnableAnalyzerAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: CanvasModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: CanvasModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.onReady(modifier._onReady_0_0value);
                    break;
                }
                default: {
                    this.onReady((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
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
    }
    onReady(value: VoidCallback | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._onReady_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    enableAnalyzer(value: boolean | undefined): this {
        if (((this._flagArray[1]) == (0)) || ((this._enableAnalyzer_0_0value) !== (value))) {
            this._flagArray[1] = 1
            this._enableAnalyzer_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<CanvasAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

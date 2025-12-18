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
import { ArkGridRowPeer, GridRowAttribute } from './component/gridRow'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod } from './component/common'
import { ItemAlign } from './component/enums'
export class GridRowModifier extends CommonMethodModifier implements GridRowAttribute,AttributeModifier<GridRowAttribute> {
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
    applyNormalAttribute(instance: GridRowAttribute): void { }
    applyPressedAttribute(instance: GridRowAttribute): void { }
    applyFocusedAttribute(instance: GridRowAttribute): void { }
    applyDisabledAttribute(instance: GridRowAttribute): void { }
    applySelectedAttribute(instance: GridRowAttribute): void { }
    public _onBreakpointChange_0_0value?: ((breakpoints: string) => void) | undefined
    public _alignItems_0_0value?: ItemAlign | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkGridRowPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkGridRowPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setOnBreakpointChangeAttribute((this._onBreakpointChange_0_0value as ((breakpoints: string) => void) | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setOnBreakpointChangeAttribute((undefined as ((breakpoints: string) => void) | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setAlignItemsAttribute((this._alignItems_0_0value as ItemAlign | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setAlignItemsAttribute((undefined as ItemAlign | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: GridRowModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: GridRowModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.onBreakpointChange(modifier._onBreakpointChange_0_0value);
                    break;
                }
                default: {
                    this.onBreakpointChange((undefined as ((breakpoints: string) => void) | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.alignItems(modifier._alignItems_0_0value);
                    break;
                }
                default: {
                    this.alignItems((undefined as ItemAlign | undefined));
                }
            }
        }
    }
    onBreakpointChange(value: ((breakpoints: string) => void) | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._onBreakpointChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    alignItems(value: ItemAlign | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._alignItems_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<GridRowAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

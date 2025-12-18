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

import { SecurityComponentMethodModifier } from './SecurityComponentMethodModifier'
import { AttributeModifier, extractors } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkPasteButtonPeer, PasteButtonCallback, PasteButtonOnClickResult, PasteButtonAttribute } from './component/pasteButton'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { SecurityComponentMethod } from './component/securityComponent'
import { ClickEvent } from './component/common'
import { BusinessError } from '@ohos.base'
export class PasteButtonModifier extends SecurityComponentMethodModifier implements PasteButtonAttribute,AttributeModifier<PasteButtonAttribute> {
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
    applyNormalAttribute(instance: PasteButtonAttribute): void { }
    applyPressedAttribute(instance: PasteButtonAttribute): void { }
    applyFocusedAttribute(instance: PasteButtonAttribute): void { }
    applyDisabledAttribute(instance: PasteButtonAttribute): void { }
    applySelectedAttribute(instance: PasteButtonAttribute): void { }
    public _onClick_0_0value?: PasteButtonCallback | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkPasteButtonPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkPasteButtonPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setOnClickAttribute((this._onClick_0_0value as PasteButtonCallback | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setOnClickAttribute((undefined as PasteButtonCallback | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: PasteButtonModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: PasteButtonModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.onClick(modifier._onClick_0_0value);
                    break;
                }
                default: {
                    this.onClick((undefined as PasteButtonCallback | undefined));
                }
            }
        }
    }
    onClick(value: PasteButtonCallback | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._onClick_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<PasteButtonAttribute> | AttributeModifier<SecurityComponentMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

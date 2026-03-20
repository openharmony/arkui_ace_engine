/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
import { ArkWithThemePeer, WithThemeAttribute } from './component/withTheme'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
export class WithThemeModifier implements WithThemeAttribute,AttributeModifier<WithThemeAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState;
    _addr: ArrayBuffer = new ArrayBuffer(4096);
    private _flagArray: Uint8Array = new Uint8Array(this._addr);
    constructor() {
        this._flagArray.fill(0);
    }
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: WithThemeAttribute): void { }
    applyPressedAttribute(instance: WithThemeAttribute): void { }
    applyFocusedAttribute(instance: WithThemeAttribute): void { }
    applyDisabledAttribute(instance: WithThemeAttribute): void { }
    applySelectedAttribute(instance: WithThemeAttribute): void { }
    public _debugLine_0_0value?: string
    public _debugLine_0_1value?: string | undefined
    applyModifierPatch(node: object): void {
        this._state.addRef()
        const peer = node as ArkWithThemePeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkWithThemePeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setDebugLineAttribute((this._debugLine_0_0value as string), (this._debugLine_0_1value as string | undefined));
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
    }
    mergeModifier(modifier: WithThemeModifier): void {
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: WithThemeModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.debugLine((modifier._debugLine_0_0value as string), (modifier._debugLine_0_1value as string | undefined));
                    break;
                }
                default: {
                }
            }
        }
    }
    debugLine(sourceLine: string, moduleName?: string): this {
        if (((this._flagArray[0]) == (0)) || ((this._debugLine_0_0value) !== (sourceLine)) || ((this._debugLine_0_1value) !== (moduleName))) {
            this._flagArray[0] = 1
            this._debugLine_0_0value = sourceLine
            this._debugLine_0_1value = moduleName
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<WithThemeAttribute> | undefined): this {
        throw new Error('Not implemented')
    }
}

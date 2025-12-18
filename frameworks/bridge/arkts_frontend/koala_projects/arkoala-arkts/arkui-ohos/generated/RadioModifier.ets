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
import { AttributeModifier, ContentModifier, hookRadioContentModifier } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkRadioPeer, OnRadioChangeCallback, RadioStyle, RadioConfiguration, RadioAttribute } from './component/radio'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod, Bindable } from './component/common'
export class RadioModifier extends CommonMethodModifier implements RadioAttribute,AttributeModifier<RadioAttribute> {
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
    applyNormalAttribute(instance: RadioAttribute): void { }
    applyPressedAttribute(instance: RadioAttribute): void { }
    applyFocusedAttribute(instance: RadioAttribute): void { }
    applyDisabledAttribute(instance: RadioAttribute): void { }
    applySelectedAttribute(instance: RadioAttribute): void { }
    public _checked_0_0value?: boolean | Bindable<boolean> | undefined
    public _onChange_0_0value?: OnRadioChangeCallback | undefined
    public _radioStyle_0_0value?: RadioStyle | undefined
    public _contentModifier_0_0value?: ContentModifier<RadioConfiguration> | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkRadioPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkRadioPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setCheckedAttribute((this._checked_0_0value as boolean | Bindable<boolean> | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setCheckedAttribute((undefined as boolean | Bindable<boolean> | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as OnRadioChangeCallback | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setOnChangeAttribute((undefined as OnRadioChangeCallback | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setRadioStyleAttribute((this._radioStyle_0_0value as RadioStyle | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setRadioStyleAttribute((undefined as RadioStyle | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    hookRadioContentModifier(peer, (this._contentModifier_0_0value as ContentModifier<RadioConfiguration> | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    hookRadioContentModifier(peer, (undefined as ContentModifier<RadioConfiguration> | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: RadioModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: RadioModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.checked(modifier._checked_0_0value);
                    break;
                }
                default: {
                    this.checked((undefined as boolean | Bindable<boolean> | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.onChange(modifier._onChange_0_0value);
                    break;
                }
                default: {
                    this.onChange((undefined as OnRadioChangeCallback | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.radioStyle(modifier._radioStyle_0_0value);
                    break;
                }
                default: {
                    this.radioStyle((undefined as RadioStyle | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.contentModifier(modifier._contentModifier_0_0value);
                    break;
                }
                default: {
                    this.contentModifier((undefined as ContentModifier<RadioConfiguration> | undefined));
                }
            }
        }
    }
    checked(value: boolean | Bindable<boolean> | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._checked_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    onChange(value: OnRadioChangeCallback | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._onChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    radioStyle(value: RadioStyle | undefined): this {
        if (((this._flagArray[2]) == (0)) || (true)) {
            this._flagArray[2] = 1
            this._radioStyle_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    contentModifier(value: ContentModifier<RadioConfiguration> | undefined): this {
        if (((this._flagArray[3]) == (0)) || (true)) {
            this._flagArray[3] = 1
            this._contentModifier_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RadioAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

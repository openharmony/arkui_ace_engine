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
import { ArkQRCodePeer, QRCodeAttribute } from './component/qrcode'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod } from './component/common'
import { ResourceColor, Resource as arkui_component_units_Resource } from './component/units'
import { Color as arkui_component_enums_Color } from './component/enums'
import { Resource as global_resource_Resource } from 'global.resource'
export class QRCodeModifier extends CommonMethodModifier implements QRCodeAttribute,AttributeModifier<QRCodeAttribute> {
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
    applyNormalAttribute(instance: QRCodeAttribute): void { }
    applyPressedAttribute(instance: QRCodeAttribute): void { }
    applyFocusedAttribute(instance: QRCodeAttribute): void { }
    applyDisabledAttribute(instance: QRCodeAttribute): void { }
    applySelectedAttribute(instance: QRCodeAttribute): void { }
    public _color_0_0value?: ResourceColor | undefined
    public _backgroundColor_0_0value?: ResourceColor | undefined
    public _contentOpacity_0_0value?: double | global_resource_Resource | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkQRCodePeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkQRCodePeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setColorAttribute((this._color_0_0value as ResourceColor | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setBackgroundColorAttribute((this._backgroundColor_0_0value as ResourceColor | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setBackgroundColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setContentOpacityAttribute((this._contentOpacity_0_0value as double | global_resource_Resource | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setContentOpacityAttribute((undefined as double | global_resource_Resource | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: QRCodeModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: QRCodeModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.color(modifier._color_0_0value);
                    break;
                }
                default: {
                    this.color((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.backgroundColor(modifier._backgroundColor_0_0value);
                    break;
                }
                default: {
                    this.backgroundColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.contentOpacity(modifier._contentOpacity_0_0value);
                    break;
                }
                default: {
                    this.contentOpacity((undefined as double | global_resource_Resource | undefined));
                }
            }
        }
    }
    color(value: ResourceColor | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._color_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    backgroundColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._backgroundColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    contentOpacity(value: double | global_resource_Resource | undefined): this {
        if (((this._flagArray[2]) == (0)) || (true)) {
            this._flagArray[2] = 1
            this._contentOpacity_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<QRCodeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

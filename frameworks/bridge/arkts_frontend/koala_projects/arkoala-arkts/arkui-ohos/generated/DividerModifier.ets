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
import { ArkDividerPeer, DividerAttribute } from './component/divider'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod } from './component/common'
import { ResourceColor, Resource as arkui_component_units_Resource } from './component/units'
import { Color as arkui_component_enums_Color, LineCapStyle } from './component/enums'
import { Resource as global_resource_Resource } from 'global.resource'
export class DividerModifier extends CommonMethodModifier implements DividerAttribute,AttributeModifier<DividerAttribute> {
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
    applyNormalAttribute(instance: DividerAttribute): void { }
    applyPressedAttribute(instance: DividerAttribute): void { }
    applyFocusedAttribute(instance: DividerAttribute): void { }
    applyDisabledAttribute(instance: DividerAttribute): void { }
    applySelectedAttribute(instance: DividerAttribute): void { }
    public _vertical_0_0value?: boolean | undefined
    public _color_0_0value?: ResourceColor | undefined
    public _strokeWidth_0_0value?: double | string | undefined
    public _lineCap_0_0value?: LineCapStyle | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkDividerPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkDividerPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setVerticalAttribute((this._vertical_0_0value as boolean | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setVerticalAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setColorAttribute((this._color_0_0value as ResourceColor | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setStrokeWidthAttribute((this._strokeWidth_0_0value as double | string | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setStrokeWidthAttribute((undefined as double | string | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setLineCapAttribute((this._lineCap_0_0value as LineCapStyle | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setLineCapAttribute((undefined as LineCapStyle | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: DividerModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: DividerModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.vertical(modifier._vertical_0_0value);
                    break;
                }
                default: {
                    this.vertical((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
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
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.strokeWidth(modifier._strokeWidth_0_0value);
                    break;
                }
                default: {
                    this.strokeWidth((undefined as double | string | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.lineCap(modifier._lineCap_0_0value);
                    break;
                }
                default: {
                    this.lineCap((undefined as LineCapStyle | undefined));
                }
            }
        }
    }
    vertical(value: boolean | undefined): this {
        if (((this._flagArray[0]) == (0)) || ((this._vertical_0_0value) !== (value))) {
            this._flagArray[0] = 1
            this._vertical_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    color(value: ResourceColor | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._color_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    strokeWidth(value: double | string | undefined): this {
        if (((this._flagArray[2]) == (0)) || ((this._strokeWidth_0_0value) !== (value))) {
            this._flagArray[2] = 1
            this._strokeWidth_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    lineCap(value: LineCapStyle | undefined): this {
        if (((this._flagArray[3]) == (0)) || (true)) {
            this._flagArray[3] = 1
            this._lineCap_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<DividerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

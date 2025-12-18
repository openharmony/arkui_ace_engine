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
import { ArkMarqueePeer, MarqueeAttribute } from './component/marquee'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod } from './component/common'
import { ResourceColor, Resource as arkui_component_units_Resource, Length } from './component/units'
import { Color as arkui_component_enums_Color, FontWeight, MarqueeUpdateStrategy } from './component/enums'
import { Resource as global_resource_Resource } from 'global.resource'
export class MarqueeModifier extends CommonMethodModifier implements MarqueeAttribute,AttributeModifier<MarqueeAttribute> {
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
    applyNormalAttribute(instance: MarqueeAttribute): void { }
    applyPressedAttribute(instance: MarqueeAttribute): void { }
    applyFocusedAttribute(instance: MarqueeAttribute): void { }
    applyDisabledAttribute(instance: MarqueeAttribute): void { }
    applySelectedAttribute(instance: MarqueeAttribute): void { }
    public _fontColor_0_0value?: ResourceColor | undefined
    public _fontSize_0_0value?: Length | undefined
    public _allowScale_0_0value?: boolean | undefined
    public _fontWeight_0_0value?: int32 | FontWeight | string | undefined
    public _fontFamily_0_0value?: string | global_resource_Resource | undefined
    public _marqueeUpdateStrategy_0_0value?: MarqueeUpdateStrategy | undefined
    public _onStart_0_0value?: (() => void) | undefined
    public _onBounce_0_0value?: (() => void) | undefined
    public _onFinish_0_0value?: (() => void) | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkMarqueePeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkMarqueePeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setFontColorAttribute((this._fontColor_0_0value as ResourceColor | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setFontColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setFontSizeAttribute((this._fontSize_0_0value as Length | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setFontSizeAttribute((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setAllowScaleAttribute((this._allowScale_0_0value as boolean | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setAllowScaleAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setFontWeightAttribute((this._fontWeight_0_0value as int32 | FontWeight | string | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setFontWeightAttribute((undefined as int32 | FontWeight | string | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setFontFamilyAttribute((this._fontFamily_0_0value as string | global_resource_Resource | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setFontFamilyAttribute((undefined as string | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setMarqueeUpdateStrategyAttribute((this._marqueeUpdateStrategy_0_0value as MarqueeUpdateStrategy | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setMarqueeUpdateStrategyAttribute((undefined as MarqueeUpdateStrategy | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1: {
                    peer.setOnStartAttribute((this._onStart_0_0value as (() => void) | undefined));
                    flagArray[6] = 2;
                    break;
                }
                case 3: {
                    flagArray[6] = 2;
                    break;
                }
                default: {
                    flagArray[6] = 0;
                    peer.setOnStartAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1: {
                    peer.setOnBounceAttribute((this._onBounce_0_0value as (() => void) | undefined));
                    flagArray[7] = 2;
                    break;
                }
                case 3: {
                    flagArray[7] = 2;
                    break;
                }
                default: {
                    flagArray[7] = 0;
                    peer.setOnBounceAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1: {
                    peer.setOnFinishAttribute((this._onFinish_0_0value as (() => void) | undefined));
                    flagArray[8] = 2;
                    break;
                }
                case 3: {
                    flagArray[8] = 2;
                    break;
                }
                default: {
                    flagArray[8] = 0;
                    peer.setOnFinishAttribute((undefined as (() => void) | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: MarqueeModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: MarqueeModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.fontColor(modifier._fontColor_0_0value);
                    break;
                }
                default: {
                    this.fontColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.fontSize(modifier._fontSize_0_0value);
                    break;
                }
                default: {
                    this.fontSize((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.allowScale(modifier._allowScale_0_0value);
                    break;
                }
                default: {
                    this.allowScale((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.fontWeight(modifier._fontWeight_0_0value);
                    break;
                }
                default: {
                    this.fontWeight((undefined as int32 | FontWeight | string | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.fontFamily(modifier._fontFamily_0_0value);
                    break;
                }
                default: {
                    this.fontFamily((undefined as string | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1:
                case 3: {
                    this.marqueeUpdateStrategy(modifier._marqueeUpdateStrategy_0_0value);
                    break;
                }
                default: {
                    this.marqueeUpdateStrategy((undefined as MarqueeUpdateStrategy | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1:
                case 3: {
                    this.onStart(modifier._onStart_0_0value);
                    break;
                }
                default: {
                    this.onStart((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1:
                case 3: {
                    this.onBounce(modifier._onBounce_0_0value);
                    break;
                }
                default: {
                    this.onBounce((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1:
                case 3: {
                    this.onFinish(modifier._onFinish_0_0value);
                    break;
                }
                default: {
                    this.onFinish((undefined as (() => void) | undefined));
                }
            }
        }
    }
    fontColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._fontColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    fontSize(value: Length | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._fontSize_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    allowScale(value: boolean | undefined): this {
        if (((this._flagArray[2]) == (0)) || ((this._allowScale_0_0value) !== (value))) {
            this._flagArray[2] = 1
            this._allowScale_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    fontWeight(value: int32 | FontWeight | string | undefined): this {
        if (((this._flagArray[3]) == (0)) || (true)) {
            this._flagArray[3] = 1
            this._fontWeight_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    fontFamily(value: string | global_resource_Resource | undefined): this {
        if (((this._flagArray[4]) == (0)) || (true)) {
            this._flagArray[4] = 1
            this._fontFamily_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    marqueeUpdateStrategy(value: MarqueeUpdateStrategy | undefined): this {
        if (((this._flagArray[5]) == (0)) || (true)) {
            this._flagArray[5] = 1
            this._marqueeUpdateStrategy_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    onStart(value: (() => void) | undefined): this {
        if (((this._flagArray[6]) == (0)) || (true)) {
            this._flagArray[6] = 1
            this._onStart_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[6] = 3
        }
        return this
    }
    onBounce(value: (() => void) | undefined): this {
        if (((this._flagArray[7]) == (0)) || (true)) {
            this._flagArray[7] = 1
            this._onBounce_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[7] = 3
        }
        return this
    }
    onFinish(value: (() => void) | undefined): this {
        if (((this._flagArray[8]) == (0)) || (true)) {
            this._flagArray[8] = 1
            this._onFinish_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[8] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<MarqueeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

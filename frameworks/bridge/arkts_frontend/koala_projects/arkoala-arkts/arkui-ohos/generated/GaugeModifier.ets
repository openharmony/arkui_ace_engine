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
import { AttributeModifier, ContentModifier, hookGaugeContentModifier } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkGaugePeer, GaugeShadowOptions, GaugeIndicatorOptions, GaugeConfiguration, GaugeAttribute } from './component/gauge'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod } from './component/common'
import { ResourceColor, Resource as arkui_component_units_Resource, Length } from './component/units'
import { Color as arkui_component_enums_Color } from './component/enums'
import { Resource as global_resource_Resource } from 'global.resource'
import { LinearGradient } from './component/dataPanel'
import { CustomBuilder } from './component/builder'
export class GaugeModifier extends CommonMethodModifier implements GaugeAttribute,AttributeModifier<GaugeAttribute> {
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
    applyNormalAttribute(instance: GaugeAttribute): void { }
    applyPressedAttribute(instance: GaugeAttribute): void { }
    applyFocusedAttribute(instance: GaugeAttribute): void { }
    applyDisabledAttribute(instance: GaugeAttribute): void { }
    applySelectedAttribute(instance: GaugeAttribute): void { }
    public _value_0_0value?: double | undefined
    public _startAngle_0_0value?: double | undefined
    public _endAngle_0_0value?: double | undefined
    public _colors_0_0value?: ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, double ]> | undefined
    public _strokeWidth_0_0value?: Length | undefined
    public _description_0_0value?: CustomBuilder | null | undefined
    public _trackShadow_0_0value?: GaugeShadowOptions | null | undefined
    public _indicator_0_0value?: GaugeIndicatorOptions | null | undefined
    public _privacySensitive_0_0value?: boolean | undefined
    public _contentModifier_0_0value?: ContentModifier<GaugeConfiguration> | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkGaugePeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkGaugePeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setValueAttribute((this._value_0_0value as double | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setValueAttribute((undefined as double | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setStartAngleAttribute((this._startAngle_0_0value as double | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setStartAngleAttribute((undefined as double | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setEndAngleAttribute((this._endAngle_0_0value as double | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setEndAngleAttribute((undefined as double | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setColorsAttribute((this._colors_0_0value as ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, double ]> | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setColorsAttribute((undefined as ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, double ]> | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setStrokeWidthAttribute((this._strokeWidth_0_0value as Length | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setStrokeWidthAttribute((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setDescriptionAttribute((this._description_0_0value as CustomBuilder | null | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setDescriptionAttribute((undefined as CustomBuilder | null | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1: {
                    peer.setTrackShadowAttribute((this._trackShadow_0_0value as GaugeShadowOptions | null | undefined));
                    flagArray[6] = 2;
                    break;
                }
                case 3: {
                    flagArray[6] = 2;
                    break;
                }
                default: {
                    flagArray[6] = 0;
                    peer.setTrackShadowAttribute((undefined as GaugeShadowOptions | null | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1: {
                    peer.setIndicatorAttribute((this._indicator_0_0value as GaugeIndicatorOptions | null | undefined));
                    flagArray[7] = 2;
                    break;
                }
                case 3: {
                    flagArray[7] = 2;
                    break;
                }
                default: {
                    flagArray[7] = 0;
                    peer.setIndicatorAttribute((undefined as GaugeIndicatorOptions | null | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1: {
                    peer.setPrivacySensitiveAttribute((this._privacySensitive_0_0value as boolean | undefined));
                    flagArray[8] = 2;
                    break;
                }
                case 3: {
                    flagArray[8] = 2;
                    break;
                }
                default: {
                    flagArray[8] = 0;
                    peer.setPrivacySensitiveAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1: {
                    hookGaugeContentModifier(peer, (this._contentModifier_0_0value as ContentModifier<GaugeConfiguration> | undefined));
                    flagArray[9] = 2;
                    break;
                }
                case 3: {
                    flagArray[9] = 2;
                    break;
                }
                default: {
                    flagArray[9] = 0;
                    hookGaugeContentModifier(peer, (undefined as ContentModifier<GaugeConfiguration> | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: GaugeModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: GaugeModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.value(modifier._value_0_0value);
                    break;
                }
                default: {
                    this.value((undefined as double | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.startAngle(modifier._startAngle_0_0value);
                    break;
                }
                default: {
                    this.startAngle((undefined as double | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.endAngle(modifier._endAngle_0_0value);
                    break;
                }
                default: {
                    this.endAngle((undefined as double | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.colors(modifier._colors_0_0value);
                    break;
                }
                default: {
                    this.colors((undefined as ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, double ]> | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.strokeWidth(modifier._strokeWidth_0_0value);
                    break;
                }
                default: {
                    this.strokeWidth((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1:
                case 3: {
                    this.description(modifier._description_0_0value);
                    break;
                }
                default: {
                    this.description((undefined as CustomBuilder | null | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1:
                case 3: {
                    this.trackShadow(modifier._trackShadow_0_0value);
                    break;
                }
                default: {
                    this.trackShadow((undefined as GaugeShadowOptions | null | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1:
                case 3: {
                    this.indicator(modifier._indicator_0_0value);
                    break;
                }
                default: {
                    this.indicator((undefined as GaugeIndicatorOptions | null | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1:
                case 3: {
                    this.privacySensitive(modifier._privacySensitive_0_0value);
                    break;
                }
                default: {
                    this.privacySensitive((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1:
                case 3: {
                    this.contentModifier(modifier._contentModifier_0_0value);
                    break;
                }
                default: {
                    this.contentModifier((undefined as ContentModifier<GaugeConfiguration> | undefined));
                }
            }
        }
    }
    value(value: double | undefined): this {
        if (((this._flagArray[0]) == (0)) || ((this._value_0_0value) !== (value))) {
            this._flagArray[0] = 1
            this._value_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    startAngle(value: double | undefined): this {
        if (((this._flagArray[1]) == (0)) || ((this._startAngle_0_0value) !== (value))) {
            this._flagArray[1] = 1
            this._startAngle_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    endAngle(value: double | undefined): this {
        if (((this._flagArray[2]) == (0)) || ((this._endAngle_0_0value) !== (value))) {
            this._flagArray[2] = 1
            this._endAngle_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    colors(value: ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, double ]> | undefined): this {
        if (((this._flagArray[3]) == (0)) || (true)) {
            this._flagArray[3] = 1
            this._colors_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    strokeWidth(value: Length | undefined): this {
        if (((this._flagArray[4]) == (0)) || (true)) {
            this._flagArray[4] = 1
            this._strokeWidth_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    description(value: CustomBuilder | null | undefined): this {
        if (((this._flagArray[5]) == (0)) || (true)) {
            this._flagArray[5] = 1
            this._description_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    trackShadow(value: GaugeShadowOptions | null | undefined): this {
        if (((this._flagArray[6]) == (0)) || (true)) {
            this._flagArray[6] = 1
            this._trackShadow_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[6] = 3
        }
        return this
    }
    indicator(value: GaugeIndicatorOptions | null | undefined): this {
        if (((this._flagArray[7]) == (0)) || (true)) {
            this._flagArray[7] = 1
            this._indicator_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[7] = 3
        }
        return this
    }
    privacySensitive(value: boolean | undefined): this {
        if (((this._flagArray[8]) == (0)) || ((this._privacySensitive_0_0value) !== (value))) {
            this._flagArray[8] = 1
            this._privacySensitive_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[8] = 3
        }
        return this
    }
    contentModifier(value: ContentModifier<GaugeConfiguration> | undefined): this {
        if (((this._flagArray[9]) == (0)) || (true)) {
            this._flagArray[9] = 1
            this._contentModifier_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[9] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<GaugeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

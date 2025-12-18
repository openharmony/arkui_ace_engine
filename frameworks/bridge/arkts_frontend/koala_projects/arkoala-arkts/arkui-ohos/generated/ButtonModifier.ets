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
import { AttributeModifier, ContentModifier, hookButtonContentModifier } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkButtonPeer, ButtonType, ButtonStyleMode, ControlSize, ButtonRole, ButtonConfiguration, ButtonLabelStyle, ButtonAttribute } from './component/button'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod } from './component/common'
import { ResourceColor, Resource as arkui_component_units_Resource, Length } from './component/units'
import { Color as arkui_component_enums_Color, FontWeight, FontStyle } from './component/enums'
import { Resource as global_resource_Resource } from 'global.resource'
export class ButtonModifier extends CommonMethodModifier implements ButtonAttribute,AttributeModifier<ButtonAttribute> {
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
    applyNormalAttribute(instance: ButtonAttribute): void { }
    applyPressedAttribute(instance: ButtonAttribute): void { }
    applyFocusedAttribute(instance: ButtonAttribute): void { }
    applyDisabledAttribute(instance: ButtonAttribute): void { }
    applySelectedAttribute(instance: ButtonAttribute): void { }
    public _type_0_0value?: ButtonType | undefined
    public _stateEffect_0_0value?: boolean | undefined
    public _buttonStyle_0_0value?: ButtonStyleMode | undefined
    public _controlSize_0_0value?: ControlSize | undefined
    public _role_0_0value?: ButtonRole | undefined
    public _fontColor_0_0value?: ResourceColor | undefined
    public _fontSize_0_0value?: Length | undefined
    public _fontWeight_0_0value?: int32 | FontWeight | string | undefined
    public _fontStyle_0_0value?: FontStyle | undefined
    public _fontFamily_0_0value?: string | global_resource_Resource | undefined
    public _contentModifier_0_0value?: ContentModifier<ButtonConfiguration> | undefined
    public _labelStyle_0_0value?: ButtonLabelStyle | undefined
    public _minFontScale_0_0value?: double | global_resource_Resource | undefined
    public _maxFontScale_0_0value?: double | global_resource_Resource | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkButtonPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkButtonPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setTypeAttribute((this._type_0_0value as ButtonType | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setTypeAttribute((undefined as ButtonType | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setStateEffectAttribute((this._stateEffect_0_0value as boolean | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setStateEffectAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setButtonStyleAttribute((this._buttonStyle_0_0value as ButtonStyleMode | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setButtonStyleAttribute((undefined as ButtonStyleMode | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setControlSizeAttribute((this._controlSize_0_0value as ControlSize | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setControlSizeAttribute((undefined as ControlSize | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setRoleAttribute((this._role_0_0value as ButtonRole | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setRoleAttribute((undefined as ButtonRole | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setFontColorAttribute((this._fontColor_0_0value as ResourceColor | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setFontColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1: {
                    peer.setFontSizeAttribute((this._fontSize_0_0value as Length | undefined));
                    flagArray[6] = 2;
                    break;
                }
                case 3: {
                    flagArray[6] = 2;
                    break;
                }
                default: {
                    flagArray[6] = 0;
                    peer.setFontSizeAttribute((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1: {
                    peer.setFontWeightAttribute((this._fontWeight_0_0value as int32 | FontWeight | string | undefined));
                    flagArray[7] = 2;
                    break;
                }
                case 3: {
                    flagArray[7] = 2;
                    break;
                }
                default: {
                    flagArray[7] = 0;
                    peer.setFontWeightAttribute((undefined as int32 | FontWeight | string | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1: {
                    peer.setFontStyleAttribute((this._fontStyle_0_0value as FontStyle | undefined));
                    flagArray[8] = 2;
                    break;
                }
                case 3: {
                    flagArray[8] = 2;
                    break;
                }
                default: {
                    flagArray[8] = 0;
                    peer.setFontStyleAttribute((undefined as FontStyle | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1: {
                    peer.setFontFamilyAttribute((this._fontFamily_0_0value as string | global_resource_Resource | undefined));
                    flagArray[9] = 2;
                    break;
                }
                case 3: {
                    flagArray[9] = 2;
                    break;
                }
                default: {
                    flagArray[9] = 0;
                    peer.setFontFamilyAttribute((undefined as string | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1: {
                    hookButtonContentModifier(peer, (this._contentModifier_0_0value as ContentModifier<ButtonConfiguration> | undefined));
                    flagArray[10] = 2;
                    break;
                }
                case 3: {
                    flagArray[10] = 2;
                    break;
                }
                default: {
                    flagArray[10] = 0;
                    hookButtonContentModifier(peer, (undefined as ContentModifier<ButtonConfiguration> | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1: {
                    peer.setLabelStyleAttribute((this._labelStyle_0_0value as ButtonLabelStyle | undefined));
                    flagArray[11] = 2;
                    break;
                }
                case 3: {
                    flagArray[11] = 2;
                    break;
                }
                default: {
                    flagArray[11] = 0;
                    peer.setLabelStyleAttribute((undefined as ButtonLabelStyle | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1: {
                    peer.setMinFontScaleAttribute((this._minFontScale_0_0value as double | global_resource_Resource | undefined));
                    flagArray[12] = 2;
                    break;
                }
                case 3: {
                    flagArray[12] = 2;
                    break;
                }
                default: {
                    flagArray[12] = 0;
                    peer.setMinFontScaleAttribute((undefined as double | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1: {
                    peer.setMaxFontScaleAttribute((this._maxFontScale_0_0value as double | global_resource_Resource | undefined));
                    flagArray[13] = 2;
                    break;
                }
                case 3: {
                    flagArray[13] = 2;
                    break;
                }
                default: {
                    flagArray[13] = 0;
                    peer.setMaxFontScaleAttribute((undefined as double | global_resource_Resource | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: ButtonModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: ButtonModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.type(modifier._type_0_0value);
                    break;
                }
                default: {
                    this.type((undefined as ButtonType | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.stateEffect(modifier._stateEffect_0_0value);
                    break;
                }
                default: {
                    this.stateEffect((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.buttonStyle(modifier._buttonStyle_0_0value);
                    break;
                }
                default: {
                    this.buttonStyle((undefined as ButtonStyleMode | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.controlSize(modifier._controlSize_0_0value);
                    break;
                }
                default: {
                    this.controlSize((undefined as ControlSize | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.role(modifier._role_0_0value);
                    break;
                }
                default: {
                    this.role((undefined as ButtonRole | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
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
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
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
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
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
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1:
                case 3: {
                    this.fontStyle(modifier._fontStyle_0_0value);
                    break;
                }
                default: {
                    this.fontStyle((undefined as FontStyle | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
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
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1:
                case 3: {
                    this.contentModifier(modifier._contentModifier_0_0value);
                    break;
                }
                default: {
                    this.contentModifier((undefined as ContentModifier<ButtonConfiguration> | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1:
                case 3: {
                    this.labelStyle(modifier._labelStyle_0_0value);
                    break;
                }
                default: {
                    this.labelStyle((undefined as ButtonLabelStyle | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1:
                case 3: {
                    this.minFontScale(modifier._minFontScale_0_0value);
                    break;
                }
                default: {
                    this.minFontScale((undefined as double | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1:
                case 3: {
                    this.maxFontScale(modifier._maxFontScale_0_0value);
                    break;
                }
                default: {
                    this.maxFontScale((undefined as double | global_resource_Resource | undefined));
                }
            }
        }
    }
    type(value: ButtonType | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._type_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    stateEffect(value: boolean | undefined): this {
        if (((this._flagArray[1]) == (0)) || ((this._stateEffect_0_0value) !== (value))) {
            this._flagArray[1] = 1
            this._stateEffect_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    buttonStyle(value: ButtonStyleMode | undefined): this {
        if (((this._flagArray[2]) == (0)) || (true)) {
            this._flagArray[2] = 1
            this._buttonStyle_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    controlSize(value: ControlSize | undefined): this {
        if (((this._flagArray[3]) == (0)) || (true)) {
            this._flagArray[3] = 1
            this._controlSize_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    role(value: ButtonRole | undefined): this {
        if (((this._flagArray[4]) == (0)) || (true)) {
            this._flagArray[4] = 1
            this._role_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    fontColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[5]) == (0)) || (true)) {
            this._flagArray[5] = 1
            this._fontColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    fontSize(value: Length | undefined): this {
        if (((this._flagArray[6]) == (0)) || (true)) {
            this._flagArray[6] = 1
            this._fontSize_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[6] = 3
        }
        return this
    }
    fontWeight(value: int32 | FontWeight | string | undefined): this {
        if (((this._flagArray[7]) == (0)) || (true)) {
            this._flagArray[7] = 1
            this._fontWeight_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[7] = 3
        }
        return this
    }
    fontStyle(value: FontStyle | undefined): this {
        if (((this._flagArray[8]) == (0)) || (true)) {
            this._flagArray[8] = 1
            this._fontStyle_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[8] = 3
        }
        return this
    }
    fontFamily(value: string | global_resource_Resource | undefined): this {
        if (((this._flagArray[9]) == (0)) || (true)) {
            this._flagArray[9] = 1
            this._fontFamily_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[9] = 3
        }
        return this
    }
    contentModifier(value: ContentModifier<ButtonConfiguration> | undefined): this {
        if (((this._flagArray[10]) == (0)) || (true)) {
            this._flagArray[10] = 1
            this._contentModifier_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[10] = 3
        }
        return this
    }
    labelStyle(value: ButtonLabelStyle | undefined): this {
        if (((this._flagArray[11]) == (0)) || (true)) {
            this._flagArray[11] = 1
            this._labelStyle_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[11] = 3
        }
        return this
    }
    minFontScale(value: double | global_resource_Resource | undefined): this {
        if (((this._flagArray[12]) == (0)) || (true)) {
            this._flagArray[12] = 1
            this._minFontScale_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[12] = 3
        }
        return this
    }
    maxFontScale(value: double | global_resource_Resource | undefined): this {
        if (((this._flagArray[13]) == (0)) || (true)) {
            this._flagArray[13] = 1
            this._maxFontScale_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[13] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ButtonAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

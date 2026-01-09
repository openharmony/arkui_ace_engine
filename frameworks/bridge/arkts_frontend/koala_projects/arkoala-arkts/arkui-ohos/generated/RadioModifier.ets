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

import { CommonMethodModifier } from "./CommonMethodModifier"
import { ModifierState } from './CommonModifier'
import { AttributeModifier, ContentModifier, hookRadioContentModifier } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkRadioPeer, OnRadioChangeCallback, RadioStyle, RadioConfiguration, RadioAttribute } from "./component/radio"
import { int32 } from "@koalaui/common"
import { CommonMethod, Bindable } from "./component/common"
export class RadioModifier extends CommonMethodModifier implements RadioAttribute,AttributeModifier<RadioAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: RadioAttribute): void { }
    applyPressedAttribute(instance: RadioAttribute): void { }
    applyFocusedAttribute(instance: RadioAttribute): void { }
    applyDisabledAttribute(instance: RadioAttribute): void { }
    applySelectedAttribute(instance: RadioAttribute): void { }
    _checked_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _checked_0_0value?: boolean | Bindable<boolean> | undefined
    _onChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onChange_0_0value?: OnRadioChangeCallback | undefined
    _radioStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _radioStyle_0_0value?: RadioStyle | undefined
    _contentModifier_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _contentModifier_0_0value?: ContentModifier<RadioConfiguration> | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkRadioPeer;
        if (this._checked_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._checked_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCheckedAttribute((this._checked_0_0value as boolean | Bindable<boolean> | undefined));
                    this._checked_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._checked_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._checked_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCheckedAttribute((undefined as boolean | Bindable<boolean> | undefined));
                }
            }
        }
        if (this._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as OnRadioChangeCallback | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnChangeAttribute((undefined as OnRadioChangeCallback | undefined));
                }
            }
        }
        if (this._radioStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._radioStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRadioStyleAttribute((this._radioStyle_0_0value as RadioStyle | undefined));
                    this._radioStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._radioStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._radioStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRadioStyleAttribute((undefined as RadioStyle | undefined));
                }
            }
        }
        if (this._contentModifier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._contentModifier_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    hookRadioContentModifier(peer, (this._contentModifier_0_0value as ContentModifier<RadioConfiguration> | undefined));
                    this._contentModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._contentModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._contentModifier_0_flag = AttributeUpdaterFlag.INITIAL;
                    hookRadioContentModifier(peer, (undefined as ContentModifier<RadioConfiguration> | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: RadioModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._checked_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._checked_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.checked(modifier._checked_0_0value);
                    break;
                }
                default: {
                    this.checked((undefined as boolean | Bindable<boolean> | undefined));
                }
            }
        }
        if (modifier._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onChange(modifier._onChange_0_0value);
                    break;
                }
                default: {
                    this.onChange((undefined as OnRadioChangeCallback | undefined));
                }
            }
        }
        if (modifier._radioStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._radioStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.radioStyle(modifier._radioStyle_0_0value);
                    break;
                }
                default: {
                    this.radioStyle((undefined as RadioStyle | undefined));
                }
            }
        }
        if (modifier._contentModifier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._contentModifier_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
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
        if (((this._checked_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._checked_0_flag = AttributeUpdaterFlag.UPDATE
            this._checked_0_0value = value
            this._state.fireChange()
        } else
        {
            this._checked_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onChange(value: OnRadioChangeCallback | undefined): this {
        if (((this._onChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onChange_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    radioStyle(value: RadioStyle | undefined): this {
        if (((this._radioStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._radioStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._radioStyle_0_0value = value
            this._state.fireChange()
        } else
        {
            this._radioStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    contentModifier(value: ContentModifier<RadioConfiguration> | undefined): this {
        if (((this._contentModifier_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._contentModifier_0_0value) !== (value)))
        {
            this._contentModifier_0_flag = AttributeUpdaterFlag.UPDATE
            this._contentModifier_0_0value = value
        } else
        {
            this._contentModifier_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RadioAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

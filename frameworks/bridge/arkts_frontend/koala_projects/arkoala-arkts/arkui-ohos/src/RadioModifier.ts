/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { AttributeModifier, ResourceColor, Bindable } from './component';
import { ContentModifier } from './component/common';
import { ArkRadioPeer, OnRadioChangeCallback, RadioStyle, RadioConfiguration, RadioAttribute, ArkRadioComponent } from './component/radio';
import { CommonMethodModifier, AttributeUpdaterFlag } from './CommonMethodModifier';
import { RadioOpsHandWritten, hookRadioContentModifier } from './handwritten';
import { PeerNode } from './PeerNode';

export class RadioModifier extends CommonMethodModifier implements RadioAttribute, AttributeModifier<RadioAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyNormalAttribute(instance: RadioAttribute): void {}
    applyPressedAttribute(instance: RadioAttribute): void {}
    applyFocusedAttribute(instance: RadioAttribute): void {}
    applyDisabledAttribute(instance: RadioAttribute): void {}
    applySelectedAttribute(instance: RadioAttribute): void {}
    _checked_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _checked_0_0value?: boolean | Bindable<boolean> | undefined
    _onChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onChange_0_0value?: OnRadioChangeCallback | undefined
    _radioStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _radioStyle_0_0value?: RadioStyle | undefined
    _contentModifier_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _contentModifier_0_0value?: ContentModifier<RadioConfiguration> | undefined
    applyModifierPatch(value: PeerNode): void {
        super.applyModifierPatch(value)
        const peer = value as ArkRadioPeer
        if (this._checked_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._checked_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    if (typeof this._checked_0_0value === "boolean" || typeof this._checked_0_0value === "undefined") {
                        peer.checked0Attribute((this._checked_0_0value as boolean | undefined));
                    } else {
                        RadioOpsHandWritten.hookRadioAttributeCheckedImpl(peer.peer.ptr, (this._checked_0_0value as Bindable<boolean>));
                    }
                    this._checked_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._checked_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._checked_0_flag = AttributeUpdaterFlag.INITIAL;
                    if (typeof this._checked_0_0value === "boolean" || typeof this._checked_0_0value === "undefined") {
                        peer.checked0Attribute((this._checked_0_0value as boolean | undefined));
                    } else {
                        RadioOpsHandWritten.hookRadioAttributeCheckedImpl(peer.peer.ptr, (this._checked_0_0value as Bindable<boolean>));
                    }
                }
            }
        }
        if (this._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onChange1Attribute((this._onChange_0_0value as OnRadioChangeCallback | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onChange1Attribute((undefined as OnRadioChangeCallback | undefined));
                }
            }
        }
        if (this._radioStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._radioStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.radioStyleAttribute((this._radioStyle_0_0value as RadioStyle | undefined));
                    this._radioStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._radioStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._radioStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.radioStyleAttribute((undefined as RadioStyle | undefined));
                }
            }
        }
        if (this._contentModifier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._contentModifier_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    const arkRadioComponent: ArkRadioComponent = new ArkRadioComponent();
                    arkRadioComponent.setPeer(peer);
                    hookRadioContentModifier(arkRadioComponent, (this._contentModifier_0_0value as ContentModifier<RadioConfiguration> | undefined));
                    this._contentModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._contentModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._contentModifier_0_flag = AttributeUpdaterFlag.INITIAL;
                    const arkRadioComponent: ArkRadioComponent = new ArkRadioComponent();
                    arkRadioComponent.setPeer(peer);
                    hookRadioContentModifier(arkRadioComponent, (this._contentModifier_0_0value as ContentModifier<RadioConfiguration> | undefined));
                }
            }
        }
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
        if (!(value instanceof RadioModifier)) {
            return
        }
        const modifier = value as RadioModifier;
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
        } else
        {
            this._radioStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    contentModifier(value: ContentModifier<RadioConfiguration> | undefined): this {
        if (((this._contentModifier_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._contentModifier_0_flag = AttributeUpdaterFlag.UPDATE
            this._contentModifier_0_0value = value
        } else
        {
            this._contentModifier_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
}
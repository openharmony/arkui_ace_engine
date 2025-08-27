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

import { ArkButtonPeer, ArkCheckboxGroupPeer, AttributeModifier, ResourceColor, SwitchStyle } from './component';
import { ContentModifier } from './component/common';
import { ToggleAttribute, ToggleConfiguration, ArkToggleComponent, ArkToggleButtonComponent, ArkToggleCheckboxComponent, ArkTogglePeer, ArkToggleButtonPeer, ArkToggleCheckboxPeer } from './component/toggle';
import { CommonMethodModifier, AttributeUpdaterFlag } from './CommonMethodModifier';
import { hookToggleContentModifier } from './handwritten'
import { PeerNode } from "./PeerNode";

export class ToggleModifier extends CommonMethodModifier implements ToggleAttribute, AttributeModifier<ToggleAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyNormalAttribute(instance: ToggleAttribute): void {}
    applyPressedAttribute(instance: ToggleAttribute): void {}
    applyFocusedAttribute(instance: ToggleAttribute): void {}
    applyDisabledAttribute(instance: ToggleAttribute): void {}
    applySelectedAttribute(instance: ToggleAttribute): void {}
    _onChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onChange_0_0value?: ((isVisible: boolean) => void) | undefined
    _contentModifier_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _contentModifier_0_0value?: ContentModifier<ToggleConfiguration> | undefined
    _selectedColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedColor_0_0value?: ResourceColor | undefined
    _switchPointColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _switchPointColor_0_0value?: ResourceColor | undefined
    _switchStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _switchStyle_0_0value?: SwitchStyle | undefined
    applyModifierPatchSwitch(peer: ArkTogglePeer): void {
        if (this._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onChangeAttribute((this._onChange_0_0value as ((isVisible: boolean) => void) | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onChangeAttribute((undefined as ((isVisible: boolean) => void) | undefined));
                }
            }
        }
        if (this._contentModifier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._contentModifier_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    const arkToggleComponent: ArkToggleComponent = new ArkToggleComponent();
                    arkToggleComponent.setPeer(peer);
                    hookToggleContentModifier(arkToggleComponent, (this._contentModifier_0_0value as ContentModifier<ToggleConfiguration> | undefined));
                    this._contentModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._contentModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._contentModifier_0_flag = AttributeUpdaterFlag.INITIAL;
                    const arkToggleComponent: ArkToggleComponent = new ArkToggleComponent();
                    arkToggleComponent.setPeer(peer);
                    hookToggleContentModifier(arkToggleComponent, (this._contentModifier_0_0value as ContentModifier<ToggleConfiguration> | undefined));
                }
            }
        }
        if (this._selectedColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectedColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.selectedColorAttribute((this._selectedColor_0_0value as ResourceColor | undefined));
                    this._selectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectedColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.selectedColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._switchPointColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._switchPointColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.switchPointColorAttribute((this._switchPointColor_0_0value as ResourceColor | undefined));
                    this._switchPointColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._switchPointColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._switchPointColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.switchPointColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._switchStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._switchStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.switchStyleAttribute((this._switchStyle_0_0value as SwitchStyle | undefined));
                    this._switchStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._switchStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._switchStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.switchStyleAttribute((undefined as SwitchStyle | undefined));
                }
            }
        }
    }
    applyModifierPatchButton(peer: ArkToggleButtonPeer): void {
        if (this._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onChangeAttribute((this._onChange_0_0value as ((isVisible: boolean) => void) | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onChangeAttribute((undefined as ((isVisible: boolean) => void) | undefined));
                }
            }
        }
        if (this._contentModifier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._contentModifier_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    const arkToggleComponent: ArkToggleComponent = new ArkToggleComponent();
                    arkToggleComponent.setPeer(peer);
                    hookToggleContentModifier(arkToggleComponent, (this._contentModifier_0_0value as ContentModifier<ToggleConfiguration> | undefined));
                    this._contentModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._contentModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._contentModifier_0_flag = AttributeUpdaterFlag.INITIAL;
                    const arkToggleComponent: ArkToggleComponent = new ArkToggleComponent();
                    arkToggleComponent.setPeer(peer);
                    hookToggleContentModifier(arkToggleComponent, (this._contentModifier_0_0value as ContentModifier<ToggleConfiguration> | undefined));
                }
            }
        }
        if (this._selectedColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectedColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.selectedColorAttribute((this._selectedColor_0_0value as ResourceColor | undefined));
                    this._selectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectedColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.selectedColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._switchPointColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._switchPointColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.switchPointColorAttribute((this._switchPointColor_0_0value as ResourceColor | undefined));
                    this._switchPointColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._switchPointColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._switchPointColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.switchPointColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._switchStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._switchStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.switchStyleAttribute((this._switchStyle_0_0value as SwitchStyle | undefined));
                    this._switchStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._switchStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._switchStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.switchStyleAttribute((undefined as SwitchStyle | undefined));
                }
            }
        }
    }
    applyModifierPatchCheckbox(peer: ArkToggleCheckboxPeer): void {
        if (this._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onChangeAttribute((this._onChange_0_0value as ((isVisible: boolean) => void) | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onChangeAttribute((undefined as ((isVisible: boolean) => void) | undefined));
                }
            }
        }
        if (this._contentModifier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._contentModifier_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    const arkToggleComponent: ArkToggleComponent = new ArkToggleComponent();
                    arkToggleComponent.setPeer(peer);
                    hookToggleContentModifier(arkToggleComponent, (this._contentModifier_0_0value as ContentModifier<ToggleConfiguration> | undefined));
                    this._contentModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._contentModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._contentModifier_0_flag = AttributeUpdaterFlag.INITIAL;
                    const arkToggleComponent: ArkToggleComponent = new ArkToggleComponent();
                    arkToggleComponent.setPeer(peer);
                    hookToggleContentModifier(arkToggleComponent, (this._contentModifier_0_0value as ContentModifier<ToggleConfiguration> | undefined));
                }
            }
        }
        if (this._selectedColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectedColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.selectedColorAttribute((this._selectedColor_0_0value as ResourceColor | undefined));
                    this._selectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectedColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.selectedColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._switchPointColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._switchPointColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.switchPointColorAttribute((this._switchPointColor_0_0value as ResourceColor | undefined));
                    this._switchPointColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._switchPointColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._switchPointColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.switchPointColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._switchStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._switchStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.switchStyleAttribute((this._switchStyle_0_0value as SwitchStyle | undefined));
                    this._switchStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._switchStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._switchStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.switchStyleAttribute((undefined as SwitchStyle | undefined));
                }
            }
        }
    }
    applyModifierPatch(value: PeerNode): void {
        super.applyModifierPatch(value)
        if (value.name == 'Button') {
            this.applyModifierPatchButton(value as ArkToggleButtonPeer);
        } else if (value.name == 'Checkbox') {
            this.applyModifierPatchCheckbox(value as ArkToggleCheckboxPeer);
        } else {
            this.applyModifierPatchSwitch(value as ArkTogglePeer)
        }
    }
    mergeModifier(modifier: ToggleModifier): void {
        super.mergeModifier(modifier)
        if (modifier._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onChange(modifier._onChange_0_0value);
                    break;
                }
                default: {
                    this.onChange((undefined as ((isVisible: boolean) => void) | undefined));
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
                    this.contentModifier((undefined as ContentModifier<ToggleConfiguration> | undefined));
                }
            }
        }
        if (modifier._selectedColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selectedColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selectedColor(modifier._selectedColor_0_0value);
                    break;
                }
                default: {
                    this.selectedColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._switchPointColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._switchPointColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.switchPointColor(modifier._switchPointColor_0_0value);
                    break;
                }
                default: {
                    this.switchPointColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._switchStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._switchStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.switchStyle(modifier._switchStyle_0_0value);
                    break;
                }
                default: {
                    this.switchStyle((undefined as SwitchStyle | undefined));
                }
            }
        }
    }

    onChange(value: ((isVisible: boolean) => void) | undefined): this {
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
    contentModifier(value: ContentModifier<ToggleConfiguration> | undefined): this {
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
    selectedColor(value: ResourceColor | undefined): this {
        if (((this._selectedColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._selectedColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectedColor_0_0value = value
        } else
        {
            this._selectedColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    switchPointColor(value: ResourceColor | undefined): this {
        if (((this._switchPointColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._switchPointColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._switchPointColor_0_0value = value
        } else
        {
            this._switchPointColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    switchStyle(value: SwitchStyle | undefined): this {
        if (((this._switchStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._switchStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._switchStyle_0_0value = value
        } else
        {
            this._switchStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
}
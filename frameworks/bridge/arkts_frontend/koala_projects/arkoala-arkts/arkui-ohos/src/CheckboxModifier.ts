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

import { AttributeModifier, ResourceColor, Bindable, CheckBoxShape, MarkStyle } from './component';
import { ContentModifier } from './component/common';
import { OnCheckboxChangeCallback, CheckBoxConfiguration, CheckboxAttribute, ArkCheckboxPeer, ArkCheckboxComponent } from "./component/checkbox"
import { AttributeUpdaterFlag, CommonMethodModifier } from './CommonMethodModifier';
import { CheckboxOpsHandWritten, hookCheckboxContentModifier } from './handwritten';

export class CheckboxModifier extends CommonMethodModifier implements CheckboxAttribute, AttributeModifier<CheckboxAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyNormalAttribute(instance: CheckboxAttribute): void { }
    applyPressedAttribute(instance: CheckboxAttribute): void { }
    applyFocusedAttribute(instance: CheckboxAttribute): void { }
    applyDisabledAttribute(instance: CheckboxAttribute): void { }
    applySelectedAttribute(instance: CheckboxAttribute): void { }
    _select_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _select_0_0value?: boolean | Bindable<boolean> | undefined
    _selectedColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedColor_0_0value?: ResourceColor | undefined
    _shape_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _shape_0_0value?: CheckBoxShape | undefined
    _unselectedColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _unselectedColor_0_0value?: ResourceColor | undefined
    _mark_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _mark_0_0value?: MarkStyle | undefined
    _onChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onChange_0_0value?: OnCheckboxChangeCallback | undefined
    _contentModifier_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _contentModifier_0_0value?: ContentModifier<CheckBoxConfiguration> | undefined
    applyModifierPatch(peer: ArkCheckboxPeer): void {
        super.applyModifierPatch(peer)
        if (this._select_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._select_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    if (typeof this._select_0_0value === "boolean" || typeof this._select_0_0value === "undefined") {
                        peer.select0Attribute((this._select_0_0value as boolean | undefined));
                    } else {
                        CheckboxOpsHandWritten.hookCheckboxAttributeSelectImpl(peer.peer.ptr, (this._select_0_0value as Bindable<boolean>));
                    }
                    this._select_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._select_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._select_0_flag = AttributeUpdaterFlag.INITIAL;
                    if (typeof this._select_0_0value === "boolean" || typeof this._select_0_0value === "undefined") {
                        peer.select0Attribute((this._select_0_0value as boolean | undefined));
                    } else {
                        CheckboxOpsHandWritten.hookCheckboxAttributeSelectImpl(peer.peer.ptr, (this._select_0_0value as Bindable<boolean>));
                    }
                }
            }
        }
        if (this._selectedColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectedColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.selectedColor0Attribute((this._selectedColor_0_0value as ResourceColor | undefined));
                    this._selectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectedColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.selectedColor0Attribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._shape_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._shape_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.shape0Attribute((this._shape_0_0value as CheckBoxShape | undefined));
                    this._shape_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._shape_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._shape_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.shape0Attribute((undefined as CheckBoxShape | undefined));
                }
            }
        }
        if (this._unselectedColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._unselectedColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.unselectedColor0Attribute((this._unselectedColor_0_0value as ResourceColor | undefined));
                    this._unselectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._unselectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._unselectedColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.unselectedColor0Attribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._mark_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._mark_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.mark0Attribute((this._mark_0_0value as MarkStyle | undefined));
                    this._mark_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._mark_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._mark_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.mark0Attribute((undefined as MarkStyle | undefined));
                }
            }
        }
        if (this._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onChange0Attribute((this._onChange_0_0value as OnCheckboxChangeCallback | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onChange0Attribute((undefined as OnCheckboxChangeCallback | undefined));
                }
            }
        }
        if (this._contentModifier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._contentModifier_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    const arkCheckboxComponent: ArkCheckboxComponent = new ArkCheckboxComponent();
                    arkCheckboxComponent.setPeer(peer);
                    hookCheckboxContentModifier(arkCheckboxComponent, (this._contentModifier_0_0value as ContentModifier<CheckBoxConfiguration> | undefined));
                    this._contentModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._contentModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._contentModifier_0_flag = AttributeUpdaterFlag.INITIAL;
                    const arkCheckboxComponent: ArkCheckboxComponent = new ArkCheckboxComponent();
                    arkCheckboxComponent.setPeer(peer);
                    hookCheckboxContentModifier(arkCheckboxComponent, (this._contentModifier_0_0value as ContentModifier<CheckBoxConfiguration> | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: CheckboxModifier): void {
        super.mergeModifier(modifier)
        if (modifier._select_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._select_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.select(modifier._select_0_0value);
                    break;
                }
                default: {
                    this.select((undefined as boolean | Bindable<boolean> | undefined));
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
        if (modifier._shape_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._shape_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.shape(modifier._shape_0_0value);
                    break;
                }
                default: {
                    this.shape((undefined as CheckBoxShape | undefined));
                }
            }
        }
        if (modifier._unselectedColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._unselectedColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.unselectedColor(modifier._unselectedColor_0_0value);
                    break;
                }
                default: {
                    this.unselectedColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._mark_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._mark_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.mark(modifier._mark_0_0value);
                    break;
                }
                default: {
                    this.mark((undefined as MarkStyle | undefined));
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
                    this.onChange((undefined as OnCheckboxChangeCallback | undefined));
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
                    this.contentModifier((undefined as ContentModifier<CheckBoxConfiguration> | undefined));
                }
            }
        }
    }
    select(value: boolean | Bindable<boolean> | undefined): this {
        if (((this._select_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._select_0_flag = AttributeUpdaterFlag.UPDATE
            this._select_0_0value = value
        } else
        {
            this._select_0_flag = AttributeUpdaterFlag.SKIP
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
    shape(value: CheckBoxShape | undefined): this {
        if (((this._shape_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._shape_0_flag = AttributeUpdaterFlag.UPDATE
            this._shape_0_0value = value
        } else
        {
            this._shape_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    unselectedColor(value: ResourceColor | undefined): this {
        if (((this._unselectedColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._unselectedColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._unselectedColor_0_0value = value
        } else
        {
            this._unselectedColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    mark(value: MarkStyle | undefined): this {
        if (((this._mark_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._mark_0_flag = AttributeUpdaterFlag.UPDATE
            this._mark_0_0value = value
        } else
        {
            this._mark_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onChange(value: OnCheckboxChangeCallback | undefined): this {
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
    contentModifier(value: ContentModifier<CheckBoxConfiguration> | undefined): this {
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
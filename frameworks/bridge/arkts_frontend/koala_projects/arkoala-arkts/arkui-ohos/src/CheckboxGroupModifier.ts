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

import { AttributeModifier, ResourceColor, CheckboxGroupAttribute, Bindable, MarkStyle, OnCheckboxGroupChangeCallback, CheckBoxShape } from './component';
import { ArkCheckboxGroupPeer } from './component/checkboxgroup';
import { CommonMethodModifier, AttributeUpdaterFlag } from './CommonMethodModifier';
import { CheckboxGroupOpsHandWritten } from './handwritten';
import { PeerNode } from './PeerNode';

export class CheckboxGroupModifier extends CommonMethodModifier implements CheckboxGroupAttribute, AttributeModifier<CheckboxGroupAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyNormalAttribute(instance: CheckboxGroupAttribute): void {}
    applyPressedAttribute(instance: CheckboxGroupAttribute): void {}
    applyFocusedAttribute(instance: CheckboxGroupAttribute): void {}
    applyDisabledAttribute(instance: CheckboxGroupAttribute): void {}
    applySelectedAttribute(instance: CheckboxGroupAttribute): void {}
    _selectAll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectAll_0_0value?: boolean | Bindable<boolean> | undefined
    _selectedColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedColor_0_0value?: ResourceColor | undefined
    _unselectedColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _unselectedColor_0_0value?: ResourceColor | undefined
    _mark_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _mark_0_0value?: MarkStyle | undefined
    _onChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onChange_0_0value?: OnCheckboxGroupChangeCallback | undefined
    _checkboxShape_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _checkboxShape_0_0value?: CheckBoxShape | undefined
    applyModifierPatch(value: PeerNode): void {
        super.applyModifierPatch(value)
        const peer = value as ArkCheckboxGroupPeer
        if (this._selectAll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectAll_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    if (typeof this._selectAll_0_0value === "boolean" || typeof this._selectAll_0_0value === "undefined") {
                        peer.selectAll0Attribute((this._selectAll_0_0value as boolean | undefined));
                    } else {
                        CheckboxGroupOpsHandWritten.hookCheckboxGroupAttributeSelectAllImpl(peer.peer.ptr, (this._selectAll_0_0value as Bindable<boolean>));
                    }
                    this._selectAll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectAll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectAll_0_flag = AttributeUpdaterFlag.INITIAL;
                    if (typeof this._selectAll_0_0value === "boolean" || typeof this._selectAll_0_0value === "undefined") {
                        peer.selectAll0Attribute((this._selectAll_0_0value as boolean | undefined));
                    } else {
                        CheckboxGroupOpsHandWritten.hookCheckboxGroupAttributeSelectAllImpl(peer.peer.ptr, (this._selectAll_0_0value as Bindable<boolean>));
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
                    peer.onChange0Attribute((this._onChange_0_0value as OnCheckboxGroupChangeCallback | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onChange0Attribute((undefined as OnCheckboxGroupChangeCallback | undefined));
                }
            }
        }
        if (this._checkboxShape_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._checkboxShape_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.checkboxShape0Attribute((this._checkboxShape_0_0value as CheckBoxShape | undefined));
                    this._checkboxShape_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._checkboxShape_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._checkboxShape_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.checkboxShape0Attribute((undefined as CheckBoxShape | undefined));
                }
            }
        }
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
        if (!(value instanceof CheckboxGroupModifier)) {
            return
        }
        const modifier = value as CheckboxGroupModifier;
        if (modifier._selectAll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selectAll_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selectAll(modifier._selectAll_0_0value);
                    break;
                }
                default: {
                    this.selectAll((undefined as boolean | Bindable<boolean> | undefined));
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
                    this.onChange((undefined as OnCheckboxGroupChangeCallback | undefined));
                }
            }
        }
        if (modifier._checkboxShape_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._checkboxShape_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.checkboxShape(modifier._checkboxShape_0_0value);
                    break;
                }
                default: {
                    this.checkboxShape((undefined as CheckBoxShape | undefined));
                }
            }
        }
    }
    selectAll(value: boolean | Bindable<boolean> | undefined): this {
        if (((this._selectAll_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._selectAll_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectAll_0_0value = value
        } else
        {
            this._selectAll_0_flag = AttributeUpdaterFlag.SKIP
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
    onChange(value: OnCheckboxGroupChangeCallback | undefined): this {
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
    checkboxShape(value: CheckBoxShape | undefined): this {
        if (((this._checkboxShape_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._checkboxShape_0_flag = AttributeUpdaterFlag.UPDATE
            this._checkboxShape_0_0value = value
        } else
        {
            this._checkboxShape_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
}
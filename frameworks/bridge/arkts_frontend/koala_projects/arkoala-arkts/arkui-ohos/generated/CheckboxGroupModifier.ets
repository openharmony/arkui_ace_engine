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
import { AttributeModifier } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkCheckboxGroupPeer, OnCheckboxGroupChangeCallback, CheckboxGroupResult, CheckboxGroupAttribute } from "./component/checkboxgroup"
import { int32 } from "@koalaui/common"
import { CommonMethod, Bindable } from "./component/common"
import { ResourceColor, MarkStyle } from "./component/units"
import { Color, CheckBoxShape } from "./component/enums"
import { Resource } from "global.resource"
export class CheckboxGroupModifier extends CommonMethodModifier implements CheckboxGroupAttribute,AttributeModifier<CheckboxGroupAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: CheckboxGroupAttribute): void { }
    applyPressedAttribute(instance: CheckboxGroupAttribute): void { }
    applyFocusedAttribute(instance: CheckboxGroupAttribute): void { }
    applyDisabledAttribute(instance: CheckboxGroupAttribute): void { }
    applySelectedAttribute(instance: CheckboxGroupAttribute): void { }
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
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkCheckboxGroupPeer;
        if (this._selectAll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectAll_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSelectAllAttribute((this._selectAll_0_0value as boolean | Bindable<boolean> | undefined));
                    this._selectAll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectAll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectAll_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSelectAllAttribute((undefined as boolean | Bindable<boolean> | undefined));
                }
            }
        }
        if (this._selectedColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectedColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSelectedColorAttribute((this._selectedColor_0_0value as ResourceColor | undefined));
                    this._selectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectedColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSelectedColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._unselectedColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._unselectedColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setUnselectedColorAttribute((this._unselectedColor_0_0value as ResourceColor | undefined));
                    this._unselectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._unselectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._unselectedColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setUnselectedColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._mark_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._mark_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMarkAttribute((this._mark_0_0value as MarkStyle | undefined));
                    this._mark_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._mark_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._mark_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMarkAttribute((undefined as MarkStyle | undefined));
                }
            }
        }
        if (this._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as OnCheckboxGroupChangeCallback | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnChangeAttribute((undefined as OnCheckboxGroupChangeCallback | undefined));
                }
            }
        }
        if (this._checkboxShape_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._checkboxShape_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCheckboxShapeAttribute((this._checkboxShape_0_0value as CheckBoxShape | undefined));
                    this._checkboxShape_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._checkboxShape_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._checkboxShape_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCheckboxShapeAttribute((undefined as CheckBoxShape | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: CheckboxGroupModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
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
    public attributeModifier(value: AttributeModifier<CheckboxGroupAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

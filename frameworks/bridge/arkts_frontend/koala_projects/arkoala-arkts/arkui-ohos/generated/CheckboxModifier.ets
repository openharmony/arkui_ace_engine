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
import { AttributeModifier, ContentModifier, hookCheckBoxContentModifier } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkCheckboxPeer, OnCheckboxChangeCallback, CheckBoxConfiguration, CheckboxAttribute } from "./component/checkbox"
import { int32 } from "@koalaui/common"
import { CommonMethod, Bindable } from "./component/common"
import { ResourceColor, MarkStyle } from "./component/units"
import { Color, CheckBoxShape } from "./component/enums"
import { Resource } from "global.resource"
export class CheckboxModifier extends CommonMethodModifier implements CheckboxAttribute,AttributeModifier<CheckboxAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
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
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkCheckboxPeer;
        if (this._select_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._select_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSelectAttribute((this._select_0_0value as boolean | Bindable<boolean> | undefined));
                    this._select_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._select_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._select_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSelectAttribute((undefined as boolean | Bindable<boolean> | undefined));
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
        if (this._shape_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._shape_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setShapeAttribute((this._shape_0_0value as CheckBoxShape | undefined));
                    this._shape_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._shape_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._shape_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setShapeAttribute((undefined as CheckBoxShape | undefined));
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
                    peer.setOnChangeAttribute((this._onChange_0_0value as OnCheckboxChangeCallback | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnChangeAttribute((undefined as OnCheckboxChangeCallback | undefined));
                }
            }
        }
        if (this._contentModifier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._contentModifier_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    hookCheckBoxContentModifier(peer, (this._contentModifier_0_0value as ContentModifier<CheckBoxConfiguration> | undefined));
                    this._contentModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._contentModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._contentModifier_0_flag = AttributeUpdaterFlag.INITIAL;
                    hookCheckBoxContentModifier(peer, (undefined as ContentModifier<CheckBoxConfiguration> | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: CheckboxModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
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
    public attributeModifier(value: AttributeModifier<CheckboxAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

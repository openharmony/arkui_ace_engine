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
import { AttributeModifier, ContentModifier } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkTogglePeer, ToggleConfiguration, SwitchStyle, ToggleAttribute } from "./component/toggle"
import { int32 } from "@koalaui/common"
import { ModifierState } from "./CommonModifier"
import { CommonMethod } from "./component/common"
import { ResourceColor } from "./component/units"
import { Color } from "./component/enums"
import { Resource } from "global.resource"
export class ToggleModifier extends CommonMethodModifier implements ToggleAttribute,AttributeModifier<ToggleAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: ToggleAttribute): void { }
    applyPressedAttribute(instance: ToggleAttribute): void { }
    applyFocusedAttribute(instance: ToggleAttribute): void { }
    applyDisabledAttribute(instance: ToggleAttribute): void { }
    applySelectedAttribute(instance: ToggleAttribute): void { }
    _onChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onChange_0_0value?: ((value0: boolean) => void) | undefined
    _selectedColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedColor_0_0value?: ResourceColor | undefined
    _switchPointColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _switchPointColor_0_0value?: ResourceColor | undefined
    _switchStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _switchStyle_0_0value?: SwitchStyle | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkTogglePeer;
        if (this._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as ((value0: boolean) => void) | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnChangeAttribute((undefined as ((value0: boolean) => void) | undefined));
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
        if (this._switchPointColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._switchPointColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSwitchPointColorAttribute((this._switchPointColor_0_0value as ResourceColor | undefined));
                    this._switchPointColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._switchPointColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._switchPointColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSwitchPointColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._switchStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._switchStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSwitchStyleAttribute((this._switchStyle_0_0value as SwitchStyle | undefined));
                    this._switchStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._switchStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._switchStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSwitchStyleAttribute((undefined as SwitchStyle | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: ToggleModifier): void {
       super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onChange(modifier._onChange_0_0value);
                    break;
                }
                default: {
                    this.onChange((undefined as ((value0: boolean) => void) | undefined));
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
    onChange(value: ((value0: boolean) => void) | undefined): this {
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
    selectedColor(value: ResourceColor | undefined): this {
        if (((this._selectedColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._selectedColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectedColor_0_0value = value
            this._state.fireChange()
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
            this._state.fireChange()
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
            this._state.fireChange()
        } else
        {
            this._switchStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ToggleAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

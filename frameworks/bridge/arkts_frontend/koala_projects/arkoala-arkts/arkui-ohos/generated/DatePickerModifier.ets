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
import { ArkDatePickerPeer, DatePickerAttribute } from "./component/datePicker"
import { int32 } from "@koalaui/common"
import { CommonMethod, PickerTextStyle } from "./component/common"
import { CrownSensitivity } from "./component/enums"
export class DatePickerModifier extends CommonMethodModifier implements DatePickerAttribute,AttributeModifier<DatePickerAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: DatePickerAttribute): void { }
    applyPressedAttribute(instance: DatePickerAttribute): void { }
    applyFocusedAttribute(instance: DatePickerAttribute): void { }
    applyDisabledAttribute(instance: DatePickerAttribute): void { }
    applySelectedAttribute(instance: DatePickerAttribute): void { }
    _lunar_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _lunar_0_0value?: boolean | undefined
    _disappearTextStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _disappearTextStyle_0_0value?: PickerTextStyle | undefined
    _textStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textStyle_0_0value?: PickerTextStyle | undefined
    _selectedTextStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedTextStyle_0_0value?: PickerTextStyle | undefined
    _onDateChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDateChange_0_0value?: ((value0: Date) => void) | undefined
    _digitalCrownSensitivity_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _digitalCrownSensitivity_0_0value?: CrownSensitivity | undefined
    _enableHapticFeedback_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableHapticFeedback_0_0value?: boolean | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkDatePickerPeer;
        if (this._lunar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._lunar_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setLunarAttribute((this._lunar_0_0value as boolean | undefined));
                    this._lunar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._lunar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._lunar_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setLunarAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._disappearTextStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._disappearTextStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDisappearTextStyleAttribute((this._disappearTextStyle_0_0value as PickerTextStyle | undefined));
                    this._disappearTextStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._disappearTextStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._disappearTextStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDisappearTextStyleAttribute((undefined as PickerTextStyle | undefined));
                }
            }
        }
        if (this._textStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._textStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTextStyleAttribute((this._textStyle_0_0value as PickerTextStyle | undefined));
                    this._textStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._textStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._textStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTextStyleAttribute((undefined as PickerTextStyle | undefined));
                }
            }
        }
        if (this._selectedTextStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectedTextStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSelectedTextStyleAttribute((this._selectedTextStyle_0_0value as PickerTextStyle | undefined));
                    this._selectedTextStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectedTextStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectedTextStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSelectedTextStyleAttribute((undefined as PickerTextStyle | undefined));
                }
            }
        }
        if (this._onDateChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDateChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDateChangeAttribute((this._onDateChange_0_0value as ((value0: Date) => void) | undefined));
                    this._onDateChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDateChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDateChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDateChangeAttribute((undefined as ((value0: Date) => void) | undefined));
                }
            }
        }
        if (this._digitalCrownSensitivity_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._digitalCrownSensitivity_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDigitalCrownSensitivityAttribute((this._digitalCrownSensitivity_0_0value as CrownSensitivity | undefined));
                    this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDigitalCrownSensitivityAttribute((undefined as CrownSensitivity | undefined));
                }
            }
        }
        if (this._enableHapticFeedback_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableHapticFeedback_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableHapticFeedbackAttribute((this._enableHapticFeedback_0_0value as boolean | undefined));
                    this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableHapticFeedbackAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: DatePickerModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._lunar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._lunar_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.lunar(modifier._lunar_0_0value);
                    break;
                }
                default: {
                    this.lunar((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._disappearTextStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._disappearTextStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.disappearTextStyle(modifier._disappearTextStyle_0_0value);
                    break;
                }
                default: {
                    this.disappearTextStyle((undefined as PickerTextStyle | undefined));
                }
            }
        }
        if (modifier._textStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._textStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.textStyle(modifier._textStyle_0_0value);
                    break;
                }
                default: {
                    this.textStyle((undefined as PickerTextStyle | undefined));
                }
            }
        }
        if (modifier._selectedTextStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selectedTextStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selectedTextStyle(modifier._selectedTextStyle_0_0value);
                    break;
                }
                default: {
                    this.selectedTextStyle((undefined as PickerTextStyle | undefined));
                }
            }
        }
        if (modifier._onDateChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDateChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDateChange(modifier._onDateChange_0_0value);
                    break;
                }
                default: {
                    this.onDateChange((undefined as ((value0: Date) => void) | undefined));
                }
            }
        }
        if (modifier._digitalCrownSensitivity_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._digitalCrownSensitivity_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.digitalCrownSensitivity(modifier._digitalCrownSensitivity_0_0value);
                    break;
                }
                default: {
                    this.digitalCrownSensitivity((undefined as CrownSensitivity | undefined));
                }
            }
        }
        if (modifier._enableHapticFeedback_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableHapticFeedback_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableHapticFeedback(modifier._enableHapticFeedback_0_0value);
                    break;
                }
                default: {
                    this.enableHapticFeedback((undefined as boolean | undefined));
                }
            }
        }
    }
    lunar(value: boolean | undefined): this {
        if (((this._lunar_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._lunar_0_0value) !== (value)))
        {
            this._lunar_0_flag = AttributeUpdaterFlag.UPDATE
            this._lunar_0_0value = value
        } else
        {
            this._lunar_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    disappearTextStyle(value: PickerTextStyle | undefined): this {
        if (((this._disappearTextStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._disappearTextStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._disappearTextStyle_0_0value = value
        } else
        {
            this._disappearTextStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    textStyle(value: PickerTextStyle | undefined): this {
        if (((this._textStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._textStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._textStyle_0_0value = value
        } else
        {
            this._textStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selectedTextStyle(value: PickerTextStyle | undefined): this {
        if (((this._selectedTextStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._selectedTextStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectedTextStyle_0_0value = value
        } else
        {
            this._selectedTextStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDateChange(value: ((value0: Date) => void) | undefined): this {
        if (((this._onDateChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDateChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDateChange_0_0value = value
        } else
        {
            this._onDateChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        if (((this._digitalCrownSensitivity_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.UPDATE
            this._digitalCrownSensitivity_0_0value = value
        } else
        {
            this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableHapticFeedback(value: boolean | undefined): this {
        if (((this._enableHapticFeedback_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableHapticFeedback_0_0value) !== (value)))
        {
            this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableHapticFeedback_0_0value = value
        } else
        {
            this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<DatePickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

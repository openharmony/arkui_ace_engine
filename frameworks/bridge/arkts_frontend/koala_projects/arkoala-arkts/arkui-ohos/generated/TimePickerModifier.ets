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
import { ArkTimePickerPeer, OnTimePickerChangeCallback, TimePickerResult, TimePickerAttribute } from "./component/timePicker"
import { int32 } from "@koalaui/common"
import { CommonMethod, PickerTextStyle } from "./component/common"
import { default as intl } from "@ohos.intl"
import { CrownSensitivity } from "./component/enums"
export class TimePickerModifier extends CommonMethodModifier implements TimePickerAttribute,AttributeModifier<TimePickerAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: TimePickerAttribute): void { }
    applyPressedAttribute(instance: TimePickerAttribute): void { }
    applyFocusedAttribute(instance: TimePickerAttribute): void { }
    applyDisabledAttribute(instance: TimePickerAttribute): void { }
    applySelectedAttribute(instance: TimePickerAttribute): void { }
    _useMilitaryTime_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _useMilitaryTime_0_0value?: boolean | undefined
    _loop_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _loop_0_0value?: boolean | undefined
    _disappearTextStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _disappearTextStyle_0_0value?: PickerTextStyle | undefined
    _textStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textStyle_0_0value?: PickerTextStyle | undefined
    _selectedTextStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedTextStyle_0_0value?: PickerTextStyle | undefined
    _dateTimeOptions_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _dateTimeOptions_0_0value?: intl.DateTimeOptions | undefined
    _onChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onChange_0_0value?: OnTimePickerChangeCallback | undefined
    _onEnterSelectedArea_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onEnterSelectedArea_0_0value?: ((value0: TimePickerResult) => void) | undefined
    _enableHapticFeedback_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableHapticFeedback_0_0value?: boolean | undefined
    _digitalCrownSensitivity_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _digitalCrownSensitivity_0_0value?: CrownSensitivity | undefined
    _enableCascade_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableCascade_0_0value?: boolean | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkTimePickerPeer;
        if (this._useMilitaryTime_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._useMilitaryTime_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setUseMilitaryTimeAttribute((this._useMilitaryTime_0_0value as boolean | undefined));
                    this._useMilitaryTime_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._useMilitaryTime_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._useMilitaryTime_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setUseMilitaryTimeAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._loop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._loop_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setLoopAttribute((this._loop_0_0value as boolean | undefined));
                    this._loop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._loop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._loop_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setLoopAttribute((undefined as boolean | undefined));
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
        if (this._dateTimeOptions_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._dateTimeOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDateTimeOptionsAttribute((this._dateTimeOptions_0_0value as intl.DateTimeOptions | undefined));
                    this._dateTimeOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._dateTimeOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._dateTimeOptions_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDateTimeOptionsAttribute((undefined as intl.DateTimeOptions | undefined));
                }
            }
        }
        if (this._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as OnTimePickerChangeCallback | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnChangeAttribute((undefined as OnTimePickerChangeCallback | undefined));
                }
            }
        }
        if (this._onEnterSelectedArea_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onEnterSelectedArea_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnEnterSelectedAreaAttribute((this._onEnterSelectedArea_0_0value as ((value0: TimePickerResult) => void) | undefined));
                    this._onEnterSelectedArea_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onEnterSelectedArea_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onEnterSelectedArea_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnEnterSelectedAreaAttribute((undefined as ((value0: TimePickerResult) => void) | undefined));
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
        if (this._enableCascade_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableCascade_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableCascadeAttribute((this._enableCascade_0_0value as boolean | undefined));
                    this._enableCascade_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableCascade_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableCascade_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableCascadeAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: TimePickerModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._useMilitaryTime_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._useMilitaryTime_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.useMilitaryTime(modifier._useMilitaryTime_0_0value);
                    break;
                }
                default: {
                    this.useMilitaryTime((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._loop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._loop_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.loop(modifier._loop_0_0value);
                    break;
                }
                default: {
                    this.loop((undefined as boolean | undefined));
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
        if (modifier._dateTimeOptions_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._dateTimeOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.dateTimeOptions(modifier._dateTimeOptions_0_0value);
                    break;
                }
                default: {
                    this.dateTimeOptions((undefined as intl.DateTimeOptions | undefined));
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
                    this.onChange((undefined as OnTimePickerChangeCallback | undefined));
                }
            }
        }
        if (modifier._onEnterSelectedArea_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onEnterSelectedArea_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onEnterSelectedArea(modifier._onEnterSelectedArea_0_0value);
                    break;
                }
                default: {
                    this.onEnterSelectedArea((undefined as ((value0: TimePickerResult) => void) | undefined));
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
        if (modifier._enableCascade_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableCascade_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableCascade(modifier._enableCascade_0_0value);
                    break;
                }
                default: {
                    this.enableCascade((undefined as boolean | undefined));
                }
            }
        }
    }
    useMilitaryTime(value: boolean | undefined): this {
        if (((this._useMilitaryTime_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._useMilitaryTime_0_0value) !== (value)))
        {
            this._useMilitaryTime_0_flag = AttributeUpdaterFlag.UPDATE
            this._useMilitaryTime_0_0value = value
        } else
        {
            this._useMilitaryTime_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    loop(value: boolean | undefined): this {
        if (((this._loop_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._loop_0_0value) !== (value)))
        {
            this._loop_0_flag = AttributeUpdaterFlag.UPDATE
            this._loop_0_0value = value
        } else
        {
            this._loop_0_flag = AttributeUpdaterFlag.SKIP
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
    dateTimeOptions(value: intl.DateTimeOptions | undefined): this {
        if (((this._dateTimeOptions_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._dateTimeOptions_0_flag = AttributeUpdaterFlag.UPDATE
            this._dateTimeOptions_0_0value = value
        } else
        {
            this._dateTimeOptions_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onChange(value: OnTimePickerChangeCallback | undefined): this {
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
    onEnterSelectedArea(value: ((value0: TimePickerResult) => void) | undefined): this {
        if (((this._onEnterSelectedArea_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onEnterSelectedArea_0_flag = AttributeUpdaterFlag.UPDATE
            this._onEnterSelectedArea_0_0value = value
        } else
        {
            this._onEnterSelectedArea_0_flag = AttributeUpdaterFlag.SKIP
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
    enableCascade(value: boolean | undefined): this {
        if (((this._enableCascade_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableCascade_0_0value) !== (value)))
        {
            this._enableCascade_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableCascade_0_0value = value
        } else
        {
            this._enableCascade_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<TimePickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

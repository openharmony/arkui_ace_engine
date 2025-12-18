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

import { CommonMethodModifier } from './CommonMethodModifier'
import { AttributeModifier } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkTimePickerPeer, OnTimePickerChangeCallback, TimePickerResult, TimePickerAttribute } from './component/timePicker'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod, PickerTextStyle, DateTimeOptions, Callback as arkui_component_common_Callback } from './component/common'
import { default as intl } from '@ohos.intl'
import { CrownSensitivity } from './component/enums'
export class TimePickerModifier extends CommonMethodModifier implements TimePickerAttribute,AttributeModifier<TimePickerAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState;
    _addr: ArrayBuffer = new ArrayBuffer(4096);
    _flagArray: Uint8Array = new Uint8Array(this._addr);
    constructor() {
        super();
        this._flagArray.fill(0);
    }
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: TimePickerAttribute): void { }
    applyPressedAttribute(instance: TimePickerAttribute): void { }
    applyFocusedAttribute(instance: TimePickerAttribute): void { }
    applyDisabledAttribute(instance: TimePickerAttribute): void { }
    applySelectedAttribute(instance: TimePickerAttribute): void { }
    public _useMilitaryTime_0_0value?: boolean | undefined
    public _loop_0_0value?: boolean | undefined
    public _disappearTextStyle_0_0value?: PickerTextStyle | undefined
    public _textStyle_0_0value?: PickerTextStyle | undefined
    public _selectedTextStyle_0_0value?: PickerTextStyle | undefined
    public _dateTimeOptions_0_0value?: DateTimeOptions | undefined
    public _onChange_0_0value?: OnTimePickerChangeCallback | undefined
    public _onEnterSelectedArea_0_0value?: arkui_component_common_Callback<TimePickerResult, void> | undefined
    public _enableHapticFeedback_0_0value?: boolean | undefined
    public _digitalCrownSensitivity_0_0value?: CrownSensitivity | undefined
    public _enableCascade_0_0value?: boolean | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkTimePickerPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkTimePickerPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setUseMilitaryTimeAttribute((this._useMilitaryTime_0_0value as boolean | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setUseMilitaryTimeAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setLoopAttribute((this._loop_0_0value as boolean | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setLoopAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setDisappearTextStyleAttribute((this._disappearTextStyle_0_0value as PickerTextStyle | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setDisappearTextStyleAttribute((undefined as PickerTextStyle | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setTextStyleAttribute((this._textStyle_0_0value as PickerTextStyle | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setTextStyleAttribute((undefined as PickerTextStyle | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setSelectedTextStyleAttribute((this._selectedTextStyle_0_0value as PickerTextStyle | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setSelectedTextStyleAttribute((undefined as PickerTextStyle | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setDateTimeOptionsAttribute((this._dateTimeOptions_0_0value as DateTimeOptions | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setDateTimeOptionsAttribute((undefined as DateTimeOptions | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as OnTimePickerChangeCallback | undefined));
                    flagArray[6] = 2;
                    break;
                }
                case 3: {
                    flagArray[6] = 2;
                    break;
                }
                default: {
                    flagArray[6] = 0;
                    peer.setOnChangeAttribute((undefined as OnTimePickerChangeCallback | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1: {
                    peer.setOnEnterSelectedAreaAttribute((this._onEnterSelectedArea_0_0value as arkui_component_common_Callback<TimePickerResult, void> | undefined));
                    flagArray[7] = 2;
                    break;
                }
                case 3: {
                    flagArray[7] = 2;
                    break;
                }
                default: {
                    flagArray[7] = 0;
                    peer.setOnEnterSelectedAreaAttribute((undefined as arkui_component_common_Callback<TimePickerResult, void> | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1: {
                    peer.setEnableHapticFeedbackAttribute((this._enableHapticFeedback_0_0value as boolean | undefined));
                    flagArray[8] = 2;
                    break;
                }
                case 3: {
                    flagArray[8] = 2;
                    break;
                }
                default: {
                    flagArray[8] = 0;
                    peer.setEnableHapticFeedbackAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1: {
                    peer.setDigitalCrownSensitivityAttribute((this._digitalCrownSensitivity_0_0value as CrownSensitivity | undefined));
                    flagArray[9] = 2;
                    break;
                }
                case 3: {
                    flagArray[9] = 2;
                    break;
                }
                default: {
                    flagArray[9] = 0;
                    peer.setDigitalCrownSensitivityAttribute((undefined as CrownSensitivity | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1: {
                    peer.setEnableCascadeAttribute((this._enableCascade_0_0value as boolean | undefined));
                    flagArray[10] = 2;
                    break;
                }
                case 3: {
                    flagArray[10] = 2;
                    break;
                }
                default: {
                    flagArray[10] = 0;
                    peer.setEnableCascadeAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: TimePickerModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: TimePickerModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.useMilitaryTime(modifier._useMilitaryTime_0_0value);
                    break;
                }
                default: {
                    this.useMilitaryTime((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.loop(modifier._loop_0_0value);
                    break;
                }
                default: {
                    this.loop((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.disappearTextStyle(modifier._disappearTextStyle_0_0value);
                    break;
                }
                default: {
                    this.disappearTextStyle((undefined as PickerTextStyle | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.textStyle(modifier._textStyle_0_0value);
                    break;
                }
                default: {
                    this.textStyle((undefined as PickerTextStyle | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.selectedTextStyle(modifier._selectedTextStyle_0_0value);
                    break;
                }
                default: {
                    this.selectedTextStyle((undefined as PickerTextStyle | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1:
                case 3: {
                    this.dateTimeOptions(modifier._dateTimeOptions_0_0value);
                    break;
                }
                default: {
                    this.dateTimeOptions((undefined as DateTimeOptions | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1:
                case 3: {
                    this.onChange(modifier._onChange_0_0value);
                    break;
                }
                default: {
                    this.onChange((undefined as OnTimePickerChangeCallback | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1:
                case 3: {
                    this.onEnterSelectedArea(modifier._onEnterSelectedArea_0_0value);
                    break;
                }
                default: {
                    this.onEnterSelectedArea((undefined as arkui_component_common_Callback<TimePickerResult, void> | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1:
                case 3: {
                    this.enableHapticFeedback(modifier._enableHapticFeedback_0_0value);
                    break;
                }
                default: {
                    this.enableHapticFeedback((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1:
                case 3: {
                    this.digitalCrownSensitivity(modifier._digitalCrownSensitivity_0_0value);
                    break;
                }
                default: {
                    this.digitalCrownSensitivity((undefined as CrownSensitivity | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1:
                case 3: {
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
        if (((this._flagArray[0]) == (0)) || ((this._useMilitaryTime_0_0value) !== (value))) {
            this._flagArray[0] = 1
            this._useMilitaryTime_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    loop(value: boolean | undefined): this {
        if (((this._flagArray[1]) == (0)) || ((this._loop_0_0value) !== (value))) {
            this._flagArray[1] = 1
            this._loop_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    disappearTextStyle(value: PickerTextStyle | undefined): this {
        if (((this._flagArray[2]) == (0)) || (true)) {
            this._flagArray[2] = 1
            this._disappearTextStyle_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    textStyle(value: PickerTextStyle | undefined): this {
        if (((this._flagArray[3]) == (0)) || (true)) {
            this._flagArray[3] = 1
            this._textStyle_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    selectedTextStyle(value: PickerTextStyle | undefined): this {
        if (((this._flagArray[4]) == (0)) || (true)) {
            this._flagArray[4] = 1
            this._selectedTextStyle_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    dateTimeOptions(value: DateTimeOptions | undefined): this {
        if (((this._flagArray[5]) == (0)) || (true)) {
            this._flagArray[5] = 1
            this._dateTimeOptions_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    onChange(value: OnTimePickerChangeCallback | undefined): this {
        if (((this._flagArray[6]) == (0)) || (true)) {
            this._flagArray[6] = 1
            this._onChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[6] = 3
        }
        return this
    }
    onEnterSelectedArea(value: arkui_component_common_Callback<TimePickerResult, void> | undefined): this {
        if (((this._flagArray[7]) == (0)) || (true)) {
            this._flagArray[7] = 1
            this._onEnterSelectedArea_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[7] = 3
        }
        return this
    }
    enableHapticFeedback(value: boolean | undefined): this {
        if (((this._flagArray[8]) == (0)) || ((this._enableHapticFeedback_0_0value) !== (value))) {
            this._flagArray[8] = 1
            this._enableHapticFeedback_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[8] = 3
        }
        return this
    }
    digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        if (((this._flagArray[9]) == (0)) || (true)) {
            this._flagArray[9] = 1
            this._digitalCrownSensitivity_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[9] = 3
        }
        return this
    }
    enableCascade(value: boolean | undefined): this {
        if (((this._flagArray[10]) == (0)) || ((this._enableCascade_0_0value) !== (value))) {
            this._flagArray[10] = 1
            this._enableCascade_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[10] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<TimePickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

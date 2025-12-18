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
import { ArkTextPickerPeer, TextPickerTextStyle, OnTextPickerChangeCallback, TextPickerScrollStopCallback, TextPickerEnterSelectedAreaCallback, DividerOptions, TextPickerAttribute } from './component/textPicker'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod, PickerTextStyle } from './component/common'
import { Dimension } from './component/units'
import { Resource as global_resource_Resource } from 'global.resource'
import { CrownSensitivity } from './component/enums'
export class TextPickerModifier extends CommonMethodModifier implements TextPickerAttribute,AttributeModifier<TextPickerAttribute> {
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
    applyNormalAttribute(instance: TextPickerAttribute): void { }
    applyPressedAttribute(instance: TextPickerAttribute): void { }
    applyFocusedAttribute(instance: TextPickerAttribute): void { }
    applyDisabledAttribute(instance: TextPickerAttribute): void { }
    applySelectedAttribute(instance: TextPickerAttribute): void { }
    public _defaultPickerItemHeight_0_0value?: double | string | undefined
    public _canLoop_0_0value?: boolean | undefined
    public _disappearTextStyle_0_0value?: PickerTextStyle | undefined
    public _textStyle_0_0value?: PickerTextStyle | undefined
    public _selectedTextStyle_0_0value?: PickerTextStyle | undefined
    public _disableTextStyleAnimation_0_0value?: boolean | undefined
    public _defaultTextStyle_0_0value?: TextPickerTextStyle | undefined
    public _onChange_0_0value?: OnTextPickerChangeCallback | undefined
    public _onScrollStop_0_0value?: TextPickerScrollStopCallback | undefined
    public _onEnterSelectedArea_0_0value?: TextPickerEnterSelectedAreaCallback | undefined
    public _selectedIndex_0_0value?: int32 | Array<int32> | undefined
    public _divider_0_0value?: DividerOptions | null | undefined
    public _gradientHeight_0_0value?: Dimension | undefined
    public _enableHapticFeedback_0_0value?: boolean | undefined
    public _digitalCrownSensitivity_0_0value?: CrownSensitivity | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkTextPickerPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkTextPickerPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setDefaultPickerItemHeightAttribute((this._defaultPickerItemHeight_0_0value as double | string | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setDefaultPickerItemHeightAttribute((undefined as double | string | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setCanLoopAttribute((this._canLoop_0_0value as boolean | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setCanLoopAttribute((undefined as boolean | undefined));
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
                    peer.setDisableTextStyleAnimationAttribute((this._disableTextStyleAnimation_0_0value as boolean | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setDisableTextStyleAnimationAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1: {
                    peer.setDefaultTextStyleAttribute((this._defaultTextStyle_0_0value as TextPickerTextStyle | undefined));
                    flagArray[6] = 2;
                    break;
                }
                case 3: {
                    flagArray[6] = 2;
                    break;
                }
                default: {
                    flagArray[6] = 0;
                    peer.setDefaultTextStyleAttribute((undefined as TextPickerTextStyle | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as OnTextPickerChangeCallback | undefined));
                    flagArray[7] = 2;
                    break;
                }
                case 3: {
                    flagArray[7] = 2;
                    break;
                }
                default: {
                    flagArray[7] = 0;
                    peer.setOnChangeAttribute((undefined as OnTextPickerChangeCallback | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1: {
                    peer.setOnScrollStopAttribute((this._onScrollStop_0_0value as TextPickerScrollStopCallback | undefined));
                    flagArray[8] = 2;
                    break;
                }
                case 3: {
                    flagArray[8] = 2;
                    break;
                }
                default: {
                    flagArray[8] = 0;
                    peer.setOnScrollStopAttribute((undefined as TextPickerScrollStopCallback | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1: {
                    peer.setOnEnterSelectedAreaAttribute((this._onEnterSelectedArea_0_0value as TextPickerEnterSelectedAreaCallback | undefined));
                    flagArray[9] = 2;
                    break;
                }
                case 3: {
                    flagArray[9] = 2;
                    break;
                }
                default: {
                    flagArray[9] = 0;
                    peer.setOnEnterSelectedAreaAttribute((undefined as TextPickerEnterSelectedAreaCallback | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1: {
                    peer.setSelectedIndexAttribute((this._selectedIndex_0_0value as int32 | Array<int32> | undefined));
                    flagArray[10] = 2;
                    break;
                }
                case 3: {
                    flagArray[10] = 2;
                    break;
                }
                default: {
                    flagArray[10] = 0;
                    peer.setSelectedIndexAttribute((undefined as int32 | Array<int32> | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1: {
                    peer.setDividerAttribute((this._divider_0_0value as DividerOptions | null | undefined));
                    flagArray[11] = 2;
                    break;
                }
                case 3: {
                    flagArray[11] = 2;
                    break;
                }
                default: {
                    flagArray[11] = 0;
                    peer.setDividerAttribute((undefined as DividerOptions | null | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1: {
                    peer.setGradientHeightAttribute((this._gradientHeight_0_0value as Dimension | undefined));
                    flagArray[12] = 2;
                    break;
                }
                case 3: {
                    flagArray[12] = 2;
                    break;
                }
                default: {
                    flagArray[12] = 0;
                    peer.setGradientHeightAttribute((undefined as Dimension | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1: {
                    peer.setEnableHapticFeedbackAttribute((this._enableHapticFeedback_0_0value as boolean | undefined));
                    flagArray[13] = 2;
                    break;
                }
                case 3: {
                    flagArray[13] = 2;
                    break;
                }
                default: {
                    flagArray[13] = 0;
                    peer.setEnableHapticFeedbackAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[14] != 0) {
            switch (flagArray[14]) {
                case 1: {
                    peer.setDigitalCrownSensitivityAttribute((this._digitalCrownSensitivity_0_0value as CrownSensitivity | undefined));
                    flagArray[14] = 2;
                    break;
                }
                case 3: {
                    flagArray[14] = 2;
                    break;
                }
                default: {
                    flagArray[14] = 0;
                    peer.setDigitalCrownSensitivityAttribute((undefined as CrownSensitivity | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: TextPickerModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: TextPickerModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.defaultPickerItemHeight(modifier._defaultPickerItemHeight_0_0value);
                    break;
                }
                default: {
                    this.defaultPickerItemHeight((undefined as double | string | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.canLoop(modifier._canLoop_0_0value);
                    break;
                }
                default: {
                    this.canLoop((undefined as boolean | undefined));
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
                    this.disableTextStyleAnimation(modifier._disableTextStyleAnimation_0_0value);
                    break;
                }
                default: {
                    this.disableTextStyleAnimation((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1:
                case 3: {
                    this.defaultTextStyle(modifier._defaultTextStyle_0_0value);
                    break;
                }
                default: {
                    this.defaultTextStyle((undefined as TextPickerTextStyle | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1:
                case 3: {
                    this.onChange(modifier._onChange_0_0value);
                    break;
                }
                default: {
                    this.onChange((undefined as OnTextPickerChangeCallback | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1:
                case 3: {
                    this.onScrollStop(modifier._onScrollStop_0_0value);
                    break;
                }
                default: {
                    this.onScrollStop((undefined as TextPickerScrollStopCallback | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1:
                case 3: {
                    this.onEnterSelectedArea(modifier._onEnterSelectedArea_0_0value);
                    break;
                }
                default: {
                    this.onEnterSelectedArea((undefined as TextPickerEnterSelectedAreaCallback | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1:
                case 3: {
                    this.selectedIndex(modifier._selectedIndex_0_0value);
                    break;
                }
                default: {
                    this.selectedIndex((undefined as int32 | Array<int32> | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1:
                case 3: {
                    this.divider(modifier._divider_0_0value);
                    break;
                }
                default: {
                    this.divider((undefined as DividerOptions | null | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1:
                case 3: {
                    this.gradientHeight(modifier._gradientHeight_0_0value);
                    break;
                }
                default: {
                    this.gradientHeight((undefined as Dimension | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
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
        if (flagArray[14] != 0) {
            switch (flagArray[14]) {
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
    }
    defaultPickerItemHeight(value: double | string | undefined): this {
        if (((this._flagArray[0]) == (0)) || ((this._defaultPickerItemHeight_0_0value) !== (value))) {
            this._flagArray[0] = 1
            this._defaultPickerItemHeight_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    canLoop(value: boolean | undefined): this {
        if (((this._flagArray[1]) == (0)) || ((this._canLoop_0_0value) !== (value))) {
            this._flagArray[1] = 1
            this._canLoop_0_0value = value
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
    disableTextStyleAnimation(value: boolean | undefined): this {
        if (((this._flagArray[5]) == (0)) || ((this._disableTextStyleAnimation_0_0value) !== (value))) {
            this._flagArray[5] = 1
            this._disableTextStyleAnimation_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    defaultTextStyle(value: TextPickerTextStyle | undefined): this {
        if (((this._flagArray[6]) == (0)) || (true)) {
            this._flagArray[6] = 1
            this._defaultTextStyle_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[6] = 3
        }
        return this
    }
    onChange(value: OnTextPickerChangeCallback | undefined): this {
        if (((this._flagArray[7]) == (0)) || (true)) {
            this._flagArray[7] = 1
            this._onChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[7] = 3
        }
        return this
    }
    onScrollStop(value: TextPickerScrollStopCallback | undefined): this {
        if (((this._flagArray[8]) == (0)) || (true)) {
            this._flagArray[8] = 1
            this._onScrollStop_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[8] = 3
        }
        return this
    }
    onEnterSelectedArea(value: TextPickerEnterSelectedAreaCallback | undefined): this {
        if (((this._flagArray[9]) == (0)) || (true)) {
            this._flagArray[9] = 1
            this._onEnterSelectedArea_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[9] = 3
        }
        return this
    }
    selectedIndex(value: int32 | Array<int32> | undefined): this {
        if (((this._flagArray[10]) == (0)) || ((this._selectedIndex_0_0value) !== (value))) {
            this._flagArray[10] = 1
            this._selectedIndex_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[10] = 3
        }
        return this
    }
    divider(value: DividerOptions | null | undefined): this {
        if (((this._flagArray[11]) == (0)) || (true)) {
            this._flagArray[11] = 1
            this._divider_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[11] = 3
        }
        return this
    }
    gradientHeight(value: Dimension | undefined): this {
        if (((this._flagArray[12]) == (0)) || (true)) {
            this._flagArray[12] = 1
            this._gradientHeight_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[12] = 3
        }
        return this
    }
    enableHapticFeedback(value: boolean | undefined): this {
        if (((this._flagArray[13]) == (0)) || ((this._enableHapticFeedback_0_0value) !== (value))) {
            this._flagArray[13] = 1
            this._enableHapticFeedback_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[13] = 3
        }
        return this
    }
    digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        if (((this._flagArray[14]) == (0)) || (true)) {
            this._flagArray[14] = 1
            this._digitalCrownSensitivity_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[14] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<TextPickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

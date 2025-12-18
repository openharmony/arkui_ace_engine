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
import { AttributeModifier, ContentModifier, hookSliderContentModifier } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkSliderPeer, SliderChangeMode, SliderBlockStyle, SliderInteraction, SliderConfiguration, SlideRange, SliderAttribute } from './component/slider'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod } from './component/common'
import { ResourceColor, Resource as arkui_component_units_Resource, Length, Dimension, SizeOptions, ResourceStr as arkui_component_units_ResourceStr } from './component/units'
import { Color as arkui_component_enums_Color, CrownSensitivity } from './component/enums'
import { Resource as global_resource_Resource } from 'global.resource'
import { LinearGradient } from './component/dataPanel'
export class SliderModifier extends CommonMethodModifier implements SliderAttribute,AttributeModifier<SliderAttribute> {
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
    applyNormalAttribute(instance: SliderAttribute): void { }
    applyPressedAttribute(instance: SliderAttribute): void { }
    applyFocusedAttribute(instance: SliderAttribute): void { }
    applyDisabledAttribute(instance: SliderAttribute): void { }
    applySelectedAttribute(instance: SliderAttribute): void { }
    public _blockColor_0_0value?: ResourceColor | undefined
    public _trackColor_0_0value?: ResourceColor | LinearGradient | undefined
    public _selectedColor_0_0value?: ResourceColor | LinearGradient | undefined
    public _showSteps_0_0value?: boolean | undefined
    public _trackThickness_0_0value?: Length | undefined
    public _onChange_0_0value?: ((value: double,mode: SliderChangeMode) => void) | undefined
    public _blockBorderColor_0_0value?: ResourceColor | undefined
    public _blockBorderWidth_0_0value?: Length | undefined
    public _stepColor_0_0value?: ResourceColor | undefined
    public _trackBorderRadius_0_0value?: Length | undefined
    public _selectedBorderRadius_0_0value?: Dimension | undefined
    public _blockSize_0_0value?: SizeOptions | undefined
    public _blockStyle_0_0value?: SliderBlockStyle | undefined
    public _stepSize_0_0value?: Length | undefined
    public _sliderInteractionMode_0_0value?: SliderInteraction | undefined
    public _minResponsiveDistance_0_0value?: double | undefined
    public _contentModifier_0_0value?: ContentModifier<SliderConfiguration> | undefined
    public _slideRange_0_0value?: SlideRange | undefined
    public _digitalCrownSensitivity_0_0value?: CrownSensitivity | undefined
    public _enableHapticFeedback_0_0value?: boolean | undefined
    public _showTips_0_0value?: boolean | undefined
    public _showTips_0_1value?: arkui_component_units_ResourceStr | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkSliderPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
        this.applyModifierPatch1(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkSliderPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setBlockColorAttribute((this._blockColor_0_0value as ResourceColor | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setBlockColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setTrackColorAttribute((this._trackColor_0_0value as ResourceColor | LinearGradient | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setTrackColorAttribute((undefined as ResourceColor | LinearGradient | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setSelectedColorAttribute((this._selectedColor_0_0value as ResourceColor | LinearGradient | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setSelectedColorAttribute((undefined as ResourceColor | LinearGradient | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setShowStepsAttribute((this._showSteps_0_0value as boolean | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setShowStepsAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setTrackThicknessAttribute((this._trackThickness_0_0value as Length | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setTrackThicknessAttribute((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as ((value: double,mode: SliderChangeMode) => void) | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setOnChangeAttribute((undefined as ((value: double,mode: SliderChangeMode) => void) | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1: {
                    peer.setBlockBorderColorAttribute((this._blockBorderColor_0_0value as ResourceColor | undefined));
                    flagArray[6] = 2;
                    break;
                }
                case 3: {
                    flagArray[6] = 2;
                    break;
                }
                default: {
                    flagArray[6] = 0;
                    peer.setBlockBorderColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1: {
                    peer.setBlockBorderWidthAttribute((this._blockBorderWidth_0_0value as Length | undefined));
                    flagArray[7] = 2;
                    break;
                }
                case 3: {
                    flagArray[7] = 2;
                    break;
                }
                default: {
                    flagArray[7] = 0;
                    peer.setBlockBorderWidthAttribute((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1: {
                    peer.setStepColorAttribute((this._stepColor_0_0value as ResourceColor | undefined));
                    flagArray[8] = 2;
                    break;
                }
                case 3: {
                    flagArray[8] = 2;
                    break;
                }
                default: {
                    flagArray[8] = 0;
                    peer.setStepColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1: {
                    peer.setTrackBorderRadiusAttribute((this._trackBorderRadius_0_0value as Length | undefined));
                    flagArray[9] = 2;
                    break;
                }
                case 3: {
                    flagArray[9] = 2;
                    break;
                }
                default: {
                    flagArray[9] = 0;
                    peer.setTrackBorderRadiusAttribute((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1: {
                    peer.setSelectedBorderRadiusAttribute((this._selectedBorderRadius_0_0value as Dimension | undefined));
                    flagArray[10] = 2;
                    break;
                }
                case 3: {
                    flagArray[10] = 2;
                    break;
                }
                default: {
                    flagArray[10] = 0;
                    peer.setSelectedBorderRadiusAttribute((undefined as Dimension | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1: {
                    peer.setBlockSizeAttribute((this._blockSize_0_0value as SizeOptions | undefined));
                    flagArray[11] = 2;
                    break;
                }
                case 3: {
                    flagArray[11] = 2;
                    break;
                }
                default: {
                    flagArray[11] = 0;
                    peer.setBlockSizeAttribute((undefined as SizeOptions | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1: {
                    peer.setBlockStyleAttribute((this._blockStyle_0_0value as SliderBlockStyle | undefined));
                    flagArray[12] = 2;
                    break;
                }
                case 3: {
                    flagArray[12] = 2;
                    break;
                }
                default: {
                    flagArray[12] = 0;
                    peer.setBlockStyleAttribute((undefined as SliderBlockStyle | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1: {
                    peer.setStepSizeAttribute((this._stepSize_0_0value as Length | undefined));
                    flagArray[13] = 2;
                    break;
                }
                case 3: {
                    flagArray[13] = 2;
                    break;
                }
                default: {
                    flagArray[13] = 0;
                    peer.setStepSizeAttribute((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[14] != 0) {
            switch (flagArray[14]) {
                case 1: {
                    peer.setSliderInteractionModeAttribute((this._sliderInteractionMode_0_0value as SliderInteraction | undefined));
                    flagArray[14] = 2;
                    break;
                }
                case 3: {
                    flagArray[14] = 2;
                    break;
                }
                default: {
                    flagArray[14] = 0;
                    peer.setSliderInteractionModeAttribute((undefined as SliderInteraction | undefined));
                }
            }
        }
        if (flagArray[15] != 0) {
            switch (flagArray[15]) {
                case 1: {
                    peer.setMinResponsiveDistanceAttribute((this._minResponsiveDistance_0_0value as double | undefined));
                    flagArray[15] = 2;
                    break;
                }
                case 3: {
                    flagArray[15] = 2;
                    break;
                }
                default: {
                    flagArray[15] = 0;
                    peer.setMinResponsiveDistanceAttribute((undefined as double | undefined));
                }
            }
        }
        if (flagArray[16] != 0) {
            switch (flagArray[16]) {
                case 1: {
                    hookSliderContentModifier(peer, (this._contentModifier_0_0value as ContentModifier<SliderConfiguration> | undefined));
                    flagArray[16] = 2;
                    break;
                }
                case 3: {
                    flagArray[16] = 2;
                    break;
                }
                default: {
                    flagArray[16] = 0;
                    hookSliderContentModifier(peer, (undefined as ContentModifier<SliderConfiguration> | undefined));
                }
            }
        }
        if (flagArray[17] != 0) {
            switch (flagArray[17]) {
                case 1: {
                    peer.setSlideRangeAttribute((this._slideRange_0_0value as SlideRange | undefined));
                    flagArray[17] = 2;
                    break;
                }
                case 3: {
                    flagArray[17] = 2;
                    break;
                }
                default: {
                    flagArray[17] = 0;
                    peer.setSlideRangeAttribute((undefined as SlideRange | undefined));
                }
            }
        }
        if (flagArray[18] != 0) {
            switch (flagArray[18]) {
                case 1: {
                    peer.setDigitalCrownSensitivityAttribute((this._digitalCrownSensitivity_0_0value as CrownSensitivity | undefined));
                    flagArray[18] = 2;
                    break;
                }
                case 3: {
                    flagArray[18] = 2;
                    break;
                }
                default: {
                    flagArray[18] = 0;
                    peer.setDigitalCrownSensitivityAttribute((undefined as CrownSensitivity | undefined));
                }
            }
        }
        if (flagArray[19] != 0) {
            switch (flagArray[19]) {
                case 1: {
                    peer.setEnableHapticFeedbackAttribute((this._enableHapticFeedback_0_0value as boolean | undefined));
                    flagArray[19] = 2;
                    break;
                }
                case 3: {
                    flagArray[19] = 2;
                    break;
                }
                default: {
                    flagArray[19] = 0;
                    peer.setEnableHapticFeedbackAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    applyModifierPatch1(peer: ArkSliderPeer, flagArray: Uint8Array): void {
        if (flagArray[20] != 0) {
            switch (flagArray[20]) {
                case 1: {
                    peer.setShowTipsAttribute((this._showTips_0_0value as boolean | undefined), (this._showTips_0_1value as arkui_component_units_ResourceStr | undefined | undefined));
                    flagArray[20] = 2;
                    break;
                }
                case 3: {
                    flagArray[20] = 2;
                    break;
                }
                default: {
                    flagArray[20] = 0;
                    peer.setShowTipsAttribute((undefined as boolean | undefined), (undefined as arkui_component_units_ResourceStr | undefined | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: SliderModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
        this.mergeModifier1(modifier, flagArray);
    }
    mergeModifier0(modifier: SliderModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.blockColor(modifier._blockColor_0_0value);
                    break;
                }
                default: {
                    this.blockColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.trackColor(modifier._trackColor_0_0value);
                    break;
                }
                default: {
                    this.trackColor((undefined as ResourceColor | LinearGradient | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.selectedColor(modifier._selectedColor_0_0value);
                    break;
                }
                default: {
                    this.selectedColor((undefined as ResourceColor | LinearGradient | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.showSteps(modifier._showSteps_0_0value);
                    break;
                }
                default: {
                    this.showSteps((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.trackThickness(modifier._trackThickness_0_0value);
                    break;
                }
                default: {
                    this.trackThickness((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1:
                case 3: {
                    this.onChange(modifier._onChange_0_0value);
                    break;
                }
                default: {
                    this.onChange((undefined as ((value: double,mode: SliderChangeMode) => void) | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1:
                case 3: {
                    this.blockBorderColor(modifier._blockBorderColor_0_0value);
                    break;
                }
                default: {
                    this.blockBorderColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1:
                case 3: {
                    this.blockBorderWidth(modifier._blockBorderWidth_0_0value);
                    break;
                }
                default: {
                    this.blockBorderWidth((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1:
                case 3: {
                    this.stepColor(modifier._stepColor_0_0value);
                    break;
                }
                default: {
                    this.stepColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1:
                case 3: {
                    this.trackBorderRadius(modifier._trackBorderRadius_0_0value);
                    break;
                }
                default: {
                    this.trackBorderRadius((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1:
                case 3: {
                    this.selectedBorderRadius(modifier._selectedBorderRadius_0_0value);
                    break;
                }
                default: {
                    this.selectedBorderRadius((undefined as Dimension | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1:
                case 3: {
                    this.blockSize(modifier._blockSize_0_0value);
                    break;
                }
                default: {
                    this.blockSize((undefined as SizeOptions | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1:
                case 3: {
                    this.blockStyle(modifier._blockStyle_0_0value);
                    break;
                }
                default: {
                    this.blockStyle((undefined as SliderBlockStyle | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1:
                case 3: {
                    this.stepSize(modifier._stepSize_0_0value);
                    break;
                }
                default: {
                    this.stepSize((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[14] != 0) {
            switch (flagArray[14]) {
                case 1:
                case 3: {
                    this.sliderInteractionMode(modifier._sliderInteractionMode_0_0value);
                    break;
                }
                default: {
                    this.sliderInteractionMode((undefined as SliderInteraction | undefined));
                }
            }
        }
        if (flagArray[15] != 0) {
            switch (flagArray[15]) {
                case 1:
                case 3: {
                    this.minResponsiveDistance(modifier._minResponsiveDistance_0_0value);
                    break;
                }
                default: {
                    this.minResponsiveDistance((undefined as double | undefined));
                }
            }
        }
        if (flagArray[16] != 0) {
            switch (flagArray[16]) {
                case 1:
                case 3: {
                    this.contentModifier(modifier._contentModifier_0_0value);
                    break;
                }
                default: {
                    this.contentModifier((undefined as ContentModifier<SliderConfiguration> | undefined));
                }
            }
        }
        if (flagArray[17] != 0) {
            switch (flagArray[17]) {
                case 1:
                case 3: {
                    this.slideRange(modifier._slideRange_0_0value);
                    break;
                }
                default: {
                    this.slideRange((undefined as SlideRange | undefined));
                }
            }
        }
        if (flagArray[18] != 0) {
            switch (flagArray[18]) {
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
        if (flagArray[19] != 0) {
            switch (flagArray[19]) {
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
    }
    mergeModifier1(modifier: SliderModifier, flagArray: Uint8Array): void {
        if (flagArray[20] != 0) {
            switch (flagArray[20]) {
                case 1:
                case 3: {
                    this.showTips(modifier._showTips_0_0value, modifier._showTips_0_1value);
                    break;
                }
                default: {
                    this.showTips((undefined as boolean | undefined), (undefined as arkui_component_units_ResourceStr | undefined | undefined));
                }
            }
        }
    }
    blockColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._blockColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    trackColor(value: ResourceColor | LinearGradient | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._trackColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    selectedColor(value: ResourceColor | LinearGradient | undefined): this {
        if (((this._flagArray[2]) == (0)) || (true)) {
            this._flagArray[2] = 1
            this._selectedColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    showSteps(value: boolean | undefined): this {
        if (((this._flagArray[3]) == (0)) || ((this._showSteps_0_0value) !== (value))) {
            this._flagArray[3] = 1
            this._showSteps_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    trackThickness(value: Length | undefined): this {
        if (((this._flagArray[4]) == (0)) || (true)) {
            this._flagArray[4] = 1
            this._trackThickness_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    onChange(value: ((value: double,mode: SliderChangeMode) => void) | undefined): this {
        if (((this._flagArray[5]) == (0)) || (true)) {
            this._flagArray[5] = 1
            this._onChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    blockBorderColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[6]) == (0)) || (true)) {
            this._flagArray[6] = 1
            this._blockBorderColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[6] = 3
        }
        return this
    }
    blockBorderWidth(value: Length | undefined): this {
        if (((this._flagArray[7]) == (0)) || (true)) {
            this._flagArray[7] = 1
            this._blockBorderWidth_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[7] = 3
        }
        return this
    }
    stepColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[8]) == (0)) || (true)) {
            this._flagArray[8] = 1
            this._stepColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[8] = 3
        }
        return this
    }
    trackBorderRadius(value: Length | undefined): this {
        if (((this._flagArray[9]) == (0)) || (true)) {
            this._flagArray[9] = 1
            this._trackBorderRadius_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[9] = 3
        }
        return this
    }
    selectedBorderRadius(value: Dimension | undefined): this {
        if (((this._flagArray[10]) == (0)) || (true)) {
            this._flagArray[10] = 1
            this._selectedBorderRadius_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[10] = 3
        }
        return this
    }
    blockSize(value: SizeOptions | undefined): this {
        if (((this._flagArray[11]) == (0)) || (true)) {
            this._flagArray[11] = 1
            this._blockSize_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[11] = 3
        }
        return this
    }
    blockStyle(value: SliderBlockStyle | undefined): this {
        if (((this._flagArray[12]) == (0)) || (true)) {
            this._flagArray[12] = 1
            this._blockStyle_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[12] = 3
        }
        return this
    }
    stepSize(value: Length | undefined): this {
        if (((this._flagArray[13]) == (0)) || (true)) {
            this._flagArray[13] = 1
            this._stepSize_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[13] = 3
        }
        return this
    }
    sliderInteractionMode(value: SliderInteraction | undefined): this {
        if (((this._flagArray[14]) == (0)) || (true)) {
            this._flagArray[14] = 1
            this._sliderInteractionMode_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[14] = 3
        }
        return this
    }
    minResponsiveDistance(value: double | undefined): this {
        if (((this._flagArray[15]) == (0)) || ((this._minResponsiveDistance_0_0value) !== (value))) {
            this._flagArray[15] = 1
            this._minResponsiveDistance_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[15] = 3
        }
        return this
    }
    contentModifier(value: ContentModifier<SliderConfiguration> | undefined): this {
        if (((this._flagArray[16]) == (0)) || (true)) {
            this._flagArray[16] = 1
            this._contentModifier_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[16] = 3
        }
        return this
    }
    slideRange(value: SlideRange | undefined): this {
        if (((this._flagArray[17]) == (0)) || (true)) {
            this._flagArray[17] = 1
            this._slideRange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[17] = 3
        }
        return this
    }
    digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        if (((this._flagArray[18]) == (0)) || (true)) {
            this._flagArray[18] = 1
            this._digitalCrownSensitivity_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[18] = 3
        }
        return this
    }
    enableHapticFeedback(value: boolean | undefined): this {
        if (((this._flagArray[19]) == (0)) || ((this._enableHapticFeedback_0_0value) !== (value))) {
            this._flagArray[19] = 1
            this._enableHapticFeedback_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[19] = 3
        }
        return this
    }
    showTips(value: boolean | undefined, content?: arkui_component_units_ResourceStr): this {
        if (((this._flagArray[20]) == (0)) || ((this._showTips_0_0value) !== (value)) || (true)) {
            this._flagArray[20] = 1
            this._showTips_0_0value = value
            this._showTips_0_1value = content
            this._state.fireChange()
        } else {
            this._flagArray[20] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<SliderAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

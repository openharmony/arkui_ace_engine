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
import { AttributeModifier, ContentModifier, hookSliderContentModifier, hookSliderSetPrefixMethod, hookSliderSetSuffixMethod } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkSliderPeer, SliderChangeMode, SliderBlockStyle, SliderInteraction, SliderConfiguration, SlideRange, SliderAttribute, SliderShowStepOptions, SliderPrefixOptions, SliderSuffixOptions } from "./component/slider"
import { int32 } from "@koalaui/common"
import { CommonMethod } from "./component/common"
import { ResourceColor, Length, Dimension, SizeOptions, ResourceStr } from "./component/units"
import { Color, CrownSensitivity } from "./component/enums"
import { Resource } from "global.resource"
import { LinearGradient } from "./component/dataPanel"
import { ComponentContent } from "arkui.ComponentContent"
export class SliderModifier extends CommonMethodModifier implements SliderAttribute,AttributeModifier<SliderAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: SliderAttribute): void { }
    applyPressedAttribute(instance: SliderAttribute): void { }
    applyFocusedAttribute(instance: SliderAttribute): void { }
    applyDisabledAttribute(instance: SliderAttribute): void { }
    applySelectedAttribute(instance: SliderAttribute): void { }
    _blockColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _blockColor_0_0value?: ResourceColor | LinearGradient | undefined
    _trackColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _trackColor_0_0value?: ResourceColor | LinearGradient | undefined
    _selectedColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedColor_0_0value?: ResourceColor | LinearGradient | undefined
    _showSteps_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _showSteps_0_0value?: boolean | undefined
    _trackThickness_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _trackThickness_0_0value?: Length | undefined
    _onChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onChange_0_0value?: ((value: double,mode: SliderChangeMode) => void) | undefined
    _blockBorderColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _blockBorderColor_0_0value?: ResourceColor | undefined
    _blockBorderWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _blockBorderWidth_0_0value?: Length | undefined
    _stepColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _stepColor_0_0value?: ResourceColor | undefined
    _trackBorderRadius_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _trackBorderRadius_0_0value?: Length | undefined
    _selectedBorderRadius_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedBorderRadius_0_0value?: Dimension | undefined
    _blockSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _blockSize_0_0value?: SizeOptions | undefined
    _blockStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _blockStyle_0_0value?: SliderBlockStyle | undefined
    _stepSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _stepSize_0_0value?: Length | undefined
    _sliderInteractionMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _sliderInteractionMode_0_0value?: SliderInteraction | undefined
    _minResponsiveDistance_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _minResponsiveDistance_0_0value?: double | undefined
    _slideRange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _slideRange_0_0value?: SlideRange | undefined
    _digitalCrownSensitivity_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _digitalCrownSensitivity_0_0value?: CrownSensitivity | undefined
    _enableHapticFeedback_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableHapticFeedback_0_0value?: boolean | undefined
    _showSteps_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _showSteps_1_0value?: boolean | undefined
    _showSteps_1_1value?: SliderShowStepOptions | undefined
    _prefix_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _prefix_0_0value?: ComponentContent | undefined
    _prefix_0_1value?: SliderPrefixOptions | undefined
    _suffix_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _suffix_0_0value?: ComponentContent | undefined
    _suffix_0_1value?: SliderSuffixOptions | undefined
    _showTips_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _showTips_0_0value?: boolean | undefined
    _showTips_0_1value?: ResourceStr | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkSliderPeer;
        if (this._blockColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._blockColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBlockColorAttribute((this._blockColor_0_0value as ResourceColor | LinearGradient | undefined));
                    this._blockColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._blockColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._blockColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBlockColorAttribute((undefined as ResourceColor | LinearGradient | undefined));
                }
            }
        }
        if (this._trackColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._trackColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTrackColorAttribute((this._trackColor_0_0value as ResourceColor | LinearGradient | undefined));
                    this._trackColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._trackColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._trackColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTrackColorAttribute((undefined as ResourceColor | LinearGradient | undefined));
                }
            }
        }
        if (this._selectedColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectedColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSelectedColorAttribute((this._selectedColor_0_0value as ResourceColor | LinearGradient | undefined));
                    this._selectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectedColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSelectedColorAttribute((undefined as ResourceColor | LinearGradient | undefined));
                }
            }
        }
        if (this._showSteps_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._showSteps_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setShowSteps0Attribute((this._showSteps_0_0value as boolean | undefined));
                    this._showSteps_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._showSteps_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._showSteps_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setShowSteps0Attribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._trackThickness_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._trackThickness_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTrackThicknessAttribute((this._trackThickness_0_0value as Length | undefined));
                    this._trackThickness_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._trackThickness_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._trackThickness_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTrackThicknessAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as ((value: double,mode: SliderChangeMode) => void) | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnChangeAttribute((undefined as ((value: double,mode: SliderChangeMode) => void) | undefined));
                }
            }
        }
        if (this._blockBorderColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._blockBorderColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBlockBorderColorAttribute((this._blockBorderColor_0_0value as ResourceColor | undefined));
                    this._blockBorderColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._blockBorderColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._blockBorderColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBlockBorderColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._blockBorderWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._blockBorderWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBlockBorderWidthAttribute((this._blockBorderWidth_0_0value as Length | undefined));
                    this._blockBorderWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._blockBorderWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._blockBorderWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBlockBorderWidthAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._stepColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._stepColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStepColorAttribute((this._stepColor_0_0value as ResourceColor | undefined));
                    this._stepColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._stepColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._stepColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStepColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._trackBorderRadius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._trackBorderRadius_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTrackBorderRadiusAttribute((this._trackBorderRadius_0_0value as Length | undefined));
                    this._trackBorderRadius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._trackBorderRadius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._trackBorderRadius_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTrackBorderRadiusAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._selectedBorderRadius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectedBorderRadius_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSelectedBorderRadiusAttribute((this._selectedBorderRadius_0_0value as Dimension | undefined));
                    this._selectedBorderRadius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectedBorderRadius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectedBorderRadius_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSelectedBorderRadiusAttribute((undefined as Dimension | undefined));
                }
            }
        }
        if (this._blockSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._blockSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBlockSizeAttribute((this._blockSize_0_0value as SizeOptions | undefined));
                    this._blockSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._blockSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._blockSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBlockSizeAttribute((undefined as SizeOptions | undefined));
                }
            }
        }
        if (this._blockStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._blockStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBlockStyleAttribute((this._blockStyle_0_0value as SliderBlockStyle | undefined));
                    this._blockStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._blockStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._blockStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBlockStyleAttribute((undefined as SliderBlockStyle | undefined));
                }
            }
        }
        if (this._stepSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._stepSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStepSizeAttribute((this._stepSize_0_0value as Length | undefined));
                    this._stepSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._stepSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._stepSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStepSizeAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._sliderInteractionMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._sliderInteractionMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSliderInteractionModeAttribute((this._sliderInteractionMode_0_0value as SliderInteraction | undefined));
                    this._sliderInteractionMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._sliderInteractionMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._sliderInteractionMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSliderInteractionModeAttribute((undefined as SliderInteraction | undefined));
                }
            }
        }
        if (this._minResponsiveDistance_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._minResponsiveDistance_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMinResponsiveDistanceAttribute((this._minResponsiveDistance_0_0value as double | undefined));
                    this._minResponsiveDistance_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minResponsiveDistance_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._minResponsiveDistance_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMinResponsiveDistanceAttribute((undefined as double | undefined));
                }
            }
        }
        if (this._slideRange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._slideRange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSlideRangeAttribute((this._slideRange_0_0value as SlideRange | undefined));
                    this._slideRange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._slideRange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._slideRange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSlideRangeAttribute((undefined as SlideRange | undefined));
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
        if (this._showSteps_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._showSteps_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setShowSteps1Attribute((this._showSteps_1_0value as boolean | undefined), (this._showSteps_1_1value as SliderShowStepOptions | undefined | undefined));
                    this._showSteps_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._showSteps_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._showSteps_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setShowSteps1Attribute((undefined as boolean | undefined), (undefined as SliderShowStepOptions | undefined | undefined));
                }
            }
        }
        if (this._prefix_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._prefix_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    hookSliderSetPrefixMethod(peer, (this._prefix_0_0value as ComponentContent | undefined), (this._prefix_0_1value as SliderPrefixOptions | undefined | undefined));
                    this._prefix_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._prefix_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._prefix_0_flag = AttributeUpdaterFlag.INITIAL;
                    hookSliderSetPrefixMethod(peer, (undefined as ComponentContent | undefined), (undefined as SliderPrefixOptions | undefined | undefined));
                }
            }
        }
        if (this._suffix_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._suffix_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    hookSliderSetSuffixMethod(peer, (this._suffix_0_0value as ComponentContent | undefined), (this._suffix_0_1value as SliderSuffixOptions | undefined | undefined));
                    this._suffix_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._suffix_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._suffix_0_flag = AttributeUpdaterFlag.INITIAL;
                    hookSliderSetSuffixMethod(peer, (undefined as ComponentContent | undefined), (undefined as SliderSuffixOptions | undefined | undefined));
                }
            }
        }
        if (this._showTips_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._showTips_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setShowTipsAttribute((this._showTips_0_0value as boolean | undefined), (this._showTips_0_1value as ResourceStr | undefined | undefined));
                    this._showTips_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._showTips_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._showTips_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setShowTipsAttribute((undefined as boolean | undefined), (undefined as ResourceStr | undefined | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: SliderModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._blockColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._blockColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.blockColor(modifier._blockColor_0_0value);
                    break;
                }
                default: {
                    this.blockColor((undefined as ResourceColor | LinearGradient | undefined));
                }
            }
        }
        if (modifier._trackColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._trackColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.trackColor(modifier._trackColor_0_0value);
                    break;
                }
                default: {
                    this.trackColor((undefined as ResourceColor | LinearGradient | undefined));
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
                    this.selectedColor((undefined as ResourceColor | LinearGradient | undefined));
                }
            }
        }
        if (modifier._showSteps_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._showSteps_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.showSteps(modifier._showSteps_0_0value);
                    break;
                }
                default: {
                    this.showSteps((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._trackThickness_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._trackThickness_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.trackThickness(modifier._trackThickness_0_0value);
                    break;
                }
                default: {
                    this.trackThickness((undefined as Length | undefined));
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
                    this.onChange((undefined as ((value: double,mode: SliderChangeMode) => void) | undefined));
                }
            }
        }
        if (modifier._blockBorderColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._blockBorderColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.blockBorderColor(modifier._blockBorderColor_0_0value);
                    break;
                }
                default: {
                    this.blockBorderColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._blockBorderWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._blockBorderWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.blockBorderWidth(modifier._blockBorderWidth_0_0value);
                    break;
                }
                default: {
                    this.blockBorderWidth((undefined as Length | undefined));
                }
            }
        }
        if (modifier._stepColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._stepColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.stepColor(modifier._stepColor_0_0value);
                    break;
                }
                default: {
                    this.stepColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._trackBorderRadius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._trackBorderRadius_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.trackBorderRadius(modifier._trackBorderRadius_0_0value);
                    break;
                }
                default: {
                    this.trackBorderRadius((undefined as Length | undefined));
                }
            }
        }
        if (modifier._selectedBorderRadius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selectedBorderRadius_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selectedBorderRadius(modifier._selectedBorderRadius_0_0value);
                    break;
                }
                default: {
                    this.selectedBorderRadius((undefined as Dimension | undefined));
                }
            }
        }
        if (modifier._blockSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._blockSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.blockSize(modifier._blockSize_0_0value);
                    break;
                }
                default: {
                    this.blockSize((undefined as SizeOptions | undefined));
                }
            }
        }
        if (modifier._blockStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._blockStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.blockStyle(modifier._blockStyle_0_0value);
                    break;
                }
                default: {
                    this.blockStyle((undefined as SliderBlockStyle | undefined));
                }
            }
        }
        if (modifier._stepSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._stepSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.stepSize(modifier._stepSize_0_0value);
                    break;
                }
                default: {
                    this.stepSize((undefined as Length | undefined));
                }
            }
        }
        if (modifier._sliderInteractionMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._sliderInteractionMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.sliderInteractionMode(modifier._sliderInteractionMode_0_0value);
                    break;
                }
                default: {
                    this.sliderInteractionMode((undefined as SliderInteraction | undefined));
                }
            }
        }
        if (modifier._minResponsiveDistance_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._minResponsiveDistance_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.minResponsiveDistance(modifier._minResponsiveDistance_0_0value);
                    break;
                }
                default: {
                    this.minResponsiveDistance((undefined as double | undefined));
                }
            }
        }
        if (modifier._slideRange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._slideRange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.slideRange(modifier._slideRange_0_0value);
                    break;
                }
                default: {
                    this.slideRange((undefined as SlideRange | undefined));
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
        if (modifier._showSteps_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._showSteps_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.showSteps(modifier._showSteps_1_0value, modifier._showSteps_1_1value);
                    break;
                }
                default: {
                    this.showSteps((undefined as boolean | undefined), (undefined as SliderShowStepOptions | undefined | undefined));
                }
            }
        }
        if (modifier._prefix_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._prefix_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.prefix(modifier._prefix_0_0value, modifier._prefix_0_1value);
                    break;
                }
                default: {
                    this.prefix((undefined as ComponentContent | undefined), (undefined as SliderPrefixOptions | undefined | undefined));
                }
            }
        }
        if (modifier._suffix_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._suffix_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.suffix(modifier._suffix_0_0value, modifier._suffix_0_1value);
                    break;
                }
                default: {
                    this.suffix((undefined as ComponentContent | undefined), (undefined as SliderSuffixOptions | undefined | undefined));
                }
            }
        }
        if (modifier._showTips_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._showTips_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.showTips(modifier._showTips_0_0value, modifier._showTips_0_1value);
                    break;
                }
                default: {
                    this.showTips((undefined as boolean | undefined), (undefined as ResourceStr | undefined | undefined));
                }
            }
        }
    }
    blockColor(value: ResourceColor | LinearGradient | undefined): this {
        if (((this._blockColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._blockColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._blockColor_0_0value = value
        } else
        {
            this._blockColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    trackColor(value: ResourceColor | LinearGradient | undefined): this {
        if (((this._trackColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._trackColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._trackColor_0_0value = value
        } else
        {
            this._trackColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selectedColor(value: ResourceColor | LinearGradient | undefined): this {
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
    showSteps(value: boolean | undefined): this {
        if (((this._showSteps_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._showSteps_0_0value) !== (value)))
        {
            this._showSteps_0_flag = AttributeUpdaterFlag.UPDATE
            this._showSteps_0_0value = value
        } else
        {
            this._showSteps_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    trackThickness(value: Length | undefined): this {
        if (((this._trackThickness_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._trackThickness_0_flag = AttributeUpdaterFlag.UPDATE
            this._trackThickness_0_0value = value
        } else
        {
            this._trackThickness_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onChange(value: ((value: double,mode: SliderChangeMode) => void) | undefined): this {
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
    blockBorderColor(value: ResourceColor | undefined): this {
        if (((this._blockBorderColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._blockBorderColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._blockBorderColor_0_0value = value
        } else
        {
            this._blockBorderColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    blockBorderWidth(value: Length | undefined): this {
        if (((this._blockBorderWidth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._blockBorderWidth_0_flag = AttributeUpdaterFlag.UPDATE
            this._blockBorderWidth_0_0value = value
        } else
        {
            this._blockBorderWidth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    stepColor(value: ResourceColor | undefined): this {
        if (((this._stepColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._stepColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._stepColor_0_0value = value
        } else
        {
            this._stepColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    trackBorderRadius(value: Length | undefined): this {
        if (((this._trackBorderRadius_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._trackBorderRadius_0_flag = AttributeUpdaterFlag.UPDATE
            this._trackBorderRadius_0_0value = value
        } else
        {
            this._trackBorderRadius_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selectedBorderRadius(value: Dimension | undefined): this {
        if (((this._selectedBorderRadius_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._selectedBorderRadius_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectedBorderRadius_0_0value = value
        } else
        {
            this._selectedBorderRadius_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    blockSize(value: SizeOptions | undefined): this {
        if (((this._blockSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._blockSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._blockSize_0_0value = value
        } else
        {
            this._blockSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    blockStyle(value: SliderBlockStyle | undefined): this {
        if (((this._blockStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._blockStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._blockStyle_0_0value = value
        } else
        {
            this._blockStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    stepSize(value: Length | undefined): this {
        if (((this._stepSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._stepSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._stepSize_0_0value = value
        } else
        {
            this._stepSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    sliderInteractionMode(value: SliderInteraction | undefined): this {
        if (((this._sliderInteractionMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._sliderInteractionMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._sliderInteractionMode_0_0value = value
        } else
        {
            this._sliderInteractionMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    minResponsiveDistance(value: double | undefined): this {
        if (((this._minResponsiveDistance_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._minResponsiveDistance_0_0value) !== (value)))
        {
            this._minResponsiveDistance_0_flag = AttributeUpdaterFlag.UPDATE
            this._minResponsiveDistance_0_0value = value
        } else
        {
            this._minResponsiveDistance_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    slideRange(value: SlideRange | undefined): this {
        if (((this._slideRange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._slideRange_0_flag = AttributeUpdaterFlag.UPDATE
            this._slideRange_0_0value = value
        } else
        {
            this._slideRange_0_flag = AttributeUpdaterFlag.SKIP
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
    showSteps(value: boolean | undefined, options?: SliderShowStepOptions): this {
        if (((this._showSteps_1_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._showSteps_1_0value) !== (value)) || (true))
        {
            this._showSteps_1_flag = AttributeUpdaterFlag.UPDATE
            this._showSteps_1_0value = value
            this._showSteps_1_1value = options
        } else
        {
            this._showSteps_1_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    prefix(content: ComponentContent | undefined, options?: SliderPrefixOptions): this {
        if (((this._prefix_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._prefix_0_flag = AttributeUpdaterFlag.UPDATE
            this._prefix_0_0value = content
            this._prefix_0_1value = options
        } else
        {
            this._prefix_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    suffix(content: ComponentContent | undefined, options?: SliderSuffixOptions): this {
        if (((this._suffix_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._suffix_0_flag = AttributeUpdaterFlag.UPDATE
            this._suffix_0_0value = content
            this._suffix_0_1value = options
        } else
        {
            this._suffix_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    showTips(value: boolean | undefined, content?: ResourceStr): this {
        if (((this._showTips_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._showTips_0_0value) !== (value)) || (true))
        {
            this._showTips_0_flag = AttributeUpdaterFlag.UPDATE
            this._showTips_0_0value = value
            this._showTips_0_1value = content
        } else
        {
            this._showTips_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<SliderAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

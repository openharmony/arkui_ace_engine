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

import { AttributeModifier, ResourceColor, LinearGradient, Length, Dimension, SizeOptions, CrownSensitivity, ResourceStr } from './component';
import { ContentModifier } from './component/common';
import { ArkSliderPeer, SliderAttribute, SliderInteraction, SliderConfiguration, SlideRange, SliderBlockStyle, SliderChangeMode, ArkSliderComponent } from './component/slider';
import { CommonMethodModifier, AttributeUpdaterFlag } from './CommonMethodModifier';
import { hookSliderContentModifier } from './handwritten';

export class SliderModifier extends CommonMethodModifier implements SliderAttribute, AttributeModifier<SliderAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyNormalAttribute(instance: SliderAttribute): void {}
    applyPressedAttribute(instance: SliderAttribute): void {}
    applyFocusedAttribute(instance: SliderAttribute): void {}
    applyDisabledAttribute(instance: SliderAttribute): void {}
    applySelectedAttribute(instance: SliderAttribute): void {}
    _blockColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _blockColor_0_0value?: ResourceColor | undefined
    _trackColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _trackColor_0_0value?: ResourceColor | LinearGradient | undefined
    _selectedColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedColor_0_0value?: ResourceColor | LinearGradient | undefined
    _minLabel_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _minLabel_0_0value?: string | undefined
    _maxLabel_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maxLabel_0_0value?: string | undefined
    _showSteps_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _showSteps_0_0value?: boolean | undefined
    _trackThickness_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _trackThickness_0_0value?: Length | undefined
    _onChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onChange_0_0value?: ((value: number,mode: SliderChangeMode) => void) | undefined
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
    _minResponsiveDistance_0_0value?: number | undefined
    _contentModifier_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _contentModifier_0_0value?: ContentModifier<SliderConfiguration> | undefined
    _slideRange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _slideRange_0_0value?: SlideRange | undefined
    _digitalCrownSensitivity_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _digitalCrownSensitivity_0_0value?: CrownSensitivity | undefined
    _enableHapticFeedback_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableHapticFeedback_0_0value?: boolean | undefined
    _showTips_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _showTips_0_0value?: boolean | undefined
    _showTips_0_1content?: ResourceStr | undefined
    applyModifierPatch(peer: ArkSliderPeer): void {
        super.applyModifierPatch(peer)
        if (this._blockColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._blockColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.blockColorAttribute((this._blockColor_0_0value as ResourceColor | undefined));
                    this._blockColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._blockColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._blockColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.blockColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._trackColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._trackColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.trackColorAttribute((this._trackColor_0_0value as ResourceColor | LinearGradient | undefined));
                    this._trackColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._trackColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._trackColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.trackColorAttribute((undefined as ResourceColor | LinearGradient | undefined));
                }
            }
        }
        if (this._selectedColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectedColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.selectedColor1Attribute((this._selectedColor_0_0value as ResourceColor | LinearGradient | undefined));
                    this._selectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectedColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.selectedColor1Attribute((undefined as ResourceColor | LinearGradient | undefined));
                }
            }
        }
        if (this._minLabel_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._minLabel_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.minLabelAttribute((this._minLabel_0_0value as string | undefined));
                    this._minLabel_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minLabel_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._minLabel_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.minLabelAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._maxLabel_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._maxLabel_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.maxLabelAttribute((this._maxLabel_0_0value as string | undefined));
                    this._maxLabel_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maxLabel_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._maxLabel_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.maxLabelAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._showSteps_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._showSteps_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.showStepsAttribute((this._showSteps_0_0value as boolean | undefined));
                    this._showSteps_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._showSteps_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._showSteps_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.showStepsAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._trackThickness_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._trackThickness_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.trackThicknessAttribute((this._trackThickness_0_0value as Length | undefined));
                    this._trackThickness_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._trackThickness_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._trackThickness_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.trackThicknessAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onChangeAttribute((this._onChange_0_0value as ((value: number,mode: SliderChangeMode) => void) | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onChangeAttribute((undefined as ((value: number,mode: SliderChangeMode) => void) | undefined));
                }
            }
        }
        if (this._blockBorderColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._blockBorderColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.blockBorderColorAttribute((this._blockBorderColor_0_0value as ResourceColor | undefined));
                    this._blockBorderColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._blockBorderColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._blockBorderColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.blockBorderColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._blockBorderWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._blockBorderWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.blockBorderWidthAttribute((this._blockBorderWidth_0_0value as Length | undefined));
                    this._blockBorderWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._blockBorderWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._blockBorderWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.blockBorderWidthAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._stepColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._stepColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.stepColorAttribute((this._stepColor_0_0value as ResourceColor | undefined));
                    this._stepColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._stepColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._stepColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.stepColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._trackBorderRadius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._trackBorderRadius_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.trackBorderRadiusAttribute((this._trackBorderRadius_0_0value as Length | undefined));
                    this._trackBorderRadius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._trackBorderRadius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._trackBorderRadius_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.trackBorderRadiusAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._selectedBorderRadius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectedBorderRadius_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.selectedBorderRadiusAttribute((this._selectedBorderRadius_0_0value as Dimension | undefined));
                    this._selectedBorderRadius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectedBorderRadius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectedBorderRadius_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.selectedBorderRadiusAttribute((undefined as Dimension | undefined));
                }
            }
        }
        if (this._blockSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._blockSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.blockSizeAttribute((this._blockSize_0_0value as SizeOptions | undefined));
                    this._blockSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._blockSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._blockSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.blockSizeAttribute((undefined as SizeOptions | undefined));
                }
            }
        }
        if (this._blockStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._blockStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.blockStyleAttribute((this._blockStyle_0_0value as SliderBlockStyle | undefined));
                    this._blockStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._blockStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._blockStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.blockStyleAttribute((undefined as SliderBlockStyle | undefined));
                }
            }
        }
        if (this._stepSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._stepSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.stepSizeAttribute((this._stepSize_0_0value as Length | undefined));
                    this._stepSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._stepSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._stepSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.stepSizeAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._sliderInteractionMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._sliderInteractionMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.sliderInteractionModeAttribute((this._sliderInteractionMode_0_0value as SliderInteraction | undefined));
                    this._sliderInteractionMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._sliderInteractionMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._sliderInteractionMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.sliderInteractionModeAttribute((undefined as SliderInteraction | undefined));
                }
            }
        }
        if (this._minResponsiveDistance_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._minResponsiveDistance_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.minResponsiveDistanceAttribute((this._minResponsiveDistance_0_0value as number | undefined));
                    this._minResponsiveDistance_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minResponsiveDistance_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._minResponsiveDistance_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.minResponsiveDistanceAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._contentModifier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._contentModifier_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    const arkSliderComponent: ArkSliderComponent = new ArkSliderComponent();
                    arkSliderComponent.setPeer(peer);
                    hookSliderContentModifier(arkSliderComponent, (this._contentModifier_0_0value as ContentModifier<SliderConfiguration> | undefined));
                    this._contentModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._contentModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._contentModifier_0_flag = AttributeUpdaterFlag.INITIAL;
                    const arkSliderComponent: ArkSliderComponent = new ArkSliderComponent();
                    arkSliderComponent.setPeer(peer);
                    hookSliderContentModifier(arkSliderComponent, (this._contentModifier_0_0value as ContentModifier<SliderConfiguration> | undefined));
                }
            }
        }
        if (this._slideRange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._slideRange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.slideRangeAttribute((this._slideRange_0_0value as SlideRange | undefined));
                    this._slideRange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._slideRange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._slideRange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.slideRangeAttribute((undefined as SlideRange | undefined));
                }
            }
        }
        if (this._digitalCrownSensitivity_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._digitalCrownSensitivity_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.digitalCrownSensitivityAttribute((this._digitalCrownSensitivity_0_0value as CrownSensitivity | undefined));
                    this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.digitalCrownSensitivityAttribute((undefined as CrownSensitivity | undefined));
                }
            }
        }
        if (this._enableHapticFeedback_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableHapticFeedback_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.enableHapticFeedbackAttribute((this._enableHapticFeedback_0_0value as boolean | undefined));
                    this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.enableHapticFeedbackAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._showTips_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._showTips_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.showTipsAttribute((this._showTips_0_0value as boolean | undefined), (this._showTips_0_1content as ResourceStr | undefined));
                    this._showTips_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._showTips_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._showTips_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.showTipsAttribute((undefined as boolean | undefined), (undefined as ResourceStr | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: SliderModifier): void {
        super.mergeModifier(modifier)
        if (modifier._blockColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._blockColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.blockColor(modifier._blockColor_0_0value);
                    break;
                }
                default: {
                    this.blockColor((undefined as ResourceColor | undefined));
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
        if (modifier._minLabel_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._minLabel_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.minLabel(modifier._minLabel_0_0value);
                    break;
                }
                default: {
                    this.minLabel((undefined as string | undefined));
                }
            }
        }
        if (modifier._maxLabel_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._maxLabel_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.maxLabel(modifier._maxLabel_0_0value);
                    break;
                }
                default: {
                    this.maxLabel((undefined as string | undefined));
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
                    this.onChange((undefined as ((value: number,mode: SliderChangeMode) => void) | undefined));
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
                    this.minResponsiveDistance((undefined as number | undefined));
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
                    this.contentModifier((undefined as ContentModifier<SliderConfiguration> | undefined));
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
        if (modifier._showTips_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._showTips_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.showTips(modifier._showTips_0_0value, modifier._showTips_0_1content);
                    break;
                }
                default: {
                    this.showTips((undefined as boolean | undefined), (undefined as ResourceStr | undefined));
                }
            }
        }
    }

    blockColor(value: ResourceColor | undefined): this {
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
    minLabel(value: string | undefined): this {
        if (((this._minLabel_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._minLabel_0_flag = AttributeUpdaterFlag.UPDATE
            this._minLabel_0_0value = value
        } else
        {
            this._minLabel_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    maxLabel(value: string | undefined): this {
        if (((this._maxLabel_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._maxLabel_0_flag = AttributeUpdaterFlag.UPDATE
            this._maxLabel_0_0value = value
        } else
        {
            this._maxLabel_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    showSteps(value: boolean | undefined): this {
        if (((this._showSteps_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
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
    onChange(value: ((value: number,mode: SliderChangeMode) => void) | undefined): this {
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
    minResponsiveDistance(value: number | undefined): this {
        if (((this._minResponsiveDistance_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._minResponsiveDistance_0_flag = AttributeUpdaterFlag.UPDATE
            this._minResponsiveDistance_0_0value = value
        } else
        {
            this._minResponsiveDistance_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    contentModifier(value: ContentModifier<SliderConfiguration> | undefined): this {
        if (((this._contentModifier_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._contentModifier_0_flag = AttributeUpdaterFlag.UPDATE
            this._contentModifier_0_0value = value
        } else
        {
            this._contentModifier_0_flag = AttributeUpdaterFlag.SKIP
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
        if (((this._enableHapticFeedback_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableHapticFeedback_0_0value = value
        } else
        {
            this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    showTips(value: boolean | undefined, content?:  ResourceStr | undefined): this {
        if (((this._showTips_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._showTips_0_flag = AttributeUpdaterFlag.UPDATE
            this._showTips_0_0value = value
            this._showTips_0_1content = content
        } else
        {
            this._showTips_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    _onChangeEvent_value(callback: ((index: number) => void)): void {}
}
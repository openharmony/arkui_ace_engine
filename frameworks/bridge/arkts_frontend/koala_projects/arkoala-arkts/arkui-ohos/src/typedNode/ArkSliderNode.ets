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

import { InteropNativeModule } from "@koalaui/interop";
import { ArkBaseNode } from "./ArkBaseNode";
import {
    ArkSliderPeer, SliderOptions, SliderAttribute, CrownSensitivity, SizeOptions,
    SlideRange, SliderBlockStyle, SliderChangeMode, SliderInteraction, Length, Dimension, SliderConfiguration,
    ResourceColor, ResourceStr
} from "../framework";
import { LinearGradient } from "../component/dataPanel";
import { ContentModifier } from "#handwritten";
import { ArkSliderComponent, SliderShowStepOptions, SliderPrefixOptions, SliderSuffixOptions } from '#generated';
import { ContentModifier, hookSliderSetPrefixMethod, hookSliderSetSuffixMethod} from '#handwritten';
import { ComponentContent } from 'arkui.ComponentContent';

export class ArkSliderNode extends ArkBaseNode implements SliderAttribute {
    constructParam(...param: Object[]): this {
        if (param.length > 1) {
            throw new Error('more than 1 parameters');
        }
        let options_casted: SliderOptions | undefined;
        if (param.length === 1) {
            options_casted = param[0] as (SliderOptions | undefined);
        }
        this.getPeer()?.setSliderOptionsAttribute(options_casted);
        this.markDirty();
        return this;
    }
    getPeer(): ArkSliderPeer {
        return this.peer as ArkSliderPeer
    }
    initialize(options?: SliderOptions): this {
        const options_casted = options as (SliderOptions | undefined)
        this.getPeer()?.setSliderOptionsAttribute(options_casted)
        this.markDirty();
        return this;
    }
    blockColor(value: ResourceColor | LinearGradient | undefined): this {
        const value_casted = value as (ResourceColor | LinearGradient | undefined);
        this.getPeer()?.setBlockColorAttribute(value_casted);
        this.markDirty();
        return this;
    }
    trackColor(value: ResourceColor | LinearGradient | undefined): this {
        const value_casted = value as (ResourceColor | LinearGradient | undefined);
        this.getPeer()?.setTrackColorAttribute(value_casted);
        this.markDirty();
        return this;
    }
    selectedColor(value: ResourceColor | LinearGradient | undefined): this {
        const value_casted = value as (ResourceColor | LinearGradient | undefined);
        this.getPeer()?.setSelectedColorAttribute(value_casted);
        this.markDirty();
        return this;
    }
    showSteps(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined);
        this.getPeer()?.setShowSteps0Attribute(value_casted);
        this.markDirty();
        return this;
    }
    showSteps(value: boolean, options: SliderShowStepOptions | undefined): this {
        const value_casted = value as (boolean | undefined);
        const options_casted = options as (SliderShowStepOptions | undefined);
        this.getPeer()?.setShowSteps1Attribute(value_casted, options_casted);
        this.markDirty();
        return this;
    }
    prefix(content: ComponentContent | undefined, options?: SliderPrefixOptions| undefined): this {
        hookSliderSetPrefixMethod(this.getPeer(), content, options);
        this.markDirty();
        return this;
    }
    suffix(content: ComponentContent | undefined, options?: SliderSuffixOptions| undefined): this {
        hookSliderSetSuffixMethod(this.getPeer(), content, options);
         this.markDirty();
         return this;
     }
    trackThickness(value: Length | undefined): this {
        const value_casted = value as (Length | undefined);
        this.getPeer()?.setTrackThicknessAttribute(value_casted);
        this.markDirty();
        return this;
    }
    onChange(value: ((value: double, mode: SliderChangeMode) => void) | undefined): this {
        const value_casted = value as (((value: double, mode: SliderChangeMode) => void) | undefined);
        this.getPeer()?.setOnChangeAttribute(value_casted);
        this.markDirty();
        return this;
    }
    blockBorderColor(value: ResourceColor | undefined): this {
        const value_casted = value as (ResourceColor | undefined);
        this.getPeer()?.setBlockBorderColorAttribute(value_casted);
        this.markDirty();
        return this;
    }
    blockBorderWidth(value: Length | undefined): this {
        const value_casted = value as (Length | undefined);
        this.getPeer()?.setBlockBorderWidthAttribute(value_casted);
        this.markDirty();
        return this;
    }
    stepColor(value: ResourceColor | undefined): this {
        const value_casted = value as (ResourceColor | undefined);
        this.getPeer()?.setStepColorAttribute(value_casted);
        this.markDirty();
        return this;
    }
    trackBorderRadius(value: Length | undefined): this {
        const value_casted = value as (Length | undefined);
        this.getPeer()?.setTrackBorderRadiusAttribute(value_casted);
        this.markDirty();
        return this;
    }
    selectedBorderRadius(value: Dimension | undefined): this {
        const value_casted = value as (Dimension | undefined);
        this.getPeer()?.setSelectedBorderRadiusAttribute(value_casted);
        this.markDirty();
        return this;
    }
    blockSize(value: SizeOptions | undefined): this {
        const value_casted = value as (SizeOptions | undefined);
        this.getPeer()?.setBlockSizeAttribute(value_casted);
        this.markDirty();
        return this;
    }
    blockStyle(value: SliderBlockStyle | undefined): this {
        const value_casted = value as (SliderBlockStyle | undefined);
        this.getPeer()?.setBlockStyleAttribute(value_casted);
        this.markDirty();
        return this;
    }
    stepSize(value: Length | undefined): this {
        const value_casted = value as (Length | undefined);
        this.getPeer()?.setStepSizeAttribute(value_casted);
        this.markDirty();
        return this;
    }
    sliderInteractionMode(value: SliderInteraction | undefined): this {
        const value_casted = value as (SliderInteraction | undefined);
        this.getPeer()?.setSliderInteractionModeAttribute(value_casted);
        this.markDirty();
        return this;
    }
    minResponsiveDistance(value: double | undefined): this {
        const value_casted = value as (double | undefined);
        this.getPeer()?.setMinResponsiveDistanceAttribute(value_casted);
        this.markDirty();
        return this;
    }
    contentModifier(value: ContentModifier<SliderConfiguration> | undefined): this {
        const value_casted = value as (ContentModifier<SliderConfiguration> | undefined);
        this.markDirty();
        return this;
    }
    slideRange(value: SlideRange | undefined): this {
        const value_casted = value as (SlideRange | undefined);
        this.getPeer()?.setSlideRangeAttribute(value_casted);
        this.markDirty();
        return this;
    }
    digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        const value_casted = value as (CrownSensitivity | undefined);
        this.getPeer()?.setDigitalCrownSensitivityAttribute(value_casted);
        this.markDirty();
        return this;
    }
    enableHapticFeedback(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined);
        this.getPeer()?.setEnableHapticFeedbackAttribute(value_casted);
        this.markDirty();
        return this;
    }
    showTips(value: boolean | undefined, content?: ResourceStr | undefined): this {
        const value_casted = value as (boolean | undefined);
        const content_casted = content as (ResourceStr | undefined);
        this.getPeer()?.setShowTipsAttribute(value_casted, content_casted);
        this.markDirty();
        return this;
    }
}
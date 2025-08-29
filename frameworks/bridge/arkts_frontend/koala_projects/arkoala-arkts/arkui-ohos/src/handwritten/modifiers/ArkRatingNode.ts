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
import { ArkRatingPeer, RatingOptions, RatingAttribute, OnRatingChangeCallback, StarStyleOptions, RatingConfiguration } from "../../component";
import { ContentModifier } from "@component_handwritten/common";
export class ArkRatingNode extends ArkBaseNode implements RatingAttribute {
    constructParam(...param: Object[]): this {
        if (param.length > 1) {
            throw new Error('more than 1 parameters');
        } 
        let options_casted: RatingOptions | undefined;
        if (param.length === 1) {
            options_casted = param[0] as (RatingOptions | undefined);
        }
        this.getPeer()?.setRatingOptionsAttribute(options_casted);
        return this;
    }
    getPeer(): ArkRatingPeer {
        return this.peer as ArkRatingPeer;
    }
    initialize(options?: RatingOptions | Object): this {
        const options_casted = options as (RatingOptions | undefined);
        this.getPeer()?.setRatingOptionsAttribute(options_casted);
        return this;
    }
    setRatingOptions(options?: RatingOptions): this {
        const options_casted = options as (RatingOptions | undefined);
        this.getPeer()?.setRatingOptionsAttribute(options_casted);
        return this;
    }
    stars(value: number | undefined): this {
        const value_casted = value as (number | undefined);
        this.getPeer()?.stars0Attribute(value_casted);
        return this;
    }
    stepSize(value: number | undefined): this {
        const value_casted = value as (number | undefined);
        this.getPeer()?.stepSize0Attribute(value_casted);        
        return this;
    }
    starStyle(value: StarStyleOptions | undefined): this {
        const value_casted = value as (StarStyleOptions | undefined);
        this.getPeer()?.starStyle0Attribute(value_casted);            
        return this;
    }
    onChange(value: ((index: number) => void) | OnRatingChangeCallback | undefined): this {
        const value_casted = value as (((index: number) => void) | OnRatingChangeCallback | undefined);
        this.getPeer()?.onChange0Attribute(value_casted);          
        return this;
    }
    contentModifier(value: ContentModifier<RatingConfiguration> | undefined): this {
        const value_casted = value as (ContentModifier<RatingConfiguration> | undefined);
        this.getPeer()?.contentModifier0Attribute(value_casted);
        return this;
    }
    _onChangeEvent_rating(callback: (index: number) => void): void {
        const callback_casted = callback as (((index: number) => void))
        this.getPeer()?._onChangeEvent_ratingAttribute(callback_casted)
        return;
    }
}
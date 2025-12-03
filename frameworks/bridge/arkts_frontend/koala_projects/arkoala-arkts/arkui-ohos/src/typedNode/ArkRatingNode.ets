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
import { ArkRatingPeer, RatingOptions, RatingAttribute, OnRatingChangeCallback, StarStyleOptions,
    RatingConfiguration } from "../framework";
import { ContentModifier } from "#handwritten";
import { hookRatingContentModifier } from "../hooks/content_modifiers/ContentModifierHooks";
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
        this.markDirty();
        return this;
    }
    getPeer(): ArkRatingPeer {
        return this.peer as ArkRatingPeer;
    }
    initialize(options?: RatingOptions | Object): this {
        const options_casted = options as (RatingOptions | undefined);
        this.getPeer()?.setRatingOptionsAttribute(options_casted);
        this.markDirty();
        return this;
    }
    stars(value: int | undefined): this {
        const value_casted = value as (int | undefined);
        this.getPeer()?.setStarsAttribute(value_casted);
        this.markDirty();
        return this;
    }
    stepSize(value: double | undefined): this {
        const value_casted = value as (double | undefined);
        this.getPeer()?.setStepSizeAttribute(value_casted);        
        this.markDirty();
        return this;
    }
    starStyle(value: StarStyleOptions | undefined): this {
        const value_casted = value as (StarStyleOptions | undefined);
        this.getPeer()?.setStarStyleAttribute(value_casted);            
        this.markDirty();
        return this;
    }
    onChange(value: ((index: double) => void) | OnRatingChangeCallback | undefined): this {
        const value_casted = value as (((index: double) => void) | OnRatingChangeCallback | undefined);
        this.getPeer()?.setOnChangeAttribute(value_casted);          
        this.markDirty();
        return this;
    }
    contentModifier(value: ContentModifier<RatingConfiguration> | undefined): this {
        const value_casted = value as (ContentModifier<RatingConfiguration> | undefined);
        hookRatingContentModifier(this.getPeer(), value_casted);
        this.markDirty();
        return this;
    }
}
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
import { AttributeModifier, ContentModifier, hookRatingContentModifier } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkRatingPeer, StarStyleOptions, OnRatingChangeCallback, RatingConfiguration, RatingAttribute } from "./component/rating"
import { int32 } from "@koalaui/common"
import { CommonMethod } from "./component/common"
export class RatingModifier extends CommonMethodModifier implements RatingAttribute,AttributeModifier<RatingAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: RatingAttribute): void { }
    applyPressedAttribute(instance: RatingAttribute): void { }
    applyFocusedAttribute(instance: RatingAttribute): void { }
    applyDisabledAttribute(instance: RatingAttribute): void { }
    applySelectedAttribute(instance: RatingAttribute): void { }
    _stars_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _stars_0_0value?: int32 | undefined
    _stepSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _stepSize_0_0value?: double | undefined
    _starStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _starStyle_0_0value?: StarStyleOptions | undefined
    _onChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onChange_0_0value?: OnRatingChangeCallback | undefined
    _contentModifier_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _contentModifier_0_0value?: ContentModifier<RatingConfiguration> | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkRatingPeer;
        if (this._stars_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._stars_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStarsAttribute((this._stars_0_0value as int32 | undefined));
                    this._stars_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._stars_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._stars_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStarsAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (this._stepSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._stepSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStepSizeAttribute((this._stepSize_0_0value as double | undefined));
                    this._stepSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._stepSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._stepSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStepSizeAttribute((undefined as double | undefined));
                }
            }
        }
        if (this._starStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._starStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStarStyleAttribute((this._starStyle_0_0value as StarStyleOptions | undefined));
                    this._starStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._starStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._starStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStarStyleAttribute((undefined as StarStyleOptions | undefined));
                }
            }
        }
        if (this._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as OnRatingChangeCallback | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnChangeAttribute((undefined as OnRatingChangeCallback | undefined));
                }
            }
        }
        if (this._contentModifier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._contentModifier_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    hookRatingContentModifier(peer, (this._contentModifier_0_0value as ContentModifier<RatingConfiguration> | undefined));
                    this._contentModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._contentModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._contentModifier_0_flag = AttributeUpdaterFlag.INITIAL;
                    hookRatingContentModifier(peer, (undefined as ContentModifier<RatingConfiguration> | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: RatingModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._stars_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._stars_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.stars(modifier._stars_0_0value);
                    break;
                }
                default: {
                    this.stars((undefined as int32 | undefined));
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
                    this.stepSize((undefined as double | undefined));
                }
            }
        }
        if (modifier._starStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._starStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.starStyle(modifier._starStyle_0_0value);
                    break;
                }
                default: {
                    this.starStyle((undefined as StarStyleOptions | undefined));
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
                    this.onChange((undefined as OnRatingChangeCallback | undefined));
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
                    this.contentModifier((undefined as ContentModifier<RatingConfiguration> | undefined));
                }
            }
        }
    }
    stars(value: int32 | undefined): this {
        if (((this._stars_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._stars_0_0value) !== (value)))
        {
            this._stars_0_flag = AttributeUpdaterFlag.UPDATE
            this._stars_0_0value = value
            this._state.fireChange()
        } else
        {
            this._stars_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    stepSize(value: double | undefined): this {
        if (((this._stepSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._stepSize_0_0value) !== (value)))
        {
            this._stepSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._stepSize_0_0value = value
            this._state.fireChange()
        } else
        {
            this._stepSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    starStyle(value: StarStyleOptions | undefined): this {
        if (((this._starStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._starStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._starStyle_0_0value = value
            this._state.fireChange()
        } else
        {
            this._starStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onChange(value: OnRatingChangeCallback | undefined): this {
        if (((this._onChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onChange_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    contentModifier(value: ContentModifier<RatingConfiguration> | undefined): this {
        if (((this._contentModifier_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._contentModifier_0_0value) !== (value)))
        {
            this._contentModifier_0_flag = AttributeUpdaterFlag.UPDATE
            this._contentModifier_0_0value = value
        } else
        {
            this._contentModifier_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RatingAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

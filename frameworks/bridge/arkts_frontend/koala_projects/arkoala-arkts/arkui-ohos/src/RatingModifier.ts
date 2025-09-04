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

import { AttributeModifier, ResourceColor } from './component';
import { ContentModifier } from './component/common';
import { OnRatingChangeCallback, StarStyleOptions, RatingConfiguration, RatingAttribute, ArkRatingPeer, ArkRatingComponent } from './component/rating'
import { CommonMethodModifier, AttributeUpdaterFlag } from './CommonMethodModifier';
import { hookRatingContentModifier } from './handwritten';
import { PeerNode } from './PeerNode';

export class RatingModifier extends CommonMethodModifier implements RatingAttribute, AttributeModifier<RatingAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyNormalAttribute(instance: RatingAttribute): void {}
    applyPressedAttribute(instance: RatingAttribute): void {}
    applyFocusedAttribute(instance: RatingAttribute): void {}
    applyDisabledAttribute(instance: RatingAttribute): void {}
    applySelectedAttribute(instance: RatingAttribute): void {}
    _stars_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _stars_0_0value?: number | undefined
    _stepSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _stepSize_0_0value?: number | undefined
    _starStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _starStyle_0_0value?: StarStyleOptions | undefined
    _onChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onChange_0_0value?: OnRatingChangeCallback | undefined
    _contentModifier_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _contentModifier_0_0value?: ContentModifier<RatingConfiguration> | undefined
    applyModifierPatch(value: PeerNode): void {
        super.applyModifierPatch(value)
        const peer = value as ArkRatingPeer
        if (this._stars_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._stars_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.stars0Attribute((this._stars_0_0value as number | undefined));
                    this._stars_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._stars_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._stars_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.stars0Attribute((undefined as number | undefined));
                }
            }
        }
        if (this._stepSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._stepSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.stepSize0Attribute((this._stepSize_0_0value as number | undefined));
                    this._stepSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._stepSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._stepSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.stepSize0Attribute((undefined as number | undefined));
                }
            }
        }
        if (this._starStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._starStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.starStyle0Attribute((this._starStyle_0_0value as StarStyleOptions | undefined));
                    this._starStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._starStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._starStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.starStyle0Attribute((undefined as StarStyleOptions | undefined));
                }
            }
        }
        if (this._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onChange1Attribute((this._onChange_0_0value as OnRatingChangeCallback | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onChange1Attribute((undefined as OnRatingChangeCallback | undefined));
                }
            }
        }
        if (this._contentModifier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._contentModifier_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    const arkRatingComponent: ArkRatingComponent = new ArkRatingComponent();
                    arkRatingComponent.setPeer(peer);
                    hookRatingContentModifier(arkRatingComponent, (this._contentModifier_0_0value as ContentModifier<RatingConfiguration> | undefined));
                    this._contentModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._contentModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._contentModifier_0_flag = AttributeUpdaterFlag.INITIAL;
                    const arkRatingComponent: ArkRatingComponent = new ArkRatingComponent();
                    arkRatingComponent.setPeer(peer);
                    hookRatingContentModifier(arkRatingComponent, (this._contentModifier_0_0value as ContentModifier<RatingConfiguration> | undefined));
                }
            }
        }
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
        if (!(value instanceof RatingModifier)) {
            return
        }
        const modifier = value as RatingModifier;
        if (modifier._stars_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._stars_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.stars(modifier._stars_0_0value);
                    break;
                }
                default: {
                    this.stars((undefined as number | undefined));
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
                    this.stepSize((undefined as number | undefined));
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

    stars(value: number | undefined): this {
        if (((this._stars_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._stars_0_flag = AttributeUpdaterFlag.UPDATE
            this._stars_0_0value = value
        } else
        {
            this._stars_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    stepSize(value: number | undefined): this {
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
    starStyle(value: StarStyleOptions | undefined): this {
        if (((this._starStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._starStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._starStyle_0_0value = value
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
        } else
        {
            this._onChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    contentModifier(value: ContentModifier<RatingConfiguration> | undefined): this {
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
}
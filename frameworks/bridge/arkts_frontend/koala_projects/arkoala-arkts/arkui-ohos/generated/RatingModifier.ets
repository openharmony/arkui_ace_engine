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
import { AttributeModifier, ContentModifier, hookRatingContentModifier } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkRatingPeer, StarStyleOptions, OnRatingChangeCallback, RatingConfiguration, RatingAttribute } from './component/rating'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod } from './component/common'
export class RatingModifier extends CommonMethodModifier implements RatingAttribute,AttributeModifier<RatingAttribute> {
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
    applyNormalAttribute(instance: RatingAttribute): void { }
    applyPressedAttribute(instance: RatingAttribute): void { }
    applyFocusedAttribute(instance: RatingAttribute): void { }
    applyDisabledAttribute(instance: RatingAttribute): void { }
    applySelectedAttribute(instance: RatingAttribute): void { }
    public _stars_0_0value?: int32 | undefined
    public _stepSize_0_0value?: double | undefined
    public _starStyle_0_0value?: StarStyleOptions | undefined
    public _onChange_0_0value?: OnRatingChangeCallback | undefined
    public _contentModifier_0_0value?: ContentModifier<RatingConfiguration> | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkRatingPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkRatingPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setStarsAttribute((this._stars_0_0value as int32 | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setStarsAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setStepSizeAttribute((this._stepSize_0_0value as double | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setStepSizeAttribute((undefined as double | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setStarStyleAttribute((this._starStyle_0_0value as StarStyleOptions | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setStarStyleAttribute((undefined as StarStyleOptions | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as OnRatingChangeCallback | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setOnChangeAttribute((undefined as OnRatingChangeCallback | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    hookRatingContentModifier(peer, (this._contentModifier_0_0value as ContentModifier<RatingConfiguration> | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    hookRatingContentModifier(peer, (undefined as ContentModifier<RatingConfiguration> | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: RatingModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: RatingModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.stars(modifier._stars_0_0value);
                    break;
                }
                default: {
                    this.stars((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.stepSize(modifier._stepSize_0_0value);
                    break;
                }
                default: {
                    this.stepSize((undefined as double | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.starStyle(modifier._starStyle_0_0value);
                    break;
                }
                default: {
                    this.starStyle((undefined as StarStyleOptions | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.onChange(modifier._onChange_0_0value);
                    break;
                }
                default: {
                    this.onChange((undefined as OnRatingChangeCallback | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
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
        if (((this._flagArray[0]) == (0)) || ((this._stars_0_0value) !== (value))) {
            this._flagArray[0] = 1
            this._stars_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    stepSize(value: double | undefined): this {
        if (((this._flagArray[1]) == (0)) || ((this._stepSize_0_0value) !== (value))) {
            this._flagArray[1] = 1
            this._stepSize_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    starStyle(value: StarStyleOptions | undefined): this {
        if (((this._flagArray[2]) == (0)) || (true)) {
            this._flagArray[2] = 1
            this._starStyle_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    onChange(value: OnRatingChangeCallback | undefined): this {
        if (((this._flagArray[3]) == (0)) || (true)) {
            this._flagArray[3] = 1
            this._onChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    contentModifier(value: ContentModifier<RatingConfiguration> | undefined): this {
        if (((this._flagArray[4]) == (0)) || (true)) {
            this._flagArray[4] = 1
            this._contentModifier_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RatingAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

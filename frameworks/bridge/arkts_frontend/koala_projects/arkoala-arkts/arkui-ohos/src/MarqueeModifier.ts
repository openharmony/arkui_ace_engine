/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { int32 } from '@koalaui/common';
import { KPointer, RuntimeType, runtimeType } from '@koalaui/interop';
import { AttributeUpdaterFlag, CommonMethodModifier } from './CommonMethodModifier';

import { AttributeModifier, CommonMethod } from './component/common'
import { ResourceColor, Length } from './component/units'
import { Color, FontWeight, MarqueeUpdateStrategy } from './component/enums'
import { Resource } from 'global.resource'
import { MarqueeAttribute, MarqueeOptions, ArkMarqueePeer } from './component/marquee'
import { PeerNode } from './PeerNode';


export class MarqueeModifier extends CommonMethodModifier implements MarqueeAttribute, AttributeModifier<MarqueeAttribute> {

    applyNormalAttribute(instance: MarqueeAttribute): void { }
    applyPressedAttribute(instance: MarqueeAttribute): void { }
    applyFocusedAttribute(instance: MarqueeAttribute): void { }
    applyDisabledAttribute(instance: MarqueeAttribute): void { }
    applySelectedAttribute(instance: MarqueeAttribute): void { }

    _setMarqueeOptions_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _setMarqueeOptions_0_0value?: MarqueeOptions | undefined
    _fontColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontColor_0_0value?: ResourceColor | undefined
    _fontSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontSize_0_0value?: Length | undefined
    _allowScale_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _allowScale_0_0value?: boolean | undefined
    _fontWeight_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontWeight_0_0value?: number | FontWeight | string | undefined
    _fontFamily_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontFamily_0_0value?: string | Resource | undefined
    _marqueeUpdateStrategy_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _marqueeUpdateStrategy_0_0value?: MarqueeUpdateStrategy | undefined
    _onStart_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onStart_0_0value?: (() => void) | undefined
    _onBounce_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onBounce_0_0value?: (() => void) | undefined
    _onFinish_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onFinish_0_0value?: (() => void) | undefined

    public setMarqueeOptions(value: MarqueeOptions | undefined): this {
        if (((this._setMarqueeOptions_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            this._setMarqueeOptions_0_0value !== value)
        {
            this._setMarqueeOptions_0_flag = AttributeUpdaterFlag.UPDATE
            this._setMarqueeOptions_0_0value = value
        } else
        {
            this._setMarqueeOptions_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public fontColor(value: ResourceColor | undefined): this {
        if (((this._fontColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            this._fontColor_0_0value !== value || !Type.of(value).isPrimitive())
        {
            this._fontColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontColor_0_0value = value
        } else
        {
            this._fontColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public fontSize(value: Length | undefined): this {
        if (((this._fontSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            this._fontSize_0_0value !== value || !Type.of(value).isPrimitive())
        {
            this._fontSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontSize_0_0value = value
        } else
        {
            this._fontSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public allowScale(value: boolean | undefined): this {
        if (((this._allowScale_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._allowScale_0_0value) !== (value)))
        {
            this._allowScale_0_flag = AttributeUpdaterFlag.UPDATE
            this._allowScale_0_0value = value
        } else
        {
            this._allowScale_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public fontWeight(value: number | FontWeight | string | undefined): this {
        if (((this._fontWeight_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            this._fontWeight_0_0value !== value)
        {
            this._fontWeight_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontWeight_0_0value = value
        } else
        {
            this._fontWeight_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public fontFamily(value: string | Resource | undefined): this {
        if (((this._fontFamily_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            this._fontFamily_0_0value !== value || !Type.of(value).isPrimitive())
        {
            this._fontFamily_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontFamily_0_0value = value
        } else
        {
            this._fontFamily_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public marqueeUpdateStrategy(value: MarqueeUpdateStrategy | undefined): this {
        if (((this._marqueeUpdateStrategy_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            this._marqueeUpdateStrategy_0_0value !== value)
        {
            this._marqueeUpdateStrategy_0_flag = AttributeUpdaterFlag.UPDATE
            this._marqueeUpdateStrategy_0_0value = value
        } else
        {
            this._marqueeUpdateStrategy_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public onStart(value: (() => void) | undefined): this {
        if (((this._onStart_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            this._onStart_0_0value !== value)
        {
            this._onStart_0_flag = AttributeUpdaterFlag.UPDATE
            this._onStart_0_0value = value
        } else
        {
            this._onStart_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public onBounce(value: (() => void) | undefined): this {
        if (((this._onBounce_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            this._onBounce_0_0value !== value)
        {
            this._onBounce_0_flag = AttributeUpdaterFlag.UPDATE
            this._onBounce_0_0value = value
        } else
        {
            this._onBounce_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    public onFinish(value: (() => void) | undefined): this {
        if (((this._onFinish_0_flag) == (AttributeUpdaterFlag.INITIAL)) ||
            this._onFinish_0_0value !== value)
        {
            this._onFinish_0_flag = AttributeUpdaterFlag.UPDATE
            this._onFinish_0_0value = value
        } else
        {
            this._onFinish_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }

    applyModifierPatch(peerNode: PeerNode): void {
        super.applyModifierPatch(peerNode)
        const peer: ArkMarqueePeer = peerNode as ArkMarqueePeer
        if (this._setMarqueeOptions_0_flag !== AttributeUpdaterFlag.INITIAL) {
            switch (this._setMarqueeOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    if (this._setMarqueeOptions_0_0value !== undefined) {
                        peer.setMarqueeOptionsAttribute((this._setMarqueeOptions_0_0value! as MarqueeOptions))
                    }
                    this._setMarqueeOptions_0_flag = AttributeUpdaterFlag.RESET
                    break
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._setMarqueeOptions_0_flag = AttributeUpdaterFlag.RESET
                    break
                }
                default: {
                    this._setMarqueeOptions_0_flag = AttributeUpdaterFlag.INITIAL
                    // peer.setMarqueeOptionsAttribute(undefined)
                }
            }
        }
        if (this._fontColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.fontColorAttribute((this._fontColor_0_0value as ResourceColor | undefined));
                    this._fontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.fontColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._fontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.fontSizeAttribute((this._fontSize_0_0value as Length | undefined));
                    this._fontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.fontSizeAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._allowScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._allowScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.allowScaleAttribute((this._allowScale_0_0value as boolean | undefined));
                    this._allowScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._allowScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._allowScale_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.allowScaleAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._fontWeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontWeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.fontWeightAttribute((this._fontWeight_0_0value as number | FontWeight | string | undefined));
                    this._fontWeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontWeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontWeight_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.fontWeightAttribute((undefined as number | FontWeight | string | undefined));
                }
            }
        }
        if (this._fontFamily_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontFamily_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.fontFamilyAttribute((this._fontFamily_0_0value as string | Resource | undefined));
                    this._fontFamily_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontFamily_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontFamily_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.fontFamilyAttribute((undefined as string | Resource | undefined));
                }
            }
        }
        if (this._marqueeUpdateStrategy_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._marqueeUpdateStrategy_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.marqueeUpdateStrategyAttribute((this._marqueeUpdateStrategy_0_0value as MarqueeUpdateStrategy | undefined));
                    this._marqueeUpdateStrategy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._marqueeUpdateStrategy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._marqueeUpdateStrategy_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.marqueeUpdateStrategyAttribute((undefined as MarqueeUpdateStrategy | undefined));
                }
            }
        }
        if (this._onStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onStartAttribute((this._onStart_0_0value as (() => void) | undefined));
                    this._onStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onStart_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onStartAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onBounce_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onBounce_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onBounceAttribute((this._onBounce_0_0value as (() => void) | undefined));
                    this._onBounce_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onBounce_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onBounce_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onBounceAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onFinish_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onFinish_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onFinishAttribute((this._onFinish_0_0value as (() => void) | undefined));
                    this._onFinish_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onFinish_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onFinish_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onFinishAttribute((undefined as (() => void) | undefined));
                }
            }
        }
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
        if (!(value instanceof MarqueeModifier)) {
            return
        }
        const modifier = value as MarqueeModifier
        if (modifier._setMarqueeOptions_0_flag !== AttributeUpdaterFlag.INITIAL) {
            switch (modifier._setMarqueeOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.setMarqueeOptions(modifier._setMarqueeOptions_0_0value)
                    break
                }
                default: {
                    this.setMarqueeOptions(undefined)
                }
            }
        }
        if (modifier._fontColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontColor(modifier._fontColor_0_0value);
                    break;
                }
                default: {
                    this.fontColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._fontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontSize(modifier._fontSize_0_0value);
                    break;
                }
                default: {
                    this.fontSize((undefined as Length | undefined));
                }
            }
        }
        if (modifier._allowScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._allowScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.allowScale(modifier._allowScale_0_0value);
                    break;
                }
                default: {
                    this.allowScale((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._fontWeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontWeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontWeight(modifier._fontWeight_0_0value);
                    break;
                }
                default: {
                    this.fontWeight((undefined as number | FontWeight | string | undefined));
                }
            }
        }
        if (modifier._fontFamily_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontFamily_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontFamily(modifier._fontFamily_0_0value);
                    break;
                }
                default: {
                    this.fontFamily((undefined as string | Resource | undefined));
                }
            }
        }
        if (modifier._marqueeUpdateStrategy_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._marqueeUpdateStrategy_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.marqueeUpdateStrategy(modifier._marqueeUpdateStrategy_0_0value);
                    break;
                }
                default: {
                    this.marqueeUpdateStrategy((undefined as MarqueeUpdateStrategy | undefined));
                }
            }
        }
        if (modifier._onStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onStart(modifier._onStart_0_0value);
                    break;
                }
                default: {
                    this.onStart((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onBounce_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onBounce_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onBounce(modifier._onBounce_0_0value);
                    break;
                }
                default: {
                    this.onBounce((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onFinish_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onFinish_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onFinish(modifier._onFinish_0_0value);
                    break;
                }
                default: {
                    this.onFinish((undefined as (() => void) | undefined));
                }
            }
        }
    }
}
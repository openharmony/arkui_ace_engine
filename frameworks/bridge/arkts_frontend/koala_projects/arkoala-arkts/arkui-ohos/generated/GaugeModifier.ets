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
import { AttributeModifier, ContentModifier, hookGaugeContentModifier } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkGaugePeer, GaugeShadowOptions, GaugeIndicatorOptions, GaugeConfiguration, GaugeAttribute } from "./component/gauge"
import { int32 } from "@koalaui/common"
import { CommonMethod } from "./component/common"
import { ResourceColor, Length } from "./component/units"
import { Color } from "./component/enums"
import { Resource } from "global.resource"
import { LinearGradient } from "./component/dataPanel"
import { CustomBuilder } from "./component/builder"
export class GaugeModifier extends CommonMethodModifier implements GaugeAttribute,AttributeModifier<GaugeAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: GaugeAttribute): void { }
    applyPressedAttribute(instance: GaugeAttribute): void { }
    applyFocusedAttribute(instance: GaugeAttribute): void { }
    applyDisabledAttribute(instance: GaugeAttribute): void { }
    applySelectedAttribute(instance: GaugeAttribute): void { }
    _value_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _value_0_0value?: double | undefined
    _startAngle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _startAngle_0_0value?: double | undefined
    _endAngle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _endAngle_0_0value?: double | undefined
    _colors_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _colors_0_0value?: ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, double ]> | undefined
    _strokeWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _strokeWidth_0_0value?: Length | undefined
    _description_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _description_0_0value?: CustomBuilder | null | undefined
    _trackShadow_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _trackShadow_0_0value?: GaugeShadowOptions | null | undefined
    _indicator_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _indicator_0_0value?: GaugeIndicatorOptions | null | undefined
    _privacySensitive_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _privacySensitive_0_0value?: boolean | undefined
    _contentModifier_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _contentModifier_0_0value?: ContentModifier<GaugeConfiguration> | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkGaugePeer;
        if (this._value_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._value_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setValueAttribute((this._value_0_0value as double | undefined));
                    this._value_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._value_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._value_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setValueAttribute((undefined as double | undefined));
                }
            }
        }
        if (this._startAngle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._startAngle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStartAngleAttribute((this._startAngle_0_0value as double | undefined));
                    this._startAngle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._startAngle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._startAngle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStartAngleAttribute((undefined as double | undefined));
                }
            }
        }
        if (this._endAngle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._endAngle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEndAngleAttribute((this._endAngle_0_0value as double | undefined));
                    this._endAngle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._endAngle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._endAngle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEndAngleAttribute((undefined as double | undefined));
                }
            }
        }
        if (this._colors_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._colors_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setColorsAttribute((this._colors_0_0value as ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, double ]> | undefined));
                    this._colors_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._colors_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._colors_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setColorsAttribute((undefined as ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, double ]> | undefined));
                }
            }
        }
        if (this._strokeWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._strokeWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStrokeWidthAttribute((this._strokeWidth_0_0value as Length | undefined));
                    this._strokeWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._strokeWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._strokeWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStrokeWidthAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._description_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._description_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDescriptionAttribute((this._description_0_0value as CustomBuilder | null | undefined));
                    this._description_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._description_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._description_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDescriptionAttribute((undefined as CustomBuilder | null | undefined));
                }
            }
        }
        if (this._trackShadow_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._trackShadow_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTrackShadowAttribute((this._trackShadow_0_0value as GaugeShadowOptions | null | undefined));
                    this._trackShadow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._trackShadow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._trackShadow_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTrackShadowAttribute((undefined as GaugeShadowOptions | null | undefined));
                }
            }
        }
        if (this._indicator_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._indicator_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setIndicatorAttribute((this._indicator_0_0value as GaugeIndicatorOptions | null | undefined));
                    this._indicator_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._indicator_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._indicator_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setIndicatorAttribute((undefined as GaugeIndicatorOptions | null | undefined));
                }
            }
        }
        if (this._privacySensitive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._privacySensitive_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPrivacySensitiveAttribute((this._privacySensitive_0_0value as boolean | undefined));
                    this._privacySensitive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._privacySensitive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._privacySensitive_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPrivacySensitiveAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._contentModifier_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._contentModifier_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    hookGaugeContentModifier(peer, (this._contentModifier_0_0value as ContentModifier<GaugeConfiguration> | undefined));
                    this._contentModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._contentModifier_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._contentModifier_0_flag = AttributeUpdaterFlag.INITIAL;
                    hookGaugeContentModifier(peer, (undefined as ContentModifier<GaugeConfiguration> | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: GaugeModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._value_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._value_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.value(modifier._value_0_0value);
                    break;
                }
                default: {
                    this.value((undefined as double | undefined));
                }
            }
        }
        if (modifier._startAngle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._startAngle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.startAngle(modifier._startAngle_0_0value);
                    break;
                }
                default: {
                    this.startAngle((undefined as double | undefined));
                }
            }
        }
        if (modifier._endAngle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._endAngle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.endAngle(modifier._endAngle_0_0value);
                    break;
                }
                default: {
                    this.endAngle((undefined as double | undefined));
                }
            }
        }
        if (modifier._colors_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._colors_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.colors(modifier._colors_0_0value);
                    break;
                }
                default: {
                    this.colors((undefined as ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, double ]> | undefined));
                }
            }
        }
        if (modifier._strokeWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._strokeWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.strokeWidth(modifier._strokeWidth_0_0value);
                    break;
                }
                default: {
                    this.strokeWidth((undefined as Length | undefined));
                }
            }
        }
        if (modifier._description_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._description_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.description(modifier._description_0_0value);
                    break;
                }
                default: {
                    this.description((undefined as CustomBuilder | null | undefined));
                }
            }
        }
        if (modifier._trackShadow_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._trackShadow_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.trackShadow(modifier._trackShadow_0_0value);
                    break;
                }
                default: {
                    this.trackShadow((undefined as GaugeShadowOptions | null | undefined));
                }
            }
        }
        if (modifier._indicator_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._indicator_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.indicator(modifier._indicator_0_0value);
                    break;
                }
                default: {
                    this.indicator((undefined as GaugeIndicatorOptions | null | undefined));
                }
            }
        }
        if (modifier._privacySensitive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._privacySensitive_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.privacySensitive(modifier._privacySensitive_0_0value);
                    break;
                }
                default: {
                    this.privacySensitive((undefined as boolean | undefined));
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
                    this.contentModifier((undefined as ContentModifier<GaugeConfiguration> | undefined));
                }
            }
        }
    }
    value(value: double | undefined): this {
        if (((this._value_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._value_0_0value) !== (value)))
        {
            this._value_0_flag = AttributeUpdaterFlag.UPDATE
            this._value_0_0value = value
        } else
        {
            this._value_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    startAngle(value: double | undefined): this {
        if (((this._startAngle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._startAngle_0_0value) !== (value)))
        {
            this._startAngle_0_flag = AttributeUpdaterFlag.UPDATE
            this._startAngle_0_0value = value
        } else
        {
            this._startAngle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    endAngle(value: double | undefined): this {
        if (((this._endAngle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._endAngle_0_0value) !== (value)))
        {
            this._endAngle_0_flag = AttributeUpdaterFlag.UPDATE
            this._endAngle_0_0value = value
        } else
        {
            this._endAngle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    colors(value: ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, double ]> | undefined): this {
        if (((this._colors_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._colors_0_flag = AttributeUpdaterFlag.UPDATE
            this._colors_0_0value = value
        } else
        {
            this._colors_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    strokeWidth(value: Length | undefined): this {
        if (((this._strokeWidth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._strokeWidth_0_flag = AttributeUpdaterFlag.UPDATE
            this._strokeWidth_0_0value = value
        } else
        {
            this._strokeWidth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    description(value: CustomBuilder | null | undefined): this {
        if (((this._description_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._description_0_flag = AttributeUpdaterFlag.UPDATE
            this._description_0_0value = value
        } else
        {
            this._description_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    trackShadow(value: GaugeShadowOptions | null | undefined): this {
        if (((this._trackShadow_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._trackShadow_0_flag = AttributeUpdaterFlag.UPDATE
            this._trackShadow_0_0value = value
        } else
        {
            this._trackShadow_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    indicator(value: GaugeIndicatorOptions | null | undefined): this {
        if (((this._indicator_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._indicator_0_flag = AttributeUpdaterFlag.UPDATE
            this._indicator_0_0value = value
        } else
        {
            this._indicator_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    privacySensitive(value: boolean | undefined): this {
        if (((this._privacySensitive_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._privacySensitive_0_0value) !== (value)))
        {
            this._privacySensitive_0_flag = AttributeUpdaterFlag.UPDATE
            this._privacySensitive_0_0value = value
        } else
        {
            this._privacySensitive_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    contentModifier(value: ContentModifier<GaugeConfiguration> | undefined): this {
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
    public attributeModifier(value: AttributeModifier<GaugeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

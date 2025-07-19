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

import { AttributeModifier, CommonMethod, CommonShapeMethod, ArkCommonShapeMethodPeer } from 'arkui/component/common';
import { AttributeUpdaterFlag, CommonMethodModifier } from './CommonMethodModifier';
import { Length, ResourceColor } from 'arkui/component/units';
import { Resource } from 'global.resource';
import { LineCapStyle, LineJoinStyle } from 'arkui/component/enums';

export class CommonShapeMethodModifier extends CommonMethodModifier implements CommonShapeMethod, AttributeModifier<CommonShapeMethod> {
    applyNormalAttribute(instance: CommonShapeMethod): void { }
    applyPressedAttribute(instance: CommonShapeMethod): void { }
    applyFocusedAttribute(instance: CommonShapeMethod): void { }
    applyDisabledAttribute(instance: CommonShapeMethod): void { }
    applySelectedAttribute(instance: CommonShapeMethod): void { }
    _stroke_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _stroke0_value?: ResourceColor | undefined
    _fill_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fill0_value?: ResourceColor | undefined
    _strokeDashOffset_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _strokeDashOffset0_value?: number | string | undefined
    _strokeLineCap_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _strokeLineCap0_value?: LineCapStyle | undefined
    _strokeLineJoin_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _strokeLineJoin0_value?: LineJoinStyle | undefined
    _strokeMiterLimit_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _strokeMiterLimit0_value?: number | string | undefined
    _strokeOpacity_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _strokeOpacity0_value?: number | string | Resource | undefined
    _fillOpacity_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fillOpacity0_value?: number | string | Resource | undefined
    _strokeWidth_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _strokeWidth0_value?: Length | undefined
    _antiAlias_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _antiAlias0_value?: boolean | undefined
    _strokeDashArray_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _strokeDashArray0_value?: Array<Length> | undefined
    applyModifierPatch(peer: ArkCommonShapeMethodPeer): void {
        if (this._stroke_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._stroke_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.strokeAttribute((this._stroke0_value as ResourceColor | undefined));
                    this._stroke_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._stroke_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._stroke_flag = AttributeUpdaterFlag.INITIAL;
                    peer.strokeAttribute(undefined);
                }
            }
        }
        if (this._fill_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fill_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.fillAttribute((this._fill0_value as ResourceColor | undefined));
                    this._fill_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fill_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fill_flag = AttributeUpdaterFlag.INITIAL;
                    peer.fillAttribute(undefined);
                }
            }
        }
        if (this._strokeDashOffset_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._strokeDashOffset_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.strokeDashOffsetAttribute((this._strokeDashOffset0_value as number | string | undefined));
                    this._strokeDashOffset_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._strokeDashOffset_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._strokeDashOffset_flag = AttributeUpdaterFlag.INITIAL;
                    peer.strokeDashOffsetAttribute(undefined);
                }
            }
        }
        if (this._strokeLineCap_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._strokeLineCap_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.strokeLineCapAttribute((this._strokeLineCap0_value as LineCapStyle | undefined));
                    this._strokeLineCap_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._strokeLineCap_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._strokeLineCap_flag = AttributeUpdaterFlag.INITIAL;
                    peer.strokeLineCapAttribute(undefined);
                }
            }
        }
        if (this._strokeLineJoin_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._strokeLineJoin_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.strokeLineJoinAttribute((this._strokeLineJoin0_value as LineJoinStyle | undefined));
                    this._strokeLineJoin_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._strokeLineJoin_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._strokeLineJoin_flag = AttributeUpdaterFlag.INITIAL;
                    peer.strokeLineJoinAttribute(undefined);
                }
            }
        }
        if (this._strokeMiterLimit_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._strokeMiterLimit_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.strokeMiterLimitAttribute((this._strokeMiterLimit0_value as number | string | undefined));
                    this._strokeMiterLimit_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._strokeMiterLimit_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._strokeMiterLimit_flag = AttributeUpdaterFlag.INITIAL;
                    peer.strokeMiterLimitAttribute(undefined);
                }
            }
        }
        if (this._strokeOpacity_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._strokeOpacity_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.strokeOpacityAttribute((this._strokeOpacity0_value as number | string | Resource | undefined));
                    this._strokeOpacity_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._strokeOpacity_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._strokeOpacity_flag = AttributeUpdaterFlag.INITIAL;
                    peer.strokeOpacityAttribute(undefined);
                }
            }
        }
        if (this._fillOpacity_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fillOpacity_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.fillOpacityAttribute((this._fillOpacity0_value as number | string | Resource | undefined));
                    this._fillOpacity_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fillOpacity_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fillOpacity_flag = AttributeUpdaterFlag.INITIAL;
                    peer.fillOpacityAttribute(undefined);
                }
            }
        }
        if (this._strokeWidth_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._strokeWidth_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.strokeWidthAttribute((this._strokeWidth0_value as Length | undefined));
                    this._strokeWidth_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._strokeWidth_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._strokeWidth_flag = AttributeUpdaterFlag.INITIAL;
                    peer.strokeWidthAttribute(undefined);
                }
            }
        }
        if (this._antiAlias_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._antiAlias_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.antiAliasAttribute((this._antiAlias0_value as boolean | undefined));
                    this._antiAlias_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._antiAlias_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._antiAlias_flag = AttributeUpdaterFlag.INITIAL;
                    peer.antiAliasAttribute(undefined);
                }
            }
        }
        if (this._strokeDashArray_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._strokeDashArray_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.strokeDashArrayAttribute((this._strokeDashArray0_value as Array<Length> | undefined));
                    this._strokeDashArray_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._strokeDashArray_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._strokeDashArray_flag = AttributeUpdaterFlag.INITIAL;
                    peer.strokeDashArrayAttribute(undefined);
                }
            }
        }
    }
    mergeModifier(modifier: CommonShapeMethodModifier): void {
        if (modifier._stroke_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._stroke_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.stroke(modifier._stroke0_value);
                    break;
                }
                default: {
                    this.stroke(undefined);
                }
            }
        }
        if (modifier._fill_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fill_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fill(modifier._fill0_value);
                    break;
                }
                default: {
                    this.fill(undefined);
                }
            }
        }
        if (modifier._strokeDashOffset_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._strokeDashOffset_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.strokeDashOffset(modifier._strokeDashOffset0_value);
                    break;
                }
                default: {
                    this.strokeDashOffset(undefined);
                }
            }
        }
        if (modifier._strokeLineCap_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._strokeLineCap_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.strokeLineCap(modifier._strokeLineCap0_value);
                    break;
                }
                default: {
                    this.strokeLineCap(undefined);
                }
            }
        }
        if (modifier._strokeLineJoin_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._strokeLineJoin_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.strokeLineJoin(modifier._strokeLineJoin0_value);
                    break;
                }
                default: {
                    this.strokeLineJoin(undefined);
                }
            }
        }
        if (modifier._strokeMiterLimit_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._strokeMiterLimit_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.strokeMiterLimit(modifier._strokeMiterLimit0_value);
                    break;
                }
                default: {
                    this.strokeMiterLimit(undefined);
                }
            }
        }
        if (modifier._strokeOpacity_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._strokeOpacity_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.strokeOpacity(modifier._strokeOpacity0_value);
                    break;
                }
                default: {
                    this.strokeOpacity(undefined);
                }
            }
        }
        if (modifier._fillOpacity_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fillOpacity_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fillOpacity(modifier._fillOpacity0_value);
                    break;
                }
                default: {
                    this.fillOpacity(undefined);
                }
            }
        }
        if (modifier._strokeWidth_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._strokeWidth_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.strokeWidth(modifier._strokeWidth0_value);
                    break;
                }
                default: {
                    this.strokeWidth(undefined);
                }
            }
        }
        if (modifier._antiAlias_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._antiAlias_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.antiAlias(modifier._antiAlias0_value);
                    break;
                }
                default: {
                    this.antiAlias(undefined);
                }
            }
        }
        if (modifier._strokeDashArray_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._strokeDashArray_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.strokeDashArray(modifier._strokeDashArray0_value);
                    break;
                }
                default: {
                    this.strokeDashArray(undefined);
                }
            }
        }
    }
    stroke(value: ResourceColor | undefined): this {
        if (((this._stroke_flag) == (AttributeUpdaterFlag.INITIAL)) || (false))
        {
            this._stroke_flag = AttributeUpdaterFlag.UPDATE
            this._stroke0_value = value
        }
        else
        {
            this._stroke_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fill(value: ResourceColor | undefined): this {
        if (((this._fill_flag) == (AttributeUpdaterFlag.INITIAL)) || (false))
        {
            this._fill_flag = AttributeUpdaterFlag.UPDATE
            this._fill0_value = value
        }
        else
        {
            this._fill_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    strokeDashOffset(value: number | string | undefined): this {
        if (((this._strokeDashOffset_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._strokeDashOffset0_value) == (value)))
        {
            this._strokeDashOffset_flag = AttributeUpdaterFlag.UPDATE
            this._strokeDashOffset0_value = value
        }
        else
        {
            this._strokeDashOffset_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    strokeLineCap(value: LineCapStyle | undefined): this {
        if (((this._strokeLineCap_flag) == (AttributeUpdaterFlag.INITIAL)) || (false))
        {
            this._strokeLineCap_flag = AttributeUpdaterFlag.UPDATE
            this._strokeLineCap0_value = value
        }
        else
        {
            this._strokeLineCap_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    strokeLineJoin(value: LineJoinStyle | undefined): this {
        if (((this._strokeLineJoin_flag) == (AttributeUpdaterFlag.INITIAL)) || (false))
        {
            this._strokeLineJoin_flag = AttributeUpdaterFlag.UPDATE
            this._strokeLineJoin0_value = value
        }
        else
        {
            this._strokeLineJoin_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    strokeMiterLimit(value: number | string | undefined): this {
        if (((this._strokeMiterLimit_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._strokeMiterLimit0_value) == (value)))
        {
            this._strokeMiterLimit_flag = AttributeUpdaterFlag.UPDATE
            this._strokeMiterLimit0_value = value
        }
        else
        {
            this._strokeMiterLimit_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    strokeOpacity(value: number | string | Resource | undefined): this {
        if (((this._strokeOpacity_flag) == (AttributeUpdaterFlag.INITIAL)) || (false))
        {
            this._strokeOpacity_flag = AttributeUpdaterFlag.UPDATE
            this._strokeOpacity0_value = value
        }
        else
        {
            this._strokeOpacity_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fillOpacity(value: number | string | Resource | undefined): this {
        if (((this._fillOpacity_flag) == (AttributeUpdaterFlag.INITIAL)) || (false))
        {
            this._fillOpacity_flag = AttributeUpdaterFlag.UPDATE
            this._fillOpacity0_value = value
        }
        else
        {
            this._fillOpacity_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    strokeWidth(value: Length | undefined): this {
        if (((this._strokeWidth_flag) == (AttributeUpdaterFlag.INITIAL)) || (false))
        {
            this._strokeWidth_flag = AttributeUpdaterFlag.UPDATE
            this._strokeWidth0_value = value
        }
        else
        {
            this._strokeWidth_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    antiAlias(value: boolean | undefined): this {
        if (((this._antiAlias_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._antiAlias0_value) == (value)))
        {
            this._antiAlias_flag = AttributeUpdaterFlag.UPDATE
            this._antiAlias0_value = value
        }
        else
        {
            this._antiAlias_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    strokeDashArray(value: Array<Length> | undefined): this {
        if (((this._strokeDashArray_flag) == (AttributeUpdaterFlag.INITIAL)) || (false))
        {
            this._strokeDashArray_flag = AttributeUpdaterFlag.UPDATE
            this._strokeDashArray0_value = value
        }
        else
        {
            this._strokeDashArray_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
}

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
import { AttributeUpdateFlag, CommonMethodModifier } from './CommonMethodModifier';
import { ViewportRect, ShapeAttribute, ArkShapePeer } from 'arkui/component/shape';
import { Length, ResourceColor } from 'arkui/component/units';
import { Resource } from 'global.resource';
import { LineCapStyle, LineJoinStyle } from 'arkui/component/enums';

export class ShapeModifier extends CommonMethodModifier implements ShapeAttribute, AttributeModifier<ShapeAttribute> {
    applyNormalAttribute(instance: CommonShapeMethod): void { }
    applyPressedAttribute(instance: CommonShapeMethod): void { }
    applyFocusedAttribute(instance: CommonShapeMethod): void { }
    applyDisabledAttribute(instance: CommonShapeMethod): void { }
    applySelectedAttribute(instance: CommonShapeMethod): void { }
    _viewPort_flag: AttributeUpdateFlag = AttributeUpdateFlag.INITIAL
    _viewPort0_value?: ViewportRect | undefined
    _stroke_flag: AttributeUpdateFlag = AttributeUpdateFlag.INITIAL
    _stroke0_value?: ResourceColor | undefined
    _fill_flag: AttributeUpdateFlag = AttributeUpdateFlag.INITIAL
    _fill0_value?: ResourceColor | undefined
    _strokeDashOffset_flag: AttributeUpdateFlag = AttributeUpdateFlag.INITIAL
    _strokeDashOffset0_value?: number | string | undefined
    _strokeDashArray_flag: AttributeUpdateFlag = AttributeUpdateFlag.INITIAL
    _strokeDashArray0_value?: Array<Length> | undefined
    _strokeLineCap_flag: AttributeUpdateFlag = AttributeUpdateFlag.INITIAL
    _strokeLineCap0_value?: LineCapStyle | undefined
    _strokeLineJoin_flag: AttributeUpdateFlag = AttributeUpdateFlag.INITIAL
    _strokeLineJoin0_value?: LineJoinStyle | undefined
    _strokeMiterLimit_flag: AttributeUpdateFlag = AttributeUpdateFlag.INITIAL
    _strokeMiterLimit0_value?: number | string | undefined
    _strokeOpacity_flag: AttributeUpdateFlag = AttributeUpdateFlag.INITIAL
    _strokeOpacity0_value?: number | string | Resource | undefined
    _fillOpacity_flag: AttributeUpdateFlag = AttributeUpdateFlag.INITIAL
    _fillOpacity0_value?: number | string | Resource | undefined
    _strokeWidth_flag: AttributeUpdateFlag = AttributeUpdateFlag.INITIAL
    _strokeWidth0_value?: number | string | undefined
    _antiAlias_flag: AttributeUpdateFlag = AttributeUpdateFlag.INITIAL
    _antiAlias0_value?: boolean | undefined
    _mesh_flag: AttributeUpdateFlag = AttributeUpdateFlag.INITIAL
    _mesh0_value?: Array<number> | undefined
    _mesh1_value?: number | undefined
    _mesh2_value?: number | undefined
    applyModifierPatch(peer: ArkShapePeer): void {
        if (this._viewPort_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (this._viewPort_flag) {
                case AttributeUpdateFlag.UPDATE: {
                    peer.viewPortAttribute((this._viewPort0_value as ViewportRect | undefined));
                    this._viewPort_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                case AttributeUpdateFlag.SKIP: {
                    this._viewPort_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                default: {
                    this._viewPort_flag = AttributeUpdateFlag.INITIAL;
                    peer.viewPortAttribute(undefined);
                }
            }
        }
        if (this._stroke_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (this._stroke_flag) {
                case AttributeUpdateFlag.UPDATE: {
                    peer.strokeAttribute((this._stroke0_value as ResourceColor | undefined));
                    this._stroke_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                case AttributeUpdateFlag.SKIP: {
                    this._stroke_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                default: {
                    this._stroke_flag = AttributeUpdateFlag.INITIAL;
                    peer.strokeAttribute(undefined);
                }
            }
        }
        if (this._fill_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (this._fill_flag) {
                case AttributeUpdateFlag.UPDATE: {
                    peer.fillAttribute((this._fill0_value as ResourceColor | undefined));
                    this._fill_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                case AttributeUpdateFlag.SKIP: {
                    this._fill_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                default: {
                    this._fill_flag = AttributeUpdateFlag.INITIAL;
                    peer.fillAttribute(undefined);
                }
            }
        }
        if (this._strokeDashOffset_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (this._strokeDashOffset_flag) {
                case AttributeUpdateFlag.UPDATE: {
                    peer.strokeDashOffsetAttribute((this._strokeDashOffset0_value as number | string | undefined));
                    this._strokeDashOffset_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                case AttributeUpdateFlag.SKIP: {
                    this._strokeDashOffset_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                default: {
                    this._strokeDashOffset_flag = AttributeUpdateFlag.INITIAL;
                    peer.strokeDashOffsetAttribute(undefined);
                }
            }
        }
        if (this._strokeDashArray_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (this._strokeDashArray_flag) {
                case AttributeUpdateFlag.UPDATE: {
                    peer.strokeDashArrayAttribute((this._strokeDashArray0_value as Array<Length> | undefined));
                    this._strokeDashArray_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                case AttributeUpdateFlag.SKIP: {
                    this._strokeDashArray_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                default: {
                    this._strokeDashArray_flag = AttributeUpdateFlag.INITIAL;
                    peer.strokeDashArrayAttribute(undefined);
                }
            }
        }
        if (this._strokeLineCap_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (this._strokeLineCap_flag) {
                case AttributeUpdateFlag.UPDATE: {
                    peer.strokeLineCapAttribute((this._strokeLineCap0_value as LineCapStyle | undefined));
                    this._strokeLineCap_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                case AttributeUpdateFlag.SKIP: {
                    this._strokeLineCap_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                default: {
                    this._strokeLineCap_flag = AttributeUpdateFlag.INITIAL;
                    peer.strokeLineCapAttribute(undefined);
                }
            }
        }
        if (this._strokeLineJoin_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (this._strokeLineJoin_flag) {
                case AttributeUpdateFlag.UPDATE: {
                    peer.strokeLineJoinAttribute((this._strokeLineJoin0_value as LineJoinStyle | undefined));
                    this._strokeLineJoin_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                case AttributeUpdateFlag.SKIP: {
                    this._strokeLineJoin_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                default: {
                    this._strokeLineJoin_flag = AttributeUpdateFlag.INITIAL;
                    peer.strokeLineJoinAttribute(undefined);
                }
            }
        }
        if (this._strokeMiterLimit_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (this._strokeMiterLimit_flag) {
                case AttributeUpdateFlag.UPDATE: {
                    peer.strokeMiterLimitAttribute((this._strokeMiterLimit0_value as number | string | undefined));
                    this._strokeMiterLimit_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                case AttributeUpdateFlag.SKIP: {
                    this._strokeMiterLimit_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                default: {
                    this._strokeMiterLimit_flag = AttributeUpdateFlag.INITIAL;
                    peer.strokeMiterLimitAttribute(undefined);
                }
            }
        }
        if (this._strokeOpacity_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (this._strokeOpacity_flag) {
                case AttributeUpdateFlag.UPDATE: {
                    peer.strokeOpacityAttribute((this._strokeOpacity0_value as number | string | Resource | undefined));
                    this._strokeOpacity_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                case AttributeUpdateFlag.SKIP: {
                    this._strokeOpacity_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                default: {
                    this._strokeOpacity_flag = AttributeUpdateFlag.INITIAL;
                    peer.strokeOpacityAttribute(undefined);
                }
            }
        }
        if (this._fillOpacity_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (this._fillOpacity_flag) {
                case AttributeUpdateFlag.UPDATE: {
                    peer.fillOpacityAttribute((this._fillOpacity0_value as number | string | Resource | undefined));
                    this._fillOpacity_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                case AttributeUpdateFlag.SKIP: {
                    this._fillOpacity_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                default: {
                    this._fillOpacity_flag = AttributeUpdateFlag.INITIAL;
                    peer.fillOpacityAttribute(undefined);
                }
            }
        }
        if (this._strokeWidth_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (this._strokeWidth_flag) {
                case AttributeUpdateFlag.UPDATE: {
                    peer.strokeWidthAttribute((this._strokeWidth0_value as number | string | undefined));
                    this._strokeWidth_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                case AttributeUpdateFlag.SKIP: {
                    this._strokeWidth_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                default: {
                    this._strokeWidth_flag = AttributeUpdateFlag.INITIAL;
                    peer.strokeWidthAttribute(undefined);
                }
            }
        }
        if (this._antiAlias_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (this._antiAlias_flag) {
                case AttributeUpdateFlag.UPDATE: {
                    peer.antiAliasAttribute((this._antiAlias0_value as boolean | undefined));
                    this._antiAlias_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                case AttributeUpdateFlag.SKIP: {
                    this._antiAlias_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                default: {
                    this._antiAlias_flag = AttributeUpdateFlag.INITIAL;
                    peer.antiAliasAttribute(undefined);
                }
            }
        }
        if (this._mesh_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (this._mesh_flag) {
                case AttributeUpdateFlag.UPDATE: {
                    if (this._mesh0_value === undefined || this._mesh1_value === undefined || this._mesh2_value === undefined) {
                        return;
                    }
                    peer.meshAttribute((this._mesh0_value as Array<number>), (this._mesh1_value as number), (this._mesh2_value as number));
                    this._mesh_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                case AttributeUpdateFlag.SKIP: {
                    this._mesh_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                default: {
                    this._mesh_flag = AttributeUpdateFlag.INITIAL;
                    peer.meshAttribute([], 0, 0);
                }
            }
        }
    }
    mergeModifier(modifier: ShapeModifier): void {
        if (modifier._viewPort_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (modifier._viewPort_flag) {
                case AttributeUpdateFlag.UPDATE:
                case AttributeUpdateFlag.SKIP: {
                    this.viewPort(modifier._viewPort0_value);
                    break;
                }
                default: {
                    this.viewPort(undefined);
                }
            }
        }
        if (modifier._stroke_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (modifier._stroke_flag) {
                case AttributeUpdateFlag.UPDATE:
                case AttributeUpdateFlag.SKIP: {
                    this.stroke(modifier._stroke0_value);
                    break;
                }
                default: {
                    this.stroke(undefined);
                }
            }
        }
        if (modifier._fill_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (modifier._fill_flag) {
                case AttributeUpdateFlag.UPDATE:
                case AttributeUpdateFlag.SKIP: {
                    this.fill(modifier._fill0_value);
                    break;
                }
                default: {
                    this.fill(undefined);
                }
            }
        }
        if (modifier._strokeDashOffset_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (modifier._strokeDashOffset_flag) {
                case AttributeUpdateFlag.UPDATE:
                case AttributeUpdateFlag.SKIP: {
                    this.strokeDashOffset(modifier._strokeDashOffset0_value);
                    break;
                }
                default: {
                    this.strokeDashOffset(undefined);
                }
            }
        }
        if (modifier._strokeDashArray_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (modifier._strokeDashArray_flag) {
                case AttributeUpdateFlag.UPDATE:
                case AttributeUpdateFlag.SKIP: {
                    this.strokeDashArray(modifier._strokeDashArray0_value);
                    break;
                }
                default: {
                    this.strokeDashArray(undefined);
                }
            }
        }
        if (modifier._strokeLineCap_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (modifier._strokeLineCap_flag) {
                case AttributeUpdateFlag.UPDATE:
                case AttributeUpdateFlag.SKIP: {
                    this.strokeLineCap(modifier._strokeLineCap0_value);
                    break;
                }
                default: {
                    this.strokeLineCap(undefined);
                }
            }
        }
        if (modifier._strokeLineJoin_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (modifier._strokeLineJoin_flag) {
                case AttributeUpdateFlag.UPDATE:
                case AttributeUpdateFlag.SKIP: {
                    this.strokeLineJoin(modifier._strokeLineJoin0_value);
                    break;
                }
                default: {
                    this.strokeLineJoin(undefined);
                }
            }
        }
        if (modifier._strokeMiterLimit_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (modifier._strokeMiterLimit_flag) {
                case AttributeUpdateFlag.UPDATE:
                case AttributeUpdateFlag.SKIP: {
                    this.strokeMiterLimit(modifier._strokeMiterLimit0_value);
                    break;
                }
                default: {
                    this.strokeMiterLimit(undefined);
                }
            }
        }
        if (modifier._strokeOpacity_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (modifier._strokeOpacity_flag) {
                case AttributeUpdateFlag.UPDATE:
                case AttributeUpdateFlag.SKIP: {
                    this.strokeOpacity(modifier._strokeOpacity0_value);
                    break;
                }
                default: {
                    this.strokeOpacity(undefined);
                }
            }
        }
        if (modifier._fillOpacity_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (modifier._fillOpacity_flag) {
                case AttributeUpdateFlag.UPDATE:
                case AttributeUpdateFlag.SKIP: {
                    this.fillOpacity(modifier._fillOpacity0_value);
                    break;
                }
                default: {
                    this.fillOpacity(undefined);
                }
            }
        }
        if (modifier._strokeWidth_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (modifier._strokeWidth_flag) {
                case AttributeUpdateFlag.UPDATE:
                case AttributeUpdateFlag.SKIP: {
                    this.strokeWidth(modifier._strokeWidth0_value);
                    break;
                }
                default: {
                    this.strokeWidth(undefined);
                }
            }
        }
        if (modifier._antiAlias_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (modifier._antiAlias_flag) {
                case AttributeUpdateFlag.UPDATE:
                case AttributeUpdateFlag.SKIP: {
                    this.antiAlias(modifier._antiAlias0_value);
                    break;
                }
                default: {
                    this.antiAlias(undefined);
                }
            }
        }
        if (modifier._mesh_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (modifier._mesh_flag) {
                case AttributeUpdateFlag.UPDATE:
                case AttributeUpdateFlag.SKIP: {
                    this.mesh(modifier._mesh0_value, modifier._mesh1_value, modifier._mesh2_value);
                    break;
                }
                default: {
                    this.mesh(undefined, undefined, undefined);
                }
            }
        }
    }
    viewPort(value: ViewportRect | undefined): this {
        if (((this._viewPort_flag) == (AttributeUpdateFlag.INITIAL)) || (false))
        {
            this._viewPort_flag = AttributeUpdateFlag.UPDATE
            this._viewPort0_value = value
        }
        else
        {
            this._viewPort_flag = AttributeUpdateFlag.SKIP
        }
        return this
    }
    stroke(value: ResourceColor | undefined): this {
        if (((this._stroke_flag) == (AttributeUpdateFlag.INITIAL)) || (false))
        {
            this._stroke_flag = AttributeUpdateFlag.UPDATE
            this._stroke0_value = value
        }
        else
        {
            this._stroke_flag = AttributeUpdateFlag.SKIP
        }
        return this
    }
    fill(value: ResourceColor | undefined): this {
        if (((this._fill_flag) == (AttributeUpdateFlag.INITIAL)) || (false))
        {
            this._fill_flag = AttributeUpdateFlag.UPDATE
            this._fill0_value = value
        }
        else
        {
            this._fill_flag = AttributeUpdateFlag.SKIP
        }
        return this
    }
    strokeDashOffset(value: number | string | undefined): this {
        if (((this._strokeDashOffset_flag) == (AttributeUpdateFlag.INITIAL)) || ((this._strokeDashOffset0_value) == (value)))
        {
            this._strokeDashOffset_flag = AttributeUpdateFlag.UPDATE
            this._strokeDashOffset0_value = value
        }
        else
        {
            this._strokeDashOffset_flag = AttributeUpdateFlag.SKIP
        }
        return this
    }
    strokeDashArray(value: Array<Length> | undefined): this {
        if (((this._strokeDashArray_flag) == (AttributeUpdateFlag.INITIAL)) || (false))
        {
            this._strokeDashArray_flag = AttributeUpdateFlag.UPDATE
            this._strokeDashArray0_value = value
        }
        else
        {
            this._strokeDashArray_flag = AttributeUpdateFlag.SKIP
        }
        return this
    }
    strokeLineCap(value: LineCapStyle | undefined): this {
        if (((this._strokeLineCap_flag) == (AttributeUpdateFlag.INITIAL)) || (false))
        {
            this._strokeLineCap_flag = AttributeUpdateFlag.UPDATE
            this._strokeLineCap0_value = value
        }
        else
        {
            this._strokeLineCap_flag = AttributeUpdateFlag.SKIP
        }
        return this
    }
    strokeLineJoin(value: LineJoinStyle | undefined): this {
        if (((this._strokeLineJoin_flag) == (AttributeUpdateFlag.INITIAL)) || (false))
        {
            this._strokeLineJoin_flag = AttributeUpdateFlag.UPDATE
            this._strokeLineJoin0_value = value
        }
        else
        {
            this._strokeLineJoin_flag = AttributeUpdateFlag.SKIP
        }
        return this
    }
    strokeMiterLimit(value: number | string | undefined): this {
        if (((this._strokeMiterLimit_flag) == (AttributeUpdateFlag.INITIAL)) || ((this._strokeMiterLimit0_value) == (value)))
        {
            this._strokeMiterLimit_flag = AttributeUpdateFlag.UPDATE
            this._strokeMiterLimit0_value = value
        }
        else
        {
            this._strokeMiterLimit_flag = AttributeUpdateFlag.SKIP
        }
        return this
    }
    strokeOpacity(value: number | string | Resource | undefined): this {
        if (((this._strokeOpacity_flag) == (AttributeUpdateFlag.INITIAL)) || (false))
        {
            this._strokeOpacity_flag = AttributeUpdateFlag.UPDATE
            this._strokeOpacity0_value = value
        }
        else
        {
            this._strokeOpacity_flag = AttributeUpdateFlag.SKIP
        }
        return this
    }
    fillOpacity(value: number | string | Resource | undefined): this {
        if (((this._fillOpacity_flag) == (AttributeUpdateFlag.INITIAL)) || (false))
        {
            this._fillOpacity_flag = AttributeUpdateFlag.UPDATE
            this._fillOpacity0_value = value
        }
        else
        {
            this._fillOpacity_flag = AttributeUpdateFlag.SKIP
        }
        return this
    }
    strokeWidth(value: number | string | undefined): this {
        if (((this._strokeWidth_flag) == (AttributeUpdateFlag.INITIAL)) || ((this._strokeWidth0_value) == (value)))
        {
            this._strokeWidth_flag = AttributeUpdateFlag.UPDATE
            this._strokeWidth0_value = value
        }
        else
        {
            this._strokeWidth_flag = AttributeUpdateFlag.SKIP
        }
        return this
    }
    antiAlias(value: boolean | undefined): this {
        if (((this._antiAlias_flag) == (AttributeUpdateFlag.INITIAL)) || ((this._antiAlias0_value) == (value)))
        {
            this._antiAlias_flag = AttributeUpdateFlag.UPDATE
            this._antiAlias0_value = value
        }
        else
        {
            this._antiAlias_flag = AttributeUpdateFlag.SKIP
        }
        return this
    }
    mesh(value: Array<number> | undefined, column: number | undefined, row: number | undefined): this {
        if (((this._mesh_flag) == (AttributeUpdateFlag.INITIAL)) || ((this._mesh0_value) == (value)) || ((this._mesh1_value) == (column)) || ((this._mesh2_value) == (row)))
        {
            this._mesh_flag = AttributeUpdateFlag.UPDATE
            this._mesh0_value = value
            this._mesh1_value = column
            this._mesh2_value = row
        }
        else
        {
            this._mesh_flag = AttributeUpdateFlag.SKIP
        }
        return this
    }
}

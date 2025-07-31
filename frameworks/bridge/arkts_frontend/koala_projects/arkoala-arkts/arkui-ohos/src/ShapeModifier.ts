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
import { ViewportRect, ShapeAttribute, ArkShapePeer } from 'arkui/component/shape';
import { Length, ResourceColor } from 'arkui/component/units';
import { Resource } from 'global.resource';
import { LineCapStyle, LineJoinStyle } from 'arkui/component/enums';
import { PeerNode } from './PeerNode';

export class ShapeModifier extends CommonMethodModifier implements ShapeAttribute, AttributeModifier<ShapeAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyNormalAttribute(instance: ShapeAttribute): void { }
    applyPressedAttribute(instance: ShapeAttribute): void { }
    applyFocusedAttribute(instance: ShapeAttribute): void { }
    applyDisabledAttribute(instance: ShapeAttribute): void { }
    applySelectedAttribute(instance: ShapeAttribute): void { }
    _viewPort_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _viewPort_0_0value?: ViewportRect | undefined
    _stroke_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _stroke_0_0value?: ResourceColor | undefined
    _fill_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fill_0_0value?: ResourceColor | undefined
    _strokeDashOffset_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _strokeDashOffset_0_0value?: number | string | undefined
    _strokeDashArray_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _strokeDashArray_0_0value?: Array<Length> | undefined
    _strokeLineCap_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _strokeLineCap_0_0value?: LineCapStyle | undefined
    _strokeLineJoin_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _strokeLineJoin_0_0value?: LineJoinStyle | undefined
    _strokeMiterLimit_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _strokeMiterLimit_0_0value?: number | string | undefined
    _strokeOpacity_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _strokeOpacity_0_0value?: number | string | Resource | undefined
    _fillOpacity_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fillOpacity_0_0value?: number | string | Resource | undefined
    _strokeWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _strokeWidth_0_0value?: number | string | undefined
    _antiAlias_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _antiAlias_0_0value?: boolean | undefined
    _mesh_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _mesh_0_0value?: Array<number> | undefined
    _mesh_0_1value?: number | undefined
    _mesh_0_2value?: number | undefined
    applyModifierPatch(peerNode: PeerNode): void {
        super.applyModifierPatch(peerNode)
        const peer = peerNode as ArkShapePeer
        if (this._viewPort_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._viewPort_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.viewPortAttribute((this._viewPort_0_0value as ViewportRect | undefined));
                    this._viewPort_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._viewPort_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._viewPort_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.viewPortAttribute(undefined);
                }
            }
        }
        if (this._stroke_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._stroke_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.strokeAttribute((this._stroke_0_0value as ResourceColor | undefined));
                    this._stroke_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._stroke_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._stroke_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.strokeAttribute(undefined);
                }
            }
        }
        if (this._fill_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fill_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.fillAttribute((this._fill_0_0value as ResourceColor | undefined));
                    this._fill_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fill_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fill_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.fillAttribute(undefined);
                }
            }
        }
        if (this._strokeDashOffset_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._strokeDashOffset_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.strokeDashOffsetAttribute((this._strokeDashOffset_0_0value as number | string | undefined));
                    this._strokeDashOffset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._strokeDashOffset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._strokeDashOffset_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.strokeDashOffsetAttribute(undefined);
                }
            }
        }
        if (this._strokeDashArray_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._strokeDashArray_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.strokeDashArrayAttribute((this._strokeDashArray_0_0value as Array<Length> | undefined));
                    this._strokeDashArray_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._strokeDashArray_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._strokeDashArray_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.strokeDashArrayAttribute(undefined);
                }
            }
        }
        if (this._strokeLineCap_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._strokeLineCap_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.strokeLineCapAttribute((this._strokeLineCap_0_0value as LineCapStyle | undefined));
                    this._strokeLineCap_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._strokeLineCap_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._strokeLineCap_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.strokeLineCapAttribute(undefined);
                }
            }
        }
        if (this._strokeLineJoin_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._strokeLineJoin_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.strokeLineJoinAttribute((this._strokeLineJoin_0_0value as LineJoinStyle | undefined));
                    this._strokeLineJoin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._strokeLineJoin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._strokeLineJoin_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.strokeLineJoinAttribute(undefined);
                }
            }
        }
        if (this._strokeMiterLimit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._strokeMiterLimit_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.strokeMiterLimitAttribute((this._strokeMiterLimit_0_0value as number | string | undefined));
                    this._strokeMiterLimit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._strokeMiterLimit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._strokeMiterLimit_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.strokeMiterLimitAttribute(undefined);
                }
            }
        }
        if (this._strokeOpacity_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._strokeOpacity_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.strokeOpacityAttribute((this._strokeOpacity_0_0value as number | string | Resource | undefined));
                    this._strokeOpacity_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._strokeOpacity_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._strokeOpacity_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.strokeOpacityAttribute(undefined);
                }
            }
        }
        if (this._fillOpacity_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fillOpacity_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.fillOpacityAttribute((this._fillOpacity_0_0value as number | string | Resource | undefined));
                    this._fillOpacity_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fillOpacity_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fillOpacity_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.fillOpacityAttribute(undefined);
                }
            }
        }
        if (this._strokeWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._strokeWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.strokeWidthAttribute((this._strokeWidth_0_0value as number | string | undefined));
                    this._strokeWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._strokeWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._strokeWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.strokeWidthAttribute(undefined);
                }
            }
        }
        if (this._antiAlias_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._antiAlias_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.antiAliasAttribute((this._antiAlias_0_0value as boolean | undefined));
                    this._antiAlias_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._antiAlias_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._antiAlias_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.antiAliasAttribute(undefined);
                }
            }
        }
        if (this._mesh_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._mesh_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    if (this._mesh_0_0value === undefined || this._mesh_0_1value === undefined || this._mesh_0_2value === undefined) {
                        return;
                    }
                    peer.meshAttribute((this._mesh_0_0value as Array<number>), (this._mesh_0_1value as number), (this._mesh_0_2value as number));
                    this._mesh_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._mesh_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._mesh_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.meshAttribute([], 0, 0);
                }
            }
        }
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
        if (!(value instanceof ShapeModifier)) {
            return;
        }
        const modifier = value as ShapeModifier
        if (modifier._viewPort_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._viewPort_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.viewPort(modifier._viewPort_0_0value);
                    break;
                }
                default: {
                    this.viewPort(undefined);
                }
            }
        }
        if (modifier._stroke_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._stroke_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.stroke(modifier._stroke_0_0value);
                    break;
                }
                default: {
                    this.stroke(undefined);
                }
            }
        }
        if (modifier._fill_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fill_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fill(modifier._fill_0_0value);
                    break;
                }
                default: {
                    this.fill(undefined);
                }
            }
        }
        if (modifier._strokeDashOffset_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._strokeDashOffset_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.strokeDashOffset(modifier._strokeDashOffset_0_0value);
                    break;
                }
                default: {
                    this.strokeDashOffset(undefined);
                }
            }
        }
        if (modifier._strokeDashArray_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._strokeDashArray_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.strokeDashArray(modifier._strokeDashArray_0_0value);
                    break;
                }
                default: {
                    this.strokeDashArray(undefined);
                }
            }
        }
        if (modifier._strokeLineCap_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._strokeLineCap_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.strokeLineCap(modifier._strokeLineCap_0_0value);
                    break;
                }
                default: {
                    this.strokeLineCap(undefined);
                }
            }
        }
        if (modifier._strokeLineJoin_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._strokeLineJoin_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.strokeLineJoin(modifier._strokeLineJoin_0_0value);
                    break;
                }
                default: {
                    this.strokeLineJoin(undefined);
                }
            }
        }
        if (modifier._strokeMiterLimit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._strokeMiterLimit_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.strokeMiterLimit(modifier._strokeMiterLimit_0_0value);
                    break;
                }
                default: {
                    this.strokeMiterLimit(undefined);
                }
            }
        }
        if (modifier._strokeOpacity_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._strokeOpacity_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.strokeOpacity(modifier._strokeOpacity_0_0value);
                    break;
                }
                default: {
                    this.strokeOpacity(undefined);
                }
            }
        }
        if (modifier._fillOpacity_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fillOpacity_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fillOpacity(modifier._fillOpacity_0_0value);
                    break;
                }
                default: {
                    this.fillOpacity(undefined);
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
                    this.strokeWidth(undefined);
                }
            }
        }
        if (modifier._antiAlias_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._antiAlias_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.antiAlias(modifier._antiAlias_0_0value);
                    break;
                }
                default: {
                    this.antiAlias(undefined);
                }
            }
        }
        if (modifier._mesh_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._mesh_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.mesh(modifier._mesh_0_0value, modifier._mesh_0_1value, modifier._mesh_0_2value);
                    break;
                }
                default: {
                    this.mesh(undefined, undefined, undefined);
                }
            }
        }
    }
    viewPort(value: ViewportRect | undefined): this {
        if (((this._viewPort_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._viewPort_0_flag = AttributeUpdaterFlag.UPDATE
            this._viewPort_0_0value = value
        }
        else
        {
            this._viewPort_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    stroke(value: ResourceColor | undefined): this {
        if (((this._stroke_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._stroke_0_flag = AttributeUpdaterFlag.UPDATE
            this._stroke_0_0value = value
        }
        else
        {
            this._stroke_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fill(value: ResourceColor | undefined): this {
        if (((this._fill_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fill_0_flag = AttributeUpdaterFlag.UPDATE
            this._fill_0_0value = value
        }
        else
        {
            this._fill_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    strokeDashOffset(value: number | string | undefined): this {
        if (((this._strokeDashOffset_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._strokeDashOffset_0_0value) !== (value)))
        {
            this._strokeDashOffset_0_flag = AttributeUpdaterFlag.UPDATE
            this._strokeDashOffset_0_0value = value
        }
        else
        {
            this._strokeDashOffset_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    strokeDashArray(value: Array<Length> | undefined): this {
        if (((this._strokeDashArray_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._strokeDashArray_0_flag = AttributeUpdaterFlag.UPDATE
            this._strokeDashArray_0_0value = value
        }
        else
        {
            this._strokeDashArray_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    strokeLineCap(value: LineCapStyle | undefined): this {
        if (((this._strokeLineCap_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._strokeLineCap_0_flag = AttributeUpdaterFlag.UPDATE
            this._strokeLineCap_0_0value = value
        }
        else
        {
            this._strokeLineCap_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    strokeLineJoin(value: LineJoinStyle | undefined): this {
        if (((this._strokeLineJoin_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._strokeLineJoin_0_flag = AttributeUpdaterFlag.UPDATE
            this._strokeLineJoin_0_0value = value
        }
        else
        {
            this._strokeLineJoin_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    strokeMiterLimit(value: number | string | undefined): this {
        if (((this._strokeMiterLimit_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._strokeMiterLimit_0_0value) !== (value)))
        {
            this._strokeMiterLimit_0_flag = AttributeUpdaterFlag.UPDATE
            this._strokeMiterLimit_0_0value = value
        }
        else
        {
            this._strokeMiterLimit_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    strokeOpacity(value: number | string | Resource | undefined): this {
        if (((this._strokeOpacity_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._strokeOpacity_0_flag = AttributeUpdaterFlag.UPDATE
            this._strokeOpacity_0_0value = value
        }
        else
        {
            this._strokeOpacity_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fillOpacity(value: number | string | Resource | undefined): this {
        if (((this._fillOpacity_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fillOpacity_0_flag = AttributeUpdaterFlag.UPDATE
            this._fillOpacity_0_0value = value
        }
        else
        {
            this._fillOpacity_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    strokeWidth(value: number | string | undefined): this {
        if (((this._strokeWidth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._strokeWidth_0_0value) !== (value)))
        {
            this._strokeWidth_0_flag = AttributeUpdaterFlag.UPDATE
            this._strokeWidth_0_0value = value
        }
        else
        {
            this._strokeWidth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    antiAlias(value: boolean | undefined): this {
        if (((this._antiAlias_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._antiAlias_0_0value) !== (value)))
        {
            this._antiAlias_0_flag = AttributeUpdaterFlag.UPDATE
            this._antiAlias_0_0value = value
        }
        else
        {
            this._antiAlias_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    mesh(value: Array<number> | undefined, column: number | undefined, row: number | undefined): this {
        if (((this._mesh_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._mesh_0_0value) !== (value)) || ((this._mesh_0_1value) !== (column)) || ((this._mesh_0_2value) !== (row)))
        {
            this._mesh_0_flag = AttributeUpdaterFlag.UPDATE
            this._mesh_0_0value = value
            this._mesh_0_1value = column
            this._mesh_0_2value = row
        }
        else
        {
            this._mesh_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
}

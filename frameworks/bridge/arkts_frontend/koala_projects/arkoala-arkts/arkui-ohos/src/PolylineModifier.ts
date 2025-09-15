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
import { ShapePoint } from 'arkui/component/line';
import { ArkPolylinePeer, PolylineAttribute } from 'arkui/component/polyline';
import { CommonShapeMethodModifier } from './CommonShapeMethodModifier';

export class PolylineModifier extends CommonShapeMethodModifier implements PolylineAttribute, AttributeModifier<PolylineAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyNormalAttribute(instance: CommonShapeMethod): void { }
    applyPressedAttribute(instance: CommonShapeMethod): void { }
    applyFocusedAttribute(instance: CommonShapeMethod): void { }
    applyDisabledAttribute(instance: CommonShapeMethod): void { }
    applySelectedAttribute(instance: CommonShapeMethod): void { }
    _points_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _points_0_0value?: Array<ShapePoint> | undefined
    applyModifierPatch(peer: ArkPolylinePeer): void {
        super.applyModifierPatch(peer)
        if (this._points_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._points_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.pointsAttribute((this._points_0_0value as Array<ShapePoint> | undefined));
                    this._points_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._points_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._points_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.pointsAttribute((undefined as Array<ShapePoint> | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: PolylineModifier): void {
        super.mergeModifier(modifier)
        if (modifier._points_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._points_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.points(modifier._points_0_0value);
                    break;
                }
                default: {
                    this.points((undefined as Array<ShapePoint> | undefined));
                }
            }
        }
    }
    points(value: Array<ShapePoint> | undefined): this {
        if (((this._points_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._points_0_flag = AttributeUpdaterFlag.UPDATE
            this._points_0_0value = value
        }
        else
        {
            this._points_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
}

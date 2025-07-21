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
import { ShapePoint } from 'arkui/component/line';
import { ArkPolylinePeer, PolylineAttribute } from 'arkui/component/polyline';
import { CommonShapeMethodModifier } from './CommonShapeMethodModifier';

export class PolylineModifier extends CommonShapeMethodModifier implements PolylineAttribute, AttributeModifier<PolylineAttribute> {
    applyNormalAttribute(instance: CommonShapeMethod): void { }
    applyPressedAttribute(instance: CommonShapeMethod): void { }
    applyFocusedAttribute(instance: CommonShapeMethod): void { }
    applyDisabledAttribute(instance: CommonShapeMethod): void { }
    applySelectedAttribute(instance: CommonShapeMethod): void { }
    _points_flag: AttributeUpdateFlag = AttributeUpdateFlag.INITIAL
    _points0_value?: Array<ShapePoint> | undefined
    applyModifierPatch(peer: ArkPolylinePeer): void {
        if (this._points_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (this._points_flag) {
                case AttributeUpdateFlag.UPDATE: {
                    peer.pointsAttribute((this._points0_value as Array<ShapePoint> | undefined));
                    this._points_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                case AttributeUpdateFlag.SKIP: {
                    this._points_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                default: {
                    this._points_flag = AttributeUpdateFlag.INITIAL;
                    peer.pointsAttribute(undefined);
                }
            }
        }
    }
    mergeModifier(modifier: PolylineModifier): void {
        if (modifier._points_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (modifier._points_flag) {
                case AttributeUpdateFlag.UPDATE:
                case AttributeUpdateFlag.SKIP: {
                    this.points(modifier._points0_value);
                    break;
                }
                default: {
                    this.points(undefined);
                }
            }
        }
    }
    points(value: Array<ShapePoint> | undefined): this {
        if (((this._points_flag) == (AttributeUpdateFlag.INITIAL)) || (false))
        {
            this._points_flag = AttributeUpdateFlag.UPDATE
            this._points0_value = value
        }
        else
        {
            this._points_flag = AttributeUpdateFlag.SKIP
        }
        return this
    }
}

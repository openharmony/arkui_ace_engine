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
import { ShapePoint, LineAttribute, ArkLinePeer } from 'arkui/component/line';
import { CommonShapeMethodModifier } from './CommonShapeMethodModifier'

export class LineModifier extends CommonShapeMethodModifier implements LineAttribute, AttributeModifier<LineAttribute> {
    applyNormalAttribute(instance: CommonShapeMethod): void { }
    applyPressedAttribute(instance: CommonShapeMethod): void { }
    applyFocusedAttribute(instance: CommonShapeMethod): void { }
    applyDisabledAttribute(instance: CommonShapeMethod): void { }
    applySelectedAttribute(instance: CommonShapeMethod): void { }
    _startPoint_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _startPoint0_value?: ShapePoint | undefined
    _endPoint_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _endPoint0_value?: ShapePoint | undefined
    applyModifierPatch(peer: ArkLinePeer): void {
        if (this._startPoint_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._startPoint_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.startPointAttribute((this._startPoint0_value as ShapePoint | undefined));
                    this._startPoint_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._startPoint_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._startPoint_flag = AttributeUpdaterFlag.INITIAL;
                    peer.startPointAttribute(undefined);
                }
            }
        }
        if (this._endPoint_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._endPoint_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.endPointAttribute((this._endPoint0_value as ShapePoint | undefined));
                    this._endPoint_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._endPoint_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._endPoint_flag = AttributeUpdaterFlag.INITIAL;
                    peer.endPointAttribute(undefined);
                }
            }
        }
    }
    mergeModifier(modifier: LineModifier): void {
        if (modifier._startPoint_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._startPoint_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.startPoint(modifier._startPoint0_value);
                    break;
                }
                default: {
                    this.startPoint(undefined);
                }
            }
        }
        if (modifier._endPoint_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._endPoint_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.endPoint(modifier._endPoint0_value);
                    break;
                }
                default: {
                    this.endPoint(undefined);
                }
            }
        }
    }
    startPoint(value: ShapePoint | undefined): this {
        if (((this._startPoint_flag) == (AttributeUpdaterFlag.INITIAL)) || (false))
        {
            this._startPoint_flag = AttributeUpdaterFlag.UPDATE
            this._startPoint0_value = value
        }
        else
        {
            this._startPoint_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    endPoint(value: ShapePoint | undefined): this {
        if (((this._endPoint_flag) == (AttributeUpdaterFlag.INITIAL)) || (false))
        {
            this._endPoint_flag = AttributeUpdaterFlag.UPDATE
            this._endPoint0_value = value
        }
        else
        {
            this._endPoint_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
}

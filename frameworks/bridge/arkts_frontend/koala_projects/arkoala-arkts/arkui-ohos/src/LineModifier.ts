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
import { ShapePoint, LineAttribute, ArkLinePeer } from 'arkui/component/line';
import { CommonShapeMethodModifier } from './CommonShapeMethodModifier'

export class LineModifier extends CommonShapeMethodModifier implements LineAttribute, AttributeModifier<LineAttribute> {
    applyNormalAttribute(instance: CommonShapeMethod): void { }
    applyPressedAttribute(instance: CommonShapeMethod): void { }
    applyFocusedAttribute(instance: CommonShapeMethod): void { }
    applyDisabledAttribute(instance: CommonShapeMethod): void { }
    applySelectedAttribute(instance: CommonShapeMethod): void { }
    _startPoint_flag: AttributeUpdateFlag = AttributeUpdateFlag.INITIAL
    _startPoint0_value?: ShapePoint | undefined
    _endPoint_flag: AttributeUpdateFlag = AttributeUpdateFlag.INITIAL
    _endPoint0_value?: ShapePoint | undefined
    applyModifierPatch(peer: ArkLinePeer): void {
        if (this._startPoint_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (this._startPoint_flag) {
                case AttributeUpdateFlag.UPDATE: {
                    peer.startPointAttribute((this._startPoint0_value as ShapePoint | undefined));
                    this._startPoint_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                case AttributeUpdateFlag.SKIP: {
                    this._startPoint_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                default: {
                    this._startPoint_flag = AttributeUpdateFlag.INITIAL;
                    peer.startPointAttribute(undefined);
                }
            }
        }
        if (this._endPoint_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (this._endPoint_flag) {
                case AttributeUpdateFlag.UPDATE: {
                    peer.endPointAttribute((this._endPoint0_value as ShapePoint | undefined));
                    this._endPoint_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                case AttributeUpdateFlag.SKIP: {
                    this._endPoint_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                default: {
                    this._endPoint_flag = AttributeUpdateFlag.INITIAL;
                    peer.endPointAttribute(undefined);
                }
            }
        }
    }
    mergeModifier(modifier: LineModifier): void {
        if (modifier._startPoint_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (modifier._startPoint_flag) {
                case AttributeUpdateFlag.UPDATE:
                case AttributeUpdateFlag.SKIP: {
                    this.startPoint(modifier._startPoint0_value);
                    break;
                }
                default: {
                    this.startPoint(undefined);
                }
            }
        }
        if (modifier._endPoint_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (modifier._endPoint_flag) {
                case AttributeUpdateFlag.UPDATE:
                case AttributeUpdateFlag.SKIP: {
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
        if (((this._startPoint_flag) == (AttributeUpdateFlag.INITIAL)) || (false))
        {
            this._startPoint_flag = AttributeUpdateFlag.UPDATE
            this._startPoint0_value = value
        }
        else
        {
            this._startPoint_flag = AttributeUpdateFlag.SKIP
        }
        return this
    }
    endPoint(value: ShapePoint | undefined): this {
        if (((this._endPoint_flag) == (AttributeUpdateFlag.INITIAL)) || (false))
        {
            this._endPoint_flag = AttributeUpdateFlag.UPDATE
            this._endPoint0_value = value
        }
        else
        {
            this._endPoint_flag = AttributeUpdateFlag.SKIP
        }
        return this
    }
}

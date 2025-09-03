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
import { PeerNode } from './PeerNode';

export class LineModifier extends CommonShapeMethodModifier implements LineAttribute, AttributeModifier<LineAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyNormalAttribute(instance: LineAttribute): void { }
    applyPressedAttribute(instance: LineAttribute): void { }
    applyFocusedAttribute(instance: LineAttribute): void { }
    applyDisabledAttribute(instance: LineAttribute): void { }
    applySelectedAttribute(instance: LineAttribute): void { }
    _startPoint_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _startPoint_0_0value?: ShapePoint | undefined
    _endPoint_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _endPoint_0_0value?: ShapePoint | undefined
    applyModifierPatch(peerNode: PeerNode): void {
        super.applyModifierPatch(peerNode)
        const peer = peerNode as ArkLinePeer
        if (this._startPoint_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._startPoint_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.startPointAttribute((this._startPoint_0_0value as ShapePoint | undefined));
                    this._startPoint_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._startPoint_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._startPoint_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.startPointAttribute((undefined as ShapePoint | undefined));
                }
            }
        }
        if (this._endPoint_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._endPoint_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.endPointAttribute((this._endPoint_0_0value as ShapePoint | undefined));
                    this._endPoint_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._endPoint_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._endPoint_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.endPointAttribute((undefined as ShapePoint | undefined));
                }
            }
        }
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
        if (!(value instanceof LineModifier)) {
            return;
        }
        const modifier = value as LineModifier
        if (modifier._startPoint_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._startPoint_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.startPoint(modifier._startPoint_0_0value);
                    break;
                }
                default: {
                    this.startPoint((undefined as ShapePoint | undefined));
                }
            }
        }
        if (modifier._endPoint_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._endPoint_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.endPoint(modifier._endPoint_0_0value);
                    break;
                }
                default: {
                    this.endPoint((undefined as ShapePoint | undefined));
                }
            }
        }
    }
    startPoint(value: ShapePoint | undefined): this {
        if (((this._startPoint_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._startPoint_0_flag = AttributeUpdaterFlag.UPDATE
            this._startPoint_0_0value = value
        }
        else
        {
            this._startPoint_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    endPoint(value: ShapePoint | undefined): this {
        if (((this._endPoint_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._endPoint_0_flag = AttributeUpdaterFlag.UPDATE
            this._endPoint_0_0value = value
        }
        else
        {
            this._endPoint_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
}

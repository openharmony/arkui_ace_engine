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
import { RectAttribute, ArkRectPeer, RadiusItem } from 'arkui/component/rect';
import { Length } from 'arkui/component/units';
import { CommonShapeMethodModifier } from './CommonShapeMethodModifier';
import { PeerNode } from './PeerNode';

export class RectModifier extends CommonShapeMethodModifier implements RectAttribute, AttributeModifier<RectAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyNormalAttribute(instance: RectAttribute): void { }
    applyPressedAttribute(instance: RectAttribute): void { }
    applyFocusedAttribute(instance: RectAttribute): void { }
    applyDisabledAttribute(instance: RectAttribute): void { }
    applySelectedAttribute(instance: RectAttribute): void { }
    _radiusWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _radiusWidth_0_0value?: number | string | undefined
    _radiusHeight_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _radiusHeight_0_0value?: number | string | undefined
    _radius_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _radius_0_0value?: Length | Array<RadiusItem> | undefined
    applyModifierPatch(peerNode: PeerNode): void {
        super.applyModifierPatch(peerNode)
        const peer = peerNode as ArkRectPeer
        if (this._radiusWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._radiusWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.radiusWidthAttribute((this._radiusWidth_0_0value as number | string | undefined));
                    this._radiusWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._radiusWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._radiusWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.radiusWidthAttribute(undefined);
                }
            }
        }
        if (this._radiusHeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._radiusHeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.radiusHeightAttribute((this._radiusHeight_0_0value as number | string | undefined));
                    this._radiusHeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._radiusHeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._radiusHeight_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.radiusHeightAttribute(undefined);
                }
            }
        }
        if (this._radius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._radius_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.radiusAttribute((this._radius_0_0value as Length | Array<RadiusItem> | undefined));
                    this._radius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._radius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._radius_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.radiusAttribute(undefined);
                }
            }
        }
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
        if (!(value instanceof RectModifier)) {
            return;
        }
        const modifier = value as RectModifier
        if (modifier._radiusWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._radiusWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.radiusWidth(modifier._radiusWidth_0_0value);
                    break;
                }
                default: {
                    this.radiusWidth(undefined);
                }
            }
        }
        if (modifier._radiusHeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._radiusHeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.radiusHeight(modifier._radiusHeight_0_0value);
                    break;
                }
                default: {
                    this.radiusHeight(undefined);
                }
            }
        }
        if (modifier._radius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._radius_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.radius(modifier._radius_0_0value);
                    break;
                }
                default: {
                    this.radius(undefined);
                }
            }
        }
    }
    radiusWidth(value: number | string | undefined): this {
        if (((this._radiusWidth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._radiusWidth_0_0value) !== (value)))
        {
            this._radiusWidth_0_flag = AttributeUpdaterFlag.UPDATE
            this._radiusWidth_0_0value = value
        }
        else
        {
            this._radiusWidth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    radiusHeight(value: number | string | undefined): this {
        if (((this._radiusHeight_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._radiusHeight_0_0value) !== (value)))
        {
            this._radiusHeight_0_flag = AttributeUpdaterFlag.UPDATE
            this._radiusHeight_0_0value = value
        }
        else
        {
            this._radiusHeight_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    radius(value: Length | Array<RadiusItem> | undefined): this {
        if (((this._radius_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._radius_0_0value) !== (value)))
        {
            this._radius_0_flag = AttributeUpdaterFlag.UPDATE
            this._radius_0_0value = value
        }
        else
        {
            this._radius_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
}

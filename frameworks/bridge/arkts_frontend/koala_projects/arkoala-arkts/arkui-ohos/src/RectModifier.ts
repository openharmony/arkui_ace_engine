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
import { RectAttribute, ArkRectPeer } from 'arkui/component/rect';
import { CommonShapeMethodModifier } from './CommonShapeMethodModifier';

export class RectModifier extends CommonShapeMethodModifier implements RectAttribute, AttributeModifier<RectAttribute> {
    applyNormalAttribute(instance: CommonShapeMethod): void { }
    applyPressedAttribute(instance: CommonShapeMethod): void { }
    applyFocusedAttribute(instance: CommonShapeMethod): void { }
    applyDisabledAttribute(instance: CommonShapeMethod): void { }
    applySelectedAttribute(instance: CommonShapeMethod): void { }
    _radiusWidth_flag: AttributeUpdateFlag = AttributeUpdateFlag.INITIAL
    _radiusWidth0_value?: number | string | undefined
    _radiusHeight_flag: AttributeUpdateFlag = AttributeUpdateFlag.INITIAL
    _radiusHeight0_value?: number | string | undefined
    _radius_flag: AttributeUpdateFlag = AttributeUpdateFlag.INITIAL
    _radius0_value?: number | string | Array<number | string> | undefined
    applyModifierPatch(peer: ArkRectPeer): void {
        if (this._radiusWidth_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (this._radiusWidth_flag) {
                case AttributeUpdateFlag.UPDATE: {
                    peer.radiusWidthAttribute((this._radiusWidth0_value as number | string | undefined));
                    this._radiusWidth_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                case AttributeUpdateFlag.SKIP: {
                    this._radiusWidth_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                default: {
                    this._radiusWidth_flag = AttributeUpdateFlag.INITIAL;
                    peer.radiusWidthAttribute(undefined);
                }
            }
        }
        if (this._radiusHeight_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (this._radiusHeight_flag) {
                case AttributeUpdateFlag.UPDATE: {
                    peer.radiusHeightAttribute((this._radiusHeight0_value as number | string | undefined));
                    this._radiusHeight_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                case AttributeUpdateFlag.SKIP: {
                    this._radiusHeight_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                default: {
                    this._radiusHeight_flag = AttributeUpdateFlag.INITIAL;
                    peer.radiusHeightAttribute(undefined);
                }
            }
        }
        if (this._radius_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (this._radius_flag) {
                case AttributeUpdateFlag.UPDATE: {
                    peer.radiusAttribute((this._radius0_value as number | string | Array<number | string> | undefined));
                    this._radius_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                case AttributeUpdateFlag.SKIP: {
                    this._radius_flag = AttributeUpdateFlag.RESET;
                    break;
                }
                default: {
                    this._radius_flag = AttributeUpdateFlag.INITIAL;
                    peer.radiusAttribute(undefined);
                }
            }
        }
    }
    mergeModifier(modifier: RectModifier): void {
        if (modifier._radiusWidth_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (modifier._radiusWidth_flag) {
                case AttributeUpdateFlag.UPDATE:
                case AttributeUpdateFlag.SKIP: {
                    this.radiusWidth(modifier._radiusWidth0_value);
                    break;
                }
                default: {
                    this.radiusWidth(undefined);
                }
            }
        }
        if (modifier._radiusHeight_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (modifier._radiusHeight_flag) {
                case AttributeUpdateFlag.UPDATE:
                case AttributeUpdateFlag.SKIP: {
                    this.radiusHeight(modifier._radiusHeight0_value);
                    break;
                }
                default: {
                    this.radiusHeight(undefined);
                }
            }
        }
        if (modifier._radius_flag != AttributeUpdateFlag.INITIAL)
        {
            switch (modifier._radius_flag) {
                case AttributeUpdateFlag.UPDATE:
                case AttributeUpdateFlag.SKIP: {
                    this.radius(modifier._radius0_value);
                    break;
                }
                default: {
                    this.radius(undefined);
                }
            }
        }
    }
    radiusWidth(value: number | string | undefined): this {
        if (((this._radiusWidth_flag) == (AttributeUpdateFlag.INITIAL)) || ((this._radiusWidth0_value) == (value)))
        {
            this._radiusWidth_flag = AttributeUpdateFlag.UPDATE
            this._radiusWidth0_value = value
        }
        else
        {
            this._radiusWidth_flag = AttributeUpdateFlag.SKIP
        }
        return this
    }
    radiusHeight(value: number | string | undefined): this {
        if (((this._radiusHeight_flag) == (AttributeUpdateFlag.INITIAL)) || ((this._radiusHeight0_value) == (value)))
        {
            this._radiusHeight_flag = AttributeUpdateFlag.UPDATE
            this._radiusHeight0_value = value
        }
        else
        {
            this._radiusHeight_flag = AttributeUpdateFlag.SKIP
        }
        return this
    }
    radius(value: number | string | Array<number | string> | undefined): this {
        if (((this._radius_flag) == (AttributeUpdateFlag.INITIAL)) || ((this._radius0_value) == (value)))
        {
            this._radius_flag = AttributeUpdateFlag.UPDATE
            this._radius0_value = value
        }
        else
        {
            this._radius_flag = AttributeUpdateFlag.SKIP
        }
        return this
    }
}

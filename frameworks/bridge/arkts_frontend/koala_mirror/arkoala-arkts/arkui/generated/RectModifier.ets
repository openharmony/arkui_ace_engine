/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { CommonShapeMethodModifier } from "./CommonShapeMethodModifier"
import { CommonMethodModifier } from "./CommonMethodModifier"
import { AttributeModifier } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdater"
import { ArkRectPeer, RectAttribute } from "./component/rect"
import { CommonShapeMethod, CommonMethod } from "./component/common"
export class RectModifier extends CommonShapeMethodModifier implements RectAttribute,AttributeModifier<RectAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: RectAttribute): void { }
    applyPressedAttribute(instance: RectAttribute): void { }
    applyFocusedAttribute(instance: RectAttribute): void { }
    applyDisabledAttribute(instance: RectAttribute): void { }
    applySelectedAttribute(instance: RectAttribute): void { }
    _radius_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _radius_0_0value?: number | string | Array<number | string> | undefined
    applyModifierPatch(peer: ArkRectPeer): void {
        super.applyModifierPatch(peer)
        if (this._radius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._radius_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRadiusAttribute((this._radius_0_0value as number | string | Array<number | string> | undefined));
                    this._radius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._radius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._radius_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRadiusAttribute((undefined as number | string | Array<number | string> | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: RectModifier): void {
        super.mergeModifier(modifier)
        if (modifier._radius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._radius_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.radius(modifier._radius_0_0value);
                    break;
                }
                default: {
                    this.radius((undefined as number | string | Array<number | string> | undefined));
                }
            }
        }
    }
    radius(value: number | string | Array<number | string> | undefined): this {
        if (((this._radius_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._radius_0_0value) !== (value)))
        {
            this._radius_0_flag = AttributeUpdaterFlag.UPDATE
            this._radius_0_0value = value
        } else
        {
            this._radius_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RectAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

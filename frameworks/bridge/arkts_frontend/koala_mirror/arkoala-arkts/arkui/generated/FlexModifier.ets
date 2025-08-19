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

import { CommonMethodModifier } from "./CommonMethodModifier"
import { AttributeModifier } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdater"
import { ArkFlexPeer, FlexAttribute } from "./component/flex"
import { CommonMethod, PointLightStyle } from "./component/common"
export class FlexModifier extends CommonMethodModifier implements FlexAttribute,AttributeModifier<FlexAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: FlexAttribute): void { }
    applyPressedAttribute(instance: FlexAttribute): void { }
    applyFocusedAttribute(instance: FlexAttribute): void { }
    applyDisabledAttribute(instance: FlexAttribute): void { }
    applySelectedAttribute(instance: FlexAttribute): void { }
    _pointLight_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _pointLight_0_0value?: PointLightStyle | undefined
    applyModifierPatch(peer: ArkFlexPeer): void {
        super.applyModifierPatch(peer)
        if (this._pointLight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._pointLight_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPointLightAttribute((this._pointLight_0_0value as PointLightStyle | undefined));
                    this._pointLight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._pointLight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._pointLight_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPointLightAttribute((undefined as PointLightStyle | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: FlexModifier): void {
        super.mergeModifier(modifier)
        if (modifier._pointLight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._pointLight_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.pointLight(modifier._pointLight_0_0value);
                    break;
                }
                default: {
                    this.pointLight((undefined as PointLightStyle | undefined));
                }
            }
        }
    }
    pointLight(value: PointLightStyle | undefined): this {
        if (((this._pointLight_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._pointLight_0_flag = AttributeUpdaterFlag.UPDATE
            this._pointLight_0_0value = value
        } else
        {
            this._pointLight_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<FlexAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

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
import { ArkStackPeer, StackAttribute } from "./component/stack"
import { CommonMethod, PointLightStyle } from "./component/common"
import { Alignment } from "./component/enums"
export class StackModifier extends CommonMethodModifier implements StackAttribute,AttributeModifier<StackAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: StackAttribute): void { }
    applyPressedAttribute(instance: StackAttribute): void { }
    applyFocusedAttribute(instance: StackAttribute): void { }
    applyDisabledAttribute(instance: StackAttribute): void { }
    applySelectedAttribute(instance: StackAttribute): void { }
    _alignContent_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _alignContent_0_0value?: Alignment | undefined
    _pointLight_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _pointLight_0_0value?: PointLightStyle | undefined
    applyModifierPatch(peer: ArkStackPeer): void {
        super.applyModifierPatch(peer)
        if (this._alignContent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._alignContent_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAlignContentAttribute((this._alignContent_0_0value as Alignment | undefined));
                    this._alignContent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._alignContent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._alignContent_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAlignContentAttribute((undefined as Alignment | undefined));
                }
            }
        }
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
    mergeModifier(modifier: StackModifier): void {
        super.mergeModifier(modifier)
        if (modifier._alignContent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._alignContent_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.alignContent(modifier._alignContent_0_0value);
                    break;
                }
                default: {
                    this.alignContent((undefined as Alignment | undefined));
                }
            }
        }
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
    alignContent(value: Alignment | undefined): this {
        if (((this._alignContent_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._alignContent_0_flag = AttributeUpdaterFlag.UPDATE
            this._alignContent_0_0value = value
        } else
        {
            this._alignContent_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
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
    public attributeModifier(value: AttributeModifier<StackAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

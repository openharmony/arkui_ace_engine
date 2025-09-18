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
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkCirclePeer, CircleAttribute } from "./component/circle"
import { int32 } from "@koalaui/common"
import { CommonShapeMethod, CommonMethod } from "./component/common"
export class CircleModifier extends CommonShapeMethodModifier implements CircleAttribute,AttributeModifier<CircleAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: Object): void { }
    applyPressedAttribute(instance: Object): void { }
    applyFocusedAttribute(instance: Object): void { }
    applyDisabledAttribute(instance: Object): void { }
    applySelectedAttribute(instance: Object): void { }
    applyModifierPatch(node: PeerNode): void {
        super.applyModifierPatch(node)
        const peer = node as ArkCirclePeer;
    }
    mergeModifier(modifier: CircleModifier): void {
        super.mergeModifier(modifier)
    }
    public attributeModifier(value: AttributeModifier<CircleAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

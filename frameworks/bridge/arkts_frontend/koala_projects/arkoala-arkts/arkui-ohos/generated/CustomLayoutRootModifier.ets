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

import { AttributeModifier } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkCustomLayoutRootPeer, Callback_onMeasureSize_SizeResult, Callback_onPlaceChildren_Void, CustomLayoutRoot } from "./component/idlize"
import { int32 } from "@koalaui/common"
import { GeometryInfo, Measurable, Layoutable } from "./component/common"
import { ConstraintSizeOptions } from "./component/units"
import { ModifierState } from "./CommonModifier"
export class CustomLayoutRootModifier implements CustomLayoutRoot,AttributeModifier<CustomLayoutRoot> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: CustomLayoutRoot): void { }
    applyPressedAttribute(instance: CustomLayoutRoot): void { }
    applyFocusedAttribute(instance: CustomLayoutRoot): void { }
    applyDisabledAttribute(instance: CustomLayoutRoot): void { }
    applySelectedAttribute(instance: CustomLayoutRoot): void { }
    _subscribeOnMeasureSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _subscribeOnMeasureSize_0_0value?: Callback_onMeasureSize_SizeResult
    _subscribeOnPlaceChildren_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _subscribeOnPlaceChildren_0_0value?: Callback_onPlaceChildren_Void
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        const peer = node as ArkCustomLayoutRootPeer;
    }
    mergeModifier(modifier: CustomLayoutRootModifier): void {
        this._state = modifier._state;
    }
    subscribeOnMeasureSize(value: Callback_onMeasureSize_SizeResult): this {
        throw new Error("Not implemented")
    }
    subscribeOnPlaceChildren(value: Callback_onPlaceChildren_Void): this {
        throw new Error("Not implemented")
    }
    public attributeModifier(value: AttributeModifier<CustomLayoutRoot> | undefined): this {
        throw new Error("Not implemented")
    }
}

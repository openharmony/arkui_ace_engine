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
import { ModifierState } from './CommonModifier'
import { AttributeModifier } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkArcScrollBarPeer } from "./@ohos.arkui.ArcScrollBar"
import { int32 } from "@koalaui/common"
import { CommonMethod } from "./component/common"
import { ArcScrollBarAttribute } from "@ohos.arkui.ArcScrollBar"
export class ArcScrollBarModifier extends CommonMethodModifier implements ArcScrollBarAttribute,AttributeModifier<ArcScrollBarAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: ArcScrollBarAttribute): void { }
    applyPressedAttribute(instance: ArcScrollBarAttribute): void { }
    applyFocusedAttribute(instance: ArcScrollBarAttribute): void { }
    applyDisabledAttribute(instance: ArcScrollBarAttribute): void { }
    applySelectedAttribute(instance: ArcScrollBarAttribute): void { }
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkArcScrollBarPeer;
    }
    mergeModifier(modifier: ArcScrollBarModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
    }
    public attributeModifier(value: AttributeModifier<ArcScrollBarAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

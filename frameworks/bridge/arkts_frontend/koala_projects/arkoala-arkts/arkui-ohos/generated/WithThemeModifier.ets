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
import { ArkWithThemePeer, WithThemeAttribute } from "./component/withTheme"
import { int32 } from "@koalaui/common"
import { ModifierState } from './CommonModifier'
export class WithThemeModifier implements WithThemeAttribute,AttributeModifier<WithThemeAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: WithThemeAttribute): void { }
    applyPressedAttribute(instance: WithThemeAttribute): void { }
    applyFocusedAttribute(instance: WithThemeAttribute): void { }
    applyDisabledAttribute(instance: WithThemeAttribute): void { }
    applySelectedAttribute(instance: WithThemeAttribute): void { }
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        const peer = node as ArkWithThemePeer;
    }
    mergeModifier(modifier: WithThemeModifier): void {
    }
    public attributeModifier(value: AttributeModifier<WithThemeAttribute> | undefined): this {
        throw new Error("Not implemented")
    }
}

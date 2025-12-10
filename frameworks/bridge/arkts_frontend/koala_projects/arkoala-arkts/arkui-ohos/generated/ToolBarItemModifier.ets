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

import { AttributeModifier } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkToolBarItemPeer, ToolBarItemAttribute } from './component/toolbar'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
export class ToolBarItemModifier implements ToolBarItemAttribute,AttributeModifier<ToolBarItemAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState;
    _addr: ArrayBuffer = new ArrayBuffer(4096);
    _flagArray: Uint8Array = new Uint8Array(this._addr);
    constructor() {
        this._flagArray.fill(0);
    }
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: ToolBarItemAttribute): void { }
    applyPressedAttribute(instance: ToolBarItemAttribute): void { }
    applyFocusedAttribute(instance: ToolBarItemAttribute): void { }
    applyDisabledAttribute(instance: ToolBarItemAttribute): void { }
    applySelectedAttribute(instance: ToolBarItemAttribute): void { }
    applyModifierPatch(node: object): void {
        this._state.addRef()
        const peer = node as ArkToolBarItemPeer;
        const flagArray = this._flagArray;
    }
    mergeModifier(modifier: ToolBarItemModifier): void {
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
    }
    public attributeModifier(value: AttributeModifier<ToolBarItemAttribute> | undefined): this {
        throw new Error('Not implemented')
    }
}

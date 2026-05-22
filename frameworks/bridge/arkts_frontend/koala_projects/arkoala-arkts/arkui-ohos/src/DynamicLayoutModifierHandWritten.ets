/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

import { CommonMethodModifier } from './CommonMethodModifier'
import { AttributeModifier } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkDynamicLayoutPeer, DynamicLayoutAttribute } from '@ohos.arkui.components.ArkDynamicLayout'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod } from './component/common'
export class DynamicLayoutModifier extends CommonMethodModifier
    implements DynamicLayoutAttribute, AttributeModifier<DynamicLayoutAttribute> {
    public dynamicLayoutAddr: ArrayBuffer = new ArrayBuffer(4096);
    public dynamicLayoutFlagArray: Uint8Array = new Uint8Array(this.dynamicLayoutAddr);
    constructor() {
        super();
        this.dynamicLayoutFlagArray.fill(0);
    }
    public isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: DynamicLayoutAttribute): void { }
    applyPressedAttribute(instance: DynamicLayoutAttribute): void { }
    applyFocusedAttribute(instance: DynamicLayoutAttribute): void { }
    applyDisabledAttribute(instance: DynamicLayoutAttribute): void { }
    applySelectedAttribute(instance: DynamicLayoutAttribute): void { }
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkDynamicLayoutPeer;
        const flagArray = this.dynamicLayoutFlagArray;
    }
    mergeModifier(modifier: DynamicLayoutModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier.dynamicLayoutFlagArray;
    }
    public attributeModifier(
        value: AttributeModifier<DynamicLayoutAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

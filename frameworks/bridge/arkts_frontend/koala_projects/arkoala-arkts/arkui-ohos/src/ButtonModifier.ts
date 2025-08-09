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

import { AttributeModifier } from 'arkui/component/common'
import { ButtonAttribute } from 'arkui/component/button'
import { AttributeUpdaterFlag, CommonMethodModifier } from './CommonMethodModifier';
import { Length } from './component/units';
import { PeerNode } from './PeerNode';
import { ArkButtonPeer } from './component/button';
import { InteropNativeModule } from "@koalaui/interop"

export class ButtonModifier extends CommonMethodModifier implements ButtonAttribute, AttributeModifier<ButtonAttribute> {
    applyNormalAttribute(instance: ButtonAttribute): void { }
    applyPressedAttribute(instance: ButtonAttribute): void { }
    applyFocusedAttribute(instance: ButtonAttribute): void { }
    applyDisabledAttribute(instance: ButtonAttribute): void { }
    applySelectedAttribute(instance: ButtonAttribute): void { }
    _fontSize_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontSize0_value?: Length | undefined
    public fontSize(value: Length | undefined): this {
        if (this._fontSize_flag === AttributeUpdaterFlag.INITIAL || this._fontSize0_value !== value || !Type.of(value).isPrimitive()) {
            this._fontSize0_value = value
            this._fontSize_flag = AttributeUpdaterFlag.UPDATE
        } else {
            this._fontSize_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    applyModifierPatch(value: PeerNode): void {
        super.applyModifierPatch(value)
        const peerNode: ArkButtonPeer = value as ArkButtonPeer
        if (this._fontSize_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._fontSize_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peerNode.fontColorAttribute((this._fontSize0_value as Length | undefined))
                    this._fontSize_flag = AttributeUpdaterFlag.RESET
                    break
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontSize_flag = AttributeUpdaterFlag.RESET
                    break
                }
                default: {
                    this._fontSize_flag = AttributeUpdaterFlag.INITIAL
                    peerNode.fontColorAttribute(undefined)
                }
            }
        }
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
        if (value instanceof ButtonModifier) {
            const buttonModifier = value as ButtonModifier;
            if (buttonModifier._fontSize_flag != AttributeUpdaterFlag.INITIAL) {
                switch (buttonModifier._fontSize_flag) {
                    case AttributeUpdaterFlag.UPDATE:
                    case AttributeUpdaterFlag.SKIP: {
                        this.fontSize(buttonModifier._fontSize0_value)
                        break
                    }
                    default: {
                        this.fontSize(undefined)
                    }
                }
            }
        }
    }
}
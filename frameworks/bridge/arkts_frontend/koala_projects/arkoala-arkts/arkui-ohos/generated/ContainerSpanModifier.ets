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
import { ArkContainerSpanPeer, ContainerSpanAttribute } from "./component/containerSpan"
import { int32 } from "@koalaui/common"
import { TextBackgroundStyle } from "./component/span"
import { ModifierState } from "./CommonModifier"
export class ContainerSpanModifier implements ContainerSpanAttribute,AttributeModifier<ContainerSpanAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: ContainerSpanAttribute): void { }
    applyPressedAttribute(instance: ContainerSpanAttribute): void { }
    applyFocusedAttribute(instance: ContainerSpanAttribute): void { }
    applyDisabledAttribute(instance: ContainerSpanAttribute): void { }
    applySelectedAttribute(instance: ContainerSpanAttribute): void { }
    _textBackgroundStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textBackgroundStyle_0_0value?: TextBackgroundStyle | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        const peer = node as ArkContainerSpanPeer;
        if (this._textBackgroundStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._textBackgroundStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTextBackgroundStyleAttribute((this._textBackgroundStyle_0_0value as TextBackgroundStyle | undefined));
                    this._textBackgroundStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._textBackgroundStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._textBackgroundStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTextBackgroundStyleAttribute((undefined as TextBackgroundStyle | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: ContainerSpanModifier): void {
        this._state = modifier._state;
        if (modifier._textBackgroundStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._textBackgroundStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.textBackgroundStyle(modifier._textBackgroundStyle_0_0value);
                    break;
                }
                default: {
                    this.textBackgroundStyle((undefined as TextBackgroundStyle | undefined));
                }
            }
        }
    }
    textBackgroundStyle(value: TextBackgroundStyle | undefined): this {
        if (((this._textBackgroundStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._textBackgroundStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._textBackgroundStyle_0_0value = value
            this._state.fireChange()
        } else
        {
            this._textBackgroundStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ContainerSpanAttribute> | undefined): this {
        throw new Error("Not implemented")
    }
}

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
import { ArkRichTextPeer, RichTextAttribute } from "./component/richText"
import { int32 } from "@koalaui/common"
import { CommonMethod } from "./component/common"
export class RichTextModifier extends CommonMethodModifier implements RichTextAttribute,AttributeModifier<RichTextAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: RichTextAttribute): void { }
    applyPressedAttribute(instance: RichTextAttribute): void { }
    applyFocusedAttribute(instance: RichTextAttribute): void { }
    applyDisabledAttribute(instance: RichTextAttribute): void { }
    applySelectedAttribute(instance: RichTextAttribute): void { }
    _onStart_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onStart_0_0value?: (() => void) | undefined
    _onComplete_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onComplete_0_0value?: (() => void) | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkRichTextPeer;
        if (this._onStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnStartAttribute((this._onStart_0_0value as (() => void) | undefined));
                    this._onStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onStart_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnStartAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onComplete_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onComplete_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnCompleteAttribute((this._onComplete_0_0value as (() => void) | undefined));
                    this._onComplete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onComplete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onComplete_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnCompleteAttribute((undefined as (() => void) | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: RichTextModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._onStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onStart(modifier._onStart_0_0value);
                    break;
                }
                default: {
                    this.onStart((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onComplete_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onComplete_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onComplete(modifier._onComplete_0_0value);
                    break;
                }
                default: {
                    this.onComplete((undefined as (() => void) | undefined));
                }
            }
        }
    }
    onStart(value: (() => void) | undefined): this {
        if (((this._onStart_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onStart_0_flag = AttributeUpdaterFlag.UPDATE
            this._onStart_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onStart_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onComplete(value: (() => void) | undefined): this {
        if (((this._onComplete_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onComplete_0_flag = AttributeUpdaterFlag.UPDATE
            this._onComplete_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onComplete_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RichTextAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

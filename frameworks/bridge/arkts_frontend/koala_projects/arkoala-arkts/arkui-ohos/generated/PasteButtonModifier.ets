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

import { SecurityComponentMethodModifier } from "./SecurityComponentMethodModifier"
import { ModifierState } from './CommonModifier'
import { AttributeModifier, extractors } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkPasteButtonPeer, PasteButtonCallback, PasteButtonOnClickResult, PasteButtonAttribute } from "./component/pasteButton"
import { int32 } from "@koalaui/common"
import { SecurityComponentMethod } from "./component/securityComponent"
import { ClickEvent } from "./component/common"
import { BusinessError } from "@ohos.base"
export class PasteButtonModifier extends SecurityComponentMethodModifier implements PasteButtonAttribute,AttributeModifier<PasteButtonAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: PasteButtonAttribute): void { }
    applyPressedAttribute(instance: PasteButtonAttribute): void { }
    applyFocusedAttribute(instance: PasteButtonAttribute): void { }
    applyDisabledAttribute(instance: PasteButtonAttribute): void { }
    applySelectedAttribute(instance: PasteButtonAttribute): void { }
    _onClick_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onClick_0_0value?: PasteButtonCallback | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkPasteButtonPeer;
        if (this._onClick_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onClick_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnClickAttribute((this._onClick_0_0value as PasteButtonCallback | undefined));
                    this._onClick_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onClick_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onClick_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnClickAttribute((undefined as PasteButtonCallback | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: PasteButtonModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._onClick_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onClick_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onClick(modifier._onClick_0_0value);
                    break;
                }
                default: {
                    this.onClick((undefined as PasteButtonCallback | undefined));
                }
            }
        }
    }
    onClick(value: PasteButtonCallback | undefined): this {
        if (((this._onClick_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onClick_0_flag = AttributeUpdaterFlag.UPDATE
            this._onClick_0_0value = value
        } else
        {
            this._onClick_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<PasteButtonAttribute> | AttributeModifier<SecurityComponentMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

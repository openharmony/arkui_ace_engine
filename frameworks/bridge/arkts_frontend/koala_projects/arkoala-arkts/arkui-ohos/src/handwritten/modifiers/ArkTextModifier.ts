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

import { int32 } from "@koalaui/common"
import { AttributeModifier, TextAttribute, TextAlign } from "../..";
import { ArkTextPeer } from "../../generated/peers/ArkTextPeer";
import { ArkCommonMethodPeer } from "../../generated/peers/ArkCommonPeer";
import { ArkCommonAttributeSet, modifierNullWithKey, modifierWithKey, ModifierWithKey } from "./ArkCommonModifier";

class TextAlignModifier extends ModifierWithKey<int32> {
    static identity: string = 'textAlign';

    constructor(value: int32) {
        super(value)
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let textPeerNode = node as ArkTextPeer
        if (reset) {
            // textPeerNode.resetTextAlignAttribute();
        } else {
            if (this.value! === 1) {
                textPeerNode.textAlignAttribute(TextAlign.Start);
            } else if (this.value! === 0) {
                textPeerNode.textAlignAttribute(TextAlign.Center);
            } else if (this.value! === 2) {
                textPeerNode.textAlignAttribute(TextAlign.End);
            } else {
                textPeerNode.textAlignAttribute(TextAlign.JUSTIFY);
            }
        }
    }

    static factory(value: int32): TextAlignModifier {
        return new TextAlignModifier(value)
    }
}

export class ArkTextAttributeSet extends ArkCommonAttributeSet /* implements TextAttribute */ {
    textAlign(value: TextAlign | undefined): this {
        if (value) {
            modifierWithKey(this._modifiersWithKeys, TextAlignModifier.identity, TextAlignModifier.factory, value as TextAlign as int32);
        } else {
            modifierNullWithKey(this._modifiersWithKeys, TextAlignModifier.identity);
        }
        return this;
    }
}

export class TextModifier extends ArkTextAttributeSet implements AttributeModifier<TextAttribute> {
   
    applyNormalAttribute(instance: TextAttribute) : void {}
 
    applyPressedAttribute(instance: TextAttribute) : void {}
  
    applyFocusedAttribute(instance: TextAttribute) : void {}
 
    applyDisabledAttribute(instance: TextAttribute) : void {}

    applySelectedAttribute(instance: TextAttribute) : void {}
}
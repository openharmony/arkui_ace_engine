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
import { AttributeModifier, StackAttribute, Alignment } from "../..";
import { ArkStackPeer } from "../../generated/peers/ArkStackPeer";
import { ArkCommonMethodPeer } from "../../generated/peers/ArkCommonPeer";
import { ArkCommonAttributeSet, modifierNullWithKey, modifierWithKey, ModifierWithKey } from "./ArkCommonModifier";

class AlignContentModifier extends ModifierWithKey<Alignment | undefined> {
    static identity: string = 'alignContent';

    constructor(value: Alignment | undefined) {
        super(value)
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let stackPeerNode = node as ArkStackPeer
        if (reset) {
        } else {
            if (this.value != undefined) {
                stackPeerNode.alignContentAttribute(this.value as Alignment);
            }
        }
    }

    static factory(value: Alignment | undefined): AlignContentModifier {
        if (value) {
            return new AlignContentModifier(value)
        }
        else {
            return new AlignContentModifier(undefined);
        }
    }
}

export class ArkStackAttributeSet extends ArkCommonAttributeSet implements StackAttribute {
    
    alignContent(value: Alignment|undefined): this {
        modifierWithKey(this._modifiersWithKeys, AlignContentModifier.identity, AlignContentModifier.factory, value);
        return this;
    }
}

export class StackModifier extends ArkStackAttributeSet implements AttributeModifier<StackAttribute> {
    applyNormalAttribute(instance: StackAttribute) { this.alignContent(Alignment.End); }
    applyPressedAttribute(instance: StackAttribute) {}
    applyFocusedAttribute(instance: StackAttribute){}
    applyDisabledAttribute(instance: StackAttribute){}
    applySelectedAttribute(instance: StackAttribute){}
}
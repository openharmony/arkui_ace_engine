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
import { AttributeModifier, RowAttribute, VerticalAlign } from "../..";
import { ArkRowPeer } from "../../generated/peers/ArkRowPeer";
import { ArkCommonMethodPeer } from "../../generated/peers/ArkCommonPeer";
import { ArkCommonAttributeSet, modifierNullWithKey, modifierWithKey, ModifierWithKey } from "./ArkCommonModifier";

class AlignItemsModifier extends ModifierWithKey<VerticalAlign | undefined> {
    static identity: string = 'alignItems';

    constructor(value: VerticalAlign | undefined) {
        super(value)
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let rowPeerNode = node as ArkRowPeer
        if (reset) {
            // rowPeerNode.resetAlignItemsAttribute();
        } else {
            if (this.value != undefined) {
                rowPeerNode.alignItemsAttribute(this.value as VerticalAlign);
            }
        }
    }

    static factory(value: VerticalAlign | undefined): AlignItemsModifier {
        if (value) {
            return new AlignItemsModifier(value)
        }
        else {
            return new AlignItemsModifier(undefined);
        }
    }
}

export class ArkRowAttributeSet extends ArkCommonAttributeSet implements RowAttribute {
    
    alignItems(value: VerticalAlign|undefined): this {
        modifierWithKey(this._modifiersWithKeys, AlignItemsModifier.identity, AlignItemsModifier.factory, value);
        return this;
    }
}

export class RowModifier extends ArkRowAttributeSet implements AttributeModifier<RowAttribute> {
    applyNormalAttribute(instance: RowAttribute) { this.alignItems(VerticalAlign.Bottom); }
    applyPressedAttribute(instance: RowAttribute) {}
    applyFocusedAttribute(instance: RowAttribute){}
    applyDisabledAttribute(instance: RowAttribute){}
    applySelectedAttribute(instance: RowAttribute){}
}
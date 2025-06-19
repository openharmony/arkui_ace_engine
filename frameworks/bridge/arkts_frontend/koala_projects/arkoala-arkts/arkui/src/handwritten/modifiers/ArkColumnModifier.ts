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
import { AttributeModifier, ColumnAttribute, HorizontalAlign } from "../..";
import { ArkColumnPeer } from "../../generated/peers/ArkColumnPeer";
import { ArkCommonMethodPeer } from "../../generated/peers/ArkCommonPeer";
import { ArkCommonAttributeSet, modifierNullWithKey, modifierWithKey, ModifierWithKey } from "./ArkCommonModifier";

class AlignItemsModifier extends ModifierWithKey<HorizontalAlign | undefined> {
    static identity: string = 'alignItems';

    constructor(value: HorizontalAlign | undefined) {
        super(value)
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let columnPeerNode = node as ArkColumnPeer
        if (reset) {
            // columnPeerNode.resetAlignItemsAttribute();
        } else {
            if (this.value != undefined) {
                columnPeerNode.alignItemsAttribute(this.value as HorizontalAlign);
            }
        }
    }

    static factory(value: HorizontalAlign | undefined): AlignItemsModifier {
        if (value) {
            return new AlignItemsModifier(value)
        }
        else {
            return new AlignItemsModifier(undefined);
        }
    }
}

export class ArkColumnAttributeSet extends ArkCommonAttributeSet implements ColumnAttribute {
    
    alignItems(value: HorizontalAlign|undefined): this {
        modifierWithKey(this._modifiersWithKeys, AlignItemsModifier.identity, AlignItemsModifier.factory, value);
        return this;
    }
}

export class ColumnModifier extends ArkColumnAttributeSet implements AttributeModifier<ColumnAttribute> {
    applyNormalAttribute(instance: ColumnAttribute) { this.alignItems(HorizontalAlign.End); }
    applyPressedAttribute(instance: ColumnAttribute) {}
    applyFocusedAttribute(instance: ColumnAttribute){}
    applyDisabledAttribute(instance: ColumnAttribute){}
    applySelectedAttribute(instance: ColumnAttribute){}
}
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

import { ArkBlankPeer, ArkCommonMethodPeer, AttributeModifier, ResourceColor, BlankAttribute, TextShadowStyleInternal } from './component';
import { ArkCommonAttributeSet, modifierWithKey, ModifierWithKey } from './handwritten/modifiers/ArkCommonModifier';

class ColorModifier extends ModifierWithKey<ResourceColor | undefined> {
    static identity: string = 'color';

    constructor(value: ResourceColor | undefined) {
        super(value);
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let colorPeerNode = node as ArkBlankPeer;
        if (reset) {
            // now do nothing
        } else {
            if (this.value !== undefined) {
                colorPeerNode.colorAttribute(this.value as ResourceColor);
            }
        }
    }

    static factory(value: ResourceColor | undefined): ColorModifier {
        return new ColorModifier(value);
    }
}

export class ArkBlankAttributeSet extends ArkCommonAttributeSet implements BlankAttribute {
    color(value: ResourceColor | undefined): this {
        modifierWithKey(this._modifiersWithKeys, ColorModifier.identity, ColorModifier.factory, value);
        return this;
    }
}

export class BlankModifier implements AttributeModifier<BlankAttribute> {
    attributeSet: ArkBlankAttributeSet = new ArkBlankAttributeSet();

    applyNormalAttribute(instance: BlankAttribute): void {}
    applyPressedAttribute(instance: BlankAttribute): void {}
    applyFocusedAttribute(instance: BlankAttribute): void {}
    applyDisabledAttribute(instance: BlankAttribute): void {}
    applySelectedAttribute(instance: BlankAttribute): void {}

    color(value: ResourceColor | undefined): this {
        this.attributeSet.color(value);
        return this;
    }
}
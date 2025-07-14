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

import { ArkRowSplitPeer, ArkCommonMethodPeer, AttributeModifier, RowSplitAttribute } from './component';
import { ArkCommonAttributeSet, modifierWithKey, ModifierWithKey } from './handwritten/modifiers/ArkCommonModifier';

class ResizeableModifier extends ModifierWithKey<boolean | undefined> {
    static identity: string = 'resizeable';

    constructor(value: boolean | undefined) {
        super(value);
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let resizeableNode = node as ArkRowSplitPeer;
        if (reset) {
            // now do nothing
        } else if (this.value !== undefined) {
            resizeableNode.resizeableAttribute(this.value as boolean);
        }
    }

    static factory(value: boolean | undefined): ResizeableModifier {
        return new ResizeableModifier(value);
    }
}

export class ArkRowSplitAttributeSet extends ArkCommonAttributeSet implements RowSplitAttribute {
    resizeable(value: boolean | undefined): this {
        modifierWithKey(this._modifiersWithKeys, ResizeableModifier.identity, ResizeableModifier.factory, value);
        return this;
    }
}

export class RowSplitModifier implements AttributeModifier<RowSplitAttribute> {
    attributeSet: ArkRowSplitAttributeSet = new ArkRowSplitAttributeSet();

    applyNormalAttribute(instance: RowSplitAttribute): void {}
    applyPressedAttribute(instance: RowSplitAttribute): void {}
    applyFocusedAttribute(instance: RowSplitAttribute): void {}
    applyDisabledAttribute(instance: RowSplitAttribute): void {}
    applySelectedAttribute(instance: RowSplitAttribute): void {}

    resizeable(value: boolean | undefined): this {
        this.attributeSet.resizeable(value);
        return this;
    }
}

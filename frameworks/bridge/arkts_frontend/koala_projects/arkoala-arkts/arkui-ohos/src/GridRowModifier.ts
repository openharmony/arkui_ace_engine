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

import { ArkGridRowPeer, ArkCommonMethodPeer, AttributeModifier, GridRowAttribute } from './component';
import { ArkCommonAttributeSet, modifierWithKey, ModifierWithKey } from './handwritten/modifiers/ArkCommonModifier';
import { ItemAlign } from './component/enums';

class OnBreakpointChangeModifier extends ModifierWithKey<((breakpoints: string) => void) | undefined> {
    static identity: string = 'onBreakpointChange';

    constructor(value: ((breakpoints: string) => void) | undefined) {
        super(value);
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let onBreakpointChangeNode = node as ArkGridRowPeer;
        if (reset) {
            // now do nothing
        } else {
            if (this.value !== undefined) {
                onBreakpointChangeNode.onBreakpointChangeAttribute(this.value as ((breakpoints: string) => void));
            }
        }
    }

    static factory(value: ((breakpoints: string) => void) | undefined): OnBreakpointChangeModifier {
        return new OnBreakpointChangeModifier(value);
    }
}

class AlignItemsModifier extends ModifierWithKey<ItemAlign | undefined> {
    static identity: string = 'alignItems';

    constructor(value: ItemAlign | undefined) {
        super(value);
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let alignItemsNode = node as ArkGridRowPeer;
        if (reset) {
            // now do nothing
        } else {
            if (this.value !== undefined) {
                alignItemsNode.alignItemsAttribute(this.value as ItemAlign);
            }
        }
    }

    static factory(value: ItemAlign | undefined): AlignItemsModifier {
        return new AlignItemsModifier(value);
    }
}

export class ArkGridRowAttributeSet extends ArkCommonAttributeSet implements GridRowAttribute {
    onBreakpointChange(value: ((breakpoints: string) => void) | undefined): this {
        modifierWithKey(this._modifiersWithKeys, OnBreakpointChangeModifier.identity, OnBreakpointChangeModifier.factory, value);
        return this;
    }

    alignItems(value: ItemAlign | undefined): this {
        modifierWithKey(this._modifiersWithKeys, AlignItemsModifier.identity, AlignItemsModifier.factory, value);
        return this;
    }
}

export class GridRowModifier implements AttributeModifier<GridRowAttribute> {
    attributeSet: ArkGridRowAttributeSet = new ArkGridRowAttributeSet();

    applyNormalAttribute(instance: GridRowAttribute): void {}
    applyPressedAttribute(instance: GridRowAttribute): void {}
    applyFocusedAttribute(instance: GridRowAttribute): void {}
    applyDisabledAttribute(instance: GridRowAttribute): void {}
    applySelectedAttribute(instance: GridRowAttribute): void {}

    onBreakpointChange(value: ((breakpoints: string) => void) | undefined): this {
        this.attributeSet.onBreakpointChange(value);
        return this;
    }

    alignItems(value: ItemAlign | undefined): this {
        this.attributeSet.alignItems(value);
        return this;
    }
}

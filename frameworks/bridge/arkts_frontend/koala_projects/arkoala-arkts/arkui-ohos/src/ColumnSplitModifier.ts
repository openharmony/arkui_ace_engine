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

import { ArkColumnSplitPeer, ArkCommonMethodPeer, AttributeModifier, ColumnSplitAttribute, ColumnSplitDividerStyle } from './component';
import { ArkCommonAttributeSet, modifierWithKey, ModifierWithKey } from './handwritten/modifiers/ArkCommonModifier';

class ResizeableModifier extends ModifierWithKey<boolean | undefined> {
    static identity: string = 'resizeable';

    constructor(value: boolean | undefined) {
        super(value);
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let resizeableNode = node as ArkColumnSplitPeer;
        if (reset) {
            // now do nothing
        } else {
            if (this.value !== undefined) {
                resizeableNode.resizeableAttribute(this.value as boolean);
            }
        }
    }

    static factory(value: boolean | undefined): ResizeableModifier {
        return new ResizeableModifier(value);
    }
}

class DividerModifier extends ModifierWithKey<ColumnSplitDividerStyle | null | undefined> {
    static identity: string = 'divider';

    constructor(value: ColumnSplitDividerStyle | null | undefined) {
        super(value);
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let dividerNode = node as ArkColumnSplitPeer;
        if (reset) {
            // now do nothing
        } else {
            if (this.value !== undefined) {
                dividerNode.dividerAttribute(this.value as ColumnSplitDividerStyle);
            }
        }
    }

    static factory(value: ColumnSplitDividerStyle | null | undefined) {
        return new DividerModifier(value);
    }
}

export class ArkColumnSplitAttributeSet extends ArkCommonAttributeSet implements ColumnSplitAttribute {
    resizeable(value: boolean | undefined): this {
        modifierWithKey(this._modifiersWithKeys, ResizeableModifier.identity, ResizeableModifier.factory, value);
        return this;
    }

    divider(value: ColumnSplitDividerStyle | null | undefined): this {
        modifierWithKey(this._modifiersWithKeys, DividerModifier.identity, DividerModifier.factory, value);
        return this;
    }
}

export class ColumnSplitModifier implements AttributeModifier<ColumnSplitAttribute> {
    attributeSet: ArkColumnSplitAttributeSet = new ArkColumnSplitAttributeSet();

    applyNormalAttribute(instance: ColumnSplitAttribute): void {}
    applyPressedAttribute(instance: ColumnSplitAttribute): void {}
    applyFocusedAttribute(instance: ColumnSplitAttribute): void {}
    applyDisabledAttribute(instance: ColumnSplitAttribute): void {}
    applySelectedAttribute(instance: ColumnSplitAttribute): void {}

    resizeable(value: boolean | undefined): this {
        this.attributeSet.resizeable(value);
        return this;
    }

    divider(value: ColumnSplitDividerStyle | null | undefined): this {
        this.attributeSet.divider(value);
        return this;
    }
}


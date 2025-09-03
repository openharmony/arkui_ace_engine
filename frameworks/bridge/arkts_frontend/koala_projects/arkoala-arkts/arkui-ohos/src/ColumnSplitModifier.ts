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

import { AttributeModifier, ColumnSplitAttribute, ColumnSplitDividerStyle } from './component';
import { CommonMethodModifier } from './CommonMethodModifier';
import { PeerNode } from './PeerNode';
 
export class ColumnSplitModifier extends CommonMethodModifier implements ColumnSplitAttribute,AttributeModifier<ColumnSplitAttribute> {
    applyNormalAttribute(instance: ColumnSplitAttribute): void {}
    applyPressedAttribute(instance: ColumnSplitAttribute): void {}
    applyFocusedAttribute(instance: ColumnSplitAttribute): void {}
    applyDisabledAttribute(instance: ColumnSplitAttribute): void {}
    applySelectedAttribute(instance: ColumnSplitAttribute): void {}

    applyModifierPatch(value: PeerNode): void {
        super.applyModifierPatch(value)
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
    }

    resizeable(value: boolean | undefined): this {
        return this;
    }

    divider(value: ColumnSplitDividerStyle | null | undefined): this {
        return this;
    }
}
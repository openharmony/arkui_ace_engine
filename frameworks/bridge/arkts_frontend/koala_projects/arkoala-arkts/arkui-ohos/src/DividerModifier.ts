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

import { ArkDividerPeer, ArkCommonMethodPeer, AttributeModifier, ResourceColor, DividerAttribute, LineCapStyle } from './component';
import { ArkCommonAttributeSet, modifierWithKey, ModifierWithKey } from './handwritten/modifiers/ArkCommonModifier';
import { AttributeUpdaterFlag, CommonMethodModifier } from './CommonMethodModifier';
import { Length } from './component/units';
import { PeerNode } from './PeerNode';

export class DividerModifier extends CommonMethodModifier implements DividerAttribute, AttributeModifier<DividerAttribute> {
    applyNormalAttribute(instance: DividerAttribute): void {}
    applyPressedAttribute(instance: DividerAttribute): void {}
    applyFocusedAttribute(instance: DividerAttribute): void {}
    applyDisabledAttribute(instance: DividerAttribute): void {}
    applySelectedAttribute(instance: DividerAttribute): void {}

    applyModifierPatch(value: PeerNode): void {
        super.applyModifierPatch(value)
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
    }

    color(value: ResourceColor | undefined): this {
        return this;
    }

    strokeWidth(value: string | number | undefined): this {
        return this;
    }

    vertical(value: boolean | undefined): this {
        return this;
    }

    lineCap(value: LineCapStyle | undefined): this {
        return this;
    }
}
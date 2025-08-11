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

import { ArkStackPeer, ArkCommonMethodPeer, AttributeModifier, Alignment, PointLightStyle, StackAttribute } from './component';
import { ArkCommonAttributeSet, modifierWithKey, ModifierWithKey } from './handwritten/modifiers/ArkCommonModifier';
import { CommonMethodModifier } from "./CommonMethodModifier"
import { PeerNode } from './PeerNode';

export class StackModifier extends CommonMethodModifier implements StackAttribute, AttributeModifier<StackAttribute> {
    applyNormalAttribute(instance: StackAttribute): void {}
    applyPressedAttribute(instance: StackAttribute): void {}
    applyFocusedAttribute(instance: StackAttribute): void {}
    applyDisabledAttribute(instance: StackAttribute): void {}
    applySelectedAttribute(instance: StackAttribute): void {}

    applyModifierPatch(value: PeerNode): void {
        super.applyModifierPatch(value)
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
    }

    alignContent(value: Alignment | undefined): this {
        return this;
    }

    pointLight(value: PointLightStyle | undefined): this {
        return this;
    }
}

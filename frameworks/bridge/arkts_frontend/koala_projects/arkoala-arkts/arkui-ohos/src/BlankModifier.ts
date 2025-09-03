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

import { AttributeModifier, ResourceColor, BlankAttribute } from './component';
import { PeerNode } from './PeerNode';
import { CommonMethodModifier } from './CommonMethodModifier';

export class BlankModifier extends CommonMethodModifier implements BlankAttribute, AttributeModifier<BlankAttribute> {

    applyNormalAttribute(instance: BlankAttribute): void {}
    applyPressedAttribute(instance: BlankAttribute): void {}
    applyFocusedAttribute(instance: BlankAttribute): void {}
    applyDisabledAttribute(instance: BlankAttribute): void {}
    applySelectedAttribute(instance: BlankAttribute): void {}

    applyModifierPatch(value: PeerNode): void {
        super.applyModifierPatch(value)
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
    }

    color(value: ResourceColor | undefined): this {
        return this;
    }
}
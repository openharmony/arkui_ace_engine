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

import { ArkFlexPeer, ArkCommonMethodPeer, AttributeModifier, PointLightStyle, FlexAttribute } from './component';
import { CommonMethodModifier } from './CommonMethodModifier';
import { PeerNode } from './PeerNode';

export class FlexModifier extends CommonMethodModifier implements FlexAttribute, AttributeModifier<FlexAttribute> {
    applyNormalAttribute(instance: FlexAttribute): void {}
    applyPressedAttribute(instance: FlexAttribute): void {}
    applyFocusedAttribute(instance: FlexAttribute): void {}
    applyDisabledAttribute(instance: FlexAttribute): void {}
    applySelectedAttribute(instance: FlexAttribute): void {}

    applyModifierPatch(value: PeerNode): void {
        super.applyModifierPatch(value)
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
    }

    pointLight(value: PointLightStyle | undefined): this {
        return this;
    }
}
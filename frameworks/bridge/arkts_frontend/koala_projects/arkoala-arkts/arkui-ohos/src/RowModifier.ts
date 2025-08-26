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

import { ArkRowPeer, ArkCommonMethodPeer, AttributeModifier, VerticalAlign, FlexAlign, PointLightStyle, RowAttribute } from './component';
import { CommonMethodModifier } from "./CommonMethodModifier"
import { PeerNode } from './PeerNode';

export class RowModifier extends CommonMethodModifier implements RowAttribute, AttributeModifier<RowAttribute> {
    applyNormalAttribute(instance: RowAttribute): void {}
    applyPressedAttribute(instance: RowAttribute): void {}
    applyFocusedAttribute(instance: RowAttribute): void {}
    applyDisabledAttribute(instance: RowAttribute): void {}
    applySelectedAttribute(instance: RowAttribute): void {}

    applyModifierPatch(value: PeerNode): void {
        super.applyModifierPatch(value)
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
    }

    alignItems(value: VerticalAlign | undefined): this {
        return this;
    }

    justifyContent(value: FlexAlign | undefined): this {
        return this;
    }

    pointLight(value: PointLightStyle | undefined): this {
        return this;
    }

    reverse(value: boolean | undefined): this {
        return this;
    }
}

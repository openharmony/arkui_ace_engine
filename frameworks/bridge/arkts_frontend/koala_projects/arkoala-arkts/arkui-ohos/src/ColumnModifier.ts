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

import { ColumnAttribute, AttributeModifier, PointLightStyle, HorizontalAlign, FlexAlign } from './component';
import { CommonMethodModifier } from './CommonMethodModifier';
import { PeerNode } from './PeerNode';

export class ColumnModifier extends CommonMethodModifier implements ColumnAttribute, AttributeModifier<ColumnAttribute> {
    applyNormalAttribute(instance: ColumnAttribute): void {}
    applyPressedAttribute(instance: ColumnAttribute): void {}
    applyFocusedAttribute(instance: ColumnAttribute): void {}
    applyDisabledAttribute(instance: ColumnAttribute): void {}
    applySelectedAttribute(instance: ColumnAttribute): void {}

    applyModifierPatch(value: PeerNode): void {
        super.applyModifierPatch(value)
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
    }

    alignItems(value: HorizontalAlign | undefined): this {
        return this
    }
    justifyContent(value: FlexAlign | undefined): this {
        return this
    }
    pointLight(value: PointLightStyle | undefined): this {
        return this
    }
    reverse(value: boolean | undefined): this {
        return this
    }
}

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
import { CommonMethodModifier } from "./CommonMethodModifier"
import { ItemAlign } from './component/enums';
import { PeerNode } from './PeerNode';

export class GridRowModifier extends CommonMethodModifier implements GridRowAttribute,AttributeModifier<GridRowAttribute> {
    applyNormalAttribute(instance: GridRowAttribute): void {}
    applyPressedAttribute(instance: GridRowAttribute): void {}
    applyFocusedAttribute(instance: GridRowAttribute): void {}
    applyDisabledAttribute(instance: GridRowAttribute): void {}
    applySelectedAttribute(instance: GridRowAttribute): void {}

    applyModifierPatch(value: PeerNode): void {
        super.applyModifierPatch(value)
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
    }

    onBreakpointChange(value: ((breakpoints: string) => void) | undefined): this {
        return this;
    }

    alignItems(value: ItemAlign | undefined): this {
        return this;
    }
}

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

import { ArkGridColPeer, ArkCommonMethodPeer, AttributeModifier, GridColAttribute, GridColColumnOption } from './component';
import { CommonMethodModifier } from "./CommonMethodModifier"
import { PeerNode } from './PeerNode';

export class GridColModifier extends CommonMethodModifier implements GridColAttribute, AttributeModifier<GridColAttribute> {
    applyNormalAttribute(instance: GridColAttribute): void {}
    applyPressedAttribute(instance: GridColAttribute): void {}
    applyFocusedAttribute(instance: GridColAttribute): void {}
    applyDisabledAttribute(instance: GridColAttribute): void {}
    applySelectedAttribute(instance: GridColAttribute): void {}

    applyModifierPatch(value: PeerNode): void {
        super.applyModifierPatch(value)
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
    }

    span(value: number | GridColColumnOption | undefined): this {
        return this;
    }

    gridColOffset(value: number | GridColColumnOption | undefined): this {
        return this;
    }

    order(value: number | GridColColumnOption | undefined): this {
        return this;
    }
}

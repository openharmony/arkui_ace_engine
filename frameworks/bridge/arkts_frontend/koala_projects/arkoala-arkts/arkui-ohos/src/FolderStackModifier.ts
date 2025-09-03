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

import { ArkFolderStackPeer, ArkCommonMethodPeer, AttributeModifier, Alignment, PointLightStyle, FolderStackAttribute, HoverEventParam, OnFoldStatusChangeInfo } from './component';
import { CommonMethodModifier } from './CommonMethodModifier';
import { PeerNode } from './PeerNode';

type OnFoldStatusChangeCallback = (event: OnFoldStatusChangeInfo) => void;
type OnHoverStatusChangeCallback = (param: HoverEventParam) => void;

export class FolderStackModifier extends CommonMethodModifier implements FolderStackAttribute, AttributeModifier<FolderStackAttribute> {
    applyNormalAttribute(instance: FolderStackAttribute): void {}
    applyPressedAttribute(instance: FolderStackAttribute): void {}
    applyFocusedAttribute(instance: FolderStackAttribute): void {}
    applyDisabledAttribute(instance: FolderStackAttribute): void {}
    applySelectedAttribute(instance: FolderStackAttribute): void {}

    applyModifierPatch(value: PeerNode): void {
        super.applyModifierPatch(value)
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
    }

    alignContent(value: Alignment | undefined): this {
        return this;
    }
    onFolderStateChange(value: OnFoldStatusChangeCallback | undefined): this {
        return this;
    }
    onHoverStatusChange(value: OnHoverStatusChangeCallback | undefined): this {
        return this;
    }
    enableAnimation(value: boolean | undefined): this {
        return this;
    }
    autoHalfFold(value: boolean | undefined): this {
        return this;
    }
}
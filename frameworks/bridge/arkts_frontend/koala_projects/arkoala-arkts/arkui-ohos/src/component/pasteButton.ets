/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

import { memo, memo_skip } from 'arkui.stateManagement.runtime'
import { PasteButtonAttribute, ArkPasteButtonComponent, ArkPasteButtonPeer } from '#generated'
import { NodeAttach, remember } from '@koalaui/runtime'

@memo
export function PasteButtonImpl(
    @memo @memo_skip
    style: ((attributes: PasteButtonAttribute) => void) | undefined,
): void {
    const receiver = remember<ArkPasteButtonComponent>((): ArkPasteButtonComponent => {
        return new ArkPasteButtonComponent()
    })
    NodeAttach<ArkPasteButtonPeer>((): ArkPasteButtonPeer => ArkPasteButtonPeer.create(receiver), (_: ArkPasteButtonPeer): void => {
        style?.(receiver)
        receiver.applyAttributesFinish()
    })
}
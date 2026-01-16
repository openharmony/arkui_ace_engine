/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

// HANDWRITTEN, DO NOT REGENERATE

import { memo } from "@koalaui/runtime/annotations"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ToggleAttribute, ArkToggleComponent, ArkTogglePeer } from "#generated"
import { ComponentBase } from "./../ComponentBase"
import { ArkUIGeneratedNativeModule } from "#components"

function createTogglePeer(component?: ComponentBase, flags: int32 = 0): ArkTogglePeer {
    const peerId  = PeerNode.nextId()
    const _peer  = new ArkTogglePeer(nullptr, peerId, 'Toggle', flags)
    component?.setPeer(_peer)
    return _peer
}

@memo
export function ToggleImpl(
    @memo
    style: ((attributes: ToggleAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkToggleComponent>((): ArkToggleComponent => {
        return new ArkToggleComponent()
    })
    NodeAttach<ArkTogglePeer>((): ArkTogglePeer => createTogglePeer(receiver), (peer: ArkTogglePeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}
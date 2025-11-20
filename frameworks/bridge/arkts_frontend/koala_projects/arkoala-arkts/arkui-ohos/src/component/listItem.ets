/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
import { ListItemAttribute, ArkListItemComponent, ArkListItemPeer, LazyBuild } from "#generated"
import { LazyForEachType } from './../PeerNode';
import { pointer } from '@koalaui/interop'

@memo
export function ListItemImpl(
    @memo
    style: ((attributes: ListItemAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkListItemComponent>((): ArkListItemComponent => {
        return new ArkListItemComponent()
    })
    NodeAttach<ArkListItemPeer>((): ArkListItemPeer => {
        LazyBuild.ApplyLazyBuilder()
        return ArkListItemPeer.create(receiver)
    }, (peer: ArkListItemPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        const peerPtr : pointer = receiver.getPeer().getPeerPtr()
        const isInLazyForEach : undefined| Boolean = receiver.getPeer()?.parent?.isKind(LazyForEachType)
        receiver.setPeer(undefined)
        LazyBuild.SetListItemLazyBuilder(peerPtr, content_ ? content_! : @memo (): void => {})
    })
}

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
import { TabContentAttribute, ArkTabContentComponent, ArkTabContentPeer } from "#generated"

@memo
export function TabContentImpl(
    @memo
    style: ((attributes: TabContentAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkTabContentComponent>((): ArkTabContentComponent => {
        return new ArkTabContentComponent()
    })
    NodeAttach<ArkTabContentPeer>((): ArkTabContentPeer => ArkTabContentPeer.create(receiver), (peer: ArkTabContentPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}
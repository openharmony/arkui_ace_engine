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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { memo } from "@koalaui/runtime/annotations"
import { NodeAttach, remember } from "@koalaui/runtime"
import { BadgeAttribute, ArkBadgeComponent, ArkBadgePeer } from "#generated"

@memo
export function BadgeImpl(
    @memo
    style: ((attributes: BadgeAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkBadgeComponent>((): ArkBadgeComponent => {
        return new ArkBadgeComponent()
    })
    NodeAttach<ArkBadgePeer>((): ArkBadgePeer => ArkBadgePeer.create(receiver), (peer: ArkBadgePeer): void => {
        content_?.()
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
    })
}
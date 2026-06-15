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

import { int32 } from '@koalaui/common'
import { KPointer } from '@koalaui/interop'
import { ComponentBase } from './arkui/ComponentBase'
import { PeerNode } from './arkui/PeerNode'
import { NodeAttach, remember } from '@koalaui/runtime'
import { memo, memo_skip } from 'arkui.stateManagement.runtime'
import { ArkUIAniModule } from 'arkui.ani'
import { CustomEnvKey, WritableSystemEnvKey } from './arkui/stateManagement/decorator'

export class WithEnvPeer extends PeerNode {
    public constructor(peerPtr: KPointer, id: int32, name: string = 'WithEnv', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }

    public static create(component?: ComponentBase): WithEnvPeer {
        const peerId = PeerNode.nextId()
        const peerPtr = ArkUIAniModule._WithEnv_construct(peerId)
        const peer = new WithEnvPeer(peerPtr, peerId)
        component?.setPeer(peer)
        return peer
    }
}

export interface WithEnvAttribute {
    env<T>(key: WritableSystemEnvKey<T>, value: T): this {
        throw new Error('Unimplemented method env')
    }
    customEnv<T>(key: CustomEnvKey<T>, value: T): this {
        throw new Error('Unimplemented method customEnv')
    }
    setWithEnvOptions(): this {
        throw new Error('Unimplemented method setWithEnvOptions')
    }
    applyAttributesFinish(): void {
        throw new Error('Unimplemented method applyAttributesFinish')
    }
}

export class WithEnvComponent extends ComponentBase implements WithEnvAttribute {
    getPeer(): WithEnvPeer {
        return this.peer as WithEnvPeer
    }

    public env<T>(key: WritableSystemEnvKey<T>, value: T): this {
        const ptr = this.getPeer().peer.ptr
        ArkUIAniModule._WithEnv_setSystemEnvProperty(ptr, key.key, value as Any)
        return this
    }

    public customEnv<T>(key: CustomEnvKey<T>, value: T): this {
        const ptr = this.getPeer().peer.ptr
        ArkUIAniModule._WithEnv_setCustomEnvProperty(ptr, key.internalId, value as Any)
        return this
    }

    public setWithEnvOptions(): this {
        this.applyOptionsFinish('WithEnvAttribute')
        return this
    }

    public applyAttributesFinish(): void {
        super.applyAttributesFinish()
    }
}

@memo
export function WithEnvImpl(
    @memo @memo_skip
    style: ((attributes: WithEnvAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<WithEnvComponent>((): WithEnvComponent => {
        return new WithEnvComponent()
    })
    NodeAttach<WithEnvPeer>((): WithEnvPeer => WithEnvPeer.create(receiver), (_: WithEnvPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export type WithEnvInterface = (content_?: () => void) => WithEnvAttribute
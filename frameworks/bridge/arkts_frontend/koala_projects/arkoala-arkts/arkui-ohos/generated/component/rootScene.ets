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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { ArkThemeScopeManager } from '#arktheme'
import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkUIGeneratedNativeModule } from '#components'
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent } from './common'
import { AttributeModifier, hookRootSceneAttributeModifier, AttributeUpdater } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { RootSceneModifier } from './../RootSceneModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
export class ArkRootScenePeer extends ArkCommonMethodPeer {
    attributeSet?: RootSceneModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkRootScenePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._RootScene_construct(peerId, flags)
        const _peer  = new ArkRootScenePeer(_peerPtr, peerId, 'RootScene', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setRootSceneOptionsAttribute(session: RootSceneSession): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        RootSceneSession_serializer.write(thisSerializer, session)
        ArkUIGeneratedNativeModule._RootSceneInterface_setRootSceneOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface RootSceneSession {
}
export interface RootSceneAttribute extends CommonMethod {
    setRootSceneOptions(session: RootSceneSession): this {
        throw new Error('Unimplemented method setRootSceneOptions')
    }
    attributeModifier(value: AttributeModifier<RootSceneAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkRootSceneComponent extends ArkCommonMethodComponent implements RootSceneAttribute {
    getPeer(): ArkRootScenePeer {
        return (this.peer as ArkRootScenePeer)
    }
    public setRootSceneOptions(session: RootSceneSession): this {
        if (this.checkPriority('setRootSceneOptions')) {
            const session_casted = session as (RootSceneSession)
            this.getPeer()?.setRootSceneOptionsAttribute(session_casted)
            this.applyOptionsFinish('RootSceneAttribute');
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RootSceneAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookRootSceneAttributeModifier(this, value);
        })
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
    public applyOptionsFinish(traceName: string): void {
        super.applyOptionsFinish(traceName)
    }
}

@memo
export function RootSceneImpl(
    @memo @memo_skip
    style: ((attributes: RootSceneAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkRootSceneComponent>((): ArkRootSceneComponent => {
        return new ArkRootSceneComponent()
    })
    NodeAttach<ArkRootScenePeer>((): ArkRootScenePeer => ArkRootScenePeer.create(receiver), (_: ArkRootScenePeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class RootSceneSession_serializer {
    public static write(buffer: SerializerBase, value: RootSceneSession): void {
    }
    public static read(buffer: DeserializerBase): RootSceneSession {
        let value : RootSceneSession = ({} as RootSceneSession)
        return value
    }
}

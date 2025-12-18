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
import { AttributeModifier, hookRemoteWindowAttributeModifier, AttributeUpdater } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { RemoteWindowModifier } from './../RemoteWindowModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
export class ArkRemoteWindowPeer extends ArkCommonMethodPeer {
    attributeSet?: RemoteWindowModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkRemoteWindowPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._RemoteWindow_construct(peerId, flags)
        const _peer  = new ArkRemoteWindowPeer(_peerPtr, peerId, 'RemoteWindow', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setRemoteWindowOptionsAttribute(target: WindowAnimationTarget): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        WindowAnimationTarget_serializer.write(thisSerializer, target)
        ArkUIGeneratedNativeModule._RemoteWindowInterface_setRemoteWindowOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface RRect {
    left: double;
    top: double;
    width: double;
    height: double;
    radius: double;
}
export interface WindowAnimationTarget {
    readonly bundleName: string;
    readonly abilityName: string;
    readonly windowBounds: RRect;
    readonly missionId: int32;
}
export interface RemoteWindowAttribute extends CommonMethod {
    setRemoteWindowOptions(target: WindowAnimationTarget): this {
        throw new Error('Unimplemented method setRemoteWindowOptions')
    }
    attributeModifier(value: AttributeModifier<RemoteWindowAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkRemoteWindowComponent extends ArkCommonMethodComponent implements RemoteWindowAttribute {
    getPeer(): ArkRemoteWindowPeer {
        return (this.peer as ArkRemoteWindowPeer)
    }
    public setRemoteWindowOptions(target: WindowAnimationTarget): this {
        if (this.checkPriority('setRemoteWindowOptions')) {
            const target_casted = target as (WindowAnimationTarget)
            this.getPeer()?.setRemoteWindowOptionsAttribute(target_casted)
            this.applyOptionsFinish('RemoteWindowAttribute');
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RemoteWindowAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookRemoteWindowAttributeModifier(this, value);
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
export function RemoteWindowImpl(
    @memo @memo_skip
    style: ((attributes: RemoteWindowAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkRemoteWindowComponent>((): ArkRemoteWindowComponent => {
        return new ArkRemoteWindowComponent()
    })
    NodeAttach<ArkRemoteWindowPeer>((): ArkRemoteWindowPeer => ArkRemoteWindowPeer.create(receiver), (_: ArkRemoteWindowPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class RRect_serializer {
    public static write(buffer: SerializerBase, value: RRect): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForLeft  = value.left
        valueSerializer.writeFloat64(valueHolderForLeft)
        const valueHolderForTop  = value.top
        valueSerializer.writeFloat64(valueHolderForTop)
        const valueHolderForWidth  = value.width
        valueSerializer.writeFloat64(valueHolderForWidth)
        const valueHolderForHeight  = value.height
        valueSerializer.writeFloat64(valueHolderForHeight)
        const valueHolderForRadius  = value.radius
        valueSerializer.writeFloat64(valueHolderForRadius)
    }
    public static read(buffer: DeserializerBase): RRect {
        let valueDeserializer : DeserializerBase = buffer
        const leftTmpResult : double = valueDeserializer.readFloat64()
        const topTmpResult : double = valueDeserializer.readFloat64()
        const widthTmpResult : double = valueDeserializer.readFloat64()
        const heightTmpResult : double = valueDeserializer.readFloat64()
        const radiusTmpResult : double = valueDeserializer.readFloat64()
        let value : RRect = ({left: leftTmpResult, top: topTmpResult, width: widthTmpResult, height: heightTmpResult, radius: radiusTmpResult} as RRect)
        return value
    }
}
export class WindowAnimationTarget_serializer {
    public static write(buffer: SerializerBase, value: WindowAnimationTarget): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForBundleName  = value.bundleName
        valueSerializer.writeString(valueHolderForBundleName)
        const valueHolderForAbilityName  = value.abilityName
        valueSerializer.writeString(valueHolderForAbilityName)
        const valueHolderForWindowBounds  = value.windowBounds
        RRect_serializer.write(valueSerializer, valueHolderForWindowBounds)
        const valueHolderForMissionId  = value.missionId
        valueSerializer.writeInt32(valueHolderForMissionId)
    }
    public static read(buffer: DeserializerBase): WindowAnimationTarget {
        let valueDeserializer : DeserializerBase = buffer
        const bundleNameTmpResult : string = (valueDeserializer.readString() as string)
        const abilityNameTmpResult : string = (valueDeserializer.readString() as string)
        const windowBoundsTmpResult : RRect = RRect_serializer.read(valueDeserializer)
        const missionIdTmpResult : int32 = valueDeserializer.readInt32()
        let value : WindowAnimationTarget = ({bundleName: bundleNameTmpResult, abilityName: abilityNameTmpResult, windowBounds: windowBoundsTmpResult, missionId: missionIdTmpResult} as WindowAnimationTarget)
        return value
    }
}

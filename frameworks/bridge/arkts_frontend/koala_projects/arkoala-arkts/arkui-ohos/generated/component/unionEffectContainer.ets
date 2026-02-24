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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { ArkThemeScopeManager } from '#arktheme'
import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { PointLightStyle_serializer, ArkCommonMethodPeer, CommonMethod, PointLightStyle, ArkCommonMethodComponent } from './common'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkUIGeneratedNativeModule } from '#components'
import { AttributeModifier, hookUnionEffectContainerAttributeModifier, AttributeUpdater } from '#handwritten'
import { CustomBuilder } from './builder'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { UnionEffectContainerModifier } from './../UnionEffectContainerModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
export class ArkUnionEffectContainerPeer extends ArkCommonMethodPeer {
    attributeSet?: UnionEffectContainerModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkUnionEffectContainerPeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIGeneratedNativeModule._UnionEffectContainer_construct(peerId, flags)
        const _peer = new ArkUnionEffectContainerPeer(_peerPtr, peerId, 'UnionEffectContainer', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setUnionEffectContainerOptionsAttribute(options?: UnionEffectContainerOptions): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue = options!
            UnionEffectContainerOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._UnionEffectContainerInterface_setUnionEffectContainerOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPointLightAttribute(value: PointLightStyle): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        PointLightStyle_serializer.write(thisSerializer, value)
        ArkUIGeneratedNativeModule._UnionEffectContainerAttribute_setPointLight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface UnionEffectContainerOptions {
    spacing?: double;
}
export interface UnionEffectContainerAttribute extends CommonMethod {
    setUnionEffectContainerOptions(options?: UnionEffectContainerOptions): this {
        throw new Error('Unimplemented method setUnionEffectContainerOptions')
    }
    pointLight(value: PointLightStyle): this {
        throw new Error('Unimplemented method pointLight')
    }
    attributeModifier(value: AttributeModifier<UnionEffectContainerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkUnionEffectContainerComponent extends ArkCommonMethodComponent implements UnionEffectContainerAttribute {
    getPeer(): ArkUnionEffectContainerPeer {
        return (this.peer as ArkUnionEffectContainerPeer)
    }
    public setUnionEffectContainerOptions(options?: UnionEffectContainerOptions): this {
        const options_casted = options as (UnionEffectContainerOptions | undefined)
        this.getPeer()?.setUnionEffectContainerOptionsAttribute(options_casted)
        this.applyOptionsFinish('UnionEffectContainerAttribute');
        return this
    }
    public pointLight(value: PointLightStyle): this {
        const value_casted = value as (PointLightStyle)
        this.getPeer()?.setPointLightAttribute(value_casted)
        return this
    }
    public attributeModifier(value: AttributeModifier<UnionEffectContainerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookUnionEffectContainerAttributeModifier(this, value);
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
export function UnionEffectContainerImpl(
    @memo @memo_skip
    style: ((attributes: UnionEffectContainerAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkUnionEffectContainerComponent>((): ArkUnionEffectContainerComponent => {
        return new ArkUnionEffectContainerComponent()
    })
    NodeAttach<ArkUnionEffectContainerPeer>((): ArkUnionEffectContainerPeer => ArkUnionEffectContainerPeer.create(receiver), (_: ArkUnionEffectContainerPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class UnionEffectContainerOptions_serializer {
    public static write(buffer: SerializerBase, value: UnionEffectContainerOptions): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForSpacing = value.spacing
        if (valueHolderForSpacing !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSpacingTmpValue = valueHolderForSpacing!
            valueSerializer.writeFloat64(valueHolderForSpacingTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): UnionEffectContainerOptions {
        let valueDeserializer: DeserializerBase = buffer
        const spacingTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let spacingTmpBuf: double | undefined = undefined
        if ((spacingTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            spacingTmpBuf = valueDeserializer.readFloat64()
        }
        const spacingTmpResult: double | undefined = spacingTmpBuf
        let value: UnionEffectContainerOptions = ({spacing: spacingTmpResult} as UnionEffectContainerOptions)
        return value
    }
}

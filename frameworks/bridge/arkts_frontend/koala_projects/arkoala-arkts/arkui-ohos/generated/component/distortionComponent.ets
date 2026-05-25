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
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkUIGeneratedNativeModule } from '#components'
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent } from './common'
import { CustomBuilder } from './builder'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { Vector2, Vector4 } from 'arkui.Graphics'
import { DistortionComponentModifier } from './../DistortionComponentModifier'
import { hookDistortionComponentAttributeModifier, AttributeModifier, AttributeUpdater } from '#handwritten'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
import { Vector2_serializer, Vector4_serializer } from './../framework/Graphics'
export class ArkDistortionComponentPeer extends ArkCommonMethodPeer {
    distortionComponentAttributeSet?: DistortionComponentModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkDistortionComponentPeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIGeneratedNativeModule._DistortionComponent_construct(peerId, flags)
        const _peer = new ArkDistortionComponentPeer(_peerPtr, peerId, 'DistortionComponent', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setDistortionComponentOptionsAttribute(options?: DistortionComponentOptions): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue = options!
            DistortionComponentOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._DistortionComponentInterface_setDistortionComponentOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface DistortionParam {
    topLeft: Vector2;
    topRight: Vector2;
    bottomLeft: Vector2;
    bottomRight: Vector2;
    barrelDistortion: Vector4;
}
export interface DistortionComponentOptions {
    distortion?: DistortionParam;
}
export interface DistortionComponentAttribute extends CommonMethod {
    setDistortionComponentOptions(options?: DistortionComponentOptions): this {
        throw new Error('Unimplemented method setDistortionComponentOptions')
    }
    attributeModifier(value: AttributeModifier<DistortionComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkDistortionComponentComponent extends ArkCommonMethodComponent implements DistortionComponentAttribute {
    getPeer(): ArkDistortionComponentPeer {
        return (this.peer as ArkDistortionComponentPeer)
    }
    public setDistortionComponentOptions(options?: DistortionComponentOptions): this {
        const options_casted = options as (DistortionComponentOptions | undefined)
        this.getPeer()?.setDistortionComponentOptionsAttribute(options_casted)
        this.applyOptionsFinish('DistortionComponentAttribute');
        return this
    }
    public attributeModifier(value: AttributeModifier<DistortionComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookDistortionComponentAttributeModifier(this, value);
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
export function DistortionComponentImpl(
    @memo @memo_skip
    style: ((attributes: DistortionComponentAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkDistortionComponentComponent>((): ArkDistortionComponentComponent => {
        return new ArkDistortionComponentComponent()
    })
    NodeAttach<ArkDistortionComponentPeer>((): ArkDistortionComponentPeer => ArkDistortionComponentPeer.create(receiver), (_: ArkDistortionComponentPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class DistortionParam_serializer {
    public static write(buffer: SerializerBase, value: DistortionParam): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForTopLeft = value.topLeft
        Vector2_serializer.write(valueSerializer, valueHolderForTopLeft)
        const valueHolderForTopRight = value.topRight
        Vector2_serializer.write(valueSerializer, valueHolderForTopRight)
        const valueHolderForBottomLeft = value.bottomLeft
        Vector2_serializer.write(valueSerializer, valueHolderForBottomLeft)
        const valueHolderForBottomRight = value.bottomRight
        Vector2_serializer.write(valueSerializer, valueHolderForBottomRight)
        const valueHolderForBarrelDistortion = value.barrelDistortion
        Vector4_serializer.write(valueSerializer, valueHolderForBarrelDistortion)
    }
    public static read(buffer: DeserializerBase): DistortionParam {
        let valueDeserializer: DeserializerBase = buffer
        const topLeftTmpResult: Vector2 = Vector2_serializer.read(valueDeserializer)
        const topRightTmpResult: Vector2 = Vector2_serializer.read(valueDeserializer)
        const bottomLeftTmpResult: Vector2 = Vector2_serializer.read(valueDeserializer)
        const bottomRightTmpResult: Vector2 = Vector2_serializer.read(valueDeserializer)
        const barrelDistortionTmpResult: Vector4 = Vector4_serializer.read(valueDeserializer)
        let value: DistortionParam = ({topLeft: topLeftTmpResult, topRight: topRightTmpResult, bottomLeft: bottomLeftTmpResult, bottomRight: bottomRightTmpResult, barrelDistortion: barrelDistortionTmpResult} as DistortionParam)
        return value
    }
}
export class DistortionComponentOptions_serializer {
    public static write(buffer: SerializerBase, value: DistortionComponentOptions): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForDistortion = value.distortion
        if (valueHolderForDistortion !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDistortionTmpValue = valueHolderForDistortion!
            DistortionParam_serializer.write(valueSerializer, valueHolderForDistortionTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): DistortionComponentOptions {
        let valueDeserializer: DeserializerBase = buffer
        const distortionTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let distortionTmpBuf: DistortionParam | undefined = undefined
        if ((distortionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            distortionTmpBuf = DistortionParam_serializer.read(valueDeserializer)
        }
        const distortionTmpResult: DistortionParam | undefined = distortionTmpBuf
        let value: DistortionComponentOptions = ({distortion: distortionTmpResult} as DistortionComponentOptions)
        return value
    }
}
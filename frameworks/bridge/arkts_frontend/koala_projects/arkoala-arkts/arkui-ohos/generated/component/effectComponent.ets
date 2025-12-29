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

import { ArkThemeScopeManager } from "#arktheme"
import { int32, int64, float32 } from "@koalaui/common"
import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { AttributeModifier, hookEffectComponentAttributeModifier, AttributeUpdater } from "#handwritten"
import { ModifierStateManager } from '../CommonModifier';
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { EffectComponentModifier } from "./../EffectComponentModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkEffectComponentPeer extends ArkCommonMethodPeer {
    attributeSet?: EffectComponentModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkEffectComponentPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._EffectComponent_construct(peerId, flags)
        const _peer  = new ArkEffectComponentPeer(_peerPtr, peerId, 'EffectComponent', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setEffectComponentOptionsAttribute(options?: EffectComponentOptions): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            EffectComponentOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._EffectComponentInterface_setEffectComponentOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface EffectComponentAttribute extends CommonMethod {
    setEffectComponentOptions(options?: EffectComponentOptions): this {
        throw new Error("Unimplemented method setEffectComponentOptions")
    }
    attributeModifier(value: AttributeModifier<EffectComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkEffectComponentStyle extends ArkCommonMethodStyle implements EffectComponentAttribute {
    attributeModifier_value?: AttributeModifier<EffectComponentAttribute> | AttributeModifier<CommonMethod> | undefined
    setEffectComponentOptions(options?: EffectComponentOptions): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<EffectComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export enum EffectLayer {
    NONE = 0,
    CHARGE_MOTION = 1,
    CHARGE_TEXT = 2
}
export interface EffectComponentOptions {
    effectLayer?: EffectLayer;
}

export class ArkEffectComponentComponent extends ArkCommonMethodComponent implements EffectComponentAttribute {
    getPeer(): ArkEffectComponentPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkEffectComponentPeer)
    }
    public setEffectComponentOptions(options?: EffectComponentOptions): this {
        if (this.checkPriority("setEffectComponentOptions")) {
            const options_casted = options as (EffectComponentOptions | undefined)
            this.getPeer()?.setEffectComponentOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<EffectComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
          hookEffectComponentAttributeModifier(this, value);
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
export function EffectComponentImpl(
    @memo
    style: ((attributes: EffectComponentAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkEffectComponentComponent>((): ArkEffectComponentComponent => {
        return new ArkEffectComponentComponent()
    })
    NodeAttach<ArkEffectComponentPeer>((): ArkEffectComponentPeer => ArkEffectComponentPeer.create(receiver), (peer: ArkEffectComponentPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

export class EffectComponentOptions_serializer {
    public static write(buffer: SerializerBase, value: EffectComponentOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForEffectLayer  = value.effectLayer
        if (valueHolderForEffectLayer !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEffectLayerTmpValue  = (valueHolderForEffectLayer as EffectLayer)
            valueSerializer.writeInt32(valueHolderForEffectLayerTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): EffectComponentOptions {
        let valueDeserializer : DeserializerBase = buffer
        const effectLayerTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let effectLayerTmpBuf : EffectLayer | undefined = undefined
        if ((effectLayerTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            effectLayerTmpBuf = EffectLayer.fromValue(valueDeserializer.readInt32())
        }
        const effectLayerTmpResult : EffectLayer | undefined = effectLayerTmpBuf
        let value : EffectComponentOptions = ({effectLayer: effectLayerTmpResult} as EffectComponentOptions)
        return value
    }
}

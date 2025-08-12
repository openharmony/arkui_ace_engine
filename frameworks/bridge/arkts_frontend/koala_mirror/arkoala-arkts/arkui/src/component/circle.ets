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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonShapeMethodPeer, CommonShapeMethod, CommonMethod, ArkCommonShapeMethodComponent, ArkCommonShapeMethodStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonShapeMethodModifier, CommonMethodModifier } from "./common"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
export class ArkCirclePeer extends ArkCommonShapeMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkCirclePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Circle_construct(peerId, flags)
        const _peer  = new ArkCirclePeer(_peerPtr, peerId, 'Circle', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setCircleOptionsAttribute(value?: CircleOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            CircleOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CircleInterface_setCircleOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface CircleOptions {
}
export interface CircleAttribute extends CommonShapeMethod {
    attributeModifier(value: AttributeModifier<CircleAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkCircleStyle extends ArkCommonShapeMethodStyle implements CircleAttribute {
    attributeModifier_value?: AttributeModifier<CircleAttribute> | AttributeModifier<CommonMethod> | undefined
    public attributeModifier(value: AttributeModifier<CircleAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkCircleComponent extends ArkCommonShapeMethodComponent implements CircleAttribute {
    getPeer(): ArkCirclePeer {
        return (this.peer as ArkCirclePeer)
    }
    public setCircleOptions(value?: CircleOptions): this {
        if (this.checkPriority("setCircleOptions")) {
            const value_casted = value as (CircleOptions | undefined)
            this.getPeer()?.setCircleOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<CircleAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

@memo
export function Circle(
    @memo
    style: ((attributes: CircleAttribute) => void) | undefined,
    value?: CircleOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkCircleComponent>((): ArkCircleComponent => {
        return new ArkCircleComponent()
    })
    NodeAttach<ArkCirclePeer>((): ArkCirclePeer => ArkCirclePeer.create(receiver), (_: ArkCirclePeer): void => {
        receiver.setCircleOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class CircleModifier extends CommonShapeMethodModifier implements CircleAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyModifierPatch(peer: ArkCirclePeer): void {
        super.applyModifierPatch(peer)
    }
    mergeModifier(modifier: CircleModifier): void {
        super.mergeModifier(modifier)
    }
    public attributeModifier(value: AttributeModifier<CircleAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class CircleOptions_serializer {
    public static write(buffer: SerializerBase, value: CircleOptions): void {
    }
    public static read(buffer: DeserializerBase): CircleOptions {
        let value : CircleOptions = ({} as CircleOptions)
        return value
    }
}

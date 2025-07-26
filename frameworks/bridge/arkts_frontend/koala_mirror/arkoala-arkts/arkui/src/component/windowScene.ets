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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer } from "@koalaui/interop"
import { Position_serializer, Position, Length } from "./units"
import { int32, int64, float32 } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { Resource } from "./../generated/resource"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkWindowScenePeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkWindowScenePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._WindowScene_construct(peerId, flags)
        const _peer  = new ArkWindowScenePeer(_peerPtr, peerId, "WindowScene", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setWindowSceneOptionsAttribute(persistentId: number): void {
        ArkUIGeneratedNativeModule._WindowSceneInterface_setWindowSceneOptions(this.peer.ptr, persistentId)
    }
    setAttractionEffectAttribute(destination: Position | undefined, fraction: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let destination_type : int32 = RuntimeType.UNDEFINED
        destination_type = runtimeType(destination)
        thisSerializer.writeInt8((destination_type).toChar())
        if ((destination_type) != (RuntimeType.UNDEFINED)) {
            const destination_value  = destination!
            Position_serializer.write(thisSerializer, destination_value)
        }
        let fraction_type : int32 = RuntimeType.UNDEFINED
        fraction_type = runtimeType(fraction)
        thisSerializer.writeInt8((fraction_type).toChar())
        if ((fraction_type) != (RuntimeType.UNDEFINED)) {
            const fraction_value  = fraction!
            thisSerializer.writeNumber(fraction_value)
        }
        ArkUIGeneratedNativeModule._WindowSceneAttribute_setAttractionEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface WindowSceneAttribute extends CommonMethod {
    attractionEffect(destination: Position | undefined, fraction: number | undefined): this {
        throw new Error("Unimplemented method attractionEffect")
    }
    attributeModifier(value: AttributeModifier<WindowSceneAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkWindowSceneStyle extends ArkCommonMethodStyle implements WindowSceneAttribute {
    attributeModifier_value?: AttributeModifier<WindowSceneAttribute> | AttributeModifier<CommonMethod> | undefined
    public attractionEffect(destination: Position | undefined, fraction: number | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<WindowSceneAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: WindowSceneAttribute): void {
        super.apply(target)
    }
}

export class ArkWindowSceneComponent extends ArkCommonMethodComponent implements WindowSceneAttribute {
    getPeer(): ArkWindowScenePeer {
        return (this.peer as ArkWindowScenePeer)
    }
    public setWindowSceneOptions(persistentId: number): this {
        if (this.checkPriority("setWindowSceneOptions")) {
            const persistentId_casted = persistentId as (number)
            this.getPeer()?.setWindowSceneOptionsAttribute(persistentId_casted)
            return this
        }
        return this
    }
    public attractionEffect(destination: Position | undefined, fraction: number | undefined): this {
        if (this.checkPriority("attractionEffect")) {
            const destination_casted = destination as (Position | undefined)
            const fraction_casted = fraction as (number | undefined)
            this.getPeer()?.setAttractionEffectAttribute(destination_casted, fraction_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<WindowSceneAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withWindowSceneStyle(receiver: WindowSceneAttribute, modifier: AttributeModifier<WindowSceneAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkWindowSceneStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("WindowScene")
// export function WindowScene(
//     persistentId: number,
//     @memo
//     content_?: () => void,
// ): WindowSceneAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function WindowScene(
    @memo
    style: ((attributes: WindowSceneAttribute) => void) | undefined,
    persistentId: number,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkWindowSceneComponent>((): ArkWindowSceneComponent => {
        return new ArkWindowSceneComponent()
    })
    NodeAttach<ArkWindowScenePeer>((): ArkWindowScenePeer => ArkWindowScenePeer.create(receiver), (_: ArkWindowScenePeer): void => {
        receiver.setWindowSceneOptions(persistentId)
        style?.(receiver)
        withWindowSceneStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkWindowSceneSet extends ArkCommonMethodSet implements WindowSceneAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _attractionEffect_flag?: boolean
    _attractionEffect0_value?: Position | undefined
    _attractionEffect1_value?: number | undefined
    applyModifierPatch(component: WindowSceneAttribute): void {
        if (this._attractionEffect_flag)
            component.attractionEffect((this._attractionEffect0_value as Position | undefined), (this._attractionEffect1_value as number | undefined))
    }
    public attractionEffect(destination: Position | undefined, fraction: number | undefined): this {
        this._attractionEffect_flag = true
        this._attractionEffect0_value = destination
        this._attractionEffect1_value = fraction
        return this
    }
    public attributeModifier(value: AttributeModifier<WindowSceneAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

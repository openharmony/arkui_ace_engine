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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer } from "@koalaui/interop"
import { Position_serializer, Position, Length } from "./units"
import { int32, int64, float32 } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier } from "./common"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { Resource } from "./../generated/resource"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
export class ArkWindowScenePeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkWindowScenePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._WindowScene_construct(peerId, flags)
        const _peer  = new ArkWindowScenePeer(_peerPtr, peerId, 'WindowScene', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setWindowSceneOptionsAttribute(persistentId: number): void {
        ArkUIGeneratedNativeModule._WindowSceneInterface_setWindowSceneOptions(this.peer.ptr, persistentId)
    }
    setAttractionEffectAttribute(destination: Position | undefined, fraction: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (destination !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const destinationTmpValue  = destination!
            Position_serializer.write(thisSerializer, destinationTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (fraction !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const fractionTmpValue  = fraction!
            thisSerializer.writeNumber(fractionTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
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
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

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
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class WindowSceneModifier extends CommonMethodModifier implements WindowSceneAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _attractionEffect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _attractionEffect_0_0value?: Position | undefined
    _attractionEffect_0_1value?: number | undefined
    applyModifierPatch(peer: ArkWindowScenePeer): void {
        super.applyModifierPatch(peer)
        if (this._attractionEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._attractionEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAttractionEffectAttribute((this._attractionEffect_0_0value as Position | undefined), (this._attractionEffect_0_1value as number | undefined));
                    this._attractionEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._attractionEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._attractionEffect_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAttractionEffectAttribute((undefined as Position | undefined), (undefined as number | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: WindowSceneModifier): void {
        super.mergeModifier(modifier)
        if (modifier._attractionEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._attractionEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.attractionEffect(modifier._attractionEffect_0_0value, modifier._attractionEffect_0_1value);
                    break;
                }
                default: {
                    this.attractionEffect((undefined as Position | undefined), (undefined as number | undefined));
                }
            }
        }
    }
    attractionEffect(destination: Position | undefined, fraction: number | undefined): this {
        if (((this._attractionEffect_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || ((this._attractionEffect_0_1value) !== (fraction)))
        {
            this._attractionEffect_0_flag = AttributeUpdaterFlag.UPDATE
            this._attractionEffect_0_0value = destination
            this._attractionEffect_0_1value = fraction
        } else
        {
            this._attractionEffect_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<WindowSceneAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

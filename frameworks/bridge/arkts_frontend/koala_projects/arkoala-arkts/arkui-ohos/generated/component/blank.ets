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
import { Resource_serializer } from "./../framework/resource"
import { int32, int64, float32 } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { ResourceColor } from "./units"
import { Color } from "./enums"
import { Resource } from "global.resource"
import { AttributeModifier, hookBlankAttributeModifier, AttributeUpdater } from "#handwritten"
import { ModifierStateManager } from '../CommonModifier';
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { BlankModifier } from "./../BlankModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkBlankPeer extends ArkCommonMethodPeer {
    attributeSet?: BlankModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkBlankPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Blank_construct(peerId, flags)
        const _peer  = new ArkBlankPeer(_peerPtr, peerId, 'Blank', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setBlankOptionsAttribute(min?: number | string): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (min !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const minTmpValue  = min!
            if (minTmpValue instanceof number) {
                thisSerializer.writeInt8((0).toByte())
                const minTmpValueForIdx0  = minTmpValue as number
                thisSerializer.writeNumber(minTmpValueForIdx0)
            } else if (minTmpValue instanceof string) {
                thisSerializer.writeInt8((1).toByte())
                const minTmpValueForIdx1  = minTmpValue as string
                thisSerializer.writeString(minTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._BlankInterface_setBlankOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._BlankAttribute_setColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface BlankAttribute extends CommonMethod {
    setBlankOptions(min?: number | string): this {
        throw new Error("Unimplemented method setBlankOptions")
    }
    color(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method color")
    }
    attributeModifier(value: AttributeModifier<BlankAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkBlankStyle extends ArkCommonMethodStyle implements BlankAttribute {
    color_value?: ResourceColor | undefined
    attributeModifier_value?: AttributeModifier<BlankAttribute> | AttributeModifier<CommonMethod> | undefined
    setBlankOptions(min?: number | string): this {
        return this
    }
    color(value: ResourceColor | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<BlankAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkBlankComponent extends ArkCommonMethodComponent implements BlankAttribute {
    getPeer(): ArkBlankPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkBlankPeer)
    }
    public setBlankOptions(min?: number | string): this {
        if (this.checkPriority("setBlankOptions")) {
            const min_casted = min as (number | string | undefined)
            this.getPeer()?.setBlankOptionsAttribute(min_casted)
            this.applyOptionsFinish('BlankAttribute');
            return this
        }
        return this
    }
    public color(value: ResourceColor | undefined): this {
        if (this.checkPriority("color")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setColorAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<BlankAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
          hookBlankAttributeModifier(this, value);
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
export function BlankImpl(
    @memo
    style: ((attributes: BlankAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkBlankComponent>((): ArkBlankComponent => {
        return new ArkBlankComponent()
    })
    NodeAttach<ArkBlankPeer>((): ArkBlankPeer => ArkBlankPeer.create(receiver), (peer: ArkBlankPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}


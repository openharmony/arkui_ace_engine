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
import { Color } from "./enums"
import { Resource } from "global.resource"
import { AttributeModifier, hookHyperlinkAttributeModifier, AttributeUpdater } from "#handwritten"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { HyperlinkModifier } from "./../HyperlinkModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ModifierStateManager } from '../CommonModifier';
export class ArkHyperlinkPeer extends ArkCommonMethodPeer {
    attributeSet?: HyperlinkModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkHyperlinkPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Hyperlink_construct(peerId, flags)
        const _peer  = new ArkHyperlinkPeer(_peerPtr, peerId, 'Hyperlink', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setHyperlinkOptionsAttribute(address: string | Resource | undefined, content?: string | Resource): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (address !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const addressTmpValue  = address!
            if (addressTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const addressTmpValueForIdx0  = addressTmpValue as string
                thisSerializer.writeString(addressTmpValueForIdx0)
            } else if (addressTmpValue instanceof Resource) {
                thisSerializer.writeInt8((1).toByte())
                const addressTmpValueForIdx1  = addressTmpValue as Resource
                Resource_serializer.write(thisSerializer, addressTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (content !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const contentTmpValue  = content!
            if (contentTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const contentTmpValueForIdx0  = contentTmpValue as string
                thisSerializer.writeString(contentTmpValueForIdx0)
            } else if (contentTmpValue instanceof Resource) {
                thisSerializer.writeInt8((1).toByte())
                const contentTmpValueForIdx1  = contentTmpValue as Resource
                Resource_serializer.write(thisSerializer, contentTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._HyperlinkInterface_setHyperlinkOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setColorAttribute(value: Color | int32 | string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx1)
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
        ArkUIGeneratedNativeModule._HyperlinkAttribute_setColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface HyperlinkAttribute extends CommonMethod {
    setHyperlinkOptions(address: string | Resource | undefined, content?: string | Resource): this {
        throw new Error("Unimplemented method setHyperlinkOptions")
    }
    color(value: Color | int32 | string | Resource | undefined): this {
        throw new Error("Unimplemented method color")
    }
    attributeModifier(value: AttributeModifier<HyperlinkAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkHyperlinkStyle extends ArkCommonMethodStyle implements HyperlinkAttribute {
    color_value?: Color | int32 | string | Resource | undefined
    attributeModifier_value?: AttributeModifier<HyperlinkAttribute> | AttributeModifier<CommonMethod> | undefined
    setHyperlinkOptions(address: string | Resource | undefined, content?: string | Resource): this {
        return this
    }
    color(value: Color | int32 | string | Resource | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<HyperlinkAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkHyperlinkComponent extends ArkCommonMethodComponent implements HyperlinkAttribute {
    getPeer(): ArkHyperlinkPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkHyperlinkPeer)
    }
    public setHyperlinkOptions(address: string | Resource | undefined, content?: string | Resource): this {
        if (this.checkPriority("setHyperlinkOptions")) {
            const address_casted = address as (string | Resource | undefined)
            const content_casted = content as (string | Resource | undefined)
            this.getPeer()?.setHyperlinkOptionsAttribute(address_casted, content_casted)
            this.applyOptionsFinish('HyperlinkAttribute');
            return this
        }
        return this
    }
    public color(value: Color | int32 | string | Resource | undefined): this {
        if (this.checkPriority("color")) {
            const value_casted = value as (Color | int32 | string | Resource | undefined)
            this.getPeer()?.setColorAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<HyperlinkAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookHyperlinkAttributeModifier(this, value);
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
export function HyperlinkImpl(
    @memo
    style: ((attributes: HyperlinkAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkHyperlinkComponent>((): ArkHyperlinkComponent => {
        return new ArkHyperlinkComponent()
    })
    NodeAttach<ArkHyperlinkPeer>((): ArkHyperlinkPeer => ArkHyperlinkPeer.create(receiver), (peer: ArkHyperlinkPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}


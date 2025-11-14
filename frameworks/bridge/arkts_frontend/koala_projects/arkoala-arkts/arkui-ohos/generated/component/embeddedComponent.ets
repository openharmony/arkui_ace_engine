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
import { int32, int64, float32 } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, TerminationInfo, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { ErrorCallback, BusinessError } from "@ohos.base"
import { extractors, AttributeModifier, hookEmbeddedComponentAttributeModifier, AttributeUpdater } from "#handwritten"
import { default as Want } from "@ohos.app.ability.Want"
import { EmbeddedType } from "./enums"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { EmbeddedComponentModifier } from "./../EmbeddedComponentModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ModifierStateManager } from '../CommonModifier';
export class ArkEmbeddedComponentPeer extends ArkCommonMethodPeer {
    attributeSet?: EmbeddedComponentModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkEmbeddedComponentPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._EmbeddedComponent_construct(peerId, flags)
        const _peer  = new ArkEmbeddedComponentPeer(_peerPtr, peerId, 'EmbeddedComponent', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setEmbeddedComponentOptionsAttribute(loader: Want, type?: EmbeddedType): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (type !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const typeTmpValue  = (type as EmbeddedType)
            thisSerializer.writeInt32(typeTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._EmbeddedComponentInterface_setEmbeddedComponentOptions(this.peer.ptr, extractors.toWantPtr(loader), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnTerminatedAttribute(value: ((value0: TerminationInfo) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._EmbeddedComponentAttribute_setOnTerminated(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnErrorAttribute(value: ErrorCallback<BusinessError> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._EmbeddedComponentAttribute_setOnError(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface EmbeddedComponentAttribute extends CommonMethod {
    setEmbeddedComponentOptions(loader: Want, type?: EmbeddedType): this {
        throw new Error("Unimplemented method setEmbeddedComponentOptions")
    }
    onTerminated(value: ((value0: TerminationInfo) => void) | undefined): this {
        throw new Error("Unimplemented method onTerminated")
    }
    onError(value: ErrorCallback<BusinessError> | undefined): this {
        throw new Error("Unimplemented method onError")
    }
    attributeModifier(value: AttributeModifier<EmbeddedComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkEmbeddedComponentStyle extends ArkCommonMethodStyle implements EmbeddedComponentAttribute {
    onTerminated_value?: ((value0: TerminationInfo) => void) | undefined
    onError_value?: ErrorCallback<BusinessError> | undefined
    attributeModifier_value?: AttributeModifier<EmbeddedComponentAttribute> | AttributeModifier<CommonMethod> | undefined
    setEmbeddedComponentOptions(loader: Want, type?: EmbeddedType): this {
        return this
    }
    onTerminated(value: ((value0: TerminationInfo) => void) | undefined): this {
        return this
    }
    onError(value: ErrorCallback<BusinessError> | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<EmbeddedComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkEmbeddedComponentComponent extends ArkCommonMethodComponent implements EmbeddedComponentAttribute {
    getPeer(): ArkEmbeddedComponentPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkEmbeddedComponentPeer)
    }
    public setEmbeddedComponentOptions(loader: Want, type?: EmbeddedType): this {
        if (this.checkPriority("setEmbeddedComponentOptions")) {
            const loader_casted = loader as (Want)
            const type_casted = type as (EmbeddedType | undefined)
            this.getPeer()?.setEmbeddedComponentOptionsAttribute(loader_casted, type_casted)
            this.applyOptionsFinish('EmbeddedComponentAttribute');
            return this
        }
        return this
    }
    public onTerminated(value: ((value0: TerminationInfo) => void) | undefined): this {
        if (this.checkPriority("onTerminated")) {
            const value_casted = value as (((value0: TerminationInfo) => void) | undefined)
            this.getPeer()?.setOnTerminatedAttribute(value_casted)
            return this
        }
        return this
    }
    public onError(value: ErrorCallback<BusinessError> | undefined): this {
        if (this.checkPriority("onError")) {
            const value_casted = value as (ErrorCallback<BusinessError> | undefined)
            this.getPeer()?.setOnErrorAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<EmbeddedComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
         ModifierStateManager.INSTANCE.scope(() => {
           hookEmbeddedComponentAttributeModifier(this, value); 
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
export function EmbeddedComponentImpl(
    @memo
    style: ((attributes: EmbeddedComponentAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkEmbeddedComponentComponent>((): ArkEmbeddedComponentComponent => {
        return new ArkEmbeddedComponentComponent()
    })
    NodeAttach<ArkEmbeddedComponentPeer>((): ArkEmbeddedComponentPeer => ArkEmbeddedComponentPeer.create(receiver), (peer: ArkEmbeddedComponentPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}


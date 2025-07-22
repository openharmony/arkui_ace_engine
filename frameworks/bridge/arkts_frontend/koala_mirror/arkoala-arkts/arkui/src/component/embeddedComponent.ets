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
import { Want_serializer, Want } from "./../generated/ohos.app.ability.Want"
import { int32, int64, float32 } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, TerminationInfo, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { ErrorCallback, BusinessError } from "./../generated/ohos.base"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { EmbeddedType } from "./enums"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkEmbeddedComponentPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkEmbeddedComponentPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._EmbeddedComponent_construct(peerId, flags)
        const _peer  = new ArkEmbeddedComponentPeer(_peerPtr, peerId, "EmbeddedComponent", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setEmbeddedComponentOptionsAttribute(loader: Want, type: EmbeddedType): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Want_serializer.write(thisSerializer, loader)
        ArkUIGeneratedNativeModule._EmbeddedComponentInterface_setEmbeddedComponentOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length(), TypeChecker.EmbeddedType_ToNumeric(type))
        thisSerializer.release()
    }
    setOnTerminatedAttribute(value: ((value0: TerminationInfo) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._EmbeddedComponentAttribute_setOnTerminated(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnErrorAttribute(value: ErrorCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._EmbeddedComponentAttribute_setOnError(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface EmbeddedComponentAttribute extends CommonMethod {
    onTerminated(value: ((value0: TerminationInfo) => void) | undefined): this {
        throw new Error("Unimplemented method onTerminated")
    }
    onError(value: ErrorCallback | undefined): this {
        throw new Error("Unimplemented method onError")
    }
    attributeModifier(value: AttributeModifier<EmbeddedComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkEmbeddedComponentStyle extends ArkCommonMethodStyle implements EmbeddedComponentAttribute {
    onTerminated_value?: ((value0: TerminationInfo) => void) | undefined
    onError_value?: ErrorCallback | undefined
    attributeModifier_value?: AttributeModifier<EmbeddedComponentAttribute> | AttributeModifier<CommonMethod> | undefined
    public onTerminated(value: ((value0: TerminationInfo) => void) | undefined): this {
        return this
    }
    public onError(value: ErrorCallback | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<EmbeddedComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: EmbeddedComponentAttribute): void {
        super.apply(target)
        if (this.onTerminated_value !== undefined)
            target.onTerminated(this.onTerminated_value!)
        if (this.onError_value !== undefined)
            target.onError(this.onError_value!)
    }
}

export class ArkEmbeddedComponentComponent extends ArkCommonMethodComponent implements EmbeddedComponentAttribute {
    getPeer(): ArkEmbeddedComponentPeer {
        return (this.peer as ArkEmbeddedComponentPeer)
    }
    public setEmbeddedComponentOptions(loader: Want, type: EmbeddedType): this {
        if (this.checkPriority("setEmbeddedComponentOptions")) {
            const loader_casted = loader as (Want)
            const type_casted = type as (EmbeddedType)
            this.getPeer()?.setEmbeddedComponentOptionsAttribute(loader_casted, type_casted)
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
    public onError(value: ErrorCallback | undefined): this {
        if (this.checkPriority("onError")) {
            const value_casted = value as (ErrorCallback | undefined)
            this.getPeer()?.setOnErrorAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<EmbeddedComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withEmbeddedComponentStyle(receiver: EmbeddedComponentAttribute, modifier: AttributeModifier<EmbeddedComponentAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkEmbeddedComponentStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("EmbeddedComponent")
// export function EmbeddedComponent(
//     loader: Want, type: EmbeddedType,
//     @memo
//     content_?: () => void,
// ): EmbeddedComponentAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function EmbeddedComponent(
    @memo
    style: ((attributes: EmbeddedComponentAttribute) => void) | undefined,
    loader: Want, type: EmbeddedType,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkEmbeddedComponentComponent>((): ArkEmbeddedComponentComponent => {
        return new ArkEmbeddedComponentComponent()
    })
    NodeAttach<ArkEmbeddedComponentPeer>((): ArkEmbeddedComponentPeer => ArkEmbeddedComponentPeer.create(receiver), (_: ArkEmbeddedComponentPeer): void => {
        receiver.setEmbeddedComponentOptions(loader,type)
        style?.(receiver)
        withEmbeddedComponentStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkEmbeddedComponentSet extends ArkCommonMethodSet implements EmbeddedComponentAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _onTerminated_flag?: boolean
    _onTerminated0_value?: ((value0: TerminationInfo) => void) | undefined
    _onError_flag?: boolean
    _onError0_value?: ErrorCallback | undefined
    applyModifierPatch(component: EmbeddedComponentAttribute): void {
        if (this._onTerminated_flag)
            component.onTerminated((this._onTerminated0_value as ((value0: TerminationInfo) => void) | undefined))
        if (this._onError_flag)
            component.onError((this._onError0_value as ErrorCallback | undefined))
    }
    public onTerminated(value: ((value0: TerminationInfo) => void) | undefined): this {
        this._onTerminated_flag = true
        this._onTerminated0_value = value
        return this
    }
    public onError(value: ErrorCallback | undefined): this {
        this._onError_flag = true
        this._onError0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<EmbeddedComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { Want_serializer, Want } from "./ohos.app.ability.Want"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { ErrorCallback, BusinessError } from "./ohos.base"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { EmbeddedType } from "./enums"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
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
    onTerminatedAttribute(value: ((value0: TerminationInfo) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._EmbeddedComponentAttribute_onTerminated(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onErrorAttribute(value: ErrorCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._EmbeddedComponentAttribute_onError(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface TerminationInfo {
    code: number;
    want?: Want;
}
export interface EmbeddedComponentAttribute extends CommonMethod {
    onTerminated(value: ((value0: TerminationInfo) => void) | undefined): this
    onError(value: ErrorCallback | undefined): this
    attributeModifier(value: AttributeModifier<EmbeddedComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this
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
            this.getPeer()?.onTerminatedAttribute(value_casted)
            return this
        }
        return this
    }
    public onError(value: ErrorCallback | undefined): this {
        if (this.checkPriority("onError")) {
            const value_casted = value as (ErrorCallback | undefined)
            this.getPeer()?.onErrorAttribute(value_casted)
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
        if (modifier!.isUpdater)
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
@memo
@BuilderLambda("EmbeddedComponentImpl")
export function EmbeddedComponent(
    loader: Want, type: EmbeddedType,
    @memo
    content_?: () => void,
): EmbeddedComponentAttribute {
    throw new Error("Not implemented")
}

@memo
export function EmbeddedComponentImpl(
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

export class TerminationInfo_serializer {
    public static write(buffer: SerializerBase, value: TerminationInfo): void {
        let valueSerializer : SerializerBase = buffer
        const value_code  = value.code
        valueSerializer.writeNumber(value_code)
        const value_want  = value.want
        let value_want_type : int32 = RuntimeType.UNDEFINED
        value_want_type = runtimeType(value_want)
        valueSerializer.writeInt8(value_want_type)
        if ((RuntimeType.UNDEFINED) != (value_want_type)) {
            const value_want_value  = value_want!
            Want_serializer.write(valueSerializer, value_want_value)
        }
    }
    public static read(buffer: DeserializerBase): TerminationInfo {
        let valueDeserializer : DeserializerBase = buffer
        const code_result : number = (valueDeserializer.readNumber() as number)
        const want_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let want_buf : Want | undefined
        if ((RuntimeType.UNDEFINED) != (want_buf_runtimeType))
        {
            want_buf = Want_serializer.read(valueDeserializer)
        }
        const want_result : Want | undefined = want_buf
        let value : TerminationInfo = ({code: code_result, want: want_result} as TerminationInfo)
        return value
    }
}

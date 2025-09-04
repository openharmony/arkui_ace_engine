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
import { PointLightStyle_serializer, ArkCommonMethodPeer, CommonMethod, PointLightStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { Alignment } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkStackPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkStackPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Stack_construct(peerId, flags)
        const _peer  = new ArkStackPeer(_peerPtr, peerId, "Stack", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setStackOptionsAttribute(options?: StackOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            StackOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._StackInterface_setStackOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAlignContentAttribute(value: Alignment | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as Alignment)
            thisSerializer.writeInt32(TypeChecker.Alignment_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._StackAttribute_setAlignContent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPointLightAttribute(value: PointLightStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            PointLightStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._StackAttribute_setPointLight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface StackOptions {
    alignContent?: Alignment;
}
export interface StackAttribute extends CommonMethod {
    alignContent(value: Alignment | undefined): this {
        throw new Error("Unimplemented method alignContent")
    }
    pointLight(value: PointLightStyle | undefined): this {
        throw new Error("Unimplemented method pointLight")
    }
    attributeModifier(value: AttributeModifier<StackAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkStackStyle extends ArkCommonMethodStyle implements StackAttribute {
    alignContent_value?: Alignment | undefined
    pointLight_value?: PointLightStyle | undefined
    attributeModifier_value?: AttributeModifier<StackAttribute> | AttributeModifier<CommonMethod> | undefined
    public alignContent(value: Alignment | undefined): this {
        return this
    }
    public pointLight(value: PointLightStyle | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<StackAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: StackAttribute): void {
        super.apply(target)
        if (this.alignContent_value !== undefined)
            target.alignContent(this.alignContent_value!)
        if (this.pointLight_value !== undefined)
            target.pointLight(this.pointLight_value!)
    }
}

export class ArkStackComponent extends ArkCommonMethodComponent implements StackAttribute {
    getPeer(): ArkStackPeer {
        return (this.peer as ArkStackPeer)
    }
    public setStackOptions(options?: StackOptions): this {
        if (this.checkPriority("setStackOptions")) {
            const options_casted = options as (StackOptions | undefined)
            this.getPeer()?.setStackOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public alignContent(value: Alignment | undefined): this {
        if (this.checkPriority("alignContent")) {
            const value_casted = value as (Alignment | undefined)
            this.getPeer()?.setAlignContentAttribute(value_casted)
            return this
        }
        return this
    }
    public pointLight(value: PointLightStyle | undefined): this {
        if (this.checkPriority("pointLight")) {
            const value_casted = value as (PointLightStyle | undefined)
            this.getPeer()?.setPointLightAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<StackAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withStackStyle(receiver: StackAttribute, modifier: AttributeModifier<StackAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkStackStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Stack")
// export function Stack(
//     options?: StackOptions,
//     @memo
//     content_?: () => void,
// ): StackAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Stack(
    @memo
    style: ((attributes: StackAttribute) => void) | undefined,
    options?: StackOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkStackComponent>((): ArkStackComponent => {
        return new ArkStackComponent()
    })
    NodeAttach<ArkStackPeer>((): ArkStackPeer => ArkStackPeer.create(receiver), (_: ArkStackPeer): void => {
        receiver.setStackOptions(options)
        style?.(receiver)
        withStackStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkStackSet extends ArkCommonMethodSet implements StackAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _alignContent_flag?: boolean
    _alignContent0_value?: Alignment | undefined
    _pointLight_flag?: boolean
    _pointLight0_value?: PointLightStyle | undefined
    applyModifierPatch(component: StackAttribute): void {
        if (this._alignContent_flag)
            component.alignContent((this._alignContent0_value as Alignment | undefined))
        if (this._pointLight_flag)
            component.pointLight((this._pointLight0_value as PointLightStyle | undefined))
    }
    public alignContent(value: Alignment | undefined): this {
        this._alignContent_flag = true
        this._alignContent0_value = value
        return this
    }
    public pointLight(value: PointLightStyle | undefined): this {
        this._pointLight_flag = true
        this._pointLight0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<StackAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class StackOptions_serializer {
    public static write(buffer: SerializerBase, value: StackOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_alignContent  = value.alignContent
        let value_alignContent_type : int32 = RuntimeType.UNDEFINED
        value_alignContent_type = runtimeType(value_alignContent)
        valueSerializer.writeInt8((value_alignContent_type).toChar())
        if ((value_alignContent_type) != (RuntimeType.UNDEFINED)) {
            const value_alignContent_value  = (value_alignContent as Alignment)
            valueSerializer.writeInt32(TypeChecker.Alignment_ToNumeric(value_alignContent_value))
        }
    }
    public static read(buffer: DeserializerBase): StackOptions {
        let valueDeserializer : DeserializerBase = buffer
        const alignContent_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let alignContent_buf : Alignment | undefined
        if ((alignContent_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            alignContent_buf = TypeChecker.Alignment_FromNumeric(valueDeserializer.readInt32())
        }
        const alignContent_result : Alignment | undefined = alignContent_buf
        let value : StackOptions = ({alignContent: alignContent_result} as StackOptions)
        return value
    }
}

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
import { PointLightStyle_serializer, ArkCommonMethodPeer, CommonMethod, PointLightStyle, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { VerticalAlign, FlexAlign } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { SpaceType } from "./column"
import { Resource, Resource_serializer } from "./resource"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkRowPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkRowPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Row_construct(peerId, flags)
        const _peer  = new ArkRowPeer(_peerPtr, peerId, "Row", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setRowOptionsAttribute(options?: RowOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            RowOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._RowInterface_setRowOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    alignItemsAttribute(value: VerticalAlign | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as VerticalAlign)
            thisSerializer.writeInt32(TypeChecker.VerticalAlign_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._RowAttribute_alignItems(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    justifyContentAttribute(value: FlexAlign | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as FlexAlign)
            thisSerializer.writeInt32(TypeChecker.FlexAlign_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._RowAttribute_justifyContent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    pointLightAttribute(value: PointLightStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            PointLightStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._RowAttribute_pointLight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    reverseAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._RowAttribute_reverse(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface RowOptions {
    space?: SpaceType;
}
export interface RowAttribute extends CommonMethod {
    alignItems(value: VerticalAlign | undefined): this
    justifyContent(value: FlexAlign | undefined): this
    pointLight(value: PointLightStyle | undefined): this
    reverse(value: boolean | undefined): this
    attributeModifier(value: AttributeModifier<RowAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkRowStyle extends ArkCommonMethodStyle implements RowAttribute {
    alignItems_value?: VerticalAlign | undefined
    justifyContent_value?: FlexAlign | undefined
    pointLight_value?: PointLightStyle | undefined
    reverse_value?: boolean | undefined
    attributeModifier_value?: AttributeModifier<RowAttribute> | AttributeModifier<CommonMethod> | undefined
    public alignItems(value: VerticalAlign | undefined): this {
        return this
    }
    public justifyContent(value: FlexAlign | undefined): this {
        return this
    }
    public pointLight(value: PointLightStyle | undefined): this {
        return this
    }
    public reverse(value: boolean | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<RowAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: RowAttribute): void {
        super.apply(target)
        if (this.alignItems_value !== undefined)
            target.alignItems(this.alignItems_value!)
        if (this.justifyContent_value !== undefined)
            target.justifyContent(this.justifyContent_value!)
        if (this.pointLight_value !== undefined)
            target.pointLight(this.pointLight_value!)
        if (this.reverse_value !== undefined)
            target.reverse(this.reverse_value!)
    }
}

export class ArkRowComponent extends ArkCommonMethodComponent implements RowAttribute {
    getPeer(): ArkRowPeer {
        return (this.peer as ArkRowPeer)
    }
    public setRowOptions(options?: RowOptions): this {
        if (this.checkPriority("setRowOptions")) {
            const options_casted = options as (RowOptions | undefined)
            this.getPeer()?.setRowOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public alignItems(value: VerticalAlign | undefined): this {
        if (this.checkPriority("alignItems")) {
            const value_casted = value as (VerticalAlign | undefined)
            this.getPeer()?.alignItemsAttribute(value_casted)
            return this
        }
        return this
    }
    public justifyContent(value: FlexAlign | undefined): this {
        if (this.checkPriority("justifyContent")) {
            const value_casted = value as (FlexAlign | undefined)
            this.getPeer()?.justifyContentAttribute(value_casted)
            return this
        }
        return this
    }
    public pointLight(value: PointLightStyle | undefined): this {
        if (this.checkPriority("pointLight")) {
            const value_casted = value as (PointLightStyle | undefined)
            this.getPeer()?.pointLightAttribute(value_casted)
            return this
        }
        return this
    }
    public reverse(value: boolean | undefined): this {
        if (this.checkPriority("reverse")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.reverseAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RowAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withRowStyle(receiver: RowAttribute, modifier: AttributeModifier<RowAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkRowStyle()
        if (modifier!.isUpdater)
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
@memo
@BuilderLambda("RowImpl")
export function Row(
    options?: RowOptions | undefined,
    @memo
    content_?: () => void,
): RowAttribute {
    throw new Error("Not implemented")
}

@memo
export function RowImpl(
    @memo
    style: ((attributes: RowAttribute) => void) | undefined,
    options?: RowOptions | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkRowComponent>((): ArkRowComponent => {
        return new ArkRowComponent()
    })
    NodeAttach<ArkRowPeer>((): ArkRowPeer => ArkRowPeer.create(receiver), (_: ArkRowPeer): void => {
        receiver.setRowOptions(options)
        style?.(receiver)
        withRowStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class RowOptions_serializer {
    public static write(buffer: SerializerBase, value: RowOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_space  = value.space
        let value_space_type : int32 = RuntimeType.UNDEFINED
        value_space_type = runtimeType(value_space)
        valueSerializer.writeInt8(value_space_type)
        if ((RuntimeType.UNDEFINED) != (value_space_type)) {
            const value_space_value  = value_space!
            let value_space_value_type : int32 = RuntimeType.UNDEFINED
            value_space_value_type = runtimeType(value_space_value)
            if (RuntimeType.STRING == value_space_value_type) {
                valueSerializer.writeInt8(0)
                const value_space_value_0  = value_space_value as string
                valueSerializer.writeString(value_space_value_0)
            }
            else if (RuntimeType.NUMBER == value_space_value_type) {
                valueSerializer.writeInt8(1)
                const value_space_value_1  = value_space_value as number
                valueSerializer.writeNumber(value_space_value_1)
            }
            else if (RuntimeType.OBJECT == value_space_value_type) {
                valueSerializer.writeInt8(2)
                const value_space_value_2  = value_space_value as Resource
                Resource_serializer.write(valueSerializer, value_space_value_2)
            }
        }
    }
    public static read(buffer: DeserializerBase): RowOptions {
        let valueDeserializer : DeserializerBase = buffer
        const space_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let space_buf : SpaceType | undefined
        if ((RuntimeType.UNDEFINED) != (space_buf_runtimeType))
        {
            const space_buf__selector : int32 = valueDeserializer.readInt8()
            let space_buf_ : string | number | Resource | undefined
            if (space_buf__selector == 0) {
                space_buf_ = (valueDeserializer.readString() as string)
            }
            else if (space_buf__selector == 1) {
                space_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (space_buf__selector == 2) {
                space_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for space_buf_ has to be chosen through deserialisation.")
            }
            space_buf = (space_buf_ as string | number | Resource)
        }
        const space_result : SpaceType | undefined = space_buf
        let value : RowOptions = ({space: space_result} as RowOptions)
        return value
    }
}

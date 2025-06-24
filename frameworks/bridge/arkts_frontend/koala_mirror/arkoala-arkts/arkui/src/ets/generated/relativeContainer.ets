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
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { Dimension } from "./units"
import { Resource, Resource_serializer } from "./resource"
import { Axis } from "./enums"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkRelativeContainerPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkRelativeContainerPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._RelativeContainer_construct(peerId, flags)
        const _peer  = new ArkRelativeContainerPeer(_peerPtr, peerId, "RelativeContainer", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setRelativeContainerOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._RelativeContainerInterface_setRelativeContainerOptions(this.peer.ptr)
    }
    guideLineAttribute(value: Array<GuideLineStyle> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeInt32(value_value.length as int32)
            for (let i = 0; i < value_value.length; i++) {
                const value_value_element : GuideLineStyle = value_value[i]
                GuideLineStyle_serializer.write(thisSerializer, value_value_element)
            }
        }
        ArkUIGeneratedNativeModule._RelativeContainerAttribute_guideLine(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    barrier0Attribute(value: Array<BarrierStyle> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeInt32(value_value.length as int32)
            for (let i = 0; i < value_value.length; i++) {
                const value_value_element : BarrierStyle = value_value[i]
                BarrierStyle_serializer.write(thisSerializer, value_value_element)
            }
        }
        ArkUIGeneratedNativeModule._RelativeContainerAttribute_barrier0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    barrier1Attribute(value: Array<LocalizedBarrierStyle> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeInt32(value_value.length as int32)
            for (let i = 0; i < value_value.length; i++) {
                const value_value_element : LocalizedBarrierStyle = value_value[i]
                LocalizedBarrierStyle_serializer.write(thisSerializer, value_value_element)
            }
        }
        ArkUIGeneratedNativeModule._RelativeContainerAttribute_barrier1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface GuideLinePosition {
    start?: Dimension;
    end?: Dimension;
}
export interface GuideLineStyle {
    id: string;
    direction: Axis;
    position: GuideLinePosition;
}
export enum BarrierDirection {
    LEFT = 0,
    RIGHT = 1,
    TOP = 2,
    BOTTOM = 3
}
export enum LocalizedBarrierDirection {
    START = 0,
    END = 1,
    TOP = 2,
    BOTTOM = 3
}
export interface BarrierStyle {
    id: string;
    direction: BarrierDirection;
    referencedId: Array<string>;
}
export interface LocalizedBarrierStyle {
    id: string;
    localizedDirection: LocalizedBarrierDirection;
    referencedId: Array<string>;
}
export interface RelativeContainerAttribute extends CommonMethod {
    guideLine(value: Array<GuideLineStyle> | undefined): this
    barrier(value: Array<BarrierStyle> | undefined | Array<LocalizedBarrierStyle> | undefined): this
    attributeModifier(value: AttributeModifier<RelativeContainerAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkRelativeContainerStyle extends ArkCommonMethodStyle implements RelativeContainerAttribute {
    guideLine_value?: Array<GuideLineStyle> | undefined
    barrier_value?: Array<BarrierStyle> | undefined
    attributeModifier_value?: AttributeModifier<RelativeContainerAttribute> | AttributeModifier<CommonMethod> | undefined
    public guideLine(value: Array<GuideLineStyle> | undefined): this {
        return this
    }
    public barrier(value: Array<BarrierStyle> | undefined | Array<LocalizedBarrierStyle> | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<RelativeContainerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: RelativeContainerAttribute): void {
        super.apply(target)
        if (this.guideLine_value !== undefined)
            target.guideLine(this.guideLine_value!)
        if (this.barrier_value !== undefined)
            target.barrier(this.barrier_value!)
    }
}

export class ArkRelativeContainerComponent extends ArkCommonMethodComponent implements RelativeContainerAttribute {
    getPeer(): ArkRelativeContainerPeer {
        return (this.peer as ArkRelativeContainerPeer)
    }
    public setRelativeContainerOptions(): this {
        if (this.checkPriority("setRelativeContainerOptions")) {
            this.getPeer()?.setRelativeContainerOptionsAttribute()
            return this
        }
        return this
    }
    public guideLine(value: Array<GuideLineStyle> | undefined): this {
        if (this.checkPriority("guideLine")) {
            const value_casted = value as (Array<GuideLineStyle> | undefined)
            this.getPeer()?.guideLineAttribute(value_casted)
            return this
        }
        return this
    }
    public barrier(value: Array<BarrierStyle> | undefined | Array<LocalizedBarrierStyle> | undefined): this {
        if (this.checkPriority("barrier")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Array<BarrierStyle> | undefined)
                this.getPeer()?.barrier0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Array<LocalizedBarrierStyle> | undefined)
                this.getPeer()?.barrier1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RelativeContainerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withRelativeContainerStyle(receiver: RelativeContainerAttribute, modifier: AttributeModifier<RelativeContainerAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkRelativeContainerStyle()
        if (modifier!.isUpdater)
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
@memo
@BuilderLambda("RelativeContainerImpl")
export function RelativeContainer(
    
    @memo
    content_?: () => void,
): RelativeContainerAttribute {
    throw new Error("Not implemented")
}

@memo
export function RelativeContainerImpl(
    @memo
    style: ((attributes: RelativeContainerAttribute) => void) | undefined,
    
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkRelativeContainerComponent>((): ArkRelativeContainerComponent => {
        return new ArkRelativeContainerComponent()
    })
    NodeAttach<ArkRelativeContainerPeer>((): ArkRelativeContainerPeer => ArkRelativeContainerPeer.create(receiver), (_: ArkRelativeContainerPeer): void => {
        receiver.setRelativeContainerOptions()
        style?.(receiver)
        withRelativeContainerStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class BarrierStyle_serializer {
    public static write(buffer: SerializerBase, value: BarrierStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_id  = value.id
        valueSerializer.writeString(value_id)
        const value_direction  = value.direction
        valueSerializer.writeInt32(TypeChecker.BarrierDirection_ToNumeric(value_direction))
        const value_referencedId  = value.referencedId
        valueSerializer.writeInt32(value_referencedId.length as int32)
        for (let i = 0; i < value_referencedId.length; i++) {
            const value_referencedId_element : string = value_referencedId[i]
            valueSerializer.writeString(value_referencedId_element)
        }
    }
    public static read(buffer: DeserializerBase): BarrierStyle {
        let valueDeserializer : DeserializerBase = buffer
        const id_result : string = (valueDeserializer.readString() as string)
        const direction_result : BarrierDirection = TypeChecker.BarrierDirection_FromNumeric(valueDeserializer.readInt32())
        const referencedId_buf_length : int32 = valueDeserializer.readInt32()
        let referencedId_buf : Array<string> = new Array<string>(referencedId_buf_length)
        for (let referencedId_buf_i = 0; referencedId_buf_i < referencedId_buf_length; referencedId_buf_i++) {
            referencedId_buf[referencedId_buf_i] = (valueDeserializer.readString() as string)
        }
        const referencedId_result : Array<string> = referencedId_buf
        let value : BarrierStyle = ({id: id_result, direction: direction_result, referencedId: referencedId_result} as BarrierStyle)
        return value
    }
}
export class LocalizedBarrierStyle_serializer {
    public static write(buffer: SerializerBase, value: LocalizedBarrierStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_id  = value.id
        valueSerializer.writeString(value_id)
        const value_localizedDirection  = value.localizedDirection
        valueSerializer.writeInt32(TypeChecker.LocalizedBarrierDirection_ToNumeric(value_localizedDirection))
        const value_referencedId  = value.referencedId
        valueSerializer.writeInt32(value_referencedId.length as int32)
        for (let i = 0; i < value_referencedId.length; i++) {
            const value_referencedId_element : string = value_referencedId[i]
            valueSerializer.writeString(value_referencedId_element)
        }
    }
    public static read(buffer: DeserializerBase): LocalizedBarrierStyle {
        let valueDeserializer : DeserializerBase = buffer
        const id_result : string = (valueDeserializer.readString() as string)
        const localizedDirection_result : LocalizedBarrierDirection = TypeChecker.LocalizedBarrierDirection_FromNumeric(valueDeserializer.readInt32())
        const referencedId_buf_length : int32 = valueDeserializer.readInt32()
        let referencedId_buf : Array<string> = new Array<string>(referencedId_buf_length)
        for (let referencedId_buf_i = 0; referencedId_buf_i < referencedId_buf_length; referencedId_buf_i++) {
            referencedId_buf[referencedId_buf_i] = (valueDeserializer.readString() as string)
        }
        const referencedId_result : Array<string> = referencedId_buf
        let value : LocalizedBarrierStyle = ({id: id_result, localizedDirection: localizedDirection_result, referencedId: referencedId_result} as LocalizedBarrierStyle)
        return value
    }
}
export class GuideLinePosition_serializer {
    public static write(buffer: SerializerBase, value: GuideLinePosition): void {
        let valueSerializer : SerializerBase = buffer
        const value_start  = value.start
        let value_start_type : int32 = RuntimeType.UNDEFINED
        value_start_type = runtimeType(value_start)
        valueSerializer.writeInt8(value_start_type)
        if ((RuntimeType.UNDEFINED) != (value_start_type)) {
            const value_start_value  = value_start!
            let value_start_value_type : int32 = RuntimeType.UNDEFINED
            value_start_value_type = runtimeType(value_start_value)
            if (RuntimeType.STRING == value_start_value_type) {
                valueSerializer.writeInt8(0)
                const value_start_value_0  = value_start_value as string
                valueSerializer.writeString(value_start_value_0)
            }
            else if (RuntimeType.NUMBER == value_start_value_type) {
                valueSerializer.writeInt8(1)
                const value_start_value_1  = value_start_value as number
                valueSerializer.writeNumber(value_start_value_1)
            }
            else if (RuntimeType.OBJECT == value_start_value_type) {
                valueSerializer.writeInt8(2)
                const value_start_value_2  = value_start_value as Resource
                Resource_serializer.write(valueSerializer, value_start_value_2)
            }
        }
        const value_end  = value.end
        let value_end_type : int32 = RuntimeType.UNDEFINED
        value_end_type = runtimeType(value_end)
        valueSerializer.writeInt8(value_end_type)
        if ((RuntimeType.UNDEFINED) != (value_end_type)) {
            const value_end_value  = value_end!
            let value_end_value_type : int32 = RuntimeType.UNDEFINED
            value_end_value_type = runtimeType(value_end_value)
            if (RuntimeType.STRING == value_end_value_type) {
                valueSerializer.writeInt8(0)
                const value_end_value_0  = value_end_value as string
                valueSerializer.writeString(value_end_value_0)
            }
            else if (RuntimeType.NUMBER == value_end_value_type) {
                valueSerializer.writeInt8(1)
                const value_end_value_1  = value_end_value as number
                valueSerializer.writeNumber(value_end_value_1)
            }
            else if (RuntimeType.OBJECT == value_end_value_type) {
                valueSerializer.writeInt8(2)
                const value_end_value_2  = value_end_value as Resource
                Resource_serializer.write(valueSerializer, value_end_value_2)
            }
        }
    }
    public static read(buffer: DeserializerBase): GuideLinePosition {
        let valueDeserializer : DeserializerBase = buffer
        const start_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let start_buf : Dimension | undefined
        if ((RuntimeType.UNDEFINED) != (start_buf_runtimeType))
        {
            const start_buf__selector : int32 = valueDeserializer.readInt8()
            let start_buf_ : string | number | Resource | undefined
            if (start_buf__selector == 0) {
                start_buf_ = (valueDeserializer.readString() as string)
            }
            else if (start_buf__selector == 1) {
                start_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (start_buf__selector == 2) {
                start_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for start_buf_ has to be chosen through deserialisation.")
            }
            start_buf = (start_buf_ as string | number | Resource)
        }
        const start_result : Dimension | undefined = start_buf
        const end_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let end_buf : Dimension | undefined
        if ((RuntimeType.UNDEFINED) != (end_buf_runtimeType))
        {
            const end_buf__selector : int32 = valueDeserializer.readInt8()
            let end_buf_ : string | number | Resource | undefined
            if (end_buf__selector == 0) {
                end_buf_ = (valueDeserializer.readString() as string)
            }
            else if (end_buf__selector == 1) {
                end_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (end_buf__selector == 2) {
                end_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for end_buf_ has to be chosen through deserialisation.")
            }
            end_buf = (end_buf_ as string | number | Resource)
        }
        const end_result : Dimension | undefined = end_buf
        let value : GuideLinePosition = ({start: start_result, end: end_result} as GuideLinePosition)
        return value
    }
}
export class GuideLineStyle_serializer {
    public static write(buffer: SerializerBase, value: GuideLineStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_id  = value.id
        valueSerializer.writeString(value_id)
        const value_direction  = value.direction
        valueSerializer.writeInt32(TypeChecker.Axis_ToNumeric(value_direction))
        const value_position  = value.position
        GuideLinePosition_serializer.write(valueSerializer, value_position)
    }
    public static read(buffer: DeserializerBase): GuideLineStyle {
        let valueDeserializer : DeserializerBase = buffer
        const id_result : string = (valueDeserializer.readString() as string)
        const direction_result : Axis = TypeChecker.Axis_FromNumeric(valueDeserializer.readInt32())
        const position_result : GuideLinePosition = GuideLinePosition_serializer.read(valueDeserializer)
        let value : GuideLineStyle = ({id: id_result, direction: direction_result, position: position_result} as GuideLineStyle)
        return value
    }
}
